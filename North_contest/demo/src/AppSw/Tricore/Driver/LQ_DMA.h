/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技TC264DA核心板
【编    写】ZYF/chiusir
【E-mail  】chiusir@163.com
【软件版本】V1.1 版权所有，单位使用请先联系授权
【最后更新】2020年4月10日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】Hightec4.9.3/Tasking6.3及以上版本
【Target 】 TC264DA
【Crystal】 20.000Mhz
【SYS PLL】 200MHz
________________________________________________________________

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef _LQ_DMA_H_
#define _LQ_DMA_H_
#include "include.h"

/** DMA中断服务函数优先级   范围：1-255   数字越大 优先级越高  注意优先级不要重复 */
#define  DMA_PRIORITY    90


/** UART0中断服务函数优先级 中断归哪个内核管理？ 范围：0：CPU0   1：CPU1   3：DMA*/
#define  DMA_VECTABNUM    0


/** 摄像头 数据采集完成标志位 */
extern volatile unsigned char Camera_Flag;

/*!
  * @brief    摄像头DMA传输初始化
  *
  * @param    srcStartAddr   ：源地址 IO地址 LQ_GPIO.h 中有对应宏定义 例如PT0__BYTE0
  * @param    dstStartAddr   ：目的地址 摄像头数据缓冲区
  * @param    channel        ：DMA传输通道 0-47      注意 DMA传输通道需要和PIX像素中断优先级保持一致
  *
  * @return   无
  *
  * @note     注意 DMA传输通道需要和PIX像素中断优先级保持一致    一幅图需要进行两次DMA传输，因此会触发两次DMA中断
  *
  * @see      DMA_CameraInitConfig((unsigned long)(&MODULE_P02.IN.U), (unsigned long)Image_Data, PIN_INT2_PRIORITY);
  *
  * @date     2019/10/22 星期二
  */
void DMA_CameraInitConfig(unsigned long srcStartAddr, unsigned long dstStartAddr, unsigned long channel);


/*!
  * @brief    摄像头DMA传输开启
  *
  * @param    channel  : DMA通道
  *
  * @return   无
  *
  * @note     注意   在场中断中再次开启DMA传输
  *
  * @see      DMA_CameraIRQ(PIN_INT2_PRIORITY);
  *
  * @date     2020/4/8
  */
void DMA_CameraStart(unsigned long channel);


/*!
  * @brief    摄像头DMA传输中断处理函数
  *
  * @param    channel  : DMA通道
  *
  * @return   无
  *
  * @note     注意    一幅图需要进行两次DMA传输，因此会触发两次DMA中断
  *
  * @see      DMA_CameraIRQ(PIN_INT2_PRIORITY);
  *
  * @date     2020/4/8
  */
void DMA_CameraIRQ(unsigned long channel);

#endif /* 0_APPSW_TRICORE_APP_LQ_GPIO_H_ */
