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
#define ADC_MOD1 ADC2
#define ADC_PIN0 ADC2_CH04_A04
#define ADC_PIN1 ADC2_CH05_A05
#define ADC_PIN3 ADC2_CH06_A06
#define ADC_PIN4 ADC2_CH07_A07
#define ADC_PIN2 ADC2_CH10_C00

#define SAMPFRE 10
/*------------------------------------------------------*/ 
/* 						�������� 						*/
/*======================================================*/
void eident_init(void);
void single_ch_filter(struct adcpara *para);
#endif
