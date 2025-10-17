#include "bsp_encode.h"
#include <tim.h>

//���嶨ʱ��
#define htim_A htim3
#define htim_B htim4
// ����������
#define ENCODER_LINES 13u      // ����������
#define GEAR_RATIO 20u         // ���ٱ�30:1
#define MOTOR_WHEEL_STRAIGHT_MM    48 // ����ֱ������λmm
#define wheel_circumference   MOTOR_WHEEL_STRAIGHT_MM*3.1415926 // �����ܳ�(cm) [2](@ref)
// ��ʱ������
#define QUADRATURE_FACTOR 4   // �ı�Ƶ
#define SAMPLE_TIME_MS 20    // 20ms ����50HZ
#define COUNTER_MAX 65535     // 16λ���������ֵ

Encode_t encodeA;
Encode_t encodeB;





void bsp_encode_init(void)
{

  
    HAL_TIM_Encoder_Start(&htim_A, TIM_CHANNEL_ALL); //�?启编码器模式
    HAL_TIM_Encoder_Start(&htim_B, TIM_CHANNEL_ALL); //�?启编码器模式
	
	
	  HAL_TIM_Base_Start_IT(&htim_A); // ���ø����ж�
	  HAL_TIM_Base_Start_IT(&htim_B); // ���ø����ж�
	
	
	
	 __HAL_TIM_SetCounter(&htim_A, 30000);//��ռ���ֵ
	 __HAL_TIM_SetCounter(&htim_B, 30000);//��ռ���ֵ
	

}


 

void speed()
{
	     
			
			

      
      encodeA._current_count = __HAL_TIM_GetCounter(&htim_A);//��ȡ������
			
			encodeA._total_count=-((encodeA.overflow_count-1)*30000+(encodeA._current_count-30000));
		  encodeA._delta_count =encodeA._total_count - (encodeA._last_count);
			
				  	
		  encodeA._motor_speed_r= (float)(encodeA._delta_count) / 
                     (ENCODER_LINES * QUADRATURE_FACTOR * GEAR_RATIO ) * 50;
		  encodeA._last_count= encodeA._total_count; // ������ʷֵ
			
			
			
			
			encodeB._current_count = __HAL_TIM_GetCounter(&htim_B);//��ȡ������
			
			encodeB._total_count=(encodeB.overflow_count-1)*30000+(encodeB._current_count-30000);
			encodeB._delta_count =encodeB._total_count - (encodeB._last_count);

			
		 
      encodeB._motor_speed_r= (float)(encodeB._delta_count) / 
                     (ENCODER_LINES * QUADRATURE_FACTOR * GEAR_RATIO ) * 50;


	


      encodeB._last_count= encodeB._total_count; // ������ʷֵ
		
		
		
	//	printf("%f,%f\n",encodeA._motor_speed_r,encodeB._motor_speed_r);

		 
	
	
	
	
	 
		 
			

		 
		//printf("%d,%d\n",encodeA._total_count,encodeB._total_count);
			
			
			
			
			
			
			
			
			
			
			
			
			










}


void HAL_TIM_PeriodCallback(TIM_HandleTypeDef *htim)
{
   


		
		  if (htim->Instance == htim4.Instance)
			 {
				 
				 
				 uint8_t dir = (htim->Instance->CR1 & TIM_CR1_DIR) ? 1 : 0;
        
        if (dir == 0) {  // ������תʱ���
            encodeA.overflow_count++; // +65536
        } else {         // ������תʱ���
            encodeA.overflow_count--; // -65536
        }
				//htim3.Instance->CNT=0;
				__HAL_TIM_SetCounter(&htim4, 30000);//��ռ���ֵ
        __HAL_TIM_CLEAR_IT(htim, TIM_IT_UPDATE); // ����жϱ�־[6](@ref)
				 
				 
				 
				 
				 
				 
				 
			 
			 
			 }
			 if (htim->Instance == htim3.Instance)
			 {
				 
				 
				 
				 				 uint8_t dir = (htim->Instance->CR1 & TIM_CR1_DIR) ? 1 : 0;
        
        if (dir == 0) {  // ������תʱ���
            encodeB.overflow_count++; // +65536
        } else {         // ������תʱ���
            encodeB.overflow_count--; // -65536
        }
				//htim3.Instance->CNT=0;
				__HAL_TIM_SetCounter(&htim3, 30000);//��ռ���ֵ
        __HAL_TIM_CLEAR_IT(htim, TIM_IT_UPDATE); // ����жϱ�־[6](@ref)
				 
				 
				 

				 
				 
			 
			 
			 }
		
		
		
	
		
}
