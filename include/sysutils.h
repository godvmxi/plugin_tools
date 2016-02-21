/*
 * sysutils.h
 *
 *  Created on: 2016-2-21
 *      Author: dan
 */

#ifndef SYSUTILS_H_
#define SYSUTILS_H_

typedef enum {
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
#define 	RPC_RET_SUCCESS = 0,
#define 	RPC_RET_NEW_DEVRND  = 1
#define 	RPC_RET_IDENTIFY_OK = 2
#define 	RPC_RET_GW_SET_DEFAULT = 3
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








int sysutils_get_json_boot(char *buf);
int sysutils_get_json_headbeat(char *buf);
int sysutils_get_json_token_update(char *buf);
int sysutils_get_json_boot_first(char *buf );
int sysutils_get_json_register_first(char *buf);
int sysutils_parse_json_type(char *buf,int cmdType);


#endif /* SYSUTILS_H_ */
