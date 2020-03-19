/**
  *********************************************************************************************************
  * @file    Record.c
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
#include "app.h"
#include "Record.h"

#include "libcrc.h"

/* Private typedef -----------------------------------------------------------*/
union Lock_Record Lockrecord;
union SaveParameterConfiguration SRPConfiguration;

SuperCard supercard;
NormalCard normalcard;
BlackListCard blacklistcard;

BufferCard SBuffercard;
BufferCard NBuffercard;
BufferCard BBuffercard;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/



/**********************************************************************************************************
 @Function			void WirteUUID(void)
 @Description		WirteUUID
 @Input					uint8_t* para
								uint8_t* data
 @Return				void
 @Other:
//记录的存储区
//0x6000-0x8000
**********************************************************************************************************/
void WirteUUID(uint8_t* para,uint8_t* data)
{
		Flash_NSS();
		FLASH_Init();

//		if(para[0] == 1)
//		{
//			ClearUUID();
//		}
	
		Event_appDate.BleUUID_address = BLEUUID_Address + (32 * para[0]);
			//判断是否写满
		if(Event_appDate.BleUUID_address>FLASH_Sector)
		{
			Event_appDate.BleUUID_address = BLEUUID_Address;
		}
//		printf("BleUUID_address %x",Event_appDate.BleUUID_address);
		
		SPI_Flash_Write(&para[0],BLEUUID_Time_Address,4);
		SPI_Flash_Write(data,Event_appDate.BleUUID_address,32);
		
		if(para[0] == para[1])
		{
			printf("pare %02x %02x %02x \r\n",para[4],para[5],para[6]);

			Event_appDate.BLEUUIDRECVEnd = 1;
			Event_appDate.BLEUUIDStart[0] = para[4];
			Event_appDate.BLEUUIDStart[1] = para[5];
			Event_appDate.BLEUUIDStart[2] = para[6];
			//Event_appDate.BLEUUID_Time = ((para[4]-Event_appDate.RtcTime[4])*3600) + ((para[5]-Event_appDate.RtcTime[5])*60) + para[6];
			Event_appDate.BLEUUID_Time = 0;
			Event_appDate.NTP_Time = 1;
			Event_appDate.BLEOSum = para[1];
			printf("Wirte Time %x BLEOSum %x\r\n",Event_appDate.BLEUUID_Time,Event_appDate.BLEOSum);
		}
		Flash_DeInit();
}

/**********************************************************************************************************
 @Function			void ReadUUID(void)
 @Description		ReadUUID
 @Input					uint8_t number
 @Return				void
 @Other:
**********************************************************************************************************/
void ReadUUID(uint8_t number)
{
		uint8_t time[4];
	
		Flash_NSS();
		FLASH_Init();
	
		Event_appDate.BleUUID_address = BLEUUID_Address + (32 * number);
		//判断是否写满
		if(Event_appDate.BleUUID_address>FLASH_Sector)
		{
			Event_appDate.BleUUID_address = BLEUUID_Address;
		}
	
		SPI_Flash_Read(time,BLEUUID_Time_Address,4);
		SPI_Flash_Read(Event_appDate.UID,Event_appDate.BleUUID_address,32);
		Event_appDate.BLEOpentime = time[2] << 8 | time[3];
		
		printf("number %x\r\n",number);
		printf("ReadUUID BLEOpentime %x",Event_appDate.BLEOpentime);
		Flash_DeInit();
}

/**********************************************************************************************************
 @Function			void ClearUUID(void)
 @Description		ClearUUID
 @Input					void
 @Return				void
 @Other:
**********************************************************************************************************/
void ClearUUID(void)
{
	Flash_NSS();
	FLASH_Init();
	
	for(int i = 0;i < Event_appDate.BLEUUID_number;i++)
	{
		memset(Event_appDate.UID,0,32);
		Event_appDate.BleUUID_address = BLEUUID_Address + (32 * i);
		SPI_Flash_Write(Event_appDate.UID,Event_appDate.BleUUID_address,32);
	}
	
	Flash_DeInit();
}

/**********************************************************************************************************
 @Function			void ClearFlash(void)
 @Description		ClearFlash
 @Input					void
 @Return				void
 @Other:
**********************************************************************************************************/
void ClearFlash(void)
{
	uint32_t WriteAddr;
	Flash_NSS();
	FLASH_Init();	
	uint8_t data[4096];
	memset(data,0,4096);

	for(int  i = 0;i<16;i++)
	{
		printf("i %x \r\n",i*4096);
		WriteAddr = i*4096;
		SPI_Flash_Write(data,WriteAddr,4096);
	}
	Flash_DeInit();
	while(1)
	{
			HAL_Delay(1000);
			Buzz_Rhythm(Swipe);
	}

}

/**********************************************************************************************************
 @Function			void ClearFlash(void)
 @Description		ClearFlash
 @Input					void
 @Return				void
 @Other:
**********************************************************************************************************/
void ClearCard(void)
{
	uint32_t WriteAddr;
	Flash_NSS();
	FLASH_Init();	
	uint8_t data[4096];
	memset(data,0,4096);

	for(int  i = 0;i<7;i++)
	{
		printf("i %x \r\n",i*4096);
		WriteAddr = i*4096;
		SPI_Flash_Write(data,WriteAddr,4096);
	}
	Flash_DeInit();
}

/**********************************************************************************************************
 @Function			void SystemInfo_Init(void)
 @Description		SystemInfo_Init
 @Input					void
 @Return				void
 @Other:
**********************************************************************************************************/
void SystemInfo_Init(void)
{
//	HAL_SPI_Init(&FLASHHandle);
	if(FLASH_OK!=FLASH_Get_Status()){
		return;
	}

	ReadConfiguration_Parameters();
	
	Flash_NSS();
	FLASH_Init();	
	ReadSuperCard(SRPConfiguration.sParameterConfiguration.SuperCard_Flag);
	ReadNormalCard(SRPConfiguration.sParameterConfiguration.NormalCard_Flag);
	ReadBlacklistCard(SRPConfiguration.sParameterConfiguration.BlackListCard_Flag);
	Flash_DeInit();
}


/**********************************************************************************************************
 @Function			void WirteConfiguration_Parameters(void)
 @Description		WirteConfiguration_Parameters
 @Input					void
 @Return				void
 @Other:
//配置参数的存储区
//0-0xfff
**********************************************************************************************************/
void WirteConfiguration_Parameters(void)
{
	Flash_NSS();
	FLASH_Init();
	
	SRPConfiguration.sParameterConfiguration.record_card_num[0] = ((Event_appDate.record_address & 0xFF000000) >> 24);
	SRPConfiguration.sParameterConfiguration.record_card_num[1] = ((Event_appDate.record_address & 0xFF0000) >> 16);
	SRPConfiguration.sParameterConfiguration.record_card_num[2] = ((Event_appDate.record_address & 0xFF00) >> 8);
	SRPConfiguration.sParameterConfiguration.record_card_num[3] = (Event_appDate.record_address & 0xFF);

	SRPConfiguration.sParameterConfiguration.Current_record_num = Event_appDate.report_record_number;
	SRPConfiguration.sParameterConfiguration.Transfer_record_Address[0] = ((Event_appDate.report_record_address & 0xFF000000) >> 24);
	SRPConfiguration.sParameterConfiguration.Transfer_record_Address[1] = ((Event_appDate.report_record_address & 0xFF0000) >> 16);
	SRPConfiguration.sParameterConfiguration.Transfer_record_Address[2] = ((Event_appDate.report_record_address & 0xFF00) >> 8);
	SRPConfiguration.sParameterConfiguration.Transfer_record_Address[3] = (Event_appDate.report_record_address & 0xFF);
	
	SPI_Flash_Write(SRPConfiguration.Configuration_array,Configuration_Address,100);

	Flash_DeInit();
}

/**********************************************************************************************************
 @Function			void LOG_OutPut_Parameters(void)
 @Description		LOG_OutPut_Parameters
 @Input					void
 @Return				void
 @Other:				输出所有参数配置
**********************************************************************************************************/
void LOG_OutPut_Parameters(void)
{
unsigned char DataStr[]=__DATE__;
unsigned char TimeStr[]=__TIME__;
	
	Buzz_Rhythm(LOG_Buzzer);
	printf("------------------------Version Meassage-----------------------------\r\n");
	printf("Software Version: %s \r\nDate of application:  %s %s\r\n",PACKAGE_VERSION,DataStr,TimeStr);
	printf("------------------------Address Table--------------------------------\r\n"); 
	printf("TimingLimitReadHTIME: %d\r\n",TimingLimitReadHTIME);
	printf("TimingLimitReadMTIME: %d\r\n",TimingLimitReadMTIME);
	printf("SWIPTIME: %d\r\n",SWIPTIME);
	printf("ADCTIME: %d\r\n",ADCTIME);
	printf("TranferRecordNO: %d\r\n",TranferRecordNO);
	printf("TranferRecord: %d\r\n",TranferRecord);
	printf("VOLTAGE: %d\r\n",VOLTAGE);
	printf("KEYTIMER: %d\r\n",KEYTIMER);
	printf("AlarmSystemTIME: %d\r\n",AlarmSystemTIME);
	printf("TestReportRecordingHTime: %d\r\n",TestReportRecordingHTime);
	printf("TestReportRecordingMTime: %d\r\n",TestReportRecordingMTime);
	printf("ReportingTimeStart: %d\r\n",ReportingTimeStart);
	printf("ReportingTimeStop: %d\r\n",ReportingTimeStop);
	printf("TranferRecordNO: %d\r\n",TranferRecordNO);
	printf("TranferRecord: %d\r\n",TranferRecord);
	printf("TranferRecordSum: %d\r\n",TranferRecordSum);
	
	printf("SuperCardn_Address: %x\r\n",SuperCardn_Address);
	printf("NormalCardn_Address: %x\r\n",NormalCardn_Address);
	printf("BlackListCardn_Address: %x\r\n",BlackListCardn_Address);
	printf("Record_Address: %x\r\n",Record_Address);
	printf("FLASH_Sector: %x\r\n",FLASH_Sector);
	printf("BleUUID_address %x\r\n",BLEUUID_Address);
	printf("BLEUUIDDELAY %x\r\n",BLEUUIDDELAY);
	
	printf("------------------------Configurable Parameter------------------------\r\n"); 
	printf("Flag S:%d N:%d B:%d\r\n",SRPConfiguration.sParameterConfiguration.SuperCard_Flag
																	,SRPConfiguration.sParameterConfiguration.NormalCard_Flag
																	,SRPConfiguration.sParameterConfiguration.BlackListCard_Flag);
	printf("record_address: %x \r\n",Event_appDate.record_address);
	printf("Restricted: %d\r\n",SRPConfiguration.sParameterConfiguration.Restricted_Condition);
	printf("Voltage: %d\r\n",SRPConfiguration.sParameterConfiguration.Voltage);
	
	printf("IWDG_Num: %d\r\n",SRPConfiguration.sParameterConfiguration.IWDG_Num);
	if(SRPConfiguration.sParameterConfiguration.IWDG_Num == 0xff)
	{
		SRPConfiguration.sParameterConfiguration.IWDG_Num = 0;
	}
	
	printf("SetOffTime: %d\r\n",Event_appDate.SetOffTime);
	
	printf("BLEUUID_number: %d\r\n",Event_appDate.BLEUUID_number);
	printf("BLEOpentime: %d\r\n",Event_appDate.BLEOpentime);
	
	printf("lastlog: %d\r\n",Event_appDate.lastlog);

	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;
	
	/* Get the RTC current Time */
	HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);
	printf("Time: 20%d : %d : %d : %d : %d : %d \r\n", sdatestructureget.Year,
																					sdatestructureget.Month,
																					sdatestructureget.Date,
																					stimestructureget.Hours,
																					stimestructureget.Minutes,
																					stimestructureget.Seconds);

	printf("LimitFlag %d \r\nLimit Time %d %d-%d %d\r\n"
																	,Event_appDate.Timing_LimitFlag
																	,SRPConfiguration.sParameterConfiguration.Restricted_Start_Time[0]
																	,SRPConfiguration.sParameterConfiguration.Restricted_Start_Time[1]
																	,SRPConfiguration.sParameterConfiguration.Restricted_Stop_Time[0]
																	,SRPConfiguration.sParameterConfiguration.Restricted_Stop_Time[1]);

	printf("supercard number:%d\r\n",supercard.cardnumber);
	printf("supercard.IdCard.cardId_array:");
	for(int i=0;i<400;i++)
	{
		printf(" %02x",supercard.Idcard.cardId_array[i]);
	}
	printf("\r\n");
	
	printf("\nnormalcard number:%d\r\n",normalcard.cardnumber);
	printf("normalcard.IdCard.cardId_array:");
	for(int i=0;i<400;i++)
	{
		printf(" %02x",normalcard.Idcard.cardId_array[i]);
	}
	printf("\r\n");
	
	printf("\nblacklistcard number:%d\r\n",blacklistcard.cardnumber);
	printf("blacklistcard.IdCard.cardId_array:");
	for(int i=0;i<400;i++)
	{
		printf(" %02x",blacklistcard.Idcard.cardId_array[i]);
	}
	printf("\r\n");
	
	printf("\nEvent_appDate.Voltage:\r\n");
	for(int i=0;i<sizeof(Event_appDate.Voltagedata);i++)
	{
		printf(" %02x",Event_appDate.Voltagedata[i]);
	}
	printf("\r\n");
	
}


/**********************************************************************************************************
 @Function			void ReadConfiguration_Parameters(void)
 @Description		ReadConfiguration_Parameters
 @Input					void
 @Return				void
 @Other:
**********************************************************************************************************/
void ReadConfiguration_Parameters(void)
{
	Flash_NSS();
	FLASH_Init();
	
	SPI_Flash_Read(SRPConfiguration.Configuration_array,Configuration_Address,100);
	
	Flash_DeInit();
//	for(int i = 0;i<4;i++)
//	{
//		printf("Read record_card_num %x \r\n",SRPConfiguration.sParameterConfiguration.record_card_num[i]);
//	}
	Event_appDate.AdminCard[0] = 0x5a;
	Event_appDate.AdminCard[1] = 0x95;
	Event_appDate.AdminCard[2] = 0x7a;
	Event_appDate.AdminCard[3] = 0x89;
	
	Event_appDate.record_address = 
	((SRPConfiguration.sParameterConfiguration.record_card_num[0] & 0xFFFFFF) << 24)|
	((SRPConfiguration.sParameterConfiguration.record_card_num[1] & 0xFFFF) << 16)|
	((SRPConfiguration.sParameterConfiguration.record_card_num[2] & 0xFF) << 8)|
	(SRPConfiguration.sParameterConfiguration.record_card_num[3]);
	
//	printf("Flag S:%x N:%x B:%x\r\n",SRPConfiguration.sParameterConfiguration.SuperCard_Flag
//																	,SRPConfiguration.sParameterConfiguration.NormalCard_Flag
//																	,SRPConfiguration.sParameterConfiguration.BlackListCard_Flag);
//	printf("record_address %x \r\n",Event_appDate.record_address);
//	printf("Restricted %x \r\n",SRPConfiguration.sParameterConfiguration.Restricted_Condition);
	
	Event_appDate.SetOffTime = SRPConfiguration.sParameterConfiguration.Automatic_Locking_Time[1]<<8|SRPConfiguration.sParameterConfiguration.Automatic_Locking_Time[0];
//	printf("SetOffTime %x \r\n",Event_appDate.SetOffTime);
//	printf("Voltage %x \r\n",SRPConfiguration.sParameterConfiguration.Voltage);	
	if(SRPConfiguration.sParameterConfiguration.Voltage != VOLTAGE)
	{
		Factory_Reset();
	}
}

/**********************************************************************************************************
 @Function			void Factory_Reset(void)//恢复出厂
 @Description		Factory_Reset
 @Input					void
 @Return				void
 @Other:
**********************************************************************************************************/
void Factory_Reset(void)
{
		ClearCard();
		SRPConfiguration.sParameterConfiguration.SuperCard_Flag = 0;
		SRPConfiguration.sParameterConfiguration.NormalCard_Flag = 0;
		SRPConfiguration.sParameterConfiguration.BlackListCard_Flag = 0;
		SRPConfiguration.sParameterConfiguration.Restricted_Condition = 0;
		SRPConfiguration.sParameterConfiguration.Voltage = VOLTAGE;
	
		SRPConfiguration.sParameterConfiguration.Automatic_Locking_Time[1] = 0x00;
		SRPConfiguration.sParameterConfiguration.Automatic_Locking_Time[0] = 0x05;
	
		SRPConfiguration.sParameterConfiguration.Restricted_Start_Time[0] = 0x00;
		SRPConfiguration.sParameterConfiguration.Restricted_Start_Time[1] = 0x00;
		SRPConfiguration.sParameterConfiguration.Restricted_Stop_Time[0] = 0x00;
		SRPConfiguration.sParameterConfiguration.Restricted_Stop_Time[1] = 0x00;
		Event_appDate.record_address = Record_Address;
		SRPConfiguration.sParameterConfiguration.Restricted_Condition = 0;
		printf("record_address %x \r\n",Event_appDate.record_address);
		printf("Voltage %x \r\n",SRPConfiguration.sParameterConfiguration.Voltage);	
		WirteConfiguration_Parameters();
	
	
		Flash_NSS();
		FLASH_Init();
		SBuffercard.cardnumber = 0;
		WirteSuperCard(SRPConfiguration.sParameterConfiguration.SuperCard_Flag);
	
		NBuffercard.cardnumber = 0;
		WirteNormalCard(SRPConfiguration.sParameterConfiguration.NormalCard_Flag);
	
		BBuffercard.cardnumber = 0;
		WirteBlacklistCard(SRPConfiguration.sParameterConfiguration.BlackListCard_Flag);
		
		memset(SBuffercard.Idcard.cardId_array,0,sizeof(SBuffercard.Idcard.cardId_array));
		SBuffercard.Idcard.cardId[0][0] = 0x1d;
		SBuffercard.Idcard.cardId[0][1] = 0x42;
		SBuffercard.Idcard.cardId[0][2] = 0xe0;
		SBuffercard.Idcard.cardId[0][3] = 0x8b;
		SBuffercard.Idcard.cardId[1][0] = 0xc2;
		SBuffercard.Idcard.cardId[1][1] = 0xc3;
		SBuffercard.Idcard.cardId[1][2] = 0xe4;
		SBuffercard.Idcard.cardId[1][3] = 0x8b;
		SBuffercard.Idcard.cardId[2][0] = 0xA1;
		SBuffercard.Idcard.cardId[2][1] = 0xEB;
		SBuffercard.Idcard.cardId[2][2] = 0xAF;
		SBuffercard.Idcard.cardId[2][3] = 0x04;
		SBuffercard.cardnumber = 3;

		WirteSuperCard(0);
		
		Flash_DeInit();
}

/**********************************************************************************************************
 @Function			void WirteSuperCard(void)
 @Description		WirteSuperCard
 @Input					uint8_t Flag
 @Return				void
 @Other:
//Supercard的存储区
//0x1000-0x1fff
**********************************************************************************************************/

void WirteSuperCard(uint8_t Flag)
{
	if(Flag)
	{
		SPI_Flash_Write(&SBuffercard.cardnumber,SuperCardn_Address,1);
		SPI_Flash_Write(SBuffercard.Idcard.cardId_array,SuperCardi_Address,1200);
	}else{
		SPI_Flash_Write(&SBuffercard.cardnumber,SuperCardn_TAddress,1);
		SPI_Flash_Write(SBuffercard.Idcard.cardId_array,SuperCardi_TAddress,1200);
	}
}
/**********************************************************************************************************
 @Function			void ReadSuperCard(void)
 @Description		ReadSuperCard
 @Input					uint8_t Flag
 @Return				void
 @Other:
**********************************************************************************************************/
void ReadSuperCard(uint8_t Flag)
{
	if(Flag)
	{
		SPI_Flash_Read(&supercard.cardnumber,SuperCardn_Address,1);
		SPI_Flash_Read(supercard.Idcard.cardId_array,SuperCardi_Address,1200);
	}else{
		SPI_Flash_Read(&supercard.cardnumber,SuperCardn_TAddress,1);
		SPI_Flash_Read(supercard.Idcard.cardId_array,SuperCardi_TAddress,1200);
	}

//	printf("supercard number:%x\r\n",supercard.cardnumber);

//	printf("supercard.IdCard.cardId_array:");
//	for(int i=0;i<400;i++)
//	{
//		printf(" %x",supercard.Idcard.cardId_array[i]);
//	}
}


/**********************************************************************************************************
 @Function			void WirteNormalCard(void)
 @Description		WirteNormalCard
 @Input					uint8_t Flag
 @Return				void
 @Other:
//Normalcard的存储区
//0x2000-0x2fff
**********************************************************************************************************/
void WirteNormalCard(uint8_t Flag)
{
//	printf("normalcard.cardnumber:%x\r\n",NBuffercard.cardnumber);

//	printf("normalcard.IdCard.cardId_array:");
//	for(int i=0;i<400;i++)
//	{
//		printf(" %x",NBuffercard.Idcard.cardId_array[i]);
//	}
	if(Flag)
	{
		SPI_Flash_Write(&NBuffercard.cardnumber,NormalCardn_Address,1);
		SPI_Flash_Write(NBuffercard.Idcard.cardId_array,NormalCardi_Address,1200);
	}else{
		SPI_Flash_Write(&NBuffercard.cardnumber,NormalCardn_TAddress,1);
		SPI_Flash_Write(NBuffercard.Idcard.cardId_array,NormalCardi_TAddress,1200);
	}
}

/**********************************************************************************************************
 @Function			void ReadNormalCard(void)
 @Description		ReadNormalCard
 @Input					uint8_t Flag
 @Return				void
 @Other:
**********************************************************************************************************/
void ReadNormalCard(uint8_t Flag)
{
	if(Flag)
	{
		SPI_Flash_Read(&normalcard.cardnumber,NormalCardn_Address,1);
		SPI_Flash_Read(normalcard.Idcard.cardId_array,NormalCardi_Address,1200);
	}else{
		SPI_Flash_Read(&normalcard.cardnumber,NormalCardn_TAddress,1);
		SPI_Flash_Read(normalcard.Idcard.cardId_array,NormalCardi_TAddress,1200);
	}
		
//	printf("normalcard number:%x\r\n",normalcard.cardnumber);

//	printf("normalcard.IdCard.cardId_array:");
//	for(int i=0;i<400;i++)
//	{
//		printf(" %x",normalcard.Idcard.cardId_array[i]);
//	}
}

/**********************************************************************************************************
 @Function			void ReadBlacklistCard(void)
 @Description		ReadBlacklistCard
 @Input					uint8_t Flag
 @Return				void
 @Other:
//黑名单的存储区
//0x3000-0x3fff
**********************************************************************************************************/
void WirteBlacklistCard(uint8_t Flag)
{
	if(Flag)
	{
		SPI_Flash_Write(&BBuffercard.cardnumber,BlackListCardn_Address,1);
		SPI_Flash_Write(BBuffercard.Idcard.cardId_array,BlackListCardi_Address,1200);
	}else{
		SPI_Flash_Write(&BBuffercard.cardnumber,BlackListCardn_TAddress,1);
		SPI_Flash_Write(BBuffercard.Idcard.cardId_array,BlackListCardi_TAddress,1200);
	}
}

/**********************************************************************************************************
 @Function			void ReadBlacklistCard(void)
 @Description		ReadBlacklistCard
 @Input					uint8_t Flag
 @Return				void
 @Other:
**********************************************************************************************************/
void ReadBlacklistCard(uint8_t Flag)
{
	if(Flag)
	{
		SPI_Flash_Read(&blacklistcard.cardnumber,BlackListCardn_Address,1);
		SPI_Flash_Read(blacklistcard.Idcard.cardId_array,BlackListCardi_Address,1200);
	}else{
		SPI_Flash_Read(&blacklistcard.cardnumber,BlackListCardn_TAddress,1);
		SPI_Flash_Read(blacklistcard.Idcard.cardId_array,BlackListCardi_TAddress,1200);
	}
//	printf("blacklistcard number:%x\r\n",blacklistcard.cardnumber);
//	
//	printf("blacklistcard.IdCard.cardId_array:");
//	for(int i=0;i<400;i++)
//	{
//		printf(" %x",blacklistcard.Idcard.cardId_array[i]);
//	}
}

/**********************************************************************************************************
 @Function			void Issued_Card(void)
 @Description		Issued_Card
 @Input					uint8_t type
								uint8_t* date
								uint8_t number
 @Return				void
 @Other:
**********************************************************************************************************/
void Issued_Card(uint8_t type,uint8_t* date,uint8_t number)
{
	Flash_NSS();
	FLASH_Init();
//	printf("type:%02x",type);
		if(type == 2)
		{
			memcpy(&SBuffercard.Idcard.cardId[SBuffercard.cardnumber][0],date,number*4);
			SBuffercard.cardnumber += number;
//			printf("SBuffercard %x \r\n",SBuffercard.cardnumber);
//			printf("SBuffercard.IdCard.cardId_array:");
//			for(int i=0;i<number*4;i++)
//			{
//				printf(" %x",NBuffercard.Idcard.cardId_array[i]);
//			}
			WirteSuperCard(!SRPConfiguration.sParameterConfiguration.SuperCard_Flag);
		}
		else if(type == 1)
		{
			memcpy(&NBuffercard.Idcard.cardId[NBuffercard.cardnumber][0],date,number*4);
			NBuffercard.cardnumber += number;
//			printf("NBuffercard %x \r\n",NBuffercard.cardnumber);
//			printf("NBuffercard.IdCard.cardId_array:");
//			for(int i=0;i<number*4;i++)
//			{
//				printf(" %x",NBuffercard.Idcard.cardId_array[i]);
//			}
			WirteNormalCard(!SRPConfiguration.sParameterConfiguration.NormalCard_Flag);

		}else if(type == 0)
		{
			memcpy(&BBuffercard.Idcard.cardId[BBuffercard.cardnumber][0],date,number*4);
			BBuffercard.cardnumber += number;
//			printf("BBuffercard %x \r\n",BBuffercard.cardnumber);
//			printf("BBuffercard.IdCard.cardId_array:");
//			for(int i=0;i<number*4;i++)
//			{
//				printf(" %x",BBuffercard.Idcard.cardId_array[i]);
//			}
			WirteBlacklistCard(!SRPConfiguration.sParameterConfiguration.BlackListCard_Flag);
		}
		Flash_DeInit();
}


/**********************************************************************************************************
 @Function			void Change_Address_Table(void)
 @Description		Change_Address_Table
 @Input					uint8_t type
 @Return				void
 @Other:
**********************************************************************************************************/
void Change_Address_Table(uint8_t type,uint8_t* u8CRC)
{
	Flash_NSS();
	FLASH_Init();
	
	uint16_t u16CRC = 0;
	uint8_t u8CRCdata[2];
	memcpy(u8CRCdata,u8CRC,2);
	u16CRC = u8CRCdata[1]<<8 | u8CRCdata[0];
//		printf("type:%d u8CRCdata %x%x \r\n",type,u8CRCdata[1],u8CRCdata[0]);
//		printf("u16CRC:%x \r\n",u16CRC);
		if(type == 2)
		{
//			printf("SBuffercard crc_16:%04x\r\n",crc_16(SBuffercard.Idcard.cardId_array,SBuffercard.cardnumber*4));
			//校验下发数据是否正确
			if(u16CRC == crc_16(SBuffercard.Idcard.cardId_array,SBuffercard.cardnumber*4))
			{
				SRPConfiguration.sParameterConfiguration.SuperCard_Flag = !SRPConfiguration.sParameterConfiguration.SuperCard_Flag;
				Event_appDate.ChangeAddressFlag = 0x01;
			}else{
				//校验是否已经切换数据
				if(u16CRC == crc_16(supercard.Idcard.cardId_array,supercard.cardnumber*4))
				{
					Event_appDate.ChangeAddressFlag = 0x01;
				}else{
					Event_appDate.ChangeAddressFlag = 0x00;
				}
			}

			SBuffercard.cardnumber = 0;
			memset(&SBuffercard.Idcard.cardId_array,0,sizeof(SBuffercard.Idcard.cardId_array));
			if(Event_appDate.ChangeAddressFlag)
			{
				//更新卡号，重新读新地址的数据
				ReadSuperCard(SRPConfiguration.sParameterConfiguration.SuperCard_Flag);
			}
		}
		else if(type == 1)
		{
//			printf("NBuffercard crc_16:%04x\r\n",crc_16(NBuffercard.Idcard.cardId_array,NBuffercard.cardnumber*4));
			//校验下发数据是否正确
			if(u16CRC == crc_16(NBuffercard.Idcard.cardId_array,NBuffercard.cardnumber*4))
			{
				SRPConfiguration.sParameterConfiguration.NormalCard_Flag = !SRPConfiguration.sParameterConfiguration.NormalCard_Flag;
				Event_appDate.ChangeAddressFlag = 0x01;
			}else{
				//校验是否已经切换数据
				if(u16CRC == crc_16(normalcard.Idcard.cardId_array,normalcard.cardnumber*4))
				{
					Event_appDate.ChangeAddressFlag = 0x01;
				}else{
					Event_appDate.ChangeAddressFlag = 0x00;
				}
			}
			
			NBuffercard.cardnumber = 0;
			memset(&NBuffercard.Idcard.cardId_array,0,sizeof(NBuffercard.Idcard.cardId_array));
			if(Event_appDate.ChangeAddressFlag)
			{
				//更新卡号，重新读新地址的数据
				ReadNormalCard(SRPConfiguration.sParameterConfiguration.NormalCard_Flag);
			}
		}
		else if(type == 0)
		{
//			printf("BBuffercard crc_16:%04x\r\n",crc_16(BBuffercard.Idcard.cardId_array,BBuffercard.cardnumber*4));
			//校验下发数据是否正确
			if(u16CRC == crc_16(BBuffercard.Idcard.cardId_array,BBuffercard.cardnumber*4))
			{
				SRPConfiguration.sParameterConfiguration.BlackListCard_Flag = !SRPConfiguration.sParameterConfiguration.BlackListCard_Flag;
				Event_appDate.ChangeAddressFlag = 0x01;
			}else{
				//校验是否已经切换数据
				if(u16CRC == crc_16(blacklistcard.Idcard.cardId_array,blacklistcard.cardnumber*4))
				{
					Event_appDate.ChangeAddressFlag = 0x01;
				}else{
					Event_appDate.ChangeAddressFlag = 0x00;
				}
			}
			
			BBuffercard.cardnumber = 0;
			memset(&BBuffercard.Idcard.cardId_array,0,sizeof(BBuffercard.Idcard.cardId_array));
			if(Event_appDate.ChangeAddressFlag)
			{
				//更新卡号，重新读新地址的数据
				ReadBlacklistCard(SRPConfiguration.sParameterConfiguration.BlackListCard_Flag);
			}
		}
		printf("ChangeAddressFlag:%x \r\n",Event_appDate.ChangeAddressFlag);
		Flash_DeInit();
		
		if(Event_appDate.ChangeAddressFlag)
		{
			WirteConfiguration_Parameters();
//			ReadFlash();
		}
		DataTransmition(MCU_ChangeAddress);
}

/**********************************************************************************************************
 @Function			void GetRecordData(void)
 @Description		GetRecordData
 @Input					void
 @Return				void
 @Other:
**********************************************************************************************************/
void GetRecordData(void)
{
	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;
	
	/* Get the RTC current Time */
	HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);

	Lockrecord.lockactionevent.Hours = stimestructureget.Hours; 
	Lockrecord.lockactionevent.Minutes = stimestructureget.Minutes;
	Lockrecord.lockactionevent.Seconds = stimestructureget.Seconds;
	Lockrecord.lockactionevent.Month = sdatestructureget.Month;
	Lockrecord.lockactionevent.Date = sdatestructureget.Date;
	Lockrecord.lockactionevent.Year[0] = 0xFF & ((2000 + sdatestructureget.Year)>>8);
	Lockrecord.lockactionevent.Year[1] = 0xFF & (2000 + sdatestructureget.Year);
	memcpy(&Lockrecord.lockactionevent.CardId[0], Event_appDate.ucCardId,4);
	Lockrecord.lockactionevent.App_or_Card = Event_appDate.Operation_Sign;

}

/**********************************************************************************************************
 @Function			void WirteOneRecord(void)
 @Description		WirteOneRecord
 @Input					void
 @Return				void
 @Other:
//记录的存储区
//0x4000-0x7f,ffff
**********************************************************************************************************/

void WirteOneRecord(void)
{
		Flash_NSS();
		FLASH_Init();
	
//		for(int i=0;i<12;i++)
//		{
//			printf(" %x",Lockrecord.cardId_array[i]);
//		}
//		printf("address %x",Event_appDate.record_address);
		
		SPI_Flash_Write(Lockrecord.cardId_array,Event_appDate.record_address,12);//改成每次添加一条记录，依次累加
		
		memset(Lockrecord.cardId_array,0,12);
		
//		for(int i=0;i<12;i++)
//		{
//			printf(" %x",Lockrecord.cardId_array[i]);
//		}
//		
//		SPI_Flash_Read(Lockrecord.cardId_array,time_event_appDate.record_address,12);
//		
//		printf("LockRecord.cardId_array:");
//		for(int i=0;i<12;i++)
//		{
//			printf(" %x",Lockrecord.cardId_array[i]);
//		}
//		
		Event_appDate.record_address +=12;
		//判断是否写满
		if(Event_appDate.record_address>FLASH_Sector)
		{
			Event_appDate.record_address = Record_Address;
		}
		
//		printf("record_address %x \r\n",Event_appDate.record_address);
		SRPConfiguration.sParameterConfiguration.record_card_num[0] = ((Event_appDate.record_address & 0xFF000000) >> 24);
		SRPConfiguration.sParameterConfiguration.record_card_num[1] = ((Event_appDate.record_address & 0xFF0000) >> 16);
		SRPConfiguration.sParameterConfiguration.record_card_num[2] = ((Event_appDate.record_address & 0xFF00) >> 8);
		SRPConfiguration.sParameterConfiguration.record_card_num[3] = ( Event_appDate.record_address & 0xFF);
		
		Flash_DeInit();
		
		WirteConfiguration_Parameters();
		memset(Event_appDate.ucCardId,0,4);

}

void Report_Record(void)
{
	uint16_t res = 0;
	Get_RTC(Event_appDate.RtcTime);
	res = Event_appDate.RtcTime[4] * 60 + Event_appDate.RtcTime[5];
	if((res > ReportingTimeStart)&&(res < ReportingTimeStop))//2点到4点
	{
		DataTransmition(MCU_Query_Lock_Record);
		if(Event_appDate.report_record_Flag)
		{
			Event_appDate.report_record_Time = TestReportRecordingMTime;
		}else{
			Event_appDate.report_record_Time = TestReportRecordingHTime;
		}
	}
}


/**********************************************************************************************************
 @Function			void Terminal_Record(void)读取记录上报
 @Description		Terminal_Record
 @Input					void
 @Return				void
 @Other:
**********************************************************************************************************/
void Terminal_Record(void)
{
		Flash_NSS();
		FLASH_Init();
	
		if((!Event_appDate.report_record_no)&&(!Event_appDate.report_record_Flag))
		{
			Event_appDate.report_record_address = 0;
			Event_appDate.report_record_address = Event_appDate.record_address - 1200;
			
			if(Event_appDate.report_record_address <= Record_Address)
			{
				Event_appDate.report_record_address = Record_Address;
			}
			WirteConfiguration_Parameters();
			Event_appDate.report_record_no = 0;
			Event_appDate.report_record_Flag = 1;
		}
		
		if((Event_appDate.report_record_no * TranferRecordNO) < TranferRecord)
		{
			Event_appDate.record_Address_value = Event_appDate.report_record_address + (Event_appDate.report_record_no * TranferRecord);
			printf("record_address %x record_number %x \r\n",Event_appDate.record_Address_value,Event_appDate.report_record_no);
			SPI_Flash_Read(&Event_appDate.report_record_data[3], Event_appDate.record_Address_value,TranferRecord);
			
			Event_appDate.report_record_data[0] = Event_appDate.report_record_no + 1;
			Event_appDate.report_record_data[1] = 12;//12个包(100/TranferRecordNO);
			Event_appDate.report_record_data[2] = TranferRecordNO;
			
			Zigbee_Transport_SendCmd(MCU_Query_Lock_Record,TranferRecordSum,&Event_appDate.report_record_data[0]);
			if(Event_appDate.report_record_Flag)
			{
				Event_appDate.report_record_no++;
			}
		}
		else{
			if(Event_appDate.report_record_Flag)
			{
			Event_appDate.report_record_Flag = 0;
			Zigbee_Transport_SendCmd(MCU_Rerport_Record_Number,1,&Event_appDate.report_record_no);//上报传输满一百条
			}
		}
		
//		if(!(Event_appDate.report_record_number%10))
//		{
//			WirteConfiguration_Parameters();
//		}
		Flash_DeInit();
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
