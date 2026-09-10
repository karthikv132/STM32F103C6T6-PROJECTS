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
	GPIOA -> CRH = 0x00088800;
	GPIOB -> CRL = 0x00000002;
	
	char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
	int count=0;
	
	while(1)
	{
		if(GPIOA -> IDR & (1<<10))
		{
			count++;	
			if(count>9)
			{
				count=9;
			}
		}
		while(GPIOA -> IDR & (1<<10));
		
		
		
		if(GPIOA -> IDR & (1<<11))
		{
			count--;
			if(count<0)
			{
				count=0;
			}	
		}
		while(GPIOA -> IDR & (1<<11));
		
		
		
		if((count<10))
		{
			GPIOA -> ODR = seg [count];
		}
		
		if(count>=0)
		{
			GPIOA -> ODR = seg [count];
		}
		
		
		
		if(GPIOA -> IDR & (1<<12))
		{
			GPIOB -> ODR = (1<<0);
			for(int i=count;i>0;i--)
			{
				GPIOA -> ODR = seg[i];
				delay(100000);
			}
			count=0;
		}
		GPIOB -> ODR =0;
	}
}