#include "interrupt.h"
#include "measure.h"
/*��ν����������ñ�����ϵ������
  Button.level_state=HAL_TIM_ReadPin();
	ͨ������������ð����������ϵ������*/
	
/*�ĸ�������Ҫ��������μ��ٴ�����ظ��ԣ�
  ����һ������״̬�ṹ��:����������justify��level��final��PIN��PORT
	����һ�������ṹ������
  �ֿ�д������������(�ں�������forѭ�������������飬���ɼ��ٴ�����ظ���)
	��һ������������*/


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
			