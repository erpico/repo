#pragma once

#include "GuiLib.h"

#include "Resource.h"

#include "afxdtctl.h"

// CDatePickerDlg dialog
class CRibbonDateTimePicker;

class GUILIB_API CDatePickerDlg : public CDialog {
  //CMonthCalCtrl m_datePicker;
  CRibbonDateTimePicker* m_pPicker;
  bool fJustShown;

private:
  DECLARE_DYNAMIC(CDatePickerDlg)

public:
  CDatePickerDlg(CWnd* pParent = NULL);   // standard constructor
  virtual ~CDatePickerDlg();

  CTime m_time;
  CMonthCalCtrl m_datePicker;

  virtual void OnOK(){};
  virtual void OnCancel(){};

  void SetParentPicker(CRibbonDateTimePicker* pPicker) { m_pPicker = pPicker; }
  BOOL GetSelectedDate(CTime& tm);
  BOOL SetSelectedDate(CTime& tm);

// Dialog Data
#ifdef GUILIB_EXPORTS
  enum { IDD = IDD_DATETIME_PICKER_DLG };
#endif

protected:
  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();
  virtual BOOL PreTranslateMessage(MSG* pMsg);

  DECLARE_MESSAGE_MAP()
public:
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnCaptureChanged(CWnd *pWnd);
  afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
  afx_msg void OnMcnSelectCalendar(NMHDR *pNMHDR, LRESULT *pResult);
};
