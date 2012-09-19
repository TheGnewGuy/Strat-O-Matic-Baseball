// DlgAddTeams.cpp : implementation file
//

#include "stdafx.h"
#include "Baseball.h"
#include "DlgAddTeams.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAddTeams dialog


DlgAddTeams::DlgAddTeams(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAddTeams::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAddTeams)
	m_Division0 = _T("");
	//}}AFX_DATA_INIT
}


void DlgAddTeams::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAddTeams)
	DDX_Control(pDX, IDC_TEAMS1, m_CListBoxTeams);
	DDX_Text(pDX, IDC_DIVISION0, m_Division0);
	DDV_MaxChars(pDX, m_Division0, 30);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAddTeams, CDialog)
	//{{AFX_MSG_MAP(DlgAddTeams)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAddTeams message handlers

BOOL DlgAddTeams::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_CListBoxTeams.ResetContent();
	for (int i=0; i<m_arrayTeams.GetSize(); i++)
	{
		m_CListBoxTeams.AddString(m_arrayTeams[i]);
	}
	int tab_stop[1] = {200};
	VERIFY(m_CListBoxTeams.SetTabStops(1, tab_stop));

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgAddTeams::OnOK() 
{
	// TODO: Add extra validation here
	CString selTeam;
	if (m_CListBoxTeams.GetSelCount())
	{
		m_arrayTeams.RemoveAll();
		for (int i=0; i<m_CListBoxTeams.GetCount(); i++)
		{
			if (m_CListBoxTeams.GetSel(i))
			{
				m_CListBoxTeams.GetText(i,selTeam);
				m_arrayTeams.Add(selTeam);
			}
		}
	}
	
	CDialog::OnOK();
}
