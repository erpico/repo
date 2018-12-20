/************************************************************************
 *  created:    7.6.2008  12:48
 *  filename:   HttpResponse.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __HTTPRESPONSE_H__
#define __HTTPRESPONSE_H__

#include "HttpLib.h"

#include "Core/Strings.h"

#include <map>
using std::map;

#include <string>
using std::string;

class HTTPLIB_API CHttpResponse
{
private:
  int m_iStatusCode;
  string m_strReasonPhrase;
  short m_shMajorProtocolVersion;
  short m_shMinorProtocolVersion;
  map<string, string, NocaseStringComparator> m_mapHeaders;
  string m_strBody;

public:
  CHttpResponse();

public:
  int GetStatusCode() const;
  void SetStatusCode(int _iStatusCode);

  const char * GetReasonPhrase() const;
  void SetReasonPhrase(const char *_strReasonPhrase);

  void GetProtocolVersion(short &_shMajor, short &_shMinor) const;
  void SetProtocolVersion(short _shMajor, short _shMinor);

  const map<string, string, NocaseStringComparator> & GetHeaders() const;
  void SetHeaders(const map<string, string, NocaseStringComparator> &_lstHeaders);
  void AddHeader(const char *_strName, const char *_strValue);
  void RemoveHeaders(const char *_strName);

  const char * GetBody() const;
  void SetBody(const char *_strBody);

public:
  void ToString(string &_strResult);
  void ToGzippedStream(string &_strResult, char*& _pResultBuf, int& _coResultBuf);

};

#endif // __HTTPRESPONSE_H__