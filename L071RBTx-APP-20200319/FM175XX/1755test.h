/**
******************************************************************************
* @file    1755test.h
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
#ifndef __1755TEST_H
#define __1755TEST_H
  /* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "READER_API.h"
/* Includes ------------------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
extern struct type_a_struct Type_A;
/* Private define ------------------------------------------------------------*/
uint16_t Official_Test(void);
void GPIO_IRQ_Event(void);
void Credit_card_processing(void);

/**
  * @}
  */ 

/**
  * @}
*/ 

#endif /* __1755TEST_H */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
