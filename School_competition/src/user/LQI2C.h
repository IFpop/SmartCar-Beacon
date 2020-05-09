/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技MK66FX1M0VLQ18核心板
【编    写】CHIUSIR
【备    注】
【软件版本】V1.0
【最后更新】2016年08月20日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
【交流邮箱】chiusir@163.com
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef _LQI2C_H_
#define _LQI2C_H_

/**********************************  IIC(引脚复用) ***************************************/

//定义读写选项
typedef enum MSmode
{
    write =   0x00,  /* Master write  */
    read =   0x01   /* Master read */
} MSmode;

void  I2C_WriteAddr(uint8 SlaveID, uint8 Addr, uint8 Data);      //读取地址里的内容
uint8  I2C_ReadAddr(uint8 SlaveID, uint8 Addr);                //往地址里写入内容

#endif