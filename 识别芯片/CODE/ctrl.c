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

}
/*------------------------------*/
/*		   ֱ������ģ�� 		*/
/*==============================*/
void cam_ctrl_direct(void){

//	�������
	if(lvet_trafcount)
		p_target[1] = (lefbor[lvet_trafpoint_row[0]]+rigbor[lvet_trafpoint_row[0]])>>1;
	if(rvet_trafcount)
		p_target[1] = (lefbor[rvet_trafpoint_row[0]]+rigbor[rvet_trafpoint_row[0]])>>1;
//	��������
	if(ring_out_flag == 1){
		if(found_point[0] < 60)
			p_target[1] = (lefbor[found_point[0]-10]+rigbor[found_point[0]-10])>>1;
		spd = 50;
	}
//	�յ�
	if(count_fork > 7)
		p_target[1] = 80;
}
