/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "ctrl_alter1.h"
#include "data.h"
#include "pid.h"
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*------------------------------*/
/*		   终点控制模块 		*/
/*==============================*/
void cam_ctrl_final_alter1(void){
//  控制
    folc_flag = 0;
//    if(cut_fork_bottom > 92) cnt_start++;
        switch(state){
            case 56://左出库

            break;
            case 55://右出库
                p_target[1] = ((80+rigbottom_cut)>>1);

            break;
            case 51://右入库
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
/*		   岔道控制模块 		*/
/*==============================*/
void cam_ctrl_fork_alter1(void){
//	控制
    p_target[0] = topbor[cut_fork_bottom];
    if(direction_fork){
        p_target[1] = (MT9V03X_W + cut_fork_bottom) >> 1;
    }else{
        p_target[1] = cut_fork_bottom >> 1;
    }
}
/*------------------------------*/
/*		   十字控制模块 		*/
/*==============================*/
void cam_ctrl_cross_alter1(void){
//	控制
	p_target[1] = ((lefbor[45]+rigbor[45]))+((lefbor[63]+rigbor[63]))>>2;
	folc_flag = 0;
}
/*------------------------------*/
/*		   环道控制模块 		*/
/*==============================*/
void cam_ctrl_ring_alter1(void){
//	变量定义
	register unsigned char i;
	unsigned char mp;
	short bias_temp = 0;
	unsigned char bend_bias[] = {22, 26, 16, 10, 6, 4, 2, 8};
//	控制
	switch(act_flag){
		case 21://出环口
		//	特殊控制
			if(lvet_trafcount)
				{p_target[1] = (lefbor[lvet_trafpoint_row[0]]+rigbor[lvet_trafpoint_row[0]])>>1, folc_flag = 0; return;}
			p_target[1] = (lefbor[90]+rigbor[90])>>1;
			p_target[1] = (p_target[1]+77)>>1;
			break;
		case 22://入环口
			p_target[1] = ((leftop_cut+lefbottom_cut)>>1);
			p_target[1] = ((p_target[1]+85)>>1);
			rad_min = 159, rad_max = 0;
			break;
		case 23://环内
		//	加权算法
			for(i = 0; i < 8; i++)
				bias_temp += (lefbor[30+(i<<2)]+rigbor[30+(i<<2)] - 160)*bend_bias[i];
			p_target[1] = (bias_temp>>7)+80;
			if(p_target[1] < rad_min) rad_min = p_target[1];
			if(p_target[1] > rad_max && p_target[1] < 80) rad_max = p_target[1];
			break;
		case 24://出环
			p_target[1] = (rad_min+rad_max)>>1;
			p_target[1] = ((p_target[1]+55)>>1);
			break;
	//	右环
		case 26://出环口
//			if(rvet_trafcount)
//				{p_target[1] = (lefbor[rvet_trafpoint_row[0]]+rigbor[rvet_trafpoint_row[0]])>>1, folc_flag = 0; return;}
			p_target[1] = (lefbor[90]+rigbor[90])>>1;
			p_target[1] = (p_target[1]+80)>>1;
			break;
		case 27://入环口
			if(exti_rigcount){
				p_target[1] = ((rigtop_cut+rigbottom_cut)>>1);
				p_target[1] = ((p_target[1]+70)>>1)+1;
			}
			rad_min = 159, rad_max = 0;
			break;
		case 28://环内
		//	加权算法
			for(i = 0; i < 8; i++)
				bias_temp += (lefbor[30+(i<<2)]+rigbor[30+(i<<2)] - 160)*bend_bias[i];
			p_target[1] = (bias_temp>>7)+80;
			folc_flag = 0;
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
void cam_ctrl_bend_alter1(void){
//	变量定义
	register unsigned char i;
	short bias_temp = 0;
	unsigned char bend_bias[] = {22, 26, 16, 10, 6, 4, 2, 8};
//	加权算法
	for(i = 0; i < 8; i++)
		bias_temp += (lefbor[30+(i<<2)]+rigbor[30+(i<<2)] - 160)*bend_bias[i];
	p_target[1] = (bias_temp>>7)+80;
//	控制
	switch(act_flag){
		case 11://左转丢边
			folrow_f = 43;
			break;
		case 12://右转丢边
			folrow_f = 43;
			break;
		case 13://左弯
			folrow_f = 43;
			break;
		case 14://右弯
			folrow_f = 43;
			break;
	}
}
/*------------------------------*/
/*		   直道控制模块 		*/
/*==============================*/
void cam_ctrl_direct_alter1(void){
//	变量定义
	register unsigned char i;
	unsigned char point_temp;
	short bias_temp;
	unsigned char bend_bias[] = {22, 26, 16, 10, 6, 4, 2, 8};
//	控制
	if(exti_lefcount > 0)
		if(!exti_rigcount)
			spd = 40;
	if(exti_rigcount > 0)
		if(!exti_lefcount)
			spd = 40;
//	加权算法
	for(i = 0; i < 8; i++)
		bias_temp += (lefbor[30+(i<<2)]+rigbor[30+(i<<2)] - 160)*bend_bias[i];
	p_target[1] = (bias_temp>>7)+80;
	folc_flag = 0;
//	特殊控制
	if(lvet_trafcount)
		p_target[1] = (lefbor[lvet_trafpoint_row[0]]+rigbor[lvet_trafpoint_row[0]])>>1;
//	环岛控制
	if(ring_out_flag == 1){
		if(found_point[0] < 60)
			p_target[1] = (lefbor[found_point[0]-10]+rigbor[found_point[0]-10])>>1;
		spd = 30;
	}
}
