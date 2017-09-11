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

// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BitwiseHelper.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_UPDATE_COMMAND_UI(ID_CHECK_MSB, &CMainFrame::OnChkBoxUpdate)
	ON_UPDATE_COMMAND_UI(ID_RESOLUTION_SLIDER, &CMainFrame::OnChkBoxUpdate)
	ON_UPDATE_COMMAND_UI(IDC_RIBBON_RES_OUT, &CMainFrame::OnLabelUpdate)
	ON_UPDATE_COMMAND_UI(ID_CHECK_ENABLE_EDIT, &CMainFrame::OnEditChkBoxUpdate)
END_MESSAGE_MAP()

// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	m_chkBox_state = TRUE;
	m_edit_chkBox_state = FALSE;
	m_lblText.LoadString(IDS_32BIT_MASK);
}

CMainFrame::~CMainFrame()
{
}

INT16 CMainFrame::GetRibbonSliderPos()
{
	CMFCRibbonSlider * slider = (CMFCRibbonSlider *)m_wndRibbonBar.FindByID(ID_RESOLUTION_SLIDER);
	return slider->GetPos();
}

void CMainFrame::SetRibbonSliderPos(INT16 pos)
{
	CMFCRibbonSlider * slider = (CMFCRibbonSlider *)m_wndRibbonBar.FindByID(ID_RESOLUTION_SLIDER);
	slider->SetPos(pos, TRUE);
}

void CMainFrame::SetRibbonSliderLabelText(CString text)
{
	m_lblText = text;
}

BOOL CMainFrame::GetRibbonMSBChkBoxValue()
{
	return m_chkBox_state;
}

void CMainFrame::SetRibbonMSBChkBoxValue(BOOL value)
{
	m_chkBox_state = value;
}

BOOL CMainFrame::GetRibbonEditChkBoxValue()
{
	return m_edit_chkBox_state;
}

void CMainFrame::SetRibbonEditChkBoxValue(BOOL value)
{
	m_edit_chkBox_state = value;
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	// enable Visual Studio 2005 style docking window behavior
	CDockingManager::SetDockingMode(DT_SMART);
	// enable Visual Studio 2005 style docking window auto-hide behavior
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// Navigation pane will be created at left, so temporary disable docking at the left side:
	EnableDocking(CBRS_ALIGN_TOP | CBRS_ALIGN_BOTTOM | CBRS_ALIGN_RIGHT);
	

	// Outlook bar is created and docking on the left side should be allowed.
	EnableDocking(CBRS_ALIGN_LEFT);
	EnableAutoHidePanes(CBRS_ALIGN_RIGHT);

	// set the visual manager used to draw all user interface elements
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
	m_wndRibbonBar.SetWindows7Look(TRUE);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		 | WS_BORDER | WS_MINIMIZEBOX | WS_SYSMENU;

	return TRUE;
}

void CMainFrame::OnChkBoxUpdate(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_chkBox_state);
}

void CMainFrame::OnSliderUpdate(CCmdUI * pCmdUI)
{
}

void CMainFrame::OnLabelUpdate(CCmdUI * pCmdUI)
{
	pCmdUI->SetText(m_lblText);
}

void CMainFrame::OnEditChkBoxUpdate(CCmdUI * pCmdUI)
{
	pCmdUI->SetCheck(m_edit_chkBox_state);
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers
