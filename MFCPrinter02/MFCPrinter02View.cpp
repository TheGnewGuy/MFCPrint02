
// MFCPrinter02View.cpp : implementation of the CMFCPrinter02View class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "MFCPrinter02.h"
#endif

#include "MFCPrinter02Doc.h"
#include "MFCPrinter02View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCPrinter02View

IMPLEMENT_DYNCREATE(CMFCPrinter02View, CView)

BEGIN_MESSAGE_MAP(CMFCPrinter02View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCPrinter02View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CMFCPrinter02View construction/destruction

CMFCPrinter02View::CMFCPrinter02View()
: m_nPageLines(0)
{
	// TODO: add construction code here

}

CMFCPrinter02View::~CMFCPrinter02View()
{
}

BOOL CMFCPrinter02View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMFCPrinter02View drawing

void CMFCPrinter02View::OnDraw(CDC* pDC)
{
	CMFCPrinter02Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	int i, y;
	CString s;
	TEXTMETRIC tm;
	CRect rcClip;

	// Set Font
	CFont font;
	font.CreateStockObject(DEFAULT_GUI_FONT);
	CFont *pOldFont = pDC->SelectObject(&font);

	// Get line height
	pDC->GetTextMetrics(&tm);
	int nLineHeight = tm.tmHeight + tm.tmExternalLeading;

	// Draw content
	for (i = y = 0; i < 100; i++, y += nLineHeight)
	{
		s.Format(_T("This is line %d."), i + 1);
		pDC->TextOut(4, y, s, s.GetLength());
	}

	// Restore DC
	pDC->SelectObject(pOldFont);
}


// CMFCPrinter02View printing


void CMFCPrinter02View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCPrinter02View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCPrinter02View::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: add extra initialization before printing
	HFONT hFont = (HFONT)::GetStockObject(DEFAULT_GUI_FONT);
	LOGFONT lf;
	::GetObject(hFont, sizeof(lf), &lf);
	lf.lfHeight = -((pDC->GetDeviceCaps(LOGPIXELSY) * lf.lfHeight) / 72);
	m_PrintFont.CreateFontIndirectW(&lf);
	
	TEXTMETRIC tm;
	CFont *pOldFont = pDC->SelectObject(&m_PrintFont);
	pDC->GetOutputTextMetrics(&tm);
	pDC->SelectObject(pOldFont);
	m_nPageLines = (pDC->GetDeviceCaps(VERTRES) / (tm.tmHeight + tm.tmExternalLeading));
	pInfo->SetMaxPage((100 / m_nPageLines) + 1);
}

void CMFCPrinter02View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
	m_PrintFont.DeleteObject();
}

void CMFCPrinter02View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCPrinter02View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCPrinter02View diagnostics

#ifdef _DEBUG
void CMFCPrinter02View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCPrinter02View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCPrinter02Doc* CMFCPrinter02View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCPrinter02Doc)));
	return (CMFCPrinter02Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCPrinter02View message handlers


void CMFCPrinter02View::OnPrint(CDC* pDC, CPrintInfo* pInfo)
{
	// TODO: Add your specialized code here and/or call the base class
	int i, y;
	CString s;
	TEXTMETRIC tm;

	// Set Font
	CFont *pOldFont = pDC->SelectObject(&m_PrintFont);

	// Get line height
	pDC->GetTextMetrics(&tm);
	int nLineHeight = tm.tmHeight + tm.tmExternalLeading;

	// Draw content
	int nStart = ((pInfo->m_nCurPage - 1) * m_nPageLines);
	for (i = nStart, y = 0; i < 100 && (y + nLineHeight) < pInfo->m_rectDraw.bottom; i++, y += nLineHeight)
	{
		s.Format(_T("This is line %d."), i + 1);
		pDC->TextOut(4, y, s, s.GetLength());
	}

	// Restore DC
	pDC->SelectObject(pOldFont);

}
