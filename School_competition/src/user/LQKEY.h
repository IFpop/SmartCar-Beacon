
/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������S9KEAZ128���ܳ����İ�
����    д��CHIUSIR
��E-mail  ��chiusir@163.com
������汾��V1.0
�������¡�2017��11��5��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4
��Target  ��S9KEAZ128
��Crystal ��16.000Mhz
��busclock��?0.000MHz
��pllclock��?0.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __KEY_H__
#define __KEY_H__

//����ģ���
typedef enum
{
    KEY0=0,
    KEY1=1,
    KEY2=2,
    KEY3=3,
    KEYALL=4,
} KEYn_e;
typedef enum
{
    KEYLOW=0,  //
    KEYHIGH=1, //   
    KEYFAIL=0xFF,
}KEYs_e;



//����
extern void   KEY_Init(void);
extern uint8_t KEY_Read(KEYn_e keyno);
extern void Test_KEY(void);
extern void   KEY1_Init(void);
extern uint8_t KEY1_Read(KEYn_e keyno);
extern void Test_KEY1(void);
#endif 
