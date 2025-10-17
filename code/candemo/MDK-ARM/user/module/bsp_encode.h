#ifndef __BSP_ENCODE_H__
#define __BSP_ENCODE_H__

#include "stm32f1xx_hal.h"



typedef struct Encode_t 
{  


   uint32_t _current_count;	// 减速比30:1
	 int16_t _delta_count; 
	 int16_t _last_count; 
	
		 int16_t overflow_count;
	   int32_t _total_count;
	
	 //int16_t _last_count; 
	
	
	
   float _motor_speed_mm;
	 float _motor_distance_mm;
	 float _motor_speed_r;


}Encode_t;
//初始化编码

void bsp_encode_init(void);

void Encode_Calculated_distance_r(Encode_t * encodeA);
void HAL_TIM_PeriodCallback(TIM_HandleTypeDef *htim);
void speed();

#endif //__BSP_MOTOR_H__
