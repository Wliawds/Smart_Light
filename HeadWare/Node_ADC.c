#include "Node_ADC.h"
#include "adc.h"
#include "tim.h"

double Node_ADC_Adjust(void)
{
	uint16_t Node_val=0;
	uint16_t Node_arr[5]={0};
	double NODE=0; 
	
	ADC_ChannelConfTypeDef sConfig = {0};   //声明一个结构体并置零
  sConfig.Channel      = ADC_CHANNEL_3;   //选择通道
  sConfig.Rank         = 1;               //排名在规则序列里的转化排名
  sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;      //采样时间
  HAL_ADC_ConfigChannel(&hadc1, &sConfig);         //采样的东西存储在ADC1的寄存器中
	
	if(HAL_ADC_Start(&hadc1 )==HAL_OK)
	{
		if(HAL_ADC_PollForConversion (&hadc1 ,10)==HAL_OK )     //ADC开启后PollForConversion等待10Ms如果不等于HAL_OK就跳过
		{
			Node_val=HAL_ADC_GetValue (&hadc1 );          //获取ADC的转换值
		}
		HAL_ADC_Stop(&hadc1 );     //关断
	}
	
	for(int i=5;i>=0;i--)
	{
		NODE=(Node_arr [0]+Node_arr [1]+Node_arr [2]+Node_arr [3]+Node_arr [4])/5;
		Node_arr [i]=Node_arr[i-1];
		Node_arr [0]=Node_val ;
	}
	return NODE;
}


void Node_Adjust_Light(double NODE)    //调节光的
{
	double node=0;
	node=(NODE-10)*2.5;
	if(node>999)
	{
		node=999;
	}
	if(node<10)
	{
		node=0;
	}
	__HAL_TIM_SET_COMPARE(&htim3 ,TIM_CHANNEL_1,node);
}








//测试程序
//uint16_t a=Node_ADC_Adjust();
//    printf("a=%d\n\r",a);
//		double b=Bright_ADC();
//	  printf("b=%.1f\n\r",b);
//    HAL_Delay(500);
//		double a=Node_ADC_Adjust();
//		Node_Adjust_Light(a);
		




