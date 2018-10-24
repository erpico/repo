#pragma once
#include <map>
#include "GuiLib.h"

class GUILIB_API CResizableLayout
{
public:
	enum RepositionAnchor
	{
		erLeftBottom,
		erLeftTop,
		erRightBottom,
		erRightTop,
		erRightTopBottom,
		erLeftRightBottom,
		erLeftRightTopBottom,
		erLeftTopBottom,
		erLeftRightTop,
	};

	struct RepositionCtx
	{
		RepositionAnchor eAnchor;
		int dLeft;
		int dRight;
		int dTop;
		int dBottom;
	};

	typedef std::map<CWnd*, RepositionCtx> RepositionWindows;
	RepositionWindows m_repositionWindows;

public:
	CResizableLayout(void);
	~CResizableLayout(void);

	void RegisterRepositionControl( CWnd* pParent, CWnd* pWnd, RepositionAnchor eAnchor );
	void HandleResize(CWnd* pResizingWnd);
	void AlignWindowToAnchor( CWnd* pParent, CWnd* pWnd, const RepositionCtx& ctx);
};

