#ifndef _GPIO_H       //��ֹ�ظ����壨gpio_H  ��ͷ)
#define _GPIO_H

#include "gpio_icf.h" 
/*

KBI0��
PTA0~PTA7  PTB0~PTB7  PTC0~PTC7  PTD0~PTD7
   0~7      8~15       16~23      24~31

KBI0��
PTE0~PTE7  PTF0~PTF7  PTG0~PTG7  PTH0~PTH7
   0~7      8~15       16~23      24~31
*/

#define PTX(PTxn)           ((PTxn)>>5)              //PORTX PORTA PORTB 
#define PTn(PTxn)           ((PTxn)&0x1f)           //PIN   0~31
#define GPIOX_BASE(PTxn)     GPIOx[PTX(PTxn)]       //GPIOxģ��ĵ�ַ


/*
 * ����ܽŷ���
 */

#define GPO   1u
#define GPI   0u   
#define HIGH  1u
#define LOW   0u

void gpio_init(PTxn ptxn, uint8_t dir, uint8_t state);
void gpio_set(PTxn ptxn, uint8_t state);
uint8_t gpio_get(PTxn ptxn);
void gpio_turn(PTxn ptxn);

#define GPIO_SET(PORTx,n,x)           GPIO_SET_##x((PORTx),(n))                                 //���������ƽx��xΪ0��1   ���� GPIO_SET(PORTA,1,1)  PA1����ߵ�ƽ
#define GPIO_TURN(PORTx,n)           (GPIO_PDOR_REG(GPIOx[(PORTx)]) ^=  (1<<(n)))               //��ת�����ƽ
#define GPIO_Get(PORTx,n)            ((GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n))&0x1)                 //��ȡ��������״̬
//GPIO  1λ����
#define GPIO_SET_1bit(PORTx,n,data)   GPIO_PDOR_REG(GPIOx[(PORTx)])=(( GPIO_PDOR_REG(GPIOx[(PORTx)])& ~(0x1<<(n)) )|(((data)&0x01)<<(n)))   //д1λ���ݣ�nΪ���λ���źţ�
#define GPIO_DDR_1bit(PORTx,n,ddr)    GPIO_PDDR_REG(GPIOx[(PORTx)])=(( GPIO_PDDR_REG(GPIOx[(PORTx)])& ~(0x1<<(n)) )|(((ddr)&0x01)<<(n)))    //����1λ�����������nΪ���λ���źţ�
#define GPIO_GET_1bit(PORTx,n)        (( GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n) ) & 0x1)                                                        //��1λ���ݣ�nΪ���λ���źţ�
//GPIO  8λ����
#define GPIO_SET_8bit(PORTx,n,data)   GPIO_PDOR_REG(GPIOx[(PORTx)])=(( GPIO_PDOR_REG(GPIOx[(PORTx)])& ~(0xff<<(n)) )|(((data)&0xff)<<(n)))  //д8λ���ݣ�nΪ���λ���źţ�  
#define GPIO_DDR_8bit(PORTx,n,ddr)    GPIO_PDDR_REG(GPIOx[(PORTx)])=(( GPIO_PDDR_REG(GPIOx[(PORTx)])& ~(0xff<<(n)) )|(((ddr)&0x0ff)<<(n)))  //����8λ�����������nΪ���λ���źţ�
#define GPIO_GET_8bit(PORTx,n)        (( GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n) ) & 0xff)                                                       //��8λ���ݣ�nΪ���λ���źţ�
/****************************�ڲ�ʹ�ã��û�����Ҫ����****************************/
#define GPIO_SET_1(PORTx,n)          GPIO_PDOR_REG(GPIOx[(PORTx)]) |=  (1<<(n))      //�������Ϊ�ߵ�ƽ        ���磺GPIO_SET_H(PORTA,1)   PA1����ߵ�ƽ
#define GPIO_SET_0(PORTx,n)          GPIO_PDOR_REG(GPIOx[(PORTx)]) &= ~(1<<(n))      //�������Ϊ�͵�ƽ        ���磺GPIO_SET_L(PORTA,1)   PA1����͵�ƽ

void gpio_init(PTxn ptxn, uint8_t dir, uint8_t state) ;
void gpio_set(PTxn ptxn, uint8_t state) ;
uint8_t gpio_get(PTxn ptxn);
void gpio_turn(PTxn ptxn) ;

#endif     //��ֹ�ظ����壨gpio_H  ��β)
