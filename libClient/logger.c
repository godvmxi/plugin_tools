#include "logger.h"
#include <stdio.h>


void logger_message( const char *fmt , ...)
{
	va_list ap;
	char buf[256];
	//assert(log_category != NULL);

	va_start(ap, fmt);
	vsprintf((char *)buf,(const char *)fmt,ap);
	//log4c_category_vlog(log_category , priority , fmt , ap);
	va_end(ap);
	printf("%s",buf);
}

void LOGGGER_ERR(const char*fmt ,...){
	va_list ap;
	char buf[256];
	//assert(log_category != NULL);

	va_start(ap, fmt);
	vsprintf((char *)buf,(const char *)fmt,ap);
	//log4c_category_vlog(log_category , priority , fmt , ap);
	va_end(ap);
	printf("%s",buf);

}
void LOGGGER_WARN(const char*fmt ,...){
	va_list ap;
	char buf[256];
	//assert(log_category != NULL);

	va_start(ap, fmt);
	vsprintf((char *)buf,(const char *)fmt,ap);
	//log4c_category_vlog(log_category , priority , fmt , ap);
	va_end(ap);
	printf("%s",buf);

}
void LOGGGER_INFO(const char*fmt ,...){
	va_list ap;
	char buf[256];
	//assert(log_category != NULL);

	va_start(ap, fmt);
	vsprintf((char *)buf,(const char *)fmt,ap);
	//log4c_category_vlog(log_category , priority , fmt , ap);
	va_end(ap);
	printf("%s",buf);

}
void LOGGGER_DBG(const char*fmt ,...) {
	va_list ap;
	char buf[256];
	//assert(log_category != NULL);

	va_start(ap, fmt);
	vsprintf((char *)buf,(const char *)fmt,ap);
	//log4c_category_vlog(log_category , priority , fmt , ap);
	va_end(ap);
	printf("%s",buf);

}
void LOGGGER_TRC(const char*fmt ,...) {
	va_list ap;
	char buf[256];
	//assert(log_category != NULL);

	va_start(ap, fmt);
	vsprintf((char *)buf,(const char *)fmt,ap);
	//log4c_category_vlog(log_category , priority , fmt , ap);
	va_end(ap);
	printf("%s",buf);

}
