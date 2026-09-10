#include<stm32f10x.h>

int main()
{
	char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
	int number=0;
	int add=0;
	int multiply=0;
	int mode=0;
	int value;
	int d1,d2,d3,d4;
	uint32_t delay;

	/* PA0-PA7 = 7-segment data
	   PA9-PA12 = digit enable
	   PB0-PB3 = keypad rows
	   PB6-PB8 = keypad columns */

	RCC->CR=(1<<7)|(1<<1)|(1<<0);
	RCC->CFGR=0;
	RCC->APB2ENR=(1<<2)|(1<<3);

	GPIOA->CRL=0X22222222;
	GPIOA->CRH=0X00022220;
	GPIOB->CRL=0X88002222;
	GPIOB->CRH=0X00000008;

	GPIOA->ODR=0;
	GPIOB->ODR=0;

	while(1)
	{
		/* Select the value to display */
		if(mode==0) value=number;
		if(mode==1) value=add;
		if(mode==2) value=multiply;

		d1=(value/1000)%10;
		d2=(value/100)%10;
		d3=(value/10)%10;
		d4=value%10;

		/* Display digit 1 using PA9 */
		
		GPIOA->ODR=GPIOA->ODR&0XE1FF;
		GPIOA->ODR=(GPIOA->ODR&0XFF00)|seg[d1];
		GPIOA->ODR=GPIOA->ODR|(1<<9);
		for(delay=0;delay<2000;delay++);

		/* Display digit 2 using PA10 */
		
		GPIOA->ODR=GPIOA->ODR&0XE1FF;
		GPIOA->ODR=(GPIOA->ODR&0XFF00)|seg[d2];
		GPIOA->ODR=GPIOA->ODR|(1<<10);
		for(delay=0;delay<2000;delay++);

		/* Display digit 3 using PA11 */
		GPIOA->ODR=GPIOA->ODR&0XE1FF;
		GPIOA->ODR=(GPIOA->ODR&0XFF00)|seg[d3];
		GPIOA->ODR=GPIOA->ODR|(1<<11);
		for(delay=0;delay<2000;delay++);

		/* Display digit 4 using PA12 */
		GPIOA->ODR=GPIOA->ODR&0XE1FF;
		GPIOA->ODR=(GPIOA->ODR&0XFF00)|seg[d4];
		GPIOA->ODR=GPIOA->ODR|(1<<12);
		for(delay=0;delay<2000;delay++);
		
		/* Row A: 1, 2, 3 */
		
		GPIOB->ODR=(GPIOB->ODR&0XFFF0)|(1<<0);
		if(GPIOB->IDR&(1<<6))
		{
			number=(number%1000)*10+1;
			mode=0;
			while(GPIOB->IDR&(1<<6));
		}
		if(GPIOB->IDR&(1<<7))
		{
			number=(number%1000)*10+2;
			mode=0;
			while(GPIOB->IDR&(1<<7));
		}
		if(GPIOB->IDR&(1<<8))
		{
			number=(number%1000)*10+3;
			mode=0;
			while(GPIOB->IDR&(1<<8));
		}

		/* Row B: 4, 5, 6 */
		GPIOB->ODR=(GPIOB->ODR&0XFFF0)|(1<<1);
		if(GPIOB->IDR&(1<<6))
		{
			number=(number%1000)*10+4;
			mode=0;
			while(GPIOB->IDR&(1<<6));
		}
		if(GPIOB->IDR&(1<<7))
		{
			number=(number%1000)*10+5;
			mode=0;
			while(GPIOB->IDR&(1<<7));
		}
		if(GPIOB->IDR&(1<<8))
		{
			number=(number%1000)*10+6;
			mode=0;
			while(GPIOB->IDR&(1<<8));
		}

		/* Row C: 7, 8, 9 */
		GPIOB->ODR=(GPIOB->ODR&0XFFF0)|(1<<2);
		if(GPIOB->IDR&(1<<6))
		{
			number=(number%1000)*10+7;
			mode=0;
			while(GPIOB->IDR&(1<<6));
		}
		if(GPIOB->IDR&(1<<7))
		{
			number=(number%1000)*10+8;
			mode=0;
			while(GPIOB->IDR&(1<<7));
		}
		if(GPIOB->IDR&(1<<8))
		{
			number=(number%1000)*10+9;
			mode=0;
			while(GPIOB->IDR&(1<<8));
		}

		/* Row D: * = add, 0 = zero, # = multiply */
		GPIOB->ODR=(GPIOB->ODR&0XFFF0)|(1<<3);
		if(GPIOB->IDR&(1<<6))
		{
			add=(number/100)+(number%100);
			mode=1;
			while(GPIOB->IDR&(1<<6));
		}
		if(GPIOB->IDR&(1<<7))
		{
			number=(number%1000)*10;
			mode=0;
			while(GPIOB->IDR&(1<<7));
		}
		if(GPIOB->IDR&(1<<8))
		{
			multiply=(number/100)*(number%100);
			mode=2;
			while(GPIOB->IDR&(1<<8));
		}
	}
}