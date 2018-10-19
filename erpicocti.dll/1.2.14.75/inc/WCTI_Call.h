#ifndef __WCTI_CALL_H
#define __WCTI_CALL_H
/*
/  Класс описывающий звонок
/
*/
#include "WCTI_Def.h"

enum WCTI_CallStatus
{
  CTICallStatusNone = 0,
  CTICallStatusInitiated,
  CTICallStatusAlerting,
  CTICallStatusDelivered,
  CTICallStatusConnected,
  CTICallStatusDisconnected,
  CTICallStatusHeld,
  CTICallStatusEstablished,
  CTICallStatusQueued
};

ERPICOCTI_API const char * CallStatusToString(WCTI_CallStatus status);

enum WCTI_CallDirection
{
  CTICallInbound,
  CTICallOutbound
};

class ERPICOCTI_API CCTICall
{
public:
  CCTICall(CTI_UID _callId, time_t _time, const char* _strSrc, const char* _strDst, WCTI_CallStatus _Status = CTICallStatusInitiated ) {
    m_time   = _time;
    m_callId = _callId;
    m_strSrc = _strSrc;
    m_strDst = _strDst;
    m_status = _Status;

    m_strQueueName = "";
    m_strAgentName = "";
    m_nQueueHoldTime = 0;
    m_nInPosition = 0;
    _direction = CTICallInbound;
  }
  ~CCTICall()
  {
  };

  inline bool IsAgentCall() const {
    return (m_strSrc.GetLength() == 3 || m_strDst.GetLength() == 3) && (m_strQueueName.GetLength() != 0) && (m_strAgentName.GetLength() != 0);
  }
/*  CRS_UINT getCallId(){ return callId; };
  CRS_USHORT getDevType(){ return devType; };
  CRS_STR getDevId(){ return devId; };
  WCTI_CallStatus getCallStatus(){ return status; };
  WCTI_CallDirection getCallDirection(){ return direction; };*/
public: 
  CTI_UID m_callId;
  time_t  m_time;
  CString m_strSrc;
  CString m_strDst;

  CString m_strQueueName;
  CString m_strAgentName;
  int m_nQueueHoldTime;
  int m_nInPosition;

  WCTI_CallStatus m_status;
  WCTI_CallDirection _direction;
};

#endif // __WCTI_CALL_H