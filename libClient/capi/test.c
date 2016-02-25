
#include "capi-app-mgr.h"

#define UCI_TEST 1
#define APP_TEST 1


int main(int argc, char *argv[])
{
	CtSgwSetDbusEnv();

#if 0//UCI_TEST
	CtSgwUCIOptVal_t value1 = {0};
	CtSgwUCIOptVal_t value2 = {0};
	CtSgwUCIOptVal_t value4 = {0};
	uint32_t size = 0, i = 0;
	CtSgwUCIOpt_t *opts = NULL;

	g_print("------test CtSgwUCIReadOption-------\n");
	CtSgwUCIReadOption("demoapp", "global", "hi", value1);
	g_print("[%s]\n", value1);
	CtSgwUCIReadOption("demoapp", "global", "hello", value2);
	g_print("[%s]\n", value2);

	g_print("------test CtSgwUCIWriteOption-------\n");
	CtSgwUCIWriteOption("demoapp", "global", "shit", "flys");
	CtSgwUCIReadOption("demoapp", "global", "shit", value4);
	g_print("[%s]\n", value4);

	g_print("------test CtSgwUCIReadSection 1-------\n");
	CtSgwUCIReadSection("demoapp", NULL, "global", &opts, &size);
	g_print("[name size %d]\n", size);
	for (i = 0; i < size && opts; i++, opts++) {
		g_print("[%d] %s = %s\n", i, opts->name, opts->value);
	}
	//free(opts);

	g_print("------test CtSgwUCIReadSection 2-------\n");
	size = 0;
	CtSgwUCIReadSection("demoapp", "section", NULL, &opts, &size);
	g_print("[section size %d]\n", size);
	for (i = 0; i < size && opts; i++, opts++) {
		g_print("[%d] %s = %s\n", i, opts->name, opts->value);
	}	
	//free(opts);
#endif

#if APP_TEST
	if (argc == 2) {
		g_print("test app c-api [%s]\n", argv[1]);

		if (g_strcmp0(argv[1], "state") == 0)
		{
			CtSgwAppStatus_t status;
			g_strlcpy(status.name, "demoapp", BUFLEN_32);
			CtSgwGetAppStatus(&status);
			g_print("name %s, state %s\n", status.name, status.state);
		}

		if (g_strcmp0(argv[1], "stop") == 0)
			CtSgwStopApp("demoapp");

		if (g_strcmp0(argv[1], "reload") == 0)
			CtSgwReloadApp("demoapp");

		if (g_strcmp0(argv[1], "start") == 0)
			CtSgwStartApp("demoapp");

		if (g_strcmp0(argv[1], "uninstall") == 0)
			CtSgwUninstallApp("demoapp");
		
		if (g_strcmp0(argv[1], "install") == 0)
			CtSgwInstallApp("/bin/demoapp_1_x86.ipk");

		if (g_strcmp0(argv[1], "upgrade") == 0)
			CtSgwUpgradeApp("/bin/demoapp_1_x86.ipk");
	}
#endif	
	g_print("all done\n");
			
	return 0;
}
