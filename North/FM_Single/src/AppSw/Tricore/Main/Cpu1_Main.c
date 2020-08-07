/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
【平    台】北京龙邱智能科技TC264DA核心板
【编    写】zyf/chiusir
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
基于iLLD_1_0_1_11_0底层程序
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"
#include "Main.h"

//IfxCpu_mutexLock mutexTFTIsOk = 0;   /** TFT18使用标志位  */
uint32_t t1 = 0;

int core1_main (void)
{

    IfxCpu_enableInterrupts();
    /*
     * 关闭看门狗
     * */
    IfxScuWdt_disableCpuWatchdog (IfxScuWdt_getCpuWatchdogPassword ());

    //等待CPU0 初始化完成
    while(!IfxCpu_acquireMutex(&mutexCpu0InitIsOk));

    VoiceInit();
//	Test_RDA5807();
    Init_RDA5807();

    while(1)//主循环
    {
//    	t1++;
    	VoiceProcess();

//    	sprintf(txt,"t1:%d",t1);
//    	TFTSPI_P8X16Str(1,7,txt,u16WHITE,u16BLACK);		//字符串显示
    }

}
