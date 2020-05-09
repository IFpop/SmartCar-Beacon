/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������S9KEAZ128���ܳ�MINI���İ�ĸ��
����    д��
��E-mail  ��
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
#include "uart.h"

volatile UART_Type *UARTx[3]={UART0,UART1,UART2};



/*************************************************************************
*  �������ƣ�uart_init
*  ����˵������ʼ��uartģ��
*  �������أ���
*  ����˵����UARTn  :    ͨ��
*           baud_rate  �������� 1200  2400  4800 9600 14400
                                19200  28800  38400  57600 
           port: 0:Ĭ������
                 1��������ӳ��

         ���ں�   Ĭ������            ��ӳ������
        UART0:  RX--B0 ��TX--B1     PTA3 TX ,PTA2 RX
        UART1:  RX--C6 ��TX--C7     PTF3 TX ,PTF2 RX
        UART2:  RX--D6 ��TX--D7     PTI1 TX ,PTI0 RX 
*  for example           uart_init(UARTR1,Default,9600);
*************************************************************************/
void uart_init(UARTn uratn,UART_PORT port,uint32_t baud_rate)
{
  uint8_t temp;
  uint16_t  sbr;
  
  sbr = (uint16_t)(BUS_CLK_HZ/(16*baud_rate)); 
      //UART ������ = UART ģ��ʱ�� / (16 �� (SBR[12:0] + BRFA))
  //������ BRFA ������£� SBR = UART ģ��ʱ�� / (16 * UART ������)
  if(sbr > 0x1FFF) sbr = 0x1FFF;                                       //SBR �� 13bit�����Ϊ 0x1FFF
 
  
  switch(uratn)
  {
  case UARTR0:
    SIM->SCGC |=  SIM_SCGC_UART0_MASK;
    if (!port)
      SIM->PINSEL &= ~SIM_PINSEL_UART0PS_MASK;   //RX--B0 ��TX--B1
    else
      SIM->PINSEL |= SIM_PINSEL_UART0PS_MASK;   //PTA3 TX ,PTA2 RX  
    SIM->SOPT0 &= ~SIM_SOPT0_TXDME_MASK ;
    SIM->SOPT0 &= ~SIM_SOPT0_RXDFE_MASK ;
    SIM->SOPT0 &= ~SIM_SOPT0_RXDCE_MASK ;
    break;
  case UARTR1:
    SIM->SCGC |=  SIM_SCGC_UART1_MASK;
    if (!port)
      SIM->PINSEL1 &= ~SIM_PINSEL1_UART1PS_MASK;   //X--C6 ��TX--C7
    else
      SIM->PINSEL1 |= SIM_PINSEL1_UART1PS_MASK ;  //PTF3 TX ,PTF2 RX 
    break ;
  case UARTR2:
    SIM->SCGC |=  SIM_SCGC_UART2_MASK;
    if (!port)
      SIM->PINSEL1 &= ~SIM_PINSEL1_UART2PS_MASK;   //RX--D6 ��TX--D7
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
*  �������ƣ�Uart_SendChar
*  ����˵��������һ���ֽ�
*  �������أ���
*  ����˵����UARTn :ģ��ţ�UART0~UART2��
*           send   :���͵�����
*  for example      Uart_SendChar(UARTR1,1);
*************************************************************************/
void Uart_SendChar(UARTn uratn,uint8_t send)
{
  while((UARTx[uratn]->S1&UART_S1_TDRE_MASK)==0);		/* Wait for transmit buffer to be empty*/							/* Read UART2_S1 register*/
//  (void)UARTx[uratn]->S1;					/* Read UART2_S1 register*/
  UARTx[uratn]->D=send;						/* Send data*/
}

/*************************************************************************
*  �������ƣ�Uart_GetChar
*  ����˵��������һ������
*  �������أ���������
*  ����˵����UARTn  :ģ��ţ�UART0~UART2��
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
*  �������ƣ� Uart_SendString
*  �������أ� ����ִ��״̬��0=��������0=�쳣��
*  ���ܸ�Ҫ�� ��ָ��UART�˿ڷ���һ����'\0'�������ַ���(��˫���ű����ַ�����������'\0'�������ַ�����
*  ����˵���� UARTn uratn:UARTģ���:UART0��UART1��UART2
*             buff:Ҫ���͵��ַ������׵�ַ
*  ����Uart_SendString(UARTR1,"abcdefg"); ���ɷ����ַ�  abcdefg
***************************************************************************/
void Uart_SendString(UARTn uratn, uint8_t *buff)
{
  uint16_t i;
  for(i = 0; *(buff+i) != '\0'; i++)  //�����ַ�������ַ�
  {
    Uart_SendChar(uratn,*(buff+i));//����ָ���Ӧ���ַ�
  }
  Uart_SendChar(uratn, 0);
}



//===========================================================================
//�������ƣ�uart_enable_re_int
//����˵����uartNo: ���ں�:UART_0��UART_1��UART_2 
//�������أ���
//���ܸ�Ҫ�������ڽ����ж�
//===========================================================================
void uart_enable_re_int(UARTn uratn)
{
  UARTx[uratn]->C2 |= UART_C2_RIE_MASK;       // ����UART�����ж�
  if(uratn==0)
    NVIC_EnableIRQ(UART0_IRQn);// ���жϿ�����IRQ�ж�
  else if (uratn==1)
    NVIC_EnableIRQ(UART1_IRQn);// ���жϿ�����IRQ�ж�
  else if (uratn==2)
    NVIC_EnableIRQ(UART2_IRQn);// ���жϿ�����IRQ�ж�
}

//===========================================================================
//�������ƣ�uart_disable_re_int
//����˵����uartNo: ���ں� :UART_0��UART_1��UART_2 
//�������أ���
//���ܸ�Ҫ���ش��ڽ����ж�
//===========================================================================
void uart_disable_re_int(UARTn uratn)
{
  UARTx[uratn]->C2 &= ~UART_C2_RIE_MASK;       // ��ֹUART�����ж�
  if(uratn==0)
    NVIC_DisableIRQ(UART0_IRQn);// ��ֹ�жϿ�����IRQ�ж�
  else if (uratn==1)
    NVIC_DisableIRQ(UART1_IRQn);// ��ֹ�жϿ�����IRQ�ж�
  else if (uratn==2)
    NVIC_DisableIRQ(UART2_IRQn);// ��ֹ�жϿ�����IRQ�ж�
}



void TestUART012(void)
{  
  DisableInterrupts ;           //��ֹ�ж�    
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
