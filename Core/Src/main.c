/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

DAC_HandleTypeDef hdac;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
static void MX_DAC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
float readAdc(){
	HAL_ADC_Start(&hadc);
	if (HAL_ADC_PollForConversion(&hadc, 100) == HAL_OK)
	  {
	    uint32_t value = HAL_ADC_GetValue(&hadc);
	    return (value * VREF) / ADC_RESOLUTION;
	  }

	  return 0;
  }

void writeDac(float voltage){
	uint32_t dac_value;
	float Vref = 3.3f; // Опорное напряжение ЦАП
	uint32_t DAC_Resolution = 4096; // 12-битный ЦАП
	dac_value = (uint32_t)((voltage / Vref) * (DAC_Resolution - 1));
	HAL_DAC_Start(&hdac, DAC_CHANNEL_2);
	HAL_DAC_SetValue(&hdac, DAC_CHANNEL_2, DAC_ALIGN_12B_R, dac_value);
	dac_value = HAL_DAC_GetValue(&hdac, DAC_CHANNEL_2);

}
typedef struct {
    float dacVoltage;
    int ledLevel;
    float corVoltage;
} SignalLevel;

#define NUM 10
// Определение уровней сигнала и соответствующих значений напряжения ЦАП
SignalLevel levels[] = {
    {0.029, 1, 0}, // -20 RSSI
    {0.044, 2, 0}, // -15 RSSI
    {0.075, 3, 0}, // -10 RSSI
    {0.13, 4, 0.13},  // -5 RSSI
    {0.23, 5, 0.1},  // 0 RSSI
    {0.41, 6, 0.1}    // +5 RSSI
};
int levelsCount = sizeof(levels) / sizeof(SignalLevel);

void CheckSignalLevel() {
	int i = levelsCount - 1;

    for (; i>=0; i--) {

        writeDac(levels[i].dacVoltage); // Установка напряжения ЦАП
        HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, 1);
        HAL_Delay(10); // Задержка для стабилизации сигнала
        HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, 0);
        int result = HAL_GPIO_ReadPin(Q1_GPIO_Port, Q1_Pin);
        if (result == 1) {
        	for(int i=0;i<NUM;i++){
        	HAL_Delay(10); // Задержка для стабилизации сигнала

        	if(HAL_GPIO_ReadPin(Q1_GPIO_Port, Q1_Pin))result++;
        	}
             // Установка уровня светодиодов
            if(result>=NUM)break; // Прекращаем цикл, если детектирован соответствующий уровень сигнала
        }
        else{
        	for(int i=0;i<NUM;i++){
        	        	HAL_Delay(10); // Задержка для стабилизации сигнала

        	        	if(!HAL_GPIO_ReadPin(Q1_GPIO_Port, Q1_Pin))result++;
        	        	}
        	             // Установка уровня светодиодов
        	            if(result<NUM-1)break; // Прекращаем цикл, если детектирован соответствующий уровень сигнала
        }
    }
    SetLedsLevel(levels[i].ledLevel);
}

void SetLedsLevel(int level) {
    switch (level) {
        case 1: One_level(); break;
        case 2: Two_level(); break;
        case 3: Three_level(); break;
        case 4: Four_level(); break;
        case 5: Five_level(); break;
        case 6: Six_level(); break;
        default: Zero_level(); // Нет сигнала
    }
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC_Init();
  MX_DAC_Init();
  /* USER CODE BEGIN 2 */


  //  HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, 0);
  HAL_GPIO_WritePin(Enable_GPIO_Port, Enable_Pin, 1);
  HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, 1);HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, 0);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  int leds = 0;
  while(1){
	  CheckSignalLevel();
	  //HAL_Delay(1500);
  }
  while (1)
  {
	  	//HAL_Delay(1500);

	    writeDac(0.41); //-20 0.029; -15 0.044; -10 0.075; -5 0.13; 0 0.23; +5 0.41
	    HAL_Delay(10); // Задержка для стабилизации сигнала
	    float temp = readAdc();
	    if (HAL_GPIO_ReadPin(Q1_GPIO_Port, Q1_Pin)) {
	    	leds++;HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, 1);HAL_GPIO_WritePin(RESET_GPIO_Port, RESET_Pin, 0);
	    	SetLedsLevel(1);
	  	}else {
	  		SetLedsLevel(0);
        }





	    //
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSI14;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSI14State = RCC_HSI14_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.HSI14CalibrationValue = 16;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DIRECTION_FORWARD;
  hadc.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  hadc.Init.LowPowerAutoWait = DISABLE;
  hadc.Init.LowPowerAutoPowerOff = DISABLE;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  hadc.Init.Overrun = ADC_OVR_DATA_PRESERVED;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel to be converted.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_RANK_CHANNEL_NUMBER;
  sConfig.SamplingTime = ADC_SAMPLETIME_1CYCLE_5;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief DAC Initialization Function
  * @param None
  * @retval None
  */
static void MX_DAC_Init(void)
{

  /* USER CODE BEGIN DAC_Init 0 */

  /* USER CODE END DAC_Init 0 */

  DAC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN DAC_Init 1 */

  /* USER CODE END DAC_Init 1 */

  /** DAC Initialization
  */
  hdac.Instance = DAC;
  if (HAL_DAC_Init(&hdac) != HAL_OK)
  {
    Error_Handler();
  }

  /** DAC channel OUT2 config
  */
  sConfig.DAC_Trigger = DAC_TRIGGER_NONE;
  sConfig.DAC_OutputBuffer = DAC_OUTPUTBUFFER_ENABLE;
  if (HAL_DAC_ConfigChannel(&hdac, &sConfig, DAC_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DAC_Init 2 */

  /* USER CODE END DAC_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Enable_GPIO_Port, Enable_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED6_Pin|LED5_Pin|LED4_Pin|LED3_Pin
                          |LED2_Pin|LED1_Pin|RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Enable_Pin */
  GPIO_InitStruct.Pin = Enable_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Enable_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LED6_Pin LED5_Pin LED4_Pin LED3_Pin
                           LED2_Pin LED1_Pin RESET_Pin */
  GPIO_InitStruct.Pin = LED6_Pin|LED5_Pin|LED4_Pin|LED3_Pin
                          |LED2_Pin|LED1_Pin|RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : Q2_Pin Q1_Pin */
  GPIO_InitStruct.Pin = Q2_Pin|Q1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
