#include "STD_Types.h"
#include "LinkedList.h"
#include <stdlib.h>
#include <stdio.h>

extern node head  ;
u32 ListLength = 0;

void AddNode(u32 val)
{
	/* First Node to Create */
	if (ListLength == 0)
	{
		head.value = val ;
		head.Next  = NULL; 
	}
	
	
	else
	{
		node *last;
		
		/* Allocate the node */
		node *new = (node*) malloc(sizeof(node));
		
		/* Assign the received value to the new node */
		new -> value = val;
		/* Make the new node next pointer to Null, as it will 
		be added to the end of the list */
		new -> Next  = NULL;
		
		last = &head;
		
		/* Search for the last node */
		while( (last -> Next) != NULL )
		{
			last = (last -> Next);
		}
		
		last -> Next = new;
	}
	
	/* Increase the list length by one node */
	ListLength++;
	
	return;
}

void PrintLinkedList(void)
{
	printf("\n\n----------------------\n");
	/* at lease 1 node is created */
	if (ListLength > 0)
	{
		node *Last = &head;
		u32 i = 1;
		
		/* Print the list head */
		printf("Node Number %d = %d\n", i,Last -> value);
	
		/* Print all nodes util you find the last node
		which has the next pointer equals to NULL  */
		while ((Last -> Next) != NULL)
		{
			i++;
			Last = Last -> Next;
			printf("Node Number %d = %d\n", i,Last -> value);
		}
	}
	
	else
	{
		printf("List is Empty\n");
	}
	
	printf("----------------------\n\n\n");
}