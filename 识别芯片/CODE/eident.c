/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "eident.h"
#include "zf_adc.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*----------------------*/
/*	 	��ų�ʼ��		*/
/*======================*/
void eident_init(void){
//	������ų�ʼ�� | �ֱ��ʣ�12λ
	adc_init(ADC_MOD1, ADC_PIN0, ADC_12BIT);
	adc_init(ADC_MOD1, ADC_PIN1, ADC_12BIT);
	adc_init(ADC_MOD1, ADC_PIN2, ADC_12BIT);
	adc_init(ADC_MOD1, ADC_PIN3, ADC_12BIT);
	adc_init(ADC_MOD1, ADC_PIN4, ADC_12BIT);
//	���Ÿ�ֵ
	adc0.pin = ADC_PIN0;
	adc1.pin = ADC_PIN1;
	adc2.pin = ADC_PIN2;
	adc3.pin = ADC_PIN3;
	adc4.pin = ADC_PIN4;
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
		ips200_showint16(0, 0, para->value);
}
