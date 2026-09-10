#include<stm32f10x.h>
void delay(uint32_t a)
{
	while(a--);
}
int main()
{
	 RCC->CR=0X00000083;
	 RCC->CFGR=0X00000000;
	 RCC->APB2ENR=0X0000001C;
	
	 GPIOA->CRL = 0X22222222;
	int i;
	int a=0;
	int count=7;
	
	while(1)
    {
    for(i = 0; i <=count; i++)
    {
        GPIOA->ODR = (1 << i)|a;
        delay(100000);
    }
    a|=1<<count--;
    
    if(a==0x00000ff)
    {
        for(i=0;i<8;i++)
        {
            GPIOA->ODR = GPIOA->ODR & (~(1<<i));
            delay(100000);
        }
    }
    
    }
}
