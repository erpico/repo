#pragma once

#include "Core.h"
#include <vector>


class CORE_API CServicesAddresses
{
  public:
    CServicesAddresses();
    virtual ~CServicesAddresses();

    bool SelectAddresses(std::vector<CServicesAddresses> &_vectAddresses);
    bool InsertAddress();
    bool DeleteAddresses();
    void GetServiceAddresses(const Json::Value &_jAddresses);

    void SetAddress(const std::string &_strAddress)  { strAddress  = _strAddress; }
    void SetName(const std::string &_strName)        { strName = _strName; }
    void SetServiceId(const DWORD &_dwServiceId)     { dwServiceId = _dwServiceId; }
    void SetId(const DWORD &_dwId)                   { dwId        = _dwId; }
    void SetAddressType(const DWORD &_dwAddressType) { dwAddressType = _dwAddressType; }
    void SetLongitude(const double &_dLongitude)     { dLongitude = _dLongitude; }
    void SetLatitude(const double &_dLatitude)       { dLatitude = _dLatitude; }    

    std::string GetAddress()     { return strAddress; }
    std::string GetName()        { return strName; }
    DWORD       GetServiceId()   { return dwServiceId; }
    DWORD       GetId()          { return dwId; }
    DWORD       GetAddressType() { return dwAddressType; }
    double      GetLongitude()   { return dLongitude; }
    double      GetLatitude()    { return dLatitude; }

  private:
    std::string strAddress;    /* ����� �����������                                      */
    std::string strName;       /* ��������                                               */
    DWORD       dwServiceId;   /* id �����������                                         */
    DWORD       dwId;          /* id ������                                              */
    DWORD       dwAddressType; /* ��� ������: 0 - �������, 1 - �����������, 2 - �������� */
    double      dLongitude;    /* �������                                                */
    double      dLatitude;     /* ������                                                 */
};
