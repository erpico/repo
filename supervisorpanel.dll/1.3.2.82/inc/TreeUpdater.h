#pragma once


#include "ErpicoCTI/ACDClient.h"
#include "afxcmn.h"
#include "afxwin.h"
#include "AgentsTab.h"

///
///////
///
class SupervisorDialog;

template<typename TUniqueId, typename TEntry, typename TChildUpdater>
class TreeCtrlItemBranchUpdater
{
protected:
  bool showHidden_;
public:
  typedef TreeCtrlItemBranchUpdater<TUniqueId, TEntry, TChildUpdater> Base;

  HTREEITEM m_rootItem;
  CTreeCtrl* m_pTree;  

  std::map<TUniqueId, HTREEITEM> m_mapItems;
  std::set<TUniqueId> m_setItemsInTree;
  std::set<HTREEITEM> m_mapShouldUpdate;

  typedef std::map<TUniqueId, TChildUpdater> TChildUpdatersCollection;
  TChildUpdatersCollection m_mapChildBranches;

  TreeCtrlItemBranchUpdater() {
    showHidden_ = true;
    m_rootItem = NULL;
    m_pTree = 0;
  }

  void setShowHidden(bool showHidden)
  {
    showHidden_ = showHidden;
  }

  bool getShowHidden()
  {
    return showHidden_;
  }

  void SetRoot(HTREEITEM hRoot)
  {
    m_rootItem = hRoot;
  }

  void SetTree(CTreeCtrl* pTree)
  {
    m_pTree = pTree;
  }

  virtual TUniqueId GetUniqueId(const TEntry& aEntry) = 0;
  virtual bool ItemsHasChildren() const { return false; }
  virtual bool isItemHidden(const TEntry& aEntry) const { return false; }
  virtual void SyncChildTree(TChildUpdater& aUpdater, const TEntry& aEntry ) {}
  virtual CString FormatItemText(const TEntry& aEntry) = 0;

  void Sync(const std::list<TEntry>& arrEntries, const CString &_strFilter = "")
  {
    std::set<TUniqueId> setPrevQueuesInTree = m_setItemsInTree;
    m_setItemsInTree.clear();

    std::list<TEntry>::const_iterator it = arrEntries.begin();
    while( it != arrEntries.end() )
    {
      const TEntry& aEntry = *it;
      if (isItemHidden(aEntry)) {
        ++it;
        continue;
      }

	  if (!_strFilter.IsEmpty())
	  {
	    SWCTIQueueInfo* queueInfo = (SWCTIQueueInfo*) &aEntry;
		if (queueInfo)
		{
	      CString strName = queueInfo->szName.c_str();
          Queue queue;
          if (R_OK == GetSupervisorPanelAdapter()->GetCtiManager()->getQueue(queue, strName))
	      {
            strName = queue.fullname;
          }

		  if (strName.Find(_strFilter, 0) == -1)
		  {
		    ++it;
		    continue;
		  }
		}
	  }

      TUniqueId id = GetUniqueId(aEntry);
      m_setItemsInTree.insert(id);
      setPrevQueuesInTree.erase(id);

      HTREEITEM hItem = TryFindTreeItemForId(id);
      if(hItem == NULL)
        hItem = InsertItemToTree( aEntry );

      SyncTreeEntry( hItem, aEntry );

      ++it;
    }

    DeleteOutdatedItems( setPrevQueuesInTree );
  }

  void Update() // time, for example;
  {
    std::set<TUniqueId>::iterator it = m_setItemsInTree.begin();
    while (it != m_setItemsInTree.end())
    {
      UpdateTreeItem(*it);
      ++it;
    }
  }

  void UpdateTreeItem(const TUniqueId& aId)
  {
    HTREEITEM hItem = TryFindTreeItemForId( aId );
    if(hItem == NULL)
      return;

    UpdateTreeItem(hItem, aId);

    TChildUpdatersCollection::iterator it = m_mapChildBranches.begin();
    while(it != m_mapChildBranches.end())
    {
      (it->second).Update();
      ++it;
    }
  }

  virtual void UpdateTreeItem(HTREEITEM hItem, const TUniqueId& aId) 
  {
    CString strText;
    if( !FormatItemTextForUpdate(aId, strText) )
      return;

    m_pTree->SetItemText(hItem, strText);
  }

  virtual bool FormatItemTextForUpdate(const std::string& aId, CString& outStr)
  {
    return false;
  }


  HTREEITEM TryFindTreeItemForId( const TUniqueId& aId )
  {
    std::map<TUniqueId, HTREEITEM>::iterator it = m_mapItems.find(aId);
    if(it == m_mapItems.end())
      return NULL;

    return it->second;
  }

  HTREEITEM InsertItemToTree( const TEntry& aEntry )
  {
    HTREEITEM hItem = m_pTree->InsertItem( "[new item placeholder]", 0, 0, m_rootItem, TVI_LAST );
    MapTreeItemToId(hItem, GetUniqueId(aEntry));
    OnItemCreated(hItem, aEntry);
    // m_pTree->Expand(m_rootItem, TVE_EXPAND);

    return hItem;	
  }

  HTREEITEM SyncTreeEntry( HTREEITEM hItem, const TEntry& aEntry )
  {
    SyncTreeItemEntry( hItem, aEntry );
    SyncChildTrees( hItem, aEntry );
    
    return hItem;
  }

  virtual HTREEITEM SyncTreeItemEntry( HTREEITEM hItem, const TEntry& aEntry )
  {
    CString strText = FormatItemText(aEntry);
    m_pTree->SetItemText(hItem, strText);
    OnTreeItemSynced(aEntry);
    return hItem;
  }

  void SyncChildTrees(HTREEITEM hEntryItem, const TEntry& aEntry)
  {
    if( !ItemsHasChildren() )
      return;

    TChildUpdatersCollection::iterator it = m_mapChildBranches.find( GetUniqueId(aEntry) );
    if( it == m_mapChildBranches.end() )
    {
      TChildUpdater childUpdater;
      childUpdater.SetRoot(hEntryItem);
      childUpdater.SetTree(m_pTree);
      SyncChildTree(childUpdater, aEntry);
      m_mapChildBranches.insert( std::make_pair(GetUniqueId(aEntry), childUpdater) );
    }
    else
    {
      SyncChildTree(it->second, aEntry);
    }
  }

  void MapTreeItemToId( HTREEITEM hItem, const TUniqueId& aId )
  {
    m_mapItems.insert( std::make_pair(aId, hItem) );
  }

  void DeleteOutdatedItems( std::set<TUniqueId>& setPrevItemsInTree )
  {
    std::set<TUniqueId>::iterator it = setPrevItemsInTree.begin();
    while(it != setPrevItemsInTree.end())
    {
      const TUniqueId& id = *it;

      HTREEITEM hItem = TryFindTreeItemForId( id );
      if(hItem != NULL)
      {
        OnItemDeleting(hItem, id);
        m_pTree->DeleteItem(hItem);
      }

      TChildUpdatersCollection::iterator itChilds = m_mapChildBranches.find( id );
      if( itChilds != m_mapChildBranches.end() )
        m_mapChildBranches.erase( itChilds );

      OnItemDeleted(id);

      ++it;
    }
  }

  virtual void OnItemCreated(HTREEITEM hItem, const TEntry& aEntry)
  {
    m_pTree->SetItemData(hItem, (DWORD_PTR)NULL);
  }

  virtual void OnTreeItemSynced(const TEntry& aEntry){}
  
  virtual void OnItemDeleting(HTREEITEM hItem, const TUniqueId& aId)
  {
    void* pData = (void*)m_pTree->GetItemData(hItem);
    if(pData != NULL)
      delete pData;
    
    std::map<TUniqueId, HTREEITEM>::iterator it = m_mapItems.find(aId);
    if(it != m_mapItems.end())
      m_mapItems.erase(it);
  }
  
  virtual void OnItemDeleted(const TUniqueId& id){}
};

//////////////////////////////////////////////////////////////////////////
///
///

class CNullBranchUpdater
{
public:	
  void SetRoot(HTREEITEM /*hRoot*/)
  {

  }

  void SetTree(CTreeCtrl* /*pTree*/)
  {

  }

  void SetSupervisorDialog(SupervisorDialog* /*pDlg*/)
  {
  }

  void Update(){}
};


//////////////////////////////////////////////////////////////////////////
// Aux function


static void ExpandBranch(CTreeCtrl& tree, HTREEITEM hti, BOOL bExpand = TRUE) {
  if (hti == NULL) {
    return;
  }

  if (hti == TVI_ROOT || tree.ItemHasChildren( hti )) {
    tree.Expand( hti, bExpand ? TVE_EXPAND : TVE_COLLAPSE );
    hti = tree.GetChildItem( hti );
    do {
      ExpandBranch( tree, hti, bExpand );
    } while ((hti = tree.GetNextSiblingItem( hti )) != NULL);
  }
  //tree.EnsureVisible( tree.GetSelectedItem() );
}