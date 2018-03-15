#pragma once

#ifndef __MYSQL_H__
#define __MYSQL_H__

#include <winsock2.h>
#include "mysql\mysql.h"
#include "afxmt.h"
#include "afxtempl.h"

//#ifdef _DEBUG
#include <string>
using std::string;
#include <list>
using std::list;
//#endif // _DEBUG

#include "Core.h"
#ifndef WIN32
  #include <pthread.h>
#endif

#define MYSQL_STATUS_FAILED 0
#define MYSQL_STATUS_OK     1

class CORE_API CMySQL
{
public:
  typedef struct tagMysqlConfig {
    char user[64];
    char password[128];
    char host[64];
    char dbName[64];
    long port;
    char AppName[256];
    int datbaselimit;//for future 
    tagMysqlConfig() {
      memset(this, 0, sizeof(*this));
    }
    ~tagMysqlConfig() {
      memset(this, 0, sizeof(*this));
    }
  } MYSQL_CONFIG;

  CMySQL(void);
  ~CMySQL(void);
  bool connect(const MYSQL_CONFIG* config, BOOL bLock = 1);
  void disconnect(BOOL bLock = 1);

  bool query(const char* query);
  bool query(std::list<std::string>& arrQueries);
  __int64 insert(const char* query);

  //MFS-based results
  char * m_getOneResult;
  int m_getOneResultSize;
  const char* getOne(const char* query);

  //Mysql-based results
  inline MYSQL_RES* getResult(const char* query) {
    return getResultInternal(query);
  }

private:
  MYSQL_RES* getResultInternal(const char *query);

public:
  MYSQL_ROW fetchRow(MYSQL_RES* result);
  void freeResult(MYSQL_RES* result);
  unsigned long long numRows(MYSQL_RES* result);

  std::string m_strLastError;
  int     m_nStatus;
  int     m_bBusy;
  int     m_bAccured;
  DWORD m_cLastQuery;
  #ifdef WIN32
    CCriticalSection m_Lock;
  #else
    pthread_mutex_t m_Lock;
  #endif
  MYSQL link;  

  MYSQL_CONFIG m_config;
  DWORD m_dwThread;
  BOOL m_bIsRoot;  
  BOOL m_bUseCompressedProtocol;

  std::string m_strQuery;

  DWORD m_dwLastQueryStart;
  DWORD GetLastQueryStart() { return m_dwLastQueryStart; }

  void SetMySQLCompressedConnectionMode();

private:
  //bool sendToInfoServerStatus(bool status);
  bool native_query(const char* query);

#ifdef DEBUG_MYSQL
private:
  struct SQueryResult 
  {
    MYSQL_RES  * pRes;
    string       strQuery;
    const char * strFile;
    int          iLine;
  };


private:
  CRITICAL_SECTION csQueryResults;
  std::list<SQueryResult> lstQueryResults;

private:
  void AddQueryResult(MYSQL_RES * _pRes, const char * _query, 
      const char * _strFile, int _iLine);
  void RemoveQueryResult(MYSQL_RES * _pRes);
  void DumpUnfreedResults();

public:
  MYSQL_RES* getResultDbg(const char * _strQuery, const char * _strFile, int _iLine);
private:
  MYSQL_RES* getResultDbg(const char* query);
#endif // DEBUG_MYSQL
};

CORE_API int GetDatabaseConnectionCount();
CORE_API void DestroySeparatedDBConnectivitys();
CORE_API void CreateDBProcessDlg(CWnd* pParent);

class CORE_API CMySQLDatabaseConnectivity {
public:
  CMySQLDatabaseConnectivity();
  ~CMySQLDatabaseConnectivity();  

  CMySQL* operator->();
  operator CMySQL*() { return pDB; }  
protected:
  CMySQL* pDB;
};

#ifdef DEBUG_MYSQL
  #define getResult(x) getResultDbg(x, __FILE__, __LINE__)
#endif

#endif //__MYSQL_H__