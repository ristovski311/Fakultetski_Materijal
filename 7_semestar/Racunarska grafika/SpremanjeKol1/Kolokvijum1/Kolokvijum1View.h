
// Kolokvijum1View.h : interface of the CKolokvijum1View class
//

#pragma once


class CKolokvijum1View : public CView
{
protected: // create from serialization only
	CKolokvijum1View() noexcept;
	DECLARE_DYNCREATE(CKolokvijum1View)
	float angle;

// Attributes
public:
	CKolokvijum1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
public:
	void Rotate(CDC* pdc, float angle, bool rightMul);
	void Translate(CDC* pdc, int dx, int dy, bool rightMul);
	void Scale(CDC* pdc, float sX, float sY, bool rightMul);
	void DrawArcSpotsPattern(CDC* pdc, int rows, int cols, float dX, float dY, float alpha, HENHMETAFILE mf, int size, COLORREF colText);


// Implementation
public:
	virtual ~CKolokvijum1View();
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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in Kolokvijum1View.cpp
inline CKolokvijum1Doc* CKolokvijum1View::GetDocument() const
   { return reinterpret_cast<CKolokvijum1Doc*>(m_pDocument); }
#endif

