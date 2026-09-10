#include<stm32f10x.h>

void delay(uint32_t a)
{
	while(a--);
}

int main()
{
	RCC -> CR = (1<<7)|(1<<1)|(1<<0);
	RCC -> CFGR = 0;
	RCC -> APB2ENR = (1<<2)|(1<<3)|(1<<4);
	
	GPIOA -> CRL = 0X00000888;
	GPIOA -> CRH = 0X00000022;
	int mode=0;
	while(1)
	{
		if((GPIOA -> IDR & (1<<0))&&(mode==0))
		{
			GPIOA -> ODR = (1<<8);
			mode=1;
			while(GPIOA -> IDR & (1<<0));
		}	
		if((GPIOA -> IDR & (1<<1))&&(mode==0))
		{
			mode=1;
			GPIOA -> ODR = (1<<9);
			while(GPIOA -> IDR & (1<<1));
		}
		if(GPIOA -> IDR & (1<<2))
		{
			GPIOA -> ODR &= ~(1<<8);
			GPIOA -> ODR &= ~(1<<9);
			mode=0;
			while(GPIOA -> IDR & (1<<2));
		}
		
	}
}