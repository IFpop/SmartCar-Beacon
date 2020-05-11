
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
#ifndef __KEY_H__
#define __KEY_H__

//定义模块号
typedef enum
{
    KEY0=0,
    KEY1=1,
    KEY2=2,
    KEY3=3,
    KEYALL=4,
} KEYn_e;
typedef enum
{
    KEYLOW=0,  //
    KEYHIGH=1, //   
    KEYFAIL=0xFF,
}KEYs_e;



//函数
extern void   KEY_Init(void);
extern uint8_t KEY_Read(KEYn_e keyno);
extern void Test_KEY(void);
extern void   KEY1_Init(void);
extern uint8_t KEY1_Read(KEYn_e keyno);
extern void Test_KEY1(void);
#endif 
