/**
  *********************************************************************************************************
  * @file    sys.c
  * @author  LockPlate -- ZZF
  * @version V2.0
  * @date    2020-3-9
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "sys.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
__IO uint32_t SystemClockSecond = 0;                    //系统运行时间(S)
__IO uint32_t SystemSoftResetTime = 0;                     //系统运行超时软件复位时间(MS)
//SystemRunningTime   SystemRunningTime = {0, 0, 100, 0, 0, 0, 1, 0, 0, 0}; //系统运行时间(结构体)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**********************************************************************************************************
 @Function			void IncSecondTick(void)
 @Description			IncSecondTick : 运行时间加1秒
 @Input				void
 @Return				void
**********************************************************************************************************/
void IncSecondTick(void)
{
	static uint32_t SecondTickPre;
	uint32_t SecondTickNow;
	
	SecondTickNow = HAL_GetTick();
	if ((SecondTickNow > SecondTickPre) && ((SecondTickNow - SecondTickPre) >= 1000)) {
		SystemClockSecond++;
		SecondTickPre += 1000;
	}
	else if ((0xFFFFFFFF - SecondTickPre + SecondTickNow + 1) >= 1000) {
		SystemClockSecond++;
		SecondTickPre += 1000;
	}
}

/**********************************************************************************************************
 @Function			uint32_t GetSecondTick(void)
 @Description			GetSecondTick 	: 获取运行秒数
 @Input				void
 @Return				SystemClockSecond : 运行秒数
**********************************************************************************************************/
uint32_t GetSecondTick(void)
{
	return SystemClockSecond;
}

/**********************************************************************************************************
 @Function			void Calculagraph_Init(CalculagraphTypeDef* timer)
 @Description			Calculagraph_Init 			: 初始化计时器
 @Input				CalculagraphTypeDef*		: 计时器结构体指针
 @Return				void
**********************************************************************************************************/
void Calculagraph_Init(CalculagraphTypeDef* timer)
{
	timer->xTicksToWait = 0;
	timer->xTimeOut = 0;
}

/**********************************************************************************************************
 @Function			void Calculagraph_ConfigurationMS(CalculagraphTypeDef* timer, uint32_t timeout_ms)
 @Description			Calculagraph_ConfigurationMS	: 配置计时器倒数时间(MS)
 @Input				CalculagraphTypeDef*		: 计时器结构体指针
					timeout_ms					: 倒计时时间(MS)
 @Return				void
**********************************************************************************************************/
void Calculagraph_ConfigurationMS(CalculagraphTypeDef* timer, uint32_t timeout_ms)
{
	timer->xTicksToWait = timeout_ms;
	timer->xTimeOut = HAL_GetTick() + timeout_ms;
}

/**********************************************************************************************************
 @Function			bool Calculagraph_MS(CalculagraphTypeDef* timer)
 @Description			Calculagraph_MS	: 查询是否到达计时器计时时间(MS)
 @Input				CalculagraphTypeDef*		: 计时器结构体指针
 @Return				true							: 到达
					false						: 未到达
**********************************************************************************************************/
bool Calculagraph_MS(CalculagraphTypeDef* timer)
{
	uint32_t MilliSecondTickNow;
	
	MilliSecondTickNow = HAL_GetTick();
	
	if ((MilliSecondTickNow > (timer->xTimeOut - timer->xTicksToWait)) && ((MilliSecondTickNow - (timer->xTimeOut - timer->xTicksToWait)) >= timer->xTicksToWait)) {
		return true;
	}
	else if ((0xFFFFFFFF - (timer->xTimeOut - timer->xTicksToWait) + MilliSecondTickNow + 1) >= timer->xTicksToWait) {
		return true;
	}
	else {
		return false;
	}
}

/**********************************************************************************************************
 @Function			void Calculagraph_ConfigurationSec(CalculagraphTypeDef* timer, uint32_t timeout_sec)
 @Description			Calculagraph_ConfigurationSec	: 配置计时器倒数时间(S)
 @Input				CalculagraphTypeDef*		: 计时器结构体指针
					timeout_sec					: 倒计时时间(S)
 @Return				void
**********************************************************************************************************/
void Calculagraph_ConfigurationSec(CalculagraphTypeDef* timer, uint32_t timeout_sec)
{
	timer->xTicksToWait = timeout_sec;
	timer->xTimeOut = GetSecondTick() + timeout_sec;
}

/**********************************************************************************************************
 @Function			bool Calculagraph_Sec(CalculagraphTypeDef* timer)
 @Description			Calculagraph_Sec	: 查询是否到达计时器计时时间(S)
 @Input				CalculagraphTypeDef*		: 计时器结构体指针
 @Return				true							: 到达
					false						: 未到达
**********************************************************************************************************/
bool Calculagraph_Sec(CalculagraphTypeDef* timer)
{
	uint32_t SecondTickNow;
	
	SecondTickNow = GetSecondTick();
	
	if ((SecondTickNow > (timer->xTimeOut - timer->xTicksToWait)) && ((SecondTickNow - (timer->xTimeOut - timer->xTicksToWait)) >= timer->xTicksToWait)) {
		return true;
	}
	else if ((0xFFFFFFFF - (timer->xTimeOut - timer->xTicksToWait) + SecondTickNow + 1) >= timer->xTicksToWait) {
		return true;
	}
	else {
		return false;
	}
}

/**********************************************************************************************************
 @Function			void EventRunningTime_Init(EventRunningTimeTypeDef* timer)
 @Description			EventRunningTime_Init 		: 初始化事件运行时间器
 @Input				CalculagraphTypeDef*		: 事件运行时间器结构体指针
 @Return				void
**********************************************************************************************************/
void EventRunningTime_Init(EventRunningTimeTypeDef* timer)
{
	timer->bEventRunningState = false;
	timer->xEventRunningStartTime = 0;
	timer->xEventRunningEndTime = 0;
}

/**********************************************************************************************************
 @Function			void EventRunningTime_StartMS(EventRunningTimeTypeDef* timer)
 @Description			EventRunningTime_StartMS	: 开启事件运行时间器(MS)
 @Input				CalculagraphTypeDef*		: 事件运行时间器结构体指针
 @Return				void
**********************************************************************************************************/
void EventRunningTime_StartMS(EventRunningTimeTypeDef* timer)
{
	if (timer->bEventRunningState == false) {
		timer->bEventRunningState = true;
		timer->xEventRunningStartTime = HAL_GetTick();
	}
}

/**********************************************************************************************************
 @Function			unsigned int EventRunningTime_EndMS(EventRunningTimeTypeDef* timer)
 @Description			EventRunningTime_StartMS	: 结束事件运行时间器(MS)
 @Input				CalculagraphTypeDef*		: 事件运行时间器结构体指针
 @Return				unsigned int					: 事件运行时间(MS)
**********************************************************************************************************/
unsigned int EventRunningTime_EndMS(EventRunningTimeTypeDef* timer)
{
	unsigned int ret = 0;
	
	if (timer->bEventRunningState == true) {
		timer->bEventRunningState = false;
		timer->xEventRunningEndTime = HAL_GetTick();
		ret = (timer->xEventRunningEndTime > timer->xEventRunningStartTime) ? \
			 (timer->xEventRunningEndTime - timer->xEventRunningStartTime) : \
			 (0xFFFFFFFF - timer->xEventRunningStartTime + timer->xEventRunningEndTime);
	}
	
	return ret;
}

/**********************************************************************************************************
 @Function			void EventRunningTime_StartSec(EventRunningTimeTypeDef* timer)
 @Description			EventRunningTime_StartSec	: 开启事件运行时间器(S)
 @Input				CalculagraphTypeDef*		: 事件运行时间器结构体指针
 @Return				void
**********************************************************************************************************/
void EventRunningTime_StartSec(EventRunningTimeTypeDef* timer)
{
	if (timer->bEventRunningState == false) {
		timer->bEventRunningState = true;
		timer->xEventRunningStartTime = GetSecondTick();
	}
}

/**********************************************************************************************************
 @Function			unsigned int EventRunningTime_EndSec(EventRunningTimeTypeDef* timer)
 @Description			EventRunningTime_EndSec		: 结束事件运行时间器(S)
 @Input				CalculagraphTypeDef*		: 事件运行时间器结构体指针
 @Return				unsigned int					: 事件运行时间(S)
**********************************************************************************************************/
unsigned int EventRunningTime_EndSec(EventRunningTimeTypeDef* timer)
{
	unsigned int ret = 0;
	
	if (timer->bEventRunningState == true) {
		timer->bEventRunningState = false;
		timer->xEventRunningEndTime = GetSecondTick();
		ret = (timer->xEventRunningEndTime > timer->xEventRunningStartTime) ? \
			 (timer->xEventRunningEndTime - timer->xEventRunningStartTime) : \
			 (0xFFFFFFFF - timer->xEventRunningStartTime + timer->xEventRunningEndTime);
	}
	
	return ret;
}
