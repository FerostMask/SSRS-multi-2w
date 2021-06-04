/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "menu.h"
#include "Init.h"
#include "menu_2.h"
#include "string.h"
#include "fontlib.h"
#include "zf_gpio.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/

//----------------------------�ָ���----------------------------//
/*--------------------------------------------------------------*/
/* 							 һ���˵� 							*/
/*==============================================================*/
/*------------------------------*/
/*		 �˵���Ϣ�洢ģ��		*/
/*==============================*/
static char info(char index, char num){
//	��������
	register unsigned char i;
//	������
	switch(index){
		case MENU_SWITCH:
		//	������
			switch(num){
				case 0://��������
					for(i = 0; i < 32; i++) nom[i] = can0[i];
					for(i = 0; i < 32; i++) nom[32+i] = shu0[i];
					for(i = 0; i < 32; i++) nom[64+i] = she0[i];
					for(i = 0; i < 32; i++) nom[96+i] = zhi0[i];
					return 4;
				case 1://ת������
					for(i = 0; i < 32; i++) nom[i] = zhuan0[i];
					for(i = 0; i < 32; i++) nom[32+i] = su0[i];
					for(i = 0; i < 32; i++) nom[64+i] = she0[i];
					for(i = 0; i < 32; i++) nom[96+i] = zhi0[i];
					return 4;
			}
			break;
		case PARASET_PID1:
			switch(num){
				case 0://�ٶ� | PD
					for(i = 0; i < 32; i++) nom[i] = su0[i];
					for(i = 0; i < 32; i++) nom[32+i] = du0[i];
					return 2;
					break;
				case 1://�Ƕ� | PD
					for(i = 0; i < 32; i++) nom[i] = jiao0[i];
					for(i = 0; i < 32; i++) nom[32+i] = du0[i];
					return 2;
				case 2://���ٶ� | PI 
					for(i = 0; i < 32; i++) nom[i] = jiao0[i];
					for(i = 0; i < 32; i++) nom[32+i] = su0[i];
					for(i = 0; i < 32; i++) nom[64+i] = du0[i];
					return 3;
			}
			break;
		case PARASET_PID2:
			switch(num){
				case 0://ת�� | PD 
					for(i = 0; i < 32; i++) nom[i] = zhuan0[i];
					for(i = 0; i < 32; i++) nom[32+i] = xiang0[i];
					return 2;
				case 1://����� | PI
					for(i = 0; i < 32; i++) nom[i] = zuo0[i];
					for(i = 0; i < 32; i++) nom[32+i] = cha0[i];
					for(i = 0; i < 32; i++) nom[64+i] = su0[i];
					return 3;
				case 2://�Ҳ��� | PI 
					for(i = 0; i < 32; i++) nom[i] = you0[i];
					for(i = 0; i < 32; i++) nom[32+i] = cha0[i];
					for(i = 0; i < 32; i++) nom[64+i] = su0[i];
					return 3;
			}
		case PARASET_OPER:
			switch(num){
				case 0://��̬
					for(i = 0; i < 32; i++) nom[i] = zi0[i];
					for(i = 0; i < 32; i++) nom[32+i] = tai0[i];
					return 2;
					break;
			}
			break;
		case MONITOR_MENU:
			switch(num){
				case 0://������
					for(i = 0; i < 32; i++) nom[i] = jian0[i];
					for(i = 0; i < 32; i++) nom[32+i] = shi0[i];
					for(i = 0; i < 32; i++) nom[64+i] = qi0[i];
					return 3;
					break;
			}
			break;
		case 100://�˵�
			for(i = 0; i < 32; i++) nom[i] = cai0[i];
			for(i = 0; i < 32; i++) nom[32+i] = dan0[i];
			return 2;
			break;
	}
	return 0;
}
/*------------------------------*/
/*		   �˵���ʾģ��			*/
/*==============================*/
void menu_display(void){
//	��������
	char show_index[ROWS];
//	����
	ips200_clear(WHITE);
//	������ʾ����
	if(menu_index-1<0) show_index[0] = ROWS-1;
	else show_index[0] = menu_index - 1;

	show_index[1] = menu_index;

	if(menu_index+1>ROWS-1) show_index[2] = 0,show_index[3] = 1;
	else if(menu_index+2>ROWS-1) show_index[2] = menu_index+1,show_index[3] = 0;
	else show_index[2] = menu_index+1,show_index[3] = menu_index+2;
//	�˵���ʾ
	ips200_display_chinese(0, 208, 16, nom, info(100, menu[show_index[0]]), 0XFDF8);
	ips200_display_chinese(14, 224, 16, nom, info(show_index[0], menu[show_index[0]]), 0xB6DB);
	
	ips200_display_chinese(20, 256, 16, nom, info(show_index[1], menu[show_index[1]]), 0xB6DB);
	
	ips200_display_chinese(10, 288, 16, nom, info(show_index[2], menu[show_index[2]]), 0xB6DB);
	ips200_display_chinese(0, 304, 16, nom, info(show_index[3], menu[show_index[3]]), 0xB6DB);
}
/*------------------------------*/
/*		 �˵���ֵ����ģ��		*/
/*==============================*/
static char menu_limit(char index, char num){
//	����������ֵ
	switch(index){
		case 0:if(num<menu_limit0) return 1;break;
		case 1:if(num<menu_limit1) return 1;break;
		case 2:if(num<menu_limit2) return 1;break;
		case 3:if(num<menu_limit3) return 1;break;
		case 4:if(num<menu_limit4) return 1;break;
	}
	return 0;
}
/*------------------------------*/
/*		 һ���˵��¼�ģ��		*/
/*==============================*/
void menu_select(unsigned char event){
//	һ���˵�
	if(!menu_level){
	//	�˵��¼���֧
		switch(event){
			case 6://�Ұ���
				if(menu_limit(menu_index, menu[menu_index])) menu[menu_index]++;
				else return;
				break;
			
			case 4://�󰴼�
				if(menu[menu_index] > 0) menu[menu_index]--;
				else return;
				break;
			
			case 2://�ϰ���
				if(menu_index>0) menu_index--;
				else menu_index = ROWS-1;
				break;
			
			case 5://�°���
				if(menu_index<ROWS-1) menu_index++;
				else menu_index = 0;
				break;
			
			case 1://ȷ����
			//	��ʼ�������˵�
				menu2_init();
				menu2_display();
				menu_level = 1;
				return;
			case 3:break;
		}
		menu_display();
	}
}
