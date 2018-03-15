/************************************************************************
 *  created:    8.4.2008  17:54
 *  filename:   LogHandler.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __LOGHANDLER_H__
#define __LOGHANDLER_H__

#include "Core.h"

#include "LogRecord.h"

class CORE_API CLogHandler
{
protected:
  CLogLevel m_cLevel;

public:
  CLogHandler();
public:
  virtual ~CLogHandler(void);

public:
  virtual void Publish(const CLogRecord &_record) = 0;

public:
  virtual bool IsLoggable(const CLogRecord &_record);

public:
  const CLogLevel & GetLevel();
  void SetLevel(const CLogLevel &_cLevel);
};

#endif // __LOGHANDLER_H__