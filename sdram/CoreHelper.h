#pragma once
#include <stm32f7xx_hal.h>

namespace Helpers
{
	class CoreHelper
	{
	public:
		static void SystemClock_Config(void);
		static void MPU_Config(void);
		
	private:
		CoreHelper() {}
		
	};
}
