#include "SDRAMDriver.h"

namespace Drivers
{
	HAL_StatusTypeDef SDRAMDriver::GPIOInit()
	{
		/** FMC GPIO Configuration  
		PF0   ------> FMC_A0
		PF1   ------> FMC_A1
		PF2   ------> FMC_A2
		PF3   ------> FMC_A3
		PF4   ------> FMC_A4
		PF5   ------> FMC_A5
		PC0   ------> FMC_SDNWE
		PF11   ------> FMC_SDNRAS
		PF12   ------> FMC_A6
		PF13   ------> FMC_A7
		PF14   ------> FMC_A8
		PF15   ------> FMC_A9
		PG0   ------> FMC_A10
		PG1   ------> FMC_A11
		PE7   ------> FMC_D4
		PE8   ------> FMC_D5
		PE9   ------> FMC_D6
		PE10   ------> FMC_D7
		PE11   ------> FMC_D8
		PE12   ------> FMC_D9
		PE13   ------> FMC_D10
		PE14   ------> FMC_D11
		PE15   ------> FMC_D12
		PH6   ------> FMC_SDNE1
		PH7   ------> FMC_SDCKE1
		PD8   ------> FMC_D13
		PD9   ------> FMC_D14
		PD10   ------> FMC_D15
		PD14   ------> FMC_D0
		PD15   ------> FMC_D1
		PG4   ------> FMC_BA0
		PG5   ------> FMC_BA1
		PG8   ------> FMC_SDCLK
		PD0   ------> FMC_D2
		PD1   ------> FMC_D3
		PG15   ------> FMC_SDNCAS
		PE0   ------> FMC_NBL0
		PE1   ------> FMC_NBL1
		*/
		
		__HAL_RCC_GPIOF_CLK_ENABLE();
		__HAL_RCC_GPIOH_CLK_ENABLE();
		__HAL_RCC_GPIOC_CLK_ENABLE();
		__HAL_RCC_GPIOG_CLK_ENABLE();
		__HAL_RCC_GPIOE_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();
		
		GPIO_InitTypeDef GPIO_InitStruct = { 0 };
		
		GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 
                          | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_11 | GPIO_PIN_12 
                          | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
		HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_0;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
		HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_4 | GPIO_PIN_5 
		                        | GPIO_PIN_8 | GPIO_PIN_15;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
		HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 
		                        | GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 
		                        | GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
		HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
		HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

		GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_14 
		                        | GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1;
		GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
		GPIO_InitStruct.Pull = GPIO_NOPULL;
		GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
		GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
		HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
		
		return HAL_OK;
	}
	
	HAL_StatusTypeDef SDRAMDriver::FMCInit()
	{
		FMC_SDRAM_TimingTypeDef SdramTiming = { 0 };
		
		__HAL_RCC_FMC_CLK_ENABLE();
		
		SDRAM_HandleTypeDef hsdram;
		hsdram.Instance = FMC_SDRAM_DEVICE;
		
		/* hsdram.Init */
		hsdram.Init.SDBank = FMC_SDRAM_BANK2;
		hsdram.Init.ColumnBitsNumber = FMC_SDRAM_COLUMN_BITS_NUM_8;
		hsdram.Init.RowBitsNumber = FMC_SDRAM_ROW_BITS_NUM_12;
		hsdram.Init.MemoryDataWidth = FMC_SDRAM_MEM_BUS_WIDTH_16;
		hsdram.Init.InternalBankNumber = FMC_SDRAM_INTERN_BANKS_NUM_4;
		hsdram.Init.CASLatency = FMC_SDRAM_CAS_LATENCY_3;
		hsdram.Init.WriteProtection = FMC_SDRAM_WRITE_PROTECTION_DISABLE;
		hsdram.Init.SDClockPeriod = FMC_SDRAM_CLOCK_PERIOD_2;
		hsdram.Init.ReadBurst = FMC_SDRAM_RBURST_ENABLE;
		hsdram.Init.ReadPipeDelay = FMC_SDRAM_RPIPE_DELAY_0;
		/* SdramTiming */
		SdramTiming.LoadToActiveDelay = 2;
		SdramTiming.ExitSelfRefreshDelay = 12;
		SdramTiming.SelfRefreshTime = 8;
		SdramTiming.RowCycleDelay = 9;
		SdramTiming.WriteRecoveryTime = 2; //6
		SdramTiming.RPDelay = 3;
		SdramTiming.RCDDelay = 2;

		return HAL_SDRAM_Init(&hsdram, &SdramTiming);
	}
	
	HAL_StatusTypeDef SDRAMDriver::SDRAMWakeUp()
	{
		HAL_StatusTypeDef status;
		FMC_SDRAM_CommandTypeDef command;
		SDRAM_HandleTypeDef hsdram;
		
		hsdram.Instance = FMC_SDRAM_DEVICE;
		
		command.CommandMode = FMC_SDRAM_CMD_CLK_ENABLE;
		command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
		command.AutoRefreshNumber = 0;
		command.ModeRegisterDefinition = 0;
		if ((status = HAL_SDRAM_SendCommand(&hsdram, &command, 0xFFFF)) != HAL_OK)
		{
			return status;
		}
		HAL_Delay(1);
	
		command.CommandMode = FMC_SDRAM_CMD_PALL;
		command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
		command.AutoRefreshNumber = 0;
		command.ModeRegisterDefinition = 0;
		if ((status = HAL_SDRAM_SendCommand(&hsdram, &command, 0xFFFF)) != HAL_OK)
		{
			return status;
		}
		HAL_Delay(1);
	
		command.CommandMode = FMC_SDRAM_CMD_AUTOREFRESH_MODE;
		command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
		command.AutoRefreshNumber = 2;
		command.ModeRegisterDefinition = 0;
		if ((status = HAL_SDRAM_SendCommand(&hsdram, &command, 0xFFFF)) != HAL_OK)
		{
			return status;
		}
		HAL_Delay(1);
	
		uint32_t tmpr = (uint32_t)SDRAM_MODEREG_BURST_LENGTH_4 |
					   SDRAM_MODEREG_BURST_TYPE_SEQUENTIAL     |
					   SDRAM_MODEREG_CAS_LATENCY_3             |
					   SDRAM_MODEREG_OPERATING_MODE_STANDARD   |
					   SDRAM_MODEREG_WRITEBURST_MODE_SINGLE;	
		command.CommandMode = FMC_SDRAM_CMD_LOAD_MODE;
		command.CommandTarget = FMC_SDRAM_CMD_TARGET_BANK2;
		command.AutoRefreshNumber = 1;
		command.ModeRegisterDefinition = tmpr;
		if ((status = HAL_SDRAM_SendCommand(&hsdram, &command, 0xFFFF)) != HAL_OK)
		{
			return status;
		}
		HAL_Delay(1);
	
	
		hsdram.Instance->SDRTR |= ((uint32_t)(1542 << 1));
		if ((status = HAL_SDRAM_WriteProtection_Disable(&hsdram)) != HAL_OK)
		{
			return status;
		}
		HAL_Delay(1);
		
		return HAL_OK;
	}
	
	HAL_StatusTypeDef SDRAMDriver::SDRAMInit()
	{
		HAL_StatusTypeDef status;
		
		if ((status = GPIOInit()) != HAL_OK)
		{
			return status;
		}
		
		if ((status = FMCInit()) != HAL_OK)
		{
			return status;
		}
		
		if ((status = SDRAMWakeUp()) != HAL_OK)
		{
			return status;
		}
		
		return HAL_OK;
	}
	
#ifdef DEBUG
	HAL_StatusTypeDef SDRAMDriver::SDRAMTest()
	{
		uint32_t counter = 0;
  
		uint8_t ubWritedata_8b = 100, ubReaddata_8b = 0;    
		uint16_t uhWritedata_16b = 200, uhReaddata_16b = 0; 
  
		//write 8bit data
		for(counter = 0 ; counter < SDRAM_SIZE ; counter++)
		{
			*(__IO uint8_t*)(SDRAM_BANK_ADDR + counter) = (uint8_t)(ubWritedata_8b + counter);
		}
  
		//check 8bit data
		for (counter = 0; counter < SDRAM_SIZE; counter++)
		{
			ubReaddata_8b = *(__IO uint8_t*)(SDRAM_BANK_ADDR + counter);   
    
			if(ubReaddata_8b != (uint8_t)(ubWritedata_8b + counter))    
			{
				return HAL_ERROR;
			}
		}
	
  
		//write 16bit data
		for (counter = 0; counter < SDRAM_SIZE / 2; counter++)
		{
			*(__IO uint16_t*)(SDRAM_BANK_ADDR + 2*counter) = (uint16_t)(uhWritedata_16b + counter);
		}
		
		//check 16bit data
		for (counter = 0; counter < SDRAM_SIZE / 2; counter++)
		{
			uhReaddata_16b = *(__IO uint16_t*)(SDRAM_BANK_ADDR + 2*counter);  
    
			if(uhReaddata_16b != (uint16_t)(uhWritedata_16b + counter))   
			{
				return HAL_ERROR;
			}
		}
		
		return HAL_OK;
	}		  
#endif // DEBUG
	
}