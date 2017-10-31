/*------------------------------------------------------- File Description -*\

  Copyright (C) Erpico, 2015

  DESCRIPTION

  For Internal use only.

\*--------------------------------------------------------------------------*/

#ifndef AMI_H__DEFINED
#define AMI_H__DEFINED

#include "AsteriskCTI.h"

#include <map>
#include <string>
#include <list>

#include "Core/Strings.h"

#define AMI_COMMAND_CORE_SHOW_CHANNELS "CoreShowChannels"

#define AMI_EVENT_NAME_CORE_SHOW_CHANNEL "CoreShowChannel"

// Список событий AMI
enum AMI_EVENTS {  
  AMI_EVENT_ORIGINATE_RESPONSE = 1,
  AMI_EVENT_CALL_BRIDGED       = 2,
  AMI_EVENT_CALL_HANGUP        = 3,
  AMI_EVENT_CHANNEL_HANGUP     = 4,
  AMI_EVENT_CALL_RING          = 5,
  AMI_EVENT_CHANNEL_RING       = 6,
  AMI_EVENT_CALL_UP            = 7,
  AMI_REQUEST_NEW_CALLID       = 8,
  AMI_EVENT_QUEUE_MEMBER_ADDED = 9,
  AMI_EVENT_QUEUE_MEMBER_REMOVED = 10,
  AMI_EVENT_QUEUE_MEMBER_STATUS  = 11,
  AMI_EVENT_QUEUE_MEMBER_PAUSED = 12,
  AMI_EVENT_QUEUE_JOIN = 13,
  AMI_EVENT_QUEUE_LEAVE = 14,
  AMI_EVENT_CHANNEL_DIAL = 15,
  AMI_EVENT_DISCONNECTED = 16
};

// Опреденеие типа параметра AMI. Пара строка-строка
typedef std::map<std::string, std::string, NocaseStringComparator> AMI_PARAMS; 

struct ASTERISKCTI_API AMI_RESPONSE {
  unsigned long nActionId;
  int nMultiEventsResponse; // 0 - no, 1 - yes, collect, 2 - complete
  AMI_PARAMS params;
  //std::string strBody;
  std::list<AMI_PARAMS> followedEvents;
};

enum AMI_CALLSTATE {
  AMI_CALL_UNKNOWN = 0,
  AMI_CALL_NEW,
  AMI_CALL_RING,
  AMI_CALL_UP,
  AMI_CALL_BRIDGED,
  AMI_CALL_HANGUP  
};

typedef unsigned long long ami_uid_t; // 0 to 18,446,744,073,709,551,615

struct ASTERISKCTI_API Channel {
  AMI_PARAMS     params;
  AMI_PARAMS     vars;
  AMI_CALLSTATE  state;
  time_t         state_time;
  Channel() {
    clear();
  }
  void clear() {
    state = AMI_CALL_UNKNOWN;
    state_time = 0;
  };

};

struct ASTERISKCTI_API AMI_CALLS_PAIR {
  int        originateActionId;
  ami_uid_t  uid;
  char       firstid[64];
  char       secondid[64];
  int        firstactive;  
  int        secondactive;  
  AMI_CALLS_PAIR() { memset(this,0,sizeof(*this)); };
//  std::list<std::string> channels;
};

typedef std::map<std::string, Channel> AMI_CALLS;

typedef std::map<ami_uid_t, AMI_CALLS_PAIR> AMI_CALLS_PAIRS;

// Определение типа калбэк-функции событий AMI
typedef void (*AMI_CALLBACK)(AMI_EVENTS, ami_uid_t, const AMI_PARAMS &);

// Макрос добавления параметра в список параметров
#define ADD_HEADER_TO_PARAMS(m, k, v) m[std::string(k)] = std::string(v)

// Макрос получения параметра в виде строки const char* из списка
#define GET_STRING_HEADER_PARAM(m, k) (m.find(k) != m.end() ? m.find(k)->second.c_str() : "")
#define IS_PARAM_EXISTS(m, k) (m.find(k) != m.end() ? 1 : 0)

typedef std::map<unsigned long, AMI_RESPONSE> AMI_RESPONSES_MAP;

#define MAX_AMI_REQUEST_LEN 65535

using namespace std;

class ASTERISKCTI_API AMI {
  public: 
    AMI();
    ~AMI();
  protected:
    char g_amiRequestBuf[MAX_AMI_REQUEST_LEN];
    int  g_amiLastActionID;
    bool g_bConnected;
    SOCKET g_amiConnection;
    int  g_stopRecvThread;
    int  g_AMIReady;
    int  g_AMICallId;
    unsigned long  g_InternalCallId;
    
    AMI_RESPONSES_MAP g_mapResponses;
    std::list<AMI_PARAMS> g_listEvents;

    AMI_CALLBACK g_pAmiCallback;

    #ifdef _WIN32
      CRITICAL_SECTION m_SocketsCrit;
      CRITICAL_SECTION m_CollectionsCrit;
      CRITICAL_SECTION m_DoRequestCrit;

      HANDLE g_evActionResponse;
      HANDLE g_evEvent;
    #else
      #include <pthread.h>
      #include <semaphore.h>
      #include <time.h>
      #include "events.h"

      pthread_mutex_t m_SocketsCrit;
      pthread_mutex_t m_CollectionsCrit;
      pthread_mutex_t m_DoRequestCrit;

      #define USE_MUTEX
      
      event_t g_evActionResponse;
      event_t g_evEvent;
      
    #endif

    AMI_CALLS       g_mapChannels;
    AMI_CALLS_PAIRS g_mapAmiCallsPairs;

    HANDLE g_hThreadRecv;
    HANDLE g_hThreadProc;

    void AMI_FireEvent(AMI_EVENTS amiEvent, ami_uid_t uid, const AMI_PARAMS &params);

    void AddChannel(const string &uid, const AMI_PARAMS &params, AMI_CALLSTATE state, time_t stateTime);
    void AddNewChannel(const string &uid, const AMI_PARAMS &params);
    Channel * GetChannel(const string &uid);
    bool HasChannel(const string &uid);
    void UpdateChannelParams(Channel &channel, const AMI_PARAMS &params);
    void ChangeChannelState(Channel &call, AMI_CALLSTATE state);
    void ChangeChannelState(string &uid, AMI_CALLSTATE state);
    void RemoveChannel(const string &uid);
    void RemoveChannel(const char *uid);
    ami_uid_t GetCallIdByChannelName(const string &channelName);
    void AddNewCall(ami_uid_t uid, const char *firstId, int firstActive, const char *secondId, int secondActive, int originateActionId);
    void AddNewCall(ami_uid_t uid, const string &firstId, int firstActive, const string &secondId, int secondActive, int originateActionId);
    ami_uid_t FindCallIdByOriginateActionId(int originateActionId);
    AMI_CALLS_PAIR * GetCall(ami_uid_t uid);
    void RemoveCall(ami_uid_t uid);
    ami_uid_t ParseAmiUid(const char *str);
    ami_uid_t ParseAmiUid(const string &str);
    int AMI_CollectionVarSet(AMI_PARAMS & params);
    int AMI_CollectionNewchannel(AMI_PARAMS & params);
    int AMI_CollectionNewCallerid(AMI_PARAMS & params);
    int AMI_CollectionNewstate(AMI_PARAMS & params);
    int AMI_CollectionDial(AMI_PARAMS & params);
    int AMI_CollectionHangup(AMI_PARAMS & params);
    int AMI_CollectionBridge(AMI_PARAMS & params);
    int AMI_OriginateResponse(AMI_PARAMS & params);
    int AMI_CollectionMasquarade(AMI_PARAMS & params);
    ami_uid_t ParseCallId(const string &callId);
    ami_uid_t GetCallId(const AMI_PARAMS &params);
    int AMI_QueueMemberAdded(AMI_PARAMS & params);
    int AMI_QueueMemberRemoved(AMI_PARAMS & params);
    int AMI_QueueMemberPaused(AMI_PARAMS & params);
    int AMI_QueueMemberStatus(AMI_PARAMS & params);
    int AMI_QueueJoin(AMI_PARAMS & params);
    int AMI_QueueLeave(AMI_PARAMS & params);
    int AMI_CoreShowChannel(const AMI_PARAMS &params);    

private:
  DWORD AMI_EventsThreadProc();
  DWORD AMI_RecvThreadProc();

  static DWORD WINAPI AMI_EventsThread(LPVOID param);
  static DWORD WINAPI AMI_RecvThread(LPVOID param);

public:
    int AMI_Create();  // Создание объектов AMI
    int AMI_Close();
    int AMI_Destroy();
    int AMI_Connect(const char* strHost, int nPort); // Подключение к серверу AMI
    int AMI_Init(const char* strUser, const char* strSecret); // Инициализация AMI и авторизация на сервере
    int AMI_Init(const char* strUser, const char* strSecret, const char* strChannel); // Инициализация AMI и авторизация на сервере
    int AMI_IsReady(); // Функция, проверяющая доступность подключения к AMI
    int AMI_IsConnected();
    int AMI_SetCallback(AMI_CALLBACK p); // Установка калбэк-функции обработки событий AMI
    int AMI_DoRequest(const char* strAction, AMI_PARAMS & mapParams); // Отправка запроса. Функция возвращает ActionID в случае успеха или 0 в случае неудачи
    int AMI_WaitForActionResponse(int nActionID, int& bResult, AMI_PARAMS & params, int nWaitTime = 10000); // Ожидание ответа на запрос.
    int AMI_WaitForActionResponseWithEvents(int nActionID, int& bResult, AMI_PARAMS & params, std::list<AMI_PARAMS> & followedEvents, int nWaitTime = 10000); // Ожидание ответа на запрос с множеством ответов

    int AMI_DoHangup(ami_uid_t nCallId);   // Завершение звонка по идентификатору звонка
    int AMI_DoHangup(const char* strCh);       // Завершение звонка по фрагменту имени соединенного канала

    int AMI_DoOriginate(ami_uid_t nCallId, const char* szTransport, const char* szPhone, const char* szExten, const char* szContext, const char* szApp, const char* szData, const char* szCid, int nTimeout = 40000, int bAsync = 1, AMI_PARAMS* answerParams = 0);

    int AMI_GetCallByChannel(const char* strId, Channel & _call); // Возвращение звонка по каналу
    int AMI_GetCall(const char* strId, Channel & _call, int bLockCrit = 1); // Возвращение звонка по идентификатору канала
    int AMI_GetCallsById(ami_uid_t nCallId, Channel & firstcall, Channel & secondcall); // Возвращение параметров звонка по идентификатору звонка
    const char* AMI_GetLocalVar(const char* strUniqueId, const char* strVar);
    int AMI_SetLocalVar(const char* strUniqueId, const char* strVar, const char* strVal);
    std::string AMI_GetVar(const char* strChannel, const char* strVar);
    int AMI_SetVar(const char* strChannel, const char* strVar, const char* strVal);

    void AMI_DumpCurrentCallsAndPairs();
    int AMI_IsHaveDahdiNotBridgedCalls();

    int AMI_GetCurrentCalls(AMI_CALLS& _calls);
    int AMI_GetCurrentCallsPairs(AMI_CALLS_PAIRS& _callsPairs);

    int AMI_LoadChannels();
};

#endif

/*--------------------------------------------------------------------------*\

  Copyright (C) Erpico, 2015


  All rights reserved. No part of this computer program may be reproduced,
  stored in any retrieval system, or transmitted, in any form or by any
  means, electronic, mechanical, photocopying, recording, or otherwise,
  without the prior written permission of Odin TeleSystems Inc., or without
  a permission stipulated in the agreement/contract under which this computer
  program was supplied.

\*--------------------------------------------------------------------------*/
