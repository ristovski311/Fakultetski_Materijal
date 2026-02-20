
// Kolokvijum2022View.h : interface of the CKolokvijum2022View class
//

#pragma once

#include "DImage.h"


class CKolokvijum2022View : public CView
{
protected: // create from serialization only
	CKolokvijum2022View() noexcept;
	DECLARE_DYNCREATE(CKolokvijum2022View)

// Attributes
public:
	CKolokvijum2022Doc* GetDocument() const;
	DImage* base;
	DImage* arm1;
	DImage* arm2;
	DImage* head;
	DImage* pozadina;
	DImage* baseShadow;
	DImage* arm1Shadow;
	DImage* arm2Shadow;
	DImage* headShadow;
	float arm1Angle;
	float arm2Angle;
	float headAngle;

// Operations
public:
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void DrawBackground(CDC* pDC);
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void DrawLampBase(CDC* pDC, bool bIsShadow);
	void DrawLampArm1(CDC* pDC, bool bIsShadow);
	void DrawLampArm2(CDC* pDC, bool bIsShadow);
	void DrawLampHead(CDC* pDC, bool bIsShadow);
	void DrawLamp(CDC* pDC, bool bIsShadow);
	void DrawLampShadow(CDC* pDC);

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
	virtual ~CKolokvijum2022View();
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

#ifndef _DEBUG  // debug version in Kolokvijum2022View.cpp
inline CKolokvijum2022Doc* CKolokvijum2022View::GetDocument() const
   { return reinterpret_cast<CKolokvijum2022Doc*>(m_pDocument); }
#endif

