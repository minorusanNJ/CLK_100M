#include "led.h"
#include "clk.h"

int main(void)
{
	led_init();
	clk_100m_init();

	while(1)
	{
		//GPIOA->ODR	^=	ODR_PA5_H;
		//for(int i=0; i<200000; i++){}
	}
}
