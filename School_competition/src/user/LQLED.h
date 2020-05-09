
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱S9KEAZ128智能车核心板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2017年11月5日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR7.80.4
【Target  】S9KEAZ128
【Crystal 】16.000Mhz
【busclock】?0.000MHz
【pllclock】?0.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LED_H__
#define __LED_H__

//定义模块号
typedef enum
{ 
    LED0=0,
    LED1=1,
    LED2=2,
    LED3=3,
    LED4=4,
    LEDALL=5,//全部  
} LEDn_e;

typedef enum
{
    LEDON=0,  //亮
    LEDOFF=1, //灭
    LEDRVS=2, //反转  
}LEDs_e;

/*********************** UART功能函数 **************************/
//初始化
extern void LED_Init(void);
extern void LED_Ctrl(LEDn_e ledno, LEDs_e sta);
extern void TestLED(void);
/********************************************************************/

#endif 
