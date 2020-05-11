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

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/

#ifndef _LQ_GTMPWM_H_
#define _LQ_GTMPWM_H_

// ATOM 时钟 100MHz
#define ATOM_PWM_CLK  100000000
// ATOM 最大占空比 可自行修改
#define ATOM_PWM_MAX  10000.0f

//////////////GTM_ATOM_PWM///////////////////////////////////////////////////////////////////////////////////
#define ISR_PRIORITY_ATOM  20                               //中断优先级


////////////////ATOM_PWM//////////////////////
void ATOM_PWM_InitConfig(IfxGtm_Atom_ToutMap pin, uint32_t duty, uint32_t pwmFreq_Hz);
void ATOM_PWM_SetDuty(IfxGtm_Atom_ToutMap pin, uint32_t duty, uint32_t pwmFreq_Hz);



////////////////TOM_TIM//////////////////////
void TOM_PWM_InitConfig(IfxGtm_Tom_ToutMap pin, uint32_t duty, uint32_t pwmFreq_Hz);
void TOM_PWM_SetDuty(IfxGtm_Tom_ToutMap pin, uint32_t duty, uint32_t pwmFreq_Hz);

void GTM_TIM_Init(IfxGtm_Tim_TinMap pin);
void Get_GTM_TIM(IfxGtm_Tim_TinMap pin);


#endif /* 0_APPSW_TRICORE_APP_LQ_GTM6PWM_H_ */
