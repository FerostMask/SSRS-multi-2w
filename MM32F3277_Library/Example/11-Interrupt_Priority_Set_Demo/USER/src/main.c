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
// 本例程初始化了逐飞科技 MM32F3277 核心板上的 UART1-A9/10
// 初始化了 TIM1 周期中断 优先级次高 0x01
// 初始化了 D0 作为外部中断输入 优先级最高  0x00
// 初始化了 D1 作为GPIO输入
// 初始化了 B13/H2 为GPIO输出 用来驱动LED作为状态演示
// 
// 烧录本例程后可见 B13 标识的LED闪烁 该 LED 在 TIM1 中断中控制闪烁
// 按下 D0 按键后触发外部中断 此时 H2 标识的 LED 亮起 B13 的LED停止闪烁
// 按下 D1 按键后从外部中断退出 H2 熄灭 B13 继续闪烁
// 
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完
// 
// *************************** 例程说明 ***************************

// **************************** 宏定义 ****************************
#define PIT_TIM						TIM_1

#define LED1						B13
#define LED2						H2
#define EXTI_KEY					D0
#define IO_KEY						D1

#define EXTI_KEY_INT				EXTI0_IRQn
#define PIT_TIM_INT					TIM1_UP_IRQn
// **************************** 宏定义 ****************************

// **************************** 变量定义 ****************************
uint8 uart1_get_buffer;
uint8 uart2_get_buffer;
bool uart2_interrupt_flag = false;
// **************************** 变量定义 ****************************

// **************************** 代码区域 ****************************
int main(void)
{
	board_init(true);																// 初始化 debug 输出串口

	gpio_init(LED1, GPO, GPIO_HIGH, GPO_PUSH_PULL);									// 初始化为GPIO功能 输出 默认高电平
	gpio_init(LED2, GPO, GPIO_HIGH, GPO_PUSH_PULL);									// 初始化为GPIO功能 输出 默认高电平
	gpio_init(IO_KEY, GPI, GPIO_HIGH, GPI_FLOATING_IN);								// 初始化为GPIO功能 输入 上拉

	exti_interrupt_init(EXTI_KEY, EXTI_Trigger_Rising, 0x00, 0x01);					// 初始化为外部中断输入 上升沿触发 优先级 0x01 次高
	tim_interrupt_init(PIT_TIM, 1, 0x00, 0x00);										// 初始化TIM为周期中断 周期1Hz 优先级 0x00 最高

	nvic_init(EXTI_KEY_INT, 0x00, 0x00, ENABLE);									// 修改 EXTI_KEY_INT 中断优先级为 0x00 最高
	nvic_init(PIT_TIM_INT, 0x00, 0x01, ENABLE);										// 修改 PIT_TIM_INT 中断优先级为 0x01 次高

	while(1)
	{
	}
}

void exti_interrupt_handler (void)													// 外部中断处理函数 在 EXTI02_IRQHandler 中调用
{
	uint8 io_state = 1;																// 用来读取 IO_KEY 的状态
	gpio_set(LED2, GPIO_LOW);														// 点亮 LED2 的LED
	while(io_state)																	// 判断 IO_KEY 是否按下
	{
		// 此时由于外部中断优先级比TIM周期定时器中断高
		// 就无法触发TIM周期中断
		// 故D7停止闪烁
		io_state = gpio_get(IO_KEY);												// 读取 IO_KEY 状态
	}
	gpio_set(LED2, GPIO_HIGH);														// 熄灭 LED2
}

void tim_interrupt_handler (void)													// TIM周期中断处理函数 在 TIM1_UP_IRQHandler 中调用
{
	static bool io_state = GPIO_LOW;												// LED1 的状态标志
	gpio_set(LED1, io_state);														// 更新 LED1 状态
	io_state = !io_state;															// 翻转 LED1 状态标志
}
// **************************** 代码区域 ****************************
