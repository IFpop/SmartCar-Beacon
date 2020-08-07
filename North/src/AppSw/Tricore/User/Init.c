/*
 * Init.c
 *
 *  Created on: 2020年7月15日
 *      Author: IFpop
 */
#include "include.h"
void init_motor(void){

	GPIO_LED_Init();
	// 显示屏
	TFTSPI_Init(1);         //LCD初始化  0:横屏  1：竖屏
	TFTSPI_CLS(u16BLACK);   //黑色屏幕
	// 蓝牙初始化
	UART_InitConfig(Bluetooth_RX,Bluetooth_TX, 38400);
	// 摄像头通信
//	UART_InitConfig(Cam_RX,Cam_TX, 9600);

	//电机初始化
	ATOM_PWM_InitConfig(ATOMPWM0, 0, 12500);
	ATOM_PWM_InitConfig(ATOMPWM1, 0, 12500);
	ATOM_PWM_InitConfig(ATOMPWM2, 0, 12500);
	ATOM_PWM_InitConfig(ATOMPWM3, 0, 12500);

	//电机初始化 1 0反转 0 1正转
	PIN_InitConfig(Motor1_port1, PIN_MODE_OUTPUT, 0);//1号电机
	PIN_InitConfig(Motor1_port2, PIN_MODE_OUTPUT, 1);
	PIN_InitConfig(Motor2_port1, PIN_MODE_OUTPUT, 0);//2号
	PIN_InitConfig(Motor2_port2, PIN_MODE_OUTPUT, 1);
	PIN_InitConfig(Motor3_port1, PIN_MODE_OUTPUT, 0);//3号
	PIN_InitConfig(Motor3_port2, PIN_MODE_OUTPUT, 1);
	PIN_InitConfig(Motor4_port1, PIN_MODE_OUTPUT, 0);//4号
	PIN_InitConfig(Motor4_port2, PIN_MODE_OUTPUT, 1);

	ENC_InitConfig(ENCODE1_INPUT, ENCODE1_DIR);
	ENC_InitConfig(ENCODE2_INPUT, ENCODE2_DIR);
	ENC_InitConfig(ENCODE3_INPUT, ENCODE3_DIR);
	ENC_InitConfig(ENCODE4_INPUT, ENCODE4_DIR);

	IIC_Init();
	//定时中断初始化
	STM_InitConfig(STM0, STM_Channel_0, 30000);//每隔50ms获取一次编码器的值/  通过运算时间得到
//	STM_InitConfig(STM0, STM_Channel_1, 50000);//每隔10ms获取一次测距模块的值
}
