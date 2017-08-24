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

// BitwiseHelperView.h : interface of the CBitwiseHelperView class
//

#pragma once

#define STATICRANGEIDSTART 4000
#define BUTTONRANGEIDSTART 5000
#define CHKBOXRANGEIDSTART 6000
#define CHKNAMERANGEIDSTART 7000
#define BUTTONOBJECTRANGE 1000	// Make upper 3 numbers range difference equal to this number
#define BUTTONSACTIONRANGE 100

#define OFFSETx 20
#define OFFSETy 20
#define BTNWIDTH 30
#define BTNHEIGHT 30
#define LABELHEIGHT 15
#define LBLBTNCORRECT 10
#define SPACER 10

#define MSBOFFSETy (2 * SPACER)
#define MSBWIDTH 170
#define MSBHEIGHT 30

#define TOTALOFFSETx OFFSETx
#define TOTALOFFSETy (MSBOFFSETy + MSBHEIGHT + 3 * SPACER)
#define TOTALLBLWIDTH (5 * BTNWIDTH)
#define TOTALLBLHEIGHT (0.8 * BTNHEIGHT)
#define TOTALVALWIDTH ( 4 * BTNWIDTH)
#define TOTALMSBNAME 0
#define TOTALDECNAME 1
#define	TOTALHEXNAME 2
#define TOTALBINNAME 3
#define TOTALDECVAL 4
#define TOTALHEXVAL 5
#define TOTALBINVAL 6

class CBitwiseHelperView : public CView
{
protected: // create from serialization only
	CBitwiseHelperView();
	DECLARE_DYNCREATE(CBitwiseHelperView)
	CButton * btn;
	CButton * checkBox;
	CStatic * labels;
	CEdit * chkBoxNames;
	MyBits * bits;

	INT16 resolution;
	INT16 MSBFirst;

// Attributes
public:
	CBitwiseHelperDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CBitwiseHelperView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void PrepareViewObjects();
	void MakeButtons();
	void ButonsState(INT16 state, CButton * btn, CButton * chk);
	void UpdateTotalLabels();

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg	void OnBnClicked(UINT nID);
	afx_msg	void OnChkBxClicked(UINT nID);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
protected:
};

#ifndef _DEBUG  // debug version in BitwiseHelperView.cpp
inline CBitwiseHelperDoc* CBitwiseHelperView::GetDocument() const
   { return reinterpret_cast<CBitwiseHelperDoc*>(m_pDocument); }
#endif

