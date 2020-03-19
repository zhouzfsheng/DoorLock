/**
******************************************************************************
* @file    gpio.h
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
#ifndef __gpio_H
#define __gpio_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "main.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */	

 

	 
#define SWITCH_EXTI_8 															 GPIO_PIN_8
//#define SWITCH_EXTI_9                        			 	 GPIO_PIN_9


#define SWITCH_INPUT_3                        			 GPIO_PIN_3
#define SWITCH_INPUT_5                        			 GPIO_PIN_5
	 
#define SWITCH_INPUT_9                        			 GPIO_PIN_9
#define SWITCH_INPUT_10                        			 GPIO_PIN_10
//#define SWITCH_INPUT_11                        			 GPIO_PIN_11
#define SWITCH_INPUT_12                        			 GPIO_PIN_12
//#define SWITCH_INPUT_13                        			 GPIO_PIN_13

#define SWITCH_INPUT_ENABLE                        		 1

#define KEY_Pin GPIO_PIN_7
#define KEY_GPIO_Port GPIOC
#define KEY_EXTI_IRQn EXTI4_15_IRQn

#define EXTI_GPIO_PORT                   		 GPIOC
#define EXTI_GPIO_CLK_ENABLE()           		 __HAL_RCC_GPIOC_CLK_ENABLE()  
#define EXTI_GPIO_CLK_DISABLE()          		 __HAL_RCC_GPIOC_CLK_DISABLE()

#define BUTTON_INPUT_5 															 GPIO_PIN_5 
#define BUTTON_INPUT_6 															 GPIO_PIN_6
//#define BUTTON_EXTI_5 															 GPIO_PIN_5 
//#define BUTTON_EXTI_6 															 GPIO_PIN_6
#define BUTTON_GPIO_PORT 										GPIOB
#define BUTTON_GPIO_CLK_ENABLE()           		 __HAL_RCC_GPIOB_CLK_ENABLE()  
#define BUTTON_GPIO_CLK_DISABLE()          		 __HAL_RCC_GPIOB_CLK_DISABLE()


//EXTI2_3_IRQn
	 
#define LED_Pin GPIO_PIN_1
#define LED_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define LED_ON	 	HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin, GPIO_PIN_RESET)
#define LED_OFF		HAL_GPIO_WritePin(LED_GPIO_Port,LED_Pin, GPIO_PIN_SET) 
#define LED_TOG		HAL_GPIO_TogglePin(LED_GPIO_Port,LED_Pin)
	 
#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()
#define TIMx_CLK_DISENABLE()           __HAL_RCC_TIM2_CLK_DISABLE()
/* Definition for TIMx Channel Pins */
#define TIMx_CHANNEL_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
#define TIMx_CHANNEL_CLK_DISENABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
#define TIMx_GPIO_PORT_CHANNEL         GPIOA
#define TIMx_GPIO_PIN_CHANNEL          GPIO_PIN_15
#define TIMx_GPIO_AF_CHANNEL           GPIO_AF5_TIM2
	 


	 
#define Zigbee_Wakeup	                       GPIO_PIN_2
#define Zigbee_IRQ	                         GPIO_PIN_4
#define Zigbee_GPIO_PORT                   	 GPIOC
#define Zigbee_GPIO_CLK_ENABLE()           	 __HAL_RCC_GPIOC_CLK_ENABLE()  
#define Zigbee_GPIO_CLK_DISABLE()          	 __HAL_RCC_GPIOC_CLK_DISABLE()

#define Zigbee_RST	                         GPIO_PIN_12
#define Zigbee_RSTGPIO_PORT                  GPIOA
#define Zigbee_RSTGPIO_CLK_ENABLE()          __HAL_RCC_GPIOA_CLK_ENABLE()  
#define Zigbee_RSTGPIO_CLK_DISABLE()         __HAL_RCC_GPIOA_CLK_DISABLE()

#define	Read_Zigbee_IRQ()										 HAL_GPIO_ReadPin(Zigbee_GPIO_PORT, Zigbee_IRQ)
	 

#define BLE_RST_IO	                       	GPIO_PIN_1
#define BLE_PWRC	                       		GPIO_PIN_0
#define BLE_AT_ENABLE	                     	GPIO_PIN_11
#define BLE_GPIO_PORT                   	 	GPIOA
#define BLE_GPIO_CLK_ENABLE()           		__HAL_RCC_GPIOA_CLK_ENABLE()  
#define BLE_GPIO_CLK_DISABLE()          	 	__HAL_RCC_GPIOA_CLK_DISABLE()



#define MOTORA_PIN                          GPIO_PIN_10
#define MOTORB_PIN                          GPIO_PIN_11
#define MOTOR_GPIO_PORT                     GPIOB
#define MOTOR_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOB_CLK_ENABLE()  
#define MOTOR_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOB_CLK_DISABLE()

#define	MOTORA_L()										 HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTORA_PIN,GPIO_PIN_RESET)
#define	MOTORA_H()										 HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTORA_PIN,GPIO_PIN_SET)
#define	MOTORB_L()										 HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTORB_PIN,GPIO_PIN_RESET)
#define	MOTORB_H()										 HAL_GPIO_WritePin(MOTOR_GPIO_PORT, MOTORB_PIN,GPIO_PIN_SET)
	 
	 
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void MX_GPIO_Init(void);

void Zigbee_RST_Init(void);
void ZigbeeIRQ(void);
void Zigbee_Wake_Up(void);
void Zigbee_DeInit(void);
void BLE_AT_Enanle_Init(void);
void BLE_PWRC_Init(void);
void BLE_RST_Init(void);
void PWMIO_Init(void);
void PWMIO_DeInit(void);
void PWMIO_OUTPUT_Init(void);
void GPIOInPut_Init(GPIO_TypeDef* GPIO_PORT,uint32_t INPUTGPIO);
void Lock_Open(char flag);
void Lock_Close(char flag);
void GPIOEXIT_Init(GPIO_TypeDef* GPIO_PORT,uint32_t EXTIGPIO);
void GPIOInPut_DeInit(GPIO_TypeDef* GPIO_PORT,uint32_t INPUTGPIO);
/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ pinoutConfig_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
