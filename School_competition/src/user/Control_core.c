#include "Control_core.h"

/*************************************************************************
*  函数名称：After_bluetoothIRQ
*  功能说明：处理蓝牙控制小车行走的动作
*  函数返回：无
*  参数说明：control_type：控制码   0xc1 —— 手动 (目前只实现了一种)
*            buffer ：缓存区数组
*************************************************************************/
void After_bluetoothIRQ(uint8_t control_type, uint8_t* buffer)
{
	int speed;
	if (control_type == 0xc1)
	{
		//首先会对接收到的字符串进行操作获取cmd,speed等信息
		//先确定相应模式
		int cmd;
		//从内存中读出字符串
		sscanf((const char*)buffer, "%d %d", &cmd, &speed);
		//speed = speed * 1000 / 10240;
		//两个电机输出pwm波
		//FTM_PWM_Duty(CFTM2, FTM_CH0, speed);
		//FTM_PWM_Duty(CFTM2, FTM_CH2, speed);
                Change_motor_target(200);
		switch (cmd)
		{
			//停车
		case 0:
			STOP();
			break;

			//切回找灯模式
		case 1:
			break;

			//后退
		case 2:
			BACK();
			break;

			//左行
		case 4:
			LEFT();
			break;

			//右行
		case 6:
			RIGHT();
			break;

			//顺时针
			//右轮电机设置为0，快速转动，外加右转
		case 7:
			Clockwise();
			break;

			//前进
		case 8:
			GO_AHEAD();
			break;

			//逆时针
			//左轮电机设置为0，快速转动，外加左转
		case 9:
			Anticlockwise();
			break;
		default:
			break;
		}
	}
}

/*************************************************************************
*  函数名称：CAMERA_deal
*  功能说明：处理摄像头捕捉到信号之后的操作
*  函数返回：无
*  参数说明：buffer ：缓存区数组
*            接收到(x,y,w,h) 分别是x,y坐标以及矩阵的宽度与高度
*************************************************************************/
void CAMERA_deal(uint8_t* buffer)
{
	static uint8 Notfind = 0; //达到4次连续的找不到才转圈
	static uint8 flag_last_state = 0; //标记上一次是否为not find
	static uint8 flag_left = 0;			//标记向左偏转

	//PD参数
	static float kp = 1;
	static float kd = 3;
        static float error = 0;
        static float last_error = 0;

	int x;
        int y;
        int w;
        int h;
	sscanf((const char*)buffer, "%d %d %d %d", &x, &y, &w, &h);
        
	/*printf("x = %d,y = %d, w = %d,h = %d", x,y,w,h);*/
	//车距离灯越远那么,w、h越小，所以当w,h达到一定值的时候(也就是到达区域，但不能撞到灯)，这个值需要测试出来
	//矩阵 x = 320  y = 240
	//现在没有找到灯
	if (x == -2000)
	{
		//如果上一次是找不到，现在也是找不到，连续4次，才开始转圈,不是连续的就将Notfind置为0
		if (flag_last_state)
			Notfind++;
		else
			Notfind = 0;
		if (Notfind == 5)
		{
                        if(flag_left)
                          Anticlockwise();
                        else
                          Clockwise();
                        Change_motor_target(1500);
			//FTM_PWM_Duty(CFTM2, FTM_CH0, 700);
			//FTM_PWM_Duty(CFTM2, FTM_CH2, 700);
			Notfind = 0;
		}
		flag_last_state = 1;
	}
	//找到灯了，应该返回的是x,y,w,h
	//x + w/2  == 160 时是中点
	else
	{
            flag_last_state = 0;
            int angle = 0;	
            if(w > 31 || h > 34)
            { 
              Change_motor_target(50);
              if(x > 160)
              {
                flag_left = 1;
                servo_pwm_duty(3480);
              }
              else
              {
                flag_left = 0;
                servo_pwm_duty(3280);
              }
            }
            else
            {
              //PD位置环控制
              error = (160 - (x+w/2))*150*1.0/ 160;
              angle = Servo_mid+kp*error+kd*(error-last_error);
              last_error = error;
              if (angle > Servo_left)
                      angle = Servo_left;
              if (angle < Servo_right)
                      angle = Servo_right;
              gpio_set(PTE3, 0); //电机左正转
              gpio_set(PTI3, 1);
              gpio_set(PTE1, 0); //电机右正转
              gpio_set(PTG7, 1);
              //FTM_PWM_Duty(CFTM1, FTM_CH1, angle);
              servo_pwm_duty(angle);
              //FTM_PWM_Duty(CFTM2, FTM_CH0, 700);
              //FTM_PWM_Duty(CFTM2, FTM_CH2, 700);
              Change_motor_target(900);
            }

	}
}


/********************************************************************
***********************基本控制函数**********************************
*********************************************************************/
void STOP(void)
{
	//将两个电机的Pwm波全部置为0
	FTM_PWM_Duty(CFTM2, FTM_CH0, 0);
	FTM_PWM_Duty(CFTM2, FTM_CH2, 0);
}
void BACK(void)
{
	//方向摆正
	//FTM_PWM_Duty(CFTM1, FTM_CH1, 117);
	servo_pwm_duty(Servo_mid);
	//将控制电机转向的io输出全部变成反转
	gpio_set(PTE3, 1); //电机左反转  E3 = 1 I3 = 0 反转
	gpio_set(PTI3, 0);
	gpio_set(PTE1, 1); //电机右反转
	gpio_set(PTG7, 0);
}
void LEFT(void)
{
	//将舵机的方向转为左边
	//FTM_PWM_Duty(CFTM1, FTM_CH1, 128);
	servo_pwm_duty(Servo_left);
}
void RIGHT(void)
{
	//同上，duty需要测试
	//FTM_PWM_Duty(CFTM1, FTM_CH1, 106);
	servo_pwm_duty(Servo_right);
}
void GO_AHEAD(void)
{
	//方向摆正
	//FTM_PWM_Duty(CFTM1, FTM_CH1, 117);
	servo_pwm_duty(Servo_mid);
	gpio_set(PTE3, 0); //电机左正转  E3 = 1 I3 = 0 正转
	gpio_set(PTI3, 1);
	gpio_set(PTE1, 0); //电机右正转
	gpio_set(PTG7, 1);
}
//顺时针
void Clockwise(void)
{
	//顺时针
	RIGHT();
	//左轮正转，右轮反转
	gpio_set(PTE3, 0); //电机左正转  E3 = 1 I3 = 0 正转
	gpio_set(PTI3, 1);
	gpio_set(PTE1, 1); //电机右反转
	gpio_set(PTG7, 0);
}
//逆时针
void Anticlockwise(void)
{
	//逆时针
	LEFT();
	//左轮反转，右轮正转
	gpio_set(PTE3, 1); //电机左反转
	gpio_set(PTI3, 0);
	gpio_set(PTE1, 0); //电机右正转
	gpio_set(PTG7, 1);
}

void Encode_init(void)
{
	PIT_Init(PIT_CHANNEL1, 50);//多长时间取一次数，这里定了个50ms

	FTM_count_init(CFTM0);
	FTM_count_init(CFTM1);
}
