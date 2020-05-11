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


extern float g_measuredPwmDutyCycle;                   /* Global variable for duty cycle of generated PWM signal   */
extern float g_measuredPwmFreq_Hz;                     /* Global variable for frequency calculation of PWM signal  */

/*************************************************************************
*  函数名称：void Test_GTM_ATOM_PWM(void)
*  功能说明：GTM测试函数
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月22日
*  备    注：P20.7作为PWM输出口，P33.12作为TIM输入口，两者短接后，串口P14.0发送到上位机
*  默认频率是125HZ，占空比50%
*************************************************************************/
void LQ_TIM_InputCature(void)
{
	char txt[16];

	GTM_TIM_Init(IfxGtm_TIM0_0_TIN34_P33_12_IN);//P20_7_OUT  P33_12_IN
	TOM_PWM_InitConfig(IfxGtm_TOM0_11_TOUT63_P20_7_OUT, 5000, 125);//初始化P20_7 作为PWM输出口 频率125Hz 占空比 百分之(5000/TOM_PWM_MAX)*100
	while(1)
	{
		Get_GTM_TIM(IfxGtm_TIM0_0_TIN34_P33_12_IN);
		sprintf(txt,"\nHz:%05d;dty:%d  ",(int)g_measuredPwmFreq_Hz,(int)(g_measuredPwmDutyCycle));
		//串口发送到上位机
		UART_PutStr(UART0,txt);//数据输出到上位机，如：Hz:00124;dty:00050，如果输入悬空则为随机数
    	LED_Ctrl(LED0,RVS);        //电平翻转,LED闪烁
		delayms(500);              //延时等待
	}
}
