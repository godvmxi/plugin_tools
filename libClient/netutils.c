/*
 * netutils.c

 *
 *  Created on: 2016-2-15
 *      Author: bright
 */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <stdio.h>
#include <logger.h>

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
	max_ret_ip--;
	for (i = 0; ( (answer->h_addr_list)[i] != NULL  )|| (i == max_ret_ip ); i++) {
		inet_ntop(AF_INET, (answer->h_addr_list)[i], ipstr, 16);
		printf("%s ->%d\n", ipstr,ipstr-ip_list);
		ipstr+= max_len_ip;
	}
	return i+1;
}

