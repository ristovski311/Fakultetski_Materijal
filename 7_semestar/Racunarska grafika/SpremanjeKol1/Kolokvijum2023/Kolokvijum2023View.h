
// Kolokvijum2023View.h : interface of the CKolokvijum2023View class
//

#pragma once
#include "DImage.h"

class CKolokvijum2023View : public CView
{
protected: // create from serialization only
	CKolokvijum2023View() noexcept;
	DECLARE_DYNCREATE(CKolokvijum2023View)

// Attributes
public:
	CKolokvijum2023Doc* GetDocument() const;
	DImage glava;
	DImage nadkolenica;
	DImage podkolenica;
	DImage podlaktica;
	DImage nadlaktica;
	DImage saka;
	DImage stopalo;
	DImage telo;
	DImage pozadina;

	float podlakticaUgao;
	float nadlakticaUgao;
	float sakaUgao;
	float robotUgao;
	float robotScale;

// Operations
public:
	void DrawImgTransparent(CDC* pDC, DImage* pImage);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void DrawHalf(CDC* pDC);
	void DrawBackground(CDC* pDC);
	void DrawHead(CDC* pDC);
	void DrawRobot(CDC* pDC);

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
	virtual ~CKolokvijum2023View();
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

#ifndef _DEBUG  // debug version in Kolokvijum2023View.cpp
inline CKolokvijum2023Doc* CKolokvijum2023View::GetDocument() const
   { return reinterpret_cast<CKolokvijum2023Doc*>(m_pDocument); }
#endif

