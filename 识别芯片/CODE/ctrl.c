/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "ctrl.h"
#include "data.h"
#include "pid.h"
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*------------------------------*/
/*		   �������ģ�� 		*/
/*==============================*/
void cam_ctrl_fork(void){
//	����
    p_target[0] = topbor[cut_fork_bottom];
    if(direction_fork){
        p_target[1] = ((MT9V03X_W + cut_fork_bottom) >> 1)+7;
    }else{
        p_target[1] = (cut_fork_bottom >> 1)-7;
    }
//	if(direction_fork)
//		p_target[1] = 90;
//	else
//		p_target[0] = 70;
	folc_flag = 0;
}
/*------------------------------*/
/*		   ʮ�ֿ���ģ�� 		*/
/*==============================*/
void cam_ctrl_cross(void){
//	����
	p_target[1] = ((lefbor[45]+rigbor[45]))+((lefbor[63]+rigbor[63]))>>2;
	folc_flag = 0;
}
/*------------------------------*/
/*		   ��������ģ�� 		*/
/*==============================*/
void cam_ctrl_ring(void){
//	��������
	unsigned char mp;
	float slope_temp;
//	����
	switch(act_flag){
	//	��
		case 21://������
		//	�������
			if(lvet_trafcount)
				{p_target[1] = (lefbor[lvet_trafpoint_row[0]]+rigbor[lvet_trafpoint_row[0]])>>1, folc_flag = 0; return;}
			p_target[1] = (lefbor[90]+rigbor[90])>>1;
			p_target[1] = (p_target[1]+80)>>1;
			folc_flag = 0;
			break;
		case 22://�뻷��
			p_target[1] = ((leftop_cut+lefbottom_cut)>>1);
			p_target[1] = ((p_target[1]+95)>>1);
			rad_min = 159, rad_max = 0;
			spd = speed.ring[1];
			folc_flag = 0;
			break;
		case 23://����
			p_target[1] = ((lefbor[56]+rigbor[56]))+((lefbor[63]+rigbor[63]))>>2;
			rad_temp = p_target[1];
			if(p_target[1] < rad_min) rad_min = p_target[1];
			if(p_target[1] > rad_max) rad_max = p_target[1];
			folc_flag = 0;
			break;
		case 24://����
			p_target[1] = (rad_min+rad_max)>>1;
			p_target[1] = ((p_target[1]+55)>>1);
			spd = speed.ring[3];
			folc_flag = 0;
			break;
	//	�һ�
		case 26://������
			p_target[1] = (lefbor[90]+rigbor[90])>>1;
			p_target[1] = (p_target[1]+81)>>1;
			if(p_target[1] < 80) p_target[1] = 80;
			spd = speed.ring[0];
			folc_flag = 0;
			break;
		case 27://�뻷��
			if(exti_rigcount){
				p_target[1] = ((rigtop_cut+rigbottom_cut)>>1);
				p_target[1] = ((p_target[1]+70)>>1)+1;
				folc_flag = 0;
			}
			rad_min = 159, rad_max = 0;
			break;
		case 28://����
			folrow_f = 63;
			if(p_target[1] < rad_min && p_target[1] > 80) rad_min = p_target[1];
			if(p_target[1] > rad_max) rad_max = p_target[1];
			break;
		case 29://����
			p_target[1] = (rad_min+rad_max)>>1;
			p_target[1] = ((p_target[1]+90)>>1);
			folc_flag = 0;
			break;
	}
}
/*------------------------------*/
/*		   �������ģ�� 		*/
/*==============================*/
void cam_ctrl_bend(void){
//	��������
	register unsigned char i;
	unsigned char mp;
	unsigned char fp[4];
	unsigned char fop;
	float slope_temp;
//	����
	switch(act_flag){
		case 11://��ת����
			folrow_f = 45;
			break;
		case 12://��ת����
			folrow_f = 45;
			break;
		case 13://����
			p_target[1] = ((lefbor[56]+rigbor[56]))+((lefbor[63]+rigbor[63]))>>2;
			folc_flag = 0;
			break;
		case 14://����
			p_target[1] = ((lefbor[56]+rigbor[56]))+((lefbor[63]+rigbor[63]))>>2;
			folc_flag = 0;
			break;
	}
}
/*------------------------------*/
/*		   ֱ������ģ�� 		*/
/*==============================*/
void cam_ctrl_direct(void){
//	��������
	unsigned char point_temp;
//	����
	p_target[1] = ((lefbor[45]+rigbor[45]))+((lefbor[63]+rigbor[63]))>>2;
	folc_flag = 0;
//	�������
	if(lvet_trafcount)
		p_target[1] = (lefbor[lvet_trafpoint_row[0]]+rigbor[lvet_trafpoint_row[0]])>>1;
}
