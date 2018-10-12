#ifndef __GEO_ADDRESS_H__
#define __GEO_ADDRESS_H__

#include "Core.h"

CORE_API int __stdcall GeoAddressSave(int nCity, const char* strStreet, const char* strHouse, const char* strCorpus, double dLatitude, double dLongitude);
CORE_API int __stdcall GeoAddressGet(int nCity, const char* strStreet, const char* strHouse, const char* strCorpus, double& dLatitude, double& dLongitude);

#endif //__GEO_ADDRESS_H__