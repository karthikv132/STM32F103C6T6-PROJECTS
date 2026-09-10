#include<stm32f10x.h>
int count=0;
void tmr()
{
	if(TIM1 -> SR & 1<<0)
	{
		count++;
		TIM1 -> SR &= ~(1<<0);
	}
	
}
int main()
{
	RCC -> CR = (1<<7)| (1<<1) | (1<<0);
	RCC -> CFGR = 0;
	RCC -> APB2ENR = (1<<2)|(1<<3)|(1<<11);
	
	TIM1 -> ARR = 0x007C;
	TIM1 -> PSC = 0xF9FF;
	TIM1 -> CR1 = 1<<0;
	TIM1 -> CNT = 0;
	TIM1 -> SR = 1<<0;
	
	GPIOA -> CRL = 0x00000002;
	while(1)
	{
		tmr();
		if(count%2!=0)
		{
			GPIOA -> BSRR = 1<<0;
		}
		else
		{
			GPIOA -> BRR = 1<<0;
			
		}
		
	}
}