/************************************************************************
 *  created:    4.6.2008  0:30
 *  filename:   TcpServer.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __TCPSERVER_H__
#define __TCPSERVER_H__

#include "HttpLib.h"

#include "Core/RunnableCycle.h"

#include <WinSock2.h>

class HTTPLIB_API CTcpServer : 
  public CRunnableCycle
{
private:
  SOCKET m_serverSocket;

private:
  int m_iPort;
  int m_iBackLog;

public:
  CTcpServer();
  CTcpServer(int _iPort);
  CTcpServer(int _iPort, int _iBackLog);

public:
  virtual int Init(int _iPort, int _iBackLog);
  virtual int Init();

public:
  virtual int GetPort();
  virtual int GetBackLog();

protected:
  virtual void Execute();

public:
  virtual void Stop();

protected:
  sockaddr_in  sClient;
  virtual void HandleNewConnection(SOCKET _clientSocket);

};



#endif // __TCPSERVER_H__
