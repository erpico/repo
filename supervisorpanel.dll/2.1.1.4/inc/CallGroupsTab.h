#pragma once

#include "SupervisorPanel.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "TreeUpdater.h"

#include "ErpicoCTI/ACDClient.h"
#include "Core/Returns.h"
#include "GuiLib/ResizableLayout.h"
#include "ErpicoPBX/Cti.h"

//////////////////////////////////////////////////////////////////////////
///
///

class CCallersBranchUpdater
  : public TreeCtrlItemBranchUpdater<std::string, SWCTIQueueInfoCaller, CNullBranchUpdater>
{
  struct ItemData
  {
    SWCTIQueueInfoCaller aEntry;
    DWORD dwAdded;
    int nWaitOrig;
  };

  std::map<std::string, ItemData> m_mapCallersData;


public:
  virtual std::string GetUniqueId(const SWCTIQueueInfoCaller& aEntry)
  {
    return aEntry.szUniqueId;
  }

  virtual CString FormatItemText(const SWCTIQueueInfoCaller& aEntry)
  {
    CString strRes;
    strRes.Format("%s , позиция %d, ожидание %d сек", aEntry.szCallerIDNum.c_str(), aEntry.nPosition, aEntry.nWait);
    return strRes;
  }

  virtual bool FormatItemTextForUpdate(const std::string& aId, CString& outStr)
  {
    std::map<std::string, ItemData>::iterator it = m_mapCallersData.find(aId);
    if(it == m_mapCallersData.end())
      return false;

    ItemData& data = it->second;

    outStr.Format("%s , позиция %d, ожидание %d сек", data.aEntry.szCallerIDNum.c_str(), data.aEntry.nPosition, data.nWaitOrig + (GetTickCount() - data.dwAdded)/1000);
    return true;
  }

  virtual void OnItemCreated(HTREEITEM /*hEntryItem*/, const SWCTIQueueInfoCaller& aEntry)
  {
    ItemData data;
    data.aEntry = aEntry;
    data.dwAdded = ::GetTickCount();
    data.nWaitOrig = aEntry.nWait;

    m_pTree->Expand(m_rootItem, TVE_EXPAND);

    m_mapCallersData.insert( std::make_pair( GetUniqueId(aEntry), data ) );
  }

  virtual void OnTreeItemSynced(const SWCTIQueueInfoCaller& aEntry)
  {
    std::map<std::string, ItemData>::iterator it = m_mapCallersData.find(GetUniqueId(aEntry));
    if(it != m_mapCallersData.end())
      (it->second).aEntry = aEntry;
  }

  virtual void OnItemDeleted(const std::string& id)
  {
    std::map<std::string, ItemData>::iterator it = m_mapCallersData.find(id);
    if(it != m_mapCallersData.end())
      m_mapCallersData.erase(it);
  }
};
// CCallGroupsTab dialog
//////////////////////////////////////////////////////////////////////////
///
///

class CQueuesBranchUpdater
  : public TreeCtrlItemBranchUpdater<std::string, SWCTIQueueInfo, CCallersBranchUpdater>
{
  typedef TreeCtrlItemBranchUpdater<std::string, SWCTIQueueInfo, CCallersBranchUpdater> Base;

public:
  virtual std::string GetUniqueId(const SWCTIQueueInfo& aEntry)
  {
    return aEntry.szName;
  }

  virtual bool ItemsHasChildren() const { return true; }

  virtual bool isItemHidden(const SWCTIQueueInfo& aEntry) const {
    if (aEntry.szName.compare("system") == 0) return true;
    if (!GetSupervisorPanelAdapter()->isQueueVisible(aEntry.szName.c_str())) return true;
    if(showHidden_) {
      return false;
    } else {
      Queue queue;
      int ret = GetSupervisorPanelAdapter()->GetCtiManager()->getQueue(queue, aEntry.szName.c_str());
      if (ret == R_OK)
        return queue.hidden;
    }
    return false;
  }

  virtual void SyncChildTree(CCallersBranchUpdater& childUpdater, const SWCTIQueueInfo& aEntry)
  {
    childUpdater.Sync(aEntry.arrCallers);
  }

  virtual HTREEITEM SyncTreeItemEntry( HTREEITEM hItem, const SWCTIQueueInfo& aEntry )
  {
    Base::SyncTreeItemEntry(hItem, aEntry);
    m_pTree->SetItem(hItem, TVIF_STATE, NULL, 0, 0, /*TVIS_BOLD, TVIS_BOLD,*/0,0, 0);
    
    SWCTIQueueInfo* pData = (SWCTIQueueInfo*)m_pTree->GetItemData(hItem);
    if(pData == NULL)
      pData = new SWCTIQueueInfo;

    *pData = aEntry;
    m_pTree->SetItemData(hItem, (DWORD_PTR)pData);

    return hItem;
  }

  virtual CString FormatItemText(const SWCTIQueueInfo& aEntry);
};


//////////////////////////////////////////////////////////////////////////
///
///

class CMembersBranchUpdater
  : public TreeCtrlItemBranchUpdater<std::string, SWCTIQueueInfoMember, CNullBranchUpdater>
{
  struct ItemData
  {
    SWCTIQueueInfoMember aEntry;
    DWORD dwAdded;
  };

  std::map<std::string, ItemData> m_mapCallersData;


public:
  virtual std::string GetUniqueId(const SWCTIQueueInfoMember& aEntry)
  {
    return aEntry.szName;
  }

  virtual HTREEITEM SyncTreeItemEntry( HTREEITEM hItem, const SWCTIQueueInfoMember& aEntry )
  {
    Base::SyncTreeItemEntry(hItem, aEntry);
    
    int iconId = aEntry.nPaused == 0 ? 1 : 0;
    m_pTree->SetItemImage(hItem, iconId, iconId);

    return hItem;
  }

  virtual CString FormatItemText(const SWCTIQueueInfoMember& aEntry)
  {
    const char *name = aEntry.szName.c_str();
    User user;
    if (R_OK == GetSupervisorPanelAdapter()->GetAclManager()->getUser(name, user)) {
      name = user.getFullname();
    }
    CString strRes;
    strRes.Format("%s (%d)", name, aEntry.nPenalty);
    if (aEntry.nPaused) {
      if (strcmp(aEntry.szPauseReason.c_str(), "afterwork") == 0) {
        strRes.Append(" (Постобработка)");
      } else {
        strRes.Append(" (Не готов)");
      }
    } else {
      strRes.Append(" (Готов)");
    }

    strRes.AppendFormat(" Принял: %d", aEntry.nCallsTaken);

    if (aEntry.nLastCall) {
      CTime tm((time_t)aEntry.nLastCall);
      strRes.AppendFormat(", Последний: %s", tm.Format("%d.%m %H:%M:%S"));
    }

    return strRes;
  }

  //virtual bool FormatItemTextForUpdate(const std::string& aId, CString& outStr)
  //{
  //	std::map<std::string, ItemData>::iterator it = m_mapCallersData.find(aId);
  //	if(it == m_mapCallersData.end())
  //		return false;

  //	ItemData& data = it->second;

  //	outStr.Format("%s , позиция %d, ожидание %d сек", data.aEntry.szUniqueId.c_str(), data.aEntry.nPosition, data.aEntry.nWait + (GetTickCount() - data.dwAdded)/1000);
  //	return true;
  //}

  //virtual void OnItemCreated(HTREEITEM /*hEntryItem*/, const SWCTIQueueInfoMember& aEntry)
  //{
  //	ItemData data;
  //	data.aEntry = aEntry;
  //	data.dwAdded = ::GetTickCount();

  //	m_mapCallersData.insert( std::make_pair( GetUniqueId(aEntry), data ) );
  //}

  //virtual void OnTreeItemSynced(const SWCTIQueueInfoMember& aEntry)
  //{
  //	std::map<std::string, ItemData>::iterator it = m_mapCallersData.find(GetUniqueId(aEntry));
  //	if(it != m_mapCallersData.end())
  //		(it->second).aEntry = aEntry;
  //}

  //virtual void OnItemDeleted(const std::string& id)
  //{
  //	std::map<std::string, ItemData>::iterator it = m_mapCallersData.find(id);
  //	if(it != m_mapCallersData.end())
  //		m_mapCallersData.erase(it);
  //}
};

//////////////////////////////////////////////////////////////////////////
///
///

class CCallGroupsQueuesBranchUpdater
  : public TreeCtrlItemBranchUpdater<std::string, SWCTIQueueInfo, CMembersBranchUpdater>
{
  //typedef TreeCtrlItemBranchUpdater<std::string, SWCTIQueueInfo, CMembersBranchUpdater> Base;
public:
  CCallGroupsQueuesBranchUpdater()
  {    
  }
  virtual std::string GetUniqueId(const SWCTIQueueInfo& aEntry)
  {
    return aEntry.szName;
  }

  virtual bool ItemsHasChildren() const { return true; }
  virtual bool isItemHidden(const SWCTIQueueInfo& aEntry) const {
    if (aEntry.szName.compare("system") == 0) return true;
    if (!GetSupervisorPanelAdapter()->isQueueVisible(aEntry.szName.c_str())) return true;
    if(showHidden_) {
      return false;
    } else {
      Queue queue;
      int ret = GetSupervisorPanelAdapter()->GetCtiManager()->getQueue(queue, aEntry.szName.c_str());
      if (ret == R_OK)
        return queue.hidden;
    }
    return false;
  }
  virtual void SyncChildTree(CMembersBranchUpdater& childUpdater, const SWCTIQueueInfo& aEntry)
  {
    childUpdater.Sync(aEntry.arrMembers);
  }

  virtual HTREEITEM SyncTreeItemEntry( HTREEITEM hItem, const SWCTIQueueInfo& aEntry )
  {
    Base::SyncTreeItemEntry(hItem, aEntry);
    m_pTree->SetItem(hItem, TVIF_STATE, NULL, 0, 0, /*TVIS_BOLD, TVIS_BOLD,*/0, 0, 0);
    m_pTree->SetItemImage(hItem, 2, 2);

    SWCTIQueueInfo* pData = (SWCTIQueueInfo*)m_pTree->GetItemData(hItem);
    if(pData == NULL)
      pData = new SWCTIQueueInfo;

    *pData = aEntry;
    m_pTree->SetItemData(hItem, (DWORD_PTR)pData);
    return hItem;
  }

  virtual CString FormatItemText(const SWCTIQueueInfo& aEntry)
  {
    const char *name = aEntry.szName.c_str();
    Queue queue;
    if (R_OK == GetSupervisorPanelAdapter()->GetCtiManager()->getQueue(queue, name)) {
      name = queue.fullname;
    }

    CString res;
    res.Format("%s, Принято звонков: %d, Время ожидания: %d", 
        name, aEntry.nCompleted, aEntry.nHoldTime);
    return res;
  }
};

///////////////////////////////////////////////////////////////////////////
//
//
template<typename TUniqueId, typename TEntry, typename TChildUpdater>
class CQueueTreeCtrl : public CTreeCtrl
{
private:
  TreeCtrlItemBranchUpdater<TUniqueId, TEntry, TChildUpdater>* m_treeUpdater;
  std::list<SWCTIQueueInfo>* queuesData_;
public:
  CQueueTreeCtrl(){};
  ~CQueueTreeCtrl(){};
  void setTreeUpdater(TreeCtrlItemBranchUpdater<TUniqueId, TEntry, TChildUpdater>* treeUpdater){m_treeUpdater = treeUpdater;}
  void setQueuesData(std::list<SWCTIQueueInfo>* queuesData) { queuesData_ = queuesData; }  
public:
  afx_msg void OnRClick(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
};
class CallGroupsQueuesTreeCtrl : public CQueueTreeCtrl<std::string, SWCTIQueueInfo, CMembersBranchUpdater>
{
  DECLARE_DYNAMIC(CallGroupsQueuesTreeCtrl)
  DECLARE_MESSAGE_MAP()
};

class QueuesTreeCtrl : public CQueueTreeCtrl<std::string, SWCTIQueueInfo, CCallersBranchUpdater>
{
public:  
  DECLARE_DYNAMIC(QueuesTreeCtrl)
  DECLARE_MESSAGE_MAP()
};
class SUPERVISORPANEL_API CCallGroupsTab : public CDialogEx, CResizableLayout {
  DECLARE_DYNAMIC(CCallGroupsTab)

public:
  CCallGroupsTab(CWnd* pParent = NULL);   // standard constructor
  virtual ~CCallGroupsTab();

  virtual BOOL PreTranslateMessage(MSG* pMsg);
  
  void Sync(std::list<SWCTIQueueInfo>& arrInfo, const CString &_strFilter);

// Dialog Data
  static const int IDD;

  enum EAction
  {
    eActionNone,
    eActionExpandAll,
    eActionCollapseAll
  };

  void DoTreeAction( EAction action );
  void DoCbSelectedAction();

protected:
  virtual BOOL OnInitDialog();
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

private:
  CCallGroupsQueuesBranchUpdater m_treeUpdater;
public:
  CallGroupsQueuesTreeCtrl m_tree;
  CImageList m_ilWndTree;

  CMFCButton m_btnLogOn;
  CMFCButton m_btnDisconnect;
  CMFCButton m_btnCall;
  CMFCButton m_btnScreen;
  CMFCButton m_btnMessage;

  CEdit      m_edtFilter;

  CComboBox  m_cbFilter;

  afx_msg void OnCbnSelchangeFilter();
  afx_msg void OnBnClickedLogOff();
  afx_msg void OnCbnCloseupFilter();
  afx_msg void OnNMDblclkTreeAgents(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnDestroy();
};
