/*
 * Motor_control.c
 *
 *  Created on: 2020��7��3��
 *      Author: IFpop
 */

#include "include.h"

static float k = 1.4;
static uint32_t times = 0;
static struct vector3f_t vec_ = {0.0f,0.0f,0.0f};

static volatile int16_t target1 = 0;//�������ת��2500����
static volatile int16_t target2 = 0;
static volatile int16_t target3 = 0;
static volatile int16_t target4 = 0;
static volatile int16_t target1_last = 0;//�������ת��2500����
static volatile int16_t target2_last = 0;
static volatile int16_t target3_last = 0;
static volatile int16_t target4_last = 0;

static int16_t sum_error[4]= {0,0,0,0};
static int16_t error = 0;              //ֱ�Ӵ���ʱt�ڵ�������

volatile    int16_t enc1  = 0;
volatile 	int16_t enc2  = 0;
volatile	int16_t enc3  = 0;
volatile	int16_t enc4  = 0;

static float PD_error = 0.0;
static float PD_last_error = 0.0;
static float z_sum_error = 0;

// ���Ʒ�ֵ������ָ��ֵ��ΧӦ����low~high֮��
float constrain_float(float amt, float low, float high)
{
	return ((amt)<(low)?(low):((amt)>(high)?(high):(amt)));
}

/*
 * @brief ������ת���ɵ���趨�ٶ�
 *
 * @param vec �ܿ�������
 * @param speed �ٶ�ֵ
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
	// �����Ҫ���ϱ���ϵ���������ٶ�ת��
	for(int i = 0 ; i <  4 ; i++){
		speed_vector[i] = speed_vector[i]*speed;

		switch(i){
		case 0:
			if(speed_vector[i] < 0 ){
				speed_vector[i] = -speed_vector[i];
				PIN_Write(Motor1_port1, 1);
				PIN_Write(Motor1_port2, 0);
			}
			else{
				PIN_Write(Motor1_port1, 0);
				PIN_Write(Motor1_port2, 1);
			}
			target1 = speed_vector[i];
//			if(target1 != target1_last){
//				sum_error[0] = 0;
//			}
			target1_last = target1;
			break;
		case 1:
			if(speed_vector[i] < 0 ){
				speed_vector[i] = -speed_vector[i];
				PIN_Write(Motor2_port1, 1);
				PIN_Write(Motor2_port2, 0);
			}
			else{
				PIN_Write(Motor2_port1, 0);
				PIN_Write(Motor2_port2, 1);
			}
			target2 = speed_vector[i];
//			if(target2 != target2_last){
//				sum_error[1] = 0;
//			}
			target2_last = target2;
			break;
		case 2:
			if(speed_vector[i] < 0 ){
				speed_vector[i] = -speed_vector[i];
				PIN_Write(Motor3_port1, 1);
				PIN_Write(Motor3_port2, 0);
			}
			else{
				PIN_Write(Motor3_port1, 0);
				PIN_Write(Motor3_port2, 1);
			}
			target3 = speed_vector[i];
//			if(target3 != target3_last){
//				sum_error[2] = 0;
//			}
			target3_last = target3;
			break;
		case 3:
			if(speed_vector[i] < 0 ){
				speed_vector[i] = -speed_vector[i];
				PIN_Write(Motor4_port1, 1);
				PIN_Write(Motor4_port2, 0);
			}
			else{
				PIN_Write(Motor4_port1, 0);
				PIN_Write(Motor4_port2, 1);
			}
			target4 = speed_vector[i];
//			if(target4 != target4_last){
//				sum_error[3] = 0;
//			}
			target4_last = target4;
			break;
		}
	}
//	ANO_DT_send_int16((int)(vec->x*100), (int)(vec->y*100), (int)(vec->z), speed ,0, 0, 0, 0);
}

/*
 * @brief ����趨�ٶ�ת��������
 *
 * @param speed_vector ��ǰ�ٶ�ֵ
 * @param speed �ٶ�ֵ
 * @retval ����
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
		vec_.x = (vec.x + offset.x*k)*100;
		vec_.y = (vec.y + offset.y*k)*100;
		vec_.z = (vec.z + offset.z*k)/2;//offset.z =0
	}
	else{
		times = 0;
		vec_.x = vec.x*100;
		vec_.y = vec.y*100;
		vec_.z = vec.z/2;
	}

	if(times == 5)//����״̬����ʱ�� times*50ms
	{
		times = 0;
		offset_flag = 0;
	}
	vector2speed(&vec_,1.285);

	enc1 = ENC_GetCounter(ENCODE1_INPUT);//1�ŵ��
	enc2 = ENC_GetCounter(ENCODE2_INPUT);//2�ŵ��
	enc3 = ENC_GetCounter(ENCODE3_INPUT);//3�ŵ��
	enc4 = ENC_GetCounter(ENCODE4_INPUT);//4�ŵ��

	enc1=enc1*(enc1>0)-enc1*(enc1<0);//ȡ����ֵ
	enc2=enc2*(enc2>0)-enc2*(enc2<0);//ȡ����ֵ
	enc3=enc3*(enc3>0)-enc3*(enc3<0);//ȡ����ֵ
	enc4=enc4*(enc4>0)-enc4*(enc4<0);//ȡ����ֵ

	int16_t motor1_pluse = motor_pid(enc1,target1,PID_P1,PID_I1,(int16_t*)&sum_error,0);
	int16_t motor2_pluse = motor_pid(enc2,target2,PID_P2,PID_I2,(int16_t*)&sum_error,1);
	int16_t motor3_pluse = motor_pid(enc3,target3,PID_P3,PID_I3,(int16_t*)&sum_error,2);
	int16_t motor4_pluse = motor_pid(enc4,target4,PID_P4,PID_I4,(int16_t*)&sum_error,3);

	// �޷�
	/* �޷�  ��ֹ���ת�ٷ������  */
	static float motor1Last = 0, motor2Last = 0, motor3Last = 0, motor4Last = 0;
	motor1_pluse = motor1Last + constrain_float(motor1_pluse - motor1Last, -1000, 1000);
	motor2_pluse = motor2Last + constrain_float(motor2_pluse - motor2Last, -1000, 1000);
	motor3_pluse = motor3Last + constrain_float(motor3_pluse - motor3Last, -1000, 1000);
	motor4_pluse = motor4Last + constrain_float(motor4_pluse - motor4Last, -1000, 1000);

	ATOM_PWM_SetDuty(ATOMPWM0, motor1_pluse, 12500);
	ATOM_PWM_SetDuty(ATOMPWM1, motor2_pluse, 12500);
	ATOM_PWM_SetDuty(ATOMPWM2, motor3_pluse, 12500);
	ATOM_PWM_SetDuty(ATOMPWM3, motor4_pluse, 12500);

	motor1Last = motor1_pluse;
	motor2Last = motor2_pluse;
	motor3Last = motor3_pluse;
	motor4Last = motor4_pluse;

//	ANO_DT_send_int16(motor1_pluse, motor2_pluse, motor1Last,motor2Last, enc1, enc2, enc3, (int)(vec_.y*1.2));
}

int16_t motor_pid(int16_t pulse, int16_t target_pulse,float P,float I,int16_t* sum_err,int8_t index){
	float PI_SUM = 0.0;

	error = target_pulse - pulse;
	sum_err[index] += error;
	PI_SUM =I * sum_err[index];

	// �޷�  --> need change
    if(PI_SUM>8000)
         PI_SUM=8000;

    float result = 0;
    result = P * error + PI_SUM;//pid������result

//    ANO_DT_send_int16(result, error, sum_err[0], pulse,target_pulse,0,0,0);

    if (result > 8000)//����޷�
           result = 8000;
    if (result < 0)
           result = 0;
    return result;
}

void Servo_PD(void){
	int16_t S[4];

	int target_ = 90;

	S[0] = -ENC_GetCounter(ENCODE1_INPUT);//1�ŵ��
	S[1] = +ENC_GetCounter(ENCODE2_INPUT);//2�ŵ��
	S[2] = +ENC_GetCounter(ENCODE3_INPUT);//3�ŵ��
	S[3] = -ENC_GetCounter(ENCODE4_INPUT);//4�ŵ��

	struct vector3f_t * vec_speed = speed2vector(S,1);

	float w = vec_speed->z/35.06;  // ���ٶ�

	if(z_change_flag == 0){  // zû�з����ı�
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

