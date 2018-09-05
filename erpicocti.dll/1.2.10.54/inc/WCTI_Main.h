/************************************************************************
* author:     Polukhin R.
*
* purpose:    Werta CTI Control Cisco module
* version:    1.0
**********************************************************************/

#ifndef __WCTI_Infra_H__
#define __WCTI_Infra_H__

#include "WCTI_Control.h"
//#include "WCTI_ManagerError.h"

enum WCTI_Modules {
  WCTI_MODULE_INFRA    = 1,
  WCTI_MODULE_GENESYS  = 2,
  WCTI_MODULE_CISCO    = 3,
  WCTI_MODULE_ASTERISK = 4,
  WCTI_MODULE_SPRECORD = 5,
  WCTI_MODULE_INFINITY = 6
};

ERPICOCTI_API CWCTI_Control * CreateWCTIInfra();
ERPICOCTI_API CWCTI_Control * CreateWCTIGenesys();
ERPICOCTI_API CWCTI_Control * CreateWCTICisco();
ERPICOCTI_API CWCTI_Control * CreateWCTIInfinity();

typedef CWCTI_Control * (__stdcall* LPCREATEWCTI)();

#endif