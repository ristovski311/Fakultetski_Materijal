
// Kolokvijum2015View.cpp : implementation of the CKolokvijum2015View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kolokvijum2015.h"
#endif

#include "Kolokvijum2015Doc.h"
#include "Kolokvijum2015View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TORAD 3.141592 / 180
#define TODEG 180 / 3.141592

// CKolokvijum2015View

IMPLEMENT_DYNCREATE(CKolokvijum2015View, CView)

BEGIN_MESSAGE_MAP(CKolokvijum2015View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKolokvijum2015View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CKolokvijum2015View construction/destruction

CKolokvijum2015View::CKolokvijum2015View() noexcept
{
	dx = 0;
	dy = 0;
	isUp = false;
	isDown = false;
	isLeft = false;
	isRight = true;
	mouthAngle = 30;

	pacmanPosX = 400;
	pacmanPosY = 400;


	background = new DImage();
	background->Load(L"blue.png");
}

CKolokvijum2015View::~CKolokvijum2015View()
{
	if (background)
		delete background;
}

BOOL CKolokvijum2015View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CKolokvijum2015View::Translate(CDC* pdc, int dx, int dy, bool rightMul) {

	XFORM matrix;
	matrix.eDx = dx;
	matrix.eDy = dy;
	matrix.eM11 = 1;
	matrix.eM12 = 0;
	matrix.eM21 = 0;
	matrix.eM22 = 1;

	if (rightMul)
		pdc->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);
}
void CKolokvijum2015View::Rotate(CDC* pdc, int angle, bool rightMul) {
	XFORM matrix;
	matrix.eDx = 0;
	matrix.eDy = 0;
	matrix.eM11 = cos(angle*TORAD);
	matrix.eM12 = sin(angle * TORAD);
	matrix.eM21 = -sin(angle * TORAD);
	matrix.eM22 = cos(angle * TORAD);

	if (rightMul)
		pdc->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);
}
void CKolokvijum2015View::Scale(CDC* pdc, int sx, int sy, bool rightMul) {
	XFORM matrix;
	matrix.eDx = 0;
	matrix.eDy = 0;
	matrix.eM11 = sx;
	matrix.eM12 = 0;
	matrix.eM21 = 0;
	matrix.eM22 = sy;

	if (rightMul)
		pdc->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);
}



void CKolokvijum2015View::DrawGhost(CDC* pDC, CRect rect) {

	XFORM oldmatrix;
	pDC->GetWorldTransform(&oldmatrix);

	Translate(pDC, rect.left - rect.Width() / 2, rect.top - rect.Height() / 2, false);
	CPen* newpen = new CPen(PS_COSMETIC, 1, RGB(0,0,0));
	CPen* oldPen = pDC->SelectObject(newpen);

	CBrush* newbrush = new CBrush(RGB(255, 0, 0));
	CBrush* oldbrush = pDC->SelectObject(newbrush);

	pDC->BeginPath();

	int shorterSide = rect.Width() >= rect.Height() ? rect.Height() : rect.Width();
	int longerSide = rect.Width() < rect.Height() ? rect.Height() : rect.Width();
	int longMinusShort = longerSide - shorterSide;

	int oldArcDir = pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->MoveTo(0, rect.Width()/2);
	pDC->ArcTo(0, 0, rect.Width(), rect.Width(), 0, rect.Width()/2, rect.Width(), rect.Width() / 2);
	pDC->LineTo(rect.Width(), rect.Height());

	int smallSide = rect.Width() / 6;
	CPoint center(rect.Width() , rect.Height() - smallSide/2);

	//Prvi poluarc dole desno
	pDC->ArcTo(center.x - smallSide/2, center.y - smallSide/2, center.x + smallSide / 2, center.y + smallSide / 2, center.x, center.y + smallSide/2, center.x - smallSide/2, center.y);

	center.x -= smallSide;

	for (int i = 0; i < 3; i++) {

		//Arc gore
		pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
		pDC->ArcTo(center.x - smallSide / 2, center.y - smallSide / 2, center.x + smallSide / 2, center.y + smallSide / 2, center.x + smallSide / 2, center.y, center.x - smallSide / 2, center.y);

		center.x -= smallSide;

		//Crtamo 3 arc-a nagore i samo 2 nadole 
		if (i == 2)
			continue;

		//Arc dole
		pDC->SetArcDirection(AD_CLOCKWISE);
		pDC->ArcTo(center.x - smallSide / 2, center.y - smallSide / 2, center.x + smallSide / 2, center.y + smallSide / 2, center.x + smallSide / 2, center.y, center.x - smallSide / 2, center.y);

		center.x -= smallSide;
	}

	//Poslednji levo poluarc
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->ArcTo(center.x - smallSide / 2, center.y - smallSide / 2, center.x + smallSide / 2, center.y + smallSide / 2, center.x + smallSide / 2, center.y, center.x, center.y + smallSide/2);

	//Linija da spojimo
	pDC->LineTo(0, rect.Width() / 2);

	pDC->EndPath();


	pDC->StrokeAndFillPath();

	int eyeRadiusOuter = rect.Width() / 8;
	int eyeRadiusInner = eyeRadiusOuter / 2;

	int eyeOffset = rect.Width() / 3;
	int innerEyeOffset = eyeRadiusOuter / 2;

	//Oko 1 spolja
	pDC->SelectObject(oldbrush);
	delete newbrush;
	newbrush = new CBrush(RGB(255, 255, 255));
	pDC->SelectObject(newbrush);
	pDC->Ellipse(rect.Width() / 3, rect.Height() / 3, rect.Width() / 3 + 2 * eyeRadiusOuter, rect.Height() / 3 + 2 * eyeRadiusOuter);

	//Oko 2 spolja
	pDC->Ellipse(rect.Width() / 3 + eyeOffset, rect.Height() / 3, rect.Width() / 3 + 2 * eyeRadiusOuter + eyeOffset, rect.Height() / 3 + 2 * eyeRadiusOuter);

	//Oko 1 unutra
	pDC->SelectObject(oldbrush);
	delete newbrush;
	newbrush = new CBrush(RGB(128, 128, 255));
	pDC->SelectObject(newbrush);
	pDC->Ellipse(rect.Width() / 3 + innerEyeOffset, rect.Height() / 3 + innerEyeOffset, rect.Width() / 3 + 2 * eyeRadiusInner + innerEyeOffset, rect.Height() / 3 + 2 * eyeRadiusInner + innerEyeOffset);

	//Oko 2 unutra
	pDC->Ellipse(rect.Width() / 3 + eyeOffset + innerEyeOffset, rect.Height() / 3 + innerEyeOffset, rect.Width() / 3 + 2 * eyeRadiusInner + eyeOffset + innerEyeOffset, rect.Height() / 3 + 2 * eyeRadiusInner + innerEyeOffset);
	
	Translate(pDC, -(rect.left - rect.Width() / 2), -(rect.top - rect.Height() / 2), false);


	pDC->SetArcDirection(oldArcDir);
	pDC->SelectObject(oldbrush);
	delete newbrush;
	pDC->SelectObject(oldPen);
	delete newpen;
	pDC->SetWorldTransform(&oldmatrix);

}


void CKolokvijum2015View::DrawPacman(CDC* pDC, CRect rect, float angle) {

	XFORM oldMatrix;
	pDC->GetWorldTransform(&oldMatrix);

	CBrush* newbrush = new CBrush(RGB(255, 255, 0));
	CBrush* oldbrush = pDC->SelectObject(newbrush);

	int mouthLen = (mouthAngle / 90) * rect.Height();
	int firsty = rect.top + (rect.Height() - mouthLen) / 2;
	int secondy = firsty + mouthLen;

	float angleToRotatePacman = 0;

	if (isUp)
		angleToRotatePacman = -90;
	else if (isDown)
		angleToRotatePacman = 90;


	//Pomeramo pacmana
	Translate(pDC, pacmanPosX, pacmanPosY, false);

	//Rotairamo ga
	Rotate(pDC, angleToRotatePacman, false);

	//Ako je nalevo mora mirror
	if (isLeft)
		Scale(pDC, -1, 1, false);
	

	//PacMan
	pDC->Pie(rect, CPoint(rect.right, firsty), CPoint(rect.right, secondy));
	pDC->SelectObject(&oldbrush);
	
	delete newbrush;
	newbrush = new CBrush(RGB(0, 0, 0));
	pDC->SelectObject(newbrush);

	//Oko
	Translate(pDC, 0.3 * rect.Width() / 2, -0.5 * rect.Height() / 2, false);
	pDC->Ellipse(-0.1 * rect.Width(), -0.1 * rect.Height(), 0.1 * rect.Width(), 0.1 * rect.Height());
	Translate(pDC, 0.3 * rect.Width() / 2, -0.5 * rect.Height() / 2, false);

	if (isLeft)
		Scale(pDC, -1, 1, false);
	Rotate(pDC, -angleToRotatePacman, false);
	Translate(pDC, -pacmanPosX, -pacmanPosY, false);



	pDC->SelectObject(oldbrush);
	delete newbrush;

	//pDC->SetWorldTransform(&oldMatrix);
}



void CKolokvijum2015View::DrawBackground(CDC* pdc) {
	
	CRect client;
	GetClientRect(&client);
	
	background->Draw(pdc, new CRect(0,0,background->Width(), background->Height()), client);
}

















// CKolokvijum2015View drawing

void CKolokvijum2015View::OnDraw(CDC* pdc)
{
	CKolokvijum2015Doc* pDoc = GetDocument();
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
	int oldMode = memdc->SetGraphicsMode(GM_ADVANCED);

	//CRTANJE U MEMDC
	{
		XFORM oldmatrix;
		memdc->GetWorldTransform(&oldmatrix);

		DrawBackground(memdc);
		DrawGhost(memdc, CRect(100, 120, 196, 216));

		DrawPacman(memdc, CRect(-50,-50,50,50), mouthAngle);



		memdc->SetWorldTransform(&oldmatrix);
	}

	pdc->BitBlt(0, 0, client.Width(), client.Height(), memdc, 0, 0, SRCCOPY);

	memdc->SetGraphicsMode(oldMode);
	memdc->SelectObject(oldbm);
	delete memdc;
}













// CKolokvijum2015View printing


void CKolokvijum2015View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKolokvijum2015View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKolokvijum2015View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKolokvijum2015View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CKolokvijum2015View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKolokvijum2015View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CKolokvijum2015View diagnostics

#ifdef _DEBUG
void CKolokvijum2015View::AssertValid() const
{
	CView::AssertValid();
}

void CKolokvijum2015View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKolokvijum2015Doc* CKolokvijum2015View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKolokvijum2015Doc)));
	return (CKolokvijum2015Doc*)m_pDocument;
}
#endif //_DEBUG


// CKolokvijum2015View message handlers

afx_msg BOOL CKolokvijum2015View::OnEraseBkgnd(CDC* pdc) {
	return TRUE;
}


void CKolokvijum2015View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CRect client;
	GetClientRect(&client);

	if (nChar == VK_UP)
	{
		isUp = true;
		isDown = isLeft = isRight = false;
		pacmanPosY -= 10;

		if (pacmanPosY < 0)
			pacmanPosY = client.Height();

		if (mouthAngle == 0)
			mouthAngle = 30;
		else
			mouthAngle = 0;
	}
	else if (nChar == VK_DOWN)
	{
		isDown = true;
		isUp = isLeft = isRight = false;
		pacmanPosY += 10;

		if (pacmanPosY > client.Height())
			pacmanPosY = 0;

		if (mouthAngle == 0)
			mouthAngle = 30;
		else
			mouthAngle = 0;
	}
	else if (nChar == VK_RIGHT)
	{
		isRight = true;
		isDown = isLeft = isUp = false;
		pacmanPosX += 10;

		if (pacmanPosX > client.Width())
			pacmanPosX = 0;


		if (mouthAngle == 0)
			mouthAngle = 30;
		else
			mouthAngle = 0;
	}
	else if (nChar == VK_LEFT)
	{
		isLeft = true;
		isDown = isUp = isRight = false;
		pacmanPosX -= 10;

		if (pacmanPosX < 0)
			pacmanPosX = client.Width();

		if (mouthAngle == 0)
			mouthAngle = 30;
		else
			mouthAngle = 0;
	}

	Invalidate(FALSE);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
