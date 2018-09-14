#pragma once

#include "GuiLib.h"

#include "DataComboUtils.h"

class GUILIB_API CDataComboEdit : public CEdit
{
  HWND m_hWndDataCombo;

private:
  DECLARE_DYNAMIC(CDataComboEdit)

public:
  CDataComboEdit();
  virtual ~CDataComboEdit();

  void SetDataComboHwnd(HWND hWnd) { m_hWndDataCombo = hWnd; }
  HWND GetDataComboHwnd() const { return m_hWndDataCombo; }

protected:
  DECLARE_MESSAGE_MAP()

  //virtual BOOL PreTranslateMessage(MSG* pMsg);
  
public:
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg void OnKillFocus(CWnd* pOldWnd);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};