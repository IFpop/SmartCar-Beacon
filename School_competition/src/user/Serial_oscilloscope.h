#ifndef __Serial_oscilloscope_H__
#define __Serial_oscilloscope_H__

#include "include.h"

typedef enum  
{
  //��ʼ��Ĭ������       --TXD--      --RXD--     ���Ը�������ͨ�����������޸� uart_init
  UART_0 = 0,    //           
  UART_1 = 1,    //           
  UART_2 = 2,    //            
} UART_n;
  


void Data_Send(UART_n uratn,unsigned short int *data);





#endif