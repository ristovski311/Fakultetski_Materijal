
// KolokvijumB2024.h : main header file for the KolokvijumB2024 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CKolokvijumB2024App:
// See KolokvijumB2024.cpp for the implementation of this class
//

class CKolokvijumB2024App : public CWinAppEx
{
public:
	CKolokvijumB2024App() noexcept;


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

extern CKolokvijumB2024App theApp;
