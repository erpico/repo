#pragma once

#include "ErpicoCTI.h"

#include "WCTI_Def.h"
#include "WCTI_Call.h"

#include <string>

class ERPICOCTI_API WCTI_CCallMessage
{
public:
  WCTI_CCallMessage(void);
  virtual ~WCTI_CCallMessage(void);
  void setCall( CTI_UID _CallId, std::string _CalledNumber, 
        std::string _CallingNumer, WCTI_CallStatus = CTICallStatusNone, WCTI_CallDirection direction = CTICallInbound);
  void setStatus( WCTI_CallStatus status ){ m_status = status;};
  WCTI_CallStatus getStatus(){ return m_status;};
  CTI_UID getCallId(){ return CallId;};
  const char* getCalled(){ return CalledNumber.c_str(); };
  const char* getCalling(){ return CallingNumber.c_str(); };
  WCTI_CallDirection getDirection(){ return m_direction; };
private:
  CTI_UID CallId;
  std::string CalledNumber;
  std::string CallingNumber;
  WCTI_CallStatus m_status;
  WCTI_CallDirection m_direction;
};
