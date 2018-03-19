#pragma once

enum TaskState {
  TASK_UNKNOWN    = -1,
  TASK_APPOINTED  = 1,
  TASK_WORK       = 2,
  TASK_DONE       = 3,
  TASK_OBSOLETE   = 4,
  TASK_CANCELED   = 5
};