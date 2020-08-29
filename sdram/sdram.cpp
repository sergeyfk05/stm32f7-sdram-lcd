#include <stm32f7xx_hal.h>
#include <stm32_hal_legacy.h>
#include <CoreDriver.h>
#include <SDRAMDriver.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>

using namespace Drivers;

#ifdef __cplusplus
extern "C"
{
#endif
	void SysTick_Handler(void)
	{
		HAL_IncTick();
		HAL_SYSTICK_IRQHandler();
	}


	extern char _heap_min;
	extern char _heap_max;
	extern int errno;

	caddr_t _sbrk(int incr) {
		static char *current = &_heap_min;
		char *previous = current;

		if (current + incr > (char*)&_heap_max) {
			errno = ENOMEM;
			return (caddr_t) - 1;
		}

		current += incr;
		return (caddr_t) previous ;
	}

#ifdef __cplusplus
}
#endif


int main(void)
{
	CoreDriver::MPU_Config();
	SCB_EnableICache();
	SCB_EnableDCache();
	
	HAL_Init();
	
	CoreDriver::SystemClock_Config();
	
	HAL_StatusTypeDef status = SDRAMDriver::SDRAMInit();
	status = SDRAMDriver::SDRAMTest();
	
	while (1)
	{
		status = SDRAMDriver::SDRAMTest();
	}
}
