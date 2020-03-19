/**
  *********************************************************************************************************
  * @file    spi.c
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
#include "spi.h"
#include "main.h"

/* Private variables ---------------------------------------------------------*/
/* SPI handler declaration */
SPI_HandleTypeDef RFIDHandle;

/**********************************************************************************************************
 @Function			void RFID_NRST_Init(void)
 @Description		RFID_NRST_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void RFID_NRST_Init(void)
{
	GPIO_InitTypeDef  gpioinitstruct;
  
  /* Enable the GPIO_LED Clock */
  RFID_NRST_CLK_ENABLE();

  /* Configure the GPIO_LED pin */
  gpioinitstruct.Pin = RFID_NRST;
  gpioinitstruct.Mode = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Pull = GPIO_NOPULL;
  gpioinitstruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  
  HAL_GPIO_Init(RFID_PORT_NRST, &gpioinitstruct);
}

/**********************************************************************************************************
 @Function			void RFID_Init(void)
 @Description		RFID_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void RFID_Init(void)
{
  /* STM32L0xx HAL library initialization:
       - Configure the Flash prefetch, Flash preread and Buffer caches
       - Systick timer is configured by default as source of time base, but user 
             can eventually implement his proper time base source (a general purpose 
             timer for example or other time source), keeping in mind that Time base 
             duration should be kept 1ms since PPP_TIMEOUT_VALUEs are defined and 
             handled in milliseconds basis.
       - Low Level Initialization
     */

	
  /*##-1- Configure the SPI peripheral #######################################*/
  /* Set the SPI parameters */
  RFIDHandle.Instance               = RFID_SPI;
  RFIDHandle.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
  RFIDHandle.Init.Direction         = SPI_DIRECTION_2LINES;
  RFIDHandle.Init.CLKPhase          = SPI_PHASE_1EDGE;
  RFIDHandle.Init.CLKPolarity       = SPI_POLARITY_LOW;
  RFIDHandle.Init.DataSize          = SPI_DATASIZE_8BIT;
  RFIDHandle.Init.FirstBit          = SPI_FIRSTBIT_MSB;
  RFIDHandle.Init.TIMode            = SPI_TIMODE_DISABLE;
  RFIDHandle.Init.CRCCalculation    = SPI_CRCCALCULATION_DISABLE;
  RFIDHandle.Init.CRCPolynomial     = 7;
  RFIDHandle.Init.NSS               = SPI_NSS_SOFT;

  RFIDHandle.Init.Mode = SPI_MODE_MASTER;


  if(HAL_SPI_Init(&RFIDHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}


/**********************************************************************************************************
 @Function			void FM175XX_HPD(void)
 @Description		FM175XX_HPD
 @Input				  mode = 1 退出HPD模式 ，mode = 0 进入HPD模式
 @Return				void
 @Other:
**********************************************************************************************************/
void FM175XX_HPD(unsigned char mode)//mode = 1 退出HPD模式 ，mode = 0 进入HPD模式
{
	GPIO_InitTypeDef GPIO_InitStruct;
	if(mode == 0x0)
		{
			HAL_Delay(1);
			HAL_GPIO_WritePin(RFID_PORT_NRST, RFID_NRST, GPIO_PIN_RESET); //NPD = 0	进入NPD模式
				
			RFID_GPIO_CLK_ENABLE();
			/* Peripheral clock enable */
			RFID_CLK_ENABLE();
		
			/**SPI1 GPIO Configuration    
			PB3     ------> SPI1_SCK
			PB4     ------> SPI1_MISO
			PB5     ------> SPI1_MOSI 
			*/
			GPIO_InitStruct.Pin = RFID_SCK_PIN|RFID_MISO_PIN|RFID_MOSI_PIN;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
				
			GPIO_InitStruct.Pin = RFID_PIN_NSS;
			GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
			GPIO_InitStruct.Pull = GPIO_NOPULL;
			
			HAL_GPIO_Init(RFID_GPIO_PORT, &GPIO_InitStruct);

//			HAL_GPIO_WritePin(RFID_GPIO_PORT, RFID_PIN_NSS, GPIO_PIN_SET);
		}
	else
		{
			 
			
			HAL_GPIO_WritePin(RFID_PORT_NRST, RFID_NRST, GPIO_PIN_SET);	//NPD = 1 退出HPD模式
			HAL_Delay(1);//延时1ms，等待FM175XX启动

			RFID_GPIO_CLK_ENABLE();
			
			GPIO_InitStruct.Pin = RFID_SCK_PIN|RFID_MISO_PIN|RFID_MOSI_PIN;
			GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
			GPIO_InitStruct.Alternate = RFID_GPIO_AF;
			HAL_GPIO_Init(RFID_GPIO_PORT, &GPIO_InitStruct);
				

			GPIO_InitStruct.Pin = RFID_PIN_NSS;
			GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
			GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
			HAL_GPIO_Init(RFID_GPIO_PORT, &GPIO_InitStruct);

			HAL_GPIO_WritePin(RFID_GPIO_PORT, RFID_PIN_NSS, GPIO_PIN_SET);
		}
	return;
}

/********************************************** END OF FLEE **********************************************/

