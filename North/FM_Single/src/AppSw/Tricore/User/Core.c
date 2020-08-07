/*
 * Core.c
 *
 *  Created on: 2020年7月15日
 *      Author: IFpop
 */

#include "include.h"
#include <Ifx_FftF32.h>
#include <LQ_FFT.h>

//软件fft
__attribute__ ((aligned(256))) cfloat32 Out1[1024];
__attribute__ ((aligned(256))) cfloat32 Out2[2048];
__attribute__ ((aligned(256))) cfloat32 Out3[2048];
__attribute__ ((aligned(256))) cfloat32 Out4[2048];
__attribute__ ((aligned(256))) cfloat32 In1[2048];
__attribute__ ((aligned(256))) cfloat32 In2[1024];
__attribute__ ((aligned(256))) cfloat32 In3[1024];
__attribute__ ((aligned(256))) cfloat32 In4[1024];


void prodatsfft(int16_t* acorIndex,int16_t * Data1, int16_t * Data2,int16_t * Data3,int16_t * Data4, uint16_t L){
	uint16_t  i = 0,j = 0;
//	uint16_t  nL = 2*L;
	float maxvalue[3] = {0.0,0.0,0.0};
//	float abs_H = 0.0;
	// 后部分置0
	for(i = 0 ; i < L ; i++){
		In1[i].real = Data1[i];
		In1[i].imag = 0;
		In2[i].real = Data2[i];
		In2[i].imag = 0;
		In3[i].real = Data3[i];
		In3[i].imag = 0;
		In4[i].real = Data4[i];
		In4[i].imag = 0;
	}

	Ifx_FftF32_radix2(Out1, In1, L);
	Ifx_FftF32_radix2(Out2, In2, L);
	Ifx_FftF32_radix2(Out3, In3, L);
	Ifx_FftF32_radix2(Out4, In4, L);
	//计算
//	for(i = 0 ; i < nL ; i++){
	for(i = 0 ; i < L ; i++){
		Out2[i].imag = -Out2[i].imag;
		In2[i].real = Out1[i].real*Out2[i].real-Out1[i].imag*Out2[i].imag;
		In2[i].imag = Out1[i].imag*Out2[i].real+Out1[i].real*Out2[i].imag;

		Out3[i].imag = -Out3[i].imag;
		In3[i].real = Out1[i].real*Out3[i].real-Out1[i].imag*Out3[i].imag;
		In3[i].imag = Out1[i].imag*Out3[i].real+Out1[i].real*Out3[i].imag;

		Out4[i].imag = -Out4[i].imag;
		In4[i].real = Out1[i].real*Out4[i].real-Out1[i].imag*Out4[i].imag;
		In4[i].imag = Out1[i].imag*Out4[i].real+Out1[i].real*Out4[i].imag;

	}


	Ifx_FftF32_radix2I(Out2, In2, L);
	Ifx_FftF32_radix2I(Out3, In3, L);
	Ifx_FftF32_radix2I(Out4, In4, L);
	for(i = 0 ; i < L ; i++){//不需要从头到尾找最值 最值只可能出现在尾部500cm/332.3*10000=150.5个数据点
		if(maxvalue[0] < Out2[i].real){
			maxvalue[0] = Out2[i].real;
			acorIndex[0] = i;//用于计算S2的下标
		}
		if(maxvalue[1] < Out3[i].real){
			maxvalue[1] = Out3[i].real;
			acorIndex[1] = i;//用于计算S1的下标
		}
		if(maxvalue[2] < Out4[i].real){
			maxvalue[2] = Out4[i].real;
			acorIndex[2] = i;//用于计算S_sub的下标
		}
	}

	ANO_DT_send_int16(acorIndex[1], maxvalue[1],acorIndex[0], maxvalue[0], acorIndex[2], maxvalue[2], 1, 0);

	return;
}
