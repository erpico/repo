#ifndef __ERPICO_MAP_IMPL_H__
#define __ERPICO_MAP_IMPL_H__

#include "ErpicoMap.h"

#ifdef WMAP_EXPORTS
  #define WMAP_DLL __declspec(dllexport)
#else
  #define WMAP_DLL __declspec(dllimport)
#endif
  
//  WMAP_DLL 
WMAP_DLL int __stdcall WMInitMap(bool bCRMServerPerverts = false);

WMAP_DLL int __stdcall WMOpenMapWindow(double dLatitude = 0, double dLogitude = 0);
WMAP_DLL int __stdcall WMShowActualRoute(DWORD dwCallLetter);
WMAP_DLL int __stdcall WMCloseMapWindow();

WMAP_DLL int __stdcall WMOpenMapWindowForSelect(double dLatitude, double dLogitude, HWND hNotifyWnd, UINT nMSg = 0);
WMAP_DLL int __stdcall WMGetSelectedCoordinats(double& dLatitude, double& dLongitude);


WMAP_DLL int __stdcall WMSearchAddress(const char* strAddress, double* lon, double* lat);

WMAP_DLL int __stdcall WMCalcRoute(std::string strAddress, std::string &strDistance, std::string &strDuration, std::string &strPoints);
WMAP_DLL int __stdcall WMCalcRouteAsync(std::list<const char*>& strAddresses, HWND hWnd, UINT nMsg);

WMAP_DLL int __stdcall WMShowRoute(std::list<GeoCoordinates>& parrRouteCoordinates);

WMAP_DLL int __stdcall WMDestroyMap();
WMAP_DLL int __stdcall WMFreeMemory(void* p);  


WMAP_DLL int __stdcall WMShowDistrictMap(int nCityId, int nType);
WMAP_DLL int __stdcall WMGetDistrict(LPCTSTR strAddr,int nType, int &nCityId, int &nDistrictId);

WMAP_DLL int __stdcall WMMapShowAlarm(DWORD dwExecId);
WMAP_DLL int __stdcall WMCenterMap(DWORD dwCityId);


typedef int (__stdcall* LPINITMAP)(bool);
typedef int (__stdcall* LPOPENMAPWINDOWS)(double,double);
typedef int (__stdcall* LPSHOWACTUALROUTE)(DWORD);
typedef int (__stdcall* LPSEARCHADDRESS)(const char*, double*, double*);
typedef int (__stdcall* LPCALCROUTE)(std::string, std::string&, std::string&, std::string&);
typedef int (__stdcall* LPCALCROUTEASYNC)(std::list<const char*>&, HWND, UINT);
typedef int (__stdcall* LPSHOWROUTE)(std::list<GeoCoordinates>&);

typedef int (__stdcall* LPOPENMAPWINDOWFORSELECT)(double, double, HWND, UINT);
typedef int (__stdcall* LPGETSELECTEDCOORDINATS)(double&, double&);
typedef int (__stdcall* LPCLOSEMAPWINDOW)();

typedef int (__stdcall* LPFREEMEMORY)(void*);

typedef int (__stdcall* LPDESTROYMAP)();
typedef int (__stdcall* LPSHOWDISTRICTMAP)(int nCityId, int nType);

typedef int (__stdcall* LPMAPSHOWALARM)(DWORD dwExecId);
typedef int (__stdcall* LPCENTERMAP)(DWORD dwCityId);

typedef int (__stdcall* LPREFRESHPAGE)();


WMAP_DLL int __stdcall WMInitMapGIS();

WMAP_DLL int __stdcall WMOpenMapWindowGIS(double dLatitude = 0, double dLogitude = 0);
WMAP_DLL int __stdcall WMCloseMapWindowGIS();

WMAP_DLL int __stdcall WMOpenMapWindowForSelectGIS(double dLatitude, double dLogitude, HWND hNotifyWnd, UINT nMSg = 0);
WMAP_DLL int __stdcall WMGetSelectedCoordinatsGIS(double& dLatitude, double& dLongitude);


WMAP_DLL int __stdcall WMSearchAddressGIS(const char* strAddress, double* lon, double* lat);

WMAP_DLL int __stdcall WMCalcRouteGIS(CArray<const char*> strAddresses, long* len, long* dur, CString* perrStr = 0, GeoCoordinates** parrRouteCoordinates = 0);
WMAP_DLL int __stdcall WMCalcRouteAsyncGIS(CArray<const char*>& strAddresses, HWND hWnd, UINT nMsg);

WMAP_DLL int __stdcall WMShowRouteGIS(CArray<GeoCoordinates>& parrRouteCoordinates);

WMAP_DLL int __stdcall WMDestroyMapGIS();
WMAP_DLL int __stdcall WMFreeMemoryGIS(void* p);  


WMAP_DLL int __stdcall WMShowDistrictMapGIS(int nCityId, int nType);
WMAP_DLL int __stdcall WMGetDistrictGIS(LPCTSTR strAddr,int nType, int &nCityId, int &nDistrictId);

WMAP_DLL int __stdcall WMMapShowAlarmGIS(DWORD dwExecId);
WMAP_DLL int __stdcall WMCenterMapGIS(DWORD dwCityId);

#endif // __ERPICO_MAP_IMPL_H__