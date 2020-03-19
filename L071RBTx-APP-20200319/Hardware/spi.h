/**
******************************************************************************
* @file    spi.h
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
#ifndef __SPI_H
#define __SPI_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
extern SPI_HandleTypeDef RFIDHandle;
/* Exported constants --------------------------------------------------------*/

/* Definition for RFID clock resources */


#define  		RFID_CS_LOW()     						HAL_GPIO_WritePin(RFID_GPIO_PORT, RFID_PIN_NSS, GPIO_PIN_RESET)
#define  		RFID_CS_HIGH()    						HAL_GPIO_WritePin(RFID_GPIO_PORT, RFID_PIN_NSS, GPIO_PIN_SET)


#define RFID_NRST                          GPIO_PIN_6
#define RFID_PORT_NRST                     GPIOC
#define RFID_NRST_CLK_ENABLE()           __HAL_RCC_GPIOC_CLK_ENABLE()  
#define RFID_NRST_CLK_DISABLE()          __HAL_RCC_GPIOC_CLK_DISABLE()

/* Definition for RFID clock resources */

#define RFID_SPI                          SPI2
#define RFID_CLK_ENABLE()                __HAL_RCC_SPI2_CLK_ENABLE()
#define RFID_CLK_DISENABLE()      		 	 __HAL_RCC_SPI2_CLK_DISABLE()
#define RFID_GPIO_CLK_ENABLE()      		 __HAL_RCC_GPIOB_CLK_ENABLE()

#define RFID_FORCE_RESET()               __HAL_RCC_SPI2_FORCE_RESET()
#define RFID_RELEASE_RESET()             __HAL_RCC_SPI2_RELEASE_RESET()

/* Definition for RFID Pins */
#define RFID_SCK_PIN                     GPIO_PIN_13
#define RFID_MISO_PIN                    GPIO_PIN_14
#define RFID_MOSI_PIN                    GPIO_PIN_15

#define RFID_GPIO_AF                     GPIO_AF0_SPI2

#define RFID_PIN_NSS                     GPIO_PIN_12
#define RFID_GPIO_PORT						       GPIOB

#define REST_H  HAL_GPIO_WritePin(RFID_GPIO_PORT, RFID_PIN_NSS, GPIO_PIN_SET)

#define REST_L  HAL_GPIO_WritePin(RFID_GPIO_PORT, RFID_PIN_NSS, GPIO_PIN_RESET)

#define FM175XX_WAKEUP         REST_H
#define FM175XX_SETINLPCD      REST_L

/* Exported macro ------------------------------------------------------------*/
/* Size of buffer */
#define BUFFERSIZE                       (COUNTOF(spiTxBuffer) - 1)
/* Exported functions ------------------------------------------------------- */
void RFID_Init(void);
void spi1_data(void);
void spi2_data(void);

void Stop_Spi(void);

void     Activate_SPI(void);
void SPI1_Rx_Callback(void);
void SPI1_Tx_Callback(void);
void SPI1_TransferError_Callback(void);
void RFID_NRST_Init(void);
void FM175XX_HPD(unsigned char mode);

#endif /* __SPI_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
