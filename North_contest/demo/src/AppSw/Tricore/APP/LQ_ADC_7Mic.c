/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技TC264DA核心板
【编    写】ZYF/chiusir
【E-mail  】chiusir@163.com
【软件版本】V1.1 版权所有，单位使用请先联系授权
【最后更新】2020年4月10日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】Hightec4.9.3/Tasking6.3及以上版本
【Target 】 TC264DA
【Crystal】 20.000Mhz
【SYS PLL】 200MHz
________________________________________________________________

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "..\Driver\include.h"//各个模块的头文件



/*************************************************************************
*  函数名称：void TestADC(void)
*  功能说明：ADC采集测试
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：
*************************************************************************/
void Test_ADC(void)
{
	unsigned long i;
    char txt[16];

    ADC_InitConfig(ADC0, 80000); //初始化
    ADC_InitConfig(ADC1, 80000);
    ADC_InitConfig(ADC2, 80000);
    ADC_InitConfig(ADC3, 80000);
    ADC_InitConfig(ADC4, 80000);
    ADC_InitConfig(ADC5, 80000);
    ADC_InitConfig(ADC6, 80000);
    ADC_InitConfig(ADC7, 80000);

    OLED_Init();
    OLED_P6x8Str(0,0,"adc test");
    while(1)
    {
    	unsigned long nowTime = STM_GetNowUs(STM0);
    	for( i = 0; i < 10000; i++)
    	{
    		ADC_Read(ADC0);
    	}
    	unsigned long time = STM_GetNowUs(STM0) - nowTime;
    	sprintf(txt, "time : %d", time);
    	OLED_P6x8Str(0,3,txt);

    }

}
/*************************************************************************
*  函数名称：void Test_Beacon7mic(void)
*  功能说明：采集测试6+1麦克风阵列
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：
*************************************************************************/
void Test_ADC_7mic(void)
{
	unsigned char chnIx;
    char txt[16];
    unsigned int MICVmin[8];

    ADC_InitConfig(ADC0, 80000); //初始化
    ADC_InitConfig(ADC1, 80000); //初始化
    ADC_InitConfig(ADC2, 80000); //初始化
    ADC_InitConfig(ADC3, 80000); //初始化
    ADC_InitConfig(ADC4, 80000); //初始化
    ADC_InitConfig(ADC5, 80000); //初始化
    ADC_InitConfig(ADC6, 80000); //初始化
    ADC_InitConfig(ADC7, 80000); //初始化
    delayms(500);                //延时等待
	UART_PutStr(UART0,"\n-------------------------------------------------\n");//分界线
	for(chnIx=0; chnIx<8; ++chnIx)
	{
		MICVmin[chnIx]=ADC_Read(chnIx);
		//转换结果为字符串，串口发送或者屏幕显示，AN0--AN7
		sprintf(txt,"[%d]:%05d  ",chnIx,MICVmin[chnIx]);
		//串口发送到上位机
		UART_PutStr(UART0,txt);//AN0--AN7十进制数据输出到上位机
	}
	delayms(500);                //延时等待
	UART_PutStr(UART0,"\n-------------------------------------------------\n");//分界线
	while(1)
	{
		//检查转换结果
		for(chnIx=0; chnIx<8; ++chnIx)
		{
			//转换结果为字符串，串口发送或者屏幕显示，AN0--AN7
			sprintf(txt,"[%d]:%05d  ",chnIx,ADC_Read(chnIx)-MICVmin[chnIx]);

			//串口发送到上位机
			if(chnIx==0) UART_PutStr(UART0,"\n");//重新起一行
			UART_PutStr(UART0,txt);//AN0--AN7十进制数据输出到上位机
		}
    	LED_Ctrl(LED0,RVS);        //电平翻转,LED闪烁
		delayms(500);              //延时等待
	}
}
//
