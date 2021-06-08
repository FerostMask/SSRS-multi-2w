/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "ctrl.h"
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
void cam_ctrl_final(void){
//  ����
    folc_flag = 0;
//    if(cut_fork_bottom > 92) cnt_start++;
        switch(act_flag){
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
void cam_ctrl_fork(void){
//	��������
	register unsigned char i;
	unsigned char i_limit, max_col = 159, min_col = 0;
//	����
	if(direction_fork){//��
		min_col = cut_fork_bottom_col - ((float)(border_top[cut_fork_rig] - bottom_point_row)/(float)(cut_fork_bottom_col - cut_fork_rig))*(point_folrow-bottom_point_row);//������߽�
		p_target[1] = (min_col+rigbor[point_folrow])>>1;
	}
	else{//��
		max_col = cut_fork_bottom_col + ((float)(border_top[cut_fork_lef] - bottom_point_row)/(float)(cut_fork_lef - cut_fork_bottom_col))*(point_folrow-bottom_point_row);//�����ұ߽�
		p_target[1] = (lefbor[point_folrow]+max_col)>>1;
	}
}
/*------------------------------*/
/*		   ʮ�ֿ���ģ�� 		*/
/*==============================*/
void cam_ctrl_cross(void){
	folc_flag = 1;
}
/*------------------------------*/
/*		   ��������ģ�� 		*/
/*==============================*/
void cam_ctrl_ring(void){
//	��������
	register unsigned char i;
	unsigned char i_limit, max_col = 159, min_col = 0;
	unsigned char ring_flag = 0;
//	����
	switch(act_flag){
	//	��
		case 21://������
			for(i = MT9V03X_H-1; i > 0; i--){
				if(lefbor[i] > 20) ring_flag = 1;
				if(ring_flag){
					if(lefbor[i] > min_col) min_col = lefbor[i], i_limit = i;
					if(lefbor[i]< 20) break;
				}
			}
			p_target[1] = (lefbor[i_limit]+rigbor[i_limit])>>1;
			p_target[1] = (p_target[1]+77)>>1;
			break;
		case 22://�뻷��
			max_col = 159-((float)(159-cut_fork_bottom_col)/(float)(89-bottom_point_row))*(89-point_folrow);//�����ұ߽�
			p_target[1] = (lefbor[point_folrow]+max_col)>>1;
			break;
		case 23://����
			folc_flag = 1;
			break;
		case 24://����
			max_col = 159-(159.0/(float)(89-rcut))*(82-point_folrow);//�����ұ߽�
			p_target[1] = (lefbor[point_folrow]+max_col)>>1;
			break;
	//	�һ�
		case 26://������
			for(i = MT9V03X_H-1; i > 0; i--){
				if(rigbor[i] < 139) ring_flag = 1;
				if(ring_flag){
					if(rigbor[i] < max_col) max_col = rigbor[i], i_limit = i;
					if(rigbor[i] > 139) break;
				}
			}
			p_target[1] = (lefbor[i_limit]+rigbor[i_limit])>>1;
			p_target[1] = (p_target[1]+83)>>1;
			break;
		case 27://�뻷��
			min_col = ((float)cut_fork_bottom_col/(float)(89-bottom_point_row))*(89-point_folrow);
			p_target[1] = (min_col+rigbor[point_folrow])>>1;
			break;
		case 28://����
			folc_flag = 1;
			break;
		case 29://����
			min_col = (159.0/(float)(89-lcut))*(82-point_folrow);
			p_target[1] = (min_col+rigbor[point_folrow])>>1;
			break;
	}
}
/*------------------------------*/
/*		   �������ģ�� 		*/
/*==============================*/
void cam_ctrl_bend(void){
	folc_flag = 1;
}
/*------------------------------*/
/*		   ֱ������ģ�� 		*/
/*==============================*/
void cam_ctrl_direct(void){
//	��������
	register unsigned char i;
	unsigned char max_col = 159, min_col = 0;
	unsigned char i_temp;
//	��������
	if(ring_out_flag){
		if(ring_out_flag == 1){
			if(lefbor[point_folrow] < 5){
				p_target[1] = (lefbor[bottom_point_row-16]+rigbor[bottom_point_row-16])>>1;
				p_target[1] = (p_target[1]+80)>>1;
				return;
			}
		}
		if(ring_out_flag){
			if(rigbor[point_folrow] > 154){
				p_target[1] = (lefbor[bottom_point_row-16]+rigbor[bottom_point_row-16])>>1;
				p_target[1] = (p_target[1]+80)>>1;
				return;
			}
		}
	}
//	�յ�
	if(count_fork > 7) {p_target[1] = 80; return;}
	folc_flag = 1;
}
/*--------------------------------------------------------------*/
/* 							 flash�洢 							*/
/*==============================================================*/
/*----------------------*/
/*	 flash������ʼ��	*/
/*======================*/
char flash_init(void){
//	ȷ���Ƿ�����ǰ����Ĳ���
	if(!(flash_check(FLASH_MEMORY_SLECTION, FLASH_PAGE_0))) return 1;
//	��ȡ�����ò���
	flash_page_read(FLASH_MEMORY_SLECTION, FLASH_PAGE_0, flash_memory, FLASH_NUM);
//	CAMת��
	cam_steering.Kp = (float)flash_memory[0]/1000;
	cam_steering.Kd = (float)flash_memory[1]/1000;
//	�ٶȿ���
	spd_set = (float)flash_memory[2]/1000;
//	׷�ٵ�
	point_folrow = (float)flash_memory[3]/1000;
	return 0;
}
/*----------------------*/
/*	  ���β�����ʼ��	*/
/*======================*/
void first_flash_init(void){
//	CAMת��
	flash_memory[0] = cam_steering.Kp*1000;
	flash_memory[1] = cam_steering.Kd*1000;
//	�ٶȿ���
	flash_memory[2] = spd_set*1000;
//	׷�ٵ�
	flash_memory[3] = point_folrow*1000;
//	������д��
	flash_erase_page(FLASH_MEMORY_SLECTION, FLASH_PAGE_0);
	flash_page_program(FLASH_MEMORY_SLECTION, FLASH_PAGE_0, flash_memory, FLASH_NUM);
}
/*----------------------*/
/*	  flash����д�� 	*/
/*======================*/
void flash_memory_write(unsigned char row, unsigned char col){
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
				case 0:
					flash_memory[2] = spd_set*1000;
					flash_memory[3] = point_folrow*1000;
					break;
			}
			break;
	}
//	������д��
	flash_erase_page(FLASH_MEMORY_SLECTION, FLASH_PAGE_0);
	flash_page_program(FLASH_MEMORY_SLECTION, FLASH_PAGE_0, flash_memory, FLASH_NUM);
}
