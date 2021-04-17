/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "CAM.h"
#include "data.h"
#include "SEEKFREE_MT9V03X.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*------------------------------*/
/*		����ͷ����ʶ��ģ��		*/
/*==============================*/
void camindet(void){
//	��������
	register unsigned char i, j, k;//ͼ���С���
	unsigned int imax, imin;
	unsigned char uplim;
//	��ֵ��ʼ��
	uplim = 63+ident_bias;
//	����ʶ��
	for(j = 0; j < MT9V03X_W; j++){
		for(i = ident_bias; i < uplim; i+=3){
		//	����
			imax = 0, imin = 255;
			for(k = 0; k < 3; k++){
				if(mt9v03x_image[i+k][j] < imin) imin = mt9v03x_image[i+k][j];
				if(mt9v03x_image[i+k][j] > imax) imax = mt9v03x_image[i+k][j];
			}
			imax = imax<<1, imin = imin << 1;
			if(imax*imax - imin*imin > 28000) border[j] = i;
		}
	}
//	ͼ����ʾ
	if(csimenu_flag[0]){
		ips200_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
		for(j = 0; j < 160; j++)
			ips200_drawpoint(j, border[j], 0xa75c);
	}
}
/*------------------------------*/
/*		����ͷ������ʾģ��		*/
/*==============================*/
void cam_draw(void){
//	��������
	register unsigned char j;	
}
