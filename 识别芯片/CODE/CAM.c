/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "CAM.h"
#include "data.h"
#include "SEEKFREE_MT9V03X.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*------------------------------*/
/*		  上升边线识别模块		*/
/*==============================*/
void rise_ident(void){
//	变量定义
	register unsigned char j;
	
} 
/*------------------------------*/   /*-----------------*/
/*		  播种地寻找模块		*/  /*     种子算法	   */
/*==============================*/ /*=================*/
static void cam_sow(void){
//	变量定义、初始化
	register unsigned char j;
	unsigned char bomrow = 0;//最低行
	efflp = 0, effrp = 0, cjug_sta = 0;
//	找左最低点
	for(j = 0; j < 80; j++){
		if(border[j] == 0) continue;
	//	留下痕迹
		ltra[efflp] = j, efflp++;
		if(bomrow < border[j]) bomrow = border[j], lbomp = j;
	}
//	重置后寻找右最低点
	bomrow = 0;
	for(j = 80; j < 160; j++){
		if(border[j] == 0) continue;
		rtra[effrp] = j, effrp++;
		if(bomrow < border[j]) bomrow = border[j], rbomp = j;
	}
//	记录最低点
	for(j = 0; j < 160; j++) borderid[j] = 0;
	borderid[lbomp] = 1, borderid[rbomp] = 1;
//	判断赛道类型
	if(border[lbomp] > 60) cjug_sta = 2;//右转
	if(border[rbomp] > 60) cjug_sta = 1;//左转
}
/*------------------------------*/
/*		摄像头边线识别模块		*/
/*==============================*/
void camident(void){
//	变量定义
	register unsigned char i, j, k;//图像行、列
	unsigned int imax, imin;
	unsigned char uplim;
//	标志位
	unsigned char foflag;
//	数值初始化
	uplim = 54+ident_bias;
//	边线识别
	for(j = 0; j < MT9V03X_W; j++){
	//	重置
		foflag = 0;
		for(i = ident_bias; i < uplim; i+=3){
		//	重置
			imax = 0, imin = 255;
			for(k = 0; k < 3; k++){
				if(mt9v03x_image[i+k][j] < imin) imin = mt9v03x_image[i+k][j];
				if(mt9v03x_image[i+k][j] > imax) imax = mt9v03x_image[i+k][j];
			}
			imax = imax<<1, imin = imin << 1;
			if(imax*imax - imin*imin > 28000) border[j] = i, foflag = 1;
		}
		if(!foflag) border[j] = 0; 
	}
//	调用种子算法
	cam_sow();
//	图像显示
	if(csimenu_flag[0]){
		ips200_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
		cam_draw();
	}
}
/*------------------------------*/
/*		摄像头边线显示模块		*/
/*==============================*/
void cam_draw(void){
//	变量定义
	register unsigned char j;
	for(j = 0; j < 160; j++){
		if(border[j] == 0) ips200_drawpoint(j, border[j], 0xfd78);//无效点
		else{
			switch(borderid[j]){
				case 0:ips200_drawpoint(j, border[j], 0xa75c);break;//未识别点
				case 1:ips200_drawpoint(j, border[j], 0xfd10);break;//最低点
			}
		}
	}
	switch(cjug_sta){
		case 0:ips200_showstr(160, 0, "direct");break;
		case 1:ips200_showstr(160, 0, "turn left");break;
		case 2:ips200_showstr(160, 0, "turn right");break;
	}
}
