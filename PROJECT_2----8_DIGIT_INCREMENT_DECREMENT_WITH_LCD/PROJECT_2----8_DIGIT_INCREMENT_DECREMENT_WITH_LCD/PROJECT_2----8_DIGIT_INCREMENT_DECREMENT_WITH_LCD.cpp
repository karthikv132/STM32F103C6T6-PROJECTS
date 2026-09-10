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
	

int main()
{
	RCC -> CR = (1<<7)|(1<<1)|(1<<0);
	RCC -> CFGR = 0;
	RCC -> APB2ENR = (1<<2)|(1<<3)|(1<<4);
	
	GPIOA -> CRL = 0x00002222;
	//GPIOA -> CRH = 0x00000088;
	GPIOB -> CRL = 0x22222222;
	GPIOB -> CRH = 0x22222222;
	GPIOC -> CRH = 0x22000000;
	
	  lcd(0, 0x02);// return home
    lcd(0, 0x28);//4 bit lcd selection
    lcd(0, 0x0E);//display on ,cursor off
    //lcd(0, 0x06);// increment cursor to right 
    lcd(0, 0x01);// clear display
	  lcd(0,0x80);
	  
    
	

	char seg[10]={0X3F,0X06,0X5B,0X4F,0X66,0X6D,0X7D,0X07,0X7F,0X6F};
	int count=0; 
	while(1)
	{
		for(int i=0;i<9999;i++)
		{
			
			
			
			int j=9999-i;
			for(int k=0;k<10;k++)
			{
				GPIOB -> ODR = 0XFE00 | seg[i/1000];
				delay(1000);
				GPIOB -> ODR = 0XFD00 | seg[(i/100)%10];
				delay(1000);
				GPIOB -> ODR = 0XFB00 | seg[(i/10)%10];
				delay(1000);
				GPIOB -> ODR = 0XF700 | seg[i%10];
				delay(1000);
				
				GPIOB -> ODR = 0XEF00 | seg[j/1000];
				delay(1000);
				GPIOB -> ODR = 0XDF00 | seg[(j/100)%10];
				delay(1000);
				GPIOB -> ODR = 0XBF00 | seg[(j/10)%10];
				delay(1000);
				GPIOB -> ODR = 0X7F00 | seg[j%10];
				delay(1000);
				
				lcd(1,(seg[i/1000]+48));
			
		    lcd(1,(seg[(i/100)%10]+48));
			
			  lcd(1,(seg[(i/10)%10]+48));
			
			  lcd(1,(seg[i%10]+48));
				
				
				
				lcd(1,(seg[j/1000]+48));
			
		    lcd(1,(seg[(j/100)%10]+48));
			
			  lcd(1,(seg[(j/10)%10]+48));
			
			  lcd(1,(seg[j%10]+48));
				
			}
		}
	}
}