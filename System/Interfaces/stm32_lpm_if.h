/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32_lpm_if.h
  * @author  MCD Application Team
  * @brief   Header for stm32_lpm_if.c module (device specific LP management)
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
#ifndef STM32_TINY_LPM_IF_H
#define STM32_TINY_LPM_IF_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_ll_cortex.h"
#include "stm32wbaxx_hal.h"
#include "stm32wbaxx_ll_pwr.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* External variables --------------------------------------------------------*/
/* USER CODE BEGIN EV */

/* USER CODE END EV */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Exported functions prototypes ---------------------------------------------*/
/**
  * @brief Enters Low Power Off Mode
  */
void PWR_EnterOffMode( void );
/**
  * @brief Exits Low Power Off Mode
  */
void PWR_ExitOffMode( void );

/**
  * @brief Enters Low Power Stop Mode
  */
void PWR_EnterStopMode( void );
/**
  * @brief Exits Low Power Stop Mode
  */
void PWR_ExitStopMode( void );

/**
  * @brief Enters Low Power Sleep Mode
  */
void PWR_EnterSleepMode( void );

/**
  * @brief Exits Low Power Sleep Mode
  */
void PWR_ExitSleepMode( void );

/**
  * @brief will restore MCU context if wakeup from standby
  * @note called in startup_stm32wl55xx_cm4.s
  */
uint32_t is_boot_from_standby(void);

/**
  * @brief will save MCU context if before standby entry
  * @note detined in startup_stm32wl55xx_cm4.s
  */
void CPUcontextSave(void);

/**
  * @brief User notification for standby entry
  * @note called from stm32wbaxx_ResetHandler.s
  */
void enter_standby_notification(void);

/**
  * @brief User notification for standby exit
  * @note called from stm32wbaxx_ResetHandler.s
  */
void exit_standby_notification(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

#ifdef __cplusplus
}
#endif

#endif /* STM32_TINY_LPM_IF_H */

