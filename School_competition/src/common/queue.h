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
* @file queue.h
*
* @author Freescale
*
* @version 0.0.1
*
* @date Jun. 25, 2013
*
* @brief Implement a first in, first out linked list. 
*
*******************************************************************************/

#ifndef _QUEUE_H_
#define _QUEUE_H_

/********************************************************************/

/* 
 * Individual queue node
 */
typedef struct NODE
{
    struct NODE *next;
} QNODE;

/* 
 * Queue Struture - linked list of qentry items 
 */
typedef struct
{
    QNODE *head;
    QNODE *tail;
} QUEUE;

/*
 * Functions provided by queue.c
 */
void
queue_init(QUEUE *);

int
queue_isempty(QUEUE *);

void
queue_add(QUEUE *, QNODE *);

QNODE*
queue_remove(QUEUE *);

QNODE*
queue_peek(QUEUE *);

void
queue_move(QUEUE *, QUEUE *);

/********************************************************************/

#endif /* _QUEUE_H_ */
