/*
 * TOF10120.h
 *
 *  Created on: 2020年7月16日
 *      Author: IFpop
 */

#ifndef SRC_APPSW_TRICORE_USER_TOF10120_H_
#define SRC_APPSW_TRICORE_USER_TOF10120_H_
#include "include.h"
//---------------TOF10120------------------
#define TOF10120_Real_Time_Dis 0x00
#define TOF10120_Filter_Dis 0x02
#define TOF10120_Offset_Dis 0x06
#define TOF10120_Model 0x0b
#define TOF10120_Send_Style 0x0c
#define TOF10120_Biggest_Dis 0x0e
#define TOF10120_SLAVE_DEVICE_ADDRESS 0x0f



#define VECTOR_LENGTH 7  // 矢量个数
#define cal_X_intercept 400  // 避障距离

void TOF10120(void);
void Sensor_Set_SendDir(void);
void Sensor_Set_Model(void);

#endif /* SRC_APPSW_TRICORE_USER_TOF10120_H_ */
