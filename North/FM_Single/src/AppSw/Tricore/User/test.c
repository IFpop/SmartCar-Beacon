/*
 * test.c
 *
 *  Created on: 2020��7��17��
 *      Author: pengs
 */

#include "include.h"

// �������Ժ���
void test_bluetooth(void){
	while(1){//��λ��һֱ����0x01
		UART_PutChar(Bluetooth,0xa0);
		UART_PutChar(Bluetooth,0x01);
		UART_PutChar(Bluetooth,0x00);
	}
}

//������Ժ���
void test_motor(void){
	struct vector3f_t temp_vec = {0,-100,0};
	while(1){
		vector2speed(&temp_vec,2);
	}
}

// �¶ȴ�����
void test_DQ(void){
	while(1){
		datapros((int)Ds18b20ReadTemp());	 //���ݴ�����
	}
}
