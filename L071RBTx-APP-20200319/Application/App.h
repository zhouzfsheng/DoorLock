/**
******************************************************************************
* @file    app.h
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
#ifndef __APP_H
#define __APP_H

/* Includes ------------------------------------------------------------------*/
#include "Common.h"

#include "Buzzer.h"
#include "Record.h"
#include "Zigbeeconfig.h"
#include "Bleconfig.h"
#include "FIFOmessage.h"

#define PACKAGE_VERSION "0.0.3"
#define AppYear 				0x19	
#define AppMonth 				RTC_MONTH_AUGUST	
#define AppDate 				0x30	

#define TestReportRecordingHTime 								1801//单位：s（半个小时）
#define TestReportRecordingMTime 								37//单位：s（分钟）

#define NTPTIME														60

#define ClockingInTIME 										0x93A80//（604800）单位：s

#define TimingLimitReadHTIME 								3601//单位：s
#define TimingLimitReadMTIME 								63//单位：s

#define AlarmSystemTIME 								5//单位：s

#define ReportingTimeStart					120//凌晨两点
#define ReportingTimeStop						300//凌晨5点

#define SWIPTIME 								33//单位：s
#define ADCTIME 								86401//单位：s
#define TranferRecordNO 				4//单位：条
#define TranferRecord 					TranferRecordNO*12
#define TranferRecordSum 				TranferRecord+3

#define VOLTAGE 								125//低电压的

#define KEYTIMER 								120//按键计数限时十分钟，按键计数超过十分钟就清空

#define BLEUUIDDELAY						5 //收完数据延时启动时间

#define FM1755DebugInfo 				0//1755刷卡调试日志输出，1-》开 0-》关

#define FM1755DebugTest					0//供调试1755时使用，1-》开 0-》关


/*
 * 结构体定义
 */

extern BLE_ATCmdTypeDef BLEATcmd;

union KYZH_Head
{
  struct{
    uint8_t  u8ASeq;
    uint8_t  u8FSeq;
    uint8_t  u8TaskTypes;
    uint8_t  u8Size;
    uint8_t  u8CRC;
  }kyzh_head;
  uint8_t array[5];
};

/*Lock action event*/
typedef struct
{
  uint8_t Year[2];
  uint8_t Month;
  uint8_t Date;
  uint8_t Hours;
  uint8_t Minutes;
  uint8_t Seconds;
}RTC_event;

union RTCParameterConfiguration
{
  RTC_event rtc_event;
  uint8_t array[7];
};


extern union RTCParameterConfiguration RTCPConfiguration;


/*Lock action event*/
typedef struct
{
  uint8_t Year[2];
  uint8_t Month;
  uint8_t Date;
  uint8_t Hours;
  uint8_t Minutes;
  uint8_t Seconds;
	uint8_t App_or_Card;//十位是APP->1或者卡->0，个位是开->1或者关->0,例如: 0x11-》就是App开门
  uint8_t CardId[4];

}Lock_action_event;

union Lock_Record
{
  Lock_action_event lockactionevent;
  uint8_t cardId_array[12];
};

extern union Lock_Record Lockrecord;

typedef enum
{
//为了避开K（0x48）Y（0x59）不使用0x40-0x5f
    MCU_Device_Self_Checking = 0x60,						//设备自检
    MCU_Abnormal_Lock_Alarm,								//门锁异常
    MCU_Low_Power_Alarm,									//电量低报警
    MCU_Electricity_Query,									//电量查询
    MCU_Parameter_Configuration,							//门禁配置					（自动上锁时间本地存储，限时开门逻辑在zigbee实现）
    MCU_Time_Limit_Set,										//门禁限时设置					（只设置标志，主逻辑在zigbee实现）
    MCU_Query_Lock_Record,									//查询操作记录					（zigbee主动查询日志上报）
		MCU_Rerport_Record_Number,								//上报记录数目
    MCU_Restricted_Event,									//限制开门					（只设置标志，主逻辑在zigbee实现）
    MCU_Issued_Door_Card,									//下发门卡事件					（平台设置开门权限）（普通卡）
    MCU_Get_RTC_Event,										//获取系统时间事件				（zigbee定时获取RTC）
    MCU_Set_RTC_Event,										//设置系统时间事件				（zigbee收到时间下发设置）
    MCU_Online_UnLock_Event,       				//接受到开锁命令回复事件
    MCU_Swipe_Events,										//刷卡事件					（唤醒zigbee实现延迟关门并上报记录（只要门锁操作就上报））
		MCU_UnLocking,											//开锁事件					（zigbee发下命令开门）
    MCU_Locking,											//关锁事件
    MCU_No_Card,											//查询无该卡号
    MCU_Not_Exist_Card,										//不存在卡
	
		MCU_NormalcardEvent,
		MCU_SupercardEvent,
    MCU_BlacklistEvent,										//黑名单

    MCU_Test_Interface,										//测试接口
    MCU_RstMCU,												//芯片重启
    MCU_Equipment_lock_or_unlock,									//锁定解锁
    MCU_Open_Door_Event,
    MCU_Back_Locking,
    MCU_Back_Unlocking,
    MCU_BLE_Open,
    MCU_BLE_Close,
    MCU_Query_UUID,
		MCU_ChangeAddress,									//切换卡库
		MCU_Key,														//钥匙开门
		
		MCU_Front_Locking,
		MCU_Behind_Locking,
    MCU_software_version,
    MCU_hardware_version,
		
    MCU_RstZigBee,												//重启zigbee
		
		MCU_Door_Event,												//三角舌数据上报
		
		MCU_AbnormalSwipe, 										//不停重复刷卡，直接把最后一张卡上报
		
		MCU_NetworkState,
		
		MCU_Ready,
		
		MCU_FactoryReset_Event,						//重置（回复出厂）
		
		MCU_UUIDList,
		
		MCU_Clocking_In,//考勤
		
		MCU_Log_Parameters,//输出参数配置
		
		MCU_Authentication,//鉴权回复
		
		MCU_LinkKey,//设置秘钥
		
		MCU_Passthrough//透传数据
		
}TaskTypes;


//动态数据
typedef struct
{   

    uint32_t                       SysTime;//0xffffffff

    uint16_t                       SetOffTime;
	
		uint16_t											 AutoClosingTime;

    uint8_t                        Operation_Sign;//APP or Card
  
    uint8_t                        DoorFlag;

    uint8_t                        CheckLockStatus;

    uint8_t                        BackLocking[2];

    uint8_t                        ucCardId[4];

    uint8_t                        VoltageNo;
    uint8_t                        Voltagedata[3];//电压
    uint16_t                       VoltageAverage;

    uint8_t                        Limit_Door_Flag;
  
    uint8_t                        lastlog;
  
    uint8_t                        currentlog;
    
    uint8_t                        Irq_Signal;
    
    uint8_t                        Operational_events;
    
    uint32_t                       record_address;
		
    uint32_t                       report_record_address;
		
    uint32_t                       record_Address_value;
		
		uint8_t                        report_record_number;
		
		uint8_t                        report_record_Flag;
		
		uint8_t                        report_record_no;
		
		uint16_t                       report_record_Time;
		
		uint8_t                        report_record_data[TranferRecord];
		
		uint8_t												 UID[32];
    
		uint8_t 											 status;
		
		uint8_t 											 Txbuffer[100];
		
    uint8_t                        NetworkState;
    uint8_t                        NetRstNo;
		uint16_t                       NetRstTime;
		
    uint16_t                       BLEOpentime;
		
    uint8_t                        BLEOSum;
		
    uint32_t                       BLERunTime;
		
		uint8_t												 FM17xx_Trigger_Number;
		
		uint8_t											 	 Self_check_result;
		
		uint16_t 											 RSTMCU_PreKeyTick;	//记录按下的Tick时间
		
		uint16_t 											 RSTMCU_KeyTick;	//记录按下->释放的时间长度
		
		uint16_t 											 RSTZB_PreKeyTick;	//记录按下的Tick时间
		
		uint16_t 											 RSTZB_KeyTick;	//记录按下->释放的时间长度
		
		uint8_t												 FactoryKeyTick;
		
		uint8_t												 SwipCardNumber;//出现连续刷无效卡就报警
		
		uint8_t												 SwipCardTime;//出现连续刷无效卡就报警
		
		uint8_t												 SwipCardNumberOld;//出现连续刷无效卡就报警
		uint8_t												 SwipCardID[10][4];//出现连续刷无效卡就报警
		
		uint8_t												 StopSwipEvent;//停止响应刷卡事件等1分钟之后再响应
		
		uint8_t												 RtcTime[7];
		
		union Lock_Record							 OpenReCord;
		
		ITStatus											 Uart1Ready;
		
		uint16_t											 Uart1length;
		
		uint16_t											 TimeOut;
		
		uint8_t												 ChangeAddressFlag;
		
		uint32_t                       BleUUID_address;
		
		uint8_t                        BLEUUIDFlag;
		
		uint8_t                        BLEUUID_number;
		
		uint16_t                       BLEUUID_Time;//接收完成蓝牙列表后需要延时的时间
		
		uint16_t                       BLEUUIDRECVEnd;//考勤列表接收完成的标志
		
		uint8_t                        BLEUUIDStart[3];
		
		uint8_t                        RTC_Flag;
		uint8_t                        NTP_Flag;
		uint8_t                        NTP_Time;	
		
		uint8_t                        NTP_No;
		
		uint8_t                        NTP_Type;
		
		uint32_t                       NTP_value[6];
		
		uint8_t                        RTCcnt;
		
		uint8_t												 Step;
		uint8_t												 Timing_LimitFlag;
		
		uint8_t                        FrontLockTime;
		uint8_t                        RearLockTime;
		
		uint8_t												 SwipNumber;
		uint8_t												 OldSwipNumber;
		uint8_t												 SwipCnt;
		
		uint8_t												 AdminCard[4];
		
		uint8_t												 Authentication_Flag;
		
		uint8_t												 MCU_RSTStatus;
		
		uint8_t												 ZBParameterSet[4];
}Event_AppData;

extern Event_AppData         Event_appDate;

//存储
typedef struct
{
    /*获取源：APP*/
    uint8_t staus;

    uint8_t record_card_num[4];              	//存储记录的地址:0-700000条w25q80
    uint8_t IWDG_Num;                   			//看门狗重启次数

//    uint8_t detection;
//        uint8_t serial_port_sign;
//    uint8_t ucKeyCap_time;
		uint8_t  Voltage;//电压
    /*获取源：平台配置*/

    uint8_t Automatic_Locking_Time[2];         //自动上锁时间

    uint8_t Restricted_Start_Time[2];          //限制开门开始时间
	  uint8_t Restricted_Stop_Time[2];           //限制开门停止时间
	
    uint8_t Restricted_Condition;           	//限制开门时间标记
	
		uint8_t SuperCard_Flag;
		uint8_t NormalCard_Flag;
		uint8_t BlackListCard_Flag;
		
		uint8_t Current_record_num;              	//上传第几条日志记录
		uint8_t Transfer_record_Address[4];              //上传日志记录的地址

}ParameterConfiguration;

union SaveParameterConfiguration
{
  ParameterConfiguration sParameterConfiguration;
  uint8_t Configuration_array[100];
};

extern union SaveParameterConfiguration SRPConfiguration;


//*/
///*Buzzer parameters*/
//typedef struct
//{
//  uint8_t tweet;
//  uint8_t tweet1;
//  uint8_t tweet2;
//  uint8_t tweet3;
//  uint8_t tweet4;
//  uint8_t tweet5;
//}Buzzer_parameters;





union IDCard
{
    uint8_t cardId[300][4];
    uint8_t cardId_array[1200];
};

//普通卡（不能开反锁白名单）
typedef struct
{
    uint8_t cardnumber;              //卡数目
    union IDCard Idcard;        //卡号存储区
}NormalCard;

//黑名单不开门
typedef struct
{
    uint8_t cardnumber;              //卡数目
    union IDCard Idcard;        //卡号存储区
}BlackListCard;

//超级权限卡（开反锁的白名单）
typedef struct
{
    uint8_t cardnumber;              //卡数目
    union IDCard Idcard;        //卡号存储区
}SuperCard;

//（名单缓存）
typedef struct
{
    uint8_t cardnumber;              //卡数目
    union IDCard Idcard;        //卡号存储区
}BufferCard;

extern SuperCard supercard;
extern NormalCard normalcard;
extern BlackListCard blacklistcard;

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void FM1755_void(uint8_t flag);
void  Front_Handle_Event(void);
void Issued_Card(uint8_t type,uint8_t* date,uint8_t number);

void DataTransmition(unsigned char number);
void Swipe_Event(void);

void NTPTIME_Funtion(void);

void RTCConfig(RTC_event* rtconfig);
void Get_RTC(uint8_t* rtconfig);


void MCU_GetUID(void);
void Peripherals(void);
void Test_Function(void);
void Lock_Event(uint8_t flag);
void Appication_Funtion(void);
void LowPowerMode(void);
void ReadIO(void);

time_t RTC_TimeToStamp(uint8_t year, uint8_t month, uint8_t date, uint8_t hour, uint8_t min, uint8_t sec);
void  NTP_Shop_Funtion(void);
void Timing_limit_Function(void);
#endif /* __APP_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



