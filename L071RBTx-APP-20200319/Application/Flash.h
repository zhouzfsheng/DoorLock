/**
******************************************************************************
* @file    flash.h
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
#ifndef __FLASH_H
#define __FLASH_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

#define W25Q80 								0XEF13 	
#define W25Q16							 	0XEF14
#define W25Q32 								0XEF15
#define W25Q64 								0XEF16

//extern u8 SPI_FLASH_BUF[4096];
//W25X16读写
#define FLASH_ID 							0XEF13
//指令表
#define W25X_WriteEnable			0x06 
#define W25X_WriteDisable			0x04 
#define W25X_ReadStatusReg		0x05 
#define W25X_WriteStatusReg		0x01 
#define W25X_ReadData					0x03 
#define W25X_FastReadData			0x0B 
#define W25X_FastReadDual			0x3B 
#define W25X_PageProgram			0x02 
#define W25X_BlockErase				0xD8 
#define W25X_SectorErase			0x20 
#define W25X_ChipErase				0xC7 
#define W25X_PowerDown				0xB9 
#define W25X_ReleasePowerDown	0xAB 
#define W25X_DeviceID					0xAB 
#define W25X_ManufactDeviceID	0x90 
#define W25X_JedecDeviceID		0x9F 

/* Exported types ------------------------------------------------------------*/
extern SPI_HandleTypeDef FLASHHandle;

#define FLASH_SPI                             SPI1
#define FLASH_CLK_ENABLE()                		__HAL_RCC_SPI1_CLK_ENABLE()
#define FLASH_CLK_DISENABLE()      		 				__HAL_RCC_SPI1_CLK_DISABLE()
#define FLASH_GPIO_CLK_ENABLE()      		 			__HAL_RCC_GPIOA_CLK_ENABLE()


#define FLASH_FORCE_RESET()                		__HAL_RCC_SPI1_FORCE_RESET()
#define FLASH_RELEASE_RESET()      		 				__HAL_RCC_SPI1_RELEASE_RESET()

/* Definition for RFID Pins */
#define FLASH_SCK_PIN                         GPIO_PIN_5
#define FLASH_MISO_PIN                        GPIO_PIN_6
#define FLASH_MOSI_PIN                        GPIO_PIN_7
#define FLASH_GPIO_AF                         GPIO_AF0_SPI1

#define FLASH_PIN_NSS                         GPIO_PIN_4
#define FLASH_GPIO_PORT                       GPIOA

#define  		SPI_FLASH_CS_LOW()     						HAL_GPIO_WritePin(FLASH_GPIO_PORT, FLASH_PIN_NSS, GPIO_PIN_RESET)
#define  		SPI_FLASH_CS_HIGH()    						HAL_GPIO_WritePin(FLASH_GPIO_PORT, FLASH_PIN_NSS, GPIO_PIN_SET)

/* Exported constants --------------------------------------------------------*/
typedef enum
{
	FLASH_OK								= 0x00,
	FLASH_ERROR							= 0x01,
	FLASH_SPI_ERROR					= 0x02
}FLASH_StatusTypeDef;
/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void Flash_NSS(void);
void Flash_DeInit(void);
void FLASH_Init(void);
FLASH_StatusTypeDef FLASH_Get_Status(void);

uint8_t	 SPI_Flash_ReadSR(void);        //读取状态寄存器 
void SPI_FLASH_Write_SR(uint8_t sr);  	//写状态寄存器
void SPI_FLASH_Write_Enable(void);  //写使能 
void SPI_FLASH_Write_Disable(void);	//写保护
void SPI_Flash_Read(uint8_t* pBuffer,uint32_t ReadAddr,uint16_t NumByteToRead);   //读取flash
void SPI_Flash_Write(uint8_t* pBuffer,uint32_t WriteAddr,uint16_t NumByteToWrite);//写入flash
void SPI_Flash_Erase_Chip(void);    	  //整片擦除
void SPI_Flash_Erase_Sector(uint32_t Dst_Addr);//扇区擦除
void SPI_Flash_Wait_Busy(void);           //等待空闲
void SPI_Flash_PowerDown(void);           //进入掉电模式
void SPI_Flash_WAKEUP(void);			  //唤醒

uint16_t SPI_Flash_ReadID(void);

#endif /* __FLASH_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
