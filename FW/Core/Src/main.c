#include "stm32f4xx.h"


#define PLL_M 4
#define PLL_N 84
#define PLL_P 0 // to odpovídá PLLP = 2 (bit17:16 v PLLCFGR)

void SysClockConfig(void){
	// Enable HSE
	RCC->CR  |= RCC_CR_HSEON;
	while((RCC->CR & RCC_CR_HSERDY));

	// set the power enable clock and voltage regulator
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	PWR->CR |= PWR_CR_VOS;

	//Flash related
	FLASH->ACR |= FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;

	//Prescalers
	//AHB PRes
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;

	//APB1_PRes
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

	//APB2
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

	//PLL (RCC_PLLCFGR register)
	RCC->PLLCFGR = (PLL_M << 0) | (PLL_N << 6) | (PLL_P << 16) | (RCC_PLLCFGR_PLLSRC_HSE);

	//Enable PLL
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));

	//Select clock source
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);



}
void delay(uint32_t time){
	while(time--);
}

void GPIO_Config(void){
	//Enable GPIO clock
	RCC->AHB1ENR |= (1<<0);

	//Set p5 as a output¨
	GPIOA->MODER |= (1<<10);

	GPIOA->OTYPER = 0;
	GPIOA->OSPEEDR = 0;

}

int main(void){
	SysClockConfig();
	GPIO_Config();
	while(1){
		GPIOA->BSRR |= (1<<5);
		delay(1000000);
		GPIOA->BSRR |= (1<<5)<<16;
		delay(1000000);
	}
}
