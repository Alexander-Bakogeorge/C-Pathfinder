/*   ------------< begin file "QueueInterface.h" >------------     */


#include "UserTypes.h"                          /* get ItemType definition */

typedef  struct  QueueNodeTag {
            ItemType               Item;   
            struct  QueueNodeTag  *Link;
         }QueueNode;
                     
typedef  struct {                                 /* a queue is empty iff */
            QueueNode  *Front;                       /* its Front == NULL */
            QueueNode  *Rear;
         }Queue;


/* defined operations */

   extern void InitializeQueue(Queue *Q);
      /* Initialize the queue Q to be the empty queue */

   extern int Empty(Queue *Q);
      /* Returns TRUE == 1 if and only if the queue Q is empty */

   extern int Full(Queue *Q);
      /* Returns TRUE == 1 if and only if the queue Q is full */

   extern int Insert(ItemType R, Queue *Q);
      /* If Q is not full, insert a new item R onto the rear of Q */

   extern int Remove(Queue *Q, ItemType *F);
      /* If Q is non-empty, remove the frontmost item of Q and put it in F */

/*   ------------< end-of-file "QueueInterface.h" >------------    */


