/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "data.h"
/*--------------------------------------------------------------*/
/*							  宏定义							*/
/*==============================================================*/
#define u8 unsigned char                                    //8位数据
#define u16 unsigned short                                  //16位数据
#define u32 unsigned int                                    //32位数据

/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/
/*----------------------*/
/*	 	 电磁模块		*/
/*======================*/
//	结构体定义
struct adcpara adc0;
struct adcpara adc1;
struct adcpara adc2;
struct adcpara adc3;
struct adcpara adc4;
/*----------------------*/
/*	 	 MOTOR模块		*/
/*======================*/
//	PID

/*----------------------*/
/*	 	 菜单模块		*/
/*======================*/
//	汉字数组
unsigned char nom[128];
//	一级菜单
unsigned char menu[ROWS];
unsigned char menu_level;
unsigned char menu_index = 0;
//	二级菜单
unsigned char menu2_index = 0;
unsigned char menu2_level = 0;
//	标志位
unsigned char fixedflag = 0;//固定显示
unsigned char monitorflag = 0;//监视器
unsigned char csimenu_flag[CSIMENU_FLAG] = {0, 0};//摄像头
unsigned char wireless_flag[WIRELESS_FLAG] = {0, 0};//无线数据
//	函数指针
//void(*menu_pfc[])(unsigned char) = {menu_select, menu2_select};

/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*----------------------*/
/*	 	参数初始化		*/
/*======================*/
void Init_para(void){
//	电磁模块
	adc0.max = 3801, adc0.min = 187;
	adc1.max = 4095, adc1.min = 0;
	adc2.max = 4095, adc2.min = 0;
	adc3.max = 4095, adc3.min = 0;
	adc4.max = 4095, adc4.min = 0;
	
////	速度
//	speed.alpha = 0.3;
//	speed.Kp = 0.1;//反应快慢 | 超调
//	speed.Ki = 0.05;//反应力度
//	speed.Kd = 0;
//	speed.I = 0;
//	speed.e1 = 0, speed.e2 = 0, speed.e3 = 0;
//	speed.rs = 0;
}
