/************************************************************
* 文件名           ：
* 功能             ：发送数据到上位机
* 备注             ：官方例程上修改
* 日期             ：2017-11-20
* 实验平台         ：龙丘 KEAZ128核心板 
* 作者             ：龙丘技术 006
* 淘宝店           ：https://longqiu.taobao.com
* 龙丘智能车讨论群 ：338766225
*************************************************************/

#include "include.h"

unsigned char data_to_send[23];         //发送缓存
//unsigned char data_to_send[16];
void Data_Send(UART_n uratn,unsigned short int *pst)
{
  unsigned char _cnt=0; 
  unsigned char sum = 0;
  
  data_to_send[_cnt++]=0xAA;
  data_to_send[_cnt++]=0xAA;
  data_to_send[_cnt++]=0x02;
  data_to_send[_cnt++]=0;
  data_to_send[_cnt++]=(unsigned char)(pst[0]>>8);  //高8位
  data_to_send[_cnt++]=(unsigned char)pst[0];  //低8位
  data_to_send[_cnt++]=(unsigned char)(pst[1]>>8);
  data_to_send[_cnt++]=(unsigned char)pst[1];
  data_to_send[_cnt++]=(unsigned char)(pst[2]>>8);
  data_to_send[_cnt++]=(unsigned char)pst[2];
  data_to_send[_cnt++]=(unsigned char)(pst[3]>>8);
  data_to_send[_cnt++]=(unsigned char)pst[3];
  data_to_send[_cnt++]=(unsigned char)(pst[4]>>8);
  data_to_send[_cnt++]=(unsigned char)pst[4];
  data_to_send[_cnt++]=(unsigned char)(pst[5]>>8);
  data_to_send[_cnt++]=(unsigned char)pst[5];
  data_to_send[_cnt++]=0;
  data_to_send[_cnt++]=0;
  data_to_send[_cnt++]=0;
  data_to_send[_cnt++]=0;
  data_to_send[_cnt++]=0;
  data_to_send[_cnt++]=0;
   
  data_to_send[3] = _cnt-4;
  
  sum = 0;
  
  for(unsigned char i=0;i<_cnt;i++)
    sum += data_to_send[i];
  
  data_to_send[_cnt++] = sum;

  for(unsigned char i=0;i<_cnt;i++)
    Uart_SendChar(uratn,data_to_send[i]);
}