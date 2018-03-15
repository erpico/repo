#pragma once

#include "Core.h"
#include "Core/json/json.h"


class CORE_API CPushNotificationSender
{
public:
    CPushNotificationSender();
    virtual~ CPushNotificationSender();

    void SetFilter(const std::string &_strField, const std::string &_strKey, const std::string &_strRelation, const std::string &_strValue);
    void SetData(const std::string &_strField, const std::string &_strData);
    void SetData(const std::string &_strField, const DWORD &_dwData);
    void SetURL(const std::string &_strURL);
    void SetContent(const std::string &_strValue);
    int  SendPushNotification();    
    int  SendPost(const std::string &_strURL, std::string &_strResult, const std::string &_strContent, const TCHAR *_headers);

private:
    std::string strURL;
    Json::Value jNotification;    
    Json::Value jFilterList; 
    Json::Value jData;
    Json::Value jContents;
};