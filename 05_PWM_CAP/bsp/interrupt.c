#include "interrupt.h"
#include "measure.h"
/*如何将按键和设置变量联系起来？
  Button.level_state=HAL_TIM_ReadPin();
	通过这个函数将该按键与变量联系了起来*/
	
/*四个按键都要消抖，如何减少代码的重复性？
  定义一个按键状态结构体:包括按键的justify，level，final，PIN，PORT
	定义一个按键结构体数组
  分开写按键消抖函数(在函数中用for循环遍历按键数组，即可减少代码的重复性)
	和一个按键处理函数*/


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM4)
	{
		KEY_Detect();
	  KEY_Proc();
	}
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM2)
	{
	
		if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_1)
		{
			Measure_Fre();
			//HAL_TIM_IC_Start(htim, TIM_CHANNEL_1); // Restart CH2 IC
		}
		if(htim->Channel==HAL_TIM_ACTIVE_CHANNEL_2)
		{
			Measure_Duty();
			//HAL_TIM_IC_Start(htim, TIM_CHANNEL_2); // Restart CH2 IC
		}
	}
}
			