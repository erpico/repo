/*
 * HttpUtils.h
 * 
 *
 * Капралов А.
 * 18.4.2013 15:46
 */

#ifndef __HTTPUTILS_H__
#define __HTTPUTILS_H__

#include "HttpLib.h"

class HTTPLIB_API HttpUtils {
public:
  static int downloadFile(const char *url, CString &fileName);
};

#endif // __HTTPUTILS_H__

