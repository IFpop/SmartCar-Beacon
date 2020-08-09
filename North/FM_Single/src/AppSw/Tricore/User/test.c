/*
 * test.c
 *
 *  Created on: 2020Äê7ÔÂ17ÈÕ
 *      Author: pengs
 */

#include "include.h"

// À¶ÑÀ²âÊÔº¯Êý
void test_bluetooth(void){
	while(1){//ÉÏÎ»»úÒ»Ö±½ÓÊÕ0x01
		UART_PutChar(Bluetooth,0xa0);
		UART_PutChar(Bluetooth,0x01);
		UART_PutChar(Bluetooth,0x00);
	}
}

//µç»ú²âÊÔº¯Êý
void test_motor(void){
	struct vector3f_t temp_vec = {0,-100,0};
	while(1){
		vector2speed(&temp_vec,2);
	}
}

// ÎÂ¶È´«¸ÐÆ÷
void test_DQ(void){
	while(1){
		datapros((int)Ds18b20ReadTemp());	 //Êý¾Ý´¦Àíº¯Êý
	}
}

void Print_Cmd(void){
	TFTSPI_CLS(u16BLACK);   //ºÚÉ«ÆÁÄ»
	sprintf(txt,"test terminal system");
	FTSPI_P8X16Str(1,0,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"you can do like following:");
	FTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"1. change obacle_length");
	FTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"2. change kp");
	FTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"3. change cut_down_speed_len");
	FTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"4. others");
	FTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"4. please touch 1~4 in button");
	FTSPI_P8X16Str(1,6,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
}

uint32_t Change_obacle_length(void){
	TFTSPI_CLS(u16BLACK);   //ºÚÉ«ÆÁÄ»
	sprintf(txt,"Change_obacle_length");
	FTSPI_P8X16Str(1,0,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"you can do like following:");
	FTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"1. add %f",(float)Change_ob);
	FTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"2.sub %f",(float)Change_ob);
	FTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"3. reback");
	FTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"4. finished");
	FTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"4. please touch 1~4 in button");
	FTSPI_P8X16Str(1,6,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾

	while(1){
		sprintf(txt,"cur_obacle_length %f",obacle_length);
		FTSPI_P8X16Str(1,7,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
		// ¼ì²â²¦Âë°´¼ü
		if(1){
			sprintf(txt,"add %f",(float)Change_ob);
			FTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
			obacle_length += Change_ob;
		}
		else if(2){
			sprintf(txt,"sub %f",(float)Change_ob);
			FTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
			obacle_length -= Change_ob;		
		}
		else if(3){
			sprintf(txt,"reback");
			FTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
			return 1;
		}
		else if(4){
			sprintf(txt,"finished");
			FTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
			start_flag = 1;
			return 2;
		}
	}
	return 0;
}
uint32_t Change_kp_(void){
	TFTSPI_CLS(u16BLACK);   //ºÚÉ«ÆÁÄ»
	sprintf(txt,"Change_kp");
	FTSPI_P8X16Str(1,0,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"you can do like following:");
	FTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"1. add %f",(float)Change_kp);
	FTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"2.sub %f",(float)Change_kp);
	FTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"3. reback");
	FTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"4. finished");
	FTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"4. please touch 1~4 in button");
	FTSPI_P8X16Str(1,6,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾

	while(1){
		sprintf(txt,"cur_kp %f",kp);
		FTSPI_P8X16Str(1,7,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
		// ¼ì²â²¦Âë°´¼ü
		if(1){
			sprintf(txt,"add %f",(float)Change_kp);
			FTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
			kp += Change_kp;
		}
		else if(2){
			sprintf(txt,"sub %f",(float)Change_kp);
			FTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
			kp -= Change_kp;		
		}
		else if(3){
			sprintf(txt,"reback");
			FTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
			return 1;
		}
		else if(4){
			sprintf(txt,"finished");
			FTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
			start_flag = 1;
			return 2;
		}
	}
	return 0;
}
uint32_t  Change_cut_down_len(void){
	TFTSPI_CLS(u16BLACK);   //ºÚÉ«ÆÁÄ»
	sprintf(txt,"Change_cut_down_len");
	FTSPI_P8X16Str(1,0,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"you can do like following:");
	FTSPI_P8X16Str(1,1,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"1. add %f",(float)Change_cut);
	FTSPI_P8X16Str(1,2,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"2.sub %f",(float)Change_cut);
	FTSPI_P8X16Str(1,3,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"3. reback");
	FTSPI_P8X16Str(1,4,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"4. finished");
	FTSPI_P8X16Str(1,5,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
	sprintf(txt,"4. please touch 1~4 in button");
	FTSPI_P8X16Str(1,6,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾

	while(1){
		sprintf(txt,"cur_cut_down_len %f",Cut_down_len);
		FTSPI_P8X16Str(1,7,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
		// ¼ì²â²¦Âë°´¼ü
		if(1){
			sprintf(txt,"add %f",(float)Change_cut);
			FTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
			Cut_down_len += Change_cut;
		}
		else if(2){
			sprintf(txt,"sub %f",(float)Change_cut);
			FTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
			Cut_down_len -= Change_cut;		
		}
		else if(3){
			sprintf(txt,"reback");
			FTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
			return 1;
		}
		else if(4){
			sprintf(txt,"finished");
			FTSPI_P8X16Str(1,8,txt,u16WHITE,u16BLACK);		//×Ö·û´®ÏÔÊ¾
			return 2;
		}
	}
	return 0;
}
void Test_terminal(void){
	// ÏÔÊ¾ÆÁ
	TFTSPI_Init(1);         //LCD³õÊ¼»¯  0:ºáÆÁ  1£ºÊúÆÁ
	TFTSPI_CLS(u16BLACK);   //ºÚÉ«ÆÁÄ»
	// ×¼±¸ÔËÐÐÖÕ¶Ë
	Print_Cmd();
	uint32_t state = 0;
	while(1){
		// ¼ì²â²¦Âë¿ª¹Ø×´Ì¬
		if(1){
			state = Change_obacle_length();
			if(state == 1){//
				Print_Cmd();
			}
			else if(state == 2){
				break;
			}
		}
		else if(2){
			state = Change_kp_();
			if(state == 1){//
				Print_Cmd();
			}
			else if(state == 2){
				break;
			}
		}
		else if(3){
			state = Change_cut_down_len();
			if(state == 1){//
				Print_Cmd();
			}
			else if(state == 2){
				break;
			}
		}
		else if(4){
			//
		}
	}

}
