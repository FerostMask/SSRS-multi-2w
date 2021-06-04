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
	folc_flag = 1;
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

			break;
		case 22://�뻷��

			break;
		case 23://����

			break;
		case 24://����

			break;
	//	�һ�
		case 26://������

			break;
		case 27://�뻷��


			break;
		case 28://����

			break;
		case 29://����
	
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
//	�������
	if(lvet_trafcount){
		p_target[1] = (lefbor[lvet_trafpoint_row[0]]+rigbor[lvet_trafpoint_row[0]])>>1;
		return;
	}
	if(rvet_trafcount){
		p_target[1] = (lefbor[rvet_trafpoint_row[0]]+rigbor[rvet_trafpoint_row[0]])>>1;
		return;
	}
//	��������
	if(ring_out_flag == 1){
		if(found_point[0] < 60)
			p_target[1] = (lefbor[found_point[0]-10]+rigbor[found_point[0]-10])>>1;
		spd = 50;
		return;
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
