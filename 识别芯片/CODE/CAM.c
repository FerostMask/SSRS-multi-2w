/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "CAM.h"
#include "pid.h"
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
/*		   斜率计算模块			*/
/*==============================*/
static void cal_slope(void){
//	变量定义、初始化
	register unsigned char i, count;
	lefslope = 0, rigslope = 0, midslope = 0;
//	计算斜率（左边线
	count = lefp;
	for(i = EFF_ROW-2; count > 0; i--, count--)
		lefslope += atan(lefbor[i]-lefbor[i+1])*57.3;
	lefslope = lefslope/(lefp-1);
//	右边线
	count = rigp;
	for(i = EFF_ROW-2; count > 0; i--, count--)
		rigslope += atan(rigbor[i]-rigbor[i+1])*57.3;
	rigslope = rigslope/(rigp-1);
//	中线
	count = midp;
	for(i = EFF_ROW-2; count > 0; i--, count--)
		midslope += atan(mid_point[i]-mid_point[i+1])*57.3;
	midslope = midslope/(midp-1);
}
/*------------------------------*/
/*		   元素判断模块			*/
/*==============================*/
static void element_jug(void){
//	变量定义、初始化
	register unsigned char i, count;
	count = midp, cjug_sta = 1;
//	识别点数量过少，通过斜率判断转向
	if(midp < 17){
		if(lefp < 21)
			if(rigp < 21){
				if(midslope < -15){cjug_sta = 22;return;}//左转
				if(midslope > 15){cjug_sta = 28;return;}//右转
			}
		if(lefp > rigp){
			if(lefslope > 47){cjug_sta = 28;return;}//右转
		}
		else
			if(rigslope < -47){cjug_sta = 22; return;}//左转
	}
	else{
		if(midslope > 30){cjug_sta = 28;return;}
		if(midslope < -30){cjug_sta = 22;return;}
		if(mid_point[EFF_ROW-midp]-mid_point[EFF_ROW-1] > 10){cjug_sta = 28;return;}
		if(mid_point[EFF_ROW-midp]-mid_point[EFF_ROW-1] < -10){cjug_sta = 22;return;}
	}
////	判断是否识别失败
//	if(midp < 17){
//		if(lefp < 21)
//			if(rigp < 21){
//			//	临时代码，粗略检测偏移方向
//				for(i = EFF_ROW-2; count > 1; i--, count--)
//					slope += mid_point[i] - mid_point[i+1];
//				if(slope > 0) cjug_sta = 28;
//				else cjug_sta = 22;
//			}//边线识别失败	
//		if(lefp > rigp){//右转检测
//			if(lefbor[EFF_ROW-lefp]>80){cjug_sta = 29;return;}
//			else{cjug_sta = 201;return;}//右边线检测失败（做斜率检测
//		}
//		else{//左转检测
//			if(rigbor[EFF_ROW-rigp]<80){cjug_sta = 21;return;}
//			else{cjug_sta = 202;return;}//左边线检测失败
//		}
//	}
//	else{
//		if(mid_point[37] < 75) cjug_sta = 22;return;//左转
//		if(mid_point[37] > 85) cjug_sta = 28;return;//右转
////		for(i = EFF_ROW; count > 0; i--, count--){
////		//	临时代码
////			if(mid_point[42] < 75) cjug_sta = 22;return;//左转
////			if(mid_point[42] > 85) cjug_sta = 28;return;//右转
////		}
//	}
} 
/*------------------------------*/
/*		   中线拟合模块			*/
/*==============================*/
static void mid_fit(void){
//	变量定义、初始化
	register unsigned char i, count;
	if(lefp > rigp) count = rigp;
	else count = lefp;
	midp = count;
//	拟合中线
	for(i = EFF_ROW-1; count > 0; i--, count--)
		mid_point[i] = (lefbor[i]+rigbor[i])/2;
	if(midp > 9){
		pos_pid(&cam_steering, 80, mid_point[EFF_ROW-midp+5], 50, -50);
		uart_putchar(UART_7, cam_steering.rs);
	}
}
/*------------------------------*/
/*		  基准点寻找模块		*/
/*==============================*/
static char foundation(char num){
//	变量定义
	register unsigned char j, k;
	unsigned char imax = 0, imin = 255, row = EFF_ROW-1;
	switch(num){
		case 1://左基准点
			for(j = 0; j < 158; j++){
				imax = 0, imin = 255;
				for(k = 0; k < 3; k++){
					if(mt9v03x_image[row][j+k] < imin) imin = mt9v03x_image[row][j+k];
					if(mt9v03x_image[row][j+k] > imax) imax = mt9v03x_image[row][j+k];
				}
				imax = imax<<1, imin = imin << 1;
				if(imax*imax - imin*imin > imgthrsod) return j+10;
			}
			break;
		case 2://右基准点
			for(j = 159; j > 1; j--){
				imax = 0, imin = 255;
				for(k = 0; k < 3; k++){
					if(mt9v03x_image[row][j-k] < imin) imin = mt9v03x_image[row][j-k];
					if(mt9v03x_image[row][j-k] > imax) imax = mt9v03x_image[row][j-k];
				}
				imax = imax<<1, imin = imin << 1;
				if(imax*imax - imin*imin > imgthrsod) return j-10;
			}
			break;
	}
}
/*------------------------------*/
/*		摄像头边线识别模块		*/
/*==============================*/
void cam_ident(void){
//	变量定义
	register unsigned char j1, j2, k;
	unsigned char i;
	unsigned int imax, imin;
	short lefslope = 20, rigslope = -20;
	int sqrs, sqmax = 0;
//	标志位
	unsigned char foflag1 = 1, foflag2 = 1;
//	数值初始化
	lefp = 0, rigp = 0;
	j1 = foundation(1);
	j2 = foundation(2);
	if(abs(j1-j2)<20){
		if(j1<80 || j2<80)
			j1 = j2, j2 = 157;
		if(j1>80||j2>80)
			j2 = j1, j1 = 2;
	}
//	边线识别
	for(i = EFF_ROW; i > 0; i--){
		if(foflag1 == 2)
			if(foflag2 == 2) break;
		/*------------------------------*/
		/*			左边线识别			*/
		/*==============================*/
		foflag1 = 0;
		for(;j1 > 1; j1--){
			if(foflag1 == 2) break;
		//	寻找跳变点
			imax = 0, imin = 255;
			for(k = 0; k < 3; k++){
				if(mt9v03x_image[i][j1-k] < imin) imin = mt9v03x_image[i][j1-k];
				if(mt9v03x_image[i][j1-k] > imax) imax = mt9v03x_image[i][j1-k];
			}
			imax = imax<<1, imin = imin << 1;
			sqrs = imax*imax - imin*imin;
			if(sqrs > sqmax) sqmax = sqrs;
			if(sqrs > imgthrsod){
				lefbor[i] = j1, lefp++;
				if(lefp > 1){
					lefslope = lefbor[i] - lefbor[i+1] + 10;
					if(abs(lefbor[i] - lefbor[i+1]) > 60){
						foflag1 = 0, j1 = 0, lefp--;
						break;
					}
				}
				j1+=lefslope, foflag1 = 1;
				break;
			}
		}
	//	没有找到边界，停止检测
		if(j1 < 2 || j1 > 160){
			if(!foflag1){
				if(i > 45) foflag1 = 1, j1=10, lefbor[i] = 0, lefp++;//继续寻找边线
				else foflag1 = 2;
			}
		}
		/*------------------------------*/
		/*			右边线识别			*/
		/*==============================*/
		foflag2 = 0;
		for(;j2 < 158; j2++){
			if(foflag2 == 2) break;
		//	寻找跳变点
			imax = 0, imin = 255;
			for(k = 0; k < 3; k++){
				if(mt9v03x_image[i][j2+k] < imin) imin = mt9v03x_image[i][j2+k];
				if(mt9v03x_image[i][j2+k] > imax) imax = mt9v03x_image[i][j2+k];
			}
			imax = imax<<1, imin = imin << 1;
			sqrs = imax*imax - imin*imin;
			if(sqrs > sqmax) sqmax = sqrs;
			if(sqrs > imgthrsod){
				rigbor[i] = j2, rigp++;
				if(rigp > 1){
					rigslope = rigbor[i] - rigbor[i+1] - 10;
					if(abs(rigbor[i] - rigbor[i+1]) > 60){
						foflag2 = 0, j2 = 159, rigp--;
						break;
					}
				}
				j2+=rigslope, foflag2 = 1;
				break;
			}
		}
	//	没有找到边界，停止检测
		if(j2 < 158){
			if(!foflag2){
				if(i > 45) foflag2 = 1, j2=150, rigbor[i] = 159, rigp++;//继续寻找边线
				else foflag2 = 2;
			}
		}
	}
//	后续处理
	mid_fit();
	cal_slope();
	element_jug();
//	ips200_showint32(160, 0, sqmax, 6);
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
	register unsigned char i, j;
//	边线显示
	ips200_drawpoint(lefbor[EFF_ROW - lefp], EFF_ROW - lefp, 0xfd78);
	ips200_drawpoint(lefbor[EFF_ROW - rigp], EFF_ROW - rigp, 0xfd78);
	for(i = EFF_ROW-1; lefp > 0; i--, lefp--){
		ips200_drawpoint(lefbor[i], i, 0xa75c);
	}
	for(i = EFF_ROW-1; rigp > 0; i--, rigp--){
		ips200_drawpoint(rigbor[i], i, 0xfd10);
	}
	for(i = EFF_ROW-1; midp > 0; i--, midp--){
		ips200_drawpoint(mid_point[i], i, 0xbea8);
	}
//	状态显示
	switch(cjug_sta){
		case 1:ips200_showstr(160, 0,   "direct    ");break;
		case 21:ips200_showstr(160, 0,  "Left      ");break;
		case 29:ips200_showstr(160, 0,  "Right     ");break;
		case 22:ips200_showstr(160, 0,  "turn left ");break;
		case 28:ips200_showstr(160, 0,  "turn right");break;
		case 200:ips200_showstr(160, 0, "error:200 ");break;
		case 201:ips200_showstr(160, 0, "error:201 ");break;
		case 202:ips200_showstr(160, 0, "error:202 ");break;
	}
	ips200_showstr(160, 1, "slope:");
	ips200_showfloat(160, 2, lefslope, 2, 1);
	ips200_showfloat(160, 3, rigslope, 2, 1);
	ips200_showfloat(160, 4, midslope, 2, 1);
}
