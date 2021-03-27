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
// 
// 本例程初始化了逐飞科技 MM32F3277 核心板上的 TIM_3/4 两个定时器作为编码器采集输入
// 将编码器接在对应的 TIM_3-B04/B05  TIM_4-B06/B07
// 开启 SOFT_SIM_ENCODER 定义时 初始化了 A0/1 两个引脚作为模拟编码器波形输出
// 将 A0/1 接在对应的 TIM_3-B04/B05 或者 TIM_4-B06/B07
// 
// 烧录本例程后 接线完毕上电后可见从串口输出的编码器采集信息
// 
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完
// 
// *************************** 例程说明 ***************************

// **************************** 宏定义 ****************************
#define ENCODER_L					TIM_3
#define ENCODER_L_A					TIM_3_ENC1_B04
#define ENCODER_L_B					TIM_3_ENC2_B05
#define ENCODER_R					TIM_4
#define ENCODER_R_A					TIM_4_ENC1_B06
#define ENCODER_R_B					TIM_4_ENC2_B07

#define SOFT_SIM_ENCODER			1												// 1-开启模拟测试 使用GPIO模拟编码器波形 0-关闭模拟测试 使用编码器实物测试
#if SOFT_SIM_ENCODER
#define SOFT_SIM_ENCODER_A_PIN		A0
#define SOFT_SIM_ENCODER_B_PIN		A1
#endif
// **************************** 宏定义 ****************************

// **************************** 变量定义 ****************************
int16 encoder_count = 0;
// **************************** 变量定义 ****************************

// **************************** 代码区域 ****************************
#if SOFT_SIM_ENCODER
void soft_sim_encoder_positive (uint8 loop_count);
void soft_sim_encoder_inverted (uint8 loop_count);
#endif

int main(void)
{
	board_init(true);																// 初始化 debug 输出串口

	tim_encoder_init(ENCODER_L, ENCODER_L_A, ENCODER_L_B);							// 初始化正交编码器采集
	tim_encoder_init(ENCODER_R, ENCODER_R_A, ENCODER_R_B);							// 初始化正交编码器采集
#if SOFT_SIM_ENCODER
	gpio_init(SOFT_SIM_ENCODER_A_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);				// 初始化 GPIO 输入模拟编码器波形
	gpio_init(SOFT_SIM_ENCODER_B_PIN, GPO, GPIO_LOW, GPO_PUSH_PULL);				// 初始化 GPIO 输入模拟编码器波形
#endif

	while(1)
	{
#if SOFT_SIM_ENCODER
		soft_sim_encoder_positive(20);												// 模拟正交编码器正转波形20个 共80个边沿

		encoder_count = tim_encoder_get_count(ENCODER_L);							// 采集对应编码器数据
		tim_encoder_rst(ENCODER_L);													// 清除对应计数
		printf("\r\nENCODER_L encoder counter: %d.", encoder_count);				// 串口输出采集到数据

		encoder_count = tim_encoder_get_count(ENCODER_R);							// 采集对应编码器数据
		tim_encoder_rst(ENCODER_R);													// 清除对应计数
		printf("\r\nENCODER_R encoder counter: %d.", encoder_count);				// 串口输出采集到数据

		systick_delay_ms(1000);														// 时间间隔 1000ms

		soft_sim_encoder_inverted(20);												// 模拟正交编码器反转波形20个 共80个边沿

		encoder_count = tim_encoder_get_count(ENCODER_L);							// 采集对应编码器数据
		tim_encoder_rst(ENCODER_L);													// 清除对应计数
		printf("\r\nENCODER_L encoder counter: %d.", encoder_count);				// 串口输出采集到数据

		encoder_count = tim_encoder_get_count(ENCODER_R);							// 采集对应编码器数据
		tim_encoder_rst(ENCODER_R);													// 清除对应计数
		printf("\r\nENCODER_R encoder counter: %d.", encoder_count);				// 串口输出采集到数据

		systick_delay_ms(1000);														// 时间间隔 1000ms
#else
		encoder_count = tim_encoder_get_count(ENCODER_L);							// 采集对应编码器数据
		tim_encoder_rst(ENCODER_L);													// 清除对应计数
		printf("\r\nENCODER_L encoder counter: %d.", encoder_count);				// 串口输出采集到数据

		encoder_count = tim_encoder_get_count(ENCODER_R);							// 采集对应编码器数据
		tim_encoder_rst(ENCODER_R);													// 清除对应计数
		printf("\r\nENCODER_R encoder counter: %d.", encoder_count);				// 串口输出采集到数据

		systick_delay_ms(1000);														// 时间间隔 1000ms
#endif
	}
}

#if SOFT_SIM_ENCODER
void soft_sim_encoder_positive (uint8 loop_count)
{
	while(loop_count--)
	{
		gpio_set(SOFT_SIM_ENCODER_A_PIN, 1);
		systick_delay_ms(10);
		gpio_set(SOFT_SIM_ENCODER_B_PIN, 1);
		systick_delay_ms(10);
		gpio_set(SOFT_SIM_ENCODER_A_PIN, 0);
		systick_delay_ms(10);
		gpio_set(SOFT_SIM_ENCODER_B_PIN, 0);
		systick_delay_ms(10);
	}
}

void soft_sim_encoder_inverted (uint8 loop_count)
{
	while(loop_count--)
	{
		gpio_set(SOFT_SIM_ENCODER_B_PIN, 1);
		systick_delay_ms(10);
		gpio_set(SOFT_SIM_ENCODER_A_PIN, 1);
		systick_delay_ms(10);
		gpio_set(SOFT_SIM_ENCODER_B_PIN, 0);
		systick_delay_ms(10);
		gpio_set(SOFT_SIM_ENCODER_A_PIN, 0);
		systick_delay_ms(10);
	}
}
#endif
// **************************** 代码区域 ****************************
