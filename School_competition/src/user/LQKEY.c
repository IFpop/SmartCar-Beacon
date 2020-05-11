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

void KEY_Init(void)
{
  gpio_init (PTA0,GPI,HIGH);
  gpio_init (PTB5,GPI,HIGH);
  gpio_init (PTH2,GPI,HIGH);
  gpio_init (PTE6,GPI,HIGH);
}

uint8_t KEY_Read(KEYn_e keyno)
{    
   uint8_t kv=0x00; 
   
   switch(keyno) 
    {
      case KEY0:
        if(PTA0_IN==0) return 0x01;
        else           return 0x00;
      break;
      
      case KEY1:
        if(PTB5_IN==0) return 0x01;
        else           return 0x00;
      break;
      
      case KEY2:
        if(PTH2_IN==0) return 0x01;
        else           return 0x00;
      break; 
      
      case KEY3:
        if(PTE6_IN==0) return 0x01;
        else           return 0x00;
      break; 
      
      case KEYALL:
         if(PTA0_IN==0) kv|=0x01;
         if(PTB5_IN==0) kv|=0x02;
         if(PTH2_IN==0) kv|=0x03;
         if(PTE6_IN==0) kv|=0x04;
        return (kv);
      break; 
      default:
        return 0XFF;           
    }     
}
//����GPIO��������
void Test_KEY(void)
{   
    LED_Init();
    LED_Ctrl(LEDALL, LEDOFF);   
    KEY_Init();
    while (1)
    { 
		//�����Ű����źţ��ֱ����LED0,LED1,LED2,LED4
      if(KEY_Read(KEY0))  LED_Ctrl(LED0, LEDON);
      if(KEY_Read(KEY1))  LED_Ctrl(LED1, LEDON);
      if(KEY_Read(KEY2))  LED_Ctrl(LED2, LEDON);
      if(KEY_Read(KEY3))  LED_Ctrl(LED4, LEDON);       
      time_delay_ms(200);
      LED_Ctrl(LEDALL, LEDOFF);      
    }
}
void KEY1_Init(void)
{
  gpio_init (PTI2,GPI,HIGH);
  gpio_init (PTI3,GPI,HIGH);
  gpio_init (PTE2,GPI,HIGH);
  gpio_init (PTE3,GPI,HIGH);
  //���뿪��û���ⲿ����������ʹ���ڲ�����
  PORT->PUE2 |= (uint32)(1<<PTn(PTI2));//ʹ���ڲ�����
  PORT->PUE2 |= (uint32)(1<<PTn(PTI3));//ʹ���ڲ�����
  PORT->PUE1 |= (uint32)(1<<PTn(PTE2));//ʹ���ڲ�����
  PORT->PUE1 |= (uint32)(1<<PTn(PTE3));//ʹ���ڲ�����
}
uint8_t KEY1_Read(KEYn_e keyno)
{    
   uint8_t kv=0x00; 
   
   switch(keyno) 
    {
      case KEY0:
        if(PTI2_IN==0) return 0x01;
        else           return 0x00;
      break;
      
      case KEY1:
        if(PTI3_IN==0) return 0x01;
        else           return 0x00;
      break;
      
      case KEY2:
        if(PTE2_IN==0) return 0x01;
        else           return 0x00;
      break; 
      
      case KEY3:
        if(PTE3_IN==0) return 0x01;
        else           return 0x00;
      break; 
      
      case KEYALL:
         if(PTI2_IN==0) kv|=0x01;
         if(PTI3_IN==0) kv|=0x02;
         if(PTE2_IN==0) kv|=0x03;
         if(PTE3_IN==0) kv|=0x04;
        return (kv);
      break; 
      default:
        return 0XFF;           
    }     
}
//����GPIO���뿪�ع���
void Test_KEY1(void)
{   
    //�ⲿ�ָ�TEST_KEY������һ���ģ����ܶ�Ӧ���յĹܽŲ�һ��
    LED_Init();
    LED_Ctrl(LEDALL, LEDOFF);   
    KEY1_Init();
    while (1)
    {          
      if(KEY1_Read(KEY0))  LED_Ctrl(LED0, LEDON);
      if(KEY1_Read(KEY1))  LED_Ctrl(LED1, LEDON);
      if(KEY1_Read(KEY2))  LED_Ctrl(LED2, LEDON);
      if(KEY1_Read(KEY3))  LED_Ctrl(LED4, LEDON);       
      time_delay_ms(200);
      LED_Ctrl(LEDALL, LEDOFF);      
    }
}    
    

//



