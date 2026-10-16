#include "KEY.h"
#include "tim.h"
#include "stdio.h"
#include "TFT.h"

//KEY2,3按键调节光亮
void AdjustKey_ON_OFF(uint16_t KEY)
{
	switch(KEY)
	{
		case 0:
			__HAL_TIM_SET_COMPARE(&htim3 ,TIM_CHANNEL_1,0);
		break;
		
		case 1:
			__HAL_TIM_SET_COMPARE(&htim3 ,TIM_CHANNEL_1,333);
		break;
		
		case 2:
			__HAL_TIM_SET_COMPARE(&htim3 ,TIM_CHANNEL_1,666);
		break;
		
		case 3:
			__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1 ,999);
		break;
		
		default :
			//printf("WARNING\n\r");
		  LCD_ShowString(40,80, "wraning", CYAN);
		  HAL_Delay (500);
//			for(int i=0;i<5;i++)
//			{
//				__HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1 ,999);
//				HAL_Delay(500);
//				__HAL_TIM_SET_COMPARE(&htim3 ,TIM_CHANNEL_1,0);
//				HAL_Delay (500);
//			}
		break;
	}
}

