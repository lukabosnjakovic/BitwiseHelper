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
#include "afxwin.h"
#include "afxcmn.h"

#define RESOLUTION 32

class CBitwiseHelperView : public CFormView
{
protected: // create from serialization only
	CBitwiseHelperView();
	DECLARE_DYNCREATE(CBitwiseHelperView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_BITWISEHELPER_FORM };
#endif

// Attributes
public:
	CBitwiseHelperDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	void ChangeState(UINT nID, BOOL state);
	void FillDataFromDocument();
	void CleanForNewDoc();
	void CleanChkBoxes();

// Implementation
public:
	virtual ~CBitwiseHelperView();
	void BitOrder();
	void MakeValue(INT16 index, BOOL state);
	void ApplyMask(UINT32 mask, BOOL state);
	void UpdateTotal();
	CString GetHexChar(CString hex);
	CString GetDecValueString();
	CString GetHexValueString();
	CString GetBinValueString();
	void RefreshTree();
	void SetFonts();
	void ResizeTree();

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
	afx_msg	void OnBnClicked(UINT nID);
	afx_msg	void OnChkBxClicked(UINT nID);
	DECLARE_MESSAGE_MAP()
protected:
	CArray<CEdit> m_edit;
	CArray<CButton> m_button;
	CArray<CButton> m_chkbx;
	CArray<CStatic> m_bit_label;
	CEdit m_MSB_Label;
	CEdit m_total_dec;
	CEdit m_total_hex;
	CEdit m_total_bin;
	CEdit m_doc_name;
	BOOL m_MSB_First;
	UINT32 m_value;
	UINT16 m_resolution;
	BOOL m_opened_document;
	BOOL m_edit_bit_names;
	CBitwiseHelperDoc * m_doc;
	CBitwiseHelperApp * m_app;
	CMainFrame * m_mainFrm;
	LOGFONT lf;
	CFont m_totalFont;
	CFont m_MSBFont;
	CFont m_DocNameFont;
	
public:
	afx_msg void OnResolutionSlider();
	afx_msg void OnCheckMsb();
	afx_msg void OnCheckEnableEdit();
	CTreeCtrl m_tree;
	afx_msg void OnNMDblclkTree(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // debug version in BitwiseHelperView.cpp
inline CBitwiseHelperDoc* CBitwiseHelperView::GetDocument() const
   { return reinterpret_cast<CBitwiseHelperDoc*>(m_pDocument); }
#endif

