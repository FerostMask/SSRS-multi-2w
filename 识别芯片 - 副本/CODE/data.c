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
/*	 	摄像头模块		*/
/*======================*/
//	阈值
unsigned short imgthrsod = 28000;
//	识别状态
unsigned char cjug_sta;
//	左右边界（存列）
unsigned char lefbor[EFF_ROW+1], rigbor[EFF_ROW+1], mid_point[EFF_ROW+1];
unsigned char lefp, rigp, midp;
//	斜率
float lefslope, rigslope, midslope;
//	ver3
float P[256] = {0}, PK[256] = {0}, MK[256] = {0};
unsigned char gray_img[MT9V03X_H][MT9V03X_W];
unsigned char img_thrsod;
/*----------------------*/
/*	 	 电磁模块		*/
/*======================*/
//	结构体定义
struct adcpara adc0;
struct adcpara adc1;
struct adcpara adc2;
struct adcpara adc3;
struct adcpara adc4;
struct adcerrpa adc_err;
//	状态标志位
unsigned char ajug_sta;
short spd;
/*----------------------*/
/*	 	 控制模块		*/
/*======================*/
//	PID
struct pidpara adc_steering;
struct pidpara cam_steering;
/*----------------------*/
/*	 	 菜单模块		*/
/*======================*/
//	汉字数组
unsigned char nom[128];
//	一级菜单
unsigned char menu[ROWS] = {0, 0, 0, 0};
unsigned char menu_level;
unsigned char menu_index = 0;
//	二级菜单
unsigned char menu2_index = 0;
unsigned char menu2_level = 0;
//	标志位
unsigned char excollflag = 0;//电磁极值采集标志位
unsigned char fixedflag = 0;//固定显示
unsigned char monitorflag = 0;//监视器
unsigned char csimenu_flag[CSIMENU_FLAG] = {0, 0};//摄像头
unsigned char wireless_flag[WIRELESS_FLAG] = {0, 0};//无线数据
//	函数指针
void(*menu_pfc[])(unsigned char) = {menu_select, menu2_select};
/*----------------------*/
/*	 	 有来有去		*/
/*======================*/
unsigned char subuff_num = 0;
unsigned char subuff_arr[3];
unsigned short subuff_ranging;
/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*----------------------*/
/*	 	参数初始化		*/
/*======================*/
void Init_para(void){
//	电磁模块
	adc0.max = 3823, adc0.min = 102;
	adc1.max = 3815, adc1.min = 98;
	adc2.max = 4095, adc2.min = 0;
	adc3.max = 3815, adc3.min = 117;
	adc4.max = 3827, adc4.min = 38;
//	差比和差
	adc_err.alpha = 15;
	adc_err.beta = 90;
	adc_err.omega = 0.2;
	adc_err.P = 60;
//	ADC转向
	adc_steering.Kp = 0.21;
	adc_steering.Kd = 0.6;
//	CAM转向
	cam_steering.Kp = 1;
	cam_steering.Kd = 1;
////	速度
//	speed.alpha = 0.3;
//	speed.Kp = 0.1;//反应快慢 | 超调
//	speed.Ki = 0.05;//反应力度
//	speed.Kd = 0;
//	speed.I = 0;
//	speed.e1 = 0, speed.e2 = 0, speed.e3 = 0;
//	speed.rs = 0;
}
