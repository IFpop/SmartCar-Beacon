#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus
extern "C" {
#endif
  
#include "include.h"
  
typedef enum  UARTn
{
  //初始化默认配置       --TXD--      --RXD--     可以复用其他通道，请自行修改 uart_init
  UARTR0 = 0,    //           
  UARTR1 = 1,    //           
  UARTR2 = 2,    //            
} UARTn;
  
typedef enum  
{
  //初始化默认配置       --TXD--      --RXD--     可以复用其他通道，请自行修改 uart_init
  Default = 0,    //           
  Remap   = 1,    //                 
} UART_PORT;    
  
void uart_init (UARTn uratn,UART_PORT port,uint32_t baud_rate) ;
void uart_enable_re_int(UARTn uratn);
uint8_t Uart_GetChar(UARTn uratn) ;
void Uart_SendChar(UARTn uratn,uint8_t send);
void Uart_SendString(UARTn uratn, uint8_t *buff) ;
void TestUART012(void);
#endif /* #ifndef _UART_H_ */
  