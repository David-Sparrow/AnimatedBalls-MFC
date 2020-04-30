
// AnimView.h : interface of the CAnimView class
//

#pragma once
#include <list>
#include "CBall.h"
#include <time.h>

class CAnimView : public CView
{
protected: // create from serialization only
	CAnimView() noexcept;
	DECLARE_DYNCREATE(CAnimView)

// Attributes
public:
	CAnimDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CAnimView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnStart();
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();

private: 
	UINT_PTR m_nTimerID;
	//CRect* m_pBall;
	//CPen* m_pBallPen;
	//CBrush* m_pBallBrush;
	//int m_nBallOffX;
	//int m_nBallOffY;
	bool m_bStart;
	CRect* m_pClientRect;

	std::list <CBall*> m_lBalls;
	int m_nBallNum;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnPrepareDC(CDC* pDC, CPrintInfo* pInfo = NULL);
	afx_msg void OnPlus();
	afx_msg void OnMinus();
};

#ifndef _DEBUG  // debug version in AnimView.cpp
inline CAnimDoc* CAnimView::GetDocument() const
   { return reinterpret_cast<CAnimDoc*>(m_pDocument); }
#endif

