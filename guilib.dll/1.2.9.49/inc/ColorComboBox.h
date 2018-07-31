/*
 * ColorComboBox.h
 * 
 *
 * Капралов А.
 * 14.3.2013 17:50
 */

#ifndef __COLORCOMBOBOX_H__
#define __COLORCOMBOBOX_H__

#include "GuiLib.h"

class GUILIB_API ColorComboBox : public CComboBox {
private:
  CRITICAL_SECTION csMonitor;

private:
  COLORREF textColor;
  COLORREF backgroundColor;
  CBrush *pBrush;

  DECLARE_DYNAMIC(ColorComboBox)

public:
  ColorComboBox();
  virtual ~ColorComboBox();

public:
  void SetTextColor(COLORREF color);
  void SetBackgroundColor(COLORREF color);

private:
  void UpdateBrush();

protected:
  DECLARE_MESSAGE_MAP()
public:
  afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
  afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

#endif // __COLORCOMBOBOX_H__


