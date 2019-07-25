//---------------------------------------------------------------------------

#ifndef KladrH
#define KladrH

#define KLADR_MAX_ID_LEN 32
#define KLADR_MAX_STR_LEN 128
//#define _ui64 unsigned __int64 
//#define _ui32 unsigned __int32
#define _ui32 int 

#include "Core.h"

struct KLADR_RES {
    char id[KLADR_MAX_ID_LEN];
    char abbr[KLADR_MAX_STR_LEN];
    char abbr_full[KLADR_MAX_STR_LEN];
    char str[KLADR_MAX_STR_LEN];
    DWORD code;

    KLADR_RES() {
      memset(this, 0, sizeof(*this));
    }
};

typedef enum {
  KLADR_DT_REGION = 0x01,
  KLADR_DT_AREA,
  KLADR_DT_CITY,
  KLADR_DT_VILLAGE,
  KLADR_DT_CITY_NEW,
  KLADR_DT_CITY_BY_REGION
} KLADR_DIR_TYPES;

template<size_t fullSize> inline int KLADR_GetAbbr(const char* abbr, char* sml, char (&full)[fullSize]) {
  return KLADR_GetAbbr(abbr, sml, full, fullSize);
}

extern "C"
{
int   CORE_API  KLADR_ConnectLib();
int   CORE_API KLADR_DisconnectLib();

_ui32 CORE_API KLADR_GetCitys(KLADR_RES ** res, const char* region, KLADR_DIR_TYPES tp, const int &_iLimit = 0, const std::string &_strName = "");
_ui32 CORE_API KLADR_GetStreets(const char* cid, KLADR_RES** res, const int &_iLimit = 0, const std::string &_strName = "");
_ui32 CORE_API KLADR_GetAbbrFullNames(KLADR_RES ** res);
int   CORE_API KLADR_FindCity(const char* city, const char* region, KLADR_RES * res, KLADR_DIR_TYPES tp);
int   CORE_API KLADR_GetObjectByCode(DWORD code, KLADR_RES* res);
int   CORE_API KLADR_FindStreet(const char* cid, const char* street, KLADR_RES * res);
int   CORE_API KLADR_FreeResult(KLADR_RES* res);
int   CORE_API KLADR_GetAbbr (const char* abbr, char* sml, size_t smlSize, char* full, size_t fullSize);
int   CORE_API KLADR_GetRegionByName(const char* chRegionName, std::string &_strRegionId);
int   CORE_API KLADR_GetRegionByCity(const char* chCity, const char* chCurrRegion, std::string* strRegion);
int   CORE_API KLADR_GetRegionById(const char* chRegionId, std::string *strRegionName);
int   CORE_API KLADR_GetRegions(std::vector<KLADR_RES> &_vectRegions, const int &_iLimit = 0, const std::string &_strName = "");
};


//---------------------------------------------------------------------------
#endif
