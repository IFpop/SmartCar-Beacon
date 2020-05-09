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

/*
通道名       默认引脚    重映射引脚
FTM0_CH0      PTA0         PTB2
FTM0_CH1      PTA1         PTB3
FTM1_CH0      PTC4         PTH2
FTM1_CH1      PTC5         PTE7
FTM2_CH0      PTC0         PTH0 , PTF0
FTM2_CH1      PTC1         PTH1 , PTF1
FTM2_CH2      PTC2         PTD0 , PTG4
FTM2_CH3      PTC3         PTD1 , PTG5
FTM2_CH4      PTB4         PTG6
FTM2_CH5      PTB5         PTG7
*/

FTM_Type * FTMx[3] = { FTM0,FTM1,FTM2};

/*************************************************************************
*  函数名称：FTM_PWM_init
*  功能说明：pwm初始化
*  函数返回：无
*  参数说明：ftm：    PWM模块
ch:      通道
ptxn:    引脚
freq  ： 频率
duty  ： 占空比 0-1000    可以调节FTM_PRECISON这个系数来改变精度
for example       FTM_PWM_init(CFTM0, FTM_CH1, FTM_PTA0，10000, 10);//PWM1 PTA0       
*************************************************************************/
void FTM_PWM_init(FTMn_e ftm, FTM_CHn_e ch,FTM_PTxn ptxn ,uint32_t freq, uint32_t duty)
{
  uint32 clk_hz ;
  uint16 mod;
  uint8  ps;
  uint16 cv;
  uint8_t   channels;
  clk_hz = CORE_CLK_HZ ;
  
  //通过系统时钟
  mod = (clk_hz >> (16+4) ) / freq ;     
  ps = 0;
  while((mod >> ps) >= 1)             // 等 (mod >> ps) < 1 才退出 while 循环 ，即求 PS 的最小值
  {
    ps++;
  }
  //ASSERT(ps <= 0x07);                // 断言， PS 最大为 0x07 ，超过此值，则 PWM频率设置过低，或 Bus 频率过高
  if(ps)
  {
    mod = 0xffff ;
  }
  else
  {
    mod = (clk_hz >> (ps+4)) / freq; // 求 MOD 的值
  }
  //PWM信号的周期和计数器计数周期有关，PWM周期=（MOD-CNTIN+1）*时钟周期
  cv = (duty * (mod - 0 + 1)) / FTM_PRECISON;  //系数
  
  switch(ftm)
  {
  case CFTM0:
    channels = 2;
    SIM->SCGC |= SIM_SCGC_FTM0_MASK;
    if (ch==FTM_CH0)
    {
      if (ptxn==FTM_PTA0)
        SIM->PINSEL &=~SIM_PINSEL_FTM0PS0_MASK ;  // PWM0 PTA0
      else
        SIM->PINSEL |= SIM_PINSEL_FTM0PS0_MASK ;  // PWM0 PTB2
    }
    else 
    {
      if (ptxn==FTM_PTA1)
        SIM->PINSEL &=~SIM_PINSEL_FTM0PS1_MASK ;  // PWM1 PTA1
      else
        SIM->PINSEL |= SIM_PINSEL_FTM0PS1_MASK ;  // PWM1 PTB3
    }
    
    break ;
  case CFTM1:
    channels = 2;
    SIM->SCGC |= SIM_SCGC_FTM1_MASK;
    if (ch==FTM_CH0)
    {
      if (ptxn==FTM_PTC4)
        SIM->PINSEL &= ~SIM_PINSEL_FTM1PS0_MASK ;  // PWM0 PTC4 （JTAG）
      else 
        SIM->PINSEL |= SIM_PINSEL_FTM1PS0_MASK ;  // PWM0 PTH2
    }
    else 
    {
      if (ptxn==FTM_PTC5)
        SIM->PINSEL &= ~SIM_PINSEL_FTM1PS1_MASK ;  // PWM1 PTC5
      else
        SIM->PINSEL |= SIM_PINSEL_FTM1PS1_MASK ;  // PWM1 PTE7
    }  
    break ;
  case CFTM2:
    channels = 6;
    SIM->SCGC  |= SIM_SCGC_FTM2_MASK;
    if (ch==FTM_CH0)
    {
      if (ptxn==FTM_PTC0)
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(0); //PWM0 PTC0
      else if (ptxn==FTM_PTH0)
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(1); //PWM0 PTH0
      else if (ptxn==FTM_PTF0)
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS0(2); //PWM0 PTF0
    }
    else if (ch==FTM_CH1)
    {
      if (ptxn==FTM_PTC1)
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(0); //PWM1 PTC1
      else if (ptxn==FTM_PTH1)
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(1); //PWM1 PTH1
      else if (ptxn==FTM_PTF1)
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS1(2); //PWM1 PTF1
    } 
    
    else if (ch==FTM_CH2)
    {
      if (ptxn==FTM_PTC2)
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(0); //PWM2 PTC2
      else if (ptxn==FTM_PTD0)
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(1); //PWM2 PTD0
      else if (ptxn==FTM_PTG4)
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS2(2); //PWM2 PTG4
    }  
    
    else if (ch==FTM_CH3)
    {
      if (ptxn==FTM_PTC3)
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(0); //PWM3 PTC3
      else if (ptxn==FTM_PTD1)
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(1); //PWM3 PTD1
      else if (ptxn==FTM_PTG5)
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS3(2); //PWM3 PTG5
    }  
    
    else if (ch==FTM_CH4)
    {
      if (ptxn==FTM_PTB4)
        SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS4_MASK; //PWM4 PTB4
      else
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS4_MASK; //PWM4 PTG6
    }    
    else if (ch==FTM_CH5)
    {
      if (ptxn==FTM_PTB5)
        SIM->PINSEL1 &= ~SIM_PINSEL1_FTM2PS5_MASK; //PWM5 PTB5 
      else
        SIM->PINSEL1 |= SIM_PINSEL1_FTM2PS5_MASK; //PWM5 PTG7
    }     
    break ;
  default:
    break;
  }
  FTMx[ftm]->SC = 0 ;
  FTMx[ftm]->CONTROLS[ch].CnSC = 0 ;
  ASSERT(ch <= channels);          // 断言， ch 最大为 channels ，超过此值，则无通道
  //边沿对齐，正极性PWM
  FTMx[ftm]->CONTROLS[ch].CnSC |= (0
                                   //  |FTM_CnSC_ELSA_MASK
                                   |FTM_CnSC_ELSB_MASK  
                                     //   |FTM_CnSC_MSA_MASK
                                     |FTM_CnSC_MSB_MASK
                                       //   |FTM_CnSC_CHIE_MASK
                                       //    |FTM_CnSC_CHF_MASK
                                       );
  FTMx[ftm]->SC &= ~FTM_SC_CPWMS_MASK;
  //********************

  //freq = MOD - CNTIN + 0x0001
  //duty = CnV - CNTIN ;
  //********************
  //    FTMx[ftm]->CNTIN = 0 ;
  FTMx[ftm]->MOD = mod ;
  FTMx[ftm]->CONTROLS[ch].CnV = cv;
  FTMx[ftm]->SC = FTM_SC_CLKS(1)|FTM_SC_PS(4) ;//系统时钟，16分频  2.5M
}
/*************************************************************************
*  函数名称：FTM_PWM_Duty
*  功能说明：pwm赋值
*  函数返回：无
*  参数说明：FTMn_e： PWM模块
ch    :  通道
duty  ： 占空比 0-1000    可以调节FTM_PRECISON这个系数来改变精度
for axample         FTM_PWM_Duty(CFTM0, FTM_CH1, 20);       
*************************************************************************/
void FTM_PWM_Duty(FTMn_e ftm, FTM_CHn_e ch, uint32_t duty)
{
  uint32_t cv;
  uint32_t mod = 0;
  uint8_t   channels;
  
  ASSERT(duty <= FTM_PRECISON); 
  switch(ftm)
  {
  case CFTM0:
    channels = 2;
    break ;
  case CFTM1:
    channels = 2;
    break ;
  case CFTM2:
    channels = 6;
    break ;
  default:
    break;
  }
  ASSERT(ch <= channels);                     // 断言， ch 最大为 channels ，超过此值，则无通道
  //Mod是/**< Modulo, offset: 0x8 */
  mod = FTMx[ftm]->MOD ;
  cv = (duty * (mod - 0 + 1)) / FTM_PRECISON;   //系数
  FTMx[ftm]->CONTROLS[ch].CnV = cv  ;
}

/*************************************************************************
*  函数名称：FTM_count_init
*  功能说明：外部计数模式初始化
*  函数返回：无
*  参数说明：FTMn_e： PWM模块
ch    :  通道

for axample         FTM_count_init(CFTM0);       
*************************************************************************/
void FTM_count_init(FTMn_e ftm)
{
  switch(ftm)
  {
  case CFTM0:
    SIM->SCGC |= SIM_SCGC_FTM0_MASK;              //开启FTM外设时钟
    SIM->PINSEL &= ~SIM_PINSEL_FTM0CLKPS_MASK;    //清除外部时钟引脚选择
    PORT->PUE1 |= (uint32)(1<<0);                 //选择上拉
    SIM->PINSEL |= SIM_PINSEL_FTM0CLKPS(1);       //选择外部时钟输入引脚 E0
    break;
  case CFTM1:
    SIM->SCGC |= SIM_SCGC_FTM1_MASK;              //开启FTM外设时钟
    SIM->PINSEL &= ~SIM_PINSEL_FTM1CLKPS_MASK;    //清除外部时钟引脚选择
    PORT->PUE1 |= (uint32)(1<<7);                 //选择上拉
    SIM->PINSEL |= SIM_PINSEL_FTM1CLKPS(2);       //选择外部时钟输入引脚 E7
    break;
  case CFTM2:
    SIM->SCGC |= SIM_SCGC_FTM2_MASK;              //开启FTM外设时钟
    SIM->PINSEL &= ~SIM_PINSEL_FTM2CLKPS_MASK;    //清除外部时钟引脚选择
    FTM2->CNTIN = 0;
    PORT->PUE0 |= (uint32)(1<<5);
    SIM->PINSEL |= SIM_PINSEL_FTM2CLKPS(0);       //选择外部时钟输入引脚 A5  JTAG引脚
    break;      
  }                                  
  FTMx[ftm]->SC |= FTM_SC_PS(0);	            //分频系数	
  FTMx[ftm]->SC |= FTM_SC_CLKS(3);                //选择外部时钟作为FTM输入时钟
  FTMx[ftm]->CNT = 0;                             //加载初始化值
}

/*************************************************************************
*  函数名称：FTM_count_get
*  功能说明：以时钟输入模式读取外部计数值
*  函数返回：计数数值
*  参数说明：FTMn_e： PWM模块   
for axample         FTM_count_init(CFTM0);       
*************************************************************************/
uint16 FTM_count_get(FTMn_e ftm)
{
  return FTMx[ftm]->CNT ;
}

/*************************************************************************
*  函数名称：FTM_count_clean
*  功能说明：计数清零
*  函数返回：无
*  参数说明：FTMn_e： PWM模块    
for axample         FTM_count_init(CFTM0);       
*************************************************************************/
void FTM_count_clean(FTMn_e ftm)
{
  FTMx[ftm]->CNT = 0;
}



//测试PWM/OLED及电机控制功能
void TestFTM_PWM(void)
{  
  char  txt[30]="X:";   
  
  //LCD_Init();
  //FTM_PWM_init(CFTM2, FTM_CH0,FTM_PTH0, 12500, 200);//PWM2 PTH0
  //FTM_PWM_init(CFTM2, FTM_CH1,FTM_PTH1, 12500, 400);//PWM2 PTH1
  //FTM_PWM_init(CFTM2, FTM_CH2,FTM_PTD0, 12500, 600);//PWM2 PTD0
  //FTM_PWM_init(CFTM2, FTM_CH3,FTM_PTD1, 12500, 800);//PWM2 PTD1
  //舵机接口
  FTM_PWM_init(CFTM1, FTM_CH1,FTM_PTE7, 100, 200);//PWM1 PTE7

  
  //sprintf(txt,"FTM2_CH0:12500HZ 20%%");
  //LCD_P6x8Str(0,0,(uint8_t*)txt);
  //sprintf(txt,"FTM2_CH1:12500HZ 40%%");
  //LCD_P6x8Str(0,1,(uint8_t*)txt);
  //sprintf(txt,"FTM2_CH2:12500HZ 60%%");
  //LCD_P6x8Str(0,2,(uint8_t*)txt);
  //sprintf(txt,"FTM2_CH3:12500HZ 80%%");
  //LCD_P6x8Str(0,3,(uint8_t*)txt);
  //sprintf(txt,"FTM1_CH1: 100 HZ ");
  //LCD_P6x8Str(0,4,(uint8_t*)txt);
  while(1)
  {
    for (int i=100;i<200;i+=10)
    {
      FTM_PWM_Duty(CFTM1, FTM_CH1,i);
      /*sprintf(txt,"FTM1_CH1: %02d %% ",(i/10));
      LCD_P6x8Str(0,5,(uint8_t*)txt);*/
    time_delay_ms(500);
    }
  }
}
//测试编码器脉冲采集功能
void TestFTM_InputCapture(void)
{  
  LCD_Init();
  uart_init(UARTR2,Remap ,9600);//A3-TX1
  uart_enable_re_int(UARTR2);
  Uart_SendString(UARTR2,(uint8_t*)"TestFTM_CNT: \n");
  FTM_count_init(CFTM1);//输入用E7
  FTM_count_init(CFTM0);//输入用E0
  gpio_init (PTH5,GPI,HIGH);
  gpio_init (PTH7,GPI,HIGH);
  PIT_Init(PIT_CHANNEL1,500);//定时500MS
  while(1)
  {    
  }
}



























/*****************************************************************************//*!
*
* @brief  set the ftm channel value.
*               
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    u16CounterValue   the CNTIN value required to set.
*
* @return none.
*
* @ Pass/ Fail criteria: none
*
* @see FTM_SetModValue.
*
*****************************************************************************/
void FTM_SetCounterInitValue(FTMn_e pFTM, uint16_t u16CounterValue)
{
  FTMx[pFTM]->CNTIN = u16CounterValue;
  if(FTMx[pFTM]->MODE & FTM_MODE_FTMEN_MASK)
  {
    FTMx[pFTM]->PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
  }
  else
  {
  }
}

uint16_t FTM_GetCounterValue(FTMn_e pFTM)
{
  return (FTMx[pFTM]->CNTIN );    
}

/*********************************************************************************//*!
*
* @brief set LDOK bit.
*        
* @param[in]    pFTM              pointer to one of three FTM base register address.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_SetLoadMatchChannel.
*
*********************************************************************************/
void FTM_SetLoadEnable(FTMn_e pFTM)
{
  FTMx[pFTM]->PWMLOAD |= FTM_PWMLOAD_LDOK_MASK;
}

/*********************************************************************************//*!
*
* @brief set the channel in the matching process.
*        
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    u8Matchchannel    the channel in the matching process.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_SetLoadEnable.
*
*********************************************************************************/
void FTM_SetLoadMatchChannel(FTMn_e pFTM, FTM_CHn_e u8Matchchannel)
{
  FTMx[pFTM]->PWMLOAD |= u8Matchchannel;
}

/*********************************************************************************//*!
*
* @brief disable the channel input capture filter.
*        
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    ch     the channel number: 0~3.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_InputCaptureFilterSet.
*
*********************************************************************************/
void FTM_InputCaptureFilterClr(FTMn_e pFTM, FTM_CHn_e ch)
{
  FTMx[pFTM]->FILTER &= ~(0x000F << (ch << 2));
}

/*********************************************************************************//*!
*
* @brief set the channel input capture filter value.
*        
* @param[in]    pFTM              pointer to one of three FTM base register address.
* @param[in]    ch     the channel number: 0~3.
* @param[in]    u8FilterValue     fliter cycles:1~15, 0: disable channel filter.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
* @see FTM_InputCaptureFilterClr.
*
*********************************************************************************/
void FTM_InputCaptureFilterSet(FTMn_e pFTM, FTM_CHn_e ch, uint8_t u8FilterValue)
{
  if (u8FilterValue)
  {
    FTMx[pFTM]->FILTER |= (u8FilterValue << (ch << 2));
  }
  else
  {
    FTM_InputCaptureFilterClr(pFTM, ch);
  }
}  
/*********************************************************************************//*!
*
* @brief general configuration to FTM_No to input capture mode, enable interrupt.
*        
* @param[in]    pFTM                  pointer to one of three FTM base register address.
* @param[in]    Channel               channel number to be configured.
* @param[in]    CaptureMode           select capture edge: rising, falling or both.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*********************************************************************************/
void FTM_InputCaptureInit(FTMn_e pFTM, FTM_CHn_e ch, uint8_t u8CaptureMode)
{ 
  
  /* open the clock gate */
  if ((CFTM0 == pFTM) && (ch < 2))
  {
    SIM->SCGC |= SIM_SCGC_FTM0_MASK;
    //NVIC_EnableIRQ(FTM0_IRQn);
  }
  else if((CFTM1 == pFTM)  && (ch < 2))
  {
    SIM->SCGC |= SIM_SCGC_FTM1_MASK;
    //NVIC_EnableIRQ(FTM1_IRQn);
  }        
  else 
  {
    SIM->SCGC |= SIM_SCGC_FTM2_MASK;
    //NVIC_EnableIRQ(FTM2_IRQn);
  }
  
  FTMx[pFTM]->SC  = 0x0;     /* disable counter */ 
  FTMx[pFTM]->MOD = 0xFFFF;  /* free running */
  
  if(FTM_INPUTCAPTURE_RISINGEDGE == u8CaptureMode)        /* enable interrupt, Capture on rising edge */
  {
    //FTMx[pFTM]->CONTROLS[ch].CnSC = FTM_CnSC_CHIE_MASK | FTM_CnSC_ELSA_MASK;//enable interrupt,
    FTMx[pFTM]->CONTROLS[ch].CnSC = FTM_CnSC_ELSA_MASK;
  }
  else if(FTM_INPUTCAPTURE_FALLINGEDGE == u8CaptureMode)  /* Capture on falling edge */
  {
    //FTMx[pFTM]->CONTROLS[ch].CnSC = FTM_CnSC_CHIE_MASK | FTM_CnSC_ELSB_MASK;
    FTMx[pFTM]->CONTROLS[ch].CnSC = FTM_CnSC_ELSB_MASK;
  }
  else if(FTM_INPUTCAPTURE_BOTHEDGE == u8CaptureMode)     /* Capture on rising or falling edge */
  {
    //FTMx[pFTM]->CONTROLS[ch].CnSC = FTM_CnSC_CHIE_MASK | FTM_CnSC_ELSA_MASK | FTM_CnSC_ELSB_MASK; 
    FTMx[pFTM]->CONTROLS[ch].CnSC = FTM_CnSC_ELSA_MASK | FTM_CnSC_ELSB_MASK; 
  }
  
  FTM_InputCaptureFilterSet( pFTM,  ch, 1);
  FTM_SetCounterInitValue(pFTM,0);
}
/*****************************************************************************//*!
*
* @brief configure the FTM as specified control parameters, CnSC and CnV not 
*        included.
*        
* @param[in]    pFTM          pointer to one of three FTM base register address.
* @param[in]    pConfig     pointer to FTM general parameters.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void FTM_Init(FTMn_e pFTM, FTM_ConfigType *pConfig)
{
  if(CFTM0 == pFTM)
  {
    SIM->SCGC |= SIM_SCGC_FTM0_MASK;
  }
  
  else if(CFTM1 == pFTM)
  {
    SIM->SCGC |= SIM_SCGC_FTM1_MASK;
  }
  else
  {
    SIM->SCGC |= SIM_SCGC_FTM2_MASK;
  }
  
  /* disable counter */
  FTMx[pFTM]->SC = 0; 
  
  if(CFTM2 == pFTM)
  {
    FTMx[pFTM]->MODE |= pConfig->mode;
    FTMx[pFTM]->COMBINE   = pConfig->combine;      
    FTMx[pFTM]->CNTIN     = pConfig->cntin;      
    FTMx[pFTM]->SYNC      = pConfig->sync;      
    FTMx[pFTM]->OUTINIT   = pConfig->outinit;      
    FTMx[pFTM]->OUTMASK   = pConfig->outmask;      
    FTMx[pFTM]->DEADTIME  = pConfig->deadtime;      
    FTMx[pFTM]->EXTTRIG   = pConfig->exttrig;      
    FTMx[pFTM]->POL       = pConfig->pol;      
    FTMx[pFTM]->FMS       = pConfig->fms;      
    FTMx[pFTM]->FILTER    = pConfig->filter;      
    FTMx[pFTM]->FLTCTRL   = pConfig->fltctrl;    /* fault control */ 
    FTMx[pFTM]->FLTPOL    = pConfig->fltpol;      
    FTMx[pFTM]->CONF      = pConfig->conf;      
    FTMx[pFTM]->SYNCONF   = pConfig->synconf;      
    FTMx[pFTM]->SWOCTRL   = pConfig->swoctrl;      
    FTMx[pFTM]->PWMLOAD   = pConfig->pwmload;      
    
  }
  FTMx[pFTM]->MOD = pConfig->modulo;
  FTMx[pFTM]->CNT = pConfig->cnt;
  
  /* write SC to enable clock */
  FTMx[pFTM]->SC |= pConfig->clk_source<<3|pConfig->prescaler<<0|pConfig->cpwms<<5|pConfig->toie<<6;
  if( pConfig->toie)
  {
    if(CFTM0 == pFTM)
    {
      NVIC_EnableIRQ(FTM0_IRQn);
      
    }
    else if(CFTM1 == pFTM)
    {
      NVIC_EnableIRQ(FTM1_IRQn);
      
    }
    else
    {
      NVIC_EnableIRQ(FTM2_IRQn);
      
    }	
  }
}

/*****************************************************************************//*!
*
* @brief configure the FTM  channels, CnSC and CnV are included.
*        
* @param[in]    pFTM               pointer to one of three FTM base register address.
* @param[in]    FTM_Channel        FTM channel number.
* @param[in]    pTFTMCH_Params     pointer to FTM channel general parameters.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void FTM_ChannelInit(FTMn_e pFTM, FTM_CHn_e ch, FTM_ChParamsType pTFTMCH_Params)
{ 
  
  if (CFTM0 == pFTM)
  {
    SIM->SCGC |= SIM_SCGC_FTM0_MASK;
  }
  
  else if(CFTM1 == pFTM)
  {
    SIM->SCGC |= SIM_SCGC_FTM1_MASK;
  }        
  
  else
  {
    
    SIM->SCGC |= SIM_SCGC_FTM2_MASK;
  }  
  
  if( pTFTMCH_Params.ctrl.bits.bMode==FTM_INPUT_CAPTURE)
  {
    FTMx[pFTM]->CONTROLS[ch].CnSC |= 0<<4;
    FTMx[pFTM]->CONTROLS[ch].CnSC |= pTFTMCH_Params.ctrl.bits.bEdge<<2;
  }
  else if( pTFTMCH_Params.ctrl.bits.bMode==FTM_OUTPUT_COMPARE)
  {
    FTMx[pFTM]->CONTROLS[ch].CnSC |= FTM_CnSC_MSA_MASK;
    FTMx[pFTM]->CONTROLS[ch].CnSC |= pTFTMCH_Params.ctrl.bits.bOutCmp<<2;
  }
  else if( pTFTMCH_Params.ctrl.bits.bMode==FTM_PWMMODE_EDGEALLIGNED)
  {
    FTMx[pFTM]->CONTROLS[ch].CnSC |= FTM_CnSC_MSB_MASK;
    FTMx[pFTM]->CONTROLS[ch].CnSC |= pTFTMCH_Params.ctrl.bits.bPWMPol<<2;
  }
  
  else if (pTFTMCH_Params.ctrl.bits.bMode==FTM_PWMMODE_CENTERALLIGNED)
  {
    FTMx[pFTM]->SC|=FTM_SC_CPWMS_MASK;
    FTMx[pFTM]->CONTROLS[ch].CnSC |= pTFTMCH_Params.ctrl.bits.bPWMPol<<2;
    
  }
  else if (pTFTMCH_Params.ctrl.bits.bMode==FTM_PWMMODE_COMBINE)
  {
    FTMx[pFTM]->CONTROLS[ch].CnSC |= FTM_CnSC_MSA_MASK|FTM_CnSC_MSB_MASK|pTFTMCH_Params.ctrl.bits.bPWMPol<<2;
    
  }
  else if (pTFTMCH_Params.ctrl.bits.bMode==FTM_INPUTCAPTURE_DUALEDGE)
  {
    FTMx[pFTM]->CONTROLS[ch].CnSC |= pTFTMCH_Params.ctrl.bits.bEdge<<2;
    if(pTFTMCH_Params.ctrl.bits.bDualCapMode==FTM_INPUTCAPTURE_DUALEDGE_ONESHOT)
    {
      FTMx[pFTM]->CONTROLS[ch].CnSC &= ~FTM_CnSC_MSA_MASK;
      
    }
    else if(pTFTMCH_Params.ctrl.bits.bDualCapMode==FTM_INPUTCAPTURE_DUALEDGE_CONTINUOUS)
    {
      FTMx[pFTM]->CONTROLS[ch].CnSC |= FTM_CnSC_MSA_MASK;
      
    }
    
  }
  
  
  
  if(1==pTFTMCH_Params.ctrl.bits.bCHIE)
  {
    FTMx[pFTM]->CONTROLS[ch].CnSC |=FTM_CnSC_CHIE_MASK;
    if(CFTM0 == pFTM)
    {
      NVIC_EnableIRQ(FTM0_IRQn);
      
    }
    else if(CFTM1 == pFTM)
    {
      NVIC_EnableIRQ(FTM1_IRQn);
      
    }
    else
    {
      NVIC_EnableIRQ(FTM2_IRQn);
      
    }
    
  }
  
  FTMx[pFTM]->CONTROLS[ch].CnV = pTFTMCH_Params.u16CnV; 
  
  return;
}




