// DlgAddDivision.cpp : implementation file
//

#include "stdafx.h"
#include "Baseball.h"
#include "DlgAddDivision.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAddDivision dialog


DlgAddDivision::DlgAddDivision(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAddDivision::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAddDivision)
	m_Division1 = _T("");
	m_Division2 = _T("");
	m_Division3 = _T("");
	m_Division4 = _T("");
	m_Division5 = _T("");
	m_Division6 = _T("");
	m_Conference0 = _T("");
	//}}AFX_DATA_INIT
}


void DlgAddDivision::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAddDivision)
	DDX_Text(pDX, IDC_DIVISION1, m_Division1);
	DDV_MaxChars(pDX, m_Division1, 30);
	DDX_Text(pDX, IDC_DIVISION2, m_Division2);
	DDV_MaxChars(pDX, m_Division2, 30);
	DDX_Text(pDX, IDC_DIVISION3, m_Division3);
	DDV_MaxChars(pDX, m_Division3, 30);
	DDX_Text(pDX, IDC_DIVISION4, m_Division4);
	DDV_MaxChars(pDX, m_Division4, 30);
	DDX_Text(pDX, IDC_DIVISION5, m_Division5);
	DDV_MaxChars(pDX, m_Division5, 30);
	DDX_Text(pDX, IDC_DIVISION6, m_Division6);
	DDV_MaxChars(pDX, m_Division6, 30);
	DDX_Text(pDX, IDC_CONFERENCE0, m_Conference0);
	DDV_MaxChars(pDX, m_Conference0, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAddDivision, CDialog)
	//{{AFX_MSG_MAP(DlgAddDivision)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAddDivision message handlers
