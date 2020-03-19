/**
******************************************************************************
* @file    sys.h
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
#ifndef __SYS_H
#define __SYS_H

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "stdbool.h"
#include "stdint.h"

/* Exported types ------------------------------------------------------------*/
typedef struct
{
	unsigned int	xTicksToWait;
	unsigned int	xTimeOut;
}CalculagraphTypeDef;													//计时器

typedef struct
{
	bool			bEventRunningState;
	unsigned int	xEventRunningStartTime;
	unsigned int	xEventRunningEndTime;
}EventRunningTimeTypeDef;												//事件运行时间器

typedef struct
{
	unsigned int	seconds;												//秒
	unsigned int	tenseconds;												//10秒
	unsigned int	minutes;												//分
	unsigned int	fifteenMinutes;											//15分钟
	unsigned int	fortyMinutes;											//40分钟
	unsigned int	hours;													//时
	unsigned int	twoHours;												//2小时
	unsigned int	fourHours;												//4小时
	unsigned int	days;													//天
	unsigned int	weeks;													//周
}SystemRunningTime;													//系统运行时间

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

void IncSecondTick(void);												//运行时间加1秒
uint32_t  GetSecondTick(void);												//获取运行秒数

void Calculagraph_Init(CalculagraphTypeDef* timer);						//初始化计时器
void Calculagraph_ConfigurationMS(CalculagraphTypeDef* timer, uint32_t timeout_ms);	//配置计时器倒数时间(MS)
bool Calculagraph_MS(CalculagraphTypeDef* timer);				//查询是否到达计时器计时时间(MS)
void Calculagraph_ConfigurationSec(CalculagraphTypeDef* timer, uint32_t timeout_sec);	//配置计时器倒数时间(S)
bool Calculagraph_Sec(CalculagraphTypeDef* timer);				//查询是否到达计时器计时时间(S)

void EventRunningTime_Init(EventRunningTimeTypeDef* timer);				//初始化事件运行时间器
void EventRunningTime_StartMS(EventRunningTimeTypeDef* timer);				//开启事件运行时间器(MS)
unsigned int EventRunningTime_EndMS(EventRunningTimeTypeDef* timer);		//结束事件运行时间器(MS)
void EventRunningTime_StartSec(EventRunningTimeTypeDef* timer);			//开启事件运行时间器(S)
unsigned int EventRunningTime_EndSec(EventRunningTimeTypeDef* timer);		//结束事件运行时间器(S)

#endif /* __SYS_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



