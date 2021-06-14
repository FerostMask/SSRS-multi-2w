#ifndef _DATA_H
#define _DATA_H
#include "menu.h"
#include "menu_2.h"
/*--------------------------------------------------------------*/
/*							  宏定义							*/
/*==============================================================*/
//	按键标志位
#define CSIMENU_FLAG 2
#define STATE_FLAG 3
//	一级菜单
#define ROWS 5
#define menu_limit0 1
#define menu_limit1 2
#define menu_limit2 2
#define menu_limit3 0
#define menu_limit4 0
//	菜单属性编号
#define MENU_SWITCH 0
#define PARASET_PID1 1
#define PARASET_PID2 2
#define PARASET_OPER 3
#define MONITOR_MENU 4
//	flash参数存储
#define FLASH_NUM 19
#define FLASH_MEMORY_SLECTION FLASH_SECTION_112
/*------------------------------------------------------*/
/* 					  外部变量声明 						*/
/*======================================================*/
/*----------------------*/
/*	    线性CCD模块		*/
/*======================*/
extern unsigned cjug_sta;
/*----------------------*/
/*	 	 MOTOR模块		*/
/*======================*/
//	编码器
extern short lcod, rcod;			//编码器读数
extern short ltcod, rtcod;          //编码器目标值
extern short lef_pwm, rig_pwm;
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

//	电机
extern struct pidpara speed;
extern struct pidpara lefdif;
extern struct pidpara rigdif;
extern struct pidpara steer;
//	角度调定参数
extern struct pidpara angle;
//	角速度
extern struct pidpara acw;

/*----------------------*/
/*	   角度控制模块		*/
/*======================*/
extern int gy, gz;
extern short blcp;
extern short pita, yawa, yawa_temp;
extern short yfilt[4];
extern short pflit[4];

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
extern unsigned char state_flag[STATE_FLAG];
extern unsigned char menu_level;
//	二级菜单
extern unsigned char menu2_index;
extern unsigned char menu2_level;
//	函数指针
extern void(*menu_pfc[])(unsigned char);
/*----------------------*/
/*	 	 通信模块		*/
/*======================*/
extern unsigned char buff_get6, buff_get7;
extern unsigned char dst_flag, final_flag;
extern unsigned char launch_command[3];
extern int distance;
/*------------------------------------------------------*/ 
/* 						函数声明 						*/
/*======================================================*/
void Init_para(void);
char flash_init(void);
void first_flash_init(void);
void flash_memory_write(row, col);
#endif
