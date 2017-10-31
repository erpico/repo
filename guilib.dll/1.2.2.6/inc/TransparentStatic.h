/************************************************************************/
/* The other approach comes in handy when the parent window's background 
 * is dynamic. If the parent window's background is constantly changing 
 * then the above approach will not look too nice. So instead of all 
 * the copying, what the static control should do is invalidate the area 
 * of the parent where the control resides every time its text is changed. 
 * This method is much simpler than the one before, but it could flicker 
 * if the text is changed at a rapid rate.                                                                     */
/************************************************************************/

#pragma once

#include "GuiLib.h"

// CTransparentStatic

class GUILIB_API CTransparentStatic : public CStatic
{
  DECLARE_DYNAMIC(CTransparentStatic)

public:
  CTransparentStatic();
  virtual ~CTransparentStatic();

protected:
   afx_msg LRESULT OnSetText(WPARAM,LPARAM);
   afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
   DECLARE_MESSAGE_MAP()
};


