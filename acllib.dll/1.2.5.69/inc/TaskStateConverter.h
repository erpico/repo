#pragma once

#include "AclLib.h"
#include "TaskState.h"
class ACLLIB_API TaskStateConverter
{
public:
  TaskStateConverter(void);
  virtual ~TaskStateConverter(void);
public:
  static CString ConvertFrom(TaskState taskState);
  static TaskState ConvertTo(CString str);
  static CString ConvertFromRussian( TaskState taskState );
  static TaskState ConvertRussianTo( char * str );
  static TaskState getNextTaskState(TaskState last);
};

