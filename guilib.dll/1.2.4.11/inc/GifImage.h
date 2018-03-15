#ifndef _GIFIMAGE_H
#define _GIFIMAGE_H

#include "GuiLib.h"
#include <afxwin.h>
#include <gdiplus.h>


class GUILIB_API GifImage : public Gdiplus::Image
{
public:
	GifImage();
	virtual ~GifImage();

	BOOL Load (UINT uiResID, HINSTANCE hinstRes = NULL);
	BOOL Load (LPCTSTR lpszResourceName, HINSTANCE hinstRes = NULL);
	
	void Draw(CDC* pDestDC, const CRect& rcDest);	

	void Update();

	CSize	GetSize();
	bool	IsAnimatedGIF() { return m_nFrameCount > 1; }

protected:
	bool	TestForAnimatedGIF();
	void	Initialize();
	void	Destroy();

	bool LoadFromBuffer(BYTE* pBuff, int nSize);
	bool GetResource(LPCTSTR lpName, LPCTSTR lpType, void* pResource, int& nBufSize, HINSTANCE hResInstance);
	bool Load(CString sResourceType, CString sResource);

	IStream*		m_pStream;	
	UINT			m_nFrameCount;
	UINT			m_nFramePosition;
	bool			m_bIsInitialized;
	Gdiplus::PropertyItem*	m_pPropertyItem;
	long m_tmNextFrame;
};

#endif //_GIFIMAGE_H

