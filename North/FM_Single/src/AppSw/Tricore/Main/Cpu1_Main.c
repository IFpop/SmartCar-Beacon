/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��zyf/chiusir
��E-mail  ��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2020��4��10��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��Hightec4.9.3/Tasking6.3�����ϰ汾
��Target �� TC264DA
��Crystal�� 20.000Mhz
��SYS PLL�� 200MHz
����iLLD_1_0_1_11_0�ײ����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include "include.h"
#include "Main.h"

//IfxCpu_mutexLock mutexTFTIsOk = 0;   /** TFT18ʹ�ñ�־λ  */
uint32_t t1 = 0;

int core1_main (void)
{

    IfxCpu_enableInterrupts();
    /*
     * �رտ��Ź�
     * */
    IfxScuWdt_disableCpuWatchdog (IfxScuWdt_getCpuWatchdogPassword ());

    //�ȴ�CPU0 ��ʼ�����
    while(!IfxCpu_acquireMutex(&mutexCpu0InitIsOk));

    //  VoiceInit();
    //  Init_RDA5807();
    // Test_RDA5807();

    while(1)//��ѭ��
    {
//    	int x = 1;
//    	int y = 2;
//    	int w = 3;
//    	int h = 4;
//    	int length = 5;
//
//    	//sscanf((const char*)buffer, "%d %d %d %d %d",&x,&y,&w,&h,&length);
//    	ANO_DT_send_int16(x, y, w, h, length, 0, 0,0);
    	// VoiceProcess();
    }

}
