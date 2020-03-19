/**
******************************************************************************
* @file    timer.h
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
#ifndef __TIMER_H
#define __TIMER_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Exported types ------------------------------------------------------------*/
extern TIM_HandleTypeDef    TimHandle;

/* User can use this section to tailor TIMx instance used and associated
   resources */
/* Definition for TIMx clock resources */
#define TIM2x                           TIM2
//#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()
//#define TIMx_CLK_DISENABLE()           __HAL_RCC_TIM2_CLK_DISABLE()

///* Definition for TIMx Channel Pins */
//#define TIMx_CHANNEL_CLK_ENABLE()       __HAL_RCC_GPIOA_CLK_ENABLE()
//#define TIMx_CHANNEL_CLK_DISENABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
//#define TIMx_GPIO_PORT_CHANNEL         GPIOA
//#define TIMx_GPIO_PIN_CHANNEL          GPIO_PIN_15
//#define TIMx_GPIO_AF_CHANNEL           GPIO_AF5_TIM2

#define TIMx_PWM_CHANNEL							 TIM_CHANNEL_1


///* Definition for TIMx clock resources */
//#define TIMx                           TIM2
//#define TIMx_CLK_ENABLE()              __HAL_RCC_TIM2_CLK_ENABLE()

///* Definition for TIMx Channel Pins */
//#define TIMx_CHANNEL_GPIO_PORT()       __HAL_RCC_GPIOC_CLK_ENABLE();__HAL_RCC_GPIOB_CLK_ENABLE()
//#define TIMx_GPIO_PORT_CHANNEL1        GPIOA
//#define TIMx_GPIO_PORT_CHANNEL2        GPIOA
//#define TIMx_GPIO_PORT_CHANNEL3        GPIOB
//#define TIMx_GPIO_PORT_CHANNEL4        GPIOB
//#define TIMx_GPIO_PIN_CHANNEL1         GPIO_PIN_15
//#define TIMx_GPIO_PIN_CHANNEL2         GPIO_PIN_1
//#define TIMx_GPIO_PIN_CHANNEL3         GPIO_PIN_10
//#define TIMx_GPIO_PIN_CHANNEL4         GPIO_PIN_11
//#define TIMx_GPIO_AF_CHANNEL1          GPIO_AF5_TIM2
//#define TIMx_GPIO_AF_CHANNEL2          GPIO_AF2_TIM2
//#define TIMx_GPIO_AF_CHANNEL3          GPIO_AF2_TIM2
//#define TIMx_GPIO_AF_CHANNEL4          GPIO_AF2_TIM2

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void TIME_Init(void);


void PWMIO_Init(void);
void PWMIO_DeInit(void);
void BEEP_void(uint8_t ucD,uint8_t ucL);
void TIMx_PWM_Init(void);
void PWM_output_start(void);
void PWM_output_stop(void);
	
#endif /* __TIME_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
