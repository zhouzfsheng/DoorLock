/**
*********************************************************************************************************
* @file    Buzzer.c
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
#include "App.h"
#include "Buzzer.h"
#include "timer.h"
#include "gpio.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Buzz_Test(void)
{
	int i = 0;
	while(1)
	{
		
		Buzz_Rhythm(i);
		i++;
		if(i>5)
		{
			i = 0;
		}
	}
}

void Buzz_Rhythm(uint8_t log)
{
	PWMIO_Init();
	TIMx_PWM_Init();
//	if(log>2)//首先是警报事件
//	{
		if(Event_appDate.lastlog)//当前事件优先级大于之前事件
		{
			log = Event_appDate.currentlog;
		}
//		else//当前事件没有大于之前事件，警报之前事件
//		{
//			Event_appDate.currentlog = Event_appDate.lastlog;
//		}
//	}else//非警报事件
//	{
//		Event_appDate.currentlog = log;
//	}
//	printf("currentlog %x\r\n", Event_appDate.currentlog);
	switch(log)
	{
		case Swipe:
			BEEP_void(0,1);
			break;
		case UnLock:
			BEEP_void(1,0);
			break;
		case Equipment_Lock://设备锁定
			BEEP_void(0,5);
			break;
		case Illegal_Card:
			BEEP_void(1,3);
			break;
		case Low_Battery:
			BEEP_void(1,1);
			break;
		case Illegal_Entrant:
			BEEP_void(1,2);
			break;
		case Fault:
			BEEP_void(1,4);
			break;
		case Installation_Mode://一直短鸣
			while(1)
			{
			BEEP_void(0,1);
			}
			break;
		case Normal_Mode:
			BEEP_void(3,3);
			break;
		case LOG_Buzzer:
			BEEP_void(0,3);
			break;
		default:
		break;
	}
//	PWMIO_DeInit();
	
	PWMIO_OUTPUT_Init();
//	HAL_GPIO_WritePin(TIMx_GPIO_PORT_CHANNEL,TIMx_GPIO_AF_CHANNEL,GPIO_PIN_RESET);
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(TIMx_GPIO_PORT_CHANNEL,TIMx_GPIO_AF_CHANNEL,GPIO_PIN_SET);
//	HAL_Delay(1);
//	HAL_GPIO_WritePin(TIMx_GPIO_PORT_CHANNEL,TIMx_GPIO_AF_CHANNEL,GPIO_PIN_RESET);

}





/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
