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
#define menu_limit1 1
#define menu_limit2 0
#define menu_limit3 1
/*------------------------------------------------------*/
/* 					  �ⲿ�������� 						*/
/*======================================================*/
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
