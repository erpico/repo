#ifndef __CITIES_H__
#define __CITIES_H__

#define __CITIES_H__

#include "Core.h"
#include "Core/json/json.h"
#include <list>

namespace ServiceDetails
{
  static const char* const_strDetails[] = { "corpName", "corpInn", "corpKpp", "corpAddress",  "corpBik", "corpBankname", "corpCoracc", "corpRacc" };
};

/* Статусы перевозчиков */
namespace ServiceStates
{
  static const int const_iActive       = 0; /* Активен */
  static const int const_iVerification = 1; /* На модерации */
  static const int const_iBlocked      = 2; /* Заблокирован */
};

namespace ServiceFields
{
  static const char* const_strServicesFields[] = { "fax", "corpName", "corpKpp", "corpInn", "corpBankname", "corpBik", "corpCoracc", "corpRacc", "corpAddress",
                                             "orgCard", "companyCharter", "licenses", "license", "postAddress" };

  static const int const_iCount = 14;
}

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
    std::string strGeoAddr;
    DWORD       dwOrgForm;
    std::string strEmail;
    int         iSendLetter;
    int         iDeleted;
    std::string strLogin;
    std::string strPassword;
    DWORD       dwSendingLetterTime;
    DWORD       dwSendingNoDriverLetterTime;
    int         iDetails;
    std::string strDirector;
    std::string strAccountant;
    int         iState;
    std::string strStamp;
    std::string strDirectorSignature;
    std::string strAccountantSignature;

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
      strGeoAddr                  = "";
      dwOrgForm                   = 0;
      strEmail                    = "";
      iSendLetter                 = 0;
      iDeleted                    = 0;
      strLogin                    = "";
      strPassword                 = "";
      dwSendingLetterTime         = 0;
      dwSendingNoDriverLetterTime = 0;
      iDetails                    = 0;
      strDirector                 = "";
      strAccountant               = "";
      iState                      = 0;
      strStamp                    = "";
      strDirectorSignature        = "";
      strAccountantSignature      = "";
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
      strGeoAddr                  = another.strGeoAddr;
      dwOrgForm                   = another.dwOrgForm;
      strEmail                    = another.strEmail;
      iSendLetter                 = another.iSendLetter;
      iDeleted                    = another.iDeleted;
      strLogin                    = another.strLogin;
      strPassword                 = another.strPassword;
      dwSendingLetterTime         = another.dwSendingLetterTime;
      dwSendingNoDriverLetterTime = another.dwSendingNoDriverLetterTime;
      iDetails                    = another.iDetails;
      strDirector                 = another.strDirector;
      strAccountant               = another.strAccountant;
      iState                      = another.iState;
      strStamp                    = another.strStamp;
      strDirectorSignature        = another.strDirectorSignature;
      strAccountantSignature      = another.strAccountantSignature;

      return *this;
    }

    bool operator == (const sCity &another)
    {
      return (this->dwId == another.dwId);
    }

    bool operator () (const sCity &_sCity) const
    {
        return (dwId == _sCity.dwId);
    }
  };

  struct sFields
  {
    std::string strKey;
    std::string strValue;

    sFields()
    {
    
    }

    sFields(const std::string &_strKey, const std::string &_strValue)
    {
        strKey   = _strKey;
        strValue = _strValue;
    }

    bool operator () (const sFields &_sFields) const
    {
        return ((_sFields.strKey.compare(strKey) == 0) ? true : false);
    }    
  };

  static std::string GetName(DWORD dwId, int iSQLSearch = 0);
  static std::string GetServiceName(DWORD dwId, int iSQLSearch = 0);
  static int GetCities(std::list<sCity> & arrCities, const DWORD &_dwId = 0, const bool &_bSkip = false);
  static int GetCities(std::list<sCity> &cities, const std::list<long> &ids);
  static int GetCitiesFromOrders(std::list<int> &lstCities);
  static int GetCitiesByWorkChannels(std::list<CCities::sCity> &arrCities, const DWORD& dwWorkChannel);
  static bool InsertCities(const std::list<CCities::sCity> &_lstCities);
  static long long InsertServiceCity(const sCity &_stCity);
  static bool UpdateServiceCity(const sCity &_stCity);
  static bool DeleteServiceCity(const DWORD &_dwId);
  static bool RestoreServiceCity(const DWORD &_dwId);
  static bool SetServiceState(const DWORD &_dwId, const int &_iValue);
  static int SelectServiceCity(const DWORD &_dwId, sCity &_stCity, const int &_iDeleted = 0);
  static bool CheckServiceId(const std::string &_strServiceId, const DWORD &_dwId = 0);

  static unsigned long GetIdByName(const char* strName, int iSQLSearch = 0);
  static std::string GetKladrId(const char* strName);
  static std::string GetKladrId(unsigned long dwId);
  
  static void RefreshCache(const DWORD &_dwId = 0, const bool &_bSkip = false);
  static void CheckCache(const DWORD &_dwId = 0, const bool &_bSkip = false);
  static void SetCitiesCache(const DWORD &_dwVal);
  static DWORD GetCitiesCache();

  static int SaveFieldValue(DWORD dwId, const char* szKey, const char* szValue);
  static int GetFieldsValues(DWORD dwId, std::list<sFields>& arr);
  static bool GetServiceCities(std::vector<std::string> &_vectServiceCities);
  static void SetServiceToJson(Json::Value &_jService, const sCity &_stCity);
  static void SetDetailsToJSON(const CCities::sCity &_stCity, Json::Value &_jList);
  static bool GetLegalFormStr(const DWORD &_dwId, std::string &_strLegalForm);
  static void GetServiceInfoFromJson(CCities::sCity &_stCity, const Json::Value &_jCity);
  static int SaveExtFields(const DWORD &_dwServiceId, const Json::Value &_jFields);
  static int DetailsExists();
};

#endif