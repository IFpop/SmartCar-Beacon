/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��ZYF/chiusir
��E-mail  ��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2020��4��24��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��Hightec4.9.3/Tasking6.3�����ϰ汾
��Target �� TC264DA/TC264D
��Crystal�� 20.000Mhz
��SYS PLL�� 200MHz
________________________________________________________________
����iLLD_1_0_1_11_0�ײ����,

ʹ�����̵�ʱ�򣬽������û�пո��Ӣ��·����
����CIFΪTC264DA�����⣬�����Ĵ������TC264D
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#include <include.h>//����ģ���ͷ�ļ�
#include <Main.h>
#define COF 2

App_Cpu0 g_AppCpu0; /**< \brief CPU 0 global data */
IfxCpu_mutexLock mutexCpu0InitIsOk = 1;   /** CPU0 ��ʼ����ɱ�־λ  */
IfxCpu_mutexLock mutexvec;

struct vector3f_t vec = {0.0f,0.0f,0.0f};
struct vector3f_t offset = {0.0f,0.0f,0.0f};
//uint32_t distance[3] = {0,0,0};
uint32_t distance[7] = {0,0,0,0,0,0,0};
uint32_t offset_flag = 0;
uint32_t direct_flag = 0;   //Ĭ����ǰ�� 0-ǰ��  1-��
char txt_main[50];

/*************************************************************************
*  �������ƣ�int core0_main (void)
*  ����˵����CPU0������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
int core0_main (void)
{
	//�ر�CPU���ж�
	IfxCpu_disableInterrupts();

	//�رտ��Ź�����������ÿ��Ź�ι����Ҫ�ر�
	IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
	IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());

	//��ȡ����Ƶ��
	g_AppCpu0.info.pllFreq = IfxScuCcu_getPllFrequency();
	g_AppCpu0.info.cpuFreq = IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex());
	g_AppCpu0.info.sysFreq = IfxScuCcu_getSpbFrequency();
	g_AppCpu0.info.stmFreq = IfxStm_getFrequency(&MODULE_STM0);

	//����CPU���ж�
	IfxCpu_enableInterrupts();

	EMEM_InitConfig();
	// ��ʼ��������֡�UART��TFT
	init_motor();

	//֪ͨCPU1   CPU0��ʼ�����
	IfxCpu_releaseMutex(&mutexCpu0InitIsOk);
	//________________________________________________________________________________
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//	test_DQ();
//	Test_GPIO_LED();
    while(1)//��ѭ��
	{
     	TOF10120();//ң��״̬�� TOF10120����һ��Լ9ms
//
//
    	delayms(30);
//    	sprintf(txt_main,"x:%02f",vec.x);
//    	TFTSPI_P8X16Str(1,1,txt_main,u16WHITE,u16BLACK);		//�ַ�����ʾ
//    	sprintf(txt_main,"y:%02f",vec.y);
//    	TFTSPI_P8X16Str(1,2,txt_main,u16WHITE,u16BLACK);		//�ַ�����ʾ
//    	sprintf(txt_main,"z:%02f",vec.z);
//    	TFTSPI_P8X16Str(1,3,txt_main,u16WHITE,u16BLACK);		//�ַ�����ʾ

//    	sprintf(txt_main,"x_:%02f",offset.x);
//    	TFTSPI_P8X16Str(1,4,txt_main,u16WHITE,u16BLACK);		//�ַ�����ʾ
//    	sprintf(txt_main,"y_:%02f",offset.y);
//    	TFTSPI_P8X16Str(1,5,txt_main,u16WHITE,u16BLACK);		//�ַ�����ʾ
//    	sprintf(txt_main,"z_:%02f",offset.z);
//    	TFTSPI_P8X16Str(1,6,txt_main,u16WHITE,u16BLACK);		//�ַ�����ʾ
	}
}



