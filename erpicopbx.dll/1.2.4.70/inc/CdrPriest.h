/*
 * CdrPriest.h
 * 
 *
 * Капралов А.
 * 21.3.2013 10:33
 */
#ifndef __CDRPRIEST_H__
#define __CDRPRIEST_H__

#include "ErpicoPBX.h"

#include "Cdr.h"

#include "AclLib/ServerPriest.h"

#include <list>
#include <vector>

class ERPICOPBX_API CdrResponse : public ServerResponse {
  friend class CdrPriest;

private:
  int count;
  long total;
  std::list<Call *> calls;

public:
  CdrResponse();
  virtual ~CdrResponse();

public:
  int getCount() const;
  long getTotal() const;
  const std::list<Call *> & getCalls() const;

protected:
  void setCount(int count);
  void setTotal(long total);
  void addCall(Call *pCall);

};

class ERPICOPBX_API CdrPriest : public ServerPriest {
public:
  CdrPriest();
  virtual ~CdrPriest();

private:
  int prepareCdrRequest(CString &request, const User & user, int firstResult, int maxResults, 
      time_t timeFrom, time_t timeTo, 
      const char *number, const char *secondNumber, 
      const char *source, const char *destination, 
      const char *contactName, const char *line, 
      CallDisposition disposition);
  
private:
  int callService(const CString &request, ServerResponse *pServerResponse);

protected:
  virtual int parseNode(CXMLNode &node, ServerResponse *pServerResponse);

private:
  int parseCdrNode(CXMLNode &cdrNode, CdrResponse &response);
  int parseCallNode(CXMLNode &callNode, CdrResponse &response);

public:
  int getCalls(std::vector<Call> & result, long &totalCount, 
      const User &user, int firstResult, int maxResults,
      time_t timeFrom, time_t timeTo, 
      const char *number, const char *secondNumber, 
      const char *source, const char *destination, 
      const char *contactName, const char *line, 
      CallDisposition disposition);
  
};

#endif // __CDRPRIEST_H__
