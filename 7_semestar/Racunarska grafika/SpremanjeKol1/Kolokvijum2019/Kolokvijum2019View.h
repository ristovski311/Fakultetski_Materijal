
// Kolokvijum2019View.h : interface of the CKolokvijum2019View class
//

#pragma once

#include "DImage.h"

class CKolokvijum2019View : public CView
{
protected: // create from serialization only
	CKolokvijum2019View() noexcept;
	DECLARE_DYNCREATE(CKolokvijum2019View)

// Attributes
public:
	CKolokvijum2019Doc* GetDocument() const;

	DImage* body1;
	DImage* arm1;
	DImage* arm2;
	DImage* leg1;
	DImage* leg2;
	DImage* background;
	
	float angleArm1;
	float angleArm2;
	float angleLeg1;
	float angleLeg2;
	float angleBody;

// Operations
public:
	void DrawBackground(CDC* pDC, CRect rc);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void DrawArm1(CDC* pDC);
	void DrawArm2(CDC* pDC);
	void DrawLeg1(CDC* pDC);
	void DrawLeg2(CDC* pDC);
	void DrawBody1(CDC* pDC);
	void DrawTransformer(CDC* pDC);

	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);

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
	virtual ~CKolokvijum2019View();
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

#ifndef _DEBUG  // debug version in Kolokvijum2019View.cpp
inline CKolokvijum2019Doc* CKolokvijum2019View::GetDocument() const
   { return reinterpret_cast<CKolokvijum2019Doc*>(m_pDocument); }
#endif

