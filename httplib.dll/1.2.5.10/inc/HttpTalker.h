/*
 * HttpTalker.h
 * 
 *
 * Капралов А.
 * 4.7.2013 2:57
 */

#ifndef __HTTPTALKER_H__
#define __HTTPTALKER_H__

#include "HttpLib.h"

#include <map>


typedef struct
{
  HWND        hWindow;     // window handle
  HINTERNET   hResource;   // HINTERNET handle created by InternetOpenUrl
} REQUEST_CONTEXT;

class HTTPLIB_API HttpTalker
{
public:
  HttpTalker();
  //HttpTalker(LPCTSTR referer, std::map<CString, CString> headers);

public:
  int get(LPCTSTR url, CString &content);
  int post(LPCTSTR url, CString &content, const CString &_strContent, const TCHAR *_headers,
           const int &_iPort, const char* chAcceptedType[], const bool &_bAsync = false);
  REQUEST_CONTEXT request_context;
  //int get(LPCTSTR url, CString &contentType, std::vector<BYTE> &content);
  //int get(LPCTSTR url, CString &contentType, HANDLE hFile);

  //int post(LPCTSTR url, CString &sendingContentType, CString &sendingContent, 
  //    CString &receivingContentType, CString &receivingContent);
};

#endif // __HTTPTALKER_H__



