#pragma once
#include "GuiLib.h"

GUILIB_API COLORREF BlendColors(COLORREF crA, COLORREF crB, double fAmountA);
GUILIB_API COLORREF LightenColor(long lScale, COLORREF lColor);
GUILIB_API void GradientFillSlow(CDC* pDC, LPCRECT lpRect, COLORREF crFrom, COLORREF crTo, BOOL bHorz);
GUILIB_API void DrawRectangle(CDC* pDC, LPCRECT lpRect, const CPen& pen);
GUILIB_API int CalculateMaxFontLineHeight(CDC* pDC, const CFont& font);

GUILIB_API BOOL CursorInRect(CWnd* pWnd, const CRect& rcClientAreaPart);
GUILIB_API LOGFONT* AdjustFontToFitSize(CDC* pDC, const CString& strText, const CSize& size, LOGFONT* pLogFont, CSize* pResSize = NULL, bool bAllowEnlarge = true);
GUILIB_API void DrawBitmapPart(CDC* pDC, CDC* pBitmapDC, const CRect& rcDest, const CRect& rcSrc, int ym);
GUILIB_API void ClearTimeForOleDateTime (COleDateTime& date);
GUILIB_API void DrawTextUnicode(CDC* pDC, const CString& txt, CRect rc, UINT format);
GUILIB_API void MoveAndRedraw(CWnd* pWnd, const CRect& rc);

GUILIB_API void CenterRectInsideRect(const CRect& rcOuter, CRect& rcToCenter);
GUILIB_API void FitRect(const CRect& rcOuter, CRect& rcToFit);
GUILIB_API void GetWindowRectInParentClientCS(CWnd* pWnd, CRect& rc);

class GUILIB_API CBackBuffer
{
	CWnd* m_pWnd;
	CDC* m_pDC;
	CDC m_dcBackBuffer;
	HBITMAP m_bmBackBuffer;
	HGDIOBJ m_hOldBitmap;

public:
	CBackBuffer(CWnd* pWnd, CDC* pDC)
	{
		m_pWnd = pWnd;
		m_pDC = pDC;
	}

	~CBackBuffer()
	{
	}

	void Create()
	{
		CRect rcClient;
		m_pWnd->GetClientRect(rcClient);
		m_bmBackBuffer = CreateCompatibleBitmap(*m_pDC, rcClient.Width(), rcClient.Height());

		m_dcBackBuffer.CreateCompatibleDC(m_pDC);
		m_hOldBitmap = m_dcBackBuffer.SelectObject(m_bmBackBuffer);
	}

	void Flush()
	{
		CRect rcClient;
		m_pWnd->GetClientRect(rcClient);
		m_pDC->BitBlt(0, 0, rcClient.Width(), rcClient.Height(), &m_dcBackBuffer, 0, 0, SRCCOPY);

		m_dcBackBuffer.SelectObject(m_hOldBitmap);
		DeleteObject(m_bmBackBuffer);
	}

	CDC* GetDC() { return &m_dcBackBuffer; }
};

class GUILIB_API CBitmapDC
{
	CDC m_dc;
	HBITMAP m_bmCanvas;
	HGDIOBJ m_hOldBitmap;

	CRect m_rcBmSize;

public:
	CBitmapDC() : m_bmCanvas(NULL), m_hOldBitmap(NULL)
	{}		

	~CBitmapDC()
	{ Destroy(); }

	const CRect& GetRect() const { return m_rcBmSize; }

	bool Create(CDC* pDC, const CRect& rcArea)
	{
		Destroy();

		m_rcBmSize = rcArea;
		m_bmCanvas = CreateCompatibleBitmap(*pDC, m_rcBmSize.Width(), m_rcBmSize.Height());
		if(m_bmCanvas == NULL)
			return false;

		if(!m_dc.CreateCompatibleDC(pDC))
			return false;

		m_hOldBitmap = m_dc.SelectObject(m_bmCanvas);
		return true;
	}

	void Destroy()
	{
		if(m_hOldBitmap != NULL)
			m_dc.SelectObject(m_hOldBitmap);
		
		if(m_bmCanvas != NULL)
			DeleteObject(m_bmCanvas);
		
		m_dc.DeleteDC();
		m_rcBmSize = CRect();
	}

	CDC* GetDC() { return &m_dc; }

	bool IsValid() const
	{
		if( m_bmCanvas == NULL)
			return false;

		if( m_dc.GetSafeHdc() == NULL)
			return false;

		return true;
	}
};

inline double Rand (double dblStart, double dblFinish)
{
	double minVal = min(dblStart, dblFinish);
	double maxVal = max(dblStart, dblFinish);

	return (maxVal - minVal) * (double)rand() / (RAND_MAX + 1) + minVal;
}