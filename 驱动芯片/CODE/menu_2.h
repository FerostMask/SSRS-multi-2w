/*------------------------------------------------------*/
/* 					   ͷ�ļ����� 						*/
/*======================================================*/
#ifndef _SECMENU_H
#define _SECMENU_H
/*------------------------------------------------------*/ 
/* 						�������� 						*/
/*======================================================*/
/*------------------------------*/
/*		    �˵���������		*/
/*==============================*/
void menu2_init(unsigned char index, unsigned char num);
static void menu2value(unsigned char index, unsigned char menu_level);
void menu2display(unsigned char index);
void menu2_slect(unsigned char event);
/*------------------------------*/
/*		   ��ֵ����ģ��			*/
/*==============================*/
void monitor(void);
void fixed_monitor(void);
/*------------------------------*/
/*		   ��ť״̬ģ��			*/
/*==============================*/
void swdisplay(void);
#endif
