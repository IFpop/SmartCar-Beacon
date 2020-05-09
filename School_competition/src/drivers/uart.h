#ifndef _UART_H_
#define _UART_H_

#ifdef __cplusplus
extern "C" {
#endif
  
#include "include.h"
  
typedef enum  UARTn
{
  //��ʼ��Ĭ������       --TXD--      --RXD--     ���Ը�������ͨ�����������޸� uart_init
  UARTR0 = 0,    //           
  UARTR1 = 1,    //           
  UARTR2 = 2,    //            
} UARTn;
  
typedef enum  
{
  //��ʼ��Ĭ������       --TXD--      --RXD--     ���Ը�������ͨ�����������޸� uart_init
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
  