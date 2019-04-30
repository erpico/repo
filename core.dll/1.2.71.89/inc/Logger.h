/************************************************************************
 *  created:    8.4.2008  17:37
 *  filename:   Logger.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "Core.h"

#include "LogLevel.h"
#include "LogRecord.h"
#include "LogHandler.h"

#include <vector>
using std::vector;


class CORE_API CLogger
{
private:
  static CLogger m_cInstance;

public:
  static CLogger * GetLogger();

protected:
  //EXPORT_STL_VECTOR(CORE_API, CLogHandler *)  

private:
  CRITICAL_SECTION m_csMonitor;

private:
  CLogLevel m_cLevel;

private:
  vector<CLogHandler *> vctHandlers;

/*private:
  char * strBuffer;*/

public:
  CLogger();
  ~CLogger();

public:
  bool IsLoggable(const CLogLevel &_cLevel);

public:
  const CLogLevel & GetLevel();
  void SetLevel(const CLogLevel &_cLevel);

public:
  void AddHandler(CLogHandler *_pHandler);
  void RemoveHandler(CLogHandler *_pHandler);

public:
  void Log(const CLogRecord &_cRecord);
  void Log(const CLogLevel &_cLevel, const char *_strMessage, ...);
  void LogVaList(const CLogLevel &_cLevel, const char *_strMessage, va_list _vlArgList);
  void Log(const CLogLevel &_cLevel, int _iLine, const char *_strFile,
      const char *_strMessage, ...);
  void LogVaList(const CLogLevel &_cLevel, const char *_strFile, int _iLine, 
      const char *_strMessage, va_list _vlArgList);

public:
  void Warn( int _iLine, const char *_strFile, const char *_strMessage, ...);
  void Warn(const char *_strMessage, ...);
  void Info(const char *_strMessage, ...);
  void Debug(const char *_strMessage, ...);
};

extern CORE_API CLogger *g_pLogger;

#endif // __LOGGER_H__