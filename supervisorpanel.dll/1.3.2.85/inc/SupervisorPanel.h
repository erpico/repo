#ifndef __SUPERVISORPANEL_H__
#define __SUPERVISORPANEL_H__

#ifdef SUPERVISORPANEL_EXPORTS
#define SUPERVISORPANEL_API __declspec(dllexport)
#else
#define SUPERVISORPANEL_API __declspec(dllimport)
#endif

#include "AclLib/AclManager.h"
#include "acllib/Config.h"
#include "ErpicoPBX/CTI.h"
#include "ErpicoCTI/WCTI_Call.h"
#include "ErpicoCTI/WCTI_Control.h"

#include <list>

class SupervisorPanelAdapter {
public:
  virtual AclManager * GetAclManager() = 0;
  virtual CtiManager * GetCtiManager() = 0;
  virtual std::list<CCTICall>& GetCurrentCalls() = 0;
  virtual std::list<SWCTIQueueInfo>& GetQueuesInfo() = 0;
  virtual Config* GetConfig() = 0;
  virtual bool isAllow(const char *ruleHandle) = 0;
  virtual bool isQueueVisible(const char *queueName) { return true; };  
};

SUPERVISORPANEL_API SupervisorPanelAdapter *GetSupervisorPanelAdapter();
SUPERVISORPANEL_API void SetSupervisorPanelAdapter(SupervisorPanelAdapter *adapter);

#endif // __SUPERVISORPANEL_H__
