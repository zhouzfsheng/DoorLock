/**
*********************************************************************************************************
* @file    mian.c
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
#include "main.h"
#include "App.h"
#include "BSP_pwr.h"
#include "1755test.h"


/* USER CODE END Includes */
uint8_t DEVICE_RTC_ALARM_HOUR           = 0x00;
uint8_t DEVICE_RTC_ALARM_MINUTE         = 0x00;
uint8_t DEVICE_RTC_ALARM_SECOND         = 0x00;

uint32_t Device_Wkup_Flag_Now = DEVICE_NON_WKUP_FLAG;          //系统唤醒源全局变量

#ifndef SleepTime
uint16_t SleepTime = 1;
#endif
/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
void power_exit_stop(void);
void power_enter_stop(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
__IO uint8_t sec = 0;
__IO uint8_t wake= 0;
/* USER CODE END 0 */

int main(void)
{

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
	Peripherals();

	LowPower_Config();
	
	//调试烧录
	HAL_Delay(1000);
  /* Infinite loop */
	while (1)
	{
			Appication_Funtion();
			LowPowerMode();

		// Stangdby 唤醒后，直接复位MCU
		
	}

}



/* USER CODE BEGIN 4 */
/*###########################################################################*/
// 只是分割线，可以在下面添加代码
/*###########################################################################*/

// 外部中断唤醒回调函数
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{

	if(GPIO_Pin==KEY_Pin){
		    Device_Wkup_Flag_Now |= DEVICE_FMXX_IRQ_FLAG;
	}
	
#ifdef Zigbee_IRQ
	if(GPIO_Pin==Zigbee_IRQ){
		    Device_Wkup_Flag_Now |= DEVICE_ZIGB_IRQ_FLAG;
	}
#endif 

#ifdef BUTTON_EXTI_5
	if(GPIO_Pin==BUTTON_EXTI_5){
		    Device_Wkup_Flag_Now |= DEVICE_SWTH_IO5_FLAG;
	}
#endif 
	
#ifdef BUTTON_EXTI_6
	if(GPIO_Pin==BUTTON_EXTI_6){
		    Device_Wkup_Flag_Now |= DEVICE_SWTH_IO6_FLAG;
	}
#endif 
	
#ifdef SWITCH_EXTI_8
	if(GPIO_Pin==SWITCH_EXTI_8){
		    Device_Wkup_Flag_Now |= DEVICE_SWTH_IO8_FLAG;
	}
#endif 
#ifdef SWITCH_EXTI_9
	if(GPIO_Pin==SWITCH_EXTI_9){
		    Device_Wkup_Flag_Now |= DEVICE_SWTH_IO9_FLAG;
	}
#endif

		// 打开RTC内部唤醒时间设置
		HAL_RTCEx_SetWakeUpTimer_IT(&RtcHandle, 2048, RTC_WAKEUPCLOCK_CK_SPRE_16BITS);
}


// rtc周期中断回调函数
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc)
{
  Device_Wkup_Flag_Now |= DEVICE_RTC_INT_FLAG;
}
/*###########################################################################*/
// 只是分割线
/*###########################################################################*/
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
	/* User can add his own implementation to report the file name and line number,
	ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
