/********************************************************************
  created:    8.12.2006   19:28
  filename:   Runnable.h
  author:	    Kapralov A.

  purpose:    
  version:    1.0
*********************************************************************/

#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__

#include "Core.h"

//
// <KAE>
class CORE_API IRunnable {
public:
  virtual void Run() = 0;
};

#endif // __RUNNABLE_H__