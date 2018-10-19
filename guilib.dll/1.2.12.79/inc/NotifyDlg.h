#pragma once
#include "GuiLib.h"

class GUILIB_API CNotifyDlg : public CDialogEx
{
protected:  
  DWORD m_dwRefID;
  static const UINT g_wndRedrawTimerId = 1;

private:
  CRect titleRect_;
  CRect timeRect_;
  CNotifyDlg();
  
  int nGlowDirection;  
  int m_nXOffset; 
  HICON m_hWndIcon;
  CString m_strTitle;
  CString m_strText;
  COLORREF m_bgColor;
  COLORREF m_titleColor;

  bool m_fIsDragging;
  CSize m_szDragDelta;
  CPoint m_pntLBtnDown;

  CMFCToolBarImages m_images;
  bool m_bAnimate;
  CSize m_szIcon;
  int m_nImageIndex;

public:
  CNotifyDlg(DWORD dwRefId, CWnd* pParentWnd = NULL);
  virtual ~CNotifyDlg();
  virtual BOOL Create(UINT nIDTemplate, CWnd* pWnd = NULL);
  virtual BOOL Create(CWnd* pWnd);
  virtual BOOL DestroyWindow();
  virtual BOOL OnInitDialog();
  BOOL MyShowWindow(int nCmdShow, int nXOffset = 0);
  virtual LONG NtfWindowHeight() const { return 80; }

  void BindDlgItems(UINT titleIdTemplate, UINT timeStateIdTemplate, UINT imageIdTemplate);  

  void SetCallTitle(const CString& strTitle) { m_strTitle = strTitle; Invalidate(FALSE); SetWindowText(strTitle); }
  void SetCallTimeState(const CString& strState) { m_strText = strState; Invalidate(FALSE); }
  
  void SetBgColor(COLORREF bgColor) { m_bgColor = bgColor; Invalidate(); }
  void SetTitleColor(COLORREF titleColor) { m_titleColor = titleColor; Invalidate(); }

  void SetImages(UINT uiResId, const CSize& szIconInImage);
  void AnimateIcon(UINT nFrameFrequencyMls);
  void StopAnimateIcon();
  CSize GetIconSize() const { return m_szIcon; }

  BOOL DrawIcon(CDC* pDC, CRect& rect);
  
  void SaveWindowPosition();
  void RestoreWindowPosition();

protected:
  BOOL CreateTextMessageFont(CFont& font);
  virtual void getSizeDefault(CRect& size) { return size.SetRect(0, 0, 360, NtfWindowHeight()); }
  void DrawWindow(CDC* pDC);
  DECLARE_DYNAMIC(CNotifyDlg)

protected:
  DECLARE_MESSAGE_MAP()

  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg void OnPaint();
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnDestroy();
  afx_msg void OnTimer(UINT nIDEvent);
};