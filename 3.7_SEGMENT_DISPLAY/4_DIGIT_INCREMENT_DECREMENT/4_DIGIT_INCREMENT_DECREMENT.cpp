#include<stm32f10x.h>

void delay (uint32_t a)
{
	while(a--);
}

int main()
{
	RCC -> CR = (1<<7)|(1<<1)|(1<<0);
	RCC -> CFGR = 0;
	RCC -> APB2ENR = (1<<2)|(1<<3)|(1<<4);
	
	GPIOA -> CRL = 0x22222222;
	GPIOA -> CRH = 0x00222200;
	
	char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
	while(1)
	{
		for(int i=0;i<100;i++)
		{
			
			int j=99-i;
			
			for(int k=0;k<10;k++)
				{
					GPIOA -> ODR = (1<<13)|(0<<12)|(1<<11)|(1<<10)  | seg[i/10];
					delay(1000);
					GPIOA -> ODR = (0<<13)|(1<<12)|(1<<11)|(1<<10) | seg[i%10];
					delay(1000);
					GPIOA -> ODR = (1<<13)|(1<<12)|(1<<11)|(0<<10) | seg[j/10];
					delay(1000);
					GPIOA -> ODR = (1<<13)|(1<<12)|(0<<11)|(1<<10) | seg[j%10];
					delay(1000);
			
				}
		}
	}
	
}