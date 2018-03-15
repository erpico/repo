/***********************************************************************
 *  created:    4.6.2008  18:42
 *  filename:   HttpScanner.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __HTTPSCANNER_H__
#define __HTTPSCANNER_H__

#include "HttpToken.h"

#include "Core/Strings.h"

#include <set>
using std::set;

#include <string>
using std::string;

class CHttpScanner
{
private:
  enum ErrorCode
  {
    ERROR_UNEXPECTED_CHARACTER = 1001
  };

private:
  // Множество ключевых слов.
  set<string, NocaseStringComparator> m_setKeywords;
  
private:
  const string * m_pstrSource;
  // Текущий индекс.
  string::size_type m_stChIdx;
  // Последний считанный символ.
  char m_chCh;

private:
  // Говорит о достижении конца файла. 
  bool m_bEofReached;

public:
  CHttpScanner();

private:
  void Init();

public:
  void SetSource(const string *_pstrSource);

public:
  bool IsEofReached() const;

public:
  string::size_type GetCurrentIdx() const;
  void MoveTo(string::size_type _stIdx);

public:
  int ScanToken(CHttpToken & _cToken);
  int ScanToCrLf(string &_strStr);
  int ScanToSpace(string &_strStr);
  int ScanBytes(string &_strStr, int _iCount);
  int ScanToEnd(string &_strStr);

private:
  int Read();

private:
  int SkipInsignificantChars();

private:
  int ScanStartedWithLetter(CHttpToken & _cToken);
  int ScanStartedWithDigit(CHttpToken & _cToken);
  int ScanTspecial(CHttpToken &_cToken);
  int ScanDelimiter(CHttpToken &_cToken);

};

#endif // __HTTPSCANNER_H__