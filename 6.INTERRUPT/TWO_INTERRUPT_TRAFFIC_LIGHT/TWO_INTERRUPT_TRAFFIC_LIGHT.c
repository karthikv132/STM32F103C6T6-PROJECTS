#include<stm32f10x.h>

void delay(unsigned long int a)
{
	while(a--);
}

void enable()
{
	GPIOC -> BSRR = (1<<14);
	delay(200);
	GPIOC -> BRR = (1<<14);
	delay(200);
	
}

void lcd(int rs,int value)
{
	if(rs)
		GPIOC->ODR=1<<15;
	else
		GPIOC->BRR=1<<15;
	
	GPIOA->ODR=((value & 0XF0)>>4);
	enable();
	GPIOA->ODR=(value & 0X0F);
	enable();
	
}
void str(unsigned char *ptr)
	{
    while (*ptr != '\0') 
		{
        lcd(1, *ptr++);
    }
}
void EXTI3_IRQHandler()
{
	if(EXTI -> PR&(1<<3))
	{
		lcd(0, 0x01);// clear display
	  lcd(0,0x80);
		str("INTERRUPT");
		delay(400000);
		
		EXTI -> PR =(1<<3);
	}
}	

void EXTI9_5_IRQHandler()
{
	if(EXTI -> PR &(1<<5))
	{
		GPIOB -> ODR = 0;
		GPIOB -> BSRR = (1<<0);
		lcd(0, 0x01);// clear display
	  lcd(0,0x80);
		str("EMERGENCY");
		delay(500000);
		//GPIOB -> BRR = (1<<0);
		
		EXTI -> PR = (1<<5);
	}
	
	
	/*{
		lcd(0, 0x01);// clear display
	  lcd(0,0x80);
		str("INTERRUPT");
		delay(400000);
		
		EXTI -> PR = (1<<6);
	}*/
	
	
}

int main()
{
	RCC -> CR = 0x00000083;
	RCC -> CFGR = 0;
	RCC -> APB2ENR = (1<<0)|(1<<2)|(1<<3)|(1<<4);
	
	GPIOA -> CRL = 0x00802222;
	GPIOB -> CRL = 0x00008222;
	GPIOC -> CRH = 0x22000000;
	
	AFIO -> EXTICR[1]=0x00000000;//her we set 0000 porta.[1]-pins from 4-7  
	AFIO -> EXTICR[0]=0x00001000;//here we set 12-15 bit for selecting EXTI3 PORTB 0001.[0]-pins from 0-38
	
	EXTI -> IMR = (1<<5)|(1<<3);
	EXTI -> FTSR = 0;
	EXTI -> RTSR = (1<<5)|(1<<3);
	
	 lcd(0, 0x02);// return home
   lcd(0, 0x28);//4 bit lcd selection
   lcd(0, 0x0E);//display on ,cursor off
   //lcd(0, 0x06);// increment cursor to right 
   lcd(0, 0x01);// clear display
	 lcd(0,0x80);
	
	NVIC_EnableIRQ(EXTI9_5_IRQn);
	NVIC_EnableIRQ(EXTI3_IRQn);
	
	
	while(1)
	{
		GPIOB -> BSRR = (1<<0);
		lcd(0, 0x01);// clear display
	  lcd(0,0x80);
		str("RED");
		delay(300000);
		GPIOB -> BRR = (1<<0);
		//delay(100000);
		
		GPIOB -> BSRR = (1<<1); 
		lcd(0, 0x01);// clear display
	  lcd(0,0x80);
		str("YELLOW");
		delay(300000);
		GPIOB -> BRR = (1<<1);
		//delay(100000);
		
		GPIOB -> BSRR = (1<<2);
		lcd(0, 0x01);// clear display
	  lcd(0,0x80);
		str("GREEN");
		delay(300000);
		GPIOB -> BRR = (1<<2);
		//delay(100000);
	}
}














