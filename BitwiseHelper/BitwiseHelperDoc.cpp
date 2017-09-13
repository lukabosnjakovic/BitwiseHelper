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

// BitwiseHelperDoc.cpp : implementation of the CBitwiseHelperDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "BitwiseHelper.h"
#endif

#include "BitwiseHelperDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CBitwiseHelperDoc

IMPLEMENT_DYNCREATE(CBitwiseHelperDoc, CDocument)

BEGIN_MESSAGE_MAP(CBitwiseHelperDoc, CDocument)
END_MESSAGE_MAP()


// CBitwiseHelperDoc construction/destruction

CBitwiseHelperDoc::CBitwiseHelperDoc()
{
	// TODO: add one-time construction code here
	m_MSBFirst = TRUE;
	m_docOpemed = FALSE;
	m_readyToWrite = FALSE;
	m_newDoc = FALSE;
	TCHAR tPath[100];
	GetModuleFileName(NULL, tPath, 100);
	bitmaskResPath = tPath;
	CString stringTmp;
	INT16 start = bitmaskResPath.ReverseFind('\\');
	bitmaskResPath.Delete(start, bitmaskResPath.GetLength() - start);
	bitmaskResPath += stringTmp;
	stringTmp.LoadString(IDS_BITMASKS_TEMPLATE_FOLDER);
	bitmaskResPath += stringTmp;
}

CBitwiseHelperDoc::~CBitwiseHelperDoc()
{
}

CString CBitwiseHelperDoc::GetDocName()
{
	return m_DocName;
}

BOOL CBitwiseHelperDoc::GetMSBFirst()
{
	return m_MSBFirst;
}

void CBitwiseHelperDoc::SetMSBFirst(BOOL MSB)
{
	m_MSBFirst = MSB;
}

BOOL CBitwiseHelperDoc::IsDocOpened()
{
	return m_docOpemed;
}

CString CBitwiseHelperDoc::GetBitAt(INT16 index)
{
	return m_bits.at(index);
}

void CBitwiseHelperDoc::CleanBits()
{
	m_bits.erase(m_bits.begin(), m_bits.end());
}

void CBitwiseHelperDoc::AppendBit(CString bit)
{
	m_bits.push_back(bit);
}

INT16 CBitwiseHelperDoc::GetResolution()
{
	return m_resolution;
}

void CBitwiseHelperDoc::SetResolution(INT16 res)
{
	m_resolution = res;
}

void CBitwiseHelperDoc::SetToWrite()
{
	m_readyToWrite = TRUE;
}

BOOL CBitwiseHelperDoc::IsNewDoc()
{
	BOOL tmp = FALSE;
	if (m_newDoc)
	{
		tmp = TRUE;
		m_newDoc = FALSE;
	}
	return tmp;
}

BOOL CBitwiseHelperDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_newDoc = TRUE;
	m_DocName.LoadString(IDS_NEW_BITMASK);
	m_MSBFirst = TRUE;
	m_docOpemed = FALSE;
	m_readyToWrite = FALSE;
	m_resolution = 32;
	return TRUE;
}

BOOL CBitwiseHelperDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	CBitwiseHelperApp * app = (CBitwiseHelperApp *)AfxGetApp();
	app->ClearDirtyBit();
	return TRUE;
}


BOOL CBitwiseHelperDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class
	CString stringTmp;
	if (!m_readyToWrite)
	{
		stringTmp.LoadString(IDS_EDIT_CHECK_WARNING);
		AfxMessageBox(stringTmp, MB_OK);
		return FALSE;
	}
	CBitwiseHelperApp * app = (CBitwiseHelperApp *)AfxGetApp();
	stringTmp.LoadString(IDS_MY_NEW_FILE);
	if (app->IsDocDirty() && m_docOpemed)
		if (AfxMessageBox(stringTmp, MB_YESNO) == IDNO)
			return FALSE;
	app->ClearDirtyBit();
	return CDocument::OnSaveDocument(lpszPathName);
}



// CBitwiseHelperDoc serialization

void CBitwiseHelperDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		if (m_readyToWrite)
		{
			ar << m_resolution;
			ar << m_MSBFirst;
			for (INT16 i = 0; i < m_resolution; i++)
				ar << m_bits.at(i);
			m_readyToWrite = FALSE;
			CBitwiseHelperApp * app = (CBitwiseHelperApp *)AfxGetApp();
			app->OnNewFile();
		}
	}
	else
	{
		m_DocName = ar.m_strFileName;
		INT16 start = m_DocName.ReverseFind(_T('\\')) + 1;
		INT16 cnt = m_DocName.GetLength() - start - 5;
		m_DocName = m_DocName.Mid(start, cnt);
		ar >> m_resolution;
		ar >> m_MSBFirst;
		m_bits.erase(m_bits.begin(), m_bits.end());
		for (INT16 i = 0; i < m_resolution; i++)
		{
			CString buff;
			ar >> buff;
			m_bits.push_back(buff);
		}
		m_docOpemed = TRUE;
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CBitwiseHelperDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CBitwiseHelperDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CBitwiseHelperDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CBitwiseHelperDoc diagnostics

#ifdef _DEBUG
void CBitwiseHelperDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBitwiseHelperDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CBitwiseHelperDoc commands

