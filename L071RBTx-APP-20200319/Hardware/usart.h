/**
******************************************************************************
* @file    usart.h
* @author  ZZF
* @version V1.0.0
* @date    10-March-2020
* @brief   Configuration file.
******************************************************************************
* @attention
*
* 
******************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __usart_H
#define __usart_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef UART1_Handler;
extern UART_HandleTypeDef UART2_Handler;
extern UART_HandleTypeDef UART5_Handler;
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

extern void _Error_Handler(char *, int);

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);
void MX_USART5_UART_Init(void);
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */


#define ENTER_CRITICAL_SECTION()	Uart_EnterCriticalSection();
#define EXIT_CRITICAL_SECTION()	Uart_ExitCriticalSection();

#define USART1_REC_LEN			256										//串口1最大接收字节数
#define USART2_REC_LEN			128										//串口2最大接收字节数

//#define USART1_CACHE_LEN			256										//串口1最大接收字节数CACHE
//#define USART2_CACHE_LEN			256										//串口2最大接收字节数CACHE

#define USART1_RXBUFFERSIZE   	1 										//HAL库使用的串口接收缓存大小
#define USART2_RXBUFFERSIZE   	1 										//HAL库使用的串口接收缓存大小

extern uint8_t USART1_RX_BUF[USART1_REC_LEN];    									//USART1接收缓冲,最大USART1_REC_LEN个字节
extern uint8_t USART2_RX_BUF[USART2_REC_LEN];    									//USART2接收缓冲,最大USART2_REC_LEN个字节

//extern uint8_t USART1_RX_CACHE_BUF[USART1_CACHE_LEN];								//USART1接收缓存2,最大USART1_CACHE_LEN个字节
//extern uint8_t USART2_RX_CACHE_BUF[USART2_CACHE_LEN];								//USART2接收缓存2,最大USART2_CACHE_LEN个字节

extern uint16_t USART1_RX_STA;												//USART1接收状态标记 bit15,接收完成标志 bit14,接收到0x0d(\n) bit13,接收中标志
extern uint16_t USART2_RX_STA;												//USART2接收状态标记 bit15,接收完成标志 bit14,接收到0x0d(\n) bit13,接收中标志

//extern uint16_t USART1_RX_CACHE_STA;											//USART1接收状态标记 bit15,接收完成标志 bit14,接收到0x0d(\n) bit13,接收中标志
//extern uint16_t USART2_RX_CACHE_STA;											//USART2接收状态标记 bit15,接收完成标志 bit14,接收到0x0d(\n) bit13,接收中标志

extern uint8_t USART1_aRxBuffer[USART1_RXBUFFERSIZE];								//HAL库使用的串口接收缓冲
extern uint8_t USART2_aRxBuffer[USART2_RXBUFFERSIZE];								//HAL库使用的串口接收缓冲

extern UART_HandleTypeDef UART1_Handler;									//UART1句柄
extern UART_HandleTypeDef UART2_Handler;									//UART2句柄


void Uart1_Init(uint32_t bound);												//串口1初始化
void Uart2_Init(uint32_t bound);												//串口2初始化
void Uart1_PortSerialEnable(uint8_t xRxEnable, uint8_t xTxEnable);						//使能/失能 发送/接收 串口中断
void Uart2_PortSerialEnable(uint8_t xRxEnable, uint8_t xTxEnable);						//使能/失能 发送/接收 串口中断

void Uart_EnterCriticalSection(void);										//进入关键操作,关闭中断,等待中断结束返回
void Uart_ExitCriticalSection(void);										//退出关键操作,开启中断

#define	USART1_DISABLE					0
#define	USART1_ENABLE					1
#define	USART1_TYPE					USART1_ENABLE						//串口1状态

#define	USART2_DISABLE					0
#define	USART2_ENABLE					1
#define	USART2_TYPE					USART2_ENABLE						//串口2状态

#define	USART3_DISABLE					0
#define	USART3_ENABLE					1
#define	USART3_TYPE					USART3_DISABLE						//串口3状态

#define	USART_IRQ_CTRL_DISABLE			0
#define	USART_IRQ_CTRL_ENABLE			1
#define	USART_IRQ_CTRL_TYPE				USART_IRQ_CTRL_ENABLE				//串口控制中断





#ifdef __cplusplus
}
#endif
#endif /*__ usart_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
