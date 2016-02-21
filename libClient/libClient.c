#include "libClient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
AppFunctionFlowCtrl app_function_flow_ctrl ;

void
get_version(){
  printf("ret version 0.1\n");
}
#define   DEBUG_FLOW_CONTROL  1
int manual_interactive_flow_control(const char *info){
		char input[64] ;
	 int ret = 0 ;
		printf("please input your choice  << %s >>--> ",info);
		scanf("%d",&ret);
		printf("\nyou input value -> %d\n",ret);
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
	app_function_flow_ctrl.flow_list[0].hander_index = LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[0].ret_handler[0].err_code =  RET_OK;
	app_function_flow_ctrl.flow_list[0].ret_handler[0].hander_index =  LOGIN_DISTRI_PLAT_STEP2_UDP;
	app_function_flow_ctrl.flow_list[0].ret_handler[1].err_code = RET_NO_ACK ;
	app_function_flow_ctrl.flow_list[0].ret_handler[1].hander_index =  LOGIN_DISTRI_PLAT_STEP1_TCP;
	app_function_flow_ctrl.flow_list[0].ret_handler[2].err_code =  RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[0].ret_handler[3].hander_index =  LOGIN_DISTRI_PLAT_STEP1_TCP;
	//handler LOGIN_DISTRI_PLAT_STEP2_UDP
	app_function_flow_ctrl.flow_list[1].hander_index = LOGIN_DISTRI_PLAT_STEP2_UDP;
	app_function_flow_ctrl.flow_list[1].ret_handler[0].err_code =  RET_OK;
	app_function_flow_ctrl.flow_list[1].ret_handler[0].hander_index =  LOGIN_OPERATE_PLAT_STEP;
	app_function_flow_ctrl.flow_list[1].ret_handler[1].err_code = RET_NO_ACK ;
	app_function_flow_ctrl.flow_list[1].ret_handler[1].hander_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[1].ret_handler[2].err_code =  RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[1].ret_handler[3].hander_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[1].ret_handler[2].err_code =  RET_NOT_MATCH;
	app_function_flow_ctrl.flow_list[1].ret_handler[3].hander_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	//handler LOGIN_DISTRI_PLAT_STEP1_TCP
	app_function_flow_ctrl.flow_list[2].hander_index = LOGIN_DISTRI_PLAT_STEP1_TCP;
	app_function_flow_ctrl.flow_list[2].ret_handler[0].err_code =  RET_OK;
	app_function_flow_ctrl.flow_list[2].ret_handler[0].hander_index =  LOGIN_DISTRI_PLAT_STEP2_TCP;
	app_function_flow_ctrl.flow_list[2].ret_handler[1].err_code = RET_NO_ACK ;
	app_function_flow_ctrl.flow_list[2].ret_handler[1].hander_index =  LOGIN_DISTRI_PLAT_STEP1_TCP;
	app_function_flow_ctrl.flow_list[2].ret_handler[2].err_code =  RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[2].ret_handler[3].hander_index =  LOGIN_DISTRI_PLAT_STEP1_TCP;
	//handler LOGIN_DISTRI_PLAT_STEP2_TCP
	app_function_flow_ctrl.flow_list[3].hander_index = LOGIN_DISTRI_PLAT_STEP2_TCP;
	app_function_flow_ctrl.flow_list[3].ret_handler[0].err_code =  RET_OK;
	app_function_flow_ctrl.flow_list[3].ret_handler[0].hander_index =  LOGIN_OPERATE_PLAT_STEP;
	app_function_flow_ctrl.flow_list[3].ret_handler[1].err_code = RET_NO_ACK ;
	app_function_flow_ctrl.flow_list[3].ret_handler[1].hander_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[3].ret_handler[2].err_code =  RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[3].ret_handler[3].hander_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;

	//handler LOGIN_OPERATE_PLAT_STEP
	app_function_flow_ctrl.flow_list[4].hander_index = LOGIN_DISTRI_PLAT_STEP2_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[0].err_code =  RET_OK;
	app_function_flow_ctrl.flow_list[4].ret_handler[0].hander_index =  SOCKET_DATA_HANDLER_STEP;
	app_function_flow_ctrl.flow_list[4].ret_handler[1].err_code = RET_NO_ACK ;
	app_function_flow_ctrl.flow_list[4].ret_handler[1].hander_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[2].err_code =  RET_DNS_FAILED;
	app_function_flow_ctrl.flow_list[4].ret_handler[3].hander_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	//handler SOCKET_DATA_HANDLER_STEP
	app_function_flow_ctrl.flow_list[4].hander_index = LOGIN_DISTRI_PLAT_STEP2_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[0].err_code =  RET_OK; //never reach here
	app_function_flow_ctrl.flow_list[4].ret_handler[0].hander_index =  SOCKET_DATA_HANDLER_STEP;
	app_function_flow_ctrl.flow_list[4].ret_handler[1].err_code = RET_NO_ACK ;
	app_function_flow_ctrl.flow_list[4].ret_handler[1].hander_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[2].err_code =  RET_TOKEN_DOWN;
	app_function_flow_ctrl.flow_list[4].ret_handler[3].hander_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[2].err_code =  RET_PLAT_ACK_ERR;
	app_function_flow_ctrl.flow_list[4].ret_handler[3].hander_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;
	app_function_flow_ctrl.flow_list[4].ret_handler[2].err_code =  RET_PLAT_RECONNECT;
	app_function_flow_ctrl.flow_list[4].ret_handler[3].hander_index =  LOGIN_DISTRI_PLAT_STEP1_UDP;

}

