#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
int main()
{
	RCC->CR = 0x00000083;          // Configure RCC Clock Control Register
   
	//RCC->CR = (1<<0)|(1<<1)|(1<<7);
  
	RCC->CFGR = 0x00000000;         // Configure system clock and bus prescalers

  RCC->APB2ENR = 0x0000001C;      // Enable clock for GPIOA, GPIOB and GPIOC
	
	GPIOA->CRL = 0X22222222;
	GPIOB->CRH = 0X22222222;
	while(1)
	{
		for(int i=0;i<8;i++)
		{
			GPIOA->ODR = 1<<i;
			delay(20000);
			
			for(int i=8;i<16;i++)
			{
				GPIOB->ODR = 1<<i;
				delay(20000);
			}
		}
	
	}
	
}