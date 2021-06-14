/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "data.h"
#include "zf_flash.h"
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
/*	     flash存储		*/
/*======================*/
int flash_memory[256];
/*----------------------*/
/*	    线性CCD模块		*/
/*======================*/
unsigned cjug_sta;
/*----------------------*/
/*	 	 MOTOR模块		*/
/*======================*/
//	编码器
short lcod = 0,rcod = 0;
short spd = 0;
short rad = 0;
short lef_pwm, rig_pwm;
//	PID
struct pidpara speed;
struct pidpara lefdif;
struct pidpara rigdif;
struct pidpara steer;
struct pidpara angle;
struct pidpara acw;
/*----------------------*/
/*	   角度控制模块		*/
/*======================*/
int gy, gz;
short blcp;
short pita, yawa, yawa_temp;
short yfilt[4] = {0, 0, 0, 0};
short pflit[4] = {0, 0, 0, 0};
/*----------------------*/
/*	 	 菜单模块		*/
/*======================*/
//	汉字数组
unsigned char nom[128];
//	一级菜单
unsigned char menu[ROWS];
unsigned char menu_level;
unsigned char menu_index = 0;
//	二级菜单
unsigned char menu2_index = 0;
unsigned char menu2_level = 0;
//	标志位
unsigned char fixedflag = 0;//固定显示
unsigned char monitorflag = 0;//监视器
unsigned char csimenu_flag[CSIMENU_FLAG] = {0, 0};//摄像头
unsigned char state_flag[STATE_FLAG] = {0, 0};//无线数据
//	函数指针
void(*menu_pfc[])(unsigned char) = {menu_select, menu2_select};
/*----------------------*/
/*	 	 通信模块		*/
/*======================*/
unsigned char buff_get6, buff_get7;
unsigned char dst_flag = 0, final_flag = 0;
unsigned char launch_command[3] = {0xA7, 0xB9, 0x12};
int distance = 0;
/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*----------------------*/
/*	 	参数初始化		*/
/*======================*/
//	PID
void Init_para(void){
//	其他参数
	blcp = 332;//平衡点
	
//	转向
	steer.Kp = 0.6;//反应快慢 | 超调
	steer.Kd = 0.2;
	
//	左轮差速
	lefdif.alpha = 0.3;
	lefdif.Kp = 30;//反应快慢 | 超调
	lefdif.Ki = 1.2;//反应力度
	lefdif.Kd = 0;

//	右轮差速
	rigdif.alpha = 0.3;
	rigdif.Kp = 30;//反应快慢 | 超调
	rigdif.Ki = 1.1;//反应力度
	rigdif.Kd = 0;
	
//	速度
	speed.Kp = 1.1;//反应快慢 | 超调
	speed.Kd = 0.3;	
	
//	角度
	angle.Kp = 1.9;//力度
	angle.Kd = 0.09;//抖动

//	角速度
	acw.alpha = 0.02;
	acw.Kp = 27;//反应快慢 | 超调
	acw.Ki = 0.32;//反应力度
	acw.Kd = 0.0;
}
/*----------------------*/
/*	 flash参数初始化	*/
/*======================*/
char flash_init(void){
//	确认是否有提前保存的参数
	if(!(flash_check(FLASH_MEMORY_SLECTION, FLASH_PAGE_0))) return 1;
//	读取、启用参数
	flash_page_read(FLASH_MEMORY_SLECTION, FLASH_PAGE_0, flash_memory, FLASH_NUM);
//	转向
	steer.Kp = (float)flash_memory[0]/1000;
	steer.Kd = (float)flash_memory[1]/1000;
//	左轮差速
	lefdif.alpha = (float)flash_memory[2]/1000;
	lefdif.Kp = (float)flash_memory[3]/1000;
	lefdif.Ki = (float)flash_memory[4]/1000;
	lefdif.Kd = (float)flash_memory[5]/1000;
//	右轮差速
	rigdif.alpha = (float)flash_memory[6]/1000;
	rigdif.Kp = (float)flash_memory[7]/1000;
	rigdif.Ki = (float)flash_memory[8]/1000;
	rigdif.Kd = (float)flash_memory[9]/1000;
//	速度
	speed.Kp = (float)flash_memory[10]/1000;
	speed.Kd = (float)flash_memory[11]/1000;	
//	角度
	angle.Kp = (float)flash_memory[12]/1000;
	angle.Kd = (float)flash_memory[13]/1000;
//	角速度
	acw.alpha = (float)flash_memory[14]/1000;
	acw.Kp = (float)flash_memory[15]/1000;
	acw.Ki = (float)flash_memory[16]/1000;
	acw.Kd = (float)flash_memory[17]/1000;
//	其他参数
	blcp = (float)flash_memory[18]/1000;
	return 0;
}
/*----------------------*/
/*	  初次参数初始化	*/
/*======================*/
void first_flash_init(void){
//	转向
	flash_memory[0] = steer.Kp*1000;
	flash_memory[1] = steer.Kd*1000;
//	左轮差速
	flash_memory[2] = lefdif.alpha*1000;
	flash_memory[3] = lefdif.Kp*1000;
	flash_memory[4] = lefdif.Ki*1000;
	flash_memory[5] = lefdif.Kd*1000;
//	右轮差速
	flash_memory[6] = rigdif.alpha*1000;
	flash_memory[7] = rigdif.Kp*1000;
	flash_memory[8] = rigdif.Ki*1000;
	flash_memory[9] = rigdif.Kd*1000;
//	速度
	flash_memory[10] = speed.Kp*1000;
	flash_memory[11] = speed.Kd*1000;	
//	角度
	flash_memory[12] = angle.Kp*1000;
	flash_memory[13] = angle.Kd*1000;
//	角速度
	flash_memory[14] = acw.alpha*1000;
	flash_memory[15] = acw.Kp*1000;
	flash_memory[16] = acw.Ki*1000;
	flash_memory[17] = acw.Kd*1000;
//	其他参数
	flash_memory[18] = blcp*1000;
//	擦除后写入
	flash_erase_page(FLASH_MEMORY_SLECTION, FLASH_PAGE_0);
	flash_page_program(FLASH_MEMORY_SLECTION, FLASH_PAGE_0, flash_memory, FLASH_NUM);
}
/*----------------------*/
/*	  flash参数写入 	*/
/*======================*/
void flash_memory_write(row, col){
//	行选择
	switch(row){
	//	列选择
		case PARASET_PID1:
			switch(col){
				case 0:
					flash_memory[10] = speed.Kp*1000;
					flash_memory[11] = speed.Kd*1000;	
					break;
				case 1:
					flash_memory[12] = angle.Kp*1000;
					flash_memory[13] = angle.Kd*1000;
					break;
				case 2:
					flash_memory[14] = acw.alpha*1000;
					flash_memory[15] = acw.Kp*1000;
					flash_memory[16] = acw.Ki*1000;
					flash_memory[17] = acw.Kd*1000;
					break;
			}
			break;
		case PARASET_PID2:
			switch(col){
				case 0:
					flash_memory[0] = steer.Kp*1000;
					flash_memory[1] = steer.Kd*1000;
					break;
				case 1:
					flash_memory[2] = lefdif.alpha*1000;
					flash_memory[3] = lefdif.Kp*1000;
					flash_memory[4] = lefdif.Ki*1000;
					flash_memory[5] = lefdif.Kd*1000;
					break;
				case 2:
					flash_memory[6] = rigdif.alpha*1000;
					flash_memory[7] = rigdif.Kp*1000;
					flash_memory[8] = rigdif.Ki*1000;
					flash_memory[9] = rigdif.Kd*1000;
					break;
			}
			break;
		case PARASET_OPER:
			switch(col){
				case 0:
					flash_memory[18] = blcp*1000;
					break;
			}
			break;
	}
//	擦除后写入
	flash_erase_page(FLASH_MEMORY_SLECTION, FLASH_PAGE_0);
	flash_page_program(FLASH_MEMORY_SLECTION, FLASH_PAGE_0, flash_memory, FLASH_NUM);
}
