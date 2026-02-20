
// Kolokvijum1View.cpp : implementation of the CKolokvijum1View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Kolokvijum1.h"
#endif

#include "Kolokvijum1Doc.h"
#include "Kolokvijum1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TORAD(x) ((x) * (3.141592 / 180))

// CKolokvijum1View

IMPLEMENT_DYNCREATE(CKolokvijum1View, CView)

BEGIN_MESSAGE_MAP(CKolokvijum1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CKolokvijum1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CKolokvijum1View construction/destruction

CKolokvijum1View::CKolokvijum1View() noexcept
{
	// TODO: add construction code here

}

CKolokvijum1View::~CKolokvijum1View()
{
}

BOOL CKolokvijum1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}



void CKolokvijum1View::Rotate(CDC* pdc, float angle, bool rightMul) {
	XFORM matrix;

	matrix.eDx = 0;
	matrix.eDy = 0;
	matrix.eM11 = cos(TORAD(angle));
	matrix.eM12 = sin(TORAD(angle));
	matrix.eM21 = -sin(TORAD(angle));
	matrix.eM22 = cos(TORAD(angle));

	if (rightMul)
		pdc->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);
}
void CKolokvijum1View::Translate(CDC* pdc, int dx, int dy, bool rightMul) {
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
void CKolokvijum1View::Scale(CDC* pdc, float sX, float sY, bool rightMul) {
	XFORM matrix;

	matrix.eDx = 0;
	matrix.eDy = 0;
	matrix.eM11 = sX;
	matrix.eM12 = 0;
	matrix.eM21 = 0;
	matrix.eM22 = sY;

	if (rightMul)
		pdc->ModifyWorldTransform(&matrix, MWT_RIGHTMULTIPLY);
	else
		pdc->ModifyWorldTransform(&matrix, MWT_LEFTMULTIPLY);
}

void createWeirdShape(CDC* pdc,int size, int widthLine, COLORREF colorPen, COLORREF colorBrush) {

	CPen* newpen = new CPen(PS_COSMETIC, widthLine, colorPen);
	CBrush* newbrush = new CBrush(colorBrush);

	CPen* oldpen = pdc->SelectObject(newpen);
	CBrush* oldbrush = pdc->SelectObject(newbrush);

	int x_side = size;
	int y_side = size;

	int x_side_smaller = x_side / 3;
	int y_side_smaller = y_side / 3;

	int x_curr = -size/2;
	int y_curr = -size/2;

	pdc->BeginPath();

	//Prvi kvadrat
	int oldArtDirection = pdc->SetArcDirection(AD_COUNTERCLOCKWISE);
	pdc->MoveTo(x_curr + x_side_smaller / 2, y_curr + y_side_smaller);
	pdc->ArcTo(x_curr, y_curr, x_curr + x_side_smaller, y_curr + y_side_smaller ,x_curr + x_side_smaller / 2, y_curr + y_side_smaller ,x_curr + x_side_smaller, y_curr + y_side_smaller / 2);
	x_curr += x_side_smaller;

	//Drugi kvadrat
	pdc->SetArcDirection(AD_CLOCKWISE);
	pdc->ArcTo(x_curr, y_curr, x_curr + x_side_smaller, y_curr + y_side_smaller, x_curr, y_curr + y_side_smaller / 2, x_curr + x_side_smaller, y_curr + y_side_smaller / 2);
	x_curr += x_side_smaller;

	//Treci kvadrat
	pdc->SetArcDirection(AD_COUNTERCLOCKWISE);
	pdc->ArcTo(x_curr, y_curr, x_curr + x_side_smaller, y_curr + y_side_smaller, x_curr, y_curr + y_side_smaller / 2, x_curr + x_side_smaller / 2, y_curr + y_side_smaller);
	y_curr += y_side_smaller;

	//Cetvrti kvadrat
	pdc->SetArcDirection(AD_CLOCKWISE);
	pdc->ArcTo(x_curr, y_curr, x_curr + x_side_smaller, y_curr + y_side_smaller, x_curr + x_side_smaller / 2, y_curr, x_curr + x_side_smaller / 2, y_curr + y_side_smaller);;
	y_curr += y_side_smaller;

	//Peti kvadrat
	pdc->SetArcDirection(AD_COUNTERCLOCKWISE);
	pdc->ArcTo(x_curr, y_curr, x_curr + x_side_smaller, y_curr + y_side_smaller, x_curr + x_side_smaller / 2, y_curr, x_curr, y_curr + y_side_smaller / 2);
	x_curr -= x_side_smaller;

	//Sesti kvadrat
	pdc->SetArcDirection(AD_CLOCKWISE);
	pdc->ArcTo(x_curr, y_curr, x_curr + x_side_smaller, y_curr + y_side_smaller, x_curr + x_side_smaller, y_curr + y_side_smaller / 2, x_curr, y_curr + y_side_smaller / 2);
	x_curr -= x_side_smaller;

	//Sedmi kvadrat
	pdc->SetArcDirection(AD_COUNTERCLOCKWISE);
	pdc->ArcTo(x_curr, y_curr, x_curr + x_side_smaller, y_curr + y_side_smaller, x_curr + x_side_smaller, y_curr + y_side_smaller/2, x_curr + x_side_smaller / 2, y_curr);
	y_curr -= y_side_smaller;

	//Osmi kvadrat
	pdc->SetArcDirection(AD_CLOCKWISE);
	pdc->ArcTo(x_curr, y_curr, x_curr + x_side_smaller, y_curr + y_side_smaller, x_curr + x_side_smaller / 2, y_curr + y_side_smaller , x_curr + x_side_smaller / 2, y_curr);

	pdc->EndPath();

	//Crtanje
	pdc->StrokeAndFillPath();

	pdc->SelectObject(oldpen);
	delete newpen;
	pdc->SelectObject(oldbrush);
	delete newbrush;
	pdc->SetArcDirection(oldArtDirection);
}

void createMultiWeirdShape(CDC* pdc, int size, int lineWidth, float ratio, COLORREF colorPen, COLORREF aColorBrush[]) {

	int outerSize = size * ratio;
	int innerSize = size / ratio;

	//Spoljasnji
	createWeirdShape(pdc, outerSize, lineWidth, colorPen, aColorBrush[0]);
	//Sredisnji
	createWeirdShape(pdc, size, lineWidth, colorPen, aColorBrush[1]);
	//Unutrasnji
	createWeirdShape(pdc, innerSize, lineWidth, colorPen, aColorBrush[2]);
}

void DrawLabel(CDC* pdc, int fontHeight, COLORREF colorText, CString text)
{
	int oldMode = pdc->SetBkMode(TRANSPARENT);

	CFont font;
	font.CreateFontW(fontHeight, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");
	CFont* oldfont = pdc->SelectObject(&font);
	int oldAlign = pdc->SetTextAlign(TA_CENTER | TA_BASELINE);
	COLORREF oldTextClr = pdc->SetTextColor(colorText);
	pdc->TextOutW(0, 0, text);

	pdc->SelectObject(oldfont);
	pdc->SetBkMode(oldMode);
	pdc->SetTextAlign(oldAlign);
	pdc->SetTextColor(oldTextClr);
}

HENHMETAFILE CreateArcThreeSpots(CDC* pdc, int size, COLORREF aColFill[], int width, COLORREF colLine, float ratio) {

	CMetaFileDC MetaDC;
	int outerSize = ratio * size;
	CRect rect = CRect(-outerSize / 2, -outerSize / 2, outerSize / 2, outerSize / 2);

	CSize sizeMM(pdc->GetDeviceCaps(HORZSIZE), pdc->GetDeviceCaps(VERTSIZE));
	CSize sizePX(pdc->GetDeviceCaps(HORZRES), pdc->GetDeviceCaps(VERTRES));

	rect.top *= (sizeMM.cy * 100) / sizePX.cy;
	rect.bottom *= (sizeMM.cy * 100) / sizePX.cy;
	rect.right *= (sizeMM.cx * 100) / sizePX.cx;
	rect.left *= (sizeMM.cx * 100) / sizePX.cx;

	//Memorijski metafile - NULL za naziv
	MetaDC.CreateEnhanced(pdc, NULL, rect, L"Zadatak 1");
	MetaDC.SetAttribDC(pdc->m_hDC);
	createMultiWeirdShape(&MetaDC, size, width, ratio, colLine, aColFill);
	MetaDC.ReleaseAttribDC();
	HENHMETAFILE hEMF = MetaDC.CloseEnhanced();
	MetaDC.DeleteDC();

	return hEMF;

}

void CKolokvijum1View::DrawArcSpotsPattern(CDC* pdc, int rows, int cols, float dX, float dY, float alpha, HENHMETAFILE mf, int size, COLORREF colText) {

	ENHMETAHEADER header;
	GetEnhMetaFileHeader(mf, sizeof(ENHMETAHEADER), &header);
	CRect rect(header.rclBounds.left, header.rclBounds.top, header.rclBounds.right, header.rclBounds.bottom);

	XFORM staraMatrica;
	pdc->GetWorldTransform(&staraMatrica);
	CString labela;

	int evenRowsPadding = (size + dX) / 2;

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols - (i%2); j++)
		{
			labela.Format(L"%d%d", i + 1, j + 1);
			Translate(pdc, size/2, size/2, false);
			Translate(pdc, j * (size + dX), i * (size + dY), false);
			if (i % 2 == 1) // Kako su parne zapravo sa neparnim indeksima
				Translate(pdc, evenRowsPadding, 0, false);
			Rotate(pdc, alpha, false);
			pdc->PlayMetaFile(mf, CRect(-size / 2, -size / 2, size / 2, size / 2));
			Rotate(pdc, -alpha, false);
			DrawLabel(pdc, size / 5, colText, labela);
			if (i % 2 == 1)
				Translate(pdc, -evenRowsPadding, 0, false);
			Translate(pdc, -j * (size + dX), - i * (size + dY), false);
			Translate(pdc, -size / 2, -size / 2, false);
		}
	}

	pdc->SetWorldTransform(&staraMatrica);
}

void CKolokvijum1View::OnDraw(CDC* pdc)
{
	CKolokvijum1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int oldGrMode = pdc->SetGraphicsMode(GM_ADVANCED);

	//Translate(pdc, 300, 300, false);

	COLORREF colors[3] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255) };
	
	HENHMETAFILE mf = CreateArcThreeSpots(pdc, 200, colors, 4, RGB(255, 128, 0), 1.5);
	DrawArcSpotsPattern(pdc, 3, 5, 20, 10, 45, mf , 200, RGB(255,255,0));

	//Translate(pdc, -300, -300, false);
	
	
	pdc->SetGraphicsMode(oldGrMode);

}



// CKolokvijum1View printing


void CKolokvijum1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CKolokvijum1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CKolokvijum1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CKolokvijum1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CKolokvijum1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CKolokvijum1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CKolokvijum1View diagnostics

#ifdef _DEBUG
void CKolokvijum1View::AssertValid() const
{
	CView::AssertValid();
}

void CKolokvijum1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKolokvijum1Doc* CKolokvijum1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKolokvijum1Doc)));
	return (CKolokvijum1Doc*)m_pDocument;
}
#endif //_DEBUG


// CKolokvijum1View message handlers


void CKolokvijum1View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'A' || nChar=='a') {
		angle += 10;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
