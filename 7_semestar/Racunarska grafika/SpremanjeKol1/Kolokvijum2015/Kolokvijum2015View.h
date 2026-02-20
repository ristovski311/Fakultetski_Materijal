
// Kolokvijum2015View.h : interface of the CKolokvijum2015View class
//

#pragma once
#include "DImage.h"


class CKolokvijum2015View : public CView
{
protected: // create from serialization only
	CKolokvijum2015View() noexcept;
	DECLARE_DYNCREATE(CKolokvijum2015View)

// Attributes
public:
	CKolokvijum2015Doc* GetDocument() const;

	DImage* background;
	float mouthAngle;
	int dx;
	int dy;
	int pacmanPosX;
	int pacmanPosY;
	bool isUp;
	bool isDown;
	bool isLeft;
	bool isRight;

// Operations
public:
	void Translate(CDC* pdc, int dx, int dy, bool rightMul);
	void Rotate(CDC* pdc, int angle, bool rightMul);
	void Scale(CDC* pdc, int sx, int sy, bool rightMul);

	void DrawGhost(CDC* pDC, CRect rect);
	void DrawPacman(CDC* pDC, CRect rect, float angle);
	void DrawBackground(CDC* pdc);

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
	virtual ~CKolokvijum2015View();
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

#ifndef _DEBUG  // debug version in Kolokvijum2015View.cpp
inline CKolokvijum2015Doc* CKolokvijum2015View::GetDocument() const
   { return reinterpret_cast<CKolokvijum2015Doc*>(m_pDocument); }
#endif

