#ifndef FTM_H_
#define FTM_H_
#ifdef __cplusplus
extern "C" {
#endif
  
  
/******************************************************************************
* Includes
******************************************************************************/
#include "common.h"
#include "include.h"

/******************************************************************************
* Constants
******************************************************************************/
extern FTM_Type * FTMx[3] ;
/******************************************************************************
* Macros
******************************************************************************/
  
#define FTM_PRECISON               1000  
#define FTMx_CV(ftmx,ch,cv)        FTMx[ftmx]->CONTROLS[ch].CnV = cv  ;
  
#define FTM_INPUTCAPTURE_RISINGEDGE           1     /*!< rising edge */
#define FTM_INPUTCAPTURE_FALLINGEDGE          2     /*!< falling edge */
#define FTM_INPUTCAPTURE_BOTHEDGE             3     /*!< both edge */
  
#define FTM_INPUTCAPTURE_DUALEDGE_NOEDGE      0     /*!< none */
#define FTM_INPUTCAPTURE_DUALEDGE_RISINGEDGE  1     /*!< rising edge*/
#define FTM_INPUTCAPTURE_DUALEDGE_FALLINGEDGE 2     /*!< falling edge*/
#define FTM_INPUTCAPTURE_DUALEDGE_BOTHEDGE    3     /*!< both edge */
  
#define FTM_PWMMODE_EDGEALLIGNED      		1          /*!< EPWM */
#define FTM_PWMMODE_CENTERALLIGNED    		2          /*!< CPWM */
#define FTM_PWMMODE_COMBINE					3		   /*!< Combine PWM */
#define FTM_INPUT_CAPTURE			  		4   	  /*!< Input capture */
#define FTM_OUTPUT_COMPARE  		  		5  	  	  /*!< Output compare */
#define FTM_INPUTCAPTURE_DUALEDGE		  	6		  /*!< Dual Edge Capture*/
/* mode edge select*/
#define FTM_INPUTCAPTURE_RISINGEDGE           1     /*!< rising edge */
#define FTM_INPUTCAPTURE_FALLINGEDGE          2     /*!< falling edge */
#define FTM_INPUTCAPTURE_BOTHEDGE             3     /*!< both edge */
  
#define FTM_INPUTCAPTURE_DUALEDGE_NOEDGE      0     /*!< none */
#define FTM_INPUTCAPTURE_DUALEDGE_RISINGEDGE  1     /*!< rising edge*/
#define FTM_INPUTCAPTURE_DUALEDGE_FALLINGEDGE 2     /*!< falling edge*/
#define FTM_INPUTCAPTURE_DUALEDGE_BOTHEDGE    3     /*!< both edge */
  
#define FTM_INPUTCAPTURE_DUALEDGE_ONESHOT     2  /*!< dual edge one shot mode*/ 
#define FTM_INPUTCAPTURE_DUALEDGE_CONTINUOUS  1  /*!< dual edge continuouse mode*/
typedef struct
{
    uint8_t   clk_source;       /*!< clock source */
    uint8_t   prescaler;        /*!< clock prescaler */
    uint8_t   cpwms;            /*!< up-down counting mode */
    uint8_t   toie;             /*!< enable overflow interrupt */
    uint16_t  modulo;           /*!< counter mod */
    uint16_t  cnt;              /*!< counter value */
    uint16_t  cntin;            /*!< counter inite */
    uint8_t   mode;             /*!< features mode selction */
    uint8_t   sync;             /*!< synchronization */
    uint8_t   outinit;          /*!< initial state for channels output  */
    uint8_t   outmask;          /*!< output mask */
    uint32_t  combine;          /*!< function for linked channels */
    uint16_t  deadtime;         /*!< dead time insertion control */
    uint8_t   exttrig;          /*!< external trigger */
    uint8_t   pol;              /*!< channels polarity */
    uint16_t  filter;           /*!< input filter control */
    uint8_t   fms;              /*!< fault mode status */
    uint16_t  fltctrl;          /*!< fault control */
    uint8_t   fltpol;           /*!< fault input polarity */
    uint16_t  conf;             /*!< FTM configuration */
    uint32_t  synconf;          /*!< synchronization configuration*/
    uint8_t   invctrl;          /*!< inverting control */
    uint16_t  swoctrl;          /*!< software output control */
    uint16_t  pwmload;          /*!< pwm load control */
} FTM_ConfigType, *FTM_ConfigPtr;
  
typedef struct
{
  uint16_t        u16CnV;                  /*!< FTM channel value control */
  union
  {
    struct 
    {
      uint32_t    bMode         : 6;        /*!< flextimer mode:INPUT_CAPTURE, OUTPUT_COMPARE, EDGE_ALIGNED_PWM, CENTER_ALIGNED_PWM,
      * COMBINE_PWM, DUAL_EDGE_CAPTURE 
      */
      uint32_t    bEdge         : 2;        /*!< edge select */
      uint32_t    bOutCmp       : 2;        /*!< toggle, clear, set */
      uint32_t    bPWMPol       : 2;        /*!< high-true pulse, low-true pulses */
      uint32_t    bDualCapMode  : 2;        /*!< dual edge capture mode: one-shot, continuous mode */
      uint32_t    bCHIE         : 1;        /*!< enable channel interrupt */
    }bits;
  }ctrl;                                    /*!< FTM channel feature control */
} FTM_ChParamsType;
  /******************************************************************************
  * Types
  ******************************************************************************/
  //定义FTM模块号
typedef enum
{
  CFTM0,
  CFTM1,
  CFTM2,
    
  FTM_MAX,
} FTMn_e;
  
  //定义FTM 通道号
typedef enum
{ 
  FTM_CH0,
  FTM_CH1,
  FTM_CH2,
  FTM_CH3,
  FTM_CH4,
  FTM_CH5,
} FTM_CHn_e; 
  
typedef enum 
{
  FTM_PTA0,         
  FTM_PTB2,
  FTM_PTA1,         
  FTM_PTB3,
  FTM_PTC4,         
  FTM_PTH2,
  FTM_PTC5,         
  FTM_PTE7,
  FTM_PTC0,         
  FTM_PTH0,
  FTM_PTF0,
  FTM_PTC1,         
  FTM_PTH1,
  FTM_PTF1,
  FTM_PTC2,        
  FTM_PTD0,
  FTM_PTG4,
  FTM_PTC3,         
  FTM_PTD1,
  FTM_PTG5,
  FTM_PTB4,        
  FTM_PTG6,
  FTM_PTB5,        
  FTM_PTG7,
}FTM_PTxn;
  
  
  
/******************************************************************************
* Global functions
******************************************************************************/
  
void FTM_PWM_init(FTMn_e ftm, FTM_CHn_e ch,FTM_PTxn ptxn ,uint32_t freq, uint32_t duty);
void FTM_PWM_Duty(FTMn_e ftm, FTM_CHn_e ch, uint32_t duty);
void FTM_count_init(FTMn_e ftm);
uint16 FTM_count_get(FTMn_e ftm);
void FTM_count_clean(FTMn_e ftm);
void TestFTM_PWM(void);
void TestFTM_InputCapture(void);

//以下为输入捕捉模式函数，有待debug，
void FTM_SetCounterInitValue(FTMn_e pFTM, uint16_t u16CounterValue);
uint16_t FTM_GetCounterValue(FTMn_e pFTM);
void FTM_SetLoadEnable(FTMn_e pFTM);
void FTM_SetLoadMatchChannel(FTMn_e pFTM, FTM_CHn_e u8Matchchannel);
void FTM_InputCaptureFilterClr(FTMn_e pFTM, FTM_CHn_e ch);
void FTM_InputCaptureFilterSet(FTMn_e pFTM, FTM_CHn_e ch, uint8_t u8FilterValue);
void FTM_InputCaptureInit(FTMn_e pFTM, FTM_CHn_e ch, uint8_t u8CaptureMode); 
  
#endif /* FTM_H_ */
  