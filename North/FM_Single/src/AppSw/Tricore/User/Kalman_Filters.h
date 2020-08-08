/*
 * Kalman_Filters.h
 *
 *  Created on: 8 Aug 2020
 *      Author: BenmuYu0
 */

#ifndef KALMAN_FILTERS_H_
#define KALMAN_FILTERS_H_

struct Kalman{
	float x;                 
	float y;
	float v;
	float Seta;      //�Ƕȣ����ǻ���
	float w;    // ���ٶ�
}Event_kalman;


#define noise_a   2.0		 //process noise standard deviation for a
#define noise_yaw 0.3    	 //process noise standard deviation for yaw acceleration


uint8_t x_var = 3.0;  	 // Deviation of Microphone Measurement
uint8_t y_var = 3.0;  	 // Deviation of Microphone Measurement
uint8_t v_var = 1.0;	 // Deviation of Encoder Measurement
uint8_t Seta_var = 0.1;  // Deviation of Microphone Measurement
uint8_t w_var = 1.0;     // Deviation of Gyroscope Measurement
uint8_t dt = 0.3;        // ��ʵ������EKFʱ������ǰ�����β�����ʱ���Դ����滻����� dt

static float32 P_predict[5][5] 	 	= {{0}};        //��ǰ X״̬��Э�������
static float32 P_predict_last[5][5] = {{0}};		   //��һ�� X״̬��Э�������
static float32 P_update[5][5] 	    = {{0}};        //��ǰ�������Э�������
//static float32 P_update_last[5][5]  = {0};		   //��һ���������Э�������

static float32 X_predict[5]      = {0};		   //��ǰX״̬��Ԥ��ֵ
static float32 X_predict_last[5] = {0};		   //��һ�� X״̬��Ԥ��ֵ
static float32 X_update[5]    = {0};		   //��ǰX״̬�������Ԥ��ֵ
static float32 X_update_last[5] = {0};		   //��һ�� X״̬������Ԥ��ֵ

static float32 StateT_X[5] = {0};         //��ǰX��״̬ת�ƾ���
static float32 Ja[5][5]    = {{0}};		   //�����Կ������˲���״̬Xƫ������Ja
static float32 Q[5][5]     = {{0}};         //�ⲿ����Э�������Q
static float32 K[5][5]     = {{0}};         //����������


static float32 Results[5][5]		= {0};         //���ڱ�����������Ľ��
//static float32 T_T[5][5]          = {0};         //���ǵ�C���Բ���ֱ�ӷ�������(����ָ ָ��)��
//												   //����ת�ú�ľ����Ǹþ����ڱ仯

//H�۲�����贫�����۲⵽��Ϊ���ԣ�����
float32  H[5][5] = {{1.0,  0.0,  0.0,  0.0,  0.0},
					{0.0,  1.0,  0.0,  0.0,  0.0},
					{0.0,  0.0,  1.0,  0.0,  0.0},
					{0.0,  0.0,  0.0,  1.0,  0.0},
					{0.0,  0.0,  0.0,  0.0,  1.0}};

//Э�������P��ʼ���� ��Ҳ������һ���������X״̬Э�������ÿ�����㶼����£�����
static float32  P_update_last[5][5] = {{1.0,  0.0,  0.0,  0.0,  0.0},
								   	    {0.0,  1.0,  0.0,  0.0,  0.0},
									    {0.0,  0.0,  1.0,  0.0,  0.0},
									    {0.0,  0.0,  0.0,  1.0,  0.0},
									    {0.0,  0.0,  0.0,  0.0,  1.0}};

//������Э������� ����
float32  R[5][5] = {{x_var^2, 0.0,     0.0,     0.0,  		0.0		},
					{0.0,  	  y_var^2, 0.0,     0.0,  		0.0		},
					{0.0,     0.0,     v_var^2, 0.0,  		0.0		},
					{0.0,     0.0,     0.0,     Seta_var^2, 0.0		},
					{0.0,     0.0,     0.0,  	0.0,  		w_var^2}};



float32 Kalman_Filters(float32* );    //Z�ǽṹ�壬ָ�������۲⵽��ֵ������x,y,v,Seta,w
float32 Transpose(float32 *, float32*, int,  int);          //����ת��   row:����     col:����
float32 Diag_Inverse(float32 *, float32*);      //���ܴ���Խ��������
float32 Dot(float32 *, float32 *,float32 *, int, int,int,  int); //���������������
																		 //r,c1:��߾��������, r,c2:�ұ߾��������
float32 Mat_Plus(float32*,float32*, float32 *,int, int);
float32 Mat_Sub(float32*, float32*,  float32 *,int, int);


#endif /* KALMAN_FILTERS_H_ */
