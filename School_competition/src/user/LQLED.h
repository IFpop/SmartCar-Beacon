
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������S9KEAZ128���ܳ����İ�
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2017��11��5��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4
��Target  ��S9KEAZ128
��Crystal ��16.000Mhz
��busclock��?0.000MHz
��pllclock��?0.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LED_H__
#define __LED_H__

//����ģ���
typedef enum
{ 
    LED0=0,
    LED1=1,
    LED2=2,
    LED3=3,
    LED4=4,
    LEDALL=5,//ȫ��  
} LEDn_e;

typedef enum
{
    LEDON=0,  //��
    LEDOFF=1, //��
    LEDRVS=2, //��ת  
}LEDs_e;

/*********************** UART���ܺ��� **************************/
//��ʼ��
extern void LED_Init(void);
extern void LED_Ctrl(LEDn_e ledno, LEDs_e sta);
extern void TestLED(void);
/********************************************************************/

#endif 
