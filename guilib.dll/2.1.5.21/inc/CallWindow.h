#pragma once
#include "GuiLib/NotifyDlg.h"
#include "GuiLib/TransparentStatic2.h"
#include "Resource.h"
#include "CallWindowSel.h"

class GUILIB_API CMakeCallWnd : public CNotifyDlg
{
public:
  CMakeCallWnd(CWnd* pParentWnd = NULL);
  virtual ~CMakeCallWnd();
  virtual BOOL OnInitDialog();
  virtual void DoDataExchange(CDataExchange* pDX);
  virtual BOOL Create(CWnd* pWnd);
  CString m_strPhone;
  time_t m_tmLastWindowFound;
  CCallWindowSel m_dlgSel;

private:
  int IDD;  
  CMFCButton m_callButton;
  DECLARE_DYNAMIC(CMakeCallWnd)
protected:
  DECLARE_MESSAGE_MAP()
public:
  /*afx_msg void OnBnClickedNotifyTransfer();
  afx_msg void OnBnClickedNotifyMakecall();
  afx_msg void OnBnClickedNotifyReturn();
  afx_msg void OnBnClickedNotifyHold();
  afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);*/
  virtual void OnOK();
  virtual void OnCancel();
  afx_msg LRESULT OnUserMessage(WPARAM wp, LPARAM lp);
  afx_msg void OnTimer(UINT_PTR nIDEvent);

  void FindAndPositionWindow();
};