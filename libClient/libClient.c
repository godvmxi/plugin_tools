#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <netutils.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <sys/select.h>
#include "sysutils.h"
#include "libClient.h"
#include "logger.h"
#include <string.h>
#include "sysutils.h"
#include "fifobuffer.h"
#include <time.h>

#define   DEBUG_FLOW_CONTROL  0

AppFunctionFlowCtrl app_function_flow_ctrl;
AppDomainInfo app_domain_info;
AppSecurityInfo app_security_info;

FIFO_BUFFER_HEADER socket_rx_fifo_header;
FIFO_BUFFER_HEADER socket_tx_fifo_header;
FIFO_BUFFER_HEADER plugins_control_down_link_header;
FIFO_BUFFER_HEADER plugins_control_ack_fifo_header;
FIFO_BUFFER_HEADER system_report_fifo_header;
FIFO_BUFFER_HEADER system_report_ack_fifo_header;
AppMessageWaitAckInfo app_message_wait_ack_info ;



AppSocketLoopExitEvent  app_socket_loop_exit_event  = ExitEventNone ;

int app_login_distri_server_retry_interval = 30;
int app_login_operate_server_retry_interval = 60;
int app_login_operate_server_heartbeat_interval = 60;
int app_socket_working_state =  1;
int app_theard_exit_flag = 0;
#define APP_DEFAULT_FIFO_BUFFER_SIZE   10

void get_version(void ) {
	printf("version 0.1\n");
}

void app_function_fifo_buffer_init(void) {
	fifo_buffer_init(&socket_rx_fifo_header, APP_DEFAULT_FIFO_BUFFER_SIZE);
	fifo_buffer_init(&socket_tx_fifo_header, APP_DEFAULT_FIFO_BUFFER_SIZE);
	fifo_buffer_init(&plugins_control_down_link_header, APP_DEFAULT_FIFO_BUFFER_SIZE);
	fifo_buffer_init(&plugins_control_ack_fifo_header, APP_DEFAULT_FIFO_BUFFER_SIZE);
	fifo_buffer_init(&system_report_fifo_header, APP_DEFAULT_FIFO_BUFFER_SIZE);
	fifo_buffer_init(&system_report_ack_fifo_header, APP_DEFAULT_FIFO_BUFFER_SIZE);
	memset(&app_message_wait_ack_info,0,sizeof(AppMessageWaitAckInfo) );
}
int manual_interactive_flow_control(const char *info) {
	char input[64];
	int ret = 0;
	printf("Input choice  << %s >>--> ", info);
	int temp = scanf("%d", &ret);
	printf("\n you input value -> %d   %d\n", ret,temp);
	return ret;
}
int login_distri_plat_step1_udp(void *dat) {
	LOGGER_TRC("%s\n", __FUNCTION__);
//	return RET_NO_ACK ;
	int ret = 0;
#if DEBUG_FLOW_CONTROL == 1
	ret = manual_interactive_flow_control(__FUNCTION__);
	return ret;
#endif
	int dns_retry_counter = 0 ;
	char *dns = app_domain_info.distri_server.domain;
	char *ip_list = app_domain_info.distri_server.ip_list[0];
	int ip_num  = 0;
	while (1) {
		ip_num = netutils_dns_resolver(dns, ip_list, NETUTIIS_MAX_IP_PER_DOMAIN, NETUTILS_MAX_IP_LEN);
		LOGGER_DBG("dns resolver result -> %d\n", ip_num);
		if (ip_num <= 0 ){
			LOGGER_ERR("distri_server dns failed,sleep and retry\n");
			sleep(app_login_distri_server_retry_interval);
			return RET_DNS_FAILED ;
		}
		else {
			break;
		}
	}
	app_domain_info.distri_server.cur_ip = 0;
	app_domain_info.distri_server.ip_list_number = ip_num;
	int cur_ip_index = 0;

	int socket_descriptor;
	int iter = 0;

	int send_counter = 0;
	struct sockaddr_in address;
	char buf[1024] = { 0 };
	uint32_t recv_json_len;
	fd_set rdfds;
	struct timeval tv;

	while (1) {
		LOGGER_TRC("begin try ip -> %s %d \n",
				app_domain_info.distri_server.ip_list[cur_ip_index],
				app_domain_info.distri_server.udp_port
				);
		if (cur_ip_index >= ip_num) {
			LOGGER_DBG("no valid ip can be used\n");
			return RET_NO_ACK;
		}
		bzero(&address, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr(app_domain_info.distri_server.ip_list[cur_ip_index]);
		address.sin_port = htons(app_domain_info.distri_server.udp_port);
		//create socket
		if (socket_descriptor > 0) {
			close(socket_descriptor);
			socket_descriptor =  -1;
		}
		socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);

		memset(buf, 0, 1024);
		sysutils_get_json_rpc_boot_first(buf + 4);
		if(ret < 0 ){
			LOGGER_ERR("get rpc boot first_json error \n");
			return RET_SYS_ERROR ;
		}
		LOGGER_DBG("json->%s\n", buf + 4);
		uint32_t buf_len = strlen(buf + 4);
		uint32_t *json_len = (uint32_t *) buf;
		*json_len = htons(buf_len);
		LOGGER_DBG("send -> %d ->%s\n", json_len, buf + 4);
		sendto(socket_descriptor, buf, buf_len + 4, 0, (struct sockaddr *) &address, sizeof(address));
		int recv_counter = 0;
		FD_ZERO(&rdfds);
		FD_SET(socket_descriptor, &rdfds);
		tv.tv_sec = 15;
		tv.tv_usec = 500;
		ret = select(socket_descriptor + 1, &rdfds, NULL, NULL, &tv);
		if (ret == 0) {
			LOGGER_DBG("no data and timeout\n");
			recv_counter++;
			sleep(app_login_distri_server_retry_interval);
			continue;
		}
		if (ret < 0)
			perror("select");/* 这说明select函数出错 */
		else if (ret == 0) {
			//have been handler before ,never run to here
			printf("no data and timeout\n");
		}

		else { /* 说明等待时间还未到1秒加500毫秒，socket的状态发生了变化 */
			printf("ret=%d\n", ret); /* if ret>1，more handler changed  */

			if (FD_ISSET(socket_descriptor, &rdfds)) {
				/* read data */
				memset(buf, 0, 1024);
				buf_len = recv(socket_descriptor, buf, 1024, 0);
				if (buf_len < 0) {
					LOGGER_DBG("receive data error -> %d\n", buf_len);
					send_counter++;
					continue;
				}
				recv_json_len = ntohl(  *( (uint32_t *)  buf) );
				LOGGER_DBG("receive data -> %d -> %s\n", recv_json_len, buf );
				if (recv_json_len != (buf_len - 4)) {
					LOGGER_ERR("receive data len not match -> %d %d\n", recv_json_len, buf_len);
					send_counter++;
#ifdef  DISTRI_SERVER_ERROR_PROTOCOL_DEBUG
					LOGGER_DBG("just ignore server error ,continue \n");
#else 
					sleep(3);
					continue;
#endif 
				}

				send_counter = 0;
				int result = -1;
				int interval_temp = 0;
				char challenge_code[64] = { 0 };
				char server_ip[20] = { 0 };
#ifdef  DISTRI_SERVER_ERROR_PROTOCOL_DEBUG
				ret = sysutils_parse_distri_server_ack_step_1(buf, &result, challenge_code, &interval_temp, server_ip);
#else 
				ret = sysutils_parse_distri_server_ack_step_1(buf+4, &result, challenge_code, &interval_temp, server_ip);
#endif
				if (ret == 0) {
					if (result == 0) {
						app_login_distri_server_retry_interval = interval_temp;
						memset(app_security_info.challenge_code, 0, 16) ;
						memcpy(app_security_info.challenge_code, challenge_code, 16);
						LOGGER_DBG("boot first registe ok ,continue \n");
						//server_ip is the wlan ip ,do not care it .

						return RET_OK;
					} else {
						LOGGER_ERR("Boot first reigister failed \n");
						sleep(app_login_distri_server_retry_interval * 1000);
					}
				}
				else{
					LOGGER_ERR("parse ack info error \n");
					send_counter++;
					sleep(app_login_distri_server_retry_interval * 1000);
					continue;
				}

			}

		}
	}
return ret;
}

int login_distri_plat_step2_udp(void *dat) {
	LOGGER_TRC("%s\n", __FUNCTION__);
	int ret = 0;
#if DEBUG_FLOW_CONTROL == 1
	ret = manual_interactive_flow_control(__FUNCTION__);sysutils_get_json_rpc_message_push
		return ret;
#endif
	int socket_descriptor;
	int iter = 0;

	int send_counter = 0;
	struct sockaddr_in address;
	char buf[1024] = { 0 };
	uint32_t recv_json_len;
	fd_set rdfds;
	struct timeval tv;
	char *ip  =  app_domain_info.distri_server.ip_list[app_domain_info.distri_server.cur_ip] ;
	uint32_t port = app_domain_info.distri_server.udp_port ;
	LOGGER_DBG("using ip address ->%s %d \n",ip ,port);
	while (1) { //try send 3 time with interval 
		bzero(&address, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr(ip);
		address.sin_port = htons(port);
		//create socket
		if (socket_descriptor > 0) {
			close(socket_descriptor);
			socket_descriptor =  -1;
		}
		if (send_counter >= 3 ){
			LOGGER_ERR("retry send message is over \n");
			return RET_NO_ACK ;
		}
		socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);

		memset(buf, 0, 1024);
		sysutils_get_json_rpc_register_first(buf + 4);
		printf("get register json ->%s\n ",buf);
		if(ret < 0 ){
			LOGGER_ERR("get rpc register_first json error \n");
			return RET_SYS_ERROR ;
		}
		LOGGER_DBG("json->%s\n", buf + 4);
		uint32_t buf_len = strlen(buf + 4);
		uint32_t *json_len = (uint32_t *) buf;
		*json_len = htons(buf_len);
		LOGGER_DBG("send -> %d ->%s\n", json_len, buf + 4);
		sendto(socket_descriptor, buf, buf_len + 4, 0, (struct sockaddr *) &address, sizeof(address));
		int recv_counter = 0;
		FD_ZERO(&rdfds);
		FD_SET(socket_descriptor, &rdfds);
		tv.tv_sec = 15;
		tv.tv_usec = 500;
		ret = select(socket_descriptor + 1, &rdfds, NULL, NULL, &tv);
		if (ret == 0) {
			LOGGER_DBG("no data and timeout\n");
			recv_counter++;
			if (recv_counter > 10) {
				close(socket_descriptor);
				socket_descriptor =  -1;
				LOGGER_DBG("wait for 15s and time out ,no data\n");
				LOGGER_DBG("try next ip\n");
				return RET_NO_ACK ;
			}
		}
		if (ret < 0)
			perror("select");/* 这说明select函数出错 */
		else if (ret == 0) {
			//have been handler before ,never run to here
			printf("no data and timeout\n");
		}

		else { /* 说明等待时间还未到1秒加500毫秒，socket的状态发生了变化 */
			printf("ret=%d\n", ret); /* if ret>1，more handler changed  */

			if (FD_ISSET(socket_descriptor, &rdfds)) {
				/* read data */
				memset(buf, 0, 1024);
				buf_len = recv(socket_descriptor, buf, 1024, 0);
				if (buf_len < 0) {
					LOGGER_DBG("receive data error -> %d\n", buf_len);
					send_counter++;
					continue;
				}
				recv_json_len = ntohl(  *( (uint32_t *)  buf) );
				LOGGER_DBG("receive data -> %d -> %s\n", recv_json_len, buf + 4);
				if (recv_json_len != (buf_len - 4)) {
					LOGGER_ERR("receive data len not match -> %d %d\n", recv_json_len, buf_len);
					send_counter++;
					continue;
				}

				send_counter = 0;
				int result = -1;
				char server_addr[64] ;
				memset(server_addr,0,64);
				uint32_t server_port ;
				int interval_temp = 0;
				char server_ip[20]  ;
				memset(server_ip,0,20);
				char token[64]  ;
				memset(token,0,64);
				char exp_date[64];
				memset(exp_date,0,64);
				char ca_download_url[64];
				memset(ca_download_url,0,64);
				/*
				 * 

int sysutils_parse_distri_server_ack_step_2(char *buf,
		int *result,
		char *server_addr,
		char *server_port,
		int *interval,
		char * server_ip,
		char *token,
		char *exp_date,
		char *ca_download_url)
				 *
				 *
				 *
				 */



				ret = sysutils_parse_distri_server_ack_step_2(buf, 
							&result, 
							server_addr, 
							&server_port,
							&interval_temp ,
							server_ip , //ignore this ?
							token ,
							exp_date ,
							ca_download_url  );
				if (ret == 0) {
					if (result == 0) {
						memset(&app_domain_info.operate_server , 0 ,sizeof(DnsAddressInfo) );
						app_login_distri_server_retry_interval = interval_temp;
						if (netutils_is_valid_ip_addr(server_addr) ==  0 ){
							app_domain_info.operate_server.ip_flag = 1;
							memcpy(app_domain_info.operate_server.ip_list[0],server_addr ,strlen(server_addr) ) ;
						}
						else {
							memcpy(app_domain_info.operate_server.domain,server_addr,strlen(server_addr) ) ;
						}
						app_domain_info.operate_server.tcp_port =  server_port ;
						app_domain_info.operate_server.udp_port =  server_port ;

						memcpy(app_security_info.token, token, strlen(token)) ;
						memcpy(app_security_info.exp_date, exp_date, strlen(exp_date)) ;
						memcpy(app_security_info.ca_download_url, ca_download_url, strlen(ca_download_url)) ;
						app_login_distri_server_retry_interval =  interval_temp ;
						LOGGER_DBG("boot first registe ok ,continue \n");
						//server_ip is the wlan ip ,do not care it .

						return RET_OK;
					} else {
						LOGGER_ERR("Boot first register  error,sleep and retry :%d %d \n",send_counter,app_login_distri_server_retry_interval);
						sleep(app_login_distri_server_retry_interval * 1000);
					}
				}
				else{
					LOGGER_ERR("parse ack info error,sleep and retry :%d %d \n",send_counter,app_login_distri_server_retry_interval);
					send_counter++;
					sleep(app_login_distri_server_retry_interval * 1000);
					continue;
				}

			}

		}
	}
	return ret;
}
int login_distri_plat_step1_tcp(void *dat) {
	LOGGER_TRC("%s\n", __FUNCTION__);
	int ret = 0;
#if DEBUG_FLOW_CONTROL == 1
	ret = manual_interactive_flow_control(__FUNCTION__);
	return ret;
#endif
	int dns_retry_counter = 0 ;
	char *dns = app_domain_info.distri_server.domain;
	char *ip_list = app_domain_info.distri_server.ip_list[0];
	int ip_num  = 0;
	while (1) {
		ip_num = netutils_dns_resolver(dns, ip_list, NETUTIIS_MAX_IP_PER_DOMAIN, NETUTILS_MAX_IP_LEN);
		LOGGER_DBG("dns resolver result -> %d\n", ip_num);
		if (ip_num <= 0 ){
			LOGGER_ERR("operate_server dns failed,sleep and retry\n");
			sleep(app_login_distri_server_retry_interval);
			return RET_DNS_FAILED ;
		}
		else {
			break;
		}
	}
	app_domain_info.distri_server.cur_ip = 0;
	app_domain_info.distri_server.ip_list_number = ip_num;
	int cur_ip_index = 0;

	int socket_descriptor;
	int iter = 0;

	int send_counter = 0;
	struct sockaddr_in address;
	char buf[1024] = { 0 };
	uint32_t recv_json_len;
	fd_set rdfds;
	struct timeval tv;

	while (1) {
		LOGGER_TRC("begin try ip ->\n");
		if (cur_ip_index >= ip_num) {
			LOGGER_DBG("no valid ip can be used\n");
			return RET_NO_ACK;
		}
		bzero(&address, sizeof(address));
		address.sin_family = AF_INET;
		address.sin_addr.s_addr = inet_addr(app_domain_info.distri_server.ip_list[cur_ip_index]);
		address.sin_port = htons(app_domain_info.distri_server.udp_port);
		//create socket
		if (socket_descriptor > 0) {
			close(socket_descriptor);
			socket_descriptor =  -1;
		}
		socket_descriptor = socket(AF_INET, SOCK_DGRAM, 0);

		ret = connect(socket_descriptor ,&address ,sizeof(address) );
		if (ret <   0 ){
			LOGGER_ERR("tcp connect error \n");
			close(socket_descriptor);
			sleep(app_login_distri_server_retry_interval);
			continue ;
		}
		LOGGER_TRC("connect result -> %d \n",ret);

		memset(buf, 0, 1024);
		sysutils_get_json_rpc_boot_first(buf + 4);
		if(ret < 0 ){
			LOGGER_ERR("get rpc boot first_json error \n");
			return RET_SYS_ERROR ;
		}
		LOGGER_DBG("json->%s\n", buf + 4);
		uint32_t buf_len = strlen(buf + 4);
		uint32_t *json_len = (uint32_t *) buf;
		*json_len = htons(buf_len);
		LOGGER_DBG("send -> %d ->%s\n", json_len, buf + 4);
		sendto(socket_descriptor, buf, buf_len + 4, 0, (struct sockaddr *) &address, sizeof(address));
		int recv_counter = 0;
		FD_ZERO(&rdfds);
		FD_SET(socket_descriptor, &rdfds);
		tv.tv_sec = 15;
		tv.tv_usec = 500;
		ret = select(socket_descriptor + 1, &rdfds, NULL, NULL, &tv);
		if (ret == 0) {
			LOGGER_DBG("no data and timeout\n");
			recv_counter++;
			sleep(app_login_distri_server_retry_interval);
			continue;
		}
		if (ret < 0)
			perror("select");/* 这说明select函数出错 */
		else if (ret == 0) {
			//have been handler before ,never run to here
			printf("no data and timeout\n");
		}

		else { /* 说明等待时间还未到1秒加500毫秒，socket的状态发生了变化 */
			printf("ret=%d\n", ret); /* if ret>1，more handler changed  */

			if (FD_ISSET(socket_descriptor, &rdfds)) {
				/* read data */
				memset(buf, 0, 1024);
				buf_len = recv(socket_descriptor, buf, 1024, 0);
				if (buf_len < 0) {
					LOGGER_DBG("receive data error -> %d\n", buf_len);
					send_counter++;
					continue;
				}
				recv_json_len = ntohl(  *( (uint32_t *)  buf) );
				LOGGER_DBG("receive data -> %d -> %s\n", recv_json_len, buf + 4);
				if (recv_json_len != (buf_len - 4)) {
					LOGGER_ERR("receive data len not match -> %d %d\n", recv_json_len, buf_len);
					send_counter++;
					continue;
				}

				send_counter = 0;
				int result = -1;
				int interval_temp = 0;
				char challenge_code[20] = { 0 };
				char server_ip[20] = { 0 };
				ret = sysutils_parse_distri_server_ack_step_1(buf, &result, challenge_code, &interval_temp, server_ip);
				if (ret == 0) {
					if (result == 0) {
						app_login_distri_server_retry_interval = interval_temp;
						memset(app_security_info.challenge_code, 0, 16) ;
						memcpy(app_security_info.challenge_code, challenge_code, 16);
						LOGGER_DBG("boot first registe ok ,continue \n");
						//server_ip is the wlan ip ,do not care it .

						return RET_OK;
					} else {
						LOGGER_ERR("Boot first reigister failed \n");
						sleep(app_login_distri_server_retry_interval * 1000);
					}
				}
				else{
					LOGGER_ERR("parse ack info error \n");
					send_counter++;
					sleep(app_login_distri_server_retry_interval * 1000);
					continue;
				}

			}

		}
	}
return ret;
	return ret;
}

int login_distri_plat_step2_tcp(void *dat) {
	LOGGER_TRC("%s\n", __FUNCTION__);
	int ret = 0;
#if DEBUG_FLOW_CONTROL == 1
	ret = manual_interactive_flow_control(__FUNCTION__);
	return ret;
#endif

	return ret;
}

int login_operation_plat(void *dat) {
	LOGGER_TRC("%s\n", __FUNCTION__);
	int ret = 0;
#if DEBUG_FLOW_CONTROL == 1
	ret = manual_interactive_flow_control(__FUNCTION__);
	return ret;
#endif
	int sockfd = -1;
	char buf[1024];
	struct hostent *he; 
	struct sockaddr_in server;
	int resend_counter = 0 ;
	fd_set rdfds;
	struct timeval tv;
	int current_ip_index = 0;


	if (app_domain_info.operate_server.ip_flag == 0 ){
		//do dns resolver
		int ip_num = netutils_dns_resolver(app_domain_info.operate_server.domain, 
				app_domain_info.operate_server.ip_list[0], NETUTIIS_MAX_IP_PER_DOMAIN, NETUTILS_MAX_IP_LEN);
		LOGGER_DBG("operate dns resolver result -> %d\n", ip_num);
		if (ip_num <= 0 ){
			LOGGER_ERR("operate_server dns failed,sleep and retry\n");
			sleep(app_login_distri_server_retry_interval);
			return RET_DNS_FAILED ;
		}

	}
	while(1)  { //check next dns
		if (current_ip_index > app_domain_info.operate_server.ip_list_number ) {
			LOGGER_ERR("no ip address can reached \n");
			return RET_NO_ACK ;

		}

		char *operate_server_ip = app_domain_info.operate_server.ip_list[current_ip_index] ;
		uint32_t operate_server_port = app_domain_info.operate_server.tcp_port ;
		current_ip_index++;
		while (1) {
			if (resend_counter >= 3 ){
				LOGGER_ERR("login to operate failed \n");
				return RET_NO_ACK ;
			}
			if((sockfd=socket(AF_INET,SOCK_STREAM, 0))==-1)
			{
				printf("socket() error\n");
				exit(1);
			}
			bzero(&server,sizeof(server));
			server.sin_family = AF_INET;
			server.sin_port = htons(operate_server_port);
			server.sin_addr.s_addr = inet_addr(operate_server_ip);
			LOGGER_DBG("try connect %s %d\n",operate_server_ip,operate_server_port);
			if(connect(sockfd, (struct sockaddr *)&server, sizeof(server))==-1)
			{
				LOGGER_ERR("connect  error\n");
				resend_counter++;
				sleep(app_login_distri_server_retry_interval);
				continue ;
			}
			ret = sysutils_get_json_rpc_boot(buf+4);		
			if(ret < 0 ){
				LOGGER_ERR("get rpc boot json error \n");
				return RET_SYS_ERROR ;
			}
			LOGGER_DBG("json->%s\n", buf + 4);
			uint32_t buf_len = strlen(buf + 4);
			uint32_t *json_len = (uint32_t *) buf;
			*json_len = htons(buf_len);
			LOGGER_DBG("send -> %d ->%s\n", json_len, buf + 4);
			ret = send(sockfd,buf,buf_len+4 ,0 );
			LOGGER_DBG("tcp send result -> %d\n",ret);
			//try receive ack
			FD_ZERO(&rdfds);
			FD_SET(sockfd, &rdfds);
			tv.tv_sec = 15;
			tv.tv_usec = 0;
			ret = select(sockfd + 1, &rdfds, NULL, NULL, &tv);
			if (ret == 0) {
				LOGGER_DBG("no data and timeout\n");
				close(sockfd);
				resend_counter++ ;
				LOGGER_DBG("wait for 15s and time out ,no data\n");
				sleep(app_login_distri_server_retry_interval);
				continue ;
			}
		}
		if (ret < 0)
		{
			LOGGER_ERR("select error ->%d \n",ret);
		}
		else if (ret == 0) {
			//have been handler before ,never run to here
			printf("no data and timeout\n");
		}

		else { /* 说明等待时间还未到1秒加500毫秒，socket的状态发生了变化 */
			ssize_t buf_len ;
			printf("ret=%d\n", ret); /* if ret>1，more handler changed  */
			if (FD_ISSET(sockfd, &rdfds)) {
				/* read data */
				memset(buf, 0, 1024);
				buf_len = recv(sockfd, buf, 1024, 0);
				if (buf_len < 0) {
					LOGGER_DBG("receive data error -> %d\n", buf_len);
					resend_counter++;
					sleep(app_login_distri_server_retry_interval);
					close(sockfd);
					sockfd = -1;
				}
				uint32_t recv_json_len = ntohl(  *( (uint32_t *)  buf) );
				LOGGER_DBG("receive data -> %d -> %s\n", recv_json_len, buf + 4);
				if (recv_json_len != (buf_len - 4)) {
					LOGGER_ERR("receive data len not match,server error -> %d %d\n", recv_json_len, buf_len);
					resend_counter++;
					sleep(app_login_distri_server_retry_interval);
					continue;
				}

				resend_counter = 0;
				int result = -1;
				int id = 0;
				ret = sysutils_parse_json_is_result(buf,&result,&id);
				printf("result ack ->%d %d %d %s\n",result,id ,ret,buf);
				if (ret == 0) {
					if (result == 0) {
						LOGGER_DBG("boot first registe ok ,continue \n");
						//server_ip is the wlan ip ,do not care it .

						return RET_OK;
					} else {
						LOGGER_ERR("Boot first reigister failed \n");
						sleep(app_login_distri_server_retry_interval * 1000);
					}
				}
				else if (result ==  -1 ){
					LOGGER_ERR("try another ip -1\n");
					close(sockfd);
					sockfd = -1;
					return RET_DNS_FAILED ;

				}
				else if (result ==  -2 ){
					LOGGER_ERR("gw info is not valid -2\n");
					close(sockfd);
					sockfd = -1;
					return RET_PLAT_ACK_ERR ;

				}
				else if (result ==  -3 ){
					close(sockfd);
					sockfd = -1;
					LOGGER_ERR("gw info is not valid -3\n");
					return RET_PLAT_ACK_ERR ;
				}
				else if (result ==  -1003 ){
					close(sockfd);
					sockfd = -1;
					LOGGER_ERR("device token is down ,need refresh\n");
					return RET_TOKEN_DOWN ;
				}
				else{
					LOGGER_ERR("parse ack info error \n");
					resend_counter++;
					sleep(app_login_distri_server_retry_interval * 1000);
					continue;
				}

			}
		}

		//now login success  .clear flags and try receive 
		resend_counter = 0 ;
		//begin handle all socket receive 	
		ret = socket_data_handler(sockfd);
		if (ret == RET_NETWORK_DOWN ) {
			sleep(app_login_distri_server_retry_interval);
			continue;
		}
		if (app_socket_loop_exit_event == ExitEventReConnectDistriServer )
			return RET_DISTRI_SERVER_RECONNECT ;
		else {

		}
	}
	return ret;
}
int socket_data_handler(int sockfd ){
	//begin send heartbeat and receive socket data	
	app_socket_working_state =  1;

	fd_set rdfds;
	struct timeval tv;
	int ret = 0 ;
	char buf[1024];
	int buf_len = 0;
	int recv_json_len = 0 ;
	int resend_heartbeat_counter = 0;
	time_t time_old ;
	time_t time_new ;
	time_t time_rx_monitor ;
	time(&time_old) ;
	time_new =time_old ;
	time_rx_monitor = time_new ;
	while(app_socket_working_state ) { //every 0.5s 检查一次
		//check reconnect event or others
		if(app_socket_loop_exit_event != ExitEventNone ){
			return RET_OK ;
		}
		//try to check ack message ,if 3*heartbeat interval no ack message ,will deifine the network down ,try reconnect network
		time(&time_new);
		if ( (time_new -  time_rx_monitor )  > (3*app_login_operate_server_heartbeat_interval) ){
			LOGGER_ERR("TCP network no ack for long time ,please reconnect it \n");
			app_socket_working_state = -1;
			return RET_DISTRI_SERVER_RECONNECT; //need to reconnect distri_server
		}
		//try send message
		if(( time_new - time_old ) > app_login_operate_server_heartbeat_interval ) {
			LOGGER_TRC("send heartbeat info\n");
			time_old =  time_new ;
			time(&time_new) ;
			while(1){ //try get heartbeat message
				ret = sysutils_get_json_rpc_heartbeat(buf+4);
				if (ret < 0 ){
					if(resend_heartbeat_counter > 3 ){
						app_socket_working_state = -1;
						return RET_SYS_ERROR ;
					}
					else {
						sleep(3);
						resend_heartbeat_counter++;
						continue;
					}
				}
				else {
					resend_heartbeat_counter = 0 ;
				}
			}
			buf_len =  strlen(buf+4);
		}
		else {
			ret = fifo_buffer_get(&socket_tx_fifo_header,buf+4,&buf_len);
			if(ret  <  0){
				//LOGGER_TRC("no data for send"\n);
				memset(buf,0,5);
			}
			buf[buf_len+4] = '\0';
		}
		if (buf_len != 0 ){
			uint32_t *len = (uint32_t *)buf ;
			*len =  htons(buf_len);
			ret = send(sockfd, buf,buf_len+4 ,0);
			if (ret <  0){
				LOGGER_ERR("send data error ,network down ,please reconnect\n");
				app_socket_working_state = -1;
				return RET_NETWORK_DOWN;
			}
		}
		FD_ZERO(&rdfds);
		FD_SET(sockfd, &rdfds);
		tv.tv_sec = 0;
		tv.tv_usec = 200;
		ret = select(sockfd + 1, &rdfds, NULL, NULL, &tv);
		if (ret == 0) {
			LOGGER_DBG("no data and timeout\n");
			sleep(app_login_distri_server_retry_interval);
			continue;
		}
		if (ret < 0) {
			LOGGER_DBG("select\n");
		}
		else if (ret == 0) {
			//have been handler before ,never run to here
			printf("no data and timeout\n");
		}

		else { /* 说明等待时间还未到1秒加500毫秒，socket的状态发生了变化 */
			printf("ret=%d\n", ret); /* if ret>1，more handler changed  */

			if (FD_ISSET(sockfd, &rdfds)) {
				/* read data */
				memset(buf, 0, 1024);
				buf_len = recv(sockfd, buf, 1024, 0);
				if (buf_len < 0) {
					LOGGER_DBG("receive data error -> %d\n", buf_len);
					continue;
				}
				recv_json_len = ntohl(  *( (uint32_t *)  buf) );
				LOGGER_DBG("receive data -> %d -> %s\n", recv_json_len, buf + 4);
				if (recv_json_len != (buf_len - 4)) {
					LOGGER_ERR("receive data len not match -> %d %d,just drop it \n", recv_json_len, buf_len);
				}
				fifo_buffer_put(&socket_rx_fifo_header , buf, buf_len);	
				//update time_rx_monitor 
				time(&time_rx_monitor);
			}
		}

	}
	return RET_NO_ACK ;
}
int socket_data_handler_loop(void *dat) {
	LOGGER_TRC("%s\n", __FUNCTION__);
	int ret = 0;
	return RET_OK;
	//do nothing .set intp login_operation_plat
#if DEBUG_FLOW_CONTROL == 1
	ret = manual_interactive_flow_control(__FUNCTION__);
	return ret;
#endif
	return ret;
}
int app_function_flow_ctrl_init(void) {
	memset(&app_function_flow_ctrl, 0, sizeof(AppFunctionFlowCtrl));

	//init all handler list
	app_function_flow_ctrl.hander_list[LOGIN_DISTRI_PLAT_STEP1_UDP] = login_distri_plat_step1_udp;
	app_function_flow_ctrl.hander_list[LOGIN_DISTRI_PLAT_STEP2_UDP] = login_distri_plat_step2_udp;
	app_function_flow_ctrl.hander_list[LOGIN_DISTRI_PLAT_STEP1_TCP] = login_distri_plat_step1_tcp;
	app_function_flow_ctrl.hander_list[LOGIN_DISTRI_PLAT_STEP2_TCP] = login_distri_plat_step2_tcp;
	app_function_flow_ctrl.hander_list[LOGIN_OPERATE_PLAT_STEP] = login_operation_plat;
	app_function_flow_ctrl.hander_list[SOCKET_DATA_HANDLER_STEP] = socket_data_handler_loop;

	app_function_flow_ctrl.handler_num = 6;
	//handler LOGIN_DISTRI_PLAT_STEP1_UDP
	app_function_flow_ctrl.flow_list[0].cur_handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[0].ret_handler[0].err_code = RET_OK;
	app_function_flow_ctrl.flow_list[0].ret_handler[0].handler_index = LOGIN_DISTRI_PLAT_STEP2_UDP;
	app_function_flow_ctrl.flow_list[0].ret_handler[1].err_code = RET_NO_ACK;
	app_function_flow_ctrl.flow_list[0].ret_handler[1].handler_index = LOGIN_DISTRI_PLAT_STEP1_TCP;
	app_function_flow_ctrl.flow_list[0].ret_handler[2].err_code = RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[0].ret_handler[3].handler_index = LOGIN_DISTRI_PLAT_STEP1_TCP;
	//handler LOGIN_DISTRI_PLAT_STEP2_UDP
	app_function_flow_ctrl.flow_list[1].cur_handler_index = LOGIN_DISTRI_PLAT_STEP2_UDP;
	app_function_flow_ctrl.flow_list[1].ret_handler[0].err_code = RET_OK;
	app_function_flow_ctrl.flow_list[1].ret_handler[0].handler_index = LOGIN_OPERATE_PLAT_STEP;
	app_function_flow_ctrl.flow_list[1].ret_handler[1].err_code = RET_NO_ACK;
	app_function_flow_ctrl.flow_list[1].ret_handler[1].handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[1].ret_handler[2].err_code = RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[1].ret_handler[3].handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[1].ret_handler[2].err_code = RET_NOT_MATCH;
	app_function_flow_ctrl.flow_list[1].ret_handler[3].handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;
	//handler LOGIN_DISTRI_PLAT_STEP1_TCP
	app_function_flow_ctrl.flow_list[2].cur_handler_index = LOGIN_DISTRI_PLAT_STEP1_TCP;
	app_function_flow_ctrl.flow_list[2].ret_handler[0].err_code = RET_OK;
	app_function_flow_ctrl.flow_list[2].ret_handler[0].handler_index = LOGIN_DISTRI_PLAT_STEP2_TCP;
	app_function_flow_ctrl.flow_list[2].ret_handler[1].err_code = RET_NO_ACK;
	app_function_flow_ctrl.flow_list[2].ret_handler[1].handler_index = LOGIN_DISTRI_PLAT_STEP1_TCP;
	app_function_flow_ctrl.flow_list[2].ret_handler[2].err_code = RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[2].ret_handler[3].handler_index = LOGIN_DISTRI_PLAT_STEP1_TCP;
	//handler LOGIN_DISTRI_PLAT_STEP2_TCP
	app_function_flow_ctrl.flow_list[3].cur_handler_index = LOGIN_DISTRI_PLAT_STEP2_TCP;
	app_function_flow_ctrl.flow_list[3].ret_handler[0].err_code = RET_OK;
	app_function_flow_ctrl.flow_list[3].ret_handler[0].handler_index = LOGIN_OPERATE_PLAT_STEP;
	app_function_flow_ctrl.flow_list[3].ret_handler[1].err_code = RET_NO_ACK;
	app_function_flow_ctrl.flow_list[3].ret_handler[1].handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[3].ret_handler[2].err_code = RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[3].ret_handler[3].handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;

	//handler LOGIN_OPERATE_PLAT_STEP
	app_function_flow_ctrl.flow_list[4].cur_handler_index = LOGIN_DISTRI_PLAT_STEP2_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[0].err_code = RET_OK;
	app_function_flow_ctrl.flow_list[4].ret_handler[0].handler_index = SOCKET_DATA_HANDLER_STEP;
	app_function_flow_ctrl.flow_list[4].ret_handler[1].err_code = RET_NO_ACK;
	app_function_flow_ctrl.flow_list[4].ret_handler[1].handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[2].err_code = RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[4].ret_handler[3].handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;
	//handler SOCKET_DATA_HANDLER_STEP
	app_function_flow_ctrl.flow_list[4].cur_handler_index = LOGIN_DISTRI_PLAT_STEP2_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[0].err_code = RET_OK; //never reach here
	app_function_flow_ctrl.flow_list[4].ret_handler[0].handler_index = SOCKET_DATA_HANDLER_STEP;
	app_function_flow_ctrl.flow_list[4].ret_handler[1].err_code = RET_NO_ACK;
	app_function_flow_ctrl.flow_list[4].ret_handler[1].handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[2].err_code = RET_TOKEN_DOWN;
	app_function_flow_ctrl.flow_list[4].ret_handler[2].handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[3].err_code = RET_PLAT_ACK_ERR;
	app_function_flow_ctrl.flow_list[4].ret_handler[3].handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[4].err_code = RET_PLAT_RECONNECT;
	app_function_flow_ctrl.flow_list[4].ret_handler[4].handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;

	app_function_flow_ctrl.flow_list[4].ret_handler[5].handler_index = -1;

	//get system  setting from setting file
	//Fix me
	//soon if need
	pthread_mutex_lock(&app_domain_info.mutex_lock);

	memset(&app_domain_info.distri_server, 0, sizeof(DnsAddressInfo));
	memset(&app_domain_info.operate_server, 0, sizeof(DnsAddressInfo));
	sprintf(app_domain_info.distri_server.domain, "operatetest.189cube.com");
	app_domain_info.distri_server.cur_ip = -1;
	app_domain_info.distri_server.ip_list_number = 0;
	app_domain_info.distri_server.tcp_port = 60001;
	app_domain_info.distri_server.udp_port = 60001;

	sprintf(app_domain_info.operate_server.domain, "operatetest.189cube.com");
	app_domain_info.operate_server.cur_ip = -1;
	app_domain_info.operate_server.ip_list_number = 0;
	app_domain_info.operate_server.tcp_port = 60004;
	app_domain_info.operate_server.udp_port = 60004;
	pthread_mutex_unlock(&app_domain_info.mutex_lock);
	return  0;
}

int  app_function_flow_ctrl_thread(void *dat) {
	FunctionStepPointer function_step_pointer = NULL;
	int handler_index = 0;
	int ret = 0;

	while (1) {
		if(app_theard_exit_flag  > 0 ){
			LOGGER_TRC("app thread exit ->%s\n",__FUNCTION__);
			return 0;
		}
		if (handler_index < 0 || handler_index >= app_function_flow_ctrl.handler_num) {
			LOGGER_ERR("handler index is error ->%d ,and set to default\n", handler_index);
			handler_index = 0;
			break;
		}
		function_step_pointer = app_function_flow_ctrl.hander_list[handler_index];
		ret = function_step_pointer(NULL);
		for (int i = 0;; i++) {
			FunctionRetHander ret_handler = app_function_flow_ctrl.flow_list[handler_index].ret_handler[i];
			if (ret_handler.handler_index < 0) {
				LOGGER_ERR("can find next handler -> %d %d\n", handler_index, ret);

				handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;
				LOGGER_ERR("set next hander to default -> %d\n", LOGIN_DISTRI_PLAT_STEP1_UDP);
				break;
			}
			if (ret_handler.err_code == ret) {
				LOGGER_DBG("find next handler src :ret:next -> %d %d %d\n", handler_index, ret, ret_handler.handler_index);
				handler_index = ret_handler.handler_index;
				break;
			}
		}
	}
}

int app_function_parse_fifo_buffer_init(void){
	LOGGER_DBG("init downlink push message handler ,maybe null\n");
	return 0;
}
int app_function_parse_fifo_buffer_thread(void *dat){
	char buf[1024];
	int buf_len = 0 ;
	int ret = 0;
	while(1 ){
		if(app_theard_exit_flag  > 0 ){
			LOGGER_TRC("app thread exit ->%s\n",__FUNCTION__);
			return 0 ;
		}
		ret = fifo_buffer_get(&socket_rx_fifo_header ,buf,&buf_len);
		if (ret < 0 ){
			//no message 
			sleep(1);
			continue ;
		}
		ret = sysutils_try_handler_ack_result_message(buf);
		if(ret  > 0 ){
			LOGGER_TRC("ack messge \n");
			continue ;	
		}
		else if (ret == 0 ){
			ret = sysutils_try_handler_server_push_message(buf);
			if(ret  > 0 ){
				LOGGER_TRC(" push message \n");
				continue ;	
			}
			else if(ret  ==  0){
				LOGGER_TRC("never reach here\n");
				continue ;
			}
			else {
				LOGGER_ERR("unknown message \n");
				continue;
			}
		}
		else {
			LOGGER_ERR("parse error ,skip\n");
		}
	}
	return 0;
}
