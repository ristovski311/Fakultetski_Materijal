
// Jun2025View.h : interface of the CJun2025View class
//

#pragma once
#include "DImage.h"


class CJun2025View : public CView
{
protected: // create from serialization only
	CJun2025View() noexcept;
	DECLARE_DYNCREATE(CJun2025View)

// Attributes
public:
	CJun2025Doc* GetDocument() const;

	DImage* background;
	float ferrisAngle;

// Operations
public:
	void DrawBackground(CDC* pDC);
	void Translate(CDC* pDC, double x, double y, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void DrawCabin(CDC* pDC, int w, int d, COLORREF clr);
	void DrawWheelPetal(CDC* pDC, int r, int d, int n, COLORREF clr);
	void DrawFerrisWheel(CDC* pDC, int r, int d, int n, COLORREF clr, CPoint prCenter, int f, CString str);

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
	virtual ~CJun2025View();
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

#ifndef _DEBUG  // debug version in Jun2025View.cpp
inline CJun2025Doc* CJun2025View::GetDocument() const
   { return reinterpret_cast<CJun2025Doc*>(m_pDocument); }
#endif

