
// Kolokvijum2023View.cpp : implementation of the CKolokvijum2023View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kolokvijum2023.h"
#endif

#include "Kolokvijum2023Doc.h"
#include "Kolokvijum2023View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TORAD 3.141592/180
#define TODEG 180 / 3.141592

// CKolokvijum2023View

IMPLEMENT_DYNCREATE(CKolokvijum2023View, CView)

BEGIN_MESSAGE_MAP(CKolokvijum2023View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKolokvijum2023View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CKolokvijum2023View construction/destruction

CKolokvijum2023View::CKolokvijum2023View() noexcept
{
	glava.Load(L"glava.png");
	nadkolenica.Load(L"nadkolenica.png");
	podkolenica.Load(L"podkolenica.png");
	podlaktica.Load(L"podlaktica.png");
	nadlaktica.Load(L"nadlaktica.png");
	saka.Load(L"saka.png");
	stopalo.Load(L"saka.png");
	telo.Load(L"telo.png");
	pozadina.Load(L"pozadina.jpg");

	nadlakticaUgao = 0;
	podlakticaUgao = 0;
	robotUgao = 0;
	sakaUgao = 0;
	robotScale = 1;
}

CKolokvijum2023View::~CKolokvijum2023View()
{
}

BOOL CKolokvijum2023View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CKolokvijum2023View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply) {
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
void CKolokvijum2023View::Rotate(CDC* pDC, float angle, bool rightMultiply) {
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
void CKolokvijum2023View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply) {
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



void CKolokvijum2023View::DrawImgTransparent(CDC* pdc, DImage* pImage) {

	byte B = pImage->GetDIBBits()[0];
	byte G = pImage->GetDIBBits()[1];
	byte R = pImage->GetDIBBits()[2];

	CRect client;
	GetClientRect(&client);

	pImage->DrawTransparent(pdc, new CRect(0, 0, pImage->Width(), pImage->Height()), new CRect(-pImage->Width() / 2, -pImage->Height() / 2, pImage->Width()/2, pImage->Height()/2), RGB(R, G, B));
}


void CKolokvijum2023View::DrawHalf(CDC* pdc) {
	XFORM oldmatrix;
	pdc->GetWorldTransform(&oldmatrix);

	DrawImgTransparent(pdc, &telo);

	//Doci na mesto na telu gde nadlaktica dolazi
	Translate(pdc, -(telo.Width() / 2 - 25), -(telo.Height() / 2 - 65), false);
		//Posto ce da crta centar podlaktice, mora da se pomerim na (35,35) u prostoru nadlaktice
		Rotate(pdc, nadlakticaUgao, false);
		Translate(pdc, (nadlaktica.Width() / 2 - 35), (nadlaktica.Height()/2 - 35), false);
		{
			DrawImgTransparent(pdc, &nadlaktica);

			//Idemo na tacku gde treba da se nadoveze podlaktica
			Translate(pdc, -(nadlaktica.Width() / 2 - 22), -(nadlaktica.Height() / 2 - 167), false);
			//Idemo na centar podlaktice
			Rotate(pdc, podlakticaUgao, false);
			Translate(pdc, (podlaktica.Width() / 2 - 30), (podlaktica.Height() / 2 - 33), false);
			{
				DrawImgTransparent(pdc, &podlaktica);

				//Idemo na tacku gde se nadovezuje saka
				Translate(pdc, -(podlaktica.Width() / 2 - 30), -(podlaktica.Height() / 2 - 140), false);

				//Idemo na centar sake
				Rotate(pdc, sakaUgao, false);
				Translate(pdc, (saka.Width() / 2 - 25), (saka.Height() / 2 - 3), false);
				DrawImgTransparent(pdc, &saka);

				//Vracamo se na centar podlaktice
				Translate(pdc, -(saka.Width() / 2 - 25), -(saka.Height() / 2 - 3), false);
				Rotate(pdc, -sakaUgao, false);

				//Vracanje na centar podlaktice
				Translate(pdc, (podlaktica.Width() / 2 - 30), (podlaktica.Height() / 2 - 140), false);
			}
			//Idemo na spoj nad i podlaktice
			Translate(pdc, -(podlaktica.Width() / 2 - 30), -(podlaktica.Height() / 2 - 33), false);
			Rotate(pdc, -podlakticaUgao, false);

			//Vracanje u centar nadlaktice
			Translate(pdc, (nadlaktica.Width() / 2 - 22), (nadlaktica.Height() / 2 - 167), false);
		}
		//Vracanje u spoj tela i nadlaktice
		Translate(pdc, -(nadlaktica.Width() / 2 - 35), -(nadlaktica.Height() / 2 - 35), false);
		Rotate(pdc, -nadlakticaUgao, false);
		
	//Vracanje u centar tela
	Translate(pdc, (telo.Width() / 2 - 25), (telo.Height() /2 - 65), false);

	//Idemo na tacku gde se nadovezuje nadkolenica
	Translate(pdc, -(telo.Width() / 2 - 61), -(telo.Height() / 2 - 262), false);

		//Idemo na centar nadkolenice
		Translate(pdc, (nadkolenica.Width() / 2 - 29), (nadkolenica.Height() / 2 - 20), false);
		DrawImgTransparent(pdc, &nadkolenica);

		//Idemo sad na mesto gde se nadovezuje podkolenica
		Translate(pdc, -(nadkolenica.Width() / 2 - 30), -(nadkolenica.Height() / 2 - 184), false);

			//Idemo na centar podkolenice
			Translate(pdc, (podkolenica.Width() / 2 - 25), (podkolenica.Height() / 2 - 37), false);
			DrawImgTransparent(pdc, &podkolenica);

			//Idemo na spoj podkolenice i stopala
			Translate(pdc, -(podkolenica.Width() / 2 - 25), -(podkolenica.Height() / 2 - 248), false);
				
				//Idemo na centar stopala
				Translate(pdc, (stopalo.Width() / 2 - 20), (stopalo.Height() / 2 - 16), false);
				//DrawImgTransparent(pdc, &stopalo);

				//Vracamo se na spoj stopala i podkolenice
				Translate(pdc, -(stopalo.Width() / 2 - 20), -(stopalo.Height() / 2 - 16), false);

			//Vracamo se na centar podkolenice
			Translate(pdc, (podkolenica.Width() / 2 - 25), (podkolenica.Height() / 2 - 248), false);

			//Vracamo se na mesto gde se spajaju pod i nadkolenica
			Translate(pdc, -(podkolenica.Width() / 2 - 25), -(podkolenica.Height() / 2 - 37), false);

		//Vracamo se na centar nadkolenice
		Translate(pdc, (nadkolenica.Width() / 2 - 30), (nadkolenica.Height() / 2 - 184), false);

		//Vracamo se na mesto na telu gde se nadovezuje nadkolenica
		Translate(pdc, -(nadkolenica.Width() / 2 - 29), -(nadkolenica.Height() / 2 - 20), false);

	//Vracamo se na centar tela
	Translate(pdc, (telo.Width() / 2 - 61), (telo.Height() / 2 - 262), false);

	pdc->SetWorldTransform(&oldmatrix);
}

void CKolokvijum2023View::DrawBackground(CDC* pdc) {

	CRect client;
	GetClientRect(&client);
	pozadina.Draw(pdc, new CRect(0, 0, pozadina.Width(), pozadina.Height()), new CRect(0, 0, client.Width(), client.Height()));
}

void CKolokvijum2023View::DrawHead(CDC* pDC)
{
	DrawImgTransparent(pDC, &glava);
}

void CKolokvijum2023View::DrawRobot(CDC* pdc) {

	XFORM matrix;
	pdc->GetWorldTransform(&matrix);

	Scale(pdc, robotScale, robotScale, false);
	Rotate(pdc, robotUgao, false);
	{
		//Leva strana
		Translate(pdc, -telo.Width() / 2, 0, false);

		DrawHalf(pdc);

		Translate(pdc, telo.Width() / 2, 0, false);

		//Desna strana
		Translate(pdc, telo.Width() / 2, 0, false);
		Scale(pdc, -1, 1, false);

		DrawHalf(pdc);

		Scale(pdc, -1, 1, false);
		Translate(pdc, -telo.Width() / 2, 0, false);

		//Glava
		Translate(pdc, 0, -(telo.Height() / 2 + glava.Height() / 2), false);

		DrawHead(pdc);

		Translate(pdc, 0, (telo.Height() / 2 + glava.Height() / 2), false);
	}
	Rotate(pdc, -robotUgao, false);
	Scale(pdc, 1 / robotScale, 1 / robotScale, false);

	pdc->SetWorldTransform(&matrix);
}

//Vreme : 1h43min











// CKolokvijum2023View drawing

void CKolokvijum2023View::OnDraw(CDC* pdc)
{
	CKolokvijum2023Doc* pDoc = GetDocument();
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
	memDC->FillSolidRect(client, RGB(200, 200, 200));

	int oldMode = memDC->SetGraphicsMode(GM_ADVANCED);

	//Crtanje u memDC
	{
		DrawBackground(memDC);
		
		Translate(memDC, client.Width()/2, client.Height()/2, false);
		
		DrawRobot(memDC);
		
		Translate(memDC, -client.Width() / 2, -client.Height() / 2, false);
	}
	pdc->BitBlt(0, 0, client.Width(), client.Height(), memDC, 0, 0, SRCCOPY);

	memDC->SetGraphicsMode(oldMode);
	memDC->SelectObject(oldBM);
	delete memDC;
}



















// CKolokvijum2023View printing


void CKolokvijum2023View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKolokvijum2023View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKolokvijum2023View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKolokvijum2023View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CKolokvijum2023View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKolokvijum2023View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CKolokvijum2023View diagnostics

#ifdef _DEBUG
void CKolokvijum2023View::AssertValid() const
{
	CView::AssertValid();
}

void CKolokvijum2023View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKolokvijum2023Doc* CKolokvijum2023View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKolokvijum2023Doc)));
	return (CKolokvijum2023Doc*)m_pDocument;
}
#endif //_DEBUG


// CKolokvijum2023View message handlers

afx_msg BOOL CKolokvijum2023View::OnEraseBkgnd(CDC * pdc)
{
	return TRUE;
}

void CKolokvijum2023View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'A')
	{
		if (sakaUgao < 30)
			sakaUgao += 5;
	}
	else if (nChar == 'S')
	{
		if (sakaUgao > -10)
			sakaUgao -= 5;
	}
	else if (nChar == 'D')
	{
		if (podlakticaUgao < 80)
			podlakticaUgao += 5;
	}
	else if (nChar == 'F')
	{
		if (podlakticaUgao > -10)
			podlakticaUgao -= 5;
	}
	else if (nChar == 'G')
	{
		if (nadlakticaUgao < 90)
			nadlakticaUgao += 5;
	}
	else if (nChar == 'H')
	{
		if (nadlakticaUgao > -10)
			nadlakticaUgao -= 5;
	}
	else if (nChar == VK_NUMPAD1)
	{
		robotUgao -= 3;
		robotScale -= 0.05;
	}
	else if (nChar == VK_NUMPAD2)
	{
		robotUgao += 3;
		robotScale += 0.05;
	}


	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
