#ifndef _DATA_H
#define _DATA_H
/*--------------------------------------------------------------*/
/*							  �궨��							*/
/*==============================================================*/
#define CSIMENU_FLAG 2
#define WIRELESS_FLAG 2
/*------------------------------------------------------*/
/* 					  �ⲿ�������� 						*/
/*======================================================*/
/*----------------------*/
/*	 	 MOTORģ��		*/
/*======================*/
//	������
extern short lcod, rcod;			//����������
extern short ltcod, rtcod;          //������Ŀ��ֵ
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

//	���
extern struct pidpara speed;
extern struct pidpara steer;
//	�Ƕȵ�������
extern struct pidpara angle;
//	���ٶ�
extern struct pidpara acw;

/*----------------------*/
/*	   �Ƕȿ���ģ��		*/
/*======================*/
extern short pita;
extern short yawa[2];
extern short yfilt[4];
extern short gy;
extern short pflit[4];
extern short blcp;

/*----------------------*/
/*	 	 �˵�ģ��		*/
/*======================*/
//	һ���˵���
extern unsigned char first_nom[128];
extern unsigned char fixedflag;
extern unsigned char monitorflag;
extern unsigned char csimenu_flag[CSIMENU_FLAG];
extern unsigned char wireless_flag[WIRELESS_FLAG];

/*------------------------------------------------------*/ 
/* 						�������� 						*/
/*======================================================*/
void Init_para(void);

#endif
