#pragma once

#include <vector>

template<typename TData>
class CComboCacheBase
{
public:
    CComboCacheBase() {}
    virtual ~CComboCacheBase() {}

    virtual void SetDataToCache(const std::vector<TData> &_vectData) {}
};
