/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】龙邱S9KEAZ128智能车核心板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2017年11月11日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR7.80.4
【Target  】S9KEAZ128
【Crystal 】16.000Mhz
【busclock】40.000MHz
【pllclock】40.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef __LQ9AX_H__
#define __LQ9AX_H__

// FXOS8700 registers and constants
#define FXOS8700_I2C_ADDR		0x1E
#define FXOS8700_OUT_X_MSB       	0x01
#define FXOS8700_WHO_AM_I      		0x0D
#define FXOS8700_XYZ_DATA_CFG       	0x0E
#define FXOS8700_CTRL_REG1        	0x2A
#define FXOS8700_CTRL_REG2        	0x2B
#define FXOS8700_M_CTRL_REG1         	0x5B
#define FXOS8700_M_CTRL_REG2        	0x5C
#define FXOS8700_WHO_AM_I_VALUE     	0xC7

// FXAS21002 registers and constants
#define FXAS21002_I2C_ADDR		0x20
#define FXAS21002_X_MSB                 0X01
#define FXAS21002_X_LSB                 0X02
#define FXAS21002_Y_MSB                 0X03
#define FXAS21002_Y_LSB                 0X04
#define FXAS21002_Z_MSB                 0X05
#define FXAS21002_Z_LSB                 0X06
#define FXAS21002_DATA_REG            	0x01 
#define FXAS21002_WHO_AM_I        	0x0C 
#define FXAS21002_CTRL_REG0           	0x0D
#define FXAS21002_CTRL_REG1           	0x13
#define FXAS21002_WHO_AM_I_VALUE	0xD4

#define OUT_X_MSB_REG         0x01
#define OUT_X_LSB_REG         0x02
#define OUT_Y_MSB_REG         0x03
#define OUT_Y_LSB_REG         0x04
#define OUT_Z_MSB_REG         0x05
#define OUT_Z_LSB_REG         0x06

typedef union
{
  uint16 MYWORD;
  struct
  {
    uint8 BYTEL;//低8位
    uint8 BYTEH;//高8位，跟CODEWARRIOR大端模式不同
  } MYBYTE;
}LQ9AXt;

extern uint8 LQ9AX_DAT[19];
extern void Test_9AX(void);
extern void TestIIC_9AX(void);
extern LQ9AXt ACC_X,ACC_Y,ACC_Z,GYRO_X,GYRO_Y,GYRO_Z,MAG_X,MAG_Y,MAG_Z;
/*********************** UART功能函数 **************************/
//初始化
extern void Init_LQ_9AX(void);
extern void Update9AX(void);
extern void Cvt_14bit_Str(char str[],LQ9AXt V2);
extern void IIC_Read(unsigned char slave,unsigned char * p, uint16 * q);
/********************************************************************/

#endif 
