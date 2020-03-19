/**
  *********************************************************************************************************
  * @file	Event.c
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
#include "gpio.h"
#include "Record.h"
#include "stm32l0xx_hal.h"
#include "1755test.h"
#include "time.h"
#include "Debug.h"

#include "libcrc.h"

Event_AppData         Event_appDate;
union RTCParameterConfiguration RTCPConfiguration;
//union RTCParameterConfiguration RTCPCFAtion[4];

extern union Lock_Record Lockrecord;
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


//void RecordAndLimit_Check(void)
//{
//	uint16_t res = 0;
//	Get_RTC(Event_appDate.RtcTime);
//	res = Event_appDate.RtcTime[4] * 60 + Event_appDate.RtcTime[5];
//	if((res > ReportingTimeStart)&&(res < ReportingTimeStop))//2点到4点
//	{
//		Event_appDate.report_record_Time = 600;//开机检测成功将在10分钟之后开启记录上报
//	}
//	printf("report_record_Time %x \r\n",Event_appDate.report_record_Time);
//}

//限时工作
void Timing_limit_Function(void)
{
	int Mtime4 = 0,Mtime3 = 0,Mtime2 = 0,Mtime1 = 0,Mtime = 0;
	Get_RTC(Event_appDate.RtcTime);
//	if(SRPConfiguration.sParameterConfiguration.Restricted_Start_Time[0] != SRPConfiguration.sParameterConfiguration.Restricted_Stop_Time[0])
//	{
		Mtime = SRPConfiguration.sParameterConfiguration.Restricted_Start_Time[0]*60 + SRPConfiguration.sParameterConfiguration.Restricted_Start_Time[1];
		Mtime1 = SRPConfiguration.sParameterConfiguration.Restricted_Stop_Time[0]*60 + SRPConfiguration.sParameterConfiguration.Restricted_Stop_Time[1];
		if(Mtime!=Mtime1)
		{
			Mtime2 = Event_appDate.RtcTime[4] * 60 + Event_appDate.RtcTime[5];
			if(Mtime < Mtime1)
			{
//				printf("Mtime %d Mtime1 %d Mtime2 %d\r\n",Mtime,Mtime1,Mtime2);
				if((Mtime2 > Mtime)&&Mtime2 < Mtime1)
				{
					Event_appDate.Timing_LimitFlag = 1;
				}else
				{
					Event_appDate.Timing_LimitFlag = 0;
				}
			}else{
				Mtime3 = (1440-Mtime2);//24*60=1440
				Mtime4 = (1440-Mtime1);
//				printf("Mtime %d Mtime1 %d Mtime2 %d Mtime3 %d Mtime4 %d\r\n",Mtime,Mtime1,Mtime2,Mtime3,Mtime4);
				if((Mtime2 > Mtime)&&(Mtime3 < Mtime4))
				{
					Event_appDate.Timing_LimitFlag = 1;
				}else
				{
					Event_appDate.Timing_LimitFlag = 0;
				}
			}
		}
//	}
}

/**********************************************************************************************************
 @Function			time_t RTC_TimeToStamp(u8 year, u8 month, u8 date, u8 hour, u8 min, u8 sec)
 @Description			时间转换为UNIX时间戳
 @Input				year, month, date 	: 年(0~99), 月(1~12), 日(0~31)
					hour, min, sec 	: 小时, 分钟, 秒钟
 @Return				time_t			: 时间戳
**********************************************************************************************************/
time_t RTC_TimeToStamp(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t min, uint8_t sec)
{
	struct tm time;
	time.tm_year = year + 100;											
	time.tm_mon =  month - 1;												//0~11 表示 1~12月
	time.tm_mday = date;
	time.tm_hour = hour - 8;
	time.tm_min = min;
	time.tm_sec = sec;
	
	return mktime(&time);
}

/**********************************************************************************************************
 @Function			struct tm RTC_ConvUnixToCalendar(time_t t)
 @Description			转换UNIX时间戳为日历时间
 @Input				UNIX时间戳
 @Return				struct tm
**********************************************************************************************************/
struct tm RTC_ConvUnixToCalendar(time_t t)
{
	struct tm *t_time;
	
	t_time = localtime(&t);
	t_time->tm_year -= 100;												//1900年标准转换至2000年标准
	t_time->tm_mon += 1;												//0~11标准转换至1~12标准
	
	return *t_time;
}


void  NTP_Shop_Funtion(void)
{
//	printf("NTP_No %x NTP_Flag %x \r\n",Event_appDate.NTP_No,Event_appDate.NTP_Flag);
	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;
	
	/* Get the RTC current Time */
	HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);
	printf("Time:20%d:%d:%d:%d:%d:%d \r\n", sdatestructureget.Year,
																					sdatestructureget.Month,
																					sdatestructureget.Date,
																					stimestructureget.Hours,
																					stimestructureget.Minutes,
																					stimestructureget.Seconds);
	
//	if(Event_appDate.RTC_Flag&&(Event_appDate.NTP_No<6))
//	{
//		printf("NTP_Flag %x NTP_Time %x NTP_No %x\r\n",Event_appDate.NTP_Flag,Event_appDate.NTP_Time,Event_appDate.NTP_No);
//		if(!Event_appDate.NTP_Flag)
//		{

//			Event_appDate.NTP_value[Event_appDate.NTP_No] = RTC_TimeToStamp(sdatestructureget.Year,
//																																			sdatestructureget.Month,
//																																			sdatestructureget.Date,
//																																			stimestructureget.Hours,
//																																			stimestructureget.Minutes,
//																																			stimestructureget.Seconds);
//			printf("RTC_TimeToStamp %08x \r\n",Event_appDate.NTP_value[Event_appDate.NTP_No]);
//			Event_appDate.NTP_No++;
//			Event_appDate.NTP_Flag = 1;
//			printf("NTP_Flag %x \r\n",Event_appDate.NTP_Flag);
//		}
//		if(Event_appDate.NTP_Flag&&(!Event_appDate.NTP_Time))
//		{
//			DataTransmition(MCU_Get_RTC_Event);
//			Event_appDate.NTP_Time = 5;
//		}
//		Event_appDate.NTP_Time--;
//		
//	}else{
//		if(Event_appDate.NTP_No>5)
//		{
//			Event_appDate.Average_value = ((Event_appDate.NTP_value[3] - Event_appDate.NTP_value[2])+
//																			(Event_appDate.NTP_value[1] - Event_appDate.NTP_value[0]))/2;
//			Event_appDate.Average_value += (Event_appDate.NTP_value[5] - Event_appDate.NTP_value[4])+
//																			(Event_appDate.NTP_value[3] - Event_appDate.NTP_value[2])/2;
//			Event_appDate.Average_value = Event_appDate.Average_value/2;
//			
//			printf("Average_value %08x \r\n",Event_appDate.Average_value);
//			Event_appDate.RTC_Flag = 0;
//		}
//		
//		struct tm Datetime;
//		Datetime = RTC_ConvUnixToCalendar(Event_appDate.Average_value);
//		printf("Datetime %x:%x:%x:%x:%x:%x \r\n",Datetime.tm_year,
//																						Datetime.tm_mon,
//																						Datetime.tm_mday,
//																						Datetime.tm_hour,
//																						Datetime.tm_min,
//																						Datetime.tm_sec);
//		
//	}
}

void ReadIO(void)
{
	GPIOInPut_Init(EXTI_GPIO_PORT,SWITCH_INPUT_3|SWITCH_INPUT_5|SWITCH_INPUT_9);
	HAL_Delay(60);
//	printf("SWITCH_INPUT_3 %x \r\n",HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_INPUT_3));
//	printf("SWITCH_INPUT_5 %x \r\n",HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_INPUT_5));
//	printf("SWITCH_INPUT_9 %x \r\n",HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_INPUT_9));
	if(!HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_INPUT_9))//钥匙开门
	{
		DataTransmition(MCU_Key);
	}
	if(HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_INPUT_5))//后面板开门
	{
//		DataTransmition(MCU_Open_Door_Event);
		Event_appDate.RearLockTime = 1;
	}
	if(HAL_GPIO_ReadPin(EXTI_GPIO_PORT,SWITCH_INPUT_3))//前面板开门
	{
		if(Event_appDate.Operational_events)
		{
			Lock_Event(0);
		}
		else{
			Buzz_Rhythm(Fault);
//			Event_appDate.FrontLockTime = 1;
			DataTransmition(MCU_Abnormal_Lock_Alarm);
		}
	}
	GPIOInPut_DeInit(EXTI_GPIO_PORT,SWITCH_INPUT_3|SWITCH_INPUT_5|SWITCH_INPUT_9);
}



void MCU_GetUID(void)
{
//	sprintf((char *)Event_appDate.UID,"4B595A48%08x%08x%08x",HAL_GetUIDw2(),HAL_GetUIDw1(),HAL_GetUIDw0());
}
/**
  * @brief  Display the current time and date.
  * @param  showtime : pointer to buffer
  * @param  showdate : pointer to buffer
  * @retval None
  */
void Get_RTC(uint8_t* rtconfig)
{
  RTC_DateTypeDef sdatestructureget;
  RTC_TimeTypeDef stimestructureget;
  
  /* Get the RTC current Time */
  HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);
  /* Get the RTC current Date */
  HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);
  
	rtconfig[0] = 0xFF & ((2000 + sdatestructureget.Year)>>8);
	rtconfig[1] = 0xFF & (2000 + sdatestructureget.Year);
	rtconfig[2] = sdatestructureget.Month;
	rtconfig[3] = sdatestructureget.Date;
	rtconfig[4] = stimestructureget.Hours; 
	rtconfig[5] = stimestructureget.Minutes;
	rtconfig[6] = stimestructureget.Seconds;

//	printf("Time:%x:%x:%x:%x:%x:%x%x \r\n", rtconfig[0],rtconfig[1],rtconfig[2],rtconfig[3],rtconfig[4],rtconfig[5],rtconfig[6]);
} 


void RTCConfig(RTC_event* rtconfig)
{
//	RTC_Init();
	
	uint16_t datayear = 0;
	uint8_t data[3];
//	rtconfig->Seconds += rtconfig->Seconds + 20;
	
	if((rtconfig->Year[0]>6)&&(rtconfig->Year[0]<9))//检测数据是否为空
	{
		printf("Time:%x:%x:%x:%x:%x:%x:%x \r\n", rtconfig->Year[0],rtconfig->Year[1],rtconfig->Month,rtconfig->Date,rtconfig->Hours,rtconfig->Minutes,rtconfig->Seconds);
		datayear = ((rtconfig->Year[0]<<8|rtconfig->Year[1])-2000);
		
		data[0]=datayear/16;
		data[1]=datayear%16;
		datayear = (data[0]<<4)+(data[0]*6+data[1]);
		
		RTC_DateTypeDef sdatestructure;
		RTC_TimeTypeDef stimestructure;

		/*##-2- Configure the Date #################################################*/
		/* Set Date: Monday April 14th 2014 */
		sdatestructure.Year    = datayear;
		sdatestructure.Month   = RTC_ByteToBcd2(rtconfig->Month);
		sdatestructure.Date    = RTC_ByteToBcd2(rtconfig->Date);
		sdatestructure.WeekDay = 0x00;
		
		if(HAL_RTC_SetDate(&RtcHandle,&sdatestructure,RTC_FORMAT_BCD) != HAL_OK)
		{
			/* Initialization Error */
			Error_Handler(); 
		} 
		
		/*##-3- Configure the Time #################################################*/
		/* Set Time: 08:10:00 */
		stimestructure.Hours          =  RTC_ByteToBcd2(rtconfig->Hours);
		stimestructure.Minutes        =  RTC_ByteToBcd2(rtconfig->Minutes);
		stimestructure.Seconds        =  RTC_ByteToBcd2(rtconfig->Seconds);
		stimestructure.SubSeconds     = 0x00;
	//  stimestructure.TimeFormat     = RTC_HOURFORMAT12_AM;
		stimestructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE ;
		stimestructure.StoreOperation = RTC_STOREOPERATION_RESET;
		
		if(HAL_RTC_SetTime(&RtcHandle,&stimestructure,RTC_FORMAT_BCD) != HAL_OK)
		{
			/* Initialization Error */
			Error_Handler(); 
		}
	}
}

void Swipe_Event(void)
{
	int i;
	uint8_t status,swiping_card = 0;
	if(Event_appDate.Timing_LimitFlag)
	{
		printf("Timing_Limit %d\n\r",Event_appDate.Timing_LimitFlag);
	}
	if(Event_appDate.Irq_Signal)
	{
		memcpy(Event_appDate.ucCardId,Type_A.UID,4 * Type_A.CASCADE_LEVEL);

		if(!swiping_card)
		{
			status = strncmp((char*)Event_appDate.ucCardId,(char*)Event_appDate.AdminCard,4);
			if(!status)
			{
				swiping_card = 1;
				SYSTEM_DEBUG = !SYSTEM_DEBUG;
				if(SYSTEM_DEBUG)
				DataTransmition(MCU_Log_Parameters);//上报平台查询
			}
		}
		if(!SRPConfiguration.sParameterConfiguration.Restricted_Condition)
		{
			if(!Event_appDate.Timing_LimitFlag)
			{
				if((!supercard.cardnumber)&&(!normalcard.cardnumber)&&(!blacklistcard.cardnumber))//无卡
				{
					DataTransmition(MCU_No_Card);
				}
				else
				{
					if(!swiping_card)
					{
						for(i=0;i<normalcard.cardnumber;i++)
						{
							status = strncmp((char*)Event_appDate.ucCardId,(char*)normalcard.Idcard.cardId[i],4);
	//						printf("normalcard status %x BackLocking %x\r\n", status,Event_appDate.BackLocking[1]);
							if(!status)
							{
								DataTransmition(MCU_NormalcardEvent);
								swiping_card = 1;
								break;
							}
						}
					}
					if(!swiping_card)
					{
						for(i=0;i<supercard.cardnumber;i++)
						{
							status = strncmp((char*)Event_appDate.ucCardId,(char*)supercard.Idcard.cardId[i],4);
	//						printf("supercard status %x\r\n", status);
							if(!status)
							{
								DataTransmition(MCU_SupercardEvent);
								swiping_card = 1;
								break;
							}
						}
					}
					if(!swiping_card)
					{
						for(i=0;i<blacklistcard.cardnumber;i++)
						{
							status = strncmp((char*)Event_appDate.ucCardId,(char*)blacklistcard.Idcard.cardId[i],4);
	//						printf("blacklistcard status %x\r\n", status);
							if(!status)
							{
								DataTransmition(MCU_BlacklistEvent);//检测是否在黑名单内，在名单内存储记录，不在上报平台
								swiping_card = 1;
								break;
							}
						}
					}
					if((!swiping_card)&&(Event_appDate.SwipCardNumber<2))
					{
						DataTransmition(MCU_No_Card);//上报平台查询
					}

					if(Event_appDate.SwipCardNumber<10)
					{
						memcpy(Event_appDate.SwipCardID[Event_appDate.SwipCardNumber],Event_appDate.ucCardId,4);
						Event_appDate.SwipCardNumber ++;//不停刷卡
					}
				}
			}
		}
		else{//锁定
			printf("Device locked \r\n");
			Zigbee_Transport_SendCmd(MCU_Equipment_lock_or_unlock,1,&SRPConfiguration.sParameterConfiguration.Restricted_Condition);
		}
	}
//	memset(Event_appDate.ucCardId,0,4);
	swiping_card = 0;
	Event_appDate.Irq_Signal = 0;
}


void Lock_Event(uint8_t flag)
{
	if(flag)
	{
			if(!Event_appDate.DoorFlag)
			{
				Lock_Open(FALSE);
				Event_appDate.AutoClosingTime = Event_appDate.SetOffTime;
				Event_appDate.DoorFlag = 1;
			}

			GetRecordData();
			if(Event_appDate.Operation_Sign)//APP开锁回复的
			{
				Zigbee_Transport_SendCmd(MCU_Online_UnLock_Event,12,Lockrecord.cardId_array);
			}
			else{
				//内开门或刷卡上报的
				if((Event_appDate.SwipCardNumber<2)||(Event_appDate.Authentication_Flag))
				{
					Zigbee_Transport_SendCmd(MCU_UnLocking,12,Lockrecord.cardId_array);
					if(Event_appDate.Authentication_Flag)
						Event_appDate.Authentication_Flag = 0;
				}
			}
			Buzz_Rhythm(UnLock);
	}else{
		//printf("Operational_events %x \r\n",Event_appDate.Operational_events);
		if(Event_appDate.DoorFlag&&Event_appDate.Operational_events)
		{
			WirteOneRecord();
			Lock_Close(FALSE);
			Event_appDate.BackLocking[1] = 1;
			Event_appDate.DoorFlag = 0;
			Event_appDate.Operational_events = 0;
			Event_appDate.AutoClosingTime = 0;
			
			Get_RTC(Event_appDate.RtcTime);
			Zigbee_Transport_SendCmd(MCU_Locking,7,Event_appDate.RtcTime);
			memset(Event_appDate.RtcTime,0,sizeof(Event_appDate.RtcTime));
		}
	}
}

void  Front_Handle_Event(void)
{
	printf("Operational_events %x \r\n",Event_appDate.Operational_events);
	if(Event_appDate.Operational_events)
	{
		Lock_Event(0);
	}else{
		Buzz_Rhythm(Fault);
		DataTransmition(MCU_Abnormal_Lock_Alarm);
	}
}
//读取flash型号，FM17550的型号，蓝牙通讯是否回复
uint8_t Device_Self_Checking(void)
{
	Event_appDate.Self_check_result = 0x01;
	
	Flash_NSS();
	FLASH_Init();	
	//BLE_PWRC_Init();//唤醒蓝牙

	if(SPI_Flash_ReadID() != 0X1f15)
	{
		Event_appDate.Self_check_result += 0x01;
	}
	if(Official_Test() != 0x88)
	{
		Event_appDate.Self_check_result += 0x01;
	}

	/*if(BLE_Self_Checking(&BLEATcmd) != BLE_OK)
	{
		Event_appDate.Self_check_result += 0x01;
		DataTransmition(MCU_BLE_Close);
	}else{
		DataTransmition(MCU_BLE_Close);
	}
	*/
	Flash_DeInit();
	return Event_appDate.Self_check_result;
}

uint8_t AbnormalSwipe(void)
{
	uint8_t AbnormalStatus = 0;
	for(int i = 0;i<6;i++)
	{
		AbnormalStatus = strncmp((char*)Event_appDate.SwipCardID[5],(char*)Event_appDate.SwipCardID[i],4);
		printf("AbnormalStatus %x \r\n",AbnormalStatus);
		if(AbnormalStatus)
		{
			return 0;
		}
	}
	return 1;
}

void NTPTIME_Funtion(void)
{
	printf("NTP\r\n");
	//Get_RTC(Event_appDate.RtcTime);
	//memcpy(&Event_appDate.Txbuffer[0],Event_appDate.RtcTime,sizeof(Event_appDate.RtcTime));
	
	Event_appDate.Txbuffer[0]=0x00;
	Event_appDate.Txbuffer[1]=0xf0;
	Zigbee_Transport_SendCmd(MCU_Get_RTC_Event,2,Event_appDate.Txbuffer);
}

void DataTransmition(unsigned char number)
{
	
	switch (number)
	{

		case MCU_RstMCU://（重启按键，把zigbee模块和蓝牙重启）
			LOG(LOG_NOL,"RM\n");
			Zigbee_Transport_SendCmd(MCU_RstZigBee,1,&Event_appDate.status);//清空终端网关数据
			HAL_Delay(1000);
			HAL_NVIC_SystemReset();
			break;

		case MCU_Device_Self_Checking://设备自检
			Device_Self_Checking();
			printf("Device_Self_Checking %x \n\r",Event_appDate.Self_check_result);
			Zigbee_Transport_SendCmd(MCU_Device_Self_Checking,1,&Event_appDate.Self_check_result);//回复成功
			break;
			
		case MCU_Get_RTC_Event:
//			printf("Get_RTC_Event\n\r");
//		  Event_appDate.NTP_Type = 0x02;
//			Zigbee_Transport_SendCmd(MCU_Get_RTC_Event,1,&Event_appDate.NTP_Type);//回复成功
			NTPTIME_Funtion();
			break;
			
		case MCU_Set_RTC_Event:
			printf("Set_RTC_Event\n\r");
			RTCConfig(&RTCPConfiguration.rtc_event);
			Event_appDate.ZBParameterSet[0] = 0x0D;//0x78--》2分钟 0xb2--》三分钟 0xF0--》四分钟
			Event_appDate.ZBParameterSet[1] = 0x00;
			Event_appDate.ZBParameterSet[2] = 0xFF;
			Event_appDate.ZBParameterSet[3] = 0xFF;
			Zigbee_Transport_SendCmd(MCU_Set_RTC_Event,4,Event_appDate.ZBParameterSet);
//			Zigbee_Transport_SendCmd(MCU_Set_RTC_Event,1,&Event_appDate.status);
			Event_appDate.NTP_Flag = 0;
			Event_appDate.RTC_Flag = 1;
			break;
			
		case MCU_Abnormal_Lock_Alarm://门锁异常
			printf("Abnormal_Lock_Alarm\n\r");
			Zigbee_Transport_SendCmd(MCU_Abnormal_Lock_Alarm,1,&Event_appDate.status);//回复成功
			break;
			
		case MCU_Electricity_Query:
			Event_appDate.Voltagedata[Event_appDate.VoltageNo] = VBAT_ADC_Read(600);
			Event_appDate.VoltageAverage += Event_appDate.Voltagedata[Event_appDate.VoltageNo];
			Event_appDate.VoltageAverage = Event_appDate.VoltageAverage/2;
			printf("VoltageAverage %d %d\n\r",Event_appDate.VoltageAverage,SRPConfiguration.sParameterConfiguration.Voltage);
			if(Event_appDate.VoltageNo>2)
			{
				Event_appDate.VoltageNo = 0;
			}else
			Event_appDate.VoltageNo++;
			
			if(Event_appDate.VoltageAverage < SRPConfiguration.sParameterConfiguration.Voltage)
			{
				Event_appDate.lastlog = Low_Battery;
				Zigbee_Transport_SendCmd(MCU_Low_Power_Alarm,1,&Event_appDate.status);//回复成功
			}else{
				NTPTIME_Funtion();//同步时间
			}
			break;
			
		case MCU_Parameter_Configuration://门禁配置
			printf("Parameter_Configuration\n\r");
//			Event_appDate.ZBParameterSet[0] = 0x02;
//			Event_appDate.ZBParameterSet[1] = 0;
//			Event_appDate.ZBParameterSet[2] = 0xFF;
//			Event_appDate.ZBParameterSet[3] = 0xFF;
//			Zigbee_Transport_SendCmd(MCU_Parameter_Configuration,4,Event_appDate.ZBParameterSet);
			Zigbee_Transport_SendCmd(MCU_Parameter_Configuration,1,&Event_appDate.status);//回复成功
			ReadConfiguration_Parameters();
			Timing_limit_Function();
			break;
			
		case MCU_Issued_Door_Card://平台设置开门权限（发卡）
			printf("Issued_Door_Card\n\r");
			Zigbee_Transport_SendCmd(MCU_Issued_Door_Card,1,&Event_appDate.status);//回复成功
			break;
		
		case MCU_ChangeAddress:
			printf("MCU_ChangeAddress %x\n\r",MCU_ChangeAddress);
			Zigbee_Transport_SendCmd(MCU_ChangeAddress,1,&Event_appDate.ChangeAddressFlag);//回复成功
			Event_appDate.ChangeAddressFlag = 0xff;
			break;

		case MCU_Query_Lock_Record://平台查询操作记录
			printf("Query_Lock_Record\n\r");
			Terminal_Record();
			break;

		case MCU_Restricted_Event://限制开门（包含APP和刷卡）加载限制计时器
			break;
			
		case MCU_Online_UnLock_Event://命令开门
			printf("Online_UnLock_Event\r\n");
			Event_appDate.Operational_events = 1;
			Event_appDate.Operation_Sign = 0x01;
			DataTransmition(MCU_UnLocking);
			break;

		case MCU_Swipe_Events://刷卡事件
			printf("Swipe_Events\r\n");
			Event_appDate.Operational_events = 2;
			Event_appDate.Operation_Sign = 0x00;
			//2019/10/05
			Swipe_Event();
			break;
			
		case MCU_UnLocking://开锁事件
			printf("Card_UnLocking\r\n");
			Lock_Event(TRUE);
			break;
			
		case MCU_Locking://关锁事件
			printf("Locking\r\n");
			Lock_Event(0);
			break;
			
	case MCU_NormalcardEvent:
//			printf("MCU_NormalcardEvent\r\n");
			if(Event_appDate.BackLocking[1])
			{
				DataTransmition(MCU_UnLocking);
			}
			else{
				Buzz_Rhythm(UnLock);//刷卡成功
				GetRecordData();
				Zigbee_Transport_SendCmd(MCU_UnLocking,12,Lockrecord.cardId_array);
				WirteOneRecord();
			}
			break;
			
	case MCU_SupercardEvent:
//			printf("MCU_SupercardEvent\r\n");
			DataTransmition(MCU_UnLocking);
			break;
		
		case MCU_BlacklistEvent:
			printf("BlacklistEvent\r\n");
			Event_appDate.Operation_Sign = 0x00;
			Buzz_Rhythm(Illegal_Card);
			GetRecordData();
//			Zigbee_Transport_SendCmd(MCU_BlacklistEvent,12,Lockrecord.cardId_array);
			WirteOneRecord();
			break;
			
		case MCU_Open_Door_Event:
			printf("MCU_Open_Door_Event\n\r");
			memset(Event_appDate.ucCardId,0xff,sizeof(Event_appDate.ucCardId));
			GetRecordData();
			Zigbee_Transport_SendCmd(MCU_Open_Door_Event,12,Lockrecord.cardId_array);
			break;
			
//		case Maintenance://维修卡
//			printf("Maintenance\n\r");
//			break;
			
		case MCU_Not_Exist_Card://没有任何卡
			printf("Storage No card number\n\r");
			Zigbee_Transport_SendCmd(MCU_Not_Exist_Card,4,Event_appDate.ucCardId);//回复成功
			break;
			
		case MCU_No_Card://查无该卡
			printf("not exist card \n\r");
			Get_RTC(Event_appDate.RtcTime);
			memcpy(&Event_appDate.Txbuffer[0],Event_appDate.RtcTime,sizeof(Event_appDate.RtcTime));
			memcpy(&Event_appDate.Txbuffer[sizeof(Event_appDate.RtcTime)],Event_appDate.ucCardId,sizeof(Event_appDate.ucCardId));
			Zigbee_Transport_SendCmd(MCU_No_Card,11,Event_appDate.Txbuffer);
			break;
			
		case MCU_Back_Locking://反锁
			printf("Back_Locking \n\r");
			Event_appDate.BackLocking[0] = 2;
			Event_appDate.BackLocking[1] = 0;
		
			Get_RTC(Event_appDate.RtcTime);
			memcpy(&Event_appDate.Txbuffer[0],Event_appDate.RtcTime,sizeof(Event_appDate.RtcTime));
			memcpy(&Event_appDate.Txbuffer[sizeof(Event_appDate.BackLocking)],Event_appDate.BackLocking,sizeof(Event_appDate.BackLocking));

			Zigbee_Transport_SendCmd(MCU_Back_Locking,9,Event_appDate.Txbuffer);
			break;
			
		case MCU_Back_Unlocking://解除反锁
			printf("Back_Unlocking \n\r");
			Event_appDate.BackLocking[0] = 2;
			Event_appDate.BackLocking[1] = 1;
		
			Get_RTC(Event_appDate.RtcTime);
			memcpy(&Event_appDate.Txbuffer[0],Event_appDate.RtcTime,sizeof(Event_appDate.RtcTime));
			memcpy(&Event_appDate.Txbuffer[sizeof(Event_appDate.BackLocking)],Event_appDate.BackLocking,sizeof(Event_appDate.BackLocking));

			Zigbee_Transport_SendCmd(MCU_Back_Unlocking,9,Event_appDate.Txbuffer);

			break;
		
		case MCU_BLE_Open://开启蓝牙
			printf("MCU_BLE_Open \n\r");
			BLE_Wakeup(&BLEATcmd);
			Zigbee_Transport_SendCmd(MCU_BLE_Open,1,&Event_appDate.status);
			break;
		
		case MCU_BLE_Close://关锁蓝牙
			BLE_Sleep_Mode(&BLEATcmd);
			Zigbee_Transport_SendCmd(MCU_BLE_Close,1,&Event_appDate.status);//解决APP开启蓝牙，但是没下发开锁命令
			break;
		
		case MCU_Query_UUID://查询UUID
			//MCU_GetUID();
			Zigbee_Transport_SendCmd(MCU_Query_UUID,32,&Event_appDate.UID[0]);
			break;
		
		case MCU_Equipment_lock_or_unlock:
			printf("MCU_Equipment_lock_or_unlock %x\r\n",SRPConfiguration.sParameterConfiguration.Restricted_Condition);
			if(SRPConfiguration.sParameterConfiguration.Restricted_Condition)
			{			
				Event_appDate.lastlog = Equipment_Lock;
			}else{
				Event_appDate.lastlog = 0;
			}
			WirteConfiguration_Parameters();
			Zigbee_Transport_SendCmd(MCU_Equipment_lock_or_unlock,0,0);
			break;
	case MCU_NetworkState:
			printf("MCU_NetworkState\r\n");
			Event_appDate.lastlog = Normal_Mode;
			Event_appDate.ZBParameterSet[0] = 0xD0;//0x78--》120s 0xb2--》180s 0xF0--》240s 0xD0--》210s
			Event_appDate.ZBParameterSet[1] = 0;
			Event_appDate.ZBParameterSet[2] = 0xFF;
			Event_appDate.ZBParameterSet[3] = 0xFF;
			Zigbee_Transport_SendCmd(MCU_NetworkState,4,Event_appDate.ZBParameterSet);
			if(Event_appDate.NetworkState)
			{
				Event_appDate.NetRstTime = 0xfffe;
			}
			break;
	case MCU_Key:
			printf("MCU_Key\r\n");
			Get_RTC(Event_appDate.RtcTime);
			Event_appDate.Txbuffer[7] = 0x02;
			memcpy(&Event_appDate.Txbuffer[0],Event_appDate.RtcTime,sizeof(Event_appDate.RtcTime));
			Zigbee_Transport_SendCmd(MCU_Key,8,Event_appDate.Txbuffer);
			break;
	case MCU_Front_Locking:
			printf("MCU_Front_Locking\r\n");
			Front_Handle_Event();
			break;
	case MCU_RstZigBee:
			LOG(LOG_NOL,"RZ\n");
			Zigbee_RST_Init();
			HAL_Delay(500);
			Zigbee_Transport_SendCmd(MCU_RstZigBee,1,&Event_appDate.status);
			break;
	case MCU_Door_Event:
			printf("MCU_Door_Event\r\n");
			Zigbee_Transport_SendCmd(MCU_Door_Event,1,&Event_appDate.CheckLockStatus);
			break;
	case MCU_AbnormalSwipe:
			printf("MCU_AbnormalSwipe\r\n");
			if(AbnormalSwipe())
			{			
				Get_RTC(Event_appDate.RtcTime);
				memcpy(&Event_appDate.Txbuffer[0],Event_appDate.RtcTime,sizeof(Event_appDate.RtcTime));
				memcpy(&Event_appDate.Txbuffer[sizeof(Event_appDate.RtcTime)],Event_appDate.ucCardId,sizeof(Event_appDate.ucCardId));

				Zigbee_Transport_SendCmd(MCU_AbnormalSwipe,11,Event_appDate.Txbuffer);
			}
			Event_appDate.SwipCardNumber = 0;
			break;
	case MCU_FactoryReset_Event:
			printf("MCU_FactoryReset_Event\r\n");
			Factory_Reset();
			Zigbee_Transport_SendCmd(MCU_FactoryReset_Event,1,&Event_appDate.status);
			Zigbee_RST_Init();
			HAL_Delay(1000);
			HAL_NVIC_SystemReset();
			break;
	case MCU_UUIDList:
			printf("MCU_UUIDList\r\n");
			Zigbee_Transport_SendCmd(MCU_UUIDList,1,&Event_appDate.status);
			break;
	case MCU_Clocking_In:
			printf("MCU_Clocking_In\r\n");
			ReadUUID(Event_appDate.BLEUUID_number++);
			BLE_Wakeup(&BLEATcmd);
			Zigbee_Transport_SendCmd(MCU_Query_UUID,32,&Event_appDate.UID[0]);
			break;
	case MCU_Log_Parameters:
			LOG_OutPut_Parameters();
			break;
	case MCU_Authentication://鉴权成功开门的
			Event_appDate.Authentication_Flag = 1;
			DataTransmition(MCU_UnLocking);
			break;
	case MCU_LinkKey://设置秘钥

			break;
	case MCU_Passthrough:

			break;
	default:
			break;
	}
	
	memset(Event_appDate.RtcTime,0,sizeof(Event_appDate.RtcTime));
	memset(Event_appDate.Txbuffer,0,sizeof(Event_appDate.Txbuffer));
	
}



///************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
