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
//  uint8_t msg[] = "Starting VGA...\n";
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  // Reset line_rx buffer
  int i;
  for(i = 0; i < LINE_BUFLEN; i++)
	  input.line_rx_buffer[i] = 0;

  for(i = 0; i < 1024; i++)
	  container[i] = 0;
  temp = 0;

  // Reset some stuff
  input.byte_buffer_rx[0] = 0;
  input.char_counter = 0;
  input.command_execute_flag = False;

  UB_VGA_Screen_Init(); // Init VGA-Screen

  UB_VGA_FillScreen(VGA_COL_WHITE);
  UB_VGA_SetPixel(10,10,10);
  UB_VGA_SetPixel(0,0,0x00);
  UB_VGA_SetPixel(319,0,0x00);

  HAL_UART_Receive_IT(&huart2, input.byte_buffer_rx, BYTE_BUFLEN);
//  HAL_UART_Transmit(&huart2, msg, (uint16_t)sizeof(msg), HAL_MAX_DELAY);
  int error = NO_ERROR;
  global_debug = False;

//  IO_draw_circle(VGA_DISPLAY_X/2, VGA_DISPLAY_Y/2, VGA_DISPLAY_X/3, VGA_COL_BLACK);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(input.command_execute_flag == True)
	  {
//		  global_debug_check();
		  global_debug = 1;
//		  Debug_Tx("HMM");
//		  HAL_GPIO_WritePin(GPIOB, TIMING_GPIO_Pin, GPIO_PIN_RESET);
		  input.command_execute_flag = False;
		  UB_VGA_SetPixel(10,10,VGA_COL_GREEN);
		  error = FL_uart_decode();
		  memset(&command,0,sizeof(command));
		  Debug_Tx("hmm\0\n");
		  if(error)
		  {
			  Debug_INT(error);
			  Global_Error_handler(error);
		  }
		  printf("Error code:\t%d\n",error);
//		  HAL_UART_Transmit(&huart2, msg, sizeof(msg), HAL_MAX_DELAY);
	  }

	  //HELPHELP CHECK OF HET WERKT

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

void Global_Error_handler(int error)
{
	printf("\n\nENCOUNTERRED AN ERROR!\n");
	printf("Error code:\t%d\n",error);
	switch(error)
	{
	case FL_INIT_ERROR: 					printf("\nERROR:\tFL_INIT_ERROR\n"); break;
	case FL_INVALID_FUNCTION_NO: 			printf("\nERROR:\tFL_INVALID_FUNCTION_NO\n");  break;
	case FL_SWITCH_INVALID_FUNCTION_NO: 	printf("\nERROR:\tFL_SWITCH_INVALID_FUNCTION_NO\n");  break;
	case FL_INVALID_ARGUMENTS: 				printf("\nERROR:\tFL_INVALID_ARGUMENTS\n");  break;
	case FL_TOO_MANY_ARGS: 					printf("\nERROR:\tFL_TOO_MANY_ARGS\n");  break;
	case FL_EMPTY_ARGUMENT: 				printf("\nERROR:\tFL_EMPTY_ARGUMENT\n");  break;
	case LL_NOT_A_SUPPORTED_FUNCTION: 		printf("\nERROR:\tLL_NOT_A_SUPPORTED_FUNCTION\n");  break;
	case IOL_LINE_INVALID_ARG_VALUE: 		printf("\nERROR:\tIOL_LINE_INVALID_ARG_VALUE\n");  break;
	default: 								printf("\nERROR:\tNo Error\n"); break;
	}
}

void Error_Tx(char  *pErrorMessage)
{
//	for(int i = 0; i <= strlen(pErrorMessage); i++)
//				printf("%c", pErrorMessage[i]);
}

void Debug_Tx( char *pDebugMessage)
{
//	if(global_debug)
//	{
//		for(int i = 0; i <= strlen(pDebugMessage); i++)
//			printf("%c", pDebugMessage[i]);
//	}

	HAL_UART_Transmit(&huart2, (uint8_t*)pDebugMessage, strlen(pDebugMessage), HAL_MAX_DELAY);
}

void Debug_INT(int num)
{
//	if(global_debug)
//		printf("%d",num);
}


void global_debug_check()
{
//	Debug_Tx("Toggling Debugging\n");
//	if(	(input.line_rx_buffer[0] == 'd') && (input.line_rx_buffer[1] == 'e') && (input.line_rx_buffer[2] == 'b'))
//	{
//		printf("Global debug voor: %d\n", global_debug);
//		global_debug = True;
//		printf("Global debug na: %d\n", global_debug);
////		global_debug = !global_debug;
//
////		global_debug = True
//
//	}

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
