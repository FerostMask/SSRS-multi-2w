/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "menu.h"
#include "Init.h"
#include "zf_pwm.h"
#include "zf_gpio.h"
#include "zf_tim.h"
#include "zf_exti.h"
/*--------------------------------------------------------------*/
/*							  宏定义							*/
/*==============================================================*/
#define u8 unsigned char                                    //8位数据
#define u16 unsigned short                                  //16位数据
#define u32 unsigned int                                    //32位数据
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*------------------------------*/
/*		 编码器初始化模块		*/
/*==============================*/
void Init_encoder(void){
//	编码器引脚初始化	
	tim_encoder_init(TIM_3, TIM_3_ENC1_B04, TIM_3_ENC2_B05);
	tim_encoder_init(TIM_4, TIM_4_ENC1_B06, TIM_4_ENC2_B07);
}
/*------------------------------*/
/*		  电机初始化模块		*/
/*==============================*/
void Init_motor(void){
//	端口初始化
//	电机引脚初始化 默认频率17kHz 初始占空比 0%
	pwm_init(TIM_5, MOTOR_R1, 17000, 0);
	pwm_init(TIM_5, MOTOR_R0, 17000, 1500);
	pwm_init(TIM_5, MOTOR_L1, 17000, 0);
	pwm_init(TIM_5, MOTOR_L0, 17000, 1500);
//	PID参数初始化
	Init_para();
}

/*------------------------------*/
/*		  按键初始化模块		*/
/*==============================*/
void Init_button(void){
//	按键中断初始化 | 最低优先级
	exti_interrupt_init(KEY1, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY2, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY3, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY4, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY5, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY6, EXTI_Trigger_Falling, 3, 3);
}
