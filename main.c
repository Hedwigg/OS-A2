#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

/*Node object*/
struct Node
{
  int data;
  struct Node *next;
  struct Node *prev;
};

struct Node *head;		//pointer to head of D-LL
int maxBufferSize = 30;
int currentBufferSize = 1;
bool BufferStatus = 0; // 0 = not full, 1 = buffer full.

//Creates a new Node and returns pointer to it. (helper function for InsertAtEnd)
struct Node *
GetNewNode (int x)
{
  struct Node *newNode = (struct Node *) malloc (sizeof (struct Node));
  newNode->data = x;
  newNode->prev = NULL;
  newNode->next = NULL;
  return newNode;
}

//Inserts a Node at tail of Doubly linked list
void InsertAtEnd (int x)
{
  struct Node *temp = head;
  struct Node *newNode = GetNewNode (x);
  if (head == NULL)
    {
      head = newNode;
      return;
    }
  while (temp->next != NULL)
    temp = temp->next;		// Go To last Node
  temp->next = newNode;
  newNode->prev = temp;
  currentBufferSize++;		//increment buffer size
}



//Prints all the elements in linked list in forward traversal order
void PrintBuffer ()
{
  struct Node *temp = head;
  printf ("Buffer: ");
  while (temp != NULL)
    {
      printf ("%d ", temp->data);
      temp = temp->next;
    }
  printf ("\n");
}

/*
Producer # 1 will generate a node and add it at the end of the linked list, the
value of the new node is a random ODD integer less than 50.
*/
void P1 ()
{
    printf("in p1 \n");
    printf("%d", currentBufferSize);
    printf("\n");
    PrintBuffer();

    if(BufferStatus == 1) //if buffer is full
    {
      //generate a full message and wait.

    }
    else//if buffer is not full
    {
        int r;
        while(r % 2 == 1)
        {
            printf("buffer not full: producing a node : ");
            r = rand() % 50;
            printf("%d", r);
        }
        //int r = rand () % 50; //generate random ODD int < 50s
        InsertAtEnd (r);
        printf("not full");
        if(currentBufferSize > 29)
        {
            BufferStatus = 1;
        }
    }

}

/*
Producer #2 will generate a node and add it at the end of the linked list, the
value of the new node is a random EVEN integer less than 50.
*/
void P2 ()
{

}

/*
Consumer #1 will delete, from the ehad of the list, the first node whos value is ODD
(if the first node has an even value, then wait). When the buffer is empty, both should
generate a message and wait.
*/
void C1 ()
{

}

/*
Consumer # 2 will delete, from the head of the list, the first node whos value is even
(if the first node has an odd value, then wait). When the buffer is empty, both should
generate a message and wait.
*/

void C2 ()
{

}




// ___Main execution funciton___
int main ()
{
  /*Create Buffer & initialize with 3 nodes */
  int r;
  srand ( time(NULL) ); //seed random with the current time for more random r values
  for (int i = 0; i < 3; i++)
    {
      //random int between 0 and 50 for node value.
      r = rand() % 50;
      InsertAtEnd (r);
    }
  printf ("Initial buffer-");
  PrintBuffer ();

  //Threads
  P1(); //not in the form of a thread for testing


}
