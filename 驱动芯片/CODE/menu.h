/*------------------------------------------------------*/
/* 					   ͷ�ļ����� 						*/
/*======================================================*/
#ifndef _MENU_H
#define _MENU_H
/*------------------------------------------------------*/ 
/* 						�������� 						*/
/*======================================================*/
/*----------------------*/
/*	 	 �˵�����		*/
/*======================*/
static char info(char index, char num);
static void display(char index, char menu[4]);
static char menu_limit(char index, char num);
static void menu_selection(unsigned char event);
/*----------------------*/
/*	 	 ��������		*/
/*======================*/
void dir(unsigned char dirc);
static unsigned char col_jug(void);
void trig_jug(void);
#endif
