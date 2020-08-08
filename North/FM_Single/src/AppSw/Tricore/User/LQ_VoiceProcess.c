#include "include.h"

// 标记当前计算是否有效
float success_f = 1;

// 声音计算出的中间变量
float x = 0.0;
float y = 0.0;
float z = 0.0;

// 方向决策  投票 求均值
static int32_t last_direct[3] = {0,0,0};
static uint32_t length = 0;

/* 存放相关峰值下标 */
int16_t acorIndex[3];
/* 记录时间 */
uint32_t nowTime = 0;
/*
 * adc采集完成标志位
 */
volatile uint8  AdcFinishFlag = 0;
/*
 * adc双buff缓冲区  缓冲完成的区域序号
 */
volatile uint8  AdcBuffIndex = 0;
/*
 * adc数组下标
 */
volatile uint32 adcCount = 0;

/*
 * ADC数据   adc0 1 2 3 采集麦克风信号
 *
 *     2     1
 *
 *     3     0
 */
__attribute__ ((aligned(256)))  volatile int16_t g_adc0Data[2][ADC_DATA_LEN];
__attribute__ ((aligned(256)))  volatile int16_t g_adc1Data[2][ADC_DATA_LEN];
__attribute__ ((aligned(256)))  volatile int16_t g_adc2Data[2][ADC_DATA_LEN];
__attribute__ ((aligned(256)))  volatile int16_t g_adc3Data[2][ADC_DATA_LEN];


/*!
  * @brief    信标一些初始化函数
  *
  */
void VoiceInit(void)
{
	// ADC_InitConfig(MIC1, 1000000); //初始化 1号麦克风
	ADC_InitConfig(MIC2, 1000000); //初始化 2号麦克风
	ADC_InitConfig(MIC3, 1000000); //初始化 3号麦克风
	ADC_InitConfig(MIC4, 1000000); //初始化 4号麦克风
	ADC_InitConfig(RF, 1000000); //初始化 射频模块

	CCU6_InitConfig(CCU60, CCU6_Channel0, 100);  //100us进入一次中断  中断中采集adc数据
}

/*!
  * @brief    ccu6 采集中断服务函数   声音信号采集
  */
void VoiceGetSample(void)
{
	static uint8 adcIndex = 0;

	if(adcCount >= ADC_DATA_LEN)
	{
		adcCount = 0;
		AdcFinishFlag = 1;

		/* 切换buff缓冲区 */
		if(adcIndex == 0)
		{
			adcIndex = 1;
			AdcBuffIndex = 0;
		}
		else
		{
			adcIndex = 0;
			AdcBuffIndex = 1;
		}
	}

	if(AdcFinishFlag == 0)
	{
		g_adc0Data[adcIndex][adcCount] = ADC_Read(RF);
//		g_adc0Data[adcIndex][adcCount] = ADC_Read(MIC1);
		g_adc1Data[adcIndex][adcCount] = ADC_Read(MIC2);
		g_adc2Data[adcIndex][adcCount] = ADC_Read(MIC3);
		g_adc3Data[adcIndex][adcCount] = ADC_Read(MIC4);

		adcCount++;
	}
}


/*!
  * @brief    归一化处理
  *
  * @param    x   ： 要处理数据
  * @param    len ： 要处理数据长度
  */
void Normal(int16_t *x, uint16 len)
{
	float sum = 0;
	int   i;

	for(i = 0; i < len; i++)
	{
		sum += x[i];
	}

	sum = sum / len;


	for(i = 0; i < len; i++)
	{
		x[i] -= sum;
	}
}

// 求指定数组平均值
int Average(int32_t* tuple,uint32_t L){
	float sum = 0;
	for(int i = 0 ; i < L ;i++){
		sum += tuple[i];
	}
	sum = (float)(sum / 3);
	if(sum >= 0){
		return 1;
	}
	else{
		return -1;
	}
}

/*!
  * @brief    麦克风数据处理  获取角度信息
  * @return   最大相关位置
  */
void VoiceProcess(void)
{
	float S1 = 0.0;
	float S2 = 0.0;
	float S_sub = 0.0;
	float M2sum = 0.0;
	float S = 0.0;
	float Mid = 0.0;
	float M2sub = 0.0;
	float seta = 0.0;
	
// 	if(AdcFinishFlag)	{
// 		/* 数据处理    */
// 		Normal((int16_t *)g_adc0Data[AdcBuffIndex], ADC_DATA_LEN);
// 		Normal((int16_t *)g_adc1Data[AdcBuffIndex], ADC_DATA_LEN);
// 		Normal((int16_t *)g_adc2Data[AdcBuffIndex], ADC_DATA_LEN);
// 		Normal((int16_t *)g_adc3Data[AdcBuffIndex], ADC_DATA_LEN);
// 		for(int i = 0; i < ADC_DATA_LEN; i ++)
// 		{
//         /* 上报匿名上位机  看原始数据波形 */
// 			ANO_DT_send_int16(g_adc0Data[AdcBuffIndex][i], g_adc1Data[AdcBuffIndex][i], g_adc3Data[AdcBuffIndex][i], g_adc2Data[AdcBuffIndex][i], 0, 0, 0,0);
// 		}
// 		LED_Ctrl(LEDALL,RVS);
// 		AdcFinishFlag = 0;
// }

	success_f = 1;  //默认是计算成功
	if(AdcFinishFlag)
	{
		z_change_flag = 1;
		/* 记录时间 */
//		nowTime = STM_GetNowUs(STM0);

		/* 数据处理    */
		Normal((int16_t *)g_adc0Data[AdcBuffIndex], ADC_DATA_LEN);
		Normal((int16_t *)g_adc1Data[AdcBuffIndex], ADC_DATA_LEN);
		Normal((int16_t *)g_adc2Data[AdcBuffIndex], ADC_DATA_LEN);
		Normal((int16_t *)g_adc3Data[AdcBuffIndex], ADC_DATA_LEN);

		prodatsfft((int16_t* )&acorIndex,(int16_t *)g_adc0Data[AdcBuffIndex],(int16_t *)g_adc1Data[AdcBuffIndex],(int16_t *)g_adc3Data[AdcBuffIndex],(int16_t *)g_adc2Data[AdcBuffIndex],ADC_DATA_LEN);

		// 计算距离
		S2 = (2048-acorIndex[0])*346*0.01;//单位cm
		S1 = (2048-acorIndex[1])*346*0.01;
		S_sub = (2048-acorIndex[2])*346*0.01;
		// S2 = (1024-acorIndex[0])*346*0.01;//单位cm
		// S1 = (1024-acorIndex[1])*346*0.01;
		// S_sub = (1024-acorIndex[2])*346*0.01;

		float res = S1-S2;

		if(res < 0){
			res = -res;
		}
		if(S1 <= 500 && S2 <= 500 && S_sub <= 500 && res <= 24){//res<=18  允许一定误差
			M2sum = S1*S1+S2*S2;
			Mid = M2sum/2 - 81;
			if(Mid >= 0){
				S = sqrtf(Mid);
				M2sub = S1*S1-S2*S2;
				M2sub = M2sub/(4*S*9);
				if(-1 <= M2sub && M2sub <= 1){
					seta = acosf(M2sub);//9为2、4麦克风之间距离的一半
					seta = (seta*180/pi);//处理为角度
				}
				else{
					success_f = 0;
				}
			}
			else{
				S = 0.0;
				seta = 0.0;
			}

			if(success_f){
				// 将指定目标定在灯的侧边
				if(0 < seta && seta < 90){
					seta += 180.0*obacle_length/(S*pi);
				}
				else{
					seta -= 180.0*obacle_length/(S*pi);
				}

				x = cosf(seta*pi/180)*1.0;//cosf和sinf处理的是弧度
				y = sinf(seta*pi/180)*1.0;
				z = (seta-90)*1.0;

				//判断灯在前还是在后
				if(S < S_sub){//灯在车尾
					direct_flag = -1;
				}
				else{
					direct_flag = 1;
				}

				if(S > 50 ){//距离大于50cm才会决策
					last_direct[length++] = direct_flag;
					if(length == 3){
						length = 0;
					}
					direct_flag = Average(last_direct,3);
					arrive_flag = 0;
				}
				else{// 否则清空状态
					for(int i = 0 ; i < 3 ; i++){
						last_direct[i] = direct_flag;
					}
					length = 0;
					arrive_flag = 1 ;  //准备接近目标灯
				}

				if(direct_flag == -1){
					y = -y;
					z = (90-seta)*1.0;
				}

				if(IfxCpu_acquireMutex(&mutevec)){
					vec.x = x;
					vec.y = y;
					vec.z = z;
					IfxCpu_releaseMutex(&mutevec);
				}
				// sprintf(txt,"S2:%f",S);
				// TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//字符串显示
				// sprintf(txt,"seta:%4f",seta);
				// TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//字符串显示
				// sprintf(txt,"S_:%4f",S_sub);
				// TFTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//字符串显示
			}
		}
		z_change_flag = 0;
		LED_Ctrl(LEDALL,RVS);
		AdcFinishFlag = 0;
	}
}

