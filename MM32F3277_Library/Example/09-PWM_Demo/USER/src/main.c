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
// 本例程初始化了逐飞科技 MM32F3277 核心板上的 A0/1/2/3 作为 TIM2 的 PWM 输出
// 请不要使用本例程来测试驱动或者驱动电机
// 
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完
// 
// *************************** 例程说明 ***************************

// **************************** 宏定义 ****************************
#define PWM_TIM				TIM_2
#define PWM_CH1				TIM_2_CH1_A00
#define PWM_CH2				TIM_2_CH2_A01
#define PWM_CH3				TIM_2_CH3_A02
#define PWM_CH4				TIM_2_CH4_A03
// **************************** 宏定义 ****************************

// **************************** 变量定义 ****************************
uint16 duty;
bool output_dir = false;
// **************************** 变量定义 ****************************

// **************************** 代码区域 ****************************
int main(void)
{
	board_init(true);																// 初始化 debug 输出串口

	pwm_init(PWM_TIM, PWM_CH1, 10000, 0);											// 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%
	pwm_init(PWM_TIM, PWM_CH2, 10000, 0);											// 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%
	pwm_init(PWM_TIM, PWM_CH3, 10000, 0);											// 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%
	pwm_init(PWM_TIM, PWM_CH4, 10000, 0);											// 初始化TIM2 频率10KHz 初始占空比为 0/PWM_DUTY_MAX*100%

	while(1)
	{
		if(output_dir)																// 防止接上电机跑PWM导致驱动双向导通
		{
			pwm_duty_updata(PWM_TIM, PWM_CH1, duty);								// 通道 1 输出
			pwm_duty_updata(PWM_TIM, PWM_CH2, 0);									// 通道 2 停止
			pwm_duty_updata(PWM_TIM, PWM_CH3, duty);								// 通道 3 输出
			pwm_duty_updata(PWM_TIM, PWM_CH4, 0);									// 通道 4 停止

			duty += 100;															// 更新占空比
			if(duty > PWM_DUTY_MAX/2)												// 占空比不超过 50%
			{
				duty = 0;															// 占空比清空
				output_dir = false;													// 翻转输出
			}
			systick_delay_ms(20);
		}
		else
		{
			pwm_duty_updata(PWM_TIM, PWM_CH1, 0);									// 通道 1 停止
			pwm_duty_updata(PWM_TIM, PWM_CH2, duty);								// 通道 2 输出
			pwm_duty_updata(PWM_TIM, PWM_CH3, 0);									// 通道 3 停止
			pwm_duty_updata(PWM_TIM, PWM_CH4, duty);								// 通道 4 输出

			duty += 100;															// 更新占空比
			if(duty > PWM_DUTY_MAX/2)												// 占空比不超过 50%
			{
				duty = 0;															// 占空比清空
				output_dir = true;													// 翻转输出
			}
			systick_delay_ms(20);
		}
	}
}
// **************************** 代码区域 ****************************
