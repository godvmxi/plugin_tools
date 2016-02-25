#include "capi-dbus-service.h"
#include "capi-sys-service.h"

/*
 * Function Name: CtSgwGetDeviceInfo
 *
 * Description: Get device information
 *
 * Parameter:
 *             info <OUT>:   A CtSgwDeviceInfo_t to contain the device information
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int
CtSgwGetDeviceInfo (CtSgwDeviceInfo_t *info)
{
    GVariant *dict = NULL;
    GVariant *value;
    GVariantIter iter;
    gchar   *key;
    gboolean bol_val;
    gchar   *str_val = NULL;
    guchar   byt_val = 0;
    guint32  int_val = 0;
    int ret = -1;

    g_return_val_if_fail ((info != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/info/Device",
                                   "com.ctc.igd1.DeviceInfo",
                                   &dict);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "path") == 0)
        {
            g_variant_get (value, FORMAT_PATH, &str_val);
            g_stpcpy (info->path.str, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "BusinessStatus") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            info->BusinessStatus = byt_val;
        }
        else if (g_strcmp0 (key, "MAC") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->MAC, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "SWVersion") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->SWVersion, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "HDVersion") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->HDVersion, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "ProductClass") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->ProductClass, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "CPUClass") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->CPUClass, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "DevType") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->DevType, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "DevType1") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->DevType1, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Capability") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->Capability, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "FlashSize") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->FlashSize = int_val;
        }
        else if (g_strcmp0 (key, "RamSize") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->RamSize = int_val;
        }
        else if (g_strcmp0 (key, "DevName") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->DevName, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "NFC") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            info->NFC = byt_val;
        }
        else if (g_strcmp0 (key, "LED") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            info->LED = byt_val;
        }
        else if (g_strcmp0 (key, "CPUUsage") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            info->CPUUsage = byt_val;
        }
        else if (g_strcmp0 (key, "MEMUsage") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            info->MEMUsage = byt_val;
        }
        else if (g_strcmp0 (key, "FlashUsage") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            info->FlashUsage = byt_val;
        }
        else if (g_strcmp0 (key, "SysDuration") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->SysDuration = int_val;
        }
        else if (g_strcmp0 (key, "Card") == 0)
        {
            g_variant_get (value, FORMAT_BOOL, &bol_val);
            info->Card = bol_val;
        }
        else if (g_strcmp0 (key, "Cardno") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->Cardno, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "CardStatus") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            info->CardStatus = byt_val;
        }
        else if (g_strcmp0 (key, "RegisterStatus") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->RegisterStatus, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "RegisterResult") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->RegisterResult, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "RegisterProgressResult") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->RegisterProgressResult, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "RegisterBussNameResult") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->RegisterBussNameResult, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "RegisterServiceResult") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->RegisterServiceResult, str_val);
            g_free (str_val);
        }
        else
        {
            g_print ("Something wrong!\n");
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;

}

/*
 * Function Name: CtSgwGetNetworkInfo
 *
 * Description: Get network information
 *
 * Parameter:
 *             info <OUT>:   A CtSgwNetworkInfo_t to contain the device information
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int
CtSgwGetNetworkInfo(CtSgwNetworkInfo_t *info)
{
    GVariant *dict = NULL;
    GVariant *value = NULL;
    GVariantIter iter;
    gchar   *key;
    gchar   *str_val = NULL;
    guchar   byt_val = 0;
    guint32  int_val = 0;
    int ret = -1;

    g_return_val_if_fail ((info != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/info/Network",
                                   "com.ctc.igd1.NetworkInfo",
                                   &dict);
    
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);

    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "path") == 0)
        {
            g_variant_get (value, FORMAT_PATH, &str_val);
            g_stpcpy (info->path.str, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "UPLink") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->UPLink = int_val;
        }
        else if (g_strcmp0 (key, "IPV6") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            info->IPV6 = byt_val;
        }
        else if (g_strcmp0 (key, "VLANbind") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            info->VLANbind = byt_val;
        }
        else if (g_strcmp0 (key, "WiFiMode") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->WiFiMode, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "PONDuration") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->PONDuration = int_val;
        }
        else if (g_strcmp0 (key, "PPPOEDuration") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->PPPOEDuration = int_val;
        }
        else if (g_strcmp0 (key, "LAN1Status") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            info->LAN1Status = byt_val;
        }
        else if (g_strcmp0 (key, "LAN2Status") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            info->LAN2Status = byt_val;
        }
        else if (g_strcmp0 (key, "LAN3Status") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            info->LAN3Status = byt_val;
        }
        else if (g_strcmp0 (key, "LAN4Status") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            info->LAN4Status = byt_val;
        }
        else if (g_strcmp0 (key, "WANLinkStatus") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->WANLinkStatus, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "WIFIModuleStatus") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->WIFIModuleStatus, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "WANConnectionStatus") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->WANConnectionStatus, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "PPPoEDialReason") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->PPPoEDialReason, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "IPV6_WANConnectionStatus") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->IPV6_WANConnectionStatus, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "IPV6_PPPoEDialReason") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->IPV6_PPPoEDialReason, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "LANIPAddr") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->LANIPAddr, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "WANIPAddr") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->WANIPAddr, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "WANIPV6Addr") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->WANIPV6Addr, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "WiFiRate") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->WiFiRate = int_val;
        }
        else if (g_strcmp0 (key, "WiFiUSRate") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->WiFiUSRate = int_val;
        }
        else if (g_strcmp0 (key, "WiFiDSRate") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->WiFiDSRate = int_val;
        }
        else if (g_strcmp0 (key, "WANRate") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->WANRate = int_val;
        }
        else if (g_strcmp0 (key, "WANUSRate") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->WANUSRate = int_val;
        }
        else if (g_strcmp0 (key, "WANDSRate") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->WANDSRate = int_val;
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return ret;
}

/*
 * Function Name: CtSgwGeWANConnectionObjs
 *
 * Description  : Return all WAN connection
 *
 * Parameter:
 *             objs <OUT>:   A CtSgwWANConnectionInfo_t array to contain all
 *                           the wan information, the memory is allocated in
 *                           the function, but need to be freed by the caller.
 *
 *            count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int
CtSgwGeWANConnectionObjs(CtSgwWANConnectionInfo_t **objs, guint32 *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *path = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    guint64          u64_val = 0;
    CtSgwWANConnectionInfo_t  *entryList = NULL;
    CtSgwWANConnectionInfo_t  *pEntry = NULL;

    g_return_val_if_fail ((count != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Info/Network/WANConnectionDb",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
    {
        g_variant_unref (result);
        return CTSGW_OK;
    }
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgwWANConnectionInfo_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &path, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, path);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "Index") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Index, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IfName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IfName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ServiceList") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->ServiceList, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ConnectionType") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->ConnectionType, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "VLANID") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->VLANID = u32_val;
                }
                else if (g_strcmp0 (key, "VLAN8021P") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->VLAN8021P = u32_val;
                }
                else if (g_strcmp0 (key, "Protocol") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Protocol, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ConnectionStatus") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->ConnectionStatus, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPAddress") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IPAddress, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "SubnetMask") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->SubnetMask, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Gateway") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Gateway, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DNS1") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DNS1, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DNS2") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DNS2, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_ConnectionStatus") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IPV6_ConnectionStatus, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_IPAddress") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IPV6_IPAddress, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_PrefixLength") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IPV6_PrefixLength, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_Gateway") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IPV6_Gateway, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_DNS1") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IPV6_DNS1, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_DNS1") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IPV6_DNS1, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_DNS2") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IPV6_DNS2, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_Prefix") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IPV6_Prefix, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "RxBytes") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT64, &u64_val);
                    pEntry->RxBytes = u64_val;
                }
                else if (g_strcmp0 (key, "TxBytes") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT64, &u64_val);
                    pEntry->TxBytes = u64_val;
                }
                else if (g_strcmp0 (key, "RxPkts") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT64, &u64_val);
                    pEntry->RxPkts = u64_val;
                }
                else if (g_strcmp0 (key, "TxPkts") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT64, &u64_val);
                    pEntry->TxPkts = u64_val;
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (path);
        g_variant_unref (interfaceDict);

        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;
}

/*
 * Function Name: CtSgwGetWANConnection
 *
 * Description  : Return a specific WAN connection according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific wan.
 *             obj <OUT>:   A CtSgwWANConnectionInfo_t struct to contain the wan information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int
CtSgwGetWANConnection(CtSgwObjPath_t path, CtSgwWANConnectionInfo_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    guint64          u64_val = 0;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Info/Network/WANConnectionDb",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);


    ret = CTSGW_NOK;
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
        
        g_stpcpy (obj->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "Index") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->Index, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IfName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->IfName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ServiceList") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->ServiceList, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ConnectionType") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->ConnectionType, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "VLANID") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    obj->VLANID = u32_val;
                }
                else if (g_strcmp0 (key, "VLAN8021P") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    obj->VLAN8021P = u32_val;
                }
                else if (g_strcmp0 (key, "Protocol") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->Protocol, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ConnectionStatus") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->ConnectionStatus, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPAddress") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->IPAddress, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "SubnetMask") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->SubnetMask, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Gateway") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->Gateway, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DNS1") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->DNS1, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DNS2") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->DNS2, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_ConnectionStatus") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->IPV6_ConnectionStatus, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_IPAddress") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->IPV6_IPAddress, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_PrefixLength") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->IPV6_PrefixLength, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_Gateway") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->IPV6_Gateway, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_DNS1") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->IPV6_DNS1, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_DNS1") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->IPV6_DNS1, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_DNS2") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->IPV6_DNS2, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IPV6_Prefix") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->IPV6_Prefix, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "RxBytes") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT64, &u64_val);
                    obj->RxBytes = u64_val;
                }
                else if (g_strcmp0 (key, "TxBytes") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT64, &u64_val);
                    obj->TxBytes = u64_val;
                }
                else if (g_strcmp0 (key, "RxPkts") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT64, &u64_val);
                    obj->RxPkts = u64_val;
                }
                else if (g_strcmp0 (key, "TxPkts") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT64, &u64_val);
                    obj->TxPkts = u64_val;
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return ret;
}

/*
 * Function Name: CtSgwGetWANConnection
 *
 * Description  : Get wan connection according to the wan name
 *
 * Parameter:
 *             name <IN>:   The wan connection name.
 *             obj <OUT>:   A CtSgwWANConnectionInfo_t struct to contain the wan information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int
CtSgwGetWANConnectionByName(const char *name, CtSgwWANConnectionInfo_t *obj)
{
    gint32 ret = -1;
    GVariant  *result = NULL;
    gchar     *path = NULL;
    CtSgwObjPath_t pathObj;

    if ( IS_EMPTY_STRING(name) )
    {
        return CTSGW_NOK;
    }
    
    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Info/Network/WANConnectionDb",
                               "com.ctc.igd1.WANConnectionDb",
                               "GetWANConnByName",
                               g_variant_new("(s)", name),
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    if (result != NULL)
    {
        g_variant_get (result, "(o)", &path, NULL);

        memset (&pathObj, '\0', sizeof(CtSgwObjPath_t));
        g_stpcpy (pathObj.str, path); 
        CtSgwGetWANConnection( pathObj, obj);
        g_free (path);
        g_variant_unref (result);
    }

    return CTSGW_OK;
}

/*
 * Function Name: CtSgwGetWANConnection
 *
 * Description  : Get the connected wan connection infromation
 *
 * Parameter:
 *             obj <OUT>:   A CtSgwWANConnectionInfo_t struct to contain the wan information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int
CtSgwGetInternetWANConnection(CtSgwWANConnectionInfo_t *obj)
{
    CtSgwWANConnectionInfo_t  *connObj = NULL;
    CtSgwWANConnectionInfo_t  *pConn = NULL;
    guint32 count = 0;
    gint32 ret = CTSGW_NOK;
    gint32 i = 0;
    // TODO: may be get wan connection according to the path.

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwGeWANConnectionObjs( &connObj, &count);

    g_return_val_if_fail ((ret == CTSGW_OK), ret);
    g_return_val_if_fail ((count > 0), CTSGW_NOK);

    pConn = connObj;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 (pConn->ConnectionStatus, "Connected") != 0)
        {
            ++pConn;
            continue;
        }

        memmove (obj, pConn, sizeof (CtSgwWANConnectionInfo_t));
        break;
    }

    if ( i >= count )
        ret = CTSGW_NOK;

    g_free (connObj);

    return ret;
}

/*
 * Function Name: CtSgwGetWiFiInfo
 *
 * Description  : Get the WiFi infromation
 *
 * Parameter:
 *     info <OUT>:   A CtSgwWiFiInfo_t struct to contain the WiFi information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */

int
CtSgwGetWiFiInfo(CtSgwWiFiInfo_t *info)
{
    GVariant *dict = NULL;
    GVariant *value = NULL;
    GVariantIter iter;
    gchar   *key;
    gboolean bol_val;
    gchar   *str_val = NULL;
    guint32  int_val = 0;
    guint64  i64_val = 0;
    int ret = -1;

    g_return_val_if_fail ((info != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Info/WiFi",
                                   "com.ctc.igd1.WiFiInfo",
                                   &dict);
    
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);

    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "path") == 0)
        {
            g_variant_get (value, FORMAT_PATH, &str_val);
            g_stpcpy (info->path.str, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "SSID") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->SSID, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Enable") == 0)
        {
            g_variant_get (value, FORMAT_BOOL, &bol_val);
            info->Enable = bol_val;
        }
        else if (g_strcmp0 (key, "Channel") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->Channel = int_val;
        }
        else if (g_strcmp0 (key, "PowerLevel") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->PowerLevel = int_val;
        }
        else if (g_strcmp0 (key, "PowerLevel_5G") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->PowerLevel_5G = int_val;
        }
        else if (g_strcmp0 (key, "PWD") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->PWD, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Encrypt") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            info->Encrypt = int_val;
        }
        else if (g_strcmp0 (key, "RxBytes") == 0)
        {
            g_variant_get (value, FORMAT_UINT64, &i64_val);
            info->Encrypt = i64_val;
        }
        else if (g_strcmp0 (key, "RxPkts") == 0)
        {
            g_variant_get (value, FORMAT_UINT64, &i64_val);
            info->RxPkts = i64_val;
        }
        else if (g_strcmp0 (key, "RxErrorPkts") == 0)
        {
            g_variant_get (value, FORMAT_UINT64, &i64_val);
            info->RxErrorPkts = i64_val;
        }
        else if (g_strcmp0 (key, "RxDropPkts") == 0)
        {
            g_variant_get (value, FORMAT_UINT64, &i64_val);
            info->RxDropPkts = i64_val;
        }
        else if (g_strcmp0 (key, "TxBytes") == 0)
        {
            g_variant_get (value, FORMAT_UINT64, &i64_val);
            info->TxBytes = i64_val;
        }
        else if (g_strcmp0 (key, "TxPkts") == 0)
        {
            g_variant_get (value, FORMAT_UINT64, &i64_val);
            info->TxPkts = i64_val;
        }
        else if (g_strcmp0 (key, "TxErrorPkts") == 0)
        {
            g_variant_get (value, FORMAT_UINT64, &i64_val);
            info->TxErrorPkts = i64_val;
        }
        else if (g_strcmp0 (key, "TxDropPkts") == 0)
        {
            g_variant_get (value, FORMAT_UINT64, &i64_val);
            info->TxDropPkts = i64_val;
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;
}

/*
 * Function Name: CtSgwGetPONInfo
 *
 * Description  : Get the PON infromation
 *
 * Parameter:
 *     info <OUT>:   A CtSgwPONInfo_t struct to contain the PON information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int
CtSgwGetPONInfo(CtSgwPONInfo_t *info)
{
    GVariant *dict = NULL;
    GVariant *value = NULL;
    GVariantIter iter;
    gchar   *key;
    gboolean bol_val;
    gchar   *str_val = NULL;
    gdouble  dbl_val = 0;
    int ret = -1;

    g_return_val_if_fail ((info != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Info/PON",
                                   "com.ctc.igd1.PONInfo",
                                   &dict);
    
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);

    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "path") == 0)
        {
            g_variant_get (value, FORMAT_PATH, &str_val);
            g_stpcpy (info->path.str, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "LOID") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->LOID, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Password") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->Password, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Temperature") == 0)
        {
            g_variant_get (value, FORMAT_DOUBLE, &dbl_val);
            info->Temperature = dbl_val;
        }
        else if (g_strcmp0 (key, "Vottage") == 0)
        {
            g_variant_get (value, FORMAT_DOUBLE, &dbl_val);
            info->Vottage = dbl_val;
        }
        else if (g_strcmp0 (key, "Current") == 0)
        {
            g_variant_get (value, FORMAT_DOUBLE, &dbl_val);
            info->Current = dbl_val;
        }
        else if (g_strcmp0 (key, "TxPower") == 0)
        {
            g_variant_get (value, FORMAT_DOUBLE, &dbl_val);
            info->TxPower = dbl_val;
        }
        else if (g_strcmp0 (key, "RxPower") == 0)
        {
            g_variant_get (value, FORMAT_DOUBLE, &dbl_val);
            info->RxPower = dbl_val;
        }
        else if (g_strcmp0 (key, "SupportPONStatusQuery") == 0)
        {
            g_variant_get (value, FORMAT_BOOL, &bol_val);
            info->SupportPONStatusQuery = bol_val;
        }
        else if (g_strcmp0 (key, "PONStatus") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->PONStatus, str_val);
            g_free (str_val);
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;
}

/*
 * Function Name: CtSgwGetVoIPInfo
 *
 * Description  : Get the VoIP infromation
 *
 * Parameter:
 *     info <OUT>:   A CtSgwVoIPInfo_t struct to contain the VoIP information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetVoIPInfo(CtSgwVoIPInfo_t *info)
{
    GVariant *dict = NULL;
    GVariant *value = NULL;
    GVariantIter iter;
    gchar   *key;
    gchar   *str_val = NULL;
    int ret = -1;
    
    g_return_val_if_fail ((info != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Info/VoIP",
                                   "com.ctc.igd1.VoIPInfo",
                                   &dict);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "path") == 0)
        {
            g_variant_get (value, FORMAT_PATH, &str_val);
            g_stpcpy (info->path.str, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "VoIPName1") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->VoIPName1, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "VoIPName2") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->VoIPName2, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Line1Status") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->Line1Status, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Line2Status") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (info->Line2Status, str_val);
            g_free (str_val);
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;
}

/*
 * Function Name: CtSgwGetLANHostMgr
 *
 * Description  : Get the LAN Host Management configuration
 *
 * Parameter:
 *     info <OUT>:   A CtSgwLANHostMgr_t struct to contain the LAN Host Management information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetLANHostMgr(CtSgwLANHostMgr_t *obj)
{
    GVariant *dict = NULL;
    GVariant *value = NULL;
    GVariantIter iter;
    gchar   *key;
    gchar   *str_val = NULL;
    gboolean    bol_val;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Info/LANHosts",
                                   "com.ctc.igd1.LANHostManager",
                                   &dict);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "path") == 0)
        {
            g_variant_get (value, FORMAT_PATH, &str_val);
            g_stpcpy (obj->path.str, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "EnableStats") == 0)
        {
            g_variant_get(value, FORMAT_BOOL, &bol_val);
            obj->EnableStats = bol_val;
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;
}

/*
 * Function Name: CtSgwSetLANHostMgr
 *
 * Description  : Set the LAN Host Management configuration
 *
 * Parameter:
 *     obj  <IN>:   A CtSgwLANHostMgr_t struct containing the LAN Host Management Setting.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetLANHostMgr (CtSgwLANHostMgr_t *obj)
{
    GVariant *value = NULL;
    int ret = -1;

    g_return_val_if_fail (obj != NULL, CTSGW_NOK);
    value = g_variant_new_boolean (obj->EnableStats);
    
    ret = CtSgwDBusSetProperty ("com.ctc.igd1",
                                "/com/ctc/igd1/Info/LANHosts",
                                "com.ctc.igd1.LANHostManager",
                                "EnableStats",
                                value);

    g_variant_unref (value);
    
    return (ret == 0) ? CTSGW_OK : CTSGW_NOK ;
}

/*
 * Function Name: CtSgwGetLANHostObjs
 *
 * Description  : Return all LAN Client information
 *
 * Parameter:
 *             objs <OUT>:   A CtSgwLANHost_t array to contain all the
 *                           lan clients information, the memory is allocated in
 *                           this function, but need to be freed by the caller.
 *
 *            count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetLANHostObjs(CtSgwLANHost_t **objs, int *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *path = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    guchar           byt_val = 0;
    gboolean         bol_val = 0;
    CtSgwLANHost_t  *entryList = NULL;
    CtSgwLANHost_t  *pEntry = NULL;

    g_return_val_if_fail ((count != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Info/LANHosts",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgwLANHost_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &path, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, path);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "MAC") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->MAC, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DevName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DevName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DenyInternetAccess") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->DenyInternetAccess = bol_val;
                }
                else if (g_strcmp0 (key, "DenyStorageAccess") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->DenyStorageAccess = bol_val;
                }
                else if (g_strcmp0 (key, "MaxUSBandwidth") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->MaxUSBandwidth = u32_val;
                }
                else if (g_strcmp0 (key, "MaxDSBandwidth") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->MaxDSBandwidth = u32_val;
                }
                else if (g_strcmp0 (key, "USBandwidth") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->USBandwidth = u32_val;
                }
                else if (g_strcmp0 (key, "DSBandwidth") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->DSBandwidth = u32_val;
                }
                else if (g_strcmp0 (key, "DevType") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DevType, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IP") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IP, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ConnectionType") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BYTE, &byt_val);
                    pEntry->ConnectionType = byt_val;
                }
                else if (g_strcmp0 (key, "Port") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BYTE, &byt_val);
                    pEntry->Port = byt_val;
                }
                else if (g_strcmp0 (key, "Brand") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Brand, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "OS") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->OS, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "OnlineTime") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->OnlineTime = u32_val;
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (path);
        g_variant_unref (interfaceDict);

        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;
}

/*
 * Function Name: CtSgwGetWANConnection
 *
 * Description  : Return a specific LAN hosts according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific lan host.
 *             obj <OUT>:   A CtSgwLANHost_t struct to contain the lan device information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetLANHost(CtSgwObjPath_t path, CtSgwLANHost_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    guchar           byt_val = 0;
    gboolean         bol_val = 0;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Info/LANHosts",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);

    ret = CTSGW_NOK;
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
    
        g_stpcpy (obj->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "MAC") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->MAC, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DevName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->DevName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DenyInternetAccess") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    obj->DenyInternetAccess = bol_val;
                }
                else if (g_strcmp0 (key, "DenyStorageAccess") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    obj->DenyStorageAccess = bol_val;
                }
                else if (g_strcmp0 (key, "MaxUSBandwidth") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    obj->MaxUSBandwidth = u32_val;
                }
                else if (g_strcmp0 (key, "MaxDSBandwidth") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    obj->MaxDSBandwidth = u32_val;
                }
                else if (g_strcmp0 (key, "USBandwidth") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    obj->USBandwidth = u32_val;
                }
                else if (g_strcmp0 (key, "DSBandwidth") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    obj->DSBandwidth = u32_val;
                }
                else if (g_strcmp0 (key, "DevType") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->DevType, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "IP") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->IP, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ConnectionType") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BYTE, &byt_val);
                    obj->ConnectionType = byt_val;
                }
                else if (g_strcmp0 (key, "Port") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BYTE, &byt_val);
                    obj->Port = byt_val;
                }
                else if (g_strcmp0 (key, "Brand") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->Brand, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "OS") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (obj->OS, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "OnlineTime") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    obj->OnlineTime = u32_val;
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return ret;
}

/*
 * Function Name: CtSgwSetLANHost
 *
 * Description  : Set a specific LAN hosts configuration according to the object path
 *
 * Parameter:
 *             obj <OUT>:   A CtSgwLANHost_t struct to contain the lan host information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetLANHost(CtSgwLANHost_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "DevName",
                           g_variant_new_string (obj->DevName));
    
    g_variant_builder_add (builder,
                           "{sv}",
                           "DenyInternetAccess",
                           g_variant_new_boolean (obj->DenyInternetAccess));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DenyStorageAccess",
                           g_variant_new_boolean (obj->DenyStorageAccess));

    g_variant_builder_add (builder,
                           "{sv}",
                           "MaxUSBandwidth",
                           g_variant_new_uint32 (obj->MaxUSBandwidth));

    g_variant_builder_add (builder,
                           "{sv}",
                           "MaxDSBandwidth",
                           g_variant_new_uint32 (obj->MaxDSBandwidth));

    g_variant_builder_add (builder,
                           "{sv}",
                           "USBandwidth",
                           g_variant_new_uint32 (obj->USBandwidth));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DSBandwidth",
                           g_variant_new_uint32 (obj->DSBandwidth));
    
    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     obj->path.str,
                                     "com.ctc.igd1.LANHost",
                                     value);
    g_variant_unref (value);

    return (ret == 0) ? CTSGW_OK : CTSGW_NOK ;
}

/*
 * Function Name: CtSgwSetHttpDownloadTestURL
 *
 * Description  : Set the url address for http download testing
 *
 * Parameter:
 *      url <IN>: The url address
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetHttpDownloadTestURL(const char url[MAX_URL_LEN+1])
{
    GVariant *value = NULL;
    int ret = -1;

    g_return_val_if_fail( !IS_EMPTY_STRING(url), CTSGW_NOK );
    value = g_variant_new (FORMAT_STRING, url);
    
    ret = CtSgwDBusSetProperty ("com.ctc.igd1",
                                "/com/ctc/igd1/Diagnostics/HttpDownload",
                                "com.ctc.igd1.HttpDownloadTest",
                                "URL",
                                value);

    return (ret == 0) ? CTSGW_OK : CTSGW_NOK ;


}


/*
 * Function Name: CtSgwGetHttpDownloadTestURL
 *
 * Description  : Get the url address for http download testing
 *
 * Parameter:
 *      url <OUT>: The url address
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetHttpDownloadTestURL(char url[MAX_URL_LEN+1])
{
    GVariant *value = NULL;
    gchar   *key;
    int ret = -1;

    g_return_val_if_fail( !IS_EMPTY_STRING(url), CTSGW_NOK );
    ret = CtSgwDBusGetProperty ("com.ctc.igd1",
                                "/com/ctc/igd1/Diagnostics/HttpDownload",
                                "com.ctc.igd1.HttpDownloadTest",
                                "URL",
                                &value);
    if (ret < 0)
        return CTSGW_NOK;

    g_variant_get(value, FORMAT_STRING, &key);
    g_stpcpy (url, key);
    g_variant_unref (value);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwStartHttpDownloadTest
 *
 * Description  : Execute the download load testing
 *
 * Parameter:
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwStartHttpDownloadTest(void)
{
    gint32 ret = -1;

    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Diagnostics/HttpDownload",
                               "com.ctc.igd1.HttpDownloadTest",
                               "StartTest",
                               g_variant_new(FORMAT_UINT32, 120), 
                               NULL,
                               -1);

    return (ret == 0) ? CTSGW_OK : CTSGW_NOK ;
}


/*
 * Function Name: CtSgwGetHttpDownloadTestResult
 *
 * Description  : Get the http download load testing result
 *
 * Parameter:
 *      result <OUT>:   a struct to hold http download testing result
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetHttpDownloadTestResult(CtSgwHttpDownloadTestResult_t *result)
{
    GVariant *dict = NULL;
    GVariant *value = NULL;
    GVariantIter iter;
    gchar   *key;
    gchar   *str_val = NULL;
    guint32  int_val = 0;
    int ret = -1;

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                    "/com/ctc/igd1/Diagnostics/HttpDownload",
                                    "com.ctc.igd1.HttpDownloadTest",
                                    &dict);
    if (ret < 0)
    {
        memset (result, '\0', sizeof(CtSgwHttpDownloadTestResult_t));
        return CTSGW_NOK;
    }
    
    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "path") == 0)
        {
            g_variant_get (value, FORMAT_PATH, &str_val);
            g_stpcpy (result->path.str, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Status") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            result->Status = int_val;
        }
        else if (g_strcmp0 (key, "Result") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (result->Result, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "URL") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (result->URL, str_val);
            g_free (str_val);
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwStartPingTest
 *
 * Description  : Execute the ping testing
 *
 * Parameter:
 *   wanconn <IN>:  The WANConnection object path, use this wan to execute the testing
 *      dest <IN>:  The destination address of the wan ping testing
 *       len <IN>:  The package length
 *      time <IN>:  The package count.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwStartPingTest(CtSgwObjPath_t *wanconn, const gchar *dest, guint32 len, guint32 time)
{
    gint32 ret = -1;
    GVariant *result = NULL;
    guint32   res = 0;
    gchar    *err;

    g_return_val_if_fail (!(IS_EMPTY_STRING(wanconn->str)), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Diagnostics/Ping",
                               "com.ctc.igd1.PingTest",
                               "StartTest",
                               g_variant_new("(osuu)", wanconn->str, dest, len, time), 
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    if (result != NULL)
    {
        g_variant_get (result, "(u&s)", &res, &err);
        if (!IS_EMPTY_STRING(err))
        {
            g_print ("%s: %s\n", __FUNCTION__, err);
        }

        g_variant_unref (result);
    }
    
    return res;
}


/*
 * Function Name: CtSgwGetPingTestResult
 *
 * Description  : Get the ping testing result
 *
 * Parameter:
 *      result <OUT>:   a struct to hold ping testing result
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetPingTestResult(CtSgwPingTestResult_t *result)
{
    GVariant *value = NULL;
    GVariantIter iter;
    GVariant *dict = NULL;
    gchar   *key;
    gchar   *str_val = NULL;
    int ret = -1;

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Diagnostics/Ping",
                                   "com.ctc.igd1.PingTest",
                                   &dict);
    g_return_val_if_fail((ret == 0), CTSGW_NOK);
    
    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "path") == 0)
        {
            g_variant_get (value, FORMAT_PATH, &str_val);
            g_stpcpy (result->path.str, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "PingStatus") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (result->PingStatus, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "PingResult") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (result->PingResult, str_val);
            g_free (str_val);
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;
}

/*
 * Function Name: CtSgwStartTraceRouteTest
 *
 * Description  : Start the trace route testing
 *
 * Parameter:
 *   wanconn <IN>:  The WANConnection object path, use this wan to execute the testing
 *      dest <IN>:  The destination address of this test.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwStartTraceRouteTest(CtSgwObjPath_t *wanconn, char *dest)
{
    gint32 ret = -1;
    GVariant *result = NULL;
    guint32   res = 0;
    gchar    *err;

    g_return_val_if_fail (!IS_EMPTY_STRING(wanconn->str), CTSGW_NOK);
    g_return_val_if_fail (!IS_EMPTY_STRING(dest), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Diagnostics/TraceRoute",
                               "com.ctc.igd1.TraceRouteTest",
                               "StartTest",
                               g_variant_new("(os)", wanconn->str, dest), 
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    g_variant_get (result, "(u&s)", &res, &err);
    if (!IS_EMPTY_STRING(err))
    {
        g_print ("%s: %s\n", __FUNCTION__, err);
    }

    g_variant_unref (result);
    
    return CTSGW_OK;
}


/*
 * Function Name: CtSgwGetTraceRouteTestResult
 *
 * Description  : Get the trace route testing result
 *
 * Parameter:
 *      result <OUT>:   a struct to hold the trace route testing result
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetTraceRouteTestResult(CtSgwTraceRouteTestResult_t *result)
{
    GVariant *value = NULL;
    GVariantIter iter;
    GVariant *dict = NULL;
    gchar   *key;
    gchar   *str_val = NULL;
    int ret = -1;

    g_return_val_if_fail((result != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Diagnostics/TraceRoute",
                                   "com.ctc.igd1.TraceRouteTest",
                                   &dict);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    
    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "path") == 0)
        {
            g_variant_get (value, FORMAT_PATH, &str_val);
            g_stpcpy (result->path.str, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "TraceStatus") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (result->TraceStatus, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "TraceResult") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (result->TraceResult, str_val);
            g_free (str_val);
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwStartInformTest
 *
 * Description  : Start the inform testing
 *
 * Parameter:
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwStartInformTest(void)
{
    gint32 ret = -1;

    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Diagnostics/InformTest",
                               "com.ctc.igd1.InformTest",
                               "StartTest",
                               NULL, 
                               NULL,
                               -1);
    
    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwGetInformTestResult
 *
 * Description  : Get the inform testing result
 *
 * Parameter:
 *      result <OUT>:   a struct to hold inform testing result
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetInformTestResult(CtSgwInformTestResult_t *result)
{
    gint32 ret = -1;
    GVariant *testResult = NULL;
    guint32 testRes;

    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Diagnostics/InformTest",
                               "com.ctc.igd1.InformTest",
                               "StartTest",
                               NULL, 
                               &testResult,
                               -1);
    if (testResult != NULL)
    {
        g_variant_get (testResult, FORMAT_UINT32, &testRes);
        result->result = testRes;

        g_variant_unref (testResult);
    }
    
    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwStartInformTest
 *
 * Description  : Start the Multicast testing
 *
 * Parameter:
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int
CtSgwStartMCTest(void)
{
    gint32 ret = -1;
    GVariant *result = NULL;
    guint32   res = 0;
    gchar    *err;

    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Diagnostics/MulticastTest",
                               "com.ctc.igd1.MulticastTest",
                               "StartTest",
                               NULL, 
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    g_variant_get (result, "(u&s)", &res, &err);
    if (!IS_EMPTY_STRING(err))
    {
        g_print ("%s: %s\n", __FUNCTION__, err);
    }

    g_variant_unref (result);
    
    return res;
}


/*
 * Function Name: CtSgwGetMCestResult
 *
 * Description  : Get the inform testing result
 *
 * Parameter:
 *      result <OUT>:   a struct to hold multicast testing result
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int
CtSgwGetMCTestResult(CtSgwMCTestResult_t *result)
{
    GVariant *value = NULL;
    GVariantIter iter;
    GVariant *dict = NULL;
    gchar   *key;
    gchar   *str_val = NULL;
    guint32  int_val = 0;
    int ret = -1;
    
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Diagnostics/MulticastTest",
                                   "com.ctc.igd1.MulticastTest",
                                   &dict);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);

    
    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "path") == 0)
        {
            g_variant_get (value, FORMAT_PATH, &str_val);
            g_stpcpy (result->path.str, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "DialStatus") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            result->DialStatus = int_val;
        }
        else if (g_strcmp0 (key, "DialResult") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (result->DialResult, str_val);
            g_free (str_val);
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwSetPW
 *
 * Description  : Set the push web configuration
 *
 * Parameter:
 *      obj <IN>: Contain the push web configuration
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetPW (CtSgwPWConfig_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;
    
    g_return_val_if_fail ((obj!= NULL), CTSGW_NOK);
    g_return_val_if_fail(((obj->Status >= 0) && (obj->Status <= 3)), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_boolean (obj->Enable));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Width",
                           g_variant_new_uint32 (obj->Width));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Height",
                           g_variant_new_uint32 (obj->Height));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Place",
                           g_variant_new_string (obj->Place));

    g_variant_builder_add (builder,
                           "{sv}",
                           "URL",
                           g_variant_new_string (obj->URL));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Time",
                           g_variant_new_string (obj->Time));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     "/com/ctc/igd1/Config/TE/PushWeb",
                                     "com.ctc.igd1.PushWeb",
                                     value);

    g_variant_unref (value);
    
    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwGetPW
 *
 * Description  : Get the push web configuration
 *
 * Parameter:
 *     obj <OUT>: Contain the push web configuration
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetPW (CtSgwPWConfig_t *obj)
{
    GVariantIter iter;
    GVariant *dict = NULL;
    gchar   *key;
    GVariant *value = NULL;
    gboolean bol_val = 0;
    guint32  int_val = 0;
    guchar   byt_val = 0;
    gchar   *str_val = NULL;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Config/TE/PushWeb",
                                   "com.ctc.igd1.PushWeb",
                                   &dict);
    g_return_val_if_fail( (ret == 0), CTSGW_NOK );
    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "Enable") == 0)
        {
            g_variant_get (value, FORMAT_BOOL, &bol_val);
            obj->Enable = bol_val;
        }
        else if (g_strcmp0 (key, "Width") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            obj->Width = int_val;
        }
        else if (g_strcmp0 (key, "Height") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            obj->Height = int_val;
        }
        else if (g_strcmp0 (key, "Place") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (obj->Place, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "URL") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (obj->URL, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Time") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (obj->Time, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Status") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            obj->Status = byt_val;
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return ret;
}


/*
 * Function Name: CtSgwSet404Redir
 *
 * Description  : Set the 404 Redirect configuration
 *
 * Parameter:
 *      obj <IN>: Contain the redirect configuration
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSet404Redir (CtSgw404Redir_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_string (obj->DownURL));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     "/com/ctc/igd1/Config/TE/Redirect404",
                                     "com.ctc.igd1.Redirect404",
                                     value);

    g_variant_unref (value);

    return ((ret == 0)? CTSGW_OK : CTSGW_NOK); 
}

/*
 * Function Name: CtSgwGet404Redir
 *
 * Description  : Get the 404 redirect configuration
 *
 * Parameter:
 *     obj <OUT>: Contain the 404 redirect configuration
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGet404Redir(CtSgw404Redir_t *obj)
{
    GVariantIter iter;
    GVariant *dict = NULL;
    gchar   *key;
    GVariant *value = NULL;
    gchar   *str_val = NULL;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Config/TE/Redirect404",
                                   "com.ctc.igd1.Redirect404",
                                   &dict);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);

    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "DownURL") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (obj->DownURL, str_val);
            g_free (str_val);
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return ret;
}

/*
 * Function Name: CtSgwSetWPS
 *
 * Description  : Set the WPS configuration
 *
 * Parameter:
 *      obj <IN>: Contain the WPS configuration
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetWPS(CtSgwWPS_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_boolean (obj->Enable));

    g_variant_builder_add (builder,
                           "{sv}",
                           "SSID",
                           g_variant_new_string (obj->SSID));

    g_variant_builder_add (builder,
                           "{sv}",
                           "TimeOut",
                           g_variant_new_uint32 (obj->TimeOut));
    
    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     "/com/ctc/igd1/Config/WLAN/WPS",
                                     "com.ctc.igd1.WPS",
                                     value);

    g_variant_unref (value);

    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwGetWPS
 *
 * Description  : Get the WPS configuration
 *
 * Parameter:
 *     obj <OUT>: Contain the WPS configuration
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetWPS(CtSgwWPS_t *obj)
{
    GVariantIter iter;
    GVariant *dict = NULL;
    gchar   *key;
    GVariant *value = NULL;
    gboolean     bol_val;
    gchar       *str_val = NULL;
    guint32      int_val;
    guchar       byt_val;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Config/WLAN/WPS",
                                   "com.ctc.igd1.WPS",
                                   &dict);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);

    
    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "Enable") == 0)
        {
            g_variant_get (value, FORMAT_BOOL, &bol_val);
            obj->Enable = bol_val;
        }
        else if (g_strcmp0 (key, "SSID") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (obj->SSID, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "TimeOut") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            obj->TimeOut = int_val;
        }
        else if (g_strcmp0 (key, "WPSStatus") == 0)
        {
            g_variant_get (value, FORMAT_BYTE, &byt_val);
            obj->WPSStatus = byt_val;
        }
        else if (g_strcmp0 (key, "DevInfo") == 0)
        {
            GVariantIter *iterSub;
            gchar   *str;
            gint32   i = 0;

            g_variant_get (value,  "as", &iterSub);
            while (g_variant_iter_loop(iterSub, "s", &str))
            {
                g_stpcpy (obj->DevInfo[i].Info, str);
                ++i;
            }
            g_variant_iter_free (iterSub);
        }


        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return ret;
}


/*
 * Function Name: CtSgwGetWLANDeviceObjs
 *
 * Description  : Return all WLAN setting information
 *
 * Parameter:
 *             objs <OUT>:   A CtSgwWLANDevice_t array to contain all the
 *                           wlan configure information, the memory is allocated in
 *                           this function, but need to be freed by the caller.
 *
 *            count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetWLANDeviceObjs(CtSgwWLANDevice_t **objs, guint32 *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    gboolean         bol_val = 0;
    CtSgwWLANDevice_t  *entryList = NULL;
    CtSgwWLANDevice_t  *pEntry = NULL;

    g_return_val_if_fail ((count != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/WLAN/Devices",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgwWLANDevice_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "SSID") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->SSID, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Enable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->Enable = bol_val;
                }
                else if (g_strcmp0 (key, "Channel") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->Channel = u32_val;
                }
                else if (g_strcmp0 (key, "ChannelInUse") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ChannelInUse = u32_val;
                }
                else if (g_strcmp0 (key, "BeaconType") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->BeaconType, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Standard") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Standard, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "WEPEncryptionLevel") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->WEPEncryptionLevel, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "BasicAuthenticationMode") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->BasicAuthenticationMode, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "WPAEncryptionModes") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->WPAEncryptionModes, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "SSIDHide") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->SSIDHide = bol_val;
                }
                else if (g_strcmp0 (key, "RFBand") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->RFBand = u32_val;
                }
                else if (g_strcmp0 (key, "ChannelWidth") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ChannelWidth = u32_val;
                }
                else if (g_strcmp0 (key, "GuardInterval") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->GuardInterval = u32_val;
                }
                else if (g_strcmp0 (key, "RetryTimeout") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->RetryTimeout = u32_val;
                }
                else if (g_strcmp0 (key, "Powerlevel") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->Powerlevel = u32_val;
                }
                else if (g_strcmp0 (key, "PowerLevel_5G") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->PowerLevel_5G = u32_val;
                }
                else if (g_strcmp0 (key, "PowerValue") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->PowerValue = u32_val;
                }
                else if (g_strcmp0 (key, "APModuleEnable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->APModuleEnable = bol_val;
                }
                else if (g_strcmp0 (key, "WPSKeyWord") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->WPSKeyWord = u32_val;
                }
                else if (g_strcmp0 (key, "PWD") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->PWD, str_val);
                    g_free (str_val);
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwGetWLANDevice
 *
 * Description  : Return a specific wlan configuration according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific wlan.
 *             obj <OUT>:   A CtSgwWLANDevice_t struct to contain the wlan information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetWLANDevice(CtSgwObjPath_t path,  CtSgwWLANDevice_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    gboolean         bol_val = 0;
    CtSgwWLANDevice_t  *pEntry = obj;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/WLAN/Devices",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);

    ret = CTSGW_NOK;
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
    
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "SSID") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->SSID, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Enable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->Enable = bol_val;
                }
                else if (g_strcmp0 (key, "Channel") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->Channel = u32_val;
                }
                else if (g_strcmp0 (key, "ChannelInUse") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ChannelInUse = u32_val;
                }
                else if (g_strcmp0 (key, "BeaconType") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->BeaconType, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Standard") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Standard, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "WEPEncryptionLevel") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->WEPEncryptionLevel, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "BasicAuthenticationMode") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->BasicAuthenticationMode, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "WPAEncryptionModes") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->WPAEncryptionModes, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "SSIDHide") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->SSIDHide = bol_val;
                }
                else if (g_strcmp0 (key, "RFBand") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->RFBand = u32_val;
                }
                else if (g_strcmp0 (key, "ChannelWidth") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ChannelWidth = u32_val;
                }
                else if (g_strcmp0 (key, "GuardInterval") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->GuardInterval = u32_val;
                }
                else if (g_strcmp0 (key, "RetryTimeout") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->RetryTimeout = u32_val;
                }
                else if (g_strcmp0 (key, "Powerlevel") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->Powerlevel = u32_val;
                }
                else if (g_strcmp0 (key, "PowerLevel_5G") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->PowerLevel_5G = u32_val;
                }
                else if (g_strcmp0 (key, "PowerValue") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->PowerValue = u32_val;
                }
                else if (g_strcmp0 (key, "APModuleEnable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->APModuleEnable = bol_val;
                }
                else if (g_strcmp0 (key, "WPSKeyWord") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->WPSKeyWord = u32_val;
                }
                else if (g_strcmp0 (key, "PWD") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->PWD, str_val);
                    g_free (str_val);
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return ret;
}


/*
 * Function Name: CtSgwGetWLANDeviceBySSID
 *
 * Description  : Get wlan configuration according to the wlan ssid
 *
 * Parameter:
 *             ssid <IN>:   The wlan ssid.
 *             obj <OUT>:   A CtSgwWLANDevice_t struct to contain the wlan information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetWLANDeviceBySSID(const char *ssid,  CtSgwWLANDevice_t *obj)
{
    CtSgwWLANDevice_t  *devObj = NULL;
    CtSgwWLANDevice_t  *pDev = NULL;
    guint32 count = 0;
    gint32 ret = CTSGW_NOK;
    gint32 i = 0;

    g_return_val_if_fail (!IS_EMPTY_STRING(ssid), CTSGW_NOK);
    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwGetWLANDeviceObjs( &devObj, &count);

    g_return_val_if_fail ((ret == CTSGW_OK), ret);
    g_return_val_if_fail ((count > 0), CTSGW_NOK);

    pDev = devObj;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 (pDev->SSID, ssid) != 0)
        {
            ++pDev;
            continue;
        }

        memmove (obj, pDev, sizeof (CtSgwWLANDevice_t));
        break;
    }

    if ( i >= count )
        ret = CTSGW_NOK;

    g_free (devObj);

    return ret;
}


/*
 * Function Name: CtSgwSetWLANDevice
 *
 * Description  : Set a specific wlan configuration according to the object path
 *
 * Parameter:
 *             obj <OUT>:   A CtSgwWLANDevice_t struct to contain the wlan information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetWLANDevice(CtSgwWLANDevice_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "SSID",
                           g_variant_new_string (obj->SSID));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_boolean (obj->Enable));
    
    g_variant_builder_add (builder,
                           "{sv}",
                           "Channel",
                           g_variant_new_uint32 (obj->Channel));

    g_variant_builder_add (builder,
                           "{sv}",
                           "BeaconType",
                           g_variant_new_string (obj->BeaconType));
    
    g_variant_builder_add (builder,
                           "{sv}",
                           "Standard",
                           g_variant_new_string (obj->Standard));

    g_variant_builder_add (builder,
                           "{sv}",
                           "WEPEncryptionLevel",
                           g_variant_new_string (obj->WEPEncryptionLevel));

    g_variant_builder_add (builder,
                           "{sv}",
                           "BasicAuthenticationMode",
                           g_variant_new_string (obj->BasicAuthenticationMode));

    g_variant_builder_add (builder,
                           "{sv}",
                           "WPAEncryptionModes",
                           g_variant_new_string (obj->WPAEncryptionModes));

    g_variant_builder_add (builder,
                           "{sv}",
                           "SSIDHide",
                           g_variant_new_boolean (obj->SSIDHide));

    g_variant_builder_add (builder,
                           "{sv}",
                           "RFBand",
                           g_variant_new_uint32 (obj->RFBand));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ChannelWidth",
                           g_variant_new_uint32 (obj->ChannelWidth));

    g_variant_builder_add (builder,
                           "{sv}",
                           "GuardInterval",
                           g_variant_new_uint32 (obj->GuardInterval));

    g_variant_builder_add (builder,
                           "{sv}",
                           "RetryTimeout",
                           g_variant_new_uint32 (obj->RetryTimeout));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Powerlevel",
                           g_variant_new_uint32 (obj->Powerlevel));

    g_variant_builder_add (builder,
                           "{sv}",
                           "PowerLevel_5G",
                           g_variant_new_uint32 (obj->PowerLevel_5G));

    g_variant_builder_add (builder,
                           "{sv}",
                           "APModuleEnable",
                           g_variant_new_boolean (obj->APModuleEnable));


    g_variant_builder_add (builder,
                           "{sv}",
                           "WPSKeyWord",
                           g_variant_new_uint32 (obj->WPSKeyWord));

    g_variant_builder_add (builder,
                           "{sv}",
                           "PWD",
                           g_variant_new_string (obj->PWD));
    
    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     obj->path.str,
                                     "com.ctc.igd1.WLANConfiguration",
                                     value);

    g_variant_unref (value);

    return ((ret == 0) ? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwGetWiFiTimerObjs
 *
 * Description  : Return all WiFi Timer configuration
 *
 * Parameter:
 *             objs <OUT>:   A CtSgwWiFiTimer1_t array to contain all the
 *                           wifi timer information. the memory is allocated in
 *                           this function, but need to be freed by the caller.
 *
 *            count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetWiFiTimerObjs(CtSgwWiFiTimer1_t **objs, int *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    CtSgwWiFiTimer1_t  *entryList = NULL;
    CtSgwWiFiTimer1_t  *pEntry = NULL;

    g_return_val_if_fail ((count != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/WLAN/ExTimers",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgwWiFiTimer1_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "WeekDay") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->WeekDay, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Time") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Time, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Active") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Active, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Enable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Enable, str_val);
                    g_free (str_val);
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;
}

/*
 * Function Name: CtSgwGetWiFiTimer
 *
 * Description  : Return a specific wifi timer configuration according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific timer.
 *             obj <OUT>:   A CtSgwWiFiTimer1_t struct to contain the wifi timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetWiFiTimer(CtSgwObjPath_t path, CtSgwWiFiTimer1_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    CtSgwWiFiTimer1_t  *pEntry = obj;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/WLAN/ExTimers",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0 && result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);

    ret = CTSGW_NOK;
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
        
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "WeekDay") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->WeekDay, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Time") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Time, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Active") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Active, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Enable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Enable, str_val);
                    g_free (str_val);
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return ret;
    
}

/*
 * Function Name: CtSgwSetWiFiTimer
 *
 * Description  : Set a specific wifi timer configuration according to the object path
 *
 * Parameter:
 *      obj <IN>: A CtSgwWiFiTimer1_t struct containing the timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetWiFiTimer (CtSgwWiFiTimer1_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "path",
                           g_variant_new_object_path (obj->path.str));
    
    g_variant_builder_add (builder,
                           "{sv}",
                           "WeekDay",
                           g_variant_new_string (obj->WeekDay));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Time",
                           g_variant_new_string (obj->Time));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Active",
                           g_variant_new_string (obj->Active));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_string (obj->Enable));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     obj->path.str,
                                     "com.ctc.igd1.WiFiTimer1",
                                     value);

    g_variant_unref (value);

    return ((ret == 0)? CTSGW_OK : CTSGW_NOK );
}


/*
 * Function Name: CtSgwAddWiFiTimer
 *
 * Description  : add a new wifi timer configuration according to the object path
 *
 * Parameter:
 *      obj <IN>: A CtSgwWiFiTimer1_t struct containing the wifi timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAddWiFiTimer(CtSgwWiFiTimer1_t *obj)
{
    GVariant *objPath = NULL;
    int ret = -1;
    gchar *str_val = NULL;
    
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/WLAN/ExTimers",
                               "com.ctc.igd1.ObjectManager",
                               "AddObject",
                               NULL,
                               &objPath,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_variant_get (objPath, FORMAT_PATH, &str_val);
    g_stpcpy (obj->path.str, str_val);
    ret = CtSgwSetWiFiTimer(obj);
    g_variant_unref (objPath);
    g_free (str_val);

    return ret;
}


/*
 * Function Name: CtSgwDelWiFiTimer
 *
 * Description  : Delete a specific wifi timer configuration according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the wifi timer to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelWiFiTimer(CtSgwObjPath_t path)
{
    int ret = CTSGW_NOK;

    g_return_val_if_fail(!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/WLAN/ExTimers",
                               "com.ctc.igd1.ObjectManager",
                               "DeleteObject",
                               g_variant_new ("o", path.str),
                               NULL,
                               -1);

    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwGetLEDObjs
 *
 * Description  : Return all LED related configuration
 *
 * Parameter:
 *             objs <OUT>:   A CtSgwLED_t array to contain all the
 *                           led configure, the memory is allocated in
 *                           this function, but need to be freed by the caller.
 *
 *            count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetLEDObjs(CtSgwLED_t **objs, int *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    CtSgwLED_t      *entryList = NULL;
    CtSgwLED_t      *pEntry = NULL;

    g_return_val_if_fail ((objs == NULL) && (count == NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/Peripheral/LED",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);
    
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgwLED_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "Status") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Status, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "StartTime") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->StartTime, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "EndTime") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->EndTime, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ControlCycle") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->ControlCycle, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Enable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Enable, str_val);
                    g_free (str_val);
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwGetLED
 *
 * Description  : Return a specific led configuration according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific led object.
 *             obj <OUT>:   A CtSgwLED_t struct to contain the led information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetLED(CtSgwObjPath_t path, CtSgwLED_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    CtSgwLED_t      *pEntry = obj;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/Peripheral/LED",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);
    
    g_return_val_if_fail ((ret == 0 && result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);

    ret = CTSGW_NOK;
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
        
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "Status") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Status, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "StartTime") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->StartTime, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "EndTime") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->EndTime, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ControlCycle") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->ControlCycle, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Enable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Enable, str_val);
                    g_free (str_val);
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return CTSGW_OK;

}


/*
 * Function Name: CtSgwSetLED
 *
 * Description  : Set a specific led configuration according to the object path
 *
 * Parameter:
 *      obj <IN>: CtSgwLED_t struct containing the led information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetLED(CtSgwLED_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "Status",
                           g_variant_new_string (obj->Status));

    g_variant_builder_add (builder,
                           "{sv}",
                           "StartTime",
                           g_variant_new_string (obj->StartTime));

    g_variant_builder_add (builder,
                           "{sv}",
                           "EndTime",
                           g_variant_new_string (obj->EndTime));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ControlCycle",
                           g_variant_new_string (obj->ControlCycle));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_string (obj->Enable));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     obj->path.str,
                                     "com.ctc.igd1.LED",
                                     value);

    g_variant_unref (value);

    return ((ret == 0) ? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwSetNFC
 *
 * Description  : Set the NFC configuration
 *
 * Parameter:
 *      obj <IN>: CtSgwNFC_t struct containing the NFC information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetNFC(CtSgwNFC_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_string (obj->Enable));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     "/com/ctc/igd1/Config/Peripheral/NFC",
                                     "com.ctc.igd1.NFC",
                                     value);

    g_variant_unref (value);
    
    return ((ret == 0) ? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwGetNFC
 *
 * Description  : Return the NFC configuration
 *
 * Parameter:
 *             obj <OUT>:   A CtSgwNFC_t struct to contain the nfc information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetNFC(CtSgwNFC_t *obj)
{
    GVariantIter iter;
    GVariant *dict = NULL;
    gchar   *key;
    GVariant *value = NULL;
    gchar       *str_val = NULL;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Config/Peripheral/NFC",
                                   "com.ctc.igd1.NFC",
                                   &dict);
    g_return_val_if_fail((ret == 0), CTSGW_NOK);
    
    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "Enable") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (obj->Enable, str_val);
            g_free (str_val);
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return ((ret == 0) ? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwGetSleepTimerObjs
 *
 * Description  : Return all sleep Timer configuration
 *
 * Parameter:
 *             objs <OUT>:   A CtSgwSleepTimer_t array to contain all the
 *                           sleep timer information. the memory is allocated in
 *                           this function, but need to be freed by the caller.
 *
 *            count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetSleepTimerObjs(CtSgwSleepTimer_t **objs, gint32 *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    CtSgwSleepTimer_t  *entryList = NULL;
    CtSgwSleepTimer_t  *pEntry = NULL;

    g_return_val_if_fail ((objs == NULL) && (count == NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/Power/SleepTimers",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgwSleepTimer_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "Day") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Day, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Time") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Time, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Active") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Active, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Enable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Enable, str_val);
                    g_free (str_val);
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;

}


/*
 * Function Name: CtSgwGetSleepTimer
 *
 * Description  : Return a specific sleep timer configuration according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific timer.
 *             obj <OUT>:   A CtSgwSleepTimer_t struct to contain the sleep timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetSleepTimer(CtSgwObjPath_t path, CtSgwSleepTimer_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    CtSgwSleepTimer_t  *pEntry = obj;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/Power/SleepTimers",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);

    ret = CTSGW_NOK;
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
        
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "Day") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Day, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Time") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Time, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Active") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Active, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Enable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Enable, str_val);
                    g_free (str_val);
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return ret;

}


/*
 * Function Name: CtSgwSetSleepTimer
 *
 * Description  : Set a specific sleep timer configuration according to the object path
 *
 * Parameter:
 *      obj <IN>: A CtSgwSleepTimer_t struct containing the timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetSleepTimer(CtSgwSleepTimer_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "path",
                           g_variant_new_object_path (obj->path.str));
    
    g_variant_builder_add (builder,
                           "{sv}",
                           "Day",
                           g_variant_new_string (obj->Day));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Time",
                           g_variant_new_string (obj->Time));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Active",
                           g_variant_new_string (obj->Active));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_string (obj->Enable));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     obj->path.str,
                                     "com.ctc.igd1.SleepTimer",
                                     value);

    g_variant_unref (value);

    return ((ret == 0) ? CTSGW_OK : CTSGW_NOK );
}


/*
 * Function Name: CtSgwAddSleepTimer
 *
 * Description  : add a new sleep timer
 *
 * Parameter:
 *      obj <IN>: A CtSgwSleepTimer_t struct containing the sleep timer information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAddSleepTimer(CtSgwSleepTimer_t *obj)
{
    GVariant *objPath = NULL;
    int ret = -1;
    gchar *str_val = NULL;
    
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/Power/SleepTimers",
                               "com.ctc.igd1.ObjectManager",
                               "AddObject",
                               NULL,
                               &objPath,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_variant_get (objPath, FORMAT_PATH, &str_val);
    g_stpcpy (obj->path.str, str_val);
    ret = CtSgwSetSleepTimer(obj);
    g_variant_unref (objPath);
    g_free (str_val);

    return ret;

}

/*
 * Function Name: CtSgwDelSleepTimer
 *
 * Description  : Delete a specific sleep timer configuration according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the sleep timer to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelSleepTimer(CtSgwObjPath_t path)
{
    int ret = CTSGW_NOK;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/Power/SleepTimers",
                               "com.ctc.igd1.ObjectManager",
                               "DeleteObject",
                               g_variant_new ("o", path.str),
                               NULL,
                               -1);


    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}
    

/*
 * Function Name: CtSgwSysCmdSetLOID
 *
 * Description  : Set the network register code and password
 *
 * Parameter:
 *          loid <IN>: Network register code.
 *      password <IN>: password of the broadband network
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdSetLOID(char loid[MAX_LOID_LEN+1], 
                       char password[MAX_PASSWORD_LEN+1])
{
    gint32 ret = -1;
    GVariant  *result = NULL;
    gchar     *err = NULL;
    guint32    succ = 0;

    g_return_val_if_fail (!IS_EMPTY_STRING(loid) || !IS_EMPTY_STRING(password), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/System",
                               "com.ctc.igd1.SysCmd",
                               "SetLOID",
                               g_variant_new("(ss)", loid, password),
                               &result,
                               -1);

    if (result != NULL)
    {
        g_variant_get (result, "(us)", &succ, &err);
        if (!IS_EMPTY_STRING(err))
        {
            g_print ("%s: %s\n", __FUNCTION__, err);
            g_free (err);
        }
        
        return succ;
    }

    return ((ret == 0) ? CTSGW_OK : CTSGW_NOK); 
}

/*
 * Function Name: CtSgwSysCmdRegisterLOID
 *
 * Description  : Start the loid registeration
 *
 * Parameter:
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdRegisterLOID(void)
{
    gint32 ret = -1;
    GVariant  *result = NULL;
    gchar     *err = NULL;
    guint32    succ = 0;

    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/System",
                               "com.ctc.igd1.SysCmd",
                               "RegisterLOID",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    if (result != NULL)
    {
        g_variant_get (result, "(us)", &succ, &err);
        if (!IS_EMPTY_STRING(err))
        {
            g_print ("%s: %s\n", __FUNCTION__, err);
            g_free (err);
        }

        g_variant_unref (result);
        
        return succ;
    }

    return CTSGW_NOK; 
}


/*
 * Function Name: CtSgwSysCmdCheckLOID
 *
 * Description  : check whether the broadband identification code is correct or not.
 *
 * Parameter:
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdCheckLOID(void )
{
    gint32 ret = -1;
    GVariant  *result = NULL;
    gchar     *err = NULL;
    guint32    succ = 0;

    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/System",
                               "com.ctc.igd1.SysCmd",
                               "CheckLOID",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    if (result != NULL)
    {
        g_variant_get (result, "(us)", &succ, &err);
        if (!IS_EMPTY_STRING(err))
        {
            g_print ("%s: %s\n", __FUNCTION__, err);
            g_free (err);
        }

        g_variant_unref (result);
        
        return succ;
    }

    return CTSGW_NOK; 
}


/*
 * Function Name: CtSgwSysCmdSetDateTime
 *
 * Description  : Set device time.
 *
 * Parameter:
 *      datetime <IN>: the time to set.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdSetDateTime(char datetime[MAX_TIME_LEN+1])
{
    gint32 ret = -1;
    GVariant  *result = NULL;
    gchar     *err = NULL;
    guint32    succ = 0;

    g_return_val_if_fail (!IS_EMPTY_STRING(datetime), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/System",
                               "com.ctc.igd1.SysCmd",
                               "SetDateTime",
                               g_variant_new_string (datetime),
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    if (result != NULL)
    {
        g_variant_get (result, "(us)", &succ, &err);
        if (!IS_EMPTY_STRING(err))
        {
            g_print ("%s: %s\n", __FUNCTION__, err);
            g_free (err);
        }
        
        g_variant_unref (result);
        
        return succ;
    }

    return CTSGW_NOK;
}


/*
 * Function Name: CtSgwSysCmdSetDevName
 *
 * Description  : Set device name.
 *
 * Parameter:
 *      datetime <IN>: the device time to set
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdSetDevName(char devname[MAX_DEVNAME_LEN+1])
{
    gint32 ret = -1;
    GVariant  *result = NULL;
    guint32    succ = 0;

    g_return_val_if_fail (!IS_EMPTY_STRING(devname), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/System",
                               "com.ctc.igd1.SysCmd",
                               "SetDevName",
                               g_variant_new_string (devname),
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    if (result != NULL)
    {
        g_variant_get (result, "(us)", &succ, NULL);
        g_variant_unref (result);
        return succ;
    }

    return CTSGW_NOK;
}


/*
 * Function Name: CtSgwSysCmdReboot
 *
 * Description  : reboot the device.
 *
 * Parameter:
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdReboot(void)
{
    gint32 ret = -1;
    GVariant  *result = NULL;
    guint32    succ = 0;

    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/System",
                               "com.ctc.igd1.SysCmd",
                               "Reboot",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    if (result != NULL)
    {
        g_variant_get (result, "(u)", &succ);
        g_variant_unref (result);
        return succ;
    }

    return CTSGW_NOK;
}


/*
 * Function Name: CtSgwSysCmdRestore
 *
 * Description  : reset the device configuration to default setting.
 *
 * Parameter:
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdRestore(void)
{
    gint32 ret = -1;
    GVariant  *result = NULL;
    guint32    succ = 0;

    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/System",
                               "com.ctc.igd1.SysCmd",
                               "Restore",
                               NULL,
                               &result,
                               -1);
    
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    if (result != NULL)
    {
        g_variant_get (result, "(u)", &succ);
        g_variant_unref (result);
        return succ;
    }

    return CTSGW_NOK;
}


/*
 * Function Name: CtSgwSysCmdUpgrade
 *
 * Description  : upgrade the device image.
 *
 * Parameter:
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdUpgrade(char url[MAX_URL_LEN+1], int mode, int method)
{
    gint32 ret = -1;

    g_return_val_if_fail (!IS_EMPTY_STRING(url), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/System",
                               "com.ctc.igd1.SysCmd",
                               "Upgrade",
                               g_variant_new ("(suu)", url, mode, method),
                               NULL,
                               -1);

    return ( (ret == 0) ? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwSysCmdCheckUAPasswd
 *
 * Description  : Check whether the user admin password is correct or not.
 *
 * Parameter:
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdCheckUAPasswd(const char *pass, int *result)
{
    gint32 ret = -1;
    GVariant  *res = NULL;
    guint32    succ = 0;
    gchar       *err;

    g_return_val_if_fail (!IS_EMPTY_STRING(pass), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/System",
                               "com.ctc.igd1.SysCmd",
                               "CheckUAPasswd",
                               g_variant_new ("s", pass),
                               &res,
                               -1);

    if (res != NULL)
    {
        g_variant_get (res, "(us)", &succ, &err);
        *result = succ;
        if (err != NULL)
        {
            g_print("%s: %s\n", __FUNCTION__, err);
            g_free (err);
        }

        g_variant_unref (res);
    }

    return ((ret == 0) ? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwSysCmdCheckTAPasswd
 *
 * Description  : Check whether the telecomadmin password is correct or not.
 *
 * Parameter:
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdCheckTAPasswd(const char *pass, int *result)
{
    gint32 ret = -1;
    GVariant  *res = NULL;
    guint32    succ = 0;
    gchar     *err;

    g_return_val_if_fail (!IS_EMPTY_STRING(pass), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/System",
                               "com.ctc.igd1.SysCmd",
                               "CheckTAPasswd",
                               g_variant_new ("s", pass),
                               &res,
                               -1);
    
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((res != NULL), CTSGW_NOK);
    if (res != NULL)
    {
        g_variant_get (res, "(us)", &succ, &err);
        *result = succ;
        if (err != NULL)
        {
            g_print("%s: %s\n", __FUNCTION__, err);
            g_free (err);
        }

        g_variant_unref (res);
    }

    return ((ret == 0) ? CTSGW_OK : CTSGW_NOK);
}

/*
 * Function Name: CtSgwSysCmdSubscribe
 *
 * Description  : open the ordered service .
 *
 * Parameter:
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSysCmdSubscribe(void)
{
    gint32 ret = -1;
    GVariant  *result = NULL;
    gchar     *err = NULL;
    guint32    succ = 0;

    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/System",
                               "com.ctc.igd1.SysCmd",
                               "SubScribe",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    if (result != NULL)
    {
        g_variant_get (result, "(us)", &succ, &err);
        if (err != NULL)
        {
            g_print("%s: %s\n", __FUNCTION__, err);
            g_free (err);
        }

        g_variant_unref (result);
        
        return succ;
    }

    return ((ret == 0) ? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwGetWANPPPConnObjs
 *
 * Description  : Return all ppp connections
 *
 * Parameter:
 *    objs <OUT>:   A CtSgwWANPPPConn_t array to contain all the
 *                  ppp connection object. the memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetWANPPPConnObjs(CtSgwWANPPPConn_t **objs, int *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    gboolean         bol_val = 0;
    CtSgwWANPPPConn_t  *entryList = NULL;
    CtSgwWANPPPConn_t  *pEntry = NULL;

    g_return_val_if_fail ((count != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/WANPPPConnection",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);
    
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgwWANPPPConn_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "LANInterface") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_PATH, &str_val);
                    g_stpcpy (pEntry->LANInterface.str, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ServiceList") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->ServiceList, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DHCPEnable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->DHCPEnable = bol_val;
                }
                else if (g_strcmp0 (key, "IPMode") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->IPMode= u32_val;
                }
                else if (g_strcmp0 (key, "IPV6ConnectionStatus") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IPV6ConnectionStatus, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ProxyEnable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->ProxyEnable = bol_val;
                }
                else if (g_strcmp0 (key, "ProxyMaxUser") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ProxyMaxUser= u32_val;
                }
                else if (g_strcmp0 (key, "DDNSCfgEnabled") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->DDNSCfgEnabled = bol_val;
                }
                else if (g_strcmp0 (key, "DDNSProvider") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSProvider, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSUsername") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSUsername, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSPassword") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSPassword, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ServicePort") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ServicePort= u32_val;
                }
                else if (g_strcmp0 (key, "DDNSDomainName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSDomainName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSHostName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSHostName, str_val);
                    g_free (str_val);
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwGetWANPPPConn
 *
 * Description  : Return a specific ppp connection according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific ppp connection.
 *             obj <OUT>:   A CtSgwWANPPPConn_t struct to contain the connection information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetWANPPPConn(CtSgwObjPath_t path, CtSgwWANPPPConn_t *objs)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    gboolean         bol_val = 0;
    CtSgwWANPPPConn_t  *pEntry = objs;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    g_return_val_if_fail (objs != NULL, CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/WANPPPConnection",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);

    ret = CTSGW_NOK;    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
        
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "LANInterface") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_PATH, &str_val);
                    g_stpcpy (pEntry->LANInterface.str, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ServiceList") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->ServiceList, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DHCPEnable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->DHCPEnable = bol_val;
                }
                else if (g_strcmp0 (key, "IPMode") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->IPMode= u32_val;
                }
                else if (g_strcmp0 (key, "IPV6ConnectionStatus") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IPV6ConnectionStatus, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ProxyEnable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->ProxyEnable = bol_val;
                }
                else if (g_strcmp0 (key, "ProxyMaxUser") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ProxyMaxUser= u32_val;
                }
                else if (g_strcmp0 (key, "DDNSCfgEnabled") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->DDNSCfgEnabled = bol_val;
                }
                else if (g_strcmp0 (key, "DDNSProvider") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSProvider, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSUsername") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSUsername, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSPassword") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSPassword, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ServicePort") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ServicePort= u32_val;
                }
                else if (g_strcmp0 (key, "DDNSDomainName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSDomainName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSHostName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSHostName, str_val);
                    g_free (str_val);
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return ret;

}


/*
 * Function Name: CtSgwSetWANPPPConn
 *
 * Description  : Set a specific ppp connection according to the object path
 *
 * Parameter:
 *      obj <IN>: A CtSgwWANPPPConn_t struct containing the ppp connection.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetWANPPPConn (CtSgwWANPPPConn_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "LANInterface",
                           g_variant_new_object_path (obj->LANInterface.str));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ServiceList",
                           g_variant_new_string (obj->ServiceList));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DHCPEnable",
                           g_variant_new_boolean (obj->DHCPEnable));

    g_variant_builder_add (builder,
                           "{sv}",
                           "IPMode",
                           g_variant_new_uint32 (obj->IPMode));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ProxyEnable",
                           g_variant_new_boolean (obj->ProxyEnable));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ProxyMaxUser",
                           g_variant_new_uint32 (obj->ProxyMaxUser));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DDNSCfgEnabled",
                           g_variant_new_boolean (obj->DDNSCfgEnabled));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DDNSProvider",
                           g_variant_new_string (obj->DDNSProvider));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DDNSUsername",
                           g_variant_new_string (obj->DDNSUsername));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DDNSPassword",
                           g_variant_new_string (obj->DDNSPassword));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ServicePort",
                           g_variant_new_uint32 (obj->ServicePort));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DDNSDomainName",
                           g_variant_new_string (obj->DDNSDomainName));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DDNSHostName",
                           g_variant_new_string (obj->DDNSHostName));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     obj->path.str,
                                     "com.ctc.igd1.WANPPPConnection",
                                     value);

    g_variant_unref (value);

    return ((ret == 0) ? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwGetWANIPConnObjs
 *
 * Description  : Return all wan IP connections
 *
 * Parameter:
 *    objs <OUT>:   A CtSgwWANIPConn_t array to contain all the
 *                  wan IP connection object. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetWANIPConnObjs(CtSgwWANIPConn_t **objs, int *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    gboolean         bol_val = 0;
    CtSgwWANIPConn_t  *entryList = NULL;
    CtSgwWANIPConn_t  *pEntry = NULL;

    g_return_val_if_fail ((count != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/WANIPConnection",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgwWANIPConn_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "LANInterface") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_PATH, &str_val);
                    g_stpcpy (pEntry->LANInterface.str, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ServiceList") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->ServiceList, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DHCPEnable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->DHCPEnable = bol_val;
                }
                else if (g_strcmp0 (key, "IPMode") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->IPMode= u32_val;
                }
                else if (g_strcmp0 (key, "IPV6ConnectionStatus") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IPV6ConnectionStatus, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSCfgEnabled") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->DDNSCfgEnabled = bol_val;
                }
                else if (g_strcmp0 (key, "DDNSProvider") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSProvider, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSUsername") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSUsername, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSPassword") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSPassword, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ServicePort") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ServicePort= u32_val;
                }
                else if (g_strcmp0 (key, "DDNSDomainName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSDomainName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSHostName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSHostName, str_val);
                    g_free (str_val);
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);
        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;

}


/*
 * Function Name: CtSgwGetWANIPConn
 *
 * Description  : Return a specific wan IP connection according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific wan IP connection.
 *             obj <OUT>:   A CtSgwWANIPConn_t struct to contain the connection information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetWANIPConn(CtSgwObjPath_t path, CtSgwWANIPConn_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    gboolean         bol_val = 0;
    CtSgwWANIPConn_t  *pEntry = obj;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    g_return_val_if_fail (obj != NULL, CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/WANIPConnection",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);

    ret = CTSGW_NOK;    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
        
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "LANInterface") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_PATH, &str_val);
                    g_stpcpy (pEntry->LANInterface.str, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ServiceList") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->ServiceList, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DHCPEnable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->DHCPEnable = bol_val;
                }
                else if (g_strcmp0 (key, "IPMode") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->IPMode= u32_val;
                }
                else if (g_strcmp0 (key, "IPV6ConnectionStatus") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->IPV6ConnectionStatus, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSCfgEnabled") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->DDNSCfgEnabled = bol_val;
                }
                else if (g_strcmp0 (key, "DDNSProvider") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSProvider, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSUsername") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSUsername, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSPassword") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSPassword, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ServicePort") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ServicePort= u32_val;
                }
                else if (g_strcmp0 (key, "DDNSDomainName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSDomainName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DDNSHostName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DDNSHostName, str_val);
                    g_free (str_val);
                }
                
                g_free (key);
                g_variant_unref (propertyValue);
            }
        
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwSetWANIPConn
 *
 * Description  : Set a specific wan IP connection according to the object path
 *
 * Parameter:
 *      obj <IN>: A CtSgwWANIPConn_t struct containing the IP connection.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetWANIPConn (CtSgwWANIPConn_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "LANInterface",
                           g_variant_new_object_path (obj->LANInterface.str));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ServiceList",
                           g_variant_new_string (obj->ServiceList));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DHCPEnable",
                           g_variant_new_boolean (obj->DHCPEnable));

    g_variant_builder_add (builder,
                           "{sv}",
                           "IPMode",
                           g_variant_new_uint32 (obj->IPMode));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DDNSCfgEnabled",
                           g_variant_new_boolean (obj->DDNSCfgEnabled));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DDNSProvider",
                           g_variant_new_string (obj->DDNSProvider));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DDNSUsername",
                           g_variant_new_string (obj->DDNSUsername));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DDNSPassword",
                           g_variant_new_string (obj->DDNSPassword));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ServicePort",
                           g_variant_new_uint32 (obj->ServicePort));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DDNSDomainName",
                           g_variant_new_string (obj->DDNSDomainName));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DDNSHostName",
                           g_variant_new_string (obj->DDNSHostName));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     obj->path.str,
                                     "com.ctc.igd1.WANIPConnection",
                                     value);

    g_variant_unref (value);

    return (ret == 0) ? CTSGW_OK : CTSGW_NOK;
}


/*
 * Function Name: CtSgwGetDHCPServerObjs
 *
 * Description  : Return all DHCP Servers
 *
 * Parameter:
 *    objs <OUT>:   A CtSgwDHCPServer_t array to contain all the
 *                  wan DHCP Server object. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetDHCPServerObjs(CtSgwDHCPServer_t **objs, int *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    CtSgwDHCPServer_t  *entryList = NULL;
    CtSgwDHCPServer_t  *pEntry = NULL;

    g_return_val_if_fail ((count != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/DHCPServer",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgwDHCPServer_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "MinAddress") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_PATH, &str_val);
                    g_stpcpy (pEntry->MinAddress, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "MaxAddress") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->MaxAddress, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "SubnetMask") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->SubnetMask, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "LeaseTime") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->LeaseTime= u32_val;
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }

            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }

        g_free (pathName);
        g_variant_unref (interfaceDict);
        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwGetDHCPServer
 *
 * Description  : Return a specific dhcp server according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific dhcp server.
 *             obj <OUT>:   A CtSgwDHCPServer_t struct to contain the dhcp server.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetDHCPServer(CtSgwObjPath_t path, CtSgwDHCPServer_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    CtSgwDHCPServer_t  *pEntry = obj;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    g_return_val_if_fail ( (obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/DHCPServer",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    ret = CTSGW_NOK;    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
        
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "MinAddress") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_PATH, &str_val);
                    g_stpcpy (pEntry->MinAddress, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "MaxAddress") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->MaxAddress, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "SubnetMask") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->SubnetMask, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "LeaseTime") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->LeaseTime= u32_val;
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }

            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }

        g_free (pathName);
        g_variant_unref (interfaceDict);
        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return ret;

}


/*
 * Function Name: CtSgwSetDHCPServer
 *
 * Description  : Set a specific dhcp server according to the object path
 *
 * Parameter:
 *      obj <IN>: A CtSgwDHCPServer_t struct containing the dhcp server.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetDHCPServer(CtSgwDHCPServer_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "MinAddress",
                           g_variant_new_string (obj->MinAddress));

    g_variant_builder_add (builder,
                           "{sv}",
                           "MaxAddress",
                           g_variant_new_string (obj->MaxAddress));

    g_variant_builder_add (builder,
                           "{sv}",
                           "SubnetMask",
                           g_variant_new_string (obj->SubnetMask));

    g_variant_builder_add (builder,
                           "{sv}",
                           "LeaseTime",
                           g_variant_new_uint32 (obj->LeaseTime));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     obj->path.str,
                                     "com.ctc.igd1.DHCPServer",
                                     value);

    g_variant_unref (value);
    
    return ret;
}


/*
 * Function Name: CtSgwSetUplinkQos
 *
 * Description  : Set the QoS configuration
 *
 * Parameter:
 *      obj <IN>: A CtSgwUplinkQoS_t struct containing the QoS configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetUplinkQos(CtSgwUplinkQoS_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "Mode",
                           g_variant_new_string (obj->Mode));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_boolean (obj->Enable));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Bandwidth",
                           g_variant_new_uint32 (obj->Bandwidth));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Plan",
                           g_variant_new_string (obj->Plan));

    g_variant_builder_add (builder,
                           "{sv}",
                           "EnableForceWeight",
                           g_variant_new_boolean (obj->EnableForceWeight));

    g_variant_builder_add (builder,
                           "{sv}",
                           "EnableDSCPMark",
                           g_variant_new_boolean (obj->EnableDSCPMark));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable802_1_P",
                           g_variant_new_uint32 (obj->Enable802_1_P));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     "/com/ctc/igd1/Config/QoS/UplinkQoS",
                                     "com.ctc.igd1.UplinkQoS",
                                     value);

    g_variant_unref (value);
    
    return (ret == 0) ? CTSGW_OK : CTSGW_NOK;
}

/*
 * Function Name: CtSgwGetUplinkQos
 *
 * Description  : Get the QoS configuration
 *
 * Parameter:
 *      obj <OUT>: A CtSgwUplinkQoS_t struct to contain QoS configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetUplinkQoS(CtSgwUplinkQoS_t *obj)
{
    GVariant *dict = NULL;
    GVariant *value = NULL;
    GVariantIter iter;
    gchar   *key;
    gchar   *str_val = NULL;
    gboolean bol_val;
    guint32  int_val;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK );
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Config/QoS/UplinkQoS",
                                   "com.ctc.igd1.UplinkQoS",
                                   &dict);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);

    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "Mode") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (obj->Mode, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Enable") == 0)
        {
            g_variant_get (value, FORMAT_BOOL, &bol_val);
            obj->Enable = bol_val;
        }
        else if (g_strcmp0 (key, "Bandwidth") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            obj->Bandwidth = int_val;
        }
        else if (g_strcmp0 (key, "Plan") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (obj->Plan, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "EnableForceWeight") == 0)
        {
            g_variant_get (value, FORMAT_BOOL, &bol_val);
            obj->EnableForceWeight = bol_val;
        }
        else if (g_strcmp0 (key, "EnableDSCPMark") == 0)
        {
            g_variant_get (value, FORMAT_BOOL, &bol_val);
            obj->EnableDSCPMark = bol_val;
        }
        else if (g_strcmp0 (key, "Enable802_1_P") == 0)
        {
            g_variant_get (value, FORMAT_UINT32, &int_val);
            obj->Enable802_1_P = int_val;
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwGetUplinkQoSAppRuleObjs
 *
 * Description  : Return all QoS app rules
 *
 * Parameter:
 *    objs <OUT>:   A CtSgwUplinkQoSAppRule_t array to contain all the
 *                  wan QoS application rule object. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetUplinkQoSAppRuleObjs(CtSgwUplinkQoSAppRule_t **paths, int *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    CtSgwUplinkQoSAppRule_t  *entryList = NULL;
    CtSgwUplinkQoSAppRule_t  *pEntry = NULL;

    g_return_val_if_fail (count != NULL, CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/QoS/UplinkQoS/App",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    // If paths is NULL, just return the object count.
    if (paths == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        paths = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgwUplinkQoSAppRule_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *paths = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "AppName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->AppName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ClassQueue") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ClassQueue= u32_val;
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }

            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);
        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwGetUplinkQoSAppRule
 *
 * Description  : Return a specific QoS app rule according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific QoS app rule.
 *             obj <OUT>:   A CtSgwUplinkQoSAppRule_t struct to contain the QoS app rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetUplinkQoSAppRule(CtSgwObjPath_t path, CtSgwUplinkQoSAppRule_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    CtSgwUplinkQoSAppRule_t  *pEntry = obj;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    g_return_val_if_fail (obj != NULL, CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/QoS/UplinkQoS/App",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);

    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
        
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "AppName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->AppName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ClassQueue") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ClassQueue= u32_val;
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }

            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);
        
        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return ret;
}


/*
 * Function Name: CtSgwSetUplinkQoSAppRule
 *
 * Description  : Set a specific QoS app rule according to the object path
 *
 * Parameter:
 *      obj <IN>: A CtSgwUplinkQoSAppRule_t struct containing the QoS app rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetUplinkQoSAppRule(CtSgwUplinkQoSAppRule_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail (obj != NULL, CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "path",
                           g_variant_new_object_path (obj->path.str));
    
    g_variant_builder_add (builder,
                           "{sv}",
                           "AppName",
                           g_variant_new_string (obj->AppName));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ClassQueue",
                           g_variant_new_uint32 (obj->ClassQueue));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     obj->path.str,
                                     "com.ctc.igd1.UplinkQoSApp",
                                     value);

    g_variant_unref (value);
    
    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwAddUplinkQoSAppRule
 *
 * Description  : add a new QoS app rule.
 *
 * Parameter:
 *      obj <IN>: A CtSgwUplinkQoSAppRule_t struct containing the QoS app rule information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAddUplinkQoSAppRule(CtSgwUplinkQoSAppRule_t *obj)
{
    GVariant *objPath = NULL;
    int ret = -1;
    gchar *str_val = NULL;
    
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/QoS/UplinkQoS/App",
                               "com.ctc.igd1.ObjectManager",
                               "AddObject",
                               NULL,
                               &objPath,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_variant_get (objPath, FORMAT_PATH, &str_val);
    g_stpcpy (obj->path.str, str_val);
    ret = CtSgwSetUplinkQoSAppRule(obj);
    g_variant_unref (objPath);
    g_free (str_val);

    return ret;
}


/*
 * Function Name: CtSgwDelUplinkQoSAppRule
 *
 * Description  : Delete a specific uplink QoS app rule according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the QoS app rule to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelUplinkQoSAppRule(CtSgwObjPath_t path)
{
    int ret = CTSGW_NOK;
        
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/QoS/UplinkQoS/App",
                               "com.ctc.igd1.ObjectManager",
                               "DeleteObject",
                               g_variant_new ("o", path.str),
                               NULL,
                               -1);


    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwGetUplinkQoSClsRuleObjs
 *
 * Description  : Return all QoS classification rules
 *
 * Parameter:
 *    objs <OUT>:   A CtSgwUplinkQoSClsRule_t array to contain all the
 *                  wan QoS classification rule object. The memory is allocated
 *                  in this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetUplinkQoSClsRuleObjs(CtSgwUplinkQoSClsRule_t **objs, int *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    gint32           i32_val = 0;
    CtSgwUplinkQoSClsRule_t  *entryList = NULL;
    CtSgwUplinkQoSClsRule_t  *pEntry = NULL;

    g_return_val_if_fail (count != NULL, CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/UplinkQos/Classification",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    // If paths is NULL, just return the object count.
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgwUplinkQoSClsRule_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "path") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_PATH, &str_val);
                    g_stpcpy (pEntry->path.str, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "match_paths") == 0)
                {
                    CtSgwObjPath_t  *pObjPath = NULL;
                    gint32 match_num = 0;
                    GVariantIter *iterSub;
                    
                    match_num = g_variant_n_children (propertyValue);
                    if (match_num <= 0)
                    {
                        pEntry->match_paths = NULL;
                        continue;
                    }
                    else
                    {
                        pEntry->match_paths = g_try_new0 (CtSgwObjPath_t, match_num);
                        g_return_val_if_fail (pEntry->match_paths != NULL, CTSGW_NOK);
                    }

                    pObjPath = pEntry->match_paths;
                    g_variant_get (propertyValue, "ao", &iterSub);
                    while (g_variant_iter_loop(iterSub, FORMAT_PATH, &str_val))
                    {
                        g_stpcpy (pObjPath->str, str_val);
                        ++pObjPath;
                    }
                    g_variant_iter_free (iterSub);
                }
                else if (g_strcmp0 (key, "path_count") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_INT32, &i32_val);
                    pEntry->path_count = i32_val;
                }
                else if (g_strcmp0 (key, "ClassQueue") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ClassQueue = u32_val;
                }
                else if (g_strcmp0 (key, "DSCPMarkValue") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->DSCPMarkValue = u32_val;
                }
                else if (g_strcmp0 (key, "_802_1P_Value") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->_802_1P_Value = u32_val;
                }
                else if (g_strcmp0 (key, "action") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_PATH, &str_val);
                    g_stpcpy (pEntry->action.path.str, str_val);
                    g_free (str_val);
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }

            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }

        g_free (pathName);
        g_variant_unref (interfaceDict);
        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwGetUplinkQoSClsRule
 *
 * Description  : Return a specific QoS classification rule according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific QoS classification rule.
 *             obj <OUT>:   A CtSgwUplinkQoSClsRule_t struct to contain the QoS classification rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetUplinkQoSClsRule(CtSgwObjPath_t path, CtSgwUplinkQoSClsRule_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    gint32           i32_val = 0;
    CtSgwUplinkQoSClsRule_t  *pEntry = obj;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    g_return_val_if_fail (obj != NULL, CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/UplinkQos/Classification",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);

    // Result is of type a{oa{sa{sv}}}
    ret = CTSGW_NOK;
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
        
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "path") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_PATH, &str_val);
                    g_stpcpy (pEntry->path.str, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "match_paths") == 0)
                {
                    CtSgwObjPath_t  *pObjPath = NULL;
                    gint32 match_num = 0;
                    GVariantIter *iterSub;
                    
                    match_num = g_variant_n_children (propertyValue);
                    if (match_num <= 0)
                    {
                        pEntry->match_paths = NULL;
                        g_free (key);
                        g_variant_unref (propertyValue);
                        continue;
                    }

                    pEntry->match_paths = g_try_new0 (CtSgwObjPath_t, match_num);
                    g_return_val_if_fail (pEntry->match_paths != NULL, CTSGW_NOK);

                    pObjPath = pEntry->match_paths;
                    g_variant_get (propertyValue, "ao", &iterSub);
                    while (g_variant_iter_loop(iterSub, "o", &str_val))
                    {
                        g_stpcpy (pObjPath->str, str_val);
                        ++pObjPath;
                    }
                    g_variant_iter_free (iterSub);
                }
                else if (g_strcmp0 (key, "path_count") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_INT32, &i32_val);
                    pEntry->path_count = i32_val;
                }
                else if (g_strcmp0 (key, "ClassQueue") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ClassQueue = u32_val;
                }
                else if (g_strcmp0 (key, "DSCPMarkValue") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->DSCPMarkValue = u32_val;
                }
                else if (g_strcmp0 (key, "_802_1P_Value") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->_802_1P_Value = u32_val;
                }
                else if (g_strcmp0 (key, "action") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_PATH, &str_val);
                    g_stpcpy (pEntry->action.path.str, str_val);
                    g_free (str_val);
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }

            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }

        g_free (pathName);
        g_variant_unref (interfaceDict);
        
        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return ret;
}


/*
 * Function Name: CtSgwAddUplinkQoSClsRule
 *
 * Description  : add a new QoS classification rule.
 *
 * Parameter:
 *      obj <IN>: A CtSgwUplinkQoSClsRule_t struct containing the QoS classification rule information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAddUplinkQoSClsRule(CtSgwUplinkQoSClsRule_t *obj)
{
    GVariant *objPath = NULL;
    int ret = -1;
    gchar *str_val = NULL;
    
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/UplinkQos/Classification",
                               "com.ctc.igd1.ObjectManager",
                               "AddObject",
                               NULL,
                               &objPath,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_variant_get (objPath, FORMAT_PATH, &str_val);
    g_stpcpy (obj->path.str, str_val);
    ret = CtSgwSetUplinkQoSClsRule(obj);
    g_variant_unref (objPath);
    g_free (str_val);

    return ret;
}


/*
 * Function Name: CtSgwDelUplinkQoSClsRule
 *
 * Description  : Delete a specific uplink QoS classification rule according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the QoS classification rule to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelUplinkQoSClsRule(CtSgwObjPath_t path)
{
    int ret = CTSGW_NOK;
        
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/UplinkQos/Classification",
                               "com.ctc.igd1.ObjectManager",
                               "DeleteObject",
                               g_variant_new (FORMAT_PATH, path.str),
                               NULL,
                               -1);


    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwSetUplinkQoSClsRule
 *
 * Description  : Set a specific QoS classification rule according to the object path
 *
 * Parameter:
 *      obj <IN>: A CtSgwUplinkQoSClsRule_t struct containing the QoS classification rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetUplinkQoSClsRule(CtSgwUplinkQoSClsRule_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    GVariantBuilder *matchBuilder;
    GVariant *matchList = NULL;
    CtSgwObjPath_t *pPath = NULL;
    int i = 0;
    int ret = -1;

    g_return_val_if_fail (obj != NULL, CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "path",
                           g_variant_new_object_path (obj->path.str));

    g_variant_builder_add (builder,
                           "{sv}",
                           "path_count",
                           g_variant_new_int32 (obj->path_count));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ClassQueue",
                           g_variant_new_uint32 (obj->ClassQueue));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DSCPMarkValue",
                           g_variant_new_uint32 (obj->DSCPMarkValue));

    g_variant_builder_add (builder,
                           "{sv}",
                           "_802_1P_Value",
                           g_variant_new_uint32 (obj->_802_1P_Value));

    g_variant_builder_add (builder,
                           "{sv}",
                           "action",
                           g_variant_new (FORMAT_PATH, obj->action.path.str));

    pPath = obj->match_paths;
    matchBuilder = g_variant_builder_new (G_VARIANT_TYPE ("ao"));
    for (i = 0; i < obj->path_count; ++i)
    {
        g_variant_builder_add (matchBuilder, FORMAT_PATH, pPath->str);
        ++pPath;
    }
    
    matchList = g_variant_builder_end (matchBuilder);
    g_variant_builder_unref (matchBuilder);

    g_variant_builder_add (builder,
                           "{sv}",
                           "match_paths",
                           matchList);

    g_variant_unref (matchList);
    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     obj->path.str,
                                     "com.ctc.igd1.UplinkQosCls",
                                     value);

    g_variant_unref (value);
    
    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwGetUplinkQoSClsMatch
 *
 * Description  : Return a specific QoS classification type rule according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific QoS classification rule.
 *             obj <OUT>:   A CtSgwUplinkQoSClsMatch_t struct to contain the QoS classification type rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetUplinkQoSClsMatch(CtSgwObjPath_t path, CtSgwUplinkQoSClsMatch_t *match)
{
    CtSgwUplinkQoSClsMatch_t *pEntry = match;
    GVariant *dict = NULL;
    GVariant *value = NULL;
    GVariantIter iter;
    gchar   *key;
    gchar   *str_val = NULL;
    int ret = -1;

    g_return_val_if_fail ((match != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   path.str,
                                   "com.ctc.igd1.UplinkQosClsType",
                                   &dict);
    
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_stpcpy (pEntry->path.str, path.str);

    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "Type") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (pEntry->Type, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Max") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (pEntry->Max, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Min") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (pEntry->Min, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "ProtocolList") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (pEntry->ProtocolList, str_val);
            g_free (str_val);
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwAddUplinkQoSClsMatch
 *
 * Description  : add a new QoS classification type rule.
 *
 * Parameter:
 *      obj <IN>: A CtSgwUplinkQoSClsMatch_t struct containing the QoS classification type rule information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAddUplinkQoSClsMatch(CtSgwUplinkQoSClsMatch_t *match)
{
    GVariant *objPath = NULL;
    int ret = -1;
    gchar *str_val = NULL;
    
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "com.ctc.igd1.UplinkQosClsType",
                               "com.ctc.igd1.ObjectManager",
                               "AddObject",
                               NULL,
                               &objPath,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_variant_get (objPath, FORMAT_PATH, &str_val);
    g_stpcpy (match->path.str, str_val);
    ret = CtSgwSetUplinkQoSClsMatch(match);
    g_variant_unref (objPath);
    g_free (str_val);

    return ret;

}


/*
 * Function Name: CtSgwDelUplinkQoSClsMatch
 *
 * Description  : Delete a specific uplink QoS classification type rule according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the QoS classification type rule to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelUplinkQoSClsMatch(CtSgwObjPath_t path)
{
    int ret = CTSGW_NOK;
        
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "com.ctc.igd1.UplinkQosClsType",
                               "com.ctc.igd1.ObjectManager",
                               "DeleteObject",
                               g_variant_new (FORMAT_PATH, path.str),
                               NULL,
                               -1);


    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwSetUplinkQoSClsMatch
 *
 * Description  : Set a specific QoS classification type rule according to the object path
 *
 * Parameter:
 *      obj <IN>: A CtSgwUplinkQoSClsRule_t struct containing the QoS classification type rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetUplinkQoSClsMatch (CtSgwUplinkQoSClsMatch_t *match)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail (match != NULL, CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "path",
                           g_variant_new_object_path (match->path.str));
    
    g_variant_builder_add (builder,
                           "{sv}",
                           "Type",
                           g_variant_new_string (match->Type));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Max",
                           g_variant_new_string (match->Max));
    
    g_variant_builder_add (builder,
                           "{sv}",
                           "Min",
                           g_variant_new_string (match->Min));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ProtocolList",
                           g_variant_new_string (match->ProtocolList));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     match->path.str,
                                     "com.ctc.igd1.UplinkQosClsType",
                                     value);

    g_variant_unref (value);
    
    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgwGetPortMappingObjs
 *
 * Description  : Return port mapping rules
 *
 * Parameter:
 *    objs <OUT>:   A CtSgwPortMapping_t array to contain all the
 *                  port mapping object. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgwGetPortMappingObjs(CtSgwPortMapping_t **objs, int *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    gboolean         bol_val;
    guint32          u32_val;
    CtSgwPortMapping_t      *entryList = NULL;
    CtSgwPortMapping_t      *pEntry = NULL;

    g_return_val_if_fail ((count == NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/PortMapping",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgwPortMapping_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_free (pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "Enable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->Enable = bol_val;
                }
                else if (g_strcmp0 (key, "LeaseDuration") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->LeaseDuration = u32_val;
                }
                else if (g_strcmp0 (key, "RemoteHost") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->RemoteHost, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ExternalPort") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ExternalPort = u32_val;
                }
                else if (g_strcmp0 (key, "InternalPort") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->InternalPort = u32_val;
                }
                else if (g_strcmp0 (key, "PortMappingProtocol") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->PortMappingProtocol, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "InternalClient") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->InternalClient, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Description") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Description, str_val);
                    g_free (str_val);
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }

            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }

        g_free (pathName);
        g_variant_unref (interfaceDict);
        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgwGetPortMapping
 *
 * Description  : Return a specific port mapping rules according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific port mapping rule.
 *             obj <OUT>:   A CtSgwPortMapping_t struct to contain the port mapping rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwGetPortMapping(CtSgwObjPath_t path, CtSgwPortMapping_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    gboolean         bol_val;
    guint32          u32_val;
    CtSgwPortMapping_t      *pEntry = obj;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    g_return_val_if_fail (obj != NULL, CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/PortMapping",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);

    ret = CTSGW_NOK;
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
        
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "Enable") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_BOOL, &bol_val);
                    pEntry->Enable = bol_val;
                }
                else if (g_strcmp0 (key, "LeaseDuration") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->LeaseDuration = u32_val;
                }
                else if (g_strcmp0 (key, "RemoteHost") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->RemoteHost, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "ExternalPort") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->ExternalPort = u32_val;
                }
                else if (g_strcmp0 (key, "InternalPort") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->InternalPort = u32_val;
                }
                else if (g_strcmp0 (key, "PortMappingProtocol") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->PortMappingProtocol, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "InternalClient") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->InternalClient, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Description") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Description, str_val);
                    g_free (str_val);
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }

            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }

        g_free (pathName);
        g_variant_unref (interfaceDict);

        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return ret;
}


/*
 * Function Name: CtSgwAddPortMapping
 *
 * Description  : add a new port mapping rule
 *
 * Parameter:
 *      obj <IN>: A CtSgwPortMapping_t struct containing the port mapping rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAddPortMapping(CtSgwPortMapping_t *obj)
{
    GVariant *objPath = NULL;
    int ret = -1;
    gchar *str_val = NULL;
    
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/PortMapping",
                               "com.ctc.igd1.ObjectManager",
                               "AddObject",
                               NULL,
                               &objPath,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_variant_get (objPath, FORMAT_PATH, &str_val);
    g_stpcpy (obj->path.str, str_val);
    ret = CtSgwSetPortMapping(obj);
    g_variant_unref (objPath);
    g_free (str_val);

    return ret;
}


/*
 * Function Name: CtSgwDelPortMapping
 *
 * Description  : Delete a specific port mapping rule according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the port mapping rule to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwDelPortMapping(CtSgwObjPath_t path)
{
    int ret = CTSGW_NOK;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/Config/PortMapping",
                               "com.ctc.igd1.ObjectManager",
                               "DeleteObject",
                               g_variant_new ("o", path.str),
                               NULL,
                               -1);


    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);

}


/*
 * Function Name: CtSgwSetPortMapping
 *
 * Description  : Set a specific port mapping rule according to the object path
 *
 * Parameter:
 *      obj <IN>: A CtSgwPortMapping_t struct containing the rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwSetPortMapping(CtSgwPortMapping_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail (obj != NULL, CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "path",
                           g_variant_new_object_path (obj->path.str));
    
    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_boolean (obj->Enable));

    g_variant_builder_add (builder,
                           "{sv}",
                           "LeaseDuration",
                           g_variant_new_uint32 (obj->LeaseDuration));

    g_variant_builder_add (builder,
                           "{sv}",
                           "RemoteHost",
                           g_variant_new_string (obj->RemoteHost));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ExternalPort",
                           g_variant_new_uint32 (obj->ExternalPort));

    g_variant_builder_add (builder,
                           "{sv}",
                           "InternalPort",
                           g_variant_new_uint32 (obj->InternalPort));

    g_variant_builder_add (builder,
                           "{sv}",
                           "PortMappingProtocol",
                           g_variant_new_string (obj->PortMappingProtocol));

    g_variant_builder_add (builder,
                           "{sv}",
                           "InternalClient",
                           g_variant_new_string (obj->InternalClient));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Description",
                           g_variant_new_string (obj->Description));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     obj->path.str,
                                     "com.ctc.igd1.PortMapping",
                                     value);

    g_variant_unref (value);
    
    return (ret == 0) ? CTSGW_OK : CTSGW_NOK;
}

#if 0
int ctsgw_usbRegister(CtUsbDevType type)
{
    // TODO:
}

int ctSgw_usbUnregister(void)
{
    // TODO:
}

int ctSgw_usbLock(int devId)
{
    // TODO:
}

int ctSgw_usbUnlock(int devId)
{
    // TODO:
}

int ctSgw_usbOpen(int devId, int *handle)
{
    // TODO:
}

int ctSgw_usbDataAvailable(int handle)
{
    // TODO:
}

int ctSgw_usbRead(int handle, void *buf, size_t *count, int timeout)
{
    // TODO:
}

int ctSgw_usbWrite(int handle, const void *buf, size_t *count)
{
    // TODO:
}

int ctSgw_usbSetSerial(int handle, const CtUsbSerialCfg *serialCfg)
{
    // TODO:
}

int ctSgw_usbClose(int handle)
{
    // TODO:
}

int CtSgw_USBMount(guint32 devid, char mount_path[MAX_PATH_LEN+1])
{
    return -1;

}

int CtSgw_USBUnMount(char mount_path[MAX_PATH_LEN+1])
{
    return -1;
}
#endif


/*
 * Function Name: CtSgw_GetUSBDeviceObjs
 *
 * Description  : Return all the usb device
 *
 * Parameter:
 *    objs <OUT>:   A CtSgw_USBDevice_t array to contain all the
 *                  usb device object. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgw_GetUSBDeviceObjs(CtSgw_USBDevice_t **objs, int *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val;
    guint16          u16_val;
    CtSgw_USBDevice_t      *entryList = NULL;
    CtSgw_USBDevice_t      *pEntry = NULL;

    g_return_val_if_fail ((count == NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/usb/devices",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgw_USBDevice_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_free (interfaceName);
            
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "DeviceType") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT16, &u16_val);
                    pEntry->DeviceType = u16_val;
                }
                else if (g_strcmp0 (key, "DeviceId") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->DeviceId = u32_val;
                }
                else if (g_strcmp0 (key, "DeviceName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DeviceName, str_val);
                    g_free (str_val);
                }
                // TODO: should we process fsinfo struct ?

                g_free (key);
                g_variant_unref (propertyValue);
            }

            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }

        g_free (pathName);
        g_variant_unref (interfaceDict);
        
        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgw_GetUSBDevice
 *
 * Description  : Return a specific usb device according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific usb device.
 *             obj <OUT>:   A CtSgw_USBDevice_t struct to contain the usb device.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_GetUSBDevice(CtSgwObjPath_t path, CtSgw_USBDevice_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val;
    guint16          u16_val;
    CtSgw_USBDevice_t      *pEntry = obj;

    g_return_val_if_fail ((obj == NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/usb/devices",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);
    
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);

    ret = CTSGW_NOK;
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
        
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "DeviceType") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT16, &u16_val);
                    pEntry->DeviceType = u16_val;
                }
                else if (g_strcmp0 (key, "DeviceId") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->DeviceId = u32_val;
                }
                else if (g_strcmp0 (key, "DeviceName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DeviceName, str_val);
                    g_free (str_val);
                }
                // TODO: should we process fsinfo struct ?

                g_free (key);
                g_variant_unref (propertyValue);
            }
            
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }

        g_free (pathName);
        g_variant_unref (interfaceDict);

        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return ret;
}


/*
 * Function Name: CtSgw_SetNASConfig
 *
 * Description  : Set the NAS configuration
 *
 * Parameter:
 *      obj <IN>: CtSgw_NASConfig_t struct containing the NAS information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_SetNASConfig(CtSgw_NASConfig_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    GVariant *macList = NULL;
    int ret = -1;
    int i = 0;

    g_return_val_if_fail (( obj != NULL ), CTSGW_NOK );
    builder = g_variant_builder_new (G_VARIANT_TYPE ("as"));
    for (i = 0; i < NAS_ACL_LIST_LEN; ++i)
    {
        if (strlen (obj->MACList[i]) > 0)
            g_variant_builder_add (builder, FORMAT_STRING, obj->MACList[i]);
    }
    
    macList = g_variant_new ("as", builder);
    g_variant_builder_unref (builder);

    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "ACLMode",
                           g_variant_new_uint16 (obj->ACLMode));

    g_variant_builder_add (builder,
                           "{sv}",
                           "MACList",
                           macList);

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     "/com/ctc/igd1/nas",
                                     "com.ctc.igd1.NASConfig",
                                     value);

    g_variant_unref (value);
    g_variant_unref (macList);
    
    return ((ret == 0) ? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgw_GetNASConfig
 *
 * Description  : Return the NAS configuration
 *
 * Parameter:
 *             obj <OUT>:   A CtSgw_NASConfig_t struct to contain the nas information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_GetNASConfig(CtSgw_NASConfig_t *obj)
{
    GVariant *dict = NULL;
    GVariant *value = NULL;
    GVariantIter iter;
    gchar   *key;
    guint16  i16_val;
    int ret = -1;

    g_return_val_if_fail (( obj != NULL ), CTSGW_NOK );
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Config/QoS/UplinkQoS",
                                   "com.ctc.igd1.NASConfig",
                                   &dict);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);

    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "ACLMode") == 0)
        {
            g_variant_get (value, FORMAT_UINT16, &i16_val);
            obj->ACLMode = i16_val;
        }
        else if (g_strcmp0 (key, "MACList") == 0)
        {
            GVariantIter *iterSub;
            gchar   *str;
            gint32   i = 0;

            g_variant_get (value, "as", &iterSub);
            while (g_variant_iter_loop(iterSub, FORMAT_STRING, &str))
            {
                g_stpcpy (obj->MACList[i], str);
                ++i;
            }
            g_variant_iter_free (iterSub);
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgw_NAS_GetFileNum
 *
 * Description  : Return the file number of a specified folder.
 *
 * Parameter:
 *     foldername <IN>:   The folder name.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_GetFileNum(char foldername[MAX_PATH_LEN+1])
{
    gint32 ret = -1;
    GVariant *fileNum = NULL;
    guint32 num = 0;

    g_return_val_if_fail (!IS_EMPTY_STRING(foldername), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/nas",
                               "com.ctc.igd1.NASAccess",
                               "GetFileNum",
                               g_variant_new ("(s)", foldername),
                               &fileNum,
                               -1);
    g_return_val_if_fail (ret == 0, CTSGW_NOK);
    g_variant_get (fileNum, FORMAT_UINT32, &num);
    g_variant_unref (fileNum);

    return num;
}


/*
 *      dest <IN>:  The destination address of the wan ping testing
 * Function Name: CtSgw_NAS_ListFolder
 *
 * Description  : List all the files and folders in a specified folder.
 *
 * Parameter:
 *     foldername  <IN>:   The folder name.
 *     startIndex  <IN>:   The start index of folder file.
 *       endIndex  <IN>:   The end index of folder file.
 *       fileList <OUT>:  The entries represent the files and folders.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_ListFolder(char *folderName, guint32 startIndex, guint32 endIndex, CtSgw_FileEntry_t **fileList)
{
    GVariant     *result;
    GVariantIter iter;
    CtSgw_FileEntry_t   *entryList = NULL;
    CtSgw_FileEntry_t   *entry = NULL;
    gchar       *f_name;
    gchar       *f_foldername;
    gboolean     f_isfolder;
    guint32      f_size;
    gchar       *f_modtime;
    gint32   num = 0;
    gint32   i = 0;
    int ret = -1;

    g_return_val_if_fail (folderName != NULL, CTSGW_NOK);
    g_return_val_if_fail ((startIndex < endIndex) && (startIndex >= 1 ), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/nas",
                               "com.ctc.igd1.NASAccess",
                               "ListFolder",
                               g_variant_new ("(suu)", folderName, startIndex, endIndex),
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    if (result == NULL)
        return CTSGW_NOK;

    num = g_variant_n_children (result);
    if (num <= 0 || num >= 20000)
    {
        g_variant_unref (result);
        return CTSGW_NOK;
    }
    
    entryList = g_try_new0(CtSgw_FileEntry_t, num);
    if (entryList == NULL)
    {
        g_variant_unref (result);
        return CTSGW_NOK;
    }

    i = 0;
    g_variant_iter_init (&iter, result);
    while (g_variant_iter_next(&iter, "(ssbus)", &f_name, &f_foldername, &f_isfolder, &f_size, &f_modtime))
    {
        entry = entryList + i;
        g_stpcpy (entry->FileName, f_name);
        g_stpcpy (entry->PhysicalFolderName, f_foldername);
        entry->IsFolder = f_isfolder;
        entry->FileSize = f_size;
        g_stpcpy (entry->ModifiedTime, f_modtime);

        g_free (f_name);
        g_free (f_foldername);
        g_free (f_modtime);
    }

    g_variant_unref (result);
    *fileList = entryList;

    return CTSGW_OK;
}


/*
 * Function Name: CtSgw_NAS_CreateFolter
 *
 * Description  : Create a folder with the specified name.
 *
 * Parameter:
 *     foldername  <IN>:   The folder name.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_CreateFolter(gchar *folderName)
{
    gint32 ret = -1;

    g_return_val_if_fail ((folderName != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/nas",
                               "com.ctc.igd1.NASAccess",
                               "CreateFolder",
                               g_variant_new ("(s)", folderName),
                               NULL,
                               -1);

    return (ret == 0) ? CTSGW_OK : CTSGW_NOK;
}


/*
 * Function Name: CtSgw_NAS_ReName
 *
 * Description  : Change the name of a file/folder.
 *
 * Parameter:
 *     oldName  <IN>:   The old name.
 *     newName  <IN>:   The new name.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_ReName(gchar *oldName, gchar *newName)
{
    gint32 ret = -1;

    g_return_val_if_fail(!IS_EMPTY_STRING(oldName), CTSGW_NOK);
    g_return_val_if_fail(!IS_EMPTY_STRING(newName), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/nas",
                               "com.ctc.igd1.NASAccess",
                               "Rename",
                               g_variant_new ("(ss)", oldName, newName),
                               NULL,
                               -1);

    return (ret == 0) ? CTSGW_OK : CTSGW_NOK;
}


/*
 * Function Name: CtSgw_NAS_Remove
 *
 * Description  : Remove a file/folder.
 *
 * Parameter:
 *     name  <IN>:   The file/folder name.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_Remove(gchar *name)
{
    gint32 ret = -1;

    g_return_val_if_fail(!IS_EMPTY_STRING(name), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/nas",
                               "com.ctc.igd1.NASAccess",
                               "Remove",
                               g_variant_new ("(s)", name),
                               NULL,
                               -1);

    return (ret == 0) ? CTSGW_OK : CTSGW_NOK;
}

/*
 * Function Name: CtSgw_NAS_Move
 *
 * Description  : Move a file/folder to another location.
 *
 * Parameter:
 *        filename  <IN>:   The source location.
 *  destFolderName  <IN>:   The destination location.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_Move(gchar *filename, char *destFolderName)
{
    gint32 ret = -1;

    g_return_val_if_fail(!IS_EMPTY_STRING(filename), CTSGW_NOK);
    g_return_val_if_fail(!IS_EMPTY_STRING(destFolderName), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/nas",
                               "com.ctc.igd1.NASAccess",
                               "Move",
                               g_variant_new ("(ss)", filename, destFolderName),
                               NULL,
                               -1);

    return (ret == 0) ? CTSGW_OK : CTSGW_NOK;
}


/*
 * Function Name: CtSgw_NAS_Copy
 *
 * Description  : Copy a file/folder to another location.
 *
 * Parameter:
 *            name  <IN>:   The source file name.
 *  destFolderName  <IN>:   The destination file name.
 *
 * Return:   transactionId on sucess, -1 on error.
 *
 */
int CtSgw_NAS_Copy(gchar *name, gchar *destFolderName)
{
    gint32 ret = -1;
    GVariant  *result = NULL;
    guint32 transId = 0;

    g_return_val_if_fail(!IS_EMPTY_STRING(name), CTSGW_NOK);
    g_return_val_if_fail(!IS_EMPTY_STRING(destFolderName), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/nas",
                               "com.ctc.igd1.NASAccess",
                               "Copy",
                               g_variant_new ("(ss)", name, destFolderName),
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    if (result != NULL)
    {
        g_variant_unref (result);
        g_variant_get (result, FORMAT_UINT32, &transId);
        return transId;
    }

    return CTSGW_NOK;
}


/*
 * Function Name: CtSgw_NAS_GetCopyProgress
 *
 * Description  : Get the copy progress.
 *
 * Parameter:
 *      transactionId  <IN>:   The transactionId of the copy progress.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_GetCopyProgress(guint32 transactionId)
{
    gint32 ret = -1;

    // TODO: how to define return value and its type.
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/nas",
                               "com.ctc.igd1.NASAccess",
                               "GetCopyProgress",
                               g_variant_new_uint32 (transactionId),
                               NULL,
                               -1);

    return ret;
}

/***************************** Private Function **************************/
static gint32 ctSgw_wanGetL2tpTunnelObjs(CtSgwL2TPConn_t **objs, gint32 *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    guint32          u32_val = 0;
    CtSgwL2TPConn_t      *entryList = NULL;
    CtSgwL2TPConn_t      *pEntry = NULL;

    g_return_val_if_fail ((count != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/VPN/L2TP/Connection",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgwL2TPConn_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "ServerIPAddr") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->ServerIPAddr, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "UserName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->UserName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Password") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Password, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "TunnelName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->TunnelName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Status") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_UINT32, &u32_val);
                    pEntry->Status = u32_val;
                }
                else if (g_strcmp0 (key, "IPAddrDomainList") == 0)
                {
                    GVariantIter *iterSub;
                    gchar   *str;
                    gint32   i = 0;

                    g_variant_get (propertyValue, "as", &iterSub);
                    while (g_variant_iter_loop(iterSub, "s", &str))
                    {
                        g_stpcpy (pEntry->IPAddrDomainList[i], str);
                        ++i;
                    }
                    g_variant_iter_free (iterSub);
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }

            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }

        g_free (pathName);
        g_variant_unref(interfaceDict);
        
        ++pEntry;
    }

    g_variant_unref(result);

    return CTSGW_OK;
}
/************************************ End of Private function ******************************/


/*
 * Function Name: ctSgw_wanCreateL2tpTunnel
 *
 * Description  : Create WAN side L2TP VPN tunnel.
 *
 * Parameter:
 *      serverIpAddr  <IN>:   L2TP Server address
 *          username  <IN>:   L2TP server username
 *          password  <IN>:   L2TP server password
 *        tunnelName <OUT>:   L2TP tunnel name
 *           nameLen  <IN>:   Buffer length of tunnel name
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int ctSgw_wanCreateL2tpTunnel(const char *serverIpAddr, const char *username, const char *password, char *tunnelName, int len)
{
    // TODO: How to get the tunnel Name ?

    GVariant *objPath = NULL;
    GVariant *value = NULL;
    GVariantBuilder *builder;
    gchar *path_str = NULL;
    int ret = -1;
    
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/VPN/L2TP/Connection",
                               "com.ctc.igd1.ObjectManager",
                               "AddObject",
                               NULL,
                               &objPath,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_variant_get (objPath, FORMAT_PATH, &path_str);

    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "path",
                           g_variant_new_object_path (path_str));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ServerIPAddr",
                           g_variant_new_string (serverIpAddr));

    g_variant_builder_add (builder,
                           "{sv}",
                           "UserName",
                           g_variant_new_string (username));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Password",
                           g_variant_new_string (password));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     path_str,
                                     "com.ctc.igd1.L2TPConnection",
                                     value);

    g_variant_unref (value);
    g_variant_unref (objPath);
    g_free (path_str);

    return (ret == 0) ? CTSGW_OK : CTSGW_NOK;

}


/*
 * Function Name: ctSgw_wanRemoveL2tpTunnel
 *
 * Description  : Remove the tunnel of the given name
 *
 * Parameter:
 *      tunnelName  <IN>:   The tunnel name.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int ctSgw_wanRemoveL2tpTunnel(const char *tunnelName)
{
    CtSgwL2TPConn_t *objs = NULL;
    CtSgwL2TPConn_t *pEntry = NULL;
    gchar      *pathName = NULL;
    gint32      count = 0;
    gint32      i = 0;
    gint32      ret = 0;
    
    ret = ctSgw_wanGetL2tpTunnelObjs(&objs, &count);
    g_return_val_if_fail ((ret == CTSGW_OK), CTSGW_NOK);

    pEntry = objs;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 (pEntry->TunnelName, tunnelName) == 0)
        {
            pathName = g_strdup (pEntry->path.str);
            break;
        }

        ++pEntry;
    }

    g_free (objs);

    g_return_val_if_fail (!IS_EMPTY_STRING(pathName), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/VPN/L2TP/Connection",
                               "com.ctc.igd1.ObjectManager",
                               "DeleteObject",
                               g_variant_new ("o", pathName),
                               NULL,
                               -1);

    g_free (pathName);
    g_return_val_if_fail ((ret ==0), CTSGW_NOK);

    return CTSGW_OK;
}


/*
 * Function Name: ctSgw_wanAttachL2tpTunnel
 *
 * Description  : Attach the data flow to L2TP VPN tunnel
 *
 * Parameter:
 *    tunnelName  <IN>:   The tunnel name.
 *    ipAddrList  <IN>:   List of the IP addresses need to be attached to the L2TP tunnel whose name is tunnelName 
 *     ipAddrNum  <IN>:   Number of IP addresses in the ipAddrList
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int ctSgw_wanAttachL2tpTunnel(const char *tunnelName, const gchar *ipAddrList, int ipAddrNum)
{
    GVariant *value = NULL;
    GVariant *ipaddr = NULL;
    GVariantBuilder *builder;
    GVariantBuilder *subuilder;
    CtSgwL2TPConn_t *objs = NULL;
    CtSgwL2TPConn_t *pEntry = NULL;
    const gchar  *pIPAddr = NULL;
    gint32      count = 0;
    gint32      i = 0;
    gint32      ret = 0;
    
    ret = ctSgw_wanGetL2tpTunnelObjs(&objs, &count);
    g_return_val_if_fail ((ret == CTSGW_OK), CTSGW_NOK);

    pEntry = objs;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 (pEntry->TunnelName, tunnelName) == 0)
        {
            break;
        }

        ++pEntry;
    }    

    // Free the object list if can not find the entry.
    if (i >= count)
    {
        g_free (objs);
        return CTSGW_NOK;
    }

    g_return_val_if_fail (pEntry != NULL, CTSGW_NOK);

    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "ServerIPAddr",
                           g_variant_new_string (pEntry->ServerIPAddr));

    g_variant_builder_add (builder,
                           "{sv}",
                           "UserName",
                           g_variant_new_string (pEntry->UserName));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Password",
                           g_variant_new_string (pEntry->Password));

    g_variant_builder_add (builder,
                           "{sv}",
                           "TunnelName",
                           g_variant_new_string (pEntry->TunnelName));

    subuilder = g_variant_builder_new (G_VARIANT_TYPE ("as"));
    for (i = 0; i < L2TP_ADDR_DOMAIN_NUM; ++i)
    {
        if (strlen (pEntry->IPAddrDomainList[i]) > 0)
            g_variant_builder_add (subuilder, FORMAT_STRING, pEntry->IPAddrDomainList[i]);
    }

    pIPAddr = ipAddrList;
    for (i = 0; i < ipAddrNum; ++i)
    {
        g_variant_builder_add (subuilder, FORMAT_STRING, pIPAddr);
        ++pIPAddr;
    }
    ipaddr = g_variant_builder_end (subuilder);
    g_variant_builder_unref (subuilder);
    
    g_variant_builder_add (builder,
                           "{sv}",
                           "IPAddrDomainList",
                           ipaddr);
    
    g_variant_unref (ipaddr);
    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     pEntry->path.str,
                                     "com.ctc.igd1.L2TPConnection",
                                     value);

    g_variant_unref (value);
    g_free (objs);

    return ((ret == 0) ? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: ctSgw_wanDetachL2tpTunnel
 *
 * Description  : Detach the data flow from L2TP VPN tunnel
 *
 * Parameter:
 *    tunnelName  <IN>:   The tunnel name.
 *    ipAddrList  <IN>:   List of the IP addresses need to be detached from the L2TP tunnel whose name is tunnelName 
 *     ipAddrNum  <IN>:   Number of IP addresses in the ipAddrList
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int ctSgw_wanDetachL2tpTunnel(const char *tunnelName, const char *ipAddrList, int ipAddrNum)
{
    GVariant *value = NULL;
    GVariant *ipaddr = NULL;
    GVariantBuilder *builder;
    GVariantBuilder *subuilder;
    CtSgwL2TPConn_t *objs = NULL;
    CtSgwL2TPConn_t *pEntry = NULL;
    const char      *pIPAddr = NULL;
    gboolean    found = FALSE;  
    gint32      count = 0;
    gint32      i = 0;
    gint32      ret = 0;
    
    ret = ctSgw_wanGetL2tpTunnelObjs(&objs, &count);
    g_return_val_if_fail ((ret == CTSGW_OK), CTSGW_NOK);

    pEntry = objs;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 (pEntry->TunnelName, tunnelName) == 0)
        {
            break;
        }

        ++pEntry;
    }    

    // Free the object list if can not find the entry.
    if (i >= count)
    {
        g_free (objs);
        return CTSGW_NOK;
    }

    g_return_val_if_fail (pEntry != NULL, CTSGW_NOK);

    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "ServerIPAddr",
                           g_variant_new_string (pEntry->ServerIPAddr));

    g_variant_builder_add (builder,
                           "{sv}",
                           "UserName",
                           g_variant_new_string (pEntry->UserName));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Password",
                           g_variant_new_string (pEntry->Password));

    g_variant_builder_add (builder,
                           "{sv}",
                           "TunnelName",
                           g_variant_new_string (pEntry->TunnelName));

    subuilder = g_variant_builder_new (G_VARIANT_TYPE ("as"));
    for (i = 0; i < L2TP_ADDR_DOMAIN_NUM; ++i)
    {
        found = FALSE;
        if (strlen (pEntry->IPAddrDomainList[i]) <= 0)
            continue;

        pIPAddr = ipAddrList;
        for (i = 0; i < ipAddrNum; ++i)
        {
            if (g_strcmp0(pIPAddr, pEntry->IPAddrDomainList[i]) == 0)
            {
                found = TRUE;
                break;
            }

            ++pIPAddr;
        }
        
        if (found) continue;
        
        g_variant_builder_add (subuilder, FORMAT_STRING, pEntry->IPAddrDomainList[i]);
    }
    ipaddr = g_variant_builder_end (subuilder);
    g_variant_builder_unref (subuilder);
    
    g_variant_builder_add (builder,
                           "{sv}",
                           "IPAddrDomainList",
                           ipaddr);

    g_variant_unref (ipaddr);
    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     pEntry->path.str,
                                     "com.ctc.igd1.L2TPConnection",
                                     value);

    g_free (objs);
    g_variant_unref (value);
    
    return ((ret == 0) ? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: ctSgw_wanGetL2tpTunnelStatus
 *
 * Description  : Query the status of wan side L2TP tunnel
 *
 * Parameter:
 *    tunnelName  <IN>:   The tunnel name.
 *  tunnelstatus <OUT>:   tunnel status, 0 on normal, 1 on abnormal
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int ctSgw_wanGetL2tpTunnelStatus(const char *tunnelName, int *tunnelStatus)
{
    CtSgwL2TPConn_t *objs = NULL;
    CtSgwL2TPConn_t *pEntry = NULL;
    gint32      count = 0;
    gint32      i = 0;
    gint32      ret = 0;
    
    ret = ctSgw_wanGetL2tpTunnelObjs(&objs, &count);
    g_return_val_if_fail ((ret == CTSGW_OK), CTSGW_NOK);

    pEntry = objs;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 (pEntry->TunnelName, tunnelName) == 0)
        {
            break;
        }

        ++pEntry;
    }    

    // Free the object list if can not find the entry.
    if (i >= count)
    {
        g_free (objs);
        return CTSGW_NOK;
    }

    g_return_val_if_fail (pEntry != NULL, CTSGW_NOK);
    *tunnelStatus = pEntry->Status;

    // Free all the entries
    g_free (objs);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgw_AddDNSTunnel
 *
 * Description  : Add DNS tunnel with the domain name and server
 *
 * Parameter:
 *    domain_name  <IN>:   The dns domain name.
 *          server <IN>:   Server address.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_AddDNSTunnel(const char *domain_name, const char *server)
{
    GVariant *objPath = NULL;
    GVariant *value = NULL;
    GVariantBuilder *builder;
    gchar *path_str = NULL;
    int ret = -1;
    
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/dns",
                               "com.ctc.igd1.ObjectManager",
                               "AddObject",
                               NULL,
                               &objPath,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_variant_get (objPath, FORMAT_PATH, &path_str);

    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "path",
                           g_variant_new_object_path (path_str));

    g_variant_builder_add (builder,
                           "{sv}",
                           "ServerIP",
                           g_variant_new_string (server));

    g_variant_builder_add (builder,
                           "{sv}",
                           "DomainName",
                           g_variant_new_string (domain_name));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     path_str,
                                     "com.ctc.igd1.DNSTunnel",
                                     value);

    g_variant_unref (value);
    g_variant_unref (objPath);
    g_free (path_str);

    return (ret == 0) ? CTSGW_OK : CTSGW_NOK;
}


/*
 * Function Name: CtSgw_DelDNSTunnel
 *
 * Description  : Delete a DNS tunnel with the specified domain name.
 *
 * Parameter:
 *    domain_name  <IN>:   The dns domain name.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_DelDNSTunnel(const char *domain_name)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *delPath = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    CtSgwDNSTunnel_t      *entryList = NULL;
    CtSgwDNSTunnel_t      *pEntry = NULL;
    gint32           i = 0;

    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/dns",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);

    entryList = g_try_new0 (CtSgwDNSTunnel_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "ServerIP") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->ServerIP, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "DomainName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->DomainName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "path") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->path.str, str_val);
                    g_free (str_val);
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }

            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }

        g_free (pathName);
        g_variant_unref (interfaceDict);
        
        ++pEntry;
    }

    g_variant_unref (result);

    pEntry = entryList;
    for (i = 0; i < num; ++i)
    {
        if (g_strcmp0(pEntry->DomainName, domain_name) == 0)
        {
            delPath = g_strdup (pEntry->path.str);
            break;
        }
    }

    // Free all the memory.
    g_free (entryList);

    g_return_val_if_fail (!(IS_EMPTY_STRING(delPath)), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/dns",
                               "com.ctc.igd1.ObjectManager",
                               "DeleteObject",
                               g_variant_new ("o", delPath),
                               NULL,
                               -1);
    g_free (delPath);

    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgw_SetFtpServer
 *
 * Description  : Set the ftp server configuration.
 *
 * Parameter:
 *     obj  <IN>: A CtSgw_FTPServerConfig_t struct with ftp server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_SetFtpServer(CtSgw_FTPServerConfig_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_boolean (obj->Enable));

    g_variant_builder_add (builder,
                           "{sv}",
                           "AllowAnonymous",
                           g_variant_new_boolean (obj->AllowAnonymous));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     "/com/ctc/igd1/ftpserver",
                                     "com.ctc.igd1.FTPServer",
                                     value);

    g_variant_unref (value);
    
    return (ret == 0) ? CTSGW_OK : CTSGW_NOK;
}


/*
 * Function Name: CtSgw_SetFtpServer
 *
 * Description  : Get the ftp server configuration.
 *
 * Parameter:
 *     obj <OUT>: A CtSgw_FTPServerConfig_t struct to contain ftp server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_GetFTPServer(CtSgw_FTPServerConfig_t *obj)
{
    GVariantIter iter;
    GVariant *dict = NULL;
    gchar   *key;
    GVariant *value = NULL;
    gboolean     bol_val;
    int ret = -1;
   
    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/ftpserver",
                                   "com.ctc.igd1.FTPServer",
                                   &dict);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    
    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "Enable") == 0)
        {
            g_variant_get (value, FORMAT_BOOL, &bol_val);
            obj->Enable = bol_val;
        }
        else if (g_strcmp0 (key, "AllowAnonymous") == 0)
        {
            g_variant_get (value, FORMAT_BOOL, &bol_val);
            obj->AllowAnonymous = bol_val;
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgw_GetFTPAccountObjs
 *
 * Description  : Return all the ftp account
 *
 * Parameter:
 *    objs <OUT>:   A pointer to CtSgw_FTPAccount_t array to contain all
 *                  the ftp account object. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgw_GetFTPAccountObjs(CtSgw_FTPAccount_t **objs, int *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    CtSgw_FTPAccount_t      *entryList = NULL;
    CtSgw_FTPAccount_t      *pEntry = NULL;

    g_return_val_if_fail ((count != NULL), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/ftpserver/Accounts",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgw_FTPAccount_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "UserName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->UserName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Password") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Password, str_val);
                    g_free (str_val);
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }

            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }

        g_free (pathName);
        g_variant_unref (interfaceDict);

        ++pEntry;
    }

    g_variant_unref (result);
    
    return CTSGW_OK;
}


/*
 * Function Name: CtSgw_GetFTPAccount
 *
 * Description  : Return a specific ftp account according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific ftp account.
 *             obj <OUT>:   A CtSgw_FTPAccount_t struct to contain the ftp account rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_GetFTPAccount(CtSgwObjPath_t path, CtSgw_FTPAccount_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    CtSgw_FTPAccount_t      *pEntry = obj;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/ftpserver/Accounts",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);

    ret = CTSGW_NOK;
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
    
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "UserName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->UserName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Password") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Password, str_val);
                    g_free (str_val);
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }

            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return ret;

}


/*
 * Function Name: CtSgw_AddFtpAccount
 *
 * Description  : add a ftp account
 *
 * Parameter:
 *      obj <IN>: A CtSgw_FTPAccount_t struct containing the ftp account.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_AddFtpAccount(CtSgw_FTPAccount_t *obj)
{
    GVariant *objPath = NULL;
    GVariant *value = NULL;
    GVariantBuilder *builder;
    gchar *path_str = NULL;
    int ret = -1;
    
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "com.ctc.igd1.FTPAccount",
                               "com.ctc.igd1.ObjectManager",
                               "AddObject",
                               NULL,
                               &objPath,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_variant_get (objPath, FORMAT_PATH, &path_str);

    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "path",
                           g_variant_new_object_path (path_str));

    g_variant_builder_add (builder,
                           "{sv}",
                           "UserName",
                           g_variant_new_string (obj->UserName));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Password",
                           g_variant_new_string (obj->Password));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     path_str,
                                     "com.ctc.igd1.FTPAccount",
                                     value);

    g_variant_unref (value);
    g_variant_unref (objPath);
    g_free (path_str);

    return (ret == 0) ? CTSGW_OK : CTSGW_NOK;
}


/*
 * Function Name: CtSgw_DelFtpAccount
 *
 * Description  : Delete a specific ftp account according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the ftp account to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_DelFtpAccount(CtSgwObjPath_t path)
{
    int ret = CTSGW_NOK;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "com.ctc.igd1.FTPAccount",
                               "com.ctc.igd1.ObjectManager",
                               "DeleteObject",
                               g_variant_new ("o", path.str),
                               NULL,
                               -1);


    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgw_GetSambaServer
 *
 * Description  : Get the samba server configuration.
 *
 * Parameter:
 *     obj <OUT>: A CtSgw_SambaServerConfig_t struct to contain samba server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_GetSambaServer(CtSgw_SambaServerConfig_t *obj)
{
    GVariantIter iter;
    GVariant *dict = NULL;
    gchar   *key;
    GVariant *value = NULL;
    gboolean     bol_val;
    int ret = -1;

    g_return_val_if_fail (obj != NULL, CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/SambaServer",
                                   "com.ctc.igd1.SambaServer",
                                   &dict);
    if (ret < 0)
    {
        memset (obj, '\0', sizeof(CtSgw_SambaServerConfig_t));
        return CTSGW_NOK;
    }
    
    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "Enable") == 0)
        {
            g_variant_get (value, FORMAT_BOOL, &bol_val);
            obj->Enable = bol_val;
        }
        else if (g_strcmp0 (key, "AllowAnonymous") == 0)
        {
            g_variant_get (value, FORMAT_BOOL, &bol_val);
            obj->AllowAnonymous = bol_val;
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgw_SetSambaServer
 *
 * Description  : Set the samba server configuration.
 *
 * Parameter:
 *     obj  <IN>: A CtSgw_SambaServerConfig_t struct with samba server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_SetSambaServer(CtSgw_SambaServerConfig_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;

    g_return_val_if_fail (obj != NULL, CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_boolean (obj->Enable));

    g_variant_builder_add (builder,
                           "{sv}",
                           "AllowAnonymous",
                           g_variant_new_boolean (obj->AllowAnonymous));

    
    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     "/com/ctc/igd1/SambaServer",
                                     "com.ctc.igd1.SambaServer",
                                     value);

    g_variant_unref (value);
    
    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgw_GetSambaAccountObjs
 *
 * Description  : Return all the samba account
 *
 * Parameter:
 *    objs <OUT>:   A pointer to CtSgw_SambaAccount_t array to contain all
 *                  the samba account object. The memory is allocated in
 *                  this function, but need to be freed by the caller.
 *
 *   count <OUT>:   The length of the array.
 *
 * Return:   0 on sucess, -1 on error..
 *
 */
int CtSgw_GetSambaAccountObjs(CtSgw_SambaAccount_t **objs, int *count)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    CtSgw_SambaAccount_t    *entryList = NULL;
    CtSgw_SambaAccount_t    *pEntry = NULL;

    g_return_val_if_fail (count != NULL, CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/SambaServer/Accounts",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num >= 0), CTSGW_NOK);

    *count = num;
    if (objs == NULL)
        return CTSGW_OK;
    
    if (num == 0)
    {
        objs = NULL;
        return CTSGW_OK;
    }

    entryList = g_try_new0 (CtSgw_SambaAccount_t, num);
    g_return_val_if_fail ((entryList != NULL), CTSGW_NOK);
    
    *objs = entryList;
    pEntry = entryList;
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "UserName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->UserName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Password") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Password, str_val);
                    g_free (str_val);
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }

            
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);
        ++pEntry;
    }

    g_variant_unref (result);

    return CTSGW_OK;
}


/*
 * Function Name: CtSgw_GetSambaAccount
 *
 * Description  : Return a specific samba account according to the object path
 *
 * Parameter:
 *             path <IN>:   The object path of the specific samba account.
 *             obj <OUT>:   A CtSgw_SambaAccount_t struct to contain the samba account rule.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_GetSambaAccount(CtSgwObjPath_t path, CtSgw_SambaAccount_t *obj)
{
    gint32           ret = -1;
    GVariant        *result = NULL;
    GVariant        *interfaceDict;
    GVariant        *propertyDict;
    GVariant        *propertyValue;
    GVariantIter     objIter;
    GVariantIter     interfaceIter;
    GVariantIter     propertyIter;
    gchar           *pathName = NULL;
    gchar           *interfaceName = NULL;
    gchar           *key = NULL;
    gint32           num = 0;
    gchar           *str_val = NULL;
    CtSgw_SambaAccount_t    *pEntry = obj;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "/com/ctc/igd1/SambaServer/Accounts",
                               "com.ctc.igd1.ObjectManager",
                               "GetManagedObjects",
                               NULL,
                               &result,
                               -1);

    g_return_val_if_fail ((result != NULL), CTSGW_NOK);
    num = g_variant_n_children (result);
    g_return_val_if_fail ((num > 0), CTSGW_NOK);
    
    // Result is of type a{oa{sa{sv}}}
    g_variant_iter_init (&objIter, result);
    while (g_variant_iter_next (&objIter, "{o@a{sa{sv}}}", &pathName, &interfaceDict))
    {
        if (g_strcmp0 (path.str, pathName) != 0)
        {
            g_free (pathName);
            g_variant_unref (interfaceDict);
            continue;
        }
        
        g_stpcpy (pEntry->path.str, pathName);
        g_variant_iter_init(&interfaceIter, interfaceDict);
        while (g_variant_iter_next(&interfaceIter, "{s@a{sv}}", &interfaceName, &propertyDict))
        {
            // TODO: Don't know how to process interfaceName, just ignore it for now
            g_variant_iter_init(&propertyIter, propertyDict);
            while (g_variant_iter_next(&propertyIter, "{sv}", &key, &propertyValue))
            {
                if (g_strcmp0 (key, "UserName") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->UserName, str_val);
                    g_free (str_val);
                }
                else if (g_strcmp0 (key, "Password") == 0)
                {
                    g_variant_get (propertyValue, FORMAT_STRING, &str_val);
                    g_stpcpy (pEntry->Password, str_val);
                    g_free (str_val);
                }

                g_free (key);
                g_variant_unref (propertyValue);
            }
            
            g_free (interfaceName);
            g_variant_unref (propertyDict);
        }
        
        g_free (pathName);
        g_variant_unref (interfaceDict);

        ret = CTSGW_OK;
        break;
    }

    g_variant_unref (result);

    return ret;
}


/*
 * Function Name: CtSgw_AddSambaAccount
 *
 * Description  : add a samba account
 *
 * Parameter:
 *      obj <IN>: A CtSgw_SambaAccount_t struct containing the samba account.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_AddSambaAccount(CtSgw_SambaAccount_t *obj)
{
    GVariant *objPath = NULL;
    GVariant *value = NULL;
    GVariantBuilder *builder;
    gchar *path_str = NULL;
    int ret = -1;
    
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "com.ctc.igd1.SambaAccount",
                               "com.ctc.igd1.ObjectManager",
                               "AddObject",
                               NULL,
                               &objPath,
                               -1);

    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    g_variant_get (objPath, FORMAT_PATH, &path_str);

    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "path",
                           g_variant_new_object_path (path_str));

    g_variant_builder_add (builder,
                           "{sv}",
                           "UserName",
                           g_variant_new_string (obj->UserName));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Password",
                           g_variant_new_string (obj->Password));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     path_str,
                                     "com.ctc.igd1.SambaAccount",
                                     value);

    g_variant_unref (value);
    g_variant_unref (objPath);
    g_free (path_str);

    return (ret == 0) ? CTSGW_OK : CTSGW_NOK;
}


/*
 * Function Name: CtSgw_DelSambaAccount
 *
 * Description  : Delete a specific samba account according to the object path
 *
 * Parameter:
 *     path <IN>: The object path of the samba account to delete.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_DelSambaAccount(CtSgwObjPath_t path)
{
    int ret = CTSGW_NOK;

    g_return_val_if_fail (!IS_EMPTY_STRING(path.str), CTSGW_NOK);
    ret = CtSgwDBusCallMethod ("com.ctc.igd1",
                               "com.ctc.igd1.SambaAccount",
                               "com.ctc.igd1.ObjectManager",
                               "DeleteObject",
                               g_variant_new ("o", path.str),
                               NULL,
                               -1);

    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgw_GetHttpServer
 *
 * Description  : Get the http server configuration.
 *
 * Parameter:
 *     obj <OUT>: A CtSgw_HttpServerConfig_t struct to contain http server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_GetHttpServer(CtSgw_HttpServerConfig_t *obj)
{
    GVariantIter iter;
    GVariant *dict = NULL;
    gchar   *key;
    GVariant *value = NULL;
    gchar    *str_val;
    gboolean  bol_val;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/HTTPServer",
                                   "com.ctc.igd1.HTTPServer",
                                   &dict);
    g_return_val_if_fail ((ret == 0), CTSGW_NOK);
    
    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "Enable") == 0)
        {
            g_variant_get (value, FORMAT_BOOL, &bol_val);
            obj->Enable = bol_val;
        }
        else if (g_strcmp0 (key, "AdminPasswd") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (obj->AdminPasswd, str_val);
            g_free (str_val);
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}


/*
 * Function Name: CtSgw_SetHttpServer
 *
 * Description  : Set the http server configuration.
 *
 * Parameter:
 *     obj  <IN>: A CtSgw_HttpServerConfig_t struct with http server configuration.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_SetHttpServer(CtSgw_HttpServerConfig_t *obj)
{
    GVariant *value = NULL;
    GVariantBuilder *builder = NULL;
    int ret = -1;

    g_return_val_if_fail ((obj != NULL), CTSGW_NOK);
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_boolean (obj->Enable));

    g_variant_builder_add (builder,
                           "{sv}",
                           "AdminPasswd",
                           g_variant_new_string (obj->AdminPasswd));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     "/com/ctc/igd1/HTTPServer",
                                     "com.ctc.igd1.HTTPServer",
                                     value);

    g_variant_unref (value);
    
    return ((ret == 0)? CTSGW_OK : CTSGW_NOK);
}
