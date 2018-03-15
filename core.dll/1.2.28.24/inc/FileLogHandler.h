/************************************************************************
 *  created:    9.4.2008  15:33
 *  filename:   FileLogHandler.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __HTMLFILELOGHANDLER_H__
#define __HTMLFILELOGHANDLER_H__

#include "Core.h"

#include "LogHandler.h"

class CORE_API CFileLogHandler :
  public CLogHandler
{
private:
  HANDLE m_hFile;

public:
  CFileLogHandler();
  virtual ~CFileLogHandler();

public:
  virtual int Create(const char *_fileName);

public:
  virtual bool IsLoggable(const CLogRecord &_record);

public:
  virtual void Publish(const CLogRecord &_record);

public:
  static void CreateLogFileName(string &_result, const char *dir = NULL, const char *prefix = NULL);

};

#endif // __HTMLFILELOGHANDLER_H__

