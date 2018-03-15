#pragma once

#include "Core.h"


class CORE_API CServicesAddresses
{
  public:
    CServicesAddresses();
    virtual ~CServicesAddresses();

    bool SelectAddresses(std::vector<CServicesAddresses> &_vectAddresses);
    bool InsertAddress();
    bool DeleteAddresses();

    void SetAddress(const std::string &_strAddress)  { strAddress  = _strAddress; }
    void SetServiceId(const DWORD &_dwServiceId)     { dwServiceId = _dwServiceId; }
    void SetId(const DWORD &_dwId)                   { dwId        = _dwId; }
    void SetAddressType(const DWORD &_dwAddressType) { dwAddressType = _dwAddressType; }

    std::string GetAddress()     { return strAddress; }
    DWORD       GetServiceId()   { return dwServiceId; }
    DWORD       GetId()          { return dwId; }
    DWORD       GetAddressType() { return dwAddressType; }

  private:
    std::string strAddress;    /* Адрес перевозчика                                      */
    DWORD       dwServiceId;   /* id перевозчика                                         */
    DWORD       dwId;          /* id записи                                              */
    DWORD       dwAddressType; /* Тип адреса: 0 - обычный, 1 - юридический, 2 - почтовый */
};
