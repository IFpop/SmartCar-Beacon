/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��ZYF/chiusir
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
________________________________________________________________
�����������д�����
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"


//#include "sinewave.inc"

// FFT�任����
#define FFT_LENGTH 512

//���ȼ�ͨ����Ifx_IntPrioDef.h�ж���
#define ISR_PRIORITY_FFT_OUTPUT 1
#define ISR_PRIORITY_FFT_INPUT  2
#define ISR_PRIORITY_FFT_INTRA  3

//Դ���Σ��������256λ��������
__attribute__ ((aligned(256))) sint32 fftIn[FFT_LENGTH];//= {#include "sinewave.inc"};

//FFT�任������������256λ��������
__attribute__ ((aligned(256))) sint32 fftOut[FFT_LENGTH*2];//1024���

// used globally
IfxFft_Fft fft;
IfxFft_Fft_Job fftJob;

//�½�FFTģ������
IfxFft_Fft_Config fftConfig;

//�½�FFT��ҵ����
IfxFft_Fft_JobConfig fftJobConfig;

//�жϴ�������
volatile uint32 fftInterruptCounter;

IFX_INTERRUPT(ISR_FFT_INTRA, 0, ISR_PRIORITY_FFT_INTRA)
{
    IfxFft_Fft_isrIntra(&fft);
}

IFX_INTERRUPT(ISR_FFT_INPUT, 0, ISR_PRIORITY_FFT_INPUT)
{
    IfxFft_Fft_isrInput(&fft);
}

IFX_INTERRUPT(ISR_FFT_OUTPUT, 0, ISR_PRIORITY_FFT_OUTPUT)
{
    ++fftInterruptCounter;

    IfxFft_Fft_isrOutput(&fft);

    // do the next transform:
    while (IfxFft_Fft_startJob(&fftJob) == FALSE) {}
}


/*************************************************************************
*  �������ƣ�void FFT_Init(void)
*  ����˵����FFT��ʼ������
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*
*************************************************************************/
void FFT_Init(void)
{

	IfxFft_Fft_initModuleConfig(&fftConfig, &MODULE_FFT, &MODULE_LMU);

	//�ж�����
	fftConfig.inputPriority = ISR_PRIORITY_FFT_INPUT;
	fftConfig.intraPriority = ISR_PRIORITY_FFT_INTRA;//���ڲ����䡱�ж����ȼ�
	fftConfig.outputPriority = ISR_PRIORITY_FFT_OUTPUT;
	fftConfig.typeOfService = IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());//����CPU�ķ�������

	//ʹ��DMAͨ������input/output�任
	fftConfig.inputDmaChannelId = IfxDma_ChannelId_4;  //����DMAͨ������(IFXFFT_FFT_DMA_SUPPORT != 0)ʱ��ʹ����
	fftConfig.outputDmaChannelId = IfxDma_ChannelId_5; //���DMAͨ������(IFXFFT_FFT_DMA_SUPPORT != 0)ʱ��ʹ����
	fftConfig.discardDmaChannelId = IfxDma_ChannelId_6;//����δʹ��������DMAͨ������(IFXFFT_FFT_DMA_SUPPORT != 0)ʱ��ʹ����

	//��װinterrupt handlers ISR_FFT_INTRA
	IfxCpu_Irq_installInterruptHandler(&ISR_FFT_INPUT, ISR_PRIORITY_FFT_INPUT);
	IfxCpu_Irq_installInterruptHandler(&ISR_FFT_OUTPUT, ISR_PRIORITY_FFT_OUTPUT);
	//IfxCpu_Irq_installInterruptHandler(&ISR_FFT_INTRA, ISR_PRIORITY_FFT_INTRA);
	IfxCpu_enableInterrupts();//���ж�ʹ��

	//FFT��ʼ��
	IfxFft_Fft_initModule(&fft, &fftConfig);

    //��ҵ����
	IfxFft_Fft_initJobConfig(&fftJobConfig, &fft);

	//�Զ�����ҵ
	fftJobConfig.fftLength = IfxFft_Length_512;//FFT�任�ĳ���

	fftJobConfig.inputFormat = IfxFft_Input_realSInt32;        //�����ʽ��ʵ��32λ���ľ�64λ��
	fftJobConfig.inputPtr = (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), (uint32)fftIn);//��������ָ��
	fftJobConfig.inputLength = FFT_LENGTH;                     //�������ݳ���

	fftJobConfig.outputFormat = IfxFft_Output_complexSInt32;   //�����ʽ������32λ���ݵ�64λ��
	fftJobConfig.outputPtr = (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), (uint32)fftOut);//�������ָ��
	fftJobConfig.outputLength = FFT_LENGTH;                    //������ݳ���
}

/*************************************************************************
*  �������ƣ�void FFT_Transform(void)
*  ����˵����FFT�任����
*  ����˵����
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
void FFT_Transform(void)
{
	//��ʼ����ҵ����
	IfxFft_Fft_initJob(&fftJob, &fftJobConfig);

	//��ʼת����ֱ��ת����������TRUE.
	while (IfxFft_Fft_startJob(&fftJob) == FALSE) {}

	//�ȴ��жϼ���Ϊ3
	while( fftInterruptCounter < 3 );
}






/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////���²���Ϊ���ܲ���/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////





/*************************************************************************
*  �������ƣ�void Test_GPIO(void)
*  ����˵����GPIO��Ƴ���
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע�����İ��ϵ�LED����˸��P10.6��P10.5���ƣ�
*************************************************************************/
void Test_FFT(void)
{
	FFT_Init();
	while(1)
	{
		FFT_Transform();
		IfxPort_togglePin(&MODULE_P10, 6);//��ƽ��ת
		delayms(500);                     //��ʱ�ȴ�
	}
}
