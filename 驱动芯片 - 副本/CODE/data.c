/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "data.h"
#include "menu.h"
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*----------------------*/
/*	 	 ����ģ��		*/
/*======================*/
//	������
short spd = 0;
short rad = 0;
short lcod, rcod;
/*----------------------*/
/*	 	 ƽ��ģ��		*/
/*======================*/
short blcp = 245;
short pita;
short gy, gz;
short yfilt[4] = {0, 0, 0, 0};
short pflit[4] = {0, 0, 0, 0};
/*----------------------*/
/*	 	  PIDģ��		*/
/*======================*/
//	�ٶȡ�ת�򡢽Ƕȡ����ٶ�
struct pidpara speed;
struct pidpara steer;
struct pidpara angle;
struct pidpara acw;
/*----------------------*/
/*	 	 �˵�ģ��		*/
/*======================*/
//	����ָ������ | �˵�ѡ��
void(*menu_pfc[2])(unsigned char) = {menu_select, menu2_select};
//	�˵���
unsigned char nom[128];
//	һ���˵�
char menu[ROWS];
unsigned char menu_level = 0;//����
unsigned char menu_index = 0;//������
//	��ť
unsigned char csimenu_flag[CSIMENU_FLAG] = {0, 0};//����ͷ
unsigned char wireless_flag[WIRELESS_FLAG] = {0, 0};//��������

/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*----------------------*/
/*	 	������ʼ��		*/
/*======================*/
void Init_para(void){
//	�ٶ�
	speed.alpha = 0.3;
	speed.Kp = 0.1;//��Ӧ���� | ����
	speed.Ki = 0.05;//��Ӧ����
	speed.Kd = 0;
	speed.I = 0;
	speed.e1 = 0, speed.e2 = 0, speed.e3 = 0;
	speed.rs = 0;
	
//	ת��
	steer.alpha = 0.3;
	steer.Kp = 10;//��Ӧ���� | ����
	steer.Ki = 1;//��Ӧ����
	steer.Kd = 1;
	steer.I = 0;
	steer.e1 = 0, steer.e2 = 0, steer.e3 = 0;
	steer.rs = 0;
	
//	�Ƕ�
	angle.Kp = 1.2;//����
	angle.Ki = 0;
	angle.Kd = 2;//����
	angle.e1 = 0, angle.e2 = 0, angle.e3 = 0; 
	angle.rs = 0;

//	���ٶ�
	acw.alpha = 0.3;
	acw.Kp = 30;//��Ӧ���� | ����
	acw.Ki = 1.7;//��Ӧ����
	acw.Kd = 2.4;
	acw.I = 0;
	acw.e1 = 0, acw.e2 = 0, acw.e3 = 0;
	acw.rs = 0;
}
