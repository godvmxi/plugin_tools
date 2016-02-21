#ifndef __NETUTILS_H__
#define __NETUTILS_H__


int  get_ip_list_from_domain(char *domain,char *ip_list,int max_ret_ip,int max_len_ip);

#define MAX_DOMAIN_LEN  64
#define MAX_IP_PER_DOMAIN 6
#define MAX_IP_LEN      20
typedef struct {
		char domain[MAX_DOMAIN_LEN];
		int  tcp_port ;
		int  udp_port ;
		int  cur_ip ;
		int  ip_list_number;
		char ip_list[MAX_IP_PER_DOMAIN][MAX_IP_LEN];

}DnsAddressInfo;


#endif
