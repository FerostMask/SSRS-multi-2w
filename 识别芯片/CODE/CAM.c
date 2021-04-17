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
/*		摄像头边线识别模块		*/
/*==============================*/
void camindet(void){
//	变量定义
	register unsigned char i, j, k;//图像行、列
	unsigned int imax, imin;
	unsigned char uplim;
//	数值初始化
	uplim = 63+ident_bias;
//	边线识别
	for(j = 0; j < MT9V03X_W; j++){
		for(i = ident_bias; i < uplim; i+=3){
		//	重置
			imax = 0, imin = 255;
			for(k = 0; k < 3; k++){
				if(mt9v03x_image[i+k][j] < imin) imin = mt9v03x_image[i+k][j];
				if(mt9v03x_image[i+k][j] > imax) imax = mt9v03x_image[i+k][j];
			}
			imax = imax<<1, imin = imin << 1;
			if(imax*imax - imin*imin > 28000) border[j] = i;
		}
	}
//	图像显示
	if(csimenu_flag[0]){
		ips200_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
		for(j = 0; j < 160; j++)
			ips200_drawpoint(j, border[j], 0xa75c);
	}
}
/*------------------------------*/
/*		摄像头边线显示模块		*/
/*==============================*/
void cam_draw(void){
//	变量定义
	register unsigned char j;	
}
