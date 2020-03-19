/**
  *********************************************************************************************************
  * @file    time.c
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
#include "timer.h"
/* Timer handler declaration */
TIM_HandleTypeDef    TimHandle;

/* Timer Output Compare Configuration Structure declaration */
TIM_OC_InitTypeDef sConfig;

/* Private typedef -----------------------------------------------------------*/
#define  PERIOD_VALUE       (uint32_t)(750 - 1)  /* Period Value  */
#define  PULSE1_VALUE       (uint32_t)(PERIOD_VALUE/2)        /* Capture Compare 1 Value  */
#define  PULSE2_VALUE       (uint32_t)(PERIOD_VALUE*37.5/100) /* Capture Compare 2 Value  */
#define  PULSE3_VALUE       (uint32_t)(PERIOD_VALUE/4)        /* Capture Compare 3 Value  */
#define  PULSE4_VALUE       (uint32_t)(PERIOD_VALUE*12.5/100) /* Capture Compare 4 Value  */

#define  PULSE5_VALUE       (uint32_t)(PERIOD_VALUE*80/100) /* Capture Compare 4 Value  */
/* Counter Prescaler value */
uint32_t uhPrescalerValue = 0;

/* Prescaler declaration */
uint32_t uwPrescalerValue = 0;

/**********************************************************************************************************
 @Function			void TIME_Init(void)
 @Description		TIME_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void TIME_Init(void)
{
	  /*##-1- Configure the TIM peripheral #######################################*/
  /* -----------------------------------------------------------------------
    In this example TIM2 input clock (TIM2CLK) is set to APB1 clock (PCLK1),
    since APB1 prescaler is equal to 1, TIM2CLK = PCLK1 = HCLK = SystemCoreClock
    
    To get TIM2 counter clock at 10 KHz, the timer Prescaler is computed as follow :
    Prescaler = (TIM2CLK / TIM2 counter clock) - 1
    Prescaler = (SystemCoreClock/10 KHz) - 1

    Note:
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32l0xx.c file.
     Each time the core clock (HCLK) changes, user had to update SystemCoreClock
     variable value. Otherwise, any configuration based on this variable will be incorrect.
     This variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetSysClockFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
  ----------------------------------------------------------------------- */

  /* Compute the prescaler value to have TIMx counter clock equal to 2500 Hz */
  uwPrescalerValue = (uint32_t)(SystemCoreClock / 2500) - 1;

  /* Set TIMx instance */
  TimHandle.Instance = TIM2x;

  /* Initialize TIMx peripheral as follows:
       + Period = 2500 - 1
       + Prescaler = (SystemCoreClock/2500) - 1
       + ClockDivision = 0
       + Counter direction = Up
  */
  TimHandle.Init.Period            = 2500 - 1;
  TimHandle.Init.Prescaler         = uwPrescalerValue;
  TimHandle.Init.ClockDivision     = 0;
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;

  if (HAL_TIM_Base_Init(&TimHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }

  /*##-2- Start the TIM Base generation in interrupt mode ####################*/
  /* Start Channel1 */
  if (HAL_TIM_Base_Start_IT(&TimHandle) != HAL_OK)
  {
    /* Starting Error */
    Error_Handler();
  }
}

/**********************************************************************************************************
 @Function			void BEEP_void(void)
 @Description		BEEP_void
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/

void BEEP_void(uint8_t ucL,uint8_t ucD)
{
	int i,j;
	
	for(i=0;i<ucL;i++)
	{
		PWM_output_start();
		HAL_Delay(1100);
		PWM_output_stop();
		HAL_Delay(200);
	}
	HAL_Delay(300);
	for(j=0;j<ucD;j++)
	{
		PWM_output_start();
		HAL_Delay(300);
		PWM_output_stop();
		HAL_Delay(200);
	}

//	HAL_TIM_PWM_DeInit(&TimHandle);
}

/**********************************************************************************************************
 @Function			void TIMx_PWM_Init(void)
 @Description		TIMx_PWM_Init
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void TIMx_PWM_Init(void)
{

  /* Compute the prescaler value to have TIM2 counter clock equal to 2000000 Hz */
  uhPrescalerValue = (uint32_t)(SystemCoreClock / 2000000) - 1;

  /*##-1- Configure the TIM peripheral #######################################*/
  /* -----------------------------------------------------------------------
  TIM2 Configuration: generate 4 PWM signals with 4 different duty cycles.

    In this example TIM2 input clock (TIM2CLK) is set to APB1 clock (PCLK1),
    since APB1 prescaler is equal to 1.
      TIM2CLK = PCLK1
      PCLK1 = HCLK
      => TIM2CLK = HCLK = SystemCoreClock

    To get TIM2 counter clock at 2.1 MHz, the prescaler is computed as follows:
       Prescaler = (TIM2CLK / TIM2 counter clock) - 1
       Prescaler = ((SystemCoreClock) /2.1 MHz) - 1

    To get TIM2 output clock at 3 KHz, the period (ARR)) is computed as follows:
       ARR = (TIM2 counter clock / TIM2 output clock) - 1
           = 699

    TIM2 Channel1 duty cycle = (TIM2_CCR1/ TIM2_ARR + 1)* 100 = 50%
    TIM2 Channel2 duty cycle = (TIM2_CCR2/ TIM2_ARR + 1)* 100 = 37.5%
    TIM2 Channel3 duty cycle = (TIM2_CCR3/ TIM2_ARR + 1)* 100 = 25%
    TIM2 Channel4 duty cycle = (TIM2_CCR4/ TIM2_ARR + 1)* 100 = 12.5%

    Note:
     SystemCoreClock variable holds HCLK frequency and is defined in system_stm32l0xx.c file.
     Each time the core clock (HCLK) changes, user had to update SystemCoreClock
     variable value. Otherwise, any configuration based on this variable will be incorrect.
     This variable is updated in three ways:
      1) by calling CMSIS function SystemCoreClockUpdate()
      2) by calling HAL API function HAL_RCC_GetSysClockFreq()
      3) each time HAL_RCC_ClockConfig() is called to configure the system clock frequency
  ----------------------------------------------------------------------- */

  /* Initialize TIMx peripheral as follows:
       + Prescaler = (SystemCoreClock / 2000000) - 1
       + Period = (700 - 1)
       + ClockDivision = 0
       + Counter direction = Up
  */
  TimHandle.Instance = TIM2x;

  TimHandle.Init.Prescaler         = uhPrescalerValue;
  TimHandle.Init.Period            = PERIOD_VALUE;
  TimHandle.Init.ClockDivision     = 0;
  TimHandle.Init.CounterMode       = TIM_COUNTERMODE_UP;
  if (HAL_TIM_PWM_Init(&TimHandle) != HAL_OK)
  {
    /* Initialization Error */
    Error_Handler();
  }
}
/**********************************************************************************************************
 @Function			void PWM_output_start(void)
 @Description		PWM_output_start
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void PWM_output_start(void)
{
	
  /*##-2- Configure the PWM channels #########################################*/
  /* Common configuration for all channels */
  sConfig.OCMode       = TIM_OCMODE_PWM1;
  sConfig.OCPolarity   = TIM_OCPOLARITY_LOW;
  sConfig.OCFastMode   = TIM_OCFAST_DISABLE;

  /* Set the pulse value for channel 3 */
  sConfig.Pulse = PULSE1_VALUE;
  if (HAL_TIM_PWM_ConfigChannel(&TimHandle, &sConfig, TIMx_PWM_CHANNEL) != HAL_OK)
  {
    /* Configuration Error */
    Error_Handler();
  }

  /*##-3- Start PWM signals generation #######################################*/

  /* Start channel 3 */
  if (HAL_TIM_PWM_Start(&TimHandle, TIMx_PWM_CHANNEL) != HAL_OK)
  {
    /* PWM generation Error */
    Error_Handler();
  }

}
/**********************************************************************************************************
 @Function			void PWM_output_stop(void)
 @Description		PWM_output_stop
 @Input				  void
 @Return				void
 @Other:
**********************************************************************************************************/
void PWM_output_stop(void)
{
	if (HAL_TIM_PWM_Stop(&TimHandle, TIMx_PWM_CHANNEL) != HAL_OK)
	{
    /* PWM generation Error */
    Error_Handler();
  }
}
/********************************************** END OF FLEE **********************************************/
