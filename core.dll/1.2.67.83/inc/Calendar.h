#pragma once

#include "Core.h"

#define SECS_IN_24HOURS 86400
#define SECS_IN_HOUR 3600
#define SECS_IN_MIN 60
#define DAYS_IN_WEEK 7

enum DayOfWeek {
  DOW_MONDAY = 0,
  DOW_TUESDAY = 1,
  DOW_WEDNESDAY = 2,
  DOW_THURSDAY = 3,
  DOW_FRIDAY = 4,
  DOW_SATURDAY = 5,
  DOW_SUNDAY = 6
};

CORE_API extern const char *DOW_STRING_RUS[DAYS_IN_WEEK];

CORE_API const char* dayOfWeekToStringRus(DayOfWeek dow);

CORE_API void intervalToHMString(std::string &result, int interval);