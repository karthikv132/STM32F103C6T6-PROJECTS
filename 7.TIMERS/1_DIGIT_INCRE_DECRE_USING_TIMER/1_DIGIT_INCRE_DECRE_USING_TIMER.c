#include<stm32f10x.h>

int count=0;
char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
void tmr()
{
	if(TIM1 -> SR & (1<<0))
	{
		count++;
		TIM1 -> SR &= ~(1<<0);
	}
}

void fwd()
{
	
}
int main()
{
	RCC -> CR = (1<<7)|(1<<1)|(1<<0);
	RCC -> CFGR =0;
	RCC -> APB2ENR = (1<<2)|(1<<3)|(1<<11);
	
	GPIOA -> CRL = 0x22222222;
	
	//TIM1 -> ARR = 0x07CF;
	TIM1 -> PSC = 0x1F3F;
	TIM1 -> CR1 = 1<<0;
	TIM1 -> CNT = 0;
	TIM1 -> SR = 1<<0;
	
	while(1)
	{
		//tmr();
		for(;count<10;)
		{
		 TIM1 -> ARR = 0x07CF; // 2 second delay
		 GPIOA -> ODR = seg[count];
		 tmr();
		}
		count=0;
		
		for(;count<10;)
		{
			TIM1 -> ARR = 0x03E7; // 1 second delay
			GPIOA -> ODR = seg[9-count];
			tmr();
		}
		
		 count=0;
		 //TIM1 -> ARR = 0x07CF;
	
  }
}