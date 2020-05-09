#include "include.h"

/*************************************************************************
*�������ƣ�RTC_Init
*����������sel_clk:rtcģ���ʱ��Դѡ��   RTC_LPOCLK:1KHz   RTC_BUSCLK:BUSCLK
*          int_ms:�жϵ�����,
*            sel_clk=RTC_LPOCLKʱ��int_ms���Դ�1��32768����ʱ��λ��S��
*            sel_clk=RTC_BUSCLKʱ��int_ms���Դ�1��819����ʱ��λ1ms��
*�������أ���
*���ܸ�Ҫ��RTC������ʼ��
*************************************************************************/
void RTC_Init(RTC_CLKSELn sel_clk,uint16 int_ms)
{
  uint16 mod_value;
  
  SIM->SCGC |= SIM_SCGC_RTC_MASK;    //��ʱ����  
  NVIC_DisableIRQ(RTC_IRQn);      //����RTC�ж�
  //����RTCģ��
  if(1 == sel_clk)
  {
    mod_value = int_ms;
    RTC->MOD = mod_value;   //����MODֵ 
    RTC->SC |= RTC_SC_RTCLKS(1);   //ѡ��ʱ��Դ��1KHz
    RTC->SC |= RTC_SC_RTCPS(7);   //ѡ��Ԥ��Ƶ:1000
    RTC->SC |= RTC_SC_RTIF_MASK | RTC_SC_RTIE_MASK; //�ж������ʹ��             
  }
  else
  {
    mod_value = int_ms * BUS_CLK_KHZ/1000;      //mod_value = int_ms * BUS_CLK_KHZ/1000
    RTC->MOD = mod_value;   //����MODֵ 
    RTC->SC |= RTC_SC_RTCLKS(3);   //ѡ��ʱ��Դ������ʱ��40?MHz
    RTC->SC |= RTC_SC_RTCPS(7);   //ѡ��Ԥ��Ƶ:1000,���40Mhz/1000=40kHz, RTC counter increases every 50 us 
    RTC->SC |= RTC_SC_RTIF_MASK | RTC_SC_RTIE_MASK; //�ж������ʹ��
  }
  //RTC->MOD =80;
  //RTC->MOD = mod_value;   //����MODֵ 
  NVIC_EnableIRQ(RTC_IRQn);
}


void TestRTC(void)
{  
  DisableInterrupts ; 
  EnableInterrupts;
  LED_Init();
  LED_Ctrl(LEDALL, LEDOFF);
  RTC_Init(RTC_LPOCLK,1);//��ʼ��rtcģ�飬��ʱ�ж�����1s 
  LCD_Init();
  while(1)
  {
  }
}
uint8_t Sec,Min,Hour;
//RTC�жϺ���
void RTC_ISR(void)
{ 
  uint8_t  txt[30]="X:";
  RTC->SC |= RTC_SC_RTIF_MASK;  /* clear interrupt flag */ 
  Sec++;
  LED_Ctrl(LEDALL, LEDRVS);
  if (Sec>=60)
  {
    Min++;
    Sec=0;
  }
   if (Min>=60)
  {
    Hour++;
    Min=0;
  }
  sprintf((char*)txt,"TIME:%02d:%02d:%02d",Hour,Min,Sec);
  LCD_P6x8Str(0,0,txt);
}
