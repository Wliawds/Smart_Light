#include "AdjustLight.h"
#include "tim.h"
#include "math.h"

/*使用TIM3定时器的PWM模式，T=1Ms*/

//初始化函数PWM
void AdjustLight_Init(void)    //括号里的void要加否则会报错
{
	HAL_TIM_PWM_Start(&htim3 , TIM_CHANNEL_1);  //开启定时器的PWM模式
}

//调节光亮
int AdjustLight(uint16_t adjustCount)   //uint8_t==unsigned char;
{
	if(adjustCount > adjust_max)
	{
		return 0;
	}
	
	/*pow是计算平方的，
	伽马补偿，公式如下：实际占空比=（感知亮度）的次方乘最大占空比*/
	adjustCount =(uint16_t )(pow((double)adjustCount /adjust_max ,2.2)*adjust_max );
	__HAL_TIM_SET_COMPARE (&htim3 ,TIM_CHANNEL_1 ,adjustCount );  //注意：这个函数是调节咱空比的函数（积累）
  return 0;
}

/*TIM3-PWM测试main里的*/
//for(uint16_t i=0;i<adjust_max ;i++)
//		{
//			AdjustLight(i);
//			HAL_Delay(2);
//		}
//		for(int j=adjust_max;j>0;j--)
//		{
//			AdjustLight (j);
//			HAL_Delay(2);
//		}

