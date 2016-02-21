#ifndef libClient_H
#define libClient_H

#include "stdio.h"
typedef enum{
	LOGIN_DISTRI_PLAT_STEP1_UDP=0,
	LOGIN_DISTRI_PLAT_STEP2_UDP =1 ,
	LOGIN_DISTRI_PLAT_STEP1_TCP =2 ,
	LOGIN_DISTRI_PLAT_STEP2_TCP =3 ,
	LOGIN_OPERATE_PLAT_STEP   =4,
	SOCKET_DATA_HANDLER_STEP  =5,

}HanderFunctionEnum;
typedef enum{
	RET_PLAT_ACK_ERR = -5,
	RET_TOKEN_DOWN = -4,
	RET_NOT_MATCH = -3,
	RET_DNS_FAILED = -2,
	RET_NO_ACK  = -1,
	RET_OK = 0,
	RET_PLAT_RECONNECT = 1,
}HanderRetEnum;
#define MAX_RET_HANDLER_NUM  5
#define MAX_HANDLER_NUM  10

typedef int (*FunctionStep)(void *dat) ;

typedef struct {
	int err_code;
	int hander_index;
}FunctionRetHander;

typedef struct {
		int hander_index ;

		FunctionRetHander  ret_handler[MAX_RET_HANDLER_NUM];
}FunctionFlowCtrl;

typedef struct {
	int handler_num ;
	int handler_flow_num;
	//
	FunctionStep hander_list[MAX_HANDLER_NUM];
	FunctionFlowCtrl flow_list[MAX_HANDLER_NUM];
} AppFunctionFlowCtrl;

extern AppFunctionFlowCtrl app_function_flow_ctrl ;

void app_funcion_flow_ctrl_init(void);

int login_distri_plat_step1_udp(void *dat);
int login_distri_plat_step2_udp(void *dat);
int login_distri_plat_step1_tcp(void *dat);
int login_distri_plat_step2_tcp(void *dat);
int login_operation_plat(void *dat);
int socket_data_handler_loop(void *dat);

extern void get_version ();

#endif
