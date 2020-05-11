#include "include.h"

void all_Init()
{
	//需要初始化舵机
	//FTM_PWM_init(CFTM1, FTM_CH1, FTM_PTE7, 100, 117);//PWM1 PTE7
	servo_pwm_init();
	//初始化编码器
        Encode_init();

	//需要初始化电机
	FTM_PWM_init(CFTM2, FTM_CH2, FTM_PTD0, 12500, 0);//PWM2 PTH0   //电机左
	FTM_PWM_init(CFTM2, FTM_CH0, FTM_PTH0, 12500, 0);//PWM2 PTD0
	//需要两个io输出，这是驱动板电路决定的，具体引脚待定
	gpio_init(PTE3, 1, 0);//电机左初始化正转  E3 = 0 I3 = 1 正转
	gpio_init(PTI3, 1, 1);
	gpio_init(PTE1, 1, 0);//电机右初始化正转
	gpio_init(PTG7, 1, 1);//电机右
	//蓝牙
        uart_init(UARTR2,1,9600);
        uart_enable_re_int(UARTR2);
	//摄像头
        uart_init(UARTR1, 1, 115200);
        uart_enable_re_int(UARTR1);
}