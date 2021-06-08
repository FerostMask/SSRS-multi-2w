/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "ctrl.h"
#include "data.h"
#include "pid.h"
#include "zf_flash.h"
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*------------------------------*/
/*		   终点控制模块 		*/
/*==============================*/
void cam_ctrl_final(void){
//  控制
    folc_flag = 0;
//    if(cut_fork_bottom > 92) cnt_start++;
        switch(act_flag){
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
void cam_ctrl_fork(void){
//	变量定义
	register unsigned char i;
	unsigned char i_limit, max_col = 159, min_col = 0;
//	控制
	if(direction_fork){//右
		min_col = cut_fork_bottom_col - ((float)(border_top[cut_fork_rig] - bottom_point_row)/(float)(cut_fork_bottom_col - cut_fork_rig))*(point_folrow-bottom_point_row);//解算左边界
		p_target[1] = (min_col+rigbor[point_folrow])>>1;
	}
	else{//左
		max_col = cut_fork_bottom_col + ((float)(border_top[cut_fork_lef] - bottom_point_row)/(float)(cut_fork_lef - cut_fork_bottom_col))*(point_folrow-bottom_point_row);//解算右边界
		p_target[1] = (lefbor[point_folrow]+max_col)>>1;
	}
}
/*------------------------------*/
/*		   十字控制模块 		*/
/*==============================*/
void cam_ctrl_cross(void){
	folc_flag = 1;
}
/*------------------------------*/
/*		   环道控制模块 		*/
/*==============================*/
void cam_ctrl_ring(void){
//	变量定义
	register unsigned char i;
	unsigned char i_limit, max_col = 159, min_col = 0;
	unsigned char ring_flag = 0;
//	控制
	switch(act_flag){
	//	左环
		case 21://出环口
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
		case 22://入环口
			max_col = 159-((float)(159-cut_fork_bottom_col)/(float)(89-bottom_point_row))*(89-point_folrow);//计算右边界
			p_target[1] = (lefbor[point_folrow]+max_col)>>1;
			break;
		case 23://环内
			folc_flag = 1;
			break;
		case 24://出环
			max_col = 159-(159.0/(float)(89-rcut))*(82-point_folrow);//计算右边界
			p_target[1] = (lefbor[point_folrow]+max_col)>>1;
			break;
	//	右环
		case 26://出环口
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
		case 27://入环口
			min_col = ((float)cut_fork_bottom_col/(float)(89-bottom_point_row))*(89-point_folrow);
			p_target[1] = (min_col+rigbor[point_folrow])>>1;
			break;
		case 28://环内
			folc_flag = 1;
			break;
		case 29://出环
			min_col = (159.0/(float)(89-lcut))*(82-point_folrow);
			p_target[1] = (min_col+rigbor[point_folrow])>>1;
			break;
	}
}
/*------------------------------*/
/*		   弯道控制模块 		*/
/*==============================*/
void cam_ctrl_bend(void){
	folc_flag = 1;
}
/*------------------------------*/
/*		   直道控制模块 		*/
/*==============================*/
void cam_ctrl_direct(void){
//	变量定义
	register unsigned char i;
	unsigned char max_col = 159, min_col = 0;
	unsigned char i_temp;
//	环岛控制
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
//	终点
	if(count_fork > 7) {p_target[1] = 80; return;}
	folc_flag = 1;
}
/*--------------------------------------------------------------*/
/* 							 flash存储 							*/
/*==============================================================*/
/*----------------------*/
/*	 flash参数初始化	*/
/*======================*/
char flash_init(void){
//	确认是否有提前保存的参数
	if(!(flash_check(FLASH_MEMORY_SLECTION, FLASH_PAGE_0))) return 1;
//	读取、启用参数
	flash_page_read(FLASH_MEMORY_SLECTION, FLASH_PAGE_0, flash_memory, FLASH_NUM);
//	CAM转向
	cam_steering.Kp = (float)flash_memory[0]/1000;
	cam_steering.Kd = (float)flash_memory[1]/1000;
//	速度控制
	spd_set = (float)flash_memory[2]/1000;
//	追踪点
	point_folrow = (float)flash_memory[3]/1000;
	return 0;
}
/*----------------------*/
/*	  初次参数初始化	*/
/*======================*/
void first_flash_init(void){
//	CAM转向
	flash_memory[0] = cam_steering.Kp*1000;
	flash_memory[1] = cam_steering.Kd*1000;
//	速度控制
	flash_memory[2] = spd_set*1000;
//	追踪点
	flash_memory[3] = point_folrow*1000;
//	擦除后写入
	flash_erase_page(FLASH_MEMORY_SLECTION, FLASH_PAGE_0);
	flash_page_program(FLASH_MEMORY_SLECTION, FLASH_PAGE_0, flash_memory, FLASH_NUM);
}
/*----------------------*/
/*	  flash参数写入 	*/
/*======================*/
void flash_memory_write(unsigned char row, unsigned char col){
//	行选择
	switch(row){
	//	列选择
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
//	擦除后写入
	flash_erase_page(FLASH_MEMORY_SLECTION, FLASH_PAGE_0);
	flash_page_program(FLASH_MEMORY_SLECTION, FLASH_PAGE_0, flash_memory, FLASH_NUM);
}
