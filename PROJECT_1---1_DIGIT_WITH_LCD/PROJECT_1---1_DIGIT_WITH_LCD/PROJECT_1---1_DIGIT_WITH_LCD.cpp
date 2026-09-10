#include<stm32f10x.h>

void delay(uint32_t a)
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

void lcd(char rs,unsigned char value) 
	{
		if(rs==1)
		{
		GPIOC -> BSRR = (1<<15);
		}
		else
		{
			GPIOC -> BRR = (1<<15);
		}
		GPIOA -> ODR &= ~0x0F;
		GPIOA -> ODR |=(value & 0xF0)>>4;
		enable();
		GPIOA -> ODR &= ~0x0F;
		GPIOA -> ODR |= (value & 0x0F);
		enable();
    
}

void str(unsigned char *ptr)
	{
    while (*ptr != '\0') 
		{
        lcd(1, *ptr++);
    }
}
	

int main()
{
	RCC -> CR = (1<<7)|(1<<1)|(1<<0);
	RCC -> CFGR = 0;
	RCC -> APB2ENR = (1<<2)|(1<<3)|(1<<4);
	
	GPIOA -> CRL = 0x00002222;
	GPIOA -> CRH = 0x00000088;
	GPIOB -> CRL = 0x22222222;
	GPIOC -> CRH = 0x22000000;
	
	  lcd(0, 0x02);// return home
    lcd(0, 0x28);//4 bit lcd selection
    lcd(0, 0x0C);//display on ,cursor off
    lcd(0, 0x06);// increment cursor to right 
    //lcd(0, 0x01);// clear display
    lcd(0, 0x80);
	
	char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
	int count=0;
	
	while(1)
	{
		if(GPIOA -> IDR & (1<<8))
		{
			count++;
			if(count>=9)
			{
				count=9;
			}
			while(GPIOA -> IDR & (1<<8));
			GPIOB -> ODR = seg[count];
			lcd(0,0x80);
			lcd(1,count+48);
		}
		
		if(GPIOA -> IDR & (1<<9))
		{
			count--;
			if(count<0)
			{
				count=0;
			}
			while(GPIOA -> IDR & (1<<9));
			GPIOB -> ODR = seg[count];
			lcd(0,0x80);
			lcd(1,count+48);
		}
	}
}