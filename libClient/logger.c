#include "logger.h"
#include <stdio.h>
#define LOGGER_MAX_BUFFER  2048

void logger_message( const char *fmt , ...)
{
	va_list ap;
	char buf[2048];
	//assert(log_category != NULL);

	va_start(ap, fmt);
	vsprintf((char *)buf,(const char *)fmt,ap);
	//log4c_category_vlog(log_category , priority , fmt , ap);
	va_end(ap);
	printf("%s",buf);
}

void LOGGER_ERR(const char*fmt ,...){
	if(LOGGER_PRI_ERR < LOGGER_PRI_SET){
		return ;
	}
	va_list ap;
	char buf[2048];
	//assert(log_category != NULL);

	va_start(ap, fmt);
	vsprintf((char *)buf,(const char *)fmt,ap);
	//log4c_category_vlog(log_category , priority , fmt , ap);
	va_end(ap);
	printf("%s",buf);

}
void LOGGER_WARN(const char*fmt ,...){
	if(LOGGER_PRI_WARN < LOGGER_PRI_SET){
		return ;
	}
	va_list ap;
	char buf[2048];
	//assert(log_category != NULL);

	va_start(ap, fmt);
	vsprintf((char *)buf,(const char *)fmt,ap);
	//log4c_category_vlog(log_category , priority , fmt , ap);
	va_end(ap);
	printf("%s",buf);

}
void LOGGER_INFO(const char*fmt ,...){
	if(LOGGER_PRI_INFO < LOGGER_PRI_SET){
		return ;
	}
	va_list ap;
	char buf[2048];
	//assert(log_category != NULL);

	va_start(ap, fmt);
	vsprintf((char *)buf,(const char *)fmt,ap);
	//log4c_category_vlog(log_category , priority , fmt , ap);
	va_end(ap);
	printf("%s",buf);

}
void LOGGER_DBG(const char*fmt ,...) {
	if(LOGGER_PRI_DBG < LOGGER_PRI_SET){
		return ;
	}
	va_list ap;
	char buf[2048];
	//assert(log_category != NULL);

	va_start(ap, fmt);
	vsprintf((char *)buf,(const char *)fmt,ap);
	//log4c_category_vlog(log_category , priority , fmt , ap);
	va_end(ap);
	printf("%s",buf);

}
void LOGGER_TRC(const char*fmt ,...) {
	if(LOGGER_PRI_TRC < LOGGER_PRI_SET){
		return ;
	}
	va_list ap;
	char buf[2048];
	//assert(log_category != NULL);

	va_start(ap, fmt);
	vsprintf((char *)buf,(const char *)fmt,ap);
	//log4c_category_vlog(log_category , priority , fmt , ap);
	va_end(ap);
	printf("%s",buf);

}
