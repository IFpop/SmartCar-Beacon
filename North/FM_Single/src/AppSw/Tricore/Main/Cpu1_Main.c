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

    VoiceInit();
//	Test_RDA5807();
    Init_RDA5807();

    while(1)//��ѭ��
    {
//    	t1++;
    	VoiceProcess();

//    	sprintf(txt,"t1:%d",t1);
//    	TFTSPI_P8X16Str(1,7,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
    }

}
