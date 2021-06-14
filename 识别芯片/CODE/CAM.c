/*--------------------------------------------------------------*/
/*							头文件加载							*/
/*==============================================================*/
#include "CAM.h"
#include "pid.h"
#include "data.h"
#include "zf_tim.h"
#include "eident.h"
#include "SEEKFREE_MT9V03X.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/* 							  宏定义 							*/
/*==============================================================*/
#define uint16 unsigned short
/*--------------------------------------------------------------*/
/* 							 变量定义 							*/
/*==============================================================*/
float show_flvalue[5];
short show_value[5];
short traf_slope[4];
short ave_slope[4];
short line_slope_diff, line_slope_ave;
unsigned char show_point;
unsigned char ac_flag[4];
unsigned char exti_leftop, exti_rigtop;
unsigned char lefhigh, righigh;
short lef_widrate, lef_toprate, lef_botrate, rig_widrate, rig_toprate, rig_botrate;//左右宽度变化
/*--------------------------------------------------------------*/
/* 							 函数定义 							*/
/*==============================================================*/
/*------------------------------*/
/*		   图像显示模块 		*/
/*==============================*/
void binary_disp(void){
//	变量定义
	register unsigned char i, j, k;
	unsigned char column = (MT9V03X_W-4)>>3;
	unsigned char binary_temp;
//	图像显示
	ips200_address_set(0,0,MT9V03X_W-5,MT9V03X_H-1);
	for(i = 0; i < MT9V03X_H; i++){
		for(j = 0; j < column; j++){
			for(k = 8; k > 0; k--){
				binary_temp = (binary_img[i][j]>>(k-1)) & 0x01;
				if(binary_temp) ips200_wr_data16(WHITE);
				else ips200_wr_data16(img_color);
			}
		}
	}
//	显示边界
	for(i = MT9V03X_H - 1; i > lcut; i--) ips200_drawpoint(lefbor[i], i, 0x00);
	for(i = MT9V03X_H - 1; i > rcut; i--) ips200_drawpoint(rigbor[i], i, 0x00);
//	显示出口
	for(i = 0; i < exti_lefcount; i++){
		ips200_drawpoint(0, exti_lefp[i], 0xB20E);
		ips200_drawpoint(1, exti_lefp[i], 0xB20E);
		ips200_drawpoint(2, exti_lefp[i], 0xB20E);
	}
	for(i = 0; i < exti_rigcount; i++){
		ips200_drawpoint(157, exti_rigp[i], 0xB20E);
		ips200_drawpoint(158, exti_rigp[i], 0xB20E);
		ips200_drawpoint(159, exti_rigp[i], 0xB20E);
	}
//	显示垂直边线
	for(i = 0; i < lefbottom_cut; i++)
		ips200_drawpoint(i, bottombor[i], 0xFD10);
	for(i = 0; i < leftop_cut; i++)
		ips200_drawpoint(i,topbor[i], 0xFD10);
	for(i = 159; i > rigbottom_cut; i--)
		ips200_drawpoint(i, bottombor[i], 0xFD10);
	for(i = 159; i > rigtop_cut; i--)
		ips200_drawpoint(i, topbor[i], 0xFD10);
//	显示岔道边线
	for(i = cut_fork_bottom_col; i < cut_fork_rig; i++)
		ips200_drawpoint(i, border_top[i], 0xB20E);
	for(i = cut_fork_lef; i < cut_fork_bottom_col; i++)
		ips200_drawpoint(i, border_top[i], 0xED2A);
	for(i = 0; i < 89; i++)
		ips200_drawpoint(cut_fork_bottom_col, i, 0xA759);
	for(i = 0; i < 159; i++)
		ips200_drawpoint(i, bottom_point_row, 0xA759);
//	显示拐点
//	for(i = 0; i < infle_lefcount; i++){
//		ips200_drawpoint(lefbor[infle_lefp[i]], infle_lefp[i], RED);
//		ips200_drawpoint(lefbor[infle_lefp[i]]+1, infle_lefp[i], RED);
//		ips200_drawpoint(lefbor[infle_lefp[i]]+2, infle_lefp[i], RED);
//	}
//	for(i = 0; i < infle_rigcount; i++){
//		ips200_drawpoint(rigbor[infle_rigp[i]], infle_rigp[i], RED);
//		ips200_drawpoint(rigbor[infle_rigp[i]]-1, infle_rigp[i], RED);
//		ips200_drawpoint(rigbor[infle_rigp[i]]-2, infle_rigp[i], RED);
//	}
//	显示状态
	ips200_showstr(160, 0, "state");
	ips200_showint16(160, 1, state);
	ips200_showstr(160, 2, "act_flag");
	ips200_showint16(160, 3, act_flag);
//	显示目标点
	ips200_drawpoint(p_target[1]+2, p_target[0], 0xED2A);
	ips200_drawpoint(p_target[1]-2, p_target[0], 0xED2A);
	ips200_drawpoint(p_target[1], p_target[0], 0xED2A);
	ips200_drawpoint(p_target[1], p_target[0]+2, 0xED2A);
	ips200_drawpoint(p_target[1], p_target[0]-2, 0xED2A);
//	显示值
	ips200_showstr(170, 4, "show_value");
	ips200_showint16(170, 5, show_value[0]);
	ips200_showint16(170, 6, show_value[1]);
	ips200_showint16(170, 7, show_value[2]);
	ips200_showint16(170, 8, show_value[3]);
	ips200_showint16(170, 9, show_value[4]);
//	显示值 | 浮点型
//	ips200_showstr(0, 12, "show_flvalue");	
//	ips200_showfloat(0, 13, show_flvalue[0], 2, 2);
//	ips200_showfloat(150, 13, show_flvalue[1], 2, 2);
//	ips200_showfloat(0, 14, show_flvalue[2], 2, 2);
//	ips200_showfloat(150, 14, show_flvalue[3], 2, 2);
//	ips200_showfloat(0, 15, show_flvalue[4], 2, 2);
	
//	ips200_drawpoint(0, show_point+1, RED);
//	ips200_drawpoint(0, show_point+2, RED);
//	ips200_drawpoint(0, show_point+1, RED);
//	ips200_drawpoint(0, show_point+2, RED);
}
/*------------------------------*/
/*	    	状态机模块			*/
/*==============================*/
void state_machine(void){
//	初始化
	state_temp = state, state = 0;
	infle_lefcount = 0, infle_rigcount = 0;
	show_value[0] = total_count_fork;
	show_value[1] = direction_fork;
	switch(act_flag){
	//	出环检测
		case 23://环内 -> 出环前
			if(exti_rigcount > 0 && yawa < -20) {state = 23; return;}
			break;
		case 24://出环前 -> 出环后
			slope_cal(1);
			if(abs(line_slope_diff) < 140)
				if(line_slope_ave < 1600 && line_slope_ave > 330)
					if(bottom_point_row > 9 && bottom_point_row < 40)
						{state = 24; return;}
//			show_value[0] = line_slope_diff, show_value[1] = line_slope_ave, show_value[2] = bottom_point_row;
			break;
		case 28:
			if(exti_lefcount > 0 && yawa > 20) {state = 28; return;}
			break;
		case 29:
			slope_cal(2);
			if(abs(line_slope_diff) < 140)
				if(line_slope_ave < 1600 && line_slope_ave > 330)
					if(bottom_point_row > 9 && bottom_point_row < 40)
						{state = 29; return;}
//			show_value[0] = line_slope_diff, show_value[1] = line_slope_ave, show_value[2] = bottom_point_row;
			break;
	//	出十字检测
		case 31:
			if(found_point[0] < 60 && found_point[2] < 60) {state = 32; return;}
			break;
	//	出岔道检测
		case 41:
			if(direction_fork){//右
				if(cut_fork_bottom_col < 18 || yawa > 25){
					act_flag = 0, state_flag = 0, img_color = 0xAE9C;
					yawa_flag = 0;
					return;
				}
			}
			else{//左
				if(cut_fork_bottom_col > 141 || yawa < -25){
					act_flag = 0, state_flag = 0, img_color = 0xAE9C;
					yawa_flag = 0;
					return;
				}
			}
			break;
	//	出库检测
		case 56://左
			if(yawa < -35){
				act_flag = 0, state_flag = 0, yawa_flag = 0, img_color = 0xAE9C;
				run_flag[0] = 0;
				return;
			}
			break;
		case 55://右
			if(yawa > 35){
				act_flag = 0, state_flag = 0, yawa_flag = 0, img_color = 0xAE9C;
				run_flag[1] = 0;
				return;
			}
			break;
	}
/*------------------------------*/
/*	       检测赛道类型			*/
/*==============================*/
//	两边都有出口 | 十字
	if(exti_lefcount)
		if(exti_rigcount){
//			if(lef_widrate < 20 || rig_widrate < 20)
//				if(abs(exti_lefp[0] - exti_rigp[0]) < 10)
//					{state = 31;return;}
		}
//	岔道检测
	vetsearch_fork_support();
	if(cut_fork_rig) vertsearch_frok();
	if(state == 41) return;
//	没有出口 | 直道 | 弯道丢边
	if(!exti_lefcount)
		if(!exti_rigcount){
		//	拐点检测
//			inflexion_search();
		//	弯道检测
			if(abs(found_point[0]-rcut)<5)
				if(abs(found_point[0] - found_point[2])>45) {state = 11;return;}
			if(abs(found_point[2]-lcut)<5)
				if(abs(found_point[0] - found_point[2])>45) {state = 12;return;}
		}
//	只有左边有出口 | 左弯 | 左环 | 十字丢边
	if(exti_lefcount)
		if(!exti_rigcount){
		//	没有直道延伸
			if(abs(ltraf_point_row[exti_leftop] - rcut) < 5)
				{state = 13;return;}//左弯
		//	有直道延伸
			if(lefhigh > 4)//9
				if(!cooling_flag)
					if(lefhigh < 23){//环道判断
						if(found_point[2] > exti_lefp[0]+10)
							slope_cal(3);
							if(abs(line_slope_diff) < 120){//判断右边是直线
//								show_value[0] = lef_widrate;
//								show_value[1] = lef_toprate;
//								show_value[2] = lef_botrate;
//								show_value[3] = pita;
								if(lef_botrate < -100 && lef_toprate < 70)
									if(lef_widrate > 46 && leftop_cut > 33)
										{state = 22;return;}
							//	未检测到入环口，判断是否为出环口
								if(leftop_cut > 33)
									if(topbor[0] - topbor[leftop_cut] > 1)
										if(count_fork < 10)
											{state = 21; return;}
							}
					}
	}
	if(exti_rigcount)
		if(!exti_lefcount){//只有右边有出口 | 右弯 | 右环 | 十字丢边 | 环道出口
			if(abs(rtraf_point_row[exti_rigtop] - lcut) < 5)//右弯
				{state = 14; return;}
		//	有直道延伸
			if(righigh > 4)//9
				if(!cooling_flag)
					if(righigh < 23){//环道判断
						if(found_point[0] > exti_rigp[0]+10)
							slope_cal(4);
							if(abs(line_slope_diff) < 120){//判断右边是直线
//								show_value[0] = rigtop_cut;
//								show_value[1] = rig_toprate;
//								show_value[2] = rig_botrate;
								if(rig_botrate < -100 && rig_toprate < 70)
									if(rig_widrate > 46 && rigtop_cut < 127)
										{state = 27;return;}
							//	未检测到入环口，判断是否为出环口
								if(rigtop_cut < 127)
									if(topbor[159] - topbor[rigtop_cut] > 1)
										if(count_fork < 10)
											{state = 26; return;}
							}
					}
		}
}
/*------------------------------*/
/*	    	终点状态机			*/
/*==============================*/
void state_machine_final(void){
	switch(act_flag){
		case 51:
			if(state == 52)
				act_flag = 52, state_flag = 0, img_color = 0xEFBE;
			return;
	}
}
/*------------------------------*/
/*	    	岔道状态机			*/
/*==============================*/
void state_machine_fork(void){
	switch(act_flag){
		case 41:

			break;
	}
}
/*------------------------------*/
/*	    	十字状态机			*/
/*==============================*/
void state_machine_cross(void){
	switch(act_flag){
		case 31:
			if(state == 32)
				act_flag = 0, state_flag = 0, img_color = 0xAE9C;
			return;
	}
}
/*------------------------------*/
/*	    	环道状态机			*/
/*==============================*/
void state_machine_ring(void){
	switch(act_flag){
	//	左环
		case 21://出环口 -> 入环
			if(state == 22)
				act_flag = 22, img_color = 0x8CF6;
			return;
		case 22://入环 -> 环内
			if(state == 11 || state == 13)
				if(found_point[2] > 60)
					act_flag = 23, yawa_flag = 1, yawa = 0, img_color = 0x46D0;
			return;
		case 23://环内 -> 出环
			if(state == 23)
				act_flag = 24, yawa = 0, img_color = 0xB6DB;
			return;
		case 24://出环 -> 环外
			if(state == 24)
				act_flag = 0, yawa_flag = 0, state_flag = 0, img_color = 0xAE9C;
				cooling_flag = 1, ring_out_flag = 1;
				tim_interrupt_init_ms(TIM_3, 1000, 0, 0);
			return;
	//	右环
		case 26://出环口 -> 入环
			if(state == 27)
				act_flag = 27, img_color = 0x8CF6;
			return;
		case 27://入环 -> 环内
			if(state == 12 || state == 14)
				if(found_point[0] > 60)
					act_flag = 28, yawa_flag = 1, yawa = 0, img_color = 0x46D0;
			return;
		case 28://环内 -> 出环
			if(state == 28)
				act_flag = 29, yawa = 0, img_color = 0xB6DB;
			return;
		case 29://出环 -> 环外
			if(state == 29)
				act_flag = 0, yawa_flag = 0, state_flag = 0, img_color = 0xAE9C;
				cooling_flag = 1, ring_out_flag = 2;
				tim_interrupt_init_ms(TIM_3, 1000, 0, 0);
			return;
	}
}
/*-
/*------------------------------*/
/*	    	弯道状态机			*/
/*==============================*/
void state_machine_bend(void){
	switch(act_flag){
		case 11:
			if(state==13)//丢边转换
				{act_flag = 13, img_color = 0x7EFE;return;}
			if(state!=11)
				act_flag = 0, state_flag = 0, img_color = 0xAE9C;
			return;
		case 12:
			if(state==14)
				{act_flag = 14, img_color = 0x7EFE;return;}
			if(state!=12)
				act_flag = 0, state_flag = 0, img_color = 0xAE9C;
			return;
		case 13:
			if(state==13)
				{act_flag = 11, img_color = 0x6DDD;return;}
			if(state!=13)
				act_flag = 0, state_flag = 0, img_color = 0xAE9C;
			return;
		case 14:
			if(state==12)
				{act_flag = 12, img_color = 0x6DDD;return;}
			if(state!=14)
				act_flag = 0, state_flag = 0, img_color = 0xAE9C;
			return;
	}
}
/*------------------------------*/
/*	    	状态机入口			*/
/*==============================*/
void state_machine_enter(void){
	switch(state){
	//	弯道、弯道丢边
		case 11:
			act_flag = 11, state_flag = 1, img_color = 0x6DDD;
			return;
		case 12:
			act_flag = 12, state_flag = 1, img_color = 0x6DDD;
			return;
		case 13:
			act_flag = 13, state_flag = 1, img_color = 0x7EFE;
			return;
		case 14:
			act_flag = 14, state_flag = 1, img_color = 0x7EFE;
			return;
	//	圆环
		case 21://检测到圆环出口 | 脆弱状态
			act_flag = 21, state_flag = 2, img_color = 0x0250;
			act_flag_temp = act_flag;
			tim_interrupt_init_ms(TIM_3, 2000, 0, 0);//状态计时
			return;
		case 22://检测到圆环入口
			act_flag = 22, state_flag = 2, img_color = 0x8CF6;
			return;
		case 26://检测到圆环出口 | 脆弱状态 | 右
			act_flag = 26, state_flag = 2, img_color = 0x0250;
			act_flag_temp = act_flag;
			tim_interrupt_init_ms(TIM_3, 2000, 0, 0);//状态计时
			return;
		case 27://检测到圆环入口 | 右
			act_flag = 27, state_flag = 2, img_color = 0x8CF6;
			return;
	//	十字、十字丢边
		case 31:
			act_flag = 31, state_flag = 3, img_color = 0x8D9B;
			act_flag_temp = act_flag;
			tim_interrupt_init_ms(TIM_3, 2000, 0, 0);//状态计时
			return;
	//	岔道
		case 41:
			act_flag = 41, state_flag = 4, img_color = 0xEFBE;
			yawa_flag = 1, yawa = 0;
			if(!cooling_flag){
				total_count_fork++;
				if(total_count_fork == 2){
//					uart_putchar(UART_6, 255);
					direction_fork = 1;
				}
//				show_value[0] = total_count_fork;
				cooling_flag = 1;
				tim_interrupt_init_ms(TIM_3, 3000, 0, 0);						
			}
			return;
	}
}
/*------------------------------*/
/*	   	 边线斜率分析模块		*/
/*==============================*/
char slope_cal(char num){
//	变量定义
	register char i;
	unsigned char mp[4];
	unsigned char line_flag;
	short slope[2];
	short angle;
//	计算斜率
	switch(num){
	//	出环辅助 | 右直道判断
		case 1:
			mp[0] = bottom_point_row;
			mp[2] = mp[0]+found_point[2] >> 1;
			mp[1] = (mp[0]+mp[2]) >> 1, mp[3] = mp[2]>>1;
		//	单调性判断
			if(rigbor[mp[0]]<rigbor[mp[1]])
				if(rigbor[mp[1]]<rigbor[mp[2]])
					if(rigbor[mp[2]]<rigbor[mp[3]])
						line_flag = 1;
			if(!line_flag) {line_slope_diff = 300;return;}
			slope[0] = (float)(rigbor[mp[0]]-rigbor[mp[2]])/(float)(mp[0]-mp[2])*1000;
			slope[1] = (float)(rigbor[mp[1]]-rigbor[mp[3]])/(float)(mp[1]-mp[3])*1000;
			line_slope_diff = slope[0]-slope[1];
			line_slope_ave = (slope[0]+slope[1])>>1;
			break;
	//	出环辅助 | 左直道判断
		case 2:
			mp[0] = bottom_point_row;
			mp[2] = mp[0]+found_point[0] >> 1;
			mp[1] = (mp[0]+mp[2]) >> 1, mp[3] = mp[2]>>1;
		//	单调性判断
			if(lefbor[mp[0]]<lefbor[mp[1]])
				if(lefbor[mp[1]]<lefbor[mp[2]])
					if(lefbor[mp[2]]<lefbor[mp[3]])
						line_flag = 1;
			if(!line_flag) {line_slope_diff = 300;return;}
			slope[0] = (float)(lefbor[mp[0]]-lefbor[mp[2]])/(float)(mp[2]-mp[0])*1000;
			slope[1] = (float)(lefbor[mp[1]]-lefbor[mp[3]])/(float)(mp[3]-mp[1])*1000;
			line_slope_diff = slope[0]-slope[1];
			line_slope_ave = (slope[0]+slope[1])>>1;
			break;
	//	圆环辅助 | 右直道检测
		case 3:
			mp[0] = ltraf_point_row[exti_leftop];
			mp[2] = mp[0]+found_point[2] >> 1;
			mp[1] = (mp[0]+mp[2]) >> 1, mp[3] = mp[2]>>1;
		//	单调性判断
			if(rigbor[mp[0]]<rigbor[mp[1]])
				if(rigbor[mp[1]]<rigbor[mp[2]])
					if(rigbor[mp[2]]<rigbor[mp[3]])
						line_flag = 1;
			if(!line_flag) {line_slope_diff = 300;return;}
			slope[0] = (float)(rigbor[mp[0]]-rigbor[mp[2]])/(float)(mp[0]-mp[2])*1000;
			slope[1] = (float)(rigbor[mp[1]]-rigbor[mp[3]])/(float)(mp[1]-mp[3])*1000;
			line_slope_diff = slope[0]-slope[1];
			break;
	//	圆环辅助 | 左直道检测
		case 4:
			mp[0] = rtraf_point_row[exti_rigtop];
			mp[2] = mp[0]+found_point[0] >> 1;
			mp[1] = (mp[0]+mp[2]) >> 1, mp[3] = mp[2]>>1;
		//	单调性判断
			if(lefbor[mp[0]]<lefbor[mp[1]])
				if(lefbor[mp[1]]<lefbor[mp[2]])
					if(lefbor[mp[2]]<lefbor[mp[3]])
						line_flag = 1;
			if(!line_flag) {line_slope_diff = 300;return;}
			slope[0] = (float)(lefbor[mp[0]]-lefbor[mp[2]])/(float)(mp[0]-mp[2])*1000;
			slope[1] = (float)(lefbor[mp[1]]-lefbor[mp[3]])/(float)(mp[1]-mp[3])*1000;
			line_slope_diff = slope[0]-slope[1];
			break;
	}
}
/*------------------------------*/
/*	   垂直边线宽度分析模块		*/
/*==============================*/
void vert_width_analysis(char num, unsigned char end_set){
//	变量定义
	register char i;
	unsigned char mp[5];
	short width[5], top_bias[4], bottom_bias[4];
	short wic[4]; 
	short topwic[4], bottomwic[4];
//	分析宽度变化
	switch(num){
		case 1://左
			mp[0] = 0, mp[4] = end_set;
			mp[2] = mp[4]>>1;
			mp[1] = mp[2]>>1, mp[3] = (mp[2]+mp[4])>>1;
		//	分析宽度变化
			for(i = 0; i < 5; i++) width[i] = bottombor[mp[i]]-topbor[mp[i]];
			for(i = 0; i < 4; i++){
				wic[i] = width[i+1]*width[i+1]-width[i]*width[i];
				top_bias[i] = topbor[0]*topbor[0]-topbor[mp[i+1]]*topbor[mp[i+1]];
				bottom_bias[i] = bottombor[0]*bottombor[0]-bottombor[mp[i+1]]*bottombor[mp[i+1]];
			}
			lef_widrate = (wic[0]+wic[1]+wic[2]+wic[3])>>2;
			lef_toprate = (top_bias[0]+top_bias[1]+top_bias[2]+top_bias[3])>>2;
			lef_botrate = (bottom_bias[0]+bottom_bias[1]+bottom_bias[2]+bottom_bias[3])>>2;
			break;
		case 2://右
			mp[0] = 159, mp[4] = end_set;
			mp[2] = (mp[0]+mp[4])>>1;
			mp[1] = (mp[0]+mp[2])>>1, mp[3] = (mp[2]+mp[4])>>1;
		//	分析宽度变化
			for(i = 0; i < 5; i++) width[i] = bottombor[mp[i]]-topbor[mp[i]];
			for(i = 0; i < 4; i++){
				wic[i] = width[i+1]*width[i+1]-width[i]*width[i];
				top_bias[i] = topbor[159]*topbor[159]-topbor[mp[i+1]]*topbor[mp[i+1]];
				bottom_bias[i] = bottombor[159]*bottombor[159]-bottombor[mp[i+1]]*bottombor[mp[i+1]];
			}
			rig_widrate = (wic[0]+wic[1]+wic[2]+wic[3])>>2;
			rig_toprate = (top_bias[0]+top_bias[1]+top_bias[2]+top_bias[3])>>2;
			rig_botrate = (bottom_bias[0]+bottom_bias[1]+bottom_bias[2]+bottom_bias[3])>>2;
//			show_value[0] = rig_widrate;
//			show_value[1] = rig_toprate;
//			show_value[2] = rig_botrate;
			break;
	}
}
/*------------------------------*/
/*	  	   拐点寻找模块			*/
/*==============================*/
void inflexion_search(void){
//	变量定义、初始化
	register unsigned char i;
	unsigned char zero_flag;
	short infle_diff = 0, infle_difftemp = 0, i_temp = 0;
//	拐点寻找
	for(i = MT9V03X_H-2; i > 10; i--){//左
		if(!zero_flag) infle_difftemp = infle_diff;
		infle_diff = lefbor[i]-lefbor[i+1];
		zero_flag = 0;
		if(infle_diff == 0){zero_flag = 1;continue;}
		if(infle_diff > 0){
			if(infle_difftemp < 0) infle_lefp[infle_lefcount] = (i+i_temp)>>1, infle_lefcount++;
			else i_temp = i;
		}
		else{
			if(infle_difftemp > 0) infle_lefp[infle_lefcount] = (i+i_temp)>>1, infle_lefcount++;
			else i_temp = i;
		}
	}
//	重置、寻找右拐点
	infle_diff = 0, infle_difftemp = 0, i_temp = 0;
	zero_flag = 0;
	for(i = MT9V03X_H-2; i > 10; i--){
		if(!zero_flag) infle_difftemp = infle_diff;
		infle_diff = rigbor[i]-rigbor[i+1];
		zero_flag = 0;
		if(infle_diff == 0){zero_flag = 1;continue;}
		if(infle_diff > 0){
			if(infle_difftemp < 0) infle_rigp[infle_rigcount] = (i+i_temp)>>1, infle_rigcount++;
			else i_temp = i;
		}
		else{
			if(infle_difftemp > 0) infle_rigp[infle_rigcount] = (i+i_temp)>>1, infle_rigcount++;
			else i_temp = i;
		}
	}
}
/*------------------------------*/
/*	  	岔道边界点辅助模块		*/
/*==============================*/
void vetsearch_fork_support(void){
//	变量定义
	register unsigned char i;
	register char j, k;
	unsigned char col = (MT9V03X_W-4)>>3;//换行
	unsigned char *p;
	unsigned char search_flag = 0, bottom_col;
	unsigned char found_flag, view_temp;
	unsigned char stop_flag1 = 0, stop_flag2 = 0;
//	变量初始化
	cut_fork_lef = 159, cut_fork_rig = 0, count_fork = 0;
//	寻找边界基点
	cut_fork_bottom_col = 0;
	p = &binary_img[MT9V03X_H-1][6];
	switch(act_flag){
		case 22:
		case 24:
			p = &binary_img[MT9V03X_H-1][4];
			break;
		case 27:
		case 29:
			p = &binary_img[MT9V03X_H-1][8];
			break;
	}
	for(i = MT9V03X_H-1; i > 0; i--, p-=col){
		if(*(unsigned long *)p == 0xffffffff && *(unsigned long *)(p+4) == 0xffffffff) continue;
		bottom_point_row = i;
		if(bottom_point_row < 10) return;
		p = &binary_img[bottom_point_row][6];
	//	找到最低点
		switch(search_flag){
			case 0:
				for(j = 6; j < 13; j++,p++){
					if(*(uint16*)p == 0xffff) continue;//全白
					if(*p != 0x00)
						if(*p != 0xff){//左突变
							for(k = 0; k < 7; k++)
								if(((*p>>(k+1))&0x01)^((*p>>k)&0x01)){cut_fork_bottom_col = (j<<3)+6-k;bottom_col = j;break;}
								break;
						}
					if(*(p+1) != 0x00)
						if(*(p+1) != 0xff){//右突变
							for(k = 0; k < 7; k++)
								if(((*(p+1)>>(k+1))&0x01)^((*(p+1)>>k)&0x01)){cut_fork_bottom_col = ((j+1)<<3)+6-k;bottom_col = j+1;break;}
								break;
						}
				}
				break;
		}
//	检测单行跳变点
	p = &binary_img[bottom_point_row-3][0];
	for(j = 0; j < 20; j++,p++){
    //	一般情况
        if(*p == 0x00) continue;//全黑
        if(*p == 0xff) continue;//全白
		if(*p != 0x00)
			if(*p != 0xff){//左突变
				for(k = 0; k < 7; k++)
					if(((*p>>(k+1))&0x01)^((*p>>k)&0x01)) count_fork++;
			}
	}
//	show_value[0] = count_fork;
//	寻找边界（左、右
	for(j = bottom_col-1; j > 1; j--){
		found_flag = 0, p = &binary_img[bottom_point_row][j];
		for(i = bottom_point_row; i > 10; i--, p-=col){
			view_temp = *(p)^*(p+col);
			for(k = 0; k < 8; k++){
				if(!((found_flag>>k)&0x01))
					if((view_temp>>k)&0x01){     
						border_top[(j<<3)+7-k] = i;
						if(cut_fork_lef > (j<<3)+7-k) cut_fork_lef = (j<<3)+7-k;
						if(!stop_flag1 && (j<<3) < cut_fork_bottom_col)
							if(border_top[(j<<3)+8-k]-border_top[(j<<3)+7-k] > 6)
								stop_flag1 = (j<<3)+7-k;
					}
			}
			found_flag |= view_temp;
			if(found_flag == 0xFF) break;
			if(*(p+col) == 0x00) break;
		}
		if(found_flag != 0xFF) break;	
	}
	for(j = bottom_col; j < 18; j++){
		found_flag = 0, p = &binary_img[bottom_point_row][j];
		for(i = bottom_point_row; i > 10; i--, p-=col){
			view_temp = *(p)^*(p+col);
			for(k = 7; k > -1; k--){
				if(!((found_flag>>k)&0x01))
					if((view_temp>>k)&0x01){     
						border_top[(j<<3)+7-k] = i;
						if(cut_fork_rig < (j<<3)+7-k) cut_fork_rig = (j<<3)+7-k;
						if(!stop_flag2 && (j<<3) > cut_fork_bottom_col)
							if(border_top[(j<<3)+6-k]-border_top[(j<<3)+7-k] > 6)
								stop_flag2 = (j<<3)+7-k;
					}
			}
			found_flag |= view_temp;
			if(found_flag == 0xFF) break;
			if(*(p+col) == 0x00) break;
		}
		if(found_flag != 0xFF) break;	
	}
	if(stop_flag1) cut_fork_lef = stop_flag1;
	if(stop_flag2) cut_fork_rig = stop_flag2;
		break;
	}
}
/*------------------------------*/
/*	  	岔道边界点寻找模块		*/
/*==============================*/
void vertsearch_frok(void){
//	变量定义
	register char i;
	unsigned char mp[5];
	short cut_lef_slope = 0, cut_rig_slope = 0;
	short lef_slope, rig_slope;
	short slope[2];
//	左边界检测
	if(cut_fork_bottom_col - cut_fork_lef > 6){
		mp[0] = cut_fork_lef+3, mp[4] = cut_fork_bottom_col;
		mp[2] = (mp[0]+mp[4])>>1;
		mp[1] = (mp[0]+mp[2])>>1, mp[3] = (mp[2]+mp[4])>>1;
		slope[0] = (float)(border_top[mp[2]]-border_top[mp[0]])/(float)(mp[2]-mp[0])*1000;
		slope[1] = (float)(border_top[mp[3]]-border_top[mp[1]])/(float)(mp[3]-mp[1])*1000;
		cut_lef_slope = abs(slope[0] - slope[1]);
		lef_slope = (float)(border_top[mp[0]]-border_top[mp[3]])/(float)(mp[0]-mp[3])*1000;
	}
	else return;
//	右边界检测
	if(cut_fork_rig - cut_fork_bottom_col > 6){
		mp[0] = cut_fork_rig-3;
		mp[2] = (mp[0]+mp[4])>>1;
		mp[1] = (mp[0]+mp[2])>>1, mp[3] = (mp[2]+mp[4])>>1;
		slope[0] = (float)(border_top[mp[0]]-border_top[mp[2]])/(float)(mp[2]-mp[0])*1000;
		slope[1] = (float)(border_top[mp[1]]-border_top[mp[3]])/(float)(mp[3]-mp[1])*1000;
		cut_rig_slope = abs(slope[0] - slope[1]);
		rig_slope = (float)(border_top[mp[0]]-border_top[mp[3]])/(float)(mp[3]-mp[0])*1000;
	}
	else return;
//	岔道判断
	if(cut_fork_lef < 40 && cut_fork_lef > 10)
		if(cut_fork_rig < 149 && cut_fork_rig > 119)
			if(cut_lef_slope < 50 && cut_rig_slope < 50)
				if(lef_slope > 90 && lef_slope < 300)
					if(rig_slope > 90 && rig_slope < 300)
						state = 41;
//						if(abs(lef_slope - cut_rig_slope) < 60)
	return;
}
/*------------------------------*/
/*	  垂直边界点寻找模块（左）	*/
/*==============================*/
void vert_leftsearch(unsigned char top, unsigned char bottom){
//	变量定义
	register unsigned char i;
	register char j, k;
	unsigned char col = (MT9V03X_W-4)>>3;//换行
	unsigned char *p;
	unsigned char found_flag, view_temp;
//	寻找下边界
	lefbottom_cut = 0;
	for(j = 0; j < 19; j++){
		found_flag = 0, p = &binary_img[exti_lefp[0]][j];
		for(i = exti_lefp[0]; i < bottom; i++, p+=col){
			view_temp = *(p)^*(p+col);
			for(k = 7; k > -1; k--){
				if(!((found_flag>>k)&0x01))
					if((view_temp>>k)&0x01){
						bottombor[(j<<3)+7-k] = i;
						if(lefbottom_cut < (j<<3)+7-k) lefbottom_cut =(j<<3)+7-k;
					}
			}
			found_flag |= view_temp;
			if(found_flag == 0xFF) break;
			if(*(p+col) == 0x00) break;
		}
		if(found_flag != 0xFF) break;
	}
//	寻找上边界
	leftop_cut = 0;
	for(j = 0; j < 19; j++){
		found_flag = 0, p = &binary_img[exti_lefp[0]][j];
		for(i = exti_lefp[0]; i > top; i--, p-=col){
			view_temp = *(p)^*(p-col);
			for(k = 7; k > -1; k--){
				if(!((found_flag>>k)&0x01))
					if((view_temp>>k)&0x01){
						topbor[(j<<3)+7-k] = i;
						if(leftop_cut < (j<<3)+7-k) leftop_cut =(j<<3)+7-k;
					}
			}
			found_flag |= view_temp;
			if(found_flag == 0xFF) break;
			if(*(p+col) == 0x00) break;
		}
		if(found_flag != 0xFF) break;
	}
//	分析垂直边界
	if(leftop_cut > 5) 
		if(lefbottom_cut > 5){
			if(lefbottom_cut < leftop_cut) vert_width_analysis(1, lefbottom_cut);
			else vert_width_analysis(1, leftop_cut);
		}
}
/*------------------------------*/
/*	  垂直边界点寻找模块（右）	*/
/*==============================*/
void vert_rightsearch(unsigned char top, unsigned char bottom){
//	变量定义
	register unsigned char i;
	register char j, k;
	unsigned char col = (MT9V03X_W-4)>>3;//换行
	unsigned char *p;
	unsigned char found_flag, view_temp;
//	寻找下边界
	rigbottom_cut = 159;
	for(j = 19; j > -1; j--){
		found_flag = 0, p = &binary_img[exti_rigp[0]][j];
		for(i = exti_rigp[0]; i < bottom; i++, p+=col){
			view_temp = *(p)^*(p+col);
			for(k = 7; k > -1; k--){
				if(!((found_flag>>k)&0x01))
					if((view_temp>>k)&0x01){
						bottombor[(j<<3)+7-k] = i;
						if(rigbottom_cut > (j<<3)+7-k) rigbottom_cut =(j<<3)+7-k;
					}
			}
			found_flag |= view_temp;
			if(found_flag == 0xFF) break;
			if(*(p+col) == 0x00) break;
		}
		if(found_flag != 0xFF) break;
	}
//	寻找上边界
	rigtop_cut = 159;
	for(j = 19; j > -1; j--){
		found_flag = 0, p = &binary_img[exti_rigp[0]][j];
		for(i = exti_rigp[0]; i > top; i--, p-=col){
			view_temp = *(p)^*(p-col);
			for(k = 7; k > -1; k--){
				if(!((found_flag>>k)&0x01))
					if((view_temp>>k)&0x01){
						topbor[(j<<3)+7-k] = i;
						if(rigtop_cut > (j<<3)+7-k) rigtop_cut =(j<<3)+7-k;
					}
			}
			found_flag |= view_temp;
			if(found_flag == 0xFF) break;
			if(*(p+col) == 0x00) break;
		}
		if(found_flag != 0xFF) break;
	}
//	分析垂直边界
	if(rigbottom_cut < 155)
		if(rigtop_cut < 155){
			if(rigbottom_cut > rigtop_cut) vert_width_analysis(2, rigbottom_cut);
			else vert_width_analysis(2, rigtop_cut);
		}
}
/*------------------------------*/
/*	  边界跳变点寻找模块（左）	*/
/*==============================*/
void border_vertical_leftsearch(void){
//	变量定义
	register unsigned char i, k;
	unsigned char vetflag = 0;
	unsigned char vet_colmax, vet_rowmax;
//	垂直边界寻找
	if(ltraf_count > 1)
		for(i = 1; i < ltraf_count; i++){
		//	左外凸
			if(ltraf_flag[i] == 0)
				if(ltraf_flag[i-1] == 1){
					for(k = ltraf_point_row[i], vet_colmax = 0; k < ltraf_point_row[i-1]; k++) 
						if(lefbor[k] > vet_colmax) vet_colmax = lefbor[k], vet_rowmax = k; 
					lvet_trafpoint_row[lvet_trafcount] = vet_rowmax, lvet_trafpoint_col[lvet_trafcount] = vet_colmax, lvet_trafcount++;
				}
		//	出口
			if(ltraf_flag[i] == 1)
				if(ltraf_flag[i-1] == 0){ 
					exti_lefp[exti_lefcount] = (ltraf_point_row[i]+ltraf_point_row[i-1])>>1, exti_lefcount++;
					if(!vetflag){
						if(i+1 < ltraf_count) {vetflag = 1, exti_leftop = i, lefhigh = ltraf_point_row[i-1] - ltraf_point_row[i];vert_leftsearch(ltraf_point_row[i+1], ltraf_point_row[i-1]+10);}
						else {vetflag = 1, exti_leftop = i, lefhigh = ltraf_point_row[i-1] - ltraf_point_row[i];vert_leftsearch(ltraf_point_row[i]-7, ltraf_point_row[i-1]+10);}
					}
				}
		}
}
/*------------------------------*/
/*	  边界跳变点寻找模块（右）	*/
/*==============================*/
void border_vertical_rightsearch(void){
//	变量定义
	register unsigned char i, k;
	unsigned char vetflag = 0;
	unsigned char vet_colmax, vet_rowmax;
//	寻找跳变
	if(rtraf_count > 1)
		for(i = 1; i < rtraf_count; i++){
		//	右外凸
			if(rtraf_flag[i] == 0)
				if(rtraf_flag[i-1] == 1){
					for(k = rtraf_point_row[i], vet_colmax = 159; k < rtraf_point_row[i-1]; k++) 
						if(rigbor[k] < vet_colmax) vet_colmax = rigbor[k], vet_rowmax = k; 
					rvet_trafpoint_row[rvet_trafcount] = vet_rowmax, rvet_trafpoint_col[rvet_trafcount] = vet_colmax, rvet_trafcount++;
				}
		//	出口
			if(rtraf_flag[i] == 1){
				if(rtraf_flag[i-1] == 0) exti_rigp[exti_rigcount] = (rtraf_point_row[i]+rtraf_point_row[i-1])>>1, exti_rigcount++;
				if(!vetflag){
					if(i+1 < rtraf_count){vetflag = 1, exti_rigtop = i, righigh = rtraf_point_row[i-1] - rtraf_point_row[i];vert_rightsearch(rtraf_point_row[i+1], rtraf_point_row[i-1]+10);}
					else {vetflag = 1, exti_rigtop = i, righigh = rtraf_point_row[i-1] - rtraf_point_row[i];vert_rightsearch(rtraf_point_row[i]-7, rtraf_point_row[i-1]+10);}
				}
			}
		}
}
/*------------------------------*/
/*		  边界点限制模块		*/
/*==============================*/
void border_limit(void){
//	变量定义
	register unsigned char i;
//	边界限制
	if(rcut > 40)
		if(lefbor[rcut-3] > 10)
			if(rigbor[rcut] < 20){
				lcut = rcut+1, border_flag = 0;
				for(i = 0; i < lcut; i++) lefbor[i] = 0, rigbor[i] = 0;
			}
	if(lcut > 40)
		if(rigbor[lcut-3] < 149)
			if(lefbor[lcut] > 139){
			rcut = lcut+1, border_flag = 0;
			for(i = 0; i < rcut; i++) lefbor[i] = 159, rigbor[i] = 159;
			}
}
/*------------------------------*/
/*		 左边界点寻找模块		*/
/*==============================*/
void lbor_search(void){
//	变量定义
	short traf_slope, traf_slope_temp;
	register unsigned char i = found_point[0], k;
	register char j = found_point[1];
	unsigned char col = (MT9V03X_W-4)>>3;//换行
	unsigned char *p;
	unsigned char traf_flag, traf_flag_temp;
	char sloptraf, lcmax = 0, lcmin = 0, local_flag1, local_flag1_temp, local_flag2, local_flag2_temp;
//	初始化
	lcut = 0, ltraf_count = 0, lefbottom_cut = 0, leftop_cut = 0;
	lvet_trafcount = 0, exti_lefcount = 0, leftop_cut = 0, lefbottom_cut = 0;
	for(k = 0; k < 4; k++) ac_flag[k] = 0;
//	从基准点开始寻找
	p = &binary_img[i][j];
	switch(fop_flag){
		case 1://基准点在最底下
			for(k = 0; k < 7; k++)
				if(((*p>>(k+1))&0x01)^((*p>>k)&0x01)){lefbor[i] = (j<<3)+6-k;break;}
			break;
		case 2:
			lefbor[i] = (j<<3)+7;
			break;
		case 3://基准点不在底下
			for(k = 0; k < 7; k++)
				if(((*p>>(k+1))&0x01)^((*p>>k)&0x01)){lefbor[i] = (j<<3)+6-k;break;}
			for(k = MT9V03X_H - 1; k > i; k--) lefbor[k] = 0;
			break;
	}
//	向上检测
	for(i--; i > 0; i--){
	//	初始化换行、方向检测
		p -= col;
		if(traf_flag!=traf_flag_temp) 
			if(i < 80)//不检测最底下的转变点
				if(ltraf_point_row[ltraf_count-1]-i>3 || ltraf_count == 0){//限制转变点高度
					if(traf_flag == 1) ltraf_flag[ltraf_count] = 0;//从右到左转变
					else ltraf_flag[ltraf_count] = 1;//从左到右转变
					ltraf_point_row[ltraf_count] = i+1, ltraf_point_col[ltraf_count] = lefbor[i+1], ltraf_count++;
				}
		traf_flag_temp = traf_flag;
		traf_flag = 0;
		if(*(p+1) != 0x00)
			if(*(p+1) != 0xff){//右突变
				for(k = 0; k < 7; k++)
					if(((*(p+1)>>(k+1))&0x01)^((*(p+1)>>k)&0x01)){lefbor[i] = ((j+1)<<3)+6-k;break;}
					continue;
			}
		if(*p != 0x00)
			if(*p != 0xff){//左突变
				for(k = 0; k < 7; k++)
					if(((*p>>(k+1))&0x01)^((*p>>k)&0x01)){lefbor[i] = (j<<3)+6-k;break;}
					continue;
			}
		if(*(uint16*)p == 0xFF00){lefbor[i] = (j<<3)+7;continue;}//左黑右白跳变
		if(*(uint16*)p == 0x00FF){lefbor[i] = (j+1)<<3;continue;}//左白右黑跳变
	//	全黑
		if(*(uint16*)p == 0x0000){
			for(p++, j++; j < 19; p++, j++){//向右寻找跳变点
				if(*(uint16*)p == 0x0000) continue;
				else break;
			}
			if(j == 19){//抵达边界，停止搜索
				lcut = i;
				if(traf_flag_temp)
					if(ltraf_point_row[ltraf_count-1]-i>5 || ltraf_count == 0)
						ltraf_flag[ltraf_count] = 1, ltraf_point_row[ltraf_count] = i+1, ltraf_point_col[ltraf_count] = lefbor[i+1], ltraf_count++;
				return;
			}
			if(*(uint16*)p == 0xFF00){lefbor[i] = (j<<3)+7;continue;}//左黑右白跳变
			if(*(uint16*)p == 0x00FF){lefbor[i] = (j+1)<<3;continue;}//左白右黑跳变
			if(*(p+1) != 0x00)
				if(*(p+1) != 0xff){//右突变
					for(k = 0; k < 7; k++)
						if(((*(p+1)>>(k+1))&0x01)^((*(p+1)>>k)&0x01)){lefbor[i] = ((j+1)<<3)+6-k;break;}
						continue;
				}
			if(*p != 0x00)
				if(*p != 0xff){//左突变
					for(k = 0; k < 7; k++)
						if(((*p>>(k+1))&0x01)^((*p>>k)&0x01)){lefbor[i] = (j<<3)+6-k;break;}
						continue;
				}
		}
	//	全白
		if(*(uint16*)p == 0xFFFF){
			for(p--, j--; j > -1; p--, j--){//向左寻找跳变点
				if(*(uint16*)p == 0xFFFF) continue;
				else break;
			}
			if(j == -1){lcut = i;traf_flag = 1,j+=6,p+=6,lefbor[i] = 0;continue;}//抵达全白边界
			if(*(uint16*)p == 0xFF00){lefbor[i] = (j<<3)+7;continue;}//左黑右白跳变
			if(*(uint16*)p == 0x00FF){lefbor[i] = (j+1)<<3;continue;}//左白右黑跳变
			if(*p != 0x00)
				if(*p != 0xff){//左突变
					for(k = 0; k < 7; k++)
						if(((*p>>(k+1))&0x01)^((*p>>k)&0x01)){lefbor[i] = (j<<3)+6-k;break;}
						continue;
				}
			if(*(p+1) != 0x00)
				if(*(p+1) != 0xff){//右突变
					for(k = 0; k < 7; k++)
						if(((*(p+1)>>(k+1))&0x01)^((*(p+1)>>k)&0x01)){lefbor[i] = ((j+1)<<3)+6-k;break;}
						continue;
				}
		}
	}
	lcut = i;//退出前保存所在行
}
/*------------------------------*/
/*		 右边界点寻找模块		*/
/*==============================*/
void rbor_search(void){
//	变量定义
	register unsigned char i = found_point[2], k;
	register char j = found_point[3];
	unsigned char col = (MT9V03X_W-4)>>3;//换行
	unsigned char traf_flag, traf_flag_temp;
	unsigned char *p;
//	初始化
	rcut = 0, rtraf_count = 0, rigbottom_cut = 159, rigtop_cut = 159;
	rvet_trafcount = 0, exti_rigcount = 0, rigtop_cut = 159, rigbottom_cut = 159;
//	从基准点开始寻找
	p = &binary_img[i][j];
	switch(fop_flag){
		case 1://基准点在最底下
			for(k = 7; k > 0; k--)
				if(((*p>>k)&0x01)^((*p>>(k-1))&0x01)){rigbor[i] = (j<<3)+8-k;break;}
			break;
		case 2:
			rigbor[i] = (j<<3);
			break;
		case 3:
			for(k = 7; k > 0; k--)
				if(((*p>>k)&0x01)^((*p>>(k-1))&0x01)){rigbor[i] = (j<<3)+8-k;break;}
			for(k = MT9V03X_H - 1; k > i; k--) rigbor[k] = 159;
			break;
	}
//	限制边界
	if(j == 19) j--, p--;
//	向上检测
	for(i--; i > 0; i--){
	//	初始化换行、方向检测
		p -= col;
		if(traf_flag!=traf_flag_temp) 
			if(i < 80)//不检测最底下的转变点
				if(rtraf_point_row[rtraf_count-1]-i>5 || rtraf_count == 0){//限制转变点高度
					if(traf_flag == 1) rtraf_flag[rtraf_count] = 0;//从左到右转变
					else rtraf_flag[rtraf_count] = 1;//从右到左转变
					rtraf_point_row[rtraf_count] = i+1, rtraf_point_col[rtraf_count] = rigbor[i+1], rtraf_count++;
				}
		traf_flag_temp = traf_flag;
		traf_flag = 0;
		if(*p != 0x00)
			if(*p != 0xff){//左突变
				for(k = 7; k > 0; k--)
					if(((*p>>k)&0x01)^((*p>>(k-1))&0x01)){rigbor[i] = (j<<3)+8-k;break;}
					continue;
			}
		if(*(p+1) != 0x00)
			if(*(p+1) != 0xff){//右突变
				for(k = 7; k > 0; k--)
					if(((*(p+1)>>k)&0x01)^((*(p+1)>>(k-1))&0x01)){rigbor[i] = ((j+1)<<3)+8-k;break;}
					continue;
			}
		if(*(uint16*)p == 0x00FF){rigbor[i] = ((j+1)<<3);continue;}//左白右黑跳变
		if(*(uint16*)p == 0xFF00){rigbor[i] = (j<<3)+7;continue;}//左黑右白跳变
	//	全黑
		if(*(uint16*)p == 0x0000){
			for(p--, j--; j >  -1; p--, j--){//向左寻找跳变点
				if(*(uint16*)p == 0x0000) continue;
				else break;
			}
			if(j == -1){//抵达边界，停止搜索
				rcut = i;
				if(traf_flag_temp)//转变点检测
					if(rtraf_point_row[rtraf_count-1]-i>5 || rtraf_count == 0)//限制转变点高度
						rtraf_point_row[rtraf_count] = i+1, rtraf_point_col[rtraf_count] = rigbor[i+1], rtraf_count++;
				return;
			}
			if(*(uint16*)p == 0x00FF){rigbor[i] = ((j+1)<<3);continue;}//左白右黑跳变
			if(*(uint16*)p == 0xFF00){rigbor[i] = (j<<3)+7;continue;}//左黑右白跳变
			if(*p != 0x00)
				if(*p != 0xff){//左突变
					for(k = 7; k > 0; k--)
						if(((*p>>k)&0x01)^((*p>>(k-1))&0x01)){rigbor[i] = (j<<3)+8-k;break;}
						continue;
				}
			if(*(p+1) != 0x00)
				if(*(p+1) != 0xff){//右突变
					for(k = 7; k > 0; k--)
						if(((*(p+1)>>k)&0x01)^((*(p+1)>>(k-1))&0x01)){rigbor[i] = ((j+1)<<3)+8-k;break;}
						continue;
				}
		}
	//	全白
		if(*(uint16*)p == 0xFFFF){
			for(p++, j++; j < 19; p++, j++){//向右寻找跳变点
				if(*(uint16*)p == 0xFFFF) continue;
				else break;
			}
			if(j == 19){rcut = i;traf_flag = 1;j-=6, p-=6,rigbor[i] = 159;continue;}
			if(*(uint16*)p == 0x00FF){rigbor[i] = ((j+1)<<3);continue;}//左白右黑跳变
			if(*(uint16*)p == 0xFF00){rigbor[i] = (j<<3)+7;continue;}//左黑右白跳变
			if(*(p+1) != 0x00)
				if(*(p+1) != 0xff){//右突变
					for(k = 7; k > 0; k--)
						if(((*(p+1)>>k)&0x01)^((*(p+1)>>(k-1))&0x01)){rigbor[i] = ((j+1)<<3)+8-k;break;}
						continue;
				}
			if(*p != 0x00)
				if(*p != 0xff){//左突变
					for(k = 7; k > 0; k--)
						if(((*p>>k)&0x01)^((*p>>(k-1))&0x01)){rigbor[i] = (j<<3)+8-k;break;}
						continue;
				}
		}
	}
	rcut = i;//退出前保存所在行
}
/*------------------------------*/
/*		基准点辅助模块（左）	*/
/*==============================*/
static void left_fop_search_sup(unsigned char* p, char j){
//	一般情况
	if(*p != 0xFF)
		if(*p != 0x00){//左视场突变
			fop_flag = 1, found_point[0] = MT9V03X_H - 1, found_point[1] = j;
			return;
		}
	if(*(p+1) != 0xFF)
		if(*(p+1) != 0x00){//右视场突变
			fop_flag = 1, found_point[0] = MT9V03X_H - 1, found_point[1] = j+1;
			return;
		}
//	左黑右白
	fop_flag = 2, found_point[0] = MT9V03X_H - 1, found_point[1] = j;
}
/*------------------------------*/
/*		基准点辅助模块（右）	*/
/*==============================*/
static void right_fop_search_sup(unsigned char* p, char j){
//	一般情况
	if(*p != 0xFF)
		if(*p != 0x00){//左视场突变
			fop_flag = 1, found_point[2] = MT9V03X_H - 1, found_point[3] = j;
			return;
		}
	if(*(p+1) != 0xFF)
		if(*(p+1) != 0x00){//右视场突变
			fop_flag = 1, found_point[2] = MT9V03X_H - 1, found_point[3] = j+1;
			return;
		}
//	左白右黑
	fop_flag = 2, found_point[2] = MT9V03X_H - 1, found_point[3] = j+1;
}
/*------------------------------*/
/*		 基准点寻找模块（左）	*/
/*==============================*/
void left_fop_search(void){
//	变量定义
	register unsigned char i = MT9V03X_H - 1;
	register char j;
	unsigned char* p;
//	左基点寻找 
	p = &binary_img[i][8];
	for(j = 8; j > -1; j--){
		if(*(uint16*)p == 0xFFFF){p--;continue;}
		left_fop_search_sup(p, j);
		return;
	}
//	未找到基点，向上寻找
	for(i = MT9V03X_H - 1; i > 0; i--){
		if(!(binary_img[i][0]^binary_img[i-1][0])) continue;
		fop_flag = 3, found_point[0] = i, found_point[1] = 0;
		return;
	}
}
/*------------------------------*/
/*		 基准点寻找模块（右）	*/
/*==============================*/
void right_fop_search(void){
//	变量定义
	register unsigned char i = MT9V03X_H - 1;
	register char j;
	unsigned char* p;
//	右基点寻找 
	p = &binary_img[i][10];
	for(j = 10; j < 19; j++){
		if(*(uint16*)p == 0xFFFF){p++;continue;}
		right_fop_search_sup(p, j);
		return;
	}
//	未找到基点，向上寻找
	for(i = MT9V03X_H - 1; i > 0; i--){
		if(!(binary_img[i][19]^binary_img[i-1][19])) continue;
		fop_flag = 3, found_point[2] = i, found_point[3] = 19;
		return;
	}
}
/*------------------------------*/
/*		  图像二值化模块		*/
/*==============================*/
void img_binary(void){
//	变量定义
	register unsigned char i, j, k;
	unsigned char column = (MT9V03X_W-4)>>3;
	unsigned char binary_temp;
//	图像二值化
	for(i = 0; i < MT9V03X_H; i++){
		for(j = 0; j < column; j++){
		//	重置图像
			binary_img[i][j] = 0x00;
		//	二值化
			for(k = 0; k < 8; k++){
				binary_img[i][j] <<= 1;
				if(mt9v03x_image[i][(j<<3)+k+2] > img_thrsod) binary_img[i][j] |= 0x01;
			}
		}
	}
}
/*------------------------------*/
/*		大津法全局阈值模块		*/
/*==============================*/
void otsu(void){
//	变量定义
	float var = 0, vartmp = 0;
	float imgsize = MT9V03X_H*MT9V03X_W, sumPK = 0, sumMK = 0;
	register short i, j;
	unsigned short hist[grayscale] = {0};	
//	获取直方图
	for(i = 0; i < MT9V03X_H; i++){
		for(j = 0; j < MT9V03X_W; j++)
			hist[mt9v03x_image[i][j]]++;
	}
//	求类间方差
	for(i = 0; i < grayscale; i++){
		P[i] = (float)hist[i]/imgsize;//计算每个灰度级出现的概率
		PK[i] = sumPK+P[i];//概率累计和
		sumPK = PK[i];
		MK[i] = sumMK+i*P[i];//灰度值累加均值
		sumMK = MK[i];
	}
	for(i = 30; i < 220; i++){
		vartmp = ((MK[grayscale-1]*PK[i] - MK[i])*(MK[grayscale-1]*PK[i] - MK[i])) / (PK[i]*(1 - PK[i]));
		if(vartmp > var){
			var = vartmp;
			img_thrsod = i;//输出阈值
		}
	}
}
