#ifndef ___LOGGER_H_
#define ___LOGGER_H_

#include <string.h>

#define LOGGER_PRI_ERR 		5
#define LOGGER_PRI_WARN 	4
#define LOGGER_PRI_INFO 	3
#define LOGGER_PRI_DBG 		2
#define LOGGER_PRI_TRC		1

#define LOGGER_PRI_SET      0

extern void logger_message(const char* fmt, ...);

#define LOGGER_ERR(fmt , args...)	\
	if(1){	if( LOGGER_PRI_ERR > LOGGER_PRI_SET ) 		logger_message(fmt, ##args) ; }
#define LOGGER_WARN(fmt, args...)		\
	if(1){ if( LOGGER_PRI_WARN > LOGGER_PRI_SET )  	logger_message(fmt , ##args);  }
#define LOGGER_INFO(fmt , args...)	\
	if(1){ if( LOGGER_PRI_INFO  > LOGGER_PRI_SET ) 	logger_message(fmt , ##args); } 
#define LOGGER_DBG(fmt , args...)	\
	if(1){ if( LOGGER_PRI_DBG > LOGGER_PRI_SET ) 		logger_message(fmt , ##args); } 
#define LOGGER_TRC(fmt,args...) 		\
	if(1){ if( LOGGER_PRI_TRC > LOGGER_PRI_SET ) 		logger_message(fmt ,## args); } 


#endif
