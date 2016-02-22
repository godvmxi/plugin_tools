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
#include <logger.h>
#include "md5.h"
#include "base64.h"
//#include "capi.h"
int sysutils_active_rpc_counter = 0;
static int  __sysutils_get_vender(char *buf){
		sprintf(buf,"vendor 1.1");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_firmware_ver(char *buf){
		sprintf(buf,"sw 1.1");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_hardware_ver(char *buf){
		sprintf(buf,"hw 1.1");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_os_ver(char *buf){
		sprintf(buf,"os 1.1");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_app_ver(char *buf){
		sprintf(buf,"1.1");
		return 0;
		//use capi get system info
}

static int  __sysutils_get_wlan_ip_addr(char *buf){
		sprintf(buf,"223.5.5.5");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_plugin_info(char *name){


}
static int  __sysutils_get_wlan_mac(char *buf){
		char mac[] =  {0x84,0x82,0xf4,0x1c,0xe9,0x28 };
		sprintf(buf,"8482F41CE928");
		return 0;
		//use capi get system info
}

static int  __sysutils_get_platform_id(char *buf){
		sprintf(buf,"platform id test");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_card(char *buf){
		sprintf(buf,"1.1");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_sys_token(char *buf){
	sprintf(buf,"token data");
			return 0;
	//get storage token data
}
static int  __sysutils_get_sys_loid(char *buf){
	sprintf(buf,"loid data");
			return 0;
	//get storage token data
}
static int  __sysutils_get_sys_sn(char *buf){
	sprintf(buf,"sn data");
			return 0;
	//get storage token data
}
static int  __sysutils_get_sys_ssn(char *buf){
	sprintf(buf,"sn data");
			return 0;
	//get storage token data
}
static int  __sysutils_get_sys_time(char *buf){
	time_t timer ;
	struct tm * t_tm;
	time(&timer);
	t_tm = localtime(&timer);
	sprintf(buf,"%4d%02d%02d%02d%02d",t_tm->tm_year+1900,t_tm->tm_mon,t_tm->tm_mday,t_tm->tm_hour,t_tm->tm_min);
	for(int i = 0 ;i<strlen(buf);i++){
		if(buf[i] == ' '){
			buf[i] = '0';
		}
	}
			return 0;
	//get storage token data
}

static int  __sysutils_get_buf_md5(char *buf,char *md5){
	md5_calc(md5,buf,strlen(buf));
	//printf("md5: %s ->%s\n",buf,md5);
			return 0;
	//get storage token data
}

int sysutils_get_json_rpc_boot(char *buf){


	char loid[64] = {0};
	if (__sysutils_get_sys_loid(loid) <  0){
		//return 0;
	}
	char mac[20] = {0};
	if (__sysutils_get_wlan_mac(mac) < 0){
		//return 0;
	}
	char token[64] = {0};
	if (__sysutils_get_sys_token(token) < 0){
		//return 0;
	}

	//srand( (unsigned)time( NULL ) );
	//thread safe
	//json_object_seed(rand());
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
	json_object_set(obj,"ID",counter_obj);
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
	char ip[64] = {0};
	if (__sysutils_get_wlan_ip_addr(ip) <  0){
		//return 0;
	}
	char mac[20] = {0};
	if (__sysutils_get_wlan_mac(mac) < 0){
		//return 0;
	}
	char token[64] = {0};
	if (__sysutils_get_sys_token(token) < 0){
		//return 0;
	}

	//srand( (unsigned)time( NULL ) );
	//thread safe
	//json_object_seed(rand());
	json_t *obj = json_object();
	//file rpc
	json_t *rpc_obj =  json_string("Heartbeat");
	json_object_set(obj,"RpcMethod",rpc_obj);
	//file loid
	json_t *ip_obj =  json_string(ip);
	json_object_set(obj,"IPAddr",ip_obj);
	//file mac
	json_t *mac_obj =  json_string(mac);
	json_object_set(obj,"MAC",mac_obj);

	//fill counter
		json_t *counter_obj = json_integer (sysutils_active_rpc_counter++ );
		json_object_set(obj,"ID",counter_obj);
		//dump

	char *result =  json_dumps(obj,JSON_COMPACT);
	memcpy(buf,result,strlen(result));
	json_decref(rpc_obj);
	json_decref(ip_obj);
	json_decref(mac_obj);
	json_decref(obj);
	free(result);
	return 0;
}
/*
 *
 * message_len is limited short than 512
 * */
int sysutils_get_json_rpc_message_push(char *buf,char *plugin_name,char *message,int message_len){
		char sn[64] = {0};
		if (__sysutils_get_sys_sn(sn) <  0){
			//return 0;
		}
		char mac[20] = {0};
		if (__sysutils_get_wlan_mac(mac) < 0){
			//return 0;
		}
		char time[20] = {0};
			if (__sysutils_get_sys_time(time) < 0){
				//return 0;
			}
		//LOG_DEBUG("current system time ->%s\n",time);
		if (message_len > 512){
			message_len = 512;
			LOG_DEBUG("message will be cut short to 512\n");
		}
		char message_base64[2048] = {0};
		char *p = message;
	 base64_encode(message,message_base64,message_len);
		//LOG_DEBUG("base64: %s  -> %s\n",p,message_base64);
		message = p;



		char md5_hash_input[2048] =  {0};
		sprintf(md5_hash_input,"%s%s%s%s",time,message_base64,mac,sn);
		//printf("will hash-> %s\n",md5_hash_input);

		char temp[20] = {0};
		if (__sysutils_get_buf_md5( md5_hash_input,temp) < 0){
			//return 0;
		}

		char md5[20] = {0};
		hash_bin2hex(temp,md5,16);

		//printf("\nmd5->>>>>%d  %s\n",strlen(md5),md5);


		//srand( (unsigned)time( NULL ) );
		//thread safe
		//json_object_seed(rand());
		json_t *obj = json_object();
		//file rpc
		json_t *rpc_obj =  json_string("MessagePush");
		json_object_set(obj,"RpcMethod",rpc_obj);
		//file plugin name
		json_t *plugin_name_obj =  json_string(plugin_name);
		json_object_set(obj,"Plugin_Name",plugin_name_obj);
		//file time
		json_t *time_obj =  json_string(time);
		json_object_set(obj,"time",time_obj);

		json_t *md5_obj =  json_string(md5);
		json_object_set(obj,"MD5",md5_obj);
		//file Message
		json_t *message_obj =  json_string(message_base64);
				json_object_set(obj,"Message",message_obj);
		//fill counter
		json_t *counter_obj = json_integer (sysutils_active_rpc_counter++ );
		json_object_set(obj,"ID",counter_obj);
		//dump
		char *result =  json_dumps(obj,JSON_COMPACT);
		memcpy(buf,result,strlen(result));
		//free all
		json_decref(rpc_obj);
		json_decref(plugin_name_obj);
		json_decref(time_obj);
		json_decref(md5_obj);
		json_decref(message_obj);
		json_decref(counter_obj);
		json_decref(obj);
		free(result);

		return 0;
}
int sysutils_get_json_rpc_token_update(char *buf){
	char ssn[64] = {0};
			if (__sysutils_get_sys_ssn(ssn) <  0){
				//return 0;
			}
			char time[20] = {0};
				if (__sysutils_get_sys_time(time) < 0){
					//return 0;
				}
			//LOG_DEBUG("current system time ->%s\n",time);

			char token[128] = {0};
			if(__sysutils_get_sys_token(token) < 0 ){
				//
			}
			//char new_token[128] = {0};

			char md5_hash_input[128] =  {0};
			sprintf(md5_hash_input,"%s%s%s",time,ssn,time);
			printf("will hash-> %s\n",md5_hash_input);

			char temp[20] = {0};
			if (__sysutils_get_buf_md5( md5_hash_input,temp) < 0){
				//return 0;
			}

			char md5[20] = {0};
			hash_bin2hex(temp,md5,16);

			//printf("\nmd5->>>>>%d  %s\n",strlen(md5),md5);


			//srand( (unsigned)time( NULL ) );
			//thread safe
			//json_object_seed(rand());
			json_t *obj = json_object();
			//file rpc
			json_t *rpc_obj =  json_string("TokenUpdate");
			json_object_set(obj,"RpcMethod",rpc_obj);

			//file token
			json_t *token_obj =  json_string(token);
			json_object_set(obj,"Token",token_obj);

			//file time
						json_t *time_obj =  json_string(time);
						json_object_set(obj,"time",time_obj);

			json_t *md5_obj =  json_string(md5);
			json_object_set(obj,"MD5",md5_obj);

			//fill counter
			json_t *counter_obj = json_integer (sysutils_active_rpc_counter++ );
			json_object_set(obj,"ID",counter_obj);
			//dump
			char *result =  json_dumps(obj,JSON_COMPACT);
			memcpy(buf,result,strlen(result));
			//free all
			json_decref(rpc_obj);
			json_decref(token_obj);
			json_decref(time_obj);
			json_decref(md5_obj);
			json_decref(counter_obj);
			json_decref(obj);
			free(result);

			return 0;
}
int sysutils_get_json_rpc_boot_first(char *buf ){
	 char vendor[64] = {0};
		if (__sysutils_get_vender(vendor) <  0){
			//return 0;
		}
		char firmware_ver[64] = {0};
		if (__sysutils_get_firmware_ver(firmware_ver) <  0){
					//return 0;
		}
		char hardware_ver[20] = {0};
		if (__sysutils_get_hardware_ver(hardware_ver) < 0){
			//return 0;
		}
		char mac[64] = {0};
		if (__sysutils_get_wlan_mac(mac) < 0){
			//return 0;
		}
		char ip[64] = {0};
		if (__sysutils_get_wlan_ip_addr(ip) < 0){
			//return 0;
		}
		char platform_id[64] = {0};
		if (__sysutils_get_platform_id(platform_id) < 0){
			//return 0;
		}


		//srand( (unsigned)time( NULL ) );
		//thread safe
		//json_object_seed(rand());
		json_t *obj = json_object();
		//file rpc
		json_t *rpc_obj =  json_string("BootFirst");
		json_object_set(obj,"RpcMethod",rpc_obj);
		//file vendor
		json_t *vendor_obj =  json_string(vendor);
		json_object_set(obj,"Vendor",vendor_obj);
		//file vendor
				json_t *firmware_ver_obj =  json_string(firmware_ver);
				json_object_set(obj,"FirmwareVer",firmware_ver_obj);
				//file hardware ver
						json_t *hardware_ver_obj =  json_string(hardware_ver);
						json_object_set(obj,"HardwareVer",hardware_ver_obj);
		//file mac
		json_t *mac_obj =  json_string(mac);
		json_object_set(obj,"MAC",mac_obj);
		//file ip
		json_t *ip_obj =  json_string(ip);
		json_object_set(obj,"IPAddr",ip_obj);
		//file platform
		json_t *platform_id_obj =  json_string(platform_id);
		json_object_set(obj,"PlatformID",platform_id_obj);

		//fill counter
			json_t *counter_obj = json_integer (sysutils_active_rpc_counter++ );
			json_object_set(obj,"ID",counter_obj);
			//dump

		char *result =  json_dumps(obj,JSON_COMPACT);
		memcpy(buf,result,strlen(result));
		json_decref(rpc_obj);
		json_decref(vendor_obj);
		json_decref(firmware_ver_obj);
		json_decref(hardware_ver_obj);
		json_decref(mac_obj);
		json_decref(ip_obj);
		json_decref(platform_id_obj);

		json_decref(obj);
		free(result);
		return strlen(buf);
}
int sysutils_get_json_rpc_register_first(char *buf){
	 char vendor[64] = {0};
		if (__sysutils_get_vender(vendor) <  0){
			//return 0;
		}
		char firmware_ver[64] = {0};
		if (__sysutils_get_firmware_ver(firmware_ver) <  0){
					//return 0;
		}
		char hardware_ver[20] = {0};
		if (__sysutils_get_hardware_ver(hardware_ver) < 0){
			//return 0;
		}
		char mac[64] = {0};
		if (__sysutils_get_wlan_mac(mac) < 0){
			//return 0;
		}
		char ip[64] = {0};
		if (__sysutils_get_wlan_ip_addr(ip) < 0){
			//return 0;
		}
		char platform_id[64] = {0};
		if (__sysutils_get_platform_id(platform_id) < 0){
			//return 0;
		}


		//srand( (unsigned)time( NULL ) );
		//thread safe
		//json_object_seed(rand());
		json_t *obj = json_object();
		//file rpc
		json_t *rpc_obj =  json_string("BootFirst");
		json_object_set(obj,"RpcMethod",rpc_obj);
		//file vendor
		json_t *vendor_obj =  json_string(vendor);
		json_object_set(obj,"Vendor",vendor_obj);
		//file vendor
				json_t *firmware_ver_obj =  json_string(firmware_ver);
				json_object_set(obj,"FirmwareVer",firmware_ver_obj);
				//file hardware ver
						json_t *hardware_ver_obj =  json_string(hardware_ver);
						json_object_set(obj,"HardwareVer",hardware_ver_obj);
		//file mac
		json_t *mac_obj =  json_string(mac);
		json_object_set(obj,"MAC",mac_obj);
		//file ip
		json_t *ip_obj =  json_string(ip);
		json_object_set(obj,"IPAddr",ip_obj);
		//file platform
		json_t *platform_id_obj =  json_string(platform_id);
		json_object_set(obj,"PlatformID",platform_id_obj);

		//fill counter
			json_t *counter_obj = json_integer (sysutils_active_rpc_counter++ );
			json_object_set(obj,"ID",counter_obj);
			//dump

		char *result =  json_dumps(obj,JSON_COMPACT);
		memcpy(buf,result,strlen(result));
		json_decref(rpc_obj);
		json_decref(vendor_obj);
		json_decref(firmware_ver_obj);
		json_decref(hardware_ver_obj);
		json_decref(mac_obj);
		json_decref(ip_obj);
		json_decref(platform_id_obj);

		json_decref(obj);
		free(result);
		return 0;
}
int sysutils_parse_rpc_json_type(char *buf,int cmdType){
	 char vendor[64] = {0};
		if (__sysutils_get_vender(vendor) <  0){
			//return 0;
		}
		char firmware_ver[64] = {0};
		if (__sysutils_get_firmware_ver(firmware_ver) <  0){
					//return 0;
		}
		char hardware_ver[20] = {0};
		if (__sysutils_get_hardware_ver(hardware_ver) < 0){
			//return 0;
		}
		char mac[64] = {0};
		if (__sysutils_get_wlan_mac(mac) < 0){
			//return 0;
		}
		char ip[64] = {0};
		if (__sysutils_get_wlan_ip_addr(ip) < 0){
			//return 0;
		}
		char platform_id[64] = {0};
		if (__sysutils_get_platform_id(platform_id) < 0){
			//return 0;
		}


		//srand( (unsigned)time( NULL ) );
		//thread safe
		//json_object_seed(rand());
		json_t *obj = json_object();
		//file rpc
		json_t *rpc_obj =  json_string("BootFirst");
		json_object_set(obj,"RpcMethod",rpc_obj);
		//file vendor
		json_t *vendor_obj =  json_string(vendor);
		json_object_set(obj,"Vendor",vendor_obj);
		//file vendor
				json_t *firmware_ver_obj =  json_string(firmware_ver);
				json_object_set(obj,"FirmwareVer",firmware_ver_obj);
				//file hardware ver
						json_t *hardware_ver_obj =  json_string(hardware_ver);
						json_object_set(obj,"HardwareVer",hardware_ver_obj);
		//file mac
		json_t *mac_obj =  json_string(mac);
		json_object_set(obj,"MAC",mac_obj);
		//file ip
		json_t *ip_obj =  json_string(ip);
		json_object_set(obj,"IPAddr",ip_obj);
		//file platform
		json_t *platform_id_obj =  json_string(platform_id);
		json_object_set(obj,"PlatformID",platform_id_obj);

		//fill counter
			json_t *counter_obj = json_integer (sysutils_active_rpc_counter++ );
			json_object_set(obj,"ID",counter_obj);
			//dump

		char *result =  json_dumps(obj,JSON_COMPACT);
		memcpy(buf,result,strlen(result));
		json_decref(rpc_obj);
		json_decref(vendor_obj);
		json_decref(firmware_ver_obj);
		json_decref(hardware_ver_obj);
		json_decref(mac_obj);
		json_decref(ip_obj);
		json_decref(platform_id_obj);

		json_decref(obj);
		free(result);
		return 0;
}
