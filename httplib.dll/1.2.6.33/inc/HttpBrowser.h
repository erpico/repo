/********************************************************************
  created:    3.2.2007   13:05
  filename:   HttpBrowser.h
  author:     Kapralov A.
  
  purpose:	
  version:    1.0.1
  updated:    4.4.2007   21:02
*********************************************************************/

#ifndef __HTTPBROWSER_H__
#define __HTTPBROWSER_H__

#include "HttpLib.h"

#include <list>
#include <vector>
#include <map>

#include <afxinet.h>

#include "Cookie.h"
#include "BrowserException.h"

#define ACCEPT_TYPES_MAX_SIZE 128

//
// <KAE>
class HTTPLIB_API CHttpBrowser
{
public: // Construction/Destruction
  
  // Initial constructor
  CHttpBrowser(
      const char * _szServerName,
      LPCTSTR * _ppstrAcceptTypes = NULL,
      bool _bKeepAlive    = true, 
      bool _bSecure       = false, 
      bool _bAutoRedirect = true,
      LPCTSTR pstrUserName = NULL, 
      LPCTSTR pstrPassword = NULL 
    );
  
  // Destructor
  virtual ~CHttpBrowser();

private:
  // Default constructor
  CHttpBrowser();
  // Copy constructor
  CHttpBrowser(const CHttpBrowser & _HttpBrowser);

private: // Properties
  CInternetSession m_Session;
  CHttpConnection * m_pServer;

private:
  CString m_sServerName;
  CString m_strObject;
  CString m_sUserName;
  CString m_sPassword;
  INTERNET_PORT m_nPort;

private: // Connection settings
  bool m_bKeepAlive;
  bool m_bSecure;
  bool m_bAutoRedirect;
  LPCTSTR m_arrAcceptTypes[ACCEPT_TYPES_MAX_SIZE];
  DWORD m_dwHttpRequestFlags;

private: // Cookies
  std::list<CCookie> m_Cookies;

private:
  CString m_sLastServerResponse;
  CString m_sLastReceivedContent;
  std::map<CString, CString> headers;

public:
  // HTTP request type
  enum ERequestType
  {
    RT_POST = 0,
    RT_GET  = 1
  };

private:
  
  //
  void SetAcceptTypes(const LPCTSTR * _ppstrAcceptTypes = NULL);
  //
  void SetRequestFlags(bool _bKeepAlive, bool _bSecure, bool _bAutoRedirect);
  //
  void SetRequestHeaders(
      CString & _RequestHeaders,
      LPCTSTR _pstrHeaders = NULL, DWORD _dwHeadersLen = 0
    );
  //
  void ConvertCookiesToString(CString & _sCookies);
  //
  CHttpFile * MakeRequest(
    DWORD &dwRet, 
    ERequestType _RequestType      = RT_GET,
    LPCTSTR      _szObjectName     = "/",
    LPCTSTR      _szReferer        = NULL,
    LPCTSTR      _pstrHeaders      = NULL,
    DWORD        _dwHeadersLen     = 0,
    LPVOID       _RequestBody      = NULL,
    DWORD        _dwRequestBodyLen = 0);
  //
  void ReadServerResponse(CHttpFile * _pHttpFile);
  //
  void ReadTextContent(CHttpFile * _pHttpFile);
  //
  void ReadContent(CHttpFile * _pHttpFile, std::vector<BYTE> &content);
  //
  void ReadContentTo(CHttpFile * _pHttpFile, HANDLE hFile);
  //
  void ReadCookies(CHttpFile * _pHttpFile);

public: // Operations

  // Makes server to reconnect
  virtual void Reconnect();

  // Requests server.
  // Returns the status code associated with an HTTP request.
  DWORD Request(
      ERequestType _RequestType      = RT_GET,
      LPCTSTR      _szObjectName     = "/",
      LPCTSTR      _szReferer        = NULL,
      LPCTSTR      _pstrHeaders      = NULL,
      DWORD        _dwHeadersLen     = 0,
      LPVOID       _RequestBody      = NULL,
      DWORD        _dwRequestBodyLen = 0
    );

  DWORD GetContent(LPCTSTR _szObjectName, std::vector<BYTE> &content, CString &contentType);
  DWORD GetContent(LPCTSTR _szObjectName, HANDLE hFile, CString &contentType);


  const char * GetLastServerResponse();
  const char * GetLastReceivedContent();
  void GetLastReceivedContent(CString & _sContent);
  const char * GetHeader(const char *name);


protected:
  void GetBoundary(CString & _Boundary);

private:
  void HandleInternetException( CHttpFile * pFile, CInternetException * pEx );

private:
  class CEqualCookieName
  {
  private:
    CString m_sCookieName;

  public: // Construction/Destruction
    
    // Initial constructor
    CEqualCookieName(const char * _szCookieName);
    
  public: // Operators
    bool operator ()(const CCookie & _Cookie);
  };
};

#endif // __BROWSER_H__