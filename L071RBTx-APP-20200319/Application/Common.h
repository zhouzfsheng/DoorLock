/**
******************************************************************************
* @file    Common.h
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
#ifndef __COMMON_H
#define __COMMON_H

/* Includes ------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>

#include "stm32l0xx_hal.h"

#include "usart.h"
#include "spi.h"
#include "gpio.h"
#include "Flash.h"
#include "time.h"
#include "rtc.h"
#include "adc.h"
#include "iwdg.h"

#include "Zigbeeconfig.h"
#include "Bleconfig.h"
/* Exported types ------------------------------------------------------------*/
/*
                _________________________
                |                       |
BLE_PWRC     <--|PA00								PB00|--> ADC 
BLE_RST      <--|PA01								PB01|--> LED3
BLE_RXD      <--|PA02								PB02|--> LED2
BLE_TXD      <--|PA03								PB03|--> SWO 
SPI1_NSS     <--|PA04								PB04|--> LED1
SPI1_SCk     <--|PA05								PB05|--> Botton1
SPI1_MISO    <--|PA06								PB06|--> Botton2
SPI1_MOSI    <--|PA07								PB07|--> BLE_XX2
BLE_WAKE     <--|PA08								PB08|--> I2C2_SCL
ZIG_RXD      <--|PA09								PB09|--> I2C2_SDA
ZIG_TXD      <--|PA10								PB10|--> Moto_IB
ATE_enable   <--|PA11								PB11|--> Moto_IA
ZIG_REST     <--|PA12								PB12|--> SPI2_NSS
SWDIO        <--|PA13								PB13|--> SPI2_SCK
SWCLK        <--|PA14								PB14|--> SPI2_MISO
BUZZER_Ctr   <--|PA15								PB15|--> SPI2_MOSI
                |     STM32L071RBT6     |           
I2C3_SDA     <--|PC00								PC08|--> Switich1
I2C3_SCL     <--|PC01               PC09|--> Switich2 
ZIG_XX1      <--|PC02               PC10|--> Switich3 
ZIG_XX2      <--|PC03               PC11|--> Switich4 
ZIG_XX3      <--|PC04               PC12|--> Switich5 
BLE_XX1      <--|PC05               PC13|--> Botton 
RF_RSTO      <--|PC06               PC14|--> ADC 
RF_IRQ       <--|PC07               PC15|--> ADC
                |_______________________|

*/

//PC13 -> 前面盖
//PC05 -> 后面盖

#define TRUE 1
#define FALSE 0

/* Exported constants --------------------------------------------------------*/

/* Defines related to Clock configuration */

#define RTC_ASYNCH_PREDIV    0x7C
#define RTC_SYNCH_PREDIV     0x0127


//打印等级
#define LOG_ERR (1)
#define LOG_WRN (2)
#define LOG_INF (3)
#define LOG_DBG (4)
#define LOG_NOL (5)
 
static int log_lvl = LOG_DBG;//设置为调试级别
 
#define LOG(lvl, ...) \
    do { \
        if(lvl == LOG_NOL) { \
					log_lvl = LOG_DBG; \
					printf(__VA_ARGS__); \
        } \
				else{ \
					if(lvl <= log_lvl) { \
            switch(lvl) { \
                case LOG_ERR: \
                     log_lvl = LOG_ERR; \
                break; \
                case LOG_WRN: \
                     log_lvl = LOG_WRN; \
                break; \
                case LOG_INF: \
                      log_lvl = LOG_INF; \
                break; \
                case LOG_DBG: \
                     log_lvl = LOG_DBG; \
                break; \
                default: \
                     log_lvl = LOG_DBG; \
                break; \
							} \
						printf(__VA_ARGS__); \
						} \
				} \
    } while(0)

/* Exported macro ------------------------------------------------------------*/
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
/* Exported functions ------------------------------------------------------- */

	
#endif /* __COMMON_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/


