/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
***************************************************************************//*!
*
* @file arm_cm0.c
*
* @author Freescale
*
* @version 0.0.1
*
* @date Jun. 25, 2013
*
* @brief provide generic high-level routines for ARM Cortex M0/M0+ processors. 
*
*******************************************************************************/

#include "common.h"

/***********************************************************************/
/*
 * Configures the ARM system control register for STOP (deep sleep) mode
 * and then executes the WFI instruction to enter the mode.
 *
 * Parameters:
 * none
 *
 * Note: Might want to change this later to allow for passing in a parameter
 *       to optionally set the sleep on exit bit.
 */

void stop (void)
{
	/* Set the SLEEPDEEP bit to enable deep sleep mode (STOP) */
	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;	

	/* WFI instruction will start entry into STOP mode */
#ifndef KEIL
        // If not using KEIL's uVision use the standard assembly command
	asm("WFI");
#else
        // If using KEIL's uVision, use the CMSIS intrinsic
	__wfi();
#endif
}
/***********************************************************************/
/*
 * Configures the ARM system control register for WAIT (sleep) mode
 * and then executes the WFI instruction to enter the mode.
 *
 * Parameters:
 * none
 *
 * Note: Might want to change this later to allow for passing in a parameter
 *       to optionally set the sleep on exit bit.
 */

void wait (void)
{
	/* Clear the SLEEPDEEP bit to make sure we go into WAIT (sleep) mode instead
	 * of deep sleep.
	 */
	SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;	

	/* WFI instruction will start entry into WAIT mode */
#ifndef KEIL
        // If not using KEIL's uVision use the standard assembly command
	asm("WFI");
#else
        // If using KEIL's uVision, use the CMSIS intrinsic
    __wfi();
#endif
}
/***********************************************************************/
/*
 * Change the value of the vector table offset register to the specified value.
 *
 * Parameters:
 * vtor     new value to write to the VTOR
 */

void write_vtor (int vtor)
{
        /* Write the VTOR with the new value */
        SCB->VTOR = vtor;	
}

/***********************************************************************/

