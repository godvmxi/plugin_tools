#include <assert.h>
#include "logger.h"
#include <stdio.h>


void logger_message( const char *fmt , ...)
{
	va_list ap;
	char buf[128];
	//assert(log_category != NULL);

	va_start(ap, fmt);
	vsprintf((char *)buf,(const char *)fmt,ap);
	//log4c_category_vlog(log_category , priority , fmt , ap);
	va_end(ap);
	printf("%s",buf);
}

