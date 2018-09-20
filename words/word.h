#ifndef WORD_H_
#define WORD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../utils/myUtils.h"

struct alias
{
   char * before;
   char * after;
};

typedef struct alias Alias;

struct word
{
   char * line;
};

typedef struct word Word;

//Word
void cleanTypeWord(void * ptr);

void * buildTypeWord(char * array);

void printTypeWord(void * passedIn);

char* getTypeWord(void * passedIn);

int compareWord(const void * p1, const void * p2);

//Alias
void * buildAlias(char * from, char * to);

char* getBefore(void * passedIn);

char* getAfter(void * passedIn);

#endif /* WORD_H_ */
