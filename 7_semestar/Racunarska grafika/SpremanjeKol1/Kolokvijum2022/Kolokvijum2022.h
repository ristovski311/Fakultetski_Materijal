
// Kolokvijum2022.h : main header file for the Kolokvijum2022 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKolokvijum2022App:
// See Kolokvijum2022.cpp for the implementation of this class
//

class CKolokvijum2022App : public CWinAppEx
{
public:
	CKolokvijum2022App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKolokvijum2022App theApp;
