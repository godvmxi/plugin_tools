/*
 * sysutils.h
 *
 *  Created on: 2016-2-21
 *      Author: dan
 */

#ifndef SYSUTILS_H_
#define SYSUTILS_H_
#include "jansson.h"
#include <stdarg.h>
#include "debug.h"
typedef enum {
	RPC_METHOD_INVALID = -1,
	RPC_METHOD_ACK  = 0,
	RPC_METHOD_BOOT = 1,
	RPC_METHOD_HEARTBEAT    ,
	RPC_METHOD_DISCONNECT    ,
	RPC_METHOD_POST    ,
	RPC_METHOD_INSTALL    ,
	RPC_METHOD_INSTALL_QUERY    ,
	RPC_METHOD_INSTALL_CANCEL    ,
	RPC_METHOD_UNINSTALL    ,
	RPC_METHOD_STOP    ,
	RPC_METHOD_RUN    ,
	RPC_METHOD_FACTORY_PLUGIN    ,
	RPC_METHOD_LIST_PLUGIN    ,
	RPC_METHOD_SET_PLUGIN_PARA    ,
	RPC_METHOD_MESSAGE_PUSH    ,
	RPC_METHOD_TOKEN_UPDATE    ,
	RPC_METHOD_BOOT_FIRST    ,
	RPC_METHOD_REGISTER_FIRST    ,



}RPC_METHOD_ENUM;
//SUCCESS RET
#define 	RPC_RET_SUCCESS          0
#define 	RPC_RET_NEW_DEVRND       1
#define 	RPC_RET_IDENTIFY_OK      2
#define 	RPC_RET_GW_SET_DEFAULT   3
//FAILED RET
#define 	RPC_RET_NORNAL_FAILED   -1
#define 	RPC_RET_INVALID_SSN_LOID   -2
#define 	RPC_RET_DOWNLOAD_URL_INVALID  -3
#define 	RPC_RET_SPACE_LACK   -4
#define 	RPC_RET_BUSY   -5
#define 	RPC_RET_VERSION_ERROR   -6
#define 	RPC_RET_OS_NOT MATCH     -7
#define 	RPC_RET_SIGN_ERROR       -8
#define 	RPC_RET_DOWNLOAD_FAILED   -9
#define 	RPC_RET_PLUGIN_BOOT_FAILED  -10
#define 	RPC_RET_INSTALL_FINISHED     -11
#define 	RPC_RET_PLUGIN_NOT_EXIST     -12
#define 	RPC_RET_PLUGIN_RUNNING       -13
#define 	RPC_RET_PLUGIN_CAN_NOT_DISABLED   -14
#define 	RPC_RET_PLUGIN_CAN_NOT_UNINSTALL   -15
#define 	RPC_RET_PLUGIN_NOT_RUNING         -16
#define 	RPC_RET_PLUGIN_INSTALL_FAILED     -17
#define 	RPC_RET_DEV_IDENTIFY_FAILED       -18
#define 	RPC_RET_NEED_REGISTE              -19
#define 	RPC_RET_PLUGIN_CONNECT_TIMEOUT    -20
#define 	RPC_RET_RESERVED                  -100
#define 	RPC_RET_MAC_INVALID               -1000
#define 	RPC_RET_DEV_NOT_IN_DATABASE       -1002
#define 	RPC_RET_DEV_TOKEN_INVALID         -1003

#define  SOCKET_CMD_TYPE_ACK    0
#define  SOCKET_CMD_TYPE_ACK    0








int sysutils_get_json_rpc_boot(char *buf);
int sysutils_get_json_rpc_heartbeat(char *buf);
int sysutils_get_json_rpc_token_update(char *buf);
int sysutils_get_json_rpc_register_first(char *buf);
int sysutils_parse_json_type(char *buf,int cmdType);
int sysutils_get_json_rpc_boot_first(char *buf );

int sysutils_parse_distri_server_ack_step_1(char *buf,int *result,char *challenge_code,int *interval,char * server_ip);
int sysutils_parse_distri_server_ack_step_2(char *buf,
		int *result,
		char *server_addr,
		unsigned int *server_port,
		int *interval,
		char *server_ip,
		char *token,
		char *exp_date,
		char *ca_download_url);
int sysutils_parse_distri_server_ack_step_2_old(char *buf,
		int *result ,
		int *interval
		);
int sysutils_parse_operate_login_ack(char *buf,int *result);
int sysutils_parse_json_cmd_type(char *buf, RPC_METHOD_ENUM  *type , int ID);
int sysutils_parse_json_is_result(char *buf,int *result ,int *id) ;
int sysutils_try_handler_ack_result_message(char *buf);

int sysutils_try_handler_server_push_message(char *buf);


RPC_METHOD_ENUM sysutils_get_rpc_type(char *buf) ;
int sysutils_get_json_plugin_ack_message(char *buf ,int key_num,... );
int sysutils_get_json_value_from(json_t *obj,char *key ,json_type type ,void *buf) ;
int sysutils_download_plugin_to_plugin_dir(char *buf,char *local_file);
int sysutils_encode_json_from_value(char *buf ,int key_num,... );




int sysutils_downlink_rpc_handler_disconnect(json_t *obj );
int sysutils_downlink_rpc_handler_install(json_t *obj );
int sysutils_downlink_rpc_handler_install_query(json_t *obj );
int sysutils_downlink_rpc_handler_install_cancel(json_t *obj );
int sysutils_downlink_rpc_handler_uninstall(json_t *obj );
int sysutils_downlink_rpc_handler_stop(json_t *obj );
int sysutils_downlink_rpc_handler_run(json_t *obj );
int sysutils_downlink_rpc_handler_list_plugin(json_t *obj );
int sysutils_downlink_rpc_handler_set_plugin_para(json_t *obj );
int sysutils_downlink_rpc_handler_factory_plugin(json_t *ojb);

#endif /* SYSUTILS_H_ */
