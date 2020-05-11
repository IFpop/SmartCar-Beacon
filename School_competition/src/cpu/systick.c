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
* @file systick.c
*
* @author Freescale
*
* @version 0.0.1
*
* @date Jun. 25, 2013
*
* @brief provide systick utility routines.
*
*******************************************************************************/

#include "include.h"

uint32_t cnt_start_value;
uint32_t cnt_end_value;
uint32_t overhead;

#if 0
  __IO uint32_t CTRL;                    /*!< Offset: 0x000 (R/W)  SysTick Control and Status Register */
  __IO uint32_t LOAD;                    /*!< Offset: 0x004 (R/W)  SysTick Reload Value Register       */
  __IO uint32_t VAL;                     /*!< Offset: 0x008 (R/W)  SysTick Current Value Register      */
  __I  uint32_t CALIB;                   /*!< Offset: 0x00C (R/ )  SysTick Calibration Register        */
#endif
void systick_init(void)
{       SysTick->VAL = 0x0;	/* clear current timer value */
    SysTick->LOAD = 0x00FFFFFF;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;   
}

void systick_disable(void)
{
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void cal_systick_read_overhead(void)
{
  	uint32_t cnt_start_value;
    uint32_t cnt_end_value;
	
	cnt_start_value = SysTick->VAL;
  
    cnt_end_value = SysTick->VAL;
	
	overhead = cnt_start_value - cnt_end_value;
	
#ifdef DEBUG_PRINT
	//printf("systick start value: 0x%x\n\r", (unsigned int)cnt_start_value);
	//printf("systick end value: 0x%x\n\r", (unsigned int) cnt_end_value);
	//printf("systick current value read overhead: 0x%x\n\r", (unsigned int)overhead);
#endif

}
//北京龙邱智能科技有限公司修改添加如下程序

void SysTick_delay(uint32_t cmd)
{
   SysTick->CTRL = 0x00;//先关了 systick ,清标志位
   SysTick->LOAD =cmd;
   SysTick->VAL  =0;
   SysTick->CTRL = SysTick_CTRL_ENABLE_Msk
                   |SysTick_CTRL_CLKSOURCE_Msk;
   while( !(SysTick->CTRL&SysTick_CTRL_COUNTFLAG_Msk) );
}

void delay_us(uint32_t cmd)//精准延时1us
{
  cmd=(uint32_t)(cmd*BUS_CLK_MHZ);//40M总线时钟
  SysTick_delay(cmd);
}

void DELAY_us(uint32_t cmd)//不精准延时1us
{
  while(cmd--)
  {
    delay_us(1);
  }

}
