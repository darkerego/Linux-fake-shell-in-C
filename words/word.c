#include "word.h"

//Represents a command string

void cleanTypeWord(void * ptr)
{
   if(ptr == NULL)
      exit(-99);
   Word* word = (Word*)ptr;

   free(word->line);
   word->line = NULL;

   free(word);
   free(ptr);
}

void * buildTypeWord(char*array)
{
   if(array == NULL)
      exit(-99);
   
   Word* new_word = (Word*)calloc(1,sizeof(Word));

int count = 0;
while(array[count]!='\0')
{count++;}

   char*str = (char*)calloc(count,sizeof(char));
   strncpy(str,array,count);

   new_word->line = str;

//new_movie->title = "ABCD";//strncpy(new_movie->title,"ABCD",5);

   return new_word;
}

void printTypeWord(void * passedIn)
{
   Word* word = (Word*)passedIn;
   printf("?: %s\n",word->line);
}

char* getTypeWord(void * passedIn)
{
   Word* word = (Word*)passedIn;
   //printf("?: %s",word->line);
   return word->line;
}
/*
void * buildTypeMovie_Prompt(FILE * fin)
{
if(fin == NULL)
      exit(-99);
   
   Movie* new_movie = (Movie*)calloc(1,sizeof(Movie));

   size_t len=0;
   ssize_t read;


printf("Enter title: ");
   char* line=NULL;
   if((read = getline(&line,&len,fin))!=-1)
      new_movie->title = line;
   else
      new_movie->title = "Title failed to load";

printf("Enter number of actors: ");
   int numActors;
   char temp[100];
   fgets(temp,100,fin);
   numActors = atoi(temp);

//new_movie->title = "ABCD";//strncpy(new_movie->title,"ABCD",5);
   new_movie->totalActors = numActors;
   new_movie->actors = (Actor*)calloc(numActors,sizeof(Actor));
   int a;
   for(a=0;a<numActors;a++)
   {
   /* char actorLine[100];
   //fgets(actorLine,100,fin);
   new_movie->actors[a].first = strtok(actorLine," ");
   new_movie->actors[a].last =  strtok(NULL," ");*/
/*printf("Enter an actor [first last]:");
      char* actorLine=NULL;
      if((read = getline(&actorLine,&len,fin))!=-1)
      {
         new_movie->actors[a].first = strtok(actorLine," ");
         new_movie->actors[a].last  = strtok(NULL," ");
      }
      else
      {
         new_movie->actors[a].first = "actor read failed";
         new_movie->actors[a].last  = " last ";
      }
   }
   return new_movie;
}
*/

int compareWord(const void * p1, const void * p2)
{
   Word* word1 = (Word*)p1;
   Word* word2 = (Word*)p2;

   return strcmp(word1->line,word2->line);
}

//Alias
void * buildAlias(char * before, char * after)
{     
if(before == NULL || after == NULL)
      exit(-99);
   
   Alias* new_alias = (Alias*)calloc(1,sizeof(Alias));

int bCount = 0,aCount =0;
while(before[bCount]!='\0')
{bCount++;}
while(after[aCount]!='\0')
{aCount++;}

char*befStr = (char*)calloc(bCount,sizeof(char));
char*aftStr = (char*)calloc(aCount,sizeof(char));
strncpy(befStr,before,bCount);
strncpy(aftStr,after ,aCount);

new_alias->before = befStr;
new_alias->after  = aftStr;

//new_movie->title = "ABCD";//strncpy(new_movie->title,"ABCD",5);

   return new_alias;
}

char* getBefore(void * passedIn)
{
if(passedIn == NULL)
return "null";
//printf("getBef\n");
  Alias* alias = (Alias*)passedIn;
   return alias->before;
}

char* getAfter(void * passedIn)
{
Alias* alias = (Alias*)passedIn;
   return alias->after;
}

