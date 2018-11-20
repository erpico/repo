/************************************************************************
 *  created:    8.4.2008  19:01
 *  filename:   CLogRecord.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __LOGRECORD_H__
#define __LOGRECORD_H__

#include "Core.h"

#include "LogLevel.h"

class CORE_API CLogRecord
{
private:
  CLogLevel    m_cLevel;
  string       m_strMessage;
  const char * m_strFile;
  int          m_iLine;

public:
  CLogRecord();
  CLogRecord(const CLogLevel &_cLevel, const char * _strMessage, 
      const char * _strFile = "", int _iLine = 0);

public:
  const CLogLevel & GetLevel()   const;
  const char *      GetMessage() const;
  const char *      GetFile()    const;
  int               GetLine()    const;

public:
  void SetLevel(const CLogLevel &_level);
  void SetMessage(const char *_message);
  void SetFile(const char *_file);
  void SetLine(int _line);
};

#endif // __LOGRECORD_H__