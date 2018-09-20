#include "linkedList.h"

//CONSTRUCTOR
LinkedList * linkedList()
{
   LinkedList* new_list = (LinkedList*)calloc(1,sizeof(LinkedList));
   Node* new_head = (Node*)calloc(1,sizeof(Node));
   new_list->head = new_head;
   new_list->size=0;
   return new_list;
}
//ADD LAST
void addLast(LinkedList * theList, Node * nn)
{
   if(theList == NULL || nn == NULL)
      exit(-99);

   Node* gozer = theList->head;
   while(gozer->next != NULL)
   {
      gozer = gozer->next;
   }

   gozer->next = nn;
   nn->prev = gozer;
   theList->size++;
}
//ADD FIRST
void addFirst(LinkedList * theList, Node * nn)
{
   if(theList == NULL || nn == NULL)
      exit(-99);

   if(theList->size==0)
   {
      theList->head->next = nn;
      nn->prev = theList->head;
      theList->size =1;
   }
   else
   {
      Node* head = theList->head;
      Node* first = head->next;
   
      head->next = nn;
      first->prev = nn;
   
      nn->next = first;
      nn->prev = head;
   
      theList->size++;
   }
}
//GET FIRST
char * getFirst(LinkedList * theList , char* (*getData)(void *))
{
if(theList == NULL || theList->size < 1)
{return "BBB";}
else
{
Node* head = theList->head;
char* ret = (*getData)(head->next->data);
return ret;//(char*)(head->next->data);
}
}
//REMOVE FIRST
void removeFirst(LinkedList * theList, void (*removeData)(void *))
{
   if(theList == NULL)
      exit(-99);

   Node* head = theList->head;
   Node* first = head->next;

   if(theList->size < 2)
   {
      head->next=NULL;
      (*removeData)(first);
   }
   else
   {
      Node* second = first->next;
      head->next = second;
      second->prev = head;
      (*removeData)(first);
   }
   theList->size--;
}
//REMOVE LAST
void removeLast(LinkedList * theList, void (*removeData)(void *))
{
   if(theList == NULL)
      exit(-99);

   Node* gozer = theList->head;
   int a;
//for(a=0;a<theList->size;a++,gozer=gozer->next);
   while(gozer->next !=NULL)gozer = gozer->next;

   //while(gozer->next != NULL)
  // {gozer = gozer->next;}

   gozer->prev->next = NULL;
   gozer->next = NULL;
   gozer->prev = NULL;
   //(*removeData)(gozer->data);
   //gozer->data=NULL;
   free(gozer);
   theList->size--;
}
//REMOVE ITEM
void removeItem(LinkedList * theList, Node * nn, void (*removeData)(void *), int (*compare)(const void *, const void *))
{
   if(theList == NULL || nn == NULL)
      exit(-99);

   Node* gozer = theList->head->next;
   while(gozer->next!=NULL)
   {
      if(compare(gozer->data,nn->data)==0)
      {
         gozer->prev->next = gozer->next;
         gozer->next->prev = gozer->prev;
      }
      gozer = gozer->next;
   }
}
//CLEAR LIST
void clearList(LinkedList * theList, void (*removeData)(void *))
{
	Node * cur = theList->head->next;
	Node * temp = NULL;

	while(cur != NULL)
	{
		temp = cur;
		cur = cur->next;
		removeData(temp->data);
		free(temp);
	}
	free(theList->head);
}
//PRINT LIST
void printList(const LinkedList * theList, void (*convertData)(void *))
{
   if(theList !=NULL && theList->size>0)
   {
      Node* gozer = theList->head->next;
      while(gozer!=NULL)
      {
         (*convertData)(gozer->data);
         gozer=gozer->next;
      }
   }
   else
   {
      printf("\nEmpty List\n\n");
   }
}
//PRINT LIST N
void printListN(const LinkedList * theList, void (*convertData)(void *),int num)
{
   int i=0;
   if(theList !=NULL && theList->size>0)
   {
      Node* gozer = theList->head->next;
      while(gozer!=NULL&&i<num)
      {
         (*convertData)(gozer->data);
         gozer=gozer->next;
	 i++;
      }
   }
   else
   {
      printf("\nEmpty List\n\n");
   }
}
//GET SIZE
int getSize(const LinkedList * theList)
{
	if(theList == NULL)
		return 0;
	return theList->size;
}
