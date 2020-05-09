
#include "include.h"

#define MPU_SDA_IN()  gpio_init(PTH3,GPI,HIGH)
#define MPU_SDA_OUT() gpio_init(PTH3,GPO,HIGH)


#define MPU_IIC_SCL        PTH4_OUT 		//SCL
#define MPU_IIC_SDA_OUT    PTH3_OUT		//SDA	 
#define MPU_IIC_SDA_IN     PTH3_IN		//SDA


void MPU_IIC_Delay(void)
{
  delay_us(2);
}


void MPU_IIC_Init(void)
{					     
  gpio_init(PTH3,GPI,HIGH);
  gpio_init(PTH4,GPO,HIGH);
  PORT->PUE1 |= (uint32)(1<<PTn(PTH3));//H3使能上拉
}

//产生IIC起始信号
void MPU_IIC_Start(void)
{
  MPU_SDA_OUT();     //sda线输出
  MPU_IIC_SDA_OUT=1;	  	  
  MPU_IIC_SCL=1;
  MPU_IIC_Delay();
  MPU_IIC_SDA_OUT=0;//START:when CLK is high,DATA change form high to low 
  MPU_IIC_Delay();
  MPU_IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void MPU_IIC_Stop(void)
{
  MPU_SDA_OUT();//sda线输出
  MPU_IIC_SCL=0;
  MPU_IIC_SDA_OUT=0;//STOP:when CLK is high DATA change form low to high
  MPU_IIC_Delay();
  MPU_IIC_SCL=1; 
  MPU_IIC_SDA_OUT=1;//发送I2C总线结束信号
  MPU_IIC_Delay();							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t MPU_IIC_Wait_Ack(void)
{
  uint8_t ucErrTime=0;
  MPU_SDA_IN();      //SDA设置为输入  
  MPU_IIC_Delay();	   
  MPU_IIC_SCL=1;
  MPU_IIC_Delay();	 
  while(MPU_IIC_SDA_IN)
  {
    ucErrTime++;
    if(ucErrTime>250)
    {
      MPU_IIC_Stop();
      return 1;//没有应答信号
    }
  }
  MPU_IIC_SCL=0;//时钟输出0 	   
  return 0;  
} 
//产生ACK应答
void MPU_IIC_Ack(void)
{
  MPU_IIC_SCL=0;
  MPU_SDA_OUT();
  MPU_IIC_SDA_OUT=0;
  MPU_IIC_Delay();
  MPU_IIC_SCL=1;
  MPU_IIC_Delay();
  MPU_IIC_SCL=0;
}
//不产生ACK应答		    
void MPU_IIC_NAck(void)
{
  MPU_IIC_SCL=0;
  MPU_SDA_OUT();
  MPU_IIC_SDA_OUT=1;
  MPU_IIC_Delay();
  MPU_IIC_SCL=1;
  MPU_IIC_Delay();
  MPU_IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void MPU_IIC_Send_Byte(uint8_t txd)
{                        
  uint8_t t;   
  MPU_SDA_OUT(); 	    
  MPU_IIC_SCL=0;//拉低时钟开始数据传输
  for(t=0;t<8;t++)
  {              
    MPU_IIC_SDA_OUT=(txd&0x80)>>7;
    txd<<=1; 	  
    MPU_IIC_SCL=1;
    MPU_IIC_Delay(); 
    MPU_IIC_SCL=0;	
    MPU_IIC_Delay();
  }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t MPU_IIC_Read_Byte(unsigned char ack)
{
  unsigned char i,receive=0;
  MPU_SDA_IN();//SDA设置为输入
  for(i=0;i<8;i++ )
  {
    MPU_IIC_SCL=0; 
    MPU_IIC_Delay();
    MPU_IIC_SCL=1;
    receive<<=1;
    if(MPU_IIC_SDA_IN)receive++;   
    MPU_IIC_Delay(); 
  }					 
  if (!ack)
    MPU_IIC_NAck();//发送nACK
  else
    MPU_IIC_Ack(); //发送ACK   
  return receive;
}