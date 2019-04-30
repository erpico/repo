/************************************************************************
 *  created:    4.4.2008  21:17
 *  filename:   Synchronizer.h
 *  author:     Kapralov A.
 *
 *  purpose:    
 *  version:    1.0
 ************************************************************************/
#ifdef WIN32
#ifndef __SYNCHRONIZER_H__
#define __SYNCHRONIZER_H__

#include "Core.h"

#include <Windows.h>

class CORE_API CSynchronizer
{
private:
  CRITICAL_SECTION *m_pCriticalSection;

public:
  CSynchronizer(CRITICAL_SECTION *_pCriticalSection);
public:
  ~CSynchronizer();
};


#endif // __SYNCHRONIZER_H__
#endif