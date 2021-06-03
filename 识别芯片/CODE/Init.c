/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "menu.h"
#include "Init.h"
#include "zf_adc.h"
#include "zf_tim.h"
#include "zf_gpio.h"
#include "zf_exti.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/*							  �궨��							*/
/*==============================================================*/
#define u8 unsigned char                                    //8λ����
#define u16 unsigned short                                  //16λ����
#define u32 unsigned int                                    //32λ����
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*------------------------------*/
/*		 ����ѡ��ģ��ģ��		*/
/*==============================*/
char core_select(void){
	gpio_init(KEY1, GPI, GPIO_LOW, GPI_FLOATING_IN);
	gpio_init(KEY2, GPI, GPIO_LOW, GPI_FLOATING_IN);
	gpio_init(KEY3, GPI, GPIO_LOW, GPI_FLOATING_IN);
	gpio_init(KEY4, GPI, GPIO_LOW, GPI_FLOATING_IN);
	gpio_init(KEY5, GPI, GPIO_LOW, GPI_FLOATING_IN);
	gpio_init(KEY6, GPI, GPIO_LOW, GPI_FLOATING_IN);
	ips200_showstr(0, 7, "< - Press Button to Continue");
	while(1){
	//	�˵�ѡ��
		if(!gpio_get(KEY1)){
			ips200_clear(0x00);
			return 0;
		}
		if(!gpio_get(KEY2)){
			ips200_clear(0x00);
			return 0;
		}
		if(!gpio_get(KEY3)) {action_flag = 0;return 1;}
	//	����ѡ��
		if(!gpio_get(KEY4)){
			ips200_showstr(90, 11, "==============");
			ips200_showstr(90, 12, "Select CODE: 0");
			ips200_showstr(90, 13, "==============");
			ctrl_pointer = 0;
		}
		if(!gpio_get(KEY5)){
			ips200_showstr(90, 11, "==============");
			ips200_showstr(90, 12, "Select CODE: 1");
			ips200_showstr(90, 13, "==============");
			ctrl_pointer = 1;
		}
		if(!gpio_get(KEY6)){
//			ips200_showstr(90, 11, "==============");
//			ips200_showstr(90, 12, "Select CODE: 2");
//			ips200_showstr(90, 13, "==============");
//			ctrl_pointer = 2;
		}
	}
}
/*------------------------------*/
/*		  ����ѡ���ʼ��		*/
/*==============================*/
void code_select(void){
//	��ʱ���ر�
	tim_interrupt_disabnle(TIM_2);
	tim_interrupt_disabnle(TIM_4);
	tim_interrupt_disabnle(TIM_5);
//	������ʱȷ��
	if(act_flag == 56 || act_flag == 55) systick_delay_ms(3000);
//	����ѡ��
	switch(ctrl_pointer){
		case 0:
			run_flag[2] = 1, run_flag[3] = 0;
			Init_para();
			tim_interrupt_init_ms(TIM_2, 25, 0, 0);
			break;
		case 1:
			run_flag[2] = 0, run_flag[3] = 1;
			Init_para_alter1();
			tim_interrupt_init_ms(TIM_4, 25, 0, 0);
			break;
		case 2:
			Init_para();
			tim_interrupt_init_ms(TIM_5, 25, 0, 0);
	}
}
/*------------------------------*/
/*		  ������ʼ��ģ��		*/
/*==============================*/
void Init_button(void){
//	�����жϳ�ʼ�� | ������ȼ�
	exti_interrupt_init(KEY1, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY2, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY3, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY4, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY5, EXTI_Trigger_Falling, 3, 3);
	exti_interrupt_init(KEY6, EXTI_Trigger_Falling, 3, 3);
}
/*------------------------------*/
/*		  ��ų�ʼ��ģ��		*/
/*==============================*/
void eident_init(void){
//	������ų�ʼ�� | �ֱ��ʣ�12λ
	adc_init(ADC_MOD1, ADC_PIN2, ADC_12BIT);
//	���Ÿ�ֵ
	adc2.pin = ADC_PIN2;
}
