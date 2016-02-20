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
/*
int main(int argc ,char **argv) {
	printf("hello world\n");
	//log_open("<span style=\"color: rgb(51, 51, 51); line-height: 20px;\">logger</span>");
	LOG_TRACE("trace\n");
	LOG_ERROR("error\n");
	LOG_WARN("warn\n");
	LOG_NOTICE("notice\n");
	LOG_DEBUG("hello log4c!\n");
	//log_close();
	return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int  get_ip_list_from_domain(char *domain,char *ip_list,int max_ret_ip,int max_len_ip){
	struct hostent *answer;
	int i;
	char *ipstr = ip_list;
	memset(ip_list , 0, max_ret_ip * max_len_ip);
	answer = gethostbyname(domain);
	if (answer == NULL) {
		herror("gethostbyname"); //由gethostbyname自带的错误处理函数
		exit(1);
	}
	max_len_ip--;
	for (i = 0; ( (answer->h_addr_list)[i] != NULL  )|| (i == max_ret_ip ); i++) {
		inet_ntop(AF_INET, (answer->h_addr_list)[i], ipstr, 16);
		printf("%s ->%d\n", ipstr,ipstr-ip_list);
		//printf("officail name : %s\n", answer->h_name);
		ipstr+= max_len_ip;
	}
	return i+1;
}
int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s hostname\n", argv[1]);
		exit(1);
	}
	struct hostent *answer;
	int i;
	char ipstr[64];
	answer = gethostbyname(argv[1]);
	if (answer == NULL) {
		herror("gethostbyname"); //由gethostbyname自带的错误处理函数
		exit(1);
	}
	for (i = 0; (answer->h_addr_list)[i] != NULL; i++) {
		memset(ipstr,0,64);
		inet_ntop(AF_INET, (answer->h_addr_list)[i], ipstr, 16);
		printf("%s -> %s\n", (answer->h_addr_list)[i],ipstr);
		printf("officail name : %s\n", answer->h_name);
	}
	printf(">>>>>>\n");
	char ipResult[128] = {0};
	int number = get_ip_list_from_domain(argv[1],ipResult,4,20);
/*
  printf("ip number -> %d\n",number);
  for(i =0; i<number;i++){
	  printf("ip%d->%s\n",i,ipResult+(i*20));
  }
  */

	exit(0);
}
