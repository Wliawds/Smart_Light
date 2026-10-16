/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
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
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "AdjustLight.h"
#include "stdio.h"
#include "Bright_ADC.h"
#include "KEY.h"
#include "Node_ADC.h"
#include "TFT.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint16_t KEY1_flag=0;
uint16_t KEY2_flag=0;
uint16_t KEY3_flag=0;
volatile uint16_t lasttime1=0;
volatile uint16_t lasttime2=0;
volatile uint16_t lasttime3=0;

volatile double a=0;
volatile double b=0;
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
  MX_TIM3_Init();
  MX_ADC1_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	AdjustLight_Init();

	LCD_Init();
  LCD_Clear(BLACK);

  /* 测试：刷全屏红色，能刷红说明 SPI 通了 */
  LCD_Init();
  /* 第二步：显示字符 */
  LCD_Clear(BLACK);
  LCD_ShowString(40,  20, "Hello tft!", YELLOW);
//  LCD_ShowString(40,  60, "1.54 inch", CYAN);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		KEY3_flag=KEY1_flag%3;
		switch(KEY3_flag)
		{
			case 0:    //按键
				 AdjustKey_ON_OFF(KEY2_flag);
			   LCD_ShowString(40,  60, "key_adjust", CYAN);
			break;
			
			case 1:    //光敏电阻
			   a=Bright_ADC();
			   Bright_ADC_Adjust(a);
			   LCD_ShowString(40,  60, "photoSensitive_adjust", CYAN);
      break;

      case 2:    //电位器
         b=	Node_ADC_Adjust();
         Node_Adjust_Light(b) ;
			   LCD_ShowString(40,  60, "node_adjust", CYAN);
      break;

      default:
//          printf("ERR\n\r");
			LCD_ShowString(40,  60, "err", CYAN);
      break;			
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
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

  /** Initializes the CPU, AHB and APB buses clocks
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
int fputc(int ch,FILE *f)
{
	HAL_UART_Transmit(&huart1 ,(uint8_t *)&ch,1,0xffff);
	return ch;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//����һ�Ĵ���
	if(GPIO_Pin==GPIO_PIN_6)
	{
		if(HAL_GPIO_ReadPin (GPIOC,GPIO_PIN_6)==0)
		{
			uint16_t now1=HAL_GetTick();
			if((now1-lasttime1)>=50)
			{
				lasttime1=now1;
				KEY1_flag++;
			}
		}
	}
	
	//�������Ĵ���
	if(GPIO_Pin==GPIO_PIN_7)
	{
		if(HAL_GPIO_ReadPin (GPIOC,GPIO_PIN_7)==0)
		{
			uint16_t now2=HAL_GetTick ();
			if((now2 -lasttime2)>=50)
			{
				lasttime2=now2;
				KEY2_flag ++;
				if(KEY2_flag>=4)
				{
					KEY2_flag=4;
				}
			}
		}
	}
	
	//�������Ĵ���
	if(GPIO_Pin==GPIO_PIN_8)
	{
		if(HAL_GPIO_ReadPin (GPIOC,GPIO_PIN_8)==0)
		{
			uint16_t now3=HAL_GetTick();
			if((now3 -lasttime3)>=40)
			{
				lasttime3=now3 ;
				KEY2_flag --;
				if(KEY2_flag<=0)
				{
					KEY2_flag=0;
				}
			}
		}
	}
	
  //测试程序
	//		if(KEY1_flag ==1)
//		{
//			printf("haha\n\r");
//			KEY1_flag =0;
//		}
//		
//		if(KEY2_flag ==1)
//		{
//			printf("hehe\n\r");
//			KEY2_flag =0;
//		}
//		
//		if(KEY3_flag ==1)
//		{
//			printf("xixi\n\r");
//			KEY3_flag =0;
//		}
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
