/*------------------------------------------------------*/
/* 					   ͷ�ļ����� 						*/
/*======================================================*/
#ifndef _DATA_H
#define _DATA_H
/*------------------------------------------------------*/
/* 					  	 �궨�� 						*/
/*======================================================*/
#define CSIMENU_FLAG 2
#define WIRELESS_FLAG 2
//	һ���˵�
#define ROWS 4//	�˵�����
//	�˵�������
#define LIMIT0 1
#define LIMIT1 3
#define LIMIT2 0
#define LIMIT3 0
/*------------------------------------------------------*/
/* 					  �ⲿ�������� 						*/
/*======================================================*/
/*----------------------*/
/*	 	 ����ģ��		*/
/*======================*/
extern short spd;
extern short rad;
extern short lcod, rcod;
/*----------------------*/
/*	 	 ƽ��ģ��		*/
/*======================*/
extern short blcp;
extern short pita;
extern short gy, gz;
extern short yfilt[4];
extern short pflit[4];
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
//	���
extern struct pidpara speed;
extern struct pidpara steer;
//	�Ƕ�
extern struct pidpara angle;
//	���ٶ�
extern struct pidpara acw;
/*----------------------*/
/*	 	 �˵�ģ��		*/
/*======================*/
extern void(*menu_pfc[2])(unsigned char event);
extern unsigned char nom[128];
extern char menu[ROWS];
extern unsigned char menu_level;
extern unsigned char menu_index;
extern unsigned char csimenu_flag[CSIMENU_FLAG];
extern unsigned char wireless_flag[WIRELESS_FLAG];
/*------------------------------------------------------*/ 
/* 						�������� 						*/
/*======================================================*/
void Init_para(void);
#endif
