#include "gpio.h"   //包含本构件头文件

volatile struct GPIO_Type *GPIOx[3]={GPIOA,GPIOB,GPIOC};

/*************************************************************************
*  函数名称：gpio_init
*  功能说明：初始化IO
*  函数返回：无
*  参数说明：port：端口号
*           dir：  引脚方向（0=输入，1=输出）
*           state：引脚初始状态（0=低电平，1=高电平）
*  for axample     gpio_init(PTG0,1,0);
*************************************************************************/
void gpio_init(PTxn ptxn, uint8_t dir, uint8_t state)
{	 
  //参数dir，决定引脚为输出还是输入
  if (1 == dir)   //输出
  {
    GPIO_PDDR_REG(GPIOX_BASE(ptxn)) |= (1 << PTn(ptxn));  //设置端口方向为输出
    gpio_set(ptxn , state);   //调用gpio_set函数，设定引脚输出状态
  }
  else 
  {
    //输入
    GPIO_PDDR_REG(GPIOX_BASE(ptxn)) &= ~(1 << PTn(ptxn));  //设置端口方向为输入
    GPIO_PIDR_REG(GPIOX_BASE(ptxn)) &= ~(1 << PTn(ptxn));  //设置端口方向为输入
  }

}

/*************************************************************************
*  函数名称：gpio_set
*  功能说明：设置引脚状态
*  函数返回：无
*  参数说明：ptxn： 端口号
*            state：输出初始状态,0=低电平,1=高电平
*  for example      gpio_set(PTG0, 1);
*************************************************************************/
void gpio_set(PTxn ptxn, uint8_t state)
{        
  if(state)
  {
     GPIO_SET(PTX(ptxn), PTn(ptxn), 1);
  }
  else 
  {
    GPIO_SET(PTX(ptxn), PTn(ptxn), 0);
  }
}
/*************************************************************************
*  函数名称：gpio_get
*  功能说明：获得引脚的状态
*  函数返回：无
*  参数说明：ptxn：端口号
*  for example     gpio_get(PTG0);
*************************************************************************/
uint8_t gpio_get(PTxn ptxn)
{	
  return GPIO_Get(PTX(ptxn),PTn(ptxn)) ;
}

/*************************************************************************
*  函数名称：gpio_turn
*  函数返回：无
*  功能说明：      翻转电平
*  参数说明：ptxn：端口号
*  for example     gpio_turn(PTG0);
*************************************************************************/
void gpio_turn(PTxn ptxn)
{
  GPIO_TURN(PTX(ptxn), PTn(ptxn));
}


