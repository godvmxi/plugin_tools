#include "capisys.h"
#include "logger.h"
#include <unistd.h>
#include <capi.h>
//get info list
int app_function_capisys_init(void){

	//LOGGER_DBG("%s \n",__FUNCTION__);
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
