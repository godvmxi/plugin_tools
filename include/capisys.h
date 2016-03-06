#ifndef  __CAPISYS_H__
#define   __CAPISYS_H__

typedef struct {
	char cmd_type[40];
	void *handler ;
	void *capi_handler ;
}CapisysHandler ;

extern CapisysHandler capisys_handler[] ;
int app_function_capisys_init(void);

int app_function_capisys_thread(void *dat);

int capisys_post_handler(char *json_buf,char *result_buf);

#endif
