#ifndef _headfile_h
#define _headfile_h

#include <stdarg.h>
#include <stdio.h>
#include <stdbool.h> 
#include <SKEAZ1284.h>
#include "sysinit.h"
#include "systick.h"
#include "common.h"
#include "ics.h"
#include "rtc.h"
#include "io.h"
#include "uart.h"
#include "sim.h"
#include "gpio.h"       //IO�ڲ���
#include "pit.h"
#include "adc.h"
#include "uart.h"
#include "ftm.h"
#include "kbi.h"
#include "i2c.h"
#include "spi.h"
#include "adc.h"
#include "acmp.h"
#include "mscan.h"
#include "pwt.h"
#include "wdog.h"
#include "pmc.h"
#include "adc.h"
#include "adc.h"


//�û��Զ���ͷ�ļ�   
#include "LQ12864.h"
#include "isr.h"   
#include "LQLED.h"
#include "LQKEY.h"  
#include "LQ9AX.h" 
#include "LQI2C.h"
#include "MPUIIC.h"
#include "MPU6050.h"
#include "Serial_oscilloscope.h"
#include "8700_2100.h"
#include "init.h"
#include "test.h"

#define Servo_left 3530  //�����ʱ�������
#define Servo_right 3230  //���ұ�ʱ��
#define Servo_mid 3380
#define Servo_target 3650
#define Target_H  200

#endif