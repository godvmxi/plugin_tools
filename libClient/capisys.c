#include "capisys.h"
#include "logger.h"
#include <unistd.h>
#include <stdlib.h>
#include <jansson.h>
#include "capisys.h"
#include <time.h>
//#include <capi.h>
//get info list
extern int sysutils_encode_json_from_value(char *buf ,int key_num,... );

//TODO : add your custom capi interface
int capisys_post_handler(char *json_buf,char *result_buf){
	


}
int  __capisys_get_vender(char *buf){
#ifdef   CAPI_INTERFACE_NULL_TEST
		sprintf(buf,"XXXX");
#else 
		
#endif 
		return 0;
		//use capi get system info
}
int  __capisys_get_user_id(char *buf){
#ifdef   CAPI_INTERFACE_NULL_TEST
		sprintf(buf,"F45BB1D7FB5E");
#else 
		
#endif 
		return 0;
		//use capi get system info
}
int  __capisys_get_firmware_ver(char *buf){
		sprintf(buf,"v1.230");
		return 0;
		//use capi get system info
}
int  __capisys_get_sys_model(char *buf){
		sprintf(buf,"xxx1.0");
		return 0;
}
int  __capisys_get_hardware_ver(char *buf){
		sprintf(buf,"sd3.64.418");
		return 0;
		//use capi get system info
}
int  __capisys_get_os_ver(char *buf){
		sprintf(buf,"ZhiNengWangGuan OS 1");
		return 0;
		//use capi get system info
}
int  __capisys_get_app_ver(char *buf){
		sprintf(buf,"1.1");
		return 0;
		//use capi get system info
}

int  __capisys_get_wlan_ip_addr(char *buf){
		sprintf(buf,"10.9.1.180");
		return 0;
		//use capi get system info
}
int  __capisys_get_plugin_info(char *name){


}
int  __capisys_get_wlan_mac(char *buf){
		char mac[] =  {0x84,0x82,0xf4,0x1c,0xe9,0x28 };
		sprintf(buf,"48555F44CA00");
		return 0;
		//use capi get system info
}

int  __capisys_get_platform_id(char *buf){
		sprintf(buf,"OSGI");
		return 0;
		//use capi get system info
}
int  __capisys_get_sys_card(char *buf){
		buf[0] = '\0';
		return 0;
		//use capi get system info
}
int  __capisys_get_sys_token(char *buf){
	sprintf(buf,"token data");
			return 0;
	//get storage token data
}
int  __capisys_get_sys_loid(char *buf){
	sprintf(buf,"SMARTHUBG07");
			return 0;
	//get storage token data
}
int  __capisys_get_sys_sn(char *buf){
//	ctSgw_sysGetSSN();
	sprintf(buf,"48555F-4384248555F44CA00");
			return 0;
	//get storage token data
}
int  __capisys_get_sys_ssn(char *buf){
	buf[0] = 0;
	//	sprintf(buf,"sn data");
	return 0;
	//get storage token data
}
int  __capisys_get_sys_time(char *buf){
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
int capisys_query_mem_info(char *buf ,char *sequence_id ,char *cmd_type ) {
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
int capisys_get_duriation(char *buf,char *sequence_id ,char *cmd_type ) {
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
int capisys_get_hg_loid(char *buf, char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);	 
	char loid_buf[24] = { 0 };
	char card_buf[64] = {0};
	int ret = 0 ;
	int all_info_flag = 0 ;
	ret = __capisys_get_sys_loid(loid_buf);
	if (ret < 0 ){
		all_info_flag = -1;
		LOGGER_ERR("get card error\n");
	}
	ret = __capisys_get_sys_card(card_buf);
	if (ret < 0 ){
		all_info_flag = -1;
		LOGGER_ERR("get card error\n");
	}
	all_info_flag =  0;
	if(all_info_flag < 0 ){
		LOGGER_ERR("cal capisys get loid error \n");
		ret = sysutils_encode_json_from_value(buf, 4 ,
					"CmdType",JSON_STRING ,cmd_type,
					"SequenceId",JSON_STRING,sequence_id ,
					"Status",JSON_STRING,"1",
					"FailReason",""
				);
	}else 
	{
		ret = sysutils_encode_json_from_value(buf, 5 ,
					"CmdType",JSON_STRING ,cmd_type,
					"SequenceId",JSON_STRING,sequence_id ,
					"Status",JSON_STRING,"0",
					"LOID",JSON_STRING,loid_buf,
					"CARD",JSON_STRING,card_buf
				);

	}
	return 0;
}
int capisys_query_cpu_info(char *buf ,char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_get_sn_info(char *buf,char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_wlan_intf_info(char *buf ,char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_get_version(char *buf ,char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_query_wlan_num(char *buf ,char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_query_wlan_info(char *buf,char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_systest(char *buf,char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_ppoe_diag_req(char *buf ,char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_query_system_info(char *buf, char *sequence_id ,char *cmd_type ) {
	LOGGER_DBG("capisys handler -> %s\n",__FUNCTION__);
	return 0;
}
int capisys_get_wifi_info(char *buf ,char *sequence_id ,char *cmd_type ) {
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
