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
unsigned char mid_point;
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*------------------------------*/
/*		  ��������ʶ��ģ��		*/
/*==============================*/
void rise_ident(void){
//	��������
	register unsigned char j;
	
} 
/*------------------------------*/   /*-----------------*/
/*		  ���ֵ�Ѱ��ģ��		*/  /*     �����㷨	   */
/*==============================*/ /*=================*/
static void cam_sow(void){
//	�������塢��ʼ��
	register unsigned char j;
	unsigned char bomrow = 0;//�����
	efflp = 0, effrp = 0, cjug_sta = 0;
//	������͵�
	for(j = 0; j < 80; j++){
		if(border[j] == 0) continue;
	//	���ºۼ�
		ltra[efflp] = j, efflp++;
		if(bomrow < border[j]) bomrow = border[j], lbomp = j;
	}
//	���ú�Ѱ������͵�
	bomrow = 0;
	for(j = 80; j < 160; j++){
		if(border[j] == 0) continue;
		rtra[effrp] = j, effrp++;
		if(bomrow < border[j]) bomrow = border[j], rbomp = j;
	}
//	��¼��͵�
	for(j = 0; j < 160; j++) borderid[j] = 0;
	borderid[lbomp] = 1, borderid[rbomp] = 1;
//	�ж���������
	if(border[lbomp] < 42) cjug_sta = 1;//��ת
	if(border[rbomp] < 42) cjug_sta = 2;//��ת
	mid_point = (rbomp+lbomp)/2;
	if(cjug_sta == 0){
		if(mid_point > 85) cjug_sta =2;
		if(mid_point < 75) cjug_sta =1;		
	}
}
/*------------------------------*/
/*		����ͷ����ʶ��ģ��		*/
/*==============================*/
//void camident(void){
////	��������
//	register unsigned char i, j, k;//ͼ���С���
//	unsigned int imax, imin;
//	unsigned char uplim;
////	��־λ
//	unsigned char foflag;
////	��ֵ��ʼ��
//	uplim = 54+ident_bias;
////	����ʶ��
//	for(j = 0; j < MT9V03X_W; j++){
//	//	����
//		foflag = 0;
//		for(i = ident_bias; i < uplim; i+=3){
//		//	����
//			imax = 0, imin = 255;
//			for(k = 0; k < 3; k++){
//				if(mt9v03x_image[i+k][j] < imin) imin = mt9v03x_image[i+k][j];
//				if(mt9v03x_image[i+k][j] > imax) imax = mt9v03x_image[i+k][j];
//			}
//			imax = imax<<1, imin = imin << 1;
//			if(imax*imax - imin*imin > 28000) border[j] = i, foflag = 1;
//		}
//		if(!foflag) border[j] = 0; 
//	}
////	���������㷨
//	cam_sow();
////	ͼ����ʾ
//	if(csimenu_flag[0]){
//		ips200_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
//		cam_draw();
//	}
//}
/*------------------------------*/
/*		����ͷ����ʶ��ģ��		*/
/*==============================*/
void cam_ident(void){
//	��������
	register unsigned char j1 = 80, j2 = 80, k;
	unsigned char i;
	unsigned int imax, imin;
//	��־λ
	unsigned char foflag1 = 1, foflag2 = 1;
//	��ֵ��ʼ��
	lefp = 0, rigp = 0;
//	����ʶ��
	for(i = EFF_ROW; i > 0; i--){
		if(!(foflag1||foflag2)) break;
		foflag1 = 0;
	//	��߽��������Ѳ��
		for(;j1 > 1; j1--){
			if(foflag1 == 2) break;
		//	Ѱ�������
			imax = 0, imin = 255;
			for(k = 0; k < 3; k++){
				if(mt9v03x_image[i][j1-k] < imin) imin = mt9v03x_image[i][j1-k];
				if(mt9v03x_image[i][j1-k] > imax) imax = mt9v03x_image[i][j1-k];
			}
			imax = imax<<1, imin = imin << 1;
			if(imax*imax - imin*imin > 28000){
				lefbor[i] = j1, lefp++, j1+=15, foflag1 = 1;
				break;
			}
		}
	//	û���ҵ��߽磬ֹͣ���
		if(j1 == 2)
			if(!foflag1) 
				foflag1 = 2;
	}
	if(csimenu_flag[0]){
		ips200_displayimage032(mt9v03x_image[0], MT9V03X_W, MT9V03X_H);
		cam_draw();
	}
}
/*------------------------------*/
/*		����ͷ������ʾģ��		*/
/*==============================*/
void cam_draw(void){
//	��������
	register unsigned char i, j;
	for(i = 0; i <= EFF_ROW; i++){
		ips200_drawpoint(lefbor[i], i, 0xa75c);
	}
////	��������
//	register unsigned char j;
//	for(j = 0; j < 160; j++){
//		if(border[j] == 0) ips200_drawpoint(j, border[j], 0xfd78);//��Ч��
//		else{
//			switch(borderid[j]){
//				case 0:ips200_drawpoint(j, border[j], 0xa75c);break;//δʶ���
//				case 1:ips200_drawpoint(j, border[j], 0xfd10);break;//��͵�
//			}
//		}
//	}
//	ips200_drawpoint(j, border[mid_point], 0xfd10);
////	����������ʾ
//	switch(cjug_sta){
//		case 0:ips200_showstr(160, 0, "direct    ");break;
//		case 1:ips200_showstr(160, 0, "turn left ");break;
//		case 2:ips200_showstr(160, 0, "turn right");break;
//	}
//	ips200_showint16(160, 1, mid_point);
}
