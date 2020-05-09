#ifndef _GPIO_H       //防止重复定义（gpio_H  开头)
#define _GPIO_H

#include "gpio_icf.h" 
/*

KBI0：
PTA0~PTA7  PTB0~PTB7  PTC0~PTC7  PTD0~PTD7
   0~7      8~15       16~23      24~31

KBI0：
PTE0~PTE7  PTF0~PTF7  PTG0~PTG7  PTH0~PTH7
   0~7      8~15       16~23      24~31
*/

#define PTX(PTxn)           ((PTxn)>>5)              //PORTX PORTA PORTB 
#define PTn(PTxn)           ((PTxn)&0x1f)           //PIN   0~31
#define GPIOX_BASE(PTxn)     GPIOx[PTX(PTxn)]       //GPIOx模块的地址


/*
 * 定义管脚方向
 */

#define GPO   1u
#define GPI   0u   
#define HIGH  1u
#define LOW   0u

void gpio_init(PTxn ptxn, uint8_t dir, uint8_t state);
void gpio_set(PTxn ptxn, uint8_t state);
uint8_t gpio_get(PTxn ptxn);
void gpio_turn(PTxn ptxn);

#define GPIO_SET(PORTx,n,x)           GPIO_SET_##x((PORTx),(n))                                 //设置输出电平x，x为0或1   例如 GPIO_SET(PORTA,1,1)  PA1输出高电平
#define GPIO_TURN(PORTx,n)           (GPIO_PDOR_REG(GPIOx[(PORTx)]) ^=  (1<<(n)))               //翻转输出电平
#define GPIO_Get(PORTx,n)            ((GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n))&0x1)                 //读取引脚输入状态
//GPIO  1位操作
#define GPIO_SET_1bit(PORTx,n,data)   GPIO_PDOR_REG(GPIOx[(PORTx)])=(( GPIO_PDOR_REG(GPIOx[(PORTx)])& ~(0x1<<(n)) )|(((data)&0x01)<<(n)))   //写1位数据（n为最低位引脚号）
#define GPIO_DDR_1bit(PORTx,n,ddr)    GPIO_PDDR_REG(GPIOx[(PORTx)])=(( GPIO_PDDR_REG(GPIOx[(PORTx)])& ~(0x1<<(n)) )|(((ddr)&0x01)<<(n)))    //设置1位输入输出方向（n为最低位引脚号）
#define GPIO_GET_1bit(PORTx,n)        (( GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n) ) & 0x1)                                                        //读1位数据（n为最低位引脚号）
//GPIO  8位操作
#define GPIO_SET_8bit(PORTx,n,data)   GPIO_PDOR_REG(GPIOx[(PORTx)])=(( GPIO_PDOR_REG(GPIOx[(PORTx)])& ~(0xff<<(n)) )|(((data)&0xff)<<(n)))  //写8位数据（n为最低位引脚号）  
#define GPIO_DDR_8bit(PORTx,n,ddr)    GPIO_PDDR_REG(GPIOx[(PORTx)])=(( GPIO_PDDR_REG(GPIOx[(PORTx)])& ~(0xff<<(n)) )|(((ddr)&0x0ff)<<(n)))  //设置8位输入输出方向（n为最低位引脚号）
#define GPIO_GET_8bit(PORTx,n)        (( GPIO_PDIR_REG(GPIOx[(PORTx)])>>(n) ) & 0xff)                                                       //读8位数据（n为最低位引脚号）
/****************************内部使用，用户不需要关心****************************/
#define GPIO_SET_1(PORTx,n)          GPIO_PDOR_REG(GPIOx[(PORTx)]) |=  (1<<(n))      //设置输出为高电平        例如：GPIO_SET_H(PORTA,1)   PA1输出高电平
#define GPIO_SET_0(PORTx,n)          GPIO_PDOR_REG(GPIOx[(PORTx)]) &= ~(1<<(n))      //设置输出为低电平        例如：GPIO_SET_L(PORTA,1)   PA1输出低电平

void gpio_init(PTxn ptxn, uint8_t dir, uint8_t state) ;
void gpio_set(PTxn ptxn, uint8_t state) ;
uint8_t gpio_get(PTxn ptxn);
void gpio_turn(PTxn ptxn) ;

#endif     //防止重复定义（gpio_H  结尾)
