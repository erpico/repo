#pragma once

#include <afxmt.h>
#include <afxtempl.h>
#include <map>

//#define CACHE_BLOCK 16

template<class T> class CCache
{
  class CCacheElement
  {
    friend CCache;  
    DWORD dwID;
    DWORD dwLastUpdated;
    DWORD tickLastAccess;
    bool  bShow;
    T m_obj;

    public:
      CCacheElement()
      {
        dwID = 0;
        dwLastUpdated = 0;
        tickLastAccess = 0;
        bShow = false;
      };
  };
  typedef struct tagCacheElement {
    //DWORD dwID;
    DWORD dwLastUpdated;
    DWORD tickLastAccess;
    bool  bShow;
    void* pObj;
  } CACHE_ELEMENT;
public:
  CCache(void);
  ~CCache(void);

public:
  //Functions
  bool Init();
  int Update(DWORD nID, DWORD dwUpdateTime, T pObj);
  int Delete(DWORD nID);
  bool Get(DWORD nID, T& pObj);
  DWORD GetLastUpdated(DWORD nID);
  int DeleteAll();
  void Reset();

protected:
  CCriticalSection m_Lock;
  //CArray<CCacheElement, CCacheElement> m_arrCache;
  std::map<DWORD, CCacheElement> m_mapCache;
  DWORD m_dwLastCleanup;
public:
  void CleanUpThis();
  int GetSize() { return (int) m_mapCache.size(); }//m_arrCache.GetSize(); }
};

template<class T>CCache<T>::CCache(void)
{
  m_dwLastCleanup = 0;
  //m_arrCache.SetSize(0, 32);
  //m_mapCache.InitHashTable(0, 0);
}

template<class T>CCache<T>::~CCache(void)
{
  CSingleLock locker(&m_Lock, TRUE);

  //m_arrCache.RemoveAll();
  m_mapCache.clear();

  AddToLog("Cache 0x%I32X destroyed.", this);
}

template<class T> bool CCache<T>::Init() {
  CSingleLock locker(&m_Lock, TRUE);

  //CCacheElement el;

  AddToLog("Cache created (0x%I32X).");// Element size: %lu", this, (DWORD) sizeof(el.m_obj));
  return 1;
}

template<class T>int CCache<T>::Delete(DWORD nID)
{
  CSingleLock locker(&m_Lock, TRUE);
  int nRet =  m_mapCache.erase(nID);
  return nRet;
  /*
  int nPos = -1;
  //Search for item in cache
  for (int cPos = 0; cPos < m_arrCache.GetSize(); cPos++) {
    if (m_arrCache[cPos].dwID == nID) {
      nPos = cPos;
      break;
    }
  }
  if (nPos != -1) {
    m_arrCache.RemoveAt(nPos);
  }  
  return 1;
  */
}

template<class T>bool CCache<T>::Get(DWORD nID, T & pObj) 
{
  CSingleLock locker(&m_Lock, TRUE);

  //CCacheElement el;

  std::map<DWORD, CCacheElement>::iterator it;
  it = m_mapCache.find(nID);

  if (it != m_mapCache.end())
  {
    pObj = it->second.m_obj;
    return 1;
  }

  return 0;

  /*int nPos = -1;
  for (int cPos = 0; cPos < m_arrCache.GetSize(); cPos++) {
    if (m_arrCache[cPos].dwID == nID) {
      nPos = cPos;
      break;
    }
  }
  try {
    if (nPos != -1) {
      m_arrCache[nPos].tickLastAccess  = ::GetTickCount();
      pObj = m_arrCache[nPos].m_obj;      
      return 1;
    } else AddToLog("Cache warning: object %lu not found.", nID);
  } catch (...) {
    ShowError();
  }
  return 0;*/
}

template<class T> int CCache<T>::Update(DWORD nID, DWORD dwUpdateTime, T pObj) 
{
  CSingleLock locker(&m_Lock, TRUE);
  CCacheElement el;
  //el.dwID = nID;    
  el.dwLastUpdated = dwUpdateTime;
  el.tickLastAccess  = ::GetTickCount();
  el.m_obj = pObj;
  
  std::map<DWORD, CCacheElement>::iterator it = m_mapCache.find(nID);
  if (it != m_mapCache.end())
  {
    it->second.m_obj = el.m_obj;
  }
  else
  {
    m_mapCache.insert(std::make_pair(nID, el));
  }

  it->second.bShow = true;
  
  return 1;
  /*
  int nPos = -1;
  //Search for item in cache
  for (int cPos = 0; cPos < m_arrCache.GetSize(); cPos++) {
    if (m_arrCache[cPos].dwID == nID) {
      nPos = cPos;
      break;
    }
  }
  try {          
    if (nPos == -1) {
      CCacheElement el;
      el.dwID = nID;    
      el.dwLastUpdated = dwUpdateTime;
      el.tickLastAccess  = ::GetTickCount();
      el.m_obj = pObj;
      m_arrCache.Add(el);
    } else {
      m_arrCache[nPos].m_obj = pObj;
      m_arrCache[nPos].dwLastUpdated = dwUpdateTime;
      m_arrCache[nPos].tickLastAccess = ::GetTickCount();
    }
  } catch (...) {
    ShowError();
  }
  return 1;*/
}

template<class T>DWORD CCache<T>::GetLastUpdated(DWORD nID) 
{
  CSingleLock locker(&m_Lock, TRUE);
  DWORD dwRet = 0;
  
  CCacheElement el;

  std::map<DWORD, CCacheElement>::iterator it;
  it = m_mapCache.find(nID);

  if (it != m_mapCache.end()) 
  {
    dwRet = it->second.dwLastUpdated;
  }

  return dwRet;

  /*int nPos = -1;
  //Search for item in cache
  for (int cPos = 0; cPos < m_arrCache.GetSize(); cPos++) {
    if (m_arrCache[cPos].dwID == nID) {
      nPos = cPos;
      break;
    }
  }
  if (nPos != -1) {
    m_arrCache[nPos].tickLastAccess  = ::GetTickCount();
    return m_arrCache[nPos].dwLastUpdated;
  } else ShowError();
  return 0;*/
}

template<class T> void CCache<T>::CleanUpThis() {
  //Disable cleanup. Use Delete.
  return;
#if 0
  if (m_dwLastCleanup == 0) {
    m_dwLastCleanup = GetTickCount();
    return;
  }    
  //Every 60 minutes
  if (GetTickCount() - m_dwLastCleanup > 3600000) {    
    CSingleLock locker(&m_Lock, TRUE);
    DWORD minTick = 0;    
    m_dwLastCleanup = GetTickCount();    
    AddToLog("Started cache 0x%I32X cleanup.", this);
    //Delete older than 3 hour
    minTick = ::GetTickCount() - 10800000;
    int cPos = 0;
    while (cPos < m_arrCache.GetSize()) {
      if (m_arrCache[cPos].tickLastAccess && (m_arrCache[cPos].tickLastAccess < minTick)) {
        //Move Up all bellow
        AddToLog("Delete old object %lu in cache 0x%I32X.", m_arrCache[cPos].dwID, this);
        m_arrCache.RemoveAt(cPos);        
      } else cPos++;
    }
    AddToLog("Finished cache 0x%I32X cleanup.", this);
  }
#endif
}

template<class T> int CCache<T>::DeleteAll()
{
  CSingleLock locker(&m_Lock, TRUE);
  //m_arrCache.RemoveAll();
  m_mapCache.clear();
  return 1;
}

template<class T> void CCache<T>::Reset()
{
  for (auto it = m_mapCache.begin(); it != m_mapCache.end(); it++)
  {
    it->second.bShow = false;
  }
}
