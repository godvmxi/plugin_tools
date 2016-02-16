/*
 ============================================================================
 Name        : exampleProgram.c
 Author      : Bright Jiang
 Version     :
 Copyright   : GPL
 Description : Uses shared library to print greeting
               To run the resulting executable the LD_LIBRARY_PATH must be
               set to ${project_loc}/libClient/.libs
               Alternatively, libtool creates a wrapper shell script in the
               build directory of this program which can be used to run it.
               Here the script will be called exampleProgram.
 ============================================================================
 */
#include <jansson.h>
#include "libClient.h"
#include "stdio.h"
#include "logger.h"

int main(int argc ,char **argv) {

	log_open("<span style=\"color: rgb(51, 51, 51); line-height: 20px;\">logger</span>");
	LOG_TRACE("trace");
	LOG_ERROR("error");
	LOG_WARN("warn");
	LOG_NOTICE("notice");
	LOG_DEBUG("hello log4c!");
	log_close();
	return 0;
}
