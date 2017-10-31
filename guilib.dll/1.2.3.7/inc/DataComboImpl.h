#pragma once

#include "DataComboList.h"
#include "DataComboEdit.h"
#include "DataComboUtils.h"
#include "DataComboBase.h"
#include <afxmt.h>
#include <afxtempl.h>
#include "Core\ThrSafeValue.h"

template<typename TData>
class CDataComboImpl : public CDataComboBase
{
protected:
  typedef CArray<TData*> TItemDataArray;

  TItemDataArray m_arrItemsData;
  CCriticalSection m_csArrItemsData;

public:
  CDataComboImpl()
  { }

  virtual ~CDataComboImpl()
  { }

  bool GetItemData(INT_PTR nItem, TData& itemData)
  {
    CSingleLock _cs(&m_csArrItemsData, TRUE);
    if(!CheckDataItemValid(nItem))
      return false;

    TData* pItemData = m_arrItemsData[nItem];
    itemData = *pItemData;
    return true;
  }

  virtual bool SetItemData(INT_PTR nItem, const TData& itemData)
  {
    CSingleLock _cs(&m_csArrItemsData, TRUE);
    if(!CheckDataItemValid(nItem))
      return false;

    TData* pItemData = m_arrItemsData[nItem];
    *pItemData = itemData;
    return true;
  }

  virtual bool SelectItemWithData(const TData& itemData)
  {    
    CSingleLock _csItemsData(&m_csArrItemsData, TRUE);
    CSingleLock _csItems(&m_csArrBaseItems, TRUE);

    for(INT_PTR i = 0; i < m_arrItemsData.GetCount(); i++) {
      TData* pItemData = m_arrItemsData[i];
      if(*pItemData == itemData) {
        SetCurSel(i);
        return true;
      }
    }

    return false;
  }

  virtual INT_PTR AddItem(const CString strLabel, const TData& itemData)
  {
    CSingleLock _cs(&m_csArrItemsData, TRUE);

    INT_PTR nItemId = CDataComboBase::AddItem(strLabel);

    TData* pItemData = new TData;
    ASSERT(pItemData != NULL);
    if(pItemData == NULL)
      return -1;

    *pItemData = itemData;
    INT_PTR nDataId = m_arrItemsData.Add(pItemData);
    ASSERT(nDataId == nItemId);
    return nItemId; 
  }

  virtual INT_PTR AddItem(const CString& strLabel)
  {
    CSingleLock _cs(&m_csArrItemsData, TRUE);

    INT_PTR nItemId = CDataComboBase::AddItem(strLabel);
      
    TData* pItemData = new TData;
    ASSERT(pItemData != NULL);
    if(pItemData == NULL)
      return -1;

    INT_PTR nDataId = m_arrItemsData.Add(pItemData);
    ASSERT(nDataId == nItemId);
    return nItemId;   
  }

  virtual void ResetItems()
  {
    CDataComboBase::ResetItems();

    CSingleLock _cs(&m_csArrItemsData, TRUE);
    for(INT_PTR i = 0; i < m_arrItemsData.GetCount(); i++)
      delete m_arrItemsData[i];

    m_arrItemsData.RemoveAll();
  }

protected:
  bool CheckDataItemValid(INT_PTR nItem)
  {
    if(nItem < 0 || nItem >= m_arrItemsData.GetCount())
      return false;

    return true;
  }

  INT_PTR GetDataItemsCount()
  {
    CSingleLock _cs(&m_csArrItemsData, TRUE);
    INT_PTR nRet = m_arrItemsData.GetCount();
    return nRet;
  }
};