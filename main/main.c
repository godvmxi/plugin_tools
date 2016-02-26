/*
 ============================================================================
 Name        : exampleProgram.c
 Author      : Bright Jiang
 Version     :
 Copyright   : GPL
 Description : Uses shared library to print greeting
               To run the resulting executable the LD_LIBRARY_PATH must be
               set to ${project_loc}/libClient/.libs
               Alternatively, libtool creates a wrapper shell script in the
               build directory of this program which can be used to run it.
               Here the script will be called exampleProgram.
 ============================================================================
 */

#include "libClient.h"
#include "stdio.h"
#include "stdlib.h"
#include "logger.h"
#include "netutils.h"
#include "sysutils.h"


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <capisys.h>
#include <unistd.h>

#include "capi-app-mgr.h"

int main(int argc, char **argv) {
//	if (argc != 2) {
//		fprintf(stderr, "Usage: %s hostname\n", argv[1]);
//		exit(1);
//	}
//
//	printf(">>>>>>\n");
//	char ipResult[200] = {0};
//	int number = get_ip_list_from_domain(argv[1],ipResult,4,20);

	char buffer[1024];
	/*  */
	pthread_t thread_network_handler ;
	pthread_t thread_capi_handler ;
	pthread_t thread_downlink_handler ;
//	pthread_t thread_autouplink_handler ;  //receive uplink signal from dbus or other ???
	//basic init 
	app_function_flow_ctrl_init();
	app_function_capisys_init();
	app_function_parse_fifo_buffer_init();
	
	CtSgwSetDbusEnv();

	int ret = 0;

	ret = pthread_create(&thread_network_handler,	NULL,(void *)app_function_flow_ctrl_thread ,NULL);
	if(ret != 0 ){
		LOGGER_ERR("create thread network handler error\n");
		exit(1);
	}
	ret = pthread_create(&thread_capi_handler,		NULL,(void *)app_function_capisys_thread ,NULL);
	if(ret != 0 ){
		LOGGER_ERR("create thread capi handler  error\n");
		exit(1);
	}
	ret = pthread_create(&thread_downlink_handler,	NULL,(void *)app_function_parse_fifo_buffer_thread ,NULL);
	if(ret != 0 ){
		LOGGER_ERR("create thread downlink hander error\n");
		exit(1);
	}
	//LOG_DEBUG("maini app is runing ,waiting for all \n");
	sleep(2);
	pthread_join(thread_network_handler,NULL);
	pthread_join(thread_capi_handler,NULL);
	pthread_join(thread_downlink_handler,NULL);
	while(1){
		sleep(1);
	}
	return 0 ;

	while(0){
		memset(buffer,0,1024);
		sysutils_get_json_rpc_boot(buffer);
		printf("boot       ->%s\n",buffer);
		memset(buffer,0,1024);
		sysutils_get_json_rpc_headbeat(buffer);
		printf("Heartbeat  ->%s\n",buffer);
		memset(buffer,0,1024);
		sysutils_get_json_rpc_message_push(buffer,"test_plugin","test_message",12);
		printf("Push Message  ->%s\n",buffer);

		memset(buffer,0,1024);
		sysutils_get_json_rpc_token_update(buffer);
		printf("TokenUpdate   ->%s\n",buffer);


		memset(buffer,0,1024);
		sysutils_get_json_rpc_boot_first(buffer);
		printf("BootFirst   ->%s\n",buffer);

		memset(buffer,0,1024);
		sysutils_get_json_rpc_token_update(buffer);
		printf("ResisterFirst   ->%s\n",buffer);
		memset(buffer,0,1024);
		sysutils_get_json_rpc_token_update(buffer);
		printf("TokenUpdate   ->%s\n",buffer);

		break;
	}
	app_funcion_flow_ctrl_init();
	//app_funcion_flow_ctrl_start();

//	login_distri_plat_step1_udp(NULL);


	exit(0);
}
