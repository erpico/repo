#ifndef PROGRESSRING_H
#define PROGRESSRING_H

#include <afxwin.h>
#include "GraphicsBuffer.h"
#include <Wingdi.h>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>
#include "GuiLib.h"

class Indicator
{
public:
	double  degrees_;
	double  fast_;

	Indicator();
	Indicator(double degrees);

	double getDegrees(){return degrees_;}
	void setDegrees(double degrees){degrees_=degrees;}

	double getFast(){return fast_;}
	void setFast(double fast){fast_=fast;}
};

class GUILIB_API ProgressRing:public CWnd
{
public:
	ProgressRing();
	~ProgressRing();
	void startAnimate();
	void stopAnimate();

	void setHeight(int height);
	int getHeight(){return height_;}

	void setIndicatorColor(COLORREF indicatorColor);
	COLORREF getIndicatorColor(){return indicatorColor_;}

	void Pulse() {this->Invalidate();}

	void setRefreshRate(int refreshRate);
	int getRefreshRate(){return refreshRate_;}
private:
	static  const   int          CONTROL_HEIGHT = 30;
	static  const   int          ANTIALIASING = 4;
    static  const   int          CONTROL_WIDTH = CONTROL_HEIGHT;
	static  COLORREF             INDICATOR_COLOR;
	static const double          INDICATOR_OFFSET;
	static  const   int          MAXIMUM_INDICATORS = 6;
	static  const   int          SIZE_FACTOR = 20;
	static  const   double       START_AT;
	static  const   unsigned int TIMER_INTERVAL=50;
		
	int                 height_;
	int                 width_;
	int                 heightDraw_;
	int                 widthDraw_;
	GraphicsBuffer      indicator_;
	
	int                 indicatorCenterRadius_;
	COLORREF            indicatorColor_;
	int                 indicatorDiameter_;
	int                 indicatorRadius_;
	std::vector<Indicator*> indicators_;
	int                 innerRadius_;
	int                 outerRadius_;	
	unsigned int        refreshRate_;	
	double              startAt_;
	UINT                m_timer;	
	// Таблицы синусов и косинусов
	std::vector<double> cosine_;
    std::vector<double> sine_;

	CMFCToolBarImages m_images;	

	double deg_2_rad ( double degrees ){return (M_PI * ( degrees / 180.0 ) );}
 
	void initializeTrigonometryTables();
	
	double cos(double degrees);
	double sin(double degrees);
	int round(double control_value){ return ((int)(control_value+0.5));}

	void initializeIndicators();	
    
	void adjustControlDimensionsFromHeight(int new_height);   
	

	void drawIndicator(CDC* pDC);
    
public:
	DECLARE_MESSAGE_MAP()
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
};

#endif //PROGRESSRING_H