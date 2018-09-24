/************************************************************************
 *  created:    4.6.2008  18:43
 *  filename:   HttpParser.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __HTTPPARSER_H__
#define __HTTPPARSER_H__

#include "HttpLib.h"

#include "HttpScanner.h"
#include "HttpRequest.h"

#include <map>
using std::map;

#include <vector>
using std::vector;

#include <utility>
using std::pair;

class HTTPLIB_API CHttpRequestParser
{
private:
  string * m_pstrSource;
  int iOffset;

private:
  CHttpScanner  m_cScanner;
  CHttpToken    m_cToken;

private:
  string m_strMethod;
  string m_strUri;
  short m_shMajorProtocolVersion;
  short m_shMinorProtocolVersion;
  map<string, string> m_mapHeaders;
  string m_strBody;

public:
  enum Stage
  {
    STAGE_REQUEST_LINE,
    STAGE_HEADERS,
    STAGE_BODY
  };
  Stage m_eStage;

private:
  string::size_type m_stStageStartIdx;

public:
  CHttpRequestParser();

private:
  void Init();

public:
  int Parse(string &_strSource);
  int Continue();

public:
  bool IsEofReached() const;

public:
  const char * GetMethod() const;
  const char * GetUri() const;
  void GetProtocolVersion(short &_shMajor, short &_shMinor) const;
  const map<string, string> & GetHeaders() const;
  const char * GetBody() const;

public:
  void GetRequest(CHttpRequest &_cRequest);

private:
  int ParseRequestLine();
  int ParseHeaders();
  int ParseBody();

private:
  int ParseHttpVersion();

};


#endif // __HTTPPARSER_H__