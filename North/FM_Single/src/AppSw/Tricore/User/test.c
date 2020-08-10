/*
 * test.c
 *
 *  Created on: 2020��7��17��
 *      Author: pengs
 */

#include "include.h"

// �������Ժ���
void test_bluetooth(void){
	while(1){//��λ��һֱ����0x01
		UART_PutChar(Bluetooth,0xa0);
		UART_PutChar(Bluetooth,0x01);
		UART_PutChar(Bluetooth,0x00);
	}
}

//������Ժ���
void test_motor(void){
	struct vector3f_t temp_vec = {0,-100,0};
	while(1){
		vector2speed(&temp_vec,2);
	}
}

// �¶ȴ�����
void test_DQ(void){
	while(1){
		datapros((int)Ds18b20ReadTemp());	 //���ݴ�����
	}
}

void Print_Cmd(void){
	TFTSPI_CLS(u16BLACK);   //��ɫ��Ļ
	sprintf(txt,"test terminal");
	TFTSPI_P8X16Str(1,0,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"do:");
	TFTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"1. change ob");
	TFTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"2. change kp");
	TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"3. change cut");
	TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"4. speed");
	TFTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"1~4");
	TFTSPI_P8X16Str(1,6,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
}

uint32_t Change_obacle_length(void){
	TFTSPI_CLS(u16BLACK);   //��ɫ��Ļ
	sprintf(txt,"Change_obacle");
	TFTSPI_P8X16Str(1,0,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"do:");
	TFTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"1. add %f",(float)Change_ob);
	TFTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"2.sub %f",(float)Change_ob);
	TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"3. reback");
	TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"4. finished");
	TFTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"1~4");
	TFTSPI_P8X16Str(1,6,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ

	while(1){
		uint32_t B1 = PIN_Read(Button1);
		uint32_t B2 = PIN_Read(Button2);
		uint32_t B3 = PIN_Read(Button3);
		uint32_t B4 = PIN_Read(Button4);

		sprintf(txt,"cur_ob %f",obacle_length);
		TFTSPI_P8X16Str(1,7,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
		// ��Ⲧ�밴��
		if(!B1){
			delayms(DELAYTIME);
			sprintf(txt,"add %f",(float)Change_ob);
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			obacle_length += Change_ob;
		}
		else if(!B2){
			delayms(DELAYTIME);
			sprintf(txt,"sub %f",(float)Change_ob);
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			obacle_length -= Change_ob;		
		}
		else if(!B3){
			delayms(DELAYTIME);
			sprintf(txt,"reback");
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			return 1;
		}
		else if(!B4){
			delayms(DELAYTIME);
			sprintf(txt,"finished");
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			return 2;
		}
	}
}
uint32_t Change_kp_(void){
	TFTSPI_CLS(u16BLACK);   //��ɫ��Ļ
	sprintf(txt,"Change_kp");
	TFTSPI_P8X16Str(1,0,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"do:");
	TFTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"1. add %f",(float)Change_kp);
	TFTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"2.sub %f",(float)Change_kp);
	TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"3. reback");
	TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"4. finished");
	TFTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"1~4");
	TFTSPI_P8X16Str(1,6,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ

	while(1){
		uint32_t B1 = PIN_Read(Button1);
		uint32_t B2 = PIN_Read(Button2);
		uint32_t B3 = PIN_Read(Button3);
		uint32_t B4 = PIN_Read(Button4);

		sprintf(txt,"cur_kp %f",kp);
		TFTSPI_P8X16Str(1,7,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
		// ��Ⲧ�밴��
		if(!B1){
			delayms(DELAYTIME);
			sprintf(txt,"add %f",(float)Change_kp);
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			kp += Change_kp;
		}
		else if(!B2){
			delayms(DELAYTIME);
			sprintf(txt,"sub %f",(float)Change_kp);
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			kp -= Change_kp;
		}
		else if(!B3){
			delayms(DELAYTIME);
			sprintf(txt,"reback");
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			return 1;
		}
		else if(!B4){
			delayms(DELAYTIME);
			sprintf(txt,"finished");
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			return 2;
		}
	}
}
uint32_t  Change_cut_down_len(void){
	TFTSPI_CLS(u16BLACK);   //��ɫ��Ļ
	sprintf(txt,"Change_cut");
	TFTSPI_P8X16Str(1,0,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"do:");
	TFTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"1. add %f",(float)Change_cut);
	TFTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"2.sub %f",(float)Change_cut);
	TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"3. reback");
	TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"4. finished");
	TFTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"1~4");
	TFTSPI_P8X16Str(1,6,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ

	while(1){
		uint32_t B1 = PIN_Read(Button1);
		uint32_t B2 = PIN_Read(Button2);
		uint32_t B3 = PIN_Read(Button3);
		uint32_t B4 = PIN_Read(Button4);

		sprintf(txt,"cur_cut %f",Cut_down_len);
		TFTSPI_P8X16Str(1,7,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
		// ��Ⲧ�밴��
		if(!B1){
			delayms(DELAYTIME);
			sprintf(txt,"add %f",(float)Change_cut);
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			Cut_down_len += Change_cut;
		}
		else if(!B2){
			delayms(DELAYTIME);
			sprintf(txt,"sub %f",(float)Change_cut);
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			Cut_down_len -= Change_cut;		
		}
		else if(!B3){
			delayms(DELAYTIME);
			sprintf(txt,"reback");
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			return 1;
		}
		else if(!B4){
			delayms(DELAYTIME);
			sprintf(txt,"finished");
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			return 2;
		}
	}
}
uint32_t Change_Speed(void){
	TFTSPI_CLS(u16BLACK);   //��ɫ��Ļ
	sprintf(txt,"Change_Speed");
	TFTSPI_P8X16Str(1,0,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"do:");
	TFTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"1. add %f",(float)Change_speed);
	TFTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"2.sub %f",(float)Change_speed);
	TFTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"3. reback");
	TFTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"4. finished");
	TFTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	sprintf(txt,"1~4");
	TFTSPI_P8X16Str(1,6,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
	while(1){
		uint32_t B1 = PIN_Read(Button1);
		uint32_t B2 = PIN_Read(Button2);
		uint32_t B3 = PIN_Read(Button3);
		uint32_t B4 = PIN_Read(Button4);

		sprintf(txt,"cur_v %f",V_speed);
		TFTSPI_P8X16Str(1,7,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
		// ��Ⲧ�밴��
		if(!B1){
			delayms(DELAYTIME);
			sprintf(txt,"add %f",(float)Change_speed);
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			V_speed += Change_speed;
		}
		else if(!B2){
			delayms(DELAYTIME);
			sprintf(txt,"sub %f",(float)Change_speed);
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			V_speed -= Change_speed;
		}
		else if(!B3){
			delayms(DELAYTIME);
			sprintf(txt,"reback");
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			return 1;
		}
		else if(!B4){
			delayms(DELAYTIME);
			sprintf(txt,"finished");
			TFTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//�ַ�����ʾ
			return 2;
		}
	}
}
void Test_terminal(void){
	// ��ʾ��
	TFTSPI_Init(1);         //LCD��ʼ��  0:����  1������
	TFTSPI_CLS(u16BLACK);   //��ɫ��Ļ
	// ׼�������ն�
	Print_Cmd();
	uint32_t state = 0;
	while(1){
		uint32_t B1 = PIN_Read(Button1);
		uint32_t B2 = PIN_Read(Button2);
		uint32_t B3 = PIN_Read(Button3);
		uint32_t B4 = PIN_Read(Button4);

		if((B1+B2+B3+B4) <= 2){
			break;
		}
		// ��Ⲧ�뿪��״̬
		if(!B1){
			delayms(DELAYTIME);
			state = Change_obacle_length();
			if(state == 1){//
				Print_Cmd();
			}
			else if(state == 2){
				break;
			}
		}
		else if(!B2){
			delayms(DELAYTIME);
			state = Change_kp_();
			if(state == 1){//
				Print_Cmd();
			}
			else if(state == 2){
				break;
			}
		}
		else if(!B3){
			delayms(DELAYTIME);
			state = Change_cut_down_len();
			if(state == 1){//
				Print_Cmd();
			}
			else if(state == 2){
				break;
			}
		}
		else if(!B4){
			delayms(DELAYTIME);
			state = Change_Speed();
			if(state == 1){//
				Print_Cmd();
			}
			else if(state == 2){
				break;
			}
		}
	}
}
