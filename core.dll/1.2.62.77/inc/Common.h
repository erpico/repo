#pragma once

#include "MySQL.h"
#include <locale.h>

#include <bitset>
#include <list>
#include <vector>

#define MAX_STR_LEN 2048

#include "Core.h"

#include "Core/Strings.h"
#include "Core/json/json.h"

class CUser;

// Use RSCommonInitLib intshead of declare this functions

extern CORE_API const char* ( __stdcall *GetUserLoginFunction )();
extern CORE_API const char* ( __stdcall *GetUserFullNameFunction )();
extern CORE_API const char* ( __stdcall *GetUserAuthTokenFunction )();
extern CORE_API const char* ( __stdcall *GetUserComputerNameFunction )();
extern CORE_API std::string ( __stdcall *GetAppVersionFunction )();
extern CORE_API const char* ( __stdcall *GetAppNameFunction )();
extern CORE_API const char* ( __stdcall *GetDomainControllerHostFunction )();
extern CORE_API BOOL ( __stdcall *IsInteractiveAppFunction )();
extern CORE_API int ( __stdcall *GetDefaultCityFunction )();

// Custom log
extern CORE_API void ( __stdcall *AddToLogFunction )( const char *fmt, const va_list &arg_list);

// Outbound calls
extern CORE_API BOOL ( __stdcall *MakeOutboundCallFunction )(const char* strPhone);

// Логин текущего пользователя
CORE_API std::string GetUserLogin();

// Полное имя текущего пользователя
CORE_API std::string GetUserFullName();

CORE_API const char* GetUserAuthToken();

// Имя компьютера
CORE_API std::string GetUserComputerName();

// Версия приложения
CORE_API std::string GetAppVersion();

// Название приложения
CORE_API std::string GetAppName();

// Название приложения для авторизации
CORE_API std::string GetAppNameAuth();

// IP-адрес контролера домена
CORE_API std::string GetDomainControllerHost();

// Добавления записи в лог
CORE_API void AddToLog( const char *fmt, ...);

CORE_API BOOL IsInteractiveApp();
CORE_API int GetDefaultCity();
CORE_API int GetCity();
CORE_API void SetCity(int nCityId);
CORE_API void GetCoords(double &_dLongitude, double &_dLatitude);
CORE_API void SetCoords(double _dLongitude, double _dLatitude);
CORE_API void GetCoordsById(int _nCityId, double &_dLatitude, double &_dLongitude);
CORE_API void SetRegion(const char* _strRegionId);
CORE_API std::string GetRegionName();
CORE_API std::string GetRegion();
CORE_API std::string GetRegionByCity(int _iCity);
CORE_API int IsCityAllowed(int nCityId);
CORE_API CUser* GetUserObj();
CORE_API int IsUserInGroup(const char* strGroup);
CORE_API const char* GetFullUserName(const char* user, const char* strDescription = 0);
template<size_t destSize> 
inline void GetFullUserName(const char* user, char (&dest)[destSize]) {
  GetFullUserName(user, dest, destSize);
}
CORE_API void GetFullUserName(const char* user, char* dest,  size_t destSize, 
    char* description = 0, size_t descriptionSize = 0);
CORE_API int IsUserInGroup(const char* strGroup);

enum EReturnCode
{
  RET_ERROR = 0,
  RET_OK    = 1,

  RET_WRONG_COST = 1000,
  RET_CLIENT_HAS_DEBT = 1001,
  
  RET_NOT_FOUND = 1404
};

struct stParams
{
  int         iId;
  int         iServiceId;
  std::string strValue;
};

#define ShowError() GlobalShowError(__FILE__, __LINE__);
#define ShowErrorEx(x) GlobalShowError(__FILE__, __LINE__, x);

inline void GlobalShowError(const char* strFile, int nLine, const char* comment = 0) {
  char strErr[256];
  if (comment) sprintf_s(strErr, "Error \"%s\" occurs in file %s on line %i.",  comment, strFile, nLine);
  else sprintf_s(strErr, "Unspecified error occurs in file %s on line %i.",  strFile, nLine);
  AddToLog(strErr);
  //::MessageBox(::GetForegroundWindow(), strErr, 0, MB_ICONERROR);
}

inline std::string CorrectTimeForSQL(const std::string &_strTime)
{
  std::string strTimeValue = _strTime;

  if (strTimeValue.empty()) strTimeValue = "0000-00-00 00:00:00";

  return strTimeValue;
}

inline std::string toMySQLtime(time_t time) 
{ 
  char chBuff[32];

  if (time > 0 ) {
    strftime(chBuff, sizeof(chBuff) - 1, "%Y%m%d%H%M%S", localtime(&time));
  } else {
    strcpy(chBuff, "00000000000000");

  }

  std::string str(chBuff);
  return str;
}

inline std::string AddSlashes(const char* str)
{
  if (str == NULL) return string("");
  
  std::string result(str);
  std::string strTmp(str);

  trim(strTmp, result);

  replace(result, "\\", "\\\\");
  replace(result,  "\'", "\\\'");
  replace(result,  "\"", "\\\"");

  return result;  
}

inline std::string ToMySQLtime(time_t _tmTm)
{
  char chBuff[32];
  strftime(chBuff, 31, "%Y%m%d%H%M%S", localtime(&_tmTm));
    
  return string(chBuff);
}

inline std::string toMySQLfloat(double dValue, int nPrec = 2) {
  std::string res;
  char tmp[32];
  char fmt[8];
  memset(tmp, 0, sizeof(tmp));
  memset(fmt, 0, sizeof(fmt));
  sprintf(fmt, "%%.%df", nPrec);
  sprintf(tmp, fmt, dValue);
  res = tmp;
  replace(res, ",", ".");

  return res;
}

inline double fromMySQLfloat(const char* str) {
  if (!str) return 0;
  std::string tmp = str;
    struct lconv* myLconf = localeconv();
    if  (tmp.find(myLconf->decimal_point) == -1) {
      if (myLconf->decimal_point[0] == ',') {
        replace(tmp, ".", ",");
      } else {
        replace(tmp, ",", ".");
      }
    }
  return strtod(tmp.c_str(), 0);
}

template<size_t size> 
inline char* NormalizeFIO(char (&src)[size]) {
  return NormalizeFIO(src, size);
}

inline char* NormalizeFIO(char* strSrc, size_t size) {
   if (!_strlwr_s(strSrc, size)) {
    return strSrc;
   }
   char* p = strSrc;
   int   bNextSymUpper = 1;
   char tmp[2];

   for (;*p != 0;p++) {
     if (*p == ' ') {
       bNextSymUpper = 1;
       continue;
     }
     if (bNextSymUpper) {
       tmp[0] = *p; tmp[1] = 0;
       _strupr_s(tmp);
       *p = tmp[0];
     }
     bNextSymUpper = 0;
   }
   return strSrc;
}

inline bool IsIntDigit(const char *s)
{
  if (s == NULL) return false;
  for(int i = 0; i < (strlen(s) - 1); i++) {
    if(!isdigit(s[i]))
      return false;
  }
  return true;
}
//------------------------------

#define CLIENT_LOOKUP_MAX 32

typedef struct tarRemoteOfficesName {
  int nId;
  std::string strName;
  time_t last_sync;
  int coIdleTime;
} REMOTE_OFFICE_NAME;

typedef std::list<REMOTE_OFFICE_NAME> REMOTE_OFFICES_ARRAY;

typedef struct tagTHREADNAME_INFO
{
   DWORD dwType; // must be 0x1000
   LPCSTR szName; // pointer to name (in user addr space)
   DWORD dwThreadID; // thread ID (-1=caller thread)
   DWORD dwFlags; // reserved for future use, must be zero
} THREADNAME_INFO;

CORE_API void SetThreadName(LPCSTR szThreadName);
CORE_API void TimeStampToSysTime(DWORD Unix, SYSTEMTIME* SysTime);

#define PHONE_MAX_COUNT 8
#define PHONE_MAX_LEN 16

inline void tileParseBlock(char*& in, char*& out, int szBlock, int nBlocks) {
  for (int i = 0; i < nBlocks; i++) {
    for (int j = 0; j < szBlock; j++) *out++ = *in++;
    *out++ = ' ';
  }
}

int CORE_API RSCommonInitLib(const char* strAppName,          // App name
                              const char* strAppVersion,      // App version
                              BOOL isInteractiveApp,          // Is application can utreract with user? (display dialogs, etc)?
                              const char* strAppAuthName = 0, // App name for Auth service (for utilites),
                              char  * pStrError      = 0      // Error description
                              );
int CORE_API RSCommonReleaseLib();

class CORE_API CCommon {
public:

  enum eParams{
    SMS_TO_CLIENTS                      = 1,
    SMS_TO_EXUCATORS                    = 2,
    BLACK_LIST_MANAGER_NOTIFY_EMAIL     = 3,
    DEFAULT_SMS_GATEWAY                 = 4,
    OSMP_BALANCE                        = 5,
    CALC_DEFAULT_ACTIVE                 = 6,
    CALC_CAN_DISABLED                   = 7,
    MOBW_BALANCE                        = 8,
    REPORTS_OPERATORS_PRICES            = 9,
    CLIENTS_PRIORITY_ORDERS_COUNT       = 10,
    CLIENT_TRIP_COUNT_ABOVE             = 11,
    CLIENT_TRIP_30_DAYS_SUM_ABOVE       = 12,
    CLIENT_TRIP_30_DAYS_COUNT_ABOVE     = 13,
    CLIENT_TRIP_CREDIT_PERCENT          = 14,
    QUALITY_CONTROL_DEP_EMAIL           = 15,
    PARTNERS_REQ_INFO_ACTIVE            = 16,
    CLIENT_SMS_FORMAT                   = 17,
    PC_SUPERVISOR                       = 18,
    AUTO_TTS_CARREADY                   = 19,
    CLIENT_TTS_FORMAT                   = 20,
    SMS_NONCLIENT_AFTERORDER            = 21,
    CAR_OPEN_CLOSE_MANAGER_NOTIFY_EMAIL = 22,
    J2ME_DRIVER_APP_VERSION             = 23,
    J2ME_DRIVER_APP_DLOAD_URL           = 24,
    ENABLE_GOOD_MAN_ACTION              = 25,
    GOOD_MAN_ACTION_BONUS               = 26,
    GOOD_MAN_ACTION_BONUS_PERIOD        = 27,
    PUT_ON_TIME_INST                    = 28,
    GPS_TIMEOUT                         = 29,
    GPS_DISTANCE                        = 30,
    MINUTE_PRICE_PENALTY_CONDITION      = 31,
    COST_PENALTY_SMS_TEXT               = 32,
    COST_PENALTY_AMOUNT                 = 33,
    WIKI_URL                            = 34,
    AUTO_ASSIGN_CAR                     = 35,
    SEND_SMS_AFTER_REGISTER             = 36,
    SMS_WAITING_INTERVAL_BEFORE         = 37,
    SMS_WAITING_INTERVAL_BETWEEN        = 38,
    SMS_WAITING_FOR_DELIVERY_RECEIPT    = 39,
    AGENTS_COUNT_RED_ALARM              = 40,
    ENABLE_ORDERS_VALIDATION            = 41,
    USE_PRECALCULATED_PRICE             = 42,
    J2ME_DRIVER_SESSION_TIMEOUT         = 43,
    J2ME_DRIVER_ORDER_INTERACTIVE       = 44,
    DRIVER_ACTION_AFTER_ORDER_REFUSAL   = 45,
    J2ME_DRIVER_ORDER_ACCEPT_TIMEOUT    = 46,
    CLIENTS_DISABLED_SDACHA             = 47,
    EXECUTORS_DISABLED_LOAN             = 48,
    TAXI_ENABLE_SELFTAKING              = 49,
    J2ME_ENABLE_NEW_ORDERS_NOTIFY       = 50,
    J2ME_NEW_ORDERS_NOTIFY_DELAY_SECONDS= 51,
    SMTP_SERVER                         = 52,
    ORDERS_DISPATCHING_REASSIGN_ENABLE  = 53,
    ORDERS_DISPATCHING_REASSING_TIME_SLICE = 54,
    ORDERS_DISPATCHING_REASSIGN_DELAY   = 55,
    NIGHTDISCOUNT_ENABLE                = 56,
    NIGHTDISCOUNT_TIME_FROM             = 57,
    NIGHTDISCOUNT_TIME_TILL             = 58,
    NIGHTDISCOUNT_AMOUNT                = 59,
    NIGHTDISCOUNT_AMOUNT_TYPE           = 60,
    BIRTHDATE_SMS_SEND_ENABLE           = 61,
    BIRTHDATE_SMS_TEXT                  = 62,
    BIRTHDATE_ORDER_DISCOUNT_ENABLE     = 63,
    BIRTHDATE_ORDER_DISCOUNT_AMOUNT     = 64,
    ASTERISKDB_HOST                     = 65,
    ASTERISKDB_USER                     = 66,
    ASTERISKDB_PASSWORD                 = 67,
    ASTERISKDB_DBNAME                   = 68,
    SMS_SEND_ALLOW_FROM                 = 69,
    J2ME_SHOW_ORDERS_TO_TIME            = 70,
    EXECUTORS_DECLINE_GO_AWAY_HOURS     = 71,
    ASTERISK_AMI_HOST                   = 72,
    ASTERISK_AMI_PORT                   = 73,
    ASTERISK_AMI_USER                   = 74,
    ASTERISK_AMI_PASSWORD               = 75,
    CONFIRM_CALL_LONG_WAIT              = 76,
    TAXI_AUTO_DISPATCHER                = 77,
    ORDER_CANCEL_DEFAULT_CLIENT_SMS_TEXT = 78,
    ORDER_CANCEL_SEND_SMS_IF_CLIENT_DIDNT_GET_OUT = 79,
    ORDER_CANCEL_SEND_SMS_IF_CLIENT_DIDNT_WAIT = 80,
    SORT_ORDERS_BY_INCOMING_PHONE_LINES = 81,
    SHORT_TAXI_TABLE                    = 82,
    SHOW_RSDRIVER_ICON_IN_TAXI_TABLE    = 83,
    BIRTHDATE_SMS_HOUR                  = 84,
    BIRTHDATE_SMS_MINUTE                = 85,
    CLIENT_ORDER_SMS_ON_SET_EXECUTOR    = 86,
    SMS_TRANSLIT_BY_DEFAULT             = 87,
    SHOW_INCOMING_PHONE_LINE_IN_MOBILE_APP = 88,
    MOBILE_APP_GET_EXCHANGE_ORDERS_LIMIT = 89,
    SET_EXECUTOR_SECOND_ORDER_WARNING_DISABLE = 90,
    ORDER_CANCEL_ALLOW_SEND_SMS         = 91,
    MOBILE_APP_ALLOW_CALL_TO_CLIENT     = 92,
    CLIENT_LONG_DRIVER_WAIT_REPEAT_NOTIFY =93,
    WARN_IF_SIMILAR_ORDERS              = 94,
    STRICT_CONFORMITY_OF_ORDER_AND_EXECUTOR_TYPES = 95,
    FILL_DISTRICT                       = 96,
    AUTO_ORDER_TRANSFER                 = 97,
    CALC_COST_MIN_LENGTH                = 98,
    CALC_ROUTE_WITH_MAP                 = 99,
    TAXI_AUTO_DISPATCHER_DELAY          = 100,
    AKCIYA_ON_REGISTER                  = 101,
    SMS_WITH_EXECUTOR_CREDENTIALS       = 102,
    HIDE_PRICE                          = 103,
    TIME_FOR_PRELIMINARY                = 104,
    BILLING_DONT_CHARGE_FOR_CASHLESS    = 105,
    SETCAR_NOT_FINE_DECLINED_DRIVERS    = 106,
    NEW_ORDER_WITH_INCOMPLETE           = 107,
    LOCALITY_TYPE                       = 108,
    DRIVER_FAR                          = 109,
    DRIVER_SPY                          = 110,
    DRIVER_LAZY                         = 111,
    CLIENT_REGULAR                      = 112,
    TAXIMETER_DRIVER                    = 113,
    CALC_FROM_DISTANCE_DIC              = 114,
    TIME_FOR_CANCEL_RESERVED            = 115,
    TIME_FOR_CANCEL_RESERVED_ENABLE     = 116,
    TIME_FOR_CLOSING_DRIVERS            = 117,
    TIME_FOR_CLOSING_DRIVERS_ENABLE     = 118,
    ALLOW_MULTIPLE_ORDERS_FROM_SAME_ADDRESS = 119,
    KLAVTO_PHOTO_HTTP_PATH              = 120,
    KLAVTO_PHOTO_SMB_PATH               = 121,
    ONE_SIGNAL_AUTH_DRIVER_APP          = 122,
    ONE_SIGNAL_ID_DRIVER_APP            = 123,
    NEWS_URL                            = 124,
    BTONE_SIGN                          = 125,
    BTONE_DRIVER_CONFIRMATION_URL       = 126,
    BTONE_DRIVER_EMAIL_SERVER           = 127,
    BTONE_CANCELLATION_TIME             = 128,
    BTONE_DRIVER_INFO_SENDING_TIME      = 129,
    BTONE_SUBMISSION                    = 130,
	AUTO_TTS_CAR_INTERVAL_BEFORE        = 131,
    WEB_PLATFORM_URI                    = 132,
    TAXI_GLOBAL_ORDERS                  = 133,
    EXECUTOR_BIRTHDATE_SMS_SEND         = 134,
    SMS_RU_API_ID                       = 135,
    SMS_RU_URL                          = 136,
    WEB_MAIL_SEND                       = 137,
    PAYMENT_CONFIRM                     = 138,
    PAYMENT_CANCEL                      = 139,
    WEB_API                             = 140,
    ONE_SIGNAL_AUTH_CLIENT_APP          = 141,
    ONE_SIGNAL_ID_CLIENT_APP            = 142,
    BUS4US_SIGN                         = 143,
    YANDEX_DISTANCE_MATRIX_KEY          = 144,
    GOOGLE_DISTANCE_MATRIX_KEY          = 145,
    ONE_SIGNAL_AUTH_WEB                 = 146,
    ONE_SIGNAL_ID_WEB                   = 147,
    DRIVER_MOBILE_CONNECTION_STATE1     = 148,
    DRIVER_MOBILE_CONNECTION_STATE2     = 149,
    BUS4US_TEXT_TO_CLIENT_IN_4_HOURS    = 150,
    BUS4US_CLIENT_PUSH_CALLING          = 151,
    BUS4US_CLIENT_PUSH_CALLNOW          = 152,
    BUS4US_CLIENT_PUSH_CALLED           = 153,
    BUS4US_CLIENT_PUSH_FINISH           = 154,
    BUS4US_SMS_TO_DRIVER_SETCAR         = 155,
    BUS4US_SMS_TO_DRIVER_IN_4_HOURS     = 156
  };

  typedef struct {
    std::string name;
    std::string prefix;
    int     nServer;
  } sSmsRoutingTable;

  typedef struct {
    int id;
    std::string name;
    int sent;
    int state;
  } sSmsServer;

  inline static bool UsePrecalculatedPrice()
  {
    return CCommon::GetParamInt(CCommon::USE_PRECALCULATED_PRICE, GetCity()) == 1;
  }

  inline static void phone_ToPlain(const char * in, char * out, bool _bBTONE = false)
  {
    const char* pIn = in;
    char* pOut = out;
    char* pBegin = out;
    while (*pIn != 0)
    {
      if (((*pIn >= '0') && (*pIn <= '9')) || (*pIn == '+')) *pOut++ = *pIn;
      pIn++;
    }
    *pOut = 0;

    if (_bBTONE)
    {
      pOut = pBegin;

      if ((strlen(pOut) == 10) && (pOut[0] != '8'))
      {
        std::string str = "8";
        str += pOut;
        strncpy(pOut, str.c_str(), 11);
      }
      else if ((strlen(pOut) == 11) && (pOut[0] == '7'))
      {
        pOut[0] = '8';
      }
      else if ((strlen(pOut) == 12) && (pOut[0] == '+') && ((pOut[1] == '8') || (pOut[1] == '7')))
      {
        pOut[1] = '8';
        memmove(pOut, pOut + 1, strlen(pOut));
      }
    }
    
    /*if (strlen(out) >= 10 && out[0] != '8' && out[0] != '+') {
      // Number without "8".
      pOut++;
      *pOut = 0;
      pOut--;
      while (pOut != out) {
        *pOut = *(pOut-1);
        pOut--;
      }
      *out='8';
    }*/
  }


  inline static int phone_Extract(char* in, std::string arrOut[PHONE_MAX_COUNT]) {
    if (in == NULL || arrOut == NULL) return 0;
    char* curPhone = NULL;
    int curPos = 0;
    int nArrPos = 0;
    char *chPhoneIn = new char[strlen(in) + 1];
    strcpy(chPhoneIn , in);

    curPhone = strtok(chPhoneIn, ";,.");
    while ((curPhone != NULL) && (nArrPos < PHONE_MAX_COUNT))
    {
      //arrOut[nArrPos] = new char[strlen(curPhone) + 1];
      //strcpy(arrOut[nArrPos], curPhone);
      arrOut[nArrPos++] = curPhone;      
      curPhone = strtok(NULL, ";,.");
    }
    int count = nArrPos;
    if (nArrPos < PHONE_MAX_COUNT)
      arrOut[nArrPos++] = "";

    if (chPhoneIn) delete[] chPhoneIn;

    return count;
  }

  inline static bool phone_Validate(const char * phone, bool _bBTONE = false)
  {
    if (phone == NULL) return false;
    
    if (!_bBTONE)
    {
      if ((strlen(phone) > 8) && (strlen(phone) < PHONE_MAX_LEN) && (phone[0] == '8'))
      {
        return true;
      }
      else if ((strlen(phone) > 9) && (strlen(phone) < PHONE_MAX_LEN) && (phone[0] == '+'))
      {    
        return true;
      }
      else if (strlen(phone) >= 3 && strlen(phone) < 8)
      { 
        return true;
      }
    }
    else
    {
      if ((strlen(phone) == 11) && (phone[0] == '8'))
      {
        return true;
      }
    }
    
    return false;
  }

  template<size_t size> inline static void phone_Format(const char *in, char (&out)[size]) {
    phone_Format(in, out, size);
  }

  inline static void phone_Format(const char* in, char* out, size_t size)
  {
    if (in == NULL || out == NULL) return;

    char tmp[128];
    strcpy_s(tmp, in);
    char* pIn = tmp;
    if (strlen(tmp) == 6) {
      tileParseBlock(pIn, out, 2, 3);
      *--out = 0;
    } else if (strlen(tmp) == 11) {
      tileParseBlock(pIn, out, 1, 1);
      if (strncmp(pIn, "485", 3) == 0) {
        tileParseBlock(pIn, out, 4, 1);
        tileParseBlock(pIn, out, 2, 1);
      } else {
        tileParseBlock(pIn, out, 3, 2);
      }
      tileParseBlock(pIn, out, 2, 2);
      *--out = 0;
    } else if (strlen(tmp) == 9) {
      tileParseBlock(pIn, out, 1, 1);
      tileParseBlock(pIn, out, 3, 2);
      tileParseBlock(pIn, out, 2, 1);
      *--out = 0;
    } else strcpy_s(out, size, in);
  }

  static std::string phone_FetchMobile(char* sepPhones, int& nPhone);
  static std::string phone_FetchMobile(char* sepPhones) {
    int nPhone = 0;
    return phone_FetchMobile(sepPhones, nPhone);
  }
  static std::string phone_FetchMobileOrFirst(char* sepPhones);
  static void phone_NormalizeList(char* out, size_t outLen);
  static BOOL SendSMS(const char* number, const char* message, int nPriority = 0,
      DWORD * dwMID = 0, int nGateway = -1, DWORD _dwUserId = 0, BOOL bTranslit = -1, const char* strFrom = 0);
  template<size_t smscIDSize> inline static bool GetSMSStatus(DWORD dwMid, DWORD *dwStatus, char (&smscID)[smscIDSize],
      long long *llTimeSent, long long *llTimeDelivered) {
    return GetSMSStatus(dwMid, dwStatus, smscID, smscIDSize, llTimeSent, llTimeDelivered);
  }
  static bool GetSMSStatus(DWORD dwMid, DWORD *dwStatus, char *smscID, size_t smscIDSize,
                  long long *llTimeSent, long long *llTimeDelivered);
  static BOOL SendToTTS(const char* number, const char* message, int nType, DWORD * dwRID, time_t tmToPlay = 0, DWORD dwDataId = 0, const char* wwwPrompt = 0);
  static BOOL CancelTTSReq(DWORD dwId, DWORD dwDataId = 0);
  static BOOL SendEMail(const char* to, const char* subj, const char* message, const char* strFile = NULL);
  static BOOL SaveParam(CCommon::eParams param, const char* value, int iServiceId = 0);
  static std::string GetParam(CCommon::eParams param, int iServiceId = 0);
  static int GetParamInt(CCommon::eParams param, int iServiceId = 0);
  static const char* GetParamCstr(CCommon::eParams param, int iServiceId = 0);
  static void GetParam(CCommon::eParams param, std::vector<stParams> &vect);
  static int  MakeCall(const char *phone);
  static BOOL IsMobileNumber(const char* pBuf);
  static int GetSmsRoutingTable(CCommon::sSmsRoutingTable** pTable);
  static int GetSmsServers(CCommon::sSmsServer** pTable);
  static int SaveSmsRoutingTable(CCommon::sSmsRoutingTable* pTable, int nCount);

  static int StartProgram(const char* strApp, const char* strObject);
  static std::string GetRemoteOfficeName(int nId);
  static REMOTE_OFFICES_ARRAY* GetRemoteOfficesList();

  static int GetLicense(/*CLicense::sDBResponseAppModule*/void* pLicense);

  // преобразивание из ansi в utf8
  static bool win32_ansi_to_utf8(const char* ansi_str, char* utf8_str, int utf8_len);
  static bool utf_to_win32_ansi(const char* utf8_str, char* ansi_str, int ansi_len);

  static time_t GetDBTime();

  static int ShortLinkCreate(Json::Value &data, string& link);
  static int ShortLinkGetData(const char* link, Json::Value& data);

  static int CheckIEMode();
};


typedef struct tagMyDate {
  int day;
  int month;
  int year;
  
  tagMyDate() {
    memset(this, 0, sizeof(*this));
  };
  
  void operator = (const char* str){
    if (strlen(str) == 10) {
      year = atoi(str);
      month = atoi(str + 5);
      day = atoi(str + 8);
    }
  }
  
  std::string GetString() {
    char str[32];
    sprintf(str, "%04i-%02i-%02i", year, month, day);
    return string(str);
  }
  
  int GetAge()
  {
    if(year == 0)
      return 0;

    time_t t = time(0);
    tm time = *localtime(&t);
    
    int nAgeYears = (time.tm_year + 1900) - year;
    if(nAgeYears <= 0)
      return 0;

    if(month > time.tm_mon)
      nAgeYears--;

    return nAgeYears;
  }

  DWORD GetTimestamp()
  {
    time_t timeStamp = 0;
    struct tm timeSet;
    memset(&timeSet, 0, sizeof(tm));

    if (year == 0 || month == 0 || day == 0) return 0;
    
    timeSet.tm_year = year - 1900;
    timeSet.tm_mon  = month - 1;
    timeSet.tm_mday  = day;
    timeStamp =  mktime(&timeSet);

    return timeStamp;
  }
} MY_DATE;

int CORE_API InitializeCore(const char* strAppName, const char* strAppVersion, BOOL isInteractiveApp, 
							std::list<long> cityIds, const CMySQL::MYSQL_CONFIG &dbConfig, std::string &strError);
int CORE_API ReleaseCore();

#define SMS_ID_MAX_LEN 128