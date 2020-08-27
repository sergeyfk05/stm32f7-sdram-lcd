#include <stm32f7xx_hal.h>
#include <stm32_hal_legacy.h>
#include <CoreHelper.h>
#include <SDRAMHelper.h>

using namespace Helpers;

#ifdef __cplusplus
extern "C"
#endif
void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}

int main(void)
{
	CoreHelper::MPU_Config();
	SCB_EnableICache();
	SCB_EnableDCache();
	
	HAL_Init();
	
	CoreHelper::SystemClock_Config();
	
	HAL_StatusTypeDef status = SDRAMHelper::SDRAMInit();
	
	while (1)
	{
		status = SDRAMHelper::SDRAMTest();
	}
}
