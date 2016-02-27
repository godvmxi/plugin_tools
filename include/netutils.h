#ifndef __NETUTILS_H__
#define __NETUTILS_H__
#include "debug.h"

int  netutils_dns_resolver(char *domain,char *ip_list,int max_ret_ip,int max_len_ip);

int netutils_is_valid_ip_addr(char *buf);

#define NETUTILS_MAX_DOMAIN_LEN  64
#define NETUTIIS_MAX_IP_PER_DOMAIN 6
#define NETUTILS_MAX_IP_LEN      20
typedef struct {
		int ip_flag; //if set ,the info just contain ip address ,no domain info
		char domain[NETUTILS_MAX_DOMAIN_LEN];
		int  tcp_port ;
		int  udp_port ;
		int  cur_ip ;
		int  ip_list_number;
		char ip_list[NETUTIIS_MAX_IP_PER_DOMAIN][NETUTILS_MAX_IP_LEN];

}DnsAddressInfo;



#endif
