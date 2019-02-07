#pragma once

#include "Core.h"

CORE_API double Distance(double dLat1, double dLon1, double dLat2, double dLon2);
CORE_API void GetStat(long lTimePrev, long lTime, double dLatitudePrev, double dLongitudePrev, double dLatitude, double dLongitude, double &dKm, int &iSpd, double &lMoveTm, double &lStopTm);
CORE_API double deg2rad(double dDeg);

