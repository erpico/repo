/*
 * Ext.h
 * 
 *
 * Капралов А.
 * 17.6.2013 18:02
 */
#ifndef __EXT_H__
#define __EXT_H__

#include "AclLib.h"
#include "AclObjects.h"

#include <list>
#include <vector>

class ACLLIB_API ExtWebApp {
public:
  long id;
  CString name;
  CString description;
  CString icon;
  CString address;
  int width;
  int height;

public:
  ExtWebApp() : 
      id(0), width(0), height(0) {
  }
  
  ExtWebApp(long id, LPCTSTR name, LPCTSTR description, LPCTSTR icon, LPCTSTR address, 
      int width, int height) : 
      id(id), name(name), description(description), icon(icon), address(address),
      width(width), height(width){
  }

};

class ExtPriest;

class ACLLIB_API ExtManager {
private:
  const User *pUser;

private:
  ExtPriest *pPriest;

public:
  ExtManager();
  virtual ~ExtManager();

public:
  int initialize(const char *serverUrl, const User *pUser);

public:
  int getWebApps(std::list<ExtWebApp> &result);
};

#endif // __EXT_H__