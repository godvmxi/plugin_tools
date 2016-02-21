#ifndef _CAPI_SYS_SERVICE_H_
#define _CAPI_SYS_SERVICE_H_

#include <string.h>
#include <gio/gio.h>

// Max length of object path
#define MAX_OBJPATH_LEN 255

#define MAX_URL_LEN     63
#define MAX_TIME_LEN    24
#define MAX_LOID_LEN    31
#define MAX_PASSWORD_LEN 31
#define MAX_PATH_LEN    127
#define MAX_DEVNAME_LEN 31


#define STR_LEN_8       8
#define STR_LEN_16      16
#define STR_LEN_24      24
#define STR_LEN_32      32
#define STR_LEN_48      48
#define STR_LEN_64      64
#define STR_LEN_128     128

#define FORMAT_BOOL     "b"
#define FORMAT_UINT16   "q"
#define FORMAT_UINT32   "u"
#define FORMAT_UINT64   "t"
#define FORMAT_DOUBLE   "d"
#define FORMAT_STRING   "s"
#define FORMAT_BYTE     "y"
#define FORMAT_INT32    "i"
#define FORMAT_PATH     "o"

#define IS_EMPTY_STRING(s)  ((s == NULL) || (*s == '\0'))

// Type definition of dbus object path
typedef struct
{
    char str[MAX_OBJPATH_LEN + 1];
} CtSgwObjPath_t;

// Error code
typedef enum
{
    CTSGW_NOK = -1,
    CTSGW_OK = 0,
} CtSgwError_t;


/* ---------------------------------------- */

typedef struct
{
    CtSgwObjPath_t  path;

    guchar      BusinessStatus;
    gchar       MAC[STR_LEN_24];
    gchar       SWVersion[STR_LEN_32];
    gchar       HDVersion[STR_LEN_32];
    gchar       ProductClass[STR_LEN_24];
    gchar       CPUClass[STR_LEN_32];
    gchar       DevType[STR_LEN_48];
    gchar       DevType1[STR_LEN_32];
    gchar       Capability[STR_LEN_48];
    guint32     FlashSize;
    guint32     RamSize;
    gchar       DevName[STR_LEN_32];
    guchar      NFC;
    guchar      LED;
    guchar      CPUUsage;
    guchar      MEMUsage;
    guchar      FlashUsage;
    guint32     SysDuration;
    gboolean    Card;
    gchar       Cardno[STR_LEN_64];
    guchar      CardStatus;
    gchar       RegisterStatus[STR_LEN_32];
    gchar       RegisterResult[STR_LEN_32];
    gchar       RegisterProgressResult[STR_LEN_32];
    gchar       RegisterBussNameResult[STR_LEN_32];
    gchar       RegisterServiceResult[STR_LEN_32];   
} CtSgwDeviceInfo_t;

typedef struct
{
    CtSgwObjPath_t path;

    guint32     UPLink;
    guchar      IPV6;
    guchar      VLANbind;
    gchar       WiFiMode[STR_LEN_48];
    guint32     PONDuration;
    guint32     PPPOEDuration;
    guchar      LAN1Status;
    guchar      LAN2Status;
    guchar      LAN3Status;
    guchar      LAN4Status;
    gchar       WANLinkStatus[STR_LEN_8];
    gchar       WIFIModuleStatus[STR_LEN_8];
    gchar       WANConnectionStatus[STR_LEN_24];
    gchar       PPPoEDialReason[STR_LEN_16];
    gchar       IPV6_WANConnectionStatus[STR_LEN_16];
    gchar       IPV6_PPPoEDialReason[STR_LEN_24];
    gchar       LANIPAddr[STR_LEN_24];
    gchar       WANIPAddr[STR_LEN_24];
    gchar       WANIPV6Addr[STR_LEN_24];
    guint32     WiFiRate;
    guint32     WiFiUSRate;
    guint32     WiFiDSRate;
    guint32     WANRate;
    guint32     WANUSRate;
    guint32     WANDSRate;
    
} CtSgwNetworkInfo_t;

    
typedef struct
{
    CtSgwObjPath_t path;

    gchar       Index[STR_LEN_8];
    gchar       IfName[STR_LEN_32];
    gchar       ServiceList[STR_LEN_64];
    gchar       ConnectionType[STR_LEN_16];
    guint32     VLANID;
    guint32     _8201P;
    gchar       Protocol[STR_LEN_16];
    gchar       ConnectionStatus[STR_LEN_32];
    gchar       IPAddress[STR_LEN_24];
    gchar       SubnetMask[STR_LEN_24];
    gchar       Gateway[STR_LEN_24];
    gchar       DNS1[STR_LEN_24];
    gchar       DNS2[STR_LEN_24];
    gchar       IPV6_ConnectionStatus[STR_LEN_16];
    gchar       IPV6_IPAddress[STR_LEN_32];
    gchar       IPV6_PrefixLength[STR_LEN_32];
    gchar       IPV6_Gateway[STR_LEN_32];
    gchar       IPV6_DNS1[STR_LEN_32];
    gchar       IPV6_DNS2[STR_LEN_32];
    gchar       IPV6_Prefix[STR_LEN_32];
    guint64     RxBytes;
    guint64     TxBytes;
    guint64     RxPkts;
    guint64     TxPkts;
    
} CtSgwWANConnectionInfo_t;


typedef struct
{
    CtSgwObjPath_t path;

    gchar       SSID[STR_LEN_32];
    gboolean    Enable;
    guint32     Channel;
    guint32     PowerLevel;
    guint32     PowerLevel_5G;
    gchar       PWD[STR_LEN_128];
    guint32     Encrypt;
    guint64     RxBytes;
    guint64     RxPkts;
    guint64     RxErrorPkts;
    guint64     RxDropPkts;
    guint64     TxBytes;
    guint64     TxPkts;
    guint64     TxErrorPkts;
    guint64     TxDropPkts;
    
} CtSgwWiFiInfo_t;


typedef struct
{
    CtSgwObjPath_t path;

    gchar       LOID[STR_LEN_32];
    gchar       Password[STR_LEN_32];
    gdouble     Temperature;
    gdouble     Vottage;
    gdouble     Current;
    gdouble     TxPower;
    gdouble     RxPower;
    gboolean    SupportPONStatusQuery;
    gchar       PONStatus[STR_LEN_32];
    
} CtSgwPONInfo_t;


typedef struct
{
    CtSgwObjPath_t path;

    gchar   VoIPName1[STR_LEN_32];
    gchar   VoIPName2[STR_LEN_32];
    gchar   Line1Status[STR_LEN_32];
    gchar   Line2Status[STR_LEN_32];
    
} CtSgwVoIPInfo_t;


typedef struct
{
    CtSgwObjPath_t path;

    gboolean   EnableStats;   
    
} CtSgwLANHostMgr_t;


typedef struct
{
    CtSgwObjPath_t path;

    gchar       MAC[STR_LEN_24];        //'r'
    gchar       DevName[STR_LEN_32];
    gboolean    DenyInternetAccess;
    gboolean    DenyStorageAccess;
    guint32     MaxUSBandwidth;
    guint32     MaxDSBandwidth;
    guint32     USBandwidth;
    guint32     DSBandwidth;
    gchar       DevType[STR_LEN_24];    // 'r'
    gchar       IP[STR_LEN_24];         // 'r'
    guchar      ConnectionType;         // 'r'
    guchar      Port;                   // 'r'
    gchar       Brand[STR_LEN_32];      // 'r'
    gchar       OS[STR_LEN_32];         // 'r'
    guint32     OnlineTime;             // 'r'
    
} CtSgwLANHost_t;


typedef struct
{
    CtSgwObjPath_t path;

    guint32     Status;             // 'r'
    gchar       Result[STR_LEN_32]; // 'r'
    gchar       URL[MAX_URL_LEN + 1];   // 'rw'
    
} CtSgwHttpDownloadTestResult_t;


typedef struct
{
    CtSgwObjPath_t path;

    gchar   PingStatus[STR_LEN_32]; // 'r'
    gchar   PingResult[STR_LEN_32]; // 'r'
    
} CtSgwPingTestResult_t;


typedef struct
{
    CtSgwObjPath_t path;
    
    gchar   TraceStatus[STR_LEN_32];
    gchar   TraceResult[STR_LEN_32];

} CtSgwTraceRouteTestResult_t;


typedef struct
{
    CtSgwObjPath_t path;
    
    guint32 result;
    
} CtSgwInformTestResult_t;


typedef struct
{
    CtSgwObjPath_t path;

    guint32     DialStatus;
    gchar       DialResult[STR_LEN_32];
    
} CtSgwMCTestResult_t;


typedef struct
{
    CtSgwObjPath_t path;

    gboolean    Enable;
    guint32     Width;
    guint32     Height;
    gchar       Place[STR_LEN_128];
    gchar       URL[STR_LEN_128];
    gchar       Time[STR_LEN_32];
    guchar      Status; // Range: 0~3, 'r'
    
} CtSgwPWConfig_t;


typedef struct
{
    CtSgwObjPath_t path;

    gchar   DownURL[STR_LEN_128];
    
} CtSgw404Redir_t;


typedef struct
{
    gchar   Info[STR_LEN_128];
} CtSgwWPSDevInfo_t;

#define WPS_ATT_DEV_NUM 16
typedef struct
{
    CtSgwObjPath_t path;

    gboolean            Enable;
    gchar               SSID[STR_LEN_32];
    guint32             TimeOut;
    guchar              WPSStatus;  // 'r'
    CtSgwWPSDevInfo_t   DevInfo[WPS_ATT_DEV_NUM];   // 'r'
    
} CtSgwWPS_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar       SSID[STR_LEN_32];
    gboolean    Enable;
    guint32     Channel;
    guint32     ChannelInUse;   // "r"
    gchar       BeaconType[STR_LEN_16];
    gchar       Standard[STR_LEN_24];
    gchar       WEPEncryptionLevel[STR_LEN_24];
    gchar       BasicAuthenticationMode[STR_LEN_24];
    gchar       WPAEncryptionModes[STR_LEN_24];
    gboolean    SSIDHide;
    guint32     RFBand;
    guint32     ChannelWidth;
    guint32     GuardInterval;
    guint32     RetryTimeout;
    guint32     Powerlevel;
    guint32     PowerLevel_5G;
    guint32     PowerValue;     // "r"
    gboolean    APModuleEnable;
    guint32     WPSKeyWord;
    gchar       PWD[STR_LEN_64];
    
} CtSgwWLANDevice_t;

//Not suggest to use this object
typedef struct {
    CtSgwObjPath_t path;

    gchar       StartTime[STR_LEN_32];
    gchar       EndTime[STR_LEN_32];
    gchar       ControlCycle[STR_LEN_32];
    gboolean    Enable;
    
} CtSgwWiFiTimer_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar       WeekDay[STR_LEN_32];
    gchar       Time[STR_LEN_32];
    gchar       Active[STR_LEN_16];
    gchar       Enable[STR_LEN_16];
    
} CtSgwWiFiTimer1_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar       Status[STR_LEN_16];
    gchar       StartTime[STR_LEN_32];
    gchar       EndTime[STR_LEN_32];
    gchar       ControlCycle[STR_LEN_32];
    gchar       Enable[STR_LEN_16];
    
} CtSgwLED_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar       Enable[STR_LEN_16];
    
} CtSgwNFC_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar       Day[STR_LEN_16];
    gchar       Time[STR_LEN_16];
    gchar       Active[STR_LEN_16];
    gchar       Enable[STR_LEN_16];
    
} CtSgwSleepTimer_t;


typedef struct {
    CtSgwObjPath_t path;

    CtSgwObjPath_t  LANInterface;
    gchar           ServiceList[STR_LEN_64];
    gboolean        DHCPEnable;
    guint32         IPMode;
    gchar           IPV6ConnectionStatus[STR_LEN_32];   // "r"
    gboolean        ProxyEnable;
    guint32         ProxyMaxUser;
    gboolean        DDNSCfgEnabled;
    gchar           DDNSProvider[STR_LEN_64];
    gchar           DDNSUsername[STR_LEN_32];
    gchar           DDNSPassword[STR_LEN_32];
    guint32         ServicePort;
    gchar           DDNSDomainName[STR_LEN_32];
    gchar           DDNSHostName[STR_LEN_32];
    
} CtSgwWANPPPConn_t;


typedef struct {
    CtSgwObjPath_t path;

    CtSgwObjPath_t  LANInterface;
    gchar           ServiceList[STR_LEN_64];
    gboolean        DHCPEnable;
    guint32         IPMode;
    gchar           IPV6ConnectionStatus[STR_LEN_32];   // "r"
    gboolean        DDNSCfgEnabled;
    gchar           DDNSProvider[STR_LEN_64];
    gchar           DDNSUsername[STR_LEN_32];
    gchar           DDNSPassword[STR_LEN_32];
    guint32         ServicePort;
    gchar           DDNSDomainName[STR_LEN_32];
    gchar           DDNSHostName[STR_LEN_32];
    
} CtSgwWANIPConn_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar           MinAddress[STR_LEN_24];
    gchar           MaxAddress[STR_LEN_24];
    gchar           SubnetMask[STR_LEN_24];
    guint32         LeaseTime;
    
} CtSgwDHCPServer_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar       Mode[STR_LEN_16];
    gboolean    Enable;
    guint32     Bandwidth;
    gchar       Plan[STR_LEN_48];
    gboolean    EnableForceWeight;
    gboolean    EnableDSCPMark;
    guint32     Enable802_1_P;
    
} CtSgwUplinkQoS_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar       AppName[STR_LEN_32];
    guint32     ClassQueue;
    
} CtSgwUplinkQoSAppRule_t;


// This just a reference to ClassQueue in CtSgwUplinkQoSAppRule_t or CtSgwUplinkQoSClsRule_t
typedef struct {
    CtSgwObjPath_t path;

} CtSgwUplinkQoSClsAction_t;


typedef struct {
    CtSgwObjPath_t path;

    gboolean    Enable;
    guint32     Priority;
    guint32     Weight;
    
} CtSgwUplinkQosPQ_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar       Type[STR_LEN_48];
    gchar       Max[STR_LEN_48];
    gchar       Min[STR_LEN_48];
    gchar       ProtocolList[STR_LEN_64];

} CtSgwUplinkQoSClsMatch_t;


typedef struct {
    CtSgwObjPath_t path;
    
    CtSgwObjPath_t *match_paths;
    gint32      path_count;

    guint32     ClassQueue;
    guint32     DSCPMarkValue;
    guint32     _802_1P_Value;
    
    CtSgwUplinkQoSClsAction_t action;
} CtSgwUplinkQoSClsRule_t;


typedef struct {
    CtSgwObjPath_t path;

    gboolean    Enable;
    guint32     LeaseDuration;
    gchar       RemoteHost[STR_LEN_64];
    guint32     ExternalPort;
    guint32     InternalPort;
    gchar       PortMappingProtocol[STR_LEN_8];
    gchar       InternalClient[STR_LEN_24];
    gchar       Description[STR_LEN_32];
    
} CtSgwPortMapping_t;


typedef struct {
    gchar       MountPoint[MAX_PATH_LEN+1] ;    // "r"
    guint32     TotalSize;  // "r"
    guint32     UsedSize;   // "r"
    guint32     FreeSize;   // "r"
    gchar       Label[STR_LEN_32];  // "r"
} CtSgw_USBFSInfo_t ;


typedef struct {
    CtSgwObjPath_t path;

    guint16     DeviceType;     // "r"
    gint32      DeviceId;       // "r"
    gchar       DeviceName[STR_LEN_32]; // "r"
    CtSgw_USBFSInfo_t *fsinfo ;
    
} CtSgw_USBDevice_t ;


#define NAS_ACL_LIST_LEN    16
typedef struct
{
    CtSgwObjPath_t path;

    guint16     ACLMode;
    gchar       MACList[NAS_ACL_LIST_LEN][STR_LEN_64];
    
} CtSgw_NASConfig_t;

#define L2TP_ADDR_DOMAIN_NUM    16
typedef struct
{
    CtSgwObjPath_t path;
    
    gchar       ServerIPAddr[STR_LEN_24];
    gchar       UserName[STR_LEN_32];
    gchar       Password[STR_LEN_32];
    gchar       TunnelName[STR_LEN_32];
    guint32     Status; // "r", [0,1]
    gchar       IPAddrDomainList[L2TP_ADDR_DOMAIN_NUM][STR_LEN_24];
    
} CtSgwL2TPConn_t;

typedef struct
{
    CtSgwObjPath_t  path;

    gchar   Server1[STR_LEN_24];
    gchar   Server2[STR_LEN_24];
    
} CtSgwDNSServerConfig_t;

typedef struct
{
    CtSgwObjPath_t  path;

    gchar   ServerIP[STR_LEN_24];
    gchar   DomainName[STR_LEN_24];
} CtSgwDNSTunnel_t;    

typedef struct
{
    gchar       FileName[STR_LEN_64];
    gchar       PhysicalFolderName[STR_LEN_128];
    gboolean    IsFolder;
    guint32     FileSize;
    gchar       ModifiedTime[STR_LEN_24];
    
} CtSgw_FileEntry_t;

typedef struct {
    CtSgwObjPath_t path;

    gboolean    Enable;
    gboolean    AllowAnonymous;

} CtSgw_FTPServerConfig_t;


typedef struct
{
    CtSgwObjPath_t path;

    gchar   UserName[STR_LEN_32];
    gchar   Password[STR_LEN_32];
    
} CtSgw_FTPAccount_t;


typedef struct {
    CtSgwObjPath_t path;

    gboolean    Enable;
    gboolean    AllowAnonymous;
    
} CtSgw_SambaServerConfig_t;


typedef struct {
    CtSgwObjPath_t path;

    gchar   UserName[STR_LEN_32];
    gchar   Password[STR_LEN_32];
    
} CtSgw_SambaAccount_t;


typedef struct {
    CtSgwObjPath_t path;
    
    gboolean    Enable;
    gchar       AdminPasswd[STR_LEN_32];
    
} CtSgw_HttpServerConfig_t;



/****************************************************************
 *                                                              *
 * Function Declaration                                         *
 *                                                              *
 ****************************************************************/


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
CtSgwGetDeviceInfo (CtSgwDeviceInfo_t *info);



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
CtSgwGetNetworkInfo(CtSgwNetworkInfo_t *info);



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
CtSgwGeWANConnectionObjs(CtSgwWANConnectionInfo_t **objs, guint32 *count);


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
CtSgwGetWANConnection(CtSgwObjPath_t path, CtSgwWANConnectionInfo_t *obj);


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
CtSgwGetWANConnectionByName(const char *name, CtSgwWANConnectionInfo_t *obj);


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
CtSgwGetInternetWANConnection(CtSgwWANConnectionInfo_t *obj);


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
CtSgwGetWiFiInfo(CtSgwWiFiInfo_t *info);


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
CtSgwGetPONInfo(CtSgwPONInfo_t *info);


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
int CtSgwGetVoIPInfo(CtSgwVoIPInfo_t *info);


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
int CtSgwGetLANHostMgr(CtSgwLANHostMgr_t *obj);


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
int CtSgwSetLANHostMgr (CtSgwLANHostMgr_t *obj);


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
int CtSgwGetLANHostObjs(CtSgwLANHost_t **objs, int *count);


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
int CtSgwGetLANHost(CtSgwObjPath_t path, CtSgwLANHost_t *obj);


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
int CtSgwSetLANHost(CtSgwLANHost_t *obj);


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
int CtSgwSetHttpDownloadTestURL(const char url[MAX_URL_LEN+1]);


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
int CtSgwGetHttpDownloadTestURL(char url[MAX_URL_LEN+1]);


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
int CtSgwStartHttpDownloadTest(void);


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
int CtSgwGetHttpDownloadTestResult(CtSgwHttpDownloadTestResult_t *result);


/*
 * Function Name: CtSgwStartPingTest
 *
 * Description  : Execute the ping testing
 *
 * Parameter:
 *      path <IN>:  The WANConnection object path, use this wan to execute the testing
 *       len <IN>:  The package length
 *      time <IN>:  The package count.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwStartPingTest(CtSgwObjPath_t path, int len, int time);


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
int CtSgwGetPingTestResult(CtSgwPingTestResult_t *result);


/*
 * Function Name: CtSgwStartTraceRouteTest
 *
 * Description  : Start the trace route testing
 *
 * Parameter:
 *      path <IN>:  The WANConnection object path, use this wan to execute the testing
 *      dest <IN>:  The destination address of this test.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwStartTraceRouteTest(CtSgwObjPath_t path, char *dest);


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
int CtSgwGetTraceRouteTestResult(CtSgwTraceRouteTestResult_t *result);


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
int CtSgwStartInformTest(void);


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
int CtSgwGetInformTestResult(CtSgwInformTestResult_t *result);


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
CtSgwStartMCTest(void);


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
CtSgwGetMCTestResult(CtSgwMCTestResult_t *result);


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
int CtSgwSetPW (CtSgwPWConfig_t *obj);


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
int CtSgwGetPW (CtSgwPWConfig_t *obj);


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
int CtSgwSet404Redir (CtSgw404Redir_t *obj);


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
int CtSgwGet404Redir(CtSgw404Redir_t *obj);


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
int CtSgwSetWPS(CtSgwWPS_t *obj);


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
int CtSgwGetWPS(CtSgwWPS_t *obj);


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
int CtSgwGetWLANDeviceObjs(CtSgwWLANDevice_t **objs, guint32 *count);


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
int CtSgwGetWLANDevice(CtSgwObjPath_t path,  CtSgwWLANDevice_t *obj);


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
int CtSgwGetWLANDeviceBySSID(const char *ssid,  CtSgwWLANDevice_t *obj);


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
int CtSgwSetWLANDevice(CtSgwWLANDevice_t *obj);


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
int CtSgwGetWiFiTimerObjs(CtSgwWiFiTimer1_t **objs, int *count);


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
int CtSgwGetWiFiTimer(CtSgwObjPath_t path, CtSgwWiFiTimer1_t *obj);


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
int CtSgwSetWiFiTimer (CtSgwWiFiTimer1_t *obj);


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
int CtSgwAddWiFiTimer(CtSgwWiFiTimer1_t *obj);


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
int CtSgwDelWiFiTimer(CtSgwObjPath_t path);


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
int CtSgwGetLEDObjs(CtSgwLED_t **objs, int *count);


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
int CtSgwGetLED(CtSgwObjPath_t path, CtSgwLED_t *obj);


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
int CtSgwSetLED(CtSgwLED_t *obj);


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
int CtSgwSetNFC(CtSgwNFC_t *obj);


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
int CtSgwGetNFC(CtSgwNFC_t *obj);


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
int CtSgwGetSleepTimerObjs(CtSgwSleepTimer_t **objs, gint32 *count);


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
int CtSgwGetSleepTimer(CtSgwObjPath_t path, CtSgwSleepTimer_t *obj);


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
int CtSgwSetSleepTimer(CtSgwSleepTimer_t *obj);


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
int CtSgwAddSleepTimer(CtSgwSleepTimer_t *obj);


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
int CtSgwDelSleepTimer(CtSgwObjPath_t path);
    

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
                       char password[MAX_PASSWORD_LEN+1]);


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
int CtSgwSysCmdRegisterLOID(void);


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
int CtSgwSysCmdCheckLOID(void );


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
int CtSgwSysCmdSetDateTime(char datetime[MAX_TIME_LEN+1]);


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
int CtSgwSysCmdSetDevName(char devname[MAX_DEVNAME_LEN+1]);


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
int CtSgwSysCmdReboot(void);


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
int CtSgwSysCmdRestore(void);


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
int CtSgwSysCmdUpgrade(char url[MAX_URL_LEN+1], int mode, int method);


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
int CtSgwSysCmdCheckUAPasswd(const char *pass, int *result);


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
int CtSgwSysCmdCheckTAPasswd(const char *pass, int *result);


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
int CtSgwSysCmdSubscribe(void);


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
int CtSgwGetWANPPPConnObjs(CtSgwWANPPPConn_t **objs, int *count);


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
int CtSgwGetWANPPPConn(CtSgwObjPath_t path, CtSgwWANPPPConn_t *objs);


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
int CtSgwSetWANPPPConn (CtSgwWANPPPConn_t *obj);


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
int CtSgwGetWANIPConnObjs(CtSgwWANIPConn_t **objs, int *count);


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
int CtSgwGetWANIPConn(CtSgwObjPath_t path, CtSgwWANIPConn_t *obj);


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
int CtSgwSetWANIPConn (CtSgwWANIPConn_t *obj);


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
int CtSgwGetDHCPServerObjs(CtSgwDHCPServer_t **objs, int *count);


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
int CtSgwGetDHCPServer(CtSgwObjPath_t path, CtSgwDHCPServer_t *obj);


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
int CtSgwSetDHCPServer(CtSgwDHCPServer_t *obj);


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
int CtSgwSetUplinkQos(CtSgwUplinkQoS_t *obj);


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
int CtSgwGetUplinkQoS(CtSgwUplinkQoS_t *obj);


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
int CtSgwGetUplinkQoSAppRuleObjs(CtSgwUplinkQoSAppRule_t **paths, int *count);


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
int CtSgwGetUplinkQoSAppRule(CtSgwObjPath_t path, CtSgwUplinkQoSAppRule_t *obj);


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
int CtSgwSetUplinkQoSAppRule(CtSgwUplinkQoSAppRule_t *obj);


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
int CtSgwAddUplinkQoSAppRule(CtSgwUplinkQoSAppRule_t *obj);


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
int CtSgwDelUplinkQoSAppRule(CtSgwObjPath_t path);


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
int CtSgwGetUplinkQoSClsRuleObjs(CtSgwUplinkQoSClsRule_t **objs, int *count);


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
int CtSgwGetUplinkQoSClsRule(CtSgwObjPath_t path, CtSgwUplinkQoSClsRule_t *obj);


/*
 * Function Name: CtSgwAddUplinkQoSClsRule
 *
 * Description  : add a new QoS classification rule.
 *
 * Parameter:
 *      obj <IN>: A CtSgwUplinkQoSAppRule_t struct containing the QoS classification rule information.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgwAddUplinkQoSClsRule(CtSgwUplinkQoSAppRule_t *obj);


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
int CtSgwDelUplinkQoSClsRule(CtSgwObjPath_t path);


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
int CtSgwSetUplinkQoSClsRule(CtSgwUplinkQoSClsRule_t *obj);


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
int CtSgwGetUplinkQoSClsMatch(CtSgwObjPath_t path, CtSgwUplinkQoSClsMatch_t *match);


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
int CtSgwAddUplinkQoSClsMatch(CtSgwUplinkQoSClsMatch_t *match);


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
int CtSgwDelUplinkQoSClsMatch(CtSgwObjPath_t path);


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
int CtSgwSetUplinkQoSClsMatch (CtSgwUplinkQoSClsMatch_t *match);



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
int CtSgwGetPortMappingObjs(CtSgwPortMapping_t **objs, int *count);



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
int CtSgwGetPortMapping(CtSgwObjPath_t path, CtSgwPortMapping_t *obj);



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
int CtSgwAddPortMapping(CtSgwPortMapping_t *obj);


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
int CtSgwDelPortMapping(CtSgwObjPath_t path);


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
int CtSgwSetPortMapping(CtSgwPortMapping_t *obj);


#if 0
int ctsgw_usbRegister(CtUsbDevType type);


int ctSgw_usbUnregister(void);


int ctSgw_usbLock(int devId);


int ctSgw_usbUnlock(int devId);


int ctSgw_usbOpen(int devId, int *handle);


int ctSgw_usbDataAvailable(int handle);


int ctSgw_usbRead(int handle, void *buf, size_t *count, int timeout);


int ctSgw_usbWrite(int handle, const void *buf, size_t *count);


int ctSgw_usbSetSerial(int handle, const CtUsbSerialCfg *serialCfg);


int ctSgw_usbClose(int handle);


int CtSgw_USBMount(guint32 devid, char mount_path[MAX_PATH_LEN+1]);


int CtSgw_USBUnMount(char mount_path[MAX_PATH_LEN+1]);

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
int CtSgw_GetUSBDeviceObjs(CtSgw_USBDevice_t **objs, int *count);


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
int CtSgw_GetUSBDevice(CtSgwObjPath_t path, CtSgw_USBDevice_t *obj);


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
int CtSgw_SetNASConfig(CtSgw_NASConfig_t *obj);


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
int CtSgw_GetNASConfig(CtSgw_NASConfig_t *obj);


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
int CtSgw_NAS_GetFileNum(char foldername[MAX_PATH_LEN+1]);


/*
 * Function Name: CtSgw_NAS_ListFolder
 *
 * Description  : List all the files and folders in a specified folder.
 *
 * Parameter:
 *     foldername  <IN>:   The folder name.
 *       fileList <OUT>:  The entries represent the files and folders.
 *
 * Return:   0 on sucess, -1 on error.
 *
 */
int CtSgw_NAS_ListFolder(char *folderName, CtSgw_FileEntry_t **fileList);


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
int CtSgw_NAS_CreateFolter(gchar *folderName);


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
int CtSgw_NAS_ReName(gchar *oldName, gchar *newName);


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
int CtSgw_NAS_Remove(gchar *name);


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
int CtSgw_NAS_Move(gchar *filename, char *destFolderName);


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
int CtSgw_NAS_Copy(gchar *name, gchar *destFolderName);


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
int CtSgw_NAS_GetCopyProgress(guint32 transactionId);


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
int ctSgw_wanCreateL2tpTunnel(const char *serverIpAddr, const char *username, const char *password, char *tunnelName, int len);


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
int ctSgw_wanRemoveL2tpTunnel(const char *tunnelName);


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
int ctSgw_wanAttachL2tpTunnel(const char *tunnelName, const gchar *ipAddrList, int ipAddrNum);


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
int ctSgw_wanDetachL2tpTunnel(const char *tunnelName, const char *ipAddrList, int ipAddrNum);


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
int ctSgw_wanGetL2tpTunnelStatus(const char *tunnelName, int *tunnelStatus);


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
int CtSgw_AddDNSTunnel(const char *domain_name, const char *server);


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
int CtSgw_DelDNSTunnel(const char *domain_name);


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
int CtSgw_SetFtpServer(CtSgw_FTPServerConfig_t *obj);


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
int CtSgw_GetFTPServer(CtSgw_FTPServerConfig_t *obj);


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
int CtSgw_GetFTPAccountObjs(CtSgw_FTPAccount_t **objs, int *count);


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
int CtSgw_GetFTPAccount(CtSgwObjPath_t path, CtSgw_FTPAccount_t *obj);


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
int CtSgw_AddFtpAccount(CtSgw_FTPAccount_t *obj);


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
int CtSgw_DelFtpAccount(CtSgwObjPath_t path);


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
int CtSgw_GetSambaServer(CtSgw_SambaServerConfig_t *obj);


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
int CtSgw_SetSambaServer(CtSgw_SambaServerConfig_t *obj);


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
int CtSgw_GetSambaAccountObjs(CtSgw_SambaAccount_t **objs, int *count);


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
int CtSgw_GetSambaAccount(CtSgwObjPath_t path, CtSgw_SambaAccount_t *obj);


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
int CtSgw_AddSambaAccount(CtSgw_SambaAccount_t *obj);


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
int CtSgw_DelSambaAccount(CtSgwObjPath_t path);


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
int CtSgw_GetHttpServer(CtSgw_HttpServerConfig_t *obj);


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
int CtSgw_SetHttpServer(CtSgw_HttpServerConfig_t *obj);


#endif
