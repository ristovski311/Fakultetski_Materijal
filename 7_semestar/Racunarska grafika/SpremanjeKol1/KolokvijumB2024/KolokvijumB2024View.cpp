
// KolokvijumB2024View.cpp : implementation of the CKolokvijumB2024View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "KolokvijumB2024.h"
#endif

#include "KolokvijumB2024Doc.h"
#include "KolokvijumB2024View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TORAD 3.141592/180

// CKolokvijumB2024View

IMPLEMENT_DYNCREATE(CKolokvijumB2024View, CView)

BEGIN_MESSAGE_MAP(CKolokvijumB2024View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKolokvijumB2024View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CKolokvijumB2024View construction/destruction

CKolokvijumB2024View::CKolokvijumB2024View() noexcept
{
	backgroundImage.Load(L"Background.jpg");
	armImage.Load(L"Arm.png");
	basketImage.Load(L"Basket.png");

	angleBase = 0;
	angleFirstArm = 0;
	angleCenter = 0;
	baseMovement = 0;

}

CKolokvijumB2024View::~CKolokvijumB2024View()
{
	//Oslobadjanje memorije?
}

BOOL CKolokvijumB2024View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CKolokvijumB2024View::Translate(CDC* pdc, float dX, float dY, bool rightMultiply) {
	XFORM matrix;
	matrix.eDx = dX;
	matrix.eDy = dY;
	matrix.eM11 = 1;
	matrix.eM12 = 0;
	matrix.eM21 = 0;
	matrix.eM22 = 1;
	if (rightMultiply)
		pdc->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);

}
void CKolokvijumB2024View::Rotate(CDC* pdc, float angle, bool rightMultiply) {
	XFORM matrix;
	matrix.eDx = 0;
	matrix.eDy = 0;
	matrix.eM11 = cos(angle*TORAD);
	matrix.eM12 = sin(angle*TORAD);
	matrix.eM21 = -sin(angle*TORAD);
	matrix.eM22 = cos(angle*TORAD);
	if (rightMultiply)
		pdc->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);
}
void CKolokvijumB2024View::Scale(CDC* pdc, float sX, float sY, bool rightMultiply) {
	XFORM matrix;
	matrix.eDx = 0;
	matrix.eDy = 0;
	matrix.eM11 = sX;
	matrix.eM12 = 0;
	matrix.eM21 = 0;
	matrix.eM22 = sY;
	if (rightMultiply)
		pdc->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);
}



void CKolokvijumB2024View::DrawBackground(CDC* pdc) {
	CRect clientRect;
	GetClientRect(&clientRect);
	backgroundImage.Draw(pdc, new CRect(0, 0, backgroundImage.Width(), backgroundImage.Height()), clientRect);
}

void CKolokvijumB2024View::DrawImageTransparent(CDC* pdc, DImage* pImage) {

	byte B = pImage->GetDIBBits()[0];
	byte G = pImage->GetDIBBits()[1];
	byte R = pImage->GetDIBBits()[2];

	CRect clientRect;
	GetClientRect(&clientRect);

	pImage->DrawTransparent(pdc, new CRect(0, 0, pImage->Width(), pImage->Height()), new CRect(-pImage->Width() / 2, -pImage->Height() / 2, pImage->Width()/2, pImage->Height()/2), RGB(R, G, B));
}

void CKolokvijumB2024View::DrawArm(CDC* pdc) {

	XFORM oldMatrix;
	pdc->GetWorldTransform(&oldMatrix);

	int imgWid = armImage.Width();
	int imgHei = armImage.Height();

	int offsetX = imgWid / 2 - 10;
	int offsetY = imgHei / 2 - 10;

	Translate(pdc, offsetX, offsetY, false);
	DrawImageTransparent(pdc, &armImage);
	Translate(pdc, -offsetX, -offsetY, false);

	pdc->SetWorldTransform(&oldMatrix);
}

void CKolokvijumB2024View::DrawBasket(CDC* pdc, int r) {

	XFORM oldMatrix;
	pdc->GetWorldTransform(&oldMatrix);

	CFont font;
	font.CreateFontW(0.9 * r, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Verdana");
	int oldAlignment = pdc->SetTextAlign(TA_CENTER | TA_BASELINE);

	CFont* oldFont = pdc->SelectObject(&font);
	int oldMode = pdc->SetBkMode(TRANSPARENT);

	Scale(pdc, 0.675, 0.675, false);
	DrawImageTransparent(pdc, &basketImage);
	Scale(pdc, 1/0.675, 1/0.675, false);

	Rotate(pdc, -60, false);
	COLORREF oldTC = pdc->SetTextColor(RGB(0, 0, 255));
	pdc->TextOutW(0, 0, L"R_G");
	pdc->SetTextColor(oldTC);
	Rotate(pdc, 60, false);

	pdc->SetTextAlign(oldAlignment);
	pdc->SelectObject(oldFont);
	pdc->SetBkMode(oldMode);

	pdc->SetWorldTransform(&oldMatrix);
}

void CKolokvijumB2024View::DrawBasketCouple(CDC* pdc, int l, int r, float angle) {

	XFORM oldMatrix;
	pdc->GetWorldTransform(&oldMatrix);

	Rotate(pdc, angle, false);
	
	//Prvi centralni basket
	Rotate(pdc, angle, false);
	DrawBasket(pdc, 50);
	Rotate(pdc, -angle, false);

	//Drugi basket
	Translate(pdc, l, 0, false);
	DrawBasket(pdc, 50);
	Translate(pdc, -l, 0, false);
	
	//Arm
	Translate(pdc, 0, 0.8 * r, false);
	Rotate(pdc, -90, false);
	DrawArm(pdc);
	Rotate(pdc, 90, false);
	Translate(pdc, 0, -0.8 * r, false);
	
	Rotate(pdc, -angle, false);

	pdc->SetWorldTransform(&oldMatrix);
}

void CKolokvijumB2024View::DrawPlatform(CDC * pdc, int l, int r, double angle) {

	XFORM oldMatrix;
	pdc->GetWorldTransform(&oldMatrix);

	//Centralna
	Rotate(pdc, angle, false);
	DrawBasket(pdc, 50);
	Rotate(pdc, -angle, false);

	Rotate(pdc, -angle, false);

	//Donji desni couple
	Rotate(pdc, 45, false);
	Translate(pdc, 2 * r, 0, false);
	DrawBasketCouple(pdc, l, r, 45);
	Translate(pdc, -2 * r, 0, false);


	//Donji levi couple
	Rotate(pdc, 90, false);
	Translate(pdc, 2 * r, 0, false);
	DrawBasketCouple(pdc, l, r, 45);
	Translate(pdc, -2 * r, 0, false);


	//Gornji levi couple
	Rotate(pdc, 90, false);
	Translate(pdc, 2 * r, 0, false);
	DrawBasketCouple(pdc, l, r, 45);
	Translate(pdc, -2 * r, 0, false);


	//Gornji desni couple
	Rotate(pdc, 90, false);
	Translate(pdc, 2*r, 0, false);
	DrawBasketCouple(pdc, l, r, 45);
	Translate(pdc, -2*r, 0, false);

	//Da se vratimo na 0 stupnjeva
	Rotate(pdc, 45, false);

	Rotate(pdc, angle, false);

	pdc->SetWorldTransform(&oldMatrix);
}


void CKolokvijumB2024View::DrawCarousel(CDC* pdc, int h, int r, double offset, double alpha, double beta, double angle) {

	XFORM oldMatrix;
	pdc->GetWorldTransform(&oldMatrix);

	//Pomeranje vodoravno svega
	Translate(pdc, offset, 0, false);

		//Rotitanje kako se krece -> l = alpha * r
		double rad_angle_to_rotate_base = (offset / r);
		double angle_to_rotate_base = rad_angle_to_rotate_base * 180 / 3.141592;
		Rotate(pdc, angle_to_rotate_base, false);
		DrawBasket(pdc, r);
		Rotate(pdc, -angle_to_rotate_base, false);

		//Prva ruka
		Rotate(pdc, alpha, false);
		Rotate(pdc, 180, false); //Zato sto mi je naopacke slika, manja osovina mi je dole, a treba gore
		DrawArm(pdc);
		Rotate(pdc, -180, false);

			//Druga ruka
			Translate(pdc, 0, -h, false);
			Rotate(pdc, beta, false);
			Rotate(pdc, 180, false);
			DrawArm(pdc);
			Rotate(pdc, -180, false);

				//Platforma
				Translate(pdc, 0, -h, false);
				DrawPlatform(pdc, h, r, angle);
				Translate(pdc, 0, h, false);

			//Rotacija druge ruke
			Rotate(pdc, -beta, false);
			//Translacija druge ruke
			Translate(pdc, 0, h, false);

		//Rotacija prve ruke
		Rotate(pdc, -alpha, false);

	//Vodoravno kretanje
	Translate(pdc, -offset, 0, false);


	pdc->SetWorldTransform(&oldMatrix);
}









// CKolokvijumB2024View drawing

void CKolokvijumB2024View::OnDraw(CDC* pdc)
{
	CKolokvijumB2024Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect clientRect;
	GetClientRect(&clientRect);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pdc);
	CBitmap memBM;
	memBM.CreateCompatibleBitmap(pdc, clientRect.Width(), clientRect.Height());
	CBitmap* oldBM = memDC->SelectObject(&memBM);
	memDC->FillSolidRect(clientRect, RGB(255, 255, 255));

	int oldGM = memDC->SetGraphicsMode(GM_ADVANCED);

	//Crtanje u memDC
	{
		DrawBackground(memDC);
		
		int offsetX = clientRect.Width() / 2;
		int offsetY = clientRect.Height() - 2 * 50;
		
		Translate(memDC, offsetX, offsetY, false);
		DrawCarousel(memDC, 182, 50, baseMovement, angleBase, angleFirstArm ,angleCenter);
		Translate(memDC, -offsetX, -offsetY, false);

	}

	pdc->BitBlt(0, 0, clientRect.Width(), clientRect.Height(), memDC, 0, 0, SRCCOPY);

	memDC->SelectObject(oldBM);
	memDC->SetGraphicsMode(oldGM);
	delete memDC;
}















// CKolokvijumB2024View printing


void CKolokvijumB2024View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKolokvijumB2024View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKolokvijumB2024View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKolokvijumB2024View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CKolokvijumB2024View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKolokvijumB2024View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CKolokvijumB2024View diagnostics

#ifdef _DEBUG
void CKolokvijumB2024View::AssertValid() const
{
	CView::AssertValid();
}

void CKolokvijumB2024View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKolokvijumB2024Doc* CKolokvijumB2024View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKolokvijumB2024Doc)));
	return (CKolokvijumB2024Doc*)m_pDocument;
}
#endif //_DEBUG


// CKolokvijumB2024View message handlers

afx_msg BOOL CKolokvijumB2024View::OnEraseBkgnd(CDC* pdc) {
	return TRUE;
}


void CKolokvijumB2024View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == 'Q')
		baseMovement -= 10;
	else if (nChar == 'W')
		baseMovement += 10;
	else if (nChar == 'A')
		angleBase -= 10;
	else if (nChar == 'S')
		angleBase += 10;
	else if (nChar == 'D')
		angleFirstArm -= 10;
	else if (nChar == 'F')
		angleFirstArm += 10;
	else if (nChar == 'E')
		angleCenter -= 10;
	else if (nChar == 'R')
		angleCenter += 10;

	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
