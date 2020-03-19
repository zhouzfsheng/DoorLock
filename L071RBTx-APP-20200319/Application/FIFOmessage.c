/**
  *********************************************************************************************************
  * @file    fifomessage.c
  * @author  LockPlate -- ZZF
  * @version V1.0
  * @date    2019-5-15
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "common.h"
#include "FIFOmessage.h"

# include <stdio.h>
# include <stdlib.h>

/***********************************************
Function: Create a empty stack;
************************************************/
int CreateQueue(PQUEUE Q,int maxsize)
{
	Q->pBase=(int *)malloc(sizeof(int)*maxsize);
	if(NULL==Q->pBase)
	{
		printf("Memory allocation failure");
		return (-1);        //退出程序
	}
	Q->front=0;         //初始化參数
	Q->rear=0;
	Q->maxsize=maxsize;
}
/***********************************************
Function: Print the stack element;
************************************************/
void TraverseQueue(PQUEUE Q)
{
	int i=Q->front;
	printf("队中的元素是:\n");
	while(i%Q->maxsize!=Q->rear)
	{
		printf("%d ",Q->pBase[i]);
		i++;
	}
	printf("\n");
}
int FullQueue(PQUEUE Q)
{
	if(Q->front==(Q->rear+1)%Q->maxsize)    //推断循环链表是否满，留一个预留空间不用
	{
//		printf("队列满\n");
		return 1;
	}
	else
		return 0;
}

int EmptyQueue(PQUEUE Q)
{
	if(Q->front==Q->rear)    //推断是否为空
		return 1;
	else
		return 0;
}

int Enqueue(PQUEUE Q, int val)
{
	if(FullQueue(Q))
		return 0;
	else
	{
		Q->pBase[Q->rear]=val;
		Q->rear=(Q->rear+1)%Q->maxsize;
		return 1;
	}
}

int Dequeue(PQUEUE Q, int *val)
{
	if(EmptyQueue(Q))
	{
		return 0;
	}
	else
	{
		*val=Q->pBase[Q->front];
		Q->front=(Q->front+1)%Q->maxsize;
		return 1;
	}
}


int Test_FIFOmessage(void)
{
    QUEUE Q;

    CreateQueue(&Q,12);
    Enqueue(&Q,1);
    Enqueue(&Q,2);
    Enqueue(&Q,3);
    Enqueue(&Q,4);

    TraverseQueue(&Q);

    int val;

    if(Dequeue(&Q,&val)){
        printf("出列成功，出列的值：%d \n",val);
    }
		if(Dequeue(&Q,&val)){
        printf("出列成功，出列的值：%d \n",val);
    }

    TraverseQueue(&Q);

    return 0;
}


//typedef struct Node
//{
//    int data;               //节点数据域
//    struct Node * next; //节点指向下一个元素的指针域
//}Node,* pNode;

//typedef struct LinkQueue
//{
//    pNode front;  //队头指针
//    pNode rear;   //队尾指针
//}LinkQueue, * pLinkQueue;

////初始化队列
//void init(pLinkQueue Q);
////销毁队列
//void DestroyQueue(pLinkQueue Q);
////判断队列是否为空
//int is_empty(pLinkQueue Q);
////入列
//void en_queue(pLinkQueue Q,int val);
////出列
//int de_queue(pLinkQueue Q,int * pVal);
////遍历输出队列元素
//void treaverse(pLinkQueue Q);

//int Test_FIFOmessage(void)
//{
//    LinkQueue Q;

//    init(&Q);
//    en_queue(&Q,1);
//    en_queue(&Q,2);
//    en_queue(&Q,3);
//    en_queue(&Q,4);

//    treaverse(&Q);

//    int val;

//    if(de_queue(&Q,&val)){
//        printf("出列成功，出列的值：%d \n",val);
//    }

//    treaverse(&Q);

//    return 0;
//}

//void init(pLinkQueue Q)
//{
//    //构造一个空队列Q，只有一个头节点
//    Q->front = Q->rear = (pNode)malloc(sizeof(Node));
//    if(Q->front == NULL){
//        printf("内存分配失败！");
//    }

//    Q->front->next = NULL;      //创建一个头节点，头节点的指针域没有指向下一个
//}

//void en_queue(pLinkQueue Q, int val)
//{   
//    //入队，从队列尾部开始
//    //创建一个节点
//    pNode pNew = (pNode)malloc(sizeof(Node));
//    if(pNew == NULL)
//    {   
//        printf("开辟内存空间失败");
//    }else{
//        pNew->data = val;        //赋值
//        pNew->next = NULL; 

//        Q->rear->next = pNew;
//        Q->rear = pNew;
//    }
//}

//int is_empty(pLinkQueue Q)
//{
//    if(Q->front == Q->rear) //队列头无指向就为空 || 或者队列头尾相等，说明是初始化时状态
//        return 1;
//    else 
//        return 0;
//}

//int de_queue(pLinkQueue Q,int *pVal)
//{
//    //出列
//    if(is_empty(Q))
//    {
//        return 0;
//    }else{
//        pNode p = Q->front;     //出列从头节点开始
//        *pVal = p->next->data;
//        Q->front = Q->front->next;      //摘下头节点
//        if(Q->rear == p)        //如果出列到最后一个了，如果不互相等，那么队列尾就消失了 
//        { 
//            Q->rear = Q->front;
//        }
//        free(p);                //释放节点空间
//        return 1;
//    }
//}

//void treaverse(pLinkQueue Q)
//{
//    pNode p = Q->front->next;

//    while(p != NULL)
//    {
//        printf("%d ", p->data);
//        p = p->next;
//    }           

//    printf("\n");
//}




