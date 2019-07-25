#ifndef _PNGIMAGE_H
#define _PNGIMAGE_H

#include "GuiLib.h"
#include <afxwin.h>

class GUILIB_API PngImage : public CBitmap
{
	int m_width;
	int m_height;	
	
public:
	PngImage();
	virtual ~PngImage();

	BOOL Load (UINT uiResID, HINSTANCE hinstRes = NULL);
	BOOL Load (LPCTSTR lpszResourceName, HINSTANCE hinstRes = NULL);

	BOOL LoadFromFile (LPCTSTR lpszPath);
	BOOL LoadFromBuffer (LPBYTE lpBuffer, UINT uiSize);

	int Width() const { return m_width; }
	int Height() const { return m_height; }

	CSize Size() const { return CSize(Width(), Height()); }
	CRect SizeAsRect() const { return CRect(CPoint(), Size()); }

	void Draw(CDC* pDestDC, const CPoint& ptLeftTop);
	void Draw(CDC* pDestDC, const CRect& rcDest);
	void Draw(CDC* pDestDC, const CRect& rcSource, const CRect& rcDest);

private:
	static CString g_strResType;
};

#endif //_PNGIMAGE_H

