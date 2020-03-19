/**
*********************************************************************************************************
* @file    Debug.c
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

/* Define to prevent recursive inclusion -------------------------------------*/


/* Includes ------------------------------------------------------------------*/
#include "Debug.h"
#include "string.h"
#include "stdio.h"
#include "main.h"


__IO uint8_t SYSTEM_DEBUG = 1;

#include "usart.h"

#ifdef BUG
#define PRINTF_USART			USART2									//Printf使用串口
#endif

int fputc(int ch, FILE *f)
{
    /* Place your implementation of fputc here */
    /* e.g. write a character to the USART2 and Loop until the end of transmission */
#ifdef BUG
if(SYSTEM_DEBUG)
{
    PRINTF_USART->TDR = ch;
    while ((PRINTF_USART->ISR & 0X40) == 0)
        ;
}
#endif
    return ch;
}


/********************************************** END OF FLEE **********************************************/
