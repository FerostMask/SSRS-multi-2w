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
/*	 	 MOTORģ��		*/
/*======================*/
//	������
short lcod = 0,rcod = 0;
short spd = 100;
short rad = 0;
//	PID
struct pidpara speed;
struct pidpara steer;
struct pidpara angle;
struct pidpara acw;

/*----------------------*/
/*	   �Ƕȿ���ģ��		*/
/*======================*/
short blcp = 330;
short pita;
short gy, gz;
short yfilt[4] = {0, 0, 0, 0};
short pflit[4] = {0, 0, 0, 0};

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
void(*menu_pfc[])(unsigned char) = {menu_select, menu2_select};

/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*----------------------*/
/*	 	������ʼ��		*/
/*======================*/
//	PID
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
	steer.Kp = 5;//��Ӧ���� | ����
	steer.Ki = 0;//��Ӧ����
	steer.Kd = 10;
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
