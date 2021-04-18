#ifndef _DATA_H
#define _DATA_H
#include "menu.h"
#include "menu_2.h"
/*--------------------------------------------------------------*/
/*							  �궨��							*/
/*==============================================================*/
//	������־λ
#define CSIMENU_FLAG 2
#define WIRELESS_FLAG 2
//	һ���˵�
#define ROWS 4
#define menu_limit0 0
#define menu_limit1 2
#define menu_limit2 0
#define menu_limit3 1
//	����ͷ
#define EFF_ROW 54
/*------------------------------------------------------*/
/* 					  �ⲿ�������� 						*/
/*======================================================*/
/*----------------------*/
/*	 	����ͷģ��		*/
/*======================*/
extern unsigned char border[160], borderid[160];
extern unsigned char lbomp, rbomp;
extern unsigned char ltra[80], rtra[80];
extern unsigned char efflp, effrp;
extern unsigned char ident_bias;
extern unsigned char cjug_sta;
//	ͼ��ver2
extern unsigned char lefbor[EFF_ROW+1], rigbor[EFF_ROW+1];
extern unsigned char lefp, rigp;
/*----------------------*/
/*	 	 ���ģ��		*/
/*======================*/
//	�ṹ������
typedef struct adcpara{//��Ż�������
	unsigned short value;
	unsigned short max;
	unsigned short min;
	unsigned short pin;
}adcpara;
typedef struct adcerrpa{//��ȺͲ����
	float alpha, beta, omega;
	float P;
	short rs;
}adcerrpa;
//	ȫ�ֽṹ������
extern struct adcpara adc0;
extern struct adcpara adc1;
extern struct adcpara adc2;
extern struct adcpara adc3;
extern struct adcpara adc4;
extern struct adcerrpa adc_err;
//	״̬��־λ
extern unsigned char ajug_sta;
/*----------------------*/
/*	 	 MOTORģ��		*/
/*======================*/
//	���
extern short spd;
extern short rad;
/*----------------------*/
/*	 	  PIDģ��		*/
/*======================*/
//	�ṹ������
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
extern struct pidpara adc_steering;
/*----------------------*/
/*	 	 ������ȥ		*/
/*======================*/
extern unsigned char subuff_num;
extern unsigned char subuff_arr[3];
extern unsigned short subuff_ranging;
/*----------------------*/
/*	 	 �˵�ģ��		*/
/*======================*/
//	һ���˵�
extern unsigned char menu_index;
extern unsigned char menu[ROWS];
extern unsigned char nom[128];
//	��־λ
extern unsigned char fixedflag;
extern unsigned char monitorflag;
extern unsigned char csimenu_flag[CSIMENU_FLAG];
extern unsigned char wireless_flag[WIRELESS_FLAG];
extern unsigned char excollflag;
extern unsigned char menu_level;
//	�����˵�
extern unsigned char menu2_index;
extern unsigned char menu2_level;
//	����ָ��
extern void(*menu_pfc[])(unsigned char);
/*------------------------------------------------------*/ 
/* 						�������� 						*/
/*======================================================*/
void Init_para(void);

#endif
