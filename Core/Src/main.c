/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f4xx_hal.h"
//#include "FL.h"

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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

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
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  // Reset line_rx buffer

  FL_Init();

  UB_VGA_Screen_Init(); // Init VGA-Screen

  UB_VGA_FillScreen(VGA_COL_WHITE);
  UB_VGA_SetPixel(10,10,10);
  UB_VGA_SetPixel(0,0,0x00);
  UB_VGA_SetPixel(319,0,0x00);

  HAL_UART_Receive_IT(&huart2, input.byte_buffer_rx, BYTE_BUFLEN);

  int diff = 0;
   global_debug = False;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  // Check if a Command was received or if there are still function to be decoded
	  if((input.command_execute_flag == True) || (waitCheck == True))
	  {
		// Check if Debug is to be toggled
		global_debug_check();

		Debug_Tx("Going to decode, main.c line 130\n");

		// Debug information, Print the whole received command
		Debug_String_tx(rb[rb_vars.read_counter].line_rx_buffer, rb[rb_vars.read_counter].msglen);

		diff = rb_vars.write_counter - rb_vars.read_counter;

		printf("\n\nWrite counter:\t%d\n", rb_vars.write_counter);
		printf("read_counter:\t%d\n", rb_vars.read_counter);
		printf("diff:\t%d\n\n", diff);

		// There are functions that were buffered and need to be processed
		if(diff != 1)
		{
			Debug_Tx("Diff != 1\n");
			Debug_Tx("Entering the while loop...\n");

			/*
			 * -1 because there is no command at write_counter.
			 * The next command will be written to write_counter in the next interrupt
			 */
			while(rb_vars.read_counter <= rb_vars.write_counter-1)
			{
				printf("Going to makeup the difference\n");
				printf("Line to be decoded:\n");
				printf("\t");
				Debug_String_tx(rb[rb_vars.read_counter].line_rx_buffer, rb[rb_vars.read_counter].msglen);
				printf("\n\n");

				Debug_Tx("Going to Decode...\n");
				FL_uart_decode(rb[rb_vars.read_counter].line_rx_buffer, rb[rb_vars.read_counter].msglen);
				Debug_Tx("Done decoding, back in main.c\n");
				printf("Done decoding\n");
				rb_vars.read_counter++;
			}
			printf("\n\nMade up the difference\n\n");
			// There are no more functions to be decoded
			waitCheck = False;

		}
		else {
			Debug_Tx("Diff == 1\n");
			Debug_Tx("Going to Decode...\n");
			FL_uart_decode(rb[rb_vars.read_counter].line_rx_buffer, rb[rb_vars.read_counter].msglen);
			rb_vars.read_counter++;
			Debug_Tx("Done decoding, back in main.c\n");
			printf("\n\nWrite counter:\t%d\n", rb_vars.write_counter);
			printf("read_counter:\t%d\n", rb_vars.read_counter);
			printf("diff:\t%d\n\n", diff);
		}
		Debug_Tx("Resetting the execute flag\n");
		input.command_execute_flag = False;


		UB_VGA_SetPixel(10,10,VGA_COL_GREEN);
//		  FL_uart_decode();
	  }



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

  /** Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void Error_Tx(char *pErrorMessage)
{
//	unsigned char hmm[128];
//	HAL_UART_Transmit(&huart2, (uint8_t *)pErrorMessage, sizeof(pErrorMessage), HAL_MAX_DELAY);
	HAL_UART_Transmit(&huart2, pErrorMessage, strlen(pErrorMessage), HAL_MAX_DELAY);
}

void Debug_Tx(char *pDebugMessage)
{
	if(global_debug)
//		Debug_String_tx(pDebugMessage, strlen(*pDebugMessage));
//		printf("%s\n", pDebugMessage);
		HAL_UART_Transmit(&huart2, pDebugMessage, strlen(pDebugMessage), HAL_MAX_DELAY);
}

void Debug_String_tx(uint8_t pDebugMessage[], uint16_t msglen)
{
//	for(int i = 0; i <= strlen(pDebugMessage); i++)
	for(int i = 0; i <= msglen; i++)
		printf("%c", pDebugMessage[i]);
	printf("\n");
}

void global_debug_check()
{
	if(	(rb[rb_vars.read_counter].line_rx_buffer[0] == 'd') &&
		(rb[rb_vars.read_counter].line_rx_buffer[1] == 'e') &&
		(rb[rb_vars.read_counter].line_rx_buffer[2] == 'b'))
	{
		global_debug = !global_debug;
		Debug_Tx("Toggling Debugging\n");
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
