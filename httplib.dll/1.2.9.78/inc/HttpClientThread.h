/************************************************************************
 *  created:    4.6.2008  17:02
 *  filename:   HttpClientThread.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __HTTPCLIENTTHREAD_H__
#define __HTTPCLIENTTHREAD_H__

#include "HttpLib.h"

#include "HttpResponse.h"

#include "Core/Thread.h"

class CHttpServer;

class HTTPLIB_API CHttpClientThread :
  public CThread
{
public:
  static bool fCSInitialized;
  static CRITICAL_SECTION csCounter;
  static int iCounter;

public:
  enum State
  {
    STATE_INITIAL   = 0,
    STATE_PROCESS   = 1,
    STATE_FINISHED  = 2
  };

private:
  SOCKET m_clientSocket;
  sockaddr_in sClient;

private:
  State m_eState;
  int m_bGzipAcceptable;

private:
  CHttpServer *m_pServer;

public:
  CHttpClientThread(CHttpServer *_pServer, SOCKET _clientSocket, sockaddr_in _sClient);
  ~CHttpClientThread();

  SOCKET GetSocket() { return m_clientSocket; }
  
public:
  virtual void Run();

private:
  void ProcessRequest();

public:
  State GetState();

public:
  void Close();

private:
  int ReadFromSocket(char *_strBuffer, int _iBufferSize, int &_iBytesRead);
  int WriteToSocket(const char *_strData, int _iDataSize);

private:
  int SendResponse(int _iStatusCode, const char *_strReasonPhrase);
  int SendResponse(CHttpResponse &_cResponse);

};


#endif // __HTTPCLIENTTHREAD_H__