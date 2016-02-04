/*
 ============================================================================
 Name        : exampleProgram.c
 Author      : Bright Jiang
 Version     :
 Copyright   : GPL
 Description : Uses shared library to print greeting
               To run the resulting executable the LD_LIBRARY_PATH must be
               set to ${project_loc}/libClient/.libs
               Alternatively, libtool creates a wrapper shell script in the
               build directory of this program which can be used to run it.
               Here the script will be called exampleProgram.
 ============================================================================
 */
#include <jansson.h>
#include "libClient.h"
#include "stdio.h"

void json_parse_test(char *filename){
	json_error_t js_error;
		json_t *js_obj ;
		const char *key;
		json_t *value ;
		print_hello();
		printf("version->%d.%d.%d\n",JANSSON_MAJOR_VERSION,JANSSON_MINOR_VERSION,JANSSON_MICRO_VERSION);
		json_object_seed(0);
		js_obj = json_load_file(filename,0,&js_error);
		if (!js_obj){
			printf("load js error->%d %s\n",js_error.line,filename);
			exit(1);
		}
		printf("load json ok\n");
		printf("show key->\n");
		int js_type ;
		json_object_foreach(js_obj, key, value) {
			    /*  block of code that uses key and value */
			switch(json_typeof(value)){
				case  JSON_OBJECT :
					printf("%s has sub json\n",key);
					break;
				case JSON_ARRAY  :
					printf("%s -> array->%d\n",key,(int)json_array_size(value));
					break;
				case JSON_STRING  :
					printf("%s -> %s\n",key,json_string_value(value));
					break;
				case JSON_INTEGER  :
					printf("%s -> %ld\n",key,(long)json_integer_value(value));
					break;
				case JSON_REAL  :
					printf("%s -> %f\n",key,json_real_value(value));
					break;
				case JSON_TRUE  :
					printf("%s -> true\n",key);
					break;
				case JSON_FALSE  :
					printf("%s -> false\n",key);
					break;
				case JSON_NULL  :
					printf("%s -> null\n",key);
					break;
				default :
					printf("%s default handler\n",key);
					break;


			}

		}
		printf("\n");

}


int main(int argc ,char **argv) {

	json_parse_test(argv[1]);
	return 0;
}
