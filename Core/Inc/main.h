/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.h
 * @brief          : Header for main.c file.
 *                   This file contains the common defines of the application.
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal.h"
#include "app_conf.h"
#include "app_entry.h"
#include "app_common.h"
#include "app_debug.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32wbaxx_nucleo.h"
#include "stm32wbaxx_ll_exti.h"
#include "stm32wbaxx_ll_tim.h"
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

typedef struct{
   uint16_t             R;
   uint16_t             G;
   uint16_t			 B;
}Color_t;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void MX_GPIO_Init(void);
void MX_ICACHE_Init(void);
void MX_RAMCFG_Init(void);
void MX_RTC_Init(void);
void MX_USART1_UART_Init(void);
void MX_CRC_Init(void);
void MX_RNG_Init(void);

/* USER CODE BEGIN EFP */
void Ming_Color(Color_t color);

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define TIM2_CH1_Pin GPIO_PIN_5
#define TIM2_CH1_GPIO_Port GPIOA
#define TIM3_CH1_Pin GPIO_PIN_2
#define TIM3_CH1_GPIO_Port GPIOA
#define TIM17_CH1_Pin GPIO_PIN_1
#define TIM17_CH1_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
