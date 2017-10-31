#pragma once
#include "ErpicoCTI/wcti_control.h"
#include "ErpicoCTI/WCTI_Win.h"
#include "WCTI_RecvThread.h"
#include "WCTI_RecvProcThread.h"
#include "Msg.h"
#include <direct.h>
#include <vector>
#include <list>
#include <map>
#include "ami.h"

#define CFG_CTI_ASTERISK_CHANNEL_MAKE_CALL "cti.asterisk.channel_make_call"
#define CFG_CTI_ASTERISK_CHANNEL_TRANSFER_CALL "cti.asterisk.channel_transfer_call"
#define CFG_CTI_ASTERISK_CHANNEL_CLEAR_CALL "cti.asterisk.channel_clear_call"
#define CFG_CTI_ASTERISK_CHANNEL "cti.asterisk.channel"
#define CFG_CTI_ASTERISK_CHANNEL1 "cti.asterisk.channel1"
#define CFG_CTI_ASTERISK_CHANNEL2 "cti.asterisk.channel2"
#define CFG_CTI_ASTERISK_DIAL_SOURCE "cti.asterisk.dial_source"
#define CFG_CTI_ASTERISK_AGENT_LOGOFF_COMMAND "cti.asterisk.agent_logoff_command"
#define CFG_CTI_ASTERISK_DIAL_EVENT_SOURCE_FIELD "cti.asterisk.dial_event_source_field"
#define CFG_CTI_ASTERISK_DIAL_EVENT_DEST_FIELD "cti.asterisk.dial_event_dest_field"
#define CFG_CTI_ASTERISK_AMI_USER "cti.asterisk.ami_user"
#define CFG_CTI_ASTERISK_AMI_SECRET "cti.asterisk.ami_secret"
#define CFG_CTI_ASTERISK_QUEUE "cti.asterisk.queue"
#define CFG_CTI_ASTERISK_PENALTY "cti.asterisk.penalty"
#define CFG_CTI_ASTERISK_TRANSPORT "cti.asterisk.transport"
#define CFG_CTI_ASTERISK_DEBUG "cti.asterisk.debug"
#define CFG_CTI_ASTERISK_HEADER_TEST_STRINGS "cti.asterisk.header_test_strings"
#define CFG_CTI_ASTERISK_CONTEXT "cti.asterisk.context"
#define CFG_CTI_ASTERISK_ALLOWED_SPY "cti.asterisk.allowedspy"

#define _DECLSPEC_WCTI_CONT_IMPL __declspec( dllexport )

#ifdef _WINDOWS
  //#include <winsock2.h>
#endif // WIN32

enum ConnectionState
{
  ConnectionStateOn,
  ConnectionStateOff
};

#define USE_INI_FILE

#ifdef USE_INI_FILE
  #include "IniParser.h"
#endif

#include "ami.h"

class _DECLSPEC_WCTI_CONT_IMPL CWCTI_Control_Impl :
  public CWCTI_Control
{
protected:
  AMI m_AMI;
public:
  CWCTI_Control_Impl(void);
  ~CWCTI_Control_Impl(void);  
  WCTIErrors init(const WCTI_STR _clientId, const WCTI_STR _clientPassword, 
      const WCTI_STR _clientNumber);
  WCTIErrors init(const WCTI_STR _clientId, const WCTI_STR _clientPassword, 
      const WCTI_STR _clientNumber, const std::map<CString, CString> &configMap);
  WCTIErrors connect( const WCTI_STR servername, WCTI_UINT port, WCTI_UINT maxTry = 1 );
  bool IsConnected();


  virtual WCTIErrors RegisterCallMsgCallback( WCTIMESSAGE_CALLBACK );
  virtual WCTIErrors RegisterAgentStateCallback( WCTIAGENT_CALLBACK );
  virtual WCTI_UINT  newCallHandler( WCTIMESSAGE_CALLBACK );
  virtual WCTI_UINT newQueueInfoHandler( WCTI_CALLBACK _func );
  virtual WCTI_UINT newTransferStatusHandler( WCTITRANSFER_CALLBACK _func ) { return ENotImplemented;};
  // Сообщения
  virtual WCTIErrors MakeCall( const WCTI_STR, CTI_UID * );
  virtual WCTIErrors MakeLocalCall(const WCTI_STR, const WCTI_STR, CTI_UID * );
//  WCTIErrors OriginateCall(const WCTI_STR szExten, const WCTI_STR szContext, const WCTI_STR szApp, const WCTI_STR szData);
  WCTIErrors SetAgentStatus( WCTIAgentStates stat );
  WCTIErrors Open();
  WCTIErrors Close( WCTI_UINT status );
  WCTIErrors GetAgentStatus( WCTIAgentStates * stat );
  WCTIErrors ClearCall( CTI_UID callId );
  WCTIErrors ClearAllCall();
  WCTIErrors AnswerCall( CTI_UID callId );
  WCTIErrors HoldCall( CTI_UID callId );
  WCTIErrors RetrieveCall( CTI_UID callId );
  virtual WCTIErrors TransferCall( CTI_UID callId, WCTI_STR number );
  virtual WCTIErrors TransferCallBlind(CTI_UID uCallId, const char* strPhone, const char* blindContext = 0);
  virtual WCTIErrors TransferCancel( CTI_UID callId );  
  virtual WCTI_UINT  GetAgentsCount();
  virtual WCTIErrors GetQueueInfo(std::list<SWCTIQueueInfo> &sResult);
#if 0
  void ParseQueueInfo(CString &strAnswer, SWCTIQueueInfo &sResult);
  void ParseQueueMembers(CString &strAnswer, CString &strLine, int &nToken, SWCTIQueueInfo &sResult);
  void ParseQueueCallers(CString &strAnswer, CString &strLine, int &nToken, SWCTIQueueInfo &sResult);
#endif
  virtual WCTIErrors SpyCall( CTI_UID callId, ESpyMode _mode);

  WCTIErrors GetCurrentCalls(std::list<CCTICall>& _arrCalls);

  // Ошибки
  WCTI_STR const getErrorMsgText(){return "";};

  // 
  WCTIErrors RecvRun( LPVOID );
  WCTIErrors RecvProcRun( LPVOID );

private:
  WCTIErrors AddToQueues(int bPaused = 1);
  WCTIErrors RemoveFromQueues();
public:

  virtual WCTIErrors SetQueues(std::list<SWCTIAgentQueues> arrQueues);

  virtual WCTIErrors AddToQueue(const char* strName, const char* strIfc, const char* strQueue, int nPenalty, int bPaused);
  virtual WCTIErrors UpdateQueuePenalty(const char* strName, const char* strIfc, const char* strQueue, int nPenalty);
  virtual WCTIErrors RemoveFromQueue(const char* strIfc, const char* strQueue);
  virtual WCTIErrors SetMemberStatus(const char* strIfc, WCTIAgentStates newState, const char* strReason = 0);
  virtual WCTIErrors ReloadCalls();

  int m_bCallConnected;
  CString m_strCallTalkChannel;
  CString m_strCallCallerID;

  int m_bAtxferActivated;
  CString m_strAgentConnectedChannel;
  CString m_strAtxferChannel;

  CString m_Login, m_Password, m_Host, m_Number;
  WCTI_UINT m_Port;
  WCTI_UINT uiClients;
  WCTIAgentStates m_AgentStatus;

  WCTI_UINT m_ulActionIdSeq;
  WCTI_UINT m_ulCallIdSeq;

  /*CString strChannelMakeCallMask;
  CString strChannelTransferCallMask;
  CString strChannelClearCallMask;
  CString strDialSource;
  CString strAgentLogoffCommand;
  CString strChannel;
  CString strChannel1;
  CString strChannel2;
  CString strDialEventSrc;
  CString strDialEventDst;*/

  CString strAmiUser;
  CString strAmiSecret;

  //CString strQueue;
  std::list<SWCTIAgentQueues> m_arrQueues;

  //CString m_Penalty;

  CString m_strIfc;

  CString strExtenTransport;
  int bDebugAmi;

  // Callback'и
  WCTIAGENT_CALLBACK m_fAgentStatus;
  WCTIMESSAGE_CALLBACK m_fMessages;
  // Новый звонок
  WCTIMESSAGE_CALLBACK m_fNewCall;
  WCTI_CALLBACK m_fQueueInfoUpdated;

  int disconnect();

  std::string context;

  std::map<int,int> m_mapAllowedToSpy;

  void readIniParams();
  void readParams(const std::map<CString, CString> &configMap);

  void AMI_Event(AMI_EVENTS nEvent, ami_uid_t amiUid, const AMI_PARAMS &params);
  
};
