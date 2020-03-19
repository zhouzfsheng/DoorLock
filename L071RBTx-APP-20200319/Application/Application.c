/**
*********************************************************************************************************
* @file    Bletransport.c
* @author  LockPlate -- ZZF
* @version V1.0
* @date    2019-5-15
* @brief   
*********************************************************************************************************
* @attention
*
* 2020.1.8
* 功耗已经到达35ua左右，暂时再无优化空间
*********************************************************************************************************
*/
	//L071RBTx
/* Includes ------------------------------------------------------------------*/
#include "App.h"
#include "main.h"
#include "Common.h"

#include "rtc.h"
#include "usart.h"
#include "gpio.h"
#include "spi.h"
#include "iwdg.h"
/* USER CODE BEGIN Includes */
#include "Debug.h"
#include "BSP_pwr.h"

#include "1755test.h"

extern __IO uint32_t uwTick;
/* Private typedef -----------------------------------------------------------*/
BLE_ATCmdTypeDef BLEATcmd;
extern uint8_t Device_Wkup_Flag_Now;
uint32_t TestTime;
int i = 0;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void Peripherals(void)
{
  MX_GPIO_Init();
  MX_USART1_UART_Init();
	MX_USART2_UART_Init();
	MX_USART5_UART_Init();
  MX_RTC_Init();
	VBAT_ADC_Init();
	Flash_NSS();
	FLASH_Init();

	MCU_ResetCheck();
	//蓝牙模块重启完要一定时间完全启动
	BLE_RST_Init();
	
	if(Event_appDate.MCU_RSTStatus != RCC_FLAG_IWDGRST)
	{
	Lock_Close(0);
	Event_appDate.DoorFlag = 0;
	}

	Event_appDate.VoltageAverage += VBAT_ADC_Read(600);
	
	SystemInfo_Init();
	
	BLE_Init(&BLEATcmd);
	
	Iwdg_Init();
	
	Official_Test();
	
	if(Event_appDate.MCU_RSTStatus != RCC_FLAG_IWDGRST)
	{
		Event_appDate.MCU_RSTStatus = 0;
		Buzz_Rhythm(Swipe);
	}else{
		SRPConfiguration.sParameterConfiguration.IWDG_Num ++;
		WirteConfiguration_Parameters();
	}

	Zigbee_RST_Init();
	ZigbeeIRQ();

	Event_appDate.status = 1;
	Event_appDate.NetworkState = 0;//上线默认zigbee网络是没问题的
	
	GPIOInPut_Init(EXTI_GPIO_PORT,GPIO_PIN_10|GPIO_PIN_12);
	Event_appDate.BackLocking[0] = HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_INPUT_10);
	Event_appDate.CheckLockStatus = HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_INPUT_12);
	
	//按键检测
	Event_appDate.RSTMCU_PreKeyTick = 0;
	Event_appDate.RSTMCU_KeyTick = 0;
	Event_appDate.RSTZB_PreKeyTick = 0;
	Event_appDate.RSTZB_KeyTick = 0;
	Event_appDate.Uart1Ready = SET;
	Event_appDate.Uart1length = 0;
	Event_appDate.BLEOpentime = 0;
	Event_appDate.SwipCardNumber = 0;
	Event_appDate.SwipCardTime = 0;
	Event_appDate.BackLocking[1] = !Event_appDate.BackLocking[0];
	Event_appDate.BLEUUIDFlag = 0;
	Event_appDate.BLEUUID_Time = 0;
	Event_appDate.BLEUUIDRECVEnd = 0;
	
	Event_appDate.SysTime = 0;
	Event_appDate.NetRstTime = 0;
	Event_appDate.Timing_LimitFlag = 0;
	Event_appDate.NTP_Time = 0;
	Event_appDate.RTC_Flag = 0;
	
	Event_appDate.report_record_Time = TestReportRecordingHTime;
	Event_appDate.report_record_no = 0;
	Event_appDate.report_record_Flag = 0;
	
	Event_appDate.Authentication_Flag = 0;
}

void Timed_task(void)
{
		if(!(Event_appDate.SysTime%ADCTIME))//一天检测电池(86401s)
		{
			DataTransmition(MCU_Electricity_Query);
		}
		
		//每分钟检测一次
		if(!(Event_appDate.SysTime%TimingLimitReadMTIME))//一分钟(60s)
		{
			Timing_limit_Function();
		}
 
		if(!(Event_appDate.SysTime%Event_appDate.report_record_Time))//3个小时或3分钟(180s)
		{
			Report_Record();//定时上报记录
		}
		
//		if(!(Event_appDate.SysTime%NTPTIME))//一天与zigbee网关同步时间
//		{
//			NTP_Shop_Funtion();
//		}
		
		//定时自检（一个星期）
		if(!(Event_appDate.SysTime%ClockingInTIME))//一个星期(604801s)
		{
			DataTransmition(MCU_Device_Self_Checking);
			Event_appDate.report_record_no = 0;
		}
		
		if((!(Event_appDate.SysTime%SWIPTIME))&&Event_appDate.SwipCardNumber)//31秒检测重复刷卡参数
		{
			if(Event_appDate.SwipCardNumber != Event_appDate.SwipCardNumberOld)
			{
				Event_appDate.SwipCardNumberOld = Event_appDate.SwipCardNumber;
			}else{
				Event_appDate.SwipCardNumber = 0;
			}
		}
}

void BLEUUID_Function(void)
{
	//获取到BLE list才会有BLEUUID_Time，便启动
	if(Event_appDate.BLEUUIDRECVEnd&&Event_appDate.BLEUUID_Time)
	{
		LOG(LOG_WRN,"BUT %d\n",Event_appDate.BLEUUID_Time);
		Event_appDate.BLEUUID_Time--;
		if(!Event_appDate.BLEUUID_Time)//进入函数就BLEUUID_Time已经等于0
		{
			Event_appDate.BLEUUIDFlag = 1;//考勤启动标志
			Event_appDate.BLEUUID_number = 1;
			Event_appDate.BLERunTime = 0;
			DataTransmition(MCU_Clocking_In);
		}
	}
}

void Test_Function(void)
{
		Event_appDate.SysTime++;
	
		if(Event_appDate.DoorFlag)
		{
			if(!Event_appDate.AutoClosingTime)
			{
				DataTransmition(MCU_Locking);
			}else{
				Event_appDate.AutoClosingTime--;
			}
		}
		if(!USART1_RX_STA)
		{
			Timed_task();
		}
		
		if(!(Event_appDate.SysTime%AlarmSystemTIME))//5秒
		{
			Credit_card_processing();//刷卡异常处理
			
			if((!Event_appDate.BLEUUID_Time)&&Event_appDate.NTP_Time&&(!Event_appDate.BLEUUIDFlag))
			{
				Event_appDate.NTP_Flag = 1;
				Event_appDate.NTP_Time = 0;
				DataTransmition(MCU_Get_RTC_Event);
			}
		}
		
		if(Event_appDate.BLEUUIDRECVEnd&&Event_appDate.RTC_Flag&&(!Event_appDate.BLEUUID_Time)&&Event_appDate.BLEOSum)
		{
			Get_RTC(Event_appDate.RtcTime);
			printf("Time:%d:%d:%d\r\n", Event_appDate.RtcTime[4],
																	Event_appDate.RtcTime[5],
																	Event_appDate.RtcTime[6]);
			Event_appDate.BLEUUID_Time = ((Event_appDate.BLEUUIDStart[0]-Event_appDate.RtcTime[4])*3600) + ((Event_appDate.BLEUUIDStart[1]-Event_appDate.RtcTime[5]-1)*60) - Event_appDate.BLEUUIDStart[2];
			Event_appDate.RTC_Flag = 0;
			printf("Wirte Time %x BLEOSum %x\r\n",Event_appDate.BLEUUID_Time,Event_appDate.BLEOSum);
		}
		
		if(Event_appDate.BLEOpentime)
		{
			LOG(LOG_WRN,"BRT %x n:%x\n",Event_appDate.BLERunTime,Event_appDate.BLEUUID_number);
			Event_appDate.BLERunTime++;
			if(Event_appDate.BLEOpentime < Event_appDate.BLERunTime)
			{
				if(Event_appDate.BLEUUIDFlag)
				{
					if(Event_appDate.BLEUUID_number>Event_appDate.BLEOSum)
					{
						Event_appDate.BLEUUIDFlag = 0;
						Event_appDate.BLEUUIDRECVEnd = 0;
						ClearUUID();
					}
					else
					{
						DataTransmition(MCU_Clocking_In);
						Event_appDate.BLERunTime = 0;
					}
				}else
				{
					LOG(LOG_NOL,"CB\n");
					DataTransmition(MCU_BLE_Close);
					Event_appDate.BLERunTime = 0;
					Event_appDate.BLEOpentime = 0;
				}
			}
		}

		if(Event_appDate.NetRstTime)//一天重启一次
		{
			Event_appDate.NetRstTime--;
			LOG(LOG_WRN,"N %04x\n",Event_appDate.NetRstTime);
			if((!Event_appDate.NetRstTime))
			{
					LOG(LOG_NOL,"RZ\n");
					DataTransmition(MCU_RstZigBee);
					Event_appDate.NetworkState = 0;
			}
		}

		if(Event_appDate.SwipCardNumber > 6)
		{
			DataTransmition(MCU_AbnormalSwipe);
		}
		
#ifdef SWITCH_INPUT_ENABLE
		GPIOInPut_Init(EXTI_GPIO_PORT,GPIO_PIN_10|GPIO_PIN_12);
		if(HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_INPUT_10) != Event_appDate.BackLocking[1])//反锁
		{
			if(HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_INPUT_10))
			{//高电平是关反锁
				DataTransmition(MCU_Back_Unlocking);
			}else{
				//低电平是开反锁
				DataTransmition(MCU_Back_Locking);
			}
		}
		
		if(HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_INPUT_12) != Event_appDate.CheckLockStatus)//三角舌/*定时读取三角舌状态判断开关门*/
		{
			if(HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_INPUT_12))
			{//高电平是开门状态
				Event_appDate.CheckLockStatus = 1;
			}else{
				//低电平是关门状态
				Event_appDate.CheckLockStatus = 0;
			}
			DataTransmition(MCU_Door_Event);
			printf("DLS %x\n",Event_appDate.CheckLockStatus);
		}
		GPIOInPut_DeInit(EXTI_GPIO_PORT,SWITCH_INPUT_10|SWITCH_INPUT_12);

		
		GPIOInPut_Init(BUTTON_GPIO_PORT,BUTTON_INPUT_5|BUTTON_INPUT_6);
		if(HAL_GPIO_ReadPin(BUTTON_GPIO_PORT,BUTTON_INPUT_5))
		{
			//长按复位，直接循环三秒，三秒内按键一直都是按下状态就复位
			if(!Event_appDate.RSTZB_PreKeyTick)
			{
				Event_appDate.RSTZB_PreKeyTick = Event_appDate.SysTime;//记录按下的时间
			}
		}else 
		{
			if(Event_appDate.RSTZB_PreKeyTick)
			{
				if(Event_appDate.SysTime >= Event_appDate.RSTZB_PreKeyTick)
				{
					Event_appDate.RSTZB_KeyTick = Event_appDate.SysTime - Event_appDate.RSTZB_PreKeyTick;//记录按下->释放的时间长度
					if(Event_appDate.RSTZB_KeyTick>3)
					{
						DataTransmition(MCU_RstZigBee);
						Event_appDate.RSTZB_KeyTick = 0 ; //清空按键计数
						Event_appDate.RSTZB_PreKeyTick = 0;
					}
				}else{
					Event_appDate.RSTZB_KeyTick = HAL_MAX_DELAY - Event_appDate.RSTZB_PreKeyTick + Event_appDate.SysTime;//记录按下->释放的时间长度
					if(Event_appDate.RSTZB_KeyTick>3)
					{
						DataTransmition(MCU_RstZigBee);
						Event_appDate.RSTZB_KeyTick = 0 ; //清空按键计数
						Event_appDate.RSTZB_PreKeyTick = 0;
					}
				}

			}
		}

		//重启全部模块（只要STM重启蓝牙和zigbee模块都会重启）
		if(HAL_GPIO_ReadPin(BUTTON_GPIO_PORT,BUTTON_INPUT_6))
		{
			//长按复位，直接循环三秒，三秒内按键一直都是按下状态就复位
			if(!Event_appDate.RSTMCU_PreKeyTick)
			{
				Event_appDate.RSTMCU_PreKeyTick = Event_appDate.SysTime;//记录按下的时间
			}
		}
		else 
		{
			if(Event_appDate.RSTMCU_PreKeyTick)
			{
				if(Event_appDate.SysTime >= Event_appDate.RSTZB_PreKeyTick)
				{
					Event_appDate.RSTMCU_KeyTick = Event_appDate.SysTime - Event_appDate.RSTMCU_PreKeyTick;//记录按下->释放的时间长度
					if(Event_appDate.RSTMCU_KeyTick>3)
					{
						DataTransmition(MCU_RstMCU);
						Event_appDate.RSTMCU_KeyTick = 0 ; //清空按键计数
						Event_appDate.RSTMCU_PreKeyTick = 0;
					}
				}else{
					Event_appDate.RSTMCU_KeyTick = HAL_MAX_DELAY - Event_appDate.RSTMCU_PreKeyTick + Event_appDate.SysTime;//记录按下->释放的时间长度
					if(Event_appDate.RSTMCU_KeyTick>3)
					{
						DataTransmition(MCU_RstMCU);
						Event_appDate.RSTMCU_KeyTick = 0 ; //清空按键计数
						Event_appDate.RSTMCU_PreKeyTick = 0;
					}
				}
			}
		}
		if((HAL_GPIO_ReadPin(BUTTON_GPIO_PORT,BUTTON_INPUT_6))&&(HAL_GPIO_ReadPin(BUTTON_GPIO_PORT,BUTTON_INPUT_5)))
		{
			Event_appDate.FactoryKeyTick ++ ;
			if(Event_appDate.FactoryKeyTick > 3)
			{
				DataTransmition(MCU_FactoryReset_Event);
				Event_appDate.FactoryKeyTick = 0 ; //清空按键计数
			}
		}
		GPIOInPut_DeInit(BUTTON_GPIO_PORT,BUTTON_INPUT_5|BUTTON_INPUT_6);
#endif
}

void Appication_Funtion(void)
{
			BLEUUID_Function();
	
			/* *************************************************************************** */
			/* RTC内部中断 */
			if(Device_Wkup_Flag_Now & DEVICE_RTC_INT_FLAG)
			{
//					printf("RTC Internal Wkup!!\n");
					HAL_IWDG_Refresh(&IwdgHandle);
					Test_Function();
			}
			
//			/* *************************************************************************** */
//			/* RTC闹钟中断 */
//			if(Device_Wkup_Flag_Now & DEVICE_ALARM_WKUP_FLAG)
//			{
//					printf("RTC Alarm Wkup!!\n");
//					RTC_Massage_Printf(); 
//			}
			
			/* *************************************************************************** */
			/* BUTTOM中断 */
			if(Device_Wkup_Flag_Now & DEVICE_FMXX_IRQ_FLAG)
			{
//					printf("Buttom Wkup!!\n");
					HAL_IWDG_Refresh(&IwdgHandle);
					GPIO_IRQ_Event();
			}
			
#ifdef Zigbee_IRQ
			if(Device_Wkup_Flag_Now & DEVICE_ZIGB_IRQ_FLAG)
			{
				Uart1_InterruptEnable(ENABLE, DISABLE);
				USART1_RX_STA = 0;
				Event_appDate.Uart1Ready = RESET;	
				Event_appDate.TimeOut = 10;
				Event_appDate.Uart1length = 0;
			}
#endif  
				
#ifdef SWITCH_EXTI_8
			if(Device_Wkup_Flag_Now & DEVICE_SWTH_IO8_FLAG)
			{
				GPIOInPut_Init(EXTI_GPIO_PORT,SWITCH_EXTI_8);
				HAL_Delay(60);
				printf("SW8 %x \n",HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_EXTI_8));
				if(!HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_EXTI_8))
				{
					ReadIO();
				}
				GPIOEXIT_Init(EXTI_GPIO_PORT,SWITCH_EXTI_8);
			}
#endif 


}

void LowPowerMode(void)
{
	if((!Event_appDate.Uart1Ready)&&(!Event_appDate.Uart1length))
	{
		/* 清除唤醒源标志 */
		Device_Wkup_Flag_Now = DEVICE_NON_WKUP_FLAG;
		HAL_Delay(100);
		if (USART1_RX_STA & 0x8000) 
		{																//接收到期待的应答结果
			Event_appDate.Uart1length = USART1_RX_STA & 0x1FFF;
			USART1_RX_STA &= 0x2000;																	//缓存状态清0可继续接收
			Event_appDate.Uart1Ready = SET;
			Uart1_InterruptEnable(DISABLE, DISABLE);
			Zigbee_Payload();
		}
		if(Event_appDate.Uart1Ready != SET)
		{
			Event_appDate.TimeOut -- ;
			LOG(LOG_NOL,"TO %x\n",Event_appDate.TimeOut);
			if(!Event_appDate.TimeOut&&(!Event_appDate.Uart1length))
			{
				Event_appDate.Uart1Ready = SET;
			}
		}
	}else
	{

		/* 清除唤醒源标志 */
		Device_Wkup_Flag_Now = DEVICE_NON_WKUP_FLAG;
		LOG(LOG_INF,"S\n");
		LowPower_enter_stop();
		LowPower_WakeUp();
		uwTick += 1000;
		IncSecondTick();
	}
}
