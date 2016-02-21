/*
 * sysutils.c
 *
 *  Created on: 2016-2-21
 *      Author: dan
 */
#include"sysutils.h"
#include <stdio.h>
#include <jansson.h>
#include <time.h>
#include <string.h>

//#include "capi.h"
int sysutils_active_rpc_counter = 0;
static int  __sysutils_get_vender(char *buf){
		sprintf(buf,"1.1");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_fireware_ver(char *buf){
		sprintf(buf,"1.1");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_hardware_ver(char *buf){
		sprintf(buf,"1.1");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_os_ver(char *buf){
		sprintf(buf,"1.1");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_app_ver(char *buf){
		sprintf(buf,"1.1");
		return 0;
		//use capi get system info
}

static int  __sysutils_get_wlan_ip_addr(char *buf){
		sprintf(buf,"1.1");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_plugin_info(char *name){


}
static int  __sysutils_get_wlan_mac(char *buf){
		sprintf(buf,"00112233445566");
		return 0;
		//use capi get system info
}

static int  __sysutils_get_platform_id(char *buf){
		sprintf(buf,"1.1");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_card(char *buf){
		sprintf(buf,"1.1");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_token(char *buf){
	sprintf(buf,"token data");
			return 0;
	//get storage token data
}
static int  __sysutils_get_loid(char *buf){
	sprintf(buf,"loid data");
			return 0;
	//get storage token data
}

int sysutils_get_json_rpc_boot(char *buf){


	char loid[64] = {0};
	if (__sysutils_get_loid(loid) <  0){
		//return 0;
	}
	char mac[20] = {0};
	if (__sysutils_get_wlan_mac(mac) < 0){
		//return 0;
	}
	char token[64] = {0};
	if (__sysutils_get_token(token) < 0){
		//return 0;
	}

	srand( (unsigned)time( NULL ) );
	json_object_seed(rand());
	json_t *obj = json_object();
	//file rpc
	json_t *rpc_obj =  json_string("Boot");
	json_object_set(obj,"RpcMethod",rpc_obj);
	//file loid
	json_t *loid_obj =  json_string(loid);
	json_object_set(obj,"LOID",loid_obj);
	//file mac
	json_t *mac_obj =  json_string(mac);
	json_object_set(obj,"MAC",mac_obj);
	json_t *token_obj =  json_string(token);
	json_object_set(obj,"Token",token_obj);
	//fill counter
	json_t *counter_obj = json_integer (sysutils_active_rpc_counter++ );
	json_object_set(obj,"Counter",counter_obj);
	//dump
	char *result =  json_dumps(obj,JSON_COMPACT);
	memcpy(buf,result,strlen(result));
	//free all
	json_decref(rpc_obj);
	json_decref(loid_obj);
	json_decref(mac_obj);
	json_decref(token_obj);
	json_decref(counter_obj);
	json_decref(obj);
	free(result);

	return 0;
}
int sysutils_get_json_rpc_headbeat(char *buf){
	char loid[64] = {0};
	if (__sysutils_get_loid(loid) <  0){
		//return 0;
	}
	char mac[20] = {0};
	if (__sysutils_get_wlan_mac(mac) < 0){
		//return 0;
	}
	char token[64] = {0};
	if (__sysutils_get_token(token) < 0){
		//return 0;
	}

	srand( (unsigned)time( NULL ) );
	json_object_seed(rand());
	json_t *obj = json_object();
	//file rpc
	json_t *rpc_obj =  json_string("Boot");
	json_object_set(obj,"RpcMethod",rpc_obj);
	//file loid
	json_t *loid_obj =  json_string(loid);
	json_object_set(obj,"LOID",loid_obj);
	//file mac
	json_t *mac_obj =  json_string(mac);
	json_object_set(obj,"MAC",mac_obj);
	//fill Token
	json_t *token_obj =  json_string(token);
	json_object_set(obj,"Token",token_obj);
	//fill counter
		json_t *counter_obj = json_integer (sysutils_active_rpc_counter++ );
		json_object_set(obj,"Counter",counter_obj);
		//dump

	char *result =  json_dumps(obj,JSON_COMPACT);
	memcpy(buf,result,strlen(result));
	json_decref(rpc_obj);
	json_decref(loid_obj);
	json_decref(mac_obj);
	json_decref(token_obj);
	json_decref(obj);
	free(result);
	return 0;
}
int sysutils_get_json_rpc_token_update(char *buf){

}
int sysutils_get_json_rpc_boot_first(char *buf ){

}
int sysutils_get_json_rpc_register_first(char *buf){

}
int sysutils_parse_rpc_json_type(char *buf,int cmdType){

}
