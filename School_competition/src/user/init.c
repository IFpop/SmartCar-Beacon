#include "include.h"

void all_Init()
{
	//��Ҫ��ʼ�����
	//FTM_PWM_init(CFTM1, FTM_CH1, FTM_PTE7, 100, 117);//PWM1 PTE7
	servo_pwm_init();
	//��ʼ��������
        Encode_init();

	//��Ҫ��ʼ�����
	FTM_PWM_init(CFTM2, FTM_CH2, FTM_PTD0, 12500, 0);//PWM2 PTH0   //�����
	FTM_PWM_init(CFTM2, FTM_CH0, FTM_PTH0, 12500, 0);//PWM2 PTD0
	//��Ҫ����io����������������·�����ģ��������Ŵ���
	gpio_init(PTE3, 1, 0);//������ʼ����ת  E3 = 0 I3 = 1 ��ת
	gpio_init(PTI3, 1, 1);
	gpio_init(PTE1, 1, 0);//����ҳ�ʼ����ת
	gpio_init(PTG7, 1, 1);//�����
	//����
        uart_init(UARTR2,1,9600);
        uart_enable_re_int(UARTR2);
	//����ͷ
        uart_init(UARTR1, 1, 115200);
        uart_enable_re_int(UARTR1);
}