/*LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
��ƽ    ̨�������������ܿƼ�TC264DA���İ�
����    д��ZYF/chiusir
��E-mail  ��chiusir@163.com
������汾��V1.1 ��Ȩ���У���λʹ��������ϵ��Ȩ
�������¡�2020��4��10��
�������Ϣ�ο����е�ַ��
����    վ��http://www.lqist.cn
���Ա����̡�http://longqiu.taobao.com
------------------------------------------------
��dev.env.��Hightec4.9.3/Tasking6.3�����ϰ汾
��Target �� TC264DA
��Crystal�� 20.000Mhz
��SYS PLL�� 200MHz
________________________________________________________________

QQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQQ*/
#ifndef __LQ_SGP18T_TFTSPI_H__
#define __LQ_SGP18T_TFTSPI_H__	
#include "..\Driver\include.h"//����ģ���ͷ�ļ�

/*******************�ӿڶ���******************************/

#define APP_LCD_WIDTH  LCD_WIDTH//Һ�������
#define APP_LCD_HEIGHT LCD_HEIGHT//Һ�����߶�

#define TFT18W        162
#define TFT18H        132

#define u16RED		0xf800
#define u16GREEN	0x07e0
#define u16BLUE	0x001f
#define u16PURPLE	0xf81f
#define u16YELLOW	0xffe0
#define u16CYAN	0x07ff 		//����ɫ
#define u16ORANGE	0xfc08
#define u16BLACK	0x0000
#define u16WHITE	0xffff

/*****************˽�к�������*********************************/							
extern void TFTSPI_Init(unsigned char type);									 //LCD��ʼ��  0:����  1������
extern void TFTSPI_Write_Cmd(unsigned char cmd);						         //���Ϳ�����
extern void TFTSPI_Write_Byte(unsigned char dat);						         //�������ݲ���
extern void TFTSPI_Write_Word(unsigned short dat);						         //����������ʾ����
extern void TFTSPI_Addr_Rst(void);							         //DDRAM��ַ����
extern void TFTSPI_Set_Pos(unsigned char xs,unsigned char ys,unsigned char xe,unsigned char ye);	                         //��λ��ʾ����λ��
extern void TFTSPI_CLS(unsigned short color);					                         //ȫ����ʾĳ����ɫ
extern void TFTSPI_Draw_Part(unsigned char xs,unsigned char ys,unsigned char xe,unsigned char ye,unsigned short color_dat);     //��������������ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
extern void TFTSPI_Draw_Line(unsigned char xs,unsigned char ys,unsigned char xe,unsigned char ye,unsigned short color_dat);     //���ߣ�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
extern void TFTSPI_Draw_Rectangle(unsigned char xs,unsigned char ys,unsigned char xe,unsigned char ye,unsigned short color_dat);//�����α߿�����ʼ����ֹ���꣬����ʼ����ֹ���꣬��ɫ
extern void TFTSPI_Draw_Circle(unsigned char x,unsigned char y,unsigned char r,unsigned short color_dat);                 //��Բ�α߿�Բ�ĺ����ꡢ�����꣬�뾶����ɫ
extern void TFTSPI_Draw_Dot(unsigned char x,unsigned char y,unsigned short color_dat);	                         //���㣬�����꣬�����꣬��ɫ
extern void TFTSPI_P8X16(unsigned char x, unsigned char y, unsigned char c_dat,unsigned short word_color,unsigned short back_color);
extern void TFTSPI_P8X16Str(unsigned char x, unsigned char y, char *s_dat,unsigned short word_color,unsigned short back_color);
extern void TFTSPI_P6X8(unsigned char x, unsigned char y, unsigned char c_dat,unsigned short word_color,unsigned short back_color);
extern void TFTSPI_P6X8Str(unsigned char x, unsigned char y, char *s_dat,unsigned short word_color,unsigned short back_color);
extern void TFTSPI_P6X8NUM(unsigned char x, unsigned char y, unsigned short num, unsigned char num_bit,unsigned short word_color,unsigned short back_color);
extern void TFTSPI_P8X8(unsigned char x, unsigned char y, unsigned char c_dat,unsigned short word_color,unsigned short back_color);
extern void TFTSPI_P8X8Str(unsigned char x, unsigned char y, char *s_dat,unsigned short word_color,unsigned short back_color);
extern void TFTSPI_P8X8NUM(unsigned char x, unsigned char y, unsigned short num, unsigned char num_bit,unsigned short word_color,unsigned short back_color);
extern void TFTSPI_P16x16Str(unsigned char x,unsigned char y,unsigned char *s_dat,unsigned short word_color,unsigned short back_color);
extern void TFTSPI_P16x12Str(unsigned char x,unsigned char y,char *s_dat,unsigned short word_color,unsigned short back_color);
extern void TFTSPI_Show_Pic(unsigned char xs,unsigned char ys,unsigned char xe,unsigned char ye,unsigned char *ppic);
extern void TFTSPI_Show_Pic2(unsigned char xs,unsigned char ys,unsigned char w,unsigned char h,const unsigned char *ppic) ;
extern void TFTSPI_Show_Battery_Icon(void);
extern void TFTSPI_Show_Title(void);
extern void TFTSPI_Show_Logo(unsigned char xs,unsigned char ys);
extern void Test_TFT18(void);
extern void ColumnarSetting(unsigned char x,unsigned char y, unsigned char w,unsigned char h,unsigned short fclolr,unsigned short bcolor);
extern void DrawingColumnar(unsigned char t,unsigned char duty,unsigned char cl);
extern void Clear_Columnar(void);
void TFT_Full_Scr_Road(void);
void TFTSPI_Road(unsigned char high_start, unsigned char wide_start, unsigned char high, unsigned char wide, unsigned char *Pixle);
void TFTSPI_BinRoad(unsigned char high_start, unsigned char wide_start, unsigned char high, unsigned char wide, unsigned char *Pixle);


#endif /*SGP18T_ILI9163B.h*/
