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

// BitwiseHelperView.cpp : implementation of the CBitwiseHelperView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BitwiseHelper.h"
#endif

#include "BitwiseHelperDoc.h"
#include "BitwiseHelperView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBitwiseHelperView

IMPLEMENT_DYNCREATE(CBitwiseHelperView, CView)

BEGIN_MESSAGE_MAP(CBitwiseHelperView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CBitwiseHelperView construction/destruction

CBitwiseHelperView::CBitwiseHelperView()
{
	// TODO: add construction code here
	resolution = 32;
}

CBitwiseHelperView::~CBitwiseHelperView()
{
}

BOOL CBitwiseHelperView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBitwiseHelperView drawing

void CBitwiseHelperView::OnDraw(CDC* /*pDC*/)
{
	CBitwiseHelperDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CBitwiseHelperView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CBitwiseHelperView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CBitwiseHelperView diagnostics

#ifdef _DEBUG
void CBitwiseHelperView::AssertValid() const
{
	CView::AssertValid();
}

void CBitwiseHelperView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBitwiseHelperDoc* CBitwiseHelperView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBitwiseHelperDoc)));
	return (CBitwiseHelperDoc*)m_pDocument;
}
#endif //_DEBUG


// CBitwiseHelperView message handlers


void CBitwiseHelperView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class

	CRect ControlRect;
	INT16 i;
	POINT p1, p2;
	for (i = 0; i < resolution; i++) {
		p1.x = OFFSETx + i * BTNWIDTH;
		p1.y = OFFSETy;
		p2.x = p1.x + BTNWIDTH;
		p2.y = p1.y + BTNHEIGHT;
		ControlRect.SetRect(p1, p2);
		btn[i].Create(_T("0"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			ControlRect,
			this, NULL);
	}
}
