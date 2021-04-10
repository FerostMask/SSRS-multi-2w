#ifndef _DATA_H
#define _DATA_H
#include "menu.h"
#include "menu_2.h"
/*--------------------------------------------------------------*/
/*							  宏定义							*/
/*==============================================================*/
//	按键标志位
#define CSIMENU_FLAG 2
#define WIRELESS_FLAG 2
//	一级菜单
#define ROWS 4
#define menu_limit0 1
#define menu_limit1 3
#define menu_limit2 0
#define menu_limit3 0
/*------------------------------------------------------*/
/* 					  外部变量声明 						*/
/*======================================================*/
/*----------------------*/
/*	 	 电磁模块		*/
/*======================*/
//	结构体声明
typedef struct adcpara{
	unsigned short value;
	unsigned short max;
	unsigned short min;
	unsigned short pin;
}adcpara;
//	全局结构体声明
extern struct adcpara adc0;
extern struct adcpara adc1;
extern struct adcpara adc2;
extern struct adcpara adc3;
extern struct adcpara adc4;
/*----------------------*/
/*	 	 MOTOR模块		*/
/*======================*/
//	电机
extern short spd;
extern short rad;
/*----------------------*/
/*	 	  PID模块		*/
/*======================*/
//	结构体声明
typedef struct pidpara{
	float alpha;
	float Kp;
	float Ki;
	float Kd;
	float I;
	int e1;
	int e2;
	int e3;
	short rs;
}pidpara;


/*----------------------*/
/*	 	 菜单模块		*/
/*======================*/
//	一级菜单
extern unsigned char menu_index;
extern unsigned char menu[ROWS];
extern unsigned char nom[128];
extern unsigned char fixedflag;
extern unsigned char monitorflag;
extern unsigned char csimenu_flag[CSIMENU_FLAG];
extern unsigned char wireless_flag[WIRELESS_FLAG];
extern unsigned char menu_level;
//	二级菜单
extern unsigned char menu2_index;
extern unsigned char menu2_level;
//	函数指针

/*------------------------------------------------------*/ 
/* 						函数声明 						*/
/*======================================================*/
void Init_para(void);

#endif
