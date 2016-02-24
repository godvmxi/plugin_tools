#ifndef libClient_H
#define libClient_H

#include "stdio.h"
#include "logger.h"
#include "netutils.h"
#include <pthread.h>
typedef enum{
	LOGIN_DISTRI_PLAT_STEP1_UDP=0,
	LOGIN_DISTRI_PLAT_STEP2_UDP =1 ,
	LOGIN_DISTRI_PLAT_STEP1_TCP =2 ,
	LOGIN_DISTRI_PLAT_STEP2_TCP =3 ,
	LOGIN_OPERATE_PLAT_STEP   =4,
	SOCKET_DATA_HANDLER_STEP  =5,

}HanderFunctionEnum;
typedef enum{
	RET_NETWORK_DOWN = -8 ,
	RET_SYS_ERROR = -7,
	RET_PLAT_RECONNECT = -6,
	RET_PLAT_ACK_ERR = -5,
	RET_TOKEN_DOWN = -4,
	RET_NOT_MATCH = -3,
	RET_DNS_FAILED = -2,
	RET_NO_ACK  = -1,
	RET_OK = 0,

}HanderRetEnum;
#define MAX_RET_HANDLER_NUM  5
#define MAX_HANDLER_NUM  10

typedef int (*FunctionStepPointer)(void *dat) ;

typedef struct {
	int err_code;
	int handler_index;
}FunctionRetHander;

typedef struct {
		int cur_handler_index ;

		FunctionRetHander  ret_handler[MAX_RET_HANDLER_NUM];
}FunctionFlowCtrl;

typedef struct {
	int handler_num ;
	FunctionStepPointer 	hander_list[MAX_HANDLER_NUM];
	FunctionFlowCtrl 			flow_list[MAX_HANDLER_NUM];
} AppFunctionFlowCtrl;
typedef struct {
	pthread_mutex_t mutex_lock ;
	DnsAddressInfo  distri_server ;
	DnsAddressInfo  operate_server ;
	DnsAddressInfo  plugin_server ;

}AppDomainInfo;
typedef struct {
	char chanllege_code[20];
	char token[64];
	char exp_date[64] ;//may be useless
	char ca_download_url[64]; //contain ca 
	char ca_local_path[64]; //contain ca 
}AppSecurityInfo;

typedef struct {
	int id ;
	int message_type ;

}MessageWaitAckInfo ;
typedef struct {
	pthread_mutex_t lock ;
	MessageWaitAckInfo messsage_wait_ack_list[10];
}AppMessageWaitAckInfo ;

extern AppFunctionFlowCtrl app_function_flow_ctrl ;
extern AppDomainInfo  app_domain_info;

void app_function_fifo_buffer_init(void);
extern void app_funcion_flow_ctrl_init(void);
extern void app_funcion_flow_ctrl_start(void);

int login_distri_plat_step1_udp(void *dat);
int login_distri_plat_step2_udp(void *dat);
int login_distri_plat_step1_tcp(void *dat);
int login_distri_plat_step2_tcp(void *dat);
int login_operation_plat(void *dat);
int socket_data_handler_loop(void *dat);
int socket_data_handler(int sockfd );


int sysutils_get_json_rpc_message_push(char *buf,char *plugin_name,char *message,int message_len);

extern void get_version (void);

#endif
