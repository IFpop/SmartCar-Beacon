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
	float Seta;      //角度，而非弧度
	float w;    // 角速度
}Event_kalman;


#define noise_a   2.0		 //process noise standard deviation for a
#define noise_yaw 0.3    	 //process noise standard deviation for yaw acceleration


uint8_t x_var = 3.0;  	 // Deviation of Microphone Measurement
uint8_t y_var = 3.0;  	 // Deviation of Microphone Measurement
uint8_t v_var = 1.0;	 // Deviation of Encoder Measurement
uint8_t Seta_var = 0.1;  // Deviation of Microphone Measurement
uint8_t w_var = 1.0;     // Deviation of Gyroscope Measurement
uint8_t dt = 0.3;        // 当实际运行EKF时会计算出前后两次测量的时间差，以此来替换这里的 dt

static float32 P_predict[5][5] 	 	= {{0}};        //当前 X状态的协方差矩阵
static float32 P_predict_last[5][5] = {{0}};		   //上一次 X状态的协方差矩阵
static float32 P_update[5][5] 	    = {{0}};        //当前修正后的协方差矩阵
//static float32 P_update_last[5][5]  = {0};		   //上一次修正后的协方差矩阵

static float32 X_predict[5]      = {0};		   //当前X状态的预测值
static float32 X_predict_last[5] = {0};		   //上一次 X状态的预测值
static float32 X_update[5]    = {0};		   //当前X状态修正后的预测值
static float32 X_update_last[5] = {0};		   //上一次 X状态修正后预测值

static float32 StateT_X[5] = {0};         //当前X的状态转移矩阵
static float32 Ja[5][5]    = {{0}};		   //非线性卡尔曼滤波，状态X偏导矩阵Ja
static float32 Q[5][5]     = {{0}};         //外部干扰协方差矩阵Q
static float32 K[5][5]     = {{0}};         //卡尔曼增益


static float32 Results[5][5]		= {0};         //用于保存矩阵运算后的结果
//static float32 T_T[5][5]          = {0};         //考虑到C语言不能直接返回数列(不是指 指针)，
//												   //所以转置后的矩阵都是该矩阵在变化

//H观测矩阵，设传感器观测到的为线性，常量
float32  H[5][5] = {{1.0,  0.0,  0.0,  0.0,  0.0},
					{0.0,  1.0,  0.0,  0.0,  0.0},
					{0.0,  0.0,  1.0,  0.0,  0.0},
					{0.0,  0.0,  0.0,  1.0,  0.0},
					{0.0,  0.0,  0.0,  0.0,  1.0}};

//协方差矩阵P初始化； 它也代表上一次修正后的X状态协方差矩阵，每次运算都会更新，变量
static float32  P_update_last[5][5] = {{1.0,  0.0,  0.0,  0.0,  0.0},
								   	    {0.0,  1.0,  0.0,  0.0,  0.0},
									    {0.0,  0.0,  1.0,  0.0,  0.0},
									    {0.0,  0.0,  0.0,  1.0,  0.0},
									    {0.0,  0.0,  0.0,  0.0,  1.0}};

//传感器协方差矩阵， 常量
float32  R[5][5] = {{x_var^2, 0.0,     0.0,     0.0,  		0.0		},
					{0.0,  	  y_var^2, 0.0,     0.0,  		0.0		},
					{0.0,     0.0,     v_var^2, 0.0,  		0.0		},
					{0.0,     0.0,     0.0,     Seta_var^2, 0.0		},
					{0.0,     0.0,     0.0,  	0.0,  		w_var^2}};



float32 Kalman_Filters(float32* );    //Z是结构体，指传感器观测到的值，包括x,y,v,Seta,w
float32 Transpose(float32 *, float32*, int,  int);          //矩阵转置   row:行数     col:列数
float32 Diag_Inverse(float32 *, float32*);      //仅能处理对角阵的求逆
float32 Dot(float32 *, float32 *,float32 *, int, int,int,  int); //用于两个矩阵相乘
																		 //r,c1:左边矩阵的行列, r,c2:右边矩阵的行列
float32 Mat_Plus(float32*,float32*, float32 *,int, int);
float32 Mat_Sub(float32*, float32*,  float32 *,int, int);


#endif /* KALMAN_FILTERS_H_ */
