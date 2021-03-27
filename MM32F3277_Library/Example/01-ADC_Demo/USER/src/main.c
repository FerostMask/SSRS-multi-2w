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
// 调试下载需要准备逐飞科技 CMSIS-DAP 调试下载器 或 ARM 调试下载器 一个
// 
// 本例程初始化了 ADC 输入引脚 ADC1_TEST/ADC2_TEST/ADC3_TEST
// 以及片内 温度传感器 ADC1_CH14_TEMP 与片内电压基准 ADC1_CH15_VS
// 
// 烧录本例程后 如果使用的是逐飞科技的 CMSIS-DAP 调试下载器 或 ARM 调试下载器
// 可以直接在串口助手中打开对应串口
// 如果使用的并不是逐飞科技的 CMSIS-DAP 调试下载器 或 ARM 调试下载器
// 请接上 USB转TTL 或其他串口调试模块等 再打开串口调试助手
// 
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完
// 
// *************************** 例程说明 ***************************

// **************************** 宏定义 ****************************
#define ADC1_TEST				ADC1_CH08_B00
#define ADC2_TEST				ADC2_CH10_C00
#define ADC3_TEST				ADC3_CH11_C01
// **************************** 宏定义 ****************************

// **************************** 变量定义 ****************************
uint16 adc_value;
// **************************** 变量定义 ****************************

// **************************** 代码区域 ****************************
int main(void)
{
	board_init(true);																// 初始化 debug 输出串口

	//此处编写用户代码(例如：外设初始化代码等)
	adc_init(ADC_1, ADC1_TEST, ADC_12BIT);
	adc_init(ADC_2, ADC2_TEST, ADC_10BIT);
	adc_init(ADC_3, ADC3_TEST, ADC_8BIT);

	adc_init(ADC_1, ADC1_CH14_TEMP, ADC_12BIT);
	adc_init(ADC_1, ADC1_CH15_VS, ADC_12BIT);
	//此处编写用户代码(例如：外设初始化代码等)

	while(1)
	{
		//此处编写需要循环执行的代码
		printf("\r\n");																// printf重定向至串口1 从串口1输出信息

		adc_value = adc_mean_filter(ADC_1, ADC1_TEST, 10);							// 读取对应通道数值 采集10次取平均值
		printf("ADC1_TEST : %d.\r\n", adc_value);									// printf重定向至串口1 从串口1输出信息

		adc_value = adc_mean_filter(ADC_2, ADC2_TEST, 10);							// 读取对应通道数值 采集10次取平均值
		printf("ADC1_TEST : %d.\r\n", adc_value);									// printf重定向至串口1 从串口1输出信息

		adc_value = adc_mean_filter(ADC_3, ADC3_TEST, 10);							// 读取对应通道数值 采集10次取平均值
		printf("ADC1_TEST : %d.\r\n", adc_value);									// printf重定向至串口1 从串口1输出信息

		adc_value = adc_mean_filter(ADC_1, ADC1_CH14_TEMP, 10);						// 读取对应通道数值 采集10次取平均值
		printf("ADC1_CH14_TEMP : %d.\r\n", adc_value);								// printf重定向至串口1 从串口1输出信息

		adc_value = adc_mean_filter(ADC_1, ADC1_CH15_VS, 10);						// 读取对应通道数值 采集10次取平均值
		printf("ADC1_CH15_VS : %d.\r\n", adc_value);								// printf重定向至串口1 从串口1输出信息

		systick_delay_ms(1000);
		//此处编写需要循环执行的代码
	}
}
// **************************** 代码区域 ****************************
