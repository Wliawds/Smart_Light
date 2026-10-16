#include "Bright_ADC.h"
#include "ADC.h"
#include "tim.h"

//采集电压值
//电压值在0.6v以上可以关闭灯光
double Bright_ADC(void)
{
	uint16_t adc_val=0;
	double Val=0;
	
	ADC_ChannelConfTypeDef sConfig = {0};
  sConfig.Channel      = ADC_CHANNEL_1;
  sConfig.Rank         = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);
	
	 __HAL_ADC_CLEAR_FLAG(&hadc1, ADC_FLAG_EOC | ADC_FLAG_OVR);  //清除标志位
	if(HAL_ADC_Start (&hadc1 )==HAL_OK )  //开启
	{
		if(HAL_ADC_PollForConversion (&hadc1 ,10)==HAL_OK )     //ADC开启后PollForConversion等待10Ms如果不等于HAL_OK就跳过
		{
			adc_val=HAL_ADC_GetValue (&hadc1 );          //获取ADC的转换值
		}
		HAL_ADC_Stop(&hadc1 );     //关断
	}
	Val=(double)adc_val *3.3/1024;         //换算电压值，2^10=1024；
	return Val;
}

void Bright_ADC_Adjust(double val)
{
	if(val>=0.6)
	{
		__HAL_TIM_SET_COMPARE(&htim3 ,TIM_CHANNEL_1,0);
	}
	
	else if((val>=0.4)&&(val<=0.6))
	{
		__HAL_TIM_SET_COMPARE (&htim3 ,TIM_CHANNEL_1 ,200);
	}
	
	else if((val>=0.2)&&(val<=0.3))
	{
		__HAL_TIM_SET_COMPARE (&htim3 ,TIM_CHANNEL_1 ,600);
	}
	
	else
	{
		__HAL_TIM_SET_COMPARE (&htim3 ,TIM_CHANNEL_1 ,999);
	}
}


//测试程序
//uint32_t a=HAL_ADC_GetValue (&hadc1 );
//double a=Bright_ADC();
//    Bright_ADC_Adjust(a);
