#pragma once

#include "GuiLib.h"

#include "DataComboUtils.h"
#include "Core/ThrSafeValue.h"
#include <afxtempl.h>
//#include <vector>

class GUILIB_API CDataComboList : public CListCtrl
{
  friend class CDataComboBase; // Этот класс предназначен только для работы с CDataCombBase, поэтому все интерфейсы доступны только ему
  friend class CNativeComboList;

public:
  struct DisplayItem
  {
    int nItemId;
    int nSortData;

    DisplayItem() 
    {
      nItemId = 0;
      nSortData = 0;
    }

    DisplayItem(int itemId, int sortData = 0)
    {
      nItemId = itemId;
      nSortData = sortData;
    }
  };

private:
  //typedef std::vector<DisplayItem> TDisplayItemArray;
  CArray<DisplayItem> m_arrDispItems;
  CCriticalSection m_csArrDispItems;

  HWND m_hWndDataCombo;
  CDataComboBase* m_pParentDataCombo;

  int m_nProgressPos;
  bool m_fProgressDirection;

  UINT_PTR m_uProgressTimer;

  SafeString m_strSearchTemplate;
  SafeString m_strEmptyListLabel;

private:
  DECLARE_DYNAMIC(CDataComboList)

protected:
  CDataComboList();
  virtual ~CDataComboList();

  void SetTrueContent(const CArray<CDataComboList::DisplayItem>& arrItems, bool fRefreshList = true);

  INT_PTR GetSelectedItem();
  void SetSelectedItem(INT_PTR nItemId);

  int GetSelectedDispItem();

  void SelectNextItem();
  void SelectPrewItem();
  void SelectFirstItem();
  void SelectLastItem();
  void SelectPageDown();
  void SelectPageUp();

  void SelectDispItem(int idx);

  virtual void PreSubclassWindow();

  void SetDataComboHwnd(HWND hWnd, CDataComboBase* pDataCombo) { m_hWndDataCombo = hWnd; m_pParentDataCombo = pDataCombo; }
  HWND GetDataComboHwnd() const { return m_hWndDataCombo; }

  void OnDataComboLock();
  void OnDataComboUnlock(); // Вызывать только из основного потока обработки сообщений!! (или переделать на postmessage)

  void OnBeginSearchTemplate();
  void OnEndSearchTemplate();

  void RedrawList();
  
  INT_PTR GetDisplayItemsCount();

  void AddDisplayItem(int nItemId, int nSortData);
  void ClearDisplayItems(); // отрисовку в основной поток!

private:
  void ResetProgressTimer();
  void KillProgressTimer(); 

  void SetSearchTemplate(const CString& sTempl) { m_strSearchTemplate.set(sTempl); }
  CString GetSearchTemplate() { return m_strSearchTemplate.get(); }

  static int DisplayItemSortProc(const void* data1, const void* data2);
  void SortDisplayItems();
  CString GetSearchLabel() const;
  CString GetLockLabel();
  void DrawProgress(const CString& strLabel);

  void AdjustListColumnWidth();

  void GetDisplayItemLabel(int nItemId, CString& strLabel);
  int ItemFromDispItem(int nDispItem);
  int DispItemFromItem(INT_PTR nItemId);

  bool IsDataComboLocked();
  bool IsDataComboSearchInProgress();
  
  void SetDisplayContent(); // должно происходить в основном потоке!
  
protected:
  virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
  //virtual BOOL PreTranslateMessage(MSG* pMsg); 

  //BOOL PassMouseEvent(CWnd* pWndCaller, MSG* pMsg);
  //DWORD MouseEventToInputFlags(UINT message);

protected:
  DECLARE_MESSAGE_MAP()

public:
  //afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnNMClick(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnKillFocus(CWnd* pOldWnd);  
  //afx_msg void OnLvnHotTrack(NMHDR *pNMHDR, LRESULT *pResult);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  //afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
  afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnDestroy();
  //afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg LRESULT OnRefreshDisplayContent(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnDataComboDisplayLock(WPARAM wParam, LPARAM lParam);
  afx_msg LRESULT OnDataComboDisplayUnlock(WPARAM wParam, LPARAM lParam);
  afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
  afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
  afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
  afx_msg void OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp);
};

//////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////

class CNativeComboList : public CListBox
{
  HWND m_hWndDataCombo;
  CDataComboList* m_pCustomComboList;

private:
  DECLARE_DYNAMIC(CNativeComboList)

  void ResizeCustomList();

public:
  CNativeComboList();
  virtual ~CNativeComboList();

  void SetDataComboHwnd(HWND hWnd) { m_hWndDataCombo = hWnd; }
  HWND GetDataComboHwnd() const { return m_hWndDataCombo; }

  void SetCustomComboList(CDataComboList* pList) { m_pCustomComboList = pList; }

protected:
  DECLARE_MESSAGE_MAP()

  virtual BOOL PreTranslateMessage(MSG* pMsg); 
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);

public:
  //afx_msg void OnKillFocus(CWnd* pOldWnd);
  //afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnMove(int x, int y);
  //afx_msg UINT OnNcHitTest(CPoint point);
  //afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  //afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  //afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};