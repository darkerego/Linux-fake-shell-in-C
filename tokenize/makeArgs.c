#include "makeArgs.h"

void clean(int argc, char **argv)
{
	int x;
	for(x=0;x<argc;x++)
	{
		free(argv[x]);
		argv[x]=NULL;
	}
	free(argv);
}// end clean

void printargs(int argc, char **argv)
{
	int x;
	for(x = 0; x < argc; x++)
		printf("%s\n", argv[x]);

}// end printargs

int makeargs(char *s, char *** argv)
{
	char copy[MAX];
	strcpy(copy,s);

	int empty = 1 , tokCount , i , addr;

	for(tokCount=0,i=0;i<strlen(copy)-1;i++)
	{
		addr = 0;
		if(copy[i]==' ')//||copy[i]=='|')
			addr = 1;
		else
			empty = 0;
		tokCount += addr;
	}

	if(empty)
		exit(-99);

	tokCount++;

	argv[0] = calloc(tokCount,sizeof(char **));
	char*saveptr=NULL;
	char*token=strtok_r(copy," ",&saveptr);

	int x,count;
	for(x=0,count=0;x<tokCount;x++,count++)
	{
		(*argv)[x] = (char*)calloc(strlen(token)+1,sizeof(char));
		strcpy((*argv)[x],token);
		token = strtok_r(NULL," ",&saveptr);
	}  
	token = NULL;
	
	return count;
}// end makeArgs
