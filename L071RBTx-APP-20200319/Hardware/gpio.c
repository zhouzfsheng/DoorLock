/**
  *********************************************************************************************************
  * @file    gpio.c
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
#include "gpio.h"
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**********************************************************************************************************
 @Function			void MX_GPIO_Init(void)
 @Description		MX_GPIO_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
//  HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : PC13 */
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
	
  /*Configure GPIO pins : PH0 PH1 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = KEY_Pin
#ifdef SWITCH_EXTI_8
												|SWITCH_EXTI_8
#endif 

#ifdef SWITCH_EXTI_9
												|SWITCH_EXTI_9
#endif

#ifdef SWITCH_EXTI_12
												|SWITCH_EXTI_12
#endif									
												;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY_GPIO_Port, &GPIO_InitStruct);


  /*Configure GPIO pins : PA1 PA2 PA3 PA4 
                           PA5 PA6 PA7 PA8 
                           PA11 PA12 PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|GPIO_PIN_4 
                          |GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8 
													|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

//#ifdef SWITCH_INPUT_12
//  /*Configure GPIO pins : PA12 */
//  GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_12;
//  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
//#endif

  /*Configure GPIO pins : PB0 PB2 PB10 PB11 
                           PB12 PB13 PB14 PB15 
                           PB3 PB4 PB5 PB6 
                           PB7 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10|GPIO_PIN_11 
                          |GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15 
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6
                          |GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

//#ifdef BUTTON_EXTI_5
//  /*Configure GPIO pin : PtPin */
//  GPIO_InitStruct.Pin = BUTTON_EXTI_5|BUTTON_EXTI_6;
//  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
//  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
//  HAL_GPIO_Init(BUTTON_GPIO_PORT, &GPIO_InitStruct);
//#endif
//  /*Configure GPIO pins : PB0 PB2 PB10 PB11 
//                           PB12 PB13 PB14 PB15 
//                           PB3 PB4 PB5 PB6 
//                           PB7 PB8 PB9 */
//  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1 
//											 //|GPIO_PIN_2|GPIO_PIN_3||GPIO_PIN_5|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13
//														;
//  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
//  GPIO_InitStruct.Pull = GPIO_NOPULL;
//  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

//  /*Configure GPIO pin : PtPin */
//  GPIO_InitStruct.Pin = LED_Pin;
//  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
//  GPIO_InitStruct.Pull = GPIO_PULLUP;
//  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
//  HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 3, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);

}

/**********************************************************************************************************
 @Function			void GPIOInPut_Init(void)
 @Description		PIOInPut_Init
 @Input				  	void
 @Return				void
 @Other:
**********************************************************************************************************/
void GPIOInPut_Init(GPIO_TypeDef* GPIO_PORT,uint32_t INPUTGPIO)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  if(GPIO_PORT == EXTI_GPIO_PORT)
		/* Enable the GPIO_LED Clock */
		EXTI_GPIO_CLK_ENABLE();
	else
		BUTTON_GPIO_CLK_ENABLE();

  GPIO_InitStruct.Pin = INPUTGPIO;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIO_PORT, &GPIO_InitStruct);
}
void GPIOEXIT_Init(GPIO_TypeDef* GPIO_PORT,uint32_t EXTIGPIO)
{
  GPIO_InitTypeDef GPIO_InitStruct;
	
	EXTI_GPIO_CLK_ENABLE();
	
  /*Configure GPIO pin : PtPin */
  GPIO_InitStruct.Pin = EXTIGPIO;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(KEY_GPIO_Port, &GPIO_InitStruct);
}

/**********************************************************************************************************
 @Function			void GPIOInPut_DeInit(void)
 @Description		GPIOInPut_DeInit
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void GPIOInPut_DeInit(GPIO_TypeDef* GPIO_PORT,uint32_t INPUTGPIO)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
	
  if(GPIO_PORT == EXTI_GPIO_PORT)
		/* Enable the GPIO_LED Clock */
		EXTI_GPIO_CLK_ENABLE();
	else
		BUTTON_GPIO_CLK_ENABLE();

  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = INPUTGPIO;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  
  HAL_GPIO_Init(GPIO_PORT, &GPIO_InitStruct);
}

/**********************************************************************************************************
 @Function			void Zigbee_RST_Init(void)
 @Description		Zigbee_RST_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void Zigbee_RST_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the BUTTON Clock */
  Zigbee_RSTGPIO_CLK_ENABLE();
  
  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = Zigbee_RST;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  
  HAL_GPIO_Init(Zigbee_RSTGPIO_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(Zigbee_RSTGPIO_PORT,Zigbee_RST,GPIO_PIN_RESET);//低电平
	HAL_Delay(5);
	HAL_GPIO_WritePin(Zigbee_RSTGPIO_PORT,Zigbee_RST,GPIO_PIN_SET);
	
  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = Zigbee_RST;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  
  HAL_GPIO_Init(Zigbee_RSTGPIO_PORT, &GPIO_InitStruct);
}

/**********************************************************************************************************
 @Function			void ZigbeeIRQ(void)
 @Description		ZigbeeIRQ
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void ZigbeeIRQ(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the BUTTON Clock */
  Zigbee_GPIO_CLK_ENABLE();

  GPIO_InitStruct.Pin = Zigbee_IRQ;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	/* Configure Button pin as input with External interrupt */
	GPIO_InitStruct.Mode   = GPIO_MODE_IT_FALLING; 
	HAL_GPIO_Init(Zigbee_GPIO_PORT, &GPIO_InitStruct);

}

/**********************************************************************************************************
 @Function			void Zigbee_Wake_Up(void)
 @Description		Zigbee_Wake_Up
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void Zigbee_Wake_Up(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the BUTTON Clock */
  Zigbee_GPIO_CLK_ENABLE();
  
  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = Zigbee_Wakeup;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  
  HAL_GPIO_Init(Zigbee_GPIO_PORT, &GPIO_InitStruct);

}

/**********************************************************************************************************
 @Function			void Zigbee_Wake_Up(void)
 @Description		Zigbee_Wake_Up
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void Zigbee_DeInit(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the BUTTON Clock */
  Zigbee_GPIO_CLK_ENABLE();
  
  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = Zigbee_Wakeup;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  
  HAL_GPIO_Init(Zigbee_GPIO_PORT, &GPIO_InitStruct);

}

/**********************************************************************************************************
 @Function			void BLE_AT_Enanle_Init(void)
 @Description		BLE_AT_Enanle_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void BLE_AT_Enanle_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the BUTTON Clock */
  BLE_GPIO_CLK_ENABLE();
  
  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = BLE_AT_ENABLE;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  
  HAL_GPIO_Init(BLE_GPIO_PORT, &GPIO_InitStruct);

}

/**********************************************************************************************************
 @Function			void BLE_PWRC_Init(void)
 @Description		BLE_PWRC_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
//低电平唤醒蓝牙

void BLE_PWRC_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the BUTTON Clock */
  BLE_GPIO_CLK_ENABLE();
  
  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = BLE_PWRC;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_OD;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  
  HAL_GPIO_Init(BLE_GPIO_PORT, &GPIO_InitStruct);
	

	HAL_GPIO_WritePin(BLE_GPIO_PORT,BLE_PWRC,GPIO_PIN_RESET);//低电平
	HAL_Delay(50);
	HAL_GPIO_WritePin(BLE_GPIO_PORT,BLE_PWRC,GPIO_PIN_SET);
	
  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = BLE_PWRC;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  
  HAL_GPIO_Init(BLE_GPIO_PORT, &GPIO_InitStruct);
}

/**********************************************************************************************************
 @Function			void BLE_RST_Init(void)
 @Description		BLE_RST_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
/*蓝牙RST是低电平重启*/
void BLE_RST_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  
  /* Enable the BUTTON Clock */
  BLE_GPIO_CLK_ENABLE();
  
  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = BLE_RST_IO;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  
  HAL_GPIO_Init(BLE_GPIO_PORT, &GPIO_InitStruct);
	
	HAL_GPIO_WritePin(BLE_GPIO_PORT,BLE_RST_IO,GPIO_PIN_SET);

  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = BLE_PWRC;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  
  HAL_GPIO_Init(BLE_GPIO_PORT, &GPIO_InitStruct);
	
}

/**********************************************************************************************************
 @Function			void PWMIO_Init(void)
 @Description		PWMIO_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void PWMIO_Init(void)
{
  GPIO_InitTypeDef   GPIO_InitStruct;
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* TIMx Peripheral clock enable */
  TIMx_CLK_ENABLE();

  /* Enable all GPIO Channels Clock requested */
  TIMx_CHANNEL_CLK_ENABLE();

  /* Configure PA.15 (On Nucleo Board, pin 17 on CN7) (TIM2_Channel1), PA.1  (On Nucleo Board, pin 30 on CN7) (TIM2_Channel2), PB.10 (On Nucleo Board, pin 25 on CN10) (TIM2_Channel3),
     PB.11 (On Nucleo Board, pin 18 on CN10) (TIM2_Channel4) in output, push-pull, alternate function mode
  */
  /* Common configuration for all channels */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;


  GPIO_InitStruct.Alternate = TIMx_GPIO_AF_CHANNEL;
  GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL;
  HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL, &GPIO_InitStruct);
}
/**********************************************************************************************************
 @Function			void PWMIO_DeInit(void)
 @Description		PWMIO_DeInit
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void PWMIO_DeInit(void)
{
  GPIO_InitTypeDef   GPIO_InitStruct;
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* TIMx Peripheral clock enable */
  TIMx_CLK_DISENABLE();

  /* Enable all GPIO Channels Clock requested */
  TIMx_CHANNEL_CLK_DISENABLE();

  /* Configure PA.15 (On Nucleo Board, pin 17 on CN7) (TIM2_Channel1), PA.1  (On Nucleo Board, pin 30 on CN7) (TIM2_Channel2), PB.10 (On Nucleo Board, pin 25 on CN10) (TIM2_Channel3),
     PB.11 (On Nucleo Board, pin 18 on CN10) (TIM2_Channel4) in output, push-pull, alternate function mode
  */
  /* Common configuration for all channels */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;


  GPIO_InitStruct.Alternate = TIMx_GPIO_AF_CHANNEL;
  GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL;
  HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL, &GPIO_InitStruct);
	
}

/**********************************************************************************************************
 @Function			void PWMIO_OUTPUT_Init(void)
 @Description		PWMIO_OUTPUT_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void PWMIO_OUTPUT_Init(void)
{
  GPIO_InitTypeDef   GPIO_InitStruct;
  /*##-1- Enable peripherals and GPIO Clocks #################################*/
  /* TIMx Peripheral clock enable */
  TIMx_CLK_ENABLE();

  /* Enable all GPIO Channels Clock requested */
  TIMx_CHANNEL_CLK_ENABLE();

  /* Common configuration for all channels */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Alternate = TIMx_GPIO_AF_CHANNEL;
  GPIO_InitStruct.Pin = TIMx_GPIO_PIN_CHANNEL;
  HAL_GPIO_Init(TIMx_GPIO_PORT_CHANNEL, &GPIO_InitStruct);
}

/**********************************************************************************************************
 @Function			void Motor_Init(void)
 @Description		Motor_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void Motor_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
  
  /* Enable the GPIO_LED Clock */
  MOTOR_GPIO_CLK_ENABLE();

  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = MOTORA_PIN|MOTORB_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  
  HAL_GPIO_Init(MOTOR_GPIO_PORT, &GPIO_InitStruct);
}

/**********************************************************************************************************
 @Function			void Motor_DeInit(void)
 @Description		Motor_DeInit
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void Motor_DeInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStruct;
  
  /* Enable the GPIO_LED Clock */
  MOTOR_GPIO_CLK_ENABLE();

  /* Configure the GPIO_LED pin */
  GPIO_InitStruct.Pin = MOTORA_PIN|MOTORB_PIN;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  HAL_GPIO_Init(MOTOR_GPIO_PORT, &GPIO_InitStruct);
}

/**********************************************************************************************************
 @Function			void Lock_Open(void)
 @Description		Lock_Open
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void Lock_Open(char flag)
{
	Motor_Init();
	if(flag)
	{
		
		MOTORA_L();
		MOTORB_H();
		HAL_Delay(300);
		MOTORA_L();
		MOTORB_L();
	}
	else{
		MOTORA_H();
		MOTORB_L();
		HAL_Delay(300);
		MOTORA_L();
		MOTORB_L();
	}
	Motor_DeInit();
}


/**********************************************************************************************************
 @Function			void Lock_Close(void)
 @Description		Lock_Close
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void Lock_Close(char flag)
{
	Motor_Init();
	if(flag)
	{
		MOTORA_H();
		MOTORB_L();
		HAL_Delay(300);
		MOTORA_L();
		MOTORB_L();
	}
	else{
		MOTORA_L();
		MOTORB_H();
		HAL_Delay(300);
		MOTORA_L();
		MOTORB_L();
	}
	Motor_DeInit();
}


/* USER CODE BEGIN 2 */

/* USER CODE END 2 */

/**
  * @}
  */

/**
  * @}
  */

/********************************************** END OF FLEE **********************************************/

