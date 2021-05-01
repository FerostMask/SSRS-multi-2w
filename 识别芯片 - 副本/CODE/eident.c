/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "Init.h"
#include "math.h"
#include "stdlib.h"
#include "menu_2.h"
#include "eident.h"
#include "zf_adc.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*----------------------*/
/*	   ���ʶ��ģ��		*/
/*======================*/
void adc_jug(void){
//	��������
	short mid_dif, out_dif;
	short oai_dif;
//	��ֵ����
	mid_dif = adc1.value*adc1.value - adc3.value*adc3.value;
	out_dif = adc0.value*adc0.value - adc4.value*adc4.value;
	oai_dif = adc0.value*adc0.value+adc4.value*adc4.value - adc1.value*adc1.value-adc3.value*adc3.value;
//	Ԫ��ʶ��
	if(abs(mid_dif) < 600)
		if(abs(out_dif) < 1800) ajug_sta = 0;
		else ajug_sta = 1;//���
	if(oai_dif > 15000) ajug_sta = 3;//����
	if(oai_dif < 1000) ajug_sta = 2;//ʮ��
//	adc_pfc[1]();
}
/*----------------------*/
/*	   	 ʮ��ֱ��		*/
/*======================*/
void cross_road(void){
	uart_putchar(UART_7, 0);
	spd_bias = 5;
}
/*----------------------*/
/*	   ��ȺͲ��㷨		*/
/*======================*/
void adc_suminus(void){
//	��������
	float divd, divs;
	short mid_val;
//	��ȺͲ��㷨
	mid_val = adc1.value - adc3.value;
	divd = adc_err.alpha*(float)(adc0.value - adc4.value) + adc_err.beta*(float)mid_val;
	divs = adc_err.alpha*(float)(adc0.value+adc4.value) + adc_err.omega*abs((float)mid_val);
	adc_err.rs = adc_err.P*divd/divs;
	if(adc_err.rs > 0) adc_err.rs = adc_err.rs*1.04;
//	PID���㡢���ݷ���
	pos_pid(&adc_steering, 0, -adc_err.rs, 60, -60);
//	���ݼ���
	if(csimenu_flag[1]){
		ips200_showint16(0, 0, adc0.value);
		ips200_showint16(0, 1, adc1.value);
		ips200_showint16(0, 2, adc2.value);
		ips200_showint16(0, 3, adc3.value);
		ips200_showint16(0, 4, adc4.value);
		ips200_showint16(0, 5, adc_convert(ADC_MOD1, ADC_PIN0));
		ips200_showint16(0, 6, adc_convert(ADC_MOD1, ADC_PIN1));
		ips200_showint16(0, 7, adc_convert(ADC_MOD1, ADC_PIN2));
		ips200_showint16(0, 8, adc_convert(ADC_MOD1, ADC_PIN3));
		ips200_showint16(0, 9, adc_convert(ADC_MOD1, ADC_PIN4));
		ips200_showstr(100, 0, "divd");
		ips200_showfloat(160, 0, divd, 4, 4);
		ips200_showstr(100, 1, "divs");
		ips200_showfloat(160, 1, divs, 4, 4);
		ips200_showstr(100, 2, "rs");
		ips200_showfloat(160, 2, adc_err.rs, 4, 3);
		ips200_showstr(100, 3, "pid");
		ips200_showfloat(160, 3, adc_steering.rs, 4, 3);
		ips200_showstr(100, 4, "a1");
		ips200_showfloat(160, 4, adc_err.alpha*(float)(adc0.value-adc4.value), 4, 4);
		ips200_showstr(100, 5, "b");
		ips200_showfloat(160, 5, adc_err.beta*(float)mid_val, 4, 4);
		ips200_showstr(100, 6, "a2");
		ips200_showfloat(160, 6, adc_err.alpha*(float)(adc0.value+adc4.value), 4, 4);
		ips200_showstr(100, 7, "c");
		ips200_showfloat(160, 7, adc_err.omega*abs((float)mid_val), 4, 4);
	}
}
/*----------------------*/
/*	    ��ͨ���˲�		*/
/*======================*/
void single_ch_filter(struct adcpara *para){
//	��������
	unsigned char i;
	register unsigned char j;
	unsigned short value[3];
	unsigned int sum_val = 0;
	unsigned char max_val, min_val;
//	��ֵ��ֵ�˲�
	for(i = 0; i < SAMPFRE; i++){
		//	����
			max_val = 0, min_val = 0;
		//	�ɼ���������
			for(j = 0; j < 3; j++)
				value[j] = adc_convert(ADC_MOD1, para->pin);
		//	�ж�����ֵ�Ƿ����
			if(value[0] == value[1])
				if(value[1] == value[2]){sum_val+= value[0];continue;}
		//	����ֵ
			for(j = 1; j < 3; j++){
				if(value[max_val] < value[j]) max_val = j;
				if(value[min_val] > value[j]) min_val = j;
			}
			sum_val += value[3-max_val-min_val];
		}
		para->value = (sum_val / SAMPFRE);
	//	�޷�
		if(para->value > para->max) para->value = para->max;
		if(para->value < para->min) para->value = para->min;
	//	��һ��
		para->value = 100*(para->value-para->min)/(para->max-para->min);
}
/*----------------------*/
/*	     �����ֵ		*/
/*======================*/
void adc_extreme(struct adcpara *para){
//	��������
	unsigned short adc_colltemp;
//	ADC�ɼ�����ֵ�Ƚ�
	adc_colltemp = adc_convert(ADC_MOD1, para->pin);
	if(para->max < adc_colltemp) para->max = adc_colltemp;
	if(para->min > adc_colltemp) para->min = adc_colltemp;
//	ˢ�¸�����ֵ
	ips200_pencolor = 0xFFFF;
	ips200_bgcolor = 0xB6DB;
	menu2value_hl();
	ips200_pencolor = 0xB6DB;
	ips200_bgcolor = 0xFFFF;
}
