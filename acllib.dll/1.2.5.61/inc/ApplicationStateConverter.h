#pragma once

#include "AclLib.h"
#include "ApplicationState.h"

class ACLLIB_API ApplicationStateConverter {
private:
  ApplicationStateConverter(void);
  virtual ~ApplicationStateConverter(void);
public:
  static ApplicationState ConvetTo(CString str);
  static const char *ConvertFrom( ApplicationState state );
};

