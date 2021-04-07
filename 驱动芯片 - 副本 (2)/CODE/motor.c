/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "motor.h"
#include "pid.h"
#include "Init.h"
#include "zf_pwm.h"
#include "zf_tim.h"
#include "SEEKFREE_VIRSCO.h"
#include "SEEKFREE_WIRELESS.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/*							  �궨��							*/
/*==============================================================*/
#define u8 unsigned char                                    //8λ����
#define u16 unsigned short                                  //16λ����
#define u32 unsigned int                                    //32λ����
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
//unsigned char temp[4] = {0, 0, 0, 0};
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*------------------------------*/
/*		 ������ֵ��ȡģ��		*/
/*==============================*/
void encoder_get(void){
//	��ȡ����������ֵ������
	lcod = tim_encoder_get_count(TIM_3);
	rcod = -tim_encoder_get_count(TIM_4);
//	����Ļ����ʾ����������ֵ	
//	ips200_showint16(0, 0, lcod);                 
//	ips200_showint16(0, 1, rcod);
//	���ߴ��ڷ�������
//	data_conversion(lcod, ltcod, rcod, rtcod, temp);
}

/*------------------------------*/
/*		   �������ģ��			*/
/*==============================*/
void motor_act(void){
	short lg, rg;
//	ת��
	if(steer.rs >= 0) rg = steer.rs, lg = 0;//��ת
	else lg = -steer.rs, rg = 0;//��ת
//	���ҵ��ռ�ձ�����
	if(acw.rs >= 0){	//��ת
	//	����
		pwm_duty_updata(TIM_5, MOTOR_L1, acw.rs+lg);     		
		pwm_duty_updata(TIM_5, MOTOR_L0, 0);
	//	�ҵ��
		pwm_duty_updata(TIM_5, MOTOR_R1, acw.rs+rg);     		
		pwm_duty_updata(TIM_5, MOTOR_R0, 0);
	}
	else{	//��ת
	//	����
		pwm_duty_updata(TIM_5, MOTOR_L1, 0);                      		
		pwm_duty_updata(TIM_5, MOTOR_L0, -acw.rs+rg);
	//	�ҵ��
		pwm_duty_updata(TIM_5, MOTOR_R1, 0);                      		
		pwm_duty_updata(TIM_5, MOTOR_R0, -acw.rs+lg);
	}
//	data_conversion(lcod, rcod, lg, rg, temp);
}
