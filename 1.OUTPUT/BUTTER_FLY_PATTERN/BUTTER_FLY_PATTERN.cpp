#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
void on(int a,int b)
{
	for(int i=a;i<b;i++)
	{
		GPIOA -> ODR |=(1<<i);
	}
	delay(100000);
}
void off(int c,int d)
{
	for(int i=d;i>=c;i--)
	{
		GPIOA -> BRR |=(1<<i);
	}
	delay(100000);
}
int main()
{
	RCC -> CR = 0X00000083;
	RCC -> CFGR = 0X00000000;
	RCC -> APB2ENR =(1<<2)|(1<<3)|(1<<4);
	
	GPIOA -> CRL = 0X22222222;
	GPIOA -> CRH = 0X22222222;
	
	while(1)
	{
		on(0,4);
		on(4,8);
		on(8,12);
		on(12,16);
		delay(10000);
		off(12,16);
		off(8,12);
		off(4,8);
		off(0,4);
	
		GPIOA -> BRR = 0;
	
	}
}