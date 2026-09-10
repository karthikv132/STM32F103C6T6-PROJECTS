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
    //PORTD = value;
    //enable();
}

void str( char *ptr)
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
	GPIOC -> CRH = 0x22000000;
	//GPIOA -> ODR =0;
	//GPIOC -> ODR =0; 
	
	  lcd(0, 0x02);// return home
    lcd(0, 0x28);//4 bit lcd selection
    lcd(0, 0x0C);//display on ,cursor off
    lcd(0, 0x06);// increment cursor to right 
    //lcd(0, 0x01);// clear display
    lcd(0, 0x80);
	while(1)
{
    lcd(0, 0x01);   // Clear LCD
    lcd(0, 0x80);   // First-line start

    str("welcome to manfree technologies      ");

    for(int i=0; i<30; i++)
    {
        lcd(0, 0x18);   // Shift display left
        delay(50000);   // Change speed here
    }

         lcd(0, 0x02);   // Return home; reset display shift
         delay(50000);
}
}
 