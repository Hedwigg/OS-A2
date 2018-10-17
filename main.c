/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>


/*Node object*/
struct Node  {
	int data;
	struct Node* next;
	struct Node* prev;
};

struct Node* head; //pointer to head of D-LL

//Creates a new Node and returns pointer to it.
struct Node* GetNewNode(int x) {
	struct Node* newNode
		= (struct Node*)malloc(sizeof(struct Node));
	newNode->data = x;
	newNode->prev = NULL;
	newNode->next = NULL;
	return newNode;
}

//Inserts a Node at tail of Doubly linked list
void InsertAtEnd(int x) {
	struct Node* temp = head;
	struct Node* newNode = GetNewNode(x);
	if(head == NULL) {
		head = newNode;
		return;
	}
	while(temp->next != NULL) temp = temp->next; // Go To last Node
	temp->next = newNode;
	newNode->prev = temp;
}



//Prints all the elements in linked list in forward traversal order
void PrintBuffer() {
	struct Node* temp = head;
	printf("Buffer: ");
	while(temp != NULL) {
		printf("%d ",temp->data);
		temp = temp->next;
	}
	printf("\n");
}


int main()
{
    /*Create Buffer & initialize with 3 nodes*/
    int r;
    for(int i = 0; i<3; i++)
    {
        //random int between 0 and 50 for node value.
        r = rand() % 50;
        InsertAtEnd(r);
    }
    PrintBuffer();
}
