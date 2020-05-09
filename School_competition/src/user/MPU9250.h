#ifndef __MPU9250_H
#define __MPU9250_H
 
// ����MPU9250�ڲ���ַ
//****************************************
#define SMPLRT_DIV	  0x19  //�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define CONFIG	  0x1A  //��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define GYRO_CONFIG	  0x1B  //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define ACCEL_CONFIG  0x1C  //���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define ACCEL_CONFIG2 0X1D  //���ٶȼƵ�ͨ�˲��� 0x06 5hz

#define ACCEL_XOUT_H  0x3B  //���ٶȼ��������
#define ACCEL_XOUT_L  0x3C
#define ACCEL_YOUT_H  0x3D
#define ACCEL_YOUT_L  0x3E
#define ACCEL_ZOUT_H  0x3F
#define ACCEL_ZOUT_L  0x40

#define TEMP_OUT_H	  0x41  //�¶ȼ��������
#define TEMP_OUT_L	  0x42

#define GYRO_XOUT_H	  0x43  //�������������
#define GYRO_XOUT_L	  0x44	
#define GYRO_YOUT_H	  0x45
#define GYRO_YOUT_L	  0x46
#define GYRO_ZOUT_H	  0x47
#define GYRO_ZOUT_L	  0x48

		
#define MAG_XOUT_L	  0x03  //�ش��������
#define MAG_XOUT_H	  0x04
#define MAG_YOUT_L	  0x05
#define MAG_YOUT_H	  0x06
#define MAG_ZOUT_L	  0x07
#define MAG_ZOUT_H	  0x08

#define PWR_MGMT_1    0X6B  //��Դ����1 ����ֵΪ0x00
#define PWR_MGMT_2    0X6C  //��Դ����2 ����ֵΪ0X00
 
#define WHO_AM_I      0X75  //����ID MPU9250Ĭ��IDΪ0X71
#define USER_CTRL     0X6A  //�û����õ�Ϊ0X10ʱʹ��SPIģʽ

//****************************
#define MPU9250_I2C_ADDR 0X68  //i2c�ĵ�ַ 
#define GYRO_ADDRESS   0xD0  //���ݵ�ַ
#define MAG_ADDRESS    0x18  //�ų���ַ
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