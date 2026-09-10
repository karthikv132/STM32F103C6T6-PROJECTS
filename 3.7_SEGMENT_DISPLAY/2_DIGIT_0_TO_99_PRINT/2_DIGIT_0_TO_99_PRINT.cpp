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
	
	GPIOA -> CRL = 0x22222222;
	GPIOB -> CRL = 0x00000022;
	char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
	
	while(1)
	{
		for(int i=0;i<100;i++)
		{
			for(int j=0;j<10;j++)
			{
				GPIOB -> ODR = (1<<0);
				GPIOA -> ODR = seg[i/10];
				delay(10000);
				GPIOB -> ODR = 0;
				GPIOA -> ODR = 0;
				
				GPIOB -> ODR = (1<<1);
				GPIOA -> ODR = seg[i%10];
				delay(10000);
				GPIOB -> ODR = 0;
				GPIOA -> ODR = 0;
			}
		}
	}
	
}