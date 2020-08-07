/*
 * test.c
 *
 *  Created on: 2020年7月17日
 *      Author: pengs
 */

#include "include.h"

// 蓝牙测试函数
void test_bluetooth(void){
	while(1){//上位机一直接收0x01
		UART_PutChar(Bluetooth,0xa0);
		UART_PutChar(Bluetooth,0x01);
		UART_PutChar(Bluetooth,0x00);
	}
}

//电机测试函数
void test_motor(void){
	struct vector3f_t temp_vec = {0,-100,0};
	while(1){
		vector2speed(&temp_vec,2);
	}
}

// 温度传感器
void test_DQ(void){
	while(1){
		datapros((int)Ds18b20ReadTemp());	 //数据处理函数
	}
}
