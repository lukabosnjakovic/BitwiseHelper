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
	ON_CONTROL_RANGE(BN_CLICKED, BUTTONRANGEIDSTART, BUTTONRANGEIDSTART + BUTTONSACTIONRANGE, &CBitwiseHelperView::OnBnClicked)
	ON_CONTROL_RANGE(BN_CLICKED, CHKBOXRANGEIDSTART, CHKBOXRANGEIDSTART + BUTTONSACTIONRANGE, &CBitwiseHelperView::OnChkBxClicked)
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
	cs.style &= ~FWS_ADDTOTITLE;
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
	resolution = bits->GetResolution();
	MSBFirst = bits->IsMSBFirst();

	btn = new CButton[resolution];
	labels = new CStatic[resolution + 7];
	checkBox = new CButton[resolution];
	chkBoxNames = new CEdit[resolution];
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
	CString tmp;

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

		// Button labels
#pragma warning "Pitati profesora kako maknuti pozadinu label-ima"
		tmp.Format(_T("%d"), b);
		labels[i].Create(tmp,
			WS_CHILD | WS_VISIBLE | SS_CENTER,
			ControlRect,
			this, STATICRANGEIDSTART + i);
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
			this, BUTTONRANGEIDSTART + i);

		// CheckBoxes
		chp1.x = SPACER + OFFSETx + i / 4 * (4 * BTNWIDTH) + i / 8 * SPACER;
		chp1.y = p2.y + SPACER + i % 4 * BTNHEIGHT;
		chp2.x = chp1.x + BTNWIDTH;
		chp2.y = chp1.y + BTNHEIGHT;
		ControlRect.SetRect(chp1, chp2);
		checkBox[i].Create(NULL,
			WS_CHILD | WS_VISIBLE | BS_CHECKBOX,
			ControlRect,
			this, CHKBOXRANGEIDSTART + i);

		// CheckBoxes Names
		chp1.x += BTNWIDTH;
		chp1.y += SPACER / 1.5;
		chp2.x += 3 * BTNWIDTH - SPACER;
		chp2.y -= BTNHEIGHT * 0.3;
		ControlRect.SetRect(chp1, chp2);
		chkBoxNames[i].Create(WS_CHILD | WS_VISIBLE | WS_DISABLED,
			ControlRect,
			this, 7000 + i);
		chkBoxNames[i].SetWindowTextW(bits->GetBit(i).name);
	}

	//For setting font of CStatic
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 35;
	CFont *font0 = new CFont();
	font0->CreateFontIndirect(&lf);
	CString MSB;
	if (bits->IsMSBFirst())
		MSB = _T("MSB First");
	else
		MSB = _T("LSB First");
	p1.x = TOTALOFFSETx;
	p1.y = chp2.y + MSBOFFSETy;
	p2.x = MSBWIDTH;
	p2.y = p1.y + MSBHEIGHT;
	ControlRect.SetRect(p1, p2);
	labels[resolution + TOTALMSBNAME].Create(MSB,
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		ControlRect,
		this, STATICRANGEIDSTART + resolution + TOTALMSBNAME);
	labels[resolution + TOTALMSBNAME].SetFont(font0);

	CFont *font = new CFont();
	lf.lfHeight = 25;
	font->CreateFontIndirect(&lf);

	p1.x = TOTALOFFSETx;
	p1.y = chp2.y + TOTALOFFSETy;
	p2.x = TOTALLBLWIDTH;
	p2.y = p1.y + TOTALLBLHEIGHT;
	ControlRect.SetRect(p1, p2);
	labels[resolution + TOTALDECNAME].Create(_T("Decimal:"),
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		ControlRect,
		this, STATICRANGEIDSTART + resolution + TOTALDECNAME);
	labels[resolution + TOTALDECNAME].SetFont(font);
	p1.y = p2.y + SPACER;
	p2.y = p1.y + TOTALLBLHEIGHT;
	ControlRect.SetRect(p1, p2);
	labels[resolution + TOTALHEXNAME].Create(_T("Hexadecimal:"),
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		ControlRect,
		this, STATICRANGEIDSTART + resolution + TOTALHEXNAME);
	labels[resolution + TOTALHEXNAME].SetFont(font);
	p1.y = p2.y + SPACER;
	p2.y = p1.y + TOTALLBLHEIGHT;
	ControlRect.SetRect(p1, p2);
	labels[resolution + TOTALBINNAME].Create(_T("Binary:"),
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		ControlRect,
		this, STATICRANGEIDSTART + resolution + TOTALBINNAME);
	labels[resolution + TOTALBINNAME].SetFont(font);

	p1.x = p2.x + SPACER;
	p1.y = chp2.y + TOTALOFFSETy;
	p2.x = p1.x + resolution / 8 * TOTALVALWIDTH;
	p2.y = p1.y + TOTALLBLHEIGHT;
	ControlRect.SetRect(p1, p2);
	labels[resolution + TOTALDECVAL].Create(bits->GetDecValueString(),
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		ControlRect,
		this, STATICRANGEIDSTART + resolution + TOTALDECVAL);
	labels[resolution + TOTALDECVAL].SetFont(font);

	p1.y = p2.y + SPACER;
	p2.y = p1.y + TOTALLBLHEIGHT;
	ControlRect.SetRect(p1, p2);
	labels[resolution + TOTALHEXVAL].Create(bits->GetHexValueString(),
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		ControlRect,
		this, STATICRANGEIDSTART + resolution + TOTALHEXVAL);
	labels[resolution + TOTALHEXVAL].SetFont(font);

	p1.y = p2.y + SPACER;
	p2.y = p1.y + TOTALLBLHEIGHT;
	ControlRect.SetRect(p1, p2);
	labels[resolution + TOTALBINVAL].Create(bits->GetBinValueString(),
		WS_CHILD | WS_VISIBLE | SS_LEFT,
		ControlRect,
		this, STATICRANGEIDSTART + resolution + TOTALBINVAL);
	labels[resolution + TOTALBINVAL].SetFont(font);

#pragma warning "Pitati profesora kako resize-at View prozor da pase content-u, te onemoguciti da korisnik moze resize-at view"
}

void CBitwiseHelperView::OnBnClicked(UINT nID)
{
	CString caption;
	CButton * Btn, * Chk;
	Btn = (CButton *) GetDlgItem(nID);
	Chk = (CButton *) GetDlgItem(nID + BUTTONOBJECTRANGE);
	Btn->GetWindowTextW(caption);

	ButonsState(caption == "0", Btn, Chk);
}

void CBitwiseHelperView::OnChkBxClicked(UINT nID)
{
	CButton * Btn, *Chk;
	Btn = (CButton *)GetDlgItem(nID - BUTTONOBJECTRANGE);
	Chk = (CButton *)GetDlgItem(nID);
	ButonsState(!Chk->GetCheck(), Btn, Chk);
}

void CBitwiseHelperView::ButonsState(INT16 state, CButton * btn, CButton * chk)
{
	INT16 index;
	index = btn->GetDlgCtrlID();
	index -= BUTTONRANGEIDSTART;
	if (state)
	{
		btn->SetWindowTextW(_T("1"));
		chk->SetCheck(TRUE);
		bits->SetBit(index, 1);
	}
	else
	{
		btn->SetWindowTextW(_T("0"));
		chk->SetCheck(FALSE);
		bits->SetBit(index, 0);
	}
	UpdateTotalLabels();
}

void CBitwiseHelperView::UpdateTotalLabels()
{
	CStatic * bin, * dec, * hex;
	dec = (CStatic *) GetDlgItem(STATICRANGEIDSTART + resolution + TOTALDECVAL);
	hex = (CStatic *) GetDlgItem(STATICRANGEIDSTART + resolution + TOTALHEXVAL);
	bin = (CStatic *) GetDlgItem(STATICRANGEIDSTART + resolution + TOTALBINVAL);

	dec->SetWindowTextW(bits->GetDecValueString());
	hex->SetWindowTextW(bits->GetHexValueString());
	bin->SetWindowTextW(bits->GetBinValueString());
}
