#pragma once

#include "DataComboImpl.h"
#include <set>
#include "Core\Common.h"

template<typename TCache, typename TData>
class CDataComboCacheImpl : public CDataComboImpl<TData>
{
protected:
  TCache* m_cache;

  typedef std::set<INT_PTR> TItemIdSet;

  TItemIdSet m_changedItemsSet;
  CCriticalSection m_csChangedItems;

  TItemIdSet m_changedItemsDataSet;
  CCriticalSection m_csChangedItemsData;

public:
  CDataComboCacheImpl()
  { 
    AddToLog("CDataComboCacheImpl() creating cache");
    m_cache = TCache::Create();
  }

  virtual ~CDataComboCacheImpl()
  { 
    AddToLog("~CDataComboCacheImpl() destroying cache");
    TCache::Destroy(m_cache);
  }

  void ResetToCache()
  {
    AddToLog("CDataComboCacheImpl::ResetToCache() begin");
    LockWithStatus("Загрузка данных из кэша...");

    //Sleep(500); // это сделано, чтобы загрузка кэша в диалоге заказа происходила после отрисовки самого диалога, а то открытие тормозило.

    {
      CSingleLock _csChangedItems(&m_csChangedItems, TRUE);
      CSingleLock _csChangedItemsData(&m_csChangedItemsData, TRUE);
      CSingleLock _csItemsData(&m_csArrItemsData, TRUE);
      CSingleLock _csItems(&m_csArrBaseItems, TRUE);
      CSingleLock _csDispCache(&m_csTrueContent, TRUE);

      ResetItems();

      ASSERT(m_cache != NULL);
      AddToLog("CDataComboCacheImpl::ResetToCache() filling items");
      m_cache->FillItems(m_arrBaseItems, m_arrItemsData, m_arrTrueContent);
      m_nCurSel.set(-1);
    }    
    
    Unlock();
    AddToLog("CDataComboCacheImpl::ResetToCache() end");
  }

  virtual void ResetItems() // удаляет только те итемы, которые не входят в кэш
  {
    CSingleLock _csChangedItems(&m_csChangedItems, TRUE);
    CSingleLock _csChangedItemsData(&m_csChangedItemsData, TRUE);
    CSingleLock _csItemsData(&m_csArrItemsData, TRUE);
    CSingleLock _csItems(&m_csArrBaseItems, TRUE);
    
    {// удаляем добавленные\измененные итемы
      TItemIdSet::iterator it = m_changedItemsSet.begin();
      while (it != m_changedItemsSet.end())
      {
        INT_PTR nItemId = *it;
        if(CheckItemValid(nItemId)) {
          delete m_arrBaseItems[nItemId];
          m_arrBaseItems[nItemId] = NULL;
        }
        ++it;
      }

      m_arrBaseItems.RemoveAll();
      m_changedItemsSet.clear();
    }
    
    {// удаляем добавленные\измененные даты у итемов
      TItemIdSet::iterator it = m_changedItemsDataSet.begin();
      while (it != m_changedItemsDataSet.end())
      {
        INT_PTR nItemDataId = *it;
        if(CheckDataItemValid(nItemDataId)) {
          delete m_arrItemsData[nItemDataId];
          m_arrItemsData[nItemDataId] = NULL;
        }
        ++it;
      }

      m_arrItemsData.RemoveAll();
      m_changedItemsDataSet.clear();
    }
  }

  virtual bool SetItemLabel(INT_PTR nItem, const CString& label)
  {
    CSingleLock _csChangedItems(&m_csChangedItems, TRUE);
    CSingleLock _csItems(&m_csArrBaseItems, TRUE);

    if(!CheckItemValid(nItem))
      return false;

    if(IsItemFromCache(nItem)) {
      CDataComboBase::Item* pItem = CDataComboBase::CreateItem(label);
      
      ASSERT(pItem != NULL);
      if(pItem == NULL)
        return false;

      m_arrBaseItems.SetAt(nItem, pItem);
      m_changedItemsSet.insert(nItem);
      return true;
    }

    return CDataComboImpl<TData>::SetItemLabel(nItem, label);
  }

  virtual bool SetItemData(INT_PTR nItem, const TData& itemData)
  {
    CSingleLock _csChangedItemsData(&m_csChangedItemsData, TRUE);
    CSingleLock _csItemsData(&m_csArrItemsData, TRUE);

    if(!CheckDataItemValid(nItem))
      return false;

    if(IsItemDataFromCache(nItem)) {
      TData* pItemData = new TData;
      
      ASSERT(pItemData != NULL);
      if(pItemData == NULL)
        return false;

      m_arrItemsData.SetAt(nItem, pItemData);
      m_changedItemsDataSet.insert(nItem);
      return true;
    }

    return CDataComboImpl<TData>::SetItemData(nItem, itemData);
  }

  virtual INT_PTR AddItem(const CString strLabel, const TData& itemData)
  {
    CSingleLock _csChangedItems(&m_csChangedItems, TRUE);
    CSingleLock _csChangedItemsData(&m_csChangedItemsData, TRUE);
    CSingleLock _csItemsData(&m_csArrItemsData, TRUE);
    CSingleLock _csItems(&m_csArrBaseItems, TRUE);

    INT_PTR nNewItem = CDataComboImpl<TData>::AddItem(strLabel, itemData);
    m_changedItemsSet.insert(nNewItem);
    m_changedItemsDataSet.insert(nNewItem);
    
    return nNewItem;
  }

  virtual INT_PTR AddItem(const CString& strLabel)
  {
    CSingleLock _csChangedItems(&m_csChangedItems, TRUE);
    CSingleLock _csChangedItemsData(&m_csChangedItemsData, TRUE);
    CSingleLock _csItemsData(&m_csArrItemsData, TRUE);
    CSingleLock _csItems(&m_csArrBaseItems, TRUE);

    INT_PTR nNewItem = CDataComboImpl<TData>::AddItem(strLabel);
    m_changedItemsSet.insert(nNewItem);
    m_changedItemsDataSet.insert(nNewItem);

    return nNewItem;
  }

protected:
  bool IsItemFromCache(INT_PTR nItem)
  {
    CSingleLock _csChangedItems(&m_csChangedItems, TRUE);
    if(m_changedItemsSet.find(nItem) == m_changedItemsSet.end())
      return true;

    return false;
  }

  bool IsItemDataFromCache(INT_PTR nItem)
  {
    CSingleLock _csChangedItemsData(&m_csChangedItemsData, TRUE);
    if(m_changedItemsDataSet.find(nItem) == m_changedItemsDataSet.end())
      return true;

    return false;
  }
};