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
extern void LOGGGER_ERR(const char*fmt ,...);
extern void LOGGGER_WARN(const char*fmt ,...);
extern void LOGGGER_INFO(const char*fmt ,...);
extern void LOGGGER_DBG(const char*fmt ,...);
extern void LOGGGER_TRC(const char*fmt ,...);
#endif
