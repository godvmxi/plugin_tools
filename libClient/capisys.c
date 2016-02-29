#include "capisys.h"
#include "logger.h"
#include <unistd.h>
#include <stdlib.h>
//#include <capi.h>
//get info list
CapisysHandler capisys_handler[] ={
	{   "GET_SERVICE" ,
		NULL,
		NULL   },

	{   {0},
		NULL ,
		NULL  },



} ;
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
