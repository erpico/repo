/*
 * RestUtils.h
 * 
 *
 * Капралов А.
 * 10.7.2013 17:37
 */
#ifndef __RESTUTILS_H__
#define __RESTUTILS_H__

#include "HttpLib.h"

class HTTPLIB_API RestUtils {
public:
  static int getString(const char *url, CString &result);
  static int sendPost(const char *url, CString &result, const CString &_strContent, const TCHAR* _headers,
	                  const char* chAcceptedType[]);
  static int sendPost(const char *url, std::string &result, const CString &_strContent, const TCHAR* _headers,
	                  const char* chAcceptedType[]);
};

#endif // __RESTUTILS_H__
