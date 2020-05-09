/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨������S9KEAZ128���ܳ�MINI���İ�ĸ��
����    д��
��E-mail  ��
������汾��V1.0
�������¡�2017��11��11��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://shop36265907.taobao.com
------------------------------------------------
��dev.env.��IAR7.80.4
��Target  ��S9KEAZ128
��Crystal ��16.000Mhz
��busclock��40.000MHz
��pllclock��40.000MHz
QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#include "include.h"

volatile KBI_Type * KBIx[2] = { KBI0,KBI1} ;

/*************************************************************************
*  �������ƣ�  KBI_Init
*  ����˵����  ��ʼ���ж�
*  �������أ�
*  ����˵����
*  for example KBI_Init(KBIX0, KBI_PTA0, KBI_FALLING_LOW);//PTA0
*************************************************************************/
void KBI_Init(KBIn_e kbix,KBI_PTxn ptxn,KBI_Edge RiFal)
{
  
  if(kbix == KBIX0 )
    {
        SIM->SCGC   |= SIM_SCGC_KBI0_MASK;             /* enable clock to KBI0 */\
        KBIx[kbix]->SC  &= ~KBI_SC_KBIE_MASK ;
        /****
        ��ʼ��IO
        *****/
        FGPIOA->PIDR  &= ~(1<<PTn(ptxn));              /* enable GPIO input */    
        FGPIOA->PDDR  &= ~(1<<PTn(ptxn)); 
        if(RiFal) PORT->PUE0  &= ~(1<<PTn(ptxn));
        else PORT->PUE0  |= (1<<PTn(ptxn));
        
    }
    else if (kbix == KBIX1)
    {        
        SIM->SCGC   |= SIM_SCGC_KBI1_MASK;             /* enable clock to KBI1 */
        KBIx[kbix]->SC  &= ~KBI_SC_KBIE_MASK ;

        /****
        ��ʼ��IO
        *****/
        FGPIOB->PIDR  &= ~(1<<PTn(ptxn));              /* enable GPIO input */    
        FGPIOB->PDDR  &= ~(1<<PTn(ptxn)); 
        if(RiFal) PORT->PUE1  &= ~(1<<PTn(ptxn));
        else PORT->PUE1  |= (1<<PTn(ptxn));

    }

  if(RiFal)
  {
    KBIx[kbix]->ES  |= (1<< PTn(ptxn));
  }
  else
  {
    KBIx[kbix]->ES  &= ~(1<< PTn(ptxn));
  }
  KBIx[kbix]->PE |= (1 << PTn(ptxn)) ;

  PORT->IOFLT0 |= PORT_IOFLT0_FLTDIV1(0) ;
  PORT->IOFLT0 |= PORT_IOFLT0_FLTKBI0(1) ;
  KBIx[kbix]->SC  = (0
                     //|KBI_SC_KBMOD_MASK           //�����غ�ˮƽ�ж�
                     |KBI_SC_KBIE_MASK              //�ж�ʹ��
                     |KBI_SC_KBACK_MASK             //
                     |KBI_SC_KBSPEN_MASK          //����KBxSP
                     |KBI_SC_RSTKBSP_MASK           //���KBIxSP
                      );
  
  if(kbix == KBIX0 )
   {
     NVIC_EnableIRQ(KBI0_IRQn);
   }
  else if (kbix == KBIX1)
    { 
      NVIC_EnableIRQ(KBI1_IRQn); 
    }
}

/*************************************************************************
*  �������ƣ�KBI_Disable
*  ����˵������ʼ���ж�
*  �������أ�
*  ����˵����
*  for example  KBI_Disable(KBIX0,KBI_PTA0);//A0
*************************************************************************/
void KBI_Disable(KBIn_e kbix,KBI_PTxn ptxn)
{
    KBIx[kbix]->PE &= ~(1 << PTn(ptxn)) ;  
}
/*************************************************************************
*  �������ƣ�KBI_Enable
*  ����˵������ʼ���ж�
*  �������أ�
*  ����˵����
*  for example  KBI_Enable(KBIX0,KBI_PTA0);//A0
*************************************************************************/
void KBI_Enable(KBIn_e kbix,KBI_PTxn ptxn)
{
  KBI0->SC |= KBI_SC_RSTKBSP_MASK ;    //����жϱ�־λ
  KBIx[kbix]->PE |= (1 << PTn(ptxn)) ;
}

//����GPIO�ⲿ�ж� ĸ����K0��K1������Ч��KBI�Ǽ����ж�
void TestKBI(void)
{   

  KBI_Init(KBIX0, KBI_PTB5, KBI_FALLING_LOW);//����K0 LED��ת
  KBI_Init(KBIX1, KBI_PTH2, KBI_FALLING_LOW);//����K1 LED��ת
  KBI_Enable(KBIX0,KBI_PTB5);
  KBI_Enable(KBIX1,KBI_PTH2);
  LED_Init();
  while(1)
  {
  }
}
