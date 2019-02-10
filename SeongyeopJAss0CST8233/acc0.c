/**********************************************************************
Filename: acc0.c
Version: 1.0
Author: Seong-yeop Jeong
Student No: 040885882
Course Name/Number: Numerical Computing CST8233
Lab Sect: 304
Assignment #: 0
Assignment name: Raster Graphic Project in C
Due Date: September 22 2018
Submission Date: September 18 2018
Professor: Andrew Tyler
Purpose: By using linked list, the program insert and delete user input into specific position.
		 Also, it reports(display) data what it is in by 1 second. 
		 When program delete data, it frees memory as well as quiting program.
*********************************************************************/

// ass0.c
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC	// need this to get the line identification
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF|_CRTDBG_LEAK_CHECK_DF); // in main, after local declarations
//NB must be in debug build

#include <crtdbg.h>
#include <stdio.h>
#include <time.h>

typedef enum
{
	FALSE = 0,
	TRUE
} BOOL;

/* Struct for data and linked list */
struct GraphicElement {
	char* fileName;
	struct GraphicElement* pNext;
};

struct RasterGraphic {
	struct GraphicElement* GraphicElements;
};

// Forward declarations
void InitRasterGraphic(struct RasterGraphic*);
void InsertGraphicElement(struct RasterGraphic*);
void DeleteGraphicElement(struct RasterGraphic*);
void ReportRasterGraphic(struct RasterGraphic*);
void CleanUp(struct RasterGraphic*);

int main(void)
{
	char response;
	BOOL RUNNING = TRUE;
	struct RasterGraphic RG;
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	InitRasterGraphic(&RG);

	while (RUNNING)
	{
		printf("MENU\n 1. Insert a GraphicElement\n 2. Delete the first GraphicElement\n 3. Report the RasterGraphic\n 4. Quit\n");
		scanf("%c", &response);
		switch (response)
		{
		case '1':InsertGraphicElement(&RG);
			break;
		case '2':DeleteGraphicElement(&RG);
			break;
		case '3':ReportRasterGraphic(&RG);
			break;
		case '4':RUNNING = FALSE;
			CleanUp(&RG);
			break;
		default:printf("Please enter a valid option\n");
		}
		printf("\n");
		while ((response = getchar()) != '\n' && response != EOF);// clear input buffer
	}
	return 0;
}

/********************************************************************
Function name: InitRasterGraphic
Purpose: initialize the variables in the struct RasterGraphic
In parameters: RasterGraphic pointer
Out parameters: return an empty content of RasterGraphic
Version: 1.0
Author: Seongyeop Jeong
**********************************************************************/
void InitRasterGraphic(struct RasterGraphic* pA)
{
	pA->GraphicElements = NULL;
}

/********************************************************************
Function name: InsertGraphicElement
Purpose: insert a new graphic element to RasterGraphic at a specific position
In parameters: RasterGraphic pointer
Out parameters: return the graphic element by user insert into RasterGraphic    
Version: 1.0
Author: Seongyeop Jeong
**********************************************************************/
void InsertGraphicElement(struct RasterGraphic* pA)
{
	int count = 0;
	int idx = 0;
	char fileName[30];
	/* adding node in ordering. */
	struct GraphicElement* head = (struct GraphicElement*) malloc(sizeof(struct GraphicElement));
	head->fileName = (char *)malloc(strlen(fileName) + 1); /* allocate memory of char */

	printf("Insert a GraphicElement in the RasterGraphic\n");
	printf("Please enter the GraphicElement filename: ");
	scanf("%30s", &fileName);
	strcpy(head->fileName, fileName);

	struct GraphicElement* current;
	current = pA->GraphicElements;
	struct GraphicElement* previous;
	/* when the linkedlist is empty, add one into first position */
	if (pA->GraphicElements == NULL)
	{
		head->pNext = NULL; 
		printf("This is the first GraphicElement in the list\n");
		pA->GraphicElements = head;
		return;
	}
	else if (head == NULL)
		return;
	/* when the linkedlist is not empty, add node into specified position */
	else 
	{
		count = 0; /* to count how many linked list is in. */
		current = pA->GraphicElements;
		while (current != NULL) /* count items in linked list */
		{
			current = current->pNext;
			count++;
		}

		printf("There are %d GraphicElement(s) in the list. Please specify the position (<= %d) to insert at : ", count, count);
		scanf("%d", &idx);

		if (idx == 0) /* when there is just only one node. */
		{
			head->pNext = pA->GraphicElements; 
			pA->GraphicElements = head;
			return;
		}
		/* avoid numbers negative numbers */
		while (idx < 0 || idx > count)
		{
			printf("Enter the valid index for position\n\n");
			printf("There are %d GraphicElement(s) in the list. Please specify the position (<= %d) to insert at : ", count, count);
			scanf("%d", &idx);

			if (0 < idx && idx <= count) /* to check arrange */
				break;
			else if (idx < count && idx > 0) /* to check negative numbrs */
				break;
		}
		
		int counts = 0;
		current = pA->GraphicElements;
		while (counts < idx)
		{
			previous = current; 
			current = current->pNext;
			counts++;
		}
		previous->pNext = head; 
		head->pNext = current;
		return;
	}

}

/********************************************************************
Function name: DeleteGraphicElement
Purpose: it is to delete an element with free memory in the RasterGraphic
In parameters: RasterGraphic pointer
Out parameters: a deleted GraphicElement in the RasterGraphic
Version: 1.0
Author: Seongyeop Jeong
**********************************************************************/
void DeleteGraphicElement(struct RasterGraphic* pA)
{
	struct GraphicElement* removeNode;
	/* When the GraphicElements are empty list, */

	if (pA->GraphicElements == NULL)
	{
		printf("There is no any Graphic elements in the list\n");
	}
	else 
	{
		removeNode = pA->GraphicElements;
		pA->GraphicElements = removeNode->pNext;
		free(removeNode->fileName); /* free memory in the part of removeNode */
		free(removeNode); /* free memory for removeNode */

		printf("Delete the first Graphic elements\n");
	}
}

/********************************************************************
Function name: CleanUp
Purpose: free memory with all elements in the RasterGraphic
In parameters: RasterGraphic pointer
Out parameters: the empty GraphicElement in the RasterGraphic 
Version: 1.0
Author: Seongyeop Jeong
**********************************************************************/
void CleanUp(struct RasterGraphic* pA)
{
	struct GraphicElement* iterator;
	
	/* to protect from clash when there is empty list */
	if (pA->GraphicElements == NULL)
		return;
	else
	{
		iterator = pA->GraphicElements;
		while (iterator != NULL)
		{
			iterator = iterator->pNext;
			free(pA->GraphicElements->fileName);
			free(pA->GraphicElements);
			pA->GraphicElements = iterator;
		}
		printf("Exit Program..\n");
	}
}

void ReportRasterGraphic(struct RasterGraphic* pA)
{
	int counter = 0;
	time_t startsec, oldsec, newsec;
	struct GraphicElement* iterator = pA->GraphicElements;

	if (pA->GraphicElements == 0)
	{
		printf("No GraphicElements in the RasterGraphic\n");
		return;
	}

	printf("Report the RasterGraphic\n");
	startsec = oldsec = time(NULL);
	while (iterator)
	{
		newsec = time(NULL);
		if (newsec > oldsec)
		{
			printf("GraphicElement #%d, time = %I64d sec\n", counter++, newsec - startsec);
			printf("Image file name = %s\n", iterator->fileName);
			iterator = iterator->pNext;
			oldsec = newsec;
		}
	}
}