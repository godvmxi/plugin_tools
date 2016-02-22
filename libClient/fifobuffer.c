/*
 * fifo.c
 *
 *  Created on: 2016-2-22
 *      Author: dan
 */
#include "fifobuffer.h"

int fifo_buffer_init(FIFO_BUFFER_HEADER *header ,int max_size)
{
		header->cur_size = 0;
		header->first = NULL;
		header->max_size = max_size ;
		pthread_mutex_init(&header->rw_lock,NULL);

}
int fifo_buffer_put(FIFO_BUFFER_HEADER *header ,char *buf,int buf_size){
	int ret = 0;
	pthread_mutex_lock(&header->rw_lock);
	if (header->cur_size <  header->max_size){
		FIFO_BUFFER_NODE_POINT  p =  (FIFO_BUFFER_NODE_POINT)malloc(sizeof(struct FIFO_BUFFER_NODE)) ;
		memset(p,0,sizeof(struct FIFO_BUFFER_NODE));
		memcpy(p->buf,buf,buf_size);
		p->buf_size = buf_size;
		header->cur_size++;
		header->last->next= p;
		header->last = p;
		ret =  0 ;
	}
	else{
		ret = -1;
	}

	pthread_metex_unlock(&header->rw_lock);
	return ret ;
}
int fifo_buffer_get(FIFO_BUFFER_HEADER *header ,char *buf,int *buf_size){
	pthread_mutex_lock(&header->rw_lock);
	if (header->cur_size >  0 ){
		FIFO_BUFFER_NODE_POINT  p = header->first ;
		memcpy(buf,p->buf,p->buf_size);
		*buf_size = p->buf_size;
		header->first =  p->next;
		free(p);
		header->cur_size--;
		return 0;
	}
	else {
		return -1;
	}

	pthread_metex_unlock(&header->rw_lock);
}
int fifo_buffet_get_size(FIFO_BUFFER_HEADER *header){
	int ret =  0;
	pthread_mutex_lock(&header->rw_lock);

	ret =  header->cur_size;
	pthread_metex_unlock(&header->rw_lock);
	return ret;
}
