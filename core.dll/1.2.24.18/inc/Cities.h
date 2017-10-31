#ifndef __CITIES_H__
#define __CITIES_H__

#define __CITIES_H__

#include "Core.h"
#include <list>

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
    std::string strLicence;
    std::string strOrgCard;
    std::string strCompanyCharter;
    std::string strPhone;
    std::string strPhoneForSms;

    sCity()
    {
      Init();
    }

    void Init()
    {
      dwId              = 0;
      strName           = "";
      strCityName       = "";
      strServiceName    = "";
      strCountry        = "";
      strRegion         = "";
      strRegionId       = "";
      dCityLongitude    = 0.0;
      dCityLatitude     = 0.0;
      strEntity         = "";
      strAccount        = "";
      strLicence        = "";
      strOrgCard        = "";
      strCompanyCharter = "";
      strPhone          = "";
      strPhoneForSms    = "";
    }

    sCity& operator = (const sCity &another)
    {
      dwId              = another.dwId;
      strName           = another.strName;
      strCityName       = another.strCityName;
      strServiceName    = another.strServiceName;
      strCountry        = another.strCountry;
      strRegion         = another.strRegion;
      strRegionId       = another.strRegionId;
      dCityLongitude    = another.dCityLongitude;
      dCityLatitude     = another.dCityLatitude;
      strEntity         = another.strEntity;
      strAccount        = another.strAccount;
      strLicence        = another.strLicence;
      strOrgCard        = another.strOrgCard;
      strCompanyCharter = another.strCompanyCharter;
      strPhone          = another.strPhone;
      strPhoneForSms    = another.strPhoneForSms;
      return *this;
    }
  };

  static std::string GetName(DWORD dwId, int iSQLSearch = 0);
  static std::string GetServiceName(DWORD dwId, int iSQLSearch = 0);
  static int GetCities(std::list<sCity> & arrCities);
  static int GetCities(std::list<sCity> &cities, const std::list<long> &ids);
  static int GetCitiesFromOrders(std::list<int> &lstCities);
  static int GetCitiesByWorkChannels(std::list<CCities::sCity> &arrCities, const DWORD& dwWorkChannel);
  static long long InsertServiceCity(const sCity &_stCity);
  static bool UpdateServiceCity(const sCity &_stCity);
  static bool DeleteServiceCity(const DWORD &_dwId);
  static int SelectServiceCity(const DWORD &_dwId, sCity &_stCity);

  static unsigned long GetIdByName(const char* strName, int iSQLSearch = 0);
  static std::string GetKladrId(const char* strName);
  static std::string GetKladrId(unsigned long dwId);
  
  static void RefreshCache();
  static void CheckCache();
};

#endif