#include "include.h"


/*************************************************************************
*  函数名称：testmotor
*  功能说明：电机测试程序
*  函数返回：无
*************************************************************************/
void testmotor(void)
{
	gpio_set(PTE3, 0); //电机左初始化正转  E3 = 1 I3 = 0 正转
	gpio_set(PTI3, 1);

	gpio_set(PTE1, 0); //电机右初始化正转
	gpio_set(PTG7, 1);

	//输出占空比为 65%的pwm波 ，貌似之前学长说过就是关于pwm波低于60%就不转来着
        //CH0右轮 ，CH2左轮
	//Change_servo_target(200);
         FTM_PWM_Duty(CFTM2, FTM_CH0, 650);
         FTM_PWM_Duty(CFTM2, FTM_CH2, 650);
}

/*************************************************************************
*  函数名称：testservo
*  功能说明：舵机测试程序
*  函数返回：无
*************************************************************************/
void testservo(void)
{
        
	servo_pwm_duty(Servo_left);
}

void testencode(void)
{
    GO_AHEAD();
    Change_servo_target(200);
}
