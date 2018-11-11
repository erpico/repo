/************************************************************************
 *  created:    7.6.2008  11:58
 *  filename:   HttpRequest.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __HTTPREQUEST_H__
#define __HTTPREQUEST_H__

#include "HttpLib.h"

#include "Core/ExpImpStlClasses.h"

#include <string>
using std::string;

#include <map>
using std::map;

class HTTPLIB_API CHttpRequest
{

private:
  string m_strMethod;
  string m_strUri;
  short m_shMajorProtocolVersion;
  short m_shMinorProtocolVersion;
  map<string, string> m_mapHeaders;
  string m_strBody;

public:
  CHttpRequest();

public:
  const char * GetMethod() const;
  void SetMethod(const char *_strMethod);

  const char * GetUri() const;
  void SetUri(const char *_strUri);

  void GetProtocolVersion(short &_shMajor, short &_shMinor) const;
  void SetProtocolVersion(short _shMajor, short _shMinor);

  const map<string, string> & GetHeaders() const;
  void SetHeaders(const map<string, string> &_mapHeaders);
  
  const char * GetBody() const;
  void SetBody(const char *_strBody);
};

#endif // __HTTPREQUEST_H__