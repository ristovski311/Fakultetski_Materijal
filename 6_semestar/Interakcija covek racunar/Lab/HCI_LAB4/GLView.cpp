// GLView.cpp : implementation of the CGLView class
//

#include "stdafx.h"
#include "GL.h"

#include "GLDoc.h"
#include "GLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGLView

IMPLEMENT_DYNCREATE(CGLView, CView)

BEGIN_MESSAGE_MAP(CGLView, CView)
	//{{AFX_MSG_MAP(CGLView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGLView construction/destruction

CGLView::CGLView()
{
	// TODO: add construction code here

}

CGLView::~CGLView()
{
}

BOOL CGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CGLView drawing

void CGLView::OnDraw(CDC* pDC)
{
	CGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	m_glRenderer.DrawScene(pDC);
}

/////////////////////////////////////////////////////////////////////////////
// CGLView printing

BOOL CGLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CGLView diagnostics

#ifdef _DEBUG
void CGLView::AssertValid() const
{
	CView::AssertValid();
}

void CGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLDoc* CGLView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLDoc)));
	return (CGLDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGLView message handlers

int CGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}

void CGLView::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}

BOOL CGLView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;

	//return CView::OnEraseBkgnd(pDC);
}

void CGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}

void CGLView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);

}

BOOL CGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	if (zDelta > 0.0)
		m_glRenderer.m_z += 0.2;

	if (zDelta < 0.0)
		m_glRenderer.m_z -= 0.2;

	Invalidate();

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//zoom
	if (nChar == VK_ADD)
		m_glRenderer.m_z += 0.2;
	if (nChar == VK_SUBTRACT)
		m_glRenderer.m_z -= 0.2;

	//rotacija
	bool bShift = GetKeyState(VK_SHIFT) & 0x8000;

	if (nChar == VK_RIGHT)
		if (bShift)
		{
			m_glRenderer.m_Ry -= 5.0;
		}
		else
		{
			//desno
			m_glRenderer.m_x -= 0.2;
		}

	if (nChar == VK_LEFT)
		if (bShift)
		{
			m_glRenderer.m_Ry += 5.0;
		}
		else
		{
			//levo
			m_glRenderer.m_x += 0.2;
		}


	if (nChar == VK_UP)
		if (bShift)
		{
			m_glRenderer.m_Rx += 5.0;
		}
		else
		{
			//gore
			m_glRenderer.m_y -= 0.2;
		}

	if (nChar == VK_DOWN)
		if (bShift)
		{
			m_glRenderer.m_Rx -= 5.0;
		}
		else
		{
			//dole
			m_glRenderer.m_y += 0.2;
		}


	Invalidate();

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//promenljive za kontrolu misem
CPoint lastMousePosition;
bool isLeftButtonDown = false;

void CGLView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//kad drzimo dugme misa (levo)
	isLeftButtonDown = true;
	lastMousePosition = point;
	SetCapture();
	CView::OnLButtonDown(nFlags, point);
}

void CGLView::OnLButtonUp(UINT nFlags, CPoint point)
{
	//kad otpustimo dugme misa (levo)
	isLeftButtonDown = false;
	ReleaseCapture();
	CView::OnLButtonUp(nFlags, point);
}

void CGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	//rotacija je shift + pomeranje misa
	bool bShift = GetKeyState(VK_SHIFT) & 0x8000;

	if (isLeftButtonDown)
	{
		if (bShift)
		{
			CPoint difference = point - lastMousePosition;

			m_glRenderer.m_Ry += difference.x * 0.5f;
			m_glRenderer.m_Rx += difference.y * 0.5f;

			lastMousePosition = point;
		}
		else
		{
			CPoint difference = point - lastMousePosition;

			m_glRenderer.m_x += difference.x * 0.01f;
			m_glRenderer.m_y -= difference.y * 0.01f;

			lastMousePosition = point;
		}

		Invalidate();
	}


	CView::OnMouseMove(nFlags, point);
}

void CGLView::OnRButtonDown(UINT nFlags, CPoint point)
{
	unsigned int ids[2] = { 0,0 };
	m_glRenderer.PickObject(this->GetDC(), point.x, point.y, ids);
	CString msg;
	if (ids[0] == 0 && ids[1] == 0)
	{
		msg = _T("Nije pritisnuto nista!");
	}
	else
	{
		msg = _T("Pritisnuta je");
		switch (ids[1])
		{
		case 0: break;
		case 1: msg += " crvena kocka"; break;
		case 2: msg += " zelena kocka"; break;
		case 3: msg += " plava kocka";  break;
		case 4: msg += " zuta kocka"; break;
		case 5: msg += " ljubicasta kocka"; break;
		default:
			break;
		}

		switch (ids[0])
		{
		case 0: msg += "."; break;
		case 1: msg += " unutar crvene kocke."; break;
		case 2: msg += " unutar zelene kocke."; break;
		case 3: msg += " unutar plave kocke."; break;
		case 4: msg += " unutar zute kocke."; break;
		case 5: msg += " unutar ljubicaste kocke."; break;
		default:
			break;
		}
	}

	AfxMessageBox(msg);

	CView::OnRButtonDown(nFlags, point);
}
