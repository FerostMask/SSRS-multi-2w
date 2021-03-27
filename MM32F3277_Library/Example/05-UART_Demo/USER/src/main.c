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

#include "headfile.h"

// *************************** 例程说明 ***************************
// 
// 测试需要准备逐飞科技 MM32F3277 核心板一块
// 
// 调试下载需要准备逐飞科技 CMSIS-DAP调试下载器 或 ARM调试下载器 一个
// 调试下载需要准备 USB转TTL 模块一个
// 
// 本例程初始化了逐飞科技 MM32F3277 核心板上的 UART1-A9/10 UART2-A2/3
// 
// 烧录本例程后 可见 UART1 输出的调试指导信息 UART2 使用中断接收方式
// 
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完
// 
// *************************** 例程说明 ***************************

// **************************** 宏定义 ****************************
// **************************** 宏定义 ****************************

// **************************** 变量定义 ****************************
uint8 uart1_get_buffer;
uint8 uart2_get_buffer;
bool uart2_interrupt_flag = false;													// 这个变量在 isr.c 的 UART2_IRQHandler 中置位
// **************************** 变量定义 ****************************

// **************************** 代码区域 ****************************
int main(void)
{
	board_init(true);																// 初始化 debug 输出串口

//	uart_init(UART_1, 115200, UART1_TX_A09, UART1_RX_A10);							// UART1 已经在 board_init(true); 初始化过了
	uart_init(UART_2, 115200, UART2_TX_A02, UART2_RX_A03);							// 默认初始化 UART1 用以支持 printf 输出
	uart_rx_irq(UART_2, ENABLE);													// 使能 UART2 的接收中断

	printf("\r\nSEEKFREE UART Demo printf test.");									// 输出信息
	printf("\r\nPlease input 'Y' to start.");										// 输出提示信息
	while(uart1_get_buffer != 'Y')													// 等待用户输入 Y
		uart_getchar(UART_1, &uart1_get_buffer);									// 获取用户输入
	printf("\r\nUART Demo printf test start.");										// 提示已通过

	while(1)
	{
		if(uart_query(UART_1, &uart1_get_buffer))									// 查询是否收到数据
			uart_putchar(UART_1, uart1_get_buffer);									// 发送收到的数据

		if(uart2_interrupt_flag)													// UART2 触发了接收中断
		{
			uart2_interrupt_flag = false;											// UART2 中断标志复位
			uart_putchar(UART_2, uart2_get_buffer);									// 发送收到的数据
		}
	}
}

void uart_interrupt_handler (void)													// 这个函数在 isr.c 的 UART2_IRQHandler 中调用
{
	uart2_interrupt_flag = true;													// UART2 中断标志置位
	uart_getchar(UART_2, &uart2_get_buffer);										// 读取数据
}
// **************************** 代码区域 ****************************
