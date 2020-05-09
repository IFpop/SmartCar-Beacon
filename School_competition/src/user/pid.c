#include "pid.h"

static volatile int16_t target = 0;
static char txt[50];
// p = 11
// i = 0.02
float PID_P = 18;
float PID_I = 0.15;
        
void speed_contorl(void) 
{
	int16_t left_count = FTM_count_get(CFTM0);//��ȡ��������������
	int16_t right_count = FTM_count_get(CFTM1);
        
        //����ģʽ
        //Uart_SendChar(UARTR2, 0xa8);
        //sprintf(txt, "left:%d\nright:%d\ntarget:%d\n", left_count,right_count,target);
	//Uart_SendString(UARTR2, (uint8_t*)txt);
        //Uart_SendChar(UARTR2,0x00);

	FTM_count_clean(CFTM0);//��������� 
	FTM_count_clean(CFTM1);
	//�ö����ڳ��ٽ����ж� ��850����700  �����Ӧ target_count
	int left_pwm = My_pid(left_count, target);
	int right_pwm = My_pid(right_count, target);

        FTM_PWM_Duty(CFTM2, FTM_CH0, right_pwm);
        FTM_PWM_Duty(CFTM2, FTM_CH2, left_pwm);

	//��һ������  �Զ��ҵ�ģʽ��  ������ 700 ��850 ����ת�� ��Ӧ��Ŀ������������Ҫ������������������ڵ�ת���ڵ���PID����ʱ����Ӧ��target_pulse 
}

int My_pid(int16_t pulse, int16_t target_pulse){
   static int16_t sum_error = 0;//ƫ����� 					
   static int16_t error = 0;              //ֱ�Ӵ���ʱt�ڵ�������
   float PI_SUM = 0.0;
        
    error = target_pulse - pulse;
    sum_error += error;
    PI_SUM =PID_I * sum_error;
            
    if(PI_SUM>900)
            PI_SUM=900;
            
    float result = 0;
    result = PID_P * error + PI_SUM;//pid������result
            
    if (result > 900)//����޷� 
           result = 900;
    if (result < 0)
           result = 0;
   return result;
            //��ν��в��������� 
}

void Change_motor_target(int16_t num)
{
    target = num;
}