#pragma once

#include "Core.h"

CORE_API bool IsThreadRunning(HANDLE hThread);
CORE_API void CloseHandleAndNull(HANDLE& hnd);