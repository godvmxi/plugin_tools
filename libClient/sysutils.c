/*
 * sysutils.c
 *
 *  Created on: 2016-2-21
 *      Author: dan
 */
#include"sysutils.h"
#include <stdio.h>
//#include "capi.h"

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


int sysutils_get_json_boot(char *buf){

	return 0;
}
int sysutils_get_json_headbeat(char *buf){

}
int sysutils_get_json_token_update(char *buf){

}
int sysutils_get_json_boot_first(char *buf ){

}
int sysutils_get_json_register_first(char *buf){

}
int sysutils_parse_json_type(char *buf,int cmdType){

}
