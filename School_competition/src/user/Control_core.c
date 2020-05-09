#include "Control_core.h"

/*************************************************************************
*  �������ƣ�After_bluetoothIRQ
*  ����˵����������������С�����ߵĶ���
*  �������أ���
*  ����˵����control_type��������   0xc1 ���� �ֶ� (Ŀǰֻʵ����һ��)
*            buffer ������������
*************************************************************************/
void After_bluetoothIRQ(uint8_t control_type, uint8_t* buffer)
{
	int speed;
	if (control_type == 0xc1)
	{
		//���Ȼ�Խ��յ����ַ������в�����ȡcmd,speed����Ϣ
		//��ȷ����Ӧģʽ
		int cmd;
		//���ڴ��ж����ַ���
		sscanf((const char*)buffer, "%d %d", &cmd, &speed);
		//speed = speed * 1000 / 10240;
		//����������pwm��
		//FTM_PWM_Duty(CFTM2, FTM_CH0, speed);
		//FTM_PWM_Duty(CFTM2, FTM_CH2, speed);
                Change_motor_target(200);
		switch (cmd)
		{
			//ͣ��
		case 0:
			STOP();
			break;

			//�л��ҵ�ģʽ
		case 1:
			break;

			//����
		case 2:
			BACK();
			break;

			//����
		case 4:
			LEFT();
			break;

			//����
		case 6:
			RIGHT();
			break;

			//˳ʱ��
			//���ֵ������Ϊ0������ת���������ת
		case 7:
			Clockwise();
			break;

			//ǰ��
		case 8:
			GO_AHEAD();
			break;

			//��ʱ��
			//���ֵ������Ϊ0������ת���������ת
		case 9:
			Anticlockwise();
			break;
		default:
			break;
		}
	}
}

/*************************************************************************
*  �������ƣ�CAMERA_deal
*  ����˵������������ͷ��׽���ź�֮��Ĳ���
*  �������أ���
*  ����˵����buffer ������������
*            ���յ�(x,y,w,h) �ֱ���x,y�����Լ�����Ŀ����߶�
*************************************************************************/
void CAMERA_deal(uint8_t* buffer)
{
	static uint8 Notfind = 0; //�ﵽ4���������Ҳ�����תȦ
	static uint8 flag_last_state = 0; //�����һ���Ƿ�Ϊnot find
	static uint8 flag_left = 0;			//�������ƫת

	//PD����
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
	//�������ԽԶ��ô,w��hԽС�����Ե�w,h�ﵽһ��ֵ��ʱ��(Ҳ���ǵ������򣬵�����ײ����)�����ֵ��Ҫ���Գ���
	//���� x = 320  y = 240
	//����û���ҵ���
	if (x == -2000)
	{
		//�����һ�����Ҳ���������Ҳ���Ҳ���������4�Σ��ſ�ʼתȦ,���������ľͽ�Notfind��Ϊ0
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
	//�ҵ����ˣ�Ӧ�÷��ص���x,y,w,h
	//x + w/2  == 160 ʱ���е�
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
              //PDλ�û�����
              error = (160 - (x+w/2))*150*1.0/ 160;
              angle = Servo_mid+kp*error+kd*(error-last_error);
              last_error = error;
              if (angle > Servo_left)
                      angle = Servo_left;
              if (angle < Servo_right)
                      angle = Servo_right;
              gpio_set(PTE3, 0); //�������ת
              gpio_set(PTI3, 1);
              gpio_set(PTE1, 0); //�������ת
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
***********************�������ƺ���**********************************
*********************************************************************/
void STOP(void)
{
	//�����������Pwm��ȫ����Ϊ0
	FTM_PWM_Duty(CFTM2, FTM_CH0, 0);
	FTM_PWM_Duty(CFTM2, FTM_CH2, 0);
}
void BACK(void)
{
	//�������
	//FTM_PWM_Duty(CFTM1, FTM_CH1, 117);
	servo_pwm_duty(Servo_mid);
	//�����Ƶ��ת���io���ȫ����ɷ�ת
	gpio_set(PTE3, 1); //�����ת  E3 = 1 I3 = 0 ��ת
	gpio_set(PTI3, 0);
	gpio_set(PTE1, 1); //����ҷ�ת
	gpio_set(PTG7, 0);
}
void LEFT(void)
{
	//������ķ���תΪ���
	//FTM_PWM_Duty(CFTM1, FTM_CH1, 128);
	servo_pwm_duty(Servo_left);
}
void RIGHT(void)
{
	//ͬ�ϣ�duty��Ҫ����
	//FTM_PWM_Duty(CFTM1, FTM_CH1, 106);
	servo_pwm_duty(Servo_right);
}
void GO_AHEAD(void)
{
	//�������
	//FTM_PWM_Duty(CFTM1, FTM_CH1, 117);
	servo_pwm_duty(Servo_mid);
	gpio_set(PTE3, 0); //�������ת  E3 = 1 I3 = 0 ��ת
	gpio_set(PTI3, 1);
	gpio_set(PTE1, 0); //�������ת
	gpio_set(PTG7, 1);
}
//˳ʱ��
void Clockwise(void)
{
	//˳ʱ��
	RIGHT();
	//������ת�����ַ�ת
	gpio_set(PTE3, 0); //�������ת  E3 = 1 I3 = 0 ��ת
	gpio_set(PTI3, 1);
	gpio_set(PTE1, 1); //����ҷ�ת
	gpio_set(PTG7, 0);
}
//��ʱ��
void Anticlockwise(void)
{
	//��ʱ��
	LEFT();
	//���ַ�ת��������ת
	gpio_set(PTE3, 1); //�����ת
	gpio_set(PTI3, 0);
	gpio_set(PTE1, 0); //�������ת
	gpio_set(PTG7, 1);
}

void Encode_init(void)
{
	PIT_Init(PIT_CHANNEL1, 50);//�೤ʱ��ȡһ���������ﶨ�˸�50ms

	FTM_count_init(CFTM0);
	FTM_count_init(CFTM1);
}
