#include "myUtils.h"

void strip(char *array)
{
	if(array == NULL)
	{
		perror("array is null");
		exit(-99);
	}// end if

	int len = strlen(array), x = 0;
   
	while(array[x] != '\0' && x < len)
	{
	  if(array[x] == '\r')
		 array[x] = '\0';

	  else if(array[x] == '\n')
		 array[x] = '\0';

	  x++;

	}// end while
   
}// end strip

void removeTrailingSpaces(char *array)
{
	if(array == NULL)
	{
		perror("array is null");
		exit(-99);
	}// end if

	int firstOfLast = -1, len = strlen(array), x = 0;
   
	while(array[x] != '\0' && x < len)
	{
	  if(array[x] == ' ')
	  {
	    if(firstOfLast == -1)
	      firstOfLast = x;
	  }
	  else if(array[x] != '\r' && array[x] != '\n' && array[x] != '\0')	
	    firstOfLast = -1;

	  if(array[x] == '\r')
		 array[x] = '\0';

	  else if(array[x] == '\n')
		 array[x] = '\0';

	  x++;

	}// end while

	array[firstOfLast] = '\0' ;  
}// end strip

void reduceSpaces(char *array)
{
	strip(array);
	int begin=-1,end=-1;

	int len = strlen(array), x = 0;
	while(array[x] != '\0' && x<len)
	{
		if(array[x] != ' ' && array[x] != '\0')
		{
			end = x;
			if(begin == -1)
			 	begin = x;
		}
		x++;
	}
	char copy[MAX];
	strcpy(copy,array);

	int i,space=1;
	for(i=0,x=begin;x<end+1;x++)
	{
		if(array[x] != ' ')
		{
			array[i] = copy[x];
			i++;
			space = 1;
		}
		else if(space == 1)
		{
			array[i] = copy[x];
			i++;
			space = 0;
		}
	}
	array[i]='\0';
}

int countChar(char*array,char key)
{
	int count = 0, x = 0;
	while(array[x]!='\0')
	{
		if(array[x]==key)
			count++;
		x++;
	}
	return count;
}

int menu()
{
   char temp[MAX];
   int choice;
   printf("1) Print the list\n");
   printf("2) Add First\n");
   printf("3) Add Last\n");
   printf("4) Sort\n");
   printf("5) Remove Item\n"); 
   printf("6) Quit\n"); 
   printf("Choice --> ");
   fgets(temp, MAX, stdin);
   choice = atoi(temp);

   
   while(choice < 1 || choice > 6)
   {
      printf("1) Print the list\n");
      printf("2) Add First\n");
      printf("3) Add Last\n");
      printf("4) Sort\n");
      printf("5) Remove Item\n"); 
      printf("6) Quit\n"); 
      printf("Choice --> ");
      fgets(temp, MAX, stdin);
      choice = atoi(temp);
   
   }// end while

   return choice;
   
}// end menu

