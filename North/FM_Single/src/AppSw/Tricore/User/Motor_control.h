/*
 * Motor_control.h
 *
 *  Created on: 2020年7月3日
 *      Author: IFpop
 */

#ifndef SRC_APPSW_TRICORE_USER_MOTOR_CONTROL_H_
#define SRC_APPSW_TRICORE_USER_MOTOR_CONTROL_H_

// PI 电机控制参数
#define PID_P1 23
#define PID_I1 0.6
#define PID_P2 23
#define PID_I2 0.6
#define PID_P3 23
#define PID_I3 0.6
#define PID_P4 23
#define PID_I4 0.6


// x,y,z 代表运动向量
typedef struct vector3f_t{
	float x;
	float y;
	float z; //z相等于舵机
};

void vector2speed(struct vector3f_t*, float);
static struct vector3f_t* speed2vector(int16_t*, uint16_t);

void speed_control(void);
int16_t motor_pid(int16_t, int16_t,float,float,int16_t *,int8_t);
void Servo_PD(void);
#endif /* SRC_APPSW_TRICORE_USER_MOTOR_CONTROL_H_ */
