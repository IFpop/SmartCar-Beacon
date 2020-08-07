/*!
  * @file     LQ_GPSR.c
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

#include <IfxInt_reg.h>
#include <IfxCpu_Irq.h>
#include <IfxSrc_reg.h>
#include <LQ_GPSR.h>
#include <Platform_Types.h>

/** cpu����ж����ȼ� */
const uint8 CpuSoftIrqPriority[8] = {CPU0_SOFT_IRQ0_PRIORITY, CPU0_SOFT_IRQ1_PRIORITY, CPU0_SOFT_IRQ2_PRIORITY, CPU0_SOFT_IRQ3_PRIORITY,
		CPU1_SOFT_IRQ0_PRIORITY,CPU1_SOFT_IRQ1_PRIORITY, CPU1_SOFT_IRQ2_PRIORITY,CPU1_SOFT_IRQ3_PRIORITY};





/**
  * @brief    CPU0_SOFT_IRQ0Handler�жϷ�����
  * @note     cpu0 ����ж�0�жϷ�����
  */
void CPU0_SOFT_IRQ0Handler(void)
{
	SRC_GPSR00.B.SRR = 0;
	/* �û����� */
}

void CPU0_SOFT_IRQ1Handler(void)
{
	SRC_GPSR01.B.SRR = 0;
	/* �û����� */
}

void CPU0_SOFT_IRQ2Handler(void)
{
	SRC_GPSR02.B.SRR = 0;
	/* �û����� */
}

void CPU0_SOFT_IRQ3Handler(void)
{
	SRC_GPSR03.B.SRR = 0;
	/* �û����� */
}

void CPU1_SOFT_IRQ0Handler(void)
{
	SRC_GPSR10.B.SRR = 0;
	/* �û����� */
}

void CPU1_SOFT_IRQ1Handler(void)
{
	SRC_GPSR11.B.SRR = 0;
	/* �û����� */
}

void CPU1_SOFT_IRQ2Handler(void)
{
	SRC_GPSR12.B.SRR = 0;
	/* �û����� */
}

void CPU1_SOFT_IRQ3Handler(void)
{
	SRC_GPSR13.B.SRR = 0;
	/* �û����� */
}



/* cpu���ж� */
IFX_INTERRUPT(CPU0_SOFT_IRQ0Handler, 0, CPU0_SOFT_IRQ0_PRIORITY);
IFX_INTERRUPT(CPU0_SOFT_IRQ1Handler, 0, CPU0_SOFT_IRQ1_PRIORITY);
IFX_INTERRUPT(CPU0_SOFT_IRQ2Handler, 0, CPU0_SOFT_IRQ2_PRIORITY);
IFX_INTERRUPT(CPU0_SOFT_IRQ3Handler, 0, CPU0_SOFT_IRQ3_PRIORITY);
IFX_INTERRUPT(CPU1_SOFT_IRQ0Handler, 1, CPU1_SOFT_IRQ0_PRIORITY);
IFX_INTERRUPT(CPU1_SOFT_IRQ1Handler, 1, CPU1_SOFT_IRQ1_PRIORITY);
IFX_INTERRUPT(CPU1_SOFT_IRQ2Handler, 1, CPU1_SOFT_IRQ2_PRIORITY);
IFX_INTERRUPT(CPU1_SOFT_IRQ3Handler, 1, CPU1_SOFT_IRQ3_PRIORITY);


/** cpu���жϷ�������ַ */
const void *CpuSoftIrqFuncPointer[8] = {&CPU0_SOFT_IRQ0Handler, &CPU0_SOFT_IRQ1Handler, &CPU0_SOFT_IRQ2Handler,
									&CPU0_SOFT_IRQ3Handler, &CPU1_SOFT_IRQ0Handler, &CPU1_SOFT_IRQ1Handler,
									&CPU1_SOFT_IRQ2Handler, &CPU1_SOFT_IRQ3Handler};


/*************************************************************************
*  �������ƣ�GPSR_InitConfig(IfxSrc_Tos cpu, uint8 softIrq)
*  ����˵��������еĳ�ʼ��
*  ����˵����cpu     �� IfxSrc_Tos_cpu0   IfxSrc_Tos_cpu1
*  ����˵����softIrq �� ÿ��CPU��4������ж�, irq���
*  �������أ���
*  �޸�ʱ�䣺2020��5��6��
*  ��    ע��
*************************************************************************/
void GPSR_InitConfig(IfxSrc_Tos cpu, SOFT_IRQ index)
{
	/* �ر��ж� */
	boolean        interruptState = IfxCpu_disableInterrupts();

	uint8 temp = cpu * 4 + index;
	SRC_GPSR00.B.SRR = 0;
	SRC_GPSR01.B.SRR = 0;
	SRC_GPSR02.B.SRR = 0;
	SRC_GPSR03.B.SRR = 0;

	SRC_GPSR10.B.SRR = 0;
	SRC_GPSR11.B.SRR = 0;
	SRC_GPSR12.B.SRR = 0;
	SRC_GPSR13.B.SRR = 0;

	/* �����ж� */
	volatile Ifx_SRC_SRCR *src = &MODULE_SRC.GPSR.GPSR[(int)cpu].SR0;
	IfxSrc_init(src, (int)cpu, (uint32)CpuSoftIrqPriority[temp]);
	IfxSrc_enable(src);

	src = &MODULE_SRC.GPSR.GPSR[(int)cpu].SR1;
	IfxSrc_init(src, (int)cpu, (uint32)CpuSoftIrqPriority[temp]);
	IfxSrc_enable(src);

	src = &MODULE_SRC.GPSR.GPSR[(int)cpu].SR2;
	IfxSrc_init(src, (int)cpu, (uint32)CpuSoftIrqPriority[temp]);
	IfxSrc_enable(src);

	src = &MODULE_SRC.GPSR.GPSR[(int)cpu].SR3;
	IfxSrc_init(src, (int)cpu, (uint32)CpuSoftIrqPriority[temp]);
	IfxSrc_enable(src);

	/* ��װ�жϷ����� */
	IfxCpu_Irq_installInterruptHandler((void*)CpuSoftIrqFuncPointer[temp],     (uint32)CpuSoftIrqPriority[temp]);

	/* �����ж� */
	IfxCpu_restoreInterrupts(interruptState);
}

/*************************************************************************
*  �������ƣ�CPSR_Trig(IfxSrc_Tos cpu, uint8 softIrq)
*  ����˵������������ж�
*  ����˵����cpu     �� IfxSrc_Tos_cpu0   IfxSrc_Tos_cpu1
*  ����˵����softIrq �� ÿ��CPU��4������ж�, irq���
*  �������أ���
*  �޸�ʱ�䣺2020��5��6��
*  ��    ע��
*************************************************************************/
void CPSR_Trig(IfxSrc_Tos cpu, SOFT_IRQ index)
{
	if(cpu == IfxSrc_Tos_cpu0)
	{
		INT_SRB0.U = 1 << (uint8)index;
	}
	else
	{
		INT_SRB1.U = 1 << (uint8)index;
	}
}










