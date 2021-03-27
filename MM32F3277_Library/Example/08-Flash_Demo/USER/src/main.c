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
// 本例程初始化了逐飞科技 MM32F3277 核心板上的 UART1-A9/10 作为 debug 输出
// 
// 烧录本例程后 可见 UART1 输出的调试信息 每次将 flash 数据读出打印 然后加1后写入回去
// 
// 打开新的工程或者工程移动了位置务必执行以下操作
// 第一步 关闭上面所有打开的文件
// 第二步 project->clean  等待下方进度条走完
// 
// *************************** 例程说明 ***************************

// **************************** 宏定义 ****************************
#define SECTION_INDEX		FLASH_SECTION_127										// 最后一个扇区
#define PAGE_INDEX			FLASH_PAGE_3											// 最后一个页
#define DATA_SIZE			1024/sizeof(uint32)										// 32bit数据存储 缓冲就是1024/4大小
// **************************** 宏定义 ****************************

// **************************** 变量定义 ****************************
uint16 temp_data;
uint32 data_buffer[DATA_SIZE];
uint8 *data_point = (uint8 *)data_buffer;
// **************************** 变量定义 ****************************

// **************************** 代码区域 ****************************
int main(void)
{
	board_init(true);																// 初始化 debug 输出串口

	if(flash_check(SECTION_INDEX, PAGE_INDEX))										// 检查Flash是否有数据
	{
		flash_page_read(SECTION_INDEX, PAGE_INDEX, data_buffer, DATA_SIZE);			// 读出来已有的数据
		printf("\r\nFlash section%d page%d data:", SECTION_INDEX, PAGE_INDEX);		// 准备打印数据
		for(temp_data = 0; temp_data<1024; temp_data++)								// 8bit打印
		{
			if(temp_data % 8 == 0)													// 每8个数据换行
				printf("\r\n");
			printf("0x%x\t", *(data_point+temp_data));								// hex方式输出
			*(data_point+temp_data) = *(data_point+temp_data)+1;					// 缓冲区数据自增
		}
		flash_erase_page(SECTION_INDEX, PAGE_INDEX);								// 擦掉数据
		flash_page_program(SECTION_INDEX, PAGE_INDEX, data_buffer, DATA_SIZE);		// 把缓冲区的数据写回去
	}
	else
	{
		memset(data_buffer, 0x55, sizeof(data_buffer));								// 给缓冲区填充数据
		flash_erase_page(SECTION_INDEX, PAGE_INDEX);								// 擦除页
		flash_page_program(SECTION_INDEX, PAGE_INDEX, data_buffer, DATA_SIZE);		// 写入缓冲数据
		flash_page_read(SECTION_INDEX, PAGE_INDEX, data_buffer, DATA_SIZE);			// 读出来
		printf("\r\nFlash section%d page%d data:", SECTION_INDEX, PAGE_INDEX);		// 准备打印数据
		for(temp_data = 0; temp_data<1024; temp_data++)								// 8bit打印
		{
			if(temp_data % 8 == 0)													// 每8个数据换行
				printf("\r\n");
			printf("0x%o\t", *(data_point+temp_data));								// hex方式输出
		}
	}

	while(1)
	{
	}
}
// **************************** 代码区域 ****************************
