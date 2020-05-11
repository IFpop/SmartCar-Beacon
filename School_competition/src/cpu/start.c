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
* @file start.c
*
* @author Freescale
*
* @version 0.0.1
*
* @date Jun. 25, 2013
*
* @brief provide high-level startup routines for KExx.
*
*******************************************************************************/

#include "start.h"
#include "common.h"
#include "wdog.h"
#include "sysinit.h"

void start(void);
void SystemInit( void );
/********************************************************************/
/*!
* \brief   Kinetis Start
* \return  None
*
* This function calls all of the needed starup routines and then 
* branches to the main process.
*/
void start(void)
{ 
  /* Disable the watchdog timer but enable update */
  WDOG_DisableWDOGEnableUpdate();    
  //禁用看门狗定时器，看门狗的含义可以自己百度去理解
  /* Copy any vector or data sections that need to be in RAM */
  common_startup();
  //复制需要在RAM中使用的中断向量以及相应的数据
  sysinit();
  //进行系统的初始化
  /* Jump to main process */
  main();
  /* No actions to perform after this so wait forever */
  while(1);
}
/********************************************************************/
/*!
* \brief   Kinetis Identify
* \return  None
*
* This is primarly a reporting function that displays information
* about the specific CPU to the default terminal including:
* - Kinetis family
* - package
* - die revision
* - P-flash size
* - Ram size
*/
void cpu_identify (void)
{
  
}
/********************************************************************/
/*!
* \brief   flash Identify
* \return  None
*
* This is primarly a reporting function that displays information
* about the specific flash parameters and flash version ID for 
* the current device. These parameters are obtained using a special
* flash command call "read resource." The first four bytes returned
* are the flash parameter revision, and the second four bytes are
* the flash version ID.
*/
void flash_identify (void)
{
  /* Get the flash parameter version */
}
/********************************************************************/
/********************************************************************/
/*!
* \brief   flash SystemInit
* \return  None
*
* this is a system initialization function which dediu16Cated in Keil 
* others complier don't use it.
* it is similar to start function
*/
void SystemInit( void )
{
#if !defined(ENABLE_WDOG)   
  /* Disable the watchdog timer */
  WDOG_Disable();
#else
  /* Disable the watchdog timer but enable update */
  WDOG_DisableWDOGEnableUpdate();    
#endif
}



