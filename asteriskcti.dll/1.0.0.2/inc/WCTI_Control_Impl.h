#pragma once
#include "ErpicoCTI/wcti_control.h"
#include "ErpicoCTI/WCTI_Win.h"
#include "WCTI_RecvThread.h"
#include "WCTI_RecvProcThread.h"
#include "Msg.h"
#include <direct.h>
#include <vector>
#include <list>

#define _DECLSPEC_WCTI_CONT_IMPL __declspec( dllexport )

#ifdef _WINDOWS
  //#include <winsock2.h>
#endif // WIN32

#define MESSAGE_SIZE_LIMIT 8192

typedef struct TReqMsgS {
  unsigned int   nActionID;
  CMsg* msgQuery;
  CMsg* msgAnswer;
  unsigned int   bAnswered;
} TReqMsgS;

typedef std::vector<std::string> TCallDesc;
typedef std::map<WCTI_UINT, TCallDesc> TCallMap;
typedef std::list<CMsg*> TMsg;
typedef std::list<TReqMsgS> TReqMsg;

enum ConnectionState
{
  ConnectionStateOn,
  ConnectionStateOff
};

#define USE_INI_FILE

#ifdef USE_INI_FILE
  #include "IniParser.h"
#endif

//#define USE_AGENTNAME

//#define TMP_ROYAL
#define NOT_USING_ASTMAN_PROXY

class _DECLSPEC_WCTI_CONT_IMPL CWCTI_Control_Impl :
  public CWCTI_Control
{
public:
  CWCTI_Control_Impl(void);
  ~CWCTI_Control_Impl(void);
  CRITICAL_SECTION * GetCS();
  WCTIErrors init( const WCTI_STR _clientId, 
        const WCTI_STR _clientPassword, 
        const WCTI_STR _clientNumber );
  WCTIErrors connect( const WCTI_STR servername, WCTI_UINT port, WCTI_UINT maxTry = 1 );


  WCTIErrors RegisterCallMsgCallback( WCTIMESSAGE_CALLBACK );
  WCTIErrors RegisterAgentStateCallback( WCTIAGENT_CALLBACK );
  WCTI_UINT  newCallHandler( WCTIMESSAGE_CALLBACK );
  // Сообщения
  WCTIErrors MakeCall( const WCTI_STR, WCTI_UINT * );
//  WCTIErrors OriginateCall(const WCTI_STR szExten, const WCTI_STR szContext, const WCTI_STR szApp, const WCTI_STR szData);
  WCTIErrors SetAgentStatus( WCTIAgentStates stat );
  WCTIErrors Open();
  WCTIErrors Close( WCTI_UINT status );
  WCTIErrors GetAgentStatus( WCTIAgentStates * stat );
  WCTIErrors ClearCall( WCTI_UINT callId );
  WCTIErrors ClearAllCall();
  WCTIErrors AnswerCall( WCTI_UINT callId );
  WCTIErrors HoldCall( WCTI_UINT callId );
  WCTIErrors RetrieveCall( WCTI_UINT callId );
  virtual WCTIErrors TransferCall( WCTI_UINT callId, WCTI_STR number );
  virtual WCTI_UINT  GetAgentsCount();
  virtual WCTIErrors GetQueueInfo(SWCTIQueueInfo &sResult);
  void ParseQueueInfo(CString &strAnswer, SWCTIQueueInfo &sResult);
  void ParseQueueMembers(CString &strAnswer, CString &strLine, int &nToken, SWCTIQueueInfo &sResult);
  void ParseQueueCallers(CString &strAnswer, CString &strLine, int &nToken, SWCTIQueueInfo &sResult);

  // Ошибки
  WCTI_STR const getErrorMsgText(){return "";};

  // 
  WCTIErrors RecvRun( LPVOID );
  WCTIErrors RecvProcRun( LPVOID );

//private:
public:
  WCTI_STR m_Login, m_Password, m_Host, m_Number;
  WCTI_UINT m_Port;
  WCTI_UINT uiClients;
  WCTI_UINT m_AgentStatus;

  WCTI_UINT m_ulActionIdSeq;
  WCTI_UINT m_ulCallIdSeq;

#ifndef TMP_ROYAL
  CString strChannelMakeCallMask;
  CString strChannelTransferCallMask;
  CString strChannelClearCallMask;
  CString strDialSource;
  CString strAgentLogoffCommand;
  CString strChannel;
  CString strChannel1;
  CString strChannel2;
  CString strDialEventSrc;
  CString strDialEventDst;

  CString strAmiUser;
  CString strAmiSecret;

  CString strQueue;

  CString m_Penalty;

  CString strExtenTransport;
  int bDebugAmi;
#endif

  CRITICAL_SECTION m_ActionIdCrit;
  CRITICAL_SECTION m_CallIdCrit;
  CRITICAL_SECTION m_CallsColl;
  CRITICAL_SECTION m_SharedMsgCrit;
  CRITICAL_SECTION m_SocketsCrit;
  CRITICAL_SECTION m_ProcCrit;
  int m_bInCall;
  void nextId( WCTI_UINT * ActionId );
  void nextCallId( WCTI_UINT * callId );

  bool opened;

  WCTIErrors sendMessage( CMsg * msg );
  WCTIErrors sendMessageAndWaitResponse( CMsg * msg /*, CMsgBase * _out*/ ); 
  //WCTI_BOOL isAnswerForMessage( CMsg * msg, CMsg * resp);
  //WCTI_BOOL isFailure( CMsg * msg );
  void ProceedMsg( CMsg * msg );
  //void clearAnswer();

  //CMsg * msgWait; // Сообщение ожидающие ответа в синхронном режиме
  //CMsg * msgAnswer; // Ответ на сообщение в синхронном режиме
  HANDLE evWaitingMessageEnded; // Ожидать приход ответа на сообщение
  HANDLE evWaitingMessageProceeded; // Ответное сообщение обработано
  HANDLE evWaitingMessageRecv;  // Ожидание прихода сообщения по TCP/IP

  sockaddr_in addr;
  SOCKET m_socket;

  CRecvThread * m_pThread;
  CRecvProcThread * m_pThreadProc;
  volatile BOOL stopRecieve;

  // Callback'и
  WCTIAGENT_CALLBACK m_fAgentStatus;
  WCTIMESSAGE_CALLBACK m_fMessages;
  // Новый звонок
  WCTIMESSAGE_CALLBACK m_fNewCall;

  int disconnect();

  TCallMap calls;
  TMsg     m_arrMessages;
  TReqMsg  m_arrReqMessages;

  std::string context;

  CMsg* CreateNewMessage(WCTI_UINT nActionID);
  int   SetMessageAnswer(CMsg* pAnswer);
  CMsg* GetAnswerMessage(CMsg* pMsg);
  //int   IsMessageResponseOk(WCTI_UINT nActionID);
  int   IsMessageResponseOk(CMsg* pMsg);
  //void  DeleteMessage(WCTI_UINT nActionID);
  void  DeleteMessage(CMsg* pMsg);
  void PurgeMessages();

  void readIniParams();
  
};
