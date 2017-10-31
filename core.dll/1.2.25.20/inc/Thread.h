/********************************************************************
created:    22.11.2006   18:37
filename:   Thread.h
author:	    Kapralov A.

purpose:    Класс-обёртка для WinAPI потока
version:    1.0
*********************************************************************/

#ifdef WIN32
#ifndef __THREAD_H__
#define __THREAD_H__

#include "Core.h"

#include "Runnable.h"

#include <windows.h>

//
// <KAE>
class CORE_API CThread : 
  public IRunnable
{
public: // Construction / Destruction
  CThread(void);
  CThread(IRunnable * _pRunnable);
  virtual ~CThread(void);

protected: // IRunnable
  virtual void Run();

public:

  //Infinite timeout
  static const DWORD INFINITE_TIMEOUT;

private:

  // Thread's handle
  HANDLE m_hThread;

private:
  class ThreadFuncParameter
  {
  private: // Properties
    IRunnable * m_pRunnable;

  public: // Construction / Destruction
    ThreadFuncParameter(IRunnable * _pRunnable)
    { m_pRunnable = _pRunnable;}

  public: // Operations
    IRunnable * GetRunnable()
    { return m_pRunnable;}
  } * m_pParam;

public: // Operations

  // Starts thread
  virtual void Start();
  // Terminates thread
  void Terminate();
  // Call this member function if you need for waiting this thread
  void Wait(DWORD dwMiliseconds = INFINITE_TIMEOUT);
  // Suspends thread
  void Suspend();
  // Resumes thread
  void Resume();

private:
  static DWORD WINAPI ExecuteRun(LPVOID lpParam);
};

#endif // __THREAD_H__
#endif