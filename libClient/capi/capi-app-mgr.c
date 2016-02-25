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

#include "capi-app-mgr.h"

int CtSgwSetDbusEnv(void)
{
	FILE *fp = NULL;
	char line[256] = {0};

	fp = fopen(DBUS_BUS_ADDRESS, "r");

	if (fp) {
		fgets(line, sizeof line, fp);
		fclose(fp);
	} else {
		CtSgwLog(LOG_ERR, "Failed to get dbus bus address, please run dbus-daemon first.\n");
		exit(-1);
	}

	if (line[strlen(line) - 1] == '\n')
		line[strlen(line) - 1] = '\0';

	setenv(DBUS_BUS_NAME, line, 1);
	//CtSgwLog(LOG_DEBUG, "export %s=%s\n", DBUS_BUS_NAME, line);
	return 0;
}


/* priority: LOG_DEBUG/LOG_NOTICE/LOG_ERR */ 
void CtSgwLog(int priority, const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vsyslog(priority, fmt, ap);
	va_end(ap);
}


/*
  * facility: LOG_USER/LOG_DEAMON
  * ident: program name	
  */
void CtSgwLogOpen(int facility, const char *ident)
{
	openlog(ident, LOG_CONS, facility);
}

void CtSgwLogClose(void)
{
	closelog();
}


static void _CtSgwGetAppVendorVersion(const char *app_name, char **vendor, int *version)
{
	char cmd[256] = {0};
	char line[32] = {0};
	FILE *fp = NULL;
	int len = 0;

	snprintf(cmd, 256, "grep Vendor /usr/lib/opkg/info/%s.control | awk -F: '{print $2}'", app_name);
	fp = popen(cmd, "r");
	if (fp) {
		fgets(line, sizeof(line), fp);
		len = strlen(line);
		if (line[len - 1] == '\n')
			line[len - 1] = '\0';
		*vendor = strdup(line + 1); //skip first space
		pclose(fp);
	}

	memset(cmd, 0, sizeof(cmd));
	snprintf(cmd, 256, "grep Version /usr/lib/opkg/info/%s.control | awk -F: '{print $2}'", app_name);
	fp = popen(cmd, "r");
	if (fp) {
		fgets(line, sizeof(line), fp);
		*version = atoi(line);
		pclose(fp);
	}	
}

static int _CtSgwGetNumOfNodes(const char *service_name, const char *object_path)
{
	GDBusNodeInfo *node_info;
	GVariant *result;
	const gchar *xml_data;
	GError *error = NULL;
	int n = 0;

	result = g_dbus_connection_call_sync (sgw_dbus_service_context->connection,
											 service_name,
											 object_path,
											 "org.freedesktop.DBus.Introspectable",
											 "Introspect",
											 NULL,
											 G_VARIANT_TYPE("(s)"),
											 G_DBUS_CALL_FLAGS_NONE,
											 -1,
											 NULL,
											 &error);
	g_assert_nonnull(result);
	g_variant_get (result, "(&s)", &xml_data);
	
	node_info = g_dbus_node_info_new_for_xml (xml_data, &error);
	g_assert_no_error (error);
	g_assert_nonnull(node_info);
		
	for (n = 0; node_info->nodes != NULL && node_info->nodes[n] != NULL; n++) {
		;//do nothing
	}

	g_variant_unref(result);
	g_dbus_node_info_unref (node_info);

	return n;
}

int CtSgwUCIReadOption(const char *pkg_name, const char *section_name, const char *option_name, CtSgwUCIOptVal_t option_val)
{
	char *vendor = NULL;
	int version = 0, ret = 0;
	char name[128] = {0}, path[128] = {0}, intf[128] = {0};
	GVariant *value = NULL;
	char *val = NULL;

	if (!pkg_name || !section_name || !option_name)
		return -1;

	_CtSgwGetAppVendorVersion(pkg_name, &vendor, &version);
	g_assert_nonnull(vendor);
	
	sprintf(name, "com.%s.%s%d", vendor, pkg_name, version);
	sprintf(path, "/com/%s/%s%d/Config/%s/%s", vendor, pkg_name, version, section_name, section_name);
	sprintf(intf, "%s.Config.%s", name, section_name);

	ret = CtSgwDBusGetProperty(name, path, intf, option_name, &value);

	if (value) {
		g_variant_get(value, "&s", &val);
		memcpy(option_val, val, strlen(val));
		g_variant_unref(value);
	}
	free(vendor);
	
	return ret;	
#if APPMGR_UCI_SUPPORT
	GDBusConnection *connection;
	GDBusProxy *proxy;
	GError *error = NULL;
	GVariant *result;
	const gchar *str = NULL;

	if (!pkg_name || !section_name || !option_name)
		return -1;

	connection = g_bus_get_sync (DBUS_TYPE, NULL, &error);
	g_assert_no_error(error);

	proxy = g_dbus_proxy_new_sync(connection,
								  G_DBUS_PROXY_FLAGS_NONE,
								  NULL,					  /* GDBusInterfaceInfo */
								  "com.ctc.appframework1", /* name */
								  "/com/ctc/appframework1", /* object path */
								  "com.ctc.appframework1.UCI",		  /* interface */
								  NULL, /* GCancellable */
								  &error);
	g_assert_no_error(error);
	
	result = g_dbus_proxy_call_sync(proxy,
								"ReadOption",
								g_variant_new("(sss)", pkg_name, section_name, option_name),
								G_DBUS_CALL_FLAGS_NONE,
								-1,
								NULL,
								&error);
	g_assert_no_error(error);
	g_assert(result != NULL);
	g_variant_get(result, "(&s)", &str);

	g_strlcpy(option_val, str, MAX_UCI_OPT_VAL_LEN);
	g_variant_unref(result);
	g_object_unref(proxy);
	g_object_unref (connection);

	return 0;
#endif
}

int CtSgwUCIReadSection(const char *pkg_name, const char *section_type, const char *section_name, CtSgwUCIOpt_t **opts, uint32_t *optsize)
{
	char *vendor = NULL;
	int version = 0, ret = 0, n = 0;
	int i = 0, cnt = 0;
	char name[128] = {0}, path[128] = {0}, intf[128] = {0};
	GVariant *value = NULL;
	GVariant *vv = NULL;
	GVariantIter *iter;
	CtSgwUCIOpt_t *opt = NULL;
	gchar *key = NULL, *val = NULL;

	if (!pkg_name || (!section_name && !section_type))
		return -1;

	_CtSgwGetAppVendorVersion(pkg_name, &vendor, &version);
	g_assert_nonnull(vendor);
	sprintf(name, "com.%s.%s%d", vendor, pkg_name, version);

	if (section_name) {
		sprintf(path, "/com/%s/%s%d/Config/%s/%s", vendor, pkg_name, version, section_name, section_name);
		sprintf(intf, "%s.Config.%s", name, section_name);

		ret = CtSgwDBusGetAllProperty(name, path, intf, &value);

		if (value) {
			g_variant_get(value, "(a{sv})", &iter);

			n = g_variant_iter_n_children(iter);
			*optsize = n;

			opt = (CtSgwUCIOpt_t *)malloc(sizeof(CtSgwUCIOpt_t) * n);
			*opts = opt;
			
			while (g_variant_iter_loop(iter,"{sv}", &key, &vv))
			{
				g_strlcpy(opt->name, key, MAX_UCI_OPT_NAME_LEN);
				g_variant_get(vv, "&s", &val);
				if (val)
					g_strlcpy(opt->value, val, MAX_UCI_OPT_VAL_LEN);
				opt++;
			}

			g_variant_iter_free(iter);
			g_variant_unref(value);
		}
	}
	else if (section_type) {
		
		sprintf(path, "/com/%s/%s%d/Config/%s", vendor, pkg_name, version, section_type);
		sprintf(intf, "%s.Config.%s", name, section_type);

		cnt = _CtSgwGetNumOfNodes(name, path);
		
		sprintf(path, "/com/%s/%s%d/Config/%s/1", vendor, pkg_name, version, section_type);
		
		ret = CtSgwDBusGetAllProperty(name, path, intf, &value);

		if (value) {
			g_variant_get(value, "(a{sv})", &iter);
			
			n = g_variant_iter_n_children(iter);
			
			//each section have same number of properties
			*optsize = n * cnt;

			opt = (CtSgwUCIOpt_t *)malloc(sizeof(CtSgwUCIOpt_t) * n * cnt);
			*opts = opt;

			//fill properties of 1st section
			while (g_variant_iter_loop(iter,"{sv}", &key, &vv))
			{
				g_variant_get(vv, "&s", &val);
				g_strlcpy(opt->name, key, MAX_UCI_OPT_NAME_LEN);
				if (val)
					g_strlcpy(opt->value, val, MAX_UCI_OPT_VAL_LEN);
				opt++;
			}
			g_variant_iter_free (iter);
			g_variant_unref(value);

			//fill other sections
			for (i = 1; i < cnt; i++) {
				sprintf(path, "/com/%s/%s%d/Config/%s/%d", vendor, pkg_name, version, section_type, i + 1);

				ret = CtSgwDBusGetAllProperty(name, path, intf, &value);
				g_assert_nonnull(value);
				g_variant_get(value, "(a{sv})", &iter);
				
				while (g_variant_iter_loop(iter,"{sv}", &key, &vv))
				{
					g_variant_get(vv, "&s", &val);
					g_strlcpy(opt->name, key, MAX_UCI_OPT_NAME_LEN);
					if (val)
						g_strlcpy(opt->value, val, MAX_UCI_OPT_VAL_LEN);
					opt++;
				}			
				g_variant_iter_free (iter);
				g_variant_unref(value);
			}
		}
	}
	
	return ret;	

#if APPMGR_UCI_SUPPORT
	GDBusConnection *connection;
	GDBusProxy *proxy;
	GError *error = NULL;
	GVariant *result;
	GVariantIter *iter;
	CtSgwUCIOpt_t *opt = NULL;
	gchar *key, *value;
	gint n = 0;

	if (!pkg_name || (!section_name && !section_type))
		return -1;

	connection = g_bus_get_sync (DBUS_TYPE, NULL, &error);
	g_assert_no_error(error);

	proxy = g_dbus_proxy_new_sync(connection,
								  G_DBUS_PROXY_FLAGS_NONE,
								  NULL,					  /* GDBusInterfaceInfo */
								  "com.ctc.appframework1", /* name */
								  "/com/ctc/appframework1", /* object path */
								  "com.ctc.appframework1.UCI",		  /* interface */
								  NULL, /* GCancellable */
								  &error);
	g_assert_no_error(error);

	if (section_name)
		result = g_dbus_proxy_call_sync(proxy,
								"ReadSectionByName",
								g_variant_new("(ss)", pkg_name, section_name),
								G_DBUS_CALL_FLAGS_NONE,
								-1,
								NULL,
								&error);
	else
		result = g_dbus_proxy_call_sync(proxy,
								"ReadSectionByType",
								g_variant_new("(ss)", pkg_name, section_type),
								G_DBUS_CALL_FLAGS_NONE,
								-1,
								NULL,
								&error);
	g_assert(result != NULL);
	g_variant_get(result, "(a{ss})", &iter);

	n = g_variant_iter_n_children(iter);
	*optsize = n;

	opt = (CtSgwUCIOpt_t *)malloc(sizeof(CtSgwUCIOpt_t) * n);
	*opts = opt;
	
	while (g_variant_iter_loop(iter,"{ss}", &key, &value))
	{
		g_strlcpy(opt->name, key, MAX_UCI_OPT_NAME_LEN);
		g_strlcpy(opt->value, value, MAX_UCI_OPT_VAL_LEN);
		opt++;
	}
	g_variant_unref(result);
	g_object_unref(proxy);
	g_object_unref (connection);
#endif
	return 0;
}

int CtSgwUCIWriteOption(const char *pkg_name, const char *section_name, const char *option_name, const char *option_val)
{
	char *vendor = NULL;
	int version = 0, ret = 0;
	char name[128] = {0}, path[128] = {0}, intf[128] = {0};
	GVariant *val;

	if (!pkg_name || !section_name || !option_name || !option_val)
		return -1;

	_CtSgwGetAppVendorVersion(pkg_name, &vendor, &version);
	g_assert_nonnull(vendor);
	sprintf(name, "com.%s.%s%d", vendor, pkg_name, version);
	sprintf(path, "/com/%s/%s%d/Config/%s/%s", vendor, pkg_name, version, section_name, section_name);
	sprintf(intf, "%s.config.%s", name, section_name);

	val = g_variant_new("s", option_val);
	ret = CtSgwDBusSetProperty(name, path, intf, option_name, val);
	
	g_variant_unref(val);

	return ret;

#if APPMGR_UCI_SUPPORT
	GDBusConnection *connection;
	GDBusProxy *proxy;
	GError *error = NULL;
	GVariant *result;
	gint ret = 0;

	if (!pkg_name || !section_name || !option_name || !option_val)
		return -1;

	connection = g_bus_get_sync (DBUS_TYPE, NULL, &error);
	g_assert_no_error(error);

	proxy = g_dbus_proxy_new_sync(connection,
								  G_DBUS_PROXY_FLAGS_NONE,
								  NULL,					  /* GDBusInterfaceInfo */
								  "com.ctc.appframework1", /* name */
								  "/com/ctc/appframework1", /* object path */
								  "com.ctc.appframework1.UCI",		  /* interface */
								  NULL, /* GCancellable */
								  &error);
	g_assert_no_error(error);

	result = g_dbus_proxy_call_sync(proxy,
								"WriteOption",
								g_variant_new("(ssss)", pkg_name, section_name, option_name, option_val),
								G_DBUS_CALL_FLAGS_NONE,
								-1,
								NULL,
								&error);
	g_assert_no_error(error);
	g_assert(result != NULL);
	g_variant_get(result, "(i)", &ret);

	g_variant_unref (result);
	g_object_unref (proxy);
	g_object_unref (connection);

	return ret;
#endif
}


int CtSgwStartApp(const char *app_name)
{
	GDBusConnection *connection;
	GDBusProxy *proxy;
	GError *error = NULL;
	GVariant *result;
	gint ret = 0;
	CtSgwAppStatus_t status;

	if (!app_name)
		return -1;

	g_strlcpy(status.name, app_name, BUFLEN_32);
	CtSgwGetAppStatus(&status);
	if (g_strcmp0(status.state, "RUNNING") == 0) {
		g_printerr("app %s is already running\n", app_name);
		return 0;
	}

	connection = g_bus_get_sync (DBUS_TYPE, NULL, &error);
	g_assert_no_error(error);

	proxy = g_dbus_proxy_new_sync(connection,
								  G_DBUS_PROXY_FLAGS_NONE,
								  NULL,					  /* GDBusInterfaceInfo */
								  "com.ctc.appframework1", /* name */
								  "/com/ctc/appframework1", /* object path */
								  "com.ctc.appframework1.AppAgent",		  /* interface */
								  NULL, /* GCancellable */
								  &error);
	g_assert_no_error(error);

	result = g_dbus_proxy_call_sync(proxy,
								"Run",
								g_variant_new("(s)", app_name),
								G_DBUS_CALL_FLAGS_NONE,
								-1,
								NULL,
								&error);
	g_assert(result != NULL);
	g_variant_get(result, "(i)", &ret);

	g_variant_unref(result);
	g_object_unref (proxy);
	g_object_unref (connection);

	return ret;
}

static int _CtSgwStopReloadApp(const char *app_name, int is_reload)
{
	GDBusConnection *connection;
	GDBusProxy *proxy;
	GError *error = NULL;
	GVariant *result;
	gint ret = 0;
	CtSgwAppStatus_t status;

	if (!app_name)
		return -1;

	g_strlcpy(status.name, app_name, BUFLEN_32);
	CtSgwGetAppStatus(&status);
	if (g_strcmp0(status.state, "RUNNING") != 0) {
		g_printerr("app %s is not running\n", app_name);
		return 0;
	}

	connection = g_bus_get_sync (DBUS_TYPE, NULL, &error);
	g_assert_no_error(error);

	proxy = g_dbus_proxy_new_sync(connection,
								  G_DBUS_PROXY_FLAGS_NONE,
								  NULL,					  /* GDBusInterfaceInfo */
								  "com.ctc.appframework1", /* name */
								  "/com/ctc/appframework1", /* object path */
								  "com.ctc.appframework1.AppAgent",		  /* interface */
								  NULL, /* GCancellable */
								  &error);
	g_assert_no_error(error);

	result = g_dbus_proxy_call_sync(proxy,
								is_reload ? "Reload" : "Stop",
								g_variant_new("(s)", app_name),
								G_DBUS_CALL_FLAGS_NONE,
								-1,
								NULL,
								&error);
	g_assert(result != NULL);
	g_variant_get(result, "(i)", &ret);

	g_variant_unref(result);
	g_object_unref (proxy);
	g_object_unref (connection);

	return ret;

}

int CtSgwStopApp(const char *app_name)
{
	return _CtSgwStopReloadApp(app_name, 0);
}

int CtSgwReloadApp(const char *app_name)
{
	return _CtSgwStopReloadApp(app_name, 1);
}

static int _CtSgwInsUpgApp(const char *app_file, int is_upgrade)
{
	GDBusConnection *connection;
	GDBusProxy *proxy;
	GError *error = NULL;
	GVariant *result;
	gchar *app_ptr = NULL, *end_ptr = NULL;
	gchar app_name[BUFLEN_128] = {0};
	gint ret = 0;
	CtSgwAppStatus_t status;

	if (!app_file)
		return -1;

	g_strlcpy(app_name, app_file, BUFLEN_128);
	app_ptr = g_strstr_len(app_name, -1, ".ipk");
	if (!app_ptr) {
		fprintf(stderr, "Invalid app %s\n", app_name);
		return -1;
	}
	if (access(app_file, R_OK) < 0) {
		fprintf(stderr, "Can not access app %s\n", app_file);
		return -1;
	}
	app_ptr = strrchr(app_name, '/');
	if (app_ptr)
		app_ptr++;
	else
		app_ptr = app_name;

	end_ptr = g_strstr_len(app_ptr, -1, "_");
	if (end_ptr)
		*end_ptr = '\0';

	g_strlcpy(status.name, app_ptr, BUFLEN_32);
	CtSgwGetAppStatus(&status);
	if (g_strcmp0(status.state, "RUNNING") == 0) {
		g_printerr("app %s is running, please stop it first\n", app_ptr);
		return -1;
	}

	connection = g_bus_get_sync (DBUS_TYPE, NULL, &error);
	g_assert_no_error(error);

	proxy = g_dbus_proxy_new_sync(connection,
								  G_DBUS_PROXY_FLAGS_NONE,
								  NULL,					  /* GDBusInterfaceInfo */
								  "com.ctc.appframework1", /* name */
								  "/com/ctc/appframework1", /* object path */
								  "com.ctc.appframework1.AppAgent",		  /* interface */
								  NULL, /* GCancellable */
								  &error);
	g_assert_no_error(error);

	result = g_dbus_proxy_call_sync(proxy,
								is_upgrade ? "Upgrade" : "Install",
								g_variant_new("(ss)", app_ptr, app_file),
								G_DBUS_CALL_FLAGS_NONE,
								-1,
								NULL,
								&error);
	g_assert(result != NULL);
	g_variant_get(result, "(i)", &ret);

	g_variant_unref (result);
	g_object_unref (proxy);
	g_object_unref (connection);

	return ret;

}

int CtSgwInstallApp(const char *app_file)
{
	return _CtSgwInsUpgApp(app_file, 0);
}

int CtSgwUpgradeApp(const char *app_file)
{
	return _CtSgwInsUpgApp(app_file, 1);
}

int CtSgwUninstallApp(const char *app_name)
{
	GDBusConnection *connection;
	GDBusProxy *proxy;
	GError *error = NULL;
	GVariant *result;
	gint ret = 0;
	CtSgwAppStatus_t status;

	if (!app_name)
		return -1;

	g_strlcpy(status.name, app_name, BUFLEN_32);
	CtSgwGetAppStatus(&status);
	if (g_strcmp0(status.state, "RUNNING") == 0) {
		g_printerr("app %s is running, please stop it first\n", app_name);
		return -1;
	}

	connection = g_bus_get_sync (DBUS_TYPE, NULL, &error);
	g_assert_no_error(error);

	proxy = g_dbus_proxy_new_sync(connection,
								  G_DBUS_PROXY_FLAGS_NONE,
								  NULL,					  /* GDBusInterfaceInfo */
								  "com.ctc.appframework1", /* name */
								  "/com/ctc/appframework1", /* object path */
								  "com.ctc.appframework1.AppAgent",		  /* interface */
								  NULL, /* GCancellable */
								  &error);
	g_assert_no_error(error);

	result = g_dbus_proxy_call_sync(proxy,
								"Uninstall",
								g_variant_new("(s)", app_name),
								G_DBUS_CALL_FLAGS_NONE,
								-1,
								NULL,
								&error);
	g_assert(result != NULL);
	g_variant_get(result, "(i)", &ret);

	g_variant_unref (result);
	g_object_unref (proxy);
	g_object_unref (connection);

	return ret;
}

int CtSgwGetAppStatus(CtSgwAppStatus_t *app_status)
{
	GDBusConnection *connection;
	GDBusProxy *proxy;
	GError *error = NULL;
	GVariant *result;
	gchar *str;
	gint ret = 0;

	connection = g_bus_get_sync (DBUS_TYPE, NULL, &error);
	g_assert_no_error(error);

	proxy = g_dbus_proxy_new_sync(connection,
								  G_DBUS_PROXY_FLAGS_NONE,
								  NULL,					  /* GDBusInterfaceInfo */
								  "com.ctc.appframework1", /* name */
								  "/com/ctc/appframework1", /* object path */
								  "com.ctc.appframework1.AppAgent",		  /* interface */
								  NULL, /* GCancellable */
								  &error);
	g_assert_no_error(error);

	result = g_dbus_proxy_call_sync(proxy,
								"GetStatus",
								g_variant_new("(s)", app_status->name),
								G_DBUS_CALL_FLAGS_NONE,
								-1,
								NULL,
								&error);
	g_assert(result != NULL);
	g_variant_get(result, "(s)", &str);
	g_strlcpy(app_status->state, str, BUFLEN_16);

	g_variant_unref (result);
	g_object_unref (proxy);
	g_object_unref (connection);

	return ret;
}

static int _handle_method_call(const char           *object_path,
				   const char           *interface_name,
				   const char           *method_name,
				   GVariant              *inargs,
				   GVariant              **outargs,
				   void               *user_data)
{
	guint ret = 0;

	//g_print("%s,%d: call %s\n", __func__, __LINE__, method_name);
	if (g_strcmp0(method_name, "Stop") == 0) {

		ret = sgw_dbus_service_context->app_cbs->stop();
		*outargs = g_variant_new ("(u)", ret);
	} else if (g_strcmp0(method_name, "Reload") == 0) {

		ret = sgw_dbus_service_context->app_cbs->reload();
		*outargs = g_variant_new ("(u)", ret);
	} else if (g_strcmp0(method_name, "Restore") == 0) {

		ret = sgw_dbus_service_context->app_cbs->restore_factory();
		*outargs = g_variant_new ("(u)", ret);
	} else if (g_strcmp0(method_name, "PostMsg") == 0) {
		char *msg = NULL;
	
		g_variant_get (inargs, "(&s)", &msg);

		sgw_dbus_service_context->app_cbs->post_msg(msg);
	}

	return ret;
}

CtSgwGDBusInterfaceVTable_t interface_vtable = { _handle_method_call, NULL, NULL, NULL, NULL };
CtSgwDBusNodeInfo_t *CtSgwAppRegisterMgtFuncs(CtSgwAppMgtCallbacks_t *cbs)
{
	CtSgwDBusNodeInfo_t *mm_data;
	guint registration_id;
	char obj_path[CTC_DBUS_NAME_LEN] = {0};
	char *ptr = NULL;

	const unsigned char *mm_xml = NULL;

	if ((sgw_dbus_service_context == NULL) || (!sgw_dbus_service_context->is_service_started))
	{
		g_print ("DBus service is not started.\n");
		return NULL;
	}

	sgw_dbus_service_context->app_cbs = cbs;

	asprintf((char **)&mm_xml, 
		"<node>"
		"  <interface name='%s.management'>"
		"	 <method name='Stop'>"
		"	 <arg type='u' name='response' direction='out'/>"
		"	 </method>"
		"	 <method name='Reload'>"
		"	 <arg type='u' name='response' direction='out'/>"
		"	 </method>"
		"	 <method name='Restore'>"
		"	 <arg type='u' name='response' direction='out'/>"
		"	 </method>"
		"	 <method name='PostMsg'>"
		"	 <arg type='s' name='message' direction='in'/>"
		"	 </method>"
		"  </interface>"
		"</node>", sgw_dbus_service_context->service_name);
	g_assert_nonnull(mm_xml);

	mm_data = CtSgwDBusNodeParseXml(mm_xml);

	snprintf(obj_path, CTC_DBUS_NAME_LEN, "/%s", sgw_dbus_service_context->service_name);
	ptr = strchr(obj_path, '.');
	while (ptr) {
		*ptr= '/';
		ptr = strchr(ptr + 1, '.');
	}
	
	registration_id = CtSgwDBusRegisterObject(obj_path,
					  mm_data->interfaces[0],
					  &interface_vtable,
					  NULL);
	g_assert(registration_id > 0);

	free((char *)mm_xml);

	return mm_data;
}


