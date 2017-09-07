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

// BitwiseHelperDoc.h : interface of the CBitwiseHelperDoc class
//


#pragma once

#include <vector>

class CBitwiseHelperDoc : public CDocument
{
protected: // create from serialization only
	CBitwiseHelperDoc();
	DECLARE_DYNCREATE(CBitwiseHelperDoc)

// Attributes
public:

protected:
	CString m_DocName;
	BOOL m_MSBFirst;
	BOOL m_docOpemed;
	BOOL m_readyToWrite;
	BOOL m_newDoc;
	std::vector<CString> m_bits;
	INT16 m_resolution;
// Operations
public:
	CString GetDocName();
	BOOL GetMSBFirst();
	void SetMSBFirst(BOOL MSB);
	BOOL IsDocOpened();
	CString GetBitAt(INT16 index);
	void CleanBits();
	void AppendBit(CString bit);
	INT16 GetResolution();
	void SetResolution(INT16 res);
	void SetToWrite();
	BOOL IsNewDoc();
	CString bitmaskResPath;
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CBitwiseHelperDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
};
