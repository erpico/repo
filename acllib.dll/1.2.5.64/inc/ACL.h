/*
 * ACL.h
 * 
 * Access Control Layer.
 *
 * Капралов А.
 * 8.3.2013 17:25
 */
#ifndef __ACL_H__
#define __ACL_H__

#include "AclLib.h"

#include "AclObjects.h"

#include <list>
#include <vector>
#include <map>
#include <string>

class ACLPriest;

/*
 * Класс ACLAgent.
 * Отвечает за авторизацию пользователя.
 *
 * Предоставляет методы: 
 * - Аутентификация 
 * - Получение информации о пользователе (ФИО) 
 * - Проверка прав доступа и наличия права на выполнения действия 
 * - Сохраняет реквизиты пользователя в реестре.
 */
class ACLLIB_API ACLAgent {
private:
  User user;
  std::map<std::string, bool> ruleMap;

private:
  ACLPriest *priest;

public:
  ACLAgent();
  virtual ~ACLAgent();

public:
  int initialize(const char *serverUrl, const char *name, const char *password);

public:
  const char * getServerUrl();
  const User & getUser();

public:
  int logIn(long &currentTime);

  int logOut();
  
private:
  int getUserRules(long time);

public:
  bool isAllow(const char *ruleHandle);

  int getUsers(long firstResult, int maxResults, std::list<User> &result, long &totalCount, const char *groupName = NULL);

  int getRules(std::list<Rule> &result);

  int getUserACLs(std::list<UserACL> &result);

  int updateUserACLs(const std::vector<UserACL> &usersACL);
  
  int createUser(long &id, const char *name, const char *password, const char *fullname,
      const char *description);
  int updateUser(long id, const char *name, const char *password, const char *fullname,
      const char *description, UserState state);
  int updateUserST(long id, long st_id, long st_group_id);
  int deleteUser(long id);

public:
  void startUpdatingRules();
  
  void stopUpdatingRules();

public:
  int getUserGroups(std::list<UserGroup> &result, long &totalCount,
    int firstResult, int maxResults);
  int getUserGroup(UserGroup &result, long id);
  int createUserGroup(long &id, const char * name, const char * description);
  int updateUserGroup(long id, const char * name, const char * description);
  int deleteUserGroup(long id);

  int getUsersByUserGroup(long firstResult, int maxResults, std::list<User> &result, long &totalCount, long groupId);
  int getUserGroupsByUser(std::list<UserGroup> &result, long userId);
  int updateUsersByUserGroup(const UpdateUserGroupMap &updateUserGroupMap);
  int getRulesByUserGroup(long groupId, std::set<long> &result);
  int updateRulesByUserGroup(const UpdateUserGroupMap &updateUserGroupMap);  
};

#endif // __ACL_H__