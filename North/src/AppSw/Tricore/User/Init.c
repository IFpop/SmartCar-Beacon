/*
 * Init.c
 *
 *  Created on: 2020��7��15��
 *      Author: IFpop
 */
#include "include.h"
void init_motor(void){

	GPIO_LED_Init();
	// ��ʾ��
	TFTSPI_Init(1);         //LCD��ʼ��  0:����  1������
	TFTSPI_CLS(u16BLACK);   //��ɫ��Ļ
	// ������ʼ��
	UART_InitConfig(Bluetooth_RX,Bluetooth_TX, 38400);
	// ����ͷͨ��
//	UART_InitConfig(Cam_RX,Cam_TX, 9600);

	//�����ʼ��
	ATOM_PWM_InitConfig(ATOMPWM0, 0, 12500);
	ATOM_PWM_InitConfig(ATOMPWM1, 0, 12500);
	ATOM_PWM_InitConfig(ATOMPWM2, 0, 12500);
	ATOM_PWM_InitConfig(ATOMPWM3, 0, 12500);

	//�����ʼ�� 1 0��ת 0 1��ת
	PIN_InitConfig(Motor1_port1, PIN_MODE_OUTPUT, 0);//1�ŵ��
	PIN_InitConfig(Motor1_port2, PIN_MODE_OUTPUT, 1);
	PIN_InitConfig(Motor2_port1, PIN_MODE_OUTPUT, 0);//2��
	PIN_InitConfig(Motor2_port2, PIN_MODE_OUTPUT, 1);
	PIN_InitConfig(Motor3_port1, PIN_MODE_OUTPUT, 0);//3��
	PIN_InitConfig(Motor3_port2, PIN_MODE_OUTPUT, 1);
	PIN_InitConfig(Motor4_port1, PIN_MODE_OUTPUT, 0);//4��
	PIN_InitConfig(Motor4_port2, PIN_MODE_OUTPUT, 1);

	ENC_InitConfig(ENCODE1_INPUT, ENCODE1_DIR);
	ENC_InitConfig(ENCODE2_INPUT, ENCODE2_DIR);
	ENC_InitConfig(ENCODE3_INPUT, ENCODE3_DIR);
	ENC_InitConfig(ENCODE4_INPUT, ENCODE4_DIR);

	IIC_Init();
	//��ʱ�жϳ�ʼ��
	STM_InitConfig(STM0, STM_Channel_0, 30000);//ÿ��50ms��ȡһ�α�������ֵ/  ͨ������ʱ��õ�
//	STM_InitConfig(STM0, STM_Channel_1, 50000);//ÿ��10ms��ȡһ�β��ģ���ֵ
}
