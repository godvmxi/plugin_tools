/*
 * fifo.c
 *
 *  Created on: 2016-2-22
 *      Author: dan
 */
#include "fifobuffer.h"
#include <string.h>
#include <pthread.h>

int fifo_buffer_init(FIFO_BUFFER_HEADER *header ,int max_size)
{
		header->cur_size = 0;
		header->in= NULL;
		header->out = NULL;
		header->max_size = max_size ;
		pthread_mutex_init(&header->rw_lock,NULL);

}
int fifo_buffer_put(FIFO_BUFFER_HEADER *header ,char *buf,int dat_size){
	int ret = 0;
	FIFO_BUFFER_NODE_POINT  p =  NULL ;
	printf("header -> %d  %d\n",sizeof(FIFO_BUFFER_NODE_POINT),sizeof(struct FIFO_BUFFER_NODE));
	pthread_mutex_lock(&header->rw_lock);
	if (header->cur_size <=  header->max_size){
		p =  (FIFO_BUFFER_NODE_POINT)malloc(sizeof(struct FIFO_BUFFER_NODE)) ;
		memset(p,0,sizeof(struct FIFO_BUFFER_NODE) );
		if(p == NULL ){
			ret = -1 ;
		}
		else {
			//	printf("maloc ->%p\n",p);
			header->cur_size++;
			if (header->cur_size ==  1 ) //innode will be added
			{
				header->in=  p ;
				header->out =  p ;
				p->next = NULL ;
			}
			else {
				p->next == NULL;
				FIFO_BUFFER_NODE_POINT q  = header->in ;
				q->next = p ;
				header->in = p  ;
				q->next  = p;
			}
		}
		//	printf("will store %p %p  %d \n",p->buf ,buf,dat_size);
		if ( dat_size  > MAX_FIFO_BUF_SIZE ) {
			ret = -1 ;
		}
		else {
			memcpy(header->in->buf,buf,dat_size);
			header->in->dat_size = dat_size;
			//		printf(" put ok\n");
			ret =  0 ;
		}
	}
	else{
		printf("fifo is full\n");
		ret = -1;
	}
	printf("fifo size -> %d  :   %d\n",header->cur_size,ret);
	if (ret == 0 ){
		p =  header->out;
		while(p ){
			printf("fifo dat ->%d  %s\n",p->dat_size,p->buf);
			p = p->next ;
			if (p == NULL){
				break;
			}
		}
	}
	pthread_mutex_unlock(&header->rw_lock);
	return ret ;
}
int fifo_buffer_get(FIFO_BUFFER_HEADER *header ,char *buf,int *dat_size){
	int ret = 0 ;
//	printf("get start -> %d %s\n",header->cur_size,header->out->buf);
	FIFO_BUFFER_NODE_POINT  p = header->out;
	FIFO_BUFFER_NODE_POINT  sav = header->out;
	pthread_mutex_lock(&header->rw_lock);
	if (header->cur_size >  0 ){
		header->cur_size--;
		memcpy(buf,p->buf,p->dat_size);
		*dat_size = p->dat_size;

		if (header->cur_size == 0 ){
			header->in= NULL;
			header->out = NULL;
		}
		else {
			header->out= p->next ;
		}
		if (sav) {
			printf("try free-> 0x%p\n",sav);
		//	free(sav);
		}
		ret = 0;
	}
	else {
		ret = -1;
	}

	pthread_mutex_unlock(&header->rw_lock);
	return ret ;
}
int fifo_buffet_get_size(FIFO_BUFFER_HEADER *header){
	int ret =  0;
	pthread_mutex_lock(&header->rw_lock);

	ret =  header->cur_size;
	pthread_mutex_unlock(&header->rw_lock);
	return ret;
}
