#pragma once

#include <vector>
#include "ListViewScrollBar.h"
#include "ExtListView\ExtendedListRow.h"
#include <set>
#include "GuiLib.h"

//template<typename TContainer>
class IntSet
{
public:
  typedef std::set<int> TContainer;

  TContainer m_data;

  void Insert(int iVal)
  {
    m_data.insert(iVal);
  }

  void Delete(int iVal)
  {
    m_data.erase(iVal);
  }

  bool HasValue(int iVal)
  {
    TContainer::iterator it = m_data.find(iVal);
    return (it != m_data.end());
  }

};

//////////////////////////////////////////////////////////////////////////
// CExtListView
#define  WM_LIST_DOUBLECLICK (WM_USER + 15)
#define  WM_LIST_ROW_SELECTED (WM_USER + 17)

class GUILIB_API CExtendedListView : public CWnd
{
  friend class CExtendedListRow;

  struct ViewColumn
  {
    ViewColumn() : width(0)
    {}

    int width;
    CString strText;
  };

  typedef std::vector<ViewColumn> ViewColumnArray;

  static const int s_minimalColumnWidth = 20;
  static const int s_ID_HORZ_SCBAR = 1220;
  static const int s_ID_VERT_SCBAR = 1221;

public:
  typedef std::set<ExtendedListRowPtr> SelectionSet;
  typedef std::set<int> IndexSelectionSet;

protected:
  ViewColumnArray m_columns;

  BOOL m_bIsColumnResizing;
  BOOL m_bIsColumnResizeAreaHover;

  CRect m_rcClient;
  CRect m_rcListViewArea;
  CRect m_rcVertScroll;
  CRect m_rcHorScroll;

  CRect m_rcListHeader;
  CRect m_rcBottomRow;
  int m_iCellsBorderPenWidth;

  std::vector<CRect> m_rcColumnHeaders;
  std::vector<CRect> m_rcColumnResizeAreas;
  //std::vector<CRect> m_rcRows;

  COLORREF m_clrCellsBorder;
  COLORREF m_clrHeaderBgnd;
  COLORREF m_evenRowBgnd;

  COLORREF m_clrBackground;
  
  BOOL fInitialized;
  int m_iResizingColumn;

  CListViewScrollBar m_sbHorisontal;
  CListViewScrollBar m_sbVertical;
  BOOL m_fVerticalScrollBarVisible;
  BOOL m_fHorizontalScrollBarVisible;

  //int m_iRowsCount;
  SelectionSet m_selection;
  
  
  int m_shortcutMultiselectBaseRow;
  int m_shortcutMultiselectLastRow;		
  IndexSelectionSet m_activeShortcutSelectionSet;

  CPoint m_ptViewportOrigin;

  int m_iTotalColumnsWidth;
  int m_iTotalRowsHeight;

  typedef std::vector<ExtendedListRowPtr> RowsArray;
  RowsArray m_rows;

  typedef std::vector<CRect> RowsRectArray;
  RowsRectArray m_arrRowsRect;

  BOOL m_bAllowColumnResize;
  BOOL m_bShowHeaderCells;

  CToolTipCtrl m_tooltip;
  UINT_PTR m_uToolId;
  int m_lastToolRowIdx;

  typedef std::set<CExtendedListRow*> RowsSet;
  RowsSet m_rowsAdvisedForTimer;
  static const UINT_PTR m_uRowsTimerId = 1;

private:
  DECLARE_DYNAMIC(CExtendedListView)

  int GetShortcutMultiselectBaseRowIdx() const;
  void SetShortcutMultiselectBaseRowIdx(int iRow);
  void ClearTempMultiselectVars();
  void ChangeActiveShortcutMultiselection(int iBaseRowIdx, int iLastRowIdx);

  BOOL HandleArrowKeyPress( UINT nChar, UINT nRepCnt, UINT nFlags );

protected:
  void AlignVerticalScrollBar();
  void ShowVerticalScrollBar(BOOL bShow);
  BOOL IsVerticalScrollBarVisible() const;
  int GetVerticalScrollBarWidth() const;
  void UpdateVerticalScrollBarRanges();
  BOOL NeedShowVerticalScrollbar();

  void AlignHorizontalScrollBar();
  void UpdateHorizontalScrollBarRanges();
  void ShowHorisontalScrollBar(BOOL bShow);
  BOOL IsHorizontalScrollBarVisible() const;
  int GetHorizontalScrollBarHeight() const;

  void HeaderToViewportCS(CRect& rcRect) const;
  void ToViewportCS(CRect& rcRect) const;
  CRect RectToViewportCS(const CRect& rcRect) const;

  BOOL ClientAreaSizeChanged();
  int GetListTotalWidth() const;

  void SetTrackMouseLeave();

  int GetListTotalHeight();
  CSize GetViewportSize() const;

  virtual void CreateHeaderFont(CFont& font);
  virtual void CreateRowFont(CFont& font);

  bool IsAddToSelectionKeyPressed();

  void RegisterTimerMessageForRow(CExtendedListRow* ptrRow);
  void UnregisterTimerMessageForRow(CExtendedListRow* ptrRow);
  void CallRegisteredTimerHandlers();

public:
  CExtendedListView();
  virtual ~CExtendedListView();

  virtual BOOL Create(CWnd* pParent, const RECT& rect);

  void AddColumn(int width, const CString& text);

  virtual int GetRowsCount() const { return m_rows.size(); }
  virtual int AddRow(ExtendedListRowPtr ptrRow);
  virtual int InsertRow(ExtendedListRowPtr ptrRow, int pos);
  virtual void DeleteRow(int rowIdx);
  ExtendedListRowPtr GetRow(int idx) const;

//  virtual int SwapPlaces(int idx1, int idx2);

  virtual void Clear();

  virtual void OnSortByColumn(int iCol) {};
  
  int GetColumnsCount() const { return m_columns.size(); }
  CRect GetHeaderCellRect(int iColumn) const;
  CRect GetCellRect(int iRow, int iColumn) const;
  CRect GetRowRect(int iRow) const;
  int GetColumnWidth(int iColumn) const;
  int HitTestColumnResizeArea(const CPoint& pt) const;
  int HitTestColumnSortArea(const CPoint& pt) const;

  virtual void AddRowToSelection(int iRow);
  virtual void RemoveRowFromSelection(int iRow);
  virtual void ToggleSelectionRow(int iRow);
  virtual void ClearSelection();
  virtual SelectionSet GetSelection() const { return m_selection; }
  virtual int GetSelectedRowsCount() const { return m_selection.size(); }
  virtual bool IsRowSelected(CExtendedListRow* pRow) const;
  virtual bool OnSelectionChanging(ExtendedListRowPtr ptrRowToAdd, int rowToAddIdx);
  virtual void OnSelectedRowChanged();
  // single selection only
  int GetSelectedRowIdx() const;
  void SelectSingleRow(int iRow);
  
  int GetRowFromPointIdx(const CPoint& ptViewCS);
  bool IsRowFullyVisible( int iRow ) const;
  bool IsRowPartlyVisible( int iRow ) const;
  int GetFirstVisibleRow() const;
  int GetLastVisibleRow() const;

    void ScrollToTop();
  void ScrollToBottom();
  void EnsureVisible( int iRow, int iPreferredLocation = -1 );

  COLORREF GetBackgroundColor() const { return m_clrBackground; }
  void SetBackgroundColor(COLORREF val) { m_clrBackground = val; }

  void AllowColumnResize(BOOL bAllow);
  void ShowHeaderCells(BOOL bShow);

  int GetRowVerticalPosition( int iRow ) const;

public:
  virtual void OnDraw(CDC* pDC);
  void DrawHeaderPanelBgImage(CDC* pDC, const CRect& rcPanel);
  virtual void DrawHeaderCells(CDC* pDC);
  
  virtual void DrawRows(CDC* pDC);
  virtual BOOL OnEraseBkgnd(CDC* pDC);

  int CalculateHeaderHeight(CDC* pDC);
  int GetTotalColumnsWidth();

  virtual void RecalculateSizes();
  bool IsRectVisible( CRect rc ) const;

public:
  //{{AFX_MSG(CExtListView)
  afx_msg void OnPaint();
  afx_msg void OnFilePrintPreview();
  //afx_msg void OnDestroy();
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  //afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
  afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
  afx_msg void OnMouseLeave();
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
  afx_msg void OnSize(UINT nType, int cx, int cy);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  afx_msg UINT OnGetDlgCode();
  //}}AFX_MSG
protected:
  DECLARE_MESSAGE_MAP()	
  
public:
  virtual BOOL PreTranslateMessage(MSG* pMsg);
  virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);	
  afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnTimer(UINT_PTR nIDEvent);
  afx_msg void OnDestroy();
  void GetRowsDrawRange(int& iFirstRowToDraw, int& iLastRowToDraw);
  virtual void CollapseGroup(long id, int rowidx){};
  virtual void ExpandGroup(long id, int rowid){};
  virtual void DeleteRows(std::set<int> setRowsToDel);
};