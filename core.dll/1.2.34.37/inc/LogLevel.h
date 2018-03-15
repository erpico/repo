/************************************************************************
 *  created:    8.4.2008  19:05
 *  filename:   CLogLevel.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/

#ifndef __LOGLEVEL_H__
#define __LOGLEVEL_H__

#include "Core.h"

#include <string>
using std::string;

class CORE_API CLogLevel 
{
public:
  static const CLogLevel OFF;
  static const CLogLevel SEVERE;
  static const CLogLevel WARNING;
  static const CLogLevel INFO;
  static const CLogLevel DEBUG_MSG;
  static const CLogLevel ALL;

private:
  string m_strName;
  int    m_iVal;

public:
  CLogLevel(const char *_strName, int _iValue);
  CLogLevel(const CLogLevel &_cAnotherLevel);

public:
  bool operator  <(const CLogLevel &_cAnotherLevel) const;
  bool operator <=(const CLogLevel &_cAnotherLevel) const;
  bool operator ==(const CLogLevel &_cAnotherLevel) const;
  bool operator !=(const CLogLevel &_cAnotherLevel) const;
  bool operator >=(const CLogLevel &_cAnotherLevel) const;
  bool operator  >(const CLogLevel &_cAnotherLevel) const;

public:
  CLogLevel & operator =(const CLogLevel &_cAnotherLevel);

public:
  const char * GetName() const;
  int          GetValue() const;
};

#endif // __LOGLEVEL_H__