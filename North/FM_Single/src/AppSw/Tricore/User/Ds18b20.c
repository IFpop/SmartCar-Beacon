/*
 * Ds18b20.c
 *
 *  Created on: 2020年8月2日
 *      Author: pengs
 */

#include <include.h>

char txt_DQ[50];
/*******************************************************************************
* 函 数 名         : datapros()
* 函数功能		   : 温度读取处理转换函数
* 输    入         : temp
* 输    出         : 无
*******************************************************************************/
void datapros(int temp)
{
   	float tp = 0.0;;
	if(temp< 0)				//当温度值为负数
  	{
		//因为读取的温度是实际温度的补码，所以减1，再取反求出原码
		temp=temp-1;
		temp=~temp;
		tp=(float)temp;
		temp=(float)(tp*0.0625+0.5);
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算加上0.5，还是在小数点后面。

  	}
 	else
  	{
		tp=(float)temp;//因为数据处理有小数点所以将温度赋给一个浮点型变量
		//如果温度是正的那么，那么正数的原码就是补码它本身
		temp=(float)(tp*0.0625+0.5);
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算加上0.5，还是在小数点后面。
	}
	sprintf(txt_DQ,"T:%02d  ",temp);
	TFTSPI_P8X16Str(1,9,txt_DQ,u16WHITE,u16BLACK);		//字符串显示
}


/*******************************************************************************
* 函 数 名         : Ds18b20Init
* 函数功能		   : 初始化
* 输    入         : 无
* 输    出         : 初始化成功返回1，失败返回0
*******************************************************************************/
unsigned char Ds18b20Init()
{
	unsigned char i = 0;
	DQ_INIT;			 //将总线拉低480us~960us
	delayus(642);         //延时642us
	DQ_H;			//然后拉高总线，如果DS18B20做出反应会将在15us~60us后总线拉低
	i = 0;
	while(DQ_READ)	//等待DS18B20拉低总线
	{
		delayms(1);
		i++;
		if(i>5)//等待>5MS
		{
			return 0;//初始化失败
		}
	}
	return 1;//初始化成功
}

/*******************************************************************************
* 函 数 名         : Ds18b20WriteByte
* 函数功能		   : 向18B20写入一个字节
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void Ds18b20WriteByte(unsigned char dat)
{
	uint32_t j = 0;

	for(j=0; j<8; j++)
	{
		DQ_L;	     	  //每写入一位数据之前先把总线拉低1us
		delayus(1);
		PIN_Write(DSPORT,dat&0x01);
		delayus(68); //延时68us，持续时间最少60us
		DQ_H;	//然后释放总线，至少1us给总线恢复时间才能接着写入第二个数值
		delayus(1);
		dat >>= 1;
	}
}

/*******************************************************************************
* 函 数 名         : Ds18b20ReadByte
* 函数功能		   : 读取一个字节
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
unsigned char Ds18b20ReadByte()
{
	unsigned char byte = 0, bi = 0;
	uint32_t j;
	for(j=8; j>0; j--)
	{
		DQ_L;//先将总线拉低1us
		delayus(5);
		DQ_H;//然后释放总线
		delayus(10);//延时6us等待数据稳定
		bi = DQ_READ;	 //读取数据，从最低位开始读取
		/*将byte左移一位，然后与上右移7位后的bi，注意移动之后移掉那位补0。*/
		byte = (byte >> 1) | (bi << 7);
		delayus(60);		//读取完之后等待48us再接着读取下一个数
	}
	return byte;
}

/*******************************************************************************
* 函 数 名         : Ds18b20ChangTemp
* 函数功能		   : 让18b20开始转换温度
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void  Ds18b20ChangTemp()
{
	Ds18b20Init();
	delayms(1);
	Ds18b20WriteByte(0xcc);		//跳过ROM操作命令
	Ds18b20WriteByte(0x44);	    //温度转换命令
	delayms(1);
}

/*******************************************************************************
* 函 数 名         : Ds18b20ReadTempCom
* 函数功能		   : 发送读取温度命令
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
void  Ds18b20ReadTempCom()
{

	Ds18b20Init();
	delayms(1);
	Ds18b20WriteByte(0xcc);	 //跳过ROM操作命令
	Ds18b20WriteByte(0xbe);	 //发送读取温度命令
}

/*******************************************************************************
* 函 数 名         : Ds18b20ReadTemp
* 函数功能		   : 读取温度
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int Ds18b20ReadTemp()
{
	int temp = 0;
	unsigned char tmh = 0, tml = 0;
	Ds18b20ChangTemp();			 	//先写入转换命令
	Ds18b20ReadTempCom();			//然后等待转换完后发送读取温度命令
	tml = Ds18b20ReadByte();		//读取温度值共16位，先读低字节
	sprintf(txt_DQ,"tml:%02d  ",tml);
	TFTSPI_P8X16Str(1,0,txt_DQ,u16WHITE,u16BLACK);//字符串显示

	tmh = Ds18b20ReadByte();		//再读高字节
	sprintf(txt_DQ,"tmh:%02d  ",tmh);
	TFTSPI_P8X16Str(1,1,txt_DQ,u16WHITE,u16BLACK);		//字符串显示
	temp = tmh;
	temp <<= 8;
	temp |= tml;

	sprintf(txt_DQ,"temp:%02d  ",temp);
	TFTSPI_P8X16Str(1,2,txt_DQ,u16WHITE,u16BLACK);		//字符串显示
	return temp;
}
