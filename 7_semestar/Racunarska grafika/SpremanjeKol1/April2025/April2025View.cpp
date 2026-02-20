
// April2025View.cpp : implementation of the CApril2025View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "April2025.h"
#endif

#include "April2025Doc.h"
#include "April2025View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TORAD 3.141592/180
// CApril2025View

IMPLEMENT_DYNCREATE(CApril2025View, CView)

BEGIN_MESSAGE_MAP(CApril2025View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CApril2025View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CApril2025View construction/destruction

CApril2025View::CApril2025View() noexcept
{
	background = new DImage();
	background->Load(L"beach.jpg");
}

CApril2025View::~CApril2025View()
{
	if (background)
		delete background;
}

BOOL CApril2025View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CApril2025View::Translate(CDC* pdc, int x, int y, bool right) {
	XFORM matrix;
	matrix.eDx = x;
	matrix.eDy = y;
	matrix.eM11 = 1;
	matrix.eM12 = 0;
	matrix.eM21 = 0;
	matrix.eM22 = 1;

	if (right)
		pdc->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);

}

void CApril2025View::Rotate(CDC* pdc, double angle, bool right) {
	XFORM matrix;
	matrix.eDx = 0;
	matrix.eDy = 0;
	matrix.eM11 = cos(angle*TORAD);
	matrix.eM12 = sin(angle * TORAD);
	matrix.eM21 = -sin(angle * TORAD);
	matrix.eM22 = cos(angle * TORAD);

	if (right)
		pdc->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);
}


void CApril2025View::DrawBackground(CDC* pdc) {
	CRect client;
	GetClientRect(&client);
	
	background->Draw(pdc, CRect(0, 0, background->Width(), background->Height()), client);
}

void CApril2025View::DrawSun(CDC* pdc, int r) {

	XFORM oldmatrix;
	pdc->GetWorldTransform(&oldmatrix);

	CPen* newpen = new CPen(PS_COSMETIC, 1, RGB(255, 255,0));
	CBrush* newbrush = new CBrush(RGB(255, 255, 0));

	CPen* oldpen = pdc->SelectObject(newpen);
	CBrush* oldbrush = pdc->SelectObject(newbrush);

	//Sunce - krug
	pdc->Ellipse(CRect(-r / 2, -r / 2, r / 2, r / 2));

	pdc->SelectObject(oldbrush);
	delete newbrush;
	newbrush = new CBrush(RGB(255 * 0.9, 255 * 0.9, 0));
	pdc->SelectObject(newbrush);

	//Sunce - 12 ljutih gusara oko njega

	int osnovica = 0.3 * r;
	int visina = 0.5 * r;
	int offset = 0.15 * r;

	POINT pts[] = {
		CPoint(-osnovica / 2, -(r / 2 + offset)), //dole levo
		CPoint(osnovica / 2, -(r / 2 + offset)), //dole desno
		CPoint(0, -(r / 2 + offset + visina)) //vrh
	};

	for (int alpha = 0; alpha < 360; alpha += 360 / 12)
	{
		Rotate(pdc, alpha, false);

		pdc->Polygon(pts, 3);

		Rotate(pdc, -alpha, false);
	}

	
	pdc->SetWorldTransform(&oldmatrix);
	pdc->SelectObject(oldbrush);
	delete newbrush;
	pdc->SelectObject(oldpen);
	delete newpen;
}


void CApril2025View::DrawSunbrella(CDC* pdc,int size, int r, int nElem, COLORREF* aClrFill, COLORREF clrLine) {

	XFORM matrix;
	pdc->GetWorldTransform(&matrix);

	CPen* pen = new CPen(PS_COSMETIC, 1, clrLine);
	CPen* oldpen = pdc->SelectObject(pen);

	CBrush* brush0 = new CBrush(aClrFill[0]);
	CBrush* brush1 = new CBrush(aClrFill[1]);
	CBrush* whitebrush = new CBrush(RGB(255,255,255));
	CBrush* oldbrush = pdc->SelectObject(brush0);

	int precnikManji = size / 4;
	int precnikVeci = size / 2;
	float step = 360 / nElem;
	int squareSide = 2 * r * sin(step * TORAD / 2);

	float angle1 = (-180 - step) / 2;
	float angle2 = (-180 - step) / 2 + step;

	int x1 = r * cos(angle1 * TORAD);
	int y1 = r * sin(angle1 * TORAD);
	int x2 = r * cos(angle2 * TORAD);
	int y2 = r * sin(angle2 * TORAD);

	float angle = 0;
	int oldArcDir = pdc->SetArcDirection(AD_COUNTERCLOCKWISE);
	Rotate(pdc, sunbrellaAngle, false);
	for (int i = 0; i < nElem; i++)
	{
		if (i % 2 == 0)
			pdc->SelectObject(brush0);
		else
			pdc->SelectObject(brush1);

		Rotate(pdc, angle, false);
		pdc->BeginPath();

		pdc->MoveTo(0, 0);
		pdc->LineTo(x1, y1); //LEFT
		pdc->MoveTo(0, 0);
		pdc->LineTo(x2, y2); //RIGHT
		pdc->ArcTo(CRect(x1, y1 - squareSide / 2, x2, y2 + squareSide / 2), CPoint(x2, y2), CPoint(x1, y1));
		pdc->MoveTo(0, 0);

		pdc->EndPath();

		pdc->StrokeAndFillPath();

		Rotate(pdc, -angle, false);

		angle += step;
	}

	angle = 0;
	for (int i = 0; i < nElem; i++)
	{

		Rotate(pdc, angle, false);

		pdc->SelectObject(whitebrush);
		pdc->Ellipse(x1 - precnikManji/2, y1 - precnikManji/2, x1 + precnikManji/2, y1 + precnikManji/2);

		Rotate(pdc, -angle, false);

		angle += step;
	}

	pdc->Ellipse(0 - precnikVeci / 2, 0 - precnikVeci / 2, 0 + precnikVeci / 2, 0 + precnikVeci / 2);
	pdc->Ellipse(0 - precnikManji / 2, 0 - precnikManji / 2, 0 + precnikManji / 2, 0 + precnikManji / 2);
	Rotate(pdc, -sunbrellaAngle, false);


	pdc->SetArcDirection(oldArcDir);
	pdc->SetWorldTransform(&matrix);
}
void DrawSunbed(CDC* pdc, int size, int nElem, COLORREF* aClrFill, COLORREF clrLine) {

}
void DrawSunbeds(CDC* pdc, int size, int nElem, COLORREF* aClrFill, COLORREF clrLine, int n, int m, CPoint ptStart) {

}

void CApril2025View::DrawSunbed(CDC* pdc, int size, int nElem, COLORREF* aClrFill, COLORREF clrLine) {

	XFORM matrix;
	pdc->GetWorldTransform(&matrix);
	



	pdc->SetWorldTransform(&matrix);

}


// CApril2025View drawing

void CApril2025View::OnDraw(CDC* pdc)
{
	CApril2025Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CRect client;
	GetClientRect(&client);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pdc);

	CBitmap memBM;
	memBM.CreateCompatibleBitmap(pdc, client.Width(), client.Height());

	CBitmap* oldbm = memDC->SelectObject(&memBM);
	int oldGM = memDC->SetGraphicsMode(GM_ADVANCED);

	//Crtanje u memDC
	{
		XFORM matrix;
		memDC->GetWorldTransform(&matrix);

		DrawBackground(memDC);
		
		Translate(memDC, client.Width() / 2, client.Height() / 2, false);
		//DrawSun(memDC, 120);
		COLORREF clrs[] = { RGB(224,224,200), RGB(245, 127,127) };
		DrawSunbrella(memDC, 100, 80,6, clrs, RGB(30,30,30));
		Translate(memDC, -client.Width() / 2, -client.Height() / 2, false);


		memDC->SetWorldTransform(&matrix);
	}

	pdc->BitBlt(0, 0, client.Width(), client.Height(), memDC, 0, 0, SRCCOPY);

	memDC->SelectObject(oldbm);
	memDC->SetGraphicsMode(oldGM);
	delete memDC;
}






















// CApril2025View printing


void CApril2025View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CApril2025View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CApril2025View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CApril2025View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CApril2025View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CApril2025View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CApril2025View diagnostics

#ifdef _DEBUG
void CApril2025View::AssertValid() const
{
	CView::AssertValid();
}

void CApril2025View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CApril2025Doc* CApril2025View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CApril2025Doc)));
	return (CApril2025Doc*)m_pDocument;
}
#endif //_DEBUG


// CApril2025View message handlers

afx_msg BOOL CApril2025View::OnEraseBkgnd(CDC* pdc) {

	return TRUE;
}

void CApril2025View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'Q')
		sunbrellaAngle += 10;
	Invalidate(TRUE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
