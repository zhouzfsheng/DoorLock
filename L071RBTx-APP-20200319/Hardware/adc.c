/**
*********************************************************************************************************
* @file    adc.c
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

#include "adc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

ADC_HandleTypeDef		VBAT_ADC_Handler;									//电池电压ADC句柄

/**********************************************************************************************************
 @Function			void VBAT_ADC_Init(void)
 @Description		电压ADC初始化
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void VBAT_ADC_Init(void)
{
	ADC_ChannelConfTypeDef ADC_ChanelConfig;
	
	// ADC Function Configuration
  VBAT_ADC_Handler.Instance = ADC1;
  
  VBAT_ADC_Handler.Init.OversamplingMode      = DISABLE;
  
  VBAT_ADC_Handler.Init.ClockPrescaler        = ADC_CLOCK_SYNC_PCLK_DIV1;
  VBAT_ADC_Handler.Init.LowPowerAutoPowerOff  = DISABLE;
  VBAT_ADC_Handler.Init.LowPowerFrequencyMode = ENABLE;
  VBAT_ADC_Handler.Init.LowPowerAutoWait      = DISABLE;
    
  VBAT_ADC_Handler.Init.Resolution            = ADC_RESOLUTION_12B;
  VBAT_ADC_Handler.Init.SamplingTime          = ADC_SAMPLETIME_7CYCLES_5;
  VBAT_ADC_Handler.Init.ScanConvMode          = ADC_SCAN_DIRECTION_FORWARD;
  VBAT_ADC_Handler.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
  VBAT_ADC_Handler.Init.ContinuousConvMode    = ENABLE;
  VBAT_ADC_Handler.Init.DiscontinuousConvMode = DISABLE;
  VBAT_ADC_Handler.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;
  VBAT_ADC_Handler.Init.EOCSelection          = ADC_EOC_SINGLE_CONV;
  VBAT_ADC_Handler.Init.DMAContinuousRequests = DISABLE;
	
	  /* Initialize ADC peripheral according to the passed parameters */
  if (HAL_ADC_Init(&VBAT_ADC_Handler) != HAL_OK)
  {
    Error_Handler();
  }
  
  /* ### - 2 - Start calibration ############################################ */
  if (HAL_ADCEx_Calibration_Start(&VBAT_ADC_Handler, ADC_SINGLE_ENDED) != HAL_OK)
  {
    Error_Handler();
  }

  /* ### - 3 - Channel configuration ######################################## */
  /* Select Channel 0 to be converted */
  ADC_ChanelConfig.Channel = ADC_CHANNEL_8;    
  if (HAL_ADC_ConfigChannel(&VBAT_ADC_Handler, &ADC_ChanelConfig) != HAL_OK)
  {
    Error_Handler();
  }	
	
}

/**********************************************************************************************************
 @Function			u16 VBAT_ADC_Read(u32 timeout)
 @Description		电源电压ADC读取
 @Input				  读出等待超时时间
 @Return				电压值
 @Other:
**********************************************************************************************************/
uint16_t VBAT_ADC_Read(uint32_t timeout)
{
	uint32_t pwr_vol = 0;
	GPIO_InitTypeDef GPIO_Initure;
	
	VBAT_ADC_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = VBAT_ADC_PIN;
	GPIO_Initure.Mode = GPIO_MODE_ANALOG;
	GPIO_Initure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(VBAT_ADC_GPIOx, &GPIO_Initure);
	
	VBAT_ADC_Init();													//电压ADC初始化
	
	
	HAL_ADC_Start(&VBAT_ADC_Handler);
	
	HAL_ADC_PollForConversion(&VBAT_ADC_Handler, timeout);
	
	pwr_vol = HAL_ADC_GetValue(&VBAT_ADC_Handler);
	
	HAL_ADC_Stop(&VBAT_ADC_Handler);
	
//	printf("pwr_vol:%x\r\n",pwr_vol);
	
	VBAT_ADC_RCC_GPIO_CLK_ENABLE();
	
	GPIO_Initure.Pin = VBAT_ADC_PIN;
	GPIO_Initure.Mode = GPIO_MODE_ANALOG;
	GPIO_Initure.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(VBAT_ADC_GPIOx, &GPIO_Initure);
	
	HAL_ADC_DeInit(&VBAT_ADC_Handler);
	
	return pwr_vol * 100 * 28 / 40960;
}

/**********************************************************************************************************
 @Function			void HAL_ADC_MspInit(void)
 @Description		HAL_ADC_MspInit
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct;
  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspInit 0 */

  /* USER CODE END ADC1_MspInit 0 */
    /* ADC1 clock enable */
    __HAL_RCC_ADC1_CLK_ENABLE();
  
    /**ADC GPIO Configuration    
    PB15     ------> ADC_IN21 
    */
    GPIO_InitStruct.Pin = VBAT_ADC_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(VBAT_ADC_GPIOx, &GPIO_InitStruct);

  /* USER CODE BEGIN ADC1_MspInit 1 */

  /* USER CODE END ADC1_MspInit 1 */
  }
}

/**********************************************************************************************************
 @Function			void HAL_ADC_MspDeInit(void)
 @Description		HAL_ADC_MspDeInit
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle)
{

  if(adcHandle->Instance==ADC1)
  {
  /* USER CODE BEGIN ADC1_MspDeInit 0 */

  /* USER CODE END ADC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_ADC1_CLK_DISABLE();
  
    /**ADC GPIO Configuration    
    PB15     ------> ADC_IN21 
    */
    HAL_GPIO_DeInit(VBAT_ADC_GPIOx, VBAT_ADC_PIN);

  /* USER CODE BEGIN ADC1_MspDeInit 1 */

  /* USER CODE END ADC1_MspDeInit 1 */
  }
} 
/********************************************** END OF FLEE **********************************************/

