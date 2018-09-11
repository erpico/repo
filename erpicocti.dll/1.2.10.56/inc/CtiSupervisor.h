/*
 * CtiSupervisor.h
 * 
 *
 * Капралов А.
 * 9.9.2013 16:02
 */
#ifndef __CTISUPERVISOR_H__
#define __CTISUPERVISOR_H__

#include "ErpicoCTI.h"

#include "WCTI_Control.h"

#include <list>
#include <map>

struct CtiQueuesSummary {
  int totalAgentsCount;
  int talkingAgentsCount;
  int readyAgentsCount;
  int notReadyAgentsCount;
  int waitingCallsCount;

  CtiQueuesSummary() {
    totalAgentsCount    = 0;
    talkingAgentsCount  = 0;
    readyAgentsCount    = 0;
    notReadyAgentsCount = 0;
    waitingCallsCount   = 0;
  }
};

enum CtiAgentState {
  CTI_AGENT_STATE_UNKNOWN     = 0,
  CTI_AGENT_STATE_READY       = 1,
  CTI_AGENT_STATE_NOT_READY   = 2,
  CTI_AGENT_STATE_AFTERWORK   = 3,
  CTI_AGENT_STATE_CALL        = 4,
  CTI_AGENT_STATE_TALKING     = 5,
  CTI_AGENT_STATE_UNAVAILABLE = 6
};

class ERPICOCTI_API CtiSupervisor {
public:
  CtiSupervisor();
  virtual ~CtiSupervisor();

public:
  static void GetQueuesSummary(const std::list<SWCTIQueueInfo> &queueInfoList, 
      CtiQueuesSummary &result);
  
  static void GetAgentsStates(const std::list<SWCTIQueueInfo> &queueInfoList, 
      std::map<std::string, CtiAgentState> &result);
  
  static CtiAgentState GetAgentState(const char *agentName, const std::list<SWCTIQueueInfo> &queueInfoList);  
  
  static int GetCurrentMaxWaitingTime(const SWCTIQueueInfo &queueInfo);
  
  static int GetReadyAgentsCount(const SWCTIQueueInfo &queueInfo);
  
  static const SWCTIQueueInfoMember * GetAgent(const char *agentName, const SWCTIQueueInfo &queueInfo);

  static void CountMembersAndCalls(std::list<SWCTIQueueInfo> &queueInfoList, int& members, int& calls);
};

#endif // __CTISUPERVISOR_H__
