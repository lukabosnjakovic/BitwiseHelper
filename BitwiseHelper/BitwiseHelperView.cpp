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
	ON_CONTROL_RANGE(BN_CLICKED, 5000, 5100, &CBitwiseHelperView::OnBnClicked)
	ON_CONTROL_RANGE(BN_CLICKED, 6000, 6100, &CBitwiseHelperView::OnChkBxClicked)
END_MESSAGE_MAP()

// CBitwiseHelperView construction/destruction

CBitwiseHelperView::CBitwiseHelperView()
{
	// TODO: add construction code here
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

void CBitwiseHelperView::PrepareViewObjects() 
{
	bits = this->GetDocument()->bits;
	resolution =bits->resolution;
	MSBFirst = bits->MSBFirst;

	btn = new CButton[resolution];
	labels = new CStatic[resolution];
	checkBox = new CButton[resolution];
}

void CBitwiseHelperView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	
	PrepareViewObjects();
	MakeButtons();

}

void CBitwiseHelperView::MakeButtons()
{
	CRect ControlRect;
	POINT p1, p2, chp1, chp2;
	INT16 b;

	if (MSBFirst)
		b = resolution - 1;
	else
		b = 0;

	for (INT16 i = 0; i < resolution; i++) {
		p1.x = OFFSETx + i * BTNWIDTH + i/8 * SPACER;
		p1.y = OFFSETy;
		p2.x = p1.x + BTNWIDTH;
		p2.y = p1.y + LABELHEIGHT;
		ControlRect.SetRect(p1, p2);
		CString tmp;
		// Labels
		tmp.Format(_T("%d"), b);
		labels[i].Create(tmp,
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			ControlRect,
			this, 4000 + i);
		if (MSBFirst)
			b--;
		else
			b++;

		p1.y += BTNHEIGHT - LBLBTNCORRECT;
		p2.y += BTNHEIGHT;
		ControlRect.SetRect(p1, p2);
		// Buttons
		btn[i].Create(_T("0"),
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
			ControlRect,
			this, 5000 + i);

		// CheckBoxes
		chp1.x = SPACER + OFFSETx + i / 4 * (4 * BTNWIDTH) + i / 8 * SPACER;
		chp1.y = p2.y + SPACER + i % 4 * BTNHEIGHT;
		chp2.x = chp1.x + 4 * BTNWIDTH;
		chp2.y = chp1.y + BTNHEIGHT;
		ControlRect.SetRect(chp1, chp2);
		tmp.Format(_T("Bit %d"), i);
		checkBox[i].Create(bits->bits[i].name,
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			ControlRect,
			this, 6000 + i);
	}
}

void CBitwiseHelperView::OnBnClicked(UINT nID)
{
	CString caption;
	CButton * Btn, * Chk;
	Btn = (CButton *) GetDlgItem(nID);
	Chk = (CButton *) GetDlgItem(nID + 1000);
	Btn->GetWindowTextW(caption);

	ButonsState(caption == "0", Btn, Chk);
}

void CBitwiseHelperView::OnChkBxClicked(UINT nID)
{
	CButton * Btn, *Chk;
	Btn = (CButton *)GetDlgItem(nID - 1000);
	Chk = (CButton *)GetDlgItem(nID);
	ButonsState(!Chk->GetCheck(), Btn, Chk);
}

void CBitwiseHelperView::ButonsState(INT16 state, CButton * btn, CButton * chk)
{
	if (state)
	{
		btn->SetWindowTextW(_T("1"));
		chk->SetCheck(TRUE);
	}
	else
	{
		btn->SetWindowTextW(_T("0"));
		chk->SetCheck(FALSE);
	}
}