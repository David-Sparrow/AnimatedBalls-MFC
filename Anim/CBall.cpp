#include "pch.h"
#include "CBall.h"


CBall::CBall(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY, COLORREF ballColor, int nOffX, int nOffY) :
	CRect(CPoint(topLeftX, topLeftY), CPoint(bottomRightX, bottomRightY))
{
	m_pBallPen = new CPen(PS_SOLID, 1, ballColor);
	m_pBallBrush = new CBrush(ballColor);
	m_nOffX = nOffX;
	m_nOffY = nOffY;

	m_pBoundRect = new CRect();
}

CBall::CBall(const CRect&  rect, COLORREF ballColor, int nOffX, int nOffY) :
	CRect(rect)
{
	//this->CopyRect(&rect);
	m_pBallPen = new CPen(PS_SOLID, 1, ballColor);
	m_pBallBrush = new CBrush(ballColor);
	m_nOffX = nOffX;
	m_nOffY = nOffY;

	m_pBoundRect = new CRect();
}

CBall::CBall(const CPoint & point, CSize size, COLORREF ballColor, int nOffX, int nOffY) :
	CRect(point, size)
{
	m_pBallPen = new CPen(PS_SOLID, 1, ballColor);
	m_pBallBrush = new CBrush(ballColor);
	m_nOffX = nOffX;
	m_nOffY = nOffY;

	m_pBoundRect = new CRect();
}

CBall::~CBall()
{
	delete m_pBallBrush;
	delete m_pBallPen;
	delete m_pBoundRect;
	
	/* //DEBUG
	CString str;
	str.Format(L"destruk");
	AfxMessageBox(str);*/
}

void CBall::SetBall(const CRect & rect, COLORREF ballColor, int nOffX, int nOffY)
{
	this->CopyRect(&rect);
	delete m_pBallBrush;
	delete m_pBallPen;

	m_pBallPen = new CPen(PS_SOLID, 1, ballColor);
	m_pBallBrush = new CBrush(ballColor);

	m_nOffX = nOffX;
	m_nOffY = nOffY;
}

void CBall::SetOffset(int nOffX, int nOffY)
{
	m_nOffX = nOffX;
	m_nOffY = nOffY;
}

void CBall::SetBoundRect(const CRect & rect)
{
	m_pBoundRect->CopyRect(&rect);
}


void CBall::PaintBall(CDC * pDC)
{
	if (this->top + 10 <= m_pBoundRect->top || this->bottom - 10 >= m_pBoundRect->bottom)
		this->MoveToY(10);

	if (this->right - 10 >= m_pBoundRect->right || this->left + 10 <= m_pBoundRect->left)
		this->MoveToX(10);

	if (this->top <= m_pBoundRect->top || this->bottom >= m_pBoundRect->bottom)
		m_nOffY = -m_nOffY;

	if (this->right >= m_pBoundRect->right || this->left <= m_pBoundRect->left)
		m_nOffX = -m_nOffX;

	CBrush* pOldBrush = pDC->SelectObject(m_pBallBrush);
	CPen* pOldPen = pDC->SelectObject(m_pBallPen);
	pDC->Ellipse(this);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);

	/*CDC memDC;
	BOOL b = memDC.CreateCompatibleDC(pDC);
	ASSERT(b);

	CBitmap bmp;
	b = bmp.CreateCompatibleBitmap(pDC, m_pBoundRect->Width(), m_pBoundRect->Height());
	ASSERT(b);

	CBitmap* pOldBitmap = memDC.SelectObject(&bmp);
	memDC.FillSolidRect(m_pBoundRect, RGB(230, 230, 230));

	CBrush* pOldBrush = memDC.SelectObject(m_pBallBrush);
	CPen* pOldPen = memDC.SelectObject(m_pBallPen);

	memDC.Ellipse(this);

	memDC.SelectObject(pOldBrush);
	memDC.SelectObject(pOldPen);

	b = pDC->BitBlt(0, 0, m_pBoundRect->Width(), m_pBoundRect->Height(), &memDC, 0, 0, SRCCOPY);
	ASSERT(b);
	
	memDC.SelectObject(pOldBitmap);
	bmp.DeleteObject();
	memDC.DeleteDC();*/

	
	this->OffsetRect(m_nOffX, m_nOffY);
}
