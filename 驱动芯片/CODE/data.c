/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "data.h"
#include "zf_flash.h"
/*--------------------------------------------------------------*/
/*							  �궨��							*/
/*==============================================================*/
#define u8 unsigned char                                    //8λ����
#define u16 unsigned short                                  //16λ����
#define u32 unsigned int                                    //32λ����
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*----------------------*/
/*	     flash�洢		*/
/*======================*/
int flash_memory[256];
/*----------------------*/
/*	    ����CCDģ��		*/
/*======================*/
unsigned cjug_sta;
/*----------------------*/
/*	 	 MOTORģ��		*/
/*======================*/
//	������
short lcod = 0,rcod = 0;
short spd = 0;
short rad = 0;
short lef_pwm, rig_pwm;
//	PID
struct pidpara speed;
struct pidpara lefdif;
struct pidpara rigdif;
struct pidpara steer;
struct pidpara angle;
struct pidpara acw;
/*----------------------*/
/*	   �Ƕȿ���ģ��		*/
/*======================*/
int gy, gz;
short blcp;
short pita, yawa, yawa_temp;
short yfilt[4] = {0, 0, 0, 0};
short pflit[4] = {0, 0, 0, 0};
/*----------------------*/
/*	 	 �˵�ģ��		*/
/*======================*/
//	��������
unsigned char nom[128];
//	һ���˵�
unsigned char menu[ROWS];
unsigned char menu_level;
unsigned char menu_index = 0;
//	�����˵�
unsigned char menu2_index = 0;
unsigned char menu2_level = 0;
//	��־λ
unsigned char fixedflag = 0;//�̶���ʾ
unsigned char monitorflag = 0;//������
unsigned char csimenu_flag[CSIMENU_FLAG] = {0, 0};//����ͷ
unsigned char state_flag[STATE_FLAG] = {0, 0};//��������
//	����ָ��
void(*menu_pfc[])(unsigned char) = {menu_select, menu2_select};
/*----------------------*/
/*	 	 ͨ��ģ��		*/
/*======================*/
unsigned char buff_get6, buff_get7;
unsigned char dst_flag = 0, final_flag = 0;
unsigned char launch_command[3] = {0xA7, 0xB9, 0x12};
int distance = 0;
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
/*----------------------*/
/*	 	������ʼ��		*/
/*======================*/
//	PID
void Init_para(void){
//	��������
	blcp = 332;//ƽ���
	
//	ת��
	steer.Kp = 0.6;//��Ӧ���� | ����
	steer.Kd = 0.2;
	
//	���ֲ���
	lefdif.alpha = 0.3;
	lefdif.Kp = 30;//��Ӧ���� | ����
	lefdif.Ki = 1.2;//��Ӧ����
	lefdif.Kd = 0;

//	���ֲ���
	rigdif.alpha = 0.3;
	rigdif.Kp = 30;//��Ӧ���� | ����
	rigdif.Ki = 1.1;//��Ӧ����
	rigdif.Kd = 0;
	
//	�ٶ�
	speed.Kp = 1.1;//��Ӧ���� | ����
	speed.Kd = 0.3;	
	
//	�Ƕ�
	angle.Kp = 1.9;//����
	angle.Kd = 0.09;//����

//	���ٶ�
	acw.alpha = 0.02;
	acw.Kp = 27;//��Ӧ���� | ����
	acw.Ki = 0.32;//��Ӧ����
	acw.Kd = 0.0;
}
/*----------------------*/
/*	 flash������ʼ��	*/
/*======================*/
char flash_init(void){
//	ȷ���Ƿ�����ǰ����Ĳ���
	if(!(flash_check(FLASH_MEMORY_SLECTION, FLASH_PAGE_0))) return 1;
//	��ȡ�����ò���
	flash_page_read(FLASH_MEMORY_SLECTION, FLASH_PAGE_0, flash_memory, FLASH_NUM);
//	ת��
	steer.Kp = (float)flash_memory[0]/1000;
	steer.Kd = (float)flash_memory[1]/1000;
//	���ֲ���
	lefdif.alpha = (float)flash_memory[2]/1000;
	lefdif.Kp = (float)flash_memory[3]/1000;
	lefdif.Ki = (float)flash_memory[4]/1000;
	lefdif.Kd = (float)flash_memory[5]/1000;
//	���ֲ���
	rigdif.alpha = (float)flash_memory[6]/1000;
	rigdif.Kp = (float)flash_memory[7]/1000;
	rigdif.Ki = (float)flash_memory[8]/1000;
	rigdif.Kd = (float)flash_memory[9]/1000;
//	�ٶ�
	speed.Kp = (float)flash_memory[10]/1000;
	speed.Kd = (float)flash_memory[11]/1000;	
//	�Ƕ�
	angle.Kp = (float)flash_memory[12]/1000;
	angle.Kd = (float)flash_memory[13]/1000;
//	���ٶ�
	acw.alpha = (float)flash_memory[14]/1000;
	acw.Kp = (float)flash_memory[15]/1000;
	acw.Ki = (float)flash_memory[16]/1000;
	acw.Kd = (float)flash_memory[17]/1000;
//	��������
	blcp = (float)flash_memory[18]/1000;
	return 0;
}
/*----------------------*/
/*	  ���β�����ʼ��	*/
/*======================*/
void first_flash_init(void){
//	ת��
	flash_memory[0] = steer.Kp*1000;
	flash_memory[1] = steer.Kd*1000;
//	���ֲ���
	flash_memory[2] = lefdif.alpha*1000;
	flash_memory[3] = lefdif.Kp*1000;
	flash_memory[4] = lefdif.Ki*1000;
	flash_memory[5] = lefdif.Kd*1000;
//	���ֲ���
	flash_memory[6] = rigdif.alpha*1000;
	flash_memory[7] = rigdif.Kp*1000;
	flash_memory[8] = rigdif.Ki*1000;
	flash_memory[9] = rigdif.Kd*1000;
//	�ٶ�
	flash_memory[10] = speed.Kp*1000;
	flash_memory[11] = speed.Kd*1000;	
//	�Ƕ�
	flash_memory[12] = angle.Kp*1000;
	flash_memory[13] = angle.Kd*1000;
//	���ٶ�
	flash_memory[14] = acw.alpha*1000;
	flash_memory[15] = acw.Kp*1000;
	flash_memory[16] = acw.Ki*1000;
	flash_memory[17] = acw.Kd*1000;
//	��������
	flash_memory[18] = blcp*1000;
//	������д��
	flash_erase_page(FLASH_MEMORY_SLECTION, FLASH_PAGE_0);
	flash_page_program(FLASH_MEMORY_SLECTION, FLASH_PAGE_0, flash_memory, FLASH_NUM);
}
/*----------------------*/
/*	  flash����д�� 	*/
/*======================*/
void flash_memory_write(row, col){
//	��ѡ��
	switch(row){
	//	��ѡ��
		case PARASET_PID1:
			switch(col){
				case 0:
					flash_memory[10] = speed.Kp*1000;
					flash_memory[11] = speed.Kd*1000;	
					break;
				case 1:
					flash_memory[12] = angle.Kp*1000;
					flash_memory[13] = angle.Kd*1000;
					break;
				case 2:
					flash_memory[14] = acw.alpha*1000;
					flash_memory[15] = acw.Kp*1000;
					flash_memory[16] = acw.Ki*1000;
					flash_memory[17] = acw.Kd*1000;
					break;
			}
			break;
		case PARASET_PID2:
			switch(col){
				case 0:
					flash_memory[0] = steer.Kp*1000;
					flash_memory[1] = steer.Kd*1000;
					break;
				case 1:
					flash_memory[2] = lefdif.alpha*1000;
					flash_memory[3] = lefdif.Kp*1000;
					flash_memory[4] = lefdif.Ki*1000;
					flash_memory[5] = lefdif.Kd*1000;
					break;
				case 2:
					flash_memory[6] = rigdif.alpha*1000;
					flash_memory[7] = rigdif.Kp*1000;
					flash_memory[8] = rigdif.Ki*1000;
					flash_memory[9] = rigdif.Kd*1000;
					break;
			}
			break;
		case PARASET_OPER:
			switch(col){
				case 0:
					flash_memory[18] = blcp*1000;
					break;
			}
			break;
	}
//	������д��
	flash_erase_page(FLASH_MEMORY_SLECTION, FLASH_PAGE_0);
	flash_page_program(FLASH_MEMORY_SLECTION, FLASH_PAGE_0, flash_memory, FLASH_NUM);
}
