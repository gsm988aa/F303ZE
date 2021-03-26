/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
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
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
#include "stdlib.h"

//
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
	HAL_UART_Transmit(&huart2 , (uint8_t *)&ch, 1, 0xFFFF);
	return ch;
}
// char msg[10];

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
// int count=0;
// char msg[10];
__IO uint32_t uhADCxConvertedValue[11];


uint32_t ADC_Value[110];
uint32_t ADC_Value2[70];
uint32_t ADC_Value3[150];
uint32_t ADC_Value4[70];
uint8_t ADC_Convert_Value[20];
uint8_t ADC_Convert_Value2[20];
uint8_t ADC_Convert_Value3[20];
uint8_t ADC_Convert_Value4[20];
uint16_t i;
uint32_t ad1,ad2;
uint32_t  ad3,ad4;
uint32_t ad10,ad5,ad6,ad7,ad8,ad9,ad11;

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
  MX_SPI1_Init();
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_ADC4_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */

//	printf(" \n" );
//	printf("F303 initialized ok\n" );


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1)
	{
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)&ADC_Value, 110);
		for(i = 0,ad1 =0,ad2=0,ad3=0,ad4=0,ad5 =0,ad6=0,ad7=0,ad8=0,ad9 =0,ad10=0,ad11=0; i < 110;)
		{
			ad1 += ADC_Value[i++];
			ad2 += ADC_Value[i++];
			ad3 += ADC_Value[i++];
      ad4 += ADC_Value[i++];
      ad5 += ADC_Value[i++];
      ad6 += ADC_Value[i++];
      ad7 += ADC_Value[i++];
      ad8 += ADC_Value[i++];
      ad9 += ADC_Value[i++];
      ad10 += ADC_Value[i++];
      ad11 += ADC_Value[i++];
    }
    
     ad1 /= 10;
     ad2 /= 10;
     ad3 /= 10;
     ad4 /= 10;
     ad5 /= 10;
     ad6 /= 10;
     ad7 /= 10;
     ad8 /= 10;
     ad9 /= 10;
     ad10 /= 10;
     ad11 /= 10;

//      printf(" info:ADC1_chanel1_value=%ld \r\n", ADC_Value[1]);
//      printf(" info:ADC1_chanel2_value=%ld \r\n", ADC_Value[2]);
//      printf(" info:ADC1_chanel3_value=%ld \r\n", ADC_Value[3]);
//      printf(" info:ADC1_chanel4_value=%ld \r\n", ADC_Value[4]);
//      printf(" info:ADC1_chanel5_value=%ld \r\n", ADC_Value[5]);
//      printf(" info:ADC1_chanel6_value=%ld \r\n", ADC_Value[6]);
//      printf(" info:ADC1_chanel7_value=%ld \r\n", ADC_Value[7]);
//      printf(" info:ADC1_chanel8_value=%ld \r\n", ADC_Value[8]);
//      printf(" info:ADC1_chanel9_value=%ld \r\n", ADC_Value[9]);
//      printf(" info:ADC1_chanel10_value=%ld \r\n", ADC_Value[10]);
//      printf(" info:ADC1_chanel11_value=%ld \r\n", ADC_Value[11]);
    printf(" info:ADC1_chanel1_value=%ld \r\n", ad1);
    printf(" info:ADC1_chanel2_value=%ld \r\n", ad2);
    printf(" info:ADC1_chanel3_value=%ld \r\n", ad3);
    printf(" info:ADC1_chanel4_value=%ld \r\n", ad4);
    printf(" info:ADC1_chanel5_value=%ld \r\n", ad5);
    printf(" info:ADC1_chanel6_value=%ld \r\n", ad6);
    printf(" info:ADC1_chanel7_value=%ld \r\n", ad7);
    printf(" info:ADC1_chanel8_value=%ld \r\n", ad8);
    printf(" info:ADC1_chanel9_value=%ld \r\n", ad9);
    printf(" info:ADC1_chanel10_value=%ld \r\n", ad10);
    printf(" info:ADC1_chanel11_value=%ld \r\n", ad11);
    printf(" info:ADC1V_chanel9_value=%ld \r\n", ADC_Value[9]);
    printf(" info:ADC1V_chanel10_value=%ld \r\n", ADC_Value[10]);
    printf(" info:ADC1V_chanel11_value=%ld \r\n", ADC_Value[11]);
    printf(" info:ADC1V_chanel0_value=%ld \r\n", ADC_Value[0]);
		HAL_Delay(50);
	}
		// 	printf("\n");
		// }

		// printf(" info:ADC1_chanel1_value=%ld \r\n", ad1);
		// printf(" info:ADC1_chanel2_value=%ld \r\n", ad2);
		// printf("\n");


	  		// ADC_Convert_Value[1]=(ad1>>8) & 0x0f;//high
	    // 	ADC_Convert_Value[0]=ad1&0xff; //low

	  		// ADC_Convert_Value[3]=(ad2>>8) & 0x0f;//high
	    // 	ADC_Convert_Value[2]=ad2&0xff; //low
	    	// HAL_SPI_Transmit_DMA (&hspi1, ADC_Convert_Value, 10);


//	  		ADC_Convert_Value[5]=(ad3>>8) & 0x0f;//high
//	    	ADC_Convert_Value[4]=ad3&0xff; //low
//
//	  		ADC_Convert_Value[7]=(ad4>>8) & 0x0f;//high
//	    	ADC_Convert_Value[6]=ad4&0xff; //low
//
//	  		ADC_Convert_Value[9]=(ad5>>8) & 0x0f;//high
//	    	ADC_Convert_Value[8]=ad5&0xff; //low
//
//	  		ADC_Convert_Value[11]=(ad6>>8) & 0x0f;//high
//	    	ADC_Convert_Value[10]=ad6&0xff; //low
//
//	  		ADC_Convert_Value[13]=(ad7>>8) & 0x0f;//high
//	    	ADC_Convert_Value[12]=ad7&0xff; //low
//
//	  		ADC_Convert_Value[15]=(ad8>>8) & 0x0f;//high
//	    	ADC_Convert_Value[14]=ad8&0xff; //low
//
//	  		ADC_Convert_Value[17]=(ad9>>8) & 0x0f;//high
//	    	ADC_Convert_Value[16]=ad9&0xff; //low
//
//	  		ADC_Convert_Value[19]=(ad10>>8) & 0x0f;//high
//	    	ADC_Convert_Value[18]=ad10&0xff; //low

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL2;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART2|RCC_PERIPHCLK_ADC12
                              |RCC_PERIPHCLK_ADC34;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  PeriphClkInit.Adc12ClockSelection = RCC_ADC12PLLCLK_DIV1;
  PeriphClkInit.Adc34ClockSelection = RCC_ADC34PLLCLK_DIV1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
