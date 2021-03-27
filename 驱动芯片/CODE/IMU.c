/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "IMU.h"
#include "pid.h"
#include "math.h"
#include "motor.h"
#include "MadgwickAHRS.h"
#include "SEEKFREE_VIRSCO.h"
#include "SEEKFREE_WIRELESS.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/*							  宏定义							*/
/*==============================================================*/
#define u8 unsigned char                                    //8位数据
#define u16 unsigned short                                  //16位数据
#define u32 unsigned int                                    //32位数据
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/
//unsigned char temp[4] = {0, 0, 0, 0};
/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*----------------------*/
/*	   角度控制模块		*/
/*======================*/
void angle_ctrl(void){
//	变量定义
	char i;
	static unsigned char imu_count;
//	计数器循环
	imu_count = (imu_count+1)&3;
//	角速度滤波
	for(i = 2; i >= 0; i--) yfilt[i+1] = yfilt[i];
	yfilt[0] = icm_gyro_y;
	gy = (yfilt[0] + yfilt[1] + yfilt[2] + yfilt[3])/65.6;
//	串级PID
	if(imu_count == 3){
	//	计算航向角、车身倾角
		yawa[1] = yawa[0];
		yawa[0] = atan2(2*(q1*q2 + q0*q3), q0*q0 + q1*q1 -q2*q2 -q3*q3)*5730;
//		inc_pid(&steer, rad, yawa[0]-yawa[1], 800);
		inc_pid(&speed, -spd, (lcod+rcod)>>1, 50);
	}
//	角度
	if(imu_count == 1 || imu_count == 3){
	//	姿态解算
		MadgwickAHRSupdateIMU(icm_gyro_x/(16.4*57.3), icm_gyro_y/(16.4*57.3), icm_gyro_z/(16.4*57.3), (9.8*icm_acc_x)/8192, (9.8*icm_acc_y)/8192, (9.8*icm_acc_z)/8192);
	//	计算俯仰角、车身角速度	
		for(i = 2; i >= 0; i--) pflit[i+1] = pflit[i];
		pflit[0] = (asin(-2*q1*q3 + 2*q0*q2))*573;
		pita = (pflit[0]+pflit[1]+pflit[2]+pflit[3])/4;
		pos_pid(&angle, blcp-speed.rs, pita, 15, -15);
	}
//	角速度、转向速度、电机控制	
	inc_pid(&acw, angle.rs, gy, 6000);
	motor_act();
//	角度显示
//	ips200_showint16(0, 3, pita);
//	ips200_showint16(0, 4, yawa[0]);
//	无线数据传输
//	data_conversion(gy, acw.rs, angle.rs, pita, temp);
}
