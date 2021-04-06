/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "init.h"
#include "data.h"
#include "motor.h"
#include "zf_pwm.h"
#include "zf_tim.h"
/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*------------------------------*/
/*	     编码器值获取模块		*/
/*==============================*/
void encoder_get(void){
//	获取编码器计数值后重置
	lcod = tim_encoder_get_count(TIM_3);
	rcod = -tim_encoder_get_count(TIM_4);
}
/*------------------------------*/
/*		   电机驱动模块			*/
/*==============================*/
void motor_act(void){
	if(acw.rs >= 0){	//正转
	//	左电机
		pwm_duty_updata(TIM_5, MOTOR_L1, acw.rs+steer.rs);     		
		pwm_duty_updata(TIM_5, MOTOR_L0, 0);
	//	右电机
		pwm_duty_updata(TIM_5, MOTOR_R1, acw.rs-steer.rs);     		
		pwm_duty_updata(TIM_5, MOTOR_R0, 0);
	}
	else{	//反转
	//	左电机
		pwm_duty_updata(TIM_5, MOTOR_L1, 0);                      		
		pwm_duty_updata(TIM_5, MOTOR_L0, -acw.rs-steer.rs);
	//	右电机
		pwm_duty_updata(TIM_5, MOTOR_R1, 0);                      		
		pwm_duty_updata(TIM_5, MOTOR_R0, -acw.rs+steer.rs);
	}
}
