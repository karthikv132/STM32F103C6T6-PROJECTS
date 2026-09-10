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
	
	GPIOA -> CRL = 0X22222222;
	char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
	while(1)
	{
		for(int i=0;i<10;i++)
		{
			GPIOA -> ODR = seg[i];
			delay(100000);
		}
	}
		
}