#include <stm32f7xx_hal.h>
#include <stm32_hal_legacy.h>
#include <CoreHelper.h>
#include <SDRAMHelper.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdlib.h>

using namespace Helpers;

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
	CoreHelper::MPU_Config();
	SCB_EnableICache();
	SCB_EnableDCache();
	
	HAL_Init();
	
	CoreHelper::SystemClock_Config();
	
	HAL_StatusTypeDef status = SDRAMHelper::SDRAMInit();
	
	while (1)
	{
		
	}
}
