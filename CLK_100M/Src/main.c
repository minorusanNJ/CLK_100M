#include "led.h"
#include "clk.h"
#include "systick.h"

volatile uint16_t	mill_sec = 0;

int main(void)
{
	led_init();
	clk_100m_init();
	systick_1ms_timer();

	while(1)
	{

	}
}
void SysTick_Handler(void)
{
	mill_sec ++;
	if(mill_sec >= 1000)
	{
		mill_sec = 0;
		GPIOA->ODR	^=	ODR_PA5_H;
	}
}
