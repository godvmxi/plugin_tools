
#include <sys/types.h>
#include "capi.h"


CtSgwDbusServiceContext_t *sgw_dbus_service_context = NULL;
CtSgwDBusSignalSubstContext_t *sgw_dbus_sigsubst_list_head = NULL;
CtSgwDBusObjectRegContext_t *sgw_dbus_obj_reg_list_head = NULL;


/*
 * Function Name: CtSgwInit
 *
 * Description: Initialize CAPI library
 *
 * Parameter:
 *    service_name <IN>:    The service name this app wanna own
 *
 * Return: 0 on success or other on failed.
 *
 */
int CtSgwInit (const char *service_name)
{
    return 0;
}

/*
 * Function Name: CtSgwDestroy
 *
 * Description: Release resource which allocated when initialize CAPI library
 *
 * Parameter  : None
 *
 * Return: None.
 *
 */
void CtSgwDestroy (void)
{
    return;
}

/*
 * Function Name: CtSgwGetAPIVersion
 *
 * Description: Get CAPI library version
 *
 * Parameter  :
 *      ver <OUT>:    Memory to contain API version.
 *
 * Return: None.
 *
 */
void CtSgwGetAPIVersion (char ver[MAX_VER_LEN + 1])
{
    strcpy (ver, CAPI_VER);
    return;
}

/***********************************************************************
 *                                                                     *
 * Private function defined here                                       *
 *                                                                     *
 **********************************************************************/
static void on_name_acquired (GDBusConnection    *connection,
                              const gchar        *name,
                              gpointer            user_data)
{
    GMainLoop   *loop = (GMainLoop *)user_data;
    
    g_main_loop_quit (loop);
}

static void on_name_lost (GDBusConnection    *connection,
                          const gchar        *name,
                          gpointer            user_data)
{
    GMainLoop   *loop = (GMainLoop *)user_data;
    g_print ("%s: connection = %p, name = %s\n", __FUNCTION__, connection, name);
    sgw_dbus_service_context->errState = TRUE;
    g_main_loop_quit (loop);
}

static void on_bus_acquired (GDBusConnection    *connection,
                             const gchar        *name,
                             gpointer            user_data)
{
    sgw_dbus_service_context->connection = connection;
}

static gpointer loop_thread (gpointer user_data)
{
    GMainContext  *thread_context = (GMainContext *) user_data;
    GMainLoop     *main_loop;

    g_main_context_push_thread_default (thread_context);

    main_loop = g_main_loop_new (thread_context, FALSE);
    sgw_dbus_service_context->loop = main_loop;

    g_main_loop_run(main_loop);

    g_main_loop_unref (main_loop);
    g_main_context_pop_thread_default (thread_context);
    g_main_context_unref (thread_context);

    return NULL;
}
/***********************************************************************
 *                                                                     *
 * End of private function defination                                  *
 *                                                                     *
 **********************************************************************/
    

/*
 * Function Name: CtSgwDBusStartService
 *
 * Description: Start DBus service in app
 *
 * Parameter:
 *    service_name <IN>:    The service name this app wanna own
 *
 * Return: 0 on success or other on failed.
 *
 */
int CtSgwDBusStartService ( const char *service_name )
{
    guint owner_id;
    GMainLoop   *main_loop;
    GMainContext *main_context;

    if ((sgw_dbus_service_context != NULL) && (sgw_dbus_service_context->is_service_started))
    {
        g_print ("Service is already stated.\n");
        return -1;
    }

    
    if ( sgw_dbus_service_context == NULL )
    {
        sgw_dbus_service_context = g_new0 (CtSgwDbusServiceContext_t, 1);
        if (NULL == sgw_dbus_service_context)
        {
            g_print("Memory allocate failed\n");
            return -1;
        }

        sgw_dbus_service_context->errState = FALSE;
        g_stpcpy(sgw_dbus_service_context->service_name, service_name);
    }

    sgw_dbus_service_context->is_service_started = TRUE;
    main_loop = g_main_loop_new (NULL, FALSE);
    owner_id = g_bus_own_name (G_BUS_TYPE_SYSTEM,
                               service_name,
                               G_BUS_NAME_OWNER_FLAGS_NONE,
                               on_bus_acquired,
                               on_name_acquired,
                               on_name_lost,
                               (gpointer)main_loop,
                               NULL);
    
    sgw_dbus_service_context->bus_owner_id = owner_id;
    
    g_main_loop_run(main_loop);
    g_main_loop_unref(main_loop);
    if (sgw_dbus_service_context->errState)
    {
        if ((sgw_dbus_service_context == NULL) || (!sgw_dbus_service_context->is_service_started)) 
            return -1;

        sgw_dbus_service_context->is_service_started = FALSE;
        
        if ( (sgw_dbus_service_context->connection != NULL) &&
            !(g_dbus_connection_is_closed (sgw_dbus_service_context->connection)))
        {
            g_dbus_connection_close_sync (sgw_dbus_service_context->connection, NULL, NULL);
        }

        
        g_bus_unown_name (sgw_dbus_service_context->bus_owner_id);

        g_free (sgw_dbus_service_context);
        sgw_dbus_service_context = NULL;
        
        return -1;
    }

    main_context = g_main_context_ref_thread_default();
    
    sgw_dbus_service_context->context = main_context;

    sgw_dbus_service_context->tid = g_thread_new ("mainLoop", loop_thread, main_context);

    return 0;

}

/*
 * Function Name: CtSgwDBusStopService
 *
 * Description: Stop DBus service in app and release all resource
 *
 * Parameter:        
 *
 * Return: 0 on success or other on failed.
 *
 */
int CtSgwDBusStopService(void)
{
    if ((sgw_dbus_service_context == NULL) || (!sgw_dbus_service_context->is_service_started)) 
        return -1;

    sgw_dbus_service_context->is_service_started = FALSE;
    
    g_main_loop_quit (sgw_dbus_service_context->loop);

    if (! g_dbus_connection_is_closed (sgw_dbus_service_context->connection))
    {
        g_dbus_connection_close_sync (sgw_dbus_service_context->connection, NULL, NULL);
    }

    
    g_bus_unown_name (sgw_dbus_service_context->bus_owner_id);

    g_free (sgw_dbus_service_context);
    sgw_dbus_service_context = NULL;

    return 0;
}

/*
 * Function Name: CtSgwDBusNodeParseXml
 *
 * Description: Parses xml_data and returns a CtSgwDBusNodeInfo_t representing the data
 *
 * Parameter:
 *    xml_data <IN>:    Valid D-Bus introspection XML
 *
 * Return: a CtSgwDBusNodeInfo_t structure or NULL if failed..
 *
 */
CtSgwDBusNodeInfo_t *CtSgwDBusNodeParseXml (const unsigned char *xml_data)
{
    GDBusNodeInfo * nodeInfo= NULL;
    
    if (xml_data == NULL)
        return NULL;

    nodeInfo = g_dbus_node_info_new_for_xml ( (const gchar *)xml_data, NULL );

    return ((CtSgwDBusNodeInfo_t *) nodeInfo);
}

/*
 * Function Name: CtSgwDBusNodeFindInterface
 *
 * Description: Looks up information about an interface
 *
 * Parameter:
 *             node <IN>:   A CtSgwDBusNodeInfo_t
 *   interface_name <IN>:   A D-Bus interface name
 *
 * Return: a CtSgwGDBusInterfaceInfo_t structure or NULL if failed..
 *
 */
CtSgwGDBusInterfaceInfo_t *CtSgwDBusNodeFindInterface(CtSgwDBusNodeInfo_t *node, const char *interface_name)
{
    GDBusInterfaceInfo *interfaceInfo = NULL;

    if ( (node == NULL) || (interface_name == NULL))
        return NULL;

    interfaceInfo = g_dbus_node_info_lookup_interface (node, interface_name);

    return ((CtSgwGDBusInterfaceInfo_t *)interfaceInfo);
}

/*
 * Function Name: CtSgwDBusNodeInfoUnref
 *
 * Description: if node_info is statically allocated, does nothing. Otherwise 
 *              decreases the reference count of info . When its reference count 
 *              drops to 0, the memory used is freed.
 *
 * Parameter:
 *    node_info <IN>:   A CtSgwGDBusInterfaceInfo_t
 *
 * Return:
 *
 */
void CtSgwDBusNodeInfoUnref (CtSgwDBusNodeInfo_t *node_info)
{
    if (node_info == NULL)
        return;

    g_dbus_node_info_unref (node_info);
}


/***********************************************************************
 *                                                                     *
 * Private function                                                    *
 *                                                                     *
 **********************************************************************/

static CtSgwDBusObjectRegContext_t *CtSgwDBusObjectRegEntryLookup (const char *object_path, const char *interface_name)
{
    CtSgwDBusObjectRegContext_t *pEntry = sgw_dbus_obj_reg_list_head;

    for (; pEntry != NULL; pEntry = pEntry->next)
    {
        if ( (g_strcmp0 (object_path, pEntry->object_path) == 0) &&
             (g_strcmp0 (interface_name, pEntry->interface_name) == 0))
        {
            //g_print ("%s: found the entry (%s, %s).\n", __FUNCTION__, object_path, interface_name);
            return pEntry;
        }
    }

    //g_print ("%s: did not found the entry.\n", __FUNCTION__);
    return NULL;
}

static CtSgwDBusObjectRegContext_t *CtSgwDBusObjectRegEntryAdd (const char *object_path, const char *interface_name, CtSgwGDBusInterfaceVTable_t *vtable)
{
    CtSgwDBusObjectRegContext_t *pEntry = NULL;

    pEntry = CtSgwDBusObjectRegEntryLookup (object_path, interface_name);

    g_return_val_if_fail ((pEntry == NULL), NULL);

    pEntry = g_try_new0 (CtSgwDBusObjectRegContext_t, 1);
    g_return_val_if_fail ((pEntry != NULL), NULL);
    pEntry->object_path = g_strdup( object_path );
    pEntry->interface_name = g_strdup( interface_name );
    pEntry->vtable = vtable;
    pEntry->next = sgw_dbus_obj_reg_list_head;
    sgw_dbus_obj_reg_list_head = pEntry;

    return sgw_dbus_obj_reg_list_head;
}

static gint32 CtSgwDBusObjectRegEntryDelById(gint32 regid)
{
    CtSgwDBusObjectRegContext_t *pEntry = NULL;
    CtSgwDBusObjectRegContext_t *pDel = NULL;

    if (sgw_dbus_obj_reg_list_head != NULL)
    {
        if (sgw_dbus_obj_reg_list_head->regid == regid)
        {
            pEntry = sgw_dbus_obj_reg_list_head->next;
            g_free (sgw_dbus_obj_reg_list_head->object_path);
            g_free (sgw_dbus_obj_reg_list_head->interface_name);
            g_free (sgw_dbus_obj_reg_list_head);
            sgw_dbus_obj_reg_list_head = pEntry;

            return 0;
        }
    }


    for (pEntry = sgw_dbus_obj_reg_list_head; pEntry->next != NULL; pEntry = pEntry->next)
    {
        if ( pEntry->next->regid == regid)
        {
            pDel = pEntry->next;
            pEntry->next = pDel->next;
            g_free (pDel->object_path);
            g_free (pDel->interface_name);
            g_free (pDel);
            return 0;
        }
    }

    return -1;
}


static void ctsgw_method_call (GDBusConnection *connection,
                               const gchar *sender,
                               const gchar *object_path,
                               const gchar *interface_name,
                               const gchar *method_name,
                               GVariant *parameters,
                               GDBusMethodInvocation *invocation,
                               gpointer user_data)
{
    CtSgwDBusObjectRegContext_t *pEntry = NULL;
    GVariant *value = NULL;
    gint32  ret = -1;
    gchar *real_interface = NULL;

    // For org.freedesktop.DBus.Properties.Get/Set/SetMulti/GetAll    
    if ( (g_strcmp0 (interface_name, "org.freedesktop.DBus.Properties") == 0) ||
         (g_strcmp0 (interface_name, "com.ctc.igd1.Properties") == 0))
    {
        if (g_strcmp0 (method_name, "Get") == 0)
        {
            g_variant_get (parameters, "(&ss)", &real_interface, NULL);
        }
        else if (g_strcmp0 (method_name, "Set") == 0)
        {
            g_variant_get (parameters, "(&ssv)", &real_interface, NULL, NULL);
        }
        else if (g_strcmp0 (method_name, "GetAll") == 0)
        {
            g_variant_get (parameters, "(&s)", &real_interface);
        }
        else if (g_strcmp0 (method_name, "SetMulti") == 0)
        {
            g_variant_get (parameters, "(&sv)", &real_interface, NULL);
        }
    }
    else
    {
        real_interface = g_strdup (interface_name);
    }

    pEntry = CtSgwDBusObjectRegEntryLookup(object_path, real_interface);
    g_return_if_fail ((pEntry != NULL));

    if (pEntry->vtable->method_func != NULL)
    {
        ret = pEntry->vtable->method_func (object_path, interface_name, method_name, parameters, &value, user_data);
        if (value == NULL)
        {
            g_dbus_method_invocation_return_value(invocation, NULL);
            return;
        }
        
        if (ret == 0)
        {
            g_dbus_method_invocation_return_value(invocation, value);
        }
        else
        {
            guint32 quark;
            gint code;
            gchar *error_msg = NULL;
            g_variant_get (value, "(ui&s)", &quark, &code, &error_msg);
            g_dbus_method_invocation_return_error (invocation,
                                                   quark,
                                                   code,
                                                   "%s",
                                                   error_msg);
        }

        g_variant_unref (value);
    }

    return;
}

static GVariant *ctsgw_get_property (GDBusConnection *connection,
                              const gchar *sender,
                              const gchar *object_path,
                              const gchar *interface_name,
                              const gchar *property_name,
                              GError **error,
                              gpointer user_data)
{
    CtSgwDBusObjectRegContext_t *pEntry = NULL;
    GVariant *value = NULL;

    pEntry = CtSgwDBusObjectRegEntryLookup(object_path, interface_name);
    g_return_val_if_fail ((pEntry != NULL), NULL);

    if (pEntry->vtable->get_func != NULL)
    {
        pEntry->vtable->get_func (object_path, property_name, &value, user_data);
        return value;
    }

    return NULL;
}

static gboolean ctsgw_set_property (GDBusConnection *connection,
                             const gchar *sender,
                             const gchar *object_path,
                             const gchar *interface_name,
                             const gchar *property_name,
                             GVariant *value,
                             GError **error,
                             gpointer user_data)
{
    CtSgwDBusObjectRegContext_t *pEntry = NULL;

    pEntry = CtSgwDBusObjectRegEntryLookup(object_path, interface_name);
    g_return_val_if_fail ((pEntry != NULL), FALSE);

    if (pEntry->vtable->set_func != NULL)
    {
        pEntry->vtable->set_func (object_path, property_name, value, user_data);
        return TRUE;
    }

    return FALSE;
}

/***********************************************************************
 *                                                                     *
 * Private function end                                                *
 *                                                                     *
 **********************************************************************/



/*
 * Function Name: CtSgwDBusRegisterObject
 *
 * Description: Registers callbacks for exported objects at object_path with the D-Bus interface 
 *              that is described in interface_info
 *
 * Parameter:
 *      object_path <IN>:     the object path to register at.
 *   interface_info <IN>:     introspection data for the interface.
 *           vtable <IN>:     a CtSgwDBusInterfaceVTable to call into or NULL
 *        user_data <IN>:     data to pass to functions in vtable.
 *
 * Return: 0 if error is set, otherwise a registration id (never 0) that can be used with CtSgwDBusUnRegisterObject()
 *
 */
unsigned int CtSgwDBusRegisterObject(const char *object_path, 
                                     CtSgwGDBusInterfaceInfo_t *interface_info,
                                     CtSgwGDBusInterfaceVTable_t *vtable,
                                     void *user_data)
{
    guint regid = -1;
    CtSgwDBusObjectRegContext_t *pEntry = NULL;
    GDBusInterfaceVTable  real_vtable;

    g_return_val_if_fail ((interface_info != NULL), 0);

    if (vtable != NULL)
    {
        pEntry = CtSgwDBusObjectRegEntryAdd (object_path, interface_info->name, vtable);
        g_return_val_if_fail ((pEntry != NULL), 0);
    }

    if (vtable != NULL)
    {
        real_vtable.method_call = NULL;
        real_vtable.get_property = NULL;
        real_vtable.set_property = NULL;
    
        if (vtable->method_func != NULL)
            real_vtable.method_call = ctsgw_method_call;

        if (vtable->get_func != NULL)
            real_vtable.get_property = ctsgw_get_property;

        if (vtable->set_func != NULL)
            real_vtable.set_property = ctsgw_set_property;
    }
        
    regid = g_dbus_connection_register_object (sgw_dbus_service_context->connection,
                                               object_path,
                                               interface_info,
                                               (vtable != NULL) ? &real_vtable : NULL,
                                               (gpointer)user_data,
                                               NULL,
                                               NULL);
    if (vtable != NULL)
    {
        pEntry->regid = regid;
    }
    
    return regid;
}

/*
 * Function Name: CtSgwDBusUnRegisterObject
 *
 * Description: Unregisters an object.
 *
 * Parameter:
 *    id <IN>:     a registration id obtained from CtSgwDBusRegisterObject.
 *
 * Return: TRUE if the object was unregistered, FALSE otherwise
 *
 */
void CtSgwDBusUnRegisterObject(unsigned int id)
{
    if ( id <= 0 )
    {
        g_print("invalid registration id.\n");
        return;
    }

    g_dbus_connection_unregister_object ( sgw_dbus_service_context->connection, id);
    CtSgwDBusObjectRegEntryDelById(id);
}

/*
 * Function Name: CtSgwDBusSetProperty
 *
 * Description: Set a property value.
 *
 * Parameter:
 *     service_name <IN>:     a unique or well-known bus name or NULL.
 *      object_path <IN>:     path of remote object.
 *        prop_name <IN>:     the name of property member
 *            value <IN>:     value of the property member to set to.
 *
 * Return: 0 on success, otherwise failed.
 *
 */
int CtSgwDBusSetProperty(const char *service_name,
                         const char *object_path,
                         const char *interface_name,
                         const char *prop_name,
                         GVariant *value)
{
    GDBusConnection *connection;
    GVariant *retValue = NULL;
    gboolean temp_conn = FALSE;
    int ret = -1;

    if ((sgw_dbus_service_context == NULL) || (sgw_dbus_service_context->connection == NULL))
    {
        connection = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, NULL);
        temp_conn = TRUE;
    }
    else
    {
        connection = sgw_dbus_service_context->connection;
    }

    g_return_val_if_fail (((connection != NULL) && (G_IS_DBUS_CONNECTION (connection))), CTSGW_NOK);
    
    retValue = g_dbus_connection_call_sync ( connection,
                                             service_name,
                                             object_path,
                                             "com.ctc.igd1.Properties",
                                             "Set",
                                             g_variant_new ("(ssv)", interface_name, prop_name, value),
                                             NULL,
                                             G_DBUS_CALL_FLAGS_NONE,
                                             -1,
                                             NULL,
                                             NULL);

    if (retValue != NULL)
    {
        g_variant_unref(retValue);
        ret = 0;
    }

    if (temp_conn)
        g_object_unref (connection);

    return ret;
}

/*
 * Function Name: CtSgwDBusSetMultiProperty
 *
 * Description: Set values of multiple properties.
 *
 * Parameter:
 *     service_name <IN>:    a unique or well-known bus name or NULL.
 *      object_path <IN>:    path of remote object.
 *            value <IN>:    dict type value of the property member/value pair to set to.
 *
 * Return: 0 on success, otherwise failed.
 *
 */
int CtSgwDBusSetMultiProperty(const char *service_name,
                              const char *object_path,
                              const char *interface_name,
                              GVariant *values)
{
    GDBusConnection *connection;
    GVariant *retValue = NULL;
    gboolean temp_conn = FALSE;
    int ret = -1;

    if ((sgw_dbus_service_context == NULL) || (sgw_dbus_service_context->connection == NULL))
    {
        connection = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, NULL);
        temp_conn = TRUE;
    }
    else
    {
        connection = sgw_dbus_service_context->connection;
    }

    g_return_val_if_fail (((connection != NULL) && (G_IS_DBUS_CONNECTION (connection))), CTSGW_NOK);

    retValue = g_dbus_connection_call_sync (connection,
                                            service_name,
                                            object_path,
                                            "com.ctc.igd1.Properties",
                                            "SetMulti",
                                            g_variant_new ("(sv)", interface_name, values),
                                            NULL,
                                            G_DBUS_CALL_FLAGS_NONE,
                                            -1,
                                            NULL,
                                            NULL);

    if (retValue != NULL)
    {
        g_variant_unref(retValue);
        ret = 0;
    }

    if (temp_conn)
        g_object_unref (connection);
    
    return ret;
}

/*
 * Function Name: CtSgwDBusGetProperty
 *
 * Description: Get value of a specific property member.
 *
 * Parameter:
 *     service_name  <IN>:    a unique or well-known bus name or NULL.
 *      object_path  <IN>:    path of remote object.
 *        prop_name  <IN>:    the name of property member
 *            value <OUT>:    value of the property member to save to.
 *
 * Return: 0 on success, otherwise failed.
 *
 */
int CtSgwDBusGetProperty(const char *service_name,
                         const char *object_path,
                         const char *interface_name,
                         const char *prop_name,
                         GVariant  **value)
{
    GDBusConnection *connection;
    gboolean temp_conn = FALSE;
    int ret = -1;

    if ((sgw_dbus_service_context == NULL) || (sgw_dbus_service_context->connection == NULL))
    {
        connection = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, NULL);
        temp_conn = TRUE;
    }
    else
    {
        connection = sgw_dbus_service_context->connection;
    }

    *value = g_dbus_connection_call_sync (connection,
                                          service_name,
                                          object_path,
                                          "com.ctc.igd1.Properties",
                                          "Get",
                                          g_variant_new ("(ss)", interface_name, prop_name),
                                          G_VARIANT_TYPE("(v)"),
                                          G_DBUS_CALL_FLAGS_NONE,
                                          -1,
                                          NULL,
                                          NULL);

    if (*value != NULL)
    {
        ret = 0;
    }

    if (temp_conn)
        g_object_unref (connection);

    return ret;

}

/*
 * Function Name: CtSgwDBusGetAllProperty
 *
 * Description: Get value of all readable property members.
 *
 * Parameter:
 *    service_name  <IN>:    a unique or well-known bus name or NULL.
 *     object_path  <IN>:    path of remote object.
 *          values <OUT>:    value of the all readable properties members to save to.
 *
 * Return: 0 on success, otherwise failed.
 *
 */
int CtSgwDBusGetAllProperty(const char *service_name,
                            const char *object_path,
                            const char *interface_name,
                            GVariant  **values)
{
    GDBusConnection *connection;
    gboolean temp_conn = FALSE;
    int ret = -1;

    if ((sgw_dbus_service_context == NULL) || (sgw_dbus_service_context->connection == NULL))
    {
        connection = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, NULL);
        temp_conn = TRUE;
    }
    else
    {
        connection = sgw_dbus_service_context->connection;
    }

    *values = g_dbus_connection_call_sync (connection,
                                           service_name,
                                           object_path,
                                           "com.ctc.igd1.Properties",
                                           "GetAll",
                                           g_variant_new ("(s)", interface_name),
                                           G_VARIANT_TYPE("(a{sv})"),
                                           G_DBUS_CALL_FLAGS_NONE,
                                           -1,
                                           NULL,
                                           NULL);

    if (*values != NULL)
    {
        ret = 0;
    }

    if (temp_conn)
        g_object_unref (connection);

    return ret;
}

/*
 * Function Name: CtSgwDBusCallMethod
 *
 * Description:  invokes the method_name method on the interface_name D-Bus interface 
 *               on the remote object at object_path owned by service_name .
 *
 * Parameter:
 *     service_name  <IN>:    a unique or well-known bus name or NULL.
 *      object_path  <IN>:    path of remote object.
 *   interface_name  <IN>:    D-Bus interface to invoke method on
 *      method_name  <IN>:    the name of the method to invoke
 *           inargs  <IN>:    a GVariant tuple with parameters for the method or NULL if not passing
 *          outargs <OUT>:    return values. Free with CtSgwVariantUnRe()
 *
 * Return: 0 on success, otherwise failed.
 *
 */
int CtSgwDBusCallMethod(const char *service_name,
                        const char *object_path,
                        const char *interface_name,
                        const char *method_name,
                        GVariant   *inargs,
                        GVariant  **outargs,
                        int timeout)
{
    GDBusConnection *connection;
    gboolean temp_conn = FALSE;
    GVariant *retValue = NULL;

    if ((sgw_dbus_service_context == NULL) || (sgw_dbus_service_context->connection == NULL))
    {
        connection = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, NULL);
        temp_conn = TRUE;
    }
    else
    {
        connection = sgw_dbus_service_context->connection;
    }
    
    retValue = g_dbus_connection_call_sync (connection,
                                            service_name,
                                            object_path,
                                            interface_name,
                                            method_name,
                                            inargs,
                                            NULL,
                                            G_DBUS_CALL_FLAGS_NONE,
                                            timeout,
                                            NULL,
                                            NULL);

    if (outargs != NULL)
    {
        if (retValue == NULL)
            outargs = NULL;
        else
            *outargs = retValue;
    }

    if (temp_conn)
        g_object_unref (connection);

    return 0;
}

/*
 * Function Name: CtSgwDBusEmitSignal
 *
 * Description: Emits a signal.
 *
 * Parameter:
 *     service_name <IN>:    a unique or well-known bus name or NULL.
 *      object_path <IN>:    path of remote object.
 *   interface_name <IN>:    D-Bus interface to emit a signal on
 *      signal_name <IN>:    the name of the signal to emit.
 *             args <IN>:    a GVariant tuple with parameters for the signal or NULL if not passing parameters
 *
 * Return: TRUE unless error is set.
 *
 */
int CtSgwDBusEmitSignal(const char *service_name,
                        const char *object_path,
                        const char *interface_name,
                        const char *signal_name,
                        GVariant *args)
{
    gboolean ret = FALSE;

    ret = g_dbus_connection_emit_signal (sgw_dbus_service_context->connection,
                                         service_name,
                                         object_path,
                                         interface_name,
                                         signal_name,
                                         args,
                                         NULL);

    return ret;
}


/****************************************************************************
 *                                                                          *
 * Private Function                                                         *
 *                                                                          *
 ****************************************************************************/
static CtSgwDBusSignalSubstContext_t * 
CtSgwDBusSignalSubstEntryLookup (const char *sender_name,
                                 const char *object_path,
                                 const char *interface_name,
                                 const char *signal_name)
{
    CtSgwDBusSignalSubstContext_t *pEntry = sgw_dbus_sigsubst_list_head;

    for (; pEntry != NULL; pEntry = pEntry->next)
    {
        if ( (g_strcmp0 (sender_name, pEntry->sender_name) == 0) &&
             (g_strcmp0 (object_path, pEntry->object_path) == 0) &&
             (g_strcmp0 (interface_name, pEntry->interface_name) == 0) &&
             (g_strcmp0 (signal_name, pEntry->interface_name) == 0))
        {
            //g_print ("%s: found the entry.\n", __FUNCTION__);
            return pEntry;
        }
    }

    return NULL;
}

static CtSgwDBusSignalSubstContext_t * 
CtSgwDBusSignalSubstEntryAdd (const char *sender_name,
                              const char *object_path,
                              const char *interface_name,
                              const char *signal_name,
                              CtSgwDBusSignalFunction cb,
                              void *user_data)
{
    CtSgwDBusSignalSubstContext_t *pEntry = NULL;

    pEntry = CtSgwDBusSignalSubstEntryLookup (sender_name,
                                              object_path,
                                              interface_name,
                                              signal_name);

    g_return_val_if_fail ((pEntry == NULL), NULL);

    pEntry = g_try_new0 (CtSgwDBusSignalSubstContext_t, 1);
    g_return_val_if_fail ((pEntry != NULL), NULL);
    pEntry->sender_name = g_strdup( sender_name );
    pEntry->object_path = g_strdup( object_path );
    pEntry->interface_name = g_strdup( interface_name );
    pEntry->signal_name = g_strdup( signal_name );
    pEntry->cb = cb;
    pEntry->user_data = user_data;
    pEntry->next = sgw_dbus_sigsubst_list_head;
    sgw_dbus_sigsubst_list_head = pEntry;

    return sgw_dbus_sigsubst_list_head;
}

static gint32 CtSgwDBusSignalSubstEntryDelById(gint32 subid)
{
    CtSgwDBusSignalSubstContext_t *pEntry = NULL;
    CtSgwDBusSignalSubstContext_t *pDel = NULL;

    if (sgw_dbus_sigsubst_list_head != NULL)
    {
        if (sgw_dbus_sigsubst_list_head->reg_id == subid)
        {
            pEntry = sgw_dbus_sigsubst_list_head->next;
            g_free (sgw_dbus_sigsubst_list_head->sender_name);
            g_free (sgw_dbus_sigsubst_list_head->object_path);
            g_free (sgw_dbus_sigsubst_list_head->interface_name);
            g_free (sgw_dbus_sigsubst_list_head->signal_name);
            g_free (sgw_dbus_sigsubst_list_head);
            sgw_dbus_sigsubst_list_head = pEntry;

            return 0;
        }
    }


    for (pEntry = sgw_dbus_sigsubst_list_head; pEntry->next != NULL; pEntry = pEntry->next)
    {
        if ( pEntry->next->reg_id == subid )
        {
            pDel = pEntry->next;
            pEntry->next = pDel->next;
            g_free (pDel->sender_name);
            g_free (pDel->object_path);
            g_free (pDel->interface_name);
            g_free (pDel->signal_name);
            g_free (pDel);
            return 0;
        }
    }

    return -1;
}

static CtSgwDBusSignalSubstContext_t * 
CtSgwDBusAddCustomizedSignalFunction (const char *sender_name,
                                      const char *object_path,
                                      const char *interface_name,
                                      const char *signal_name,
                                      CtSgwDBusSignalFunction cb,
                                      void *user_data) 
{
    CtSgwDBusSignalSubstContext_t *pSigSubstEntry = NULL;
    
    pSigSubstEntry = CtSgwDBusSignalSubstEntryLookup(sender_name,
                                                     object_path,
                                                     interface_name,
                                                     signal_name);

    g_return_val_if_fail (pSigSubstEntry == NULL, NULL);
    pSigSubstEntry = CtSgwDBusSignalSubstEntryAdd (sender_name,
                                                   object_path,
                                                   interface_name,
                                                   signal_name,
                                                   cb,
                                                   user_data);
    
    return pSigSubstEntry;
}

static void CtSgwBusGenericSignalFunction ( GDBusConnection *connection,
                                            const gchar *sender_name,
                                            const gchar *object_path,
                                            const gchar *interface_name,
                                            const gchar *signal_name,
                                            GVariant *parameters,
                                            gpointer user_data)
{
    CtSgwDBusSignalSubstContext_t *pSigSubstEntry = NULL;
    
    pSigSubstEntry = CtSgwDBusSignalSubstEntryLookup(sender_name,
                                                     object_path,
                                                     interface_name,
                                                     signal_name);

    g_return_if_fail (pSigSubstEntry != NULL); 

    pSigSubstEntry->cb(sender_name, object_path, interface_name, signal_name, parameters, user_data);
}

/****************************************************************************
 *                                                                          *
 * End of Private Function                                                  *
 *                                                                          *
 ****************************************************************************/


/*
 * Function Name: CtSgwDBusSubscribeSignal
 *
 * Description: Subscribes to signals on connection and invokes callback with a whenever the signal is received..
 *
 * Parameter:
 *     service_name <IN>:    a unique or well-known bus name or NULL.
 *      object_path <IN>:    path of remote object.
 *   interface_name <IN>:    D-Bus interface to emit a signal on
 *      signal_name <IN>:    D-Bus signal name to match on or NULL to match on all signals
 *               cb <IN>:    callback to invoke when there is a signal matching the requested data
 *             args <IN>:    a GVariant tuple with parameters for the signal or NULL if not passing parameters
 *        user_data <IN>:    user data to pass to callback
 *
 * Return: a subscription identifier that can be used with CtSgwDBusUnSubscribeSignal().
 *
 */
unsigned int CtSgwDBusSubscribeSignal(const char *sender_name,
                                      const char *object_path,
                                      const char *interface_name,
                                      const char *signal_name,
                                      CtSgwDBusSignalFunction cb,
                                      void *user_data)
{
    CtSgwDBusSignalSubstContext_t *pEntry = NULL;
    guint subid = 0;
    
    pEntry = CtSgwDBusAddCustomizedSignalFunction(sender_name, object_path, interface_name, signal_name, cb, user_data);
    g_return_val_if_fail (pEntry != NULL, -1);
    subid = g_dbus_connection_signal_subscribe (sgw_dbus_service_context->connection,
                                                sender_name,
                                                interface_name,
                                                signal_name,
                                                object_path,
                                                NULL,
                                                G_DBUS_SIGNAL_FLAGS_NONE,
                                                CtSgwBusGenericSignalFunction,
                                                user_data,
                                                NULL);

    pEntry->reg_id = subid;
    
    return subid;
}


/*
 * Function Name: CtSgwDBusUnSubscribeSignal
 *
 * Description: Unsubscribes from signals.
 *
 * Parameter:
 *    id <IN>:    a subscription id obtained from CtSgwDBusSubscribeSignal()

 * Return: 
 *
 */
void CtSgwDBusUnSubscribeSignal(unsigned int id)
{
    if (id < 0)
    {
        g_print ("invalid id.\n");
        return;
    }
    
    g_dbus_connection_signal_unsubscribe (sgw_dbus_service_context->connection, id);
    CtSgwDBusSignalSubstEntryDelById (id);
}
