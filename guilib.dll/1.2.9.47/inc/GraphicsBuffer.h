#include <afxwin.h>
#ifndef GRAPHICSBUFFER_H
#define GRAPHICSBUFFER_H


class GraphicsBuffer
{
private:
	CBitmap     bitmap_;
    CDC         dcMemory_;
    int         height_;
    int         width_;
	int         heightDraw_;
	int         widthDraw_;
	bool        isCreated;
public:
	GraphicsBuffer() {width_ = 0; height_ = 0;isCreated=false;}
	~GraphicsBuffer(){}	

	bool create(int width, int height, CDC* pDC,int widthDraw,int heightDraw);
	void release();
	CDC* getDC(){return &dcMemory_;}
	
	void render(CDC* dc);
}; 

#endif //GRAPHICSBUFFER_H