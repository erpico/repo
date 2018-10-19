#ifndef __URLCODING_H__
#define __URLCODING_H__

#include <string>
#include "HttpLib.h"
 
namespace UrlCoding {
    HTTPLIB_API std::string urlEncode(const std::string &url);
    HTTPLIB_API std::string urlDecode(const std::string &encoded);
     
    HTTPLIB_API std::string charToHex(unsigned char c);
    HTTPLIB_API unsigned char hexToChar(const std::string &str);
}

#endif