#ifndef __MPUIIC_H__
#define __MPUIIC_H__


extern void MPU_IIC_Delay(void);
extern void MPU_IIC_Init(void);
extern void MPU_IIC_Start(void);
extern void MPU_IIC_Stop(void);
extern uint8_t MPU_IIC_Wait_Ack(void);
extern void MPU_IIC_Ack(void);
extern void MPU_IIC_NAck(void);
extern void MPU_IIC_Send_Byte(uint8_t txd);
extern uint8_t MPU_IIC_Read_Byte(unsigned char ack);

#endif 