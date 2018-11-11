/*
 * CtiPriest.h
 * 
 *
 * Капралов А.
 * 24.4.2013 15:44
 */
#ifndef __CTIPRIEST_H__
#define __CTIPRIEST_H__

#include "ErpicoPBX.h"

#include "Cti.h"

#include "AclLib/AclObjects.h"
#include "AclLib/ServerPriest.h"

class ERPICOPBX_API CtiResponse : public ServerResponse {
friend class CtiPriest;

public:
  CtiResponse();
  virtual ~CtiResponse();

public:
  CtiUserSetting *userSetting;
  
  int getIsOC()
  {
    return bIsOC;
  }

  int getOCUpdateStatus()
  {
    return iOCUpdateStatus;
  }

  void setIsOC(bool _bIsOC)
  {
    bIsOC = _bIsOC;
  }

  void setOCUpdateStatus(int _iOCUpdateStatus)
  {
    iOCUpdateStatus = _iOCUpdateStatus;
  }
  
private:
  std::list<Queue *> queues;
  std::list<QueueAgent *> queueAgents;
  bool bIsOC;
  int iOCUpdateStatus;

public:
  const std::list<Queue *> & getQueues() const;
  const std::list<QueueAgent *> & getQueueAgents() const;

protected:
  void addQueue(Queue *queue);
  void addQueueAgent(QueueAgent *queueAgent);

};

class CtiPriest : public ServerPriest {
public:
  CtiPriest();
  virtual ~CtiPriest();

private:
  int prepareUserSettingRequest(CString &request, const User &user);
  int prepareUpdateUserSettingRequest(CString &request, const User &user, 
      const CtiUserSetting &setting);
  int prepareGetQueuesRequest(CString &request, const User & user, const char *name = NULL);
  int prepareGetQueueAgentsRequest(CString &request, const User & user, 
      long queueId = 0, long userId = 0);
  int prepareCreateQueueAgentRequest(CString &request, const User & user, 
      long queueId, long userId, int penalty);
  int prepareUpdateQueueAgentRequest(CString &request, const User & user, 
    long queueId, long userId, long newQueueId, long newUserId, int penalty);
  int prepareDeleteQueueAgentRequest(CString &request, const User & user, 
    long queueId, long userId);
  int prepareUpdateRequest(CString &request, const User & user, const Queue* queue);

private:
  int callService(const CString &request, ServerResponse *pServerResponse);

protected:
  virtual int parseNode(CXMLNode &node, ServerResponse *pServerResponse);

private:
  int parseUserSettingNode(CXMLNode &cdrNode, CtiResponse &response);
  int parseQueuesNode(CXMLNode &queuesNode, CtiResponse &response);
  int parseQueueNode(CXMLNode &queueNode, CtiResponse &response);
  int parseQueueAgentsNode(CXMLNode &queuesNode, CtiResponse &response);
  int parseQueueAgentNode(CXMLNode &queueNode, CtiResponse &response);

public:
  int getUserSetting(CtiUserSetting &result, const User &user);
  int updateUserSetting(const User &user, CtiUserSetting &setting);

public:
  int getQueues(std::list<Queue> &result, const User &user);
  int getQueue(Queue &result, const User &user, const char *name);
  int updateQueue(const User &user, const Queue* queue);
  int getQueueAgents(std::list<QueueAgent> &result, const User &user, 
      long queueId = 0, long userId = 0);
  int createQueueAgent(const User &user, long queueId, long userId, int penalty);
  int updateQueueAgent(const User &user, long queueId, long userId, 
      long newQueueId, long newUserId, int penalty);
  int deleteQueueAgent(const User &user, long queueId, long userId);
  int getQueueByPhone(unsigned long long iCallId, const User &user, bool &bIsOC);
  int prepareGetQueueByPhoneRequest(CString &request, unsigned long long iCallId, const User &user);
  int parseQueueByPhone(CXMLNode &node, CtiResponse &response);
  int planOCCall(const unsigned long long &iCallId, const User &user, const DWORD &dwTimeStamp, int &iStatus);
  int preparePlanOCCalRequest(CString &request, const User &user, const unsigned long long &iCallId, const DWORD &dwTimeStamp);
  int parsePlanOCCall(CXMLNode &node, CtiResponse &response);
};

#endif // __CTIPRIEST_H__
