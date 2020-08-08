#include "include.h"

// ��ǵ�ǰ�����Ƿ���Ч
float success_f = 1;

// ������������м����
float x = 0.0;
float y = 0.0;
float z = 0.0;

// �������  ͶƱ ���ֵ
static int32_t last_direct[3] = {0,0,0};
static uint32_t length = 0;

/* �����ط�ֵ�±� */
int16_t acorIndex[3];
/* ��¼ʱ�� */
uint32_t nowTime = 0;
/*
 * adc�ɼ���ɱ�־λ
 */
volatile uint8  AdcFinishFlag = 0;
/*
 * adc˫buff������  ������ɵ��������
 */
volatile uint8  AdcBuffIndex = 0;
/*
 * adc�����±�
 */
volatile uint32 adcCount = 0;

/*
 * ADC����   adc0 1 2 3 �ɼ���˷��ź�
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
  * @brief    �ű�һЩ��ʼ������
  *
  */
void VoiceInit(void)
{
	// ADC_InitConfig(MIC1, 1000000); //��ʼ�� 1����˷�
	ADC_InitConfig(MIC2, 1000000); //��ʼ�� 2����˷�
	ADC_InitConfig(MIC3, 1000000); //��ʼ�� 3����˷�
	ADC_InitConfig(MIC4, 1000000); //��ʼ�� 4����˷�
	ADC_InitConfig(RF, 1000000); //��ʼ�� ��Ƶģ��

	CCU6_InitConfig(CCU60, CCU6_Channel0, 100);  //100us����һ���ж�  �ж��вɼ�adc����
}

/*!
  * @brief    ccu6 �ɼ��жϷ�����   �����źŲɼ�
  */
void VoiceGetSample(void)
{
	static uint8 adcIndex = 0;

	if(adcCount >= ADC_DATA_LEN)
	{
		adcCount = 0;
		AdcFinishFlag = 1;

		/* �л�buff������ */
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
  * @brief    ��һ������
  *
  * @param    x   �� Ҫ��������
  * @param    len �� Ҫ�������ݳ���
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

// ��ָ������ƽ��ֵ
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
  * @brief    ��˷����ݴ���  ��ȡ�Ƕ���Ϣ
  * @return   ������λ��
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
// 		/* ���ݴ���    */
// 		Normal((int16_t *)g_adc0Data[AdcBuffIndex], ADC_DATA_LEN);
// 		Normal((int16_t *)g_adc1Data[AdcBuffIndex], ADC_DATA_LEN);
// 		Normal((int16_t *)g_adc2Data[AdcBuffIndex], ADC_DATA_LEN);
// 		Normal((int16_t *)g_adc3Data[AdcBuffIndex], ADC_DATA_LEN);
// 		for(int i = 0; i < ADC_DATA_LEN; i ++)
// 		{
//         /* �ϱ�������λ��  ��ԭʼ���ݲ��� */
// 			ANO_DT_send_int16(g_adc0Data[AdcBuffIndex][i], g_adc1Data[AdcBuffIndex][i], g_adc3Data[AdcBuffIndex][i], g_adc2Data[AdcBuffIndex][i], 0, 0, 0,0);
// 		}
// 		LED_Ctrl(LEDALL,RVS);
// 		AdcFinishFlag = 0;
// }

	success_f = 1;  //Ĭ���Ǽ���ɹ�
	if(AdcFinishFlag)
	{
		z_change_flag = 1;
		/* ��¼ʱ�� */
//		nowTime = STM_GetNowUs(STM0);

		/* ���ݴ���    */
		Normal((int16_t *)g_adc0Data[AdcBuffIndex], ADC_DATA_LEN);
		Normal((int16_t *)g_adc1Data[AdcBuffIndex], ADC_DATA_LEN);
		Normal((int16_t *)g_adc2Data[AdcBuffIndex], ADC_DATA_LEN);
		Normal((int16_t *)g_adc3Data[AdcBuffIndex], ADC_DATA_LEN);

		prodatsfft((int16_t* )&acorIndex,(int16_t *)g_adc0Data[AdcBuffIndex],(int16_t *)g_adc1Data[AdcBuffIndex],(int16_t *)g_adc3Data[AdcBuffIndex],(int16_t *)g_adc2Data[AdcBuffIndex],ADC_DATA_LEN);

		// �������
		S2 = (2048-acorIndex[0])*346*0.01;//��λcm
		S1 = (2048-acorIndex[1])*346*0.01;
		S_sub = (2048-acorIndex[2])*346*0.01;
		// S2 = (1024-acorIndex[0])*346*0.01;//��λcm
		// S1 = (1024-acorIndex[1])*346*0.01;
		// S_sub = (1024-acorIndex[2])*346*0.01;

		float res = S1-S2;

		if(res < 0){
			res = -res;
		}
		if(S1 <= 500 && S2 <= 500 && S_sub <= 500 && res <= 24){//res<=18  ����һ�����
			M2sum = S1*S1+S2*S2;
			Mid = M2sum/2 - 81;
			if(Mid >= 0){
				S = sqrtf(Mid);
				M2sub = S1*S1-S2*S2;
				M2sub = M2sub/(4*S*9);
				if(-1 <= M2sub && M2sub <= 1){
					seta = acosf(M2sub);//9Ϊ2��4��˷�֮������һ��
					seta = (seta*180/pi);//����Ϊ�Ƕ�
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
				// ��ָ��Ŀ�궨�ڵƵĲ��
				if(0 < seta && seta < 90){
					seta += 180.0*obacle_length/(S*pi);
				}
				else{
					seta -= 180.0*obacle_length/(S*pi);
				}

				x = cosf(seta*pi/180)*1.0;//cosf��sinf������ǻ���
				y = sinf(seta*pi/180)*1.0;
				z = (seta-90)*1.0;

				//�жϵ���ǰ�����ں�
				if(S < S_sub){//���ڳ�β
					direct_flag = -1;
				}
				else{
					direct_flag = 1;
				}

				if(S > 50 ){//�������50cm�Ż����
					last_direct[length++] = direct_flag;
					if(length == 3){
						length = 0;
					}
					direct_flag = Average(last_direct,3);
					arrive_flag = 0;
				}
				else{// �������״̬
					for(int i = 0 ; i < 3 ; i++){
						last_direct[i] = direct_flag;
					}
					length = 0;
					arrive_flag = 1 ;  //׼���ӽ�Ŀ���
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
				// TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
				// sprintf(txt,"seta:%4f",seta);
				// TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
				// sprintf(txt,"S_:%4f",S_sub);
				// TFTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			}
		}
		z_change_flag = 0;
		LED_Ctrl(LEDALL,RVS);
		AdcFinishFlag = 0;
	}
}

