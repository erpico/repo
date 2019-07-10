/********************************************************************
  created:    3.2.2007   15:50
  filename:   BrowserException.h
  author:     Kapralov A.
  
  purpose:    
  version:    1.0
*********************************************************************/

#ifndef __BROWSEREXCEPTION_H__
#define __BROWSEREXCEPTION_H__

#include "HttpLib.h"

#include "Core/MyException.h"

//
// <KAE>
class HTTPLIB_API CBrowserException : public CMyException
{
public: // Construction/Destruction
  
  // Default constructor
  CBrowserException();
  // Initial constructor
  CBrowserException(const char * szErrorMessage);
  // Initial constructor
  CBrowserException(DWORD errorCode, const char * szErrorMessage);
};

#endif // __BROWSEREXCEPTION_H__