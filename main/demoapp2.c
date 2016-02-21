/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2, as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>

#include <gio/gio.h>

#include "capi.h"

CtSgwDBusNodeInfo_t *intro_data;
CtSgwDBusNodeInfo_t *config_data;
int running = 1;

/* Introspection data for the service we are exporting */

static const unsigned char intro_xml[] =
	"<node>"
	"  <interface name='com.upointech.demoapp1.service'>"
	"    <method name='Config'>"
	"      <arg type='s' name='name' direction='in'/>"
	"	 <arg type='i' name='response' direction='out'/>"
	"    </method>"
	"    <method name='Func1'>"
	"      <arg type='s' name='name' direction='in'/>"
	"	 <arg type='s' name='response' direction='out'/>"
	"    </method>"
	"    <method name='Func2' >"
	"	   <arg type='s' name='response' direction='out'/>"
	"    </method>"
	"	 <property type='s' name='Title' access='readwrite'/>"
	"	 <property type='s' name='ReadingAlwaysThrowsError' access='read'/>"
	"	 <property type='s' name='WritingAlwaysThrowsError' access='readwrite'/>"
	"  </interface>"
	"</node>";

static const unsigned char config_xml[] =
	"<node>"
	"  <interface name='org.freedesktop.DBus.Properties'>"
	"    <method name='Get' >"
	"      <arg type='s' name='key' direction='in'/>"
	"      <arg type='s' name='value' direction='out'/>"
	"    </method>"
	"    <method name='Set' >"
	"      <arg type='s' name='key' direction='in'/>"
	"      <arg type='s' name='value' direction='in'/>"
	"      <arg type='i' name='response' direction='out'/>"
	"    </method>"
	"    <property type='s' name='key1' access='readwrite'/>"
	"    <property type='s' name='key3' access='readwrite'/>"
	"    <property type='s' name='hello' access='readwrite'/>"
	"  </interface>"
	"</node>";

static int
handle_method_call(const char           *object_path,
				   const char           *interface_name,
				   const char           *method_name,
				   GVariant            *inargs,
				   GVariant            **outargs,
				   void                      *user_data)
{
	g_print("%s,%d: call %s\n", __func__, __LINE__, method_name);
	if (g_strcmp0(method_name, "Func1") == 0) {
		const gchar *name = NULL;
		char str[64] = {0};

		g_variant_get (inargs, "(&s)", &name);		

		sprintf(str, "Hello %s", name);
		*outargs = g_variant_new("(s)", str);
	} else if (g_strcmp0(method_name, "Func2") == 0) {

		GDBusConnection *connection;
		GDBusProxy *proxy;
		GError *error = NULL;
		GVariant *result;
		const gchar *str = NULL;
		
		connection = g_bus_get_sync (DBUS_TYPE, NULL, &error);
		g_assert_no_error(error);
		
		proxy = g_dbus_proxy_new_sync(connection,
									  G_DBUS_PROXY_FLAGS_NONE,
									  NULL, 				  /* GDBusInterfaceInfo */
									  "com.upointech.testapp1", /* name */
									  "/com/upointech/testapp1", /* object path */
									  "com.upointech.testapp1.intf2",		  /* interface */
									  NULL, /* GCancellable */
									  &error);
		g_assert_no_error(error);
		
		result = g_dbus_proxy_call_sync(proxy,
									"Func2",
									NULL,
									G_DBUS_CALL_FLAGS_NONE,
									-1,
									NULL,
									&error);
		g_assert_no_error(error);
		g_assert(result != NULL);
		g_variant_get(result, "(&s)", &str);

		*outargs = g_variant_new("(s)", str);
		
		g_variant_unref(result);
		g_object_unref(proxy);
		g_object_unref (connection);
	}

	return 0;
}


static int
config_global_handle_method_call(const char           *object_path,
								 const char           *interface_name,
								 const char           *method_name,
								 GVariant           *inargs,
								 GVariant           **outargs,
								 void *user_data)
{
	const gchar *key;
	char cmd[64] = {0};

	g_print("%s,%d: call %s\n", __func__, __LINE__, method_name);
	if (g_strcmp0(method_name, "Get") == 0) {

		char line[64] = {0};
		int len = 0;
		FILE *fp = NULL;
		
		g_variant_get(inargs, "(&s)", &key);

		sprintf(cmd, "uci get demoapp.global.%s", key);
		fp = popen(cmd, "r");
		if (fp) {
			fgets(line, 64, fp);
			len = strlen(line);
			if (line[len - 1] == '\n')
				line[len - 1] = '\0';	
			pclose(fp);
		}

		*outargs = g_variant_new("(s)", line);
	} else if (g_strcmp0(method_name, "Set") == 0) {

		const gchar *value;
		gint ret = 0;

		g_variant_get(inargs, "(&s&s)", &key, &value);
		sprintf(cmd, "uci set demoapp.global.%s=%s", key, value);
		system(cmd);	
		system("uci commit demoapp");

		*outargs = g_variant_new("(i)", ret);
	}

	return 0;
}


static int
config_section1_handle_method_call(const char           *object_path,
								 const char           *interface_name,
								 const char           *method_name,
								 GVariant           *inargs,
								 GVariant           **outargs,
								 void *user_data)
{
	const gchar *key;
	char cmd[64] = {0};

	if (g_strcmp0(method_name, "Get") == 0) {
		char line[64] = {0};
		int len = 0;
		FILE *fp = NULL;
				
		g_variant_get(inargs, "(&s)", &key);

		sprintf(cmd, "uci get demoapp.@section[0].%s", key);
		fp = popen(cmd, "r");
		if (fp) {
			fgets(line, 64, fp);
			len = strlen(line);
			if (line[len - 1] == '\n')
				line[len - 1] = '\0';	
			pclose(fp);
		}		
		*outargs = g_variant_new("(s)", line);
	} else if (g_strcmp0(method_name, "Set") == 0) {

		const gchar *value;
		gint ret = 0;

		g_variant_get(inargs, "(&s&s)", &key, &value);
		sprintf(cmd, "uci set demoapp.@section[0].%s=%s", key, value);
		system(cmd);	
		system("uci commit demoapp");
		*outargs = g_variant_new("(i)", ret);
	}

	return 0;
}

static int
config_section2_handle_method_call(const char           *object_path,
								 const char           *interface_name,
								 const char           *method_name,
								 GVariant           *inargs,
								 GVariant           **outargs,
								 void *user_data)
{
	const gchar *key;
	char cmd[64] = {0};

	if (g_strcmp0(method_name, "Get") == 0) {
		char line[64] = {0};
		int len = 0;
		FILE *fp = NULL;
				
		g_variant_get(inargs, "(&s)", &key);

		sprintf(cmd, "uci get demoapp.@section[1].%s", key);
		fp = popen(cmd, "r");
		if (fp) {
			fgets(line, 64, fp);
			len = strlen(line);
			if (line[len - 1] == '\n')
				line[len - 1] = '\0';	
			pclose(fp);
		}		
		*outargs = g_variant_new("(s)", line);
	} else if (g_strcmp0(method_name, "Set") == 0) {
		const gchar *value;
		gint ret = 0;

		g_variant_get(inargs, "(&s&s)", &key, &value);
		sprintf(cmd, "uci set demoapp.@section[1].%s=%s", key, value);
		system(cmd);	
		system("uci commit demoapp");
		*outargs = g_variant_new("(i)", ret);
	}

	return 0;
}


static const CtSgwGDBusInterfaceVTable_t interface_vtable = { handle_method_call, NULL, NULL, NULL, NULL };

static const CtSgwGDBusInterfaceVTable_t interface_global_vtable = { config_global_handle_method_call, NULL, NULL, NULL, NULL };
static const CtSgwGDBusInterfaceVTable_t interface_section1_vtable = {config_section1_handle_method_call, NULL, NULL, NULL, NULL};
static const CtSgwGDBusInterfaceVTable_t interface_section2_vtable = {config_section2_handle_method_call, NULL, NULL, NULL, NULL};

static gboolean
on_timeout_cb (gpointer user_data)
{
	
	GDBusConnection *connection;
	GDBusProxy *proxy;
	GError *error = NULL;
	GVariant *result;
	const gchar *str = NULL;
	
	connection = g_bus_get_sync (DBUS_TYPE, NULL, &error);
	g_assert_no_error(error);

	//fprintf(stderr, "************ call com.upointech.testapp1.intf2.Func2\n");
	proxy = g_dbus_proxy_new_sync(connection,
								  G_DBUS_PROXY_FLAGS_NONE,
								  NULL, 				  /* GDBusInterfaceInfo */
								  "com.upointech.testapp1", /* name */
								  "/com/upointech/testapp1", /* object path */
								  "com.upointech.testapp1.intf2",		  /* interface */
								  NULL, /* GCancellable */
								  &error);
	g_assert_no_error(error);
	
	result = g_dbus_proxy_call_sync(proxy,
								"Func2",
								NULL,
								G_DBUS_CALL_FLAGS_NONE,
								-1,
								NULL,
								&error);
	g_assert_no_error(error);
	g_assert(result != NULL);
	g_variant_get(result, "(&s)", &str);
	
	//fprintf(stderr, "************ ret %s\n", str);
	
	g_variant_unref(result);
	g_object_unref(proxy);
	g_object_unref (connection);

	return TRUE;
}

static int demoapp_stop(void)
{
	running = 0;

	return 0;
}

static int demoapp_reload(void)
{
	CtSgwLog(LOG_NOTICE, "reloaded\n");
	return 0;
}

static void _register_methods(CtSgwDBusNodeInfo_t *intro, CtSgwDBusNodeInfo_t *config)
{
	guint registration_id;

	registration_id = CtSgwDBusRegisterObject("/com/upointech/demoapp1",
					  intro->interfaces[0],
					  &interface_vtable,
					  NULL);
	g_assert(registration_id > 0);

	registration_id = CtSgwDBusRegisterObject("/com/upointech/demoapp1/Config/global/global",
					  config->interfaces[0],
					  &interface_global_vtable,
					  NULL);
	g_assert(registration_id > 0);

	registration_id = CtSgwDBusRegisterObject("/com/upointech/demoapp1/Config/section/1",
					  config->interfaces[0],
					  &interface_section1_vtable,
					  NULL);
	g_assert(registration_id > 0);

	registration_id = CtSgwDBusRegisterObject("/com/upointech/demoapp1/Config/section/2",
					  config->interfaces[0],
					  &interface_section2_vtable,
					  NULL);
	g_assert(registration_id > 0);

#if 1 //setup response for method: GetManagedObjects
	GDBusObjectManagerServer *manager = NULL;
	GDBusObjectSkeleton *skeleton;

	manager = g_dbus_object_manager_server_new("/com/upointech/demoapp1/Config");

	skeleton = g_dbus_object_skeleton_new("/com/upointech/demoapp1/Config/global/global");
	g_dbus_object_manager_server_export(manager, skeleton);
	skeleton = g_dbus_object_skeleton_new("/com/upointech/demoapp1/Config/section/1");
	g_dbus_object_manager_server_export(manager, skeleton);
	skeleton = g_dbus_object_skeleton_new("/com/upointech/demoapp1/Config/section/2");
	g_dbus_object_manager_server_export(manager, skeleton);

	//TODO: add api func to return connection
	g_dbus_object_manager_server_set_connection(manager, sgw_dbus_service_context->connection);
#endif

	//TODO: 
	g_timeout_add_seconds (120, on_timeout_cb, sgw_dbus_service_context->connection);
}


int main(int argc, char *argv[])
{

	CtSgwAppMgtCallbacks_t app_cbs = { 
		.stop = demoapp_stop,
		.reload = demoapp_reload
	};

	CtSgwLogOpen(LOG_USER, "demoapp");
	CtSgwLog(LOG_NOTICE, "start\n");

	CtSgwSetDbusEnv();

	CtSgwDBusStartService("com.upointech.demoapp1");

	CtSgwAppRegisterMgtFuncs(&app_cbs);

	intro_data = CtSgwDBusNodeParseXml(intro_xml);
	config_data = CtSgwDBusNodeParseXml(config_xml);

	_register_methods(intro_data, config_data);

	g_print("DEMOAPP SOMETHING\n");
	while (running) {
		//g_print("sleep 60s\n");
		sleep(60);
	}

	CtSgwDBusNodeInfoUnref(intro_data);
	CtSgwDBusNodeInfoUnref(config_data);
	CtSgwDBusStopService();

	CtSgwLog(LOG_NOTICE, "exit\n");
	CtSgwLogClose();	

	return 0;
}
