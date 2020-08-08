/*!
  * @file     LQ_SmartCar.h
  *
  * @brief    
  *
  * @company  北京龙邱智能科技
  *
  * @author   LQ-005
  *
  * @note     Tab键 4个空格
  *
  * @version  V1.0
  *
  * @par URL  http://shop36265907.taobao.com
  *           http://www.lqist.cn
  *
  * @date     2020年4月27日
  */ 
#ifndef SRC_APPSW_TRICORE_MAIN_LQ_SMARTCAR_H_
#define SRC_APPSW_TRICORE_MAIN_LQ_SMARTCAR_H_

#define ADC_DATA_LEN    2048
// #define ADC_DATA_LEN    1024

#define ChangeState 10  // 设置状态改变值
#define obacle_length 28.5   // 避障距离

void VoiceInit(void);

void VoiceProcess(void);

void VoiceGetSample(void);

#endif /* SRC_APPSW_TRICORE_MAIN_LQ_SMARTCAR_H_ */
