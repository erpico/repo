#ifndef __CITIES_H__
#define __CITIES_H__

#define __CITIES_H__

#include "Core.h"
#include <list>

class CORE_API CCities {
public:
  struct sCity {
    unsigned long dwId;
    std::string strName;
    std::string strCityName;
    std::string strServiceName;
  };
  static std::string GetName(DWORD dwId, int iSQLSearch = 0);
  static std::string GetServiceName(DWORD dwId, int iSQLSearch = 0);
  static int GetCities(std::list<sCity> & arrCities);
  static int GetCities(std::list<sCity> &cities, const std::list<long> &ids);
  static int GetCitiesFromOrders(std::list<int> &lstCities);
  static int GetCitiesByWorkChannels(std::list<CCities::sCity> &arrCities, const DWORD& dwWorkChannel);

  static unsigned long GetIdByName(const char* strName, int iSQLSearch = 0);
  static std::string GetKladrId(const char* strName);
  static std::string GetKladrId(unsigned long dwId);
  
  static void RefreshCache();
  static void CheckCache();
};

#endif