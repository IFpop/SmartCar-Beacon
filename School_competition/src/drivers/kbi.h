#ifndef _KBI_H_
#define _KBI_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gpio_icf.h" 
  
extern volatile KBI_Type * KBIx[2] ;
/*!
* @brief KBI MODE select enum.
*
*/
typedef enum
{
    KBI_MODE_EDGE_ONLY = 0,             /*!< select  edge only mode  */         
    KBI_MODE_EDGE_LEVEL                 /*!< select  both edge and level  mode */
}KBI_ModeType;

typedef enum
{
    KBIX0 = 0,             /*!< select  edge only mode  */         
    KBIX1                 /*!< select  both edge and level  mode */
}KBIn_e;



 /*!
 * @brief KBI Edge select enum.
 *
 */
typedef enum
{
    KBI_FALLING_LOW  = 0,     /*!< select falling edge and/or low level  */
    KBI_RISING__HIGH         /*!< select rising edge and/or high level  */
}KBI_Edge;

typedef enum {
KBI_PTA0,	
KBI_PTA1,
KBI_PTA2,
KBI_PTA3,
KBI_PTA4,
KBI_PTA5,
KBI_PTA6,
KBI_PTA7,
KBI_PTB0,	
KBI_PTB1,
KBI_PTB2,
KBI_PTB3,
KBI_PTB4,
KBI_PTB5,
KBI_PTB6,
KBI_PTB7,
KBI_PTC0,	
KBI_PTC1,
KBI_PTC2,
KBI_PTC3,
KBI_PTC4,
KBI_PTC5,
KBI_PTC6,
KBI_PTC7,
KBI_PTD0,	
KBI_PTD1,
KBI_PTD2,
KBI_PTD3,
KBI_PTD4,
KBI_PTD5,
KBI_PTD6,
KBI_PTD7,
KBI_PTE0,	
KBI_PTE1,
KBI_PTE2,
KBI_PTE3,
KBI_PTE4,
KBI_PTE5,
KBI_PTE6,
KBI_PTE7,
KBI_PTF0,	
KBI_PTF1,
KBI_PTF2,
KBI_PTF3,
KBI_PTF4,
KBI_PTF5,
KBI_PTF6,
KBI_PTF7,
KBI_PTG0,	
KBI_PTG1,
KBI_PTG2,
KBI_PTG3,
KBI_PTG4,
KBI_PTG5,
KBI_PTG6,
KBI_PTG7,
KBI_PTH0,	
KBI_PTH1,
KBI_PTH2,
KBI_PTH3,
KBI_PTH4,
KBI_PTH5,
KBI_PTH6,
KBI_PTH7,
KBI_PTI0,	
KBI_PTI1,
KBI_PTI2,
KBI_PTI3,
KBI_PTI4,
KBI_PTI5,
KBI_PTI6,
KBI_PTI7,
}KBI_PTxn;


/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Global functions
******************************************************************************/
void KBI_Init(KBIn_e kbix,KBI_PTxn ptxn,KBI_Edge RiFal) ;
void KBI_Disable(KBIn_e kbix,KBI_PTxn ptxn) ;
void KBI_Enable(KBIn_e kbix,KBI_PTxn ptxn) ;
void TestKBI(void);
#endif 
