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

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "..\Driver\include.h"//����ģ���ͷ�ļ�



/*************************************************************************
*  �������ƣ�void TestADC(void)
*  ����˵����ADC�ɼ�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
void Test_ADC(void)
{
	unsigned long i;
    char txt[16];

    ADC_InitConfig(ADC0, 80000); //��ʼ��
    ADC_InitConfig(ADC1, 80000);
    ADC_InitConfig(ADC2, 80000);
    ADC_InitConfig(ADC3, 80000);
    ADC_InitConfig(ADC4, 80000);
    ADC_InitConfig(ADC5, 80000);
    ADC_InitConfig(ADC6, 80000);
    ADC_InitConfig(ADC7, 80000);

    OLED_Init();
    OLED_P6x8Str(0,0,"adc test");
    while(1)
    {
    	unsigned long nowTime = STM_GetNowUs(STM0);
    	for( i = 0; i < 10000; i++)
    	{
    		ADC_Read(ADC0);
    	}
    	unsigned long time = STM_GetNowUs(STM0) - nowTime;
    	sprintf(txt, "time : %d", time);
    	OLED_P6x8Str(0,3,txt);

    }

}
/*************************************************************************
*  �������ƣ�void Test_Beacon7mic(void)
*  ����˵�����ɼ�����6+1��˷�����
*  ����˵������
*  �������أ���
*  �޸�ʱ�䣺2020��3��10��
*  ��    ע��
*************************************************************************/
void Test_ADC_7mic(void)
{
	unsigned char chnIx;
    char txt[16];
    unsigned int MICVmin[8];

    ADC_InitConfig(ADC0, 80000); //��ʼ��
    ADC_InitConfig(ADC1, 80000); //��ʼ��
    ADC_InitConfig(ADC2, 80000); //��ʼ��
    ADC_InitConfig(ADC3, 80000); //��ʼ��
    ADC_InitConfig(ADC4, 80000); //��ʼ��
    ADC_InitConfig(ADC5, 80000); //��ʼ��
    ADC_InitConfig(ADC6, 80000); //��ʼ��
    ADC_InitConfig(ADC7, 80000); //��ʼ��
    delayms(500);                //��ʱ�ȴ�
	UART_PutStr(UART0,"\n-------------------------------------------------\n");//�ֽ���
	for(chnIx=0; chnIx<8; ++chnIx)
	{
		MICVmin[chnIx]=ADC_Read(chnIx);
		//ת�����Ϊ�ַ��������ڷ��ͻ�����Ļ��ʾ��AN0--AN7
		sprintf(txt,"[%d]:%05d  ",chnIx,MICVmin[chnIx]);
		//���ڷ��͵���λ��
		UART_PutStr(UART0,txt);//AN0--AN7ʮ���������������λ��
	}
	delayms(500);                //��ʱ�ȴ�
	UART_PutStr(UART0,"\n-------------------------------------------------\n");//�ֽ���
	while(1)
	{
		//���ת�����
		for(chnIx=0; chnIx<8; ++chnIx)
		{
			//ת�����Ϊ�ַ��������ڷ��ͻ�����Ļ��ʾ��AN0--AN7
			sprintf(txt,"[%d]:%05d  ",chnIx,ADC_Read(chnIx)-MICVmin[chnIx]);

			//���ڷ��͵���λ��
			if(chnIx==0) UART_PutStr(UART0,"\n");//������һ��
			UART_PutStr(UART0,txt);//AN0--AN7ʮ���������������λ��
		}
    	LED_Ctrl(LED0,RVS);        //��ƽ��ת,LED��˸
		delayms(500);              //��ʱ�ȴ�
	}
}
//
