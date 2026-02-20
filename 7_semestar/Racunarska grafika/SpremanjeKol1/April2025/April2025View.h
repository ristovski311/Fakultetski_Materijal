
// April2025View.h : interface of the CApril2025View class
//

#pragma once
#include "DImage.h"


class CApril2025View : public CView
{
protected: // create from serialization only
	CApril2025View() noexcept;
	DECLARE_DYNCREATE(CApril2025View)

// Attributes
public:
	CApril2025Doc* GetDocument() const;
	float sunbrellaAngle = 0;
	DImage* background;

// Operations
public:
	void DrawBackground(CDC* pdc);
	void Translate(CDC* pdc, int x, int y, bool right);
	void Rotate(CDC* pdc, double angle, bool right);
	void DrawSun(CDC* pdc, int r);
	void DrawSunbrella(CDC* pdc,int size, int r, int nElem, COLORREF* aClrFill, COLORREF clrLine);
	void DrawSunbed(CDC* pdc, int size, int nElem, COLORREF* aClrFill, COLORREF clrLine);
	void DrawSunbeds(CDC* pdc, int size, int nElem, COLORREF* aClrFill, COLORREF clrLine, int n, int m, CPoint ptStart);


// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CApril2025View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pdc);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in April2025View.cpp
inline CApril2025Doc* CApril2025View::GetDocument() const
   { return reinterpret_cast<CApril2025Doc*>(m_pDocument); }
#endif

