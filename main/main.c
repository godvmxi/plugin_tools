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
#include "netutils.h"


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s hostname\n", argv[1]);
		exit(1);
	}

	printf(">>>>>>\n");
	char ipResult[200] = {0};
	int number = get_ip_list_from_domain(argv[1],ipResult,4,20);


	exit(0);
}
