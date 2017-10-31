#pragma once

#include "resource.h"

LONG saveHKLMGuid(const TCHAR *registryPath, const TCHAR *option, const GUID &value);
GUID stringToGUID(const char* guidString);