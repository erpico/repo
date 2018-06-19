/************************************************************************
 *  created:    22.1.2008  15:40
 *  filename:   RunnableCycle.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __RUNNABLECYCLE_H__
#define __RUNNABLECYCLE_H__

#include "Core.h"

#include "Runnable.h"
#include "Thread.h"

class CORE_API CRunnableCycle :
  public IRunnable
{
protected:
  CRITICAL_SECTION m_csMonitor;
  HANDLE           m_evWakeUp;
  int              m_nCycleTimeout;

private:
  CThread * m_pThread;

private:
  bool m_bActive;

public:
  CRunnableCycle(int nCycleTimeout = 0);
public:
  virtual ~CRunnableCycle();

public:
  virtual void Start();
  virtual void Stop();
  virtual void ForceExecute();

public:
  void Wait(DWORD dwTimeout = 0);

public:
  bool IsActive();
private:
  void SetActive(bool active);

protected:
  void Run();

protected:
  virtual void Execute() = 0;
};

#endif // __RUNNABLECYCLE_H__