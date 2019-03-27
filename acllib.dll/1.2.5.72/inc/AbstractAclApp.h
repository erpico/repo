/*
 * AbstractAclApp.h
 * 
 *
 * Капралов А.
 * 4.7.2013 16:22
 */
#ifndef __ABSTRACTACLAPP_H__
#define __ABSTRACTACLAPP_H__

#include "AclLib.h"
#include "ACL.h"
#include "AclManager.h"
#include "Config.h"
#include "ConfigAgent.h"

#include <list>

// AbstractAclApp

class ACLLIB_API AbstractAclApp : public CWinAppEx {
  DECLARE_DYNCREATE(AbstractAclApp)

protected:
  CString serverHost;
  ACLAgent aclAgent;
  Config config;
  ConfigAgent configAgent;

public:
  AclManager aclManager;
  static AbstractAclApp* GetInstance();

  AclManager* GetAdminAclManager() { return &aclAdminManager; }
  ACLAgent*   GetAdminAclAgent()   { return &aclAdminAgent; }

private:
  /* Менеджер и агент с правами админа для создания/редактирования/удаления из ErpicoCRM пользователей WebCRM подрядчика */
  AclManager aclAdminManager;
  ACLAgent   aclAdminAgent;

protected:
  AbstractAclApp();           // protected constructor used by dynamic creation
  virtual ~AbstractAclApp();

public:
  virtual int LogIn(const char *serverHost, const char *name, const char *password, bool saveCredentials, bool autoLogOn, const char* serverApp = "phc");
  virtual int LogOut(bool exitApp = false);
  bool isAllow(const char *ruleHandle);

public:
  virtual const char * GetServerUrl();
  virtual const char * GetServerHost();
  virtual const User * GetUser();
  virtual Config & GetConfig();
  
public:
  virtual int GetUsers(std::list<User> &result, const char *groupName = NULL);
  CString GetFullUserName(const char* name, CString* strDescription = 0);
  template<size_t destSize> inline void GetFullUserName(const char* name, char (&dest)[destSize]) {
    GetFullUserName(name, dest, destSize);
  }
  void GetFullUserName(const char* name, char* dest,  size_t destSize, char* description = 0, size_t descriptionSize = 0);

public:
  virtual void GetStringOption(const char *optionName, CString &val);
  virtual int GetIntOption(const char *optionName);
  virtual long GetLongOption(const char *optionName);
  virtual void GetLongOptions(const char *optionName, std::list<long> &result);
  virtual bool GetBoolOption(const char *optionName);

public:
  virtual BOOL InitInstance();
  virtual int ExitInstance();

public:
  virtual void ReadCredentials(std::list<CString> &serverHosts, CString &username, CString &password, 
    bool &saveCredentials);
  virtual void SaveBasicCredentials(const char *serverHost, const char *username);
  virtual void SaveCredentials(const char *password);
  virtual void NotSaveCredentials();

  virtual bool ReadAutoLogOn();
  virtual void SaveAutoLogOn(bool autoLogOn);
  
protected:
  DECLARE_MESSAGE_MAP()
};

#endif // __ABSTRACTACLAPP_H__