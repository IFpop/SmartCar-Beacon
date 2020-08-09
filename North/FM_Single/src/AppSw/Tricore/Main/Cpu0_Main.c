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

App_Cpu0 g_AppCpu0; /**< \brief CPU 0 global data */
IfxCpu_mutexLock mutexCpu0InitIsOk = 1;   /** CPU0 ��ʼ����ɱ�־λ  */
IfxCpu_mutexLock mutevec = 0;

struct vector3f_t vec = {0.0f,0.0f,0.0f};
struct vector3f_t offset = {0.0f,0.0f,0.0f};
uint32_t offset_flag = 0;
uint32_t direct_flag = 0;   //Ĭ����ǰ�� 1-ǰ��  1--��
uint32_t arrive_flag = 0;   // 1 ��ʾ�ﵽ��ƾ���
uint32_t z_change_flag = 0;
float w_target = 0.0;
uint32_t dd = 0;
float S = 0.0;

char txt[50];

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
    	 if(arrive_flag == 0&&direct_flag!=0){
    	 	 TOF10120();//ң��״̬�� TOF10120����һ��Լ9ms
    	 }
    	 delayms(10);

//    	sprintf(txt,"x:%02f",vec.x);
//    	TFTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
//    	sprintf(txt,"y:%02f",vec.y);
//    	TFTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
//    	sprintf(txt,"z:%02f",vec.z);
//    	TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ

//    	sprintf(txt,"x_:%02f",offset.x);
//    	TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
//    	sprintf(txt,"y_:%02f",offset.y);
//    	TFTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
//    	sprintf(txt,"z_:%02f",offset.z);
//    	TFTSPI_P8X16Str(1,6,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	}
}



