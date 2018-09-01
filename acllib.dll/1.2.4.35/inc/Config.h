/*
 * Config.h
 * 
 *
 * Капралов А.
 * 18.3.2013 16:29
 */

#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "AclLib.h"
#include "AclObjects.h"

#include <map>
#include <string>

class ConfigPriest;

class ACLLIB_API Config {
private:
  const User *pUser;
  std::map<CString, CString> optionMap;

private:
  ConfigPriest *pPriest;

public:
  Config();
  virtual ~Config();

public:
  int initialize(const char *serverUrl, const User *pUser);

public:
  int updateConfig(long updatedTime = 0);

public:
  const std::map<CString, CString> &getOptionMap() const;
  void getStringOption(const char *optionName, CString &val) const;
  int getIntOption(const char *optionName, int nDefaultValue = 0) const;
  long getLongOption(const char *optionName) const;
  void getLongOptions(const char *optionName, std::list<long> &result);
  bool getBoolOption(const char *optionName) const;
  void setLongOptions(const char *optionName, const std::list<long> &optionList);
  std::string Config::getAllowedCitiesAsStr();
  std::string Config::getCTIExt();

public:
  int saveOptions(std::map<CString, CString> optionMap);
  int saveOptions();

  const User* GetUser();

};

#endif // __CONFIG_H__