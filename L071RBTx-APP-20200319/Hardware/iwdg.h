/**
******************************************************************************
* @file    iwdgh.h
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
#ifndef __IWDG_H
#define __IWDG_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"

extern IWDG_HandleTypeDef IwdgHandle;
	 
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void Iwdg_Init(void);

/* USER CODE BEGIN Prototypes */
void MCU_ResetCheck(void);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__ __IWDG_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
