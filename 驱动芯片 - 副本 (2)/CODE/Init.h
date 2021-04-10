/*------------------------------------------------------*/
/* 					   头文件声明 						*/
/*======================================================*/
#ifndef _INIT_H
#define _INIT_H
/*------------------------------------------------------*/
/* 					   头文件调用 						*/
/*======================================================*/
#include "data.h"
/*------------------------------------------------------*/ 
/* 						 宏定义 						*/
/*======================================================*/
#define MOTOR_R1 TIM_5_CH1_A00                   		//左电机 正转引脚
#define MOTOR_R0 TIM_5_CH2_A01                   		//左电机 反转引脚

#define MOTOR_L1 TIM_5_CH3_A02                   		//右电机 正转引脚
#define MOTOR_L0 TIM_5_CH4_A03                   		//右电机 反转引脚                   

////	按键-列
//#define column1 D4
//#define column2 D27
//#define column3 C31
////	按键-行
//#define row1 C27
//#define row2 C26
//	按键引脚定义
#define KEY1 D0
#define KEY2 D1
#define KEY3 D2
#define KEY4 D3
#define KEY5 D14
#define KEY6 D15
/*------------------------------------------------------*/
/* 					  外部变量声明 						*/
/*======================================================*/
/*----------------------*/
/*	 	 模块名称		*/
/*======================*/

/*------------------------------------------------------*/ 
/* 						函数声明 						*/
/*======================================================*/
void Init_encoder(void);
void Init_motor(void);
void Init_button(void);
#endif
