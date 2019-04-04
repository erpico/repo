#pragma once

#include "GuiLib.h"

#include <afxribboncombobox.h>

#include "DatePickerDlg.h"

class GUILIB_API CRibbonDateTimePicker : public CMFCRibbonComboBox
{
  CDatePickerDlg dlg;

private:
  DECLARE_DYNCREATE(CRibbonDateTimePicker)
  CTime m_time;
  bool m_empty;

public:
  CRibbonDateTimePicker(UINT nID, BOOL bHasEditBox = TRUE, 
      int nWidth = -1, LPCTSTR lpszLabel = NULL, int nImage = -1);
protected:
  CRibbonDateTimePicker();
public:
  virtual ~CRibbonDateTimePicker();

public:		
  virtual void OnAfterChangeRect(CDC* pDC);
  virtual void DropDownList();
  void OnDropListHidden();
  void SetTime(CTime tm);
  CTime GetTime();
  void UpdateDateTime();
  void Clear();
  bool IsEmpty();
};