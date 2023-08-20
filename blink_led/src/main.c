#include <stdint.h>
#include "stm32f1xx.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_rcc.h"

void BlockingDelay(volatile uint32_t delay)
{
	 while (delay-- > 0) {
            __asm("nop");
        }
	
}


int main(void)
{
	GPIO_InitTypeDef Gpio_InitStruct;
	__HAL_RCC_GPIOC_CLK_ENABLE();
	Gpio_InitStruct.Pin = GPIO_PIN_13;
	Gpio_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	Gpio_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
	HAL_GPIO_Init(GPIOC,&Gpio_InitStruct);
	
	while(1)
	{
		BlockingDelay(100000UL);
		HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
	}
	return 0;
}
