#include "./commands/myCommands.h"
#include "./pipes/pipes.h"
#include "./utils/myUtils.h"
#include "./process/process.h"
#include "./tokenize/makeArgs.h"
#include "./linkedlist/linkedList.h"
#include "./linkedlist/listUtils.h"
#include "./linkedlist/requiredIncludes.h"
//#include "./words/word.h"

int main()
{
	int histCount = 100,histFileCount=1000;

	int argc;
	char **argv = NULL;
	LinkedList * histList = linkedList();
	LinkedList * aliasList = linkedList();
	addFirst(aliasList,buildNodeAlias("bef","aft",buildAlias));
	//buildListTotal(intList, total, stdin, buildInt);
	//Node * buildNode_Type(void * passedIn);
	//addFirst(histList, buildNodeStr("line", buildTypeWord));

	int readingFromRC = 0;

	FILE * rcfile;
	rcfile = fopen(".msshrc","rwx");

	FILE * historyreader;
	historyreader = fopen(".mssh_history","r");
	
	if(historyreader)
	{
		char line[MAX];
		while(!feof(historyreader))
		{
			fgets(line,MAX,(FILE*)historyreader);
			strip(line);
			if(strcmp(line,"")!=0)
			{
				//printf("histline: %s\n",line);
				addFirst(histList,buildNodeStr(line,buildTypeWord));
			}
		}
		fclose(historyreader);
	}
	

	FILE * historyfile;
	historyfile = fopen(".mssh_history","w");
	if(!historyfile)
		printf("history file does not exist\n");
//fprintf(historyfile,"%s\n","thing");

	char buffer[100];

	if(rcfile != NULL)// file found
	{
		//printf("rc found\n");
		fgets(buffer,100,(FILE*)rcfile);//read history count
		strip(buffer);
		histCount = atoi((char*)(buffer+10));
		fgets(buffer,100,(FILE*)rcfile);
		strip(buffer);
		histFileCount = atoi((char*)(buffer+14));

		readingFromRC = 1;
		//printf("rc: %s,%d\n",buffer,histFileCount);
	//read from rc and change histcount and histfilecount
	}

	char s[MAX];
	
	if(readingFromRC)
		s[0]='\0';
	else{
		printf("command?: ");
		fgets(s,MAX,stdin);
	}
	//addFirst(histList,buildNodeStr(s,buildTypeWord));
	reduceSpaces(s);

	while(strncmp(s,"exit",4)!=0)
	{
		//if(strcmp(s,"")!=0)
		//	printf("[%s]\n",s);

		if(strncmp(s,"!!",2)==0)
		{
			strcpy(s,(char*)getFirst(histList,getTypeWord));
		}
		else if(strncmp(s,"!",1)==0)
		{// ./a.out > cmd |wc -w		
			int histDist = atoi((char *)(s+1));//parseint
		//strcpy(s,(char*)getIndex(histList,histDist,getTypeWord));
			//printf("your number:%d\n",histDist);

			int bi;
			Node * bgo;
			bgo=histList->head->next;
			for(bi=0;bi<getSize(histList) && bi<histDist &&bgo->next!=NULL;bi++)
			{
				//printf("(%s>%s)\n",getBefore(go->data),getAfter(go->data));
				bgo = bgo->next;
			}
//printf("i: %d go:%s\n",bi,(char*)getTypeWord(bgo->data));
			if((bi-0)==histDist)
				strcpy(s,(char*)getTypeWord(bgo->data));
			else
				printf("outside range\n");
			
		}

		if(strncmp(s,"history",7)==0)
		{
		   	printListN(histList, printTypeWord, histCount);
		}
		else if(strncmp(s,"PATH=$PATH:",11)==0)
		{
			char newpath[100];
			char * fullpath = getenv("PATH");
			newpath[0]='\0';
			strcat(newpath,(char*)(s+10));
		
			strcat(fullpath,newpath);
			//printf("n[%s] \n",newpath);
			setenv("PATH", fullpath, 1);
			char * oldpath = getenv("PATH");
			printf("Current env:\n[%s]\n",oldpath);

		}
		else if(strncmp(s,"cd",2)==0)
		{
			char directory[200];	
			directory[0]='\0';
			int start = 3;				
			if(strncmp(s,"cd ~",4)==0)
			{
				char * homedir = getenv("HOME");
				strcat(directory,homedir);
				start = 4;
			}
			strcat(directory,(char*)(s+start));	
			if(chdir(directory)!=0)
				printf("cd didn't work right.\n");
		}
		else if(strncmp(s,"alias",5)==0)
		{
			char * copy = calloc(100,sizeof(char));
			char * copy2 = calloc(100,sizeof(char));

			strncpy(copy,s,100);
			strncpy(copy2,s,100);

			char * before = strtok_r(copy,"=",&copy);
			 
			strtok_r(copy2,"\"",&copy2);
			char * after = strtok_r(copy2,"\"",&copy2);

			addFirst(aliasList,buildNodeAlias(((char*)before+6),after,buildAlias));
		}
		else if(strncmp(s,"unalias",7)==0)
		{
			printf("unalias is not implemented\n");
		}
		else if(countChar(s,'<') > 0 && countChar(s,'>') > 0)
		{
			printf("double redirect is not implemented\n");
		}
		else if(countChar(s,'<') > 0)
		{
			printf("< redirect is not implemented\n");
		}
		else if(countChar(s,'>') > 0)
		{
			printf("> redirect is not implemented\n");
		}
		else if(containsPipe(s) > 1)
		{
			int preCount = 0,twoCount =0,threeCount=0;
			char ** prePipe = NULL, ** twoPipe =NULL, ** threePipe = NULL;
			prePipe = parsePrePipe(s, &preCount);
			twoPipe = parsePostPipe(s, &twoCount, 1);
			threePipe = parsePostPipe(s, &threeCount, 2);		
			pipeIt(prePipe, twoPipe);
			pipeIt(twoPipe,threePipe);
		}
		else if(containsPipe(s) > 0)
		{
	
			int preCount = 0, postCount = 0;
			char ** prePipe = NULL, ** postPipe = NULL;
			prePipe = parsePrePipe(s, &preCount);
			postPipe = parsePostPipe(s, &postCount, 1);		
			pipeIt(prePipe, postPipe);
			//clean(preCount, prePipe);
			//clean(postCount, postPipe);
		}
		else if(strncmp(s,"aCheck",6)==0)
		{
			printf("aCheck:\n");
			int JJ;
			Node * go;go=aliasList->head->next;
			for(JJ=0;JJ<getSize(aliasList)&&go->next!=NULL;JJ++)
			{
				printf("(%s>%s)\n",getBefore(go->data),getAfter(go->data));
				go = go->next;
			}
		}
		else
		{
			if(strcmp(s,"")!=0)
			{
				argc = makeargs(s,&argv);

				int m,n,aliasLen = getSize(aliasList);
				Node* gozer; 
				for(m=0;m<argc;m++)
				{
					gozer = aliasList->head;
					for(n=0;n<aliasLen;n++)
					{
						if(strcmp(argv[m],getBefore(gozer->data)) == 0)
						{
							strcpy(argv[m],getAfter(gozer->data));
						}
						gozer = gozer ->next;
					}
				}

				if(argc != -1)
					forkIt(argv);
				clean(argc,argv);
				argv = NULL;
			}
		}

		if(readingFromRC)
		{
			fgets(buffer,100,(FILE*)rcfile);
			reduceSpaces(buffer);
			strcpy(s,buffer);

			if(feof(rcfile))
				readingFromRC = 0;
		}
		else
		{
			addFirst(histList,buildNodeStr(s,buildTypeWord));
			
			printf("command?: ");
			fgets(s,MAX,stdin);

			reduceSpaces(s);
		}
	}
//char * teststring = "testval";
//fprintf(historyfile,"%s\n",teststring);
	int hI,hNum=getSize(histList);
	if(hNum>histFileCount)
	hNum = histFileCount;

	Node * histGo = histList->head->next;
	for(hI=0;hI<hNum;hI++)
	{
		//fprintf(historyfile,".");
		fprintf(historyfile,"%s\n",getTypeWord(histGo->data));
		histGo=histGo->next;
	}//fprintf(historyfile,"%s\n",);}
   	free(histList);
   	histList = NULL;
	fclose(historyfile);
}

