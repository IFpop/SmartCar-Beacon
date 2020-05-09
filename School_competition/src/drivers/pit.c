/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱S9KEAZ128智能车MINI核心板母板
【编    写】
【E-mail  】
【软件版本】V1.0
【最后更新】2017年11月11日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR7.80.4
【Target  】S9KEAZ128
【Crystal 】16.000Mhz
【busclock】40.000MHz
【pllclock】40.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

/*************************************************************************
*  函数名称：PIT_Init
*  功能说明：初始化中断定时器
*  函数返回：无
*  参数说明：u8Channel_No：PIT通道端口号
*           cn  ：定时器时间 单位ms
*  for example     PIT_Init(PIT_CHANNEL0,5);
*************************************************************************/
void PIT_Init(uint8_t u8Channel_No, uint32_t cn)
{  
    SIM->SCGC |= SIM_SCGC_PIT_MASK;     /*!< enable clock to PIT */
    
    PIT->MCR &= ~PIT_MCR_MDIS_MASK;    
    PIT->CHANNEL[u8Channel_No].LDVAL = cn*BUS_CLK_KHZ ;//u32loadvalue;   //初始化时间                                  
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
  PIT_Init(PIT_CHANNEL0,500);//定时500MS
  while(1)
  {
  }
}

/***********************************************************
* 函数名称 ：servo_pwm_init
* 功能说明 ：初始化舵机pwm波
* 函数返回 ：无
* 参数说明 ：无
************************************************************/
void servo_pwm_init(void)
{
	gpio_init(PTI2, 1, 0);
	PIT_Init(PIT_CHANNEL0, 5);//定时器初始化为5ms
}


   


