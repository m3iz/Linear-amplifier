/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include "stm32f0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Enable_Pin GPIO_PIN_3
#define Enable_GPIO_Port GPIOA
#define LED6_Pin GPIO_PIN_2
#define LED6_GPIO_Port GPIOB
#define Q2_Pin GPIO_PIN_8
#define Q2_GPIO_Port GPIOA
#define Q1_Pin GPIO_PIN_10
#define Q1_GPIO_Port GPIOA
#define LED5_Pin GPIO_PIN_3
#define LED5_GPIO_Port GPIOB
#define LED4_Pin GPIO_PIN_4
#define LED4_GPIO_Port GPIOB
#define LED3_Pin GPIO_PIN_5
#define LED3_GPIO_Port GPIOB
#define LED2_Pin GPIO_PIN_6
#define LED2_GPIO_Port GPIOB
#define LED1_Pin GPIO_PIN_7
#define LED1_GPIO_Port GPIOB
#define RESET_Pin GPIO_PIN_8
#define RESET_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define ADC_RESOLUTION 4096.0 // 12-битное разрешение
#define VREF 3.3

#define Zero_level() HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 0); HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 0); HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 0); HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 0); HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 0); HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, 0);
#define One_level() HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1); HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 0); HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 0); HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 0); HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 0); HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, 0);
#define Two_level() HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1); HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1); HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 0); HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 0); HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 0); HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, 0);
#define Three_level() HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1); HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1); HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 1); HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 0); HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 0); HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, 0);
#define Four_level() HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1); HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1); HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 1); HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 1); HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 0); HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, 0);
#define Five_level() HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1); HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1); HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 1); HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 1); HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 1); HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, 0);
#define Six_level() HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, 1); HAL_GPIO_WritePin(LED2_GPIO_Port, LED2_Pin, 1); HAL_GPIO_WritePin(LED3_GPIO_Port, LED3_Pin, 1); HAL_GPIO_WritePin(LED4_GPIO_Port, LED4_Pin, 1); HAL_GPIO_WritePin(LED5_GPIO_Port, LED5_Pin, 1); HAL_GPIO_WritePin(LED6_GPIO_Port, LED6_Pin, 1);
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
