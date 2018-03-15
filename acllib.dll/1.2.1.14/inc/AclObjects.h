/*
 * AclObjects.h
 * 
 *
 * Капралов А.
 * 12.3.2013 20:16
 */
#ifndef __ACLOBJECTS_H__
#define __ACLOBJECTS_H__

#include "AclLib.h"

#include <list>
#include <set>
#include <map>

enum UserState {
  USER_STATE_UNKNOWN = 0,
  USER_STATE_ACTIVE  = 1,
  USER_STATE_BLOCKED = 2,
  USER_STATE_DELETED = 3, 
  USER_STATE_HIDDEN = 4
};

#define USER_STATE_NAME_ACTIVE  "ACTIVE"
#define USER_STATE_NAME_BLOCKED "BLOCKED"
#define USER_STATE_NAME_DELETED "DELETED"
#define USER_STATE_NAME_HIDDEN "HIDDEN"

ACLLIB_API UserState stringToUserState(const char *str);
ACLLIB_API const char * userStateToString(UserState state);

class ACLLIB_API User {

private:
  long id;
  CString name;
  CString password;
  CString fullname;
  CString authToken;
  CString description;
  UserState state;
  time_t created;
  time_t updated;
  time_t lastLogin;

public:
  User();
  virtual ~User();

public:
  long getId() const;
  void setId(long id);

  const char * getName() const;
  void setName(const char *name);

  const char * getPassword() const;
  void setPassword(const char *password);

  const char * getFullname() const;
  void setFullname(const char *fullname);

  const char * getAuthToken() const;
  void setAuthToken(const char *authToken);

  const char * getDescription() const;
  void setDescription(const char *description);

  UserState getState() const;
  void setState(UserState state);

  time_t getCreated() const;
  void setCreated(time_t created);

  time_t getUpdated() const;
  void setUpdated(time_t updated);

  time_t getLastLogin() const;
  void setLastLogin(time_t lastLogin);

};

class ACLLIB_API Rule {

private:
  long id;
  CString name;
  CString description;
  CString handle;

public:
  Rule();
  virtual ~Rule();

public:
  long getId() const;
  void setId(long id);

  const char * getName() const;
  void setName(const char *name);

  const char * getDescription() const;
  void setDescription(const char *description);

  const char * getHandle() const;
  void setHandle(const char *handle);

};

class ACLLIB_API UserRule : public Rule {

private:
  bool allow;

public:
  UserRule();
  virtual ~UserRule();

public:
  bool isAllow() const;
  void setAllow(bool allow);

};

struct ACLLIB_API UserACL {
  User user;
  std::set<CString> allowedRules;
};

struct ACLLIB_API UniversalConfig {
  std::map<CString, CString> serverOptions;
  std::map<CString, CString> globalOptions;
  std::map<long, std::map<CString, CString>> groupOptions;
  std::map<long, std::map<CString, CString>> userOptions;
};



class ACLLIB_API UserGroup {
private:
  long id;
  std::string name;
  std::string description;

public:
  UserGroup();
  virtual ~UserGroup();

public:
  long getId() const;
  void setId(long id);

  const char * getName() const;
  void setName(const char * name);

  const char * getDescription() const;
  void setDescription(const char * description);

};

class ACLLIB_API UpdateUserGroupMap
{
private:
  std::map<long, std::map<CString, std::pair<CString,bool>>> settings_;	
  std::map<long, std::set<long>> relationsAdded_;
  std::map<long, std::set<long>> relationsDeleted_;
  std::map<long, std::set<long>> rules_;
public:
  void setConfigOption(long userGroupId, CString setting_handle, CString value);
  void unSetConfigOption(long userGroupId, CString setting_handle);
  void addRelation(long userId, long groupId);
  void deleteRelation(long userId, long groupId);
  void allowRule(long ruleId, long groupId);

  std::map<long, std::map<CString, std::pair<CString,bool>>>& getSettings();  
  std::map<long, std::set<long>>& getRelationsAdd();
  std::map<long, std::set<long>>& getRelationsDelete();
  std::map<long, std::set<long>>& getRules();
  bool hasRelationsData() const; 
};

#endif // __ACLOBJECTS_H__
