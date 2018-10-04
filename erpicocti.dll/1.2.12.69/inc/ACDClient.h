/*
 * ACDClient.h
 * Automatic call distributor client. 
 *
 * Капралов А.
 * 6.2.2013 20:25
 */
#pragma once

#include "ErpicoCTI.h"

#include "WCTI_Control.h"
#include "WCTI_Main.h"

#include "Core/Thread.h"
#include "Core/ThrSafeValue.h"

#include "AclLib/Config.h"
#include "Core/json/json.h"
#include <list>

#include <afxmt.h>

#define CFG_CTI_TYPE "cti.type"
#define CFG_CTI_HOST "cti.host"
#define CFG_CTI_PORT "cti.port"
#define CFG_CTI_USER "cti.user"
#define CFG_CTI_PASSWORD "cti.password"
#define CFG_CTI_EXT "cti.ext"
#define CFG_CTI_PREFIX "cti.prefix"
#define CFG_CTI_REMOVE_PREFIX "cti.remove_prefix"
#define CFG_CTI_SHOW_WELCOME "cti.show_welcome"
#define CFG_CTI_DENY_TO_SPY "cti.spy_deny"
#define CFG_CTI_ALLOWED_QUEUES "cti.queues.allowed"
#define CFG_CTI_EXTENS_ALLOW_MASK "cti.extens.allow.mask"
#define CFG_CTI_OPERATOR_READY "cti.operator.ready"
#define CFG_CTI_AUTO_ANSWER "cti.autoanswer"
#define CFG_CTI_TIME_FOR_HANGING_UP "cti.time.for.hangingup"
#define CFG_CTI_SHOW_WELCOME_TIMEOUT "cti.show_welcome.timeout"
#define CFG_CTI_AUTOREADY_AFTERWORK "cti.autoready.afterwork.timeout"
#define CFG_CTI_AUTOREADY_ADDITIONAL "cti.autoready.additional.timeout"
#define CFG_CTI_TOP_WINDOW_ON_CALL "acdclient.topwindowoncall"

#define ACD_CLIENT_BUF_SIZE 2048

enum EACDState{
  ACD_UNKNOWN,
  ACD_ERROR,
  ACD_NOTHING,
  ACD_LOGOFF,
  ACD_LOGON,
  ACD_READY,
  ACD_NOT_READY,
  ACD_MISSED,
  ACD_REST,  
  ACD_DISCONNECTED,
  ACD_AFTERWORK,
  ACD_LUNCH,
  ACD_MEETING,
  ACD_TASKS
};

enum EACDCallState {
  ACD_CALL_NONE,
  ACD_CALL_RING,
  ACD_CALL_TALK,
  ACD_CALL_UNKNOW
};

enum EACDError {
  ACD_ERROR_NONE            = 0,
  ACD_ERROR_UNAVAILABLE     = 1,
  ACD_ERROR_ILLEGAL_LIBRARY = 2,
  ACD_ERROR_CONNECTION_LOST = 3,
  ACD_ERROR_CTI_ERROR       = 4,
  ACD_ERROR_SERVER_UNAVAILABLE = 5
};

struct ERPICOCTI_API SWCTIConfig {
  int     nType;
  CString strHost;
  int     nPort;
  CString strUser;
  CString strPassw;
  CString strExt;

  SWCTIConfig() {
    nType = 0;
    nPort = 0;
  };
};

class CACDClient;

class IACDClientListener {
public:
  virtual void ErrorOccured(CACDClient *pSource, EACDError eError, const char *strMessage) = 0;
  virtual void StateChanged(CACDClient *pSource) = 0;
  virtual void StateTimeChanged(CACDClient *pSource) = 0;
  virtual void CallStateChanged(CACDClient *pSource, WCTI_CCallMessage * const call) = 0;
  virtual void QueueInfoUpdate(CACDClient *pSource) = 0;
};

class ACDClientAsyncExecutor;

class ERPICOCTI_API CACDClient {
private:
  static BOOL __stdcall pfnOutboundCallGenesysFromCommon(const char* strPhone);
  static void pfnWCTIAgentStateCallback (WCTIAgentStates status);
  static void pfnWCTINewCall(WCTI_CCallMessage * const call);
  static void pfnWCTICallStatusCallback(WCTI_CCallMessage * const call);
  static void pfnWCTIQueueInfoUpdated();

private:
  CCriticalSection m_cLock;
  CCriticalSection m_cConnectionLock;

  SOCKET m_rawConnection;
  SafeVar<HANDLE> m_hThreadRecv;
  
  SWCTIConfig m_sConfig;
  //HMODULE m_hWCTIModule;
  //SafeVar<CWCTI_Control *> m_pWCTI;

  CTI_UID m_nCallId;  

  SafeVar<EACDState> m_eState;
  WCTIAgentStates m_eStateReadyNotReady;
  SafeVar<EACDCallState> m_eCallState;
  SafeVar<int> m_eCallDirection;
  SafeVar<CString> m_strCallState;
  SafeVar<CTime> m_cStateTime; 
  bool m_bAutoAnswer;
  int  m_iTimeForHangingUp;

  SafeVar<EACDState> m_userState;
  SafeVar<std::string> m_userStateReason;

  CString m_strOutCallPrefix;
  CStringArray m_arrIncomingCallRemovePrefixes;
  
  SafeVar<CString> m_strCallPhone;
  CString m_strIncomingLine;
    
  bool m_bCallHold;

  Config *m_pConfig;
  const User* m_pUser;

  std::list<SWCTIAgentQueues> m_arrQueues;

  ACDClientAsyncExecutor *asyncExecutor;

private:
  CACDClient();

public:
  virtual ~CACDClient();

private:
  static CACDClient m_cInstance;
public:
  static CACDClient & GetInstance();

public:
  const char * GetExt() const;
  void SetExt(const char *strExt);
  EACDState GetState();
  EACDCallState GetCallState();
  int GetCallDirection();
  const CTime GetStateTime();
  bool IsLoggedIn() const;
  int GetTimeForHangingUp();
  void SetTimeForHangingUp(int _iTimeSec);

  const CString GetCallPhone();
  
  bool IsCallHold() const;
  void SetCallHold(bool bCallHold);
  bool IsAutoAnswer();
  void SetAutoAnswer(bool _bAutoAnswer);
  int SpyCall(CTI_UID uCallId, ESpyMode nMode = ACD_SPY_LISTEN);

  int SetQueueMemberStatus(const char* strIfc, EACDState newState, const char* strReason = 0);
  int AddToQueue(const char* strName, const char* strIfc, const char* strQueue, int nPenalty, int bPaused);
  int UpdateQueuePenalty(const char* strName, const char* strIfc, const char* strQueue, int nPenalty);
  int RemoveFromQueue(const char* strIfc, const char* strQueue);
public:
  void Initialize(Config *pConfig/* = NULL*/, const User *pUser/* = NULL*/);
  void SetQueues(std::list<SWCTIAgentQueues> arrQueues);

private:
  void Clear();

public:
  void LogOn();

private:
  WCTIErrors Connect();
public:  
  bool IsConnected();

private:
#if 0
  CWCTI_Control * GetCTIAgentInstance();
  int LoadCTIModule();
  void UnloadCTIModule();
#endif

public:
  void LogOff();
  
  void HangUp(CTI_UID uCallId);
  void Answer();
  
  void ClearCallPhone();

  bool IsReady();
  void SetReady();

  bool IsNotReady();
  void SetNotReady(WCTIAgentStates eState = AGENT_STATE_NOT_READY);
  int SetAgentStatus(EACDState newState, const char* strReason);

  int TransferCall(CTI_UID uCallId, const char* strPhone);
  int TransferCancel(CTI_UID uCallId);

  int TransferCallBlind(CTI_UID uCallId, const char* strPhone, const char* blindContext = 0);

  int GetQueueInfo(std::list<SWCTIQueueInfo> &sResult);
  int GetCurrentCalls(std::list<CCTICall>& _arrCalls);

  bool MakeOutboundCall(const char* strDialNumber);
  bool MakeLocalCall(const char* strANum, const char* strDialNumber, CTI_UID* pCallId = 0);

  // Statistics
  void LogWebPageClosed(CTI_UID uCallId);

  int Park(CTI_UID uCallId);

private:
  void SetWCTICallPhoneNumber(const char* strIn);
  
  void UpdateState(WCTIAgentStates state);
  void UpdateCallState(WCTI_CCallMessage * const call);
  
  void HandleNewCall(WCTI_CCallMessage * const call);

private:
  ACDClientAsyncExecutor * GetAsyncExecutor();

public:
  void LogOnAsync();
  void LogOffAsync();
  void SetReadyAsync();
  void SetNotReadyAsync();
  void SetAfterworkAsync();
  void SetNotReadyExtAsync(const char* reason);
  void CallAsync(const char* strDialNumber);
  void ReloadCalls();

private:
  std::list<IACDClientListener *> m_lstStateListeners;

public:
  void AddListener(IACDClientListener *pListener);
  void RemoveListener(IACDClientListener *pListener);

private:
  void FireErrorOccured(EACDError eError, const char *strMessage);
  void FireStateChanged();
  void FireStateTimeChanged();  
  void FireCallStateChanged(WCTI_CCallMessage * const call);
  void FireQueueInfoUpdate();
  //void FireOriginateResponse();

public:
  CTI_UID GetCallId();
private:
  std::list<SWCTIQueueInfo> m_arrQueuesInfo;
  unsigned long m_nQueuesVersion;
  std::list<CCTICall> m_arrCalls;
  unsigned long m_nCallsVersion;    

  int RemoveFromQueues();
  int AddToQueue(const char* strQueue, int nPenalty, int bPaused);
  int RemoveFromQueue(const char* strQueue);
  
  int CallToService(const char* strRequest, Json::Value* jsonResponse = 0);

  SafeVar<int> g_bRawReady;
  static DWORD WINAPI RecvThread(LPVOID param);
  DWORD RecvThreadProc();
  int ProcessEvent(Json::Value* json);
};

