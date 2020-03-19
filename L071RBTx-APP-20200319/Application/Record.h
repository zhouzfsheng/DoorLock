/**
******************************************************************************
* @file    record.h
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
#ifndef __RECORD_H
#define __RECORD_H

/* Includes ------------------------------------------------------------------*/
#include "Common.h"
#include "App.h"

#define  Configuration_Address           	0x00000

#define  SuperCardn_Address               0x01000
#define  SuperCardi_Address              	0x01010

#define  NormalCardn_Address              0x03000
#define  NormalCardi_Address             	0x03010

#define  BlackListCardn_Address           0x04000
#define  BlackListCardi_Address          	0x04010


#define  SuperCardn_TAddress              0x02000
#define  SuperCardi_TAddress              0x02010
#define  NormalCardn_TAddress             0x04000
#define  NormalCardi_TAddress             0x04010
#define  BlackListCardn_TAddress          0x05000
#define  BlackListCardi_TAddress          0x05010

#define  BLEUUID_Time_Address          		0x06000
#define  BLEUUID_Address          				0x06010
//4Mflash(0x00000-0x7ffff)
#define  Record_Address                 0x08000			//存储地址

#define  FLASH_Sector                   0x7EFFF			//记录结束地址


/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */

void GetRecordData(void);

void Issued_Card(uint8_t type,uint8_t* date,uint8_t number);

void SystemInfo_Init(void);

void WirteConfiguration_Parameters(void);
void ReadConfiguration_Parameters(void);

void WirteNormalCard(uint8_t Flag);
void ReadNormalCard(uint8_t Flag);

void WirteSuperCard(uint8_t Flag);
void ReadSuperCard(uint8_t Flag);

void WirteBlacklistCard(uint8_t Flag);
void ReadBlacklistCard(uint8_t Flag);

void WirteOneRecord(void);
void Terminal_Record(void);

void Change_Address_Table(uint8_t type,uint8_t* u8CRC);

void ClearFlash(void);

void Factory_Reset(void);

void WirteUUID(uint8_t* para,uint8_t* data);
void ReadUUID(uint8_t number);

void LOG_OutPut_Parameters(void);
void Report_Record(void);

void ClearUUID(void);

#endif /* __RECORD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



