/**
  *********************************************************************************************************
  * @file    Zigbeetransport.c
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
#include "Zigbeeconfig.h"
/* Private typedef -----------------------------------------------------------*/

uint8_t rxdata[10];


/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

union KYZH_Head Kyzh_Head;
extern union RTCParameterConfiguration RTCPConfiguration;

/****************************************************************************
 *
 * NAME: u8SL_CalculateCRC
 *
 * DESCRIPTION:
 * Calculate CRC of packet
 *
 * PARAMETERS: Name                   RW  Usage
 *             u8Type                 R   Message type
 *             u16Length              R   Message length
 *             pu8Data                R   Message payload
 * RETURNS:
 * CRC of packet
 ****************************************************************************/
uint8_t u8SL_CalculateCRC(uint16_t u16Type, uint16_t u16Length, uint8_t *pu8Data)
{

    int n;
    uint8_t u8CRC;

    u8CRC  = (u16Type   >> 0) & 0xff;
    u8CRC ^= (u16Type   >> 8) & 0xff;
    u8CRC ^= (u16Length >> 0) & 0xff;
    u8CRC ^= (u16Length >> 8) & 0xff;

    for(n = 0; n < u16Length; n++)
    {
        u8CRC ^= pu8Data[n];
    }

    return(u8CRC);
}

//通讯包只是在原来基本上家'K''H''事件类型''长度''数据'/r/n
void Zigbee_Transport_SendCmd(uint8_t Types,uint8_t Size,uint8_t* date)
{
	uint8_t senddate[255];
	Zigbee_Wake_Up();
	
  /* Reset PIN to switch off the LED */
  HAL_GPIO_WritePin(Zigbee_GPIO_PORT, Zigbee_Wakeup, GPIO_PIN_SET); 
	
	HAL_Delay(10);
	Kyzh_Head.kyzh_head.u8ASeq = 'K';
	Kyzh_Head.kyzh_head.u8FSeq = 'H';
	Kyzh_Head.kyzh_head.u8TaskTypes = Types;
	Kyzh_Head.kyzh_head.u8Size = Size;
	
	if(Size >0)
	{
		memcpy(senddate,date,Size);
	}
	senddate[Size] = 0x0A;

	Kyzh_Head.kyzh_head.u8CRC = u8SL_CalculateCRC(Kyzh_Head.kyzh_head.u8TaskTypes,Kyzh_Head.kyzh_head.u8Size,senddate);
	
	HAL_UART_Transmit(&UART1_Handler, Kyzh_Head.array, sizeof(Kyzh_Head.array), 0x07FF);

	HAL_UART_Transmit(&UART1_Handler, senddate, Size+1, 0x07FF);
	
	HAL_GPIO_WritePin(Zigbee_GPIO_PORT, Zigbee_Wakeup, GPIO_PIN_RESET); 
	Zigbee_DeInit();
}

//通讯包只是在原来基本上家'K''H''事件类型''长度''数据'/r/n
void Zigbee_Transport_SendRecord(uint8_t Types,uint8_t Size,uint8_t* date)
{

	uint8_t senddate[255];
	
	Kyzh_Head.kyzh_head.u8ASeq = 'K';
	Kyzh_Head.kyzh_head.u8FSeq = 'H';
	Kyzh_Head.kyzh_head.u8TaskTypes = Types;
	Kyzh_Head.kyzh_head.u8Size = Size;
	
	if(Size >0)
	{
		memcpy(senddate,date,Size);
	}

	senddate[Size] = 0x0A;

	Kyzh_Head.kyzh_head.u8CRC = u8SL_CalculateCRC(Kyzh_Head.kyzh_head.u8TaskTypes,Kyzh_Head.kyzh_head.u8Size,senddate);
	

	HAL_UART_Transmit(&UART1_Handler, Kyzh_Head.array, sizeof(Kyzh_Head.array), 0x07FF);

	HAL_UART_Transmit(&UART1_Handler, senddate, Size+1, 0x07FF);

	memset(senddate,0,sizeof(senddate));
	memset(Kyzh_Head.array,0,sizeof(Kyzh_Head.array));

}


//通讯包只是在原来基本上家'K''H''事件类型''长度''数据'/r/n
void Zigbee_Payload(void)
{
	printf("U1L %x\r\n",Event_appDate.Uart1length);
	if(Event_appDate.Uart1length)
	{
		printf("U1RX:");
		for(int i = 2;i<Event_appDate.Uart1length;i++)
		{
			printf(" %02x",USART1_RX_BUF[i]);
		}
		printf("\r\n");
	}
	memcpy(Kyzh_Head.array,USART1_RX_BUF,sizeof(Kyzh_Head.array));

	if(Kyzh_Head.kyzh_head.u8CRC == u8SL_CalculateCRC(Kyzh_Head.kyzh_head.u8TaskTypes,Kyzh_Head.kyzh_head.u8Size,&USART1_RX_BUF[5]))
	{
//		printf("CRC sussecc \r\n");

		if(Kyzh_Head.kyzh_head.u8TaskTypes<0x40)
		{
//			BLE_Task(Kyzh_Head.kyzh_head.u8TaskTypes,&BLEATcmd);
		}else{
			switch(Kyzh_Head.kyzh_head.u8TaskTypes)
			{
				case MCU_RstMCU:
						DataTransmition(MCU_RstMCU);
						break;
				case MCU_Device_Self_Checking://设备自检
						DataTransmition(MCU_Device_Self_Checking);
						break;
				case MCU_Set_RTC_Event:
						if(Kyzh_Head.kyzh_head.u8Size)
						{
							if(USART1_RX_BUF[sizeof(Kyzh_Head.array)])
							{
								if(!USART1_RX_BUF[sizeof(Kyzh_Head.array)])
								{
								memcpy(RTCPConfiguration.array,&USART1_RX_BUF[sizeof(Kyzh_Head.array)+1],sizeof(RTCPConfiguration.array));
								Event_appDate.NTP_value[Event_appDate.NTP_No] = RTC_TimeToStamp(RTCPConfiguration.rtc_event.Year[1],
																																									RTCPConfiguration.rtc_event.Month,
																																									RTCPConfiguration.rtc_event.Date,
																																									RTCPConfiguration.rtc_event.Hours,
																																									RTCPConfiguration.rtc_event.Minutes,
																																									RTCPConfiguration.rtc_event.Seconds);
								}else if(USART1_RX_BUF[sizeof(Kyzh_Head.array)] == 0x02 )
								{
									Event_appDate.NTP_value[Event_appDate.NTP_No] = USART1_RX_BUF[sizeof(Kyzh_Head.array)+4]<< 24 | 
																																		USART1_RX_BUF[sizeof(Kyzh_Head.array)+3]<< 16 | 
																																		USART1_RX_BUF[sizeof(Kyzh_Head.array)+2]<< 8 |
																																		USART1_RX_BUF[sizeof(Kyzh_Head.array)+1];
								}
							}else{
								memcpy(RTCPConfiguration.array,&USART1_RX_BUF[sizeof(Kyzh_Head.array)+1],sizeof(RTCPConfiguration.array));
							}
							DataTransmition(MCU_Set_RTC_Event);
						}
						break;
				case MCU_Test_Interface://测试接口
						DataTransmition(MCU_Test_Interface);
						break;
				case MCU_Parameter_Configuration://门禁配置
						if(Kyzh_Head.kyzh_head.u8Size)
						{
							SRPConfiguration.sParameterConfiguration.Automatic_Locking_Time[0] = USART1_RX_BUF[sizeof(Kyzh_Head.array)];
							SRPConfiguration.sParameterConfiguration.Automatic_Locking_Time[1] = USART1_RX_BUF[sizeof(Kyzh_Head.array)+1];
							
							SRPConfiguration.sParameterConfiguration.Restricted_Start_Time[0] = USART1_RX_BUF[sizeof(Kyzh_Head.array)+2];
							SRPConfiguration.sParameterConfiguration.Restricted_Start_Time[1] = USART1_RX_BUF[sizeof(Kyzh_Head.array)+3];
							
							SRPConfiguration.sParameterConfiguration.Restricted_Stop_Time[0] = USART1_RX_BUF[sizeof(Kyzh_Head.array)+4];
							SRPConfiguration.sParameterConfiguration.Restricted_Stop_Time[1] = USART1_RX_BUF[sizeof(Kyzh_Head.array)+5];
							WirteConfiguration_Parameters();
						}
						DataTransmition(MCU_Parameter_Configuration);
						break;
				case MCU_Issued_Door_Card://平台设置开门权限（发卡）
						Issued_Card(USART1_RX_BUF[sizeof(Kyzh_Head.array)+2],&USART1_RX_BUF[sizeof(Kyzh_Head.array)+4],USART1_RX_BUF[sizeof(Kyzh_Head.array)+3]);
						DataTransmition(MCU_Issued_Door_Card);
						break;
				case MCU_Query_Lock_Record://平台查询操作记录
						DataTransmition(MCU_Query_Lock_Record);
						break;
				case MCU_Online_UnLock_Event://命令开门
						memcpy(Event_appDate.ucCardId,&USART1_RX_BUF[sizeof(Kyzh_Head.array)],sizeof(Event_appDate.ucCardId));
						DataTransmition(MCU_Online_UnLock_Event);
						break;
				case MCU_Electricity_Query:
						DataTransmition(MCU_Electricity_Query);
						break;
				case MCU_UnLocking://开锁事件
						if(USART1_RX_BUF[sizeof(Kyzh_Head.array)])
						{
							DataTransmition(MCU_Authentication);
						}
						Zigbee_Transport_SendCmd(MCU_Authentication,0,0);//回复成功
						break;
				case MCU_Locking://关锁事件
						DataTransmition(MCU_Locking);
						break;
			case MCU_Equipment_lock_or_unlock:
						SRPConfiguration.sParameterConfiguration.Restricted_Condition = USART1_RX_BUF[sizeof(Kyzh_Head.array)];
						DataTransmition(MCU_Equipment_lock_or_unlock);
						break;
				case MCU_BLE_Open://开启蓝牙
						memcpy(Event_appDate.UID, &USART1_RX_BUF[sizeof(Kyzh_Head.array)],32);
						Event_appDate.BLEOpentime = USART1_RX_BUF[sizeof(Kyzh_Head.array)+32] << 8 | USART1_RX_BUF[sizeof(Kyzh_Head.array)+33];
						DataTransmition(MCU_BLE_Open);
						break;
				case MCU_BLE_Close://关锁蓝牙
						DataTransmition(MCU_BLE_Close);
						break;
				case MCU_Query_UUID://获取UUID
						DataTransmition(MCU_Query_UUID);
						break;
				case MCU_NetworkState:
						Event_appDate.NetworkState = 1;
						DataTransmition(MCU_NetworkState);
						break;
				case MCU_ChangeAddress:
						Change_Address_Table(USART1_RX_BUF[sizeof(Kyzh_Head.array)+2],&USART1_RX_BUF[sizeof(Kyzh_Head.array)+4]);
						break;
				case MCU_FactoryReset_Event:
						DataTransmition(MCU_FactoryReset_Event);
						break;
				case MCU_UUIDList:
						if(!Event_appDate.BLEUUID_Time)
						{
							WirteUUID(&USART1_RX_BUF[sizeof(Kyzh_Head.array)],&USART1_RX_BUF[sizeof(Kyzh_Head.array)+7]);
						}
						DataTransmition(MCU_UUIDList);
						break;
				case MCU_Passthrough:
					//与zigbee网关同步时间
					break;
				default:
					break;
			}
		}

	}else
	{
		printf("CRC %x \r\n",u8SL_CalculateCRC(Kyzh_Head.kyzh_head.u8TaskTypes,Kyzh_Head.kyzh_head.u8Size,&USART1_RX_BUF[5]));
	}
	
	Event_appDate.Uart1length = 0;
	memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
	memset(Kyzh_Head.array,0,sizeof(Kyzh_Head.array));
}

/**********************************************************************************************************
 @Function			ZIGBEE_StatusTypeDef ZIGBEE_Transport_SendCmd(NBIOT_CmdTypeDef* Cmd)
 @Description		ZIGBEE_Transport_SendCmd 				: 发送指令等待应答
 @Input					Cmd		 													: 指令结构体
 @Return				ZIGBEE_StatusTypeDef						: ZIGBEE处理状态
**********************************************************************************************************/
ZIGBEE_StatusTypeDef ZIGBEE_Transport_SendCmd(ZIGBEE_CmdTypeDef* Cmd)
{
		ZIGBEE_StatusTypeDef ZIGBEEStatus = ZIGBEE_OK;
		__IO ITStatus UartReady = RESET;
		uint16_t cnt = 0;

		Uart1_InterruptEnable(ENABLE, DISABLE);
	
		HAL_UART_Transmit(&UART1_Handler,Cmd->Sendbuf, Cmd->Sendlen, 0x07FF);
		
		while(!UartReady)
		{
			HAL_Delay(100);
			
			if (USART1_RX_STA & 0x8000) {																//接收到期待的应答结果
				USART1_RX_STA &= 0x2000;																	//缓存状态清0可继续接收
				UartReady = SET;
			}
			cnt ++ ;
			if(cnt>30)
			{
				cnt = 0;
				ZIGBEEStatus = ZIGBEE_CMD_TIMEOUT;
				printf("ZIGBEE_CMD_TIMEOUT\r\n");
				break;
			}
		}
		UartReady = RESET;
		
		printf("USART1_RX_BUF: %s \r\n",USART1_RX_BUF);

		if (strstr((const char*)USART1_RX_BUF, Cmd->ack)) {
			printf("ZIGBEE_OK\r\n");
			ZIGBEEStatus = ZIGBEE_OK;
		}else if (strstr((const char*)USART1_RX_BUF, Cmd->Nack)) {
			printf("ZIGBEE_OK\r\n");
			ZIGBEEStatus = ZIGBEE_OK;
		}
		
		Uart1_InterruptEnable(DISABLE, DISABLE);
		memset(USART1_RX_BUF,0,sizeof(USART1_RX_BUF));
	return ZIGBEEStatus;
}

/**********************************************************************************************************
 @Function			ZIGBEE_StatusTypeDef ZIGBEE_Transport_RecvCmd(NBIOT_CmdTypeDef* Cmd)
 @Description		ZIGBEE_Transport_RecvCmd 				: 接收指令应答
 @Input					Cmd		 													: 指令结构体
 @Return				ZIGBEE_StatusTypeDef						: ZIGBEE处理状态
**********************************************************************************************************/
ZIGBEE_StatusTypeDef ZIGBEE_Transport_RecvCmd(ZIGBEE_CmdTypeDef* Cmd)
{
	ZIGBEE_StatusTypeDef ZIGBEEStatus = ZIGBEE_OK;

	__IO ITStatus UartReady = RESET;
	uint16_t cnt = 0;
	
	USART1_RX_STA = 0;																				//接收状态复位
	memset((void *)USART1_RX_BUF, 0x0, sizeof(USART1_RX_BUF));												//清空缓存空间
	

		while (!UartReady) {									//等待倒计时
			HAL_Delay(100);
			if (USART1_RX_STA & 0x8000) {																//接收到期待的应答结果
				USART1_RX_STA &= 0x2000;																	//缓存状态清0可继续接收
				UartReady = SET;
			}

			cnt ++ ;
			if(cnt>30)
			{
				cnt = 0;
				ZIGBEEStatus = ZIGBEE_CMD_TIMEOUT;
				printf("ZIGBEE_CMD_TIMEOUT\r\n");
				break;
			}
		}
		UartReady = RESET;
		
		printf("USART1_RX_BUF: %s \r\n",USART1_RX_BUF);
		
	return ZIGBEEStatus;
}

/**********************************************************************************************************
 @Function			NBIOT_StatusTypeDef NBIOT_Transport_SendATCmd(NBIOT_ATCmdTypeDef* ATCmd)
 @Description			NBIOT_Transport_SendATCmd 				: 发送AT指令等待应答
 @Input				ATCmd		 						: AT指令结构体
 @Return				NBIOT_StatusTypeDef						: NBIOT处理状态
**********************************************************************************************************/
ZIGBEE_StatusTypeDef ZIGBEE_Transport_SendATCmd(ZIGBEE_CmdTypeDef* Cmd)
{
	ZIGBEE_StatusTypeDef ZGStatus = ZIGBEE_OK;
	CalculagraphTypeDef Serial_timer_Ms;
	
	if (Cmd->Sendlen > Cmd->Sendbuf_size) {														//发送数据长度检测
		ZGStatus = ZIGBEE_ERROR;
		goto exit;
	}
	
	Uart1_InterruptEnable(ENABLE, DISABLE);															//开启接收中断
	USART1_RX_STA |= 0x2000;																			//接收状态复位
	memset((void *)USART1_RX_BUF, 0x0, sizeof(USART1_RX_BUF));												//清空缓存空间
	
	if (HAL_OK != HAL_UART_Transmit(&UART1_Handler, Cmd->Sendbuf, Cmd->Sendlen, 0x07FF)) {					//发送命令
		ZGStatus = ZIGBEE_ERROR;
		Uart1_InterruptEnable(DISABLE, DISABLE);
		goto exit;
	}
	
	if ((Cmd->ack && Cmd->CmdWaitTime.xTicksToWait) || (Cmd->Nack && Cmd->CmdWaitTime.xTicksToWait)) {	//需要等待应答
		
		Calculagraph_ConfigurationMS(&Serial_timer_Ms, ZIGBEE_SERIAL_TIMEOUT_MSEC);
		Cmd->SerialWaitTime = Serial_timer_Ms;
		
		while (Calculagraph_MS(&Cmd->SerialWaitTime) != true) {								//等待倒计时
			if (USART1_RX_STA & 0x8000) {																//接收到期待的应答结果
				USART1_RX_STA &= 0x2000;																//缓存状态清0可继续接收
			}
			else if (USART1_RX_STA & 0x2000) {															//正在接收中
				Calculagraph_ConfigurationMS(&Serial_timer_Ms, ZIGBEE_SERIAL_TIMEOUT_MSEC);
				Cmd->SerialWaitTime = Serial_timer_Ms;
			}
			if (Calculagraph_MS(&Cmd->CmdWaitTime) == true) {								//超过命令执行时间
				break;
			}
		}
		
		while (Calculagraph_MS(&Cmd->CmdWaitTime) != true) {									//等待倒计时
			if (USART1_RX_STA != 0) {															//接收到期待的应答结果
				
				if (Cmd->ack && (strstr((const char*)USART1_RX_BUF, (const char*)Cmd->ack) != NULL)) {			//Found! OK
					if (Cmd->Recvbuf) {															//获取应答数据
						if (USART1_RX_STA > Cmd->Recvbuf_size) {								//接收AT数据长度检测
							ZGStatus = ZIGBEE_ERROR;
							goto exit;
						}
						strncpy((char *)Cmd->Recvbuf, (char*)USART1_RX_BUF, USART1_RX_STA);
						Cmd->Recvbuf[USART1_RX_STA] = '\0';
						Cmd->Recvlen = USART1_RX_STA;
					}
					ZGStatus = ZIGBEE_OK;
					break;
				}
				else if (Cmd->Nack && (strstr((const char*)USART1_RX_BUF, (const char*)Cmd->Nack) != NULL)) {		//Found! Err
					if (Cmd->Recvbuf) {															//获取应答数据
						if (USART1_RX_STA > Cmd->Recvbuf_size) {								//接收AT数据长度检测
							ZGStatus = ZIGBEE_ERROR;
							goto exit;
						}
						strncpy((char *)Cmd->Recvbuf, (char*)USART1_RX_BUF, USART1_RX_STA);
						Cmd->Recvbuf[USART1_RX_STA] = '\0';
						Cmd->Recvlen = USART1_RX_STA;
					}
					ZGStatus = ZIGBEE_ERROR;
					break;
				}
				else {																						//NotFound!
					ZGStatus = ZIGBEE_CMD_TIMEOUT;
					goto exit;
				}
			}
			else {
				ZGStatus = ZIGBEE_CMD_TIMEOUT;
				goto exit;
			}
		}
		
		if (Calculagraph_MS(&Cmd->CmdWaitTime) == true) {
			Cmd->Recvlen = 0;
			ZGStatus = ZIGBEE_CMD_TIMEOUT;
		}
	}
	
exit:
	Uart1_InterruptEnable(DISABLE, DISABLE);
	
	return ZGStatus;
}

