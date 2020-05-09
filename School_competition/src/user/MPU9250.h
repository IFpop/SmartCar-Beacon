#ifndef __MPU9250_H
#define __MPU9250_H
 
// 定义MPU9250内部地址
//****************************************
#define SMPLRT_DIV	  0x19  //陀螺仪采样率，典型值：0x07(125Hz)
#define CONFIG	  0x1A  //低通滤波频率，典型值：0x06(5Hz)
#define GYRO_CONFIG	  0x1B  //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define ACCEL_CONFIG  0x1C  //加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define ACCEL_CONFIG2 0X1D  //加速度计低通滤波器 0x06 5hz

#define ACCEL_XOUT_H  0x3B  //加速度计输出数据
#define ACCEL_XOUT_L  0x3C
#define ACCEL_YOUT_H  0x3D
#define ACCEL_YOUT_L  0x3E
#define ACCEL_ZOUT_H  0x3F
#define ACCEL_ZOUT_L  0x40

#define TEMP_OUT_H	  0x41  //温度计输出数据
#define TEMP_OUT_L	  0x42

#define GYRO_XOUT_H	  0x43  //陀螺仪输出数据
#define GYRO_XOUT_L	  0x44	
#define GYRO_YOUT_H	  0x45
#define GYRO_YOUT_L	  0x46
#define GYRO_ZOUT_H	  0x47
#define GYRO_ZOUT_L	  0x48

		
#define MAG_XOUT_L	  0x03  //地磁输出数据
#define MAG_XOUT_H	  0x04
#define MAG_YOUT_L	  0x05
#define MAG_YOUT_H	  0x06
#define MAG_ZOUT_L	  0x07
#define MAG_ZOUT_H	  0x08

#define PWR_MGMT_1    0X6B  //电源管理1 典型值为0x00
#define PWR_MGMT_2    0X6C  //电源管理2 典型值为0X00
 
#define WHO_AM_I      0X75  //器件ID MPU9250默认ID为0X71
#define USER_CTRL     0X6A  //用户配置当为0X10时使用SPI模式

//****************************
#define MPU9250_I2C_ADDR 0X68  //i2c的地址 
#define GYRO_ADDRESS   0xD0  //陀螺地址
#define MAG_ADDRESS    0x18  //磁场地址
#define ACCEL_ADDRESS  0xD0

//unsigned char Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data);		     //void
//unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address);
//void Init_MPU9250(void);
//void READ_MPU9250_ACCEL(void);
//void READ_MPU9250_GYRO(void);
//void READ_MPU9250_MAG(void);
int MPU9250_Init(void);
int MPU9250_ReadValues(void);
short MPU_Get_Temperature(void);
uint8_t MPU_Get_Gyroscope(short *gx,short *gy,short *gz);
uint8_t MPU_Get_Accelerometer(short *ax,short *ay,short *az);
uint8_t MPU_Get_MAG(short *mx,short *my,short *mz);
#endif