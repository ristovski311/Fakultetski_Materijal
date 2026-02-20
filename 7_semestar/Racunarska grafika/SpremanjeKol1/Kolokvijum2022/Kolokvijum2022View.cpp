
// Kolokvijum2022View.cpp : implementation of the CKolokvijum2022View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kolokvijum2022.h"
#endif

#include "Kolokvijum2022Doc.h"
#include "Kolokvijum2022View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TORAD 3.141592 / 180
#define TODEG 180 / 3.141592

// CKolokvijum2022View

IMPLEMENT_DYNCREATE(CKolokvijum2022View, CView)

BEGIN_MESSAGE_MAP(CKolokvijum2022View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKolokvijum2022View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CKolokvijum2022View construction/destruction

CKolokvijum2022View::CKolokvijum2022View() noexcept
{
	base = new DImage();
	arm1 = new DImage();
	arm2 = new DImage();
	head = new DImage();
	pozadina = new DImage();
	baseShadow = new DImage();
	arm1Shadow = new DImage();
	arm2Shadow = new DImage();
	headShadow = new DImage();

	base->Load(L"base.png");
	arm1->Load(L"arm1.png");
	arm2->Load(L"arm2.png");
	head->Load(L"head.png");
	pozadina->Load(L"pozadina.jpg");
	baseShadow->Load(L"base_shadow.png");
	arm1Shadow->Load(L"arm1_shadow.png");
	arm2Shadow->Load(L"arm2_shadow.png");
	headShadow->Load(L"head_shadow.png");

	arm1Angle = 45;
	arm2Angle = -90;
	headAngle = 180; //Ne znam zasto mi iscrtava inicijalno zarotiranog za -90 bukv nemam ideju, help

}

CKolokvijum2022View::~CKolokvijum2022View()
{
	if (base)
		delete base;
	if (arm1)
		delete arm1;
	if (arm2)
		delete arm2;
	if (head)
		delete head;
	if (pozadina)
		delete pozadina;
	if (baseShadow)
		delete baseShadow;
	if (arm1Shadow)
		delete arm1Shadow;
	if (arm2Shadow)
		delete arm2Shadow;
	if (headShadow)
		delete headShadow;
}

BOOL CKolokvijum2022View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CKolokvijum2022View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply) {
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
void CKolokvijum2022View::Rotate(CDC* pDC, float angle, bool rightMultiply){
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
void CKolokvijum2022View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply) {
	XFORM matrix;
	matrix.eDx = 0;
	matrix.eDy = 0;
	matrix.eM11 = sX;
	matrix.eM12 = 0;
	matrix.eM21 = 0;
	matrix.eM22 = sY;

	if (rightMultiply)
		pDC->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pDC->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);

}

void CKolokvijum2022View::DrawBackground(CDC* pDC) {

	CRect client;
	GetClientRect(&client);

	pozadina->Draw(pDC, new CRect(0, 0, pozadina->Width(), pozadina->Height()), client);
}

void CKolokvijum2022View::DrawImgTransparent(CDC* pDC, DImage* pImage) {

	byte B = pImage->GetDIBBits()[0];
	byte G = pImage->GetDIBBits()[1];
	byte R = pImage->GetDIBBits()[2];

	pImage->DrawTransparent(pDC, new CRect(0, 0, pImage->Width(), pImage->Height()), new CRect(-pImage->Width() / 2, -pImage->Height() / 2, pImage->Width() / 2, pImage->Height() / 2), RGB(R,G,B));
}

void CKolokvijum2022View::DrawLampBase(CDC* pDC, bool bIsShadow) {

	XFORM oldMatrix;
	pDC->GetWorldTransform(&oldMatrix);

	if(!bIsShadow)
		DrawImgTransparent(pDC, base);
	else
		DrawImgTransparent(pDC, baseShadow);

	//Idemo na poziciju gde cemo nadovezati arm1
	Translate(pDC, -(base->Width()/2 - 167), -(base->Height()/2 - 39), false); //167 39

	//pDC->SetWorldTransform(&oldMatrix);
}

void CKolokvijum2022View::DrawLampArm1(CDC* pDC, bool bIsShadow) {

	XFORM oldMatrix;
	pDC->GetWorldTransform(&oldMatrix);

	Rotate(pDC, arm1Angle - 90, false);
	// Na centar lampe
	Translate(pDC, (arm1->Width()/2 - 58), (arm1->Height()/2 - 61), false);
	
	if (!bIsShadow)
		DrawImgTransparent(pDC, arm1);
	else
		DrawImgTransparent(pDC, arm1Shadow);

	//Idemo na poziciju manjeg kruga (309, 61)
	Translate(pDC, -(arm1->Width() / 2 - 309), -(arm1->Height() / 2 - 61), false);

}

void CKolokvijum2022View::DrawLampArm2(CDC* pDC, bool bIsShadow) {

	Rotate(pDC, arm2Angle, false);
	//Idemo na centar manje ruke
	Translate(pDC, (arm2->Width() / 2 - 36), (arm2->Height() / 2 - 40), false);

	//Idemo na poziciju gde nadovezujemo glavu odmah, da bi glava bila ispod GDI SLOVA
	Translate(pDC, -(arm2->Width()/2 - 272), -(arm2->Height()/2 - 40), false);
	DrawLampHead(pDC, bIsShadow); 
	
	//Posle ovog iscrtavanja ja sam idalje u spoju, mora da se vratim na centar arm2
	Translate(pDC, (arm2->Width() / 2 - 272), (arm2->Height() / 2 - 40), false);

	if(!bIsShadow)
		DrawImgTransparent(pDC, arm2);
	else
		DrawImgTransparent(pDC, arm2Shadow);
}

void CKolokvijum2022View::DrawLampHead(CDC* pDC, bool bIsShadow) {

	XFORM oldMatrix;
	pDC->GetWorldTransform(&oldMatrix);

	Rotate(pDC,headAngle, false);
	//idemo na centar glave
	Translate(pDC, (head->Width() / 2 - 178), (head->Height() / 2 - 100), false);
	
	if (!bIsShadow)
		DrawImgTransparent(pDC, head);
	else
		DrawImgTransparent(pDC, headShadow);

	pDC->SetWorldTransform(&oldMatrix);
}

void CKolokvijum2022View::DrawLamp(CDC* pDC, bool bIsShadow) {

	XFORM matrixOld;
	pDC->GetWorldTransform(&matrixOld);

	DrawLampBase(pDC, bIsShadow);
	DrawLampArm1(pDC, bIsShadow);
	DrawLampArm2(pDC, bIsShadow);

	pDC->SetWorldTransform(&matrixOld);
}

void CKolokvijum2022View::DrawLampShadow(CDC* pDC) {

	XFORM oldMatrix;
	pDC->GetWorldTransform(&oldMatrix);

	Scale(pDC, 1, 0.25, false);
	Rotate(pDC, -90, false);

	DrawLamp(pDC, true);

	Rotate(pDC, 90, false);
	Scale(pDC, 1, 4, false);

	pDC->SetWorldTransform(&oldMatrix);
}

//Vreme : 1h 20min

// CKolokvijum2022View drawing

void CKolokvijum2022View::OnDraw(CDC* pdc)
{
	CKolokvijum2022Doc* pDoc = GetDocument();
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
	int oldMode = memDC->SetGraphicsMode(GM_ADVANCED);

	memDC->FillSolidRect(client, RGB(213, 231, 51));

	//CRTANJE U MEMDC
	{
		XFORM oldMatrix;
		memDC->GetWorldTransform(&oldMatrix);
		DrawBackground(memDC);

		Translate(memDC, client.Width() * 0.65, client.Height() * 0.8, false);

		DrawLampShadow(memDC);
		DrawLamp(memDC, false);

		Translate(memDC, -client.Width() * 0.65, -client.Height() * 0.8, false);
	
		memDC->SetWorldTransform(&oldMatrix);
	}


	pdc->BitBlt(0,0, client.Width(), client.Height(), memDC, 0, 0, SRCCOPY);


	memDC->SetGraphicsMode(oldMode);
	memDC->SelectObject(oldBM);
	delete memDC;
}

















// CKolokvijum2022View printing


void CKolokvijum2022View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKolokvijum2022View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKolokvijum2022View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKolokvijum2022View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CKolokvijum2022View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKolokvijum2022View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CKolokvijum2022View diagnostics

#ifdef _DEBUG
void CKolokvijum2022View::AssertValid() const
{
	CView::AssertValid();
}

void CKolokvijum2022View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKolokvijum2022Doc* CKolokvijum2022View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKolokvijum2022Doc)));
	return (CKolokvijum2022Doc*)m_pDocument;
}
#endif //_DEBUG


// CKolokvijum2022View message handlers

afx_msg BOOL CKolokvijum2022View::OnEraseBkgnd(CDC* pdc) {
	return TRUE;
}


void CKolokvijum2022View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if (nChar == VK_NUMPAD1)
		arm1Angle -= 10;
	else if (nChar == VK_NUMPAD2)
		arm1Angle += 10;
	else if (nChar == VK_NUMPAD4)
		arm2Angle -= 10;
	else if (nChar == VK_NUMPAD5) //umesto 3 i 4, ide 4 i 5, a umesto 5 i 6 ide 7 i 8 jer je logicnije
		arm2Angle += 10;
	else if (nChar == VK_NUMPAD7)
		headAngle -= 10;
	else if (nChar == VK_NUMPAD8)
		headAngle += 10;


	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
