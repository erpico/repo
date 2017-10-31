#ifndef __LICENSE_H__
#define __LICENSE_H__

#ifdef LICENSE_EXPORTS
#define LICENSE_API __declspec(dllexport)
#else
#define LICENSE_API __declspec(dllimport)
#endif

#define DB_SVC_REQTYPE 0x1B6A8D9F
#define DB_SVC_REQTYPE_APP 0xC2D3BCAE
#define DB_SVC_REQTYPE_APP_MODULE 0x3A809B1F
#define DB_SVC_RESPONSE_IP_TYPE 0x7A6A1D97
#define DB_SVC_RESPONSE_MODULE_TYPE 0x5D4F1D28
#define DB_SVC_RESPONSE_LICENSE_LIMIT 0x7F1D93A8
#define DB_SVC_PORT 8920

#define DB_SVC_STATUS_NITIFI 0x2DA01F2E

#define DB_SVC_FLAG_REMOTE_OFFICE 0x01

class LICENSE_API CLicense {
  public:
  typedef struct tagMysqlConfig {
    char user[64];
    char password[128];
    char host[64];
    char dbName[64];
    long port;
    char AppName[256];
    int datbaselimit;//for future 
    tagMysqlConfig() {
      memset(this, 0, sizeof(*this));
    }
    ~tagMysqlConfig() {
      memset(this, 0, sizeof(*this));
    }
  } MYSQL_CONFIG;

  struct sDBRequestApp
  {
    DWORD dwSize;
    DWORD dwType; //Only DB_SVC_REQTYPE_APP must be now!
    DWORD sessionId;
    char key[256];
    char strComputer[256];
    char strUser[256];
    char strDomain[256];
    char strApp[256];
    DWORD dwFlags;
  };

  struct sDBResponse {
    DWORD dwSize;
    CLicense::MYSQL_CONFIG m_Config;
  };
  struct sDBResponseApp {
    DWORD dwSize;
    CLicense::MYSQL_CONFIG m_Config;
    DWORD dwFlags;
  };

  struct sDBResponseIp
  {
    DWORD dwSize;
    DWORD dwType; //Only DB_SVC_REQTYPE_APP_MODULE must be!
  };

  struct sDBRequestAppModule
  {
    DWORD dwSize;
    DWORD dwType; //Only DB_SVC_REQTYPE_APP must be now!
    char strApp[256];
  };
  class sDBResponseAppModule
  {
  public:
    DWORD dwSize;
    DWORD dwType; //Only DB_SVC_RESPONSE_MODULE_TYPE must be!
    int CityID;
    char param[256];
    char modules[256] ;
    char allowed_cities[256] ;
  };
  class sDBResponseLicenseLimit
  {
  public:
    DWORD dwSize;
    DWORD dwType; //Only DB_SVC_RESPONSE_LICENSE_LIMIT must be!
  };

  struct sConnectionStatusNotification
  {
    DWORD dwSize;
    DWORD dwType; //Only DB_SVC_STATUS_NITIFI must be!
    char AppName[256];
    bool status;
  };

  public: 

  static void SetAuthOptions(const char* strAuthServer, const char* strComputerName, const char* strUserLogin, const char* strDCHost, const char* strAppAuthName);

  static BOOL GetDBConnectionCrendals(CLicense::MYSQL_CONFIG* pConfig, DWORD* pFlags = 0);
  static int GetLicenseParams(sDBResponseAppModule* pParams);

  static CString GetServerInfoHost();
  static bool FillUnicKey(CString & key);

  static int sendToInfoServerStatus(bool status);

};


#endif // __LICENSE_H__
