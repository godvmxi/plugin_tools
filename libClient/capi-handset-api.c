#include <stdio.h>
#include <stdlib.h>
#include "ctsgw.h"
#include "capi-sys-service.h"
#include "capi-dbus-service.h"

#ifdef __cplusplus
extern "C" {
#endif


int ctSgw_lanGetDevBandwidth(const unsigned char *macAddr, int *usBandwidth, int *dsBandwidth, char *status)
{
    CtSgwLANHost_t  *objs = NULL;
    CtSgwLANHost_t  *pEntry = NULL;
    int     count = 0;
    int     ret = CTSGW_NOK;
    int     i = 0;

    g_return_val_if_fail (!IS_EMPTY_STRING(macAddr), CTSGW_NOK);
    g_return_val_if_fail ((usBandwidth != NULL), CTSGW_NOK);
    ret = CtSgwGetLANHostObjs(&objs, &count);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    pEntry = objs;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 (pEntry->MAC, (const char *)macAddr) == 0)
        {
            *usBandwidth = pEntry->USBandwidth;
            *dsBandwidth = pEntry->DSBandwidth;
            if (status != NULL)
            {
                g_stpcpy (status, STR_SUCCESS);
            }

            ret = CTSGW_OK;
            break;
        }

        ++ pEntry;
    }

    // If did not find the entry
    if (i >= count)
    {
        g_stpcpy (status, STR_FAIL);
        ret = CTSGW_NOK;
    }

    // Free the allocated memory
    g_free (objs);

    return ret;
}

int ctSgw_lanSetDevMaxBandwidth(const unsigned char *macAddr, int usBandwidth, int dsBandwidth, char *status)
{
    CtSgwLANHost_t  *objs = NULL;
    CtSgwLANHost_t  *pEntry = NULL;
    GVariant *value = NULL;
    GVariantBuilder *builder;
    gchar  *pathName = NULL;
    int     count = 0;
    int     ret = CTSGW_NOK;
    int     i = 0;

    g_return_val_if_fail (!IS_EMPTY_STRING(macAddr), CTSGW_NOK);
    ret = CtSgwGetLANHostObjs(&objs, &count);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    // Looking for the specific entry.
    pEntry = objs;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 (pEntry->MAC, (const char *)macAddr) == 0)
        {
            pathName = g_strdup (pEntry->path.str);
            ret = CTSGW_OK;
            g_stpcpy (status, STR_FAIL);
            break;
        }

        ++ pEntry;
    }

    // If did not find the entry
    if (IS_EMPTY_STRING(pathName))
    {
        g_stpcpy (status, STR_FAIL);
        ret = CTSGW_NOK;
    }

    // Free the allocated memory
    g_free (objs);

    g_return_val_if_fail ((ret == CTSGW_OK), ret);

    /* Now set the value */
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "MaxUSBandwidth",
                           g_variant_new_uint32 (usBandwidth));

    g_variant_builder_add (builder,
                           "{sv}",
                           "MaxDSBandwidth",
                           g_variant_new_uint32 (dsBandwidth));
    
    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     pathName,
                                     "com.ctc.igd1.LANHost",
                                     value);


    if (ret == 0)
    {
        g_stpcpy (status, STR_SUCCESS);
        ret = CTSGW_OK;
    }
    else
    {
        g_stpcpy (status, STR_FAIL);
        ret = CTSGW_NOK;
    }

    g_free (pathName);
    g_variant_unref (value);

    return ret;
}

int ctSgw_lanGetDevInfo(CtLanDevInfo **devInfoList, int *devNum, char *status)
{
    int ret = CTSGW_OK;
    CtSgwLANHost_t  *lanObj = NULL;
    CtSgwLANHost_t  *pLanEntry = NULL;
    CtLanDevInfo    *lanDev = NULL;
    CtLanDevInfo    *pDevEntry = NULL;
    int count = 0;
    int i = 0;

    ret = CtSgwGetLANHostObjs(&lanObj, &count);
    g_return_val_if_fail ((ret == CTSGW_OK), CTSGW_NOK);

    *devNum = count;
    if (count == 0)
    {
        g_stpcpy (status, STR_SUCCESS);
        *devInfoList = NULL;
        return CTSGW_OK;
    }

    lanDev = g_try_new0 (CtLanDevInfo, count);
    if (lanDev == NULL)
    {
        g_stpcpy (status, STR_FAIL);
        g_free (lanObj);
        return CTSGW_NOK;
    }

    *devInfoList = lanDev;
    pLanEntry = lanObj;
    pDevEntry = lanDev;
    for (i = 0; i < count; ++i)
    {
        g_stpcpy (pDevEntry->devName, pLanEntry->DevName);
        //pDevEntry->devType = pLanEntry->DevType;    // TODO: translate from char* and int
        //g_stpcpy (pDevEntry->macAddr, pLanEntry->MAC);    // TODO: How to translate it
        g_stpcpy (pDevEntry->ipAddr, pLanEntry->IP);
        pDevEntry->connType = pLanEntry->ConnectionType;
        pDevEntry->port = pLanEntry->Port;
        g_stpcpy (pDevEntry->brandName, pLanEntry->Brand);
        g_stpcpy (pDevEntry->osName, pLanEntry->OS);
        pDevEntry->onlineTime = pLanEntry->OnlineTime;

        ++pLanEntry;
        ++pDevEntry;
    }

    g_free (lanObj);
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_lanUpdateDevInfo(const CtLanDevInfo *devInfo, char *status)
{
    // TODO: No path or interface defined.
    
    return CTSGW_OK;
}

int ctSgw_lanGetDevInternetAccessBlacklist(unsigned char **macAddrList, int *macAddrNum, char *status)
{
#if 0
    CtSgwLANHost_t  *objs = NULL;
    CtSgwLANHost_t  *pEntry = NULL;
    unsigned char   *macList = NULL;
    int objLen = 0;
    int denyNum = 0;
    int i = 0;
    int ret = CTSGW_NOK;
    
    
    ret = CtSgwGetLANHostObjs(&objs, &objLen);
    if (ret != CTSGW_OK || objs == NULL)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    // Get the deny mac num
    denyNum = 0;
    pEntry = *objs;
    for (i = 0; i < objLen; ++i)
    {
        if (pEntry->DenyInternetAccess)
            ++denyNum;
    }

    *macAddrNum = denyNum;
    if (denyNum == 0)
    {
        g_stpcpy (status, STR_SUCCESS);
        return CTSGW_OK;
    }

    macList = g_try_new0 ((unsigned char [STR_LEN_24]), denyNum);
#endif
    
    return CTSGW_OK;
}

int ctSgw_lanGetDevStorageAccessBlacklist(unsigned char **macAddrList, int *macAddrNum, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_wanGetPPPoEAccount(char *pppoeAccount, char *status)
{
    // TODO: Don't know which interface to use.
    return CTSGW_OK;
}

int ctSgw_lanSetInternetAccessPermission(const char *macAddr, int internetAccess, char *status)
{
    CtSgwLANHost_t  *objs = NULL;
    CtSgwLANHost_t  *pEntry = NULL;
    gchar  *pathName = NULL;
    int     count = 0;
    int     ret = CTSGW_NOK;
    int     i = 0;

    g_return_val_if_fail (!IS_EMPTY_STRING(macAddr), CTSGW_NOK);
    ret = CtSgwGetLANHostObjs(&objs, &count);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    // Looking for the specific entry.
    pEntry = objs;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 (pEntry->MAC, macAddr) == 0)
        {
            pathName = g_strdup (pEntry->path.str);
            ret = CTSGW_OK;
            g_stpcpy (status, STR_FAIL);
            break;
        }

        ++ pEntry;
    }

    // If did not find the entry
    if (IS_EMPTY_STRING(pathName))
    {
        g_stpcpy (status, STR_FAIL);
        ret = CTSGW_NOK;
    }

    // Free the allocated memory
    g_free (objs);

    /* Now set the value */
    ret = CtSgwDBusSetProperty ("com.ctc.igd1",
                                 pathName,
                                 "com.ctc.igd1.LANHost",
                                 "DenyInternetAccess",
                                 g_variant_new_uint32 (internetAccess));


    if (ret == 0)
    {
        g_stpcpy (status, STR_FAIL);
        ret = CTSGW_OK;
    }
    else
    {
        g_stpcpy (status, STR_FAIL);
        ret = CTSGW_NOK;
    }

    g_free (pathName);

    return ret;
}

int ctSgw_lanSetStorageAccessPermission(const char *macAddr, int storageAccess, char *status)
{
    CtSgwLANHost_t  *objs = NULL;
    CtSgwLANHost_t  *pEntry = NULL;
    gchar  *pathName = NULL;
    int     count = 0;
    int     ret = CTSGW_NOK;
    int     i = 0;

    g_return_val_if_fail (!IS_EMPTY_STRING(macAddr), CTSGW_NOK);
    ret = CtSgwGetLANHostObjs(&objs, &count);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    // Looking for the specific entry.
    pEntry = objs;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 (pEntry->MAC, macAddr) == 0)
        {
            pathName = g_strdup (pEntry->path.str);
            ret = CTSGW_OK;
            g_stpcpy (status, STR_FAIL);
            break;
        }

        ++ pEntry;
    }

    // If did not find the entry
    if (IS_EMPTY_STRING(pathName))
    {
        g_stpcpy (status, STR_FAIL);
        ret = CTSGW_NOK;
    }

    // Free the allocated memory
    g_free(objs);
    g_return_val_if_fail ((ret == CTSGW_OK), ret);

    /* Now set the value */
    ret = CtSgwDBusSetProperty ("com.ctc.igd1",
                                 pathName,
                                 "com.ctc.igd1.LANHost",
                                 "DenyStorageAccess",
                                 g_variant_new_uint32 (storageAccess));


    if (ret == 0)
    {
        g_stpcpy (status, STR_SUCCESS);
        ret = CTSGW_OK;
    }
    else
    {
        g_stpcpy (status, STR_FAIL);
        ret = CTSGW_NOK;
    }

    g_free (pathName);

    return ret;
}

int ctSgw_sysGetCpuUsage(int *percent, char *status)
{
    CtSgwDeviceInfo_t info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(CtSgwDeviceInfo_t));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *percent = info.CPUUsage;
    g_stpcpy (status, STR_SUCCESS);
    return CTSGW_OK;
}

int ctSgw_sysGetMemUsage(int *percent, char *status)
{
    CtSgwDeviceInfo_t info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(CtSgwDeviceInfo_t));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *percent = info.MEMUsage;
    g_stpcpy (status, STR_SUCCESS);
    return CTSGW_OK;
}

int ctSgw_sysGetLoid(char *loid, char *status)
{
    CtSgwPONInfo_t info;
    int ret = CTSGW_NOK;

    memset (&info, '\0', sizeof(info));
    ret = CtSgwGetPONInfo(&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    if (loid != NULL)
        g_stpcpy (loid, info.LOID);
    
    g_stpcpy (status, STR_SUCCESS);
    return CTSGW_OK;
}

int ctSgw_sysPushWeb(int enable, int width, int height, int x, int y, char *url, int time, char *status)
{
    CtSgwPWConfig_t obj;
    int ret = CTSGW_NOK;

    memset (&obj, '\0', sizeof(obj));
    obj.Enable = enable;
    obj.Width = width;
    obj.Height = height;
    sprintf (obj.Place, "%d.%d", x, y);     // TODO: How to generate place ?
    g_stpcpy (obj.URL, url);
    sprintf(obj.Time, "%d", time);
    
    ret = CtSgwSetPW (&obj);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (status, STR_SUCCESS);
    return CTSGW_OK;
}

int ctSgw_getLanIpAddr(char *lanIpAddr, char *lanSubnetMask, char *ipv6LanAddr, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_getWanIpAddr(char *wanIpAddr, char *wanSubnetMask, char *ipv6WanAddr, char *status)
{
    // TODO:
    return CTSGW_OK;
}

/*
 * Get the gateway mac address
 */
int ctSgw_sysGetMac(char *mac, char *status)
{
    int ret = -1;
    CtSgwDeviceInfo_t devInfo;

    memset (&devInfo, 0, sizeof(CtSgwDeviceInfo_t));
    ret = CtSgwGetDeviceInfo (&devInfo);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (mac, devInfo.MAC);
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysGetSSN(char *ssn, int ssnLength, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysSetSSN(const char *ssn, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_wlanGetSecurityCfg(int ssidIndex, int *enable, CtWlanAuthMode *authMode, char *ssid, char *password, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_wps(int on1OrOff0, int time, char *status)
{
    CtSgwWPS_t obj;
    int ret = CTSGW_NOK;

    memset (&obj, '\0', sizeof(obj));
    obj.Enable = on1OrOff0;
    obj.TimeOut= time;
    
    ret = CtSgwSetWPS (&obj);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (status, STR_SUCCESS);
    return CTSGW_OK;
}

#if 0
int ctSgw_wanCreateL2tpTunnel(const char *serverIpAddr, const char *userId, const char *username,
                              const char *password, char *tunnelName, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_wanRemoveL2tpTunnel(const char *tunnelName, const char *userId, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_wanAttachL2tpTunnel(const char *tunnelName, const char **ipDomainNameAddr, int number, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_wanDetachL2tpTunnel(const char *tunnelName, const char *ipDomainNameAddr, int number, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_wanQueryL2tpTunnel(const char *tunnelName, const char *userId, char *tunnelStatus, char *status)
{
    // TODO:
    return CTSGW_OK;
}
#endif

int ctSgw_setLanDeviceFlow(int enable, char *status)
{
    CtSgwLANHostMgr_t obj;
    int ret = CTSGW_NOK;

    memset (&obj, '\0', sizeof(obj));
    obj.EnableStats = enable;
    
    ret = CtSgwSetLANHostMgr (&obj);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (status, STR_SUCCESS);
    return CTSGW_OK;
}

#if 0
int ctSgw_setAccountManage(Account *ftp, Account *samba, char *httpPassword, char *status)
{
    // TODO: add operation
}
#endif

int ctSgw_setAccountManage(int *ftpEnable, int *ftpService, int *sambaEnable, int *sambaService, int *httpEnable, Account *ftp, int *ftpNumber, Account *samba, int *sambaNumber, char *httpPassword, char *status)
{
    // TODO: Same function name as above.
    return CTSGW_OK;
}

int ctSgw_plugGetParameter(Parameter *parameter, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_plugSetParameter(Parameter *parameter, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_setOSRight(int cpu, int flash, int ram, int socket, int port, int thread, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetMfName(char *mfName, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetSoftwVer (char *SoftVer, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (SoftVer, info.SWVersion);
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetHardwVer (char *hardVer, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (hardVer, info.HDVersion);
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetModel (char *pModel, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (pModel, info.ProductClass);
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetCPUInfo(char * cpuVendor, char *cpuModel, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    // TODO: CPUClass = ChipSet Vendor + ChipSet Model, how to split them?
    g_stpcpy (cpuVendor, info.CPUClass);
    g_stpcpy (cpuModel, info.CPUClass);
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetDevModel (char *pdevModel, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (pdevModel, info.DevType);
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetDevType (char *pdevType,  char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (pdevType, info.DevType1);
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetCap (char *pgwCap,char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (pgwCap, info.Capability);
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetCard(int *pcard, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pcard = info.Card;
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetCardno(char *pCardNo, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (pCardNo, info.Cardno);
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetUplink(int *plink, char *status)
{
    CtSgwNetworkInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetNetworkInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *plink = info.UPLink;
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetIpv6(int *pipv6, char *status)
{
    CtSgwNetworkInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetNetworkInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pipv6 = info.IPV6;
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetVLanBind(int *pbind, char *status)
{
    CtSgwNetworkInfo_t   info;
    int ret = CTSGW_NOK;
    
    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetNetworkInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pbind = info.VLANbind;
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysGetLed(int *pLed, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pLed = info.LED;
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetFlashSize (unsigned int *pFlashSize, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pFlashSize = info.FlashSize;
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetRamSize (unsigned int *pRamSize, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pRamSize = info.RamSize;
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetDevName (char *pdevName, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (pdevName, info.DevName);
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetWifiMode(char * pwifiModel, char *status)
{
    CtSgwNetworkInfo_t   info;
    int ret = CTSGW_NOK;
    
    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetNetworkInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (pwifiModel, info.WiFiMode);
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysGetNFC (int * pnfc, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;
    
    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pnfc = info.NFC;
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetWanStatus (int *pwan, char *status)
{
    CtSgwNetworkInfo_t   info;
    int ret = CTSGW_NOK;
    
    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetNetworkInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pwan = atoi(info.WANLinkStatus);
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysGetLanStatus (int *lan1, int *lan2, int *lan3, int *lan4, char *status)
{
    CtSgwNetworkInfo_t   info;
    int ret = CTSGW_NOK;
    
    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetNetworkInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *lan1 = info.LAN1Status;
    *lan2 = info.LAN2Status;
    *lan3 = info.LAN3Status;
    *lan4 = info.LAN4Status;
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysGetWifiModuleStatus (int *pwifiModule, char *status)
{
    CtSgwNetworkInfo_t   info;
    int ret = CTSGW_NOK;
    
    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetNetworkInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pwifiModule = atoi(info.WIFIModuleStatus);
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysGetPPPoEStatus (int *Ipv4ConnctionStatus, char *Ipv4WanStatus, char *Ipv4DialReason, int *Ipv6ConnctionStatus,char *Ipv6WanStatus, char *Ipv6DialReason, char *status)
{
    CtSgwNetworkInfo_t   info;
    int ret = CTSGW_NOK;
    
    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetNetworkInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *Ipv4ConnctionStatus = atoi(info.WANLinkStatus);
    g_stpcpy (Ipv4WanStatus, info.WANConnectionStatus);
    g_stpcpy (Ipv4DialReason, info.PPPoEDialReason);
    //*Ipv6ConnctionStatus = atoi(info.);               TODO: what does this parameter mean?
    g_stpcpy (Ipv6WanStatus, info.IPV6_WANConnectionStatus);
    g_stpcpy (Ipv6DialReason, info.IPV6_PPPoEDialReason);
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysGetWanLinkNum (int *pNum, char *status)
{
    int ret = -1;
    guint32 count = 0;
    
    ret = CtSgwGeWANConnectionObjs(NULL, &count);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pNum = count;
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysGetWanLinksDesc (char *pwanLinksDesc, char *status)
{
    int ret = -1;
    guint32 count = 0;
    int i = 0;
    CtSgwWANConnectionInfo_t  *objs = NULL;
    CtSgwWANConnectionInfo_t  *pEntry = NULL;
    
    ret = CtSgwGeWANConnectionObjs(&objs, &count);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    pEntry = objs;
    for (i = 0; i < count; ++i)
    {
        g_strlcat (pwanLinksDesc, pEntry->IfName, STR_LEN_128);
        ++pEntry;
    }

    // Free all the allocated memory
    g_free (objs);
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysGetWanBaseInfo (char *pwanLinkName,int *pindex,char *pifName,char *pserviceList,char *pconnType,char *pvlanID,char *p8021p,char *pprotocol,char *status)
{
    int ret = -1;
    guint32 count = 0;
    int i = 0;
    CtSgwWANConnectionInfo_t  *objs = NULL;
    CtSgwWANConnectionInfo_t  *pEntry = NULL;
    
    ret = CtSgwGeWANConnectionObjs(&objs, &count);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    pEntry = objs;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 (pEntry->IfName, pwanLinkName) == 0)
        {
            *pindex = atoi(pEntry->Index);
            g_stpcpy (pifName, pEntry->IfName);
            g_stpcpy (pserviceList, pEntry->ServiceList);
            g_stpcpy (pconnType, pEntry->ConnectionType);
            sprintf(pvlanID, "%d", pEntry->VLANID);
            sprintf(p8021p, "%d", pEntry->VLAN8021P);
            g_stpcpy (pprotocol, pEntry->Protocol);
            g_stpcpy (status, STR_SUCCESS);
            ret = CTSGW_OK;
        }

        ++pEntry;
    }

    if (i >= count)
    {
        g_stpcpy (status, STR_FAIL);
        ret = CTSGW_OK;
    }

    // Free all the allocated memory
    g_free (objs);
    
    return ret;
}

int ctSgw_sysGetWanIpInfo (const char *pwanLinkName,char * pconnStatus,char *pipAddr,char *psubNetMask,char *pgateway,char *pdns1,char *pdns2,char *status)
{
    int ret = -1;
    guint32 count = 0;
    int i = 0;
    CtSgwWANConnectionInfo_t  *objs = NULL;
    CtSgwWANConnectionInfo_t  *pEntry = NULL;
    
    ret = CtSgwGeWANConnectionObjs(&objs, &count);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    pEntry = objs;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 (pEntry->IfName, pwanLinkName) == 0)
        {
            g_stpcpy (pconnStatus, pEntry->ConnectionStatus);
            g_stpcpy (pipAddr, pEntry->IPAddress);
            g_stpcpy (psubNetMask, pEntry->SubnetMask);
            g_stpcpy (pgateway, pEntry->Gateway);
            g_stpcpy (pdns1, pEntry->DNS1);
            g_stpcpy (pdns2, pEntry->DNS2);
            g_stpcpy (status, STR_SUCCESS);
            ret = CTSGW_OK;
        }

        ++pEntry;
    }

    if (i >= count)
    {
        g_stpcpy (status, STR_FAIL);
        ret = CTSGW_OK;
    }

    // Free all the allocated memory
    g_free (objs);
    
    return ret;
}

int ctSgw_sysGetWanIpv6Info (const char *pwanLinkName,char * pconnStatus,char *pipAddr,int *pprifixLen,char *pgateway,char *pdns1,char *pdns2,char *pprifix,char *status)
{
    int ret = -1;
    guint32 count = 0;
    int i = 0;
    CtSgwWANConnectionInfo_t  *objs = NULL;
    CtSgwWANConnectionInfo_t  *pEntry = NULL;
    
    ret = CtSgwGeWANConnectionObjs(&objs, &count);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    pEntry = objs;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 (pEntry->IfName, pwanLinkName) == 0)
        {
            g_stpcpy (pconnStatus, pEntry->IPV6_ConnectionStatus);
            g_stpcpy (pipAddr, pEntry->IPV6_IPAddress);
            *pprifixLen = atoi(pEntry->IPV6_PrefixLength);
            g_stpcpy (pgateway, pEntry->IPV6_Gateway);
            g_stpcpy (pdns1, pEntry->IPV6_DNS1);
            g_stpcpy (pdns2, pEntry->IPV6_DNS2);
            g_stpcpy (pprifix, pEntry->IPV6_Prefix);
            g_stpcpy (status, STR_SUCCESS);
            ret = CTSGW_OK;
        }

        ++pEntry;
    }

    if (i >= count)
    {
        g_stpcpy (status, STR_FAIL);
        ret = CTSGW_OK;
    }

    // Free all the allocated memory
    g_free (objs);
    
    return ret;

}

int ctSgw_speedTestValueList (char * ptotalList,char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_speedTestControl (const char *pusr,const char *ppwd,const char *pmethod,int time, char *status)
{
    // TODO: No interface or method to invoke
    return CTSGW_OK;
}

int ctSgw_speedTestSetting (const char *pusr,const char *ppwd,const char *purl, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetSSIDInfo (int ssidIndex,char *pssidName,char *ppwd,int *pcryptType,int *ppowerLeve,int *pchannel,int *penable, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetvoipInfo (char *pvoipName1,char *pvoipName2, char *status)
{
    CtSgwVoIPInfo_t info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetVoIPInfo(&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (pvoipName1, info.VoIPName1);
    g_stpcpy (pvoipName2, info.VoIPName2);
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysGetVoipRegStatus (char *pline1Status,char * pline2Status,char *status)
{
    CtSgwVoIPInfo_t info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetVoIPInfo(&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (pline1Status, info.Line1Status);
    g_stpcpy (pline2Status, info.Line2Status);
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_wanPing (const char *pusr,const char *ppwd,const char *pDest,const char *pwanLinkName,int pkgLen,int times, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_wanPingResult (const char *pusr,const char *ppwd,char *ppingStatus,int *pingResult, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_wanTraceroute (const char *pusr,const char *ppwd,const char *pDest,const char *pwanLinkName, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_wanTracerouteResult (const char *pusr,char *ppwd,char *ptracertStatus,char *ptracertResult, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_wanInformResult (const char *pusr,const char *ppwd,char *pinformStatus,char *pinformResult,char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysLOIDRegistry (const char *pusr,const char *ppwd, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetDevRegisterStatus (char *pregisterStatus,int * pRegisterResult,char *pregBussNameResult, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetPONStatus(double *ptemp,double *pvot,double *pcur,double *ptxpw,double *prxpw, char *status)
{
    CtSgwPONInfo_t info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetPONInfo(&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *ptemp = info.Temperature;
    *pvot = info.Vottage;
    *pcur = info.Current;
    *ptxpw = info.TxPower;
    *prxpw = info.RxPower;
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysGetPONRegStatus(char *pstatus, char *status)
{
    CtSgwPONInfo_t info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetPONInfo(&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (pstatus, info.PONStatus);
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysSetDateTime(const char *pTime, char *status)
{
    int ret = CTSGW_NOK;

    ret = CtSgwSysCmdSetDateTime((char *)pTime);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysGetWifiEnable(int *pEnable, char *status)
{
    CtSgwNetworkInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetNetworkInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pEnable= atoi(info.WIFIModuleStatus);
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetWanRecv (unsigned long long *pnRecvbytes, unsigned long long *pnRecvPkgs, unsigned long long *pnWrongPkgs, unsigned long long *pnLostPkgs, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetWanSend (unsigned long long *pnSendbytes, unsigned long long *pnSendPkgs, unsigned long long *pnWrongPkgs, unsigned long long *pnLostPkgs, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysSetSSIDSettings (int ssidIndex,const char *pssidName, const char *ppwd, int cryptType,int powerLeve,int channel,int enable, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysCloseSSID (int ssidIndex, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysSetWifiTimer (const char * pStartTime,const char * pEndTime, ControlCycleType ControlCycle,int Enable)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysSetApiRight (const char *pApi,int right, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetSystemDuration (int *duration, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *duration = info.SysDuration;
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetPPPOEDuration (int *duration, char *status)
{
    CtSgwNetworkInfo_t   info;
    int ret = CTSGW_NOK;
    
    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetNetworkInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *duration = info.PPPOEDuration;
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetPONDuration (int *duration, char *status)
{
    CtSgwNetworkInfo_t   info;
    int ret = CTSGW_NOK;
    
    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetNetworkInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *duration = info.PONDuration;
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetCardStatus (int *pstatus, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pstatus = info.CardStatus;
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetBussinessStatus (char *pstatus, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysReboot(char *status)
{
    int ret = CTSGW_NOK;
    
    ret = CtSgwSysCmdReboot();
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysRestoreNotPrimeParm(char *status)
{
    int ret = CTSGW_NOK;
    
    ret = CtSgwSysCmdRestore();
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetTopInfo(char *ptop)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetLOID(char *ploid, char *status)
{
    CtSgwPONInfo_t info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetPONInfo(&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (ploid, info.LOID);
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysCheckPwd(const char *pw, char *status)
{
    // TODO: can do
    // SetUAPasswd or CheckTAPasswd
    return CTSGW_OK;
}

int ctSgw_sysSetErrorRedirectSetting(char *purl, char *status)
{
    CtSgw404Redir_t obj;
    int ret = CTSGW_NOK;

    memset(&obj, '\0', sizeof(obj));
    g_stpcpy (obj.DownURL, purl);
    ret = CtSgwSet404Redir (&obj);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysTrigerFwUpdate(const char *purl,int mode,int method)
{
    int ret = CTSGW_NOK;

    ret = CtSgwSysCmdUpgrade((char *)purl, mode, method);
    if (ret != CTSGW_OK)
    {
        return CTSGW_NOK;
    }

    return CTSGW_OK;
}

int ctSgw_sysGetLanFlow(double *pport1Rx, double *pport1Tx, double *pport2Rx, double *pport2Tx, double *pport3Rx, double *pport3Tx, double *pport4Rx, double *pport4Tx, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetPPPoEFailReason(const char *pusr, const char *ppwd, const char *pvpnAcc, const char *pvpnPwd, int *pconnStatus,char *pwanStatus,int len1,char *pdialReason,int len2, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetWifiTimerInfo (char *pStartTime,char *pEndTime, ControlCycleType *pControlCycle,int *pEnable)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetNfcStatus (int * pnStatus, char *status)
{
    CtSgwNFC_t obj;
    int ret = CTSGW_NOK;
    
    ret = CtSgwGetNFC(&obj);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pnStatus = atoi(obj.Enable);
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysGetSleepStatus (int * pnStatus, char *status)
{
    // TODO: This is a multi-instance object, which should get
    return CTSGW_OK;
}

// TODO: take it as a single instance object here, but as 
// the document definition, it's multi-instance object.
int ctSgw_sysGetLedStatus (int *pled, char *status)
{
    GVariantIter iter;
    GVariant *dict = NULL;
    gchar   *key;
    GVariant *value = NULL;
    gchar    *str_val = NULL;
    int ret = -1;

    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/Config/Peripheral/LED",
                                   "com.ctc.igd1.LED",
                                   &dict);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "Enable") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            *pled = atoi(str_val);
            g_free (str_val);
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_stpcpy (status, STR_SUCCESS);
    g_variant_unref (dict);

    return CTSGW_OK;
}

// TODO: What does ControlCycle mean
int ctSgw_sysSetLedTimer (char * pStartTime,char * pEndTime, ControlCycleType ControlCycle,int Enable, char *status)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    gchar str[STR_LEN_32];
    int ret = -1;

    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "Status",
                           g_variant_new_string (status));

    g_variant_builder_add (builder,
                           "{sv}",
                           "StartTime",
                           g_variant_new_string (pStartTime));

    g_variant_builder_add (builder,
                           "{sv}",
                           "EndTime",
                           g_variant_new_string (pEndTime));
#if 0
    g_variant_builder_add (builder,
                           "{sv}",
                           "ControlCycle",
                           g_variant_new_string (ControlCycle));
#endif
    sprintf(str, "%d", Enable);
    g_variant_builder_add (builder,
                           "{sv}",
                           "Enable",
                           g_variant_new_string (str));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);

    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     "/com/ctc/igd1/Config/Peripheral/LED",
                                     "com.ctc.igd1.LED",
                                     value);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (status, STR_SUCCESS);
    g_variant_unref (value);

    return CTSGW_OK;
}

int ctSgw_sysDiagMulticast(char* pdiagResult, char *status)
{
    CtSgwMCTestResult_t result;
    int ret = -1;

    memset(&result, '\0', sizeof(result));
    ret = CtSgwGetMCTestResult (&result);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (pdiagResult, result.DialResult);
    g_stpcpy (status, STR_SUCCESS);

    return CTSGW_OK;
}

int ctSgw_sysSetDns(const char* pdns1,const char* pdns2, char *status)
{
    GVariant *value = NULL;
    GVariantBuilder *builder;
    int ret = -1;
    
    if (IS_EMPTY_STRING(pdns1) && IS_EMPTY_STRING(pdns2))
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }
    
    builder = g_variant_builder_new (G_VARIANT_TYPE("a{sv}"));
    g_variant_builder_add (builder,
                           "{sv}",
                           "Server1",
                           g_variant_new_string (pdns1));

    g_variant_builder_add (builder,
                           "{sv}",
                           "Server2",
                           g_variant_new_string (pdns2));

    value = g_variant_builder_end (builder);
    g_variant_builder_unref (builder);
    
    ret = CtSgwDBusSetMultiProperty ("com.ctc.igd1",
                                     "/com/ctc/igd1/dns",
                                     "com.ctc.igd1.DNSServerConfig",
                                     value);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (status, STR_SUCCESS);
    g_variant_unref (value);

    return CTSGW_OK;
}

int ctSgw_sysAddObject(char* pObject, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysDelObject(const char* pObject, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetBlackList (char *pmaclist, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetDownUpBandwidth (double *pnUp, double *pnDown, char *status)
{
    CtSgwNetworkInfo_t   info;
    int ret = CTSGW_NOK;

    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetNetworkInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    *pnUp = info.WANUSRate;
    *pnDown = info.WANDSRate;
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysSetNfcStatus (int nStatus, char *status)
{
    CtSgwNFC_t  obj;
    int ret = CTSGW_NOK;

    memset(&obj, '\0', sizeof(obj));
    sprintf(obj.Enable, "%d", nStatus);
    ret = CtSgwSetNFC(&obj);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysSetLedStatus(int nStatus, char *status)
{
    gchar   str[STR_LEN_16];
    int ret = CTSGW_NOK;

    memset(str, '\0', sizeof(str));
    sprintf(str, "%d", nStatus);
    ret = CtSgwDBusSetProperty( "com.ctc.igd1",
                                "/com/ctc/igd1/Config/Peripheral/LED",
                                "com.ctc.igd1.LED",
                                "Status",
                                g_variant_new_string(str));
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysSetSleepTimer(int Action, StrongTimer sleepTimer[], int nCount, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysSetStrongWifiTimer(int Action, StrongTimer wifiTimer[], int nCount, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysSetDevName (const char *pdevName, char *status)
{
    int ret = CTSGW_NOK;

    ret = CtSgwSysCmdSetDevName((char *)pdevName);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetDNS (char *pdns1,char *pdns2, char *status)
{
    GVariant *dict = NULL;
    GVariant *value = NULL;
    GVariantIter iter;
    gchar   *key;
    gchar   *str_val = NULL;
    int ret = -1;

    ret = CtSgwDBusGetAllProperty ("com.ctc.igd1",
                                   "/com/ctc/igd1/dns",
                                   "com.ctc.igd1.DNSServerConfig",
                                   &dict);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    // val is a type of "a{sv}", unpack it
    g_variant_iter_init (&iter, dict);
    while (g_variant_iter_next (&iter, "{sv}", &key, &value))
    {
        if (g_strcmp0 (key, "Server1") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (pdns1, str_val);
            g_free (str_val);
        }
        else if (g_strcmp0 (key, "Server2") == 0)
        {
            g_variant_get (value, FORMAT_STRING, &str_val);
            g_stpcpy (pdns2, str_val);
            g_free (str_val);
        }

        g_free (key);
        g_variant_unref (value);
    }

    g_variant_unref (dict);

    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetSleepTimer(StrongTimer *sleepTimer, int nCount, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_sysGetStrongWifiTimer(StrongTimer *sleepTimer, int nCount, char *status)
{
    // TODO:
    return CTSGW_OK;
}

int ctSgw_lanGetDevMaxBandwidth(const unsigned char *pmacAddr, int *pusBandwidth, int *pdsBandwidth, char *status)
{
    CtSgwLANHost_t  *objs = NULL;
    CtSgwLANHost_t  *pEntry = NULL;
    int     count = 0;
    int     ret = CTSGW_NOK;
    int     i = 0;

    g_return_val_if_fail (!IS_EMPTY_STRING(pmacAddr), CTSGW_NOK);
    ret = CtSgwGetLANHostObjs(&objs, &count);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    // Looking for the specific entry.
    pEntry = objs;
    for (i = 0; i < count; ++i)
    {
        if (g_strcmp0 ((const char *)pmacAddr, pEntry->MAC) == 0)
        {
            *pusBandwidth = pEntry->MaxUSBandwidth;
            *pdsBandwidth = pEntry->MaxDSBandwidth;
            
            ret = CTSGW_OK;
            g_stpcpy (status, STR_SUCCESS);
            break;
        }

        ++ pEntry;
    }

    if (i >= count)
    {
        g_stpcpy (status, STR_FAIL);
        ret = CTSGW_NOK;
    }

    // Free the allocated memory
    g_free (objs);

    return ret;
}

int ctSgw_sysBootSSID(int ssidIndx, char *status)
{
    // TODO:
    return CTSGW_OK;
}

// TODO: which property is SN?
int ctSgw_sysGetSN(char *psn, char *status)
{
    CtSgwDeviceInfo_t   info;
    int ret = CTSGW_NOK;
    
    memset(&info, '\0', sizeof(info));
    ret = CtSgwGetDeviceInfo (&info);
    if (ret != CTSGW_OK)
    {
        g_stpcpy (status, STR_FAIL);
        return CTSGW_NOK;
    }

    g_stpcpy (psn, info.DevType);
    g_stpcpy (status, STR_SUCCESS);
    
    return CTSGW_OK;
}

int ctSgw_sysGetOsVer(char * pOsVer, char *status)
{
    // TODO:
    return CTSGW_OK;
}

#ifdef __cplusplus
}
#endif


