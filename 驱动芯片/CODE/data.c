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
/*	    ����CCDģ��		*/
/*======================*/
unsigned cjug_sta;
/*----------------------*/
/*	 	 MOTORģ��		*/
/*======================*/
//	������
short lcod = 0,rcod = 0;
short spd = 0;
short rad = 0;
short lef_pwm, rig_pwm;
//	PID
struct pidpara speed;
struct pidpara lefdif;
struct pidpara rigdif;
struct pidpara steer;
struct pidpara angle;
struct pidpara acw;
/*----------------------*/
/*	   �Ƕȿ���ģ��		*/
/*======================*/
short blcp = 330;
short pita, yawa, yawa_temp;
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
/*----------------------*/
/*	 	 ͨ��ģ��		*/
/*======================*/
unsigned char buff_get6, buff_get7;
unsigned char dst_flag = 0, final_flag = 0;
unsigned char launch_command[3] = {0xA7, 0xB9, 0x12};
int distance = 0;
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*----------------------*/
/*	 	������ʼ��		*/
/*======================*/
//	PID
void Init_para(void){
//	�ٶ�
	speed.alpha = 0.1;
	speed.Kp = 1.1;//��Ӧ���� | ����
	speed.Ki = 0.01;//��Ӧ����
	speed.Kd = 0.0;
	speed.I = 0;
	speed.e1 = 0, speed.e2 = 0, speed.e3 = 0;
	speed.rs = 0;
	
//	���ֲ���
	lefdif.alpha = 0.3;
	lefdif.Kp = 30;//��Ӧ���� | ����
	lefdif.Ki = 0.75;//��Ӧ����
	lefdif.Kd = 0;
	lefdif.I = 0;
	lefdif.e1 = 0, lefdif.e2 = 0, lefdif.e3 = 0;
	lefdif.rs = 0;

//	���ֲ���
	rigdif.alpha = 0.3;
	rigdif.Kp = 30;//��Ӧ���� | ����
	rigdif.Ki = 0.75;//��Ӧ����
	rigdif.Kd = 0;
	rigdif.I = 0;
	rigdif.e1 = 0, rigdif.e2 = 0, rigdif.e3 = 0;
	rigdif.rs = 0;
	
//	ת��
	steer.alpha = 0.3;
	steer.Kp = 1.8;//��Ӧ���� | ����
	steer.Ki = 0;//��Ӧ����
	steer.Kd = 0.6;
	steer.I = 0;
	steer.e1 = 0, steer.e2 = 0, steer.e3 = 0;
	steer.rs = 0;	
	
////	ת��
//	steer.alpha = 0.3;
//	steer.Kp = 167;//��Ӧ���� | ����
//	steer.Ki = 0;//��Ӧ����
//	steer.Kd = 1.5;
//	steer.I = 0;
//	steer.e1 = 0, steer.e2 = 0, steer.e3 = 0;
//	steer.rs = 0;
	
//	�Ƕ�
	angle.Kp = 2.6;//����
	angle.Ki = 0;
	angle.Kd = 0.15;//����
	angle.e1 = 0, angle.e2 = 0, angle.e3 = 0; 
	angle.rs = 0;

//	���ٶ�
	acw.alpha = 0.05;
	acw.Kp = 37;//��Ӧ���� | ����
	acw.Ki = 0.29;//��Ӧ����
	acw.Kd = 0.0;
	acw.I = 0;
	acw.e1 = 0, acw.e2 = 0, acw.e3 = 0;
	acw.rs = 0;
}
