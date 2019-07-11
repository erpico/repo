/*
 * ExtPriest.h
 * 
 *
 * Капралов А.
 * 17.6.2013 18:16
 */
#ifndef __EXTPRIEST_H__
#define __EXTPRIEST_H__

#include "AclLib.h"
#include "Ext.h"
#include "AclObjects.h"
#include "ServerPriest.h"

#include <list>

class ACLLIB_API ExtWebAppResponse : public ServerResponse {
public:
  std::list<ExtWebApp *> webApps;

public:
  ExtWebAppResponse();
  virtual ~ExtWebAppResponse();

};

class ACLLIB_API ExtPriest : public ServerPriest {
public:
  ExtPriest();
  virtual ~ExtPriest();

private:
  int prepareWebAppRequest(CString &request, const User &user);

private:
  int callService(const CString &request, ServerResponse *pServerResponse);

protected:
  virtual int parseNode(CXMLNode &node, ServerResponse *pServerResponse);

private:
  int parseWebAppsNode(CXMLNode &webAppsNode, ExtWebAppResponse &response);
  int parseWebAppNode(CXMLNode &webAppNode, ExtWebAppResponse &response);

public:
  int getWebApps(std::list<ExtWebApp> &result, const User &user);
};

#endif // __EXTPRIEST_H__