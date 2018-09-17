#ifndef __CCTIMANAGERERROR_H
#define __CCTIMANAGERERROR_H


#include "WCTI_Def.h"
#include "basictype.h"

namespace com_cisco
{
  // Обработка ошибок 
  class WCTI_CISCO_DLL WCTI_ManagerError
  {
  public:
    static WCTIErrorLevel getErrorLevel( WCTIErrors );
    static CRS_STR getErrorDescription( WCTIErrors );
  };
}

#endif // __CCTIMANAGERERROR_H