/**
*********************************************************************************************************
* @file    Buzzer.h
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
#ifndef __BUZZER_H
#define __BUZZER_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
	 
///*
//十位是长鸣，个位是短鸣
//例如: 
//0x01-》就是0长1短
//0x23-》就是2长1短

//0x0f-》就是没有长鸣，一直短鸣
//****************************
enum Logevent
{
  Swipe =0,
  UnLock = 1, //能开锁
	Equipment_Lock,//设备锁定
  Illegal_Card,//非法卡（联网情况在黑名单内报警不用平台查询；不联网直接报警不联网不用查询）
  Illegal_Entrant,//非法开门
  Low_Battery,
  Fault,//故障
  //Not connected to the Internet
  Installation_Mode,
  Normal_Mode,//正常模式没联网
	LOG_Buzzer
};
	 
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void Buzz_Rhythm(uint8_t log);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__BUZZER_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
