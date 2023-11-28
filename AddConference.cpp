// AddConference.cpp : implementation file
//

#include "stdafx.h"
#include "Baseball.h"
#include "AddConference.h"
#include "afxdialogex.h"


// AddConference dialog

IMPLEMENT_DYNAMIC(AddConference, CDialog)

AddConference::AddConference(CWnd* pParent /*=NULL*/)
	: CDialog(AddConference::IDD, pParent)
	, m_LeagueName(_T(""))
	, m_Conference1(_T(""))
	, m_Conference2(_T(""))
	, m_Conference3(_T(""))
	, m_Conference4(_T(""))
	, m_Conference5(_T(""))
	, m_Conference6(_T(""))
{

}

AddConference::~AddConference()
{
}

void AddConference::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//  DDX_Control(pDX, IDC_LEAGUE1, m_LeagueName);
	DDX_Text(pDX, IDC_LEAGUE1, m_LeagueName);
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
}


BEGIN_MESSAGE_MAP(AddConference, CDialog)
END_MESSAGE_MAP()


// AddConference message handlers


void AddConference::OnOK()
{
	GetDlgItemText(IDC_CONFERENCE1, m_Conference1);
	GetDlgItemText(IDC_CONFERENCE2, m_Conference2);
	GetDlgItemText(IDC_CONFERENCE3, m_Conference3);
	GetDlgItemText(IDC_CONFERENCE4, m_Conference4);
	GetDlgItemText(IDC_CONFERENCE5, m_Conference5);
	GetDlgItemText(IDC_CONFERENCE6, m_Conference6);

	if (m_Conference1.IsEmpty())
	{
		CWnd* pmyCWnd = AfxGetMainWnd();
		pmyCWnd->MessageBox("You Must Enter one Conference Name",
			"Enter a Conference Name!", MB_OK | MB_ICONEXCLAMATION);
	}
	else
	{
		CDialog::OnOK();
	}
}
