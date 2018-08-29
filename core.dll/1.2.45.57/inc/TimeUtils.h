/*
 * TimeUtils.h
 * 
 * Kapralov A.
 * 29.04.2014 16:56
 */
#ifndef __TIMEUTILS_H__
#define __TIMEUTILS_H__


#include "Core.h"

#define SECONDS_IN_MINUTE 60
#define SECONDS_IN_HOUR 3600
#define MINUTES_IN_HOUR 60

<<<<<<< HEAD
CORE_API void TimeSpanToStringRus(std::string &result, time_t timeSpan);

=======
namespace TimeType
{
  static const int const_iTime = 0;
  static const int const_iTimeMin = 1;
  static const int const_iTimeMax = 2;
};

CORE_API void TimeSpanToStringRus(std::string &result, time_t timeSpan);

CORE_API void SystemtimeToStructTm(const SYSTEMTIME &_stSystemTime, struct tm &stTm, const int &_iTimeType = 0);

>>>>>>> 89c176ae9dc5e0f157e44d4fb8e5c5415b64b90e
#endif // __TIMEUTILS_H__