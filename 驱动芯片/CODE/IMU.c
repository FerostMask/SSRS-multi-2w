/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "IMU.h"
#include "pid.h"
#include "math.h"
#include "motor.h"
#include "MadgwickAHRS.h"
#include "SEEKFREE_VIRSCO.h"
#include "SEEKFREE_TSL1401.h"
#include "SEEKFREE_WIRELESS.h"
#include "SEEKFREE_ICM20602.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*----------------------*/
/*	   角度控制模块		*/
/*======================*/
void angle_ctrl(void){
//	变量定义
	register char i ;
	static unsigned char imu_count, sbuf_count, spd_count;
//	计数器循环
	spd_count++;
	imu_count = !imu_count;
	sbuf_count = (sbuf_count+1)&15;
//	角速度滤波
	for(i = 2; i >= 0; i--) yfilt[i+1] = yfilt[i];
	yfilt[0] = icm_gyro_y;
	gy = (yfilt[0] + yfilt[1] + yfilt[2] + yfilt[3])/65.6;
//	串级PID
	if(spd_count == 4){
	//	速度PID
			spd_count = 0;
			pos_pid(&speed, spd, (lcod+rcod)>>1, 360, -360);
	}
//	角度
	if(imu_count){
	//	姿态解算
		MadgwickAHRSupdateIMU(icm_gyro_x/(16.4*57.3), icm_gyro_y/(16.4*57.3), icm_gyro_z/(16.4*57.3), (9.8*icm_acc_x)/8192, (9.8*icm_acc_y)/8192, (9.8*icm_acc_z)/8192);
	//	计算俯仰角、车身角速度	
		for(i = 2; i >= 0; i--) pflit[i+1] = pflit[i];
		pflit[0] = (asin(-2*q1*q3 + 2*q0*q2))*573;
		pita = (pflit[0]+pflit[1]+pflit[2]+pflit[3])/4;
		pos_pid(&steer, rad, gz, 200, -200);
		pos_pid(&angle, blcp, pita-speed.rs, 400, -400);
	}
//	角速度、电机、航向角控制
	gz = (icm_gyro_z/(164*573))/(float)(((lcod+rcod)>>1));
	inc_pid(&lefdif, ((lcod+rcod)>>1)-steer.rs, lcod, 3500);
	inc_pid(&rigdif, ((lcod+rcod)>>1)+steer.rs, rcod, 3500);
	inc_pid(&acw, angle.rs, gy, 5000);
	motor_act();
//	串口发送角度变化
	if(!sbuf_count){
		yawa_temp = yawa;
		yawa = atan2(2*(q1*q2 + q0*q3), q0*q0 + q1*q1 -q2*q2 -q3*q3)*57.3;
		uart_putchar(UART_6, yawa_temp-yawa);
		uart_putchar(UART_7, pita/10);
	}
}
