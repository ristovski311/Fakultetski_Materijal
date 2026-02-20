
// Kolokvijum2019View.cpp : implementation of the CKolokvijum2019View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kolokvijum2019.h"
#endif

#include "Kolokvijum2019Doc.h"
#include "Kolokvijum2019View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TORAD 3.141592 / 180
#define TODEG 180 / 3.141592

// CKolokvijum2019View

IMPLEMENT_DYNCREATE(CKolokvijum2019View, CView)

BEGIN_MESSAGE_MAP(CKolokvijum2019View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKolokvijum2019View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CKolokvijum2019View construction/destruction

CKolokvijum2019View::CKolokvijum2019View() noexcept
{
	body1 = new DImage();
	arm1 = new DImage();
	arm2 = new DImage();
	leg1 = new DImage();
	leg2 = new DImage();
	background = new DImage();

	body1->Load(L"body1.png");
	arm1->Load(L"arm1.png");
	arm2->Load(L"arm2.png");
	leg1->Load(L"leg1.png");
	leg2->Load(L"leg2.png");
	background->Load(L"background.jpg");

	angleArm1 = 0;
	angleArm2 = 180;
	angleLeg1 = 0;
	angleLeg2 = 0;
	angleBody = 0;
}

CKolokvijum2019View::~CKolokvijum2019View()
{
	if (body1)
		delete body1;
	if (arm1)
		delete arm1;
	if (arm2)
		delete arm2;
	if (leg1)
		delete leg1;
	if (leg2)
		delete leg2;
	if (background)
		delete background;

}

BOOL CKolokvijum2019View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}


void CKolokvijum2019View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply) {
	XFORM matrix;
	matrix.eDx = dX;
	matrix.eDy = dY;
	matrix.eM11 = 1;
	matrix.eM12 = 0;
	matrix.eM21 = 0;
	matrix.eM22 = 1;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);

}

void CKolokvijum2019View::Rotate(CDC * pDC, float angle, bool rightMultiply) {
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



void CKolokvijum2019View::DrawBackground(CDC* pDC, CRect rc) {
	
	background->Draw(pDC, CRect(0, 0, background->Width(), background->Height()), rc);
}


void CKolokvijum2019View::DrawImgTransparent(CDC* pDC, DImage* pImage) {

	byte B = pImage->GetDIBBits()[0];
	byte G = pImage->GetDIBBits()[1];
	byte R = pImage->GetDIBBits()[2];

	pImage->DrawTransparent(pDC, CRect(0, 0, pImage->Width(), pImage->Height()), CRect(-pImage->Width() / 2, -pImage->Height() / 2, pImage->Width() / 2, pImage->Height() / 2), RGB(R,G,B));
}

void CKolokvijum2019View::DrawArm1(CDC* pDC) {
	XFORM matrix;
	pDC->GetWorldTransform(&matrix);

	//Idemo na tacku (34, 31) da se rotiramo, trenutno smo u koordinatnom pocetku
	Translate(pDC, -(arm1->Width() / 2 - 34), -(arm1->Height() / 2 - 31), false);

	//Rotacija oko tacke
	Rotate(pDC, angleArm1, false);

	//Idemo opet na centar slike da se iscrtamo
	Translate(pDC, (arm1->Width() / 2 - 34), (arm1->Height() / 2 - 31), false);
	DrawImgTransparent(pDC, arm1);
	
	//Idemo sad opet na tacku rotacije da bismo vratili rotate na normalu
	Translate(pDC, -(arm1->Width() / 2 - 34), -(arm1->Height() / 2 - 31), false);

	Rotate(pDC, -angleArm1, false);

	//Vracamo se na center slke ponovo
	Translate(pDC, (arm1->Width() / 2 - 34), (arm1->Height() / 2 - 31), false);

	pDC->SetWorldTransform(&matrix);
}

void CKolokvijum2019View::DrawArm2(CDC* pDC) {

	XFORM matrix;
	pDC->GetWorldTransform(&matrix);

	//Pomeramo se na tacku na slici arm1 gde se rotira arm1 (34, 31):
	Translate(pDC, -(arm1->Width() / 2 - 34), -(arm1->Height() / 2 - 31), false);

	//Rotiramo se oko te tacke za arm1 ugao
	Rotate(pDC, angleArm1, false);

	//Idemo na centar arm1 slike:
	Translate(pDC, (arm1->Width() / 2 - 34), (arm1->Height() / 2 - 31), false);

	//Idemo na tacku na slici arm1 gde se nadovezuje arm2: (210, 102)
	Translate(pDC, -(arm1->Width() / 2 - 210), -(arm1->Height() / 2 - 102), false);

	//Sad ta tacka predstavlja tacku (23,61) u slici arm2, prvo se rotiramo oko te tacke za ugao arm2 
	Rotate(pDC, angleArm2, false);

	//Sad treba da odemo u centar slike arm2 kako bismo iscrtali
	Translate(pDC, (arm2->Width() / 2 - 23), (arm2->Height() / 2 - 61), false);

	DrawImgTransparent(pDC, arm2);

	//Sad se vracamo na spojnu tacku
	Translate(pDC, -(arm2->Width() / 2 - 23), -(arm2->Height() / 2 - 61), false);

	//Rotiramo se nazad za -arm2 ugao
	Rotate(pDC, -angleArm2, false);

	//Idemo nazad na centar arm1
	Translate(pDC, (arm1->Width() / 2 - 210), (arm1->Height() / 2 - 102), false);

	//Idemo ponovo na tacku gde se rotira arm1
	Translate(pDC, -(arm1->Width() / 2 - 34), -(arm1->Height() / 2 - 31), false);

	//Vracamo rotaciju 
	Rotate(pDC, -angleArm1, false);

	//I konacno se vracamo na centar slike arm1:
	Translate(pDC, (arm1->Width() / 2 - 34), (arm1->Height() / 2 - 31), false);


	pDC->SetWorldTransform(&matrix);
}

void CKolokvijum2019View::DrawLeg1(CDC* pDC) {

	XFORM matrix;
	pDC->GetWorldTransform(&matrix);

	//Idemo na tacku oko koje se rotira leg1  (30,125)
	Translate(pDC, -(leg1->Width() / 2 - 30), -(leg1->Height() / 2 - 125), false);

	//Rotiramo se
	Rotate(pDC, angleLeg1, false);

	//Idemo na centar da se nacrtamo
	Translate(pDC, (leg1->Width() / 2 - 30), (leg1->Height() / 2 - 125), false);
	DrawImgTransparent(pDC, leg1);

	//Idemo opet na tacku rotacije
	Translate(pDC, -(leg1->Width() / 2 - 30), -(leg1->Height() / 2 - 125), false);

	//Da se zarotiramo nazad -leg1 angle
	Rotate(pDC, -angleLeg1, false);

	//I opet na centar
	Translate(pDC, (leg1->Width() / 2 - 30), (leg1->Height() / 2 - 125), false);

	pDC->SetWorldTransform(&matrix);
}

void CKolokvijum2019View::DrawLeg2(CDC* pDC) {
	XFORM matrix;
	pDC->GetWorldTransform(&matrix);


	//Idemo na mesto gde se spajaju  (30,125)
	Translate(pDC, -(leg1->Width() / 2 - 30), -(leg1->Height() / 2 - 125), false);

	//Rotacija
	Rotate(pDC, angleLeg2, false);

	//Sad idemo na centar leg 2 jer smo trenutno u (35,60)
	Translate(pDC, (leg2->Width() / 2 - 35), (leg2->Height() / 2 - 60), false);

	DrawImgTransparent(pDC, leg2);

	//Vracamo se nazad u spoj
	Translate(pDC, -(leg2->Width() / 2 - 35), -(leg2->Height() / 2 - 60), false);

	//Rotacija unazad
	Rotate(pDC, -angleLeg2, false);

	//Idemo na centar leg1
	Translate(pDC, (leg1->Width() / 2 - 30), (leg1->Height() / 2 - 125), false);

	pDC->SetWorldTransform(&matrix);
}

void CKolokvijum2019View::DrawBody1(CDC* pDC) {

	XFORM matrix;
	pDC->GetWorldTransform(&matrix);

	//Idemo do rotirajuce tacke (26,133)
	Translate(pDC, -(body1->Width()/2 - 26), -(body1->Height()/2 - 133), false);

	//Rotiramo se
	Rotate(pDC, angleBody, false);

	//Idemo na centar da se nacrtamo
	Translate(pDC, (body1->Width() / 2 - 26), (body1->Height() / 2 - 133), false);

	DrawImgTransparent(pDC, body1);

	//Idemo nazad na rotirajucu tacku da vratimo rotaciju
	Translate(pDC, -(body1->Width() / 2 - 26), -(body1->Height() / 2 - 133), false);

	//Rotiramo se nazad
	Rotate(pDC, -angleBody, false);

	//Idemo na centar opet
	Translate(pDC, (body1->Width() / 2 - 26), (body1->Height() / 2 - 133), false);

	pDC->SetWorldTransform(&matrix);
}

void CKolokvijum2019View::DrawTransformer(CDC* pDC) {

	XFORM matrix;
	pDC->GetWorldTransform(&matrix);

	//Leg 1 i 2
	DrawLeg1(pDC);
	DrawLeg2(pDC);


	//Na lokaciju rotacije leg1
	Translate(pDC, -(leg1->Width() / 2 - 30), -(leg1->Height() / 2 - 125), false);

	Rotate(pDC, angleLeg1, false);

	//Nazad na centar
	Translate(pDC, (leg1->Width() / 2 - 30), (leg1->Height() / 2 - 125), false);

	{
		//Idemo na tacku (237,125) gde je mesto rotacije body1
		Translate(pDC, -(leg1->Width() / 2 - 237), -(leg1->Height() / 2 - 125), false);

		//Sad idemo na centar body dela jer je ovo njemu tacka (26,133)
		Translate(pDC, (body1->Width() / 2 - 26), (body1->Height() / 2 - 133), false);

		//Crtamo body
		DrawBody1(pDC);

		//Nazad na spojnu 
		Translate(pDC, -(body1->Width() / 2 - 26), -(body1->Height() / 2 - 133), false);

		//Rotacija zajedno sa body delom
		Rotate(pDC, angleBody, false);

		//Idemo na centar body
		Translate(pDC, (body1->Width() / 2 - 26), (body1->Height() / 2 - 133), false);

		//Idemo na 210, 85 jer tu ide arm1 rotacija
		Translate(pDC, -(body1->Width() / 2 - 210), -(body1->Height() / 2 - 85), false);

		//Idemo na centar arm1, jer je za arm1 ovo  (34,31)
		Translate(pDC, (arm1->Width() / 2 - 34), (arm1->Height() / 2 - 31), false);
		
		//Crtamo prvo arm2
		DrawArm2(pDC);

		//Crtamo arm1
		DrawArm1(pDC);
		
		//Nazad na spoj
		Translate(pDC, -(arm1->Width() / 2 - 34), -(arm1->Height() / 2 - 31), false);

		//Nazad na centar body
		Translate(pDC, (body1->Width() / 2 - 210), (body1->Height() / 2 - 85), false);


	}

	pDC->SetWorldTransform(&matrix);
}





// CKolokvijum2019View drawing

void CKolokvijum2019View::OnDraw(CDC* pdc)
{
	CKolokvijum2019Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect client;
	GetClientRect(&client);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pdc);

	CBitmap memBM;
	memBM.CreateCompatibleBitmap(pdc, client.Width(), client.Height());

	CBitmap* oldBM = memDC->SelectObject(&memBM);
	int oldGM = memDC->SetGraphicsMode(GM_ADVANCED);

	//CRTANJE u memDC
	{
		XFORM matrix;
		memDC->GetWorldTransform(&matrix);

		DrawBackground(memDC, client);

		Translate(memDC, client.Width()/2, client.Height() / 2 + 30, false);
		DrawTransformer(memDC);
		Translate(memDC, -client.Width() / 2, -client.Height() / 2 - 30, false);

		memDC->SetWorldTransform(&matrix);
	}


	pdc->BitBlt(0, 0, client.Width(), client.Height(), memDC, 0, 0, SRCCOPY);

	memDC->SelectObject(oldBM);
	memDC->SetGraphicsMode(oldGM);
	delete memDC;
}
















// CKolokvijum2019View printing

void CKolokvijum2019View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKolokvijum2019View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKolokvijum2019View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKolokvijum2019View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CKolokvijum2019View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKolokvijum2019View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CKolokvijum2019View diagnostics

#ifdef _DEBUG
void CKolokvijum2019View::AssertValid() const
{
	CView::AssertValid();
}

void CKolokvijum2019View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKolokvijum2019Doc* CKolokvijum2019View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKolokvijum2019Doc)));
	return (CKolokvijum2019Doc*)m_pDocument;
}
#endif //_DEBUG


// CKolokvijum2019View message handlers


void CKolokvijum2019View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'Q')
	{
		angleArm1 -= 5;
	}
	if (nChar == 'A')
	{
		angleArm1 += 5;
	}

	if (nChar == 'E')
		angleLeg1 -= 5;
	if (nChar == 'D')
		angleLeg1 += 5;

	if (nChar == 'T')
		angleArm2 -= 5;
	if (nChar == 'G')
		angleArm2 += 5;

	if (nChar == 'R')
		angleLeg2 -= 5;
	if (nChar == 'F')
		angleLeg2 += 5;

	if (nChar == 'W')
		angleBody -= 5;
	if (nChar == 'S')
		angleBody += 5;

	if (nChar == VK_LEFT)
	{
		if(angleArm1 < 90)
			angleArm1 += 5;
		if (angleArm2 < 180 + 95)
			angleArm2 += 5;
		if (angleLeg1 > -110)
			angleLeg1 -= 5;
		if (angleLeg2 < 100)
			angleLeg2 += 5;
		if (angleBody < 15)
			angleBody += 5;
	}

	if (nChar == VK_RIGHT)
	{
		if (angleArm1 > 0)
			angleArm1 -= 5;
		if (angleArm2 > 180)
			angleArm2 -= 5;
		if (angleLeg1 < 0)
			angleLeg1 += 5;
		if (angleLeg2 > 0)
			angleLeg2 -= 5;
		if (angleBody > 0)
			angleBody -= 5;
	}


	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

afx_msg BOOL CKolokvijum2019View::OnEraseBkgnd(CDC* pdc) {
	return TRUE;
}
