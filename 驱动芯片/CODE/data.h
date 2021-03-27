#ifndef _DATA_H
#define _DATA_H
/*--------------------------------------------------------------*/
/*							  宏定义							*/
/*==============================================================*/
#define CSIMENU_FLAG 2
#define WIRELESS_FLAG 2
/*------------------------------------------------------*/
/* 					  外部变量声明 						*/
/*======================================================*/
/*----------------------*/
/*	 	 MOTOR模块		*/
/*======================*/
//	编码器
extern short lcod, rcod;			//编码器读数
extern short ltcod, rtcod;          //编码器目标值
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
extern struct pidpara steer;
//	角度调定参数
extern struct pidpara angle;
//	角速度
extern struct pidpara acw;

/*----------------------*/
/*	   角度控制模块		*/
/*======================*/
extern short pita;
extern short yawa[2];
extern short yfilt[4];
extern short gy;
extern short pflit[4];
extern short blcp;

/*----------------------*/
/*	 	 菜单模块		*/
/*======================*/
//	一级菜单名
extern unsigned char first_nom[128];
extern unsigned char fixedflag;
extern unsigned char monitorflag;
extern unsigned char csimenu_flag[CSIMENU_FLAG];
extern unsigned char wireless_flag[WIRELESS_FLAG];

/*------------------------------------------------------*/ 
/* 						函数声明 						*/
/*======================================================*/
void Init_para(void);

#endif
