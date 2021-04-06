/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "data.h"
#include "menu.h"
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/
/*----------------------*/
/*	 	 驱动模块		*/
/*======================*/
//	编码器
short spd = 0;
short rad = 0;
short lcod, rcod;
/*----------------------*/
/*	 	 平衡模块		*/
/*======================*/
short blcp = 245;
short pita;
short gy, gz;
short yfilt[4] = {0, 0, 0, 0};
short pflit[4] = {0, 0, 0, 0};
/*----------------------*/
/*	 	  PID模块		*/
/*======================*/
//	速度、转向、角度、角速度
struct pidpara speed;
struct pidpara steer;
struct pidpara angle;
struct pidpara acw;
/*----------------------*/
/*	 	 菜单模块		*/
/*======================*/
//	函数指针数组 | 菜单选择
void(*menu_pfc[2])(unsigned char) = {menu_select, menu2_select};
//	菜单名
unsigned char nom[128];
//	一级菜单
char menu[ROWS];
unsigned char menu_level = 0;//级别
unsigned char menu_index = 0;//行索引
//	按钮
unsigned char csimenu_flag[CSIMENU_FLAG] = {0, 0};//摄像头
unsigned char wireless_flag[WIRELESS_FLAG] = {0, 0};//无线数据

/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*----------------------*/
/*	 	参数初始化		*/
/*======================*/
void Init_para(void){
//	速度
	speed.alpha = 0.3;
	speed.Kp = 0.1;//反应快慢 | 超调
	speed.Ki = 0.05;//反应力度
	speed.Kd = 0;
	speed.I = 0;
	speed.e1 = 0, speed.e2 = 0, speed.e3 = 0;
	speed.rs = 0;
	
//	转向
	steer.alpha = 0.3;
	steer.Kp = 10;//反应快慢 | 超调
	steer.Ki = 1;//反应力度
	steer.Kd = 1;
	steer.I = 0;
	steer.e1 = 0, steer.e2 = 0, steer.e3 = 0;
	steer.rs = 0;
	
//	角度
	angle.Kp = 1.2;//力度
	angle.Ki = 0;
	angle.Kd = 2;//抖动
	angle.e1 = 0, angle.e2 = 0, angle.e3 = 0; 
	angle.rs = 0;

//	角速度
	acw.alpha = 0.3;
	acw.Kp = 30;//反应快慢 | 超调
	acw.Ki = 1.7;//反应力度
	acw.Kd = 2.4;
	acw.I = 0;
	acw.e1 = 0, acw.e2 = 0, acw.e3 = 0;
	acw.rs = 0;
}
