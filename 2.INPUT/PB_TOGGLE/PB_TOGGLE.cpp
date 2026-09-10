#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}

int main()
{
	RCC -> CR = (1<<7)|(1<<1)|(1<<0);
	RCC -> CFGR = 0;
	RCC -> APB2ENR = (1<<2)|(1<<3)|(1<<3);
	
	GPIOA -> CRL = 0X00000888;
	GPIOA -> CRH = 0X00000002;
	
	int on = 1;
	int off = 0;
	int count=0;
	
	while(1)
	{
		if(GPIOA -> IDR & (1<<0))
		{
			GPIOA -> ODR =(on<<8);
			while(GPIOA -> IDR & (on<<0));
		}
		else if(GPIOA -> IDR & (1<<1))
		{
			GPIOA -> ODR =(off<<8);
			while(GPIOA -> IDR & (1<<1));
		}
		else if(GPIOA -> IDR & (1<<2))
		{
			count++;
			while(GPIOA -> IDR & (1<<2));
		}
		if(count%2!=0)
		{
			on = 0;
			off = 1;
		}
		else if(count%2==0)
		{
			on=1;
			off=0;
		}
	}
}