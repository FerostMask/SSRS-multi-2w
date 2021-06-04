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
	folc_flag = 1;
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
	unsigned char mp;
	float slope_temp;
	register unsigned char i;
	unsigned char point_temp;
	short bias_temp;
//	控制
	switch(act_flag){
	//	左环
		case 21://出环口
		//	特殊控制

			break;
		case 22://入环口

			break;
		case 23://环内

			break;
		case 24://出环

			break;
	//	右环
		case 26://出环口

			break;
		case 27://入环口


			break;
		case 28://环内

			break;
		case 29://出环
	
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
//	特殊控制
	if(lvet_trafcount){
		p_target[1] = (lefbor[lvet_trafpoint_row[0]]+rigbor[lvet_trafpoint_row[0]])>>1;
		return;
	}
	if(rvet_trafcount){
		p_target[1] = (lefbor[rvet_trafpoint_row[0]]+rigbor[rvet_trafpoint_row[0]])>>1;
		return;
	}
//	环岛控制
	if(ring_out_flag == 1){
		if(found_point[0] < 60)
			p_target[1] = (lefbor[found_point[0]-10]+rigbor[found_point[0]-10])>>1;
		spd = 50;
		return;
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
