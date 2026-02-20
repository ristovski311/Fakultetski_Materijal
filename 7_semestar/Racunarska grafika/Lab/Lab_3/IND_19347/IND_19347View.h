
// IND_19347View.h : interface of the CIND19347View class
//

#pragma once
#include "DImage.h"	

#define GSS 25

class CIND19347View : public CView
{
protected: // create from serialization only
	CIND19347View() noexcept;
	DECLARE_DYNCREATE(CIND19347View)
	CRect grid;
	bool showGrid;
	int puzzleAngle[9] = { 0,0,0,0,0,0,0,0,0 };
	int puzzleTranslateY[9] = { 1,1,1,7*GSS,7 * GSS,7 * GSS, 13 * GSS,13 * GSS,13 * GSS };
	int puzzleTranslateX[9] = { 1,7 * GSS,13 * GSS,1,7 * GSS,13 * GSS,1,7 * GSS, 13 * GSS };
	bool puzzleMirrorRelToX[9] = { false, false, false, false, false, false, false ,false, false };
	bool puzzleMirrorRelToY[9] = { false, false, false, false, false, false, false ,false, false };
	int currentPuzzle;
	bool showNumbersOnPuzzles;

// Attributes
public:
	CIND19347Doc* GetDocument() const;
	DImage backgroundImage;
	DImage armImage;
	DImage basketImage;


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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);

	void DrawGrid(CDC* pDC);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply); 
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Mirror(CDC* pDC, bool mx, bool my, bool rightMultiply);
	void DrawPuzzleMovable(CDC* pDC);
	void DrawPuzzle(CDC* pDC);
	void FilterPuzzlePiece(CBitmap* slika, bool r, bool g, bool b, COLORREF dontFilterColor);
	void RemoveBkgFromPuzzlePiece(CDC* pDC, DImage* img, bool r, bool g, bool b);
	void DrawSiglePuzzle(CDC* pDC, int dX, int dY, float angle, bool mirror_x, bool mirror_y, CString path, bool r, bool g, bool b);

// Implementation
public:
	virtual ~CIND19347View();
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

#ifndef _DEBUG  // debug version in IND_19347View.cpp
inline CIND19347Doc* CIND19347View::GetDocument() const
   { return reinterpret_cast<CIND19347Doc*>(m_pDocument); }
#endif

