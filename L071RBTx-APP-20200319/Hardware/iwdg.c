/**
  *********************************************************************************************************
  * @file    iwdg.c
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
#include "app.h"
#include "iwdg.h"

IWDG_HandleTypeDef IwdgHandle;


/**********************************************************************************************************
 @Function			void Iwdg_Init(void)
 @Description		Iwdg_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void Iwdg_Init(void)
{
	  /*##-1- Check if the system has resumed from IWDG reset ####################*/
  if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST) != RESET)
  {
		printf("IWDG reset!!\r\n");
  }
  /* Clear reset flags anyway */
  __HAL_RCC_CLEAR_RESET_FLAGS();

  /*##-2- Configure & Start the IWDG peripheral ##############################*/
  /* Set counter reload value to obtain 762ms IWDG TimeOut.
     Counter Reload Value = (LsiFreq(Hz) * Timeout(ms)) / (prescaler * 1000)                         
  */
  IwdgHandle.Instance = IWDG;
  IwdgHandle.Init.Prescaler = IWDG_PRESCALER_128;
  IwdgHandle.Init.Reload = 4095;
  IwdgHandle.Init.Window = 4095;

  if(HAL_IWDG_Init(&IwdgHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}

/**********************************************************************************************************
 @Function			void MCU_ResetCheck(void)
 @Description		MCU_ResetCheck
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void MCU_ResetCheck(void)
{
	
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_OBLRST))
    {
        printf("Options bytes loading Reset!\r\n");
    }
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST))
    {
        printf("PIN Reset!\r\n");
    }
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST))
    {
        printf("POR/PDR Reset!\r\n");
    }
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST))
    {
        printf("Software Reset!\r\n");
    }
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST))
    {
        printf("IWDG Reset!\r\n");
				Event_appDate.MCU_RSTStatus = RCC_FLAG_IWDGRST;
    }
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST))
    {
        printf("WWDG Reset!\r\n");
    }
    if(__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST))
    {
        printf("Low-Power Reset!\r\n");
    }

    // 清除全部复位标志
    __HAL_RCC_CLEAR_RESET_FLAGS();
}
/**
  * @}
  */

/********************************************** END OF FLEE **********************************************/

