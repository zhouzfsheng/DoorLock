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
  *
  *
  *********************************************************************************************************
  */
	
/* Includes ------------------------------------------------------------------*/
#include "App.h"
#include "Bleconfig.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
BLE_StatusTypeDef BLEStatus = BLE_OK;

uint8_t BLE_ATSendBuf[BLE_ATBUFFER_SIZE];
uint8_t BLE_ATRecvBuf[BLE_ATBUFFER_SIZE];
/**********************************************************************************************************
 @Function			static void BLE_Neul_NBxx_DictateEvent_SetTime(BLE_ClientsTypeDef* pClient, unsigned int TimeoutMsec)
 @Description			BLE_Neul_NBxx_DictateEvent_SetTime	: 事件运行控制器注入时间(内部使用)
 @Input				pClient							: BLE客户端实例
					TimeoutMsec						: 注入超时时间
 @Return				void
**********************************************************************************************************/
static void BLE_DictateEvent_SetTime(BLE_ATCmdTypeDef* ATCmdStack, unsigned int TimeoutMsec)
{
	CalculagraphTypeDef ATCmd_timer_Ms;
	
	Calculagraph_ConfigurationMS(&ATCmd_timer_Ms, TimeoutMsec);
	ATCmdStack->CmdWaitTime = ATCmd_timer_Ms;
}


/**********************************************************************************************************
 @Function			void BLE_ControlIO(BLE_ATCmdTypeDef* ATCmd)
 @Description		BLE_ControlIO 							: 初始化蓝牙模块
 @Input					ATCmd		 										: AT指令结构体
 @Return				BLE_StatusTypeDef						: BLE处理状态
 @Other:
P12 IO1 输出 IO1 引脚可以通过 APP 控制电平
P13 IO2 输出 IO2 引脚可以通过 APP 控制电平
P15 IO3 输出 IO3 引脚可以通过 APP 控制电平
P14 IO4 输出 IO4 引脚可以通过 APP 控制电平
AT+ PIO<Param> Param												:（00 - 44）
设置 IO1 为高电平 AT+ PIO11
设置 IO1 为低电平 AT+ PIO10
**********************************************************************************************************/
void BLE_ControlIO(BLE_ATCmdTypeDef* ATCmd,uint8_t flag)
{
	char PIO_date[14] = {0};
	BLE_PWRC_Init();
	
	if(flag)
	{
		sprintf(PIO_date,"%s%s",AT_PIO,"11");//high
		BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)PIO_date,strlen((const char*)PIO_date),"+OK","+ERR");
		BLE_Transport_SendATCmd(ATCmd);
	}else{
		sprintf(PIO_date,"%s%s",AT_PIO,"10");//low
		BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)PIO_date,strlen((const char*)PIO_date),"+OK","+ERR");
		BLE_Transport_SendATCmd(ATCmd);
	}
}

void BLE_Task(BLE_Types types,BLE_ATCmdTypeDef* ATCmd)
{
	switch(types)
	{
		case BLE_RST:                             //复位 M/S －
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_BOUD:                           //串口波特率设置 M/S － 115200
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_HOSTEN:                         //主从设置 M/S － 从机
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_HOST:                           //读取主机状态 M －
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_DISC:                           //断开连接 M/S －
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_ADVEN:                          //打开广播 S － 打开
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_ADVIN:                          //广播间隔 S － 100ms
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_NEIN:                           //连接间隔 S － 10ms
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_POWR:                           //发射功率 S － 0db
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_NAME:                           //广播名 S － JDY-08
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_MAC:                            //读 MAC 地址 M/S －
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_STRUUID:                        //设置 iBeacon UUID(字符串类型 UUID)
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_HEXUUID:                        //设置 iBeacon UUID(十六进制类型 UUID)
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_MAJOR:                          //设置 iBeacon Major
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_MINOR:                          //设置 iBeacon Minor
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_VER:                            //读取版本号 M/S － JDY-08-2.1
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_VID:                            //厂家识别码
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_TEMP:                           //温度值设置 S iBeacon
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_HUMID:                          //温度值设置 S iBeacon
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_ISCEN:                          //设置是否打开密码连接 S － 关闭
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_PASS:                           //连接密码 S － 123456
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_SVRUUID:                        //更改服务 UUID M/S － FFE0
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_CHRUUID:                        //更改特征 UUID M/S － FFE1
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_SCAN:                           //主机扫描从机 M 主机透传
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_RSLV:                           //读取主机扫描到的从机 MAC M 主机透传
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_CONNET:                         //连接扫描到从机的 MAC M 主机透传
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_BAND:                           //绑定从机 MAC M －
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_GETDCD:                         //读取主机扫描到的从机数量 M －
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_GETSTAT:                        //查找模块的工作状态 M/S －
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_PWMFRE:                         //设置 PWM 频率 M/S － 1000HZ
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_PWMOPEN:                        //打开 PWM M/S － 关闭
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_PWM1PUS:                        //设置 PWM1 的脉宽 M/S － 50%
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_PWM2PUS:                        //设置 PWM2 的脉宽 M/S － 50%
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_PWM3PUS:                        //设置 PWM3 的脉宽 M/S － 50%
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_PWM4PUS:                        //设置 PWM4 的脉宽 M/S － 50%
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_WXSVR:                          //微信 H5 与服务器通信设置 S 微信 H5
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_RTCFLSH:                        //RTC 刷新时间（秒） M/S －
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_RTCDATE:                        //RTC 时间读写 M/S －
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_RTCOPEN:                        //RTC 开关 M/S －
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_RESTORE:                        //恢复出厂配置 M/S －
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_STARTEN:                        //开机是否唤醒 M/S 唤醒模式
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_SLEEP:                          //进入睡眠模式 M/S
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_KBYTE:                          //传输速度设置 M/S 1K bytes/s
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_REVERSE:                        //P1_6 电平与唤醒 MCU 延时 M/S 1
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_CLSS:                           //设置设备类型 S 透传 A0
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_RTCALAM:                        //RTC 定时值读写 M/S
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_ALAMEN:                         //RTC 定时开关 M/S 关
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_RSSI:                           //RSSI 值 S
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_PIO:                            //指令控制 IO M/S
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_PARITY:                         //串口奇偶校验位设置 无校验位
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
			break;
		case BLE_WXINEN:                         //微信自动、手动测试模式选择 S 手动模式	
			BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");		
			break;
		default:
			break;
	}
	BLE_Transport_SendATCmd(ATCmd);	
}

/**********************************************************************************************************
 @Function			void BLE_Init(BLE_ATCmdTypeDef* ATCmd)
 @Description		BLE_Init 										: 初始化蓝牙模块
 @Input					ATCmd		 										: AT指令结构体
 @Return				BLE_StatusTypeDef						: BLE处理状态
 @Other:
AT+NAME<Param>  Param												：模块蓝牙名称 最长： 20 字节
**********************************************************************************************************/
void BLE_Init(BLE_ATCmdTypeDef* ATCmd)
{
//	uint16_t timeout = 0;
	
#ifdef BLE_ENABLE
	char NAME_date[30] = {0};
	char UUID_date[50] = {0};
	
//	char MAJOR_date[14] = {0};
//	char MINOR_date[14] = {0};
//	char VID_date  [12] = {0};

//	sprintf(MAJOR_date,"%s%s",AT_MAJOR,"FFFF");
//	sprintf(MINOR_date,"%s%s",AT_MINOR,"FFFF");
//	sprintf(VID_date,"%s%s",AT_VID,"FF");

//	MCU_GetUID();
	sprintf(NAME_date,"%s%s",AT_NAME,"KY-L-802");
	sprintf(UUID_date,"%s%s",AT_STRUUID,Event_appDate.UID);
#endif
	
	BLE_PWRC_Init();//唤醒蓝牙
	
#ifdef BLE_ENABLE
//	BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_STARTEN,strlen((const char*)AT_STARTEN),"+OK","+ERR");
//	BLEStatus = BLE_Transport_SendATCmd(ATCmd);

	BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)NAME_date,strlen((const char*)NAME_date),"+OK","+ERR");
	if(BLE_Transport_SendATCmd(ATCmd) == BLE_CMD_TIMEOUT)
	timeout++;
	
	BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_HOSTEN3,strlen((const char*)AT_HOSTEN3),"+OK","+ERR");
	if(BLE_Transport_SendATCmd(ATCmd) == BLE_CMD_TIMEOUT)
	timeout++;

	BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_RST,strlen((const char*)AT_RST),"+OK","+ERR");
	if(BLE_Transport_SendATCmd(ATCmd) == BLE_CMD_TIMEOUT)
	timeout++;
	if(timeout>3)
	{
		BLEStatus = BLE_CMD_TIMEOUT;
		return BLEStatus;
	}

	HAL_Delay(500);

	BLE_PWRC_Init();
//	BLE_ControlIO(ATCmd,0);

	BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)UUID_date,strlen((const char*)UUID_date),"+OK","+ERR");
	BLE_Transport_SendATCmd(ATCmd);
	
//	BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)MAJOR_date,strlen((const char*)MAJOR_date),"+OK","+ERR");
//	BLE_Transport_SendATCmd(ATCmd);
//	
//	BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)MINOR_date,strlen((const char*)MINOR_date),"+OK","+ERR");
//	BLE_Transport_SendATCmd(ATCmd);
//	
//	BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)VID_date,strlen((const char*)VID_date),"+OK","+ERR");
//	BLE_Transport_SendATCmd(ATCmd);

#endif
	BLE_Transport_Init(ATCmd);

	BLE_DictateEvent_SetTime(ATCmd,BLE_SERIAL_TIMEOUT_MSEC);

	BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_SLEEP2,strlen((const char*)AT_SLEEP2),"+SLEEP:OK","+ERR");
	if(BLE_Transport_SendATCmd(ATCmd) == BLE_CMD_TIMEOUT)
	{

		printf("BLE_CMD_TIMEOUT\r\n");
	}

}

/**********************************************************************************************************
 @Function			BLE_StatusTypeDef BLE_GetStatus(void)
 @Description		BLE_GetStatus 					: 启动蓝牙
 @Input					void		 								
 @Return				BLEStatus								: BLE处理状态
 @Other:
**********************************************************************************************************/
BLE_StatusTypeDef BLE_GetStatus(void)
{
	return BLEStatus;
}

/**********************************************************************************************************
 @Function			void BLE_Self_Checking(BLE_ATCmdTypeDef* ATCmd)
 @Description		BLE_Self_Checking 					: 启动蓝牙
 @Input					ATCmd		 										: AT指令结构体
 @Return				BLE_StatusTypeDef						: BLE处理状态
 @Other:
**********************************************************************************************************/
BLE_StatusTypeDef BLE_Self_Checking(BLE_ATCmdTypeDef* ATCmd)
{
	BLE_PWRC_Init();
	
	BLE_Transport_RecvATCmd(ATCmd);

	BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_STRUUID,strlen((const char*)AT_STRUUID),"+UUID","+ERR");
	return BLE_Transport_SendATCmd(ATCmd);

}

/**********************************************************************************************************
 @Function			void BLE_Wakeup(BLE_ATCmdTypeDef* ATCmd)
 @Description		BLE_Wakeup 									: 启动蓝牙
 @Input					ATCmd		 										: AT指令结构体
 @Return				BLE_StatusTypeDef						: BLE处理状态
 @Other:
**********************************************************************************************************/
void BLE_Wakeup(BLE_ATCmdTypeDef* ATCmd)
{
	BLE_PWRC_Init();
	
	char WAKEUUID_date[50] = {0};

	BLE_Transport_RecvATCmd(ATCmd);
	
	sprintf(WAKEUUID_date,"%s%s",AT_STRUUID,Event_appDate.UID);
	BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_STRUUID,strlen((const char*)AT_STRUUID),"+UUID","+ERR");
	BLE_Transport_SendATCmd(ATCmd);

	WAKEUUID_date[42] = 0x00;
	BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)WAKEUUID_date,strlen((const char*)WAKEUUID_date),"+OK","+ERR");
	BLE_Transport_SendATCmd(ATCmd);

}

/**********************************************************************************************************
 @Function			void BLE_Sleep_Mode(BLE_ATCmdTypeDef* ATCmd)
 @Description		BLE_Sleep_Mode 									: 启动蓝牙休眠
 @Input					ATCmd		 										: AT指令结构体
 @Return				BLE_StatusTypeDef						: BLE处理状态
 @Other:
**********************************************************************************************************/
void BLE_Sleep_Mode(BLE_ATCmdTypeDef* ATCmd)
{
	BLE_ControlIO(ATCmd,0);
	BLE_ATCmd_SetCmdStack(ATCmd,(unsigned char*)AT_SLEEP2,strlen((const char*)AT_SLEEP2),"+SLEEP:OK","+ERR");
	BLE_Transport_SendATCmd(ATCmd);
}


/**********************************************************************************************************
 @Function			void BLE_ATCmd_SetCmdStack(BLE_ClientsTypeDef* pClient, ...)
 @Description					: AT指令设置(内部使用)
 @Input				pClient							: 
					...
 @Return				void
 @Other:
**********************************************************************************************************/
void BLE_ATCmd_SetCmdStack(BLE_ATCmdTypeDef* ATCmd, unsigned char* Sendbuf, unsigned int Sendlen, char* ATack, char* ATNack)
{
	ATCmd->ATSendbuf = Sendbuf;
	ATCmd->ATSendlen = Sendlen;
	ATCmd->ATack = ATack;
	ATCmd->ATNack = ATNack;
}

/**********************************************************************************************************
 @Function			void BLE_Transport_RecvATCmd(BLE_ATCmdTypeDef* ATCmd)
 @Description		BLE_Transport_RecvATCmd 		: 接收AT指令应答
 @Input					ATCmd		 										: AT指令结构体
 @Return				BLE_StatusTypeDef						: BLE处理状态
 @Other:
**********************************************************************************************************/
void BLE_Transport_RecvATCmd(BLE_ATCmdTypeDef* ATCmd)
{
	BLE_StatusTypeDef BLEStatus = BLE_OK;
	CalculagraphTypeDef Serial_timer_Ms;
	
	if (ATCmd->ATSendlen > ATCmd->ATSendbuf_size) {														//发送数据长度检测
		BLEStatus = BLE_ERROR;
		goto exit;
	}
	
	Uart2_InterruptEnable(ENABLE, DISABLE);															//开启接收中断
	USART2_RX_STA |= 0x2000;																			//接收状态复位
	memset((void *)USART2_RX_BUF, 0x0, sizeof(USART2_RX_BUF));												//清空缓存空间


	if ((ATCmd->ATack && ATCmd->CmdWaitTime.xTicksToWait) || (ATCmd->ATNack && ATCmd->CmdWaitTime.xTicksToWait)) {	//需要等待应答
		
		Calculagraph_ConfigurationMS(&Serial_timer_Ms, BLE_SERIAL_TIMEOUT_MSEC);
		ATCmd->SerialWaitTime = Serial_timer_Ms;

		while (Calculagraph_MS(&ATCmd->SerialWaitTime) != true) {								//等待倒计时
			if (USART2_RX_STA & 0x8000) {																//接收到期待的应答结果
				USART2_RX_STA &= 0x1FFF;
			}
			if (Calculagraph_MS(&ATCmd->CmdWaitTime) == true) {								//超过命令执行时间
				break;
			}
		}
		
		while (Calculagraph_MS(&ATCmd->CmdWaitTime) != true) {									//等待倒计时
			if (USART2_RX_STA != 0) {															//接收到期待的应答结果

				if (ATCmd->ATack && (strstr((const char*)USART2_RX_BUF, (const char*)ATCmd->ATack) != NULL)) {			//Found! OK
					if (ATCmd->ATRecvbuf) {															//获取应答数据
						if (USART2_RX_STA > ATCmd->ATRecvbuf_size) {								//接收AT数据长度检测
							BLEStatus = BLE_ERROR;
							goto exit;
						}
						strncpy((char *)ATCmd->ATRecvbuf, (char*)USART2_RX_BUF, USART2_RX_STA);
						ATCmd->ATRecvbuf[USART2_RX_STA] = '\0';
						ATCmd->ATRecvlen = USART2_RX_STA;
					}
					BLEStatus = BLE_OK;
					break;
				}
				else if (ATCmd->ATNack && (strstr((const char*)USART2_RX_BUF, (const char*)ATCmd->ATNack) != NULL)) {		//Found! Err
					if (ATCmd->ATRecvbuf) {															//获取应答数据
						if (USART2_RX_STA > ATCmd->ATRecvbuf_size) {								//接收AT数据长度检测
							BLEStatus = BLE_ERROR;
							goto exit;
						}
						strncpy((char *)ATCmd->ATRecvbuf, (char*)USART2_RX_BUF, USART2_RX_STA);
						ATCmd->ATRecvbuf[USART2_RX_STA] = '\0';
						ATCmd->ATRecvlen = USART2_RX_STA;
					}
					BLEStatus = BLE_ERROR;
					break;
				}
				else {																						//NotFound!
					BLEStatus = BLE_CMD_TIMEOUT;
					goto exit;
				}
			}
			else {
				BLEStatus = BLE_CMD_TIMEOUT;
				goto exit;
			}
		}
		
		if (Calculagraph_MS(&ATCmd->CmdWaitTime) == true) {
			ATCmd->ATRecvlen = 0;
			BLEStatus = BLE_CMD_TIMEOUT;
		}
	}
	
exit:
	Uart2_InterruptEnable(DISABLE, DISABLE);
	
//	return BLEStatus;
}

/**********************************************************************************************************
 @Function			BLE_StatusTypeDef BLE_Transport_SendATCmd(BLE_ATCmdTypeDef* ATCmd)
 @Description			BLE_Transport_SendATCmd 				: 发送AT指令等待应答
 @Input				ATCmd		 						: AT指令结构体
 @Return				BLE_StatusTypeDef						: BLE处理状态
**********************************************************************************************************/
BLE_StatusTypeDef BLE_Transport_SendATCmd(BLE_ATCmdTypeDef* ATCmd)
{
	BLE_StatusTypeDef BLEStatus = BLE_OK;
	CalculagraphTypeDef Serial_timer_Ms;
	
	if (ATCmd->ATSendlen > ATCmd->ATSendbuf_size) {														//发送数据长度检测
		BLEStatus = BLE_ERROR;
		goto exit;
	}
	
	Uart2_InterruptEnable(ENABLE, DISABLE);															//开启接收中断
	USART2_RX_STA |= 0x2000;																			//接收状态复位
	memset((void *)USART2_RX_BUF, 0x0, sizeof(USART2_RX_BUF));												//清空缓存空间

	if (HAL_OK != HAL_UART_Transmit(&UART2_Handler, ATCmd->ATSendbuf, ATCmd->ATSendlen, 0x07FF)) {					//发送命令
		BLEStatus = BLE_ERROR;
		Uart2_InterruptEnable(DISABLE, DISABLE);
		goto exit;
	}
	
	if ((ATCmd->ATack && ATCmd->CmdWaitTime.xTicksToWait) || (ATCmd->ATNack && ATCmd->CmdWaitTime.xTicksToWait)) {	//需要等待应答
		
		Calculagraph_ConfigurationMS(&Serial_timer_Ms, BLE_SERIAL_TIMEOUT_MSEC);
		ATCmd->SerialWaitTime = Serial_timer_Ms;

		while (Calculagraph_MS(&ATCmd->SerialWaitTime) != true) {								//等待倒计时
			if (USART2_RX_STA & 0x8000) {																//接收到期待的应答结果
				USART2_RX_STA &= 0x1FFF;
			}
			if (Calculagraph_MS(&ATCmd->CmdWaitTime) == true) {								//超过命令执行时间
				break;
			}
		}
		
		while (Calculagraph_MS(&ATCmd->CmdWaitTime) != true) {									//等待倒计时
			if (USART2_RX_STA != 0) {															//接收到期待的应答结果

				if (ATCmd->ATack && (strstr((const char*)USART2_RX_BUF, (const char*)ATCmd->ATack) != NULL)) {			//Found! OK
					if (ATCmd->ATRecvbuf) {															//获取应答数据
						if (USART2_RX_STA > ATCmd->ATRecvbuf_size) {								//接收AT数据长度检测
							BLEStatus = BLE_ERROR;
							goto exit;
						}
						strncpy((char *)ATCmd->ATRecvbuf, (char*)USART2_RX_BUF, USART2_RX_STA);
						ATCmd->ATRecvbuf[USART2_RX_STA] = '\0';
						ATCmd->ATRecvlen = USART2_RX_STA;
					}
					BLEStatus = BLE_OK;
					break;
				}
				else if (ATCmd->ATNack && (strstr((const char*)USART2_RX_BUF, (const char*)ATCmd->ATNack) != NULL)) {		//Found! Err
					if (ATCmd->ATRecvbuf) {															//获取应答数据
						if (USART2_RX_STA > ATCmd->ATRecvbuf_size) {								//接收AT数据长度检测
							BLEStatus = BLE_ERROR;
							goto exit;
						}
						strncpy((char *)ATCmd->ATRecvbuf, (char*)USART2_RX_BUF, USART2_RX_STA);
						ATCmd->ATRecvbuf[USART2_RX_STA] = '\0';
						ATCmd->ATRecvlen = USART2_RX_STA;
					}
					BLEStatus = BLE_ERROR;
					break;
				}
				else {																						//NotFound!
					BLEStatus = BLE_CMD_TIMEOUT;
					goto exit;
				}
			}
			else {
				BLEStatus = BLE_CMD_TIMEOUT;
				goto exit;
			}
		}
		
		if (Calculagraph_MS(&ATCmd->CmdWaitTime) == true) {
			ATCmd->ATRecvlen = 0;
			BLEStatus = BLE_CMD_TIMEOUT;
		}
	}
	
exit:
	Uart2_InterruptEnable(DISABLE, DISABLE);
	
	return BLEStatus;
}

/**********************************************************************************************************
 @Function			BLE_StatusTypeDef BLE_Transport_Init(BLE_ATCmdTypeDef* ATCmd)
 @Description			BLE_Transport_Init					: Initiative初始化BLE数据传输接口
 @Input				TCmd		 							: AT指令结构体
 @Return				BLE_StatusTypeDef						: BLE处理状态
**********************************************************************************************************/
BLE_StatusTypeDef BLE_Transport_Init(BLE_ATCmdTypeDef* ATCmd)
{
	BLE_StatusTypeDef NBStatus = BLE_OK;
	
	ATCmd->ATSendbuf					= BLE_ATSendBuf;
	ATCmd->ATRecvbuf					= BLE_ATRecvBuf;
	ATCmd->ATSendbuf_size				= sizeof(BLE_ATSendBuf);
	ATCmd->ATRecvbuf_size				= sizeof(BLE_ATRecvBuf);
	
	ATCmd->ATSendlen					= 0;
	ATCmd->ATRecvlen					= 0;
	
	ATCmd->Write						= BLE_Transport_SendATCmd;
//	ATCmd->Read						= BLE_Transport_RecvATCmd;
	
	return NBStatus;
}


