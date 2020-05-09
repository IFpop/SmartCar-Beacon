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

volatile KBI_Type * KBIx[2] = { KBI0,KBI1} ;

/*************************************************************************
*  函数名称：  KBI_Init
*  功能说明：  初始化中断
*  函数返回：
*  参数说明：
*  for example KBI_Init(KBIX0, KBI_PTA0, KBI_FALLING_LOW);//PTA0
*************************************************************************/
void KBI_Init(KBIn_e kbix,KBI_PTxn ptxn,KBI_Edge RiFal)
{
  
  if(kbix == KBIX0 )
    {
        SIM->SCGC   |= SIM_SCGC_KBI0_MASK;             /* enable clock to KBI0 */\
        KBIx[kbix]->SC  &= ~KBI_SC_KBIE_MASK ;
        /****
        初始化IO
        *****/
        FGPIOA->PIDR  &= ~(1<<PTn(ptxn));              /* enable GPIO input */    
        FGPIOA->PDDR  &= ~(1<<PTn(ptxn)); 
        if(RiFal) PORT->PUE0  &= ~(1<<PTn(ptxn));
        else PORT->PUE0  |= (1<<PTn(ptxn));
        
    }
    else if (kbix == KBIX1)
    {        
        SIM->SCGC   |= SIM_SCGC_KBI1_MASK;             /* enable clock to KBI1 */
        KBIx[kbix]->SC  &= ~KBI_SC_KBIE_MASK ;

        /****
        初始化IO
        *****/
        FGPIOB->PIDR  &= ~(1<<PTn(ptxn));              /* enable GPIO input */    
        FGPIOB->PDDR  &= ~(1<<PTn(ptxn)); 
        if(RiFal) PORT->PUE1  &= ~(1<<PTn(ptxn));
        else PORT->PUE1  |= (1<<PTn(ptxn));

    }

  if(RiFal)
  {
    KBIx[kbix]->ES  |= (1<< PTn(ptxn));
  }
  else
  {
    KBIx[kbix]->ES  &= ~(1<< PTn(ptxn));
  }
  KBIx[kbix]->PE |= (1 << PTn(ptxn)) ;

  PORT->IOFLT0 |= PORT_IOFLT0_FLTDIV1(0) ;
  PORT->IOFLT0 |= PORT_IOFLT0_FLTKBI0(1) ;
  KBIx[kbix]->SC  = (0
                     //|KBI_SC_KBMOD_MASK           //跳变沿和水平中断
                     |KBI_SC_KBIE_MASK              //中断使能
                     |KBI_SC_KBACK_MASK             //
                     |KBI_SC_KBSPEN_MASK          //锁存KBxSP
                     |KBI_SC_RSTKBSP_MASK           //清除KBIxSP
                      );
  
  if(kbix == KBIX0 )
   {
     NVIC_EnableIRQ(KBI0_IRQn);
   }
  else if (kbix == KBIX1)
    { 
      NVIC_EnableIRQ(KBI1_IRQn); 
    }
}

/*************************************************************************
*  函数名称：KBI_Disable
*  功能说明：初始化中断
*  函数返回：
*  参数说明：
*  for example  KBI_Disable(KBIX0,KBI_PTA0);//A0
*************************************************************************/
void KBI_Disable(KBIn_e kbix,KBI_PTxn ptxn)
{
    KBIx[kbix]->PE &= ~(1 << PTn(ptxn)) ;  
}
/*************************************************************************
*  函数名称：KBI_Enable
*  功能说明：初始化中断
*  函数返回：
*  参数说明：
*  for example  KBI_Enable(KBIX0,KBI_PTA0);//A0
*************************************************************************/
void KBI_Enable(KBIn_e kbix,KBI_PTxn ptxn)
{
  KBI0->SC |= KBI_SC_RSTKBSP_MASK ;    //清除中断标志位
  KBIx[kbix]->PE |= (1 << PTn(ptxn)) ;
}

//测试GPIO外部中断 母版上K0，K1按键有效，KBI是键盘中断
void TestKBI(void)
{   

  KBI_Init(KBIX0, KBI_PTB5, KBI_FALLING_LOW);//按下K0 LED反转
  KBI_Init(KBIX1, KBI_PTH2, KBI_FALLING_LOW);//按下K1 LED反转
  KBI_Enable(KBIX0,KBI_PTB5);
  KBI_Enable(KBIX1,KBI_PTH2);
  LED_Init();
  while(1)
  {
  }
}
