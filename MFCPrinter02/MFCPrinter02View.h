
// MFCPrinter02View.h : interface of the CMFCPrinter02View class
//

#pragma once
#include "afxwin.h"


class CMFCPrinter02View : public CView
{
protected: // create from serialization only
	CMFCPrinter02View();
	DECLARE_DYNCREATE(CMFCPrinter02View)

// Attributes
public:
	CMFCPrinter02Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CMFCPrinter02View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CFont m_PrintFont;
	int m_nPageLines;
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
};

#ifndef _DEBUG  // debug version in MFCPrinter02View.cpp
inline CMFCPrinter02Doc* CMFCPrinter02View::GetDocument() const
   { return reinterpret_cast<CMFCPrinter02Doc*>(m_pDocument); }
#endif

