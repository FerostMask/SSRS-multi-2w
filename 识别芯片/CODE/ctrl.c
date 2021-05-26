/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "ctrl.h"
#include "data.h"
#include "pid.h"
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*------------------------------*/
/*		   岔道控制模块 		*/
/*==============================*/
void cam_ctrl_fork(void){
//	控制
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
/*		   十字控制模块 		*/
/*==============================*/
void cam_ctrl_cross(void){
//	控制
	p_target[1] = ((lefbor[45]+rigbor[45]))+((lefbor[63]+rigbor[63]))>>2;
	folc_flag = 0;
}
/*------------------------------*/
/*		   环道控制模块 		*/
/*==============================*/
void cam_ctrl_ring(void){
//	变量定义
	unsigned char mp;
	float slope_temp;
//	控制
	switch(act_flag){
	//	左环
		case 21://出环口
		//	特殊控制
			if(lvet_trafcount)
				{p_target[1] = (lefbor[lvet_trafpoint_row[0]]+rigbor[lvet_trafpoint_row[0]])>>1, folc_flag = 0; return;}
			p_target[1] = (lefbor[90]+rigbor[90])>>1;
			p_target[1] = (p_target[1]+80)>>1;
			folc_flag = 0;
			break;
		case 22://入环口
			p_target[1] = ((leftop_cut+lefbottom_cut)>>1);
			p_target[1] = ((p_target[1]+95)>>1);
			rad_min = 159, rad_max = 0;
			spd = speed.ring[1];
			folc_flag = 0;
			break;
		case 23://环内
			p_target[1] = ((lefbor[56]+rigbor[56]))+((lefbor[63]+rigbor[63]))>>2;
			rad_temp = p_target[1];
			if(p_target[1] < rad_min) rad_min = p_target[1];
			if(p_target[1] > rad_max) rad_max = p_target[1];
			folc_flag = 0;
			break;
		case 24://出环
			p_target[1] = (rad_min+rad_max)>>1;
			p_target[1] = ((p_target[1]+55)>>1);
			spd = speed.ring[3];
			folc_flag = 0;
			break;
	//	右环
		case 26://出环口
			p_target[1] = (lefbor[90]+rigbor[90])>>1;
			p_target[1] = (p_target[1]+81)>>1;
			if(p_target[1] < 80) p_target[1] = 80;
			spd = speed.ring[0];
			folc_flag = 0;
			break;
		case 27://入环口
			if(exti_rigcount){
				p_target[1] = ((rigtop_cut+rigbottom_cut)>>1);
				p_target[1] = ((p_target[1]+70)>>1)+1;
				folc_flag = 0;
			}
			rad_min = 159, rad_max = 0;
			break;
		case 28://环内
			folrow_f = 63;
			if(p_target[1] < rad_min && p_target[1] > 80) rad_min = p_target[1];
			if(p_target[1] > rad_max) rad_max = p_target[1];
			break;
		case 29://出环
			p_target[1] = (rad_min+rad_max)>>1;
			p_target[1] = ((p_target[1]+90)>>1);
			folc_flag = 0;
			break;
	}
}
/*------------------------------*/
/*		   弯道控制模块 		*/
/*==============================*/
void cam_ctrl_bend(void){
//	变量定义
	register unsigned char i;
	unsigned char mp;
	unsigned char fp[4];
	unsigned char fop;
	float slope_temp;
//	控制
	switch(act_flag){
		case 11://左转丢边
			folrow_f = 45;
			break;
		case 12://右转丢边
			folrow_f = 45;
			break;
		case 13://左弯
			p_target[1] = ((lefbor[56]+rigbor[56]))+((lefbor[63]+rigbor[63]))>>2;
			folc_flag = 0;
			break;
		case 14://右弯
			p_target[1] = ((lefbor[56]+rigbor[56]))+((lefbor[63]+rigbor[63]))>>2;
			folc_flag = 0;
			break;
	}
}
/*------------------------------*/
/*		   直道控制模块 		*/
/*==============================*/
void cam_ctrl_direct(void){
//	变量定义
	unsigned char point_temp;
//	控制
	p_target[1] = ((lefbor[45]+rigbor[45]))+((lefbor[63]+rigbor[63]))>>2;
	folc_flag = 0;
//	特殊控制
	if(lvet_trafcount)
		p_target[1] = (lefbor[lvet_trafpoint_row[0]]+rigbor[lvet_trafpoint_row[0]])>>1;
}
