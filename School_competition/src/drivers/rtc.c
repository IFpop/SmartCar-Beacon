#include "include.h"

/*************************************************************************
*函数名称：RTC_Init
*函数参数：sel_clk:rtc模块的时钟源选择   RTC_LPOCLK:1KHz   RTC_BUSCLK:BUSCLK
*          int_ms:中断的秒数,
*            sel_clk=RTC_LPOCLK时，int_ms可以从1到32768，定时单位是S；
*            sel_clk=RTC_BUSCLK时，int_ms可以从1到819。定时单位1ms；
*函数返回：无
*功能概要：RTC驱动初始化
*************************************************************************/
void RTC_Init(RTC_CLKSELn sel_clk,uint16 int_ms)
{
  uint16 mod_value;
  
  SIM->SCGC |= SIM_SCGC_RTC_MASK;    //开时钟门  
  NVIC_DisableIRQ(RTC_IRQn);      //禁用RTC中断
  //配置RTC模块
  if(1 == sel_clk)
  {
    mod_value = int_ms;
    RTC->MOD = mod_value;   //设置MOD值 
    RTC->SC |= RTC_SC_RTCLKS(1);   //选择时钟源；1KHz
    RTC->SC |= RTC_SC_RTCPS(7);   //选择预分频:1000
    RTC->SC |= RTC_SC_RTIF_MASK | RTC_SC_RTIE_MASK; //中断清除并使能             
  }
  else
  {
    mod_value = int_ms * BUS_CLK_KHZ/1000;      //mod_value = int_ms * BUS_CLK_KHZ/1000
    RTC->MOD = mod_value;   //设置MOD值 
    RTC->SC |= RTC_SC_RTCLKS(3);   //选择时钟源；总线时钟40?MHz
    RTC->SC |= RTC_SC_RTCPS(7);   //选择预分频:1000,如果40Mhz/1000=40kHz, RTC counter increases every 50 us 
    RTC->SC |= RTC_SC_RTIF_MASK | RTC_SC_RTIE_MASK; //中断清除并使能
  }
  //RTC->MOD =80;
  //RTC->MOD = mod_value;   //设置MOD值 
  NVIC_EnableIRQ(RTC_IRQn);
}


void TestRTC(void)
{  
  DisableInterrupts ; 
  EnableInterrupts;
  LED_Init();
  LED_Ctrl(LEDALL, LEDOFF);
  RTC_Init(RTC_LPOCLK,1);//初始化rtc模块，定时中断周期1s 
  LCD_Init();
  while(1)
  {
  }
}
uint8_t Sec,Min,Hour;
//RTC中断函数
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
