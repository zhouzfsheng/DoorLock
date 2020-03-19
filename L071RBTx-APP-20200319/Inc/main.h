/**
******************************************************************************
* @file    main.h
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
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
/** 唤醒源宏定义
***************************************/
#define DEVICE_NON_WKUP_FLAG                     0x0000    //无唤醒源
#define DEVICE_RTC_INT_FLAG                      0x0001    //RTC内部中断唤醒
#define DEVICE_ALARM_WKUP_FLAG                   0x0002    //RTC闹钟中断唤醒

#define DEVICE_FMXX_IRQ_FLAG                     0x0004    //BUTTOM中断唤醒
#define DEVICE_ZIGB_IRQ_FLAG                     0x0008    //BUTTOM中断唤醒

#define DEVICE_SWTH_IO8_FLAG                     0x0010    //BUTTOM中断唤醒

#define DEVICE_SWTH_IO5_FLAG                     0x0020    //BUTTOM中断唤醒
#define DEVICE_SWTH_IO6_FLAG                     0x0040    //BUTTOM中断唤醒

//#define DEVICE_SWTH_IOB_FLAG                     0x040    //BUTTOM中断唤醒
//#define DEVICE_SWTH_IOC_FLAG                     0x080    //BUTTOM中断唤醒
//#define DEVICE_SWTH_IOD_FLAG                     0x100    //BUTTOM中断唤醒
//#define DEVICE_SWTH_IO3_FLAG                     0x200    //BUTTOM中断唤醒
//#define DEVICE_SWTH_IO5_FLAG                     0x400    //BUTTOM中断唤醒
/* Private define ------------------------------------------------------------*/

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
