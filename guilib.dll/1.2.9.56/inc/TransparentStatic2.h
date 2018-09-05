/************************************************************************/
/* If the background is static, then the best approach is to make a 
 * copy of the area on the parent window behind the static control before 
 * it is drawn for the first time, and then simply copy the image back to 
 * the parent every time the static control needs to be redrawn. 
 * The advantage of this approach is its flicker free display every time 
 * the static control is changed.                                                                     */
/************************************************************************/

#pragma once

#include "GuiLib.h"

// CTransparentStatic2

class GUILIB_API CTransparentStatic2 : public CStatic
{
  DECLARE_DYNAMIC(CTransparentStatic2)

public:
  CTransparentStatic2();
  virtual ~CTransparentStatic2();

private:
  CRITICAL_SECTION csMonitor;

private:
  COLORREF textColor;

public:
  void SetTextColor(COLORREF color);
  
protected:
   afx_msg LRESULT OnSetText(WPARAM,LPARAM);
   afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
   afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  DECLARE_MESSAGE_MAP()
private:
   CBitmap m_Bmp;
};


