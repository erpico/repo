#pragma once

#include "GuiLib/DataComboCacheImpl.h"
#include <vector>

//#define WM_SERVICES_LOADED WM_USER + 35


typedef struct ContactsGroups
{
  int iId;
  std::string strName;
  std::string strQueue;
  std::vector<std::string> vectNumbers;
  std::vector<int> vectUsers;

  ContactsGroups()
  {
      iId = 0;
  }

  ContactsGroups& operator = (const ContactsGroups &_stGroup)
  {
      iId         = _stGroup.iId;
      strName     = _stGroup.strName;
      strQueue    = _stGroup.strQueue;
      vectNumbers = _stGroup.vectNumbers;
      vectUsers   = _stGroup.vectUsers;

      return *this;
  }

  bool operator == (const ContactsGroups &_stGroup)
  {
      bool bRet = false;

      if (strName.compare(_stGroup.strName) == 0)
          if (strQueue.compare(_stGroup.strQueue) == 0)
              if (vectNumbers == _stGroup.vectNumbers)
                if (vectUsers == _stGroup.vectUsers)
                  bRet = true;

      return bRet;
  }
} ContactsGroups;

class CContactsGroupDataComboCache;

class GUILIB_API CContactsGroupDataCombo : public CDataComboCacheImpl<CContactsGroupDataComboCache, ContactsGroups>
{
  DECLARE_DYNAMIC(CContactsGroupDataCombo)
  friend class CContactsGroupDataComboCache;

public:
  CContactsGroupDataCombo() {};
  virtual ~CContactsGroupDataCombo() {};

  ContactsGroups GetGroup(const int &_iSel) const;
  int GetGroupId(const int &_iSel) const;
  std::string GetGroupName(const int &_iSel) const;
  bool CContactsGroupDataCombo::SelectGroupById(const int &_iId);

  void SetData(const std::vector<ContactsGroups> &_vectGroups) { CDataComboCacheImpl::SetData(_vectGroups); }

protected:
  DECLARE_MESSAGE_MAP()

private:
  bool GetItemData(INT_PTR nItem, ContactsGroups &_stGroup) const;
};

//////////////////////////////////////////////////////////////////////////
// Кэш для дата-комбо подрядчиков
//////////////////////////////////////////////////////////////////////////


class GUILIB_API CContactsGroupDataComboCache : public CComboCacheBase<ContactsGroups>
{
public:
  typedef CArray<CContactsGroupDataCombo::Item*> TItemsArray;
  typedef CArray<ContactsGroups*> TItemsDataArray;

private:
  class sCache 
  {
  private:
    LONG  m_nUseCount;
    DWORD m_dwVersion;    
  
  public:
    TItemsArray m_items;
    TItemsDataArray m_data;
    TrueContentArray m_trueContent;

  public:
    sCache();
    ~sCache();

    int  GetUseCount() const { return m_nUseCount; }
    void Advise();
    void Release();

    DWORD GetVersion() const { return m_dwVersion; }
    void SetVersion(DWORD version) { m_dwVersion = version; }

    const TItemsArray& GetItems() const { return m_items; }
    const TItemsDataArray& GetItemsData() const { return m_data; }

    void SetItems(const TItemsArray& items) { m_items.Copy(items); }
    void SetItemsData(const TItemsDataArray& data) { m_data.Copy(data); }
  };

  typedef std::vector<sCache*> TCachesVector;
  static TCachesVector m_caches;
  std::vector<ContactsGroups> m_vectGroups;

private:
  sCache* m_pCache; // содержит указатель на текущий используемый кэш.
  static CCriticalSection m_csCaches;
  void SelectLatestCache();
  static sCache* GetLatestCache(); 

public:
  CContactsGroupDataComboCache();
  virtual ~CContactsGroupDataComboCache();

  // интерфейс для шаблона CDataComboCacheImpl
  static CContactsGroupDataComboCache* Create() { return new CContactsGroupDataComboCache; }
  static void Destroy(CContactsGroupDataComboCache* pInstance) { delete pInstance; }  
  void FillItems(TItemsArray& arrItems, TItemsDataArray& arrItemsData, TrueContentArray& arrTrueContent);
  void SetDataToCache(const std::vector<ContactsGroups> &_vectGroups) { m_vectGroups = _vectGroups; }

  // Интерфейс к самому кэшу
  static void RefreshCaches(const std::vector<ContactsGroups> &_vectGroups);
  static void Initialize();
  static void Clear();
  static void RemoveUnusedCaches();
};

