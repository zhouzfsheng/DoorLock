/**
******************************************************************************
* @file    BSP_pwr.h
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
#ifndef __BSP_PWM_H__
#define __BSP_PWM_H__

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#ifndef _BSP_CONFIG_
//__________________________ F
#if defined (STM32F303xC)
#include "stm32f3xx_hal.h"
#endif
#if defined (STM32F103xB)
#include "stm32f1xx_hal.h"
#endif
	 
//__________________________ F0	 
#if defined (STM32F072xB) || defined (STM32F030x8)
#include "stm32f0xx_hal.h"
#endif
	 
//__________________________ L
#if defined (STM32L433xx)
#include "stm32l4xx_hal.h"
#endif
#if defined (STM32L151xB) || defined (STM32L151xBA)
#include "stm32l1xx_hal.h"
#endif
#if defined (STM32L053xx)|| defined (STM32L071xx)
#include "stm32l0xx_hal.h"
#endif
//__________________________ user includes ___________

#include "usart.h"
#include "rtc.h"
#include "spi.h"
#include "adc.h"
#include "Debug.h"
#else	//____________________________________________
#include "BSP_pcb_config.h"
#endif

#define SleepTime    				1
#ifndef SleepTime
extern uint16_t SleepTime;
#endif 
/* Public API functions  -----------------------------------------------------*/
void 	LowPower_Config(void);
void	LowPower_enter_stop(void);
void 	LowPower_enter_standby(void);
void	LowPower_WakeUp(void);


#ifdef __cplusplus
}
#endif
#endif /* __LCD_GDC21310_H__ */


/********************************************** END OF FLEE **********************************************/

