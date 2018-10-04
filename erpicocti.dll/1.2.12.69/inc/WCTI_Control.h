/************************************************************************
*  author:     Polukhin R.
*
*  purpose:    Werta CTI Control abstraction class
*  version:    1.0
************************************************************************/

#ifndef __WCTI_CONTROL_H__
#define __WCTI_CONTROL_H__

#include "WCTI_Def.h"
#include "WCTI_CallMessage.h"
#include "WCTI_Call.h"
//#include "ACDClient.h"
#include <string>
#include <map>
#include <list>

// работа с ини-файлом
#define WCTI_INI_FILE "./wcti.ini"
#define WCTI_LOGIN    (const WCTI_STR)CWCTI_Control::getIniFileTextParameter("User", "Asterisk","",true).c_str()
#define WCTI_PASSWORD (const WCTI_STR)CWCTI_Control::getIniFileTextParameter("Passw", "Asterisk","",true).c_str()
#define WCTI_EXTEN    (const WCTI_STR)CWCTI_Control::getIniFileTextParameter("Ext", "Asterisk").c_str()
#define WCTI_PREFIX   (const WCTI_STR)CWCTI_Control::getIniFileTextParameter("Prefix", "Asterisk").c_str()
#define WCTI_HOST     (const WCTI_STR)CWCTI_Control::getIniFileTextParameter("Host", "Asterisk").c_str()
#define WCTI_PORT     CWCTI_Control::getIniFileIntParameter("Port", "Asterisk")
#define WCTI_TYPE     CWCTI_Control::getIniFileIntParameter("Type", "Asterisk")

// Callback функция для возврата события
typedef void (*WCTIMESSAGE_CALLBACK)( WCTI_CCallMessage * const msg );
typedef void (*WCTIAGENT_CALLBACK)  ( WCTIAgentStates  status);
typedef void (*WCTITRANSFER_CALLBACK)  ( WCTITransferStates  state);
typedef void (*WCTI_CALLBACK)  ();

#define AST_DEVICE_UNKNOWN	0
  /*! Device is not used */
#define AST_DEVICE_NOT_INUSE	1
  /*! Device is in use */
#define AST_DEVICE_INUSE	2
  /*! Device is busy */
#define AST_DEVICE_BUSY	 3
  /*! Device is invalid */
#define AST_DEVICE_INVALID	4
  /*! Device is unavailable */
#define AST_DEVICE_UNAVAILABLE	5
  /*! Device is ringing */
#define AST_DEVICE_RINGING	6
  /*! Device is ringing *and* in use */
#define AST_DEVICE_RINGINUSE	7
  /*! Device is on hold */
#define AST_DEVICE_ONHOLD	8

struct ERPICOCTI_API SWCTIQueueInfoMember {
  std::string szName;
  std::string szLocation;
  int nPenalty;  
  int nCallsTaken;
  time_t nLastCall;
  int nStatus;
  int nPaused;
  std::string szPauseReason;
  inline SWCTIQueueInfoMember(): nPenalty(0), nCallsTaken(0), nLastCall(0), nStatus(0), nPaused(0) {}
};

struct ERPICOCTI_API SWCTIQueueInfoCaller {
  std::string szChannel;
  std::string szUniqueId;
  std::string szCallerIDNum;
  int nPosition;  
  int nWait;
  inline SWCTIQueueInfoCaller(): nPosition(0), nWait(0) {}
};

struct ERPICOCTI_API SWCTIQueueInfo {
  std::string szName;
  int nCalls;
  int nHoldTime;
  int nTalkTime;
  int nCompleted;
  int nAbandoned;
  int nMembers;
  int nCallers;
  std::list<SWCTIQueueInfoCaller> arrCallers;
  std::list<SWCTIQueueInfoMember> arrMembers;

  inline SWCTIQueueInfo() : nMembers(0), nCallers(0), nCalls(0), nHoldTime(0), nTalkTime(0), nCompleted(0), nAbandoned(0) {}
};

struct ERPICOCTI_API SWCTIAgentQueues {
  std::string szQueueName;
  int nPenalty;
};

class ERPICOCTI_API CWCTI_Control
{
public:
  virtual ~CWCTI_Control(){};
//  virtual CRITICAL_SECTION * GetCS() = 0;
  virtual WCTIErrors init(const WCTI_STR _clientId, const WCTI_STR _clientPassword, 
      const WCTI_STR _clientNumber) = 0;
  virtual WCTIErrors init(const WCTI_STR _clientId, const WCTI_STR _clientPassword, 
      const WCTI_STR _clientNumber, const std::map<CString, CString> &configMap) = 0;
  virtual WCTIErrors connect(const WCTI_STR servername, WCTI_UINT port, WCTI_UINT maxTry = 20 ) = 0;
  virtual WCTIErrors SetQueues(std::list<SWCTIAgentQueues> arrQueues) = 0;
  virtual int disconnect() = 0;
  virtual bool IsConnected() = 0;
  virtual WCTIErrors RegisterCallMsgCallback( WCTIMESSAGE_CALLBACK ) = 0;
  virtual WCTIErrors RegisterAgentStateCallback( WCTIAGENT_CALLBACK ) = 0;
  virtual WCTI_UINT  newCallHandler( WCTIMESSAGE_CALLBACK ) = 0;
  virtual WCTI_UINT  newQueueInfoHandler( WCTI_CALLBACK _func ) = 0;
  virtual WCTI_UINT  newTransferStatusHandler( WCTITRANSFER_CALLBACK _func ) = 0;
  // Сообщения
  virtual WCTIErrors MakeCall(const WCTI_STR number, CTI_UID * idCall ) = 0;
  virtual WCTIErrors MakeLocalCall(const WCTI_STR numA, const WCTI_STR dial, CTI_UID * idCall ) = 0;

  virtual WCTIErrors SetAgentStatus( WCTIAgentStates stat ) = 0;
  virtual WCTIErrors Open() = 0;
  virtual WCTIErrors Close( WCTI_UINT status ) = 0;
  virtual WCTIErrors GetAgentStatus( WCTIAgentStates * st ) = 0;
  virtual WCTIErrors ClearCall( CTI_UID callId ) = 0;
  virtual WCTIErrors ClearAllCall() = 0;
  virtual WCTIErrors AnswerCall( CTI_UID callId ) = 0;
  virtual WCTIErrors HoldCall( CTI_UID callId ) = 0;
  virtual WCTIErrors RetrieveCall( CTI_UID callId ) = 0;
  virtual WCTIErrors TransferCall( CTI_UID callId, WCTI_STR number ){return ENotImplemented;};
  virtual WCTIErrors TransferCallBlind(CTI_UID uCallId, const char* strPhone, const char* blindContext = 0) {return ENotImplemented;};
  virtual WCTIErrors TransferInit( CTI_UID callId, WCTI_STR number ){return ENotImplemented;};
  virtual WCTIErrors TransferFinish( CTI_UID callId ){return ENotImplemented;};
  virtual WCTIErrors TransferCancel( CTI_UID callId ){return ENotImplemented;};
  virtual WCTI_UINT  GetAgentsCount() {return -1;};
  virtual WCTIErrors GetQueueInfo(std::list<SWCTIQueueInfo> &sResult) {return ENotImplemented;}

  virtual WCTIErrors SpyCall( CTI_UID callId, ESpyMode _mode){return ENotImplemented;};

  virtual WCTIErrors AddToQueue(const char* strName, const char* strIfc, const char* strQueue, int nPenalty, int bPaused) = 0;
  virtual WCTIErrors UpdateQueuePenalty(const char* strName, const char* strIfc, const char* strQueue, int nPenalty) = 0;
  virtual WCTIErrors RemoveFromQueue(const char* strIfc, const char* strQueue) = 0;
  virtual WCTIErrors SetMemberStatus(const char* strIfc, WCTIAgentStates newState, const char* strReason = 0) = 0;

  // Ошибки
  static WCTIErrorLevel getErrorLevel( WCTIErrors );
  static WCTI_STR getErrorDescription( WCTIErrors );
  virtual WCTI_STR const getErrorMsgText() = 0;

  virtual WCTIErrors GetCurrentCalls(std::list<CCTICall>& _arrCalls) = 0;
  virtual WCTIErrors ReloadCalls() = 0;

public:
  static int getIniFileIntParameter(const char *strName, const char *strSection = "WCTI", 
    int iDefValue = 0, bool autoReplace = false);
  static std::string getIniFileTextParameter(const char *strName, const char *strSection = "WCTI", 
    const char *strDefValue = "", bool autoReplace = false);
};


// Class Factory

#endif
