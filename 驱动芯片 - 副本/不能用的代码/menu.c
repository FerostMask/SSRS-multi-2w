/*--------------------------------------------------------------*/
/*							ͷ�ļ�����							*/
/*==============================================================*/
#include "data.h"
#include "menu.h"
#include "zf_pit.h"
#include "SEEKFREE_IPS200_PARALLEL8.h"
/*--------------------------------------------------------------*/
/*							  �궨��							*/
/*==============================================================*/

/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/
//	һ���˵�
unsigned char menu_col = 0;
//	�����˵�
unsigned char menu2flag;
unsigned char menu2_mode;
unsigned char menu2_index;
unsigned char menu2_limit;
//	������
unsigned char fixed_index;
unsigned char fixed_flag;
//	��ֵ�޸�
unsigned char magflag = 1;
unsigned char magindex = 1;
float mag[] = {10,1,0.1,0.01,0.001};
short *shortvalue0, *shortvalue1, *shortvalue2;
float *value0, *value1, *value2, *value3, *value4;
/*--------------------------------------------------------------*/
/* 							 �������� 							*/
/*==============================================================*/

//----------------------------�ָ���----------------------------//
/*--------------------------------------------------------------*/
/* 							 ��Ϣ�洢 							*/
/*==============================================================*/
static char info(char index, char num){
//	�����б�-> index:�˵������� | num:��ֵ����
//	��������
	register unsigned char i;
//	������ģ
	unsigned char cai0[] = {0x08,0x20,0x08,0x20,0xFF,0xFE,0x08,0x20,0x00,0x10,0x00,0xF8,0x3F,0x00,0x11,0x10,0x08,0x20,0x01,0x00,0x7F,0xFC,0x05,0x40,0x09,0x20,0x31,0x18,0xC1,0x06,0x01,0x00};/*"��",0*/
	unsigned char dan0[] = {0x10,0x10,0x08,0x20,0x04,0x40,0x3F,0xF8,0x21,0x08,0x21,0x08,0x3F,0xF8,0x21,0x08,0x21,0x08,0x3F,0xF8,0x01,0x00,0x01,0x00,0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00};//��
	unsigned char jiao0[] = {0x00,0x00,0x04,0x00,0x0F,0xF0,0x10,0x10,0x30,0x20,0x5F,0xFC,0x20,0x84,0x20,0x84,0x3F,0xFC,0x20,0x84,0x20,0x84,0x20,0x84,0x3F,0xFC,0x20,0x84,0x20,0x84,0x40,0xBC};/*"��"*/
	unsigned char su0[] = {0x00,0x00,0x00,0x00,0x20,0x40,0x27,0xFE,0x10,0x40,0x07,0xFC,0x04,0x44,0x74,0x44,0x14,0x44,0x13,0xF8,0x10,0xF0,0x11,0x58,0x12,0x4C,0x1C,0x46,0x28,0x40,0x46,0xFE};/*"��"*/
	unsigned char du0[] = {0x00,0x00,0x00,0x00,0x00,0x80,0x3F,0xFE,0x44,0x10,0x5F,0xFC,0x44,0x10,0x44,0x10,0x43,0xF0,0x40,0x00,0x5F,0xF8,0x44,0x08,0x42,0x30,0x41,0xC0,0x43,0x60,0xBC,0x1E};/*"��"*/
	unsigned char zhuan0[] = {0x00,0x00,0x00,0x20,0x10,0x20,0x7E,0x20,0x21,0xFE,0x20,0x40,0x40,0x40,0x51,0xFE,0x50,0x40,0x7C,0x40,0x10,0x7E,0x10,0x04,0x3C,0x04,0x10,0x08,0x10,0x70,0x00,0x0E};/*"ת"*/
	unsigned char xiang0[] = {0x00,0x00,0x01,0x00,0x01,0x00,0x1F,0xF8,0x20,0x06,0x20,0x02,0x27,0xE2,0x28,0x12,0x28,0x12,0x28,0x12,0x28,0x12,0x28,0x12,0x28,0x12,0x27,0xE2,0x20,0x02,0x20,0x1C};/*"��",0*/
	unsigned char zi0[] = {0x00,0x00,0x00,0x00,0x62,0x00,0x13,0xFC,0x04,0x84,0x08,0xC8,0x0D,0x20,0x33,0x10,0x4D,0x0E,0x01,0x00,0x7F,0xFE,0x04,0x20,0x08,0x20,0x07,0x40,0x01,0xF0,0x7E,0x0E};/*"��",0*/
	unsigned char tai0[] = {0x00,0x00,0x00,0x00,0x01,0x00,0x7F,0xFE,0x01,0x80,0x02,0x40,0x05,0x20,0x19,0x18,0xE0,0x86,0x00,0x00,0x24,0x88,0x24,0x84,0x24,0x54,0x24,0x52,0x44,0x12,0x47,0xF0};/*"̬",1*/
	unsigned char jian0[] = {0x00,0x00,0x00,0x00,0x04,0x80,0x24,0xFE,0x24,0x80,0x25,0x00,0x25,0x20,0x26,0x10,0x04,0x08,0x00,0x00,0x3F,0xFC,0x24,0x44,0x24,0x44,0x24,0x44,0x24,0x44,0x7F,0xFE};/*"��"*/
	unsigned char shi0[] = {0x00,0x00,0x00,0x00,0x11,0xFC,0x11,0x04,0x79,0x24,0x09,0x24,0x09,0x24,0x11,0x24,0x19,0x24,0x35,0x34,0x51,0x30,0x10,0x50,0x10,0x50,0x10,0x92,0x11,0x12,0x16,0x1E};/*"��"*/
	unsigned char qi0[] = {0x00,0x00,0x00,0x00,0x3E,0x7C,0x22,0x84,0x22,0x84,0x3E,0x7C,0x01,0x10,0x7F,0xFE,0x04,0x40,0x08,0x30,0x70,0x0E,0x3E,0x7C,0x22,0x84,0x22,0x84,0x22,0x84,0x3E,0x7C};/*"��"*/
	unsigned char tu0[] = {0x00,0x00,0x00,0x00,0x3F,0xFE,0x44,0x02,0x47,0xF2,0x4C,0x22,0x53,0x62,0x40,0x82,0x43,0x62,0x5E,0x1A,0x41,0x82,0x40,0x62,0x43,0x02,0x40,0xC2,0x40,0x22,0x3F,0xFC};/*"ͼ"*/
	unsigned char xian0[] = {0x00,0x00,0x00,0x00,0x3F,0xFC,0x20,0x04,0x20,0x04,0x3F,0xFC,0x20,0x04,0x20,0x04,0x1F,0xF8,0x24,0x44,0x14,0x48,0x14,0x48,0x14,0x48,0x0C,0x50,0x04,0x40,0x7F,0xFE};/*"��"*/
	unsigned char shi1[] = {0x00,0x00,0x00,0x00,0x3F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,0xFE,0x00,0x80,0x08,0x90,0x08,0x88,0x10,0x88,0x10,0x84,0x20,0x84,0x20,0x82,0x40,0x82,0x07,0x80};/*"ʾ"*/
	unsigned char ju0[] = {0x00,0x00,0x10,0x00,0x11,0xFE,0x11,0x02,0x7D,0x02,0x11,0xFC,0x11,0x10,0x11,0xFE,0x15,0x10,0x1A,0x10,0x72,0x7C,0x12,0x82,0x12,0x82,0x12,0x82,0x14,0x82,0x74,0xFE};/*"��"*/
	unsigned char fa0[] = {0x00,0x00,0x01,0x00,0x11,0x30,0x21,0x08,0x22,0x00,0x3F,0xFE,0x02,0x00,0x02,0x00,0x07,0xFC,0x05,0x08,0x08,0x88,0x08,0x90,0x10,0x60,0x20,0x60,0x41,0x98,0x0E,0x06};/*"��"*/
	unsigned char song0[] = {0x00,0x00,0x00,0x00,0x22,0x04,0x21,0x08,0x10,0x90,0x03,0xFC,0x60,0x40,0x10,0x40,0x17,0xFE,0x10,0x40,0x10,0x40,0x10,0xB0,0x11,0x08,0x12,0x04,0x2C,0x00,0x47,0xFE};/*"��"*/
	unsigned char can0[] = {0x00,0x00,0x02,0x00,0x04,0x20,0x08,0x10,0x3F,0xF8,0x01,0x08,0x7F,0xFE,0x02,0x40,0x04,0x20,0x08,0x98,0xF3,0x07,0x0C,0x20,0x00,0xCC,0x1F,0x18,0x00,0x60,0x1F,0x80};/*"��"*/
	unsigned char shu0[] = {0x00,0x00,0x00,0x00,0x25,0x20,0x25,0x20,0x26,0x3E,0x7F,0xA4,0x0E,0x64,0x35,0x64,0x44,0x24,0x08,0x24,0x7F,0x18,0x11,0x18,0x21,0x18,0x1A,0x14,0x06,0x24,0x79,0xC2};/*"��"*/
	unsigned char ming0[] = {0x00,0x00,0x00,0x00,0x02,0x00,0x07,0xF8,0x18,0x08,0x28,0x08,0x46,0x10,0x01,0x20,0x00,0xC0,0x0F,0xFC,0xF8,0x02,0x08,0x02,0x08,0x02,0x08,0x02,0x08,0x02,0x0F,0xFE};/*"��"*/
	unsigned char zhi0[] = {0x00,0x00,0x10,0x40,0x10,0x40,0x2F,0xFE,0x20,0x40,0x20,0x40,0x23,0xFC,0x64,0x04,0x63,0xFC,0xA4,0x04,0x23,0xFC,0x24,0x04,0x23,0xFC,0x24,0x04,0x24,0x04,0x2F,0xFE};/*"ֵ"*/
	unsigned char ping0[] = {0x00,0x00,0x00,0x00,0x1F,0xFC,0x21,0x00,0x21,0x04,0x11,0x04,0x09,0x08,0x09,0x10,0x05,0x20,0x01,0x00,0x7F,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x00,0x00};/*"ƽ"*/
	unsigned char heng0[] = {0x00,0x00,0x00,0x00,0x17,0xCE,0x28,0x40,0x48,0x80,0x4F,0xE0,0x19,0x3F,0x29,0x24,0x2F,0xE4,0x69,0x24,0x2F,0xE4,0x21,0x04,0x3F,0xF4,0x22,0x84,0x26,0x44,0x28,0x1C};/*"��"*/
	unsigned char dian0[] = {0x00,0x00,0x00,0x00,0x02,0x00,0x01,0xFE,0x02,0x00,0x02,0x00,0x3F,0xF8,0x20,0x08,0x20,0x08,0x20,0x08,0x20,0x08,0x3F,0xF8,0x24,0x44,0x24,0x44,0x22,0x22,0x42,0x22};/*"��"*/
	unsigned char fu0[] = {0x00,0x00,0x10,0x40,0x10,0x40,0x27,0xFE,0x24,0x84,0x24,0x84,0x25,0x7E,0x65,0x04,0x65,0x44,0x27,0x24,0x27,0x24,0x29,0x14,0x29,0x14,0x29,0x04,0x29,0x04,0x29,0x3C};/*"��"*/
	unsigned char yang0[] = {0x00,0x00,0x10,0x80,0x13,0x3C,0x24,0x42,0x24,0x42,0x24,0x42,0x24,0x42,0x64,0x42,0x64,0x42,0xA4,0x42,0x24,0x42,0x24,0x42,0x24,0xC2,0x25,0x44,0x22,0x5C,0x20,0x00};/*"��"*/
	unsigned char hang0[] = {0x00,0x00,0x08,0x20,0x08,0x20,0x3D,0xFE,0x32,0x00,0x32,0x00,0x2A,0xF8,0x2A,0x88,0x22,0x88,0xFE,0x88,0x32,0x88,0x52,0x88,0x4A,0x8A,0x4A,0x8A,0x4B,0x0A,0x53,0x0E};/*"��"*/
	unsigned char zuo0[] = {0x00,0x00,0x01,0x00,0x01,0x00,0x02,0x00,0x7F,0xFE,0x02,0x00,0x04,0x00,0x04,0x00,0x0F,0xFC,0x10,0x40,0x20,0x40,0x40,0x40,0x00,0x40,0x00,0x40,0x00,0x40,0x3F,0xFE};/*"��"*/
	unsigned char you0[] = {0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x7F,0xFE,0x02,0x00,0x04,0x00,0x08,0x00,0x1F,0xF8,0x30,0x04,0x70,0x04,0x90,0x04,0x10,0x04,0x10,0x04,0x10,0x04,0x0F,0xF8};/*"��"*/
	unsigned char lun0[] = {0x00,0x00,0x00,0x00,0x10,0x30,0x10,0x58,0x7E,0x88,0x29,0x06,0x2A,0x01,0x48,0x80,0x7E,0x84,0x08,0x98,0x08,0xA0,0x08,0xC2,0x7F,0x82,0x08,0x82,0x08,0x82,0x08,0x7C};/*"��"*/
	unsigned char zhuang0[] = {0x00,0x00,0x08,0x00,0x08,0x48,0x08,0x48,0x48,0x44,0x2B,0xFE,0x18,0x40,0x08,0x60,0x08,0x60,0x18,0x50,0x18,0x50,0x28,0x90,0x48,0x88,0xC9,0x04,0x0A,0x04,0x0A,0x02};/*"״"*/
	unsigned char gong0[] = {0x00,0x00,0x00,0x20,0x00,0x20,0x7C,0x20,0x13,0xFE,0x10,0x22,0x10,0x42,0x10,0x42,0x10,0x42,0x10,0x42,0x10,0x82,0x10,0x82,0x17,0x02,0x19,0x02,0x62,0x04,0x0C,0x7C};/*"��"*/
	unsigned char neng0[] = {0x00,0x00,0x10,0x00,0x10,0x40,0x22,0x44,0x21,0x78,0x7F,0x40,0x00,0xC2,0x3F,0x42,0x41,0x3C,0x7F,0x40,0x41,0x46,0x41,0x78,0x7F,0x40,0x41,0x42,0x41,0x42,0x4F,0x7E};/*"��"*/
	unsigned char kai0[] = {0x00,0x00,0x00,0x00,0x3F,0xFC,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x7F,0xFE,0x08,0x10,0x08,0x10,0x08,0x10,0x08,0x10,0x10,0x10,0x10,0x10,0x20,0x10};/*"��"*/
	unsigned char guan0[] = {0x00,0x00,0x00,0x00,0x08,0x10,0x04,0x20,0x3F,0xFC,0x01,0x00,0x01,0x00,0x01,0x00,0x7F,0xFE,0x01,0x80,0x01,0x80,0x02,0x40,0x02,0x20,0x0C,0x10,0x10,0x08,0x60,0x06};/*"��"*/
	unsigned char cai1[] = {0x00,0x00,0x00,0x00,0x07,0x08,0x78,0x88,0x49,0x10,0x29,0x60,0x2E,0x04,0x08,0x08,0x7F,0x10,0x0C,0x20,0x1C,0xC2,0x1A,0x04,0x29,0x08,0x48,0x10,0x08,0x60,0x09,0x80};/*"��",1*/
	unsigned char se0[] = {0x00,0x00,0x00,0x00,0x04,0x00,0x0F,0xF0,0x10,0x20,0x20,0x20,0x7F,0xFC,0x20,0x84,0x20,0x84,0x20,0x84,0x20,0x84,0x3F,0xF8,0x20,0x00,0x20,0x02,0x20,0x02,0x1F,0xFE};/*"ɫ"*/
	unsigned char hui0[] = {0x00,0x00,0x08,0x00,0x08,0x00,0x7F,0xFE,0x08,0x40,0x08,0x40,0x0A,0x48,0x0A,0x48,0x12,0x48,0x12,0x50,0x10,0x50,0x20,0xA0,0x20,0xA0,0x43,0x10,0x44,0x0C,0x18,0x02};/*"��"*/
	unsigned char xiang1[] = {0x00,0x00,0x10,0x80,0x11,0xF0,0x1E,0x10,0x23,0xF8,0x2C,0x46,0x28,0x42,0x67,0xFA,0x60,0x84,0x23,0x46,0x2C,0xB8,0x23,0x20,0x2C,0xF0,0x23,0x28,0x2C,0x26,0x23,0x40};/*"��",1*/
	unsigned char state0[] = {0x00,0x00,0x00,0x00,0x7F,0xFF,0x40,0x01,0x40,0x01,0x40,0x01,0x40,0x01,0x40,0x01,0x40,0x01,0x40,0x01,0x40,0x01,0x40,0x01,0x40,0x01,0x40,0x01,0x40,0x01,0x7F,0xFF};/*"��"*/
	unsigned char state1[] = {0x00,0x00,0x00,0x00,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF,0x7F,0xFF};/*"��"*/
	unsigned char xiang2[] = {0x00,0x00,0x00,0x00,0x10,0xFE,0x11,0x02,0x11,0x02,0x7F,0x02,0x19,0xFE,0x15,0x02,0x35,0x02,0x33,0x02,0x51,0xFE,0x51,0x02,0x11,0x02,0x11,0x02,0x11,0x02,0x00,0xFC};/*"��"*/
	unsigned char block0[] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};/*"��"*/
/*------------------------------*/
/*		   	�����˵�			*/
/*==============================*/
	if(menu_level){
		switch(index){
			case 0:
				switch(num){
					case 0://��ɫͼ��
						for(i = 0; i < 32; i++) nom[i] = cai1[i];
						for(i = 0; i < 32; i++) nom[32+i] = se0[i];
						for(i = 0; i < 32; i++) nom[64+i] = tu0[i];
						for(i = 0; i < 32; i++) nom[96+i] = xiang1[i];
						return 4;
					case 1://�Ҷ�ͼ��
						for(i = 0; i < 32; i++) nom[i] = hui0[i];
						for(i = 0; i < 32; i++) nom[32+i] = du0[i];
						for(i = 0; i < 32; i++) nom[64+i] = tu0[i];
						for(i = 0; i < 32; i++) nom[96+i] = xiang1[i];
						return 4;
					case 2://ƽ�����
						for(i = 0; i < 32; i++) nom[i] = ping0[i];
						for(i = 0; i < 32; i++) nom[32+i] = heng0[i];
						for(i = 0; i < 32; i++) nom[64+i] = xiang2[i];
						for(i = 0; i < 32; i++) nom[96+i] = guan0[i];
						return 4;
					case 3://ת�����
						for(i = 0; i < 32; i++) nom[i] = zhuan0[i];
						for(i = 0; i < 32; i++) nom[32+i] = su0[i];
						for(i = 0; i < 32; i++) nom[64+i] = xiang2[i];
						for(i = 0; i < 32; i++) nom[96+i] = guan0[i];
						return 4;
					
				}
			case 1:
				switch(num){
					case 0://������
						for(i = 0; i < 32; i++) nom[i] = can0[i];
						for(i = 0; i < 32; i++) nom[32+i] = shu0[i];
						for(i = 0; i < 32; i++) nom[64+i] = ming0[i];
						return 3;
					case 1://����ֵ
						for(i = 0; i < 32; i++) nom[i] = can0[i];
						for(i = 0; i < 32; i++) nom[32+i] = shu0[i];
						for(i = 0; i < 32; i++) nom[64+i] = zhi0[i];
						return 3;
				}
				break;
			case 2:
				switch(num){
					case 0://ת��
						for(i = 0; i < 32; i++) nom[i] = zhuan0[i];
						for(i = 0; i < 32; i++) nom[32+i] = su0[i];
						return 2;
					case 1://ת���
						for(i = 0; i < 32; i++) nom[i] = zhuan0[i];
						for(i = 0; i < 32; i++) nom[32+i] = xiang0[i];
						for(i = 0; i < 32; i++) nom[64+i] = jiao0[i];
						return 3;
					case 2://ƽ���
						for(i = 0; i < 32; i++) nom[i] = ping0[i];
						for(i = 0; i < 32; i++) nom[32+i] = heng0[i];
						for(i = 0; i < 32; i++) nom[64+i] = dian0[i];
						return 3;
				}
			case 3:
				switch(num){
					case 0://������
						for(i = 0; i < 32; i++) nom[i] = fu0[i];
						for(i = 0; i < 32; i++) nom[32+i] = yang0[i];
						for(i = 0; i < 32; i++) nom[64+i] = jiao0[i];
						return 3;
					case 1://�����
						for(i = 0; i < 32; i++) nom[i] = hang0[i];
						for(i = 0; i < 32; i++) nom[32+i] = xiang0[i];
						for(i = 0; i < 32; i++) nom[64+i] = jiao0[i];
						return 3;
					case 2://����ת��
						for(i = 0; i < 32; i++) nom[i] = zuo0[i];
						for(i = 0; i < 32; i++) nom[32+i] = lun0[i];
						for(i = 0; i < 32; i++) nom[64+i] = zhuan0[i];
						for(i = 0; i < 32; i++) nom[96+i] = su0[i];
						return 4;
					case 3://����ת��
						for(i = 0; i < 32; i++) nom[i] = you0[i];
						for(i = 0; i < 32; i++) nom[32+i] = lun0[i];
						for(i = 0; i < 32; i++) nom[64+i] = zhuan0[i];
						for(i = 0; i < 32; i++) nom[96+i] = su0[i];
						return 4;
				}
			case 100://������Ϣ
				switch(menu2_index){//������
					case 0:
						switch(num){
							case 0://����
								for(i = 0; i < 32; i++) nom[i] = gong0[i];
								for(i = 0; i < 32; i++) nom[32+i] = neng0[i];
								return 2;
							case 1://״̬
								for(i = 0; i < 32; i++) nom[i] = zhuang0[i];
								for(i = 0; i < 32; i++) nom[32+i] = tai0[i];
								return 2;
							case 2://��
								for(i = 0; i < 32; i++) nom[i] = kai0[i];
								return 1;
							case 3://��
								for(i = 0; i < 32; i++) nom[i] = guan0[i];
								return 1;
							case 4:
								for(i = 0; i < 32; i++) nom[i] = state1[i];
								return 1;
								break;
							case 5:
								for(i = 0; i < 32; i++) nom[i] = state0[i];
								return 1;
								break;
						}
				}
		}
	}
/*-------------------*/
/*	   һ���˵�		 */
/*===================*/
	else{
	//	������
		switch(index){
			case 0:
			//	������
				switch(num){
					case 0://ͼ����ʾ
						for(i = 0; i < 32; i++) nom[i] = tu0[i];
						for(i = 0; i < 32; i++) nom[32+i] = xiang1[i];
						for(i = 0; i < 32; i++) nom[64+i] = xian0[i];
						for(i = 0; i < 32; i++) nom[96+i] = shi1[i];
						return 4;
					case 1://���ݷ���
						for(i = 0; i < 32; i++) nom[i] = shu0[i];
						for(i = 0; i < 32; i++) nom[32+i] = ju0[i];
						for(i = 0; i < 32; i++) nom[64+i] = fa0[i];
						for(i = 0; i < 32; i++) nom[96+i] = song0[i];
						return 4;
				}
				break;
			case 1:
				switch(num){
					case 0://���ٶ�
						for(i = 0; i < 32; i++) nom[i] = jiao0[i];
						for(i = 0; i < 32; i++) nom[32+i] = su0[i];
						for(i = 0; i < 32; i++) nom[64+i] = du0[i];
						return 3;
					case 1://�Ƕ�
						for(i = 0; i < 32; i++) nom[i] = jiao0[i];
						for(i = 0; i < 32; i++) nom[32+i] = du0[i];
						return 2;
					case 2://�ٶ�
						for(i = 0; i < 32; i++) nom[i] = su0[i];
						for(i = 0; i < 32; i++) nom[32+i] = du0[i];
						return 2;
					case 3://ת��
						for(i = 0; i < 32; i++) nom[i] = zhuan0[i];
						for(i = 0; i < 32; i++) nom[32+i] = xiang0[i];
						return 2;
				}
				break;
			case 2:
				switch(num){
					case 0://��̬
						for(i = 0; i < 32; i++) nom[i] = zi0[i];
						for(i = 0; i < 32; i++) nom[32+i] = tai0[i];
						return 2;
				}
				break;
			case 3:
				switch(num){
					case 0://������
						for(i = 0; i < 32; i++) nom[i] = jian0[i];
						for(i = 0; i < 32; i++) nom[32+i] = shi0[i];
						for(i = 0; i < 32; i++) nom[64+i] = qi0[i];
						return 3;
				}
				break;
			case 100://������Ϣģ�� | �˵�
				switch(num){
					case 0:
						break;
					case 1:
						for(i = 0; i < 32; i++) nom[i] = cai0[i];
						for(i = 0; i < 32; i++) nom[32+i] = dan0[i];
						return 2;
				}
			}
	}
	return 0;
}
//----------------------------�ָ���----------------------------//
/*--------------------------------------------------------------*/
/* 							 �����˵� 							*/
/*==============================================================*/
/*------------------------------*/
/*		 �����˵���ʼ��ģ��		*/
/*==============================*/
void menu2_init(void){
//	��ʼ����ֵ
	menu2flag = 1;
	menu2_index = 0;
	magflag = 1;
	menu_col = menu[menu_index];
//	��ʼ��ģ��
	switch(menu_index){
		case 0:
			magflag = 0;
			menu2flag = 3;//�л�Ϊ����
			switch(menu[menu_index]){
				case 0:
					menu2_mode = 0;//��ʾģʽ
					menu2_limit = CSIMENU_FLAG-1;//��������
					break;
				case 1:
					menu2_mode = 1;//��ʾģʽ
					menu2_limit = WIRELESS_FLAG-1;//��������
					break;
			}
			break;
		case 1:
		//	�رսǶȿ���
			acw.rs = 0;
			steer.rs = 0;
			motor_act();
			tim_interrupt_disabnle(TIM_2);
			switch(menu[menu_index]){
				case 0://���ٶ�
					value0 = &acw.alpha;
					value1 = &acw.Kp;
					value2 = &acw.Ki;
					value3 = &acw.Kd;
					menu2_limit = 3;
					menu2_mode = 0;
					break;
				case 1://�Ƕ�
					value0 = &angle.Kp;
					value1 = &angle.Kd;
					menu2_limit = 1;
					menu2_mode = 1;
					break;
				case 2://�ٶ�
					value0 = &speed.alpha;
					value1 = &speed.Kp;
					value2 = &speed.Ki;
					value3 = &speed.Kd;
					menu2_limit = 3;
					menu2_mode = 0;
					break;
				case 3://ת��
					value0 = &steer.alpha;
					value1 = &steer.Kp;
					value2 = &steer.Ki;
					value3 = &steer.Kd;
					menu2_limit = 3;
					menu2_mode = 0;
					break;
			}
			break;
		case 2://��̬
			acw.rs = 0;
			steer.rs = 0;
			motor_act();
			tim_interrupt_disabnle(TIM_2);
			switch(menu[menu_index]){
				case 0:
					shortvalue0 = &spd;
					shortvalue1 = &rad;
					shortvalue2 = &blcp;
					menu2_limit = 2;
					menu2_mode = 0;
					break;
			}
			break;
		case 3://������
		//	�����ж���ʾ
//			pit_interrupt_ms(PIT_CH2,40);
			magflag = 0;
			menu2flag = 2;
//			monitorflag = 1;
			break;
	}
}
/*------------------------------*/
/*		   ��ֵ��ʾģ��			*/
/*==============================*/
static void menu2value(unsigned char menu_level){
//	��ʾ����
	if(magflag) ips200_showfloat(180, 14, mag[magindex], 2, 3);
//	��ʾ��ֵ
	switch(menu_index){
		case 0:
			swdisplay();
			break;
		case 1:
			switch(menu2_mode){
				case 0:
					ips200_showfloat(120, 15, *value0, 2, 3);
					ips200_showfloat(120, 16, *value1, 2, 3);
					ips200_showfloat(120, 17, *value2, 2, 3);
					ips200_showfloat(120, 18, *value3, 2, 3);
					break;
				case 1:
					ips200_showfloat(120, 15, *value0, 2, 3);
					ips200_showfloat(120, 16, *value1, 2, 3);
					break;
			}
			break;
		case 2:
			switch(menu2_mode){
				case 0:
					ips200_showint16(120, 15, *shortvalue0);
					ips200_showint16(120, 16, *shortvalue1);
					ips200_showint16(120, 17, *shortvalue2);
					break;
			}
	}
//	������ֵ
	if(!menu_level){
	//	ѡ��
		ips200_pencolor = 0xFFFF;
		ips200_bgcolor = 0xFDF8;
		switch(menu_index){
			case 1:
				switch(menu2_index){
					case 0:ips200_showfloat(120, 15, *value0, 2, 3);break;
					case 1:ips200_showfloat(120, 16, *value1, 2, 3);break;
					case 2:ips200_showfloat(120, 17, *value2, 2, 3);break;
					case 3:ips200_showfloat(120, 18, *value3, 2, 3);break;
				}
				break;
			case 2:
				switch(menu2_index){
					case 0:ips200_showint16(120, 15, *shortvalue0);break;
					case 1:ips200_showint16(120, 16, *shortvalue1);break;
					case 2:ips200_showint16(120, 17, *shortvalue2);break;
				}
				break;
		}
		ips200_pencolor = 0xB6DB;
		ips200_bgcolor = 0xFFFF;
	}
	else{
	//	�޸�
		ips200_pencolor = 0xFFFF;
		ips200_bgcolor = 0xAE9C;
		switch(menu_index){
			case 1:
				switch(menu2_index){
					case 0:ips200_showfloat(120, 15, *value0, 2, 3);break;
					case 1:ips200_showfloat(120, 16, *value1, 2, 3);break;
					case 2:ips200_showfloat(120, 17, *value2, 2, 3);break;
					case 3:ips200_showfloat(120, 18, *value3, 2, 3);break;
				}
				break;
			case 2:
				switch(menu2_index){
					case 0:ips200_showint16(120, 15, *shortvalue0);break;
					case 1:ips200_showint16(120, 16, *shortvalue1);break;
					case 2:ips200_showint16(120, 17, *shortvalue2);break;
				}
				break;
		}
		ips200_pencolor = 0xB6DB;
		ips200_bgcolor = 0xFFFF;
	}
}
/*------------------------------*/
/*		   ������ʾģ��			*/
/*==============================*/
void menu2display(void){
//	����
	ips200_clear(WHITE);
	ips200_pencolor = 0xB6DB;
	ips200_bgcolor = 0xFFFF;
//	��ʾ����
	switch(menu_index){
		case 0:
			switch(menu2_mode){
				case 0:
					ips200_display_chinese(0, 208, 16, nom, info(100, 0), 0XFDF8);
					ips200_display_chinese(120, 208, 16, nom, info(100, 1), 0XFDF8);
					ips200_display_chinese(90, 224, 16, nom, info(100, 2), 0XFDF8);
					ips200_display_chinese(170, 224, 16, nom, info(100, 3), 0XFDF8);
					ips200_display_chinese(0, 240, 16, nom, info(menu_index, 0), 0xB6DB);
					ips200_display_chinese(0, 256, 16, nom, info(menu_index, 1), 0xB6DB);
					break;
				case 1:
					ips200_display_chinese(0, 208, 16, nom, info(100, 0), 0XFDF8);
					ips200_display_chinese(120, 208, 16, nom, info(100, 1), 0XFDF8);
					ips200_display_chinese(90, 224, 16, nom, info(100, 2), 0XFDF8);
					ips200_display_chinese(170, 224, 16, nom, info(100, 3), 0XFDF8);
					ips200_display_chinese(0, 240, 16, nom, info(menu_index, 2), 0xB6DB);
					ips200_display_chinese(0, 256, 16, nom, info(menu_index, 3), 0xB6DB);
					break;
			}
			break;
		case 1:
			switch(menu2_mode){
			//	���ѡ��
				case 0:
					ips200_display_chinese(0, 208, 16, nom, info(menu_index, 0), 0XFDF8);
					ips200_display_chinese(120, 208, 16, nom, info(menu_index, 1), 0XFDF8);
					ips200_showstr(0, 15, "alpha");
					ips200_showstr(0, 16, "Kp");
					ips200_showstr(0, 17, "Ki");
					ips200_showstr(0, 18, "Kd");
					break;
				case 1:
					ips200_display_chinese(0, 208, 16, nom, info(menu_index, 0), 0XFDF8);
					ips200_display_chinese(120, 208, 16, nom, info(menu_index, 1), 0XFDF8);
					ips200_showstr(0, 15, "Kp");
					ips200_showstr(0, 16, "Kd");
					break;
			}
			break;
		case 2:
			switch(menu2_mode){
				case 0:
					ips200_display_chinese(0, 208, 16, nom, info(1, 0), 0XFDF8);
					ips200_display_chinese(120, 208, 16, nom, info(1, 1), 0XFDF8);
					ips200_display_chinese(0, 240, 16, nom, info(menu_index, 0), 0xB6DB);
					ips200_display_chinese(0, 256, 16, nom, info(menu_index, 1), 0xB6DB);
					ips200_display_chinese(0, 272, 16, nom, info(menu_index, 2), 0xB6DB);
					break;
			}
			break;
		case 3:
			switch(menu2_mode){
				case 0:
					ips200_display_chinese(0, 208, 16, nom, info(1, 0), 0XFDF8);
					ips200_display_chinese(120, 208, 16, nom, info(1, 1), 0XFDF8);
					ips200_display_chinese(0, 240, 16, nom, info(menu_index, 0), 0xB6DB);
					ips200_display_chinese(0, 256, 16, nom, info(menu_index, 1), 0xB6DB);
					ips200_display_chinese(0, 272, 16, nom, info(menu_index, 2), 0xB6DB);
					ips200_display_chinese(0, 288, 16, nom, info(menu_index, 3), 0xB6DB);
					break;
			}
			break;
	}
//	��ʾ��ֵ
	menu2value(0);
}
/*------------------------------*/
/*		   ��ֵ�޸�ģ��			*/
/*==============================*/
static void modify(unsigned char event){
//	�޸�ģʽѡ��	
	switch(menu_index){
		case 1:
			if(event){
		//	��ֵ����
				switch(menu2_index){
					case 0:*value0+=mag[magindex];break;
					case 1:*value1+=mag[magindex];break;
					case 2:*value2+=mag[magindex];break;
					case 3:*value3+=mag[magindex];break;
					case 4:*value4+=mag[magindex];break;
				}
			}
		//	��ֵ����
			else{
				switch(menu2_index){
					case 0:*value0-=mag[magindex];break;
					case 1:*value1-=mag[magindex];break;
					case 2:*value2-=mag[magindex];break;
					case 3:*value3-=mag[magindex];break;
					case 4:*value4-=mag[magindex];break;
				}
			}
			break;
		case 2:
			if(event){
				switch(menu2_index){
					case 0: *shortvalue0+=mag[magindex];break;
					case 1: *shortvalue1+=mag[magindex];break;
					case 2: *shortvalue2+=mag[magindex];break;
				}
			}
			else{
				switch(menu2_index){
					case 0: *shortvalue0-=mag[magindex];break;
					case 1: *shortvalue1-=mag[magindex];break;
					case 2: *shortvalue2-=mag[magindex];break;
				}
			}
			break;
	}
}
/*------------------------------*/
/*		   ��ť״̬ģ��			*/
/*==============================*/
void swdisplay(void){
//	��������
	register unsigned char i;
	switch(menu_col){
	//	ҳ��ѡ��
		case 0:
			for(i=0; i<CSIMENU_FLAG; i++){
				if(csimenu_flag[i]){
					ips200_display_chinese(90, 240+16*i, 16, nom, info(100, 4), 0xB6DB);
					ips200_display_chinese(170, 240+16*i, 16, nom, info(100, 5), 0xB6DB);
				}
				else{
					ips200_display_chinese(90, 240+16*i, 16, nom, info(100, 5), 0xB6DB);
					ips200_display_chinese(170, 240+16*i, 16, nom, info(100, 4), 0xB6DB);
				}
			}
			//	����ѡ��
			if(csimenu_flag[menu2_index]) ips200_display_chinese(90, 240+16*menu2_index, 16, nom, info(100, 4), 0XB7BD);
			else ips200_display_chinese(170, 240+16*menu2_index, 16, nom, info(100, 4), 0XF5BA);
			break;
		case 1:
			for(i=0; i<WIRELESS_FLAG; i++){
				if(wireless_flag[i]){
					ips200_display_chinese(90, 240+16*i, 16, nom, info(100, 4), 0xB6DB);
					ips200_display_chinese(170, 240+16*i, 16, nom, info(100, 5), 0xB6DB);
				}
				else{
					ips200_display_chinese(90, 240+16*i, 16, nom, info(100, 5), 0xB6DB);
					ips200_display_chinese(170, 240+16*i, 16, nom, info(100, 4), 0xB6DB);
				}
			}
			//	����ѡ��
			if(wireless_flag[menu2_index]) ips200_display_chinese(90, 240+16*menu2_index, 16, nom, info(100, 4), 0XB7BD);
			else ips200_display_chinese(170, 240+16*menu2_index, 16, nom, info(100, 4), 0XF5BA);
			break;
	}
}
/*------------------------------*/
/*		   ��ť�л�ģ��			*/
/*==============================*/
static void swmode(void){
//	��������
	unsigned char temp, i;
//	���ز���
	switch(menu_col){
		case 0:
			fixed_flag = 0;
//			pit_close(PIT_CH2);
			temp = csimenu_flag[menu2_index];
			for(i=0; i<CSIMENU_FLAG; i++) csimenu_flag[i] = 0;
			csimenu_flag[menu2_index] = !temp;
			break;
		case 1:
			temp = wireless_flag[menu2_index];
			for(i=0; i<WIRELESS_FLAG; i++) wireless_flag[i] = 0;
			wireless_flag[menu2_index] = !temp;
//			if(!temp) pit_interrupt_ms(PIT_CH3,20);
//			else pit_close(PIT_CH3);
			break;
	}
}
/*------------------------------*/
/*		   ��ֵ����ģ��			*/
/*==============================*/
void monitor(void){
	switch(menu_col){
		case 0:
			ips200_showint16(120, 15, pita);
			ips200_showint16(120, 16, gz);
			ips200_showint16(120, 17, lcod);
			ips200_showint16(120, 18, rcod);
			break;
	}
}
/*------------------------------*/
/*		   �̶�����ģ��			*/
/*==============================*/
void fixed_monitor(void){
	switch(fixed_index){
		case 0:
		//	������ʾ
			ips200_display_chinese(0, 0, 16, nom, info(3, 0), 0XFDF8);
			ips200_display_chinese(0, 16, 16, nom, info(3, 1), 0XFDF8);
			ips200_display_chinese(0, 32, 16, nom, info(3, 2), 0XFDF8);
			ips200_display_chinese(0, 48, 16, nom, info(3, 3), 0XFDF8);
		//	��ֵ��ʾ
			ips200_showint16(120, 0, pita);
			ips200_showint16(120, 1, gz);
			ips200_showint16(120, 2, lcod);
			ips200_showint16(120, 3, rcod);
			break;
	}
}
/*------------------------------*/
/*		 �����˵�ѡ��ģ��		*/
/*==============================*/
void menu2_select(unsigned char event){
//	��������
	register unsigned char i;
//	�˵��ȼ�
	static unsigned char menu2_level;
//	���ؼ�
	if(event == 3){
	//	����
		menu_level = 0;
		display();
		menu2_level = 0;
		magindex = 1;
//		monitorflag = 0;
//	//	������ʱ��
//		if(!fixedflag) pit_close(PIT_CH2);
		tim_interrupt_enabnle(TIM_2);
		return;
	}
//	��֧ѡ��
	if(!menu2_level){
		switch(event){
			case 6://�Ұ���
				if(magindex < 4) magindex++;
				break;
			
			case 4://�󰴼�
				if(magindex > 0) magindex--; 
				break;
			
			case 2://�ϰ���
				if(menu2_index > 0) menu2_index--;
				break;
			
			case 5://�°���
				if(menu2_index < menu2_limit) menu2_index++;
				break;
			
			case 1://ȷ����
				switch(menu2flag){
					case 1:menu2_level = 1;break;
					case 2:
						fixed_flag = !fixed_flag;
						fixed_index = menu_col;
						if(fixed_flag) for(i=0; i<CSIMENU_FLAG; i++) csimenu_flag[i] = 0;
						break;//�л��̶���ʾ
					case 3:
						swmode();
						swdisplay();
						break;
					case 0:break;
				}
				break;
		}
		menu2value(menu2_level);
	}
//	��ֵ�޸�
	else{
		switch(event){
			case 6://�Ұ���
				if(magindex < 4) magindex++;
				break;
			
			case 4://�󰴼�
				if(magindex > 0) magindex--; 
				break;
			
			case 2://�ϰ���
				modify(1);
				break;
			
			case 5://�°���
				modify(0);
				break;
			
			case 1://ȷ����
				menu_level = 0;
				break;
		}
		menu2value(menu_level);
	}
}
//----------------------------�ָ���----------------------------//
/*--------------------------------------------------------------*/
/* 							 һ���˵� 							*/
/*==============================================================*/
/*------------------------------*/
/*		   �˵���ʾģ��			*/
/*==============================*/
void display(void){
//	��������
	char show_index[ROWS];
	unsigned char i;
//	����
	ips200_clear(WHITE);
//	������ʾ����
	if(menu_index-1<0) show_index[0] = ROWS-1;
	else show_index[0] = menu_index - 1;

	show_index[1] = menu_index;

	if(menu_index+1>ROWS-1) show_index[2] = 0,show_index[3] = 1;
	else if(menu_index+2>ROWS-1) show_index[2] = menu_index+1,show_index[3] = 0;
	else show_index[2] = menu_index+1,show_index[3] = menu_index+2;
//	�˵���ʾ
	ips200_display_chinese(0, 208, 16, nom, info(100, 1), 0XFDF8);//�˵�
	ips200_display_chinese(14, 224, 16, nom, info(show_index[0], menu[show_index[0]]), 0xB6DB);
	
	ips200_display_chinese(20, 256, 16, nom, info(show_index[1], menu[show_index[1]]), 0xB6DB);
	
	ips200_display_chinese(10, 288, 16, nom, info(show_index[2], menu[show_index[2]]), 0xB6DB);
	ips200_display_chinese(0, 304, 16, nom, info(show_index[3], menu[show_index[3]]), 0xB6DB);
}
/*------------------------------*/
/*		 �˵���ֵ����ģ��		*/
/*==============================*/
static char menu_limit(char num){
//	����������ֵ
	switch(menu_index){
		case 0:if(num<LIMIT0) return 1;break;
		case 1:if(num<LIMIT1) return 1;break;
		case 2:if(num<LIMIT2) return 1;break;
		case 3:if(num<LIMIT3) return 1;break;
	}
	return 0;
}
/*------------------------------*/
/*		 һ���˵�ѡ��ģ��		*/
/*==============================*/
void menu_select(unsigned char event){
//	�˵��¼���֧
	switch(event){
		case 6://�Ұ���
			if(menu_limit(menu[menu_index])) menu[menu_index]++;
			else return;
			break;
		
		case 4://�󰴼�
			if(menu[menu_index] > 0) menu[menu_index]--;
			else return;
			break;
		
		case 2://�ϰ���
			if(menu_index>0) menu_index--;
			else menu_index = ROWS-1;
			break;
		
		case 5://�°���
			if(menu_index<ROWS-1) menu_index++;
			else menu_index = 0;
			break;
		
		case 1://ȷ����
		//	��ʼ�������˵�
			menu2_init();
			menu2display();
			menu_level = 1;
			return;
		case 3:break;
	}
	display();
}
