
// MFCPrinter02.h : main header file for the MFCPrinter02 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMFCPrinter02App:
// See MFCPrinter02.cpp for the implementation of this class
//

class CMFCPrinter02App : public CWinAppEx
{
public:
	CMFCPrinter02App();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMFCPrinter02App theApp;
