#pragma once
#include "AclLib.h"
#include "ChatMessage.h"
#include "TaskPriority.h"
#include "TaskState.h"

class ACLLIB_API ChatTaskId :
  public ChatMessage
{
private:
  long dateEnd;
  TaskPriority prioritieTask;
  TaskState taskState;
public:
  ChatTaskId(void);
  virtual ~ChatTaskId(void);
public:
  long getDateEnd() const;
  void setDateEnd(long val);
  TaskPriority getPrioritieTask() const;
  void setPrioritieTask(TaskPriority val);
  TaskState getTaskState() const;
  void setTaskState(TaskState val);

};

