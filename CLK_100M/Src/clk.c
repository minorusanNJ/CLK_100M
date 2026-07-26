#include "clk.h"
//FLASH access control register in reference manual
#define	FLASH_LATENCY_RESET			~(0xF<<0)
#define FLASH_LATENCY_3		(3U<<0)
//RCC reset and clock control in reference manual
#define CR_HSEON			(1U<<16)
#define CR_HSERDY			(1U<<17)
#define APB1ENR_PWREN		(1U<<28)
//PWR power control register
#define	CR_VOS				(3U<<14)
//RCC reset and clock control in reference manual
#define CFGR_PPRE2					~(1U<<15)
#define CFGR_PPRE1			(4U<<10)
#define CFGR_HPRE					~(1U<<7)
#define	PLLCFGR_PLLP				~(2U<<16)
#define PLLCFGR_PLLN				~(0x137<<6)
#define PLLCFGR_PLLM				~(0x3B<<0)
#define PLLCFGR_PLLSRC		(1U<<22)
#define CR_PLLON			(1U<<24)
#define	CR_PLLRDY			(1U<<25)
#define	CFGR_SW				(2U<<0)
#define	CFGR_SWS			(2U<<2)

void clk_100m_init(void)
{
	FLASH->ACR		&=			FLASH_LATENCY_RESET;
	FLASH->ACR		|=	FLASH_LATENCY_3;
	RCC->CR			|=	CR_HSEON;
	while(!(RCC->CR & CR_HSERDY)){}
	RCC->APB1ENR	|=	APB1ENR_PWREN;
	PWR->CR			|=	CR_VOS;
	RCC->CFGR		&=			(CFGR_PPRE2 & CFGR_HPRE);
	RCC->CFGR		|=	CFGR_PPRE1;
	RCC->PLLCFGR	&=			(PLLCFGR_PLLP & PLLCFGR_PLLN & PLLCFGR_PLLM);
	RCC->PLLCFGR 	|=	PLLCFGR_PLLSRC;
	RCC->CR			|=	CR_PLLON;
	while(!(RCC->CR & CR_PLLRDY)){}
	RCC->CFGR		|=	CFGR_SW;
	while(!(RCC->CFGR & CFGR_SWS)){}
}
