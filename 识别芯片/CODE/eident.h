/*------------------------------------------------------*/ 
/* 					   ͷ�ļ����� 						*/
/*======================================================*/
#ifndef _EIDENT_H
#define _EIDENT_H
//	����ͷ�ļ�
#include "data.h"
/*------------------------------------------------------*/ 
/* 						 �궨�� 						*/
/*======================================================*/
#define SAMPFRE 10
/*------------------------------------------------------*/ 
/* 						�������� 						*/
/*======================================================*/
void ccd_ident(void);
void eident_init(void);
void adc_jug(void);
void single_ch_filter(struct adcpara *para);
void adc_extreme(struct adcpara *para);
void adc_suminus(void);
#endif
