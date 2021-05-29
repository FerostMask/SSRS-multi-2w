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
/*	    线性CCD模块		*/
/*======================*/
unsigned cjug_sta;
/*----------------------*/
/*	 	 MOTOR模块		*/
/*======================*/
//	编码器
short lcod = 0,rcod = 0;
short spd = 0;
short rad = 0;
short lef_pwm, rig_pwm;
//	PID
struct pidpara speed;
struct pidpara lefdif;
struct pidpara rigdif;
struct pidpara steer;
struct pidpara angle;
struct pidpara acw;
/*----------------------*/
/*	   角度控制模块		*/
/*======================*/
short blcp = 330;
short pita, yawa, yawa_temp;
short gy, gz;
short yfilt[4] = {0, 0, 0, 0};
short pflit[4] = {0, 0, 0, 0};
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
void(*menu_pfc[])(unsigned char) = {menu_select, menu2_select};
/*----------------------*/
/*	 	 通信模块		*/
/*======================*/
unsigned char buff_get6, buff_get7;
unsigned char dst_flag = 0, final_flag = 0;
unsigned char launch_command[3] = {0xA7, 0xB9, 0x12};
int distance = 0;
/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*----------------------*/
/*	 	参数初始化		*/
/*======================*/
//	PID
void Init_para(void){
//	速度
	speed.alpha = 0.1;
	speed.Kp = 1.1;//反应快慢 | 超调
	speed.Ki = 0.01;//反应力度
	speed.Kd = 0.0;
	speed.I = 0;
	speed.e1 = 0, speed.e2 = 0, speed.e3 = 0;
	speed.rs = 0;
	
//	左轮差速
	lefdif.alpha = 0.3;
	lefdif.Kp = 30;//反应快慢 | 超调
	lefdif.Ki = 0.75;//反应力度
	lefdif.Kd = 0;
	lefdif.I = 0;
	lefdif.e1 = 0, lefdif.e2 = 0, lefdif.e3 = 0;
	lefdif.rs = 0;

//	右轮差速
	rigdif.alpha = 0.3;
	rigdif.Kp = 30;//反应快慢 | 超调
	rigdif.Ki = 0.75;//反应力度
	rigdif.Kd = 0;
	rigdif.I = 0;
	rigdif.e1 = 0, rigdif.e2 = 0, rigdif.e3 = 0;
	rigdif.rs = 0;
	
//	转向
	steer.alpha = 0.3;
	steer.Kp = 1.8;//反应快慢 | 超调
	steer.Ki = 0;//反应力度
	steer.Kd = 0.6;
	steer.I = 0;
	steer.e1 = 0, steer.e2 = 0, steer.e3 = 0;
	steer.rs = 0;	
	
////	转向
//	steer.alpha = 0.3;
//	steer.Kp = 167;//反应快慢 | 超调
//	steer.Ki = 0;//反应力度
//	steer.Kd = 1.5;
//	steer.I = 0;
//	steer.e1 = 0, steer.e2 = 0, steer.e3 = 0;
//	steer.rs = 0;
	
//	角度
	angle.Kp = 2.6;//力度
	angle.Ki = 0;
	angle.Kd = 0.15;//抖动
	angle.e1 = 0, angle.e2 = 0, angle.e3 = 0; 
	angle.rs = 0;

//	角速度
	acw.alpha = 0.05;
	acw.Kp = 37;//反应快慢 | 超调
	acw.Ki = 0.29;//反应力度
	acw.Kd = 0.0;
	acw.I = 0;
	acw.e1 = 0, acw.e2 = 0, acw.e3 = 0;
	acw.rs = 0;
}
