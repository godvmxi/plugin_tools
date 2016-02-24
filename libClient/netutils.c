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
#include <arpa/inet.h>

int  netutils_dns_resolver(char *domain,char *ip_list,int max_ret_ip,int max_len_ip){
	struct hostent *answer;
	int i;
	char *ipstr = ip_list;
	memset(ip_list , 0, max_ret_ip * max_len_ip);
	answer = gethostbyname(domain);
	if (answer == NULL) {
		LOG_ERROR("gethostbyname error \n"); //由gethostbyname自带的错误处理函数
		exit(1);
	}
	max_ret_ip--;
	for (i = 0; ( (answer->h_addr_list)[i] != NULL  )|| (i == max_ret_ip ); i++) {
		inet_ntop(AF_INET, (answer->h_addr_list)[i], ipstr, 16);
		printf("dns-> %s ->%ld\n", ipstr,ipstr-ip_list);
		ipstr+= max_len_ip;
	}
	return i;
}

int netutils_is_valid_ip_addr(char *buf){
	int n[4];
	char c[4];
	char *p = buf ;
	if (sscanf(p, "%d%c%d%c%d%c%d%c",
				&n[0], &c[0], &n[1], &c[1],
				&n[2], &c[2], &n[3], &c[3])
			== 7)
	{
		int i;
		for(i = 0; i < 3; ++i)
			if (c[i] != '.')
				return 0;
		for(i = 0; i < 4; ++i)
			if (n[i] > 255 || n[i] < 0)
				return 0;
		return 0;
	} else
		return -1;
}
