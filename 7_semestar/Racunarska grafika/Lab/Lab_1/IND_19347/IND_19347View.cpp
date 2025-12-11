
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

#define GSS 25 //GSS - Grid square side duzina stranice kvadrata u gridu
#define TORAD 3.14159265358979323846 / 180.0


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
	grid = CRect(0, 0, 500, 500);
	show_grid = false;
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

void CIND19347View::Grid(CDC* pdc, CRect grid)
{
	CPen* newpen = new CPen(PS_COSMETIC, 1, RGB(255, 255, 255));
	CPen* oldpen = pdc->SelectObject(newpen);

	//Vertikalne linije

	int x, y;

	for (int i = 0; i < 21; i++)
	{
		x = i * GSS;
		y = grid.top;
		pdc->MoveTo(x, y);
		y = grid.bottom;
		pdc->LineTo(x, y);
	}

	//Horizontalne linije - ova dva iscrtavanja naravno mogu u jednoj for petlji, ali ovako je citljivije i lakse za razumevanje

	for (int i = 0; i < 21; i++)
	{
		y = i * GSS;
		x = grid.right;
		pdc->MoveTo(x, y);
		x = grid.left;
		pdc->LineTo(x, y);
	}

	pdc->SelectObject(oldpen);
	delete newpen;
}


void CIND19347View::DrawRegularPolygon(CDC* pdc, int cx, int cy, int r, int n, float rotAngle)
{
	POINT* pts = new CPoint[n];
	int x = 0, y = 0;

	double angle = (360 / n) * TORAD;

	for (int i = 0; i < n; i++)
	{
		x = (int)(cx + r * cos(i * angle + rotAngle * TORAD));
		y = (int)(cy + r * sin(i * angle + rotAngle * TORAD));
		pts[i] = CPoint(x, y);
	}

	CBrush* oldbrush = (CBrush*)pdc->SelectStockObject(NULL_BRUSH);

	pdc->Polygon(pts, n);

	pdc->SelectObject(oldbrush);

	delete pts;
}

//25354 - sifra za zadatak


// CIND19347View drawing

void CIND19347View::OnDraw(CDC* pdc)
{
	CIND19347Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CPen* newpen = new CPen(PS_NULL, 1, RGB(0, 0, 0));
	CPen* oldpen = pdc->SelectObject(newpen);

	CBrush* newbrush = new CBrush(RGB(200, 200, 200));
	CBrush* oldbrush = pdc->SelectObject(newbrush);

	//Sivi kvadrat po kom se crta

	pdc->Rectangle(grid);

	pdc->SelectObject(oldbrush);
	pdc->SelectObject(oldpen);

	delete(newpen);
	delete(newbrush);

	///
	//Crtanje primitiva (GS = Grid square - za lakse izracunavanje koordinata temena)
	///

	//Olovka je za sve ista (osim za pravilne poligone):
	LOGBRUSH lb;
	lb.lbStyle = BS_SOLID;
	lb.lbColor = RGB(0, 255, 0);
	newpen = new CPen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_SQUARE | PS_JOIN_ROUND, 5, &lb);

	oldpen = pdc->SelectObject(newpen);

	//Zeleni Poligon: T0(5.5,10) T1(10,10) T2(7.7,7.7) T3(7.7,12.2)

	newbrush = new CBrush(RGB(0, 128, 0));
	pdc->SelectObject(newbrush);

	POINT pts_zeleni[4] = {
		CPoint(GSS * 5.5, GSS * 10),
		CPoint(GSS * 7.7, GSS * 7.7),
		CPoint(GSS * 10, GSS * 10),
		CPoint(GSS * 7.7, GSS * 12.2)
	};

	pdc->Polygon(pts_zeleni, 4);

	pdc->SelectObject(oldbrush);
	delete(newbrush);

	//Ljubicasti trougao: T0(10,14.5) T1(7.7, 12.2) T2(12.2.12.2)

	newbrush = new CBrush(RGB(255, 0, 255));
	oldbrush = pdc->SelectObject(newbrush);

	POINT pts_ljubicasti[3] = {
		CPoint(GSS * 10, GSS * 14.5),
		CPoint(GSS * 7.7, GSS * 12.2),
		CPoint(GSS * 12.2, GSS * 12.2)
	};

	pdc->Polygon(pts_ljubicasti, 3);

	pdc->SelectObject(oldbrush);
	delete(newbrush);

	//Crveni Paralelogram: T0(10,10) T1(14.5,10) T3(7.7, 12.2) T4(12.2.12.2)

	newbrush = new CBrush(RGB(255, 0, 0));
	oldbrush = pdc->SelectObject(newbrush);

	POINT pts_paralelogram[4] = {
		CPoint(GSS * 10,GSS * 10),
		CPoint(GSS * 14.5,GSS * 10),
		CPoint(GSS * 12.2,GSS * 12.2),
		CPoint(GSS * 7.7,GSS * 12.2)
	};

	pdc->Polygon(pts_paralelogram, 4);

	pdc->SelectObject(oldbrush);
	delete(newbrush);


	//Narandzasti trougao: T0(10,5.5) T1(10,10) T2(7.7,7.7)

	newbrush = new CBrush(RGB(255, 165, 0));
	oldbrush = pdc->SelectObject(newbrush);

	POINT pts_narandzasti[3] = {
		CPoint(GSS * 10, GSS * 5.5),
		CPoint(GSS * 10, GSS * 10),
		CPoint(GSS * 7.7, GSS * 7.7)
	};

	pdc->Polygon(pts_narandzasti, 3);

	pdc->SelectObject(oldbrush);
	delete(newbrush);

	//Beli trougao: T0(10,5.5) T1(14.5,1) T2(14.5,10)

	newbrush = new CBrush(HS_HORIZONTAL, RGB(0, 0, 128));
	oldbrush = pdc->SelectObject(newbrush);

	POINT pts_beli[3] = {
		CPoint(GSS * 10, GSS * 5.5),
		CPoint(GSS * 14.5, GSS * 1),
		CPoint(GSS * 14.5, GSS * 10)
	};

	pdc->Polygon(pts_beli, 3);

	pdc->SelectObject(oldbrush);
	delete(newbrush);

	//Zuti trougao: T0(10,10) T1(10,5.5) T2(14.5,10)

	newbrush = new CBrush(RGB(255, 255, 0));
	oldbrush = pdc->SelectObject(newbrush);

	POINT pts_zuti[3] = {
		CPoint(GSS * 10, GSS * 10),
		CPoint(GSS * 10, GSS * 5.5),
		CPoint(GSS * 14.5, GSS * 10)
	};

	pdc->Polygon(pts_zuti, 3);

	pdc->SelectObject(oldbrush);
	delete(newbrush);

	//Rozi trougao: T0(10,14.5) T1(14,5,10) T2(14.5,19)

	newbrush = new CBrush(RGB(255, 192, 203));
	oldbrush = pdc->SelectObject(newbrush);

	POINT pts_rozi[3] = {
		CPoint(GSS * 10, GSS * 14.5),
		CPoint(GSS * 14.5, GSS * 10),
		CPoint(GSS * 14.5, GSS * 19)
	};

	pdc->Polygon(pts_rozi, 3);

	pdc->SelectObject(oldbrush);
	delete(newbrush);

	//Na kraju iscrtavanja osnovnih primitiva:
	pdc->SelectObject(oldpen);
	delete(newpen);

	//
	//Iscrtavanje pravilnih poligona:
	//

	LOGBRUSH lb2;
	lb2.lbColor = RGB(0, 180, 0);
	lb2.lbStyle = BS_SOLID;

	newpen = new CPen(PS_GEOMETRIC | PS_SOLID | PS_ENDCAP_FLAT | PS_JOIN_ROUND, 3, &lb2);
	oldpen = pdc->SelectObject(newpen);

	//Osmougao u narandzastom trouglu:	

	DrawRegularPolygon(pdc, 9 * GSS, 7.8 * GSS, 15, 8, 50);

	//Pentagon u belom trouglu:

	DrawRegularPolygon(pdc, 12.5 * GSS, 5.5 * GSS, 25 , 5, 0);

	//Kvadrat u roze trouglu:

	DrawRegularPolygon(pdc, 12.5 * GSS, 14.5 * GSS, 25, 4, 0);

	//Sedmougao u ljubicastom trouglu:

	DrawRegularPolygon(pdc, 9.9 * GSS, 13.2 * GSS, 13, 7, 0);

	//Sestougao u zutom trouglu:

	DrawRegularPolygon(pdc, 11.3 * GSS, 8.5 * GSS, 20 , 6, 0);

	pdc->SelectObject(oldpen);
	delete(newpen);

	//Prikaz grid-a
	if (show_grid)
	{
		Grid(pdc, grid);
	}
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
	CRgn region;
	region.CreateRectRgn(grid.left, grid.top, grid.right, grid.bottom);
	show_grid = !show_grid;
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
