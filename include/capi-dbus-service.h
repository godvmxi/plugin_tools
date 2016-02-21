#ifndef CAPI_DBUS_SERVICE_H
#define CAPI_DBUS_SERVICE_H

#include <gio/gio.h>

typedef struct _GDBusNodeInfo CtSgwDBusNodeInfo_t;
typedef struct _GDBusInterfaceInfo CtSgwGDBusInterfaceInfo_t;
typedef struct _CtSgwDbusServiceContext    CtSgwDbusServiceContext_t;
typedef struct _CtSgwDBusSignalSubstContext CtSgwDBusSignalSubstContext_t;

#ifndef TRUE
#define TRUE    1
#endif

#ifndef FALSE
#define FALSE   0
#endif


typedef int (*CtSgwMgtCallback)(void);
typedef struct {
    CtSgwMgtCallback stop;
    CtSgwMgtCallback reload;
} CtSgwAppMgtCallbacks_t;



#define CTC_DBUS_NAME_LEN 64

typedef int (* CtSgwDBusPropSetFunction) ( const char *path,
                                           const char *prop,
                                           GVariant *value,
                                           void *userdata);

typedef GVariant * (* CtSgwDBusPropGetFunction) ( const char    *path,
                                                  const char    *prop,
                                                  GVariant      *value,
                                                  void          *userdata);

typedef GVariant * (* CtSgwDBusPropGetAllFunction) ( const char *path,
                                                     GVariant   *value,
                                                     void       *userdata);

typedef int (* CtSgwDBusPropSetMultiFunction) ( const char    *path,
                                                GVariant      *value,
                                                void          *userdata);

typedef int (* CtSgwDBusMethodFunction) ( const char    *path,
                                          const char    *interface,
                                          const char    *method,
                                          GVariant      *inargs,
                                          GVariant     **outargs,
                                          void          *userdata);

typedef int (* CtSgwDBusSignalFunction) ( const char    *sender_name,
                                          const char    *path,
                                          const char    *interface,
                                          const char    *signal,
                                          GVariant      *args,
                                          void          *userdata);


/* DBus Service Context, used internal */
struct _CtSgwDbusServiceContext {
    gchar                service_name[CTC_DBUS_NAME_LEN];  // Key ID
    guint                bus_owner_id;          // The bus owner id, used when unown the name.
    GDBusConnection     *connection;            // DBus Connection
    GMainLoop           *loop;                  // The main loop reference.
    GMainContext        *context;               // The thread default context.
    GThread             *tid;                   // The main loop thread id.
    gboolean             is_service_started;    // Whether the dbus service is started.
    CtSgwAppMgtCallbacks_t *app_cbs;    
};

/* DBus signal subscribe/unsubscribe context, used internal */
struct _CtSgwDBusSignalSubstContext
{
    guint reg_id;
    char *sender_name;
    char *object_path;
    char *interface_name;
    char *signal_name;
    CtSgwDBusSignalFunction cb;
    void *user_data;
    struct _CtSgwDBusSignalSubstContext *next;
};

/************************* Function Declairation **************************/


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
int CtSgwDBusStartService ( const char *service_name );


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
int CtSgwDBusStopService(void);


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
CtSgwDBusNodeInfo_t *CtSgwDBusNodeParseXml (const unsigned char *xml_data);


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
CtSgwGDBusInterfaceInfo_t *CtSgwDBusNodeFindInterface(CtSgwDBusNodeInfo_t *node, const char *interface_name);


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
void CtSgwDBusNodeInfoUnref (CtSgwDBusNodeInfo_t *node_info);


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
                                     const CtSgwGDBusInterfaceVTable_t *vtable,
                                     void *user_data);


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
void CtSgwDBusUnRegisterObject(unsigned int id);


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
                         GVariant *value);


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
                              GVariant *values);


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
                         GVariant *value);


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
                            GVariant *values);


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
                        GVariant *inargs,
                        GVariant **outargs,
                        int timeout);


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
                        GVariant *args);


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
                                      void *user_data);


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
void CtSgwDBusUnSubscribeSignal(unsigned int id);


#endif

