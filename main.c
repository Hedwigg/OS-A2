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

//Inserts a Node at head of doubly linked list
void InsertAtHead(int x) {
	struct Node* newNode = GetNewNode(x);
	if(head == NULL) {
		head = newNode;
		return;
	}
	head->prev = newNode;
	newNode->next = head;
	head = newNode;


}

//Prints all the elements in linked list in forward traversal order
void Print() {
	struct Node* temp = head;
	printf("Forward: ");
	while(temp != NULL) {
		printf("%d ",temp->data);
		temp = temp->next;
	}
	printf("\n");
}


int main()
{
    /*Create Buffer */
    int r;
    for(int i = 0; i<30; i++)
    {
        //random int between 0 and 50 for node value.
        r = rand() % 50;
        InsertAtHead(r); Print();
    }
}
