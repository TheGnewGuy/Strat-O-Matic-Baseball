// AddLeague.cpp : implementation file
//

#include "stdafx.h"
#include "Baseball.h"
#include "AddLeague.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AddLeague dialog


AddLeague::AddLeague(CWnd* pParent /*=NULL*/)
	: CDialog(AddLeague::IDD, pParent)
{
	//{{AFX_DATA_INIT(AddLeague)
	m_NewLeagueName = _T("");
	m_Conference1 = _T("");
	m_Conference2 = _T("");
	m_Conference3 = _T("");
	m_Conference4 = _T("");
	m_Conference5 = _T("");
	m_Conference6 = _T("");
	//}}AFX_DATA_INIT
}


void AddLeague::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddLeague)
	DDX_Text(pDX, IDC_LEAGUE1, m_NewLeagueName);
	DDV_MaxChars(pDX, m_NewLeagueName, 30);
	DDX_Text(pDX, IDC_CONFERENCE1, m_Conference1);
	DDV_MaxChars(pDX, m_Conference1, 30);
	DDX_Text(pDX, IDC_CONFERENCE2, m_Conference2);
	DDV_MaxChars(pDX, m_Conference2, 30);
	DDX_Text(pDX, IDC_CONFERENCE3, m_Conference3);
	DDV_MaxChars(pDX, m_Conference3, 30);
	DDX_Text(pDX, IDC_CONFERENCE4, m_Conference4);
	DDV_MaxChars(pDX, m_Conference4, 30);
	DDX_Text(pDX, IDC_CONFERENCE5, m_Conference5);
	DDV_MaxChars(pDX, m_Conference5, 30);
	DDX_Text(pDX, IDC_CONFERENCE6, m_Conference6);
	DDV_MaxChars(pDX, m_Conference6, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(AddLeague, CDialog)
	//{{AFX_MSG_MAP(AddLeague)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AddLeague message handlers

void AddLeague::OnOK() 
{
	// TODO: Add extra validation here
	GetDlgItemText( IDC_LEAGUE1, m_NewLeagueName );
	if (m_NewLeagueName.IsEmpty())
	{
		CWnd* pmyCWnd = AfxGetMainWnd();
		pmyCWnd->MessageBox("You Must Enter a League Name",
			"Enter a League Name!",MB_OK|MB_ICONEXCLAMATION);
	}
	else
	{
		CDialog::OnOK();
	}
}
// AddLeague.cpp : implementation file
//

// AddLeagueName dialog

IMPLEMENT_DYNAMIC(AddLeagueName, CDialog)

AddLeagueName::AddLeagueName(CWnd* pParent /*=NULL*/)
	: CDialog(AddLeagueName::IDD, pParent)
	, m_NewLeagueName(_T(""))
	, m_Year(1800)
{
}

AddLeagueName::~AddLeagueName()
{
}

void AddLeagueName::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_LEAGUE1, m_NewLeagueName);
	DDV_MaxChars(pDX, m_NewLeagueName, 30);
	DDX_Text(pDX, IDC_YEAR, m_Year);
	DDV_MinMaxInt(pDX, m_Year, 1800, 2200);
}


BEGIN_MESSAGE_MAP(AddLeagueName, CDialog)
END_MESSAGE_MAP()


// AddLeagueName message handlers


void AddLeagueName::OnOK()
{
	GetDlgItemText(IDC_LEAGUE1, m_NewLeagueName);
	m_Year = GetDlgItemInt(IDC_YEAR);

	if (m_NewLeagueName.IsEmpty())
	{
		CWnd* pmyCWnd = AfxGetMainWnd();
		pmyCWnd->MessageBox("You Must Enter a League Name",
			"Enter a League Name!", MB_OK | MB_ICONEXCLAMATION);
	}
	else
	{
		CDialog::OnOK();
	}
}
