#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netutils.h>
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

AppFunctionFlowCtrl app_function_flow_ctrl ;
AppDomainInfo  app_domain_info;

void get_version(){
  printf("version 0.1\n");
}
#define   DEBUG_FLOW_CONTROL  0

int manual_interactive_flow_control(const char *info){
		char input[64] ;
	  int ret = 0 ;
		printf("Input choice  << %s >>--> ",info);
		scanf("%d",&ret);
		printf("\n you input value -> %d\n",ret);
		return ret ;
}
int login_distri_plat_step1_udp(void *dat)
{
	LOG_TRACE("%s\n",__FUNCTION__);
	int ret = 0;
#if DEBUG_FLOW_CONTROL == 1
	ret = manual_interactive_flow_control(__FUNCTION__) ;
	return ret;
#endif

	char *dns = app_domain_info.distri_server.domain;
	char *ip_list =  app_domain_info.distri_server.ip_list[0] ;
	int ip_num = netutils_dns_resolver(dns,ip_list,NETUTIIS_MAX_IP_PER_DOMAIN,NETUTILS_MAX_IP_LEN);
	LOG_DEBUG("dns resolver result -> %d\n",ip_num);
	app_domain_info.distri_server.cur_ip = 0;
	app_domain_info.distri_server.ip_list_number =  ip_num ;
	int cur_ip_index = 0;


	int socket_descriptor;
	int iter=0;
	int send_counter = 0;
	struct sockaddr_in address;
	char buf[1024] = {0};
	uint32_t  recv_json_len ;
	fd_set rdfds;
	struct timeval tv; 

	while(1){ 
		if(cur_ip_index >= ip_num ){
			LOG_DEBUG("no valid ip can be used\n");
			return RET_NO_ACK;
		}
		bzero(&address,sizeof(address));
		address.sin_family=AF_INET;
		address.sin_addr.s_addr=inet_addr(app_domain_info.distri_server.ip_list[cur_ip_index]);
		address.sin_port=htons(app_domain_info.distri_server.udp_port);
		//create socket
		socket_descriptor=socket(AF_INET,SOCK_DGRAM,0);


		memset(buf,0,1024);
		sysutils_get_json_rpc_boot_first(buf+4);
		LOG_DEBUG("json->%s\n",buf+4);
		uint32_t buf_len = strlen(buf+4);
		uint32_t *json_len = (uint32_t *)buf ;
		*json_len = htons(buf_len);
		LOG_DEBUG("send -> %d ->%s\n",json_len,buf+4);
		sendto(socket_descriptor,buf,buf_len+4,0,(struct sockaddr *)&address,sizeof(address));
		int recv_counter = 0;
		while(1){
		FD_ZERO(&rdfds); 
		FD_SET(socket_descriptor, &rdfds);
		tv.tv_sec = 0;
		tv.tv_usec = 500; 
		ret = select(socket_descriptor + 1, &rdfds, NULL, NULL, &tv); 
			if (ret ==  0){
				LOG_DEBUG("no data and timeout\n"); 
				recv_counter++;
				if (recv_counter > 10){
					close(socket_descriptor);
					LOG_DEBUG("wait for 15s and time out ,no data\n") ;
					LOG_DEBUG("try next ip\n") ;
					cur_ip_index++;
					
				}
			}
		}
		if(ret < 0) perror("select");/* 这说明select函数出错 */
		else if(ret == 0) {
			//have been handler before ,never run to here
			printf("no data and timeout\n"); 
		}

		else { /* 说明等待时间还未到1秒加500毫秒，socket的状态发生了变化 */
			printf("ret=%d\n", ret); /* if ret>1，more handler changed  */


			if(FD_ISSET(socket_descriptor, &rdfds)) { 
				/* read data */
				memset(buf,0 ,1024);
				buf_len = recv(socket_descriptor,buf,1024,0);
				if (buf_len < 0 ){
					LOG_DEBUG("receive data error -> %d\n",buf_len);
					send_counter++;
					continue;
				}
				recv_json_len =ntohl(buf);
				LOG_DEBUG("receive data -> %d -> %s\n",recv_json_len,buf+4);
				//try parse json data 
			}
		}
	}



	return ret ;
}
int login_distri_plat_step2_udp(void *dat)
{
	LOG_TRACE("%s\n",__FUNCTION__);
	int ret = 0;
#if DEBUG_FLOW_CONTROL == 1
	ret = manual_interactive_flow_control(__FUNCTION__) ;
	return ret;
#endif
	return ret ;
}
int login_distri_plat_step1_tcp(void *dat)
{
	LOG_TRACE("%s\n",__FUNCTION__);
	int ret = 0;
#if DEBUG_FLOW_CONTROL == 1
	ret = manual_interactive_flow_control(__FUNCTION__) ;
	return ret;
#endif
	return ret ;
}

int login_distri_plat_step2_tcp(void *dat)
{
	LOG_TRACE("%s\n",__FUNCTION__);
	int ret = 0;
#if DEBUG_FLOW_CONTROL == 1
	ret = manual_interactive_flow_control(__FUNCTION__) ;
	return ret;
#endif

	return ret ;
}

int login_operation_plat(void *dat){
	LOG_TRACE("%s\n",__FUNCTION__);
	int ret = 0;
#if DEBUG_FLOW_CONTROL == 1
	ret = manual_interactive_flow_control(__FUNCTION__) ;
	return ret;
#endif
	return ret ;
}
int socket_data_handler_loop(void *dat) {
	LOG_TRACE("%s\n", __FUNCTION__);
	int ret = 0;
#if DEBUG_FLOW_CONTROL == 1
	ret = manual_interactive_flow_control(__FUNCTION__);
	return ret;
#endif
	return ret;
}
/*
 *
 * 	LOGIN_DISTRI_PLAT_STEP1_UDP=0,
	LOGIN_DISTRI_PLAT_STEP2_UDP =1 ,
	LOGIN_DISTRI_PLAT_STEP1_TCP =2 ,
	LOGIN_DISTRI_PLAT_STEP2_TCP =3 ,
	LOGIN_OPERATE_PLAT   =4,
	SOCKET_DATA_HANDLER  =5,
 *
int login_distri_plat_step1_udp(void *dat);
int login_distri_plat_step2_udp(void *dat);
int login_distri_plat_step1_tcp(void *dat);
int login_distri_plat_step2_tcp(void *dat);
int login_operation_plat(void *dat);
int socket_data_handler_loop(void *dat);
 *
 */
void app_funcion_flow_ctrl_init(void){
	memset(&app_function_flow_ctrl,0,sizeof(AppFunctionFlowCtrl));

	//init all handler list
	app_function_flow_ctrl.hander_list[LOGIN_DISTRI_PLAT_STEP1_UDP] = login_distri_plat_step1_udp;
	app_function_flow_ctrl.hander_list[LOGIN_DISTRI_PLAT_STEP2_UDP] = login_distri_plat_step2_udp;
	app_function_flow_ctrl.hander_list[LOGIN_DISTRI_PLAT_STEP1_TCP] = login_distri_plat_step1_tcp;
	app_function_flow_ctrl.hander_list[LOGIN_DISTRI_PLAT_STEP2_TCP] = login_distri_plat_step2_tcp;
	app_function_flow_ctrl.hander_list[LOGIN_OPERATE_PLAT_STEP] 		 = login_operation_plat;
	app_function_flow_ctrl.hander_list[SOCKET_DATA_HANDLER_STEP] 		 = socket_data_handler_loop;

	app_function_flow_ctrl.handler_num = 6 ;
	//handler LOGIN_DISTRI_PLAT_STEP1_UDP
	app_function_flow_ctrl.flow_list[0].cur_handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[0].ret_handler[0].err_code =  RET_OK;
	app_function_flow_ctrl.flow_list[0].ret_handler[0].handler_index =  LOGIN_DISTRI_PLAT_STEP2_UDP;
	app_function_flow_ctrl.flow_list[0].ret_handler[1].err_code = RET_NO_ACK ;
	app_function_flow_ctrl.flow_list[0].ret_handler[1].handler_index =  LOGIN_DISTRI_PLAT_STEP1_TCP;
	app_function_flow_ctrl.flow_list[0].ret_handler[2].err_code =  RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[0].ret_handler[3].handler_index =  LOGIN_DISTRI_PLAT_STEP1_TCP;
	//handler LOGIN_DISTRI_PLAT_STEP2_UDP
	app_function_flow_ctrl.flow_list[1].cur_handler_index = LOGIN_DISTRI_PLAT_STEP2_UDP;
	app_function_flow_ctrl.flow_list[1].ret_handler[0].err_code =  RET_OK;
	app_function_flow_ctrl.flow_list[1].ret_handler[0].handler_index =  LOGIN_OPERATE_PLAT_STEP;
	app_function_flow_ctrl.flow_list[1].ret_handler[1].err_code = RET_NO_ACK ;
	app_function_flow_ctrl.flow_list[1].ret_handler[1].handler_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[1].ret_handler[2].err_code =  RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[1].ret_handler[3].handler_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[1].ret_handler[2].err_code =  RET_NOT_MATCH;
	app_function_flow_ctrl.flow_list[1].ret_handler[3].handler_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	//handler LOGIN_DISTRI_PLAT_STEP1_TCP
	app_function_flow_ctrl.flow_list[2].cur_handler_index = LOGIN_DISTRI_PLAT_STEP1_TCP;
	app_function_flow_ctrl.flow_list[2].ret_handler[0].err_code =  RET_OK;
	app_function_flow_ctrl.flow_list[2].ret_handler[0].handler_index =  LOGIN_DISTRI_PLAT_STEP2_TCP;
	app_function_flow_ctrl.flow_list[2].ret_handler[1].err_code = RET_NO_ACK ;
	app_function_flow_ctrl.flow_list[2].ret_handler[1].handler_index =  LOGIN_DISTRI_PLAT_STEP1_TCP;
	app_function_flow_ctrl.flow_list[2].ret_handler[2].err_code =  RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[2].ret_handler[3].handler_index =  LOGIN_DISTRI_PLAT_STEP1_TCP;
	//handler LOGIN_DISTRI_PLAT_STEP2_TCP
	app_function_flow_ctrl.flow_list[3].cur_handler_index = LOGIN_DISTRI_PLAT_STEP2_TCP;
	app_function_flow_ctrl.flow_list[3].ret_handler[0].err_code =  RET_OK;
	app_function_flow_ctrl.flow_list[3].ret_handler[0].handler_index =  LOGIN_OPERATE_PLAT_STEP;
	app_function_flow_ctrl.flow_list[3].ret_handler[1].err_code = RET_NO_ACK ;
	app_function_flow_ctrl.flow_list[3].ret_handler[1].handler_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[3].ret_handler[2].err_code =  RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[3].ret_handler[3].handler_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;

	//handler LOGIN_OPERATE_PLAT_STEP
	app_function_flow_ctrl.flow_list[4].cur_handler_index = LOGIN_DISTRI_PLAT_STEP2_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[0].err_code =  RET_OK;
	app_function_flow_ctrl.flow_list[4].ret_handler[0].handler_index =  SOCKET_DATA_HANDLER_STEP;
	app_function_flow_ctrl.flow_list[4].ret_handler[1].err_code = RET_NO_ACK ;
	app_function_flow_ctrl.flow_list[4].ret_handler[1].handler_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[2].err_code =  RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[4].ret_handler[3].handler_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	//handler SOCKET_DATA_HANDLER_STEP
	app_function_flow_ctrl.flow_list[4].cur_handler_index = LOGIN_DISTRI_PLAT_STEP2_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[0].err_code =  RET_OK; //never reach here
	app_function_flow_ctrl.flow_list[4].ret_handler[0].handler_index =  SOCKET_DATA_HANDLER_STEP;
	app_function_flow_ctrl.flow_list[4].ret_handler[1].err_code = RET_NO_ACK ;
	app_function_flow_ctrl.flow_list[4].ret_handler[1].handler_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[2].err_code =  RET_TOKEN_DOWN;
	app_function_flow_ctrl.flow_list[4].ret_handler[2].handler_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[3].err_code =  RET_PLAT_ACK_ERR;
	app_function_flow_ctrl.flow_list[4].ret_handler[3].handler_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[4].err_code =  RET_PLAT_RECONNECT;
	app_function_flow_ctrl.flow_list[4].ret_handler[4].handler_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;

	app_function_flow_ctrl.flow_list[4].ret_handler[5].handler_index =  -1;

	//get system  setting from setting file
	//Fix me
	//soon if need
	pthread_mutex_lock(&app_domain_info.mutex_lock);

	memset(&app_domain_info.distri_server,0,sizeof(DnsAddressInfo));
	memset(&app_domain_info.operate_server,0,sizeof(DnsAddressInfo));
	sprintf(app_domain_info.distri_server.domain,"189cube.com");
	app_domain_info.distri_server.cur_ip  = -1;
	app_domain_info.distri_server.ip_list_number = 0 ;
	app_domain_info.distri_server.tcp_port =   12112;
	app_domain_info.distri_server.udp_port =   12112;

	sprintf(app_domain_info.operate_server.domain,"189cube.com");
	app_domain_info.operate_server.cur_ip  = -1;
	app_domain_info.operate_server.ip_list_number = 0 ;
	app_domain_info.distri_server.tcp_port =   12112;
	app_domain_info.distri_server.udp_port =   12112;
	pthread_mutex_unlock(&app_domain_info.mutex_lock);

}

void app_funcion_flow_ctrl_start(void){
	FunctionStepPointer function_step_pointer = NULL;
	int handler_index = 0;
	int ret = 0;

	while(1){
			if (handler_index < 0 || handler_index >= app_function_flow_ctrl.handler_num){
				LOG_ERROR("handler index is error ->%d ,and set to default\n",handler_index);
				handler_index = 0;
				break;
			}
		function_step_pointer = app_function_flow_ctrl.hander_list[handler_index] ;
		ret = function_step_pointer(NULL);
		for(int i = 0 ;   ;i++){
			FunctionRetHander ret_handler = app_function_flow_ctrl.flow_list[handler_index].ret_handler[i];
			if (ret_handler.handler_index < 0 ){
				LOG_ERROR("can find next handler -> %d %d\n",handler_index,ret);

				handler_index = LOGIN_DISTRI_PLAT_STEP1_UDP ;
				LOG_ERROR("set next hander to default -> %d\n",LOGIN_DISTRI_PLAT_STEP1_UDP);
				break;
			}
			if (ret_handler.err_code ==  ret){
				LOG_DEBUG("find next handler src :ret:next -> %d %d %d\n",handler_index,ret,ret_handler.handler_index);
				handler_index = ret_handler.handler_index ;
				break;
			}

		}
	}


}

