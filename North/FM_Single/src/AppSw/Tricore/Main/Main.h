/*!
  * @file     Main.h
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
  * @date     2020��6��11��
  */ 
#ifndef SRC_APPSW_TRICORE_MAIN_MAIN_H_
#define SRC_APPSW_TRICORE_MAIN_MAIN_H_


extern IfxCpu_mutexLock mutexCpu0InitIsOk;   /** CPU0 ��ʼ����ɱ�־λ  */

extern IfxCpu_mutexLock mutevec; /*vecʹ�û����ź���*/

/* ���ϱ�־λ */
extern volatile uint8_t evadibleFlage;

extern struct vector3f_t vec;
extern struct vector3f_t offset;

extern float w_target;
extern float S;

extern uint32_t offset_flag;    // ���ϱ�־λ  1
extern uint32_t z_change_flag;  // z�ı��־λ  1 
extern uint32_t direct_flag;    //Ĭ����ǰ�� 1-ǰ��  -1-��
extern uint32_t arrive_flag;    // 1 ��ʾ�ﵽ��ƾ��� 0 
extern uint32_t on_the_light;   // 1 ���ڵ���

extern uint32_t dd;


extern float Cut_down_len ;
extern float obacle_length;   // ���Ͼ���
extern float kp;
extern float V_speed;

extern float Pitch;

extern char txt[50];

#endif /* SRC_APPSW_TRICORE_MAIN_MAIN_H_ */
