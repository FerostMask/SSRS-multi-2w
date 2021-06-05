/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "ctrl_alter1.h"
#include "data.h"
#include "pid.h"
#include "zf_flash.h"
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*------------------------------*/
/*		   �յ����ģ�� 		*/
/*==============================*/
void cam_ctrl_final_alter1(void){
//  ����
    folc_flag = 0;
//    if(cut_fork_bottom > 92) cnt_start++;
        switch(state){
            case 56://�����

            break;
            case 55://�ҳ���
                p_target[1] = ((80+rigbottom_cut)>>1);

            break;
            case 51://�����
                p_target[1] = ((rigtop_cut+rigbottom_cut)>>1);
                p_target[1] = ((p_target[1]+125)>>1);
                if(p_target[1] < 95) p_target[1] = 95;
    //            else{
//                p_target[0]=cut_fork_bottom;
//                p_target[1]=MT9V03X_W-20; 
    //            }
            break;
//            case 50:
//                p_target[0]=cut_fork_bottom;
//                p_target[1]=20; 
//            break;
        }
        
    if( yawa >= 78 ) spd = 0,  p_target[1] = 80;
}
/*------------------------------*/
/*		   �������ģ�� 		*/
/*==============================*/
void cam_ctrl_fork_alter1(void){
//	����
    p_target[0] = topbor[cut_fork_bottom_col];
    if(direction_fork){
        p_target[1] = (MT9V03X_W + cut_fork_bottom_col) >> 1;
    }else{
        p_target[1] = cut_fork_bottom_col >> 1;
    }
}
/*------------------------------*/
/*		   ʮ�ֿ���ģ�� 		*/
/*==============================*/
void cam_ctrl_cross_alter1(void){
//	����
	p_target[1] = ((lefbor[45]+rigbor[45]))+((lefbor[63]+rigbor[63]))>>2;
	folc_flag = 0;
}
/*------------------------------*/
/*		   ��������ģ�� 		*/
/*==============================*/
void cam_ctrl_ring_alter1(void){
//	��������
	register unsigned char i;
	unsigned char mp;
	short bias_temp = 0;
	unsigned char bend_bias[] = {22, 26, 16, 10, 6, 4, 2, 8};
//	����
	switch(act_flag){
		case 21://������
		//	�������
			if(lvet_trafcount)
				{p_target[1] = (lefbor[lvet_trafpoint_row[0]]+rigbor[lvet_trafpoint_row[0]])>>1, folc_flag = 0; return;}
			p_target[1] = (lefbor[90]+rigbor[90])>>1;
			p_target[1] = (p_target[1]+77)>>1;
			break;
		case 22://�뻷��
			p_target[1] = ((leftop_cut+lefbottom_cut)>>1);
			p_target[1] = ((p_target[1]+85)>>1);
			rad_min = 159, rad_max = 0;
			break;
		case 23://����
		//	��Ȩ�㷨
			for(i = 0; i < 8; i++)
				bias_temp += (lefbor[30+(i<<2)]+rigbor[30+(i<<2)] - 160)*bend_bias[i];
			p_target[1] = (bias_temp>>7)+80;
			if(p_target[1] < rad_min) rad_min = p_target[1];
			if(p_target[1] > rad_max && p_target[1] < 80) rad_max = p_target[1];
			break;
		case 24://����
			p_target[1] = (rad_min+rad_max)>>1;
			p_target[1] = ((p_target[1]+55)>>1);
			break;
	//	�һ�
		case 26://������
//			if(rvet_trafcount)
//				{p_target[1] = (lefbor[rvet_trafpoint_row[0]]+rigbor[rvet_trafpoint_row[0]])>>1, folc_flag = 0; return;}
			p_target[1] = (lefbor[90]+rigbor[90])>>1;
			p_target[1] = (p_target[1]+80)>>1;
			break;
		case 27://�뻷��
			if(exti_rigcount){
				p_target[1] = ((rigtop_cut+rigbottom_cut)>>1);
				p_target[1] = ((p_target[1]+70)>>1)+1;
			}
			rad_min = 159, rad_max = 0;
			break;
		case 28://����
		//	��Ȩ�㷨
			for(i = 0; i < 8; i++)
				bias_temp += (lefbor[30+(i<<2)]+rigbor[30+(i<<2)] - 160)*bend_bias[i];
			p_target[1] = (bias_temp>>7)+80;
			folc_flag = 0;
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
void cam_ctrl_bend_alter1(void){
//	��������
	register unsigned char i;
	short bias_temp = 0;
	unsigned char bend_bias[] = {22, 26, 16, 10, 6, 4, 2, 8};
//	��Ȩ�㷨
	for(i = 0; i < 8; i++)
		bias_temp += (lefbor[30+(i<<2)]+rigbor[30+(i<<2)] - 160)*bend_bias[i];
	p_target[1] = (bias_temp>>7)+80;
//	����
	switch(act_flag){
		case 11://��ת����
			folrow_f = 43;
			break;
		case 12://��ת����
			folrow_f = 43;
			break;
		case 13://����
			folrow_f = 43;
			break;
		case 14://����
			folrow_f = 43;
			break;
	}
}
/*------------------------------*/
/*		   ֱ������ģ�� 		*/
/*==============================*/
void cam_ctrl_direct_alter1(void){
//	��������
	register unsigned char i;
	unsigned char point_temp;
	short bias_temp;
	unsigned char bend_bias[] = {22, 26, 16, 10, 6, 4, 2, 8};
//	����
	if(exti_lefcount > 0)
		if(!exti_rigcount)
			spd = 40;
	if(exti_rigcount > 0)
		if(!exti_lefcount)
			spd = 40;
//	��Ȩ�㷨
	for(i = 0; i < 8; i++)
		bias_temp += (lefbor[30+(i<<2)]+rigbor[30+(i<<2)] - 160)*bend_bias[i];
	p_target[1] = (bias_temp>>7)+80;
	folc_flag = 0;
//	�������
	if(lvet_trafcount)
		p_target[1] = (lefbor[lvet_trafpoint_row[0]]+rigbor[lvet_trafpoint_row[0]])>>1;
//	��������
	if(ring_out_flag == 1){
		if(found_point[0] < 60)
			p_target[1] = (lefbor[found_point[0]-10]+rigbor[found_point[0]-10])>>1;
		spd = 30;
	}
}
/*----------------------*/
/*	 flash������ʼ��	*/
/*======================*/
char flash_init_alter1(void){
//	ȷ���Ƿ�����ǰ����Ĳ���
	if(!(flash_check(FLASH_MEMORY_SLECTION, FLASH_PAGE_1))) return 1;
//	��ȡ�����ò���
	flash_page_read(FLASH_MEMORY_SLECTION, FLASH_PAGE_1, flash_memory, FLASH_NUM);
//	CAMת��
	cam_steering.Kp = (float)flash_memory[0]/1000;
	cam_steering.Kd = (float)flash_memory[1]/1000;
//	�ٶȿ���
	spd_set = (float)flash_memory[2]/1000;
	return 0;
}
/*----------------------*/
/*	  ���β�����ʼ��	*/
/*======================*/
void first_flash_init_alter1(void){
//	CAMת��
	flash_memory[0] = cam_steering.Kp*1000;
	flash_memory[1] = cam_steering.Kd*1000;
//	�ٶȿ���
	flash_memory[2] = spd_set*1000;
//	������д��
	flash_erase_page(FLASH_MEMORY_SLECTION, FLASH_PAGE_1);
	flash_page_program(FLASH_MEMORY_SLECTION, FLASH_PAGE_1, flash_memory, FLASH_NUM);
}
/*----------------------*/
/*	  flash����д�� 	*/
/*======================*/
void flash_memory_write_alter1(unsigned char row, unsigned char col){
//	��ѡ��
	switch(row){
	//	��ѡ��
		case PARASET_PID:
			switch(col){
				case 0:
					flash_memory[0] = cam_steering.Kp*1000;
					flash_memory[1] = cam_steering.Kd*1000;	
					break;
			}
			break;
		case PARASET_OPER:
			switch(col){
				case 1:
					flash_memory[2] = spd_set*1000;
					break;
			}
			break;
	}
//	������д��
	flash_erase_page(FLASH_MEMORY_SLECTION, FLASH_PAGE_1);
	flash_page_program(FLASH_MEMORY_SLECTION, FLASH_PAGE_1, flash_memory, FLASH_NUM);
}
