#ifndef __CITIES_H__
#define __CITIES_H__

#define __CITIES_H__

#include "Core.h"
#include <list>
#include "Core/json/json.h"


class CORE_API CCities {
public:
  struct sCity
  {
    unsigned long dwId;
    std::string strName;
    std::string strCityName;
    std::string strServiceName;
    std::string strCountry;
    std::string strRegion;
    std::string strRegionId;
    double      dCityLongitude;
    double      dCityLatitude;
    std::string strEntity;
    std::string strAccount;
    std::string strLicense;
    std::string strOrgCard;
    std::string strCompanyCharter;
    std::string strPhone;
    std::string strPhoneForSms;
    std::string strServiceId;
    int         iActive;
    std::string strGeoAddr;
    DWORD       dwOrgForm;
    std::string strEmail;
    int         iSendLetter;
    int         iDeleted;
    std::string strLogin;
    std::string strPassword;
    DWORD       dwSendingLetterTime;
    DWORD       dwSendingNoDriverLetterTime;

    sCity()
    {
      Init();
    }

    void Init()
    {
      dwId                        = 0;
      strName                     = "";
      strCityName                 = "";
      strServiceName              = "";
      strCountry                  = "";
      strRegion                   = "";
      strRegionId                 = "";
      dCityLongitude              = 0.0;
      dCityLatitude               = 0.0;
      strEntity                   = "";
      strAccount                  = "";
      strLicense                  = "";
      strOrgCard                  = "";
      strCompanyCharter           = "";
      strPhone                    = "";
      strPhoneForSms              = "";
      strServiceId                = "";
      iActive                     = 0;
      strGeoAddr                  = "";
      dwOrgForm                   = 0;
      strEmail                    = "";
      iSendLetter                 = 0;
      iDeleted                    = 0;
      strLogin                    = "";
      strPassword                 = "";
      dwSendingLetterTime         = 0;
      dwSendingNoDriverLetterTime = 0;
    }

    sCity& operator = (const sCity &another)
    {
      dwId                        = another.dwId;
      strName                     = another.strName;
      strCityName                 = another.strCityName;
      strServiceName              = another.strServiceName;
      strCountry                  = another.strCountry;
      strRegion                   = another.strRegion;
      strRegionId                 = another.strRegionId;
      dCityLongitude              = another.dCityLongitude;
      dCityLatitude               = another.dCityLatitude;
      strEntity                   = another.strEntity;
      strAccount                  = another.strAccount;
      strLicense                  = another.strLicense;
      strOrgCard                  = another.strOrgCard;
      strCompanyCharter           = another.strCompanyCharter;
      strPhone                    = another.strPhone;
      strPhoneForSms              = another.strPhoneForSms;
      strServiceId                = another.strServiceId;
      iActive                     = another.iActive;
      strGeoAddr                  = another.strGeoAddr;
      dwOrgForm                   = another.dwOrgForm;
      strEmail                    = another.strEmail;
      iSendLetter                 = another.iSendLetter;
      iDeleted                    = another.iDeleted;
      strLogin                    = another.strLogin;
      strPassword                 = another.strPassword;
      dwSendingLetterTime         = another.dwSendingLetterTime;
      dwSendingNoDriverLetterTime = another.dwSendingNoDriverLetterTime;

      return *this;
    }

    bool operator==(const sCity &another)
    {
      return (this->dwId == another.dwId);
    }    
  };

  struct sFields
  {
    std::string strKey;
    std::string strValue;
  };

  static std::string GetName(DWORD dwId, int iSQLSearch = 0);
  static std::string GetServiceName(DWORD dwId, int iSQLSearch = 0);
  static int GetCities(std::list<sCity> & arrCities, const DWORD &_dwId = 0);
  static int GetCities(std::list<sCity> &cities, const std::list<long> &ids);
  static int GetCitiesFromOrders(std::list<int> &lstCities);
  static int GetCitiesByWorkChannels(std::list<CCities::sCity> &arrCities, const DWORD& dwWorkChannel);
  static bool InsertCities(const std::list<CCities::sCity> &_lstCities);
  static long long InsertServiceCity(const sCity &_stCity);
  static bool UpdateServiceCity(const sCity &_stCity);
  static bool DeleteServiceCity(const DWORD &_dwId);
  static bool RestoreServiceCity(const DWORD &_dwId);
  static int SelectServiceCity(const DWORD &_dwId, sCity &_stCity, const int &_iDeleted = 0);
  static bool CheckServiceId(const std::string &_strServiceId, const DWORD &_dwId = 0);

  static unsigned long GetIdByName(const char* strName, int iSQLSearch = 0);
  static std::string GetKladrId(const char* strName);
  static std::string GetKladrId(unsigned long dwId);
  
  static void RefreshCache(const DWORD &_dwId = 0);
  static void CheckCache(const DWORD &_dwId = 0);
  static void SetCitiesCache(const DWORD &_dwVal);
  static DWORD GetCitiesCache();

  static int SaveFieldValue(DWORD dwId, const char* szKey, const char* szValue);
  static int GetFieldsValues(DWORD dwId, std::list<sFields>& arr);
  static bool GetServiceCities(std::vector<std::string> &_vectServiceCities);
  static void SetServiceToJson(Json::Value &_jService, const sCity &_stCity);
};

#endif