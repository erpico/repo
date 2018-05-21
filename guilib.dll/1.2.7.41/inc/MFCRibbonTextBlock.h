/*
 * MFCRibbonTextBlock.h
 * 
 *
 * Капралов А.
 * 22.4.2013 12:36
 */
#ifndef __MFCRIBBONTEXTBLOCK_H__
#define __MFCRIBBONTEXTBLOCK_H__

#include "GuiLib.h"

class GUILIB_API CMFCRibbonTextBlock : public CMFCRibbonLabel {
  DECLARE_DYNCREATE(CMFCRibbonTextBlock)

private:
  int m_nWidth;

public:
  CMFCRibbonTextBlock();
  CMFCRibbonTextBlock(LPCTSTR lpszText, BOOL bIsMultiLine = FALSE);
  virtual ~CMFCRibbonTextBlock();

protected:
  virtual void OnCalcTextSize(CDC* pDC);
  virtual CSize GetRegularSize(CDC* pDC);
  
public:
  virtual void SetWidth(int nWidth);
};

#endif // __MFCRIBBONTEXTBLOCK_H__


