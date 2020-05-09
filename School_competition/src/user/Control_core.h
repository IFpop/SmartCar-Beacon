/******************************************************************************
* 文件:    Control_core.h
* 目的:    将智能车运动函数、中断函数之后的处理
******************************************************************************/

#ifndef _CONTROL_CORE_H_
#define _CONTROL_CORE_H_

#include "include.h"
void After_bluetoothIRQ(uint8_t control_type, uint8_t* buffer);
void CAMERA_deal(uint8_t* buffer);
void STOP(void);
void BACK(void);
void LEFT(void);
void RIGHT(void);
void GO_AHEAD(void);
void Clockwise(void);
void Anticlockwise(void);
void Encode_init(void);

#endif