/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������S9KEAZ128���ܳ�MINI���İ�ĸ��
����    д��
��E-mail  ��
������汾��V1.0
�������¡�2017��11��11��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4
��Target  ��S9KEAZ128
��Crystal ��16.000Mhz
��busclock��40.000MHz
��pllclock��40.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

/*************************************************************************
*  �������ƣ�PIT_Init
*  ����˵������ʼ���ж϶�ʱ��
*  �������أ���
*  ����˵����u8Channel_No��PITͨ���˿ں�
*           cn  ����ʱ��ʱ�� ��λms
*  for example     PIT_Init(PIT_CHANNEL0,5);
*************************************************************************/
void PIT_Init(uint8_t u8Channel_No, uint32_t cn)
{  
    SIM->SCGC |= SIM_SCGC_PIT_MASK;     /*!< enable clock to PIT */
    
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;    
    PIT->CHANNEL[u8Channel_No].LDVAL = cn*BUS_CLK_KHZ ;//u32loadvalue;   //��ʼ��ʱ��                                  
    PIT->CHANNEL[u8Channel_No].TCTRL |= PIT_TCTRL_TIE_MASK;  
    PIT->CHANNEL[u8Channel_No].TCTRL |= PIT_TCTRL_TEN_MASK;
    PIT->CHANNEL[u8Channel_No].TFLG  |= PIT_TFLG_TIF_MASK;
    if (u8Channel_No)
    {  
      NVIC_EnableIRQ(PIT_CH1_IRQn);             
    }
    else
    {  
      NVIC_EnableIRQ(PIT_CH0_IRQn);
    }
    
}


void TestPIT(void)
{   

  LED_Init();
  LED_Ctrl(LEDALL, LEDON);
  PIT_Init(PIT_CHANNEL0,500);//��ʱ500MS
  while(1)
  {
  }
}

/***********************************************************
* �������� ��servo_pwm_init
* ����˵�� ����ʼ�����pwm��
* �������� ����
* ����˵�� ����
************************************************************/
void servo_pwm_init(void)
{
	gpio_init(PTI2, 1, 0);
	PIT_Init(PIT_CHANNEL0, 5);//��ʱ����ʼ��Ϊ5ms
}


   


