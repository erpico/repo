#pragma once
#include "GuiLib.h"


// CClipGroupBox

class GUILIB_API CClipGroupBox : public CStatic
{
	DECLARE_DYNAMIC(CClipGroupBox)

public:
	CClipGroupBox();
	virtual ~CClipGroupBox();

protected:
	DECLARE_MESSAGE_MAP()
  virtual void PreSubclassWindow();
public:
  afx_msg void OnPaint();
};


