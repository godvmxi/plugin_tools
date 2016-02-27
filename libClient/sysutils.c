/*
 * sysutils.c
 *
 *  Created on: 2016-2-21
 *      Author: dan
 */
#include <stdio.h>
#include <stdlib.h>
#include <jansson.h>
#include <time.h>
#include <string.h>
#include <assert.h>
#include <jansson.h>
#include <stdarg.h>

#include "fifobuffer.h"
#include "logger.h"
#include "sysutils.h"
#include "md5.h"
#include "base64.h"

#include "capi.h"
extern FIFO_BUFFER_HEADER socket_tx_fifo_header;
//#include "capi.h"
int sysutils_active_rpc_counter = 0;
static int  __sysutils_get_vender(char *buf){
#ifdef   CAPI_INTERFACE_NULL_TEST
		sprintf(buf,"XXXX");
#else 
		
#endif 
		return 0;
		//use capi get system info
}
static int  __sysutils_get_firmware_ver(char *buf){
		sprintf(buf,"v1.230");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_hardware_ver(char *buf){
		sprintf(buf,"sd3.64.418");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_os_ver(char *buf){
		sprintf(buf,"ZhiNengWangGuan OS 1");
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
		sprintf(buf,"48555F44CA00");
		return 0;
		//use capi get system info
}

static int  __sysutils_get_platform_id(char *buf){
		sprintf(buf,"OSGI");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_card(char *buf){
		sprintf(buf,"");
		return 0;
		//use capi get system info
}
static int  __sysutils_get_sys_token(char *buf){
	sprintf(buf,"token data");
			return 0;
	//get storage token data
}
static int  __sysutils_get_sys_loid(char *buf){
	sprintf(buf,"SMARTHUBG07");
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
int sysutils_get_json_rpc_heartbeat(char *buf){
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
	return strlen(buf);
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
		//LOGGER_DBG("current system time ->%s\n",time);
		if (message_len > 512){
			message_len = 512;
			LOGGER_DBG("message will be cut short to 512\n");
		}
		char message_base64[2048] = {0};
		char *p = message;
	 base64_encode(message,message_base64,message_len);
		//LOGGER_DBG("base64: %s  -> %s\n",p,message_base64);
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
		return strlen(buf);

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
			//LOGGER_DBG("current system time ->%s\n",time);

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
			return strlen(buf);

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
#ifdef DISTRI_SERVER_TEMP_TEST
		json_t *rpc_obj =  json_string("Boot");
#else 
		json_t *rpc_obj =  json_string("BootFirst");
#endif
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
#ifdef  DISTRI_SERVER_TEMP_TEST
		json_t *dev_rnd_obj = json_string("44464135443C07090878276F5D4D187F");
		json_object_set(obj,"DevRND",dev_rnd_obj);
		json_t *card_obj = json_string("");
		json_object_set(obj,"Card",card_obj);
		json_t *loid_obj = json_string("SMARTHUBG07");
		json_object_set(obj,"LOID",loid_obj);
		json_t *os_obj = json_string("ZhiNengWangGuan OS 1");
		json_object_set(obj,"OsVer",os_obj);

#endif 

		char *result =  json_dumps(obj,JSON_COMPACT);
		memcpy(buf,result,strlen(result));
		json_decref(rpc_obj);
		json_decref(vendor_obj);
		json_decref(firmware_ver_obj);
		json_decref(hardware_ver_obj);
		json_decref(mac_obj);
		json_decref(ip_obj);
		json_decref(platform_id_obj);
#ifdef  DISTRI_SERVER_TEMP_TEST
		json_decref(dev_rnd_obj);
		json_decref(card_obj);
		json_decref(loid_obj);
		json_decref(os_obj);

#endif 
#ifdef  DISTRI_SERVER_TEMP_TEST
		if(dev_rnd_obj) json_decref(dev_rnd_obj);
		if(card_obj) json_decref(card_obj);
		if(loid_obj) json_decref(loid_obj);

#endif 
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
		return strlen(buf);
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
		return strlen(buf);
}

int sysutils_parse_distri_server_ack_step_1(char *buf,int *result,char *challenge_code,int *interval,char * server_ip){
	json_error_t json_error ;
	json_t *json_root  = NULL;
	json_t *obj_result = NULL;
	json_t *obj_challenge_code = NULL;
	json_t *obj_interval = NULL;
	json_t *obj_server_ip =  NULL;
	char *temp= NULL;

	assert(buf == NULL) ;
	assert(result ==  NULL);
	assert(challenge_code == NULL);
	assert(interval == NULL );
	assert(server_ip == NULL);

	json_root = json_loads(buf, 0 ,&json_error);
	if (json_root == NULL){
		LOGGER_ERR("parse json error -> %s\n",buf);
		goto sysutils_parse_distri_server_ack_step_1_error ;
	}
	//Result
	obj_result =  json_object_get(json_root,"Result" ) ;
	if (json_is_number(obj_result)  ==  JSON_TRUE ){
		*result = json_integer_value(obj_result) ;
	}
	else if(json_is_string(obj_result ) ==  JSON_TRUE ){
		temp =  (char *) json_string_value(obj_result ) ;
		if (temp != NULL) {
						*result = atoi(temp);
						free(temp);
					 }
					 else {
						 	 LOGGER_ERR("reuslt get result code error\n");
						 		goto sysutils_parse_distri_server_ack_step_1_error ;
					 }

	}
	else {
		LOGGER_ERR("reuslt value error\n");
		goto sysutils_parse_distri_server_ack_step_1_error ;
	}
	//ChallengeCode
	obj_challenge_code =  json_object_get(json_root,"ChallengeCode" ) ;
		 if(json_is_string(obj_challenge_code ) ==  JSON_TRUE ){
			 temp =  (char *) json_string_value(obj_challenge_code) ;
			 if (temp != NULL) {
				memcpy(challenge_code,  temp,strlen(temp) ) ;
				free(temp);
			 }
			 else {
				 	 LOGGER_ERR("reuslt get challenge code error\n");
				 		goto sysutils_parse_distri_server_ack_step_1_error ;
			 }
		}
		else {
			LOGGER_ERR("reuslt challenge code error\n");
			goto sysutils_parse_distri_server_ack_step_1_error ;
		}

	 //interval code
		obj_interval =  json_object_get(json_root,"Interval" ) ;
		if (json_is_number(obj_interval)  ==  JSON_TRUE ){
				 		*interval = json_integer_value(obj_interval) ;
				 	}
		else		if(json_is_string(obj_interval ) ==  JSON_TRUE ){
				 temp =  (char *) json_string_value(obj_interval) ;
				 if (temp != NULL) {
					 *interval = atoi(temp);
					free(temp);
				 }
				 else {
						 LOGGER_ERR("reuslt get obj_intervale error\n");
							goto sysutils_parse_distri_server_ack_step_1_error ;
				 }
			}
			else {
				LOGGER_ERR("reuslt obj_interval error\n");
				goto sysutils_parse_distri_server_ack_step_1_error ;
			}
		//ip addr
		 obj_server_ip =  json_object_get(json_root,"ServerIP" ) ;
		 		 if(json_is_string(obj_server_ip ) ==  JSON_TRUE ){
						 temp =  (char *) json_string_value(obj_server_ip) ;
						 if (temp != NULL) {
							memcpy(server_ip,  temp,strlen(temp) ) ;
							free(temp);
						 }
						 else {
								 LOGGER_ERR("reuslt get obj_server_ip  error\n");
									goto sysutils_parse_distri_server_ack_step_1_error ;
						 }
					}
					else {
						LOGGER_ERR("reuslt obj_server_ip error\n");
						goto sysutils_parse_distri_server_ack_step_1_error ;
			 			}


	json_decref(json_root);
	return 0;
sysutils_parse_distri_server_ack_step_1_error :
	if (json_root != NULL) {
		json_decref(json_root);
	}
	if (obj_result != NULL) {
			json_decref(obj_result);
		}
	if (obj_challenge_code != NULL) {
			json_decref(obj_challenge_code);
		}
	if (obj_interval != NULL) {
			json_decref(obj_interval);
		}
	if (obj_server_ip != NULL) {
				json_decref(obj_server_ip);
			}
	return -1 ;



}

int sysutils_parse_distri_server_ack_step_2(char *buf,
		int *result,
		char *server_addr,
		unsigned int *server_port,
		int *interval,
		char * server_ip,
		char *token,
		char *exp_date,
		char *ca_download_url)
{
	json_error_t json_error ;
		json_t *json_root  = NULL;
		json_t *obj_result = NULL;
		json_t *obj_challenge_code = NULL;
		json_t *obj_interval = NULL;
		json_t *obj_server_ip =  NULL;
		json_t *obj_server_addr = NULL;
		json_t *obj_server_port = NULL;
		json_t *obj_token = NULL;
		json_t *obj_exp_date = NULL;
		json_t *obj_ca_download_url = NULL;


		char *temp= NULL;

		assert(buf == NULL) ;
		assert(result ==  NULL);
		assert(server_addr == NULL);
		assert(server_port == NULL);
		assert(interval == NULL);
		assert(server_ip == NULL);
		assert(token == NULL);
		assert(exp_date == NULL );
		assert(ca_download_url == NULL );


		json_root = json_loads(buf, 0 ,&json_error);
		if (json_root == NULL){
			LOGGER_ERR("parse json error -> %s\n",buf);
			goto sysutils_parse_distri_server_ack_step_2_error ;
		}
		//Result
		obj_result =  json_object_get(json_root,"Result" ) ;
		if (json_is_number(obj_result)  ==  JSON_TRUE ){
			*result = json_integer_value(obj_result) ;
		}
		else if(json_is_string(obj_result ) ==  JSON_TRUE ){
			temp =  (char *) json_string_value(obj_result ) ;
			if (temp != NULL) {
							*result = atoi(temp);
							free(temp);
						 }
						 else {
							 	 LOGGER_ERR("reuslt get result code error\n");
							 		goto sysutils_parse_distri_server_ack_step_2_error ;
						 }

		}
		else {
			LOGGER_ERR("reuslt value error\n");
			goto sysutils_parse_distri_server_ack_step_2_error ;
		}
		//ServerAddr
		obj_challenge_code =  json_object_get(json_root,"ServerAddr" ) ;
			 if(json_is_string(obj_challenge_code ) ==  JSON_TRUE ){
				 temp =  (char *) json_string_value(obj_challenge_code) ;
				 if (temp != NULL) {
					memcpy(server_addr,  temp,strlen(temp) ) ;
					free(temp);
				 }
				 else {
					 	 LOGGER_ERR("reuslt get server_addr code error\n");
					 		goto sysutils_parse_distri_server_ack_step_2_error ;
				 }
			}
			else {
				LOGGER_ERR("reuslt server_addr code error\n");
				goto sysutils_parse_distri_server_ack_step_2_error ;
			}
			 //ServerPort
			 		obj_challenge_code =  json_object_get(json_root,"ServerPort" ) ;
			 			 if(json_is_string(obj_challenge_code ) ==  JSON_TRUE ){
			 				 temp =  (char *) json_string_value(obj_challenge_code) ;
			 				 if (temp != NULL) {
			 					memcpy(server_port,  temp,strlen(temp) ) ;
			 					free(temp);
			 				 }
			 				 else {
			 					 	 LOGGER_ERR("reuslt get server_port code error\n");
			 					 		goto sysutils_parse_distri_server_ack_step_2_error ;
			 				 }
			 			}
			 			else {
			 				LOGGER_ERR("reuslt server_port code error\n");
			 				goto sysutils_parse_distri_server_ack_step_2_error ;
			 			}


		 //interval code
			obj_interval =  json_object_get(json_root,"Interval" ) ;
			if (json_is_number(obj_interval)  ==  JSON_TRUE ){
					 		*interval = json_integer_value(obj_interval) ;
					 	}
			else		if(json_is_string(obj_interval ) ==  JSON_TRUE ){
					 temp =  (char *)  json_string_value(obj_interval) ;
					 if (temp != NULL) {
						 *interval = atoi(temp);
						free(temp);
					 }
					 else {
							 LOGGER_ERR("reuslt get obj_intervale error\n");
								goto sysutils_parse_distri_server_ack_step_2_error ;
					 }
				}
				else {
					LOGGER_ERR("reuslt obj_interval error\n");
					goto sysutils_parse_distri_server_ack_step_2_error ;
				}
			//ServerIP
			 obj_server_ip =  json_object_get(json_root,"ServerIP" ) ;
			 		 if(json_is_string(obj_server_ip ) ==  JSON_TRUE ){
							 temp =  (char *)  json_string_value(obj_server_ip) ;
							 if (temp != NULL) {
								memcpy(server_ip,  temp,strlen(temp) ) ;
								free(temp);
							 }
							 else {
									 LOGGER_ERR("reuslt get obj_server_ip  error\n");
										goto sysutils_parse_distri_server_ack_step_2_error ;
							 }
						}
						else {
							LOGGER_ERR("reuslt obj_server_ip error\n");
							goto sysutils_parse_distri_server_ack_step_2_error ;
				 			}
		//Token
		obj_token =  json_object_get(json_root,"Token" ) ;
		if(json_is_string(obj_token ) ==  JSON_TRUE ){
		temp =  (char *) json_string_value(obj_token) ;
		if (temp != NULL) {
		memcpy(token,  temp,strlen(temp) ) ;
		free(temp);
		}
		else {
		LOGGER_ERR("reuslt get obj_token  error\n");
		goto sysutils_parse_distri_server_ack_step_2_error ;
		}
		}
		else {
		LOGGER_ERR("reuslt obj_token error\n");
		goto sysutils_parse_distri_server_ack_step_2_error ;
		}
		//ExpDate
		obj_exp_date =  json_object_get(json_root,"ExpDate" ) ;
		if(json_is_string(obj_exp_date ) ==  JSON_TRUE ){
			 temp =  (char *) json_string_value(obj_exp_date) ;
			 if (temp != NULL) {
				memcpy(exp_date,  temp,strlen(temp) ) ;
				free(temp);
			 }
			 else {
					 LOGGER_ERR("reuslt get obj_exp_date  error\n");
						goto sysutils_parse_distri_server_ack_step_2_error ;
			 }
		}
		else {
			LOGGER_ERR("reuslt obj_exp_date error\n");
			goto sysutils_parse_distri_server_ack_step_2_error ;
			}
		//CADownloadURL
				obj_ca_download_url =  json_object_get(json_root,"CADownloadURL" ) ;
				if(json_is_string(obj_ca_download_url ) ==  JSON_TRUE ){
					 temp =  (char *) json_string_value(obj_ca_download_url) ;
					 if (temp != NULL) {
						memcpy(ca_download_url,  temp,strlen(temp) ) ;
						free(temp);
					 }
					 else {
							 LOGGER_ERR("reuslt get obj_ca_download_url  error\n");
								goto sysutils_parse_distri_server_ack_step_2_error ;
					 }
				}
				else {
					LOGGER_ERR("reuslt obj_ca_download_url error\n");
					goto sysutils_parse_distri_server_ack_step_2_error ;
					}



		json_decref(json_root);
		json_decref(obj_result);
		json_decref(obj_challenge_code);
		json_decref(obj_interval);
		json_decref(obj_server_ip);
		json_decref(obj_server_addr);
		json_decref(obj_server_port);
		json_decref(obj_token);
		json_decref(obj_exp_date);
		json_decref(obj_ca_download_url);
		return 0;
	sysutils_parse_distri_server_ack_step_2_error :
		if (json_root != NULL) {
			json_decref(json_root);
		}
		if (obj_result != NULL) {
				json_decref(obj_result);
			}
		if (obj_challenge_code != NULL) {
				json_decref(obj_challenge_code);
			}
		if (obj_interval != NULL) {
				json_decref(obj_interval);
			}
		if (obj_server_ip != NULL) {
					json_decref(obj_server_ip);
				}
		if (obj_server_addr != NULL) {
			json_decref(obj_server_addr);
		}
		if (obj_server_port != NULL) {
				json_decref(obj_server_port);
			}
		if (obj_token != NULL) {
				json_decref(obj_token);
			}
		if (obj_exp_date != NULL) {
				json_decref(obj_exp_date);
			}
		if (obj_ca_download_url != NULL) {
					json_decref(obj_ca_download_url);
				}


		return -1 ;

}

int sysutils_parse_operate_login_ack(char *buf,int *result){
	json_error_t json_error ;
	json_t *json_root  = NULL;
	json_t *obj_result = NULL;
	json_t *obj_challenge_code = NULL;
	json_t *obj_interval = NULL;
	json_t *obj_server_ip =  NULL;
	char *temp= NULL;

	assert(buf == NULL) ;
	assert(result ==  NULL);

	json_root = json_loads(buf, 0 ,&json_error);
	if (json_root == NULL){
		LOGGER_ERR("parse json error -> %s\n",buf);
		goto sysutils_parse_operate_login_ack_error ;
	}
	//Result
	obj_result =  json_object_get(json_root,"Result" ) ;
	if (json_is_number(obj_result)  ==  JSON_TRUE ){
		*result = json_integer_value(obj_result) ;
	}
	else if(json_is_string(obj_result ) ==  JSON_TRUE ){
		temp =  (char *) json_string_value(obj_result ) ;
		if (temp != NULL) {
						*result = atoi(temp);
						free(temp);
					 }
					 else {
						 	 LOGGER_ERR("reuslt get result code error\n");
						 		goto sysutils_parse_operate_login_ack_error ;
					 }

	}
	else {
		LOGGER_ERR("reuslt value error\n");
		goto sysutils_parse_operate_login_ack_error ;
	}

	json_decref(obj_result);
	json_decref(json_root);
	return 0;
	sysutils_parse_operate_login_ack_error :
	if (json_root != NULL) {
		json_decref(json_root);
	}
	if (obj_result != NULL) {
			json_decref(obj_result);
		}
	if (obj_server_ip != NULL) {
				json_decref(obj_server_ip);
			}
	return -1 ;
}

int sysutils_parse_json_cmd_type(char *buf, RPC_METHOD_ENUM  *type , int ID){
	json_error_t json_error ;
	json_t *json_root  = NULL;
	json_t *obj_result = NULL;
	json_t *obj_challenge_code = NULL;
	int result = -1;
	char *temp;

	json_root = json_loads(buf, 0 ,&json_error);
	if (json_root == NULL){
		LOGGER_ERR("parse json error -> %s\n",buf);
		return -1;
	}
		//Result
		obj_result =  json_object_get(json_root,"Result" ) ;
		if (json_is_number(obj_result)  ==  JSON_TRUE ){
			result = json_integer_value(obj_result) ;
			*type = RPC_METHOD_ACK;
		}
		else if(json_is_string(obj_result ) ==  JSON_TRUE ){
			temp =  (char *) json_string_value(obj_result ) ;
			if (temp != NULL) {
				result = atoi(temp);
				free(temp);
			}
			else {
				LOGGER_ERR("reuslt get result code error\n");
				goto sysutils_parse_json_cmd_type_error ;
			}

		}
		else {
			LOGGER_ERR("reuslt value error\n");
			goto sysutils_parse_json_cmd_type_error ;
		}
sysutils_parse_json_cmd_type_error :
		if (json_root != NULL) {
			json_decref(json_root);
		}
		if (obj_result != NULL) {
			json_decref(obj_result);
		}
}
int sysutils_parse_json_is_result(char *buf,int *result ,int *id){
	json_error_t json_error ;
	json_t *json_root  = NULL;
	json_t *obj_result = NULL;
	json_t *obj_challenge_code = NULL;
	char *temp;

	json_root = json_loads(buf, 0 ,&json_error);
	if (json_root == NULL){
		LOGGER_ERR("parse json error -> %s\n",buf);
		return -1;
	}
	//Result
	obj_result =  json_object_get(json_root,"Result" ) ;
	if (json_is_number(obj_result)  ==  JSON_TRUE ){
		*result = json_integer_value(obj_result) ;
	}
	else if(json_is_string(obj_result ) ==  JSON_TRUE ){
		temp =  (char *) json_string_value(obj_result ) ;
		if (temp != NULL) {
			*result = atoi(temp);
			free(temp);
		}
		else {
			LOGGER_ERR("reuslt get result code error\n");
			goto sysutils_parse_json_is_result_error ;
		}

	}
	else {
		LOGGER_ERR("reuslt value error\n");
		goto sysutils_parse_json_is_result_error ;
	}
	return 0 ;
sysutils_parse_json_is_result_error :
	if (json_root != NULL) {
		json_decref(json_root);
	}
	if (obj_result != NULL) {
		json_decref(obj_result);
	}
}
/*
 * 
 *
 * return value : 1 :message is result ack 
 * 0: not result ack 
 * -1 :handler error 
 *
 */
int sysutils_try_handler_ack_result_message(char *buf){
	json_error_t json_error ;
	json_t *json_root  = NULL;
	json_t *obj_result = NULL;
	int result = 0 ;
	char *temp =NULL ;
	
	json_root = json_loads(buf, 0 ,&json_error);
	if (json_root == NULL){
		LOGGER_ERR("parse json error -> %s\n",buf);
		return -1;
	}
	//Result
	obj_result =  json_object_get(json_root,"Result" ) ;
	if(obj_result == NULL ){
		//not ack result
		return 0;
	}

	if (json_is_number(obj_result)  ==  JSON_TRUE ){
		result = json_integer_value(obj_result) ;
	}
	else if(json_is_string(obj_result ) ==  JSON_TRUE ){
		temp =  (char *) json_string_value(obj_result ) ;
		if (temp != NULL) {
			result = atoi(temp);
			free(temp);
		}
		else {
			LOGGER_ERR("reuslt get result code error\n");
			goto sysutils_try_handler_ack_result_message_error ;
		}

	}
	else {
		LOGGER_ERR("reuslt value error\n");
		goto sysutils_try_handler_ack_result_message_error ;
	}

	switch (result ){
		case  0: //ok ,try parse other info
			break ;
		case -1: //????
			LOGGER_DBG("ack result -1, how to handler it ?? \n");
			break;
		case -2 :
			LOGGER_DBG("ack result -2 ,how to handler it ??  \n");
			break ;
		case -3:
			LOGGER_DBG("device should re-register to distri_server\n");
			break;
	}

	if (obj_result != NULL){
		json_decref(obj_result);
	}
	if (json_root != NULL){
		json_decref(json_root);
	}
	return 1;
sysutils_try_handler_ack_result_message_error:
	if (obj_result != NULL){
		json_decref(obj_result);
	}
	if (json_root != NULL){
		json_decref(json_root);
	}

	return -1;
}
/*
 * 
 *
 * return value : 1 :message is result ack 
 * 0: not result ack 
 * -1 :handler error 
 *
 */
int sysutils_try_handler_server_push_message(char *buf){
	json_error_t json_error ;
	json_t *json_root  = NULL;
	json_t *obj_rpc_method = NULL;
	RPC_METHOD_ENUM rpc_method_type = 0 ;
	int result = 0 ;
	char *temp =NULL ;
	char rpc_method[20];
	
	json_root = json_loads(buf, 0 ,&json_error);
	if (json_root == NULL){
		LOGGER_ERR("parse json error -> %s\n",buf);
		return -1;
	}
	//Result
	obj_rpc_method =  json_object_get(json_root,"RPCMethod" ) ;
	if(obj_rpc_method == NULL ){
		//not ack result
		return 0;
	}

	if(json_is_string(obj_rpc_method ) ==  JSON_TRUE ){
		temp =  (char *) json_string_value(obj_rpc_method ) ;
		if (temp != NULL) {
			memcpy(rpc_method,temp,strlen(temp));
			free(temp);
		}
		else {
			LOGGER_ERR("get rpc method  error\n");
			goto sysutils_try_handler_server_push_message_error;
		}

	}
	else {
		LOGGER_ERR("rpc value is error\n");
		goto sysutils_try_handler_server_push_message_error;
	}
//	
	rpc_method_type =  sysutils_get_rpc_type(rpc_method);
/*
 * Disconnect
 * Install
 * Install_query
 * Install_cancel
 * UnInstall
 * Stop
 * Run
 * FactoryPlugin
 * ListPlugin
 * SetPlug-inParameterValues
 */
	switch(rpc_method_type) {
		case RPC_METHOD_DISCONNECT :
			sysutils_downlink_rpc_handler_disconnect(json_root);
			break;
		case RPC_METHOD_INSTALL :
			sysutils_downlink_rpc_handler_install(json_root);

			break;
		case RPC_METHOD_INSTALL_QUERY :
			sysutils_downlink_rpc_handler_install_query(json_root);

			break;
		case RPC_METHOD_INSTALL_CANCEL :
			sysutils_downlink_rpc_handler_install_query(json_root);

			break;
		case RPC_METHOD_UNINSTALL :
			sysutils_downlink_rpc_handler_uninstall(json_root);

			break;
		case RPC_METHOD_STOP :
			sysutils_downlink_rpc_handler_stop(json_root);

			break;
		case RPC_METHOD_RUN :
			sysutils_downlink_rpc_handler_run(json_root);

			break;
		case RPC_METHOD_FACTORY_PLUGIN :
			sysutils_downlink_rpc_handler_factory_plugin(json_root);

			break;
		case RPC_METHOD_LIST_PLUGIN :
			sysutils_downlink_rpc_handler_list_plugin(json_root);

			break;
		case RPC_METHOD_SET_PLUGIN_PARA :
			sysutils_downlink_rpc_handler_set_plugin_para(json_root);

			break;
		default :
			LOGGER_ERR("unknown rpc method -> %d %s \n",rpc_method_type,rpc_method);
	}
	if(json_root  != NULL)
		json_decref(json_root);
	if(obj_rpc_method  != NULL)
		json_decref(obj_rpc_method);
	return 1;
sysutils_try_handler_server_push_message_error:
	if(json_root  != NULL)
		json_decref(json_root);
	if(obj_rpc_method  != NULL)
		json_decref(obj_rpc_method);
	return -1;

}
/*
 * Disconnect
 * Install
 * Install_query
 * Install_cancel
 * UnInstall
 * Stop
 * Run
 * FactoryPlugin
 * ListPlugin
 * SetPlug-inParameterValues
 */
RPC_METHOD_ENUM sysutils_get_rpc_type(char *buf) {
	if (strncmp(buf,"Disconnect",strlen("Disconnect") ) == 0 ){
		return RPC_METHOD_DISCONNECT ;
	}
	if (strncmp(buf,"Install_cancel",strlen("Install_cancel") ) == 0 ){
		return RPC_METHOD_INSTALL_CANCEL ;
	}
	if (strncmp(buf,"Install_query",strlen("Install_query") ) == 0 ){
		return RPC_METHOD_INSTALL_QUERY ;
	}
	if (strncmp(buf,"Install",strlen("Install") ) == 0 ){
		return RPC_METHOD_INSTALL ;
	}
	if (strncmp(buf,"UnInstall",strlen("UnInstall") ) == 0 ){
		return RPC_METHOD_UNINSTALL ;
	}
	if (strncmp(buf,"Stop",strlen("Stop") ) == 0 ){
		return RPC_METHOD_STOP ;
	}
	if (strncmp(buf,"Run",strlen("Run") ) == 0 ){
		return RPC_METHOD_RUN ;
	}
	if (strncmp(buf,"FactoryPlugin",strlen("FactoryPlugin") ) == 0 ){
		return RPC_METHOD_FACTORY_PLUGIN ;
	}
	if (strncmp(buf,"ListPlugin",strlen("ListPlugin") ) == 0 ){
		return RPC_METHOD_LIST_PLUGIN ;
	}
	if (strncmp(buf,"SetPlug-inParameterValues",strlen("SetPlug-inParameterValues") ) == 0 ){
		return RPC_METHOD_SET_PLUGIN_PARA ;
	}
	return RPC_METHOD_INVALID;
}
/*
 * Disconnect
 * Install
 * Install_query
 * Install_cancel
 * UnInstall
 * Stop
 * Run
 * FactoryPlugin
 * ListPlugin
 * SetPlug-inParameterValues
 */
int sysutils_downlink_rpc_handler_disconnect(json_t *obj ){
	//get distri_server info 
	LOGGER_TRC("rpc handler -> %s\n",__FUNCTION__);
}
int sysutils_downlink_rpc_handler_install(json_t *obj ){
	LOGGER_TRC("rpc handler -> %s\n",__FUNCTION__);
	char name_buf[64]  = {0};
	char version_buf[64]  = {0};
	char download_url_buf[64]  = {0};
	char plugin_size_buf[64]  = {0};
	char os_buf[64]  = {0};
	int upgrade_id  =  0;
	int id  =  0;
	char *temp = NULL;
	int ret = 0 ;
	//get Plugin_Name
	ret = sysutils_get_json_value_from(obj,"Plugin_Name",JSON_STRING,name_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_install_error;
	//get id
	ret = sysutils_get_json_value_from(obj,"ID",JSON_INTEGER, &id);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_install_error;
	//get version_buf
	ret = sysutils_get_json_value_from(obj,"Version",JSON_STRING,version_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_install_error;
	//get download_url
	ret = sysutils_get_json_value_from(obj,"Download_url",JSON_STRING,download_url_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_install_error;
	//get plugin_size
	ret = sysutils_get_json_value_from(obj,"Plugin_size",JSON_STRING,plugin_size_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_install_error;
	//get os
	ret = sysutils_get_json_value_from(obj,"OS",JSON_STRING,os_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_install_error;
	//get update_id
	ret = sysutils_get_json_value_from(obj,"upgrade_ID",JSON_INTEGER,&upgrade_id);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_install_error;
	//down plug ??
	char local_plugin_file[64] = { 0 };
	LOGGER_TRC("begin download plugin -> %s\n",name_buf);
	ret = sysutils_download_plugin_to_plugin_dir(download_url_buf,local_plugin_file);
	if(ret < 0 ){
		LOGGER_ERR("download plugin error -> %s:  %s %d\n",name_buf,download_url_buf);
		goto sysutils_downlink_rpc_handler_install_error ;
	}
	//+++++++++++
	LOGGER_TRC("begin install plugin -> %s\n",name_buf);
//	ret = CtSgwInstallApp(local_plugin_file);
	//send ack
	//
	char buf[1024] = {0} ;
	ret = sysutils_get_json_plugin_ack_message("Result",JSON_INTEGER,ret ,"ID",JSON_INTEGER,id);
	if(ret < 0 ){
		LOGGER_ERR("get install ack json error \n");
		goto sysutils_downlink_rpc_handler_install_error ;
	}
	//add into send buffer
	ret = fifo_buffer_put(&socket_tx_fifo_header,buf,strlen(buf));
	if(ret < 0) {
		LOGGER_ERR("add data into send buffer error  \n");
		goto sysutils_downlink_rpc_handler_install_error ;
	}

	return 1;
sysutils_downlink_rpc_handler_install_error :

	return -1;

//try lock install process
}
int sysutils_downlink_rpc_handler_install_query(json_t *obj ){
	LOGGER_TRC("rpc handler -> %s\n",__FUNCTION__);
	char name_buf[64]  = {0};
	char version_buf[64]  = {0};
	int upgrade_id  =  0;
	int id  =  0;
	int ret = 0 ;
	//get Plugin_Name
	ret = sysutils_get_json_value_from(obj,"Plugin_Name",JSON_STRING,name_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_install_query_error;
	//get id
	ret = sysutils_get_json_value_from(obj,"ID",JSON_INTEGER, &id);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_install_query_error;
	//get version_buf
	ret = sysutils_get_json_value_from(obj,"Version",JSON_STRING,version_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_install_query_error;

	//+++++++++++
	LOGGER_TRC("begin install query ->but no interface  %s\n",name_buf);
	ret = 0 ;
	//ret = CtSgwInstallApp(local_plugin_file);
	//send ack
	//
	char buf[1024] = {0} ;
	ret = sysutils_get_json_plugin_ack_message("Result",JSON_INTEGER,ret ,"ID",JSON_INTEGER,id);
	if(ret < 0 ){
		LOGGER_ERR("get install ack json error \n");
		goto sysutils_downlink_rpc_handler_install_query_error ;
	}
	//add into send buffer
	ret = fifo_buffer_put(&socket_tx_fifo_header,buf,strlen(buf));
	if(ret < 0) {
		LOGGER_ERR("add data into send buffer error  \n");
		goto sysutils_downlink_rpc_handler_install_query_error ;
	}

	return -0;
sysutils_downlink_rpc_handler_install_query_error :
	LOGGER_ERR("install query error \n");
	return -1;
}
int sysutils_downlink_rpc_handler_install_cancel(json_t *obj ){
	LOGGER_TRC("rpc handler -> %s\n",__FUNCTION__);
	char name_buf[64]  = {0};
	char version_buf[64]  = {0};
	int id  =  0;
	int ret = 0 ;
	//get Plugin_Name
	ret = sysutils_get_json_value_from(obj,"Plugin_Name",JSON_STRING,name_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_install_cancel_error;
	//get id
	ret = sysutils_get_json_value_from(obj,"ID",JSON_INTEGER, &id);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_install_cancel_error;
	//get version_buf
	ret = sysutils_get_json_value_from(obj,"Version",JSON_STRING,version_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_install_cancel_error;

	//+++++++++++
	LOGGER_TRC("begin install cancel ->but no interface  %s\n",name_buf);
	ret = 0 ;
	//ret = CtSgwInstallApp(local_plugin_file);
	//send ack
	//
	char buf[1024] = {0} ;
	ret = sysutils_get_json_plugin_ack_message("Result",JSON_INTEGER,ret ,"ID",JSON_INTEGER,id);
	if(ret < 0 ){
		LOGGER_ERR("get install ack json error \n");
		goto sysutils_downlink_rpc_handler_install_cancel_error ;
	}
	//add into send buffer
	ret = fifo_buffer_put(&socket_tx_fifo_header,buf,strlen(buf));
	if(ret < 0) {
		LOGGER_ERR("add data into send buffer error  \n");
		goto sysutils_downlink_rpc_handler_install_cancel_error ;
	}

	return -0;
sysutils_downlink_rpc_handler_install_querry_error :
	LOGGER_ERR("install query error \n");
	return -1;
	return -0;
sysutils_downlink_rpc_handler_install_cancel_error :
	LOGGER_ERR("install cancel error \n");
	return -1;

//try lock install process
}
int sysutils_downlink_rpc_handler_uninstall(json_t *obj ){
	LOGGER_TRC("rpc handler -> %s\n",__FUNCTION__);
	char name_buf[64]  = {0};
	char version_buf[64]  = {0};
	int id  =  0;
	int ret = 0 ;
	//get Plugin_Name
	ret = sysutils_get_json_value_from(obj,"Plugin_Name",JSON_STRING,name_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_uninstall_error;
	//get id
	ret = sysutils_get_json_value_from(obj,"ID",JSON_INTEGER, &id);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_uninstall_error;
	//get version_buf
	ret = sysutils_get_json_value_from(obj,"Version",JSON_STRING,version_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_uninstall_error;

	//+++++++++++
	LOGGER_TRC("begin install query ->but no interface  %s\n",name_buf);
	ret = 0 ;
//	ret = CtSgwUnnstallApp(name_buf);
	//send ack
	//
	char buf[1024] = {0} ;
	ret = sysutils_get_json_plugin_ack_message("Result",JSON_INTEGER,ret ,"ID",JSON_INTEGER,id);
	if(ret < 0 ){
		LOGGER_ERR("get install ack json error \n");
		goto sysutils_downlink_rpc_handler_uninstall_error ;
	}
	//add into send buffer
	ret = fifo_buffer_put(&socket_tx_fifo_header,buf,strlen(buf));
	if(ret < 0) {
		LOGGER_ERR("add data into send buffer error  \n");
		goto sysutils_downlink_rpc_handler_uninstall_error ;
	}

	return -0;
sysutils_downlink_rpc_handler_uninstall_error :
	LOGGER_ERR("install query error \n");
	return -1;
}
int sysutils_downlink_rpc_handler_stop(json_t *obj ){

	LOGGER_TRC("rpc handler -> %s\n",__FUNCTION__);
	char name_buf[64]  = {0};
	char version_buf[64]  = {0};
	int upgrade_id  =  0;
	int id  =  0;
	int ret = 0 ;
	//get Plugin_Name
	ret = sysutils_get_json_value_from(obj,"Plugin_Name",JSON_STRING,name_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_stop_error;
	//get id
	ret = sysutils_get_json_value_from(obj,"ID",JSON_STRING, &id);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_stop_error;
	//get version_buf
	ret = sysutils_get_json_value_from(obj,"Version",JSON_STRING,version_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_stop_error;

	//+++++++++++
	LOGGER_TRC("begin install query ->but no interface  %s\n",name_buf);
	ret = 0 ;
//	ret = CtSgwStopApp(name_buf);
	//send ack
	//
	char buf[1024] = {0} ;
	ret = sysutils_get_json_plugin_ack_message("Result",JSON_INTEGER,ret ,"ID",JSON_INTEGER,id);
	if(ret < 0 ){
		LOGGER_ERR("get install ack json error \n");
		goto sysutils_downlink_rpc_handler_stop_error ;
	}
	//add into send buffer
	ret = fifo_buffer_put(&socket_tx_fifo_header,buf,strlen(buf));
	if(ret < 0) {
		LOGGER_ERR("add data into send buffer error  \n");
		goto sysutils_downlink_rpc_handler_stop_error ;
	}

	return -0;
sysutils_downlink_rpc_handler_stop_error :
	LOGGER_ERR("install query error \n");
	return -1;
}
int sysutils_downlink_rpc_handler_run(json_t *obj ){
	LOGGER_TRC("rpc handler -> %s\n",__FUNCTION__);
	LOGGER_TRC("rpc handler -> %s\n",__FUNCTION__);
	char name_buf[64]  = {0};
	char version_buf[64]  = {0};
	int upgrade_id  =  0;
	int id  =  0;
	int ret = 0 ;
	//get Plugin_Name
	ret = sysutils_get_json_value_from(obj,"Plugin_Name",JSON_STRING,name_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_run_error;
	//get id
	ret = sysutils_get_json_value_from(obj,"ID",JSON_STRING, &id);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_run_error;
	//get version_buf
	ret = sysutils_get_json_value_from(obj,"Version",JSON_STRING,version_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_run_error;

	//+++++++++++
	LOGGER_TRC("begin install query ->but no interface  %s\n",name_buf);
	ret = 0 ;
//	ret = CtSgwStartApp(name_buf);
	//send ack
	//
	char buf[1024] = {0} ;
	ret = sysutils_get_json_plugin_ack_message("Result",JSON_INTEGER,ret ,"ID",JSON_INTEGER,id);
	if(ret < 0 ){
		LOGGER_ERR("get install ack json error \n");
		goto sysutils_downlink_rpc_handler_run_error ;
	}
	//add into send buffer
	ret = fifo_buffer_put(&socket_tx_fifo_header,buf,strlen(buf));
	if(ret < 0) {
		LOGGER_ERR("add data into send buffer error  \n");
		goto sysutils_downlink_rpc_handler_run_error ;
	}

	return -0;
sysutils_downlink_rpc_handler_run_error :
	LOGGER_ERR("install query error \n");
	return -1;

}
int sysutils_downlink_rpc_handler_list_plugin(json_t *obj ){
	LOGGER_TRC("rpc handler -> %s\n",__FUNCTION__);
	char name_buf[64]  = {0};
	char version_buf[64]  = {0};
	int upgrade_id  =  0;
	int id  =  0;
	int ret = 0 ;
	//get Plugin_Name
	ret = sysutils_get_json_value_from(obj,"Plugin_Name",JSON_STRING,name_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_list_plugin_error;
	//get id
	ret = sysutils_get_json_value_from(obj,"ID",JSON_STRING, &id);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_list_plugin_error;
	//get version_buf
	ret = sysutils_get_json_value_from(obj,"Version",JSON_STRING,version_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_list_plugin_error;

	//+++++++++++
	LOGGER_TRC("begin list ->but no interface  %s\n",name_buf);
	ret = 0 ;
	//ret = CtSgwInstallApp(local_plugin_file);
	//send ack
	//
	char buf[1024] = {0} ;
	ret = sysutils_get_json_plugin_ack_message("Result",JSON_INTEGER,ret ,"ID",JSON_INTEGER,id);
	if(ret < 0 ){
		LOGGER_ERR("get list ack json error \n");
		goto sysutils_downlink_rpc_handler_list_plugin_error ;
	}
	//add into send buffer
	ret = fifo_buffer_put(&socket_tx_fifo_header,buf,strlen(buf));
	if(ret < 0) {
		LOGGER_ERR("add data into send buffer error  \n");
		goto sysutils_downlink_rpc_handler_list_plugin_error ;
	}

	return -0;
sysutils_downlink_rpc_handler_list_plugin_error :
	LOGGER_ERR("list error \n");
	return -1;

}
int sysutils_downlink_rpc_handler_set_plugin_para(json_t *obj ){
	LOGGER_TRC("rpc handler -> %s\n",__FUNCTION__);
	char name_buf[64]  = {0};
	char version_buf[64]  = {0};
	int upgrade_id  =  0;
	int id  =  0;
	int ret = 0 ;
	//get Plugin_Name
	ret = sysutils_get_json_value_from(obj,"Plugin_Name",JSON_STRING,name_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_set_plugin_error;
	//get id
	ret = sysutils_get_json_value_from(obj,"ID",JSON_STRING, &id);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_set_plugin_error;
	//get version_buf
	ret = sysutils_get_json_value_from(obj,"Version",JSON_STRING,version_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_set_plugin_error;

	//+++++++++++
	LOGGER_TRC("begin install query ->but no interface  %s\n",name_buf);
	ret = 0 ;
	//ret = CtSgwInstallApp(local_plugin_file);
	//send ack
	//
	char buf[1024] = {0} ;
	ret = sysutils_get_json_plugin_ack_message("Result",JSON_INTEGER,ret ,"ID",JSON_INTEGER,id);
	if(ret < 0 ){
		LOGGER_ERR("get install ack json error \n");
		goto sysutils_downlink_rpc_handler_set_plugin_error ;
	}
	//add into send buffer
	ret = fifo_buffer_put(&socket_tx_fifo_header,buf,strlen(buf));
	if(ret < 0) {
		LOGGER_ERR("add data into send buffer error  \n");
		goto sysutils_downlink_rpc_handler_set_plugin_error ;
	}

	return -0;
sysutils_downlink_rpc_handler_set_plugin_error :
	LOGGER_ERR("install query error \n");
	return -1;
//try lock install process
}
int sysutils_downlink_rpc_handler_factory_plugin(json_t *obj){
	LOGGER_TRC("rpc handler -> %s\n",__FUNCTION__);
	char name_buf[64]  = {0};
	char version_buf[64]  = {0};
	int upgrade_id  =  0;
	int id  =  0;
	int ret = 0 ;
	//get Plugin_Name
	ret = sysutils_get_json_value_from(obj,"Plugin_Name",JSON_STRING,name_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_factory_error;
	//get id
	ret = sysutils_get_json_value_from(obj,"ID",JSON_STRING, &id);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_factory_error;
	//get version_buf
	ret = sysutils_get_json_value_from(obj,"Version",JSON_STRING,version_buf);
	if(ret < 0 )
		goto sysutils_downlink_rpc_handler_factory_error;

	//+++++++++++
	LOGGER_TRC("begin install query ->but no interface  %s\n",name_buf);
	ret = 0 ;
	//ret = CtSgwInstallApp(local_plugin_file);
	//send ack
	//
	char buf[1024] = {0} ;
	ret = sysutils_get_json_plugin_ack_message("Result",JSON_INTEGER,ret ,"ID",JSON_INTEGER,id);
	if(ret < 0 ){
		LOGGER_ERR("get install ack json error \n");
		goto sysutils_downlink_rpc_handler_factory_error ;
	}
	//add into send buffer
	ret = fifo_buffer_put(&socket_tx_fifo_header,buf,strlen(buf));
	if(ret < 0) {
		LOGGER_ERR("add data into send buffer error  \n");
		goto sysutils_downlink_rpc_handler_factory_error ;
	}

	return -0;
sysutils_downlink_rpc_handler_factory_error :
	LOGGER_ERR("factory plugin  error \n");
	return -1;
}
int sysutils_download_plugin_to_plugin_dir(char *buf,char *local_file){
	return 1;
}
/* 
 *
 * buf ,json dumps to 
 * number : json child number
 * 
 * all arg should be char *
 *
 * type : 0 : int 1 :string
 *  call like this  (key_num ,key1,type1,value1,key2,type2,value2 ...)
 * */
#define JSON_MAX_ENCODE_KEYS   20
int sysutils_get_json_plugin_ack_message(char *buf ,int key_num,... ){
	char *key = NULL;
	char *value = NULL;
	int value_type = 0 ;
	json_t *obj_value =  NULL;
	json_t *obj = NULL;
	size_t  obj_json_list[JSON_MAX_ENCODE_KEYS] ;
	memset(obj_json_list,0,JSON_MAX_ENCODE_KEYS);

	obj = json_object();
	if(!obj) goto sysutils_send_json_plugin_ack_message_error;


	va_list argptr ;
	va_start(argptr,key_num );
	for(int i = 0 ;i< key_num ;i++ ) {
		key = NULL;
		value = NULL;
		key =  va_arg(argptr,char *);
		value_type = va_arg(argptr,int);
		if (value_type == JSON_INTEGER ){
			int temp  = va_arg(argptr,int);
			obj_value = json_integer(temp );
		}
		else if (value_type == JSON_STRING){
			char *temp_char = va_arg(argptr,char *);
			obj_value = json_string(temp_char );
		}
		else {
			LOGGER_ERR("current not support value type -> %d \n,value_type");
			goto sysutils_send_json_plugin_ack_message_error;
		}
		if(!obj_value) goto sysutils_send_json_plugin_ack_message_error;
		json_object_set(obj,key,obj_value);
		obj_json_list[i] = ( size_t) obj_value ;
	}
	va_end(argptr);

	//dump
	char *result =  json_dumps(obj,JSON_COMPACT);
	memcpy(buf,result,strlen(result));
	//free all
	for(int i = 0 ;i< key_num ;i++){
		if (obj_json_list[i] !=  0 )
			json_decref((json_t *)obj_json_list[i]);
	}
	json_decref(obj);
	free(result);
	return 0;
sysutils_send_json_plugin_ack_message_error :
	LOGGER_ERR("send ack faild\n");
	for(int i = 0 ;i< key_num ;i++){
		if (obj_json_list[i] !=  0 )
			json_decref((json_t *)obj_json_list[i]);
	}
	if(!obj) json_decref(obj);
	free(result);


}
int sysutils_get_json_value_from(json_t *obj, char *key ,json_type  type   ,void *buf){
	json_t *obj_value = json_object_get(obj,key);
	if (!obj_value){
		LOGGER_ERR("%s get error -> %s ,%d\n",key,type);
		return -1;
	}
	int ret = json_typeof(obj_value) ;
	if (ret  != type ){
		LOGGER_ERR("%s not support type -> %s ,%d ,%d\n",key,type,ret);
		return -1;
	}
	char * temp =  NULL ;
	switch(type){
		case JSON_STRING :
		    temp = json_string_value(obj_value);
			memcpy(buf,temp,strlen(temp));
			break;
		case JSON_INTEGER :
			*((int *) buf) =  json_integer_value(obj_value);
			break;
		case JSON_REAL :
			*((double *) buf) =  json_real_value(obj_value);
			break ;
		case JSON_TRUE :
			*((int *) buf) =  1;
			break;
		case JSON_FALSE :
			*((int *) buf) =  0;
			break;
		case JSON_NULL :
			*((int *) buf) =  0;
			break;
		default :
			LOGGER_ERR("not support json type,please check \n");
		break;
	}
	json_decref(obj_value);
	return 0;

}
