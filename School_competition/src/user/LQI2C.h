/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�MK66FX1M0VLQ18���İ�
����    д��CHIUSIR
����    ע��
������汾��V1.0
�������¡�2016��08��20��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
���������䡿chiusir@163.com
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef _LQI2C_H_
#define _LQI2C_H_

/**********************************  IIC(���Ÿ���) ***************************************/

//�����дѡ��
typedef enum MSmode
{
    write =   0x00,  /* Master write  */
    read =   0x01   /* Master read */
} MSmode;

void  I2C_WriteAddr(uint8 SlaveID, uint8 Addr, uint8 Data);      //��ȡ��ַ�������
uint8  I2C_ReadAddr(uint8 SlaveID, uint8 Addr);                //����ַ��д������

#endif