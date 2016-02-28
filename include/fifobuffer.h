/*
 * fifo.h
 *
 *  Created on: 2016-2-22
 *      Author: dan
 */
#include <pthread.h>
#include <stdlib.h>
#ifndef __FIFO_BUFFER_H_
#define __FIFO_BUFFER_H_
#define  MAX_FIFO_BUF_SIZE  512
#include "debug.h"

typedef struct FIFO_BUFFER_NODE *FIFO_BUFFER_NODE_POINT ;
struct FIFO_BUFFER_NODE{
		int ID ;//json cmd ID
		int dat_size ;
		char buf[MAX_FIFO_BUF_SIZE] ;
		FIFO_BUFFER_NODE_POINT next;
} ;

typedef struct {
		pthread_mutex_t rw_lock ;
		int cur_size ;
		int max_size;
		FIFO_BUFFER_NODE_POINT in ;
		FIFO_BUFFER_NODE_POINT out;
}FIFO_BUFFER_HEADER;

int fifo_buffer_init(FIFO_BUFFER_HEADER *header , int max_size);
int fifo_buffer_put(FIFO_BUFFER_HEADER *header ,char *buf,int buf_size);
int fifo_buffer_get(FIFO_BUFFER_HEADER *header ,char *buf,int *buf_size);
int fifo_buffet_get_size(FIFO_BUFFER_HEADER *header);
#endif /* FIFO_H_ */
