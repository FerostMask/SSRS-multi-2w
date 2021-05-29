/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "ctrl.h"
#include "data.h"
#include "pid.h"
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
unsigned char bend_bias[] = {16, 20, 14, 12, 10, 10, 8, 6};
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
	register unsigned char i;
	unsigned char point_temp;
	short bias_temp;
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
			folc_flag = 0;
		//	��Ȩ�㷨
//			for(i = 0; i < 8; i++)
//				bias_temp += (lefbor[55+(i<<2)+i]+rigbor[55+(i<<2)+i] - 160)*bend_bias[i];
//			p_target[1] = (bias_temp>>7)+80;
//			folc_flag = 0;
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
			if(rvet_trafcount)
				{p_target[1] = (lefbor[rvet_trafpoint_row[0]]+rigbor[rvet_trafpoint_row[0]])>>1, folc_flag = 0; return;}
			p_target[1] = (lefbor[90]+rigbor[90])>>1;
			p_target[1] = (p_target[1]+80)>>1;
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
	unsigned char point_temp;
	short bias_temp;
////	��Ȩ�㷨
//	for(i = 0; i < 8; i++)
//		bias_temp += (lefbor[55+(i<<2)+i]+rigbor[55+(i<<2)+i] - 160)*bend_bias[i];
//	p_target[1] = (bias_temp>>7)+80;
//	folc_flag = 0;
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
	register unsigned char i;
	unsigned char point_temp;
	short bias_temp, cal_temp;
	short neg_add = 0, pos_add = 0;

////	��Ȩ�㷨
//	for(i = 0; i < 8; i++){
//		cal_temp = (lefbor[55+(i<<2)+i]+rigbor[55+(i<<2)+i] - 160);
//		bias_temp += cal_temp*bend_bias[i];
//	//	������ƫ�û���
//		if(cal_temp < 0) neg_add += cal_temp;
//		else pos_add += cal_temp;
//	}
//	p_target[1] = (bias_temp>>7)+80;
//	if(abs(pos_add + neg_add) < 20) p_target[1] = (p_target[1]+80)>>1;
//	folc_flag = 0;

	p_target[1] = ((lefbor[45]+rigbor[45]))+((lefbor[63]+rigbor[63]))>>2;
	folc_flag = 0;
//	�������
	if(lvet_trafcount)
		p_target[1] = (lefbor[lvet_trafpoint_row[0]]+rigbor[lvet_trafpoint_row[0]])>>1;
	if(rvet_trafcount)
		p_target[1] = (lefbor[rvet_trafpoint_row[0]]+rigbor[rvet_trafpoint_row[0]])>>1;
//	��������
	if(ring_out_flag == 1){
		if(found_point[0] < 60)
			p_target[1] = (lefbor[found_point[0]-10]+rigbor[found_point[0]-10])>>1;
		spd = 30;
	}
//	�յ�
	if(count_fork > 7)
		p_target[1] = 80;
}
