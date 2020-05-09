#include "include.h"
//简单延时
/*void delay_ms(long t)
{
    while(t--)
    {
      delay_us(1000);
    }
}
*/
//32位绝对值函数
int mylabs(int temp_data)
{
  return(temp_data>0?temp_data:-temp_data);
}

//16位绝对值函数
int16 myabs(int16 temp_data)
{
  return(temp_data>0?temp_data:-temp_data);
}

//32位限幅函数   将X限幅在-y到+y之间
int limit(int x, int y)
{
    if(x>y)             return(y);
    else if(x<-y)       return(-y);
    return(x);
}

//32位限幅函数   将X限幅在 a到 b之间
int limit_ab(int x, int a, int b)
{
    if(x>b)             return(b);
    else if(x<a)        return(a);
    return(x);
}