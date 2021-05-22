/*--------------------------------------------------------------*/
/*							头文件加载							*/
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
/*							  宏定义							*/
/*==============================================================*/
#define u8 unsigned char                                    //8位数据
#define u16 unsigned short                                  //16位数据
#define u32 unsigned int                                    //32位数据
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/
//unsigned char temp[4] = {0, 0, 0, 0};
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
	if(dst_flag){
		distance += (lcod+rcod)>>1;
		if(distance > 100000)
			final_flag = 1, dst_flag = 0;
	}
//	显示计数值
//	ips200_showint16(0, 0, lcod);
//	ips200_showint16(0, 1, rcod);
}
/*------------------------------*/
/*		   电机驱动模块			*/
/*==============================*/
void motor_act(void){
//	PWM计算
	lef_pwm = acw.rs-steer.rs;
	rig_pwm = acw.rs+steer.rs;
	if(abs(lef_pwm > 7000)){
		if(lef_pwm > 0) lef_pwm = 7000;
		else lef_pwm = -7000;
	}
	if(abs(rig_pwm > 7000)){
		if(rig_pwm > 0) rig_pwm = 7000;
		else rig_pwm = -7000;
	}
//	左电机
	if(lef_pwm >= 0){	//	正转
		pwm_duty_updata(TIM_5, MOTOR_L1, lef_pwm);     		
		pwm_duty_updata(TIM_5, MOTOR_L0, 0);
	}
	else{	//	反转
		pwm_duty_updata(TIM_5, MOTOR_L1, 0);                      		
		pwm_duty_updata(TIM_5, MOTOR_L0, -lef_pwm);
	}
//	右电机
	if(rig_pwm >= 0){
		pwm_duty_updata(TIM_5, MOTOR_R1, rig_pwm);     		
		pwm_duty_updata(TIM_5, MOTOR_R0, 0);
	}
	else{
		pwm_duty_updata(TIM_5, MOTOR_R1, 0);                      		
		pwm_duty_updata(TIM_5, MOTOR_R0, -rig_pwm);
	}
}
