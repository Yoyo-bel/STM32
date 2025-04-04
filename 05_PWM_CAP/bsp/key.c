#include "key.h"
#include "PWM.h"
#include "LCD.h"
#include "stdio.h"

Button buttons[4]=
{
	{GPIOB,GPIO_PIN_0,0,0,0},
	{GPIOB,GPIO_PIN_1,0,0,0},
	{GPIOB,GPIO_PIN_2,0,0,0},
	{GPIOA,GPIO_PIN_0,0,0,0},
};

char data[20];	
void KEY_Detect(void)
{
	for(uint8_t i=0;i<4;i++)
	{
		/*输入按键PORT, PIN，读取按键状态,存入level*/
		buttons[i].level_state=HAL_GPIO_ReadPin(buttons[i].port,buttons[i].pin);
		switch(buttons[i].justify_state)
		{
			case 0:
				if(buttons[i].level_state==0)
				{
					buttons[i].justify_state=1;
				}
				break;
			case 1:
				if(buttons[i].level_state==0)
				{
					buttons[i].justify_state=2;
				}
				else 
				{
					buttons[i].justify_state=0;
				}
				break;
			case 2:
				if(buttons[i].level_state==1)
				{
					buttons[i].justify_state=0;
					buttons[i].final_state=1;
				}
				break;
			}
		}
}

void KEY_Proc(void)
{
		for(uint8_t i=0;i<4;i++)
	  {
			if(buttons[0].final_state==1)
			{
				buttons[0].final_state=0;
				PWM_Duty_Incre();
				sprintf(data,"Duty:%d%%",duty);
				LCD_DisplayStringLine(Line1,(uint8_t*)data);	
				HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_7);
			}
			if(buttons[1].final_state==1)
			{
				buttons[1].final_state=0;
				PWM_Duty_Decre();
				sprintf(data,"Duty:%d%%",duty);
				LCD_DisplayStringLine(Line1,(uint8_t*)data);
			}
			if(buttons[2].final_state==1)
			{
				buttons[2].final_state=0;
				PWM_Fre_Incre();
				sprintf(data,"Fre:%ld Hz",fre);
				LCD_DisplayStringLine(Line2,(uint8_t*)data);
			}
			if(buttons[3].final_state==1)
			{
				buttons[3].final_state=0;
				PWM_Fre_Decre();
			  sprintf(data,"Fre:%ld Hz",fre);
				LCD_DisplayStringLine(Line2,(uint8_t*)data);
			}
		}
}
