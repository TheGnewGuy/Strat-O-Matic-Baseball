// AddTeam.cpp : implementation file
//

#include "stdafx.h"
#include "Baseball.h"
#include "AddTeam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// AddTeam dialog


AddTeam::AddTeam(CWnd* pParent /*=NULL*/)
	: CDialog(AddTeam::IDD, pParent)
	, m_TotalLosses(0)
	, m_TotalWins(0)
{
	//{{AFX_DATA_INIT(AddTeam)
	m_TeamName = _T("");
	m_ShortTeamName = _T("");
	m_BallPark = _T("");
	m_AwayLoss = 0;
	m_AwayWin = 0;
	m_HomeLoss = 0;
	m_HomeWin = 0;
	m_League = _T("DEFAULT");
	m_Division = _T("DEFAULT");
	m_Conference = _T("DEFAULT");
	m_Year = 1800;
	m_Base = FALSE;
	//}}AFX_DATA_INIT
}

BOOL AddTeam::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	if (m_Base)
		m_BaseControl.SetCheck(TRUE);
	else
		m_BaseControl.SetCheck(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void AddTeam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(AddTeam)
	DDX_Text(pDX, IDC_TEAM1, m_TeamName);
	DDV_MaxChars(pDX, m_TeamName, 40);
	DDX_Text(pDX, IDC_SHORTTEAM1, m_ShortTeamName);
	DDV_MaxChars(pDX, m_ShortTeamName, 3);
	DDX_Text(pDX, IDC_BALLPARK1, m_BallPark);
	DDV_MaxChars(pDX, m_BallPark, 30);
	DDX_Text(pDX, IDC_AWAYLOSS, m_AwayLoss);
	DDV_MinMaxInt(pDX, m_AwayLoss, 0, 200);
	DDX_Text(pDX, IDC_YEAR, m_Year);
	DDV_MinMaxInt(pDX, m_Year, 1800, 2500);
	DDX_Text(pDX, IDC_AWAYWIN, m_AwayWin);
	DDV_MinMaxInt(pDX, m_AwayWin, 0, 200);
	DDX_Text(pDX, IDC_CONFERENCE, m_Conference);
	DDV_MaxChars(pDX, m_Conference, 100);
	DDX_Text(pDX, IDC_DIVISION, m_Division);
	DDV_MaxChars(pDX, m_Division, 200);
	DDX_Text(pDX, IDC_HOMEWIN, m_HomeWin);
	DDV_MinMaxInt(pDX, m_HomeWin, 0, 200);
	DDX_Text(pDX, IDC_League, m_League);
	DDV_MaxChars(pDX, m_League, 100);
	DDX_Text(pDX, IDC_HOMELOSS, m_HomeLoss);
	DDV_MinMaxInt(pDX, m_HomeLoss, 0, 200);
	//  DDX_Control(pDX, IDC_BASE, m_Base);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_BASE, m_BaseControl);
	DDX_Text(pDX, IDC_TOTALLOSSES, m_TotalLosses);
	DDX_Text(pDX, IDC_TOTALWINS, m_TotalWins);
}


BEGIN_MESSAGE_MAP(AddTeam, CDialog)
	//{{AFX_MSG_MAP(AddTeam)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// AddTeam message handlers
/////////////////////////////////////////////////////////////////////////////

// dlgSelTeam dialog


dlgSelTeam::dlgSelTeam(CWnd* pParent /*=NULL*/)
	: CDialog(dlgSelTeam::IDD, pParent)
{
	//{{AFX_DATA_INIT(dlgSelTeam)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void dlgSelTeam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(dlgSelTeam)
	DDX_Control(pDX, IDC_SELTEAMLISTBOX1, m_selTeamListBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(dlgSelTeam, CDialog)
	//{{AFX_MSG_MAP(dlgSelTeam)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// dlgSelTeam message handlers

BOOL dlgSelTeam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_selTeamListBox.ResetContent();
	for (int i=0; i<m_arrayTeams.GetSize(); i++)
	{
		m_selTeamListBox.AddString(m_arrayTeams[i]);
	}
	int tab_stop[1] = {200};
	VERIFY(m_selTeamListBox.SetTabStops(1, tab_stop));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void dlgSelTeam::OnOK() 
{
	CString selTeam;
	
	int i = m_selTeamListBox.GetCurSel();
	m_arrayTeams.RemoveAll();
	if (i == LB_ERR)
	{
		CWnd* pmyCWnd = AfxGetMainWnd();
		pmyCWnd->MessageBox("No Teams were selected\nPlease select a Team",
			"Team not Selected!",MB_OK|MB_ICONEXCLAMATION);
	}
	else
	{
		m_selIndex = i;
		m_selTeamListBox.GetText(i,selTeam);
		m_arrayTeams.Add(selTeam);
	
		CDialog::OnOK();
	}
}
/////////////////////////////////////////////////////////////////////////////
// DlgSelLeague dialog


DlgSelLeague::DlgSelLeague(CWnd* pParent /*=NULL*/)
	: CDialog(DlgSelLeague::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgSelLeague)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgSelLeague::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgSelLeague)
	DDX_Control(pDX, IDC_SELLEAGUELISTBOX1, m_selLeagueListBox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgSelLeague, CDialog)
	//{{AFX_MSG_MAP(DlgSelLeague)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgSelLeague message handlers

BOOL DlgSelLeague::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_selLeagueListBox.ResetContent();
	for (int i=0; i<m_arrayLeagues.GetSize(); i++)
	{
		m_selLeagueListBox.AddString(m_arrayLeagues[i]);
	}
	int tab_stop[1] = {200};
	VERIFY(m_selLeagueListBox.SetTabStops(1, tab_stop));
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgSelLeague::OnOK() 
{
	CString selLeague;
	
	int i = m_selLeagueListBox.GetCurSel();
	m_arrayLeagues.RemoveAll();
	if (i == LB_ERR)
	{
		CWnd* pmyCWnd = AfxGetMainWnd();
		pmyCWnd->MessageBox("No League were selected\nPlease select a League",
			"League not Selected!",MB_OK|MB_ICONEXCLAMATION);
	}
	else
	{
		m_selIndex = i;
		m_selLeagueListBox.GetText(i,selLeague);
		m_arrayLeagues.Add(selLeague);
	
		CDialog::OnOK();
	}
}
/////////////////////////////////////////////////////////////////////////////
// EditTeam dialog


EditTeam::EditTeam(CWnd* pParent /*=NULL*/)
	: CDialog(EditTeam::IDD, pParent)
{
	//{{AFX_DATA_INIT(EditTeam)
	m_BallPark = _T("");
	m_ShortTeamName = _T("");
	m_TeamName = _T("");
	//}}AFX_DATA_INIT
}


void EditTeam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(EditTeam)
	DDX_Text(pDX, IDC_BALLPARK1, m_BallPark);
	DDV_MaxChars(pDX, m_BallPark, 30);
	DDX_Text(pDX, IDC_SHORTTEAM1, m_ShortTeamName);
	DDV_MaxChars(pDX, m_ShortTeamName, 3);
	DDX_Text(pDX, IDC_TEAM1, m_TeamName);
	DDV_MaxChars(pDX, m_TeamName, 40);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(EditTeam, CDialog)
	//{{AFX_MSG_MAP(EditTeam)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// EditTeam message handlers
