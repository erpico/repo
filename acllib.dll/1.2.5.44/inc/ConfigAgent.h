/*
 * ConfigAgent.h
 * 
 *
 * Капралов А.
 * 26.7.2013 18:53
 */

#ifndef __CONFIGAGENT_H__
#define __CONFIGAGENT_H__

#include "AclLib.h"
#include "AclObjects.h"

#include <map>
#include <string>

class ConfigPriest;

class ACLLIB_API ConfigAgent {
private:
  const User *user;

private:
  ConfigPriest *priest;

public:
  ConfigAgent();
  virtual ~ConfigAgent();

public:
  int initialize(const char *serverUrl, const User *pUser);

public:
  int getUniversalConfig(UniversalConfig &result);

public:
  int updateUniversalConfig(const UniversalConfig &universalConfig);

  int getConfigByUserGroup(long groupId, std::map<CString, CString> &groupOptions);
  int updateConfigByUserGroup(const UpdateUserGroupMap &updateUserGroupMap);

};

#endif // __CONFIGAGENT_H__