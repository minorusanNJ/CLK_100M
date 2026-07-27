#include "led.h"
#include "clk.h"

//SysTick	CortexM4GenericUserGuide
#define	COUNTFLAG		(1U<<16)
#define CLKSOURCE		(1U<<2)
#define	ENABLE			(1U<<0)

void systick_init(void)
{
	SysTick->LOAD	=	100000000 /10 - 1;
	SysTick->VAL	=	0;
	SysTick->CTRL	|=	(CLKSOURCE | ENABLE);
}

int main(void)
{
	led_init();
	clk_100m_init();

	systick_init();

	uint8_t tencount = 0;

	while(1)
	{
		if(SysTick->CTRL & COUNTFLAG)
		{
			tencount++;
			if(tencount >= 10)
			{
				GPIOA->ODR	^=	ODR_PA5_H;
				tencount = 0;
			}
		}
	}
}
