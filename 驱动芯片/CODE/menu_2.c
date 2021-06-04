/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "data.h"
#include "menu.h"
#include "motor.h"
#include "menu_2.h"
#include "zf_pit.h"
#include "fontlib.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/
unsigned char menu2_limit = 0;
unsigned char fixedindex;//固定显示| 列索引
unsigned char menu2flag = 1;//次级菜单进入标志位
unsigned char menu2mode = 0;//菜单显示模式
//	修改倍数相关
unsigned char magflag = 1;
unsigned char magindex = 1;
float mag[] = {10, 1, 0.1, 0.01, 0.001};
//	数值修改相关
short *shortvalue0, *shortvalue1, *shortvalue2;
float *value0, *value1, *value2, *value3, *value4;

/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*------------------------------*/
/*		 二级菜单初始化模块		*/
/*==============================*/
void menu2_init(void){
//	初始化数值
	menu2flag = 1;
	magflag = 0;
	menu2_index = 0;
//	初始化模块
	switch(menu_index){
		case MENU_SWITCH:
			menu2flag = 3;//切换为开关
			switch(menu[menu_index]){
				case 0:
					menu2mode = 0;//显示模式
					menu2_limit = CSIMENU_FLAG-1;//索引限制
					break;
				case 1:
					menu2mode = 1;//显示模式
					menu2_limit = STATE_FLAG-1;//索引限制
					break;
			}
			break;
		case PARASET_PID1:
		//	关闭角度控制
			acw.rs = 0;
			steer.rs = 0;
			motor_act();
			magflag = 1;
			menu2_index = 1;
			tim_interrupt_disabnle(TIM_2);
			switch(menu[menu_index]){
				case 0://速度
					value0 = &speed.Kp;
					value1 = &speed.Kd;
					menu2_limit = 2;
					menu2mode = 1;
					break;
				case 1://角度
					value0 = &angle.Kp;
					value1 = &angle.Kd;
					menu2_limit = 2;
					menu2mode = 1;
					break;
				case 2://角速度
					value0 = &acw.alpha;
					value1 = &acw.Kp;
					value2 = &acw.Ki;
					value3 = &acw.Kd;
					menu2_limit = 4;
					menu2mode = 0;
					break;
			}
			break;
		case PARASET_PID2:
		//	关闭角度控制
			acw.rs = 0;
			steer.rs = 0;
			motor_act();
			magflag = 1;
			menu2_index = 1;
			tim_interrupt_disabnle(TIM_2);
			switch(menu[menu_index]){
				case 0://转向
					value0 = &steer.Kp;
					value1 = &steer.Kd;
					menu2_limit = 2;
					menu2mode = 1;
					break;
				case 1://左差速
					value0 = &lefdif.alpha;
					value1 = &lefdif.Kp;
					value2 = &lefdif.Ki;
					value3 = &lefdif.Kd;
					menu2_limit = 4;
					menu2mode = 0;
					break;
				case 2://右差速
					value0 = &rigdif.alpha;
					value1 = &rigdif.Kp;
					value2 = &rigdif.Ki;
					value3 = &rigdif.Kd;
					menu2_limit = 4;
					menu2mode = 0;
					break;
			}
			break;
		case PARASET_OPER://姿态
			acw.rs = 0;
			steer.rs = 0;
			motor_act();
			magflag = 1;
			tim_interrupt_disabnle(TIM_2);
			switch(menu[menu_index]){
				case 0:
					shortvalue0 = &spd;
					shortvalue1 = &rad;
					shortvalue2 = &blcp;
					menu2_limit = 3;
					menu2mode = 0;
					menu2_index = 1;
					break;
			}
			break;
		case MONITOR_MENU://监视器
		//	开启中断显示
			tim_interrupt_init_ms(TIM_6, 40, 1, 3);
			menu2flag = 2;
			monitorflag = 1;
			break;
	}
}
/*------------------------------*/
/*		   信息存放模块			*/
/*==============================*/
static char info(unsigned char index, unsigned char num){
//	变量定义
	register unsigned char i;
	switch(index){
		case MENU_SWITCH:
			switch(num){
				case 0://参数保存
					for(i = 0; i < 32; i++) nom[i] = can0[i];
					for(i = 0; i < 32; i++) nom[32+i] = shu0[i];
					for(i = 0; i < 32; i++) nom[64+i] = bao0[i];
					for(i = 0; i < 32; i++) nom[96+i] = cun0[i];
					return 4;
				case 1://参数还原
					for(i = 0; i < 32; i++) nom[i] = can0[i];
					for(i = 0; i < 32; i++) nom[32+i] = shu0[i];
					for(i = 0; i < 32; i++) nom[64+i] = huan0[i];
					for(i = 0; i < 32; i++) nom[96+i] = yuan0[i];
					return 4;
				case 10://开关
					for(i = 0; i < 32; i++) nom[i] = kai0[i];
					for(i = 0; i < 32; i++) nom[32+i] = guan0[i];
					return 2;
				case 11://关转速
					for(i = 0; i < 32; i++) nom[i] = guan0[i];
					for(i = 0; i < 32; i++) nom[32+i] = zhuan0[i];
					for(i = 0; i < 32; i++) nom[64+i] = su0[i];
					return 3;
				case 12://关转向
					for(i = 0; i < 32; i++) nom[i] = guan0[i];
					for(i = 0; i < 32; i++) nom[32+i] = zhuan0[i];
					for(i = 0; i < 32; i++) nom[64+i] = xiang0[i];
					return 3;
			}
		case PARASET_OPER:
			switch(num){
				case 0://转速
					for(i = 0; i < 32; i++) nom[i] = zhuan0[i];
					for(i = 0; i < 32; i++) nom[32+i] = su0[i];
					return 2;
				case 1://转向角
					for(i = 0; i < 32; i++) nom[i] = zhuan0[i];
					for(i = 0; i < 32; i++) nom[32+i] = xiang0[i];
					for(i = 0; i < 32; i++) nom[64+i] = jiao0[i];
					return 3;
				case 2://平衡点
					for(i = 0; i < 32; i++) nom[i] = ping0[i];
					for(i = 0; i < 32; i++) nom[32+i] = heng0[i];
					for(i = 0; i < 32; i++) nom[64+i] = dian1[i];
					return 3;
			}
		case MONITOR_MENU:
			switch(num){
				case 0://俯仰角
					for(i = 0; i < 32; i++) nom[i] = fu0[i];
					for(i = 0; i < 32; i++) nom[32+i] = yang0[i];
					for(i = 0; i < 32; i++) nom[64+i] = jiao0[i];
					return 3;
				case 1://航向角
					for(i = 0; i < 32; i++) nom[i] = hang0[i];
					for(i = 0; i < 32; i++) nom[32+i] = xiang0[i];
					for(i = 0; i < 32; i++) nom[64+i] = jiao0[i];
					return 3;
				case 2://左轮转速
					for(i = 0; i < 32; i++) nom[i] = zuo0[i];
					for(i = 0; i < 32; i++) nom[32+i] = lun0[i];
					for(i = 0; i < 32; i++) nom[64+i] = zhuan0[i];
					for(i = 0; i < 32; i++) nom[96+i] = su0[i];
					return 4;
				case 3://右轮转速
					for(i = 0; i < 32; i++) nom[i] = you0[i];
					for(i = 0; i < 32; i++) nom[32+i] = lun0[i];
					for(i = 0; i < 32; i++) nom[64+i] = zhuan0[i];
					for(i = 0; i < 32; i++) nom[96+i] = su0[i];
					return 4;
			}
		case 100:
			switch(menu_index){
				case 0:
					switch(num){
						case 0://开
							for(i = 0; i < 32; i++) nom[i] = kai0[i];
							return 1;
						case 1://关
							for(i = 0; i < 32; i++) nom[i] = guan0[i];
							return 1;
						case 2:
							for(i = 0; i < 32; i++) nom[i] = state1[i];
							return 1;
							break;
						case 3:
							for(i = 0; i < 32; i++) nom[i] = state0[i];
							return 1;
						case 4://功能
							for(i = 0; i < 32; i++) nom[i] = gong0[i];
							for(i = 0; i < 32; i++) nom[32+i] = neng0[i];
							return 2;
						case 5://状态
							for(i = 0; i < 32; i++) nom[i] = zhuang0[i];
							for(i = 0; i < 32; i++) nom[32+i] = tai0[i];
							return 2;
					}
			}
	}
	return 0;
}
/*------------------------------*/
/*		   基础信息存放			*/
/*==============================*/
static info_found(unsigned char index, unsigned char num){
//	变量定义
	register unsigned char i;
	switch(index){
		case 1:
			switch(num){
				case 0://参数名
					for(i = 0; i < 32; i++) nom[i] = can0[i];
					for(i = 0; i < 32; i++) nom[32+i] = shu0[i];
					for(i = 0; i < 32; i++) nom[64+i] = ming0[i];
					return 3;
				case 1://参数值
					for(i = 0; i < 32; i++) nom[i] = can0[i];
					for(i = 0; i < 32; i++) nom[32+i] = shu0[i];
					for(i = 0; i < 32; i++) nom[64+i] = zhi1[i];
					return 3;
				case 2://参数保存
					for(i = 0; i < 32; i++) nom[i] = can0[i];
					for(i = 0; i < 32; i++) nom[32+i] = shu0[i];
					for(i = 0; i < 32; i++) nom[64+i] = bao0[i];
					for(i = 0; i < 32; i++) nom[96+i] = cun0[i];
					return 4;
				case 3://已保存
					for(i = 0; i < 32; i++) nom[i] = yi0[i];
					for(i = 0; i < 32; i++) nom[32+i] = bao0[i];
					for(i = 0; i < 32; i++) nom[64+i] = cun0[i];
					return 3;
			}
	}
	return 0;
}
/*------------------------------*/
/*		 数值显示辅助模块		*/
/*==============================*/
static void menu2value_sup(void){
	switch(menu_index){
		case MENU_SWITCH:
			swdisplay();
			break;
		case PARASET_PID1:
		case PARASET_PID2:
			switch(menu2mode){
				case 0:
					ips200_display_chinese(176, 192, 16, nom, info_found(1, 2), 0XFFFF);
					ips200_showfloat(120, 15, *value0, 3, 3);
					ips200_showfloat(120, 16, *value1, 3, 3);
					ips200_showfloat(120, 17, *value2, 3, 3);
					ips200_showfloat(120, 18, *value3, 3, 3);
					break;
				case 1:
					ips200_display_chinese(176, 192, 16, nom, info_found(1, 2), 0XFFFF);
					ips200_showfloat(120, 15, *value0, 2, 3);
					ips200_showfloat(120, 16, *value1, 2, 3);
					break;
			}
			break;
		case PARASET_OPER:
			switch(menu2mode){
				case 0:
					ips200_display_chinese(176, 192, 16, nom, info_found(1, 2), 0XFFFF);
					ips200_showint16(120, 15, *shortvalue0);
					ips200_showint16(120, 16, *shortvalue1);
					ips200_showint16(120, 17, *shortvalue2);
					break;
			}
	}
}
/*------------------------------*/
/*		 菜单高亮显示模块		*/
/*==============================*/
void menu2value_hl(void){
	switch(menu_index){
		case PARASET_PID1:
		case PARASET_PID2:
			switch(menu2_index){
				case 0:ips200_display_chinese(176, 192, 16, nom, info_found(1, 2), 0xAE9C);break;
				case 1:ips200_showfloat(120, 15, *value0, 3, 3);break;
				case 2:ips200_showfloat(120, 16, *value1, 3, 3);break;
				case 3:ips200_showfloat(120, 17, *value2, 3, 3);break;
				case 4:ips200_showfloat(120, 18, *value3, 3, 3);break;
			}
			break;
		case PARASET_OPER:
			switch(menu2_index){
				case 0:ips200_display_chinese(176, 192, 16, nom, info_found(1, 2), 0xAE9C);break;
				case 1:ips200_showint16(120, 15, *shortvalue0);break;
				case 2:ips200_showint16(120, 16, *shortvalue1);break;
				case 3:ips200_showint16(120, 17, *shortvalue2);break;
			}
			break;
	}
}
/*------------------------------*/
/*		   数值显示模块			*/
/*==============================*/
static void menu2value(void){
//	显示级别
	if(magflag) ips200_showfloat(180, 14, mag[magindex], 2, 3);
//	显示数值
		menu2value_sup();
//	高亮数值
	if(!menu2_level){
	//	选择
		ips200_pencolor = 0xFFFF;
		ips200_bgcolor = 0xFDF8;
		menu2value_hl();
		ips200_pencolor = 0xB6DB;
		ips200_bgcolor = 0xFFFF;
	}
	else{
	//	修改
		ips200_pencolor = 0xFFFF;
		ips200_bgcolor = 0xAE9C;
		menu2value_hl();
		ips200_pencolor = 0xB6DB;
		ips200_bgcolor = 0xFFFF;
	}
}
/*------------------------------*/
/*		   名称显示模块			*/
/*==============================*/
void menu2_display(void){
//	清屏
	ips200_clear(WHITE);
//	显示名称
	switch(menu_index){
	//	开关
		case MENU_SWITCH:
			switch(menu2mode){
				case 0:
					ips200_display_chinese(0, 208, 16, nom, info(100, 4), 0XFDF8);
					ips200_display_chinese(120, 208, 16, nom, info(100, 5), 0XFDF8);
					ips200_display_chinese(90, 224, 16, nom, info(100, 0), 0XFDF8);
					ips200_display_chinese(170, 224, 16, nom, info(100, 1), 0XFDF8);
					ips200_display_chinese(0, 240, 16, nom, info(menu_index, 0), 0xB6DB);
					ips200_display_chinese(0, 256, 16, nom, info(menu_index, 1), 0xB6DB);
					break;
				case 1:
					ips200_display_chinese(0, 208, 16, nom, info(100, 4), 0XFDF8);
					ips200_display_chinese(120, 208, 16, nom, info(100, 5), 0XFDF8);
					ips200_display_chinese(90, 224, 16, nom, info(100, 0), 0XFDF8);
					ips200_display_chinese(170, 224, 16, nom, info(100, 1), 0XFDF8);
					ips200_display_chinese(0, 240, 16, nom, info(menu_index, 10), 0xB6DB);
					ips200_display_chinese(0, 256, 16, nom, info(menu_index, 11), 0xB6DB);
					ips200_display_chinese(0, 272, 16, nom, info(menu_index, 12), 0xB6DB);
					break;
			}
			break;
	//	PID
		case PARASET_PID1:
		case PARASET_PID2:
			switch(menu2mode){
			//	面板选择
				case 0:
					ips200_display_chinese(0, 208, 16, nom, info_found(1, 0), 0XFDF8);
					ips200_display_chinese(120, 208, 16, nom, info_found(1, 1), 0XFDF8);
					ips200_showstr(0, 15, "alpha");
					ips200_showstr(0, 16, "Kp");
					ips200_showstr(0, 17, "Ki");
					ips200_showstr(0, 18, "Kd");
					break;
				case 1:
					ips200_display_chinese(80, 192, 16, nom, info(100, 4), 0XFFFF);
					ips200_display_chinese(0, 208, 16, nom, info_found(1, 0), 0XFDF8);
					ips200_display_chinese(120, 208, 16, nom, info_found(1, 1), 0XFDF8);
					ips200_showstr(0, 15, "Kp");
					ips200_showstr(0, 16, "Kd");
					break;
			}
			break;
		case PARASET_OPER:
			switch(menu2mode){
				case 0:
					ips200_display_chinese(0, 208, 16, nom, info(1, 0), 0XFDF8);
					ips200_display_chinese(120, 208, 16, nom, info(1, 1), 0XFDF8);
					ips200_display_chinese(0, 240, 16, nom, info(menu_index, 0), 0xB6DB);
					ips200_display_chinese(0, 256, 16, nom, info(menu_index, 1), 0xB6DB);
					ips200_display_chinese(0, 272, 16, nom, info(menu_index, 2), 0xB6DB);
					break;
			}
			break;
		case MONITOR_MENU:
			switch(menu2mode){
				case 0:
					ips200_display_chinese(0, 208, 16, nom, info(1, 0), 0XFDF8);
					ips200_display_chinese(120, 208, 16, nom, info(1, 1), 0XFDF8);
					ips200_display_chinese(0, 240, 16, nom, info(menu_index, 0), 0xB6DB);
					ips200_display_chinese(0, 256, 16, nom, info(menu_index, 1), 0xB6DB);
					ips200_display_chinese(0, 272, 16, nom, info(menu_index, 2), 0xB6DB);
					ips200_display_chinese(0, 288, 16, nom, info(menu_index, 3), 0xB6DB);
					break;
			}
			break;
	}
//	显示数值
	menu2value();
}
/*------------------------------*/
/*		   数值监视模块			*/
/*==============================*/
void monitor(void){
	switch(menu[menu_index]){
		case 0:
			ips200_showint16(120, 15, pita);
			ips200_showint16(120, 16, gz);
			ips200_showint16(120, 17, lcod);
			ips200_showint16(120, 18, rcod);
			break;
	}
}
/*------------------------------*/
/*		   固定监视模块			*/
/*==============================*/
void fixed_monitor(void){
	switch(fixedindex){
		case 0:
		//	名称显示
			ips200_display_chinese(0, 0, 16, nom, info(menu_index, 0), 0XFDF8);
			ips200_display_chinese(0, 16, 16, nom, info(menu_index, 1), 0XFDF8);
			ips200_display_chinese(0, 32, 16, nom, info(menu_index, 2), 0XFDF8);
			ips200_display_chinese(0, 48, 16, nom, info(menu_index, 3), 0XFDF8);
		//	数值显示
			ips200_showint16(120, 0, pita);
			ips200_showint16(120, 1, gz);
			ips200_showint16(120, 2, lcod);
			ips200_showint16(120, 3, rcod);
			break;
	}
}
/*------------------------------*/
/*		   按钮状态模块			*/
/*==============================*/
void swdisplay(void){
//	变量定义
	register unsigned char i;
	switch(menu[menu_index]){
	//	按钮状态
		case 0:
			for(i=0; i<CSIMENU_FLAG; i++){
				if(csimenu_flag[i]){
					ips200_display_chinese(90, 240+16*i, 16, nom, info(100, 2), 0xB6DB);
					ips200_display_chinese(170, 240+16*i, 16, nom, info(100, 3), 0xB6DB);
				}
				else{
					ips200_display_chinese(90, 240+16*i, 16, nom, info(100, 3), 0xB6DB);
					ips200_display_chinese(170, 240+16*i, 16, nom, info(100, 2), 0xB6DB);
				}
			}
			//	高亮选项
			if(csimenu_flag[menu2_index]) ips200_display_chinese(90, 240+16*menu2_index, 16, nom, info(100, 2), 0XB7BD);
			else ips200_display_chinese(170, 240+16*menu2_index, 16, nom, info(100, 2), 0XF5BA);
			break;
		case 1:
			for(i=0; i<STATE_FLAG; i++){
				if(state_flag[i]){
					ips200_display_chinese(90, 240+16*i, 16, nom, info(100, 2), 0xB6DB);
					ips200_display_chinese(170, 240+16*i, 16, nom, info(100, 3), 0xB6DB);
				}
				else{
					ips200_display_chinese(90, 240+16*i, 16, nom, info(100, 3), 0xB6DB);
					ips200_display_chinese(170, 240+16*i, 16, nom, info(100, 2), 0xB6DB);
				}
			}
			//	高亮选项
			if(state_flag[menu2_index]) ips200_display_chinese(90, 240+16*menu2_index, 16, nom, info(100, 2), 0XB7BD);
			else ips200_display_chinese(170, 240+16*menu2_index, 16, nom, info(100, 2), 0XF5BA);
			break;
	}
}
/*------------------------------*/
/*		   按钮切换模块			*/
/*==============================*/
static void swmode(void){
//	变量定义
	unsigned char temp, i;
//	开关操作
	switch(menu[menu_index]){
		case 0:
			fixedflag = 0;
			temp = csimenu_flag[menu2_index];
			for(i=0; i<CSIMENU_FLAG; i++) csimenu_flag[i] = 0;
			csimenu_flag[menu2_index] = !temp;
		//	执行按键功能	
			switch(menu2_index){
				case 0:first_flash_init();break;
				case 1:Init_para();break;
			}
			break;
		case 1:
			temp = state_flag[menu2_index];
			state_flag[menu2_index] = !temp;
			break;
	}
}
/*------------------------------*/
/*		   数值修改模块			*/
/*==============================*/
static void modify(unsigned char index, unsigned char event, unsigned char mode){
	switch(mode){
		case PARASET_PID1:
		case PARASET_PID2:
			if(event){
		//	数值增加
				switch(index){
					case 1:*value0+=mag[magindex];break;
					case 2:*value1+=mag[magindex];break;
					case 3:*value2+=mag[magindex];break;
					case 4:*value3+=mag[magindex];break;
					case 5:*value4+=mag[magindex];break;
				}
			}
		//	数值减少
			else{
				switch(index){
					case 1:*value0-=mag[magindex];break;
					case 2:*value1-=mag[magindex];break;
					case 3:*value2-=mag[magindex];break;
					case 4:*value3-=mag[magindex];break;
					case 5:*value4-=mag[magindex];break;
				}
			}
			break;
		case PARASET_OPER:
			if(event){
				switch(index){
					case 1: *shortvalue0+=mag[magindex];break;
					case 2: *shortvalue1+=mag[magindex];break;
					case 3: *shortvalue2+=mag[magindex];break;
				}
			}
			else{
				switch(index){
					case 1: *shortvalue0-=mag[magindex];break;
					case 2: *shortvalue1-=mag[magindex];break;
					case 3: *shortvalue2-=mag[magindex];break;
				}
			}
	}
}
/*------------------------------*/
/*		 二级菜单选择模块		*/
/*==============================*/
void menu2_select(unsigned char event){
//	变量定义
	register unsigned char i;
//	返回键
	if(event == 3){
	//	重置
		menu2_level = 0;
		magindex = 1;
		monitorflag = 0;
		menu_level = 0;
		menu_display();
	//	操作定时器
		if(!fixedflag) tim_interrupt_disabnle(TIM_6);
		tim_interrupt_init_ms(TIM_2, 2, 0, 0);
		return;
	}
	if(!menu2_level){
		switch(event){
			case 6://右按键
				break;
			
			case 4://左按键
				break;
			
			case 2://上按键
				if(menu2_index > 0) menu2_index--;
				break;
			
			case 5://下按键
				if(menu2_index < menu2_limit) menu2_index++;
				break;
			
			case 1://确定键
				switch(menu2flag){
				//	参数修改
					case 1:
						if(!menu2_index){
							flash_memory_write(menu_index, menu[menu_index]);
							ips200_display_chinese(109, 192, 16, nom, info_found(1, 3), 0xAE9C);
						}
						else
							menu2_level = 1;
						break;
				//	监视器固定显示
					case 2:
						fixedflag = !fixedflag;
						fixedindex = menu[menu_index];
						if(fixedflag) for(i=0; i<CSIMENU_FLAG; i++) csimenu_flag[i] = 0;
						break;//切换固定显示
				//	开关
					case 3:
						swmode();
						swdisplay();
						break;
					case 0:break;
				}
				break;
		}
		menu2value();
	}
	else{
		switch(event){
			case 6://右按键
				if(magindex < 4) magindex++;
				break;
			
			case 4://左按键
				if(magindex > 0) magindex--; 
				break;
			
			case 2://上按键
				modify(menu2_index, 1, menu_index);
				break;
			
			case 5://下按键
				modify(menu2_index, 0, menu_index);
				break;
			
			case 1://确定键
				menu2_level = 0;
				break;
		}
		menu2value();
	}
}