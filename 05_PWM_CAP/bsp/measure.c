#include "measure.h"
#include "tim.h"
#include "stdio.h"
#include "lcd.h"

uint32_t CCR1_Duty;
float Measured_Duty;
uint32_t CCR2_Fre;
float Measured_Fre;

char write[20]={0};

/*
  主从触发模式：从模式：reset；触发源：TI1FP1
  注意reset的是CNT的值，CRR的值没有被删除
*/


void Measure_Duty(void)
{
   CCR1_Duty=HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_2);
	
	 if (CCR2_Fre != 0)  // 检查除数是否为 0
    {
        Measured_Duty = ((float)CCR1_Duty / CCR2_Fre) * 100;
    }
    else
    {
        Measured_Duty = 0;  // 避免除零错误
    }

	 sprintf(write,"Duty is %.2f%%",Measured_Duty);
	 LCD_DisplayStringLine(Line4,(uint8_t*)write);
		
}

void Measure_Fre(void)
{
	CCR2_Fre=HAL_TIM_ReadCapturedValue(&htim2,TIM_CHANNEL_1);
	Measured_Fre=80000000/CCR2_Fre;
	sprintf(write,"fre is %.2fHz",Measured_Fre);
  LCD_DisplayStringLine(Line5,(uint8_t*)write);
}
