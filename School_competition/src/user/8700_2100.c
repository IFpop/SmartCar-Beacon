#include "include.h"

uint8_t Write_Byte_2100_8700(uint8_t SlaveID,uint8_t reg,uint8_t data) 				 
{ 
  MPU_IIC_Start(); 
  MPU_IIC_Send_Byte((SlaveID<<1)|0);//����������ַ+д����	
  if(MPU_IIC_Wait_Ack())	//�ȴ�Ӧ��
  {
    MPU_IIC_Stop();		 
    return 1;		
  }
  MPU_IIC_Send_Byte(reg);	//д�Ĵ�����ַ
  MPU_IIC_Wait_Ack();		//�ȴ�Ӧ�� 
  MPU_IIC_Send_Byte(data);//��������
  if(MPU_IIC_Wait_Ack())	//�ȴ�ACK
  {
    MPU_IIC_Stop();	 
    return 1;		 
  }
  MPU_IIC_Stop();	 
  return 0;
}

uint8_t Read_Byte_2100_8700(uint8_t SlaveID,uint8_t reg)
{
  uint8_t res;
  MPU_IIC_Start(); 
  MPU_IIC_Send_Byte((SlaveID<<1)|0);//����������ַ+д����	
  MPU_IIC_Wait_Ack();               //�ȴ�Ӧ�� 
  MPU_IIC_Send_Byte(reg);           //д�Ĵ�����ַ
  MPU_IIC_Wait_Ack();               //�ȴ�Ӧ��
  MPU_IIC_Start();
  MPU_IIC_Send_Byte((SlaveID<<1)|1);//����������ַ+������	
  MPU_IIC_Wait_Ack();               //�ȴ�Ӧ�� 
  res=MPU_IIC_Read_Byte(0);         //��ȡ����,����nACK 
  MPU_IIC_Stop();	                //����һ��ֹͣ���� 
  return res;		
}

void Init_8700_2100()
{
  MPU_IIC_Init(); 
  ////////////////////8700��ʼ��//////////////////////////////  
  Write_Byte_2100_8700(FXOS_8700_ADDR,FXOS8700CQ_CTRL_REG1, 0x00);
  Write_Byte_2100_8700(FXOS_8700_ADDR,FXOS8700CQ_CTRL_REG1, 0x0f);
  Write_Byte_2100_8700(FXOS_8700_ADDR,FXOS8700CQ_M_CTRL_REG2,0x20);
  Write_Byte_2100_8700(FXOS_8700_ADDR,FXOS8700CQ_XYZ_DATA_CFG,0x01);
  Write_Byte_2100_8700(FXOS_8700_ADDR,FXOS8700CQ_CTRL_REG1,0x0d);
  /////////////////////2100��ʼ��////////////////////////////
  Write_Byte_2100_8700(FX_2100_ADDR,FX_CTRL_REG3, 0x40);
  Write_Byte_2100_8700(FX_2100_ADDR,FX_CTRL_REG1, 0x01);
  time_delay_ms(1);
  Write_Byte_2100_8700(FX_2100_ADDR,FX_CTRL_REG1,0x03);   
}

void Read_2100_8700(unsigned char slave,unsigned char * p, short * q)
{
  int MUP_Zero=0x0000;
  p[0]  =    Read_Byte_2100_8700(slave,OUT_X_MSB_REG);
  p[1]  =    Read_Byte_2100_8700(slave,OUT_X_LSB_REG);
  p[2]  =    Read_Byte_2100_8700(slave,OUT_Y_MSB_REG);
  p[3]  =    Read_Byte_2100_8700(slave,OUT_Y_LSB_REG);
  p[4]  =    Read_Byte_2100_8700(slave,OUT_Z_MSB_REG);
  p[5]  =    Read_Byte_2100_8700(slave,OUT_Z_LSB_REG);
  
  q[0] = (((MUP_Zero | p[0])<<8)|p[1]);
  q[1] = (((MUP_Zero | p[2])<<8)|p[3]);
  q[2] = (((MUP_Zero | p[4])<<8)|p[5]);
}

void Test_2100_8700(void)
{
  short int accle_x,accle_y,accle_z;	//���ٶȴ�����ԭʼ����
  short int gyro_x,gyro_y,gyro_z;	//������ԭʼ����
  uint8_t bit8_data[6];
  short  bit16_data16[3];
  uint16_t a[8];
  uint8_t  txt[30]="X:";
  Init_8700_2100();              
  uart_init(UARTR2,Remap,9600);
  LCD_Init();
  while(1)
  {
    //�ɼ�8700����
    Read_2100_8700(FXOS_8700_ADDR,bit8_data,bit16_data16);//14λ����
    accle_x= bit16_data16[0];
    accle_y= bit16_data16[1];
    accle_z= bit16_data16[2];
    //�ɼ�2100����
    Read_2100_8700(FX_2100_ADDR,bit8_data,bit16_data16);//16λ����
    gyro_x= bit16_data16[0];
    gyro_y= bit16_data16[1];
    gyro_z= bit16_data16[2];
    //OLED��ʾ
    sprintf((char*)txt,"ax:%06d",accle_x);
    LCD_P6x8Str(0,0,txt);
    sprintf((char*)txt,"ay:%06d",accle_y);
    LCD_P6x8Str(0,1,txt);
    sprintf((char*)txt,"az:%06d",accle_z);
    LCD_P6x8Str(0,2,txt);
    sprintf((char*)txt,"gx:%06d",gyro_x);
    LCD_P6x8Str(0,3,txt);
    sprintf((char*)txt,"gy:%06d",gyro_y);
    LCD_P6x8Str(0,4,txt);
    sprintf((char*)txt,"gz:%06d",gyro_z);
    LCD_P6x8Str(0,5,txt);
    //���͵���λ��
    a[0]=accle_x;
    a[1]=accle_y;
    a[2]=accle_z;
    a[3]=gyro_x;
    a[4]=gyro_y;
    a[5]=gyro_z;
    Data_Send(UARTR2,a);
  }
}
