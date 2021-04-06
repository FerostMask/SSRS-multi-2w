/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "init.h"
#include "data.h"
#include "motor.h"
#include "zf_pwm.h"
#include "zf_tim.h"
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*------------------------------*/
/*	     ������ֵ��ȡģ��		*/
/*==============================*/
void encoder_get(void){
//	��ȡ����������ֵ������
	lcod = tim_encoder_get_count(TIM_3);
	rcod = -tim_encoder_get_count(TIM_4);
}
/*------------------------------*/
/*		   �������ģ��			*/
/*==============================*/
void motor_act(void){
	if(acw.rs >= 0){	//��ת
	//	����
		pwm_duty_updata(TIM_5, MOTOR_L1, acw.rs+steer.rs);     		
		pwm_duty_updata(TIM_5, MOTOR_L0, 0);
	//	�ҵ��
		pwm_duty_updata(TIM_5, MOTOR_R1, acw.rs-steer.rs);     		
		pwm_duty_updata(TIM_5, MOTOR_R0, 0);
	}
	else{	//��ת
	//	����
		pwm_duty_updata(TIM_5, MOTOR_L1, 0);                      		
		pwm_duty_updata(TIM_5, MOTOR_L0, -acw.rs-steer.rs);
	//	�ҵ��
		pwm_duty_updata(TIM_5, MOTOR_R1, 0);                      		
		pwm_duty_updata(TIM_5, MOTOR_R0, -acw.rs+steer.rs);
	}
}
