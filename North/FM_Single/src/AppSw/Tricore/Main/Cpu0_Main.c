/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技TC264DA核心板
【编    写】ZYF/chiusir
【E-mail  】chiusir@163.com
【软件版本】V1.1 版权所有，单位使用请先联系授权
【最后更新】2020年4月24日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://longqiu.taobao.com
------------------------------------------------
【dev.env.】Hightec4.9.3/Tasking6.3及以上版本
【Target 】 TC264DA/TC264D
【Crystal】 20.000Mhz
【SYS PLL】 200MHz
________________________________________________________________
基于iLLD_1_0_1_11_0底层程序,

使用例程的时候，建议采用没有空格的英文路径，
除了CIF为TC264DA独有外，其它的代码兼容TC264D
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include <include.h>//各个模块的头文件
#include <Main.h>

App_Cpu0 g_AppCpu0; /**< \brief CPU 0 global data */
IfxCpu_mutexLock mutexCpu0InitIsOk = 1;   /** CPU0 初始化完成标志位  */
IfxCpu_mutexLock mutevec = 0;

struct vector3f_t vec = {0.0f,0.0f,0.0f};
struct vector3f_t offset = {0.0f,0.0f,0.0f};
uint32_t offset_flag = 0;
uint32_t direct_flag = 0;   //默认在前方 1-前方  1--后方
uint32_t arrive_flag = 0;   // 1 表示达到灭灯距离
uint32_t z_change_flag = 0;
float w_target = 0.0;
uint32_t dd = 0;
float S = 0.0;

char txt[50];

/*************************************************************************
*  函数名称：int core0_main (void)
*  功能说明：CPU0主函数
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：
*************************************************************************/
int core0_main (void)
{
	//关闭CPU总中断
	IfxCpu_disableInterrupts();

	//关闭看门狗，如果不设置看门狗喂狗需要关闭
	IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
	IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

	//读取总线频率
	g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
	g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());
	g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
	g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

	//开启CPU总中断
	IfxCpu_enableInterrupts();

	EMEM_InitConfig();
	// 初始化电机部分、UART、TFT
	init_motor();

	//通知CPU1   CPU0初始化完成
	IfxCpu_releaseMutex(&mutexCpu0InitIsOk);
	//________________________________________________________________________________
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	test_DQ();
//	Test_GPIO_LED();

    while(1)//主循环
	{
    	 if(arrive_flag == 0&&direct_flag!=0){
    	 	 TOF10120();//遥控状态下 TOF10120运行一次约9ms
    	 }
    	 delayms(10);

//    	sprintf(txt,"x:%02f",vec.x);
//    	TFTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//字符串显示
//    	sprintf(txt,"y:%02f",vec.y);
//    	TFTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//字符串显示
//    	sprintf(txt,"z:%02f",vec.z);
//    	TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//字符串显示

//    	sprintf(txt,"x_:%02f",offset.x);
//    	TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//字符串显示
//    	sprintf(txt,"y_:%02f",offset.y);
//    	TFTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//字符串显示
//    	sprintf(txt,"z_:%02f",offset.z);
//    	TFTSPI_P8X16Str(1,6,txt,u16WHITE,u16BLACK);		//字符串显示
	}
}



