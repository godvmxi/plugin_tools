#ifndef ___LOGGER_H_
#define ___LOGGER_H_

#include <string.h>
#include <stdarg.h>

#define LOGGER_PRI_ERR 		5
#define LOGGER_PRI_WARN 	4
#define LOGGER_PRI_INFO 	3
#define LOGGER_PRI_DBG 		2
#define LOGGER_PRI_TRC		1

#define LOGGER_PRI_SET      4

extern void logger_message(const char* fmt, ...);
extern void LOGGER_ERR(const char*fmt ,...);
extern void LOGGER_WARN(const char*fmt ,...);
extern void LOGGER_INFO(const char*fmt ,...);
extern void LOGGER_DBG(const char*fmt ,...);
extern void LOGGER_TRC(const char*fmt ,...);
#endif
