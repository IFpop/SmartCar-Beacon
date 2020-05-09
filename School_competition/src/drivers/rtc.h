#ifndef RTC_H_
#define RTC_H_
#ifdef __cplusplus
extern "C" {
#endif
  
typedef enum  
{ // ±÷”—°‘Ò     
  RTC_BUSCLK = 0,    //           
  RTC_LPOCLK = 1,    // 
}RTC_CLKSELn;
  
#define RTC_OUTPUT_ENABLE           1	/*!< enable RTCO pin  */ 
#define RTC_INTERRUPT_ENABLE        1	/*!< enable RTC interrupt  */ 
#define RTC_CLKSRC_EXTERNAL         0	/*!< select external clock as RTC clock source  */
#define RTC_CLKSRC_1KHZ             1	/*!< select LPO as RTC clock source  */
#define RTC_CLKSRC_IREF             2	/*!< select internal reference clock as RTC clock source  */
#define RTC_CLKSRC_BUS              3	/*!< select bus clock as RTC clock source  */
#define RTC_CLK_PRESCALER_128       1	/*!< presalcer is 1 or 128 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_256       2	/*!< presalcer is 2 or 256 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_512       3	/*!< presalcer is 4 or 512 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_1024      4	/*!< presalcer is 8 or 1024 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_2048      5	/*!< presalcer is 16 or 2048 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_100       6	/*!< presalcer is 32 or 100 according to RTCLKS bits */
#define RTC_CLK_PRESCALER_1000      7	/*!< presalcer is 64 or 1000 according to RTCLKS bits */


void RTC_Init(RTC_CLKSELn sel_clk,uint16 int_ms);
void TestRTC(void);
void RTC_ISR(void);

#endif

