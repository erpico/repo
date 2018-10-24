/************************************************************************
 *  created:    9.4.2008  4:43
 *  filename:   ConsoleLogHandler.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __CONSOLELOGHANDLER_H__
#define __CONSOLELOGHANDLER_H__

#include "Core.h"

#include "LogHandler.h"

class CORE_API CConsoleLogHandler :
  public CLogHandler
{
public:
  CConsoleLogHandler();

public:
  virtual void Publish(const CLogRecord &_cRecord);
};


#endif // __CONSOLELOGHANDLER_H__
