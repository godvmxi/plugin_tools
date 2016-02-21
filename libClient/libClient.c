#include "libClient.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
AppFunctionFlowCtrl app_function_flow_ctrl ;
AppDomainInfo  app_domain_info;

void get_version(){
  printf("version 0.1\n");
}
#define   DEBUG_FLOW_CONTROL  1

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

