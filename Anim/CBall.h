#pragma once
#include <atltypes.h>
class CBall : public CRect
{
private:
	CPen* m_pBallPen;
	CBrush* m_pBallBrush;
	int m_nOffX;
	int m_nOffY;
	CRect* m_pBoundRect;
	
public:
	CBall(int topLeftX = 0, int topLeftY = 0, int bottomRightX = 0, int bottomRightY  = 0, COLORREF ballColor = BLACK, int nOffX = 0, int nOffY = 0);
	CBall(const CRect& rect, COLORREF ballColor = BLACK, int nOffX = 0, int nOffY = 0);
	CBall(const CPoint& point, CSize size, COLORREF ballColor = BLACK, int nOffX = 0, int nOffY = 0);
	~CBall();

	void SetBall(const CRect& rect, COLORREF ballColor = BLACK, int nOffX = 0, int nOffY = 0);
	void SetOffset(int nOffX, int nOffY);
	void SetBoundRect(const CRect& rect);

	void PaintBall(CDC* pDC);
};

