/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "data.h"
#include "eident.h"
#include "CAM.h"
#include "ctrl.h"
#include "ctrl_alter1.h"
/*--------------------------------------------------------------*/
/*							  宏定义							*/
/*==============================================================*/
#define u8 unsigned char                                    //8位数据
#define u16 unsigned short                                  //16位数据
#define u32 unsigned int                                    //32位数据
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/
/*----------------------*/
/*	 	摄像头模块		*/
/*======================*/
//	大津法二值化
float P[256] = {0}, PK[256] = {0}, MK[256] = {0};
unsigned char binary_img[MT9V03X_H][(MT9V03X_W-4)/8];
unsigned char img_thrsod;
//	基准点寻找
unsigned char found_point[4];
unsigned char fop_flag;
unsigned char border_flag = 0;
//	水平边线寻找
unsigned char lefbor[MT9V03X_H], rigbor[MT9V03X_H], mid_point[MT9V03X_H];
unsigned char ltraf_point_row[10], rtraf_point_row[10], ltraf_point_col[10], rtraf_point_col[10];
unsigned char ltraf_flag[10], rtraf_flag[10];
unsigned char ltraf_count, rtraf_count;
unsigned char lcut, rcut;
//	垂直边线寻找
unsigned char topbor[MT9V03X_W-4], bottombor[MT9V03X_W-4];//上下边线
unsigned char lvet_trafpoint_row[5], rvet_trafpoint_row[5], lvet_trafpoint_col[5], rvet_trafpoint_col[5];//转变点
unsigned char lvet_trafcount, rvet_trafcount;//转变点计数
unsigned char leftop_cut, lefbottom_cut, rigtop_cut, rigbottom_cut;//截止列
unsigned char exti_lefp[4], exti_rigp[4], exti_lefcount, exti_rigcount;//出口
//	状态机
unsigned char act_flag, act_flag_temp, fragile_flag;
unsigned char state, state_temp;
unsigned char state_flag;
unsigned short img_color = 0xAE9C;
void(*state_pfc[])(void) = {state_machine_enter, state_machine_bend, state_machine_ring, state_machine_cross, state_machine_fork, state_machine_final};
//  岔道相关
unsigned char direction_fork, border_top[MT9V03X_W-4]; //0 左 1 右
unsigned char cnt_left, cnt_right;//数左右倾斜
unsigned char total_count_fork = 0;
unsigned short cut_fork_lef, cut_fork_rig, cut_fork_bottom_col;
unsigned char bottom_point_row;
unsigned char count_fork = 0;//终点检测
//	拐点相关
unsigned char infle_lefcount, infle_rigcount;
unsigned char infle_lefp[90], infle_rigp[90];
/*----------------------*/
/*	 	 控制模块		*/
/*======================*/
struct pidpara cam_steering;
short p_target[2];
short spd_set;
short spd, rad;
short rad_temp, rad_min, rad_max;
char folc_flag, cooling_flag = 0, ring_out_flag = 0;
unsigned char folrow_f = 63;
unsigned char ctrl_pointer = 0, dir_run_out;
//	一号代码
char ring_bias = -14;
unsigned short point_folrow;
void(*ctrl_pfc[])(void) = {cam_ctrl_direct, cam_ctrl_bend, cam_ctrl_ring, cam_ctrl_cross, cam_ctrl_fork, cam_ctrl_final};
//	二号代码
unsigned char bend_bias[] = {16, 20, 14, 12, 10, 10, 8, 6}; 
void(*ctrl_pfc_alter1[])(void) = {cam_ctrl_direct_alter1, cam_ctrl_bend_alter1, cam_ctrl_ring_alter1, cam_ctrl_cross_alter1, cam_ctrl_fork_alter1, cam_ctrl_final_alter1};
/*----------------------*/
/*	     flash存储		*/
/*======================*/
int flash_memory[256];
void(*Init_para_pfc[])(void) = {Init_para, Init_para_alter1};
char(*flash_init_pfc[])(void) = {flash_init, flash_init_alter1};
void(*first_flash_init_pfc[])(void) = {first_flash_init, first_flash_init_alter1};
void(*flash_memory_write_pfc[])(unsigned char, unsigned char) = {flash_memory_write, flash_memory_write_alter1};
/*----------------------*/
/*	 	 菜单模块		*/
/*======================*/
//	汉字数组
unsigned char nom[128];
//	一级菜单
unsigned char menu[ROWS] = {0, 0, 0, 0};
unsigned char menu_level;
unsigned char menu_index = 0;
//	二级菜单
unsigned char menu2_index = 0;
unsigned char menu2_level = 0;
//	标志位
unsigned char excollflag = 0;//电磁极值采集标志位
unsigned char fixedflag = 0;//固定显示
unsigned char monitorflag = 0;//监视器
unsigned char csimenu_flag[CSIMENU_FLAG] = {0, 0, 0};//摄像头
unsigned char run_flag[RUN_FLAG] = {0, 0, 0, 0};//发车
unsigned char flash_memory_flag[RUN_FLAG] = {0, 0};//数据存储
//	指针函数
void(*menu_pfc[])(unsigned char) = {menu_select, menu2_select};
/*----------------------*/
/*	 	 有来有去		*/
/*======================*/
unsigned char subuff_num = 0;
unsigned char subuff_arr[3];
unsigned short subuff_ranging;
/*----------------------*/
/*	 	 串口通信		*/
/*======================*/
unsigned char yawa_flag, action_flag;
short yawa, pita;
char buff_get6, buff_get7;
/*----------------------*/
/*	 	 电磁模块		*/
/*======================*/
//	结构体定义
struct adcpara adc2;
/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*----------------------*/
/*	 	参数初始化		*/
/*======================*/
void Init_para(void){
//	速度控制
	spd_set = 130;
//	出库方向
	dir_run_out = 0;
//	CAM转向
	cam_steering.Kp = 1.2;
	cam_steering.Kd = 0.1;
//	追踪点
	point_folrow = 70;
//	电磁模块
	adc2.max = 4095, adc2.min = 0;
}
/*----------------------*/
/*	 	参数初始化1		*/
/*======================*/
void Init_para_alter1(void){
//	速度控制
	spd_set = 130;
//	出库方向
	dir_run_out = 0;
//	CAM转向
	cam_steering.Kp = 1.2;
	cam_steering.Kd = 0.1;	
//	电磁模块
	adc2.max = 4095, adc2.min = 0;
}
