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
/*		 编码器值获取模块		*/
/*==============================*/
void encoder_get(void){
//	获取编码器计数值后重置
	lcod = tim_encoder_get_count(TIM_3);
	rcod = -tim_encoder_get_count(TIM_4);
//	在屏幕上显示编码器计数值	
	ips200_showint16(0, 0, lcod);                 
	ips200_showint16(0, 1, rcod);
//	无线串口发送数据
//	data_conversion(lcod, ltcod, rcod, rtcod, temp);
}

/*------------------------------*/
/*		   电机驱动模块			*/
/*==============================*/
void motor_act(void){
	short lg, rg;
//	转向
	if(steer.rs >= 0) rg = steer.rs, lg = 0;//左转
	else lg = -steer.rs, rg = 0;//右转
//	左、右电机占空比设置
	if(acw.rs >= 0){	//正转
	//	左电机
		pwm_duty_updata(TIM_5, MOTOR_L1, acw.rs+lg);     		
		pwm_duty_updata(TIM_5, MOTOR_L0, 0);
	//	右电机
		pwm_duty_updata(TIM_5, MOTOR_R1, acw.rs+rg);     		
		pwm_duty_updata(TIM_5, MOTOR_R0, 0);
	}
	else{	//反转
	//	左电机
		pwm_duty_updata(TIM_5, MOTOR_L1, 0);                      		
		pwm_duty_updata(TIM_5, MOTOR_L0, -acw.rs+rg);
	//	右电机
		pwm_duty_updata(TIM_5, MOTOR_R1, 0);                      		
		pwm_duty_updata(TIM_5, MOTOR_R0, -acw.rs+lg);
	}
//	data_conversion(lcod, rcod, lg, rg, temp);
}
