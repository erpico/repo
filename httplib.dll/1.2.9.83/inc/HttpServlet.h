/************************************************************************
 *  created:    7.6.2008  15:17
 *  filename:   HttpServlet.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __HTTPSERVLET_H__
#define __HTTPSERVLET_H__

#include "HttpLib.h"

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpParser.h"
#include "Winsock2.h"

class CHttpServer;

class HTTPLIB_API CHttpServlet
{
public:
  sockaddr_in sClient;

public:
  CHttpServlet();

public:
  virtual void ProcessRequest(CHttpRequest &_cRequest, CHttpResponse &_cResponse, const CHttpServer *pServer = NULL) = 0;
  virtual void StopAllThreads() {}
};

typedef CHttpServlet * (*GetServletFunction)(void); 

#endif // __HTTPSERVLET_H__