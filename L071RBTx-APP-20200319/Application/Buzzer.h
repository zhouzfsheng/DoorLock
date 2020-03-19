/**
*********************************************************************************************************
* @file    Buzzer.h
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
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __BUZZER_H
#define __BUZZER_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
	 
///*
//ʮλ�ǳ�������λ�Ƕ���
//����: 
//0x01-������0��1��
//0x23-������2��1��

//0x0f-������û�г�����һֱ����
//****************************
enum Logevent
{
  Swipe =0,
  UnLock = 1, //�ܿ���
	Equipment_Lock,//�豸����
  Illegal_Card,//�Ƿ�������������ں������ڱ�������ƽ̨��ѯ��������ֱ�ӱ������������ò�ѯ��
  Illegal_Entrant,//�Ƿ�����
  Low_Battery,
  Fault,//����
  //Not connected to the Internet
  Installation_Mode,
  Normal_Mode,//����ģʽû����
	LOG_Buzzer
};
	 
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

void Buzz_Rhythm(uint8_t log);

/* USER CODE BEGIN Prototypes */

/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif
#endif /*__BUZZER_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
