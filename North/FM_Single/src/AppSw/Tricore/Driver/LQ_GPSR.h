/*!
  * @file     LQ_GPSR.h
  *
  * @brief    ÿ��CPU��4������ж�
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
  * @date     2020��5��6��
  */ 
#ifndef SRC_APPSW_TRICORE_DRIVER_LQ_GPSR_H_
#define SRC_APPSW_TRICORE_DRIVER_LQ_GPSR_H_

#include "Tricore/_Impl/IfxSrc_cfg.h"

/***********************************************************************************************/
/***********************************************************************************************/
/*****************    CPU�ж����ȼ� �� ָ���ں����� �û����������޸�*******************************/
/***********************************************************************************************/
/***********************************************************************************************/

/** CPU0����жϷ��������ȼ�   ��Χ��1-255   ����Խ�� ���ȼ�Խ��  ע�����ȼ���Ҫ�ظ� */
#define  CPU0_SOFT_IRQ0_PRIORITY    240

/** CPU0����жϷ��������ȼ�   ��Χ��1-255   ����Խ�� ���ȼ�Խ��  ע�����ȼ���Ҫ�ظ� */
#define  CPU0_SOFT_IRQ1_PRIORITY    241

/** CPU0����жϷ��������ȼ�   ��Χ��1-255   ����Խ�� ���ȼ�Խ��  ע�����ȼ���Ҫ�ظ� */
#define  CPU0_SOFT_IRQ2_PRIORITY    242

/** CPU0����жϷ��������ȼ�   ��Χ��1-255   ����Խ�� ���ȼ�Խ��  ע�����ȼ���Ҫ�ظ� */
#define  CPU0_SOFT_IRQ3_PRIORITY    243


/** CPU1����жϷ��������ȼ�   ��Χ��1-255   ����Խ�� ���ȼ�Խ��  ע�����ȼ���Ҫ�ظ� */
#define  CPU1_SOFT_IRQ0_PRIORITY    244

/** CPU1����жϷ��������ȼ�   ��Χ��1-255   ����Խ�� ���ȼ�Խ��  ע�����ȼ���Ҫ�ظ� */
#define  CPU1_SOFT_IRQ1_PRIORITY    245

/** CPU1����жϷ��������ȼ�   ��Χ��1-255   ����Խ�� ���ȼ�Խ��  ע�����ȼ���Ҫ�ظ� */
#define  CPU1_SOFT_IRQ2_PRIORITY    246

/** CPU1����жϷ��������ȼ�   ��Χ��1-255   ����Խ�� ���ȼ�Խ��  ע�����ȼ���Ҫ�ظ� */
#define  CPU1_SOFT_IRQ3_PRIORITY    247



/**
 * ����е����ö��
 */
typedef enum
{
	SoftIRQ0,
	SoftIRQ1,
	SoftIRQ2,
	SoftIRQ3
}SOFT_IRQ;

void GPSR_InitConfig(IfxSrc_Tos cpu, SOFT_IRQ index);
void CPSR_Trig(IfxSrc_Tos cpu, SOFT_IRQ index);

#endif /* SRC_APPSW_TRICORE_DRIVER_LQ_GPSR_H_ */
