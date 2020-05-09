#ifndef __8700_2100_H__
#define __8700_2100_H__ 

#define OUT_X_MSB_REG         0x01
#define OUT_X_LSB_REG         0x02
#define OUT_Y_MSB_REG         0x03
#define OUT_Y_LSB_REG         0x04
#define OUT_Z_MSB_REG         0x05
#define OUT_Z_LSB_REG         0x06

/////////////////2100////////////////////////////
#define FX_2100_ADDR   0x20  //µÿ÷∑
#define FX_READ         0x41
#define FA_WRITE        0x40

#define FX_STATUS       0X00

#define FA_X_MSB        0X01
#define FA_X_LSB        0X02
#define FA_Y_MSB        0X03
#define FA_Y_LSB        0X04
#define FA_Z_MSB        0X05
#define FA_Z_LSB        0X06

#define FA_DR_STATUS    0X07   //0X00
#define FA_F_STATUS     0X08   //0X00
#define FA_F_SETUP      0X09   //RW
#define FA_EVENT        0X0A
#define FA_INT_SRC_FLAG 0X0B
#define FA_WHO_AM_I     0X0C
#define FA_CTRL_REG0    0X0D  //RW
#define FA_RT_CFG       0X0E  //RW
#define FA_RT_SRC       0X0F
#define FA_RT_THS       0X10  //RW
#define FA_RT_COUNT     0X11  //RW
#define FA_TEMP         0X12

#define FX_CTRL_REG1    0X13  //RW
#define FX_CTRL_REG2    0X14  //RW
#define FX_CTRL_REG3    0X15  //RW

//////////////8700////////////////////////////////
#define FXOS_8700_ADDR          0x1e

#define FXOS8700CQ_STATUS       0x00

#define FXOS8700CQ_WHOAMI       0x00

#define FXOS8700CQ_XYZ_DATA_CFG 0x0E

#define FXOS8700CQ_CTRL_REG1    0x2A

#define FXOS8700CQ_M_CTRL_REG1  0x5B

#define FXOS8700CQ_M_CTRL_REG2  0x5C

#define FXOS8700CQ_WHOAMI_VAL   0xC7


uint8_t Write_Byte_2100_8700(uint8_t SlaveID,uint8_t reg,uint8_t data); 				 
uint8_t Read_Byte_2100_8700(uint8_t SlaveID,uint8_t reg);

void Init_8700_2100();
void Read_2100_8700(unsigned char slave,unsigned char * p,short * q);
void Test_2100_8700(void);


#endif