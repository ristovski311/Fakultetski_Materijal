
// KolokvijumB2024View.h : interface of the CKolokvijumB2024View class
//

#pragma once
#include "DImage.h"

class CKolokvijumB2024View : public CView
{
protected: // create from serialization only
	CKolokvijumB2024View() noexcept;
	DECLARE_DYNCREATE(CKolokvijumB2024View)

// Attributes
public:
	CKolokvijumB2024Doc* GetDocument() const;
	DImage backgroundImage;
	DImage armImage;
	DImage basketImage;

	float angleFirstArm;
	float angleBase;
	float baseMovement;
	float angleCenter;

// Operations
public:

	void DrawBackground(CDC* pdc);
	void DrawImageTransparent(CDC* pDC, DImage* pImage);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void DrawArm(CDC* pDC);
	void DrawBasket(CDC* pDC, int r);
	void DrawBasketCouple(CDC* pDC, int l, int r, float angle);
	void DrawPlatform(CDC* pDC, int l, int r, double angle);
	void DrawCarousel(CDC* pDC, int h, int r, double offset, double alpha, double beta, double angle);

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
	virtual ~CKolokvijumB2024View();
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

#ifndef _DEBUG  // debug version in KolokvijumB2024View.cpp
inline CKolokvijumB2024Doc* CKolokvijumB2024View::GetDocument() const
   { return reinterpret_cast<CKolokvijumB2024Doc*>(m_pDocument); }
#endif

