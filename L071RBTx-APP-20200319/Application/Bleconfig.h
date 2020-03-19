/**
******************************************************************************
* @file    Bleconfig.h
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
#ifndef __BLE_CONFIG_H
#define __BLE_CONFIG_H

#include "Common.h"

//#define BLE_RST_IO	                       	GPIO_PIN_1
//#define BLE_PWRC	                       		GPIO_PIN_0
//#define BLE_AT_ENABLE	                     	GPIO_PIN_11
//#define BLE_GPIO_PORT                   	 	GPIOA
//#define BLE_GPIO_CLK_ENABLE()           		__HAL_RCC_GPIOA_CLK_ENABLE()  
//#define BLE_GPIO_CLK_DISABLE()          	 	__HAL_RCC_GPIOA_CLK_DISABLE()

#define BLE_SERIAL_TIMEOUT_MSEC			100												//串口连续接收数据包超时时间MS
#define BLE_COMMAND_TIMEOUT_MSEC			8000												//指令发送等待响应包超时时间MS
#define BLE_COMMAND_FAILURE_CNT			3												//指令执行错误尝试次数

#define BLE_COMMAND_TIMEOUT_AUTO			0
#define BLE_COMMAND_TIMEOUT_MANUAL		1
#define BLE_COMMAND_TIMEOUT_TYPE			BLE_COMMAND_TIMEOUT_AUTO

/* BLE 协议栈开辟缓存大小 */
#define BLE_BUFFER_SIZE						128
#define BLE_ATBUFFER_SIZE					128
#define BLE_DATASTACK_SIZE				256

typedef enum 
{
    BLE_RST = 0,                        //复位 M/S －  
    BLE_BOUD,                           //串口波特率设置 M/S － 115200    
    BLE_HOSTEN,                         //主从设置 M/S － 从机    
    BLE_HOST,                           //读取主机状态 M －   
    BLE_DISC,                           //断开连接 M/S －   
    BLE_ADVEN,                          //打开广播 S － 打开  
    BLE_ADVIN,                          //广播间隔 S － 100ms   
    BLE_NEIN,                           //连接间隔 S － 10ms  
    BLE_POWR,                           //发射功率 S － 0db
    BLE_NAME,                           //广播名 S － JDY-08
    BLE_MAC,                            //读 MAC 地址 M/S －
    BLE_STRUUID,                        //设置 iBeacon UUID(字符串类型 UUID)
    BLE_HEXUUID,                        //设置 iBeacon UUID(十六进制类型 UUID)
    BLE_MAJOR,                          //设置 iBeacon Major
    BLE_MINOR,                          //设置 iBeacon Minor
    BLE_VER,                            //读取版本号 M/S － JDY-08-2.1
    BLE_VID,                            //厂家识别码
    BLE_TEMP,                           //温度值设置 S iBeacon
    BLE_HUMID,                          //温度值设置 S iBeacon
    BLE_ISCEN,                          //设置是否打开密码连接 S － 关闭
    BLE_PASS,                           //连接密码 S － 123456
    BLE_SVRUUID,                        //更改服务 UUID M/S － FFE0
    BLE_CHRUUID,                        //更改特征 UUID M/S － FFE1
    BLE_SCAN,                           //主机扫描从机 M 主机透传
    BLE_RSLV,                           //读取主机扫描到的从机 MAC M 主机透传
    BLE_CONNET,                         //连接扫描到从机的 MAC M 主机透传
    BLE_BAND,                           //绑定从机 MAC M －
    BLE_GETDCD,                         //读取主机扫描到的从机数量 M －
    BLE_GETSTAT,                        //查找模块的工作状态 M/S －
    BLE_PWMFRE,                         //设置 PWM 频率 M/S － 1000HZ
    BLE_PWMOPEN,                        //打开 PWM M/S － 关闭
    BLE_PWM1PUS,                        //设置 PWM1 的脉宽 M/S － 50%
    BLE_PWM2PUS,                        //设置 PWM2 的脉宽 M/S － 50%
    BLE_PWM3PUS,                        //设置 PWM3 的脉宽 M/S － 50%
    BLE_PWM4PUS,                        //设置 PWM4 的脉宽 M/S － 50%
    BLE_WXSVR,                          //微信 H5 与服务器通信设置 S 微信 H5
    BLE_RTCFLSH,                        //RTC 刷新时间（秒） M/S －
    BLE_RTCDATE,                        //RTC 时间读写 M/S －
    BLE_RTCOPEN,                        //RTC 开关 M/S －
    BLE_RESTORE,                        //恢复出厂配置 M/S －
    BLE_STARTEN,                        //开机是否唤醒 M/S 唤醒模式
    BLE_SLEEP,                          //进入睡眠模式 M/S
    BLE_KBYTE,                          //传输速度设置 M/S 1K bytes/s
    BLE_REVERSE,                        //P1_6 电平与唤醒 MCU 延时 M/S 1
    BLE_CLSS,                           //设置设备类型 S 透传 A0
    BLE_RTCALAM,                        //RTC 定时值读写 M/S
    BLE_ALAMEN,                         //RTC 定时开关 M/S 关
    BLE_RSSI,                           //RSSI 值 S
    BLE_PIO,                            //指令控制 IO M/S
    BLE_PARITY,                         //串口奇偶校验位设置 无校验位
    BLE_WXINEN,                         //微信自动、手动测试模式选择 S 手动模式
}BLE_Types;


/* BLE 指令发送等待响应时间 */
#define BLE_COMMAND_NCSEARFCN_MSEC		600
#define BLE_COMMAND_CGMI_MSEC			600
#define BLE_COMMAND_CGMM_MSEC			600
#define BLE_COMMAND_CGMR_MSEC			600
#define BLE_COMMAND_CGSN_MSEC			600
#define BLE_COMMAND_CSQ_MSEC			600
#define BLE_COMMAND_NUESTATS_MSEC		600
#define BLE_COMMAND_CEREG_MSEC			1800
#define BLE_COMMAND_NCCID_MSEC			600
#define BLE_COMMAND_CIMI_MSEC			600
#define BLE_COMMAND_CGPADDR_MSEC			600
#define BLE_COMMAND_CGDCONT_MSEC			600
#define BLE_COMMAND_CCLK_MSEC			600
#define BLE_COMMAND_NPSMR_MSEC			1800
#define BLE_COMMAND_CSCON_MSEC			600
#define BLE_COMMAND_NMSTATUS_MSEC		600
#define BLE_COMMAND_CGATT_MSEC			1500
#define BLE_COMMAND_CFUN_MSEC			8000
#define BLE_COMMAND_NNMI_MSEC			600
#define BLE_COMMAND_NSMI_MSEC			600
#define BLE_COMMAND_NBAND_MSEC			600
#define BLE_COMMAND_CMEE_MSEC			600
#define BLE_COMMAND_NCDP_MSEC			600
#define BLE_COMMAND_NCONFIG_MSEC			1000
#define BLE_COMMAND_NQMGS_MSEC			600
#define BLE_COMMAND_NQMGR_MSEC			600
#define BLE_COMMAND_NMGS_MSEC			1000
#define BLE_COMMAND_NMGR_MSEC			1000
#define BLE_COMMAND_DATASTATUS_MSEC		800
#define BLE_COMMAND_DATAEX_MSEC			1000
#define BLE_COMMAND_NSOCR_MSEC			600
#define BLE_COMMAND_NSOCL_MSEC			600
#define BLE_COMMAND_NSOST_MSEC			1000
#define BLE_COMMAND_NSOSTF_MSEC			1000
#define BLE_COMMAND_NSORF_MSEC			1000



/* BLE配置参数 */

// #define AT_RST						"AT+"						//复位 M/S －  
// #define AT_BOUD						"AT+"						//串口波特率设置 M/S － 115200    
// #define AT_HOSTEN					"AT+"						//主从设置 M/S － 从机    
// #define AT_HOST						"AT+"						//读取主机状态 M －   
// #define AT_DISC						"AT+"						//断开连接 M/S －   
// #define AT_ADVEN					"AT+"						//打开广播 S － 打开  
// #define AT_ADVIN					"AT+"						//广播间隔 S － 100ms   
// #define AT_NEIN						"AT+"						//连接间隔 S － 10ms  
// #define AT_POWR						"AT+"						//发射功率 S － 0db
// #define AT_NAME						"AT+NAME"						//广播名 S － JDY-08
// #define AT_MAC						"AT+"						//读 MAC 地址 M/S －
// #define AT_STRUUID					"AT+"						//设置 iBeacon UUID(字符串类型 UUID)
// #define AT_HEXUUID					"AT+"						//设置 iBeacon UUID(十六进制类型 UUID)
// #define AT_MAJOR					"AT+"						//设置 iBeacon Major
// #define AT_MINOR					"AT+"						//设置 iBeacon Minor
// #define AT_VER						"AT+"						//读取版本号 M/S － JDY-08-2.1
// #define AT_VID						"AT+"						//厂家识别码
// #define AT_TEMP						"AT+"						//温度值设置 S iBeacon
// #define AT_HUMID					"AT+"						//温度值设置 S iBeacon
// #define AT_ISCEN					"AT+"						//设置是否打开密码连接 S － 关闭
// #define AT_PASS						"AT+"						//连接密码 S － 123456
// #define AT_SVRUUID					"AT+"						//更改服务 UUID M/S － FFE0
// #define AT_CHRUUID					"AT+"						//更改特征 UUID M/S － FFE1
// #define AT_SCAN						"AT+"						//主机扫描从机 M 主机透传
// #define AT_RSLV						"AT+"						//读取主机扫描到的从机 MAC M 主机透传
// #define AT_CONNET					"AT+"						//连接扫描到从机的 MAC M 主机透传
// #define AT_BAND						"AT+"						//绑定从机 MAC M －
// #define AT_GETDCD					"AT+"						//读取主机扫描到的从机数量 M －
// #define AT_GETSTAT					"AT+"						//查找模块的工作状态 M/S －
// #define AT_PWMFRE					"AT+"						//设置 PWM 频率 M/S － 1000HZ
// #define AT_PWMOPEN					"AT+"						//打开 PWM M/S － 关闭
// #define AT_PWM1PUS					"AT+"						//设置 PWM1 的脉宽 M/S － 50%
// #define AT_PWM2PUS					"AT+"						//设置 PWM2 的脉宽 M/S － 50%
// #define AT_PWM3PUS					"AT+"						//设置 PWM3 的脉宽 M/S － 50%
// #define AT_PWM4PUS					"AT+"						//设置 PWM4 的脉宽 M/S － 50%
// #define AT_WXSVR					"AT+"						//微信 H5 与服务器通信设置 S 微信 H5
// #define AT_RTCFLSH					"AT+"						//RTC 刷新时间（秒） M/S －
// #define AT_RTCDATE					"AT+"						//RTC 时间读写 M/S －
// #define AT_RTCOPEN					"AT+"						//RTC 开关 M/S －
// #define AT_RESTORE					"AT+"						//恢复出厂配置 M/S －
// #define AT_STARTEN					"AT+"						//开机是否唤醒 M/S 唤醒模式
// #define AT_SLEEP					"AT+"						//进入睡眠模式 M/S
// #define AT_KBYTE					"AT+"						//传输速度设置 M/S 1K bytes/s
// #define AT_REVERSE					"AT+"						//P1_6 电平与唤醒 MCU 延时 M/S 1
// #define AT_CLSS						"AT+"						//设置设备类型 S 透传 A0
// #define AT_RTCALAM					"AT+"						//RTC 定时值读写 M/S
// #define AT_ALAMEN					"AT+"						//RTC 定时开关 M/S 关
// #define AT_RSSI						"AT+"						//RSSI 值 S
// #define AT_PIO						"AT+"						//指令控制 IO M/S
// #define AT_PARITY					"AT+"						//串口奇偶校验位设置 无校验位
// #define AT_WXINEN					"AT+"						//微信自动、手动测试模式选择 S 手动模式


#define AT_STARTEN				"AT+STARTEN1"			//开机睡眠  1：开机唤醒 0：开机睡眠
#define AT_NAME						"AT+NAME"					
#define AT_HOSTEN3					"AT+HOSTEN3"				
#define AT_RST						"AT+RST"					
#define AT_STRUUID					"AT+STRUUID"									
#define AT_SLEEP2					"AT+SLEEP2"					
#define AT_MAJOR					"AT+ MAJOR"					
#define AT_MINOR					"AT+MINOR"					
#define AT_VID						"AT+VID"
#define AT_PIO						"AT+PIO"
#define AT_RESTORE				"AT+RESTORE"

//#define BLE_ENABLE					0

typedef struct BLE_ParameterTypeDef		BLE_ParameterTypeDef;
typedef struct BLE_ATCmdTypeDef				BLE_ATCmdTypeDef;

/* BLE Status */
typedef enum
{
	/* -Normal Errors- */
	BLE_OK       					= 0x00,
	BLE_ERROR    					= 0x01,
	BLE_CMD_TIMEOUT					= 0x02,
	
	/* -General Errors- */

	
	/* -HISI specific error codes- */

}BLE_StatusTypeDef;


/* BLE ATCmd */
struct BLE_ATCmdTypeDef
{
	unsigned char*						ATSendbuf;
	unsigned char*						ATRecvbuf;
	size_t							ATSendbuf_size;
	size_t							ATRecvbuf_size;
	short							ATSendlen;
	short							ATRecvlen;
	char*							ATack;
	char*							ATNack;
	CalculagraphTypeDef			CmdWaitTime;
	CalculagraphTypeDef			SerialWaitTime;
	BLE_StatusTypeDef					(*Write)(BLE_ATCmdTypeDef*);
	BLE_StatusTypeDef 				(*Read)(BLE_ATCmdTypeDef*);
};

void BLE_PWRC_Init(void);
void BLE_Init(BLE_ATCmdTypeDef* ATCmd);
void BLE_Wakeup(BLE_ATCmdTypeDef* ATCmd);
void BLE_Sleep_Mode(BLE_ATCmdTypeDef* ATCmd);

void BLE_ControlIO(BLE_ATCmdTypeDef* ATCmd,uint8_t flag);
void BLE_ATCmd_SetCmdStack(BLE_ATCmdTypeDef* ATCmd, unsigned char* Sendbuf, unsigned int Sendlen, char* ATack, char* ATNack);

BLE_StatusTypeDef BLE_Transport_Init(BLE_ATCmdTypeDef* ATCmd);
BLE_StatusTypeDef BLE_Transport_SendATCmd(BLE_ATCmdTypeDef* ATCmd);
void BLE_Transport_RecvATCmd(BLE_ATCmdTypeDef* ATCmd);
void BLE_Task(BLE_Types types,BLE_ATCmdTypeDef* ATCmd);
BLE_StatusTypeDef BLE_Self_Checking(BLE_ATCmdTypeDef* ATCmd);
//void BLE_Client_Init(BLE_ClientsTypeDef* pClient, BLE_ATCmdTypeDef* ATCmdStack, NET_BLE_ClientsTypeDef* NetBLEStack);	//BLE客户端初始化

//void BLE_COAP_RA_NORMAL_SET_STATE(BLE_ClientsTypeDef* pClient, bool enable);										//设置COAP发送RA包或Normal包状态
//bool BLE_COAP_RA_NORMAL_GET_STATE(BLE_ClientsTypeDef* pClient);													//读取COAP发送RA包或Normal包状态

#endif /* __BLE_CONFIG_H */
