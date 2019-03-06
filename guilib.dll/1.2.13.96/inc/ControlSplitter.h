#if !defined(AFX_CONTROLSPLITTER_H__AEB6C69A_7B1E_4CBD_9391_76B6E8B7900D__INCLUDED_)
#define AFX_CONTROLSPLITTER_H__AEB6C69A_7B1E_4CBD_9391_76B6E8B7900D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#define SPF_TOP             0x0010                  /* distance of the control to the top of the window will be constant */
#define SPF_BOTTOM          0x0020                  /* distance of the control to the bottom of the window will be constant */
#define SPF_LEFT            0x0040                  /* distance of the control to the left of the window will be constant */
#define SPF_RIGHT           0x0080                  /* distance of the control to the right of the window will be constant */

#endif // _MSC_VER > 1000
// ControlSplitter.h : ヘッダー ファイル
//
#include <vector>
#include "GuiLib.h"
/////////////////////////////////////////////////////////////////////////////
// CControlSplitter ウィンドウ
#define WM_SPLITTER_MOVED (WM_USER + 154)
#define UWM_SPLIT_MOVED_MSG		_T("UWM_SPLIT_MOVED_MSG	")
static UINT UWM_SPLIT_MOVED   = ::RegisterWindowMessage(UWM_SPLIT_MOVED_MSG);

class GUILIB_API CControlSplitter : public CButton
{	
// コンストラクション
public:
  typedef enum {
    CS_VERT = 1,
    CS_HORZ = 2,
    CS_NONE = 0
  };
  
  CControlSplitter();
  virtual ~CControlSplitter();

  virtual void PreSubclassWindow();
  virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

public:
  void AddToBottomOrRightCtrls(UINT nCtrlId, WORD nFlags = SPF_TOP|SPF_LEFT|SPF_RIGHT|SPF_BOTTOM);
  void AddToTopOrLeftCtrls(UINT nCtrlId, WORD nFlags = SPF_TOP|SPF_LEFT|SPF_BOTTOM|SPF_RIGHT);
  void SetType(UINT nType);

  void SetBgColor(COLORREF val) { m_clrBackground = val; }
  
  void SetLimits(int left, int right)
  {
    m_leftLimit = left;
    m_rightLimit = right;
  }

  // 生成されたメッセージ マップ関数
protected:
  //{{AFX_MSG(CControlSplitter)
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
  //}}AFX_MSG

  DECLARE_MESSAGE_MAP()
  void DrawSplitter(CDC* pDC);
private:
  unsigned int m_nType;
  std::vector<DWORD> m_vtTopLeftControls;
  std::vector<DWORD> m_vtBottomRightControls;
  CWnd * m_pOldDragCapture;
  CPoint m_ptStartDrag,m_ptStartPos;  
    bool m_bDragging;
  HCURSOR m_hCursor;
  CRect m_rectMax;

  int m_leftLimit;
  int m_rightLimit;

  COLORREF m_clrBackground;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CONTROLSPLITTER_H__AEB6C69A_7B1E_4CBD_9391_76B6E8B7900D__INCLUDED_)
