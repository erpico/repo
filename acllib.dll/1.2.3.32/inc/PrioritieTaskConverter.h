#pragma once
#include "AclLib.h"
#include "StdAfx.h"
#include "TaskPriority.h"
#include <list>
#include <vector>
//#include "list.h"
//using namespace std;

class ACLLIB_API PrioritieTaskConverter
{
private:
  static std::vector<TaskPriority> allTask;
protected:
  PrioritieTaskConverter(void);
  virtual ~PrioritieTaskConverter(void);
public:
  static TaskPriority ConvertTo(const char * str);
  static const char * ConvertFrom(TaskPriority prioritieTask);
  static const char * ConvertFromRussian(TaskPriority prioritieTask);
  static std::vector<TaskPriority> * getAllTask();
};

