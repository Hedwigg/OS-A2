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
bool BufferFull = 0;
bool BufferEmpty = 0;

pthread_mutex_t lock; //mutex lock for threads




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

//Buffer full message
void bufferFullMessage()
{
    printf("buffer is full");
}

//buffer empty message
void bufferEmptyMessage()
{
    printf("buffer is empty");   
}

/*
Producer # 1 will generate a node and add it at the end of the linked list, the
value of the new node is a random ODD integer less than 50.

Producer #2 will generate a node and add it at the end of the linked list, the
value of the new node is a random EVEN integer less than 50.

Consumer #1 will delete, from the ehad of the list, the first node whos value is ODD
(if the first node has an even value, then wait). When the buffer is empty, both should
generate a message and wait.

Consumer # 2 will delete, from the head of the list, the first node whos value is even
(if the first node has an odd value, then wait). When the buffer is empty, both should
generate a message and wait.
*/
void *produceOrConsume(void *tID_point)
{
    int *tID = (int *)tID_point;
    
    printf("in a thread");
    printf("%d ---" , *tID);
    
    
    pthread_mutex_lock(&lock); //lock

    if(*tID == 1)  //Producer 1 (odd)
    {
        //printf("\nin 1\n ");
        
        //https://stackoverflow.com/questions/13675132/pthread-cond-wait-for-2-threads
        
        if(BufferFull == 1) 
        {
         bufferFullMessage();  
         pthread_cond_wait(&BufferFull,&lock);
        }
        
    }else if(*tID ==2) //Producer 2 (even)
    {
        //printf("\nin 2\n ");
   
    }else if(*tID ==3) //Consumer 1 (odd)
    {
        // printf("\nin 3\n ");

        
    }else if(*tID ==4) //Consumer 2 (even)
    {
        //printf("\nin 4\n ");

    }else
    {
        printf("error in produceOrConsume");
    }
    
    pthread_mutex_unlock(&lock); //unlock

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
    pthread_t thread1; //Producer 1
    pthread_t thread2; //Producer 2
    pthread_t thread3; //Consumer 1
    pthread_t thread4; //Consumer 2
    int P1 = 1;
    int P2 = 2;
    int C1 = 3;
    int C2 = 4;
    
    pthread_create(&thread1, NULL, produceOrConsume, &P1);
    pthread_create(&thread2, NULL, produceOrConsume, &P2);
    pthread_create(&thread3, NULL, produceOrConsume, &C1);
    pthread_create(&thread4, NULL, produceOrConsume, &C2);

//Join threads after finished.
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    pthread_join(thread4, NULL);


    
}


