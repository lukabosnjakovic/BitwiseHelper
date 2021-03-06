// This MFC Samples source code demonstrates using MFC Microsoft Office Fluent User Interface 
// (the "Fluent UI") and is provided only as referential material to supplement the 
// Microsoft Foundation Classes Reference and related electronic documentation 
// included with the MFC C++ library software.  
// License terms to copy, use or distribute the Fluent UI are available separately.  
// To learn more about our Fluent UI licensing program, please visit 
// https://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// BitwiseHelper.h : main header file for the BitwiseHelper application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBitwiseHelperApp:
// See BitwiseHelper.cpp for the implementation of this class
//

class CBitwiseHelperApp : public CWinAppEx
{
protected:
	BOOL m_dirty_bit;
public:
	CBitwiseHelperApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	void SetDirtyBit();
	void ClearDirtyBit();
	BOOL IsDocDirty();

// Implementation
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	afx_msg void OnNewFile();
	afx_msg void OnOpenFile();
	DECLARE_MESSAGE_MAP()	
};

extern CBitwiseHelperApp theApp;
