#pragma once
#include <memory>
#include "GuiLib.h"

class CExtendedListView;
//////////////////////////////////////////////////////////////////////////
//ExtendedListView Row
class GUILIB_API CExtendedListRow
{
protected:
  CExtendedListView* m_pOwnerList;
  int m_rowIdx;
  bool m_bWasShownToUser;
  bool m_bVisible;

public:
  CExtendedListRow();
  virtual ~CExtendedListRow();

  void SetOwner(CExtendedListView* pOwner);
  virtual CString FormatTextForCopy() 
  { return CString(); }

  CExtendedListView* GetOwner();

  bool IsSelected();
  bool WasShownToUser() const { return m_bWasShownToUser; }
  
  virtual void PreDrawRow();
  virtual void Draw(CDC* pDC, const CRect& rcRow) = 0;
  virtual void DrawMultiselectLastRowFocus(CDC* pDC, const CRect& rcRect);

  virtual int GetRowHeight(CDC* pDC);

  virtual void OnRowLButtonDblClk(UINT nFlags, CPoint point);
  virtual void OnContextMenu(CWnd* pWnd, CPoint point);

  virtual void OnRowWasShownToUser();

  virtual bool GetTooltipText(CString& strText);

  virtual void OnTimer(){};
  virtual bool isGroupRow() {return false;}
  virtual bool isInviteRow() {return false;}
  virtual void OnLButtonDown(UINT nFlags, CPoint point){};
  virtual void OnLButtonUp(UINT nFlags, CPoint point){};

  int rowIdx() const { return m_rowIdx; }
  void setRowIdx(int idx) { m_rowIdx = idx; }
  bool isVisible() {return m_bVisible;}
  void MakeInvisible() {m_bVisible = false;}
  void MakeVisible() {m_bVisible = true;}

protected:
  void RegisterTimerMessage();
};

typedef std::shared_ptr<CExtendedListRow> ExtendedListRowPtr;