#pragma once
#include <stm32f7xx_hal.h>

namespace Drivers
{
	class CoreDriver
	{
	public:
		static void SystemClock_Config(void);
		static void MPU_Config(void);
		
	private:
		CoreDriver() {}
		
	};
}
