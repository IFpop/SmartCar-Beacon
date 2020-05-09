#ifndef PIT_H_
#define PIT_H_
#ifdef __cplusplus
extern "C" {
#endif

  
typedef enum
{
    PIT_CHANNEL0 = 0,       /*!< PIT channel 0 */
    PIT_CHANNEL1            /*!< PIT channel 1 */
} PITn;
void       PIT_Init(uint8_t u8Channel_No, uint32_t cn) ;                                        //初始化PITn，并设置定时时间(单位为bus时钟周期)
#define     pit_init_ms(PITn,ms)          PIT_Init(PITn,ms * BUS_CLK_KHZ);                      //初始化PITn，并设置定时时间(单位为 ms)
#define     pit_init_us(PITn,us)          PIT_Init(PITn,us * BUS_CLK_KHZ/100);                  //初始化PITn，并设置定时时间(单位为 10us)
#define     PITENDINTERRUPT(PITn)         PIT->CHANNEL[PITn].TCTRL |= PIT_TCTRL_TIE_MASK        //使能PIT中断
#define     PITDIENDINTERRUPT(PITn)       PIT->CHANNEL[PITn].TCTRL &= ~PIT_TCTRL_TIE_MASK       //禁止PIT中断

void TestPIT(void);
void servo_pwm_init(void);

#endif 
