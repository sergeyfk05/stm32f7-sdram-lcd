#include "CoreDriver.h"

namespace Drivers
{
	void CoreDriver::SystemClock_Config()
	{
		//200MHz
		
		RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
		RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

		/** Configure the main internal regulator output voltage 
		*/
		__HAL_RCC_PWR_CLK_ENABLE();
		__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
		/** Initializes the CPU, AHB and APB busses clocks 
		*/
		RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
		RCC_OscInitStruct.HSIState = RCC_HSI_ON;
		RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
		RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
		RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
		RCC_OscInitStruct.PLL.PLLM = 8;
		RCC_OscInitStruct.PLL.PLLN = 180;
		RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
		RCC_OscInitStruct.PLL.PLLQ = 2;
		HAL_RCC_OscConfig(&RCC_OscInitStruct);
		
		/** Initializes the CPU, AHB and APB busses clocks 
		*/
		RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
		                            | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
		RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
		RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
		RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
		RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

		HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5);
	}
	
	void CoreDriver::MPU_Config()
	{
		MPU_Region_InitTypeDef MPU_InitStruct = { 0 };

		/* Disables the MPU */
		HAL_MPU_Disable();
		/** Initializes and configures the Region and the memory to be protected 
		*/
		MPU_InitStruct.Enable = MPU_REGION_ENABLE;
		MPU_InitStruct.Number = MPU_REGION_NUMBER0;
		MPU_InitStruct.BaseAddress = 0x20010000;
		MPU_InitStruct.Size = MPU_REGION_SIZE_256B;
		MPU_InitStruct.SubRegionDisable = 0x0;
		MPU_InitStruct.TypeExtField = MPU_TEX_LEVEL0;
		MPU_InitStruct.AccessPermission = MPU_REGION_FULL_ACCESS;
		MPU_InitStruct.DisableExec = MPU_INSTRUCTION_ACCESS_ENABLE;
		MPU_InitStruct.IsShareable = MPU_ACCESS_NOT_SHAREABLE;
		MPU_InitStruct.IsCacheable = MPU_ACCESS_CACHEABLE;
		MPU_InitStruct.IsBufferable = MPU_ACCESS_NOT_BUFFERABLE;

		HAL_MPU_ConfigRegion(&MPU_InitStruct);
		/* Enables the MPU */
		HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);
	}
}