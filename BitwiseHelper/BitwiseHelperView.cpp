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

#include "MainFrm.h"
#include "BitwiseHelperDoc.h"
#include "BitwiseHelperView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBitwiseHelperView

IMPLEMENT_DYNCREATE(CBitwiseHelperView, CFormView)

BEGIN_MESSAGE_MAP(CBitwiseHelperView, CFormView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_BUTTON_0, IDC_BUTTON_31, &CBitwiseHelperView::OnBnClicked)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_CHECK_0, IDC_CHECK_31, &CBitwiseHelperView::OnChkBxClicked)
	ON_COMMAND(ID_RESOLUTION_SLIDER, &CBitwiseHelperView::OnResolutionSlider)
	ON_COMMAND(ID_CHECK_MSB, &CBitwiseHelperView::OnCheckMsb)
	ON_COMMAND(ID_CHECK_ENABLE_EDIT, &CBitwiseHelperView::OnCheckEnableEdit)
	ON_NOTIFY(NM_DBLCLK, IDC_TREE, &CBitwiseHelperView::OnNMDblclkTree)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CBitwiseHelperView construction/destruction

CBitwiseHelperView::CBitwiseHelperView()
	: CFormView(IDD_BITWISEHELPER_FORM)
{
	m_edit.SetSize(RESOLUTION);
	m_button.SetSize(RESOLUTION);
	m_chkbx.SetSize(RESOLUTION);
	m_bit_label.SetSize(RESOLUTION);
	m_value = 0;
	m_resolution = 32;
	m_MSB_First = TRUE;
	m_opened_document = FALSE;

	memset(&lf, 0, sizeof(LOGFONT));
	lf.lfHeight = 18;
	m_totalFont.CreateFontIndirect(&lf);
	lf.lfHeight = 30;
	m_MSBFont.CreateFontIndirect(&lf);
	lf.lfHeight = 45;
	m_DocNameFont.CreateFontIndirect(&lf);
}

CBitwiseHelperView::~CBitwiseHelperView()
{
}

void CBitwiseHelperView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	for (INT16 i = 0; i < RESOLUTION; i++) {
		DDX_Control(pDX, IDC_STATIC_0 + i, m_bit_label.ElementAt(i));
		DDX_Control(pDX, IDC_BUTTON_0 + i, m_button.ElementAt(i));
		DDX_Control(pDX, IDC_CHECK_0 + i, m_chkbx.ElementAt(i));
		DDX_Control(pDX, IDC_EDIT_0 + i, m_edit.ElementAt(i));
	}
	DDX_Control(pDX, IDC_STATIC_MSB, m_MSB_Label);
	DDX_Control(pDX, IDC_EDIT_DEC, m_total_dec);
	DDX_Control(pDX, IDC_EDIT_HEX, m_total_hex);
	DDX_Control(pDX, IDC_EDIT_BIN, m_total_bin);
	DDX_Control(pDX, IDC_DOC_NAME_STATIC, m_doc_name);
	DDX_Control(pDX, IDC_TREE, m_tree);
}

BOOL CBitwiseHelperView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CFormView::PreCreateWindow(cs);
}

void CBitwiseHelperView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	m_doc = GetDocument();
	m_app = (CBitwiseHelperApp *) AfxGetApp();
	m_mainFrm = (CMainFrame*)AfxGetMainWnd();
	
	SetFonts();
	CString stringTmp;
	stringTmp.LoadString(IDS_NEW_BITMASK);
	m_doc_name.SetWindowText(stringTmp);
	if (m_doc->IsNewDoc())
		CleanForNewDoc();
	BitOrder();
	CleanChkBoxes();
	m_opened_document = m_doc->IsDocOpened();
	ResizeTree();
	if (m_opened_document)
		FillDataFromDocument();
	else
		RefreshTree();
	if(m_MSB_First)
		stringTmp.LoadString(IDS_MSB_FIRST);
	else
		stringTmp.LoadString(IDS_LSB_FIRST);
	m_MSB_Label.SetWindowText(stringTmp);
}

void CBitwiseHelperView::ChangeState(UINT nID, BOOL state)
{
	CString stringTmp;
	if (state)
	{
		stringTmp.LoadString(IDS_STRING_1);
		m_chkbx.ElementAt(nID).SetCheck(TRUE);
	}
	else
	{
		stringTmp.LoadString(IDS_STRING_0);
		m_chkbx.ElementAt(nID).SetCheck(FALSE);
	}
	m_button.ElementAt(nID).SetWindowText(stringTmp);
	UpdateData();
	UpdateData(FALSE);
	UpdateTotal();
}

void CBitwiseHelperView::FillDataFromDocument()
{
	m_doc_name.SetWindowText(m_doc->GetDocName());
	m_resolution = m_doc->GetResolution();
	m_MSB_First = m_doc->GetMSBFirst();
	BitOrder();
	UpdateTotal();
	for (INT16 i = 0; i < m_resolution; i++)
		m_edit.ElementAt(i).SetWindowText(m_doc->GetBitAt(i));
	m_mainFrm->SetRibbonMSBChkBoxValue(m_MSB_First);
	CString stringTmp;
	switch (m_resolution)
	{
	case 8: stringTmp.LoadString(IDS_8BIT_MASK); m_mainFrm->SetRibbonSliderPos(0); break;
	case 16: stringTmp.LoadString(IDS_16BIT_MASK); m_mainFrm->SetRibbonSliderPos(1); break;
	case 32: stringTmp.LoadString(IDS_32BIT_MASK); m_mainFrm->SetRibbonSliderPos(2);  break;
	};
	m_mainFrm->SetRibbonSliderLabelText(stringTmp);

	SetFonts();
}

void CBitwiseHelperView::CleanForNewDoc()
{
	m_opened_document = FALSE;
	m_MSB_First = TRUE;
	m_resolution = 32;
	m_edit_bit_names = FALSE;
	m_mainFrm->SetRibbonMSBChkBoxValue(m_MSB_First);
	m_mainFrm->SetRibbonSliderPos(2);
	CString stringTmp;
	stringTmp.LoadString(IDS_32BIT_MASK);
	m_mainFrm->SetRibbonSliderLabelText(stringTmp);
	m_mainFrm->SetRibbonEditChkBoxValue(m_edit_bit_names);
	for (INT16 i = 0; i < RESOLUTION; i++)
	{
		m_edit.ElementAt(i).SetReadOnly(!m_edit_bit_names);
		ChangeState(i, FALSE);
	}
}

void CBitwiseHelperView::CleanChkBoxes()
{
	for (INT16 i = 0; i < RESOLUTION; i++)
	{
		ChangeState(i, FALSE);
	}
}

void CBitwiseHelperView::RefreshTree()
{
	HTREEITEM root, tmp;
	m_tree.DeleteAllItems();
	CString stringTmp;
	stringTmp.LoadString(IDS_TREE_ROOT_NAME);
	root = m_tree.InsertItem(stringTmp);
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;
	CString bitmaskResPath = m_doc->bitmaskResPath;
	hFind = FindFirstFile(bitmaskResPath, &FindFileData);
	do
	{
		CString diskObject;
		diskObject = FindFileData.cFileName;
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if (diskObject == _T(".") || diskObject == _T(".."))		// Directory
				continue;
			tmp = m_tree.InsertItem(diskObject, root);
			WIN32_FIND_DATA FindFileDataInFolder;
			HANDLE hFindInFolder;
			CString folderPath = bitmaskResPath;
			folderPath.Remove('*');
			folderPath += diskObject + _T("\\*");
			hFindInFolder = FindFirstFile(folderPath, &FindFileDataInFolder);
			do {
				CString dir = FindFileDataInFolder.cFileName;
				if (dir == _T(".") || dir == _T(".."))
					continue;
				if (dir.Find(_T(".bmsk")) == -1)
					continue;
				m_tree.InsertItem(FindFileDataInFolder.cFileName, tmp);
			} while (FindNextFile(hFindInFolder, &FindFileDataInFolder) != 0);
			FindClose(hFindInFolder);
		}
		else
		{
			if (diskObject.Find(_T(".bmsk")) == -1)
				continue;
			m_tree.InsertItem(diskObject, root);		// File
		}
	} while (FindNextFile(hFind, &FindFileData) != 0);
	FindClose(hFind);

	m_tree.Expand(root, TVE_EXPAND);
}

void CBitwiseHelperView::SetFonts()
{
	if(!m_total_dec)
		return;
	m_total_dec.SetFont(&m_totalFont);
	m_total_hex.SetFont(&m_totalFont);
	m_total_bin.SetFont(&m_totalFont);
	CStatic * myStatic;
	myStatic = (CStatic *)GetDlgItem(IDC_STATIC0);
	myStatic->SetFont(&m_totalFont);
	myStatic = (CStatic *)GetDlgItem(IDC_STATIC1);
	myStatic->SetFont(&m_totalFont);
	myStatic = (CStatic *)GetDlgItem(IDC_STATIC2);
	myStatic->SetFont(&m_totalFont);
	m_MSB_Label.SetFont(&m_MSBFont);
	m_doc_name.SetFont(&m_DocNameFont);
}

void CBitwiseHelperView::ResizeTree()
{
	if (m_tree.GetSafeHwnd() != NULL)
	{
		CRect windowRect;
		GetClientRect(windowRect);
		m_tree.MoveWindow(5, 5, 250, windowRect.bottom - 5);

	}
}

void CBitwiseHelperView::MakeValue(INT16 index, BOOL state)
{
	UINT32 tmp;
	tmp = 1;
	if (m_MSB_First) 
	{
		tmp <<= m_resolution - index - 1;
	}
	else
	{
		tmp <<= index;
	}
	if ((m_value & tmp) == state)
		return;
	ApplyMask(tmp, state);
}

void CBitwiseHelperView::ApplyMask(UINT32 mask, BOOL state)
{
	if (state)
		m_value |= mask;
	else
		m_value ^= mask;
}

void CBitwiseHelperView::UpdateTotal()
{
	m_total_dec.SetWindowText(GetDecValueString());
	m_total_hex.SetWindowText(GetHexValueString());
	m_total_bin.SetWindowText(GetBinValueString());
}

CString CBitwiseHelperView::GetDecValueString()
{
	CString output = _T("");
	for (INT16 i = 0; i < m_resolution; i++)
		MakeValue(i, m_chkbx.ElementAt(i).GetCheck());
	output.Format(_T("%u"), m_value);
	return output;
}

CString CBitwiseHelperView::GetHexValueString()
{
	CString tmp, tmp2, output = _T("0x");
	for (INT16 i = 0; i < m_resolution; i++)
	{
		tmp.Format(_T("%d"), m_chkbx.ElementAt(i).GetCheck());
		tmp2 += tmp;
		if ((i + 1) % 4 == 0)
		{
			output += GetHexChar(tmp2);
			tmp2 = _T("");
		}
	}
	return output;
}

CString CBitwiseHelperView::GetBinValueString()
{
	CString tmp, output = _T("0b");
	for (INT16 i = 0; i < this->m_resolution; i++)
	{
		tmp.Format(_T("%d"), m_chkbx.ElementAt(i).GetCheck());
		output += tmp;
	}
	return output;
}

CString CBitwiseHelperView::GetHexChar(CString hex)
{
	if (hex == "0000")
		return _T("0");
	if (hex == "0001")
		return _T("1");
	if (hex == "0010")
		return _T("2");
	if (hex == "0011")
		return _T("3");
	if (hex == "0100")
		return _T("4");
	if (hex == "0101")
		return _T("5");
	if (hex == "0110")
		return _T("6");
	if (hex == "0111")
		return _T("7");
	if (hex == "1000")
		return _T("8");
	if (hex == "1001")
		return _T("9");
	if (hex == "1010")
		return _T("A");
	if (hex == "1011")
		return _T("B");
	if (hex == "1100")
		return _T("C");
	if (hex == "1101")
		return _T("D");
	if (hex == "1110")
		return _T("E");
	if (hex == "1111")
		return _T("F");

	return _T("");
}

void CBitwiseHelperView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CBitwiseHelperView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CBitwiseHelperView::OnBnClicked(UINT nID)
{
	m_app->SetDirtyBit();
	CString tmp;
	nID -= 1100;
	m_button.ElementAt(nID).GetWindowText(tmp);
	ChangeState(nID, tmp == "0") ;
}

void CBitwiseHelperView::OnChkBxClicked(UINT nID)
{
	m_app->SetDirtyBit();
	nID -= 1200;
	ChangeState(nID, m_chkbx.ElementAt(nID).GetCheck());
}

// CBitwiseHelperView diagnostics

#ifdef _DEBUG
void CBitwiseHelperView::AssertValid() const
{
	CFormView::AssertValid();
}

void CBitwiseHelperView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif //_DEBUG

void CBitwiseHelperView::BitOrder()
{
	for (INT16 i = 0; i < RESOLUTION; i++)
	{
		m_edit.ElementAt(i).ShowWindow(i >(m_resolution - 1) ? SW_HIDE : SW_SHOW);
		m_bit_label.ElementAt(i).ShowWindow(i >(m_resolution - 1) ? SW_HIDE : SW_SHOW);
		m_button.ElementAt(i).ShowWindow(i >(m_resolution - 1) ? SW_HIDE : SW_SHOW);
		m_chkbx.ElementAt(i).ShowWindow(i >(m_resolution - 1) ? SW_HIDE : SW_SHOW);
		CString tmp;
		INT16 index;
		if(m_MSB_First)
			index = m_resolution - i - 1;
		else
			index = i;
		if (!m_opened_document)
		{
			tmp.Format(_T("Bit %d"), index);
			m_edit.ElementAt(i).SetWindowText(tmp);
		}		
		tmp.Format(_T("%d"), index);
		m_bit_label.ElementAt(i).SetWindowText(tmp);
	}
}

#ifdef DEBUG

CBitwiseHelperDoc* CBitwiseHelperView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBitwiseHelperDoc)));
	return (CBitwiseHelperDoc*)m_pDocument;
}
#endif // DEBUG


// CBitwiseHelperView message handlers

void CBitwiseHelperView::OnResolutionSlider()
{
	m_app->SetDirtyBit();

	CString stringTmp;
	switch (m_mainFrm->GetRibbonSliderPos())
	{
		case 0: stringTmp.LoadString(IDS_8BIT_MASK); m_resolution = 8; break;
		case 1: stringTmp.LoadString(IDS_16BIT_MASK); m_resolution = 16; break;
		case 2: stringTmp.LoadString(IDS_32BIT_MASK); m_resolution = 32; break;
	};
	m_mainFrm->SetRibbonSliderLabelText(stringTmp);
	BitOrder();
	m_value = 0;
	UpdateTotal();
}


void CBitwiseHelperView::OnCheckMsb()
{
	m_app->SetDirtyBit();
	m_MSB_First = !m_mainFrm->GetRibbonMSBChkBoxValue();
	m_mainFrm->SetRibbonMSBChkBoxValue(m_MSB_First);
	CString stringTmp;
	if (m_MSB_First)
		stringTmp.LoadString(IDS_MSB_FIRST);
	else
		stringTmp.LoadString(IDS_LSB_FIRST);

	m_MSB_Label.SetWindowText(stringTmp);
	SetFonts();
	BitOrder();
	UpdateTotal();
	UpdateData();
	UpdateData(FALSE);
}

void CBitwiseHelperView::OnCheckEnableEdit()
{
	m_app->SetDirtyBit();
	m_edit_bit_names = !m_mainFrm->GetRibbonEditChkBoxValue();
	m_mainFrm->SetRibbonEditChkBoxValue(m_edit_bit_names);
	for (INT16 i = 0; i < RESOLUTION; i++)
	{
		m_edit.ElementAt(i).SetReadOnly(!m_edit_bit_names);
	}
	if(!m_edit_bit_names)
	{
		m_opened_document = TRUE;
		m_doc->SetResolution(m_resolution);
		m_doc->SetMSBFirst(m_MSB_First);
		m_doc->CleanBits();
		for (INT16 i = 0; i < m_resolution; i++)
		{
			CString tmp;
			m_edit.ElementAt(i).GetWindowText(tmp);
			m_doc->AppendBit(tmp);
		}
		m_doc->SetToWrite();
	}
}


void CBitwiseHelperView::OnNMDblclkTree(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	HTREEITEM treeItm = m_tree.GetSelectedItem();
	CString itemText = m_tree.GetItemText(treeItm);
	if (itemText.Find(_T(".bmsk")) != -1)
	{
		HTREEITEM parent = m_tree.GetParentItem(treeItm);
		HTREEITEM root = m_tree.GetRootItem();
		CString file = m_doc->bitmaskResPath;
		file.Remove('*');
		if (m_tree.GetItemText(parent) != m_tree.GetItemText(root))
			file += m_tree.GetItemText(parent) + _T("\\");		
		file += itemText;
		CString stringTmp;
		stringTmp.LoadString(IDS_MY_OPEN_FILE);
		if (m_app->IsDocDirty())
			if (AfxMessageBox(stringTmp, MB_YESNO) == IDNO)
			{
				*pResult = 0;
				return;
			}
		m_app->OpenDocumentFile(file);
	}
	*pResult = 0;
}


void CBitwiseHelperView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	SetFonts();
	ResizeTree();
}
