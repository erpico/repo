#pragma once

#include "Core.h"
#include "Core/json/json.h"

namespace SoundFileName
{
    const std::string const_strAnswer = "answer";
    const std::string const_strNew    = "neworder";
    const std::string const_strDenial = "denial";
    const std::string const_strError  = "error";
};

namespace PushType
{
    const int const_iDriverPush  = 1;
    const int const_iClientPush  = 2;
    const int const_iWebOperator = 3;

    const int const_iCount       = 3;
};

class CORE_API CPushNotificationSender
{
public:
    CPushNotificationSender();
    virtual~ CPushNotificationSender();

    void SetAppId(const std::string &_strOneSignalId);
    void SetOneSignalAuth(const std::string &_strOneSignalAuth);
    void SetFilter(const std::string &_strField, const std::string &_strKey, const std::string &_strRelation, const std::string &_strValue);
    void SetData(const std::string &_strField, const std::string &_strData);
    void SetData(const std::string &_strField, const DWORD &_dwData);
    void SetData(const std::string &_strField, const int &_iData);
    /* _iDeviceType = 0 - android */
    void SetSound(const std::string &_strData, const int &_iDeviceType = 0);
    void SetURL(const std::string &_strURL);
    void SetContent(const std::string &_strValue);
    int  SendPushNotification();    
    int  SendPost(const std::string &_strURL, std::string &_strResult, const std::string &_strContent, const TCHAR *_headers);

private:
    std::string strURL;
    std::string strAndroidSound;
    std::string strOneSignalAuth;

    Json::Value jNotification;    
    Json::Value jFilterList; 
    Json::Value jData;    
    Json::Value jContents;
};