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
	UART_InitConfig(Cam_RX,Cam_TX, 9600);

	//电机初始化
	ATOM_PWM_InitConfig(ATOMPWM0, 0, 12500);
	ATOM_PWM_InitConfig(ATOMPWM1, 0, 12500);
	ATOM_PWM_InitConfig(ATOMPWM2, 0, 12500);
	ATOM_PWM_InitConfig(ATOMPWM3, 0, 12500);
//
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
	STM_InitConfig(STM0, STM_Channel_0, 30000);//每隔30ms获取一次编码器的值
//	STM_InitConfig(STM1, STM_Channel_0, 50000);//每隔50ms获取一次测距模块的值
}

//初始化RDA5807
void Init_RDA5807(void){
	unsigned char RSSI = 0;
	RDA5807_Init();	      //RDA5807初始化

	//显示芯片ID 0x5804
	RXFreq = RDA5807_ReadReg(RDA_R00);
	// sprintf(txt,"Chip:0x%04X",RXFreq);
	// TFTSPI_P8X16Str(1,0,txt,u16WHITE,u16BLACK);		//字符串显示

	RSSI=RDA5807_GetRssi();//显示信号强度0~127
	// sprintf(txt,"RSSI:%02d  ",RSSI);
	// TFTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//字符串显示

	//设置收听频率 95.00
	RXFreq=9500;
	RDA5807_Reset();  //软件复位
	RDA5807_SetFreq(RXFreq);
	// sprintf(txt,"Freq:%d.%02dMHz ",RXFreq/100,RXFreq%100);
	// TFTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//字符串显示
}
