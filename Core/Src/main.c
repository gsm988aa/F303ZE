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

#define CS_Pin GPIO_PIN_10
#define CS_GPIO_Port GPIOC
//#define CS_EXTI_IRQn EXTI4_IRQn

    int flag;
#ifdef __GNUC__
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif
PUTCHAR_PROTOTYPE
{
  HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 0xFFFF);
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



/* Private variables ---------------------------------------------------------*/
/* SPI handler declaration */
//SPI_HandleTypeDef SpiHandle;

/* Buffer used for transmission */
uint8_t aTxBuffer[84];
#define COUNTOF(__BUFFER__)   (sizeof(__BUFFER__) / sizeof(*(__BUFFER__)))
#define BUFFERSIZE                       (COUNTOF(aTxBuffer) - 1)
/* Buffer used for reception */
uint8_t aRxBuffer[83];





__IO uint32_t uhADCxConvertedValue[11];

uint32_t ADC1_Value[110];
uint32_t ADC2_Value[70];
uint32_t ADC3_Value[150];
uint32_t ADC4_Value[70];
// uint8_t ADC_Convert_Value[20];
// uint8_t ADC_Convert_Value2[20];
// uint8_t ADC_Convert_Value3[20];
// uint8_t ADC_Convert_Value4[20];
uint16_t i, j;
uint32_t ADC1Channel1, ADC1Channel2, ADC1Channel3, ADC1Channel4, ADC1Channel5, ADC1Channel6, ADC1Channel7, ADC1Channel8, ADC1Channel9, ADC1Channel10, ADC1Channel11;

uint32_t ADC2Channel1, ADC2Channel2, ADC2Channel3, ADC2Channel4, ADC2Channel5, ADC2Channel6, ADC2Channel7;

uint32_t ADC3Channel1, ADC3Channel2, ADC3Channel3, ADC3Channel4, ADC3Channel5, ADC3Channel6, ADC3Channel7, ADC3Channel8, ADC3Channel9, ADC3Channel10, ADC3Channel11, ADC3Channel12, ADC3Channel13, ADC3Channel14, ADC3Channel15;

uint32_t ADC4Channel1, ADC4Channel2, ADC4Channel3, ADC4Channel4, ADC4Channel5, ADC4Channel6, ADC4Channel7;

uint16_t ADCsum_Value[41],midvalue; //all 40 Channels
uint8_t ADCconvert_Value[82]; // for DMA SPI Transmitt

// choose a MCU-Header    "1101" = 1-Slave,  1-board number, 0-nothing, 1-device_id
uint16_t Slaveboard1_dev_id1 = 1101;
//uint32_t Slaveboard1_dev_id2 = 1102;
//uint32_t Slaveboard1_dev_id3 = 1103;
//uint32_t Slaveboard1_dev_id4 = 1104;
//uint32_t Slaveboard1_dev_id5 = 1105;

//uint32_t Slaveboard2_dev_id1 = 1201;
//uint32_t Slaveboard2_dev_id2 = 1202;
//uint32_t Slaveboard2_dev_id3 = 1203;
//uint32_t Slaveboard2_dev_id4 = 1204;
//uint32_t Slaveboard2_dev_id5 = 1205;

//uint32_t Slaveboard3_dev_id1 = 1301;
//uint32_t Slaveboard3_dev_id2 = 1302;
//uint32_t Slaveboard3_dev_id3 = 1303;
//uint32_t Slaveboard3_dev_id4 = 1304;
//uint32_t Slaveboard3_dev_id5 = 1305;

//uint32_t Slaveboard4_dev_id1 = 1401;
//uint32_t Slaveboard4_dev_id2 = 1402;
//uint32_t Slaveboard4_dev_id3 = 1403;
//uint32_t Slaveboard4_dev_id4 = 1404;
//uint32_t Slaveboard4_dev_id5 = 1405;

//uint32_t Slaveboard5_dev_id1 = 1501;
//uint32_t Slaveboard5_dev_id2 = 1502;
//uint32_t Slaveboard5_dev_id3 = 1503;
//uint32_t Slaveboard5_dev_id4 = 1504;
//uint32_t Slaveboard5_dev_id5 = 1505;


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
  MX_ADC1_Init();
  MX_ADC2_Init();
  MX_ADC3_Init();
  MX_ADC4_Init();
  MX_USART2_UART_Init();
  MX_SPI3_Init();
  /* USER CODE BEGIN 2 */

//
//  if(HAL_SPI_Init(&hspi3) != HAL_OK)
//  {
//    /* Initialization Error */
//    Error_Handler();
//  }
//
//
//  /*##-2- Start the Full Duplex Communication process ########################*/
//  /* While the SPI in TransmitReceive process, user can transmit data through
//     "aTxBuffer" buffer & receive data through "aRxBuffer" */
//  if(HAL_SPI_TransmitReceive_DMA(&hspi3, (uint8_t*)aTxBuffer, (uint8_t *)aRxBuffer, BUFFERSIZE) != HAL_OK)
//  {
//    /* Transfer error in transmission process */
//    Error_Handler();
//  }
//
//
//  /*##-3- Wait for the end of the transfer ###################################*/
//  /*  Before starting a new communication transfer, you need to check the current
//      state of the peripheral; if it�s busy you need to wait for the end of current
//      transfer before starting a new one.
//      For simplicity reasons, this example is just waiting till the end of the
//      transfer, but application may perform other tasks while transfer operation
//      is ongoing. */
//  while (HAL_SPI_GetState(&hspi3) != HAL_SPI_STATE_READY)
//  {
//  }
//
//  /*##-4- Compare the sent and received buffers ##############################*/
//  if(Buffercmp((uint8_t*)aTxBuffer, (uint8_t*)aRxBuffer, BUFFERSIZE))
//  {
//    /* Transfer error in transmission process */
//    Error_Handler();
//  }
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    HAL_ADC_Start_DMA(&hadc1, (uint32_t *)&ADC1_Value, 110);
    for (i = 0, ADC1Channel1 = 0, ADC1Channel2 = 0, ADC1Channel3 = 0, ADC1Channel4 = 0, ADC1Channel5 = 0, ADC1Channel6 = 0, ADC1Channel7 = 0, ADC1Channel8 = 0, ADC1Channel9 = 0, ADC1Channel10 = 0, ADC1Channel11 = 0; i < 110;)
    {
      ADC1Channel1 += ADC1_Value[i++];
      ADC1Channel2 += ADC1_Value[i++];
      ADC1Channel3 += ADC1_Value[i++];
      ADC1Channel4 += ADC1_Value[i++];
      ADC1Channel5 += ADC1_Value[i++];
      ADC1Channel6 += ADC1_Value[i++];
      ADC1Channel7 += ADC1_Value[i++];
      ADC1Channel8 += ADC1_Value[i++];
      ADC1Channel9 += ADC1_Value[i++];
      ADC1Channel10 += ADC1_Value[i++];
      ADC1Channel11 += ADC1_Value[i++];
    }
    ADC1Channel1 /= 10;
    ADC1Channel2 /= 10;
    ADC1Channel3 /= 10;
    ADC1Channel4 /= 10;
    ADC1Channel5 /= 10;
    ADC1Channel6 /= 10;
    ADC1Channel7 /= 10;
    ADC1Channel8 /= 10;
    ADC1Channel9 /= 10;
    ADC1Channel10 /= 10;
    ADC1Channel11 /= 10;
    HAL_Delay(50);
    // 11 7  15  7
    HAL_ADC_Start_DMA(&hadc2, (uint32_t *)&ADC2_Value, 70);
    for (i = 0, ADC2Channel1 = 0, ADC2Channel2 = 0, ADC2Channel3 = 0, ADC2Channel4 = 0, ADC2Channel5 = 0, ADC2Channel6 = 0, ADC2Channel7 = 0; i < 70;)
    {
      ADC2Channel1 += ADC2_Value[i++];
      ADC2Channel2 += ADC2_Value[i++];
      ADC2Channel3 += ADC2_Value[i++];
      ADC2Channel4 += ADC2_Value[i++];
      ADC2Channel5 += ADC2_Value[i++];
      ADC2Channel6 += ADC2_Value[i++];
      ADC2Channel7 += ADC2_Value[i++];
    }
    ADC2Channel1 /= 10;
    ADC2Channel2 /= 10;
    ADC2Channel3 /= 10;
    ADC2Channel4 /= 10;
    ADC2Channel5 /= 10;
    ADC2Channel6 /= 10;
    ADC2Channel7 /= 10;
    HAL_Delay(50);
    HAL_ADC_Start_DMA(&hadc3, (uint32_t *)&ADC3_Value, 150);
    for (i = 0, ADC3Channel1 = 0, ADC3Channel2 = 0, ADC3Channel3 = 0, ADC3Channel4 = 0, ADC3Channel5 = 0, ADC3Channel6 = 0, ADC3Channel7 = 0, ADC3Channel8 = 0, ADC3Channel9 = 0, ADC3Channel10 = 0, ADC3Channel11 = 0, ADC3Channel12 = 0, ADC3Channel13 = 0, ADC3Channel14 = 0, ADC3Channel15 = 0; i < 150;)
    {
      ADC3Channel1 += ADC3_Value[i++];
      ADC3Channel2 += ADC3_Value[i++];
      ADC3Channel3 += ADC3_Value[i++];
      ADC3Channel4 += ADC3_Value[i++];
      ADC3Channel5 += ADC3_Value[i++];
      ADC3Channel6 += ADC3_Value[i++];
      ADC3Channel7 += ADC3_Value[i++];
      ADC3Channel8 += ADC3_Value[i++];
      ADC3Channel9 += ADC3_Value[i++];
      ADC3Channel10 += ADC3_Value[i++];
      ADC3Channel11 += ADC3_Value[i++];
      ADC3Channel12 += ADC3_Value[i++];
      ADC3Channel13 += ADC3_Value[i++];
      ADC3Channel14 += ADC3_Value[i++];
      ADC3Channel15 += ADC3_Value[i++];
    }
    ADC3Channel1 /= 10;
    ADC3Channel2 /= 10;
    ADC3Channel3 /= 10;
    ADC3Channel4 /= 10;
    ADC3Channel5 /= 10;
    ADC3Channel6 /= 10;
    ADC3Channel7 /= 10;
    ADC3Channel8 /= 10;
    ADC3Channel9 /= 10;
    ADC3Channel10 /= 10;
    ADC3Channel11 /= 10;
    ADC3Channel12 /= 10;
    ADC3Channel13 /= 10;
    ADC3Channel14 /= 10;
    ADC3Channel15 /= 10;
    HAL_Delay(50);
    HAL_ADC_Start_DMA(&hadc4, (uint32_t *)&ADC4_Value, 70);
    for (i = 0, ADC4Channel1 = 0, ADC4Channel2 = 0, ADC4Channel3 = 0, ADC4Channel4 = 0, ADC4Channel5 = 0, ADC4Channel6 = 0, ADC4Channel7 = 0; i < 70;)
    {
      ADC4Channel1 += ADC4_Value[i++];
      ADC4Channel2 += ADC4_Value[i++];
      ADC4Channel3 += ADC4_Value[i++];
      ADC4Channel4 += ADC4_Value[i++];
      ADC4Channel5 += ADC4_Value[i++];
      ADC4Channel6 += ADC4_Value[i++];
      ADC4Channel7 += ADC4_Value[i++];
    }
    ADC4Channel1 /= 10;
    ADC4Channel2 /= 10;
    ADC4Channel3 /= 10;
    ADC4Channel4 /= 10;
    ADC4Channel5 /= 10;
    ADC4Channel6 /= 10;
    ADC4Channel7 /= 10;
    HAL_Delay(50);

    ADCsum_Value[0] = Slaveboard1_dev_id1;
    //     	ADCsum_Value[0]=Slaveboard1_dev_id2;
    //     	ADCsum_Value[0]=Slaveboard1_dev_id3;
    //     	ADCsum_Value[0]=Slaveboard1_dev_id4;
    //     	ADCsum_Value[0]=Slaveboard1_dev_id5;

    //     	ADCsum_Value[0]=Slaveboard2_dev_id1;
    //     	ADCsum_Value[0]=Slaveboard2_dev_id2;
    //     	ADCsum_Value[0]=Slaveboard2_dev_id3;
    //     	ADCsum_Value[0]=Slaveboard2_dev_id4;
    //     	ADCsum_Value[0]=Slaveboard2_dev_id5;

    //    	ADCsum_Value[0]=Slaveboard3_dev_id1;
    //     	ADCsum_Value[0]=Slaveboard3_dev_id2;
    //     	ADCsum_Value[0]=Slaveboard3_dev_id3;
    //     	ADCsum_Value[0]=Slaveboard3_dev_id4;
    //     	ADCsum_Value[0]=Slaveboard3_dev_id5;

    //    	ADCsum_Value[0]=Slaveboard4_dev_id1;
    //     	ADCsum_Value[0]=Slaveboard4_dev_id2;
    //     	ADCsum_Value[0]=Slaveboard4_dev_id3;
    //     	ADCsum_Value[0]=Slaveboard4_dev_id4;
    //     	ADCsum_Value[0]=Slaveboard4_dev_id5;

    //    	ADCsum_Value[0]=Slaveboard5_dev_id1;
    //     	ADCsum_Value[0]=Slaveboard5_dev_id2;
    //     	ADCsum_Value[0]=Slaveboard5_dev_id3;
    //     	ADCsum_Value[0]=Slaveboard5_dev_id4;
    //     	ADCsum_Value[0]=Slaveboard5_dev_id5;

    //       ADCsum_Value = {Slaveboard_id,ADC1Channel1,ADC1Channel2,ADC1Channel3,ADC1Channel4,ADC1Channel10,ADC1Channel5,ADC1Channel6,ADC1Channel7,
    //     	 ADC1Channel8,ADC1Channel9,ADC1Channel11,ADC2Channel1,ADC2Channel2,ADC2Channel3,ADC2Channel4,ADC2Channel10,ADC2Channel5,ADC2Channel6,ADC2Channel7,
    //     	 ADC3Channel1,ADC3Channel2,ADC3Channel3,ADC3Channel4,ADC3Channel10,ADC3Channel5,ADC3Channel6,ADC3Channel7,ADC3Channel8,ADC3Channel9,ADC3Channel11,ADC3Channel12,ADC3Channel13,ADC3Channel14,ADC3Channel15,
    //     	 ADC4Channel1,ADC4Channel2,ADC4Channel3,ADC4Channel4,ADC4Channel10,ADC4Channel5,ADC4Channel6,ADC4Channel7};


    ADCsum_Value[1] = ADC1Channel1;
    ADCsum_Value[2] = ADC1Channel2;
    ADCsum_Value[3] = ADC1Channel3;
    ADCsum_Value[4] = ADC1Channel4;
    ADCsum_Value[5] = ADC1Channel5;
    ADCsum_Value[6] = ADC1Channel6;
    ADCsum_Value[7] = ADC1Channel7;
    ADCsum_Value[8] = ADC1Channel8;
    ADCsum_Value[9] = ADC1Channel9;
    ADCsum_Value[10] = ADC1Channel10;
    ADCsum_Value[11] = ADC1Channel11;

    ADCsum_Value[12] = ADC2Channel1;
    ADCsum_Value[13] = ADC2Channel2;
    ADCsum_Value[14] = ADC2Channel3;
    ADCsum_Value[15] = ADC2Channel4;
    ADCsum_Value[16] = ADC2Channel5;
    ADCsum_Value[17] = ADC2Channel6;
    ADCsum_Value[18] = ADC2Channel7;

    ADCsum_Value[19] = ADC3Channel1;
    ADCsum_Value[20] = ADC3Channel2;
    ADCsum_Value[21] = ADC3Channel3;
    ADCsum_Value[22] = ADC3Channel4;
    ADCsum_Value[23] = ADC3Channel5;
    ADCsum_Value[24] = ADC3Channel6;
    ADCsum_Value[25] = ADC3Channel7;
    ADCsum_Value[26] = ADC3Channel8;
    ADCsum_Value[27] = ADC3Channel9;
    ADCsum_Value[28] = ADC3Channel10;
    ADCsum_Value[29] = ADC3Channel11;
    ADCsum_Value[30] = ADC3Channel12;
    ADCsum_Value[31] = ADC3Channel13;
    ADCsum_Value[32] = ADC3Channel14;
    ADCsum_Value[33] = ADC3Channel15;

    ADCsum_Value[34] = ADC4Channel1;
    ADCsum_Value[35] = ADC4Channel2;
    ADCsum_Value[36] = ADC4Channel3;
    ADCsum_Value[37] = ADC4Channel4;
    ADCsum_Value[38] = ADC4Channel5;
    ADCsum_Value[39] = ADC4Channel6;
    ADCsum_Value[40] = ADC4Channel7;

//    HAL_SPI_Transmit_DMA(&hspi3, (uint16_t *)ADCsum_Value, 41);

 //	ADCsum_Value change to transmit  ADCconvert_Value[82];
//    for (i = 1; i < 41; i++)
//    {
//      midvalue=ADCsum_Value[i];
//      ADCconvert_Value[2*i+1] = (ADCsum_Value[i] >> 8) & 0x0f; //high 8bit
//      ADCconvert_Value[2*i] = midvalue & 0xff;            //low 8bit
//    }
    midvalue=Slaveboard1_dev_id1;
    ADCconvert_Value[0] = Slaveboard1_dev_id1 & 0xff;
    ADCconvert_Value[1] = (midvalue >> 8) & 0x0f;
    HAL_Delay(3);


    midvalue=ADCsum_Value[1];

    ADCconvert_Value[2] = ADCsum_Value[1] & 0xff;

    ADCconvert_Value[3] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[2];

    ADCconvert_Value[4] = ADCsum_Value[2] & 0xff;

    ADCconvert_Value[5] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[3];

    ADCconvert_Value[6] = ADCsum_Value[3] & 0xff;

    ADCconvert_Value[7] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[4];

    ADCconvert_Value[8] = ADCsum_Value[4] & 0xff;

    ADCconvert_Value[9] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[5];

    ADCconvert_Value[10] = ADCsum_Value[5] & 0xff;

    ADCconvert_Value[11] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[6];

    ADCconvert_Value[12] = ADCsum_Value[6] & 0xff;

    ADCconvert_Value[13] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[7];

    ADCconvert_Value[14] = ADCsum_Value[7] & 0xff;

    ADCconvert_Value[15] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[8];

    ADCconvert_Value[16] = ADCsum_Value[8] & 0xff;

    ADCconvert_Value[17] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[9];

    ADCconvert_Value[18] = ADCsum_Value[9] & 0xff;

    ADCconvert_Value[19] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[10];

    ADCconvert_Value[20] = ADCsum_Value[10] & 0xff;

    ADCconvert_Value[21] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[11];

    ADCconvert_Value[22] = ADCsum_Value[11] & 0xff;

    ADCconvert_Value[23] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[12];

    ADCconvert_Value[24] = ADCsum_Value[12] & 0xff;

    ADCconvert_Value[25] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[13];

    ADCconvert_Value[26] = ADCsum_Value[13] & 0xff;

    ADCconvert_Value[27] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[14];

    ADCconvert_Value[28] = ADCsum_Value[14] & 0xff;

    ADCconvert_Value[29] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[15];

    ADCconvert_Value[30] = ADCsum_Value[15] & 0xff;

    ADCconvert_Value[31] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[16];

    ADCconvert_Value[32] = ADCsum_Value[16] & 0xff;

    ADCconvert_Value[33] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[17];

    ADCconvert_Value[34] = ADCsum_Value[17] & 0xff;

    ADCconvert_Value[35] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[18];

    ADCconvert_Value[36] = ADCsum_Value[18] & 0xff;

    ADCconvert_Value[37] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[19];

    ADCconvert_Value[38] = ADCsum_Value[19] & 0xff;

    ADCconvert_Value[39] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[20];

    ADCconvert_Value[40] = ADCsum_Value[20] & 0xff;

    ADCconvert_Value[41] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[21];

    ADCconvert_Value[42] = ADCsum_Value[21] & 0xff;

    ADCconvert_Value[43] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[22];

    ADCconvert_Value[44] = ADCsum_Value[22] & 0xff;

    ADCconvert_Value[45] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[23];

    ADCconvert_Value[46] = ADCsum_Value[23] & 0xff;

    ADCconvert_Value[47] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[24];

    ADCconvert_Value[48] = ADCsum_Value[24] & 0xff;

    ADCconvert_Value[49] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[25];

    ADCconvert_Value[50] = ADCsum_Value[25] & 0xff;

    ADCconvert_Value[51] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[26];

    ADCconvert_Value[52] = ADCsum_Value[26] & 0xff;

    ADCconvert_Value[53] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[27];

    ADCconvert_Value[54] = ADCsum_Value[27] & 0xff;

    ADCconvert_Value[55] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[28];

    ADCconvert_Value[56] = ADCsum_Value[28] & 0xff;

    ADCconvert_Value[57] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[29];

    ADCconvert_Value[58] = ADCsum_Value[29] & 0xff;

    ADCconvert_Value[59] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[30];

    ADCconvert_Value[60] = ADCsum_Value[30] & 0xff;

    ADCconvert_Value[61] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[31];

    ADCconvert_Value[62] = ADCsum_Value[31] & 0xff;

    ADCconvert_Value[63] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[32];

    ADCconvert_Value[64] = ADCsum_Value[32] & 0xff;

    ADCconvert_Value[65] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[33];

    ADCconvert_Value[66] = ADCsum_Value[33] & 0xff;

    ADCconvert_Value[67] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[34];

    ADCconvert_Value[68] = ADCsum_Value[34] & 0xff;

    ADCconvert_Value[69] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[35];

    ADCconvert_Value[70] = ADCsum_Value[35] & 0xff;

    ADCconvert_Value[71] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[36];

    ADCconvert_Value[72] = ADCsum_Value[36] & 0xff;

    ADCconvert_Value[73] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[37];

    ADCconvert_Value[74] = ADCsum_Value[37] & 0xff;

    ADCconvert_Value[75] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[38];

    ADCconvert_Value[76] = ADCsum_Value[38] & 0xff;

    ADCconvert_Value[77] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[39];

    ADCconvert_Value[78] = ADCsum_Value[39] & 0xff;

    ADCconvert_Value[79] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);

    midvalue=ADCsum_Value[40];

    ADCconvert_Value[80] = ADCsum_Value[40] & 0xff;

    ADCconvert_Value[81] = (midvalue >> 8) & 0x0f;

    HAL_Delay(3);


//    HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10,  GPIO_PIN_RESET);
    HAL_SPI_Transmit_DMA(&hspi3, (uint8_t *)ADCconvert_Value, sizeof((uint8_t *)ADCconvert_Value));
//    		HAL_GPIO_WritePin(SPI1_NSS_GPIO_Port, SPI1_NSS_Pin, GPIO_PIN_SET);
    		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_SET);
    		HAL_Delay(500);
//
//    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10,  GPIO_PIN_SET);
//     HAL_SPI_TransmitReceive(&hspi3, (uint8_t *)ADCconvert_Value,(uint8_t *)ADCconvert_Value,sizeof((uint8_t *)ADCconvert_Value),0xFF);
//   HAL_GPIO_WritePin(GPIOC, GPIO_PIN_10, GPIO_PIN_RESET);
//    HAL_Delay(1000);
//    HAL_SPI_Transmit_DMA(&hspi3, ADCconvert_Value, 82);, HAL_MAX_DELAY




    //    printf("init ok2");
//    HAL_Delay(400);

//			  HAL_SPI_Transmit(&hspi3, ADCconvert_Value, 1, 100);

    //debug ADCconvert_Value
//    for (j = 0; j < 82; j++)
//    {
//      printf("ADCconvert_Value[%d] = %d \r\n", j, ADCconvert_Value[j]);
//      HAL_Delay(10);
//    }
  }
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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
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
//void HAL_SPI_ErrorCallback(SPI_HandleTypeDef *hspi)
//{
// /* Turn LED5 on: Transfer error in reception/transmission process */
//// BSP_LED_On(LED5);
//	;
//}
//
///**
// * @brief  Compares two buffers.
// * @param  pBuffer1, pBuffer2: buffers to be compared.
// * @param  BufferLength: buffer's length
// * @retval 0  : pBuffer1 identical to pBuffer2
// *         >0 : pBuffer1 differs from pBuffer2
// */
//static uint16_t Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength)
//{
// while (BufferLength--)
// {
//   if((*pBuffer1) != *pBuffer2)
//   {
//     return BufferLength;
//   }
//   pBuffer1++;
//   pBuffer2++;
// }
//
// return 0;
//}
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
