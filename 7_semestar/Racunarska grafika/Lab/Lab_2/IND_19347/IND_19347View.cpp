
// IND_19347View.cpp : implementation of the CIND19347View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "IND_19347.h"
#endif

#include "IND_19347Doc.h"
#include "IND_19347View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define GSS 25

// CIND19347View

IMPLEMENT_DYNCREATE(CIND19347View, CView)

BEGIN_MESSAGE_MAP(CIND19347View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CIND19347View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CIND19347View construction/destruction

CIND19347View::CIND19347View() noexcept
{
	grid = new CRect(0, 0, 500, 500);
	show_grid = false;
	// TODO: add construction code here

}

CIND19347View::~CIND19347View()
{
}

BOOL CIND19347View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CIND19347View drawing

void CIND19347View::ShowGrid(CDC* pdc) {
	
	int x, y;

	CPen* newpen = new CPen(PS_COSMETIC, 1, RGB(250, 250, 250));
	CPen* oldpen = pdc->SelectObject(newpen);

	CBrush* oldbrush = (CBrush*)pdc->SelectStockObject(NULL_BRUSH);

	for (int i = 0; i < 21; i++) {
		pdc->MoveTo(0, GSS * i);
		pdc->LineTo(500, GSS * i);
		pdc->MoveTo(GSS * i, 0);
		pdc->LineTo(GSS * i, 500);
	}

	pdc->SelectObject(oldpen);
	pdc->SelectObject(oldbrush);

	delete newpen;
}

void CIND19347View::OnDraw(CDC* pdc)
{
	CIND19347Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPen* newpen;
	CPen* oldpen = (CPen*)pdc->SelectStockObject(NULL_PEN);

	CBrush* newbrush = new CBrush(RGB(135, 206, 235));
	CBrush* oldbrush = pdc->SelectObject(newbrush);

	//Plava pozadina

	pdc->Rectangle(grid);

	pdc->SelectObject(oldpen);
	pdc->SelectObject(oldbrush);

	delete newbrush;

	//KAKTUSSS

	HENHMETAFILE mf_dark_part = GetEnhMetaFile(L"C:\\gitHub\\Fakultetski_Materijal\\7_semestar\\Racunarska grafika\\Lab\\Lab_2\\RESURSI\\cactus_part.emf");
	HENHMETAFILE mf_light_part = GetEnhMetaFile(L"C:\\gitHub\\Fakultetski_Materijal\\7_semestar\\Racunarska grafika\\Lab\\Lab_2\\RESURSI\\cactus_part_light.emf");
	if (!mf_dark_part)
	{
		AfxMessageBox(_T("Greska pri citanju dark metafajla!"));
		return;
	}
	else if (!mf_light_part)
	{
		AfxMessageBox(_T("Greska pri citanju light metafajla!"));
		return;
	}

	PlayEnhMetaFile(pdc->m_hDC, mf_dark_part, CRect(40,40,150,150));
	PlayEnhMetaFile(pdc->m_hDC, mf_light_part, CRect(300,300,390,390));

	DeleteEnhMetaFile(mf_dark_part);
	DeleteEnhMetaFile(mf_light_part);



	//SAKSIJA T1(7.5GSS, 17.2GSS) T2(12.5GSS, 18GSS)

	newbrush = new CBrush(RGB(222, 148, 0));
	oldbrush = pdc->SelectObject(newbrush);
	newpen = new CPen(PS_COSMETIC, 1, RGB(0, 0, 0));
	oldpen = pdc->SelectObject(newpen);

	pdc->Rectangle(7.5 * GSS, 17.2 * GSS, 12.5 * GSS, 18 * GSS);

	POINT pts[4] = {
		CPoint(8 * GSS,18 * GSS),
		CPoint(12 * GSS,18 * GSS),
		CPoint(11.5 * GSS,20 * GSS),
		CPoint(8.5 * GSS,20 * GSS)
	};

	pdc->Polygon(pts, 4);

	pdc->SelectObject(oldpen);
	pdc->SelectObject(oldbrush);

	delete newpen;
	delete newbrush;

	//Prikaz grid-a

	if (show_grid)
		ShowGrid(pdc);
	// TODO: add draw code for native data here
}


// CIND19347View printing


void CIND19347View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CIND19347View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIND19347View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIND19347View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CIND19347View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CIND19347View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CIND19347View diagnostics

#ifdef _DEBUG
void CIND19347View::AssertValid() const
{
	CView::AssertValid();
}

void CIND19347View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIND19347Doc* CIND19347View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIND19347Doc)));
	return (CIND19347Doc*)m_pDocument;
}
#endif //_DEBUG


// CIND19347View message handlers


void CIND19347View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CRgn rgn;
	rgn.CreateRectRgn(grid.left, grid.top, grid.right, grid.bottom);
	show_grid = !show_grid;
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
