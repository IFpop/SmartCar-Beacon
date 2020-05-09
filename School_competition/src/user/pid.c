#include "pid.h"

static volatile int16_t target = 0;
static char txt[50];
// p = 11
// i = 0.02
float PID_P = 18;
float PID_I = 0.15;
        
void speed_contorl(void) 
{
	int16_t left_count = FTM_count_get(CFTM0);//获取左右两轮脉冲数
	int16_t right_count = FTM_count_get(CFTM1);
        
        //波形模式
        //Uart_SendChar(UARTR2, 0xa8);
        //sprintf(txt, "left:%d\nright:%d\ntarget:%d\n", left_count,right_count,target);
	//Uart_SendString(UARTR2, (uint8_t*)txt);
        //Uart_SendChar(UARTR2,0x00);

	FTM_count_clean(CFTM0);//清空脉冲数 
	FTM_count_clean(CFTM1);
	//得对现在车速进行判断 是850还是700  传入对应 target_count
	int left_pwm = My_pid(left_count, target);
	int right_pwm = My_pid(right_count, target);

        FTM_PWM_Duty(CFTM2, FTM_CH0, right_pwm);
        FTM_PWM_Duty(CFTM2, FTM_CH2, left_pwm);

	//有一个问题  自动找灯模式下  车轮有 700 和850 两种转速 对应的目标脉冲数都需要测量，并且须根据现在的转速在调用PID函数时给对应的target_pulse 
}

int My_pid(int16_t pulse, int16_t target_pulse){
   static int16_t sum_error = 0;//偏差积分 					
   static int16_t error = 0;              //直接处理定时t内的脉冲数
   float PI_SUM = 0.0;
        
    error = target_pulse - pulse;
    sum_error += error;
    PI_SUM =PID_I * sum_error;
            
    if(PI_SUM>900)
            PI_SUM=900;
            
    float result = 0;
    result = PID_P * error + PI_SUM;//pid计算结果result
            
    if (result > 900)//输出限幅 
           result = 900;
    if (result < 0)
           result = 0;
   return result;
            //如何进行参数调整？ 
}

void Change_motor_target(int16_t num)
{
    target = num;
}