#ifndef __ERPICO_MAP_H__
#define __ERPICO_MAP_H__

#include "Core.h"
#include <list> 

  #define WM_GEO_NOTIFY_COORDINATES WM_USER+72
  #define WM_GET_COORDS_MESSAGE WM_USER + 73
  #define COORDINATES_IN_ADDRESS_TAG "~~COORDINATES##"

  struct GeoCoordinates {
    double dLatitute;
    double dLongitude;
  };

  CORE_API int __stdcall InitMap(const char *moduleName, bool bCRMServerPerverts = false);

  CORE_API int __stdcall OpenMapWindow(double dLatitude = 0, double dLongitude = 0);
  CORE_API int __stdcall ShowActualRoute(const DWORD &_dwOrderId);
  CORE_API int __stdcall CloseMapWindow(const DWORD &_dwCallLetter);

  CORE_API int __stdcall OpenMapWindowForSelect(double dLatitude, double dLongitude, HWND hNotifyWnd, UINT nMsg = 0);
  CORE_API int __stdcall GetSelectedCoordinates(double& dLatitude, double& dLongitude);


  CORE_API int __stdcall SearchAddress(const char* strAddress, double* lon, double* lat);

  CORE_API int __stdcall CalcRoute(std::string strAddress, std::string &strDistance, std::string &strDuration, std::string &strPoints);
  CORE_API int __stdcall CalcRouteAsync(std::list<const char*>& strAddresses, HWND hWnd, UINT nMsg);
  CORE_API int __stdcall ShowRoute(std::list<GeoCoordinates>& parrRouteCoordinates);
  CORE_API int __stdcall FreeMemory(void* p);  

  CORE_API int __stdcall DestroyMap();

  CORE_API int __stdcall ShowDistrictMap(int nCityId, int nType);
  CORE_API int __stdcall GetDistrictMap(LPCTSTR strAddr,int nType, int &nCityId, int &nDistrictId);

  CORE_API int __stdcall IsMapEnabled();

  CORE_API int __stdcall MapShowAlarm(DWORD dwExecId);
  CORE_API int __stdcall CenterMap(DWORD dwCityId);

#endif