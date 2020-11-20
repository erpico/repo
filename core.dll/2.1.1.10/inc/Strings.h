/************************************************************************
 *  created:    3.4.2008  17:50
 *  filename:   Strings.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __STRINGS_H__
#define __STRINGS_H__

#include "Core.h"

#include <string>
#include <sstream>
#include <vector>

template <typename T>
std::string ToString(const T &_tVal)
{
  std::ostringstream cOss;
  cOss << _tVal;
  return cOss.str();
}

template<typename T> 
T Parse(const std::string &_strStr) 
{
  return Parse<T>(_strStr.c_str());
}

template<typename T> 
T Parse(const char *_strStr) 
{
  std::istringstream cIss(_strStr);
  T tRes;
  cIss >> tRes;
  return tRes;
}

class CORE_API NocaseStringComparator
{
public:
  bool operator ()(const std::string &_x, const std::string &_y) const;
};

/*class CORE_API NocaseMFCStringComparator
{
public:
  bool operator ()(const CString &_x, const CString &_y) const;
};*/

CORE_API void TrimRight(std::string &str, const std::string &_substr);

CORE_API void trim(const std::string& str, std::string &result, const std::string& whitespace = " \t");

CORE_API void replace(std::string &str, const char* chFrom, const char* chTo, const bool &_bRemoveLast = false, const bool &_bRemoveFirst = false);

CORE_API void tokenize(const std::string &_strSource, const std::string &_strTemplate, std::vector<std::string> &_vectStrings);

CORE_API void tokenize(const std::string &_strSource, const std::string &_strTemplate, std::vector<DWORD> &_vectStrings);

CORE_API int CompareNoCase(const std::string &_str1, const std::string &_str2, const std::locale &_loc);

CORE_API std::string ToUpper(const std::string &_str, const std::locale &_loc);

CORE_API std::string ToLower(const std::string &_str, const std::locale &_loc);

CORE_API void GetSurnameNamePatronymic(const std::string &_strDriverFio, std::string &_strName, std::string &_strPatronymic, std::string &_strSurname);

CORE_API bool FindSubstrInTokenizedString(const std::string &_strSource, const std::string &_strToken, const std::string &_strFind);

CORE_API void RemoveLetters(const std::string &_strSource, const std::string &_strLetters, std::string &_strRet);

CORE_API bool IsDigit(const std::string &_strIn, const std::locale &_loc, std::string &_strOut, const bool &_bRemoveLetters /* = false */);

CORE_API std::string CreateRandomString(const int &_iCount);

#endif // __STRINGS_H__