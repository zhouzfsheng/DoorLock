/**
  *********************************************************************************************************
  * @file    rtc.c
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
#include "rtc.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

RTC_HandleTypeDef RtcHandle;

/**********************************************************************************************************
 @Function			void MX_RTC_Init(void)
 @Description		MX_RTC_Init
 @Input				void
 @Return			void
 @Other:
**********************************************************************************************************/
void MX_RTC_Init(void)
{
  RTC_TimeTypeDef sTime;
  RTC_DateTypeDef sDate;
	
	/**Initialize RTC Only 
	*/
	RtcHandle.Instance = RTC;
	RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
	RtcHandle.Init.AsynchPrediv = 127;
	RtcHandle.Init.SynchPrediv = 255;
	RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;
	RtcHandle.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
	RtcHandle.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
	if (HAL_RTC_Init(&RtcHandle) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}
	
  if (HAL_RTCEx_BKUPRead(&RtcHandle, RTC_BKP_DR1) == 0xDF59)
  {
    /* if the wakeup timer is enabled then deactivate it to disable the wakeup timer interrupt */
    if(HAL_RTCEx_DeactivateWakeUpTimer(&RtcHandle) != HAL_OK)
    {
      /* Initialization Error */
      Error_Handler(); 
    }
  }
	
//	printf("HAL_RTCEx_BKUPRead %02x",HAL_RTCEx_BKUPRead(&RtcHandle, RTC_BKP_DR1));
		/**Initialize RTC and set the Time and Date 
		*/
	//0x4B->"K" 0x48->"H"
	if(HAL_RTCEx_BKUPRead(&RtcHandle, RTC_BKP_DR1) != 0xDF59){
		sTime.Hours = 0x0;
		sTime.Minutes = 0x0;
		sTime.Seconds = 0x0;
		sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
		sTime.StoreOperation = RTC_STOREOPERATION_RESET;
		if (HAL_RTC_SetTime(&RtcHandle, &sTime, RTC_FORMAT_BCD) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}

		sDate.WeekDay = 0;
		sDate.Month = AppMonth;
		sDate.Date = AppDate;
		sDate.Year = AppYear;

		if (HAL_RTC_SetDate(&RtcHandle, &sDate, RTC_FORMAT_BCD) != HAL_OK)
		{
			_Error_Handler(__FILE__, __LINE__);
		}

		HAL_RTCEx_BKUPWrite(&RtcHandle,RTC_BKP_DR1,0xDF59);
	}
		/**Enable the WakeUp 
		*/
	if (HAL_RTCEx_SetWakeUpTimer_IT(&RtcHandle, 2048, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
	{
		_Error_Handler(__FILE__, __LINE__);
	}

}

/**********************************************************************************************************
 @Function			void HAL_RTC_MspInit(void)
 @Description		HAL_RTC_MspInit
 @Input				void
 @Return			void
 @Other:
**********************************************************************************************************/
void HAL_RTC_MspInit(RTC_HandleTypeDef* hrtc)
{

  if(hrtc->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspInit 0 */

  /* USER CODE END RTC_MspInit 0 */
    /* RTC clock enable */
    __HAL_RCC_RTC_ENABLE();

    /* RTC interrupt Init */
    HAL_NVIC_SetPriority(RTC_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(RTC_IRQn);
  /* USER CODE BEGIN RTC_MspInit 1 */

  /* USER CODE END RTC_MspInit 1 */
  }
}

/**********************************************************************************************************
 @Function			void HAL_RTC_MspDeInit(void)
 @Description		HAL_RTC_MspDeInit
 @Input				void
 @Return			void
 @Other:
**********************************************************************************************************/
void HAL_RTC_MspDeInit(RTC_HandleTypeDef* hrtc)
{

  if(hrtc->Instance==RTC)
  {
  /* USER CODE BEGIN RTC_MspDeInit 0 */

  /* USER CODE END RTC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_RTC_DISABLE();

    /* RTC interrupt Deinit */
    HAL_NVIC_DisableIRQ(RTC_IRQn);
  /* USER CODE BEGIN RTC_MspDeInit 1 */

  /* USER CODE END RTC_MspDeInit 1 */
  }
} 

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/**
  * @}
  */

/**
  * @}
  */

/********************************************** END OF FLEE **********************************************/

