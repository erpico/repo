/*
 * AclManager.h
 * 
 *
 * Капралов А.
 * 22.8.2013 15:35
 */
#ifndef __ACLMANAGER_H__
#define __ACLMANAGER_H__

#include "AclLib.h"

#include "ACL.h"
#include "AclObjects.h"
#include "ConfigAgent.h"

#include "Core/Strings.h"

#include <list>
#include <vector>
#include <map>
#include <string>

enum DataEventType {CREATED, UPDATED, DELETED, ADDED,REMOVED};
enum AdminDataType {USER, USER_GROUP, RULE};

class Listener {
public:
  virtual void dataChanged(AdminDataType adminDataType, DataEventType dataEventType, long id)=0;
  virtual void relationChanged(AdminDataType childDataType, DataEventType dataEventType, long id, long childId)=0;
};


class ACLLIB_API ListenerManager {
private:
  std::list<Listener*> listeners_;
  std::map<AdminDataType,std::list<Listener*>> relationListeners_;  
  AdminDataType adminDataType_;  
public:
  ListenerManager(AdminDataType adminDataType);
  ~ListenerManager();

  void addListener(Listener* listener);  
  void removeListener(Listener* listener);

  bool addRelationListener(Listener* listener, AdminDataType childDataType);
  bool removeRelationListener(Listener* listener,  AdminDataType childDataType);

  void fireRelation(AdminDataType childDataType, DataEventType dataEventType, long id, long childId);
  void fireChanged(DataEventType dataEventType, long id);
};

class ACLLIB_API AclManager {
private:
  const User *user;

private:
  std::list<User> users;
  std::map<long, const User *> userMap;
  std::map<CString, const User *> userLoginMap;

private:
  UniversalConfig universalConfig;

private:
  ACLAgent *aclAgent;
  ConfigAgent configAgent;

public:
  AclManager();
  virtual ~AclManager();
  void CleanUp();

public:
  int initialize(ACLAgent *aclAgent);

public:
  int loadUsers();
  int loadConfig();
  int сreateUser(const char *userName, const char *userPassword, const char *userFullName, const char *description);
  int updateUserST(const char* login, long st_id, long st_group_id);

public:
  int getUser(long userId, User &result);
  int getUser(const char *name, User &result);

  int getUsers(std::list<User> &result);

  int getUserConfig(long userId, std::map<CString, CString> &result);

protected:
  std::list<UserGroup> userGroups;
  std::map<long, const UserGroup *> userGroupMap;
  std::map<long, std::list<User>> usersByUserGroup;      // Пользователи группы
  std::map<long, std::list<UserGroup>> userGroupsByUser; // Группы пользоателя
  std::map<long, std::set<long>> userGroupsRules;        // Права групп

  ListenerManager listenerManagerUserGroup;

private:
  virtual int loadUsersByUserGroup(std::list<User> &result, long groupId);

public:
  // Группы
  const std::list<UserGroup> &getUserGroups() const;
  const UserGroup * getUserGroup(long id);
  
  int loadUserGroups();
  std::list<User>& getUsersByGroup(long id);

  int loadRulesByUserGroup(long groupId, std::set<long> &rules); //  
  std::set<long>& getRulesByGroup(long id);

  int createUserGroup(long &id, const char * name, const char * description);
  int updateUserGroup(long id, const char * name, const char * description);
  int deleteUserGroup(long id);


  ListenerManager* getListenerManagerUserGroups();
};

#endif // __ACLMANAGER_H__

