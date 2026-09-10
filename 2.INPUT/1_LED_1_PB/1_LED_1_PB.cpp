#include<stm32f10x.h>
void delay(uint32_t a)
{
while(a--);
}
int main()
{
	int count=0;
	RCC -> CR = 0X00000083;
	RCC -> CFGR = 0X00000000;
	RCC -> APB2ENR = (1<<2)|(1<<3)|(1<<4); 
	
	GPIOA -> CRL = 0X00000028;
	while(1)
	{
		if(GPIOA -> IDR &(1<<0))
		{
			count++;
			while(GPIOA -> IDR & (1<<0));
		}
		if(count % 2 !=0)
		{
			GPIOA -> ODR |= (1<<1);
		}
		else 
		{
			GPIOA -> ODR &= ~(1<<1);
		}
	}
}
