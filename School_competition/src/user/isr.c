#include "isr.h"

static volatile uint16_t PWM_VALUE = Servo_mid;
static const uint16_t PWM_SUM = 5000;


//串口0接收中断服务例程
void UART0_ISR(void)
{
  //uint8_t ReData;
  //uint8_t txt[20];
  
  DisableInterrupts ;//关总中断
  
  //ReData = Uart_GetChar(UARTR0);
  //sprintf((char*)txt,"UART0_RX: %c \n",ReData);  
  //Uart_SendString(UARTR0,txt);
  
  EnableInterrupts;   //开总中断
}


//串口1接收中断服务例程
//void UART1_ISR(void)
//{
//  //uint8_t ReData;
//  //uint8_t txt[20];
//  //
//  //DisableInterrupts ;//关总中断
//  //
//  //ReData = Uart_GetChar(UARTR1);
//  //sprintf((char*)txt,"UART1_RX: %c \n",ReData);  
//  //Uart_SendString(UARTR1,txt);
//  //
//  //EnableInterrupts;   //开总中断
//  TestLED();
//}

//串口2接收中断服务例程
//void UART2_ISR(void)
//{
//  //uint8_t ReData;
//  //uint8_t txt[20];
//  //
//  //DisableInterrupts ;//关总中断
//  //
//  //ReData = Uart_GetChar(UARTR2);
//  //sprintf((char*)txt,"UART2_RX: %c \n",ReData);  
//  //Uart_SendString(UARTR2,txt);
//  //
//  //EnableInterrupts;   //开总中断
//   
//}


//定时器0中断函数
//void PIT0_ISR(void)
//{
//  PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK;//清楚中断标志位
//  LED_Ctrl(LEDALL,LEDRVS);
//  
//}

//定时器1中断函数
//void PIT1_ISR(void)
//{
//  char  txt[30]="X:";
//  int number=0;  
//  PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK;//清楚中断标志位
//  if(gpio_get(PTH7))
//    number=FTM_count_get(CFTM0);
//  else
//    number=-FTM_count_get(CFTM0);
//  sprintf(txt,"FTM0 PTE0: %05d \n",number);
//  Uart_SendString(UARTR2,(uint8_t*)txt); 
//  LCD_P6x8Str(0,0,txt);
//  if(gpio_get(PTH5))
//    number=FTM_count_get(CFTM1);
//  else
//    number=-FTM_count_get(CFTM1);
//  sprintf(txt,"FTM1 PTE7: %05d \n",number);
//  Uart_SendString(UARTR2,(uint8_t*)txt);
//  LCD_P6x8Str(0,2,txt);
//  FTM_count_clean(CFTM0); 
//  FTM_count_clean(CFTM1);
//}



////KBI0中断函数
void KBI0_Isr(void)	
{  
  KBI0->SC |= KBI_SC_KBACK_MASK;       /* clear interrupt flag */
  uint16_t n = PTn(KBI_PTB5) ;   //PTA0引脚触发中断 
  if(KBI0->SP &(1<<n))
  {
    //用户代码 
    LED_Ctrl(LED0, LEDRVS);             
  } 
}

////KBI1中断函数
void KBI1_Isr(void)	
{  
  KBI1->SC |= KBI_SC_KBACK_MASK;                /* clear interrupt flag */
  
  uint16_t n = PTn(KBI_PTH2) ;   //PTH2引脚触发中断 
  if(KBI1->SP &(1<<n))
  {
    //用户代码 
    LED_Ctrl(LED1, LEDRVS);             
  }
}


/*****************************************************************************//*!
*
* @brief  FTM0_Isr interrupt service routine.
*        
* @param  none.
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void FTM0_IRQHandler(void)
{
  /* clear the flag */
  FTMx[CFTM0]->SC &= ~FTM_SC_TOF_MASK;
  
}

/*****************************************************************************//*!
*
* @brief  FTM1_Isr interrupt service routine.
*        
* @param  none. 
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/
void FTM1_IRQHandler(void)
{
  /* clear the flag */
  FTMx[CFTM1]->SC &= ~FTM_SC_TOF_MASK;
}

/*****************************************************************************//*!
*
* @brief  FTM2_Isr interrupt service routine.
*        
* @param  none. 
*
* @return none.
*
* @ Pass/ Fail criteria: none.
*
*****************************************************************************/

void FTM2_IRQHandler(void)
{
  /* clear the flag */
  FTMx[CFTM2]->SC &= ~FTM_SC_TOF_MASK;
}

//接收蓝牙信息
void UART2_buleteeth_ISR(void)
{
    //使用static是为了在传输一道指令时只初始化一次
	static uint8_t buffer1[30]; //记录信息
	static uint8_t control_type = 0;  //记录模式类型
	static bool receive_start_flag = false; //标记一次传送是否完成
        static uint8_t *ptr = 0;

	DisableInterrupts;//关总中断
	//从通道中获取一个字节
	uint8_t  data = Uart_GetChar(UARTR2);
	if (data == 0xc1 || data == 0xc3) //一共会有两种模式
	{
		ptr = buffer1;
		control_type = data;
		receive_start_flag = 1; 
	}
	else if (data == '\0')
	{
		*ptr = '\0';
		ptr = buffer1;
		if (receive_start_flag == 1)
		{
			receive_start_flag = 0;
			After_bluetoothIRQ(control_type, buffer1); //接收之后的处理
		}
	}
	else
	{
		*ptr = data;
		++ptr;
	}
	EnableInterrupts;   //开总中断
}

// 接收摄像头信息
void UART1_camera_ISR(void)
{
	static uint8_t buffer[50]; 
	static bool receive_start_flag = false;
	static uint8_t* ptr = 0;
        static int num = 0;
	//从通道中获取一个字节

	uint8_t data = Uart_GetChar(UARTR1);
	if (data == 's')
	{
		ptr = buffer;
		receive_start_flag = 1;
	}
	else if (data == '\n')
	{
		*ptr = '\0';
		ptr = buffer;
		if (receive_start_flag == 1)
		{
			receive_start_flag = 0;
                        num++;
                        num = 0;
                        
			CAMERA_deal(buffer);
                      
		}
	}
	else
	{
		*ptr = data;
		++ptr;
	}
}

/***********************************************************
* 函数名称 ：PIT0_ServoIRQ
* 功能说明 ：定时器中断输出pwm
* 函数返回 ：无
* 参数说明 ：无
************************************************************/
void PIT0_ServoIRQ(void)
{
	static bool io = false;
	PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK; //清除标记位

	//输出低电平
	if (io)
	{
		io = false;
		PIT->CHANNEL[0].LDVAL = (PWM_SUM - PWM_VALUE) * BUS_CLK_MHZ;  //BUS_CLK_MHZ  40
	}
	//输出高电平
	else
	{
		io = true;
		PIT->CHANNEL[0].LDVAL = PWM_VALUE * BUS_CLK_MHZ;
	}
	gpio_set(PTI2, io);
}

/***********************************************************
* 函数名称 ：servo_pwm_duty
* 功能说明 ：赋予pwm波
* 函数返回 ：无
* 参数说明 ：无
************************************************************/
void servo_pwm_duty(uint32_t Duty)
{
	PWM_VALUE = Duty;
}


/***********************************************************
* 函数名称 ：PIT1_EncodeIRQ
* 功能说明 ：定时获取编码器的值
* 函数返回 ：无
* 参数说明 ：无
************************************************************/
void PIT1_EncodeIRQ(void)
{
	PIT->CHANNEL[1].TFLG |= PIT_TFLG_TIF_MASK; //清除标记位
	speed_contorl();
}