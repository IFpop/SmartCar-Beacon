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
#include "uart.h"

volatile UART_Type *UARTx[3]={UART0,UART1,UART2};



/*************************************************************************
*  函数名称：uart_init
*  功能说明：初始化uart模块
*  函数返回：无
*  参数说明：UARTn  :    通道
*           baud_rate  ：波特率 1200  2400  4800 9600 14400
                                19200  28800  38400  57600 
           port: 0:默认引脚
                 1：引脚重映射

         串口号   默认引脚            重映射引脚
        UART0:  RX--B0 ；TX--B1     PTA3 TX ,PTA2 RX
        UART1:  RX--C6 ；TX--C7     PTF3 TX ,PTF2 RX
        UART2:  RX--D6 ；TX--D7     PTI1 TX ,PTI0 RX 
*  for example           uart_init(UARTR1,Default,9600);
*************************************************************************/
void uart_init(UARTn uratn,UART_PORT port,uint32_t baud_rate)
{
  uint8_t temp;
  uint16_t  sbr;
  
  sbr = (uint16_t)(BUS_CLK_HZ/(16*baud_rate)); 
      //UART 波特率 = UART 模块时钟 / (16 × (SBR[12:0] + BRFA))
  //不考虑 BRFA 的情况下， SBR = UART 模块时钟 / (16 * UART 波特率)
  if(sbr > 0x1FFF) sbr = 0x1FFF;                                       //SBR 是 13bit，最大为 0x1FFF
 
  
  switch(uratn)
  {
  case UARTR0:
    SIM->SCGC |=  SIM_SCGC_UART0_MASK;
    if (!port)
      SIM->PINSEL &= ~SIM_PINSEL_UART0PS_MASK;   //RX--B0 ；TX--B1
    else
      SIM->PINSEL |= SIM_PINSEL_UART0PS_MASK;   //PTA3 TX ,PTA2 RX  
    SIM->SOPT0 &= ~SIM_SOPT0_TXDME_MASK ;
    SIM->SOPT0 &= ~SIM_SOPT0_RXDFE_MASK ;
    SIM->SOPT0 &= ~SIM_SOPT0_RXDCE_MASK ;
    break;
  case UARTR1:
    SIM->SCGC |=  SIM_SCGC_UART1_MASK;
    if (!port)
      SIM->PINSEL1 &= ~SIM_PINSEL1_UART1PS_MASK;   //X--C6 ；TX--C7
    else
      SIM->PINSEL1 |= SIM_PINSEL1_UART1PS_MASK ;  //PTF3 TX ,PTF2 RX 
    break ;
  case UARTR2:
    SIM->SCGC |=  SIM_SCGC_UART2_MASK;
    if (!port)
      SIM->PINSEL1 &= ~SIM_PINSEL1_UART2PS_MASK;   //RX--D6 ；TX--D7
    else
      SIM->PINSEL1 |= SIM_PINSEL1_UART2PS_MASK ;  //PTI1 TX ,PTI0 RX 
    break;
  default:
    break;
  }
  temp = UARTx[uratn]->BDH&~UART_BDH_SBR(0X1F);  
  UARTx[uratn]->BDH = temp|UART_BDH_SBR(((sbr & 0x1F00) >> 8)) ;
  UARTx[uratn]->BDL = (uint8_t)(sbr&UART_BDL_SBR_MASK);
  UARTx[uratn]->C1  = 0 ;
  UARTx[uratn]->C2  = (0
                       |UART_C2_TE_MASK
                         |UART_C2_RE_MASK
                           );
  
}

/*************************************************************************
*  函数名称：Uart_SendChar
*  功能说明：发送一个字节
*  函数返回：无
*  参数说明：UARTn :模块号（UART0~UART2）
*           send   :发送的数据
*  for example      Uart_SendChar(UARTR1,1);
*************************************************************************/
void Uart_SendChar(UARTn uratn,uint8_t send)
{
  while((UARTx[uratn]->S1&UART_S1_TDRE_MASK)==0);		/* Wait for transmit buffer to be empty*/							/* Read UART2_S1 register*/
//  (void)UARTx[uratn]->S1;					/* Read UART2_S1 register*/
  UARTx[uratn]->D=send;						/* Send data*/
}

/*************************************************************************
*  函数名称：Uart_GetChar
*  功能说明：接受一个数据
*  函数返回：接受数据
*  参数说明：UARTn  :模块号（UART0~UART2）
*  for example       data = Uart_GetChar(UART1);
*************************************************************************/
uint8_t Uart_GetChar(UARTn uratn)
{  
  uint8_t recieve;
  
  while(( UARTx[uratn]->S1 & UART_S1_RDRF_MASK)==0);	/* Wait for received buffer to be full*/								/* Read UART2_S1 register*/
  recieve= UARTx[uratn]->D;								/* Read received data*/
  return recieve;
  
}

/**************************************************************************
*  函数名称： Uart_SendString
*  函数返回： 函数执行状态：0=正常；非0=异常。
*  功能概要： 从指定UART端口发送一个以'\0'结束的字符串(以双引号表达的字符串，即是以'\0'结束的字符串）
*  参数说明： UARTn uratn:UART模块号:UART0、UART1、UART2
*             buff:要发送的字符串的首地址
*  例：Uart_SendString(UARTR1,"abcdefg"); 即可发送字符  abcdefg
***************************************************************************/
void Uart_SendString(UARTn uratn, uint8_t *buff)
{
  uint16_t i;
  for(i = 0; *(buff+i) != '\0'; i++)  //遍历字符串里的字符
  {
    Uart_SendChar(uratn,*(buff+i));//发送指针对应的字符
  }
  Uart_SendChar(uratn, 0);
}



//===========================================================================
//函数名称：uart_enable_re_int
//参数说明：uartNo: 串口号:UART_0、UART_1、UART_2 
//函数返回：无
//功能概要：开串口接收中断
//===========================================================================
void uart_enable_re_int(UARTn uratn)
{
  UARTx[uratn]->C2 |= UART_C2_RIE_MASK;       // 开放UART接收中断
  if(uratn==0)
    NVIC_EnableIRQ(UART0_IRQn);// 开中断控制器IRQ中断
  else if (uratn==1)
    NVIC_EnableIRQ(UART1_IRQn);// 开中断控制器IRQ中断
  else if (uratn==2)
    NVIC_EnableIRQ(UART2_IRQn);// 开中断控制器IRQ中断
}

//===========================================================================
//函数名称：uart_disable_re_int
//参数说明：uartNo: 串口号 :UART_0、UART_1、UART_2 
//函数返回：无
//功能概要：关串口接收中断
//===========================================================================
void uart_disable_re_int(UARTn uratn)
{
  UARTx[uratn]->C2 &= ~UART_C2_RIE_MASK;       // 禁止UART接收中断
  if(uratn==0)
    NVIC_DisableIRQ(UART0_IRQn);// 禁止中断控制器IRQ中断
  else if (uratn==1)
    NVIC_DisableIRQ(UART1_IRQn);// 禁止中断控制器IRQ中断
  else if (uratn==2)
    NVIC_DisableIRQ(UART2_IRQn);// 禁止中断控制器IRQ中断
}



void TestUART012(void)
{  
  DisableInterrupts ;           //禁止中断    
  EnableInterrupts;   
  uart_init(UARTR0,Remap,9600);
  uart_init(UARTR1,Default,9600);
  uart_init(UARTR2,Remap,9600);
  uart_enable_re_int(UARTR0);
  uart_enable_re_int(UARTR1);
  uart_enable_re_int(UARTR2);
  while(1)
  {
  }
}
