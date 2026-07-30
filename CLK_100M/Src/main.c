#include "led.h"
#include "clk.h"
#include "systick.h"
#include "uart.h"
#include <stdio.h>

volatile uint16_t	mill_sec = 0;
volatile uint8_t	timer1 = 0;

int main(void)
{
	led_init();
	clk_100m_init();
	systick_1ms_timer();
	uart_init();

	while(1)
	{
		if(timer1)
		{
			printf("UART is working... \n\r");
			timer1 = 0;
		}
	}
}
void SysTick_Handler(void)
{
	mill_sec ++;
	if(mill_sec >= 1000)
	{
		mill_sec = 0;
		GPIOA->ODR	^=	ODR_PA5_H;
		timer1 = 1;
	}
}
