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
* @file queue.c
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

#include "common.h"
#include "queue.h"

/********************************************************************/
/* 
 * Initialize the specified queue to an empty state
 * 
 * Parameters:
 *  q   Pointer to queue structure
 */
void
queue_init(QUEUE *q)
{
    q->head = NULL;
}
/********************************************************************/
/* 
 * Check for an empty queue
 *
 * Parameters:
 *  q       Pointer to queue structure
 * 
 * Return Value:
 *  1 if Queue is empty
 *  0 otherwise
 */
int
queue_isempty(QUEUE *q)
{
    return (q->head == NULL);
}
/********************************************************************/
/* 
 * Add an item to the end of the queue 
 *
 * Parameters:
 *  q       Pointer to queue structure
 *  node    New node to add to the queue
 */
void
queue_add(QUEUE *q, QNODE *node)
{
    if (queue_isempty(q))
    {
        q->head = q->tail = node;
    }
    else
    {
        q->tail->next = node;
        q->tail = node;
    }
    
    node->next = NULL;
}

/********************************************************************/
/* 
 * Remove and return first (oldest) entry from the specified queue 
 *
 * Parameters:
 *  q       Pointer to queue structure
 *
 * Return Value:
 *  Node at head of queue - NULL if queue is empty
 */
QNODE*
queue_remove(QUEUE *q)
{
    QNODE *oldest;
    
    if (queue_isempty(q))
        return NULL;
    
    oldest = q->head;
    q->head = oldest->next;
    return oldest;
}
/********************************************************************/
/* 
 * Peek into the queue and return pointer to first (oldest) entry.
 * The queue is not modified
 *
 * Parameters:
 *  q       Pointer to queue structure
 *
 * Return Value:
 *  Node at head of queue - NULL if queue is empty
 */
QNODE*
queue_peek(QUEUE *q)
{
    return q->head;
}
/********************************************************************/
/* 
 * Move entire contents of one queue to the other
 *
 * Parameters:
 *  src     Pointer to source queue
 *  dst     Pointer to destination queue
 */
void
queue_move(QUEUE *dst, QUEUE *src)
{
    if (queue_isempty(src))
        return;
    
    if (queue_isempty(dst))
        dst->head = src->head;
    else
        dst->tail->next = src->head;

    dst->tail = src->tail;
    src->head = NULL;
    return;
}
/********************************************************************/
