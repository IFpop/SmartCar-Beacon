/******************************************************************************
* File:    isr.h
* Purpose: Define interrupt service routines referenced by the vector table.
* Note: Only "vectors.c" should include this header file.
******************************************************************************/

#ifndef __ISR_H
#define __ISR_H 

#include "include.h"

/* Example */
/*
#undef  VECTOR_036
#define VECTOR_036 RTC_Isr

// ISR(s) are defined in your project directory.
extern void RTC_Isr(void);
*/


#undef  VECTOR_038
#define VECTOR_038 PIT0_ISR
#undef  VECTOR_039
#define VECTOR_039 PIT1_ISR
#undef  VECTOR_040
#define VECTOR_040 KBI0_Isr
#undef  VECTOR_041
#define VECTOR_041 KBI1_Isr
#undef  VECTOR_028 
#define VECTOR_028 UART0_ISR                
#undef  VECTOR_029
#define VECTOR_029 UART1_ISR    
#undef  VECTOR_030 
#define VECTOR_030 UART2_buleteeth_ISR  


extern void PIT0_ISR(void);
extern void PIT1_ISR(void);
extern void KBI0_Isr(void);
extern void KBI1_Isr(void);
extern void UART0_ISR(void);
extern void UART1_ISR(void);
extern void UART2_buleteeth_ISR(void);
void servo_pwm_duty(uint32_t Duty);
#endif  //__ISR_H

/* End of "isr.h" */
