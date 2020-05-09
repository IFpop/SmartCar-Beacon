#include "gpio.h"   //����������ͷ�ļ�

volatile struct GPIO_Type *GPIOx[3]={GPIOA,GPIOB,GPIOC};

/*************************************************************************
*  �������ƣ�gpio_init
*  ����˵������ʼ��IO
*  �������أ���
*  ����˵����port���˿ں�
*           dir��  ���ŷ���0=���룬1=�����
*           state�����ų�ʼ״̬��0=�͵�ƽ��1=�ߵ�ƽ��
*  for axample     gpio_init(PTG0,1,0);
*************************************************************************/
void gpio_init(PTxn ptxn, uint8_t dir, uint8_t state)
{	 
  //����dir����������Ϊ�����������
  if (1 == dir)   //���
  {
    GPIO_PDDR_REG(GPIOX_BASE(ptxn)) |= (1 << PTn(ptxn));  //���ö˿ڷ���Ϊ���
    gpio_set(ptxn , state);   //����gpio_set�������趨�������״̬
  }
  else 
  {
    //����
    GPIO_PDDR_REG(GPIOX_BASE(ptxn)) &= ~(1 << PTn(ptxn));  //���ö˿ڷ���Ϊ����
    GPIO_PIDR_REG(GPIOX_BASE(ptxn)) &= ~(1 << PTn(ptxn));  //���ö˿ڷ���Ϊ����
  }

}

/*************************************************************************
*  �������ƣ�gpio_set
*  ����˵������������״̬
*  �������أ���
*  ����˵����ptxn�� �˿ں�
*            state�������ʼ״̬,0=�͵�ƽ,1=�ߵ�ƽ
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
*  �������ƣ�gpio_get
*  ����˵����������ŵ�״̬
*  �������أ���
*  ����˵����ptxn���˿ں�
*  for example     gpio_get(PTG0);
*************************************************************************/
uint8_t gpio_get(PTxn ptxn)
{	
  return GPIO_Get(PTX(ptxn),PTn(ptxn)) ;
}

/*************************************************************************
*  �������ƣ�gpio_turn
*  �������أ���
*  ����˵����      ��ת��ƽ
*  ����˵����ptxn���˿ں�
*  for example     gpio_turn(PTG0);
*************************************************************************/
void gpio_turn(PTxn ptxn)
{
  GPIO_TURN(PTX(ptxn), PTn(ptxn));
}


