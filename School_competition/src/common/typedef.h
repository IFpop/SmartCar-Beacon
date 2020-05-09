/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2013 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
***************************************************************************
*
* THIS SOFTWARE IS PROVIDED BY FREESCALE "AS IS" AND ANY EXPRESSED OR
* IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL FREESCALE OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
* INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
* IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
* THE POSSIBILITY OF SUCH DAMAGE.
*
***************************************************************************//*!
*
* @file typedef.h
*
* @author Freescale
*
* @version 0.0.1
*
* @date Jun. 25, 2013
*
* @brief provide some type definitions which are not CMSIS style. 
*
*******************************************************************************/

#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	s8
#define s8		char
#endif
#ifndef	u8
#define u8		unsigned char
#endif
#ifndef	s16
#define s16		short
#endif
#ifndef	u16
#define u16		unsigned short
#endif
#ifndef	s32
#define s32		long
#endif
#ifndef	u32
#define u32		unsigned long
#endif
#ifndef	sint
#define sint		int
#endif
#ifndef	uint
#define uint		unsigned int
#endif
#ifndef	s64
#define s64		long long
#endif
#ifndef	u64
#define u64		unsigned long long
#endif

#ifdef __cplusplus 
} 
#endif 

#endif	/* __TYPEDEF_H__ */