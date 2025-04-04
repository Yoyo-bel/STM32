#include "PWM.h"
#include "tim.h"//重点：记得包括“tim.h"文件，main.h中并没有包括这个
#include "LCD.h"
#include "stdio.h"

uint16_t duty;
uint32_t fre;


char test[30];

void PWM_Duty_Incre(void)
{
	duty=HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);
	duty+=10;
	if(duty>=100)
	{
		duty=100;
	}
	__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,duty);
	
} 

void PWM_Duty_Decre(void)
{
	duty=HAL_TIM_ReadCapturedValue(&htim3,TIM_CHANNEL_1);
	duty-=10;
	if(duty<=0)
	{
		duty=0;
	}
		__HAL_TIM_SetCompare(&htim3,TIM_CHANNEL_1,duty);
}
	

void PWM_Fre_Incre(void)
{
	uint32_t psc_cur=htim3.Instance->PSC;
	psc_cur=(psc_cur+1)/10;
	if(psc_cur<=8)
	{
		psc_cur=8; 
	}
  psc_cur-=1;
	fre=80000000/(psc_cur+1)/100;
	__HAL_TIM_SET_PRESCALER(&htim3,psc_cur);
}

void PWM_Fre_Decre(void)
{
	uint32_t psc_cur=htim3.Instance->PSC;
	psc_cur=(psc_cur+1)*10;
	if(psc_cur>=8000)
	{
		psc_cur=8000;
	}
  psc_cur-=1;
	fre=80000000/(psc_cur+1)/100;
	__HAL_TIM_SET_PRESCALER(&htim3,psc_cur);
}
	
	
	
