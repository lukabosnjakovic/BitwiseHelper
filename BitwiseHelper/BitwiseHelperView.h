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

#define OFFSETx 20
#define OFFSETy 20
#define BTNWIDTH 30
#define BTNHEIGHT 30

class CBitwiseHelperView : public CView
{
protected: // create from serialization only
	CBitwiseHelperView();
	DECLARE_DYNCREATE(CBitwiseHelperView)
	CButton btn[32];
	INT16 resolution;

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

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in BitwiseHelperView.cpp
inline CBitwiseHelperDoc* CBitwiseHelperView::GetDocument() const
   { return reinterpret_cast<CBitwiseHelperDoc*>(m_pDocument); }
#endif

