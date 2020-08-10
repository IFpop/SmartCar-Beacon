/*
 * Motor_control.c
 *
 *  Created on: 2020年7月3日
 *      Author: IFpop
 */

#include "include.h"

static float k = 1.4;
static uint32_t times = 0;
static struct vector3f_t vec_ = {0.0f,0.0f,0.0f};
static int16_t S[4] = {0,0,0,0};

static volatile int16_t target1 = 0;//轮子最高转速2500左右
static volatile int16_t target2 = 0;
static volatile int16_t target3 = 0;
static volatile int16_t target4 = 0;
static volatile int16_t target1_last = 0;//轮子最高转速2500左右
static volatile int16_t target2_last = 0;
static volatile int16_t target3_last = 0;
static volatile int16_t target4_last = 0;

static int16_t sum_error[4]= {0,0,0,0};
static int16_t error = 0;              //直接处理定时t内的脉冲数

volatile    int16_t enc1  = 0;
volatile 	int16_t enc2  = 0;
volatile	int16_t enc3  = 0;
volatile	int16_t enc4  = 0;

//static float PD_error = 0.0;
//static float PD_last_error = 0.0;
//static float z_sum_error = 0;

// 限制幅值函数，指定值范围应该在low~high之间
float constrain_float(float amt, float low, float high)
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

/*
 * @brief 总向量转换成电机设定速度
 *
 * @param vec 总控制向量
 * @param speed 速度值
 *
 */
void vector2speed(struct vector3f_t* vec, float speed){
//	char  txt[30];
	static float speed_vector[4] = {0};
	static float trans_vec[12] = {+1.0f, +1.0f, -1.0f,
								  -1.0f, +1.0f, +1.0f,
								  +1.0f, +1.0f, +1.0f,
								  -1.0f, +1.0f, -1.0f,
	                              };
//	int length_vec = sizeof(vec)/sizeof(float);
//	ANO_DT_send_int16((int)(vec->x*100), (int)(vec->y*100), (int)(vec->z), speed ,0, 0, 0, 0);
	speed_vector[0] = trans_vec[0]*vec->x+trans_vec[1]*vec->y+trans_vec[2]*vec->z;
	speed_vector[1] = trans_vec[3]*vec->x+trans_vec[4]*vec->y+trans_vec[5]*vec->z;
	speed_vector[2] = trans_vec[6]*vec->x+trans_vec[7]*vec->y+trans_vec[8]*vec->z;
	speed_vector[3] = trans_vec[9]*vec->x+trans_vec[10]*vec->y+trans_vec[11]*vec->z;
	// 最后需要乘上比例系数，进行速度转化
	for(int i = 0 ; i <  4 ; i++){
		speed_vector[i] = speed_vector[i]*speed;

		target1 = speed_vector[0];
		target2 = speed_vector[1];
		target3 = speed_vector[2];
		target4 = speed_vector[3];
	}
//	ANO_DT_send_int16((int)(vec->x*100), (int)(vec->y*100), (int)(vec->z), speed ,0, 0, 0, 0);
}

/*
 * @brief 电机设定速度转换成向量
 *
 * @param speed_vector 当前速度值
 * @param speed 速度值
 * @retval 向量
 */
static struct vector3f_t* speed2vector(int16_t* speed_vector, uint16_t speed){
	static struct vector3f_t control_vector;
	static float scale[4];
	static float trans_vec[12] = {0.5f, 0.0f, 0.0f,-0.5f,
								  0.5f, 0.5f, 0.0f, 0.0f,
								  -0.5f, 0.0f, 0.5f, 0.0f};
	scale[0] = (float)speed_vector[0] / speed;
	scale[1] = (float)speed_vector[1] / speed;
	scale[2] = (float)speed_vector[2] / speed;
	scale[3] = (float)speed_vector[3] / speed;

	control_vector.x = trans_vec[0]*scale[0]+trans_vec[1]*scale[1]+trans_vec[2]*scale[2]+trans_vec[3]*scale[3];
	control_vector.y = trans_vec[4]*scale[0]+trans_vec[5]*scale[1]+trans_vec[6]*scale[2]+trans_vec[7]*scale[3];
	control_vector.z = trans_vec[8]*scale[0]+trans_vec[9]*scale[1]+trans_vec[10]*scale[2]+trans_vec[11]*scale[3];

	return &control_vector;
}

void speed_control(void){
	if(offset_flag >= 1){
		times ++;
//		vec_.x = (vec.x + offset.x*k)*100;
//		vec_.y = (vec.y + offset.y*k)*100;
//		vec_.z = (vec.z + offset.z*k);//offset.z =0
		vec_.x = (offset.x*k)*100;
		vec_.y = 0;
		vec_.z = 0;//offset.z =0***********************
	}
	else{
		times = 0;
		vec_.x = vec.x*100;
		vec_.y = vec.y*100;
		vec_.z = vec.z;
	}

	if(times == 3)//避障状态持续时间 times*30ms

	{
		times = 0;
		offset_flag = 0;
	}

	// 设置速度分段
	if(0 < S && S < Cut_down_len){ //低速*******************************************************
		vec_.x *= 0.5;
		vec_.y *= 0.5;
	}
	else if(S > 350){ // 高速*****************************************************************
		vec_.x *= 0.8;
		vec_.y *= 0.8;
	}

	vector2speed(&vec_,V_speed);

	enc1 = ENC_GetCounter(ENCODE1_INPUT);//1号电机
	enc2 = ENC_GetCounter(ENCODE2_INPUT);//2号电机
	enc3 = ENC_GetCounter(ENCODE3_INPUT);//3号电机
	enc4 = ENC_GetCounter(ENCODE4_INPUT);//4号电机

	// 编码器正负与电机转向一致
	enc1 = -enc1;
	enc2 = +enc2;
	enc3 = +enc3;
	enc4 = -enc4;

	//车轮PD
	S[0] = enc1;
	S[1] = enc2;
	S[2] = enc3;
	S[3] = enc4;

	Servo_PD();

	int16_t motor1_pluse = motor_pid(enc1,target1,PID_P1,PID_I1,(int16_t*)&sum_error,0);
	int16_t motor2_pluse = motor_pid(enc2,target2,PID_P2,PID_I2,(int16_t*)&sum_error,1);
	int16_t motor3_pluse = motor_pid(enc3,target3,PID_P3,PID_I3,(int16_t*)&sum_error,2);
	int16_t motor4_pluse = motor_pid(enc4,target4,PID_P4,PID_I4,(int16_t*)&sum_error,3);

	// 限幅
	/* 限幅  防止电机转速反差过大  */
	static float motor1Last = 0, motor2Last = 0, motor3Last = 0, motor4Last = 0;
//	motor1_pluse = motor1Last + constrain_float(motor1_pluse - motor1Last, -4000, 4000);
//	motor2_pluse = motor2Last + constrain_float(motor2_pluse - motor2Last, -4000, 4000);
//	motor3_pluse = motor3Last + constrain_float(motor3_pluse - motor3Last, -4000, 4000);
//	motor4_pluse = motor4Last + constrain_float(motor4_pluse - motor4Last, -4000, 4000);

	motor1_pluse = constrain_float(motor1_pluse,-8000,8000);
	motor2_pluse = constrain_float(motor2_pluse,-8000,8000);
	motor3_pluse = constrain_float(motor3_pluse,-8000,8000);
	motor4_pluse = constrain_float(motor4_pluse,-8000,8000);

//	motor1Last = motor1_pluse;
//	motor2Last = motor2_pluse;
//	motor3Last = motor3_pluse;
//	motor4Last = motor4_pluse;
	if(motor1_pluse > 0){
		PIN_Write(Motor1_port1, 0);
		PIN_Write(Motor1_port2, 1);
		ATOM_PWM_SetDuty(ATOMPWM0, motor1_pluse, 12500);
	}
	else{
		PIN_Write(Motor1_port1, 1);
		PIN_Write(Motor1_port2, 0);
		ATOM_PWM_SetDuty(ATOMPWM0, -motor1_pluse, 12500);
	}

	if(motor2_pluse > 0){
		PIN_Write(Motor2_port1, 0);
		PIN_Write(Motor2_port2, 1);
		ATOM_PWM_SetDuty(ATOMPWM1, motor2_pluse, 12500);
	}
	else{
		PIN_Write(Motor2_port1, 1);
		PIN_Write(Motor2_port2, 0);
		ATOM_PWM_SetDuty(ATOMPWM1, -motor2_pluse, 12500);
	}

	if(motor3_pluse > 0){
		PIN_Write(Motor3_port1, 0);
		PIN_Write(Motor3_port2, 1);
		ATOM_PWM_SetDuty(ATOMPWM2, motor3_pluse, 12500);
	}
	else{
		PIN_Write(Motor3_port1, 1);
		PIN_Write(Motor3_port2, 0);
		ATOM_PWM_SetDuty(ATOMPWM2, -motor3_pluse, 12500);
	}

	if(motor4_pluse > 0){
		PIN_Write(Motor4_port1, 0);
		PIN_Write(Motor4_port2, 1);
		ATOM_PWM_SetDuty(ATOMPWM3, motor4_pluse, 12500);
	}
	else{
		PIN_Write(Motor4_port1, 1);
		PIN_Write(Motor4_port2, 0);
		ATOM_PWM_SetDuty(ATOMPWM3, -motor4_pluse, 12500);
	}

//	ANO_DT_send_int16(enc1, enc2, enc3, enc4, target1, motor1_pluse, 0, 0);
}

int16_t motor_pid(int16_t pulse, int16_t target_pulse,float P,float I,int16_t* sum_err,int8_t index){
	float PI_SUM = 0.0;

	error = target_pulse - pulse;
	sum_err[index] += error;
	PI_SUM =I * sum_err[index];

	PI_SUM = constrain_float(PI_SUM,-8000,8000);

    float result = 0;
    result = P * error + PI_SUM;//pid计算结果result

//    ANO_DT_send_int16(pulse, target_pulse, error, sum_err[index], result, 0, 0, 0);
    return result;
}

void Servo_PD(void){
	struct vector3f_t * vec_speed = speed2vector(S,1);

	float w = (vec_speed->z*180)/(35.06*pi);  // 角速度

	if(z_change_flag == 0){  // z没有发生改变
		z_sum_error += w*0.05;
	}
	else{
		z_sum_error = w*0.05;
	}

	float angle = 0;
	PD_error = target_-z_sum_error;
	angle = kp*PD_error+kd*(PD_error-PD_last_error);
	PD_last_error = PD_error;
	if(IfxCpu_acquireMutex(&mutevec)){
		vec.z = angle;
		IfxCpu_releaseMutex(&mutevec);
	}
//	ANO_DT_send_int16((int)PD_last_error, (int)PD_error, (int)target_, (int)vec_speed->z, (int)angle, (int)z_sum_error , (int)vec.z, 0);
}

