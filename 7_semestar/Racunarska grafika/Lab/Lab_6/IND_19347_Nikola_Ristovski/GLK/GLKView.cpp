
// GLKView.cpp : implementation of the CGLKView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GLK.h"
#endif

#include "GLKDoc.h"
#include "GLKView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define TORAD 3.141592/180

// CGLKView

IMPLEMENT_DYNCREATE(CGLKView, CView)

BEGIN_MESSAGE_MAP(CGLKView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CGLKView construction/destruction

CGLKView::CGLKView()
{
	// TODO: add construction code here

}

CGLKView::~CGLKView()
{
}

BOOL CGLKView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGLKView drawing

void CGLKView::OnDraw(CDC* pDC)
{
	CGLKDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	m_glRenderer.DrawScene(pDC);
}


// CGLKView printing

BOOL CGLKView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGLKView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGLKView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGLKView diagnostics

#ifdef _DEBUG
void CGLKView::AssertValid() const
{
	CView::AssertValid();
}

void CGLKView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLKDoc* CGLKView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLKDoc)));
	return (CGLKDoc*)m_pDocument;
}
#endif //_DEBUG


// CGLKView message handlers


int CGLKView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void CGLKView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


void CGLKView::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);	
}


BOOL CGLKView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void CGLKView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}


void CGLKView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == 'B')
		m_glRenderer.enableLight = !m_glRenderer.enableLight;

	if (nChar == 'W')
	{
		m_glRenderer.wheelRotationAngle += 15;
		m_glRenderer.truckRotationAngle += m_glRenderer.wheelSteerAngle;
	}
	if(nChar == 'S')
	{
		m_glRenderer.wheelRotationAngle -= 15;
		m_glRenderer.truckRotationAngle -= m_glRenderer.wheelSteerAngle;
	}

	if(nChar == 'A')
	{
		if(m_glRenderer.wheelSteerAngle < 45)
			m_glRenderer.wheelSteerAngle += 5;
	}

	if (nChar == 'D')
	{
		if (m_glRenderer.wheelSteerAngle > -45)
			m_glRenderer.wheelSteerAngle -= 5;
	}



	Invalidate(TRUE);
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CGLKView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_glRenderer.lastMousePos = point;
	m_glRenderer.isMouseDown = true;
	CView::OnLButtonDown(nFlags, point);
}


void CGLKView::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_glRenderer.isMouseDown = false;
	CView::OnLButtonUp(nFlags, point);
}


void CGLKView::OnMouseMove(UINT nFlags, CPoint point)
{
	if(m_glRenderer.isMouseDown)
	{
		double moveSensitivity = 0.01;

		double dx = point.x - m_glRenderer.lastMousePos.x;
		double dy = point.y - m_glRenderer.lastMousePos.y;

		m_glRenderer.angleCameraY -= dx * moveSensitivity;
		m_glRenderer.angleCameraX += dy * moveSensitivity;

		m_glRenderer.lastMousePos = point;

		if (m_glRenderer.angleCameraX > 90 * TORAD)
			m_glRenderer.angleCameraX = 90 * TORAD;

		if (m_glRenderer.angleCameraX < -90 * TORAD)
			m_glRenderer.angleCameraX = -90 * TORAD;

		Invalidate(TRUE);
	}
	CView::OnMouseMove(nFlags, point);
}


BOOL CGLKView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	double zoomSensitivity = 0.5;

	m_glRenderer.radiusCamera -= zDelta * zoomSensitivity;

	if (m_glRenderer.radiusCamera < 1)
		m_glRenderer.radiusCamera = 1;
	else if (m_glRenderer.radiusCamera > 2000)
		m_glRenderer.radiusCamera = 2000;

	Invalidate(TRUE);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
