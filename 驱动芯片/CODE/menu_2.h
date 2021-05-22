/*------------------------------------------------------*/
/* 					   头文件声明 						*/
/*======================================================*/
#ifndef _SECMENU_H
#define _SECMENU_H
/*------------------------------------------------------*/ 
/* 						函数声明 						*/
/*======================================================*/
/*------------------------------*/
/*		    菜单基础部分		*/
/*==============================*/
void menu2_init(void);
void menu2_display(void);
void menu2_select(unsigned char event);
/*------------------------------*/
/*		   数值监视模块			*/
/*==============================*/
void monitor(void);
void fixed_monitor(void);
/*------------------------------*/
/*		   按钮状态模块			*/
/*==============================*/
void swdisplay(void);
#endif
