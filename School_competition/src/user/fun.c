#include "include.h"
//����ʱ
/*void delay_ms(long t)
{
    while(t--)
    {
      delay_us(1000);
    }
}
*/
//32λ����ֵ����
int mylabs(int temp_data)
{
  return(temp_data>0?temp_data:-temp_data);
}

//16λ����ֵ����
int16 myabs(int16 temp_data)
{
  return(temp_data>0?temp_data:-temp_data);
}

//32λ�޷�����   ��X�޷���-y��+y֮��
int limit(int x, int y)
{
    if(x>y)             return(y);
    else if(x<-y)       return(-y);
    return(x);
}

//32λ�޷�����   ��X�޷��� a�� b֮��
int limit_ab(int x, int a, int b)
{
    if(x>b)             return(b);
    else if(x<a)        return(a);
    return(x);
}