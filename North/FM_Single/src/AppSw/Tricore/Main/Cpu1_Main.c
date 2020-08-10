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
    Init_RDA5807();

    uint32_t Rda_count = 0;
    unsigned char RSSI = 0;
    while(1)//主循环
    {
   	RSSI=RDA5807_GetRssi();
		if(RSSI < 30){  // 准备发车
			Rda_count++;
		}
		else{ // 等待声音信号
			Rda_count = 0;
		}
		if(Rda_count < 3){
			VoiceProcess();
		}
		else{
			vec.x = 0;
			vec.y = 0;
			vec.z = 0;
		}
    }

}
