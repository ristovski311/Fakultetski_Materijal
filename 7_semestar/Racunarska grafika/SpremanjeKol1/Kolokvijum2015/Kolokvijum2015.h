
// Kolokvijum2015.h : main header file for the Kolokvijum2015 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKolokvijum2015App:
// See Kolokvijum2015.cpp for the implementation of this class
//

class CKolokvijum2015App : public CWinAppEx
{
public:
	CKolokvijum2015App() noexcept;


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

extern CKolokvijum2015App theApp;
