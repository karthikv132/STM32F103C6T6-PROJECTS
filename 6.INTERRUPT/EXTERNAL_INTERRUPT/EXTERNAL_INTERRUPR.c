#include<stm32f10x.h>

void delay(unsigned long int a)
{
	while(a--);
}

void EXTI0_IRQHandler()
{
	if(EXTI -> PR&(1<<0))
	{
		GPIOC -> BRR = 1<<13;
		GPIOB -> ODR = 1<<0;
		delay(100000);
		GPIOB ->BRR = 1<<0;
	}
	EXTI -> PR = 1<<0;
}

int main()
{
	RCC -> CR = 0x00000083;
	RCC -> CFGR = 0;
	RCC -> APB2ENR = (1<<2) | (1<<0) | (1<<3) | (1<<4);
	
	GPIOA -> CRL = 0x00000008;
	GPIOB -> CRL = 0x00000002;
	GPIOC -> CRH = 0x00200000;
	
	AFIO -> EXTICR [0]=0x00000000;
	
	EXTI -> IMR = 1<<0;
	EXTI -> FTSR = 0;
	EXTI -> RTSR = 1<<0;
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	while(1)
		
	{
		GPIOC -> ODR = 1<<13;
	}
}
	