/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __FIFOMEASSAGE_H
#define __FIFOMEASSAGE_H

/* Includes ------------------------------------------------------------------*/
#include "Common.h"

typedef struct queue 
{
	int *pBase;
	int front;    //指向队列第一个元素
	int rear;    //指向队列最后一个元素的下一个元素
	int maxsize; //循环队列的最大存储空间
}QUEUE,*PQUEUE;

/* Exported types ------------------------------------------------------------*/


/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

int CreateQueue(PQUEUE Q,int maxsize);
void TraverseQueue(PQUEUE Q);
int FullQueue(PQUEUE Q);
int EmptyQueue(PQUEUE Q);
int Enqueue(PQUEUE Q, int val);
int Dequeue(PQUEUE Q, int *val);

int Test_FIFOmessage(void);




#endif /* __FIFOMEASSAGE_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/







