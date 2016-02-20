#ifndef libClient_H
#define libClient_H

#include "stdio.h"
typedef enum{


}HanderFunctionEnum;
typedef enum{
	HandlerLoginDistributePlatStep1WithUdp,
	Handler  ,
	Handler  ,
	Handler  ,
	Handler  ,
	Handler  ,
	Handler  ,
}HanderRetEnum;
typedef struct {
	int retValue;
	void *handler ;
}RetHander;
#define MAX_RET_HANDER_NUM  5
typedef struct {
		void *hander ;
		RetHander[MAX_RET_HANDER_NUM];
}FunctionFlowCtrol;

int login_distribute_plat_step1_udp();
int login_distribute_plat_step2_udp();
int login_distribute_plat_step1_tcp();
int login_distribute_plat_step2_tcp();


int login_operation_plat();
int socket_data_handler_loop();

extern void get_version ();

#endif
