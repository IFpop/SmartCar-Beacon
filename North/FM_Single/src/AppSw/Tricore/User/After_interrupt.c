/*
 * Interrupt_handle.c
 *
 *  Created on: 2020
 *      Author: IFpop
 */
#include "include.h"

static uint32_t count = 0;
static float w_error = 0.0f;
static float w_last_error = 0.0f;
static float w_sum_error = 0.0f;
/*
 * 遥控接收
 */
void After_bluetoothIRQ(uint8_t control_type, uint8_t* buffer){

	int v;
	float x;
	float y;
	if(control_type == 0xc3){
		sscanf((const char*)buffer, "%f %f %d",&x,&y,&v);

    		vec.x = x;
    		vec.y = y;
    		vec.z = 0;
    		if(y < 0){
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
	int length = 0;

	sscanf((const char*)buffer, "%d %d %d %d %d",&x,&y,&w,&h,&length);
	ANO_DT_send_int16(x, y, w, h, length, 0, 0,0);
//	sprintf(txt,"Cam");
//	TFTSPI_P8X16Str(1,0,txt,u16WHITE,u16BLACK);		//字符串显示
//	sprintf(txt,"x:%d",x);
//	TFTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//字符串显示
//	sprintf(txt,"y:%d",y);
//	TFTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//字符串显示
//	sprintf(txt,"w:%d",w);
//	TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//字符串显示
//	sprintf(txt,"h:%d",h);
//	TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//字符串显示
//	sprintf(txt,"length:%d",length);
//	TFTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//字符串显示

	// TFTSPI_P8X16Str(1,1,(char *)buffer,u16WHITE,u16BLACK);		//字符串显示
	// if(x != -2000){
	// 	count++;
	// }
	// else{
	// 	count = 0;
	// }
	// if(count == 2){
	// 	offset_flag = 0;
	// 	int mid = x + w/2;
	// 	if(mid < 80){
	// 		offset.x = 1;
	// 		offset.y = offset.x/3;
	// 		offset.z = 0;
	// 	}
	// 	else{
	// 		offset.x = 1;
	// 		offset.y = offset.x/3;
	// 		offset.z = 0;
	// 	}
	// }
}

void After_Jy_Receive_Angle(uint8_t* buffer){
	static int16_t V_Angle[3];
	V_Angle[0] = ((short)(buffer[1]<<8| buffer[0]))/32768.0*180;
	V_Angle[1] = ((short)(buffer[3]<<8| buffer[2]))/32768.0*180;
	V_Angle[2] = ((short)(buffer[5]<<8| buffer[4]))/32768.0*180;

//	sprintf(txt,"angle");
//	TFTSPI_P8X16Str(1,0,txt,u16WHITE,u16BLACK);		//字符串显示
//	sprintf(txt,"x_1:%d",V_Angle[0]);
//	TFTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//字符串显示
//	sprintf(txt,"y_1:%d",V_Angle[1]);
//	TFTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//字符串显示
//	sprintf(txt,"z_1:%d",V_Angle[2]);
//	TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//字符串显示

//	ANO_DT_send_int16(V_Angle[0], V_Angle[1], V_Angle[2], 0, 0, 0, 0,0);
}
void After_Jy_Receive_a(uint8_t* buffer){
	static int16_t V_a[3];
	V_a[0] = ((short)(buffer[1]<<8| buffer[0]))/32768.0*16;
	V_a[1] = ((short)(buffer[3]<<8| buffer[2]))/32768.0*16;
	V_a[2] = ((short)(buffer[5]<<8| buffer[4]))/32768.0*16;
}

// PD调整
void After_Jy_Receive_w(uint8_t* buffer){
	static int16_t V_w[3];
	V_w[0] = ((short)(buffer[1]<<8| buffer[0]))/32768.0*2000;
	V_w[1] = ((short)(buffer[3]<<8| buffer[2]))/32768.0*2000;
	V_w[2] = ((short)(buffer[5]<<8| buffer[4]))/32768.0*2000;

	if(z_change_flag == 0){  // z没有发生改变
		w_sum_error += V_w[2]*0.05;
	}
	else{
		w_sum_error = V_w[2]*0.05;
	}
	float angle = 0;
	w_error = w_target-w_sum_error;
//	w_error = 180-w_sum_error;
	angle = kp*w_error+kd*(w_error-w_last_error);
	w_last_error = w_error;
	if(IfxCpu_acquireMutex(&mutevec)){
		vec.z = angle;
		IfxCpu_releaseMutex(&mutevec);
	}

//	ANO_DT_send_int16(w_error, w_last_error, V_w[2], angle, w_sum_error, 0, 0,0);
}

