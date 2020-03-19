/**
  ******************************************************************************
  * @file    stm32l0xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "stm32l0xx.h"
#include "stm32l0xx_it.h"

/* USER CODE BEGIN 0 */
#include "gpio.h"
#include "sys.h"
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern RTC_HandleTypeDef RtcHandle;
extern UART_HandleTypeDef UART1_Handler;
extern uint8_t Device_Wkup_Flag_Now;
/******************************************************************************/
/*            Cortex-M0+ Processor Interruption and Exception Handlers         */ 
/******************************************************************************/

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
//  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

/**********************************************************************************************************
 @Function      void HAL_SYSTICK_Callback(void)
 @Description     系统嘀嗒定时器中断处理回调函数
          在HAL库中所有系统嘀嗒定时器中断服务函数都会调用此函数
 @Input       void
 @Return        void
**********************************************************************************************************/
void HAL_SYSTICK_Callback(void)
{
  __IO uint32_t SystickCtrlVal = SysTick->CTRL;             //清除COUNTFLAG
  (void) SystickCtrlVal;                        //丢弃SystickCtrlVal
  
  HAL_IncTick();
  IncSecondTick();
  
//  SystemSoftResetTime++;                        //软重启计数器累加
//  if (SystemSoftResetTime >= 100000) {                  //100秒计数器溢出重启
//    Stm32_System_Software_Reboot(RBTMODE_SYSTEM_OVERTIME);
//  }
}
/******************************************************************************/
/* STM32L0xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l0xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles RTC global interrupt through EXTI lines 17, 19 and 20 and LSE CSS interrupt through EXTI line 19.
*/
void RTC_IRQHandler(void)
{
  /* USER CODE BEGIN RTC_IRQn 0 */

  /* USER CODE END RTC_IRQn 0 */
  HAL_RTCEx_WakeUpTimerIRQHandler(&RtcHandle);
  /* USER CODE BEGIN RTC_IRQn 1 */

  /* USER CODE END RTC_IRQn 1 */
}

///**
//* @brief This function handles EXTI line 0 and line 1 interrupts.
//*/
//void EXTI0_1_IRQHandler(void)
//{
//  /* USER CODE BEGIN EXTI0_1_IRQn 0 */

//  /* USER CODE END EXTI0_1_IRQn 0 */
//  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
//  /* USER CODE BEGIN EXTI0_1_IRQn 1 */

//  /* USER CODE END EXTI0_1_IRQn 1 */
//}

/**
* @brief This function handles EXTI line 0 and line 1 interrupts.
*/
void EXTI4_15_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI0_1_IRQn 0 */

  /* USER CODE END EXTI0_1_IRQn 0 */
	
#ifdef Zigbee_IRQ
  HAL_GPIO_EXTI_IRQHandler(Zigbee_IRQ);
#endif 
	
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_7);

#ifdef BUTTON_EXTI_5
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_5);
#endif 

#ifdef BUTTON_EXTI_6
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_6);
#endif 
	
#ifdef SWITCH_EXTI_8
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_8);
#endif 

#ifdef SWITCH_EXTI_9
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
#endif
	
  /* USER CODE BEGIN EXTI0_1_IRQn 1 */

  /* USER CODE END EXTI0_1_IRQn 1 */

}

///**
//* @brief This function handles USART1 global interrupt / USART1 wake-up interrupt through EXTI line 25.
//*/
//void USART1_IRQHandler(void)
//{
//  /* USER CODE BEGIN USART1_IRQn 0 */

//  /* USER CODE END USART1_IRQn 0 */
//  HAL_UART_IRQHandler(&UART1_Handler);
//  /* USER CODE BEGIN USART1_IRQn 1 */

//  /* USER CODE END USART1_IRQn 1 */
//}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
