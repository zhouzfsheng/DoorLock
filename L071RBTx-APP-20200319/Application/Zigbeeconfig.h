/**
******************************************************************************
* @file    Zigbeeconfig.h
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
#ifndef __ZIGBEE_CONFIG_H
#define __ZIGBEE_CONFIG_H

#include "sys.h"

#define ZIGBEE_SERIAL_TIMEOUT_MSEC			100												//串口连续接收数据包超时时间MS
#define ZIGBEE_COMMAND_TIMEOUT_MSEC			8000												//指令发送等待响应包超时时间MS
#define ZIGBEE_COMMAND_FAILURE_CNT			3												//指令执行错误尝试次数

typedef enum 
{  
  GPIOMODE_INTPUT = 0,
  GPIOMODE_EXTI = 1
} GPIOMode_TypeDef;

#define ZIGBEE_SERIAL_TIMEOUT_MSEC			100												//串口连续接收数据包超时时间MS
#define ZIGBEE_COMMAND_TIMEOUT_MSEC			8000												//指令发送等待响应包超时时间MS
#define ZIGBEE_COMMAND_FAILURE_CNT			3												//指令执行错误尝试次数

#define ZIGBEE_COMMAND_TIMEOUT_AUTO			0
#define ZIGBEE_COMMAND_TIMEOUT_MANUAL		1
#define ZIGBEE_COMMAND_TIMEOUT_TYPE			ZIGBEE_COMMAND_TIMEOUT_AUTO


#define ZIGBEE_ENAZIGBEE					0


typedef struct ZIGBEE_CmdTypeDef			ZIGBEE_CmdTypeDef;


/* ZIGBEE Status */
typedef enum
{
	/* -Normal Errors- */
	ZIGBEE_OK       					= 0x00,
	ZIGBEE_ERROR    					= 0x01,
	ZIGBEE_CMD_TIMEOUT					= 0x02,
	
	/* -General Errors- */

	
	/* -HISI specific error codes- */

}ZIGBEE_StatusTypeDef;


/* ZIGBEE Cmd */
struct ZIGBEE_CmdTypeDef
{
	unsigned char*						Sendbuf;
	unsigned char*						Recvbuf;
	size_t							Sendbuf_size;
	size_t							Recvbuf_size;
	short							Sendlen;
	short							Recvlen;
	char*							ack;
	char*							Nack;
	CalculagraphTypeDef			CmdWaitTime;
	CalculagraphTypeDef			SerialWaitTime;
	ZIGBEE_StatusTypeDef					(*Write)(ZIGBEE_CmdTypeDef*);
	ZIGBEE_StatusTypeDef 				(*Read)(ZIGBEE_CmdTypeDef*);
};

void Zigbee_Payload(void);

void Zigbee_Transport_SendCmd(uint8_t Types,uint8_t Size,uint8_t* date);
void Zigbee_Transport_SendRecord(uint8_t Types,uint8_t Size,uint8_t* date);


uint8_t u8SL_CalculateCRC(uint16_t u16Type, uint16_t u16Length, uint8_t *pu8Data);


#endif /* __ZIGBEE_CONFIG_H */
