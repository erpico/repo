/*
 * ServerPriest.h
 * 
 *
 * Капралов А.
 * 19.3.2013 12:35
 */
#ifndef __SERVERPRIEST_H__
#define __SERVERPRIEST_H__

#include "AclLib.h"

#include "Core/XMLNode.h"

#include <vector>

#define XML_DECLARATION "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
#define XML_REQUEST_DEFAULT_BUFFER_SIZE 1024

enum ServerResultCode {
  SRV_R_UNKNOWN = 0,
  SRV_R_OK = 1,
  SRV_R_ERROR = 2
};

struct ServiceError {
  long code;
  CString description;
  CString message;

  ServiceError() : code(0) {}
};

class ACLLIB_API ServerResponse {
private:
  long uid;
  int resultCode;

public:
  ServiceError serviceError;

public:
  ServerResponse();
  virtual ~ServerResponse();

public:
  long getUid() const;
  void setUid(long uid);

  int getResultCode() const;
  void setResultCode(int resultCode);
};

class ACLLIB_API ServerPriest {
private:
  CString serverUrl;
  bool secure;

private:
  long requestUid;
  CRITICAL_SECTION requestUidCS;

public:
  ServerPriest();
  virtual ~ServerPriest();

public:
  const char * getServerUrl() const;
  void setServerUrl(const char *serverUrl);

protected:
  long getNextRequestUid();
  const char * getProtocolVersion();


public:
  int callService(const char *path, const CString &request, CString &response);
  int getContent(const char *path, std::vector<BYTE> &content, CString &contentType);
  int readContentToFile(const char *path, HANDLE hFile, CString &contentType);
 
protected:
  int parseResponse(const CString &response, ServerResponse *pServerResponse);

private:
  int parseResponseNode(CXMLNode &responseNode, ServerResponse *pServerResponse);

protected:
  virtual int parseNode(CXMLNode &node, ServerResponse *pServerResponse) = 0;
  virtual int parseOther(CXMLNode &node, ServerResponse *pServerResponse);
  int parseErrorNode( CXMLNode & node, ServerResponse * pServerResponse );
};

#endif // __SERVERPRIEST_H__

