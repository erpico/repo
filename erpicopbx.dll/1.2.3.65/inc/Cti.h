/*
 * Cti.h
 * 
 *
 * Капралов А.
 * 23.4.2013 16:18
 */

#ifndef __CTI_H__
#define __CTI_H__

#include "ErpicoPBX.h"

#include "Core/RunnableCycle.h"

#include "AclLib/AclObjects.h"

class ERPICOPBX_API CtiUserSetting {
public:
  bool doNotDisturb;
  bool callForwardingAll;
  CString callForwardingAllNumber;
  bool callForwardingBusy;
  CString callForwardingBusyNumber;
  bool callForwardingUnavailable;
  CString callForwardingUnavailableNumber;
  bool recordIncoming;
  bool recordOutgoing;
  bool recordInternal;
  bool callBack;

public:
  CtiUserSetting() : 
      doNotDisturb(false), 
      callForwardingAll(false),
      callForwardingBusy(false),
      callForwardingUnavailable(false),
      recordIncoming(false),
      recordOutgoing(false),
      recordInternal(false),
      callBack(false) {
  }
};

class Queue {
public:
  Queue()
  {
    id = 0; name = ""; fullname = ""; description = ""; url = ""; closeOnHangup = 0; isViq = 0; hidden = false; iServiceId = 0;
  }

  long id;
  CString name;
  CString fullname;
  CString description;
  CString url;
  int closeOnHangup;
  int isViq;
  bool hidden;
  int iServiceId;
};

class QueueAgent {
public:
  long queueId;
  long userId;
  int penalty;
};

class CtiPriest;

class ERPICOPBX_API CtiManager {
private:
  const User *pUser;

private:
  CRITICAL_SECTION csQueuesMonitor;
  std::list<Queue> queues;
  std::map<CString, const Queue *> queueNameMap;
  std::map<long, const Queue *> queueIdMap;

private:
  class QueueCacheUpdater : public CRunnableCycle {
  private:
    CtiManager *ctiManager;

  public:
    QueueCacheUpdater(CtiManager *ctiManager);

  public:
    void Execute();
  } queueCacheUpdater;

private:
  CtiPriest *pPriest;

public:
  CtiManager();
  virtual ~CtiManager();

public:
  int initialize(const char *serverUrl, const User *pUser);

public:
  int getUserSetting(CtiUserSetting &result);
  int updateUserSetting(CtiUserSetting &result);

private:
  int loadQueues();
  void updateCachedQueue(const Queue &queue);

private:
  const Queue * getCachedQueue(const char *name);
  const Queue * getCachedQueue(long id);

public:
  int getQueue(Queue &result, const char *name, bool cached = true);

public:
  void startQueueCache();
  void stopQueueCache();

public:
  int getQueueAgents(std::list<QueueAgent> &result, long queueId = 0, long userId = 0);
  int setQueueAgent(long queueId, long userId, int penalty);
  int deleteQueueAgent(long queueId, long userId);

public:
  int putAgentInQueues(long agentId);

public:
  int updateQueue(const Queue* queue);
  int getQueueByPhone(unsigned long long iCallId, bool &bIsOC);
  int planOCCall(const unsigned long long &iCallId, const DWORD &dwTimeStamp, int &iStatus);
};

#endif // __CTI_H__
