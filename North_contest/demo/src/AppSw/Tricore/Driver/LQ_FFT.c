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
本部分内容有待完善
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"


//#include "sinewave.inc"

// FFT变换长度
#define FFT_LENGTH 512

//优先级通常在Ifx_IntPrioDef.h中定义
#define ISR_PRIORITY_FFT_OUTPUT 1
#define ISR_PRIORITY_FFT_INPUT  2
#define ISR_PRIORITY_FFT_INTRA  3

//源波形，必须对齐256位，整数倍
__attribute__ ((aligned(256))) sint32 fftIn[FFT_LENGTH];//= {#include "sinewave.inc"};

//FFT变换结果，必须对齐256位，整数倍
__attribute__ ((aligned(256))) sint32 fftOut[FFT_LENGTH*2];//1024最大

// used globally
IfxFft_Fft fft;
IfxFft_Fft_Job fftJob;

//新建FFT模块配置
IfxFft_Fft_Config fftConfig;

//新建FFT作业配置
IfxFft_Fft_JobConfig fftJobConfig;

//中断次数计数
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
*  函数名称：void FFT_Init(void)
*  功能说明：FFT初始化函数
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：
*
*************************************************************************/
void FFT_Init(void)
{

	IfxFft_Fft_initModuleConfig(&fftConfig, &MODULE_FFT, &MODULE_LMU);

	//中断配置
	fftConfig.inputPriority = ISR_PRIORITY_FFT_INPUT;
	fftConfig.intraPriority = ISR_PRIORITY_FFT_INTRA;//“内部传输”中断优先级
	fftConfig.outputPriority = ISR_PRIORITY_FFT_OUTPUT;
	fftConfig.typeOfService = IfxCpu_Irq_getTos(IfxCpu_getCoreIndex());//调用CPU的服务类型

	//使用DMA通道进行input/output变换
	fftConfig.inputDmaChannelId = IfxDma_ChannelId_4;  //输入DMA通道，当(IFXFFT_FFT_DMA_SUPPORT != 0)时，使用中
	fftConfig.outputDmaChannelId = IfxDma_ChannelId_5; //输出DMA通道，当(IFXFFT_FFT_DMA_SUPPORT != 0)时，使用中
	fftConfig.discardDmaChannelId = IfxDma_ChannelId_6;//丢弃未使用样本的DMA通道，当(IFXFFT_FFT_DMA_SUPPORT != 0)时，使用中

	//安装interrupt handlers ISR_FFT_INTRA
	IfxCpu_Irq_installInterruptHandler(&ISR_FFT_INPUT, ISR_PRIORITY_FFT_INPUT);
	IfxCpu_Irq_installInterruptHandler(&ISR_FFT_OUTPUT, ISR_PRIORITY_FFT_OUTPUT);
	//IfxCpu_Irq_installInterruptHandler(&ISR_FFT_INTRA, ISR_PRIORITY_FFT_INTRA);
	IfxCpu_enableInterrupts();//总中断使能

	//FFT初始化
	IfxFft_Fft_initModule(&fft, &fftConfig);

    //作业配置
	IfxFft_Fft_initJobConfig(&fftJobConfig, &fft);

	//自定义作业
	fftJobConfig.fftLength = IfxFft_Length_512;//FFT变换的长度

	fftJobConfig.inputFormat = IfxFft_Input_realSInt32;        //输入格式：实际32位数的据64位字
	fftJobConfig.inputPtr = (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), (uint32)fftIn);//输入数据指针
	fftJobConfig.inputLength = FFT_LENGTH;                     //输入数据长度

	fftJobConfig.outputFormat = IfxFft_Output_complexSInt32;   //输出格式：复合32位数据的64位字
	fftJobConfig.outputPtr = (void *)IFXCPU_GLB_ADDR_DSPR(IfxCpu_getCoreId(), (uint32)fftOut);//输出数据指针
	fftJobConfig.outputLength = FFT_LENGTH;                    //输出数据长度
}

/*************************************************************************
*  函数名称：void FFT_Transform(void)
*  功能说明：FFT变换函数
*  参数说明：
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：
*************************************************************************/
void FFT_Transform(void)
{
	//初始化作业任务
	IfxFft_Fft_initJob(&fftJob, &fftJobConfig);

	//开始转换，直到转换结束返回TRUE.
	while (IfxFft_Fft_startJob(&fftJob) == FALSE) {}

	//等待中断计数为3
	while( fftInterruptCounter < 3 );
}






/////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////以下部分为功能测试/////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////





/*************************************************************************
*  函数名称：void Test_GPIO(void)
*  功能说明：GPIO点灯程序
*  参数说明：无
*  函数返回：无
*  修改时间：2020年3月10日
*  备    注：核心板上的LED灯闪烁，P10.6和P10.5闪灯，
*************************************************************************/
void Test_FFT(void)
{
	FFT_Init();
	while(1)
	{
		FFT_Transform();
		IfxPort_togglePin(&MODULE_P10, 6);//电平翻转
		delayms(500);                     //延时等待
	}
}
