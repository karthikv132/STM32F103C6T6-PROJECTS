#include<stm32f10x.h>

void delay(uint32_t a)
{
	while(a--);
}
int count=0;

void EXTI0_IRQHandler()
{
	if(EXTI -> PR &(1<<0))
	{
		GPIOB -> BRR = (1<<0);
		count++;
		EXTI -> PR = (1<<0);
	}
}
void EXTI1_IRQHandler()
{
	if(EXTI -> PR &(1<<1))
	{
		GPIOB -> BRR = (1<<1);
		count++;
		EXTI -> PR = (1<<1);
	}
}
	
void EXTI2_IRQHandler()
{
	if(EXTI -> PR &(1<<2))
	{
		GPIOB -> BRR = (1<<2);
		count++;
		EXTI -> PR = (1<<2);
	}
}
	
void EXTI3_IRQHandler()
{
	if(EXTI -> PR &(1<<3))
	{
		GPIOB -> BRR = (1<<3);
		count++;
		EXTI -> PR = (1<<3);
	}
}
	
void EXTI4_IRQHandler()
{
	if(EXTI -> PR &(1<<4))
	{
		GPIOB -> BRR = (1<<4);
		count++;
		EXTI -> PR = (1<<4);
	}
}
	
void EXTI9_5_IRQHandler()
{
	if(EXTI -> PR &(1<<5))
	{
		GPIOB -> BRR = (1<<5);
		count++;
		EXTI -> PR = (1<<5);
	}
	
	if(EXTI -> PR &(1<<6))
	{
		GPIOB -> BRR = (1<<6);
		count++;
		EXTI -> PR = (1<<6);
	}
	
	if(EXTI -> PR &(1<<7))
	{
		GPIOB -> BRR = (1<<7);
		count++;
		EXTI -> PR = (1<<7);
	}
	
	if(EXTI -> PR &(1<<8))
	{
		GPIOB -> BRR = (1<<8);
		count++;
		EXTI -> PR = (1<<8);
	}
	
	if(EXTI -> PR &(1<<9))
	{
		GPIOB -> BRR = (1<<9);
		count++;
		EXTI -> PR = (1<<9);
	}
}
	
void EXTI15_10_IRQHandler()
{
	if(EXTI -> PR &(1<<10))
	{
		GPIOB -> BRR = (1<<10);
		count++;
		EXTI -> PR = (1<<10);
	}
	
	if(EXTI -> PR &(1<<11))
	{
		GPIOB -> BRR = (1<<11);
		count++;
		EXTI -> PR = (1<<11);
	}
	
	if(EXTI -> PR &(1<<12))
	{
		GPIOB -> BRR = (1<<12);
		count++;
		EXTI -> PR = (1<<12);
	}
	
	if(EXTI -> PR &(1<<13))
	{
		GPIOB -> BRR = (1<<13);
		count++;
		EXTI -> PR = (1<<13);
	}
	
	if(EXTI -> PR &(1<<14))
	{
		GPIOB -> BRR = (1<<14);
		count++;
		EXTI -> PR = (1<<14);
	}
	
	if(EXTI -> PR &(1<<15))
	{
		GPIOB -> BRR = (1<<15);
		count++;
		EXTI -> PR = (1<<15);
	}
}
	

int main()
{
	RCC -> CR = (1<<7)|(1<<1)|(1<<0);
	RCC -> CFGR = 0;
	RCC ->APB2ENR = (1<<0)|(1<<2)|(1<<3)|(1<<4);
	
	GPIOA -> CRL = 0x88888888;
	GPIOA -> CRH = 0x88888888;
	GPIOB -> CRL = 0x22222222;
	GPIOB -> CRH = 0x22222222;
	
	AFIO -> EXTICR [0] = 0x00000000;
	AFIO -> EXTICR [1] = 0x00000000;
	AFIO -> EXTICR [2] = 0x00000000;
	AFIO -> EXTICR [3] = 0x00000000;
	
	EXTI -> IMR = 0xFFFF;
	EXTI -> FTSR = 0;
	EXTI -> RTSR = 0xFFFF;
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
	NVIC_EnableIRQ(EXTI2_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(EXTI4_IRQn);
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_EnableIRQ(EXTI15_10_IRQn);
	
	GPIOB -> ODR = 0XFFFF;
	
	while(1)
	{	
		if(count==16)
		{
			delay(100000);
			GPIOB -> ODR = 0XFFFF;
		}
	}
}