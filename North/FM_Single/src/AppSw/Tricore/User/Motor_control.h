/*
 * Motor_control.h
 *
 *  Created on: 2020��7��3��
 *      Author: IFpop
 */

#ifndef SRC_APPSW_TRICORE_USER_MOTOR_CONTROL_H_
#define SRC_APPSW_TRICORE_USER_MOTOR_CONTROL_H_

// PI ������Ʋ���
#define PID_P1 13
#define PID_I1 3
#define PID_P2 13
#define PID_I2 3
#define PID_P3 13
#define PID_I3 3
#define PID_P4 13
#define PID_I4 3

// PD z ������Ʋ���
#define kp 10
#define kd 0


// x,y,z �����˶�����
typedef struct vector3f_t{
	float x;
	float y;
	float z; //z����ڶ��
};

void vector2speed(struct vector3f_t*, float);
static struct vector3f_t* speed2vector(int16_t*, uint16_t);

void speed_control(void);
int16_t motor_pid(int16_t, int16_t,float,float,int16_t *,int8_t);
void Servo_PD(void);
#endif /* SRC_APPSW_TRICORE_USER_MOTOR_CONTROL_H_ */
