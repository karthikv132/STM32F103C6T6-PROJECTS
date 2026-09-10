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
	GPIOA -> CRH = 0x00002222;
	GPIOB -> CRL = 0x00000888;
	
	 char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
	 
	 while(1)
	 {
		 GPIOA ->ODR |= (1<<8);
		 if(GPIOB -> IDR &(1<<0))
		 {
			 GPIOA -> ODR = seg[1];
			 while(GPIOB -> IDR &(1<<0));
		 }
		 if(GPIOB -> IDR &(1<<1))
		 {
			 GPIOA -> ODR = seg[2];
			 while(GPIOB -> IDR &(1<<1));
		 }
		 
		 if(GPIOB -> IDR &(1<<2))
		 {
			 GPIOA -> ODR = seg[3];
			 while(GPIOB -> IDR &(1<<2));
		 }
		 
		 
		  GPIOA ->ODR |= (1<<9);
		 if(GPIOB -> IDR &(1<<0))
		 {
			 GPIOA -> ODR = seg[4];
			 while(GPIOB -> IDR &(1<<0));
		 }
		 if(GPIOB -> IDR &(1<<1))
		 {
			 GPIOA -> ODR = seg[5];
			 while(GPIOB -> IDR &(1<<1));
		 }
		 
		 if(GPIOB -> IDR &(1<<2))
		 {
			 GPIOA -> ODR = seg[6];
			 while(GPIOB -> IDR &(1<<2));
		 }
		 
		  GPIOA ->ODR |= (1<<10);
		 if(GPIOB -> IDR &(1<<0))
		 {
			 GPIOA -> ODR = seg[7];
			 while(GPIOB -> IDR &(1<<0));
		 }
		 if(GPIOB -> IDR &(1<<1))
		 {
			 GPIOA -> ODR = seg[8];
			 while(GPIOB -> IDR &(1<<1));
		 }
		 
		 if(GPIOB -> IDR &(1<<2))
		 {
			 GPIOA -> ODR = seg[9];
			 while(GPIOB -> IDR &(1<<2));
		 }
		 
		 GPIOA ->ODR |= (1<<11);
		 if(GPIOB -> IDR &(1<<1))
		 {
			 GPIOA -> ODR = seg[0];
			 while(GPIOB -> IDR &(1<<1));
		 }
	 }
}