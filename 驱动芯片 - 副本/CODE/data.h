/*------------------------------------------------------*/
/* 					   头文件声明 						*/
/*======================================================*/
#ifndef _DATA_H
#define _DATA_H
/*------------------------------------------------------*/
/* 					  	 宏定义 						*/
/*======================================================*/
#define CSIMENU_FLAG 2
#define WIRELESS_FLAG 2
//	一级菜单
#define ROWS 4//	菜单行数
//	菜单列限制
#define LIMIT0 1
#define LIMIT1 3
#define LIMIT2 0
#define LIMIT3 0
/*------------------------------------------------------*/
/* 					  外部变量声明 						*/
/*======================================================*/
/*----------------------*/
/*	 	 驱动模块		*/
/*======================*/
extern short spd;
extern short rad;
extern short lcod, rcod;
/*----------------------*/
/*	 	 平衡模块		*/
/*======================*/
extern short blcp;
extern short pita;
extern short gy, gz;
extern short yfilt[4];
extern short pflit[4];
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
extern struct pidpara steer;
//	角度
extern struct pidpara angle;
//	角速度
extern struct pidpara acw;
/*----------------------*/
/*	 	 菜单模块		*/
/*======================*/
extern void(*menu_pfc[2])(unsigned char event);
extern unsigned char nom[128];
extern char menu[ROWS];
extern unsigned char menu_level;
extern unsigned char menu_index;
extern unsigned char csimenu_flag[CSIMENU_FLAG];
extern unsigned char wireless_flag[WIRELESS_FLAG];
/*------------------------------------------------------*/ 
/* 						函数声明 						*/
/*======================================================*/
void Init_para(void);
#endif
