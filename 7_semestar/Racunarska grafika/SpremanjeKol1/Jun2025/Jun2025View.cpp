
// Jun2025View.cpp : implementation of the CJun2025View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Jun2025.h"
#endif

#include "Jun2025Doc.h"
#include "Jun2025View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TORAD 3.141592/180

// CJun2025View

IMPLEMENT_DYNCREATE(CJun2025View, CView)

BEGIN_MESSAGE_MAP(CJun2025View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CJun2025View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CJun2025View construction/destruction

CJun2025View::CJun2025View() noexcept
{
	background = new DImage();
	background->Load(L"background.jpg");
	ferrisAngle = 0;
}

CJun2025View::~CJun2025View()
{
}

BOOL CJun2025View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CJun2025View::DrawBackground(CDC* pDC) {

	CRect client;
	GetClientRect(&client);

	background->Draw(pDC, CRect(0, 0, background->Width(), background->Height()), client);
}

void CJun2025View::Translate(CDC* pDC, double x, double y, bool rightMultiply) {
	XFORM matrix;
	matrix.eDx = x;
	matrix.eDy = y;
	matrix.eM11 = 1;
	matrix.eM12 = 0;
	matrix.eM21 = 0;
	matrix.eM22 = 1;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);

}
void CJun2025View::Rotate(CDC* pDC, float angle, bool rightMultiply) {
	XFORM matrix;
	matrix.eDx = 0;
	matrix.eDy = 0;
	matrix.eM11 = cos(angle*TORAD);
	matrix.eM12 = sin(angle * TORAD);
	matrix.eM21 = -sin(angle * TORAD);
	matrix.eM22 = cos(angle * TORAD);

	if (rightMultiply)
		pDC->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);
}

void CJun2025View::DrawCabin(CDC* pdc, int w, int d, COLORREF clr) {

	CPen* newpen = new CPen(PS_COSMETIC, d, clr);
	CBrush* newbrush = new CBrush(clr);
	CBrush* oldbrush = pdc->SelectObject(newbrush);
	CPen* oldpen = pdc->SelectObject(newpen);

	//Sajla na vrhu
	pdc->LineTo(0, w / 4);

	//Polukruzni dome
	int oldArcDir = pdc->SetArcDirection(AD_CLOCKWISE);
	pdc->Pie(CRect(-w / 2, w / 4, w / 2, w / 4 + w), CPoint(-w / 2, w / 4 + w / 2), CPoint(w / 2, w / 4 + w / 2));
	pdc->SetArcDirection(oldArcDir);

	//Dve sajle
	//Leva
	pdc->MoveTo(CPoint(-w / 2, w / 4 + w / 2));
	pdc->LineTo(CPoint(-w / 2, w / 4 + w));
	//Desna
	pdc->MoveTo(CPoint(w / 2, w / 4 + w / 2));
	pdc->LineTo(CPoint(w / 2, w / 4 + w));

	//Vracamo se u centar
	pdc->MoveTo(0, 0);

	int offsetForCabinBase = (w - (2.0 / 3) * w) / 2;

	//Kabina
	POINT pts[] = {
		CPoint(w / 2, w / 4 + w), //top right
		CPoint(-w / 2, w / 4 + w), //top left
		CPoint(-w / 2 + offsetForCabinBase, w / 4 + w + w / 2), // bottom left
		CPoint(w / 2 - offsetForCabinBase, w / 4 + w + w / 2) //bottom right
	};

	pdc->SelectObject(oldbrush);
	delete newbrush;
	newbrush = new CBrush(HS_BDIAGONAL, RGB(GetRValue(clr) * 0.7, GetGValue(clr) * 0.7, GetBValue(clr) * 0.7));
	pdc->SelectObject(newbrush);

	pdc->Polygon(pts, 4);



	pdc->SelectObject(oldbrush);
	delete newbrush;
	pdc->SelectObject(oldpen);
	delete newpen;
}


void CJun2025View::DrawWheelPetal(CDC * pDC, int r, int d, int n, COLORREF clr) {

	XFORM matrix;
	pDC->GetWorldTransform(&matrix);

	CPen* newpen = new CPen(PS_COSMETIC, 3 * d, clr);
	CPen* oldpen = pDC->SelectObject(newpen);
	CBrush* oldbrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	//Koncentricne kruznice
	float mini_r = 0.8 * r;
	float osovina_r = 0.1 * r;
	
	//Spoljasnja
	pDC->Ellipse(CRect(-r, -r, r, r));
	//Unutrasnja
	pDC->Ellipse(CRect(-mini_r, -mini_r, mini_r, mini_r));

	//Elipse lude
	pDC->SelectObject(oldpen);
	delete newpen;
	newpen = new CPen(PS_COSMETIC, d, clr);
	pDC->SelectObject(newpen);


	for (float alpha = 0; alpha < 360; alpha += 360 / n)
	{
		Rotate(pDC, alpha, false);

		pDC->Ellipse(CRect(-r/10, -r, r/10, r));

		Rotate(pDC, -alpha, false);
	}

	CBrush* newbrush = new CBrush(clr);
	pDC->SelectObject(newbrush);

	//Osovina
	pDC->Ellipse(CRect(-osovina_r, -osovina_r, osovina_r, osovina_r));

	pDC->SelectObject(oldbrush);
	pDC->SelectObject(oldpen);
	pDC->SetWorldTransform(&matrix);
}

void CJun2025View::DrawFerrisWheel(CDC* pDC, int r, int d, int n, COLORREF clr, CPoint ptCenter, int f, CString str) {

	XFORM matrix;
	pDC->GetWorldTransform(&matrix);

	CPen* newpen = new CPen(PS_COSMETIC, d, clr);
	CPen* oldpen = pDC->SelectObject(newpen);

	CBrush* oldbrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	CFont font;
	font.CreateFontW(f, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Verdana");
	CFont* oldfont = pDC->SelectObject(&font);
	COLORREF oldClrT = pDC->SetTextColor(clr);
	int oldBMode = pDC->SetBkMode(TRANSPARENT);

	POINT pts[] = {
		CPoint(0,0),
		CPoint(-0.4 * r, 1.6 * r),
		CPoint(0.4 * r, 1.6 * r)
	};


	//Sve pomeramo u ptCenter
	Translate(pDC, ptCenter.x, ptCenter.y, false);
	{
		//Osnovica = trougao
		pDC->Polygon(pts, 3);

		//Ferris wheel rotiramo za alpha
		Rotate(pDC, ferrisAngle, false);
		{
			//Wheel
			DrawWheelPetal(pDC, r, d, n, clr);


			//Kabine
			float step = 360 / n;
			int x, y;

			for (float alpha = step; alpha < 360; alpha += 2 * step)
			{
				x = r * cos(alpha*TORAD);
				y = r * sin(alpha*TORAD);

				Translate(pDC, x, y, false);

				Rotate(pDC, -ferrisAngle, false);
				DrawCabin(pDC, r/5, d, clr);
				Rotate(pDC, ferrisAngle, false);


				Translate(pDC, -x, -y, false);
			}
		}
		Rotate(pDC, -ferrisAngle, false);

		//Text iznad
		int chNum = str.GetLength();
		float step = 180 / chNum;
		float startAngle = 180;
		int x;
		int y;

		for (int i = 0; i < chNum; i++)
		{
			x = 1.8 * r * cos(startAngle * TORAD);
			y = 1.8 * r * sin(startAngle * TORAD);
			pDC->TextOutW(x, y, CString(str[i]));
			startAngle += step;
		}

	}
	Translate(pDC, -ptCenter.x, -ptCenter.y, false);

	pDC->SetBkMode(oldBMode);
	pDC->SelectObject(oldfont);
	pDC->SetTextColor(oldClrT);
	pDC->SelectObject(oldpen);
	pDC->SelectObject(oldbrush);
	pDC->SetWorldTransform(&matrix);
}



//Vreme: 1h 30min, ali sajla kabina nije ok






// CJun2025View drawing

void CJun2025View::OnDraw(CDC* pdc)
{
	CJun2025Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect client;
	GetClientRect(&client);

	CDC* memdc = new CDC();
	memdc->CreateCompatibleDC(pdc);

	CBitmap membm;
	membm.CreateCompatibleBitmap(pdc, client.Width(), client.Height());

	CBitmap* oldbm = memdc->SelectObject(&membm);
	int oldGM = memdc->SetGraphicsMode(GM_ADVANCED);


	//Crtanje u memddc
	{
		XFORM matrix;
		memdc->GetWorldTransform(&matrix);
		DrawBackground(memdc);
		
		DrawFerrisWheel(memdc, 200, 1, 20, RGB(255,100,0), CPoint(client.Width()/2, client.Height()/2), 90, L"Festival");

		memdc->SetWorldTransform(&matrix);
	}

	pdc->BitBlt(0, 0, client.Width(), client.Height(), memdc, 0, 0, SRCCOPY);

	memdc->SetGraphicsMode(oldGM);
	memdc->SelectObject(oldbm);
	delete memdc;
}















// CJun2025View printing


void CJun2025View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CJun2025View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CJun2025View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CJun2025View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CJun2025View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CJun2025View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CJun2025View diagnostics

#ifdef _DEBUG
void CJun2025View::AssertValid() const
{
	CView::AssertValid();
}

void CJun2025View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJun2025Doc* CJun2025View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJun2025Doc)));
	return (CJun2025Doc*)m_pDocument;
}
#endif //_DEBUG


// CJun2025View message handlers

afx_msg BOOL CJun2025View::OnEraseBkgnd(CDC* pdc) {
	return TRUE;
}


void CJun2025View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == VK_RIGHT)
		ferrisAngle += 10;
	if (nChar == VK_LEFT)
		ferrisAngle -= 10;

	Invalidate(TRUE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
