/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "data.h"
#include "init.h"
#include "zf_pwm.h"
#include "zf_tim.h"
#include "zf_exti.h"
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*------------------------------*/
/*		 ��������ʼ��ģ��		*/
/*==============================*/
void Init_encoder(void){
//	���������ų�ʼ��	
	tim_encoder_init(TIM_3, TIM_3_ENC1_B04, TIM_3_ENC2_B05);
	tim_encoder_init(TIM_4, TIM_4_ENC1_B06, TIM_4_ENC2_B07);
}
/*------------------------------*/
/*		  �����ʼ��ģ��		*/
/*==============================*/
void Init_motor(void){
//	������ų�ʼ�� Ĭ��Ƶ��17kHz ��ʼռ�ձ� 0%
	pwm_init(TIM_5, MOTOR_R1, 17000, 0);
	pwm_init(TIM_5, MOTOR_R0, 17000, 0);
	pwm_init(TIM_5, MOTOR_L1, 17000, 0);
	pwm_init(TIM_5, MOTOR_L0, 17000, 0);
}
/*------------------------------*/
/*		�����жϳ�ʼ��ģ��		*/
/*==============================*/
void Init_button(void){
//	�����жϳ�ʼ�� | ������ȼ�
	exti_interrupt_init(KEY1, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY2, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY3, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY4, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY5, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY6, EXTI_Trigger_Falling, 3, 3);
}
