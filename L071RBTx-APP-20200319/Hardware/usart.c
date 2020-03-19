/**
  *********************************************************************************************************
  * @file    usart.c
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
/* Includes ------------------------------------------------------------------*/
#include "usart.h"

#include "gpio.h"

/* USER CODE BEGIN 0 */

uint8_t USART1_RX_BUF[USART1_REC_LEN];    										//USART1接收缓冲,最大USART1_REC_LEN个字节
uint8_t USART2_RX_BUF[USART2_REC_LEN];    										//USART2接收缓冲,最大USART2_REC_LEN个字节

//uint8_t USART1_RX_CACHE_BUF[USART1_CACHE_LEN];									//USART1接收缓存2,最大USART1_CACHE_LEN个字节
//uint8_t USART2_RX_CACHE_BUF[USART2_CACHE_LEN];									//USART2接收缓存2,最大USART2_CACHE_LEN个字节

uint16_t USART1_RX_STA = 0;													//USART1接收状态标记 bit15,接收完成标志 bit14,接收到0x0d(\n) bit13,接收中标志
uint16_t USART2_RX_STA = 0;													//USART2接收状态标记 bit15,接收完成标志 bit14,接收到0x0d(\n) bit13,接收中标志

uint16_t USART1_RX_CACHE_STA = 0;												//USART1接收状态标记 bit15,接收完成标志 bit14,接收到0x0d(\n) bit13,接收中标志
uint16_t USART2_RX_CACHE_STA = 0;												//USART2接收状态标记 bit15,接收完成标志 bit14,接收到0x0d(\n) bit13,接收中标志

uint8_t USART1_aRxBuffer[USART1_RXBUFFERSIZE];									//HAL库使用的串口接收缓冲
uint8_t USART2_aRxBuffer[USART2_RXBUFFERSIZE];									//HAL库使用的串口接收缓冲

/* USER CODE END 0 */

UART_HandleTypeDef UART1_Handler;											//UART1句柄
UART_HandleTypeDef UART2_Handler;											//UART2句柄
UART_HandleTypeDef UART5_Handler;											//UART2句柄

/**********************************************************************************************************
 @Function			void MX_USART1_UART_Init(void)
 @Description		MX_USART1_UART_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void MX_USART1_UART_Init(void)
{

  UART1_Handler.Instance = USART1;
  UART1_Handler.Init.BaudRate = 115200;
  UART1_Handler.Init.WordLength = UART_WORDLENGTH_8B;
  UART1_Handler.Init.StopBits = UART_STOPBITS_1;
  UART1_Handler.Init.Parity = UART_PARITY_NONE;
  UART1_Handler.Init.Mode = UART_MODE_TX_RX;
  UART1_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UART1_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
  UART1_Handler.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  UART1_Handler.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&UART1_Handler) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/**********************************************************************************************************
 @Function			void HAL_UART_MspInit(void)
 @Description		HAL_UART_MspInit	
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void HAL_UART_MspInit(UART_HandleTypeDef* uartHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART1_CLK_ENABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9|GPIO_PIN_10;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART1_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
	else  if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART2_CLK_ENABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /* USART1 interrupt Init */
    HAL_NVIC_SetPriority(USART2_IRQn, 1, 0);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
	else  if(uartHandle->Instance==USART5)
  {
  /* USER CODE BEGIN USART1_MspInit 0 */

  /* USER CODE END USART1_MspInit 0 */
    /* USART1 clock enable */
    __HAL_RCC_USART5_CLK_ENABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF6_USART5;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN USART1_MspInit 1 */

  /* USER CODE END USART1_MspInit 1 */
  }
	
}
/**********************************************************************************************************
 @Function			void HAL_UART_MspDeInit(void)
 @Description		HAL_UART_MspDeInit
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void HAL_UART_MspDeInit(UART_HandleTypeDef* uartHandle)
{

  if(uartHandle->Instance==USART1)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART1_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_9|GPIO_PIN_10);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART1_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
	else if(uartHandle->Instance==USART2)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART2_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2|GPIO_PIN_3);

    /* USART1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(USART2_IRQn);
  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
		else if(uartHandle->Instance==USART5)
  {
  /* USER CODE BEGIN USART1_MspDeInit 0 */

  /* USER CODE END USART1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_USART5_CLK_DISABLE();
  
    /**USART1 GPIO Configuration    
    PA9     ------> USART1_TX
    PA10     ------> USART1_RX 
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_3);


  /* USER CODE BEGIN USART1_MspDeInit 1 */

  /* USER CODE END USART1_MspDeInit 1 */
  }
} 

/**********************************************************************************************************
 @Function			void MX_USART2_UART_Init(void)
 @Description		MX_USART2_UART_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void MX_USART2_UART_Init(void)
{

  UART2_Handler.Instance = USART2;
  UART2_Handler.Init.BaudRate = 115200;
  UART2_Handler.Init.WordLength = UART_WORDLENGTH_8B;
  UART2_Handler.Init.StopBits = UART_STOPBITS_1;
  UART2_Handler.Init.Parity = UART_PARITY_NONE;
  UART2_Handler.Init.Mode = UART_MODE_TX_RX;
  UART2_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UART2_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
  UART2_Handler.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  UART2_Handler.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&UART2_Handler) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}
/**********************************************************************************************************
 @Function			void MX_USART5_UART_Init(void)
 @Description		MX_USART5_UART_Init	
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void MX_USART5_UART_Init(void)
{

  UART5_Handler.Instance = USART5;
  UART5_Handler.Init.BaudRate = 115200;
  UART5_Handler.Init.WordLength = UART_WORDLENGTH_8B;
  UART5_Handler.Init.StopBits = UART_STOPBITS_1;
  UART5_Handler.Init.Parity = UART_PARITY_NONE;
  UART5_Handler.Init.Mode = UART_MODE_TX_RX;
  UART5_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UART5_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
  UART5_Handler.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  UART5_Handler.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&UART5_Handler) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/**********************************************************************************************************
 @Function			void Uart_EnterCriticalSection(void)
 @Description		入关键操作,关闭中断,等待中断结束返回
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void Uart_EnterCriticalSection(void)
{
	__disable_irq();
}

/**********************************************************************************************************
 @Function			void Uart_ExitCriticalSection(void)
 @Description		退出关键操作,开启中断
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void Uart_ExitCriticalSection(void)
{
	__enable_irq();
}

/**********************************************************************************************************
 @Function			void Uart1_InterruptEnable(uint8_t xRxEnable, uint8_t xTxEnable)
 @Description		使能/失能 发送/接收 串口中断
 @Input				  xRxEnable : 1 ENABLE
							  v DISABLE
					       xTxEnabe : 1 ENBALE
							  : 0 DISABLE
 @Return				void
 @Other:
**********************************************************************************************************/
void Uart1_InterruptEnable(uint8_t xRxEnable, uint8_t xTxEnable)
{
#if USART_IRQ_CTRL_TYPE
	ENTER_CRITICAL_SECTION();
	
	if (xRxEnable) {													//使能串口接收中断
		__HAL_UART_ENABLE_IT(&UART1_Handler, UART_IT_RXNE);
	}
	else {															//失能串口接收中断
		__HAL_UART_DISABLE_IT(&UART1_Handler, UART_IT_RXNE);
	}
	
	if (xTxEnable) {													//使能串口发送中断
		__HAL_UART_ENABLE_IT(&UART1_Handler, UART_IT_TXE);
	}
	else {															//失能串口发送中断
		__HAL_UART_DISABLE_IT(&UART1_Handler, UART_IT_TXE);
	}
	
	EXIT_CRITICAL_SECTION();
#endif
}

/**********************************************************************************************************
 @Function			void Uart2_InterruptEnable(uint8_t xRxEnable, uint8_t xTxEnable)
 @Description			使能/失能 发送/接收 串口中断
 @Input				xRxEnable : 1 ENABLE
							  v DISABLE
					xTxEnabe : 1 ENBALE
							  : 0 DISABLE
 @Return				void
 @Other:
 @Other:
**********************************************************************************************************/
void Uart2_InterruptEnable(uint8_t xRxEnable, uint8_t xTxEnable)
{
#if USART_IRQ_CTRL_TYPE
	ENTER_CRITICAL_SECTION();
	
	if (xRxEnable) {													//使能串口接收中断
		__HAL_UART_ENABLE_IT(&UART2_Handler, UART_IT_RXNE);
	}
	else {															//失能串口接收中断
		__HAL_UART_DISABLE_IT(&UART2_Handler, UART_IT_RXNE);
	}
	
	if (xTxEnable) {													//使能串口发送中断
		__HAL_UART_ENABLE_IT(&UART2_Handler, UART_IT_TXE);
	}
	else {															//失能串口发送中断
		__HAL_UART_DISABLE_IT(&UART2_Handler, UART_IT_TXE);
	}
	
	EXIT_CRITICAL_SECTION();
#endif
}


/**********************************************************************************************************
 @Function			void USART1_IRQHandler(void)
 @Description		串口1中断服务程序
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void USART1_IRQHandler(void)
{
#if USART1_TYPE
	uint32_t timeout = 0;
	
	HAL_UART_IRQHandler(&UART1_Handler);									//调用HAL库中断处理公用函数
	
	timeout = 0;
	while (HAL_UART_GetState(&UART1_Handler) != HAL_UART_STATE_READY) {			//等待就绪
		timeout++;													//超时处理
		if (timeout > HAL_MAX_DELAY) break;
	}
	
	timeout = 0;
	/* 一次处理完成之后, 重新开启中断并设置RxXferCount为1 */
	while (HAL_UART_Receive_IT(&UART1_Handler, (uint8_t *)USART1_aRxBuffer, USART1_RXBUFFERSIZE) != HAL_OK) {
		timeout++;													//超时处理
		if (timeout > HAL_MAX_DELAY) break;
	}
	
#endif
}

/**********************************************************************************************************
 @Function			void USART2_IRQHandler(void)
 @Description		串口2中断服务程序
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void USART2_IRQHandler(void)
{
#if USART2_TYPE
	uint32_t timeout = 0;
	
	HAL_UART_IRQHandler(&UART2_Handler);									//调用HAL库中断处理公用函数
	
	timeout = 0;
	while (HAL_UART_GetState(&UART2_Handler) != HAL_UART_STATE_READY) {			//等待就绪
		timeout++;													//超时处理
		if (timeout > HAL_MAX_DELAY) break;
	}
	
	timeout = 0;
	/* 一次处理完成之后, 重新开启中断并设置RxXferCount为1 */
	while (HAL_UART_Receive_IT(&UART2_Handler, (uint8_t *)USART2_aRxBuffer, USART2_RXBUFFERSIZE) != HAL_OK) {
		timeout++;													//超时处理
		if (timeout > HAL_MAX_DELAY) break;
	}

#endif
}

/**********************************************************************************************************
 @Function			void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
 @Description		v串口接收中断处理回调函数
					在HAL库所有串口接收中断服务函数都会调用此函数
 @Input				  huart : UART句柄
 @Return				void
 @Other:
**********************************************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
#if USART1_TYPE
	if (huart->Instance == USART1)										//如果是串口1
	{
		USART1_RX_STA |= 0x2000;											//接收中
		if ((USART1_RX_STA & 0x8000) == 0) {								//接收未完成
			if (USART1_RX_STA & 0x4000) {									//接收到了0x0D
				if (USART1_aRxBuffer[0] != 0x0a) {							//还未接收到\r\n
					USART1_RX_STA &= 0xBFFF;
					USART1_RX_BUF[USART1_RX_STA & 0X1FFF] = USART1_aRxBuffer[0];
					USART1_RX_STA++;
					if ((USART1_RX_STA & 0X1FFF) > (USART1_REC_LEN-1)) USART1_RX_STA = 0;		//接收数据错误, 重新开始接收
				}
				else {												//接收完成了
					USART1_RX_BUF[USART1_RX_STA & 0X1FFF] = USART1_aRxBuffer[0];
					USART1_RX_STA++;
					if ((USART1_RX_STA & 0X1FFF) > (USART1_REC_LEN-1)) USART1_RX_STA = 0;		//接收数据错误, 重新开始接收
					USART1_RX_STA |= 0x8000;
					USART1_RX_STA &= 0xDFFF;								//接收完成
				}
			}
			else {													//还没收到0x0D
				if (USART1_aRxBuffer[0] == 0x0d) {
					USART1_RX_BUF[USART1_RX_STA & 0X1FFF] = USART1_aRxBuffer[0];
					USART1_RX_STA++;
					if ((USART1_RX_STA & 0X1FFF) > (USART1_REC_LEN-1)) USART1_RX_STA = 0;		//接收数据错误, 重新开始接收
					USART1_RX_STA |= 0x4000;
				}
				else {
					
					USART1_RX_BUF[USART1_RX_STA & 0X1FFF] = USART1_aRxBuffer[0];
					USART1_RX_STA++;
					if ((USART1_RX_STA & 0X1FFF) > (USART1_REC_LEN-1)) USART1_RX_STA = 0;		//接收数据错误, 重新开始接收
				}
			}
		}
	}
#endif
	
#if USART2_TYPE
	if (huart->Instance == USART2)										//如果是串口2
	{
		USART2_RX_STA |= 0x2000;											//接收中
		if ((USART2_RX_STA & 0x8000) == 0) {								//接收未完成
				
				if (USART2_aRxBuffer[0] != 0x0A) {							//还未接收到\r\n
					USART2_RX_STA &= 0xBFFF;
					USART2_RX_BUF[USART2_RX_STA & 0X1FFF] = USART2_aRxBuffer[0];
					USART2_RX_STA++;
					if ((USART2_RX_STA & 0X1FFF) > (USART2_REC_LEN-1)) USART2_RX_STA = 0;		//接收数据错误, 重新开始接收
				}
				else {												//接收完成了
					USART2_RX_BUF[USART2_RX_STA & 0X1FFF] = USART2_aRxBuffer[0];
					USART2_RX_STA++;
					if ((USART2_RX_STA & 0X1FFF) > (USART2_REC_LEN-1)) USART2_RX_STA = 0;		//接收数据错误, 重新开始接收
					USART2_RX_STA |= 0x8000;
					USART2_RX_STA &= 0xDFFF;								//接收完成
				}
		}

	}
#endif
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/********************************************** END OF FLEE **********************************************/

