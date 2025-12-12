
// IND_19347View.h : interface of the CIND19347View class
//

#pragma once


class CIND19347View : public CView
{
protected: // create from serialization only
	CIND19347View() noexcept;
	DECLARE_DYNCREATE(CIND19347View)
	CRect grid;
	bool show_grid;
	float cactus_angle;
	float cactus_part_angle;
	HENHMETAFILE mf_dark_part;
	HENHMETAFILE mf_light_part;
	CRect initialMetafileRectangle;

// Attributes
public:
	CIND19347Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	void ShowGrid(CDC* pdc);
	void Translate(CDC* pdc, float dX, float dY, bool rightMultiply);
	void Scale(CDC* pdc, float sX, float sY, bool rightMultiply);
	void Rotate(CDC* pdc, float angle, bool rightMultiply);
	void DrawFigure(CDC* pdc);

	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

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

