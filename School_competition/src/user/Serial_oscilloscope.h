#ifndef __Serial_oscilloscope_H__
#define __Serial_oscilloscope_H__

#include "include.h"

typedef enum  
{
  //初始化默认配置       --TXD--      --RXD--     可以复用其他通道，请自行修改 uart_init
  UART_0 = 0,    //           
  UART_1 = 1,    //           
  UART_2 = 2,    //            
} UART_n;
  


void Data_Send(UART_n uratn,unsigned short int *data);





#endif