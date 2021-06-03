#ifndef _DATA_H
#define _DATA_H
#include "menu.h"
#include "menu_2.h"
#include "SEEKFREE_MT9V03X.h"
/*--------------------------------------------------------------*/
/*							  �궨��							*/
/*==============================================================*/
//	������־λ
#define CSIMENU_FLAG 3
#define RUN_FLAG 4
//	һ���˵�
#define ROWS 4
#define menu_limit0 1
#define menu_limit1 0
#define menu_limit2 1
#define menu_limit3 1
//	����ͷ
#define EFF_ROW 54
//	�˵����Ա��
#define MENU_SWITCH 0
#define PARASET_PID 1
#define PARASET_OPER 2
#define MONITOR_MENU 3
/*------------------------------------------------------*/
/* 					  �ⲿ�������� 						*/
/*======================================================*/
/*----------------------*/
/*	 	����ͷģ��		*/
/*======================*/
//	��򷨶�ֵ��
extern float P[256], PK[256], MK[256];
extern unsigned char binary_img[MT9V03X_H][(MT9V03X_W-4)/8];
extern unsigned char img_thrsod;
//	��׼��Ѱ��
extern unsigned char found_point[4];
extern unsigned char fop_flag;
//	ˮƽ����Ѱ��
extern unsigned char lefbor[MT9V03X_H], rigbor[MT9V03X_H], mid_point[MT9V03X_H];
extern unsigned char ltraf_point_row[10], rtraf_point_row[10], ltraf_point_col[10], rtraf_point_col[10];
extern unsigned char ltraf_flag[10], rtraf_flag[10];
extern unsigned char lcut, rcut;
extern unsigned char ltraf_count, rtraf_count;
//	��ֱ����Ѱ��
extern unsigned char topbor[MT9V03X_W-4], bottombor[MT9V03X_W-4];//���±���
extern unsigned char lvet_trafpoint_row[5], rvet_trafpoint_row[5], lvet_trafpoint_col[5], rvet_trafpoint_col[5];
extern unsigned char lvet_trafcount, rvet_trafcount;
extern unsigned char leftop_cut, lefbottom_cut, rigtop_cut, rigbottom_cut;//��ֹ��
extern unsigned char exti_lefp[4], exti_rigp[4], exti_lefcount, exti_rigcount;
//	״̬��
extern unsigned char act_flag, act_flag_temp, fragile_flag;
extern unsigned short img_color;
extern unsigned char state, state_temp;
extern unsigned char state_flag;
extern void(*state_pfc[])(void);
//  ������
extern unsigned char direction_fork, border_top[MT9V03X_W-4]; //0 �� 1 ��
extern unsigned char cnt_left, cnt_right;//��������б
extern unsigned char total_count_fork;
extern unsigned short cut_fork_lef, cut_fork_rig, cut_fork_bottom;
extern unsigned char count_fork;
/*----------------------*/
/*	 	 ����ģ��		*/
/*======================*/
extern unsigned short cut_fork, cut_fork_bottom;
extern short p_target[2];
extern short spd_set;
extern short spd, rad;
extern short rad_temp, rad_min, rad_max;
extern unsigned char folrow_f;
extern unsigned char ctrl_bias[];
extern char folc_flag, cooling_flag, ring_out_flag;
extern unsigned char ctrl_pointer, dir_run_out;
extern void(*ctrl_pfc[])(void);
extern void(*ctrl_pfc_alter1[])(void);
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
extern struct pidpara cam_steering;
/*----------------------*/
/*	 	 ������ȥ		*/
/*======================*/
extern unsigned char subuff_num;
extern unsigned char subuff_arr[3];
extern unsigned short subuff_ranging;
/*----------------------*/
/*	 	 ����ͨ��		*/
/*======================*/
extern unsigned char yawa_flag, action_flag;
extern short yawa, pita;
extern char buff_get6, buff_get7;
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
extern unsigned char run_flag[RUN_FLAG];
extern unsigned char excollflag;
extern unsigned char menu_level;
//	�����˵�
extern unsigned char menu2_index;
extern unsigned char menu2_level;
//	����ָ��
extern void(*menu_pfc[])(unsigned char);
extern void(*ctrl_pfc_alter1[])(void);
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
//	ȫ�ֽṹ������
extern struct adcpara adc2;
/*------------------------------------------------------*/ 
/* 						�������� 						*/
/*======================================================*/
void Init_para(void);
void Init_para_alter1(void);
#endif
