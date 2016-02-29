#include "capisys.h"
#include "logger.h"
#include <unistd.h>
#include <stdlib.h>
#include <jansson.h>
#include "capisys.h"
//#include <capi.h>
//get info list
extern int sysutils_encode_json_from_value(char *buf ,int key_num,... );
int capisys_post_handler(char *json_buf,char *result_buf){
	


}
int app_function_capisys_init(void){

	//LOGGER_DBG("%s \n",__FUNCTION__);
	//CtSgwSetDbusEnv();
	return 0;
}
int app_function_capisys_thread(void *dat){
//	LOGGER_DBG("%s  thread start \n",__FUNCTION__);
	while(1){
	  //  LOG_ERROR("CAPI SYS RUNING\n");
		sleep(5);
	}
	return 0;
}
/*  
int capisys_query_cpu_info(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
*/
int capisys_query_mem_info(char *sequence_id ,char *cmd_type ,char *buf) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	char mem_info[64] = {0};
	char failed_reason[64];
	int  ret = 0;
	//TODO :all fake data
	if (ret == 0 ){
		strcat(mem_info,"50%");
		sysutils_encode_json_from_value(buf, 4 ,
				"CmdType",JSON_STRING ,cmd_type ,
				"SequenceId",JSON_STRING ,sequence_id , 
				"Status",JSON_INTEGER ,0 ,
				"Percent",JSON_STRING,mem_info  
				);
	}
	else {
		strcat(mem_info,"-1");
		strcat(failed_reason,"mem full");
	}
	return 0;
}
int capisys_get_duriation(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_get_service(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_get_wlan_intf_info(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_get_hg_loid(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_query_cpu_info(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_get_sn_info(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_wlan_intf_info(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_get_version(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_query_wlan_num(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_query_wlan_info(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_systest(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_ppoe_diag_req(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_query_system_info(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_get_wifi_info(char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}























CapisysHandler capisys_handler[] ={
	{   "QUERY_CPU_INFO" ,
		capisys_query_cpu_info,
		NULL   },

	{   "GET_WLAN_INTF_INFO" ,
		capisys_wlan_intf_info,
		NULL   },
	{   "GET_HG_LOID" ,
		capisys_get_hg_loid,
		NULL   },
	{   "GET_SN_INFO" ,
		capisys_get_sn_info,
		NULL   },
	{   "GET_VERSION" ,
		capisys_get_version,
		NULL   },
	{   "SYSTEST" ,
		capisys_systest,
		NULL   },
	{   "PPPOE_DIAG_REQ" ,
		capisys_ppoe_diag_req,
		NULL   },
	{   "QUERY_WAN_NUM" ,
		capisys_query_wlan_num,
		NULL   },
	{   "QUERY_WAN_INFO" ,
		capisys_query_wlan_info,
		NULL   },
	{   "QUERY_SYSTEM_INFO" ,
		capisys_query_system_info,
		NULL   },
	{   "GET_WAN_REALRATE" ,
		NULL,
		NULL   },
	{   "GET_SERVICE" ,
		NULL,
		NULL   },
	{   "GET_SERVICE" ,
		NULL,
		NULL   },
	{   "GET_SERVICE" ,
		NULL,
		NULL   },
	{   "GET_SERVICE" ,
		NULL,
		NULL   },
	{   "GET_SERVICE" ,
		NULL,
		NULL   },
	{   "GET_SERVICE" ,
		NULL,
		NULL   },
	{   "QUERY_SYSTEM_INFO" ,
		NULL,
		NULL   },
	{   {0},
		NULL ,
		NULL  }


} ;
