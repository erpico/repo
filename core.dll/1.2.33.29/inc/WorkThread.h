#pragma once

#include <afxtempl.h>
#include <afxmt.h>
#include "ThrSafeValue.h"

#include "Core.h"

//namespace NotifyWndType
//{
//  enum Id {
//    er_CallRequest = 0,
//    er_Operators = 1,
//    er_Paycard   = 2,
//    er_Sms       = 3,
//    er_Remind    = 4,
//    er_OperMessage = 5,
//    er_Talk = 6,
//    er_ProgramUpdate = 7,
//    er_TimeSyncProblem = 8,
//    _notifyTypeCount
//  };
//}

namespace WorkThread
{
  enum ControlStatus
  {
    eOk,
    eFail,
    eAlreadyCreated,
    eNotCreated
  };

  class CORE_API Thread
  {
    HANDLE m_hThread;
    HANDLE m_hControlEvent;
    HANDLE m_hClientEvent;
    SafeBool m_fDestroyFlag;

  public:
    Thread();
    ~Thread();

    ControlStatus Create();
    ControlStatus Destroy();

    ControlStatus AsyncDestroy();
    bool IsRunning();

  protected:
    bool CreateControlEvents();
    bool DestroyControlEvents();

    static DWORD WINAPI WorkerThreadFunc(LPVOID pParam);
    void InThreadWorkerFunc(LPVOID pParam);
    virtual void UserDefinedThreadProc(LPVOID pParam) = 0;
  };

}; //namespace WorkThread
