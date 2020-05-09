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
* @file stdlib.h
*
* @author Freescale
*
* @version 0.0.1
*
* @date Jun. 25, 2013
*
* @brief Implement some basic functions normally found in a standard C lib. 
*
*******************************************************************************/

#ifndef _STDLIB_H
#define _STDLIB_H

/********************************************************************
 * Standard library functions
 ********************************************************************/

int
isspace (int);

int
isalnum (int);

int
isdigit (int);

int
isupper (int);

int
strcasecmp (const char *, const char *);

int
strncasecmp (const char *, const char *, int);

unsigned long
strtoul (char *, char **, int);

//int
//strlen (const char *);

char *
strcat (char *, const char *);

//char *
//strncat (char *, const char *, int);

char *
strcpy (char *, const char *);

//char *
//strncpy (char *, const char *, int );

int
strcmp (const char *, const char *);

//int
//strncmp (const char *, const char *, int);

void *
memcpy (void *, const void *, unsigned);

void *
memset (void *, int, unsigned);

void
free (void *);
 
void *
malloc (unsigned);

int
strlen (const char *str);

/********************************************************************/

#endif
