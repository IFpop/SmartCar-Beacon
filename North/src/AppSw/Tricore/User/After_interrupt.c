/*
 * Interrupt_handle.c
 *
 *  Created on: 2020閿熸枻鎷�7閿熸枻鎷�3閿熸枻鎷�
 *      Author: IFpop
 */
#include "include.h"
#define Const 0
#define Obstacle_Cam  600

static float Cam_k = 1.0;
static uint32_t count = 0;

extern struct vector3f_t vec ;
extern struct vector3f_t offset;
extern uint32_t offset_flag;
extern uint32_t direct_flag;


/*
 * 遥控接收
 */
void After_bluetoothIRQ(uint8_t control_type, uint8_t* buffer){

	int v;
	float x;
	float y;
	char txt[50];
	if(control_type == 0xc3){
		sscanf((const char*)buffer, "%f %f %d",&x,&y,&v);

    		vec.x = x;
    		vec.y = y;
    		vec.z = 0;
    		if(x < 0){
    			direct_flag = 1;
    		}
    		else{
    			direct_flag = 0;
    		}
	}
//	sprintf(txt,"x:%02f",vec.x);
//	TFTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//字符串显示
//	sprintf(txt,"y:%02f",vec.y);
//	TFTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//字符串显示
//	sprintf(txt,"z:%02f",vec.z);
//	TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//字符串显示
}
void After_Receive_Cam(uint8_t* buffer){
	int x = 0;
	int y = 0;
	int w = 0;
	int h = 0;
	float obstacle_S = 0.0;

	sscanf((const char*)buffer, "%d %d %d %d",&x,&y,&w,&h);
	TFTSPI_P8X16Str(1,1,(char *)buffer,u16WHITE,u16BLACK);		//字符串显示
	if(x != -2000){
		count++;
	}
	else{
		count = 0;
	}
	if(count == 2){
		offset_flag = 0;
		int mid = x + w/2;
		if(mid < 80){
			offset.x = 1;
			offset.y = offset.x/3;
			offset.z = 0;
		}
		else{
			offset.x = 1;
			offset.y = offset.x/3;
			offset.z = 0;
		}
	}
}
