/*
 * TOF10120.c
 *
 *  Created on: 2020年7月16日
 *      Author: IFpop
 */

#include "include.h"


//#define VECTOR_LENGTH 3
#define VECTOR_LENGTH 7
#define cal_X_intercept 400


char txt_tof[50];

extern struct vector3f_t offset;
//extern uint32_t distance[3];
extern uint32_t distance[7];
extern uint32_t offset_flag;
extern uint32_t direct_flag;

static uint32_t count = 0;

unsigned char dis_buff[2]={0,0};
//uint8_t TOF10120_Addr[3] = {0x13,0x14,0x15};
uint8_t TOF10120_Addr[7] = {0,0x13,0x14,0x15,0x16,0x17,0x19};
uint8_t Get_flag = 0; // 0代表接收能够，1代表失败
uint32_t dis = 0;

#ifndef MAX
#define MAX(x,y) ((x)>(y)?(x):(y))
#endif
#ifndef MIN
#define MIN(x,y) ((x)<(y)?(x):(y))
#endif

static float sin_table[VECTOR_LENGTH] = { //测距在y轴分量
	   0.0f,
	  +0.0f, +0.0f, 0.0f,    //后   1 2 3
	  -0.0f, -0.0f, -0.0f  // 前 4 5 6

//	  +1.0f, +1.0f, +1.0f,
//	  -1.0f, -1.0f, -1.0f
};
static float cos_table[VECTOR_LENGTH] = { //测距在x轴分量
	0.0f,
    +1.0f, +1.5f, -1.0f,  // 后
	-1.0f, -1.5f, +1.0f // 前
};
static float z_table[VECTOR_LENGTH] = {   //测距在z轴分量
	0.0f,
    -0.0f, -0.0f, +0.0f,  //后
	+0.0f, -0.0f, -0.0f // 前
};

static float length_table[VECTOR_LENGTH] = {
//	  1.0f,1.0f,1.0f
	  0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f
};

static float length_last_table[VECTOR_LENGTH] = {
    0.0f
};

// 计算所有的
float Calculate_length(int index){
	int temp_dis = distance[index];
	if(temp_dis > cal_X_intercept){
		return 0.0;
	}
	else{
		return 1-temp_dis/((float)cal_X_intercept);
	}
}
//测距
void TOF10120(void){
	float b_x = 0.0;
	float b_y = 0.0;
	float b_z  = 0.0;
	// 取三个测距模块内容
	for(int i = 1 ; i < VECTOR_LENGTH ; i++){
//		LED_Ctrl(LEDALL,RVS);        //四个LED同时闪烁
//		delayms(300);
		Get_flag = IIC_ReadMultByteFromSlave(TOF10120_Addr[i]<<1,TOF10120_Real_Time_Dis,2,dis_buff);
		if(Get_flag == 0){
			dis = (dis_buff[0]<<8) + (dis_buff[1]);
			if(dis <= cal_X_intercept){
				distance[i] = dis;
			}
			else{
				distance[i] = 2000;
			}
		}
	}
//	ANO_DT_send_int16((int)distance[1],(int)distance[2],(int)distance[3],(int)distance[4],(int)distance[5],(int)distance[6],0,0);
	for(int i = 1 ; i < VECTOR_LENGTH ; i++){
		length_table[i] = Calculate_length(i);
	}
	float Min1 = MIN(length_table[1],length_last_table[1]);
	float Min3 = MIN(length_table[3],length_last_table[3]);

	if(Min1 > Min3){
		cos_table[2] =+1.5f;
		z_table[2] = -0.0f;
	}
	else{
		cos_table[2] = -1.5f;
		z_table[2] = +0.0f;
	}

	float Min4 = MIN(length_table[4],length_last_table[4]);
	float Min6 = MIN(length_table[6],length_last_table[6]);
	if(Min4>Min6){
		cos_table[5] = -1.5f;
		z_table  [5] = +0.0f;
	} else {
		cos_table[5] = +1.5f;
		z_table  [5] = -0.0f;
	}
	if(direct_flag == -1){//车后
		for(int i = 1 ; i < 4 ; i++){
			b_x += length_table[i] * cos_table[i];
			b_y += length_table[i] * sin_table[i];
			b_z += length_table[i] * z_table[i];

			length_last_table[i] = length_table[i];
		}
		if(length_table[1] != 0 || length_table[2] != 0 || length_table[3] != 0){
			count++;
		}
		else {
			count = 0;
		}
	}
	else if(direct_flag == 1){//车前
		// 点乘
		for(int i = 4 ; i < VECTOR_LENGTH ; i++){
			b_x += length_table[i] * cos_table[i];
			b_y += length_table[i] * sin_table[i];
			b_z += length_table[i] * z_table[i];

			length_last_table[i] = length_table[i];
		}
		if(length_table[4] != 0 || length_table[5] != 0 || length_table[6] != 0){
			count++;
		}
		else {
			count = 0;
		}
	}
	if(count >= 1){
		count = 0;
		offset.x = b_x;
		offset.y = b_y;
		offset.z = b_z;
		offset_flag = 1;
	}
//	sprintf(txt_tof,"d4:%d",distance[4]);
//	TFTSPI_P8X16Str(1,0,txt_tof,u16WHITE,u16BLACK);		//字符串显
//	sprintf(txt_tof,"d5:%d",distance[5]);
//	TFTSPI_P8X16Str(1,1,txt_tof,u16WHITE,u16BLACK);		//字符串显
//	sprintf(txt_tof,"d6:%d",distance[6]);
//	TFTSPI_P8X16Str(1,2,txt_tof,u16WHITE,u16BLACK);		//字符串显

}
