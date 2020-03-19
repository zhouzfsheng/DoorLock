/**
******************************************************************************
* @file    adc.h
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
#ifndef __ADC_H
#define __ADC_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

/* Exported types ------------------------------------------------------------*/
  
/**ADC GPIO Configuration    
PC0     ------> ADC_IN10
PC1     ------> ADC_IN11
PC2     ------> ADC_IN12
PC3     ------> ADC_IN13
PA0     ------> ADC_IN0
PA1     ------> ADC_IN1
PA2     ------> ADC_IN2
PA3     ------> ADC_IN3
PA4     ------> ADC_IN4
PA5     ------> ADC_IN5
PA6     ------> ADC_IN6
PA7     ------> ADC_IN7
PC4     ------> ADC_IN14
PC5     ------> ADC_IN15
PB0     ------> ADC_IN8
PB1     ------> ADC_IN9 
*/
//#define ADCx                           ADC1
//#define ADC_CLK_ENABLE()              __HAL_RCC_ADC1_CLK_ENABLE()
//#define ADC_CLK_DISABLE()      				__HAL_RCC_ADC1_CLK_DISABLE()
//#define ADC_GPIO_CLK_ENABLE()      	 	__HAL_RCC_GPIOB_CLK_ENABLE()


//#define ADC_FORCE_RESET()             __HAL_RCC_ADC1_FORCE_RESET()
//#define ADC_RELEASE_RESET()           __HAL_RCC_ADC1_RELEASE_RESET()

//#define ADCx_IN8                    	GPIO_PIN_0
//#define ADC_GPIO_PORT              		GPIOB

#define VBAT_ADC_GPIOx										GPIOB
#define VBAT_ADC_PIN											GPIO_PIN_0
#define VBAT_ADC_RCC_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOB_CLK_ENABLE()
#define VBAT_ADC_RCC_GPIO_CLK_DISABLE()		__HAL_RCC_GPIOB_CLK_DISABLE()
#define VBAT_ADC_RCC_ADC1_CLK_ENABLE()		__HAL_RCC_ADC1_CLK_ENABLE()
#define VBAT_ADC_RCC_ADC1_CLK_DISABLE()		__HAL_RCC_ADC1_CLK_DISABLE()

#define VBATPOWER(n)	(n?HAL_GPIO_WritePin(VBAT_POWER_GPIOx, VBAT_POWER_PIN, GPIO_PIN_RESET):HAL_GPIO_WritePin(VBAT_POWER_GPIOx, VBAT_POWER_PIN, GPIO_PIN_SET))

extern ADC_HandleTypeDef		VBAT_ADC_Handler;								//电池电压ADC句柄


/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void VBAT_ADC_Init(void);												//电压ADC初始化
uint16_t  VBAT_ADC_Read(uint32_t timeout);											//电源电压ADC读取
	
#endif /* __ADC_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


