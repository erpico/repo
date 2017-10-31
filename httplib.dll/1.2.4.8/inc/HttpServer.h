/************************************************************************
 *  created:    4.6.2008  0:55
 *  filename:   HttpServer.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __HTTPSERVER_H__
#define __HTTPSERVER_H__

#include "HttpLib.h"

#include "TcpServer.h"
#include "HttpClientTreadsCleaner.h"

#include "HttpServlet.h"


#include <map>
using std::map;

class HTTPLIB_API CHttpServer :
  public CTcpServer
{
public:
  int Port;
  int MaxConnections;

  static int ExtractServletNameFromUri(const char *_strUri, string &_strName);

private:
  map<string, CHttpServlet *> m_mapServlets;

private:
  CHttpClientTreadsCleaner m_cCleaner;

public:
  CHttpServer();
  CHttpServer(int _iPort);
  CHttpServer(int _iPort, int _iBackLog);

public:
  virtual void Start();
  virtual void Stop();
  void LoadServlets();

protected:
  virtual void HandleNewConnection(SOCKET _clientSocket);

public:
  CHttpServlet * GetServlet(const char *_strUri);

private:
  CHttpServlet * LoadServlet(const char *_strServletDllName);


};

#endif // __HTTPSERVER_H__