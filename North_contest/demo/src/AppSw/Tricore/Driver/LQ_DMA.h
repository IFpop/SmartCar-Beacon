/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��ZYF/chiusir
��E-mail  ��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2020��4��10��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��Hightec4.9.3/Tasking6.3�����ϰ汾
��Target �� TC264DA
��Crystal�� 20.000Mhz
��SYS PLL�� 200MHz
________________________________________________________________

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef _LQ_DMA_H_
#define _LQ_DMA_H_
#include "include.h"

/** DMA�жϷ��������ȼ�   ��Χ��1-255   ����Խ�� ���ȼ�Խ��  ע�����ȼ���Ҫ�ظ� */
#define  DMA_PRIORITY    90


/** UART0�жϷ��������ȼ� �жϹ��ĸ��ں˹��� ��Χ��0��CPU0   1��CPU1   3��DMA*/
#define  DMA_VECTABNUM    0


/** ����ͷ ���ݲɼ���ɱ�־λ */
extern volatile unsigned char Camera_Flag;

/*!
  * @brief    ����ͷDMA�����ʼ��
  *
  * @param    srcStartAddr   ��Դ��ַ IO��ַ LQ_GPIO.h ���ж�Ӧ�궨�� ����PT0__BYTE0
  * @param    dstStartAddr   ��Ŀ�ĵ�ַ ����ͷ���ݻ�����
  * @param    channel        ��DMA����ͨ�� 0-47      ע�� DMA����ͨ����Ҫ��PIX�����ж����ȼ�����һ��
  *
  * @return   ��
  *
  * @note     ע�� DMA����ͨ����Ҫ��PIX�����ж����ȼ�����һ��    һ��ͼ��Ҫ��������DMA���䣬��˻ᴥ������DMA�ж�
  *
  * @see      DMA_CameraInitConfig((unsigned long)(&MODULE_P02.IN.U), (unsigned long)Image_Data, PIN_INT2_PRIORITY);
  *
  * @date     2019/10/22 ���ڶ�
  */
void DMA_CameraInitConfig(unsigned long srcStartAddr, unsigned long dstStartAddr, unsigned long channel);


/*!
  * @brief    ����ͷDMA���俪��
  *
  * @param    channel  : DMAͨ��
  *
  * @return   ��
  *
  * @note     ע��   �ڳ��ж����ٴο���DMA����
  *
  * @see      DMA_CameraIRQ(PIN_INT2_PRIORITY);
  *
  * @date     2020/4/8
  */
void DMA_CameraStart(unsigned long channel);


/*!
  * @brief    ����ͷDMA�����жϴ�����
  *
  * @param    channel  : DMAͨ��
  *
  * @return   ��
  *
  * @note     ע��    һ��ͼ��Ҫ��������DMA���䣬��˻ᴥ������DMA�ж�
  *
  * @see      DMA_CameraIRQ(PIN_INT2_PRIORITY);
  *
  * @date     2020/4/8
  */
void DMA_CameraIRQ(unsigned long channel);

#endif /* 0_APPSW_TRICORE_APP_LQ_GPIO_H_ */
