#include "include.h"

//���ֽ�д��*******************************************
unsigned char TX_DATA[4];     //��ʾ�ݻ�����
unsigned char BUF[10];       //�������ݻ�����				 //IIC�õ�
unsigned int A_X,A_Y,A_Z;    //X,Y,Z��
unsigned int G_X,G_Y,G_Z;    //X,Y,Z��
unsigned int M_X,M_Y,M_Z;    //X,Y,Z��
/*
unsigned char Single_Write(unsigned char SlaveAddress,unsigned char REG_Address,unsigned char REG_data)		     //void
{
  MPU_IIC_Start();
  //�����豸��ַ+д�ź�//MPU_IIC_Send_Byte(((REG_Address & 0x0700) >>7) | SlaveAddress & 0xFFFE);//���ø���ʼ��ַ+������ַ 
  MPU_IIC_Send_Byte(SlaveAddress);
  if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
  {
    MPU_IIC_Stop();		 
    return 1;		
  }
  MPU_IIC_Send_Byte(REG_Address );   //���õ���ʼ��ַ      
  MPU_IIC_Wait_Ack();	
  MPU_IIC_Send_Byte(REG_data);
  MPU_IIC_Wait_Ack();   
  MPU_IIC_Stop(); 
  return 0;
}

//���ֽڶ�ȡ*****************************************
unsigned char Single_Read(unsigned char SlaveAddress,unsigned char REG_Address)
{   
  unsigned char REG_data;     	
  MPU_IIC_Start();
  MPU_IIC_Send_Byte(SlaveAddress); //I2C_SendByte(((REG_Address & 0x0700) >>7) | REG_Address & 0xFFFE);//���ø���ʼ��ַ+������ַ 
  if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
  {
    MPU_IIC_Stop();		 
    return 1;		
  }
  MPU_IIC_Send_Byte((uint8_t) REG_Address);   //���õ���ʼ��ַ      
  MPU_IIC_Wait_Ack();
  MPU_IIC_Send_Byte(SlaveAddress+1);
  MPU_IIC_Wait_Ack();
  
  REG_data= MPU_IIC_Read_Byte(0);
  MPU_IIC_Stop();
  //return TRUE;
  return REG_data;
  
}	
*/
//�õ����ٶ�ֵ(ԭʼֵ)
//ax,ay,az:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
uint8_t MPU9250_Get_Accelerometer(short *ax,short *ay,short *az)
{
  uint8_t buf[6],res;  
  res=MPU_Read_Len(MPU_ADDR,ACCEL_XOUT_H,6,buf);
  if(res==0)
  {
    *ax=((uint16_t)buf[0]<<8)|buf[1];  
    *ay=((uint16_t)buf[2]<<8)|buf[3];  
    *az=((uint16_t)buf[4]<<8)|buf[5];
  } 	
  return res;;
}
//�õ�������ֵ(ԭʼֵ)
//gx,gy,gz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
uint8_t MPU9250_Get_Gyroscope(short *gx,short *gy,short *gz)
{
  uint8_t buf[6],res;  
  res=MPU_Read_Len(MPU_ADDR,GYRO_XOUT_H,6,buf);
  if(res==0)
  {
    *gx=((uint16_t)buf[0]<<8)|buf[1];  
    *gy=((uint16_t)buf[2]<<8)|buf[3];  
    *gz=((uint16_t)buf[4]<<8)|buf[5];
  } 	
  return res;;
}  
 //�õ��ش�ֵ(ԭʼֵ)
//mx,my,mz:������x,y,z���ԭʼ����(������)
//����ֵ:0,�ɹ�
//    ����,�������
uint8_t MPU9250_Get_MAG(short *mx,short *my,short *mz)
{
  uint8_t buf[6],res;  
  res=MPU_Read_Len(MPU_ADDR,MAG_XOUT_L,6,buf);
  if(res==0)
  {
    *mx=((uint16_t)buf[1]<<8)|buf[0];  
    *my=((uint16_t)buf[3]<<8)|buf[2];  
    *mz=((uint16_t)buf[5]<<8)|buf[4];
  } 	
  return res;;
}

//�õ��¶�ֵ
//����ֵ:�¶�ֵ(������100��)
short MPU9250_Get_Temperature(void)
{
  uint8_t buf[2]; 
  short raw;
  float temp;
  MPU_Read_Len(MPU_ADDR,TEMP_OUT_H,2,buf); 
  raw=((uint16_t)buf[0]<<8)|buf[1];  
  temp=36.53+((double)raw)/340;  
  return temp*100;;
}
/*
uint8_t MPU9250_Init(void)
{
  uint8_t value;
  MPU_Read_Len(MPU9250_I2C_ADDR,(WHO_AM_I|0x80),1,&value);//��ȡ����ID
  if(value==0x71)
  {
    MPU_Write_Len(MPU9250_I2C_ADDR,PWR_MGMT_1,1,0X80);  //��Դ����,��λMPU9250  �ڲ�20M����
    MPU_Write_Len(MPU9250_I2C_ADDR,SMPLRT_DIV,1,0x07);//�����ǲ�����1000/(1+7)=125HZ
    MPU_Write_Len(MPU9250_I2C_ADDR,CONFIG,1,0X06); //��ͨ�˲��� 0x06 5hz
    MPU_Write_Len(MPU9250_I2C_ADDR,ACCEL_CONFIG,1,0x18); //���ٶȼƲ�����Χ 0X18 ����16g
    MPU_Write_Len(MPU9250_I2C_ADDR,ACCEL_CONFIG2,1,0x00); //���ٶȲ���Ƶ��460HZ
    return 0;
  }
  return 1;
}
*/
/*
//��ʼ��MPU9250��
void Init_MPU9250(void)
{
MPU_IIC_Init();//��ʼ��IIC����
Single_Write(GYRO_ADDRESS,PWR_MGMT_1, 0x00);	//�������״̬
Single_Write(GYRO_ADDRESS,SMPLRT_DIV, 0x07);
Single_Write(GYRO_ADDRESS,CONFIG, 0x06);
Single_Write(GYRO_ADDRESS,GYRO_CONFIG, 0x18);
Single_Write(GYRO_ADDRESS,ACCEL_CONFIG, 0x01);
}

//******��ȡMPU9250����****************************************
void READ_MPU9250_ACCEL(void)
{ 

BUF[0]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_L); 
BUF[1]=Single_Read(ACCEL_ADDRESS,ACCEL_XOUT_H);
A_X=	(BUF[1]<<8)|BUF[0];
//A_X/=164; 						   //��ȡ����X������

BUF[2]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_L);
BUF[3]=Single_Read(ACCEL_ADDRESS,ACCEL_YOUT_H);
A_Y=	(BUF[3]<<8)|BUF[2];
//A_Y/=164; 						   //��ȡ����Y������
BUF[4]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_L);
BUF[5]=Single_Read(ACCEL_ADDRESS,ACCEL_ZOUT_H);
A_Z=	(BUF[5]<<8)|BUF[4];
//A_Z/=164; 					       //��ȡ����Z������

}

void READ_MPU9250_GYRO(void)
{ 

BUF[0]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_L); 
BUF[1]=Single_Read(GYRO_ADDRESS,GYRO_XOUT_H);
G_X=	(BUF[1]<<8)|BUF[0];
//G_X/=16.4; 						   //��ȡ����X������

BUF[2]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_L);
BUF[3]=Single_Read(GYRO_ADDRESS,GYRO_YOUT_H);
G_Y=	(BUF[3]<<8)|BUF[2];
//G_Y/=16.4; 						   //��ȡ����Y������
BUF[4]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_L);
BUF[5]=Single_Read(GYRO_ADDRESS,GYRO_ZOUT_H);
G_Z=	(BUF[5]<<8)|BUF[4];
//G_Z/=16.4; 					       //��ȡ����Z������


// BUF[6]=Single_Read(GYRO_ADDRESS,TEMP_OUT_L); 
// BUF[7]=Single_Read(GYRO_ADDRESS,TEMP_OUT_H); 
// T_T=(BUF[7]<<8)|BUF[6];
// T_T = 35+ ((double) (T_T + 13200)) / 280;// ��ȡ������¶�
}


void READ_MPU9250_MAG(void)
{ 
Single_Write(GYRO_ADDRESS,0x37,0x02);//turn on Bypass Mode 
delay_ms(10);	
Single_Write(MAG_ADDRESS,0x0A,0x01);
delay_ms(10);	
BUF[0]=Single_Read (MAG_ADDRESS,MAG_XOUT_L);
BUF[1]=Single_Read (MAG_ADDRESS,MAG_XOUT_H);
M_X=(BUF[1]<<8)|BUF[0];

BUF[2]=Single_Read(MAG_ADDRESS,MAG_YOUT_L);
BUF[3]=Single_Read(MAG_ADDRESS,MAG_YOUT_H);
M_Y=	(BUF[3]<<8)|BUF[2];
//��ȡ����Y������

BUF[4]=Single_Read(MAG_ADDRESS,MAG_ZOUT_L);
BUF[5]=Single_Read(MAG_ADDRESS,MAG_ZOUT_H);
M_Z=	(BUF[5]<<8)|BUF[4];
//��ȡ����Z������
}
*/