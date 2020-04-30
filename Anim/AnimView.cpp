
// AnimView.cpp : implementation of the CAnimView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Anim.h"
#endif

#include "AnimDoc.h"
#include "AnimView.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAnimView

IMPLEMENT_DYNCREATE(CAnimView, CView)

BEGIN_MESSAGE_MAP(CAnimView, CView)
	ON_COMMAND(ID_START_STOP, &CAnimView::OnStart)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_PLUS, &CAnimView::OnPlus)
	ON_COMMAND(ID_MINUS, &CAnimView::OnMinus)
	ON_WM_SIZE()
END_MESSAGE_MAP()

//CALLBACK Timer procedure

void CALLBACK ZfxTimerProc(HWND hWnd, UINT nMsg, UINT nIDEvent, DWORD dwTime)
{
	::SendMessage(hWnd, WM_TIMER, 0, 0);
}


// CAnimView construction/destruction

CAnimView::CAnimView() noexcept
{
	// TODO: add construction code here
	/*m_pBall = new CRect(20, 20, 20 + BALLSIZE, 20 + BALLSIZE);
	m_pBallPen = new CPen(PS_SOLID, 1, BLUE);
	m_pBallBrush = new CBrush(BLUE);

	m_nBallOffX = 3;
	m_nBallOffY = 1;*/

	srand(time(NULL));

	m_bStart = FALSE;
	m_nBallNum = 1;
	m_lBalls.push_back(new CBall(20,20,20+BALLSIZE,20+BALLSIZE,RGB(0,153,76), 3,1));

	m_pClientRect = new CRect(0, 0, 0, 0);
	
}

CAnimView::~CAnimView()
{
	/*delete m_pBall;
	delete m_pBallPen;
	delete m_pBallBrush;*/
	delete m_pClientRect;

	for (auto it = m_lBalls.begin(); it != m_lBalls.end(); it++)
	{
		delete *it;
	}

	m_lBalls.clear();

}

BOOL CAnimView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CAnimView drawing

void CAnimView::OnDraw(CDC* pDC)
{
	CAnimDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	/*CBrush* pOldBrush = pDC->SelectObject(m_pBallBrush);
	CPen* pOldPen = pDC->SelectObject(m_pBallPen);
	pDC->Ellipse(m_pBall);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);*/


	//------------------------------

	for (auto it = m_lBalls.begin(); it != m_lBalls.end(); it++)
	{
		(*it)->PaintBall(pDC);
	}



	//------------------------------

	/*CDC memDC;
	BOOL b = memDC.CreateCompatibleDC(pDC);
	ASSERT(b);

	CBitmap bmp;
	b = bmp.CreateCompatibleBitmap(pDC, m_pClientRect->Width(), m_pClientRect->Height());
	ASSERT(b);

	CBitmap* pOldBitmap = memDC.SelectObject(&bmp);
	memDC.FillSolidRect(m_pClientRect, RGB(230, 230, 230));

	CBrush* pOldBrush = memDC.SelectObject(m_pBallBrush);
	CPen* pOldPen = memDC.SelectObject(m_pBallPen);

	memDC.Ellipse(m_pBall);

	memDC.SelectObject(pOldBrush);
	memDC.SelectObject(pOldPen);

	b = pDC->BitBlt(0, 0, m_pClientRect->Width(), m_pClientRect->Height(), &memDC, 0, 0, SRCCOPY);
	ASSERT(b);


	memDC.SelectObject(pOldBitmap);
	bmp.DeleteObject();
	memDC.DeleteDC();*/
}


// CAnimView diagnostics

#ifdef _DEBUG
void CAnimView::AssertValid() const
{
	CView::AssertValid();
}

void CAnimView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAnimDoc* CAnimView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimDoc)));
	return (CAnimDoc*)m_pDocument;
}
#endif //_DEBUG


// CAnimView message handlers


void CAnimView::OnStart()
{
	// TODO: Add your command handler code here
	m_bStart = !m_bStart;

	//Podmiana przycisku
	CMainFrame* pFrame = (CMainFrame*)GetParentFrame();
	pFrame->ResetButton(m_bStart);
}


void CAnimView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	//m_nTimerID = SetTimer(WM_USER + 1, 20, NULL);
	m_nTimerID = SetTimer(WM_USER + 1, 20, ZfxTimerProc);
}


void CAnimView::OnDestroy()
{
	KillTimer(m_nTimerID);
	CView::OnDestroy();

	// TODO: Add your message handler code here
}


void CAnimView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (m_bStart)
	{
		/*if (m_pBall->top <= m_pClientRect->top || m_pBall->bottom >= m_pClientRect->bottom)
			m_nBallOffY = -m_nBallOffY;

		if (m_pBall->right >= m_pClientRect->right || m_pBall->left <= m_pClientRect->left)
			m_nBallOffX = -m_nBallOffX;
		
		m_pBall->OffsetRect(m_nBallOffX, m_nBallOffY);*/
		Invalidate();
	}
	CView::OnTimer(nIDEvent);
}


BOOL CAnimView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CView::OnEraseBkgnd(pDC);
	//return 1;//Nie czyszcze tla w ten sposob
}


void CAnimView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	GetClientRect(m_pClientRect);

	for (auto it = m_lBalls.begin(); it != m_lBalls.end(); it++)
	{
		(*it)->SetBoundRect(*m_pClientRect);
	}

	CView::OnPrepareDC(pDC, pInfo);
}


void CAnimView::OnPlus()
{
	//OBSLUGA DODANIA KULKI
	if (m_nBallNum <= 10)
	{	
		int ballsize = rand() % 100 + 20;
		int r = rand() % 256;
		int g = rand() % 256;
		int b = rand() % 256;
		int wek_x = r % 9 + 1;
		int wek_y = g % 9 + 1;
		m_lBalls.push_back(new CBall(20, 20, 20 + ballsize, 20 + ballsize, RGB(r,g,b), wek_x, wek_y));
		m_nBallNum++;
	}
}


void CAnimView::OnMinus()
{
	//OBSLUGA USUNIECIA KULKI
	if (m_nBallNum > 1)
	{
		delete m_lBalls.back();
		m_lBalls.pop_back();
		m_nBallNum--;
	}
}

