/************************************************************************
 *  created:    7.6.2008  15:56
 *  filename:   HttpClientTreadsCleaner.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __HTTPCLIENTTREADSCLEANER_H__
#define __HTTPCLIENTTREADSCLEANER_H__

#include "HttpLib.h"

#include "HttpClientThread.h"

#include "Core/RunnableCycle.h"

#include <list>
using std::list;

class HTTPLIB_API CHttpClientTreadsCleaner :
  public CRunnableCycle
{
private:
  CRITICAL_SECTION m_csMonitor;
  HANDLE m_hWakeUpEvent;

  list<CHttpClientThread *> m_lstPool;

public:
  CHttpClientTreadsCleaner();
  ~CHttpClientTreadsCleaner();

  list<CHttpClientThread *> GetPool() { return m_lstPool; }

protected:
  void Execute();

public:
  virtual void Stop();

public:
  void Add(CHttpClientThread * _pClientThread);
};




#endif // __HTTPCLIENTTREADSCLEANER_H__