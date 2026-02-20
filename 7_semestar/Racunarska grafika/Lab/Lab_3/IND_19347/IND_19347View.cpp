
// IND_19347View.cpp : implementation of the CIND19347View class
//

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include <string>
#include <string.h>
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
#define TORAD 3.14159/180
#define ANGLE_STEP 1
#define TRANSLATE_STEP 7

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
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CIND19347View construction/destruction

CIND19347View::CIND19347View() noexcept
{
	grid = CRect(0, 0, 512, 512);
	showGrid = false;
	currentPuzzle = 1;
	showNumbersOnPuzzles = false;	
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

void CIND19347View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply) {
	XFORM t;
	t.eDx = dX;
	t.eDy = dY;
	t.eM11 = 1;
	t.eM12 = 0;
	t.eM21 = 0;
	t.eM22 = 1;

	if(rightMultiply)
		pDC->ModifyWorldTransform(&t, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&t, MWT_LEFTMULTIPLY);
}

void CIND19347View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply) {
	XFORM t;
	t.eDx = 0;
	t.eDy = 0;
	t.eM11 = sX;
	t.eM12 = 0;
	t.eM21 = 0;
	t.eM22 = sY;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&t, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&t, MWT_LEFTMULTIPLY);
}

void CIND19347View::Rotate(CDC* pDC, float angle, bool rightMultiply) {
	XFORM t;
	t.eDx = 0;
	t.eDy = 0;
	t.eM11 = cos(angle*TORAD);
	t.eM12 = sin(angle * TORAD);
	t.eM21 = -sin(angle * TORAD);
	t.eM22 = cos(angle * TORAD);

	if (rightMultiply)
		pDC->ModifyWorldTransform(&t, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&t, MWT_LEFTMULTIPLY);
}

void CIND19347View::Mirror(CDC* pDC, bool mx, bool my, bool rightMultiply) {
	XFORM t;
	t.eDx = 0;
	t.eDy = 0;
	t.eM11 = my ? -1 : 1; //Da li zelim da rotiram oko y-ose?
	t.eM12 = 0;
	t.eM21 = 0;
	t.eM22 = mx ? -1 : 1;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&t, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&t, MWT_LEFTMULTIPLY);
}

void CIND19347View::DrawGrid(CDC* pDC) {

	CPen* newpen = new CPen(PS_COSMETIC, 1, RGB(200, 200, 200));
	CPen* oldpen = pDC->SelectObject(newpen);

	for (int i = 0; i < 21; i++)
	{
		pDC->MoveTo(i*GSS, 0);
		pDC->LineTo(i * GSS, 500);

		pDC->MoveTo(0, i * GSS);
		pDC->LineTo(500, i * GSS);
	}

	pDC->SelectObject(oldpen);
	delete newpen;
}

void DrawCS(CDC* pdc) {
	//Pomocna fja za orijentaciju pri koriscenju LEFT MULTIPLY svetske transformacione matrice
	//Prikazuje mi x i y ose

	CPen* xpen = new CPen(PS_GEOMETRIC, 3, RGB(200, 0, 0));
	CPen* ypen = new CPen(PS_GEOMETRIC, 3, RGB(200, 200, 0));
	CPen* oldpen = pdc->SelectObject(xpen);
	pdc->MoveTo(0, 0);
	pdc->LineTo(100, 0);
	pdc->MoveTo(0, 0);
	pdc->SelectObject(ypen);
	pdc->LineTo(0, 100);
	pdc->MoveTo(0, 0);
	pdc->SelectObject(oldpen);
	delete xpen;
	delete ypen;
}

void CIND19347View::FilterPuzzlePiece(CBitmap* slika, bool r, bool g, bool b, COLORREF dontFilterColor) {

	BITMAP bmp;
	slika->GetBitmap(&bmp);
	int width = bmp.bmWidth;
	int height = bmp.bmHeight;
	int stride = bmp.bmWidthBytes;
	int size = stride * height;

	BYTE* bits = new BYTE[size];
	slika->GetBitmapBits(size, bits);

	int bytesPerPixel = bmp.bmBitsPixel / 8;

	for (int y = 0; y < height; y++)
	{
		BYTE* row = bits + y * stride;
		for (int x = 0; x < width; x++)
		{
			BYTE* px = row + x * bytesPerPixel;

			BYTE B = px[0];
			BYTE G = px[1];
			BYTE R = px[2];

			if (RGB(R, G, B) == dontFilterColor)
				continue;

			int new_clr = 64 + (R + G + B) / 3;
			if (new_clr > 255)
				new_clr = 255;

			px[0] = b ? (BYTE)new_clr : 0;
			px[1] = g ? (BYTE)new_clr : 0;
			px[2] = r ? (BYTE)new_clr : 0;
		}
	}

	slika->SetBitmapBits(size, bits);
	delete[] bits;

}

void CIND19347View::RemoveBkgFromPuzzlePiece(CDC* pDC, DImage* img, bool r, bool g, bool b) {

	int w = img->Width();
	int h = img->Height();

	CBitmap slika;
	CBitmap maska;

	slika.CreateCompatibleBitmap(pDC, w, h);
	maska.CreateBitmap(w, h, 1, 1, NULL);

	CDC* pSlikaDC = new CDC(), * pMaskaDC = new CDC();
	pSlikaDC->CreateCompatibleDC(pDC);
	pMaskaDC->CreateCompatibleDC(pDC);
	pSlikaDC->SelectObject(slika);
	pMaskaDC->SelectObject(maska);

	img->Draw(pSlikaDC, CRect(0, 0, w, h), CRect(0, 0, w, h));
	
	COLORREF clrTopLeft = pSlikaDC->GetPixel(0, 0);
	COLORREF oldClrSlika = pSlikaDC->SetBkColor(clrTopLeft);

	FilterPuzzlePiece(&slika, r, g, b, clrTopLeft);

	pMaskaDC->BitBlt(0, 0, w, h, pSlikaDC, 0, 0, SRCCOPY);

	COLORREF oldClrTextSlika = pSlikaDC->SetTextColor(RGB(255, 255, 255));
	pSlikaDC->SetBkColor(RGB(0, 0, 0));
	pSlikaDC->BitBlt(0, 0, w, h, pMaskaDC, 0, 0, SRCAND);

	pDC->BitBlt(0,0,w,h, pMaskaDC, 0, 0, SRCAND);
	pDC->BitBlt(0, 0, w, h, pSlikaDC, 0, 0, SRCPAINT);

	delete pMaskaDC;
	delete pSlikaDC;

}

void CIND19347View::DrawPuzzleMovable(CDC* pDC)
{
	XFORM prevMatrix;
	pDC->GetWorldTransform(&prevMatrix);
	
	Scale(pDC, 1, 1, false);

	//Za filter
	bool r, g, b;

	for (int i = 0; i < 9; i++)
	{
		CString path;
		path.Format(L"%d.bmp", i+1);

		DImage img;
		img.Load(path);
		int width = img.Width();
		int height = img.Height();

		Translate(pDC, puzzleTranslateX[i], puzzleTranslateY[i], false);
		Translate(pDC, width/2, height/2, false);
		Mirror(pDC, puzzleMirrorRelToX[i], puzzleMirrorRelToY[i], false);
		Rotate(pDC, puzzleAngle[i], false);
		Translate(pDC, -width/2, -height/2, false);

		if (i == 5)
		{
			b = false;
			g = false;
			r = true;
		}
		else 
		{
			b = true;
			g = true;
			r = true;
		}
		
		RemoveBkgFromPuzzlePiece(pDC, &img, r, g, b);

		if(showNumbersOnPuzzles)
		{
			CString num;
			num.Format(L"%d", i + 1);

			COLORREF oldTextColor = pDC->SetTextColor(RGB(255, 0, 0));
			pDC->TextOutW(width / 2, height / 2, num);
			pDC->SetTextColor(oldTextColor);
		}

		Translate(pDC, width/2, height/2, false);
		Rotate(pDC, -puzzleAngle[i], false);
		Mirror(pDC, puzzleMirrorRelToX[i], puzzleMirrorRelToY[i], false);
		Translate(pDC, -width/2, -height/2, false);
		Translate(pDC, -puzzleTranslateX[i], -puzzleTranslateY[i], false);
	}

	pDC->SetWorldTransform(&prevMatrix);
}

void CIND19347View::DrawPuzzle(CDC* pDC)
{
	XFORM prevMatrix;
	pDC->GetWorldTransform(&prevMatrix);

	Scale(pDC, 1, 1, false);

	//Rotacija i mirror
	Translate(pDC, 250, 250, false);
	Mirror(pDC, true, false, false);
	Translate(pDC, -250, -250, false);

	//Za filter
	bool r, g, b;
	//Delovi:

	//Ucitavamo da dobijemo height i width
	DImage img;
	img.Load(L"1.bmp");
	int width = img.Width();
	int height = img.Height();

	// Deo 1
	Translate(pDC, (1-1.9)*GSS, (1-2.4)*GSS, false);
	Translate(pDC, width / 2, height / 2, false);
	Mirror(pDC, false, false, false);
	Rotate(pDC, 26, false);
	Translate(pDC, -width / 2, -height / 2, false);

	RemoveBkgFromPuzzlePiece(pDC, &img, true, true, true);

	Translate(pDC, width / 2, height / 2, false);
	Rotate(pDC, -(26), false);
	Mirror(pDC, false, false, false);
	Translate(pDC, -width / 2, -height / 2, false);
	Translate(pDC, -(1 - 1.9) *GSS, -(1 - 2.4) *GSS, false);
	

	// Deo 2
	img.Load(L"2.bmp");
	Translate(pDC, (7 - 2.1) * GSS, (7 - 2.4) * GSS, false);
	Translate(pDC, width / 2, height / 2, false);
	Mirror(pDC, false, false, false);
	Rotate(pDC, -19, false);
	Translate(pDC, -width / 2, -height / 2, false);

	RemoveBkgFromPuzzlePiece(pDC, &img, true, true, true);

	Translate(pDC, width / 2, height / 2, false);
	Rotate(pDC, -(-19), false);
	Mirror(pDC, false, false, false);
	Translate(pDC, -width / 2, -height / 2, false);
	Translate(pDC, -(7 - 2.1) * GSS, -(7 - 2.4) * GSS, false);

	// Deo 3
	img.Load(L"3.bmp");
	Translate(pDC, (7 - 2.2) * GSS, (13 - 1.8) * GSS, false);
	Translate(pDC, width / 2, height / 2, false);
	Mirror(pDC, true, true, false);
	Rotate(pDC, -23, false);
	Translate(pDC, -width / 2, -height / 2, false);

	RemoveBkgFromPuzzlePiece(pDC, &img, true, true, true);

	Translate(pDC, width / 2, height / 2, false);
	Rotate(pDC, -(-23), false);
	Mirror(pDC, true, true, false);
	Translate(pDC, -width / 2, -height / 2, false);
	Translate(pDC, -(7 - 2.2) * GSS, -(13 - 1.8) * GSS, false);

	// Deo 4
	img.Load(L"4.bmp");
	Translate(pDC, (13 - 1.9) * GSS, (1 - 2.3) * GSS, false);
	Translate(pDC, width / 2, height / 2, false);
	Mirror(pDC, false, false, false);
	Rotate(pDC, 34, false);
	Translate(pDC, -width / 2, -height / 2, false);

	RemoveBkgFromPuzzlePiece(pDC, &img, true, true, true);

	Translate(pDC, width / 2, height / 2, false);
	Rotate(pDC, -(34), false);
	Mirror(pDC, false, false, false);
	Translate(pDC, -width / 2, -height / 2, false);
	Translate(pDC, -(13 - 1.9) * GSS, -(1 - 2.3) * GSS, false);

	// Deo 5
	img.Load(L"5.bmp");
	Translate(pDC, (1 - 1.8) * GSS, (13 - 2) * GSS, false);
	Translate(pDC, width / 2, height / 2, false);
	Mirror(pDC, false, false, false);
	Rotate(pDC, 90, false);
	Translate(pDC, -width / 2, -height / 2, false);

	RemoveBkgFromPuzzlePiece(pDC, &img, true, true, true);

	Translate(pDC, width / 2, height / 2, false);
	Rotate(pDC, -(90), false);
	Mirror(pDC, false, false, false);
	Translate(pDC, -width / 2, -height / 2, false);
	Translate(pDC, -(1 - 1.8) * GSS, -(13 - 2) * GSS, false);

	// Deo 6
	img.Load(L"6.bmp");
	Translate(pDC, (13 - 2.2) * GSS, (7 - 1.7) * GSS, false);
	Translate(pDC, width / 2, height / 2, false);
	Mirror(pDC, true, true, false);
	Rotate(pDC, -21, false);
	Translate(pDC, -width / 2, -height / 2, false);

	RemoveBkgFromPuzzlePiece(pDC, &img, true, false, false);

	Translate(pDC, width / 2, height / 2, false);
	Rotate(pDC, -(-21), false);
	Mirror(pDC, true, true, false);
	Translate(pDC, -width / 2, -height / 2, false);
	Translate(pDC, -(13 - 2.2) * GSS, -(7 - 1.7) * GSS, false);

	// Deo 7
	img.Load(L"7.bmp");
	Translate(pDC, (1 - 2.5)* GSS, (7 - 2.2)* GSS, false);
	Translate(pDC, width / 2, height / 2, false);
	Mirror(pDC, true, true, false);
	Rotate(pDC, -13+90, false);
	Translate(pDC, -width / 2, -height / 2, false);

	RemoveBkgFromPuzzlePiece(pDC, &img, true, true, true);

	Translate(pDC, width / 2, height / 2, false);
	Rotate(pDC, -(-13+90), false);
	Mirror(pDC, true, true, false);
	Translate(pDC, -width / 2, -height / 2, false);
	Translate(pDC, -(1 - 2.5) * GSS, -(7 - 2.2) * GSS, false);

	// Deo 8
	img.Load(L"8.bmp");
	Translate(pDC, (13 - 1.9) * GSS, (13 - 2.4) * GSS, false);
	Translate(pDC, width / 2, height / 2, false);
	Mirror(pDC, false, false, false);
	Rotate(pDC, 14, false);
	Translate(pDC, -width / 2, -height / 2, false);

	RemoveBkgFromPuzzlePiece(pDC, &img, true, true, true);

	Translate(pDC, width / 2, height / 2, false);
	Rotate(pDC, -(14), false);
	Mirror(pDC, false, false, false);
	Translate(pDC, -width / 2, -height / 2, false);
	Translate(pDC, -(13 - 1.9) * GSS, -(13 - 2.4) * GSS, false);

	// Deo 9
	img.Load(L"9.bmp");
	Translate(pDC, (7 - 1.7) * GSS, (1 - 2.1) * GSS, false);
	Translate(pDC, width / 2, height / 2, false);
	Mirror(pDC, false, false, false);
	Rotate(pDC, -25+90, false);
	Translate(pDC, -width / 2, -height / 2, false);

	RemoveBkgFromPuzzlePiece(pDC, &img, true, true, true);

	Translate(pDC, width / 2, height / 2, false);
	Rotate(pDC, -(-25+90), false);
	Mirror(pDC, false, false, false);
	Translate(pDC, -width / 2, -height / 2, false);
	Translate(pDC, -(7 - 1.7) * GSS, -(1 - 2.1) * GSS, false);


	pDC->SetWorldTransform(&prevMatrix);
}

//Delovi i uglovi:
//1: 25 | 26
//2: -32 | -19
//3: -18 | -23
//4: 19 ili 18 | 34
//5: -14 | 0
//6: 22 ili 23 | -20
//7: -35 | -13
//8: -19 | 13
//9: 17 | -25

// CIND19347View drawing 

void CIND19347View::OnDraw(CDC* pDC)
{
	CIND19347Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect clientRect;
	GetClientRect(&clientRect);


	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(pDC, clientRect.Width(), clientRect.Height());
	CBitmap* oldBitmap = memDC->SelectObject(&memBitmap);
	memDC->FillSolidRect(clientRect, RGB(255, 255, 255));

	int prevMode;
	prevMode = memDC->SetGraphicsMode(GM_ADVANCED);

	if (showGrid)
		DrawGrid(memDC);

	//DrawPuzzleMovable(memDC);
	DrawPuzzle(memDC);

	memDC->SetGraphicsMode(prevMode);

	pDC->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->SelectObject(oldBitmap);
	delete memDC;
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
	if (nChar == VK_NUMPAD1)
		currentPuzzle = 1;
	else if (nChar == VK_NUMPAD2)
		currentPuzzle = 2;
	else if (nChar == VK_NUMPAD3)
		currentPuzzle = 3;
	else if (nChar == VK_NUMPAD4)
		currentPuzzle = 4;
	else if (nChar == VK_NUMPAD5)
		currentPuzzle = 5;
	else if (nChar == VK_NUMPAD6)
		currentPuzzle = 6;
	else if (nChar == VK_NUMPAD7)
		currentPuzzle = 7;
	else if (nChar == VK_NUMPAD8)
		currentPuzzle = 8;
	else if (nChar == VK_NUMPAD9)
		currentPuzzle = 9;
	else if (nChar == 'N' || nChar == 'n')
		showNumbersOnPuzzles = !showNumbersOnPuzzles;
	else if (nChar == 'X' || nChar == 'x')
		puzzleMirrorRelToX[currentPuzzle - 1] = !puzzleMirrorRelToX[currentPuzzle - 1];
	else if (nChar == 'Y' || nChar == 'y' || nChar == 'Z' || nChar == 'z')
		puzzleMirrorRelToY[currentPuzzle - 1] = !puzzleMirrorRelToY[currentPuzzle - 1];
	else if (nChar == 'W' || nChar == 'w')
		puzzleTranslateY[currentPuzzle - 1] -= TRANSLATE_STEP;
	else if (nChar == 'S' || nChar == 's')
		puzzleTranslateY[currentPuzzle - 1] += TRANSLATE_STEP;
	else if (nChar == 'A' || nChar == 'a')
		puzzleTranslateX[currentPuzzle - 1] -= TRANSLATE_STEP;
	else if (nChar == 'D' || nChar == 'd')
		puzzleTranslateX[currentPuzzle - 1] += TRANSLATE_STEP;
	else if (nChar == VK_LEFT)
		puzzleAngle[currentPuzzle - 1] -= ANGLE_STEP;
	else if (nChar == VK_RIGHT)
		puzzleAngle[currentPuzzle - 1] += ANGLE_STEP;
	else if(nChar == 'O' || nChar == 'o')
	{
		CRgn rgn;
		rgn.CreateRectRgn(grid.left, grid.top, grid.right, grid.bottom);
		showGrid = !showGrid;
	}

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

BOOL CIND19347View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}