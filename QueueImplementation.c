/*   ------------< begin file "QueueImplementation.c" >------------   */

   #include <stdio.h>                   
   #include <stdlib.h>                 
   #include "QueueInterface.h"         
                                       

   void SystemError(char *errorMsg) {fprintf(stderr,"%s\n", errorMsg);}

   void InitializeQueue(Queue *Q)
   {
      Q->Front = NULL;
      Q->Rear  = NULL;
   }

 /* -------------------- */

   int Empty(Queue *Q)
   {
      return (Q->Front == NULL);
   }
 /* -------------------- */

   int Full(Queue *Q)   
   {                     /* we assume an already constructed queue, Q, is */
      return 0;              /* not full, since it could potentially grow */
   }                                             /* as a linked structure */

/* -------------------- */

   int Insert(ItemType R, Queue *Q)
   {   
      QueueNode *Temp;
                                                   /* attempt to allocate */
      Temp = (QueueNode *) malloc(sizeof(QueueNode));       /* a new node */

      if (Temp == NULL) {               /* Temp = NULL signals allocation */
         SystemError("system storage is exhausted");           /* failure */
	 return 0;
      } else {
         Temp->Item = R;
         Temp->Link = NULL;
         if ( Q->Rear == NULL ) {
            Q->Front = Temp;
            Q->Rear = Temp;
         } else {
            Q->Rear->Link = Temp;
            Q->Rear = Temp;
         }
      }
      return 1;
   }

/* -------------------- */

   int Remove(Queue *Q, ItemType *F)
   {   
      QueueNode *Temp;

      if (Q->Front == NULL) {
         SystemError("attempt to remove item from empty Queue");
	 return 0 ;
      } else {
         *F = Q->Front->Item;
         Temp = Q->Front;
         Q->Front = Temp->Link;
         free(Temp);
         if (Q->Front == NULL) Q->Rear = NULL;
	 return 1;
      }
   }

/* -------------------- */
      


