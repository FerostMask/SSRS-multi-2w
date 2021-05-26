/*********************************************************************************************************************
* COPYRIGHT NOTICE
* Copyright (c) 2019,逐飞科技
* All rights reserved.
* 技术讨论QQ群：一群：179029047(已满)  二群：244861897
*
* 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
* 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
*
* @file				main
* @company			成都逐飞科技有限公司
* @author			逐飞科技(QQ3184284598)
* @version			查看doc内version文件 版本说明
* @Software			IAR 8.3 or MDK 5.24
* @Target core		MM32F3277
* @Taobao			https://seekfree.taobao.com/
* @date				2021-02-22
********************************************************************************************************************/
/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "headfile.h"
#include "Init.h"
#include "menu.h"
#include "logo.h"
/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
int main(void){
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							初始化设置 							*/
/*==============================================================*/
/*----------------------*/
/*	 	 逐飞初始化		*/
/*======================*/
	board_init(true);																// 初始化 debug 输出串口
	//此处编写用户代码(例如：外设初始化代码等)
	icm20602_init_spi();
	ips200_init();
	uart_init(UART_7, 115200, UART7_TX_E08, UART7_RX_E07);
	uart_init(UART_6, 115200, UART6_TX_C06, UART6_RX_C07);
	uart_rx_irq(UART_7, 1);
	uart_rx_irq(UART_6, 1);
/*----------------------*/
/*	 	 用户初始化		*/
/*======================*/
	Init_motor();
	Init_encoder();
	if(core_select()){
		Init_button();
		menu_display();
	}
	seekfree_wireless_init();
	tim_interrupt_init_ms(TIM_2, 2, 0, 0);
/*--------------------------------------------------------------*/
/* 							 循环执行 							*/
/*==============================================================*/	
	while(1){
	//	此处编写需要循环执行的代码
	}
}
// **************************** 代码区域 ****************************
