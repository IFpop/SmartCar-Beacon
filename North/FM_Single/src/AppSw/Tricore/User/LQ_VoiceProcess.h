/*!
  * @file     LQ_SmartCar.h
  *
  * @brief    
  *
  * @company  �����������ܿƼ�
  *
  * @author   LQ-005
  *
  * @note     Tab�� 4���ո�
  *
  * @version  V1.0
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2020��4��27��
  */ 
#ifndef SRC_APPSW_TRICORE_MAIN_LQ_SMARTCAR_H_
#define SRC_APPSW_TRICORE_MAIN_LQ_SMARTCAR_H_

#define ADC_DATA_LEN    2048
// #define ADC_DATA_LEN    1024

#define ChangeState 10  // ����״̬�ı�ֵ
#define obacle_length 28.5   // ���Ͼ���

void VoiceInit(void);

void VoiceProcess(void);

void VoiceGetSample(void);

#endif /* SRC_APPSW_TRICORE_MAIN_LQ_SMARTCAR_H_ */
