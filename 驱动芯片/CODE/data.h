#ifndef _DATA_H
#define _DATA_H
#include "menu.h"
#include "menu_2.h"
/*--------------------------------------------------------------*/
/*							  �궨��							*/
/*==============================================================*/
//	������־λ
#define CSIMENU_FLAG 2
#define STATE_FLAG 3
//	һ���˵�
#define ROWS 5
#define menu_limit0 1
#define menu_limit1 2
#define menu_limit2 2
#define menu_limit3 0
#define menu_limit4 0
//	�˵����Ա��
#define MENU_SWITCH 0
#define PARASET_PID1 1
#define PARASET_PID2 2
#define PARASET_OPER 3
#define MONITOR_MENU 4
//	flash�����洢
#define FLASH_NUM 19
#define FLASH_MEMORY_SLECTION FLASH_SECTION_112
/*------------------------------------------------------*/
/* 					  �ⲿ�������� 						*/
/*======================================================*/
/*----------------------*/
/*	    ����CCDģ��		*/
/*======================*/
extern unsigned cjug_sta;
/*----------------------*/
/*	 	 MOTORģ��		*/
/*======================*/
//	������
extern short lcod, rcod;			//����������
extern short ltcod, rtcod;          //������Ŀ��ֵ
extern short lef_pwm, rig_pwm;
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
extern struct pidpara lefdif;
extern struct pidpara rigdif;
extern struct pidpara steer;
//	�Ƕȵ�������
extern struct pidpara angle;
//	���ٶ�
extern struct pidpara acw;

/*----------------------*/
/*	   �Ƕȿ���ģ��		*/
/*======================*/
extern int gy, gz;
extern short blcp;
extern short pita, yawa, yawa_temp;
extern short yfilt[4];
extern short pflit[4];

/*----------------------*/
/*	 	 �˵�ģ��		*/
/*======================*/
//	һ���˵�
extern unsigned char menu_index;
extern unsigned char menu[ROWS];
extern unsigned char nom[128];
extern unsigned char fixedflag;
extern unsigned char monitorflag;
extern unsigned char csimenu_flag[CSIMENU_FLAG];
extern unsigned char state_flag[STATE_FLAG];
extern unsigned char menu_level;
//	�����˵�
extern unsigned char menu2_index;
extern unsigned char menu2_level;
//	����ָ��
extern void(*menu_pfc[])(unsigned char);
/*----------------------*/
/*	 	 ͨ��ģ��		*/
/*======================*/
extern unsigned char buff_get6, buff_get7;
extern unsigned char dst_flag, final_flag;
extern unsigned char launch_command[3];
extern int distance;
/*------------------------------------------------------*/ 
/* 						�������� 						*/
/*======================================================*/
void Init_para(void);
char flash_init(void);
void first_flash_init(void);
void flash_memory_write(row, col);
#endif
