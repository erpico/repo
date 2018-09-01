/************************************************************************
*  author:     Polukhin R.
*
*  purpose:    Werta CTI Control defines
*  version:    1.0
************************************************************************/

#ifndef __WCTI_DEF_H__
#define __WCTI_DEF_H__

#include "ErpicoCTI.h"

#ifdef _WINDOWS
#include "WCTI_Win.h"
#endif

#define WCTI_TRUE  1
#define WCTI_FALSE  0

typedef unsigned long long CTI_UID;
typedef unsigned int WCTI_UINT;
typedef int WCTI_INT;
typedef unsigned char WCTI_BYTE;
typedef char WCTI_CHAR;
typedef unsigned char WCTI_UCHAR;
typedef unsigned short WCTI_USHORT;
typedef unsigned long WCTI_ULONG;
typedef unsigned short WCTI_BOOL;
typedef char * WCTI_STR;

namespace WCTI_CalleeType
{
  static const int const_iService = 0;
  static const int const_iClient  = 1;
  static const int const_iDriver  = 2;
};

// Уровни ошибок
enum WCTIErrorLevel
{
  ELevelNoError  = 0, // Ошибок нет
  ELevelNormal   = 1, // Ошибка при выполнении действия - исправляемая
  ELevelCritical = 2, // Неустранимая ошибка
  ELevelUnknown  = 3  // Уровень данной ошибки неизвестен
};

// Список ошибок
enum WCTIErrors
{
  ENoError = 0,
  EServerNameError,
  EServerPortError,
  ESocketAlreadyOpened,
  ESocketConnectionError,
  ERcvStart,
  EOpenSessionError,
  EMakeCallError,
  ECallOperationError,
  ERegisterCallback,
  EStatusFailed,
  EMsgFailed,
  ENoMessage,
  ESocketClosedByRemote,
  ENoMemory,
  ENoSuchCall,
  EGeneralError,
  ETimeOut,
  ENotImplemented
};

// Agent states
enum WCTIAgentStates
{
  AGENT_STATE_LOGIN           =  0,
  AGENT_STATE_LOGOUT          =  1,
  AGENT_STATE_NOT_READY       =  2,
  AGENT_STATE_AVAILABLE       =  3,
//  AGENT_STATE_TALKING         =  4,
//  AGENT_STATE_WORK_NOT_READY  =  5,
//  AGENT_STATE_WORK_READY      =  6,
//  AGENT_STATE_BUSY_OTHER      =  7,
//  AGENT_STATE_RESERVED        =  8,
  AGENT_STATE_UNKNOWN         =  9,
//  AGENT_STATE_HOLD            = 10,
//  AGENT_STATE_ACTIVE          = 11,
//  AGENT_STATE_PAUSED          = 12,
//  AGENT_STATE_INTERRUPTED     = 13,
//  AGENT_STATE_NOT_ACTIVE      = 14,
  AGENT_STATE_DISCONNECTED    = 15,
  AGENT_STATE_AFTERWORK = 16
};

inline const char * AgentStateToString(WCTIAgentStates state) {
  switch (state) {
  case AGENT_STATE_LOGIN:
    return "LOGIN";
  case AGENT_STATE_LOGOUT:
    return "LOGOUT";
  case AGENT_STATE_NOT_READY:
    return "NOT_READY";
  case AGENT_STATE_AVAILABLE:
    return "AVAILABLE";
  case AGENT_STATE_UNKNOWN:
    return "UNKNOWN";
  case AGENT_STATE_DISCONNECTED:
    return "DISCONNECTED";
  case AGENT_STATE_AFTERWORK:
    return "AFTERWORK";
  default:
    return "";
  }
}

enum ESpyMode {
  ACD_SPY_NONE,
  ACD_SPY_LISTEN,
  ACD_SPY_WHISPER,
  ACD_SPY_CONFERENCE
};

enum WCTITransferStates {
  ACD_TRANSFER_STATE_NONE,
  ACD_TRANSFER_STATE_INIT,
  ACD_TRANSFER_STATE_STERTED,
  ACD_TRANSFER_STATE_BRIDGE,
  ACD_TRANSFER_STATE_DONE,
  ACD_TRANSFER_STATE_CANCELED,
};

#define WCTI_APP_CALL_PREFIX "app://"

#endif // __WCTI_DEF_H__