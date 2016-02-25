#include "capisys.h"
#include "logger.h"
#include <unistd.h>
#include <capi.h>
//get info list
int app_function_capisys_init(void){

	//LOG_DEBUG("%s \n",__FUNCTION__);
	return 0;
}
int app_function_capisys_thread(void *dat){
//	LOG_DEBUG("%s  thread start \n",__FUNCTION__);
	while(1){

	  //  LOG_ERROR("CAPI SYS RUNING\n");
		sleep(5);
	}
	return 0;
}
