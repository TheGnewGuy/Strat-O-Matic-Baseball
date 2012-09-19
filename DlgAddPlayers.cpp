// DlgAddPlayers.cpp : implementation file
//

#include "stdafx.h"
#include "Baseball.h"
#include "FileStruct.h"
#include "DlgAddPlayers.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgAddPlayers dialog


DlgAddPlayers::DlgAddPlayers(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAddPlayers::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAddPlayers)
	m_TeamName = _T("");
	m_strBattingAverage = _T("");
	m_strOnBasePercentage = _T("");
	m_strSLG = _T("");
	//}}AFX_DATA_INIT
}


void DlgAddPlayers::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAddPlayers)
	DDX_Control(pDX, IDC_SPIN_HBP1, m_spinHBP1);
	DDX_Control(pDX, IDC_SPIN_GAMES2, m_spinGAMES2);
	DDX_Control(pDX, IDC_GAMES2, m_ceditGAMES2);
	DDX_Control(pDX, IDC_HBP1, m_ceditHBP1);
	DDX_Control(pDX, IDC_COMBO_BATTERHITS, m_BatterHits);
	DDX_Control(pDX, IDC_RIGHTFIELD, m_ceditRightField);
	DDX_Control(pDX, IDC_CENTERFIELD, m_ceditCenterField);
	DDX_Control(pDX, IDC_LEFTFIELD, m_ceditLeftField);
	DDX_Control(pDX, IDC_THIRDBASE, m_ceditThirdBase);
	DDX_Control(pDX, IDC_SHORTSTOP, m_ceditShortStop);
	DDX_Control(pDX, IDC_SECONDBASE, m_ceditSecondBase);
	DDX_Control(pDX, IDC_FIRSTBASE, m_ceditFirstBase);
	DDX_Control(pDX, IDC_CATCHER, m_ceditCatcher);
	DDX_Control(pDX, IDC_PITCHER, m_ceditPitcher);
	DDX_Control(pDX, IDC_SPIN_THIRDBASE, m_spinThirdBase);
	DDX_Control(pDX, IDC_SPIN_SHORTSTOP, m_spinShortStop);
	DDX_Control(pDX, IDC_SPIN_SECONDBASE, m_spinSecondBase);
	DDX_Control(pDX, IDC_SPIN_RIGHTFIELD, m_spinRightField);
	DDX_Control(pDX, IDC_SPIN_PITCHER, m_spinPitcher);
	DDX_Control(pDX, IDC_SPIN_LEFTFIELD, m_spinLeftField);
	DDX_Control(pDX, IDC_SPIN_FIRSTBASE, m_spinFirstBase);
	DDX_Control(pDX, IDC_SPIN_CENTERFIELD, m_spinCenterField);
	DDX_Control(pDX, IDC_SPIN_CATCHER, m_spinCatcher);
	DDX_Control(pDX, IDC_CS1, m_ceditCS);
	DDX_Control(pDX, IDC_SPIN_CS1, m_spinCS);
	DDX_Control(pDX, IDC_COMBO_PLAYERNAME1, m_comboPlayerName);
	DDX_Control(pDX, IDC_WALK1, m_ceditWalk);
	DDX_Control(pDX, IDC_STRIKEOUT1, m_ceditStrikeOut);
	DDX_Control(pDX, IDC_STOLENBASE1, m_ceditStolenBase);
	DDX_Control(pDX, IDC_SACRICIFE1, m_ceditSacrifie);
	DDX_Control(pDX, IDC_RUNS1, m_ceditRuns);
	DDX_Control(pDX, IDC_REACHEDONERROR1, m_ceditReachedOnError);
	DDX_Control(pDX, IDC_RBI1, m_ceditRBI);
	DDX_Control(pDX, IDC_HR1, m_ceditHomeRuns);
	DDX_Control(pDX, IDC_HITS1, m_ceditHits);
	DDX_Control(pDX, IDC_AB1, m_ceditAB);
	DDX_Control(pDX, IDC_3B1, m_cedit3B);
	DDX_Control(pDX, IDC_2B1, m_cedit2B);
	DDX_Control(pDX, IDC_COMBO_STEALING1, m_Stealing);
	DDX_Control(pDX, IDC_COMBO_RUNNING1, m_Running);
	DDX_Control(pDX, IDC_COMBO_HITRUN1, m_HitRun);
	DDX_Control(pDX, IDC_COMBO_BUNTING1, m_Bunting);
	DDX_Control(pDX, IDC_SPIN_WALK1, m_spinWalk);
	DDX_Control(pDX, IDC_SPIN_STRIKOUT1, m_spinStrikeOut);
	DDX_Control(pDX, IDC_SPIN_STOLENBASE1, m_spinStolenBase);
	DDX_Control(pDX, IDC_SPIN_SACRICIFE1, m_spinSacricife);
	DDX_Control(pDX, IDC_SPIN_RUNS1, m_spinRuns);
	DDX_Control(pDX, IDC_SPIN_REACHEDONERROR1, m_spinReachedOnError);
	DDX_Control(pDX, IDC_SPIN_RBI1, m_spinRBI);
	DDX_Control(pDX, IDC_SPIN_HR1, m_spinHR);
	DDX_Control(pDX, IDC_SPIN_AB1, m_spinAB);
	DDX_Control(pDX, IDC_SPIN_3B1, m_spin3B);
	DDX_Control(pDX, IDC_SPIN_2B1, m_spin2B);
	DDX_Control(pDX, IDC_SPIN_HITS1, m_spinHits);
	DDX_Text(pDX, IDC_TEAM0, m_TeamName);
	DDX_Text(pDX, IDC_BATTINGAVERAGE1, m_strBattingAverage);
	DDX_Text(pDX, IDC_ONBASEPERCENT1, m_strOnBasePercentage);
	DDX_Text(pDX, IDC_SLG1, m_strSLG);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAddPlayers, CDialog)
	//{{AFX_MSG_MAP(DlgAddPlayers)
	ON_BN_CLICKED(IDPLAYERADD1, OnPlayerAdd)
	ON_BN_CLICKED(IDPLAYERUPDATE1, OnPlayerUpdate)
	ON_BN_CLICKED(IDNEW, OnNewPlayer)
	ON_CBN_CLOSEUP(IDC_COMBO_PLAYERNAME1, OnCloseupComboPlayername1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAddPlayers message handlers

BOOL DlgAddPlayers::OnInitDialog() 
{
	LONG lTeamSection = 74;
	LONG lPlayerSection = m_structBatter.m_RecordSize;

	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_spin2B.SetRange(0, 1000);
	m_spin3B.SetRange(0, 1000);
	m_spinHR.SetRange(0, 1000);
	m_spinAB.SetRange(0, 1000);
	m_spinHits.SetRange(0, 1000);
	m_spinRBI.SetRange(0, 500);
	m_spinReachedOnError.SetRange(0, 100);
	m_spinRuns.SetRange(0, 1000);
	m_spinSacricife.SetRange(0, 100);
	m_spinStolenBase.SetRange(0, 100);
	m_spinStrikeOut.SetRange(0, 300);
	m_spinWalk.SetRange(0, 300);
	m_spinHBP1.SetRange(0, 300);
	m_spinGAMES2.SetRange(0, 500);
	m_spinCS.SetRange(0, 300);
	m_spin2B.SetBuddy( &m_cedit2B );
	m_spin3B.SetBuddy( &m_cedit3B );
	m_spinHR.SetBuddy( &m_ceditHomeRuns );
	m_spinAB.SetBuddy( &m_ceditAB );
	m_spinHits.SetBuddy( &m_ceditHits );
	m_spinRBI.SetBuddy( &m_ceditRBI );
	m_spinReachedOnError.SetBuddy( &m_ceditReachedOnError );
	m_spinRuns.SetBuddy( &m_ceditRuns );
	m_spinSacricife.SetBuddy( &m_ceditSacrifie );
	m_spinStolenBase.SetBuddy( &m_ceditStolenBase );
	m_spinStrikeOut.SetBuddy( &m_ceditStrikeOut );
	m_spinWalk.SetBuddy( &m_ceditWalk );
	m_spinCS.SetBuddy( &m_ceditCS );
	m_spinPitcher.SetBuddy( &m_ceditPitcher );
	m_spinCatcher.SetBuddy( &m_ceditCatcher );
	m_spinFirstBase.SetBuddy( &m_ceditFirstBase );
	m_spinSecondBase.SetBuddy( &m_ceditSecondBase );
	m_spinShortStop.SetBuddy( &m_ceditShortStop );
	m_spinThirdBase.SetBuddy( &m_ceditThirdBase );
	m_spinLeftField.SetBuddy( &m_ceditLeftField );
	m_spinCenterField.SetBuddy( &m_ceditCenterField );
	m_spinRightField.SetBuddy( &m_ceditRightField );
	m_spinHBP1.SetBuddy( &m_ceditHBP1 );
	m_spinGAMES2.SetBuddy( &m_ceditGAMES2 );
	m_spinPitcher.SetRange(0, 8);
	m_spinCatcher.SetRange(0, 5);
	m_spinFirstBase.SetRange(0, 5);
	m_spinSecondBase.SetRange(0, 5);
	m_spinShortStop.SetRange(0, 5);
	m_spinThirdBase.SetRange(0, 5);
	m_spinLeftField.SetRange(0, 5);
	m_spinCenterField.SetRange(0, 5);
	m_spinRightField.SetRange(0, 5);
	
	SetDlgItemText( IDC_COMBO_PLAYERNAME1, NULL );
	SetDlgItemInt( IDC_AB1, 0, FALSE );
	SetDlgItemInt( IDC_RUNS1, 0, FALSE );
	SetDlgItemInt( IDC_HITS1, 0, FALSE );
	SetDlgItemInt( IDC_RBI1, 0, FALSE );
	SetDlgItemInt( IDC_2B1, 0, FALSE );
	SetDlgItemInt( IDC_3B1, 0, FALSE );
	SetDlgItemInt( IDC_HR1, 0, FALSE );
	SetDlgItemInt( IDC_WALK1, 0, FALSE );
	SetDlgItemInt( IDC_STRIKEOUT1, 0, FALSE );
	SetDlgItemInt( IDC_REACHEDONERROR1, 0, FALSE );
	SetDlgItemInt( IDC_SACRICIFE1, 0, FALSE );
	SetDlgItemInt( IDC_STOLENBASE1, 0, FALSE );
	SetDlgItemText( IDC_BATTINGAVERAGE1, NULL );
	SetDlgItemText( IDC_SLG1, NULL );
	SetDlgItemText( IDC_ONBASEPERCENT1, NULL );
	SetDlgItemInt( IDC_CS1, 0, FALSE );
	SetDlgItemInt( IDC_HBP1, 0, FALSE );
	SetDlgItemInt( IDC_GAMES2, 0, FALSE );
	m_Bunting.SetCurSel(3);
	m_Stealing.SetCurSel(5);
	m_Running.SetCurSel(0);
	m_HitRun.SetCurSel(3);
	m_BatterHits.SetCurSel(0);
	SetDlgItemInt( IDC_PITCHER, 0, FALSE );
	SetDlgItemInt( IDC_CATCHER, 0, FALSE );
	SetDlgItemInt( IDC_FIRSTBASE, 0, FALSE );
	SetDlgItemInt( IDC_SECONDBASE, 0, FALSE );
	SetDlgItemInt( IDC_SHORTSTOP, 0, FALSE );
	SetDlgItemInt( IDC_THIRDBASE, 0, FALSE );
	SetDlgItemInt( IDC_LEFTFIELD, 0, FALSE );
	SetDlgItemInt( IDC_CENTERFIELD, 0, FALSE );
	SetDlgItemInt( IDC_RIGHTFIELD, 0, FALSE );
	SetDlgItemText( IDC_CHANCEBASIC, NULL );
	SetDlgItemText( IDC_CHANCELEFT, NULL );
	SetDlgItemText( IDC_CHANCERIGHT, NULL );

	// Build combo table for player display
	BuildPlayerNameCombo(m_FileName1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgAddPlayers::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
}

void DlgAddPlayers::OnPlayerAdd() 
{
	BOOL rc_GetDlgItemInt;
	BYTE count;
	CString filler10("          ");
	char cTemp[31];
	char buf[10];
	// TODO: Add your control notification handler code here
	count = 0;

	// Fill in all of the dialog fields
	m_structBatter.m_AB				= GetDlgItemInt( IDC_AB1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_Runs			= GetDlgItemInt( IDC_RUNS1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_Hits			= GetDlgItemInt( IDC_HITS1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_RBI			= GetDlgItemInt( IDC_RBI1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_2B				= GetDlgItemInt( IDC_2B1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_3B				= GetDlgItemInt( IDC_3B1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_HomeRuns		= GetDlgItemInt( IDC_HR1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_Walk			= GetDlgItemInt( IDC_WALK1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_StrikeOut		= GetDlgItemInt( IDC_STRIKEOUT1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_ReachedOnError	= GetDlgItemInt( IDC_REACHEDONERROR1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_Sacrifice		= GetDlgItemInt( IDC_SACRICIFE1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_StolenBase		= GetDlgItemInt( IDC_STOLENBASE1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_CS				= GetDlgItemInt( IDC_CS1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_bBunting		= m_Bunting.GetCurSel();
	m_structBatter.m_bStealing		= m_Stealing.GetCurSel();
	m_structBatter.m_bRunning		= m_Running.GetCurSel();
	m_structBatter.m_bHitRun		= m_HitRun.GetCurSel();
	m_structBatter.m_bBatterHits	= m_BatterHits.GetCurSel();
	GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
	cTemp[30]		= NULL;
	m_structBatter.m_PlayerName		= cTemp+filler10+filler10+filler10+filler10;
	m_structBatter.m_Pitcher		= GetDlgItemInt( IDC_PITCHER, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_Catcher		= GetDlgItemInt( IDC_CATCHER, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_FirstBase		= GetDlgItemInt( IDC_FIRSTBASE, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_SecondBase		= GetDlgItemInt( IDC_SECONDBASE, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_ShortStop		= GetDlgItemInt( IDC_SHORTSTOP, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_ThirdBase		= GetDlgItemInt( IDC_THIRDBASE, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_LeftField		= GetDlgItemInt( IDC_LEFTFIELD, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_CenterField	= GetDlgItemInt( IDC_CENTERFIELD, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_RightField		= GetDlgItemInt( IDC_LEFTFIELD, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_HBP			= GetDlgItemInt( IDC_HBP1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_Games			= GetDlgItemInt( IDC_GAMES2, &rc_GetDlgItemInt, FALSE );
	GetDlgItemText( IDC_CHANCEBASIC, cTemp, 6 );
	cTemp[6]		= NULL;
	m_structBatter.m_OBChanceBasic		= cTemp+filler10;
	GetDlgItemText( IDC_CHANCELEFT, cTemp, 6 );
	cTemp[6]		= NULL;
	m_structBatter.m_OBChanceLeft		= cTemp+filler10;
	GetDlgItemText( IDC_CHANCERIGHT, cTemp, 6 );
	cTemp[6]		= NULL;
	m_structBatter.m_OBChanceRight		= cTemp+filler10;

	// Open file and write new player
	m_structBatter.AddBatter(m_FileName1);

	if (m_structBatter.m_AB == 0)
	{
		SetDlgItemText( IDC_BATTINGAVERAGE1, "0" );
		SetDlgItemText( IDC_SLG1, "0" );
		SetDlgItemText( IDC_ONBASEPERCENT1, "0" );
	}
	else
	{
		m_fBattingAverage = (float)m_structBatter.m_Hits/m_structBatter.m_AB;
		sprintf(buf,"%1.3f",m_fBattingAverage);
		SetDlgItemText( IDC_BATTINGAVERAGE1, buf );
		m_fSLG = (float)((m_structBatter.m_Hits-(m_structBatter.m_2B+m_structBatter.m_3B+m_structBatter.m_HomeRuns))+(2*m_structBatter.m_2B)+(3*m_structBatter.m_3B)+(4*m_structBatter.m_HomeRuns))/(m_structBatter.m_AB);
		sprintf(buf,"%1.3f",m_fSLG);
		SetDlgItemText( IDC_SLG1, buf );
		m_fOnBasePercentage = (float)(m_structBatter.m_Hits+m_structBatter.m_Walk+m_structBatter.m_ReachedOnError+m_structBatter.m_Sacrifice)/(m_structBatter.m_AB+m_structBatter.m_Walk+m_structBatter.m_ReachedOnError+m_structBatter.m_Sacrifice);
		sprintf(buf,"%1.3f",m_fOnBasePercentage);
		SetDlgItemText( IDC_ONBASEPERCENT1, buf );
	}
	// ReBuild combo table for player display
	BuildPlayerNameCombo(m_FileName1);
}

void DlgAddPlayers::OnPlayerUpdate() 
{
	BOOL rc_GetDlgItemInt;
	char cTemp[31];
	CString filler10("          ");
	char buf[10];
	// TODO: Add your control notification handler code here
	m_structBatter.m_AB				= GetDlgItemInt( IDC_AB1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_Runs			= GetDlgItemInt( IDC_RUNS1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_Hits			= GetDlgItemInt( IDC_HITS1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_RBI			= GetDlgItemInt( IDC_RBI1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_2B				= GetDlgItemInt( IDC_2B1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_3B				= GetDlgItemInt( IDC_3B1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_HomeRuns		= GetDlgItemInt( IDC_HR1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_Walk			= GetDlgItemInt( IDC_WALK1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_StrikeOut		= GetDlgItemInt( IDC_STRIKEOUT1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_ReachedOnError	= GetDlgItemInt( IDC_REACHEDONERROR1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_Sacrifice		= GetDlgItemInt( IDC_SACRICIFE1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_StolenBase		= GetDlgItemInt( IDC_STOLENBASE1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_CS				= GetDlgItemInt( IDC_CS1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_bBunting		= m_Bunting.GetCurSel();
	m_structBatter.m_bStealing		= m_Stealing.GetCurSel();
	m_structBatter.m_bRunning		= m_Running.GetCurSel();
	m_structBatter.m_bHitRun		= m_HitRun.GetCurSel();
	m_structBatter.m_bBatterHits	= m_BatterHits.GetCurSel();
	m_structBatter.m_CS				= GetDlgItemInt( IDC_CS1, &rc_GetDlgItemInt, FALSE );
	GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
	cTemp[30]		= NULL;
	m_structBatter.m_PlayerName		= cTemp+filler10+filler10+filler10+filler10;
	m_structBatter.m_Pitcher		= GetDlgItemInt( IDC_PITCHER, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_Catcher		= GetDlgItemInt( IDC_CATCHER, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_FirstBase		= GetDlgItemInt( IDC_FIRSTBASE, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_SecondBase		= GetDlgItemInt( IDC_SECONDBASE, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_ShortStop		= GetDlgItemInt( IDC_SHORTSTOP, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_ThirdBase		= GetDlgItemInt( IDC_THIRDBASE, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_LeftField		= GetDlgItemInt( IDC_LEFTFIELD, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_CenterField	= GetDlgItemInt( IDC_CENTERFIELD, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_RightField		= GetDlgItemInt( IDC_LEFTFIELD, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_HBP			= GetDlgItemInt( IDC_HBP1, &rc_GetDlgItemInt, FALSE );
	m_structBatter.m_Games			= GetDlgItemInt( IDC_GAMES2, &rc_GetDlgItemInt, FALSE );
	GetDlgItemText( IDC_CHANCEBASIC, cTemp, 6 );
	cTemp[6]		= NULL;
	m_structBatter.m_OBChanceBasic		= cTemp+filler10;
	GetDlgItemText( IDC_CHANCELEFT, cTemp, 6 );
	cTemp[6]		= NULL;
	m_structBatter.m_OBChanceLeft		= cTemp+filler10;
	GetDlgItemText( IDC_CHANCERIGHT, cTemp, 6 );
	cTemp[6]		= NULL;
	m_structBatter.m_OBChanceRight		= cTemp+filler10;

	if (m_lSeekPlayerFile!=0)
	{
		// Open file and write new player
		m_structBatter.UpdateBatter(m_FileName1,m_lSeekPlayerFile);

		if (m_structBatter.m_AB == 0)
		{
			SetDlgItemText( IDC_BATTINGAVERAGE1, "0" );
			SetDlgItemText( IDC_SLG1, "0" );
			SetDlgItemText( IDC_ONBASEPERCENT1, "0" );
		}
		else
		{
			m_fBattingAverage = (float)m_structBatter.m_Hits/m_structBatter.m_AB;
			sprintf(buf,"%1.3f",m_fBattingAverage);
			SetDlgItemText( IDC_BATTINGAVERAGE1, buf );
			m_fSLG = (float)((m_structBatter.m_Hits-(m_structBatter.m_2B+m_structBatter.m_3B+m_structBatter.m_HomeRuns))+(2*m_structBatter.m_2B)+(3*m_structBatter.m_3B)+(4*m_structBatter.m_HomeRuns))/(m_structBatter.m_AB);
			sprintf(buf,"%1.3f",m_fSLG);
			SetDlgItemText( IDC_SLG1, buf );
			m_fOnBasePercentage = (float)(m_structBatter.m_Hits+m_structBatter.m_Walk+m_structBatter.m_ReachedOnError+m_structBatter.m_Sacrifice)/(m_structBatter.m_AB+m_structBatter.m_Walk+m_structBatter.m_ReachedOnError+m_structBatter.m_Sacrifice);
			sprintf(buf,"%1.3f",m_fOnBasePercentage);
			SetDlgItemText( IDC_ONBASEPERCENT1, buf );
		}
		// ReBuild combo table for player display
		BuildPlayerNameCombo(m_FileName1);
	}
}

void DlgAddPlayers::OnNewPlayer() 
{
	// TODO: Add your control notification handler code here
	SetDlgItemText( IDC_COMBO_PLAYERNAME1, NULL );
	SetDlgItemInt( IDC_AB1, 0, FALSE );
	SetDlgItemInt( IDC_RUNS1, 0, FALSE );
	SetDlgItemInt( IDC_HITS1, 0, FALSE );
	SetDlgItemInt( IDC_RBI1, 0, FALSE );
	SetDlgItemInt( IDC_2B1, 0, FALSE );
	SetDlgItemInt( IDC_3B1, 0, FALSE );
	SetDlgItemInt( IDC_HR1, 0, FALSE );
	SetDlgItemInt( IDC_WALK1, 0, FALSE );
	SetDlgItemInt( IDC_STRIKEOUT1, 0, FALSE );
	SetDlgItemInt( IDC_REACHEDONERROR1, 0, FALSE );
	SetDlgItemInt( IDC_SACRICIFE1, 0, FALSE );
	SetDlgItemInt( IDC_STOLENBASE1, 0, FALSE );
	SetDlgItemText( IDC_BATTINGAVERAGE1, NULL );
	SetDlgItemText( IDC_SLG1, NULL );
	SetDlgItemText( IDC_ONBASEPERCENT1, NULL );
	SetDlgItemInt( IDC_CS1, 0, FALSE );
	SetDlgItemInt( IDC_HBP1, 0, FALSE );
	SetDlgItemInt( IDC_GAMES2, 0, FALSE );
	m_Bunting.SetCurSel(3);
	m_Stealing.SetCurSel(5);
	m_Running.SetCurSel(0);
	m_HitRun.SetCurSel(3);
	m_BatterHits.SetCurSel(0);
	SetDlgItemInt( IDC_PITCHER, 0, FALSE );
	SetDlgItemInt( IDC_CATCHER, 0, FALSE );
	SetDlgItemInt( IDC_FIRSTBASE, 0, FALSE );
	SetDlgItemInt( IDC_SECONDBASE, 0, FALSE );
	SetDlgItemInt( IDC_SHORTSTOP, 0, FALSE );
	SetDlgItemInt( IDC_THIRDBASE, 0, FALSE );
	SetDlgItemInt( IDC_LEFTFIELD, 0, FALSE );
	SetDlgItemInt( IDC_CENTERFIELD, 0, FALSE );
	SetDlgItemInt( IDC_RIGHTFIELD, 0, FALSE );
	SetDlgItemText( IDC_CHANCEBASIC, NULL );
	SetDlgItemText( IDC_CHANCELEFT, NULL );
	SetDlgItemText( IDC_CHANCERIGHT, NULL );
}

void DlgAddPlayers::OnCloseupComboPlayername1() 
{
	int i, rcompare, rgetcursel;
	BYTE count;
	CString csPlayer;
	LONG lTeamSection = 74;
	LONG lPlayerSection = m_structBatter.m_RecordSize;
	CString rString;
	char buf[10];
	CWnd* pmyCWnd;

	// TODO: Add your control notification handler code here
	rgetcursel = m_comboPlayerName.GetCurSel();
	if (rgetcursel != CB_ERR)
	{
		m_comboPlayerName.GetLBText( rgetcursel, rString );
		count = m_structBatter.GetCountBatter(m_FileName1);
		csPlayer.Empty();
		rcompare = rString.Compare(csPlayer);
		i = -1;
		while (rcompare)
		{
			i++;
			if (i >= count)
			{
				// Player compare failed so display message
				pmyCWnd = AfxGetMainWnd();
				pmyCWnd->MessageBox("Player Compare Failed",
					"Player Compare Failed",MB_OK|MB_ICONEXCLAMATION);
				break;
			}
			// Read in the player Data
			m_lSeekPlayerFile = lTeamSection+(i*lPlayerSection);
			m_structBatter.GetBatter(m_FileName1,m_lSeekPlayerFile);
			csPlayer = m_structBatter.m_PlayerName;
			rcompare = rString.Compare(csPlayer);
		}

		// Read in the player Data
		m_structBatter.GetBatter(m_FileName1,m_lSeekPlayerFile);
		// Set the Dialog Items
		SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structBatter.m_PlayerName );
		SetDlgItemInt( IDC_AB1, m_structBatter.m_AB, FALSE );
		SetDlgItemInt( IDC_RUNS1, m_structBatter.m_Runs, FALSE );
		SetDlgItemInt( IDC_HITS1, m_structBatter.m_Hits, FALSE );
		SetDlgItemInt( IDC_RBI1, m_structBatter.m_RBI, FALSE );
		SetDlgItemInt( IDC_2B1, m_structBatter.m_2B, FALSE );
		SetDlgItemInt( IDC_3B1, m_structBatter.m_3B, FALSE );
		SetDlgItemInt( IDC_HR1, m_structBatter.m_HomeRuns, FALSE );
		SetDlgItemInt( IDC_WALK1, m_structBatter.m_Walk, FALSE );
		SetDlgItemInt( IDC_STRIKEOUT1, m_structBatter.m_StrikeOut, FALSE );
		SetDlgItemInt( IDC_REACHEDONERROR1, m_structBatter.m_ReachedOnError, FALSE );
		SetDlgItemInt( IDC_SACRICIFE1, m_structBatter.m_Sacrifice, FALSE );
		SetDlgItemInt( IDC_STOLENBASE1, m_structBatter.m_StolenBase, FALSE );
		SetDlgItemInt( IDC_CS1, m_structBatter.m_CS, FALSE );
		m_Bunting.SetCurSel(m_structBatter.m_bBunting);
		m_Stealing.SetCurSel(m_structBatter.m_bStealing);
		m_Running.SetCurSel(m_structBatter.m_bRunning);
		m_HitRun.SetCurSel(m_structBatter.m_bHitRun);
		m_BatterHits.SetCurSel(m_structBatter.m_bBatterHits);
		SetDlgItemInt( IDC_PITCHER, m_structBatter.m_Pitcher, FALSE );
		SetDlgItemInt( IDC_CATCHER, m_structBatter.m_Catcher, FALSE );
		SetDlgItemInt( IDC_FIRSTBASE, m_structBatter.m_FirstBase, FALSE );
		SetDlgItemInt( IDC_SECONDBASE, m_structBatter.m_SecondBase, FALSE );
		SetDlgItemInt( IDC_SHORTSTOP, m_structBatter.m_ShortStop, FALSE );
		SetDlgItemInt( IDC_THIRDBASE, m_structBatter.m_ThirdBase, FALSE );
		SetDlgItemInt( IDC_LEFTFIELD, m_structBatter.m_LeftField, FALSE );
		SetDlgItemInt( IDC_CENTERFIELD, m_structBatter.m_CenterField, FALSE );
		SetDlgItemInt( IDC_RIGHTFIELD, m_structBatter.m_RightField, FALSE );
		SetDlgItemText( IDC_CHANCEBASIC, m_structBatter.m_OBChanceBasic );
		SetDlgItemText( IDC_CHANCELEFT, m_structBatter.m_OBChanceLeft );
		SetDlgItemText( IDC_CHANCERIGHT, m_structBatter.m_OBChanceRight );
		SetDlgItemInt( IDC_GAMES2, m_structBatter.m_Games, FALSE );
		SetDlgItemInt( IDC_HBP1, m_structBatter.m_HBP, FALSE );
		if (m_structBatter.m_AB == 0)
		{
			SetDlgItemText( IDC_BATTINGAVERAGE1, "0" );
			SetDlgItemText( IDC_SLG1, "0" );
			SetDlgItemText( IDC_ONBASEPERCENT1, "0" );
		}
		else
		{
			m_fBattingAverage = (float)m_structBatter.m_Hits/m_structBatter.m_AB;
			sprintf(buf,"%1.3f",m_fBattingAverage);
			SetDlgItemText( IDC_BATTINGAVERAGE1, buf );
			m_fSLG = (float)((m_structBatter.m_Hits-(m_structBatter.m_2B+m_structBatter.m_3B+m_structBatter.m_HomeRuns))+(2*m_structBatter.m_2B)+(3*m_structBatter.m_3B)+(4*m_structBatter.m_HomeRuns))/(m_structBatter.m_AB);
			sprintf(buf,"%1.3f",m_fSLG);
			SetDlgItemText( IDC_SLG1, buf );
			m_fOnBasePercentage = (float)(m_structBatter.m_Hits+m_structBatter.m_Walk+m_structBatter.m_ReachedOnError+m_structBatter.m_Sacrifice)/(m_structBatter.m_AB+m_structBatter.m_Walk+m_structBatter.m_ReachedOnError+m_structBatter.m_Sacrifice);
			sprintf(buf,"%1.3f",m_fOnBasePercentage);
			SetDlgItemText( IDC_ONBASEPERCENT1, buf );
		}
	}
	else
	{
		// No player selected Edit Box being used, set seek to 0 as flag
		m_lSeekPlayerFile = 0;
	}
}

void DlgAddPlayers::BuildPlayerNameCombo(CString myFileName)
{
	BYTE count;
	int i;
	LONG lTeamSection = 74;
	LONG lPlayerSection = m_structBatter.m_RecordSize;

	m_comboPlayerName.ResetContent();
	// Get count of players in file
	count = m_structBatter.GetCountBatter(myFileName);
	// Open file and build player ComboBox
	for (i=0; i<count; i++)
	{
		m_lSeekPlayerFile = lTeamSection+(i*lPlayerSection);
		m_structBatter.GetBatter(myFileName ,m_lSeekPlayerFile);
		m_comboPlayerName.AddString(m_structBatter.m_PlayerName);
	}
	m_lSeekPlayerFile = 0;
}
/////////////////////////////////////////////////////////////////////////////
// DlgAddPitchers dialog


DlgAddPitchers::DlgAddPitchers(CWnd* pParent /*=NULL*/)
	: CDialog(DlgAddPitchers::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgAddPitchers)
	m_TeamName = _T("");
	//}}AFX_DATA_INIT
}


void DlgAddPitchers::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgAddPitchers)
	DDX_Control(pDX, IDC_SPIN_GAMES1, m_spinGAMES1);
	DDX_Control(pDX, IDC_SPIN_COMPLETEGAMES1, m_spinCOMPLETEGAMES1);
	DDX_Control(pDX, IDC_COMPLETEGAMES1, m_ceditCOMPLETEGAMES1);
	DDX_Control(pDX, IDC_GAMES1, m_ceditGAMES1);
	DDX_Control(pDX, IDC_STARTS1, m_ceditSTARTS1);
	DDX_Control(pDX, IDC_SPIN_STARTS1, m_spinSTARTS1);
	DDX_Control(pDX, IDC_STARTER1, m_ceditSTARTER1);
	DDX_Control(pDX, IDC_COMBO_PLAYERNAME1, m_comboPLAYERNAME);
	DDX_Control(pDX, IDC_COMBO_PITCHERTHROWS, m_comboPITCHERTHROWS);
	DDX_Control(pDX, IDC_COMBO_HOLD1, m_comboHOLD);
	DDX_Control(pDX, IDC_COMBO_BUNTING1, m_comboBUNTING);
	DDX_Control(pDX, IDC_WINS1, m_ceditWINS1);
	DDX_Control(pDX, IDC_WALK1, m_ceditWALK1);
	DDX_Control(pDX, IDC_STRIKEOUT1, m_ceditSTRIKEOUT1);
	DDX_Control(pDX, IDC_SPIN_STARER1, m_spinSTARTER1);
	DDX_Control(pDX, IDC_SPIN_WINS1, m_spinWINS1);
	DDX_Control(pDX, IDC_SPIN_WALK1, m_spinWALK1);
	DDX_Control(pDX, IDC_SPIN_STRIKOUT1, m_spinSTRIKEOUT);
	DDX_Control(pDX, IDC_SPIN_SAVES1, m_spinSAVES1);
	DDX_Control(pDX, IDC_SPIN_RELIEF1, m_spinRELIEF1);
	DDX_Control(pDX, IDC_SPIN_LOSS1, m_spinLOSS1);
	DDX_Control(pDX, IDC_SPIN_HR1, m_spinHR1);
	DDX_Control(pDX, IDC_SPIN_HITS1, m_spinHITS1);
	DDX_Control(pDX, IDC_SPIN_ER1, m_spinER1);
	DDX_Control(pDX, IDC_SAVES1, m_ceditSAVES1);
	DDX_Control(pDX, IDC_RELIEF1, m_ceditRELIEF1);
	DDX_Control(pDX, IDC_LOSS1, m_ceditLOSS1);
	DDX_Control(pDX, IDC_HR1, m_ceditHR1);
	DDX_Control(pDX, IDC_HITS1, m_ceditHITS1);
	DDX_Control(pDX, IDC_ER1, m_ceditER1);
	DDX_Text(pDX, IDC_TEAM0, m_TeamName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgAddPitchers, CDialog)
	//{{AFX_MSG_MAP(DlgAddPitchers)
	ON_CBN_CLOSEUP(IDC_COMBO_PLAYERNAME1, OnCloseupComboPlayername1)
	ON_BN_CLICKED(IDNEW, OnNew)
	ON_BN_CLICKED(IDPLAYERUPDATE1, OnPitcherUpdate)
	ON_BN_CLICKED(IDPLAYERADD1, OnPitcherAdd)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgAddPitchers message handlers

BOOL DlgAddPitchers::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_spinER1.SetRange(0, 300);
	m_spinER1.SetBuddy( &m_ceditER1 );
	m_spinHITS1.SetRange(0, 300);
	m_spinHITS1.SetBuddy( &m_ceditHITS1 );
	m_spinHR1.SetRange(0, 300);
	m_spinHR1.SetBuddy( &m_ceditHR1 );
	m_spinLOSS1.SetRange(0, 300);
	m_spinLOSS1.SetBuddy( &m_ceditLOSS1 );
	m_spinRELIEF1.SetRange(0, 300);
	m_spinRELIEF1.SetBuddy( &m_ceditRELIEF1 );
	m_spinSAVES1.SetRange(0, 300);
	m_spinSAVES1.SetBuddy( &m_ceditSAVES1 );
	m_spinSTARTER1.SetRange(0, 300);
	m_spinSTARTER1.SetBuddy( &m_ceditSTARTER1 );
	m_spinSTRIKEOUT.SetRange(0, 300);
	m_spinSTRIKEOUT.SetBuddy( &m_ceditSTRIKEOUT1 );
	m_spinWALK1.SetRange(0, 300);
	m_spinWALK1.SetBuddy( &m_ceditWALK1 );
	m_spinWINS1.SetRange(0, 300);
	m_spinWINS1.SetBuddy( &m_ceditWINS1 );
	m_spinSTARTS1.SetRange(0, 100);
	m_spinSTARTS1.SetBuddy( &m_ceditSTARTS1 );
	m_spinGAMES1.SetRange(0, 500);
	m_spinGAMES1.SetBuddy( &m_ceditGAMES1 );
	m_spinCOMPLETEGAMES1.SetRange(0, 500);
	m_spinCOMPLETEGAMES1.SetBuddy( &m_ceditCOMPLETEGAMES1 );

	m_comboBUNTING.SetCurSel(4);
	m_comboHOLD.SetCurSel(4);
	m_comboPITCHERTHROWS.SetCurSel(1);
	
	SetDlgItemText( IDC_COMBO_PLAYERNAME1, NULL );
	SetDlgItemText( IDC_CHANCEBASIC, NULL );
	SetDlgItemText( IDC_CHANCELEFT, NULL );
	SetDlgItemText( IDC_CHANCERIGHT, NULL );
	SetDlgItemText( IDC_IP1, NULL );
	SetDlgItemText( IDC_ERA1, NULL );
	SetDlgItemText( IDC_TRG1, NULL );
	SetDlgItemInt( IDC_STARTER1, 0, FALSE );
	SetDlgItemInt( IDC_WINS1, 0, FALSE );
	SetDlgItemInt( IDC_WALK1, 0, FALSE );
	SetDlgItemInt( IDC_STRIKEOUT1, 0, FALSE );
	SetDlgItemInt( IDC_SAVES1, 0, FALSE );
	SetDlgItemInt( IDC_RELIEF1, 0, FALSE );
	SetDlgItemInt( IDC_LOSS1, 0, FALSE );
	SetDlgItemInt( IDC_IP1, 0, FALSE );
	SetDlgItemInt( IDC_HR1, 0, FALSE );
	SetDlgItemInt( IDC_HITS1, 0, FALSE );
	SetDlgItemInt( IDC_ER1, 0, FALSE );
	SetDlgItemInt( IDC_STARTS1, 0, FALSE );
	SetDlgItemInt( IDC_GAMES1, 0, FALSE );
	SetDlgItemInt( IDC_COMPLETEGAMES1, 0, FALSE );

	// Build combo table for player display
	BuildPlayerNameCombo(m_FileName1);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgAddPitchers::BuildPlayerNameCombo(CString myFileName)
{
	BYTE count;
	int i;
	LONG lCount = sizeof(BYTE);
	LONG lPlayerSection = m_structPitcher.m_RecordSize;

	m_comboPLAYERNAME.ResetContent();
	// Get count of players in file
	count = m_structPitcher.GetCountPitcher(myFileName);
	// Open file and build player ComboBox
	for (i=0; i<count; i++)
	{
		m_lSeekPlayerFile = lCount+(i*lPlayerSection);
		m_structPitcher.GetPitcher(myFileName ,m_lSeekPlayerFile);
		m_comboPLAYERNAME.AddString(m_structPitcher.m_PitcherName);
	}
	m_lSeekPlayerFile = 0;
}

void DlgAddPitchers::OnCloseupComboPlayername1() 
{
	int i, rcompare, rgetcursel;
	BYTE count;
	CString csPlayer;
	LONG lTeamSection = sizeof(BYTE);
	LONG lPlayerSection = m_structPitcher.m_RecordSize;
	CString rString;
	char buf[10];
	CWnd* pmyCWnd;

	// TODO: Add your control notification handler code here
	rgetcursel = m_comboPLAYERNAME.GetCurSel();
	if (rgetcursel != CB_ERR)
	{
		m_comboPLAYERNAME.GetLBText( rgetcursel, rString );
		count = m_structPitcher.GetCountPitcher(m_FileName1);
		csPlayer.Empty();
		rcompare = rString.Compare(csPlayer);
		i = -1;
		while (rcompare)
		{
			i++;
			if (i >= count)
			{
				// Player compare failed so display message
				pmyCWnd = AfxGetMainWnd();
				pmyCWnd->MessageBox("Player Compare Failed",
					"Pitcher Compare Failed",MB_OK|MB_ICONEXCLAMATION);
				break;
			}
			// Read in the player Data
			m_lSeekPlayerFile = lTeamSection+(i*lPlayerSection);
			m_structPitcher.GetPitcher(m_FileName1,m_lSeekPlayerFile);
			csPlayer = m_structPitcher.m_PitcherName;
			rcompare = rString.Compare(csPlayer);
		}

		// Read in the player Data
		m_structPitcher.GetPitcher(m_FileName1,m_lSeekPlayerFile);
		// Set the Dialog Items
		SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structPitcher.m_PitcherName );
		SetDlgItemInt( IDC_STARTER1, m_structPitcher.m_Starter, FALSE );
		SetDlgItemInt( IDC_WINS1, m_structPitcher.m_Wins, FALSE );
		SetDlgItemInt( IDC_WALK1, m_structPitcher.m_Walks, FALSE );
		SetDlgItemInt( IDC_STRIKEOUT1, m_structPitcher.m_Strikeouts, FALSE );
		SetDlgItemInt( IDC_SAVES1, m_structPitcher.m_Saves, FALSE );
		SetDlgItemInt( IDC_RELIEF1, m_structPitcher.m_Relief, FALSE );
		SetDlgItemInt( IDC_LOSS1, m_structPitcher.m_Loss, FALSE );
		SetDlgItemInt( IDC_HR1, m_structPitcher.m_HomeRuns, FALSE );
		SetDlgItemInt( IDC_HITS1, m_structPitcher.m_Hits, FALSE );
		SetDlgItemInt( IDC_ER1, m_structPitcher.m_ER, FALSE );
		SetDlgItemInt( IDC_STARTS1, m_structPitcher.m_Starts, FALSE );
		SetDlgItemInt( IDC_GAMES1, m_structPitcher.m_Games, FALSE );
		SetDlgItemInt( IDC_COMPLETEGAMES1, m_structPitcher.m_CompGames, FALSE );

		m_comboHOLD.SetCurSel(m_structPitcher.m_Hold);
		m_comboBUNTING.SetCurSel(m_structPitcher.m_Bunting);
		m_comboPITCHERTHROWS.SetCurSel(m_structPitcher.m_Throws);

		SetDlgItemText( IDC_CHANCEBASIC, m_structPitcher.m_OBChanceBasic );
		SetDlgItemText( IDC_CHANCELEFT, m_structPitcher.m_OBChanceLeft );
		SetDlgItemText( IDC_CHANCERIGHT, m_structPitcher.m_OBChanceRight );

		SetDlgItemText( IDC_IP1, m_structPitcher.m_IP );
		
		m_fIP = atof(m_structPitcher.m_IP);

		if (m_fIP == 0)
		{
			SetDlgItemText( IDC_ERA1, "0" );
			SetDlgItemText( IDC_TRG1, "0" );
		}
		else
		{
			m_fERA = (double)(m_structPitcher.m_ER*9)/m_fIP;
			sprintf(buf,"%1.2f",m_fERA);
			SetDlgItemText( IDC_ERA1, buf );
			m_fTRG = (double)((m_structPitcher.m_Hits+m_structPitcher.m_Walks)*9)/m_fIP;
			sprintf(buf,"%1.2f",m_fTRG);
			SetDlgItemText( IDC_TRG1, buf );
		}
	}
	else
	{
		// No player selected Edit Box being used, set seek to 0 as flag
		m_lSeekPlayerFile = 0;
	}
}

void DlgAddPitchers::OnNew() 
{
	m_comboBUNTING.SetCurSel(4);
	m_comboHOLD.SetCurSel(4);
	m_comboPITCHERTHROWS.SetCurSel(1);
	
	SetDlgItemText( IDC_COMBO_PLAYERNAME1, NULL );
	SetDlgItemText( IDC_CHANCEBASIC, NULL );
	SetDlgItemText( IDC_CHANCELEFT, NULL );
	SetDlgItemText( IDC_CHANCERIGHT, NULL );
	SetDlgItemText( IDC_IP1, NULL );
	SetDlgItemText( IDC_ERA1, NULL );
	SetDlgItemText( IDC_TRG1, NULL );
	SetDlgItemInt( IDC_STARTER1, 0, FALSE );
	SetDlgItemInt( IDC_WINS1, 0, FALSE );
	SetDlgItemInt( IDC_WALK1, 0, FALSE );
	SetDlgItemInt( IDC_STRIKEOUT1, 0, FALSE );
	SetDlgItemInt( IDC_SAVES1, 0, FALSE );
	SetDlgItemInt( IDC_RELIEF1, 0, FALSE );
	SetDlgItemInt( IDC_LOSS1, 0, FALSE );
	SetDlgItemInt( IDC_HR1, 0, FALSE );
	SetDlgItemInt( IDC_HITS1, 0, FALSE );
	SetDlgItemInt( IDC_ER1, 0, FALSE );
	SetDlgItemInt( IDC_STARTS1, 0, FALSE );
	SetDlgItemInt( IDC_GAMES1, 0, FALSE );
	SetDlgItemInt( IDC_COMPLETEGAMES1, 0, FALSE );
}

void DlgAddPitchers::OnPitcherUpdate() 
{
	BOOL rc_GetDlgItemInt;
	char cTemp[31];
	CString filler10("          ");
	char buf[10];
	// TODO: Add your control notification handler code here

	// Fill in all of the dialog fields
	GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
	cTemp[30]		= NULL;
	m_structPitcher.m_PitcherName	= cTemp+filler10+filler10+filler10+filler10;
	GetDlgItemText( IDC_IP1, cTemp, 7 );
	cTemp[7]		= NULL;
	m_structPitcher.m_IP			= cTemp;
	m_structPitcher.m_Starter		= GetDlgItemInt( IDC_STARTER1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Wins			= GetDlgItemInt( IDC_WINS1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Walks			= GetDlgItemInt( IDC_WALK1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Strikeouts	= GetDlgItemInt( IDC_STRIKEOUT1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Saves			= GetDlgItemInt( IDC_SAVES1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Relief		= GetDlgItemInt( IDC_RELIEF1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Loss			= GetDlgItemInt( IDC_LOSS1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_HomeRuns		= GetDlgItemInt( IDC_HR1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Hits			= GetDlgItemInt( IDC_HITS1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_ER			= GetDlgItemInt( IDC_ER1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Starts		= GetDlgItemInt( IDC_STARTS1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Games			= GetDlgItemInt( IDC_GAMES1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_CompGames		= GetDlgItemInt( IDC_COMPLETEGAMES1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Bunting		= m_comboBUNTING.GetCurSel();
	m_structPitcher.m_Hold			= m_comboHOLD.GetCurSel();
	m_structPitcher.m_Throws		= m_comboPITCHERTHROWS.GetCurSel();
	GetDlgItemText( IDC_CHANCEBASIC, cTemp, 6 );
	cTemp[6]		= NULL;
	m_structPitcher.m_OBChanceBasic	= cTemp+filler10;
	GetDlgItemText( IDC_CHANCELEFT, cTemp, 6 );
	cTemp[6]		= NULL;
	m_structPitcher.m_OBChanceLeft	= cTemp+filler10;
	GetDlgItemText( IDC_CHANCERIGHT, cTemp, 6 );
	cTemp[6]		= NULL;
	m_structPitcher.m_OBChanceRight	= cTemp+filler10;

	if (m_lSeekPlayerFile!=0)
	{
		// Open file and write new player
		m_structPitcher.UpdatePitcher(m_FileName1,m_lSeekPlayerFile);
		
		m_fIP = atof(m_structPitcher.m_IP);

		if (m_fIP == 0)
		{
			SetDlgItemText( IDC_ERA1, "0" );
			SetDlgItemText( IDC_TRG1, "0" );
		}
		else
		{
			m_fERA = (double)(m_structPitcher.m_ER*9)/m_fIP;
			sprintf(buf,"%1.2f",m_fERA);
			SetDlgItemText( IDC_ERA1, buf );
			m_fTRG = (double)((m_structPitcher.m_Hits+m_structPitcher.m_Walks)*9)/m_fIP;
			sprintf(buf,"%1.2f",m_fTRG);
			SetDlgItemText( IDC_TRG1, buf );
		}
		// ReBuild combo table for player display
		BuildPlayerNameCombo(m_FileName1);
	}
}

void DlgAddPitchers::OnPitcherAdd() 
{
	BOOL rc_GetDlgItemInt;
	CString filler10("          ");
	char cTemp[31];
	char buf[10];
	// TODO: Add your control notification handler code here

	// Fill in all of the dialog fields
	GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
	cTemp[30]		= NULL;
	m_structPitcher.m_PitcherName	= cTemp+filler10+filler10+filler10+filler10;
	GetDlgItemText( IDC_IP1, cTemp, 7 );
	cTemp[7]		= NULL;
	m_structPitcher.m_IP			= cTemp;
	m_structPitcher.m_Starter		= GetDlgItemInt( IDC_STARTER1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Wins			= GetDlgItemInt( IDC_WINS1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Walks			= GetDlgItemInt( IDC_WALK1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Strikeouts	= GetDlgItemInt( IDC_STRIKEOUT1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Saves			= GetDlgItemInt( IDC_SAVES1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Relief		= GetDlgItemInt( IDC_RELIEF1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Loss			= GetDlgItemInt( IDC_LOSS1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_HomeRuns		= GetDlgItemInt( IDC_HR1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Hits			= GetDlgItemInt( IDC_HITS1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_ER			= GetDlgItemInt( IDC_ER1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Starts		= GetDlgItemInt( IDC_STARTS1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Games			= GetDlgItemInt( IDC_GAMES1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_CompGames		= GetDlgItemInt( IDC_COMPLETEGAMES1, &rc_GetDlgItemInt, FALSE );
	m_structPitcher.m_Bunting		= m_comboBUNTING.GetCurSel();
	m_structPitcher.m_Hold			= m_comboHOLD.GetCurSel();
	m_structPitcher.m_Throws		= m_comboPITCHERTHROWS.GetCurSel();
	GetDlgItemText( IDC_CHANCEBASIC, cTemp, 6 );
	cTemp[6]		= NULL;
	m_structPitcher.m_OBChanceBasic	= cTemp+filler10;
	GetDlgItemText( IDC_CHANCELEFT, cTemp, 6 );
	cTemp[6]		= NULL;
	m_structPitcher.m_OBChanceLeft	= cTemp+filler10;
	GetDlgItemText( IDC_CHANCERIGHT, cTemp, 6 );
	cTemp[6]		= NULL;
	m_structPitcher.m_OBChanceRight	= cTemp+filler10;

	// Open file and write new player
	m_structPitcher.AddPitcher(m_FileName1);
		
	m_fIP = atof(m_structPitcher.m_IP);

	if (m_fIP == 0)
	{
		SetDlgItemText( IDC_ERA1, "0" );
		SetDlgItemText( IDC_TRG1, "0" );
	}
	else
	{
		m_fERA = (double)(m_structPitcher.m_ER*9)/m_fIP;
		sprintf(buf,"%1.2f",m_fERA);
		SetDlgItemText( IDC_ERA1, buf );
		m_fTRG = (double)((m_structPitcher.m_Hits+m_structPitcher.m_Walks)*9)/m_fIP;
		sprintf(buf,"%1.2f",m_fTRG);
		SetDlgItemText( IDC_TRG1, buf );
	}
	// ReBuild combo table for player display
	BuildPlayerNameCombo(m_FileName1);
}
