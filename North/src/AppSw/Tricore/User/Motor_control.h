/*
 * Motor_control.h
 *
 *  Created on: 2020年7月3日
 *      Author: IFpop
 */

#ifndef SRC_APPSW_TRICORE_USER_MOTOR_CONTROL_H_
#define SRC_APPSW_TRICORE_USER_MOTOR_CONTROL_H_

// x,y,z 代表运动向量
typedef struct vector3f_t{
	float x;
	float y;
	float z; //z相等于舵机
};

void vector2speed(struct vector3f_t*, float);
static struct vector3f_t* speed2vector(uint8_t*, uint16_t);

void speed_control(void);
int16_t motor_pid(int16_t, int16_t,float,float,int16_t *,int8_t);

#endif /* SRC_APPSW_TRICORE_USER_MOTOR_CONTROL_H_ */
