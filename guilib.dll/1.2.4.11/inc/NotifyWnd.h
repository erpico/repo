#pragma once

#include <afxtempl.h>
#include <afxmt.h>
#include "GuiLib.h"

// CNotifyWnd

#define DEFAULT_NOTIFY_WND_ID 0

class GUILIB_API CNotifyWnd : public CWnd
{
protected:  
  DWORD m_dwRefID;

  static const UINT g_wndRedrawTimerId = 1;

public:
  int nGlowDirection;
  int m_nBlinkState;
  int m_nXOffset;
  HICON m_hIcon;
  HICON m_hWndIcon;
  CString m_strTitle;
  CString m_strText;
  COLORREF m_bgColor;
  COLORREF m_titleColor;
  HWND m_hMessageWnd;
  UINT m_wmMessage;
  bool m_fSendAsWmCommand;
  int m_bActive;	

  bool m_fIsDragging;
  CSize m_szDragDelta;
  CPoint m_pntLBtnDown;

  CMFCToolBarImages m_images;
  bool m_bAnimate;
  CSize m_szIcon;
  int m_nImageIndex;

private:
  DECLARE_DYNAMIC(CNotifyWnd)
  CNotifyWnd();

public:
  CNotifyWnd(DWORD dwRefId);
  virtual ~CNotifyWnd();

  virtual BOOL Create(CWnd* pWnd);
  virtual BOOL DestroyWindow();

  BOOL MyShowWindow(int nCmdShow, int nXOffset = 0);
  virtual LONG NtfWindowHeight() const { return 50; }

  void SetCallTitle(const CString& strTitle) { m_strTitle = strTitle; Invalidate(FALSE); SetWindowText(strTitle); }
  void SetCallTimeState(const CString& strState) { m_strText = strState; Invalidate(FALSE); }
  void SetBgColor(COLORREF bgColor) { m_bgColor = bgColor; Invalidate(); }
  void SetTitleColor(COLORREF titleColor) { m_titleColor = titleColor; Invalidate(); }

  int GetXOffset() const { return m_nXOffset; }
  DWORD GetRefID() const { return m_dwRefID; }
  int IsActive() const { return m_bActive; }

  void SetImages(UINT uiResId, const CSize& szIconInImage);
  void AnimateIcon(UINT nFrameFrequencyMls);
  void StopAnimateIcon();
  CSize GetIconSize() const { return m_szIcon; }

  BOOL DrawIcon(CDC* pDC, CRect& rect);

  void SaveWindowPosition();
  void RestoreWindowPosition();

protected:
  BOOL CreateTextMessageFont(CFont& font);
  void DrawWindow(CDC* pDC);

protected:
  DECLARE_MESSAGE_MAP()	
  
  afx_msg void OnPaint();
  afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
  afx_msg void OnSetFocus(CWnd* pOldWnd);
  afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);  
  afx_msg void OnTimer(UINT nIDEvent);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg void OnDestroy();
  afx_msg BOOL OnEraseBkgnd( CDC* pDC );
};

#undef _DECLSPEC
