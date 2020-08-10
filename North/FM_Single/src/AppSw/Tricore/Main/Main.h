/*!
  * @file     Main.h
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
  * @date     2020年6月11日
  */ 
#ifndef SRC_APPSW_TRICORE_MAIN_MAIN_H_
#define SRC_APPSW_TRICORE_MAIN_MAIN_H_


extern IfxCpu_mutexLock mutexCpu0InitIsOk;   /** CPU0 初始化完成标志位  */

extern IfxCpu_mutexLock mutevec; /*vec使用互斥信号量*/

/* 避障标志位 */
extern volatile uint8_t evadibleFlage;

extern struct vector3f_t vec;
extern struct vector3f_t offset;

extern float w_target;
extern float S;

extern uint32_t offset_flag;    // 避障标志位  1
extern uint32_t z_change_flag;  // z改变标志位  1 
extern uint32_t direct_flag;    //默认在前方 1-前方  -1-后方
extern uint32_t arrive_flag;    // 1 表示达到灭灯距离 0 
extern uint32_t on_the_light;   // 1 困在灯上

extern uint32_t dd;


extern float Cut_down_len ;
extern float obacle_length;   // 避障距离
extern float kp;
extern float V_speed;

extern float Pitch;

extern char txt[50];

#endif /* SRC_APPSW_TRICORE_MAIN_MAIN_H_ */
