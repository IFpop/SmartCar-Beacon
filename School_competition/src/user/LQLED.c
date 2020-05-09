/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������S9KEAZ128���ܳ�MINI���İ�ĸ��
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
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

void LED_Init(void)
{
    gpio_init (PTC2, GPO,HIGH);
    gpio_init (PTB4, GPO,HIGH);
    gpio_init (PTE5, GPO,HIGH);
    gpio_init (PTI4, GPO,HIGH);
    gpio_init (PTH6, GPO,HIGH);

}

void LED_Ctrl(LEDn_e ledno, LEDs_e sta)
{
    switch(ledno) 
    {
    case LED0:
      if(sta==LEDON)        PTC2_OUT=0; //Turn on target LED1 
      else if(sta==LEDOFF) PTC2_OUT=1; //Turn off target LED1 
      else if(sta==LEDRVS) gpio_turn(PTC2);//Toggle on target LED1
    break;
    
    case LED1:
      if(sta==LEDON)        PTB4_OUT=0; //Turn on target LED2 
      else if(sta==LEDOFF) PTB4_OUT=1; //Turn off target LED2 
      else if(sta==LEDRVS) gpio_turn(PTB4);//Toggle on target LED2
    break;
    
    case LED2:
      if(sta==LEDON)        PTE5_OUT=0; //Turn on target LED3 
      else if(sta==LEDOFF) PTE5_OUT=1; //Turn off target LED3 
      else if(sta==LEDRVS) gpio_turn(PTE5);//Toggle on target LED3
    break; 
    case LED3:
      if(sta==LEDON)        PTI4_OUT=0; //Turn on target LED3 
      else if(sta==LEDOFF) PTI4_OUT=1; //Turn off target LED3 
      else if(sta==LEDRVS) gpio_turn(PTI4);//Toggle on target LED3
    break; 
    case LED4:
      if(sta==LEDON)        PTH6_OUT=0; //Turn on target LED4
      else if(sta==LEDOFF) PTH6_OUT=1; //Turn off target LED4 
      else if(sta==LEDRVS) gpio_turn(PTH6);//Toggle on target LED4
    break; 
    case LEDALL:
      if(sta==LEDON) 
      {       
          PTC2_OUT=0; //Turn on target LED1 
          PTB4_OUT=0; //Turn on target LED2 
          PTE5_OUT=0;//Turn on target LED3 
          PTI4_OUT=0;
          PTH6_OUT=0;
      }
      else if(sta==LEDOFF)
      { 
          PTC2_OUT=1; //Turn on target LED1 
          PTB4_OUT=1; //Turn on target LED2 
          PTE5_OUT=1;//Turn on target LED3 
          PTI4_OUT=1;
          PTH6_OUT=1;
      }
      else if(sta==LEDRVS)
      {       
          gpio_turn(PTC2);
          gpio_turn(PTB4);
          gpio_turn(PTE5);
          gpio_turn(PTI4);
          gpio_turn(PTH6);
      }
    break;
    default:
    break;    
    }   
}


void time_delay_ms(uint16_t ms)
{  
  while(ms--)
  {
    delay_us(1000);
  }
}
void time_delay_ms2(uint16_t ms)
{
  uint16_t a;
  while(ms)
  {
    a=5000;
    while(a--);
    ms--;
  }
}

void TestLED(void)
{
    uint8 i=0;
    //��ʼ��LED
    LED_Init(); 
	//��ʼ�����е���Ϊ�ر�״̬
    LED_Ctrl(LEDALL, LEDOFF);
	//ʹ��while�����LEDȫ��ѭ������
    while (1)
    {  
	//ÿ��ѭ����ʼ��ʱ�����еƻָ�Ϊ��ʼ״̬
      LED_Ctrl(LEDALL, LEDOFF);
	//���ڽ�LED0��ת
      LED_Ctrl(LED0, LEDRVS); 
      time_delay_ms(50); //�ж�50ms���ٽ���ִ���������

	  //���½����еĵ���Ϊ0
      LED_Ctrl(LEDALL, LEDOFF);
	  //Ȼ��LED1��ת
      LED_Ctrl(LED1, LEDRVS); 
      time_delay_ms(50);

	  //ͬ��
      LED_Ctrl(LEDALL, LEDOFF);
      LED_Ctrl(LED2, LEDRVS); 
      time_delay_ms(50);

      LED_Ctrl(LEDALL, LEDOFF);
      LED_Ctrl(LED3, LEDRVS); 
      time_delay_ms(50);

      LED_Ctrl(LEDALL, LEDOFF);
      LED_Ctrl(LED4, LEDRVS); 
      time_delay_ms(50);
    } 
      
}
