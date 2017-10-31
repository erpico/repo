#pragma once

#include "GuiLib.h"

#include "DataComboList.h"
#include "DataComboEdit.h"
#include "DataComboUtils.h"
#include "Core\ThrSafeValue.h"


#define WM_STREET_OBJ_KILLFOCUS WM_USER+1111

typedef CArray<CDataComboList::DisplayItem> TrueContentArray;

class GUILIB_API CDataComboBase : public CComboBox
{
  DECLARE_DYNAMIC(CDataComboBase)

protected:
  CDataComboList m_listCtrl;
  CDataComboEdit m_editCtrl;
  CNativeComboList m_nativeListBox;

  bool m_fPassParentNotify;

  SafeBool m_fStopSearch;
  HANDLE m_hSearchThread;
  SafeBool m_fIsSearchInProgress;
  
  SafeString m_strCmpTemplate;
  CString m_strSearchLabel;

  SafeBool m_fIsLocked;
  SafeString m_strLockLabel;
  
  UINT_PTR m_uSearchTemplateTimer;

  struct Item
  {
    CString strLabel; // строка для отображения в листе и комбо
    CString strSearchLabel; // строка, по которой будет происходить поиск на соотв. с шаблоном. Пока тут храним strLabel.MakeLower()
  };

  CArray<Item*> m_arrBaseItems;
  CCriticalSection m_csArrBaseItems;

  TrueContentArray m_arrTrueContent; // кэшированный массив, который используется для быстрого сброса отображаемых элементов
  CCriticalSection m_csTrueContent;

  Safe_INT_PTR m_nCurSel;

  SafeBool m_fAutoSelectOneItem;

public:
  CDataComboBase();
  virtual ~CDataComboBase();

  INT_PTR GetCurSel() { return m_nCurSel.get(); }
  bool SetCurSelEx(INT_PTR nItem);
  bool SetCurSel(INT_PTR nItem); // может быть вызвана из другого потока?
  bool SelectItemWithLabel(const CString& sLabel);
  CString GetSelectedItemLabel();

  void ShowDropDown(BOOL bShowIt = TRUE); // Использует SendMessage! Нельзя вызывать из-под крит. секции!

  bool GetAutoSelectOneItem() { return m_fAutoSelectOneItem.get(); }
  void SetAutoSelectOneItem(bool fSelect) { m_fAutoSelectOneItem.set(fSelect); }

  void SearchCountForTemplate(const CString& strTmpl, int& iCurSel, int& iCount);

  //BOOL GetDroppedState() const;
  virtual void SetTrueContent(bool fRefreshList = true); // тоже разные потоки!
  
  virtual INT_PTR GetItemsCount();
  virtual INT_PTR AddItem(const CString& strLabel);  
  virtual void ResetItems(); // тоже разные потоки!
  
  virtual bool SetItemLabel(INT_PTR nItem, const CString& label);
  virtual bool GetItemLabel(INT_PTR nItem, CString& label);

  CString GetSearchLabel() const { return m_strSearchLabel; }
  void SetSearchLabel(const CString& strLabel) { m_strSearchLabel = strLabel; }

  void LockWithStatus(const CString& strStatus);
  void Unlock();
  bool IsLocked() { return m_fIsLocked.get(); }
  CString GetLockStatusLabel() { return m_strLockLabel.get(); }

  bool IsSearchInProgress() { return m_fIsSearchInProgress.get(); }

  void SetShowDropDown(const bool &_bValue) { m_bShowDropDown = _bValue; }

private:
  int GetCount() const { return 0; } // эта функция заменена виртуальной GetItemsCount()
  DWORD_PTR GetItemData(int nIndex) const { return 0; }
  int SelectString(int nStartAfter, LPCTSTR lpszString) { return -1; } // Заменена на SelectItemWithLabel()
  void GetLBText(int nIndex, CString& rString) const {}; // заменена на GetItemLabel
  void ResetContent() {};
  int AddString(LPCTSTR lpszString) { return -1; }
  int DeleteString(UINT nIndex) { return -1; }
  int InsertString(int nIndex, LPCTSTR lpszString) { return -1; }

  bool FilterSpecialKeyEvents(MSG* pMsg);
  void PassParentNotify(USHORT uNotify);

  bool m_bShowDropDown;
  
protected:
  INT_PTR AddItem(Item* pItem);
  bool CheckItemValid(INT_PTR nItem);

  static Item* CreateItem(const CString& strLabel);
  
protected:
  virtual void PreSubclassWindow();
  virtual BOOL PreTranslateMessage(MSG* pMsg); 
  virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
  
  void SetMatchingContent(const CString& strTemplate);

  BOOL SubclassComboEdit();
  void UnsubclassComboEdit();

  BOOL CreateCustomComboList();
  //BOOL DataComboControlsFocused();
  BOOL IsDataComboWindow(HWND hWnd);
  BOOL IsDataComboWindow(CWnd* pWnd);

  //void ShowCustomComboList(BOOL bShow = TRUE);

  CString GetSearchTemplate() { return m_strCmpTemplate.get(); }
  void SetSearchTemplate(const CString& strTemplate) { m_strCmpTemplate.set(strTemplate); }
  
  void StartSearchThread();
  void StopSearchThread();

  static DWORD WINAPI SearchThreadProc(LPVOID pParam);
  virtual void InThreadSearchTemplate();

  void ResetSearchTemplateTimer();
  void DestroySearchTimer();

protected:
  DECLARE_MESSAGE_MAP()

public:
  //afx_msg void OnSetFocus(CWnd* pOldWnd);
  //afx_msg void OnKillFocus(CWnd* pOldWnd);
  afx_msg void OnDestroy();
  afx_msg void OnCbnSelendCancel();
  //afx_msg void OnCbnSelchange();
  //afx_msg void OnCbnSelendok();
  afx_msg void OnCbnDropdown();
  //afx_msg void OnCbnCloseup();
  afx_msg void OnCbnKillFocus();
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
  //afx_msg LRESULT OnHideComboList(WPARAM wParam, LPARAM lParam);
  //afx_msg LRESULT OnComboListKillFocus(WPARAM wParam, LPARAM lParam);
  //afx_msg LRESULT OnComboEditClick(WPARAM wParam, LPARAM lParam);
  //afx_msg LRESULT OnNativeComboSetFocus(WPARAM wParam, LPARAM lParam);
  //afx_msg LRESULT OnComboEditKillFocus(WPARAM wParam, LPARAM lParam);
  //afx_msg LRESULT OnComboListMouseClose(WPARAM wParam, LPARAM lParam);
  //afx_msg LRESULT OnMouseClickCheck(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnCombolistSelendOk(WPARAM wParam, LPARAM lParam);
  //afx_msg void OnCbnKillFocus();
  afx_msg LRESULT OnTemplateSearchStarted(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnTemplateSearchFinished(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnTemplateSearchCancelled(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnDataComboUnlock(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetCurSel(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetTrueContent(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnSetMatchingContent(WPARAM wParam, LPARAM lParam);
  afx_msg void OnCbnEditChange();
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  //afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnActivateApp( BOOL bActive, DWORD dwThreadID);
  //afx_msg void OnPaint();
  //afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
  //afx_msg void OnSize(UINT nType, int cx, int cy);
  //afx_msg BOOL OnNcActivate(BOOL bActive);
  //afx_msg void OnParentNotify(UINT message, LPARAM lParam);
};