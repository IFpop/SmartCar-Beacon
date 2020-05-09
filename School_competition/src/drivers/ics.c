/*****************************************************************************
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
* @file ics.c
*
* @author Freescale
*
* @version 0.0.1
*
* @date Jun. 25, 2013
*
* @brief providing APIs for configuring internal clock sources (ICS). 
*
*******************************************************************************
*
* provide APIs for configuring internal clock sources (ICS)
******************************************************************************/
#include "common.h"
#include "ics.h"

/******************************************************************************
* Global variables
******************************************************************************/

/******************************************************************************
* Constants and macros
******************************************************************************/

/* default value of ICS and OSC registers after reset */
#define ICS_C1_DEFAULT  0x04
#define ICS_C2_DEFAULT  0x20
#define ICS_C3_DEFAULT  0x54
#define ICS_C4_DEFAULT  0x00
#define ICS_S_DEFAULT   0x50
#define OSC_CR_DEFAULT  0


/******************************************************************************
* Local types
******************************************************************************/

/******************************************************************************
* Local function prototypes
******************************************************************************/


/******************************************************************************
* Local variables
******************************************************************************/

/******************************************************************************
* Local functions
******************************************************************************/

/******************************************************************************
* Global functions
******************************************************************************/


/*****************************************************************************//*!
   *
   * @brief change clock from FEI mode to FEE mode and divide clock by 2.
   *        
   * @param[in] pConfig pointer to the ICS configuration structure
   *
   * @return none
   *
   * @Pass/ Fail criteria: none
   *****************************************************************************/
void FEI_to_FEE(ICS_ConfigType *pConfig)
{
	/* enable OSC
	 * 
	 */
	OSC_Init(&pConfig->oscConfig);
	
	/* divide down external clock frequency 
	 * to be within 31.25K to 39.0625K
	 */
        ICS_SetClkDivider(pConfig->u32ClkFreq);

	/* change FLL reference clock to external clock */
	ICS->C1 =  ICS->C1 & ~ICS_C1_IREFS_MASK;
         
	
	/* wait for the reference clock to be changed to external */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
};        
#endif        
	while(ICS->S & ICS_S_IREFST_MASK);
	
	/* wait for FLL to lock */
	while(!(ICS->S & ICS_S_LOCK_MASK));
		
	/* now FLL output clock is FLL reference clock* FLL multiplication factor. 
	 * See Reference Manual for multiplication factor.
	 */
#if defined(CPU_KEA8)
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
	/* now system/bus clock is the target frequency
	 * 
	 */
	/* clear Loss of lock sticky bit */
	ICS->S |= ICS_S_LOLS_MASK;	
}

/*****************************************************************************//*!
   *
   * @brief change clock from FEI mode to FBI mode and divide clock by 2.
   *        
   * @param  pConfig    pointer to configuration strucure. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FEI_to_FBI(ICS_ConfigType *pConfig)
{
	/* change clock source to internal reference clock */
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(1);   
	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 
	/* wait for the reference clock to be changed  */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif        
	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=1);
			
	/* now internal reference clock is the system clock
	 * 
	 */
#if defined(BUS_CLK_EQU_CORE_DIVIDE_BY_2)||defined(CPU_KEA8)        
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}

#else
	ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK));     
#endif        
	/* clear Loss of lock sticky bit */
	ICS->S |= ICS_S_LOLS_MASK;	
}

/*****************************************************************************//*!
   *
   * @brief change clock from FEI mode to FBE mode and divide clock by 2.
   *        
   * @param  pConfig    pointer to configuration strucure. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FEI_to_FBE(ICS_ConfigType *pConfig)
{
	OSC_Init(&pConfig->oscConfig); /* enable OSC */

	/* change clock source to external reference clock */
    ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(2);   
	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 
        
	/* wait for the reference clock to be changed  */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif        

	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=2);
        while(ICS->S & ICS_S_IREFST_MASK);
			
	/* now external  clock is the system clock
	 * 
	 */
#if defined(CPU_KEA8)
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
	/* now system/bus clock is external clock
	 * 
	 */
	/* clear Loss of lock sticky bit */
	ICS->S |= ICS_S_LOLS_MASK;	
}

/*****************************************************************************//*!
   *
   * @brief change clock from FEI mode to FBE mode with external clock/oscillator 
   * and divide clock by 2.
   *        
   * @param  pConfig    pointer to configuration strcuture. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FEI_to_FBE_OSC(ICS_ConfigType *pConfig)
{
    
	OSC_Init(&pConfig->oscConfig); /* enable OSC */

	/* change RDIV  reference divider to divide reference clock to be with FLL input spec
	 * 
	 */
    ICS_SetClkDivider(pConfig->u32ClkFreq);
    
	/* assume external oscillator is 8Mhz or 4MHz
	 * 
	 */
	/* change clock source to external reference clock */
        ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(2);   
	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 
        
	/* wait for the reference clock to be changed  */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=2);
        while(ICS->S & ICS_S_IREFST_MASK);
			
	/* now external  clock is the system clock
	 * 
	 */
#if defined(CPU_KEA8)
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
	/* now system/bus clock is external clock
	 * 
	 */
	/* clear Loss of lock sticky bit */
	ICS->S |= ICS_S_LOLS_MASK;	
}

/*****************************************************************************//*!
   *
   * @brief change clock from FEI mode to FEE mode with external clock/oscillator 
   * and divide clock by 2.
   *        
   * @param  pConfig     pointer to configuration. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FEI_to_FEE_OSC(ICS_ConfigType *pConfig)
{
        /* enable OSC */
	OSC_Init(&pConfig->oscConfig); 

	/* change RDIV  reference divider to divide reference clock to be with FLL input spec
	 * 
	 */
        ICS_SetClkDivider(pConfig->u32ClkFreq);

	/* change FLL reference clock to external clock */
        ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);
	
	/* wait for the reference clock to be changed to external */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	//while(ICS->S & ICS_S_IREFST_MASK);
	
	/* wait for FLL to lock */
	//while(!(ICS->S & ICS_S_LOCK_MASK));
#if defined(CPU_KEA8)		
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
	/* now system/bus clock is the target frequency
	 * 
	 */
	/* clear Loss of lock sticky bit */
	ICS->S |= ICS_S_LOLS_MASK;	
}


/*****************************************************************************//*!
   *
   * @brief change clock from FEE mode to FEI mode.
   *        
   * @param  pConfig     pointer to configuration. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FEE_to_FEI(ICS_ConfigType *pConfig)
{
	/* select internal reference for FLL */ 
    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
	
	/* wait for the reference clock to be changed */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(!(ICS->S & ICS_S_IREFST_MASK));
	
	/* wait for FLL to lock */
	while(!(ICS->S & ICS_S_LOCK_MASK));

	/* clear Loss of lock sticky bit */
	ICS->S |= ICS_S_LOLS_MASK;

	/* now FLL output clock is target frequency
	 * 
	 */
#if defined(CPU_KEA8)
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
	/* now system/bus clock is around 16MHz
	 * 
	 */
      OSC_Disable();            /* disable OSC */
}

/*****************************************************************************//*!
   *
   * @brief change clock from FEE mode to FBI mode.
   *        
   * @param  pConfig     pointer to configuration. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FEE_to_FBI(ICS_ConfigType *pConfig)
{
	/* clear Loss of lock sticky bit */
	ICS->S |= ICS_S_LOLS_MASK;
	
	/* select internal clock as clock source */
	/* select internal reference for FLL */ 
	/* LP = 0 */

    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(1);   
	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 
	
	/* wait for the reference clock to be changed */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(!(ICS->S & ICS_S_IREFST_MASK));
	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=1);
	
#if defined(BUS_CLK_EQU_CORE_DIVIDE_BY_2)||defined(CPU_KEA8)        
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}

#else
	ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK));
       
#endif    
        OSC_Disable();            
}


/*****************************************************************************//*!
   *
   * @brief change clock from FEE mode to FBE mode.
   *        
   * @param  pConfig     pointer to configuration .
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FEE_to_FBE(ICS_ConfigType *pConfig)
{
	/* clear Loss of lock sticky bit */
	ICS->S |= ICS_S_LOLS_MASK;
	
	/* select the external clock as clock source */
        /* LP = 0 */
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(2);   
	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 
	
	/* wait for the clock source to be changed */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=2);
	
	/* now system clock source is external clock
	 * NOTE: make sure that the external clock is within 20MHz 
	 */
#if defined(CPU_KEA8)	 
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}	
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
}


/*****************************************************************************//*!
   *
   * @brief change clock from FBI mode to FBE mode.
   *        
   * @param  pConfig     pointer to configuration. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FBI_to_FBE(ICS_ConfigType *pConfig)
{
        /* enable OSC */
	OSC_Init(&pConfig->oscConfig); 
    
	/* select external reference clock */
	/* select the external clock as clock source */

        ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(2);   
	
	/* wait for the clock source to be changed */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) !=2);
	while((ICS->S & ICS_S_IREFST_MASK));
	
	/* now system clock source is external clock
	 * NOTE: make sure that the external clock is within 20MHz 
	 */
#if defined(CPU_KEA8)
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}	
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
}


/*****************************************************************************//**
   *
   * @brief change clock from FBI mode to FEE mode.
   *        
   * @param  pConfig     pointer to configuration. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FBI_to_FEE(ICS_ConfigType *pConfig)
{
	OSC_Init(&pConfig->oscConfig); /* enable OSC */
  
	/* select external reference clock */
	/* select the FLL output as clock source */

        ICS->C1 =  ICS->C1 & ~(ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK));   
	
	/* wait for the clock source to be changed */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     

	while((ICS->S & ICS_S_CLKST_MASK));
	while((ICS->S & ICS_S_IREFST_MASK));
	
	
	/* now system clock source is external clock
	 * NOTE: make sure that the external clock is within 20MHz 
	 */
#if defined(CPU_KEA8)
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
	/* clear Loss of lock sticky bit */
	ICS->S |= ICS_S_LOLS_MASK;	
}

/*****************************************************************************//*!
   *
   * @brief change clock from FBI mode to FBILP mode. 
   * 
   * @param  pConfig     pointer to configuration 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @warning   must run without debug interface attached.
   * @see   ICS_ConfigType
   *****************************************************************************/
void FBI_to_FBILP(ICS_ConfigType *pConfig)
{
	/* assume external crystal is 8Mhz or 4MHz
	 * 
	 */
	ICS->C2 |= ICS_C2_LP_MASK;	/* enter low power mode */
}


/*****************************************************************************//*!
   *
   * @brief change clock from FBI mode to FEI mode. 
   * 
   * @param  pConfig     pointer to configuration. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FBI_to_FEI(ICS_ConfigType *pConfig)
{
	/* select internal reference clock */
	/* select the FLL output as clock source */
    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK));   
	
	/* wait for the clock source to be changed */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while((ICS->S & ICS_S_CLKST_MASK));
	while(!(ICS->S & ICS_S_IREFST_MASK));

        
	/* now system clock source is FLL output
	 * 
	 */
#if defined(CPU_KEA8)
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}	
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
	/* clear Loss of lock sticky bit */
	ICS->S |= ICS_S_LOLS_MASK;	
}



/*****************************************************************************//*!
   *
   * @brief change clock from FBE mode to FBI mode.
   *        
   * @param  pConfig     pointer to configuration. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FBE_to_FBI(ICS_ConfigType *pConfig)
{
	/* select internal reference clock */
	/* select the internal clock as clock source */
    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK)) | ICS_C1_CLKS(1);   
	
	/* wait for the clock source to be changed */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(((ICS->S & ICS_S_CLKST_MASK) >> ICS_S_CLKST_SHIFT) != 1);
	while(!(ICS->S & ICS_S_IREFST_MASK));
	
	/* now system clock source is internal clock
	 * 
	 */
	 
#if defined(CPU_KEA8)
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}	
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif
        
    /* Disable OSC to save power
     */
    OSC_Disable();
}

/*****************************************************************************//*!
   *
   * @brief change clock from FBE mode to FEE mode.
   *        
   * @param  pConfig     pointer to configuration. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FBE_to_FEE(ICS_ConfigType *pConfig)
{
	/* select the FLL output as clock source */
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK));   
	
	/* wait for the clock source to be changed */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while(ICS->S & ICS_S_CLKST_MASK);

	
	/* now system clock source is FLL output
	 * NOTE: external clock <= 20MHz
	 */
#if defined(CPU_KEA8)
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}	
#else
    ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif	
	/* clear Loss of lock sticky bit */
	ICS->S |= ICS_S_LOLS_MASK;	
}


/*****************************************************************************//*!
   *
   * @brief change clock from FBE mode to FEI mode.
   *        
   * @param  pConfig     pointer to configuration. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FBE_to_FEI(ICS_ConfigType *pConfig)
{
	/* select internal reference clock */
	/* select the internal clock as clock source */

    ICS->C1 =  ICS->C1 | (ICS_C1_IREFS_MASK);
	ICS->C1 = (ICS->C1 & ~(ICS_C1_CLKS_MASK));   
	
	/* wait for the clock source to be changed */
#if defined(IAR)        
	asm(
		"nop \n"
		"nop \n"
	);
#elif defined(__MWERKS__)
	asm{
		nop 
		nop
        };        
#endif     
	while((ICS->S & ICS_S_CLKST_MASK));
	while(!(ICS->S & ICS_S_IREFST_MASK));
#if defined(CPU_KEA8)	
	/* now system clock source is internal clock
	 * 
	 */
	if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
	{
		ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
	}
#else
        ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
#endif	
	/* clear Loss of lock sticky bit */
	ICS->S |= ICS_S_LOLS_MASK;	
        
    /* Disable OSC to save power
     */
    OSC_Disable();
}



/*****************************************************************************//*!
   *
   * @brief change clock from FBE mode to FBELP mode. 
   *
   * @param  pConfig     pointer to configuration. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FBE_to_FBELP(ICS_ConfigType *pConfig)
{
	/* enter low power mode */
 	ICS->C2 = ICS->C2 | (ICS_C2_LP_MASK); 
}


/*****************************************************************************//*!
   *
   * @brief change clock from FBELP mode to FBE mode. 
   * 
   * @param  pConfig     pointer to configuration. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FBELP_to_FBE(ICS_ConfigType *pConfig)
{
	/* enter low power mode */
 	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 
}

/*****************************************************************************//*!
   *
   * @brief change clock from FBILP mode to FBI mode. 
   * 
   * @param  pConfig     pointer to configuration. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/
void FBILP_to_FBI(ICS_ConfigType *pConfig)
{
	/* enter low power mode */
	ICS->C2 = ICS->C2 & ~(ICS_C2_LP_MASK); 
}

/******************************************************************************
* define ICS API list
*
*//*! @addtogroup ics_api_list
* @{
*******************************************************************************/


/*****************************************************************************//*!
   *
   * @brief  trim internal clock (IRC). 
   * 
   * @param  u16TrimValue    trim value 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/

void ICS_Trim(uint16_t u16TrimValue)
{
   ICS->C3 =  (uint8_t) u16TrimValue;
   ICS->C4 = (ICS->C4 & ~(ICS_C4_SCFTRIM_MASK)) | ((u16TrimValue>>8) & 0x01);
   while(!(ICS->S & ICS_S_LOCK_MASK));    
}


/*****************************************************************************//*!
   *
   * @brief set clock divider so that the reference clock for FLL/PLL is within 
   *    spec.
   *
   * @param  u32ClkFreqKHz  reference clock frequency in KHz.
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/

void ICS_SetClkDivider(uint32_t u32ClkFreqKHz)
{
    
    switch(u32ClkFreqKHz)
    {
        case 8000L:
        case 10000L:
            /* 8MHz or 10MHz */
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(3);	
            /* now the divided frequency is 8000/256 = 31.25K */
            /* now the divided frequency is 10000/256 = 39.0625K */
            break;
        case 4000L:
            /* 4MHz */
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(2);	
            /* now the divided frequency is 4000/128 = 31.25K */
            break;
        case 16000L:
            /* 16MHz */
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(4);	
            /* now the divided frequency is 16000/512 = 31.25K */
            break;
        case 20000L:
            /* 20MHz */
            ICS->C1 = (ICS->C1 & ~(ICS_C1_RDIV_MASK)) | ICS_C1_RDIV(4);     
            /* now the divided frequency is 20000/512 = 39.0625K */
            break;
        case 32L:
            /* 32KHz */
            ICS->C1  &= ~(ICS_C1_RDIV_MASK);
            break;
        default:
            break;
    }
}

/*****************************************************************************//*!
   *
   * @brief initialize ICS to the desired clock as defined in BUS_CLK_HZ.
   * 
   * @param  pConfig    pointer to ICS configuration.  
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_ConfigType
   *****************************************************************************/

void ICS_Init(ICS_ConfigType *pConfig)
{
  if(pConfig->u8ClkMode == ICS_CLK_MODE_FEE)
  {    
        // is crystal  
        pConfig->oscConfig.bIsCryst = 1;        
        // wait init complete      
        pConfig->oscConfig.bWaitInit = 1;        
        // switch to FEE mode with external crystal    
        FEI_to_FEE(pConfig);    
  }
  else if (pConfig->u8ClkMode == ICS_CLK_MODE_FEE_OSC)
  {     
        pConfig->oscConfig.bIsCryst = 0;        // is clock      
        FEI_to_FEE_OSC(pConfig);                // switch to FEE mode with active oscillator input 
  }
  else if (pConfig->u8ClkMode == ICS_CLK_MODE_FBE_OSC)
  {
        pConfig->oscConfig.bIsCryst = 0;        // is clock      
        FEI_to_FBE_OSC(pConfig);                // switch to FBE mode with active oscillator input
  } 
  else
  {
        // FEI mode by default 
        #if defined(CPU_KEA8)
        if(((ICS->C2 & ICS_C2_BDIV_MASK)>>5) != 1)
        {
            ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(1);
        }
        #else
            ICS->C2 = (ICS->C2 & ~(ICS_C2_BDIV_MASK)) | ICS_C2_BDIV(0);
        #endif
  }
}

/*****************************************************************************//*!
   *
   * @brief initialize ICS to the default state.
   * 
   * @param  none      
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_Init
   *****************************************************************************/

void ICS_DeInit(void)
{
    ICS->C1 = ICS_C1_DEFAULT;
    ICS->C2 = ICS_C2_DEFAULT;
    ICS->C3 = ICS_C3_DEFAULT;
    ICS->C4 = ICS_C4_DEFAULT;
    while(ICS->S != ICS_S_DEFAULT)
        ;       
}

/*! @} End of ics_api_list                                                    					*/


/******************************************************************************
* define OSC API list
*
*//*! @addtogroup osc_api_list
* @{
*******************************************************************************/

/*****************************************************************************//*!
   *
   * @brief initialize XOSC with given parameters: GAIN, RANGE in control structure.
   * 
   * @param  pConfig    pointer to OSC configuration. 
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   *****************************************************************************/
void OSC_Init(OSC_ConfigType *pConfig)
{
	uint8   cr = 0;
	/* 
	 * 
	 */
	if(pConfig->bGain)
	{
		/* high gain */
		cr |= OSC_CR_HGO_MASK ;		/* Rs must be added and be large up to 200K */
	}
	
	if(pConfig->bRange)
	{
		cr |= OSC_CR_RANGE_MASK; /* high range */	
	}

	if(pConfig->bStopEnable)
	{
		cr |= OSC_CR_OSCSTEN_MASK; 
	}

	if(pConfig->bIsCryst)
	{
		cr |= OSC_CR_OSCOS_MASK;
	}

	if(pConfig->bEnable)
	{
		cr |= OSC_CR_OSCEN_MASK;
	}
    
    OSC->CR = cr;
    
	if(pConfig->bWaitInit)
	{

		/* wait for OSC to be initialized
		 * 
		 */
		while(!(OSC->CR & OSC_CR_OSCINIT_MASK));
		
	}
}

/*****************************************************************************//*!
   *
   * @brief initialize OSC to the default state.
   * 
   * @param  none      
   *
   * @return none
   *
   * @ Pass/ Fail criteria: none
   * @see   ICS_Init
   *****************************************************************************/

void OSC_DeInit(void)
{
    OSC->CR = OSC_CR_DEFAULT;
}


/*! @} End of osc_api_list                                                    					*/




