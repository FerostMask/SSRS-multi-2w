/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "Init.h"
#include "math.h"
#include "stdlib.h"
#include "menu_2.h"
#include "eident.h"
#include "zf_adc.h"
#include "SEEKFREE_TSL1401.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*----------------------*/
/*	    ����CCDģ��		*/
/*======================*/
void ccd_ident(void){
//	��������
	register unsigned char i;
	unsigned char border[2];
	unsigned char bo_num = 0, mp;
//	�����ʶ��
	for(i = 0; i < 127; i++)
		if(ccd_data[0][i+1]- ccd_data[0][i] > 800){
			border[bo_num] = i;
			bo_num++;
			if(bo_num == 2){
				mp = (border[0]+border[1])>>1;
				ips200_showint16(0, 0, mp);
				return;
			}
		}
}
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
		if(abs(out_dif) < 1800)	ajug_sta = 0;//ֱ��
		else ajug_sta = 1;//���
	if(oai_dif > 15000) ajug_sta = 3;//����
	if(oai_dif < 1000) ajug_sta = 2;//ʮ��
}
/*----------------------*/
/*	   ��ȺͲ��㷨		*/
/*======================*/
void adc_suminus(void){
//	��������
	float divd, divs, mid_val;
//	��ȺͲ��㷨
	mid_val = adc1.value - adc3.value;
	divd = adc_err.alpha*(float)(adc0.value-adc4.value) + adc_err.beta*(float)mid_val;
	divs = adc_err.alpha*(float)(adc0.value+adc4.value) + adc_err.omega*abs((float)mid_val);
	adc_err.rs = adc_err.P*divd/divs;
	pos_pid(&adc_steering, 0, adc_err.rs, 30, -30);

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
