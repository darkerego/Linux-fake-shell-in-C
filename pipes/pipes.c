#include "pipes.h"
#include "../tokenize/makeArgs.h"
#include "../utils/myUtils.h"

int containsPipe(char *s)
{
	char trav = s[0];
	int i=0,ret = 0;
	while(trav != '\0')
	{
		i++;
		trav = s[i]; 
		if(trav == '|')
			ret ++;
	}

//printf("Number of pipes:[%d]\n",ret);
	return ret;
}

char ** parsePrePipe(char *s, int * preCount)
{//COPY NUMBNUTS
	char * copy = calloc(MAX,sizeof(char));
	strcpy(copy,s);

	char*saveptr=NULL;
	char*token=strtok_r(copy,"|",&saveptr);

	char ** ret;
	*preCount = makeargs(token,&ret);

//printf("prePipe: [%s][%s]   preCount:[%d]\n",ret[0],ret[1],*preCount);

	return ret;
}

char ** parsePostPipe(char *s, int * postCount, int count)
{
	char * copy = calloc(MAX,sizeof(char));
	strcpy(copy,s);
	int x = 0;	
	for(x=0;x<count;x++)
		strtok_r(copy,"|",&copy);
	char * subString;
	subString = strtok_r(copy,"|",&copy);

	reduceSpaces(subString);

	char ** ret;
	*postCount = makeargs(subString,&ret);

	return ret;
}

void pipeIt(char ** prePipe, char ** postPipe)
{
	pid_t pid1 = fork();
	int status;
	if(pid1!=0)
	{
		waitpid(pid1,&status,0);
	}
	else
	{
		//pipe
		pid_t pid;
		int fd[2], res, status;

		res = pipe(fd);

		if(res < 0)
		{
			printf("Pipe Failure\n");
			exit(-1);
		}// end if

		pid = fork();
		int res2;
	
		if(pid != 0)
		{
			close(fd[1]);
			close(0);
			dup2(fd[0],0);
			close(fd[0]);
			res2 = execvp(postPipe[0],postPipe);	
			exit(res2);
		}// end if AKA parent
		else
		{
			waitpid(pid,&status,0);

			close(fd[0]);
			close(1);
			dup2(fd[1],1);
			close(fd[1]);
			res2 = execvp(prePipe[0],prePipe);
			exit(res2);
		}// end else AKA child
	}
	
}



