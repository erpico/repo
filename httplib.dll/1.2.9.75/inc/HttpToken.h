/************************************************************************
 *  created:    4.6.2008  18:47
 *  filename:   HttpToken.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __HTTPTOKEN_H__
#define __HTTPTOKEN_H__

#include <string>
using std::string;

class CHttpToken
{
public:
  enum Type
  {
    TYPE_KEYWORD,
    TYPE_CRLF,
    TYPE_TSPECIAL,
    TYPE_DELIMITER,
    TYPE_NUMBER,
    TYPE_STRING
  };

public:
  static const string KEYWORD_HTTP;
  static const string KEYWORD_OPTIONS;
  static const string KEYWORD_GET;
  static const string KEYWORD_HEAD;
  static const string KEYWORD_POST;
  static const string KEYWORD_CRLF;

public:
  /*
    tspecials = "(" | ")" | "<" | ">" | "@"
              | "," | ";" | ":" | "\" | <">
              | "/" | "[" | "]" | "?" | "="
              | "{" | "}" | SP | HT
  */
  static bool IsTspecial(char _chCh);
  static bool IsDelimiter(char _chCh);

private:
  Type    m_eType;
  string  m_strValue;

public:
  CHttpToken();
  CHttpToken(Type _eType, const char *_strValue);

public:
  Type GetType();
  void SetType(Type _eType);

  const char * GetValue();
  void SetValue(const char *_strValue);
};


#endif // __HTTPTOKEN_H__