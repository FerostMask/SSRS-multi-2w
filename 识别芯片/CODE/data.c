/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "data.h"
/*--------------------------------------------------------------*/
/*							  �궨��							*/
/*==============================================================*/
#define u8 unsigned char                                    //8λ����
#define u16 unsigned short                                  //16λ����
#define u32 unsigned int                                    //32λ����

/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*----------------------*/
/*	 	 ���ģ��		*/
/*======================*/
//	�ṹ�嶨��
struct adcpara adc0;
struct adcpara adc1;
struct adcpara adc2;
struct adcpara adc3;
struct adcpara adc4;
/*----------------------*/
/*	 	 MOTORģ��		*/
/*======================*/
//	PID

/*----------------------*/
/*	 	 �˵�ģ��		*/
/*======================*/
//	��������
unsigned char nom[128];
//	һ���˵�
unsigned char menu[ROWS];
unsigned char menu_level;
unsigned char menu_index = 0;
//	�����˵�
unsigned char menu2_index = 0;
unsigned char menu2_level = 0;
//	��־λ
unsigned char fixedflag = 0;//�̶���ʾ
unsigned char monitorflag = 0;//������
unsigned char csimenu_flag[CSIMENU_FLAG] = {0, 0};//����ͷ
unsigned char wireless_flag[WIRELESS_FLAG] = {0, 0};//��������
//	����ָ��
//void(*menu_pfc[])(unsigned char) = {menu_select, menu2_select};

/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*----------------------*/
/*	 	������ʼ��		*/
/*======================*/
void Init_para(void){
//	���ģ��
	adc0.max = 3801, adc0.min = 187;
	adc1.max = 4095, adc1.min = 0;
	adc2.max = 4095, adc2.min = 0;
	adc3.max = 4095, adc3.min = 0;
	adc4.max = 4095, adc4.min = 0;
	
////	�ٶ�
//	speed.alpha = 0.3;
//	speed.Kp = 0.1;//��Ӧ���� | ����
//	speed.Ki = 0.05;//��Ӧ����
//	speed.Kd = 0;
//	speed.I = 0;
//	speed.e1 = 0, speed.e2 = 0, speed.e3 = 0;
//	speed.rs = 0;
}
