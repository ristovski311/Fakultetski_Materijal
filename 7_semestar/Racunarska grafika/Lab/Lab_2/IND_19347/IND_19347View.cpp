
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

#define TORAD 3.141592/180
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
	cactus_angle = 0;
	cactus_part_angle = 0;

	mf_dark_part = GetEnhMetaFile(L".\\res\\cactus_part.emf");
	mf_light_part = GetEnhMetaFile(L".\\res\\cactus_part_light.emf");

	ENHMETAHEADER emh;
	GetEnhMetaFileHeader(mf_dark_part, sizeof(emh), &emh);
	int mfWidth = emh.rclBounds.right - emh.rclBounds.left;
	int mfHeight = emh.rclBounds.bottom - emh.rclBounds.top;
	int factor = 6;

	int factoredX = (mfWidth / 2) / factor;
	int factoredY = (mfHeight / 2) / factor;
	
	initialMetafileRectangle = CRect(-factoredX, -factoredY, factoredX, factoredY);
	
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
}

CIND19347View::~CIND19347View()
{
	DeleteEnhMetaFile(mf_dark_part);
	DeleteEnhMetaFile(mf_light_part);
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

void CIND19347View::Translate(CDC* pdc, float dX, float dY, bool rightMultiply) {
	XFORM trans;
	trans.eM11 = 1.0;
	trans.eM12 = 0.0;
	trans.eM21 = 0.0;
	trans.eM22 = 1.0;
	trans.eDx = dX;
	trans.eDy = dY;
	if (rightMultiply)
		pdc->ModifyWorldTransform(&trans, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&trans, MWT_LEFTMULTIPLY);
}

void CIND19347View::Scale(CDC* pdc, float sX, float sY, bool rightMultiply) {
	XFORM scale;
	scale.eM11 = sX;
	scale.eM12 = 0.0;
	scale.eM21 = 0.0;
	scale.eM22 = sY;
	scale.eDx = 0.0;
	scale.eDy = 0.0;
	if (rightMultiply)
		pdc->ModifyWorldTransform(&scale, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&scale, MWT_LEFTMULTIPLY);
}

void CIND19347View::Rotate(CDC* pdc, float angle, bool rightMultiply) {
	XFORM trans;
	trans.eM11 = cos(angle*TORAD);
	trans.eM12 = sin(angle*TORAD);
	trans.eM21 = -sin(angle*TORAD);
	trans.eM22 = cos(angle*TORAD);
	trans.eDx = 0.0;
	trans.eDy = 0.0;
	if (rightMultiply)
		pdc->ModifyWorldTransform(&trans, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&trans, MWT_LEFTMULTIPLY);
}

///
//CRTANJE KAKTUSA
///

void CIND19347View::DrawFigure(CDC* pdc) {

	XFORM prevMatrix;
	pdc->GetWorldTransform(&prevMatrix);
	
	CRect cactus_connector = new CRect(-10, -10, 10, 10);
	
	//Kaktus konektor u saksiji oko cega se ceo kaktus rotira
	float c_saksija_x = 10 * GSS;
	float c_saksija_y = 17 * GSS;

	//Centar kaktus konektora iznad najdebljeg kaktus dela
	float c_debeo_x = c_saksija_x;
	float c_debeo_y = c_saksija_y - 3 * GSS;

	//Centar kaktus konektora levog od tri tamna
	float c_levi_tamni_x = c_debeo_x - 2 * GSS;
	float c_levi_tamni_y = c_debeo_y - 2 * GSS;

	//Centar kaktus konektora oko kog se svetli deo kaktusa rotira
	float c_rotira_x = c_debeo_x + 2 * GSS;
	float c_rotira_y = c_debeo_y - 2 * GSS;

	//Centar kaktus konektora koji je najvise desno
	float c_najvise_desno_x = c_rotira_x + 3 * GSS;
	float c_najvise_desno_y = c_rotira_y;


	///
	//Rotirajuci svetli deo kaktusa
	///

	//Inicijalno postavljanje pozicije svetlog dela kaktusa (pomeren sa (0,0))
	Scale(pdc, 0.5, 2, true);
	Translate(pdc, c_najvise_desno_x, c_najvise_desno_y - initialMetafileRectangle.Height()/2 - cactus_connector.Height(), true);

	//Inicijalna rotacija oko svog kaktus konektora
	Translate(pdc, -c_najvise_desno_x, -c_najvise_desno_y, true);
	Rotate(pdc, 90, true);
	Translate(pdc, c_najvise_desno_x, c_najvise_desno_y, true);

	//Rotacija svetlog dela kaktusa oko svog kaktus konektora
	Translate(pdc, -c_najvise_desno_x, -c_najvise_desno_y, true);
	Rotate(pdc, cactus_part_angle, true);
	Translate(pdc, c_najvise_desno_x, c_najvise_desno_y, true);

	//Rotacija oko konektora na debelom donjem
	Translate(pdc, -c_debeo_x, -c_debeo_y, true);
	Rotate(pdc, cactus_angle, true);
	Translate(pdc, c_debeo_x, c_debeo_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Svetli deo kaktusa koji se rotira
	pdc->PlayMetaFile(mf_light_part, initialMetafileRectangle);
	
	pdc->SetWorldTransform(&prevMatrix);
	

	///
	//Kaktus deo tamni debeo na dnu
	///

	//Inicijalno pomeranje na poziciju
	Scale(pdc, 1.5, 2, true);
	Translate(pdc, c_saksija_x, c_saksija_y - initialMetafileRectangle.Height() / 2 - cactus_connector.Height(), true);
	
	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Crtanje
	pdc->PlayMetaFile(mf_dark_part, initialMetafileRectangle);

	pdc->SetWorldTransform(&prevMatrix);


	///
	//Tri kaktus dela iznad najveceg kaktus dela
	///

	//Sredisnji
	//
	//Inicijalno postavljanje pozicija
	Scale(pdc, 0.5, 2, true);
	Translate(pdc, c_debeo_x, c_debeo_y - initialMetafileRectangle.Height()/2 - 2 * cactus_connector.Height() / 3, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Crtanje
	pdc->PlayMetaFile(mf_dark_part, initialMetafileRectangle);

	pdc->SetWorldTransform(&prevMatrix);

	//Levi
	//
	//Inicijalno postavljanje pozicija
	Scale(pdc, 0.5, 2, true);
	Translate(pdc, c_debeo_x, c_debeo_y - initialMetafileRectangle.Height() / 2 - 3 * cactus_connector.Height() / 3, true);

	//Rotacija oko konektora ispod njega
	Translate(pdc, -c_debeo_x, -c_debeo_y, true);
	Rotate(pdc, -45, true);
	Translate(pdc, c_debeo_x, c_debeo_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Crtanje
	pdc->PlayMetaFile(mf_dark_part, initialMetafileRectangle);

	pdc->SetWorldTransform(&prevMatrix);

	//Desni - OVAJ SE SAD ROTIRA U NOVOM ZADATKU
	//
	//Inicijalno postavljanje pozicija
	Scale(pdc, 0.5, 2, true);
	Translate(pdc, c_debeo_x, c_debeo_y - initialMetafileRectangle.Height() / 2 - 3 * cactus_connector.Height() / 3, true);

	//Rotacija oko konektora ispod njega
	Translate(pdc, -c_debeo_x, -c_debeo_y, true);
	Rotate(pdc, 45, true);
	Translate(pdc, c_debeo_x, c_debeo_y, true);

	//Rotacija oko konektora na debelom donjem
	Translate(pdc, -c_debeo_x, -c_debeo_y, true);
	Rotate(pdc, cactus_angle, true);
	Translate(pdc, c_debeo_x, c_debeo_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Crtanje
	pdc->PlayMetaFile(mf_light_part, initialMetafileRectangle);

	pdc->SetWorldTransform(&prevMatrix);


	///
	// Kaktusi tamni na bivsem rotirajucem
	///

	//Uspravan
	// 
	//Inicijalno postavljanje pozicije
	Scale(pdc, 0.5, 2, true);
	Translate(pdc, c_rotira_x, c_rotira_y - initialMetafileRectangle.Height() / 2 - cactus_connector.Height(), true);

	//Rotacija oko konektora na debelom donjem
	Translate(pdc, -c_debeo_x, -c_debeo_y, true);
	Rotate(pdc, cactus_angle, true);
	Translate(pdc, c_debeo_x, c_debeo_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Crtanje
	pdc->PlayMetaFile(mf_dark_part, initialMetafileRectangle);

	pdc->SetWorldTransform(&prevMatrix);

	//Nalevo
	// 
	//Inicijalno postavljanje pozicije
	Scale(pdc, 0.5, 2, true);
	Translate(pdc, c_rotira_x, c_rotira_y - initialMetafileRectangle.Height() / 2 - cactus_connector.Height(), true);

	//Rotacija oko konektora ispod njega
	Translate(pdc, -c_rotira_x, -c_rotira_x, true);
	Rotate(pdc, 45, true);
	Translate(pdc, c_rotira_x, c_rotira_x, true);

	//Rotacija oko konektora na debelom donjem
	Translate(pdc, -c_debeo_x, -c_debeo_y, true);
	Rotate(pdc, cactus_angle, true);
	Translate(pdc, c_debeo_x, c_debeo_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Crtanje
	pdc->PlayMetaFile(mf_dark_part, initialMetafileRectangle);

	pdc->SetWorldTransform(&prevMatrix);
		

	///
	// Tamni kaktus deo na bivsem rotirajucem konektoru ide nalevo
	///

	//Inicijalno pomeranje na poziciju
	Scale(pdc, 0.5, 2, true);
	Translate(pdc, c_rotira_x, c_rotira_y - initialMetafileRectangle.Height() / 2 - cactus_connector.Height(), true);

	//Rotacija oko svog konektora nadesno
	Translate(pdc, -c_rotira_x, -c_rotira_y, true);
	Rotate(pdc, 90, true);
	Translate(pdc, c_rotira_x, c_rotira_y, true);

	//Rotacija oko konektora na debelom donjem
	Translate(pdc, -c_debeo_x, -c_debeo_y, true);
	Rotate(pdc, cactus_angle, true);
	Translate(pdc, c_debeo_x, c_debeo_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Cratanje
	pdc->PlayMetaFile(mf_dark_part, initialMetafileRectangle);

	pdc->SetWorldTransform(&prevMatrix);


	///
	//Dva tamna kaktus dela na konektoru najvise desno iznad i ispod onog sto se sad rotira
	///

	//Nagore
	//
	//Inicijalno pomeranje na poziciju
	Scale(pdc, 0.5, 2, true);
	Translate(pdc, c_najvise_desno_x, c_najvise_desno_y - initialMetafileRectangle.Height() / 2 - cactus_connector.Height(), true);

	//Rotacija oko svog konektora
	Translate(pdc, -c_najvise_desno_x, -c_najvise_desno_y, true);
	Rotate(pdc, 45, true);
	Translate(pdc, c_najvise_desno_x, c_najvise_desno_y, true);

	//Rotacija oko konektora na debelom donjem
	Translate(pdc, -c_debeo_x, -c_debeo_y, true);
	Rotate(pdc, cactus_angle, true);
	Translate(pdc, c_debeo_x, c_debeo_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Crtanje
	pdc->PlayMetaFile(mf_dark_part, initialMetafileRectangle);

	pdc->SetWorldTransform(&prevMatrix);

	//Nadole
	//
	//Inicijalno pomeranje na poziciju
	Scale(pdc, 0.5, 2, true);
	Translate(pdc, c_najvise_desno_x, c_najvise_desno_y - initialMetafileRectangle.Height() / 2 - cactus_connector.Height(), true);

	//Rotacija oko svog konektora
	Translate(pdc, -c_najvise_desno_x, -c_najvise_desno_y, true);
	Rotate(pdc, 135, true);
	Translate(pdc, c_najvise_desno_x, c_najvise_desno_y, true);

	//Rotacija oko konektora na debelom donjem
	Translate(pdc, -c_debeo_x, -c_debeo_y, true);
	Rotate(pdc, cactus_angle, true);
	Translate(pdc, c_debeo_x, c_debeo_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Crtanje
	pdc->PlayMetaFile(mf_dark_part, initialMetafileRectangle);

	pdc->SetWorldTransform(&prevMatrix);


	///
	// Debeo kaktus na vrhu
	///

	//Inicijalno postavljanje pozicije
	Scale(pdc, 1.5, 2, true);
	Translate(pdc, c_levi_tamni_x, c_levi_tamni_y - initialMetafileRectangle.Height() / 2 - cactus_connector.Height(), true);

	//Rotacija oko svog konektora
	Translate(pdc, -c_levi_tamni_x, -c_levi_tamni_y, true);
	Rotate(pdc, -45, true);
	Translate(pdc, c_levi_tamni_x, c_levi_tamni_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Crtanje
	pdc->PlayMetaFile(mf_dark_part, initialMetafileRectangle);

	pdc->SetWorldTransform(&prevMatrix);


	///
	////// KONEKTORI
	///


	///
	//Konektor oko kog se svetli deo kaktusa rotirao nekad
	///

	CPen* newpen = new CPen(PS_COSMETIC, 1, RGB(0, 128, 0));
	CPen* oldpen = pdc->SelectObject(newpen);

	CBrush* newbrush = new CBrush(RGB(0, 180, 0));
	CBrush* oldbrush = pdc->SelectObject(newbrush);

	Translate(pdc, c_rotira_x, c_rotira_y, true);

	//Rotacija oko konektora na debelom donjem
	Translate(pdc, -c_debeo_x, -c_debeo_y, true);
	Rotate(pdc, cactus_angle, true);
	Translate(pdc, c_debeo_x, c_debeo_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Crtanje
	pdc->Ellipse(cactus_connector);
	
	pdc->SetWorldTransform(&prevMatrix);


	///
	//Konektor levog od tri tamna
	///

	//Inicijalno pomeranje na poziciju
	Translate(pdc, c_levi_tamni_x, c_levi_tamni_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Crtanje
	pdc->Ellipse(cactus_connector);

	pdc->SetWorldTransform(&prevMatrix);


	///
	//Konektor najvise desno
	///

	//Inicijalno pomeranje na poziciju
	Translate(pdc, c_najvise_desno_x, c_najvise_desno_y, true);

	//Rotacija oko konektora na debelom donjem
	Translate(pdc, -c_debeo_x, -c_debeo_y, true);
	Rotate(pdc, cactus_angle, true);
	Translate(pdc, c_debeo_x, c_debeo_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Crtanje
	pdc->Ellipse(cactus_connector);

	pdc->SetWorldTransform(&prevMatrix);
	

	///
	//Konektor iznad najveceg kaktus dela - sad je on oko koga se rotiraju desni delovi
	///

	//Inicijalno pomeranje na poziciju
	Translate(pdc, c_debeo_x, c_debeo_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	//Crtanje
	pdc->Ellipse(cactus_connector);
	pdc->SetWorldTransform(&prevMatrix);

	//
	//Kaktus konektor u saksiji
	//

	Translate(pdc, c_saksija_x, c_saksija_y, true);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	pdc->Ellipse(cactus_connector);
	pdc->SetWorldTransform(&prevMatrix);

	delete newpen;
	delete newbrush;

	///
	//SAKSIJA
	///

	newbrush = new CBrush(RGB(222, 148, 0));
	oldbrush = pdc->SelectObject(newbrush);
	newpen = new CPen(PS_COSMETIC, 1, RGB(0, 0, 0));
	oldpen = pdc->SelectObject(newpen);

	//Rotacija da slika bude okrenuta
	Translate(pdc, -250, -250, true);
	Rotate(pdc, 90, true);
	Translate(pdc, 250, 250, true);

	pdc->Rectangle(7.5 * GSS, 17.2 * GSS, 12.5 * GSS, 18 * GSS);

	POINT pts[4] = {
		CPoint(8 * GSS,18 * GSS),
		CPoint(12 * GSS,18 * GSS),
		CPoint(11.5 * GSS,20 * GSS),
		CPoint(8.5 * GSS,20 * GSS)
	};

	pdc->Polygon(pts, 4);

	pdc->SetWorldTransform(&prevMatrix);

	//Vracanje svega na prvobitno stanje
	pdc->SelectObject(oldpen);
	pdc->SelectObject(oldbrush);
	delete newpen;
	delete newbrush;
}


//
// ONDRAW
//


void CIND19347View::OnDraw(CDC* pdc)
{
	CIND19347Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	///
	//Postavljamo advanced graphics mode
	///

	int prevMode = pdc->SetGraphicsMode(GM_ADVANCED);
	DWORD dw = GetLastError();
	if (dw != 0)
	{
		AfxMessageBox(_T("Greska pri postavljanju GM_ADVANCED!"));
		return;
	}

	///
	//Plava pozadina
	///

	CPen* newpen;
	CPen* oldpen = (CPen*)pdc->SelectStockObject(NULL_PEN);

	CBrush* newbrush = new CBrush(RGB(135, 206, 235));
	CBrush* oldbrush = pdc->SelectObject(newbrush);

	pdc->Rectangle(grid);

	pdc->SelectObject(oldpen);
	pdc->SelectObject(oldbrush);

	delete newbrush;

	///
	//KAKTUS
	///

	//KOD ZA ZADATAK: 72072

	//DrawFigure(pdc);

	///
	// TEKST
	///

	//int prevBkMode = pdc->SetBkMode(TRANSPARENT);
	//CFont* newfont = new CFont();
	//
	////Moguce je i preko svetskih transformacija!
	///*XFORM prevMatrix;
	//pdc->GetWorldTransform(&prevMatrix);
	//Translate(pdc, -18 * GSS, -GSS, true);
	//Rotate(pdc, 90, true);
	//Translate(pdc, 18 * GSS, GSS, true);
	//newfont->CreateFontW(GSS, 12, 0, 0, 700, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial"); */
	//	
	//newfont->CreateFontW(30, 12, -900, -900, 600, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");
	//CFont* oldfont = pdc->SelectObject(newfont);
	//COLORREF oldFontColor = pdc->SetTextColor(RGB(0, 0, 0));
	//
	//pdc->SetTextColor(RGB(0, 0, 0)); //CRNA
	//pdc->TextOutW(19*GSS,GSS + 3 /*Da bude crni malo nize od zutog teksta*/, L"Biljka", 8);
	//pdc->SetTextColor(RGB(255, 255, 0)); //ZUTA
	//pdc->TextOutW(19 * GSS, GSS, L"Biljka", 8);

	//pdc->SelectObject(oldfont);
	//delete newfont;
	//pdc->SetBkMode(prevBkMode);

	//pdc->SetWorldTransform(&prevMatrix);

	///
	//Prikaz grid-a
	///

	if (show_grid)
		ShowGrid(pdc);

	pdc->SetGraphicsMode(prevMode);
	dw = GetLastError();
	if (dw != 0)
	{
		AfxMessageBox(_T("Greska pri vracanju normalnog GM!"));
		return;
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
	if (nChar == VK_RIGHT)
	{
		cactus_part_angle += 10;
	}
	else if (nChar == VK_LEFT)
	{
		cactus_part_angle -= 10;
	}
	else if (nChar == VK_UP)
	{
		cactus_angle += 10;
	}
	else if (nChar == VK_DOWN)
	{
		cactus_angle -= 10;
	}
	else
	{
		CRgn rgn;
		rgn.CreateRectRgn(grid.left, grid.top, grid.right, grid.bottom);
		show_grid = !show_grid;
	}
	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
