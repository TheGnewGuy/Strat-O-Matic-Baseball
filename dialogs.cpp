// dialogs.cpp : implementation file
//

#include "stdafx.h"
#include "baseball.h"
#include "dialogs.h"
#include "registry.h"
#include "BaseballDoc.h"
#include "BaseballView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PropertyPageBatters property page

IMPLEMENT_DYNCREATE(PropertyPageBatters, CPropertyPage)

PropertyPageBatters::PropertyPageBatters() : CPropertyPage(PropertyPageBatters::IDD)
{
	//{{AFX_DATA_INIT(PropertyPageBatters)
	m_TeamName = _T("");
	//}}AFX_DATA_INIT
	
	// Get pointer to Doc
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window.
	CBaseballView *pView = (CBaseballView *) pChild->GetActiveView();
	m_pDocVoid = pView->GetDocument();

	m_bChangedFlag = FALSE;
}

PropertyPageBatters::~PropertyPageBatters()
{
}

void PropertyPageBatters::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropertyPageBatters)
	DDX_Control(pDX, IDC_SPIN_THIRDBASE, m_spinThirdBase);
	DDX_Control(pDX, IDC_SPIN_SHORTSTOP, m_spinShortStop);
	DDX_Control(pDX, IDC_SPIN_SECONDBASE, m_spinSecondBase);
	DDX_Control(pDX, IDC_SPIN_RIGHTFIELD, m_spinRightField);
	DDX_Control(pDX, IDC_SPIN_PITCHER, m_spinPitcher);
	DDX_Control(pDX, IDC_SPIN_LEFTFIELD, m_spinLeftField);
	DDX_Control(pDX, IDC_SPIN_FIRSTBASE, m_spinFirstBase);
	DDX_Control(pDX, IDC_SPIN_ERSS, m_spinERSS);
	DDX_Control(pDX, IDC_SPIN_ERRF, m_spinERRF);
	DDX_Control(pDX, IDC_SPIN_ERP, m_spinERP);
	DDX_Control(pDX, IDC_SPIN_ERLF, m_spinERLF);
	DDX_Control(pDX, IDC_SPIN_ERCF, m_spinERCF);
	DDX_Control(pDX, IDC_SPIN_ERC, m_spinERC);
	DDX_Control(pDX, IDC_SPIN_ER3B, m_spinER3B);
	DDX_Control(pDX, IDC_SPIN_ER2B, m_spinER2B);
	DDX_Control(pDX, IDC_SPIN_ER1B, m_spinER1B);
	DDX_Control(pDX, IDC_SPIN_CENTERFIELD, m_spinCenterField);
	DDX_Control(pDX, IDC_SPIN_CATCHER, m_spinCatcher);
	DDX_Control(pDX, IDC_ERSS, m_ceditERSS);
	DDX_Control(pDX, IDC_ERRF, m_ceditERRF);
	DDX_Control(pDX, IDC_ERP, m_ceditERP);
	DDX_Control(pDX, IDC_ERLF, m_ceditERLF);
	DDX_Control(pDX, IDC_ERCF, m_ceditERCF);
	DDX_Control(pDX, IDC_ERC, m_ceditERC);
	DDX_Control(pDX, IDC_ER3B, m_ceditER3B);
	DDX_Control(pDX, IDC_ER2B, m_ceditER2B);
	DDX_Control(pDX, IDC_ER1B, m_ceditER1B);
	DDX_Control(pDX, IDC_COMBO_PLAYERNAME1, m_comboPlayerName);
	DDX_Control(pDX, IDC_THIRDBASE, m_ceditThirdBase);
	DDX_Control(pDX, IDC_SHORTSTOP, m_ceditShortStop);
	DDX_Control(pDX, IDC_SECONDBASE, m_ceditSecondBase);
	DDX_Control(pDX, IDC_RIGHTFIELD, m_ceditRightField);
	DDX_Control(pDX, IDC_PITCHER, m_ceditPitcher);
	DDX_Control(pDX, IDC_LEFTFIELD, m_ceditLeftField);
	DDX_Control(pDX, IDC_FIRSTBASE, m_ceditFirstBase);
	DDX_Control(pDX, IDC_CENTERFIELD, m_ceditCenterField);
	DDX_Control(pDX, IDC_CATCHER, m_ceditCatcher);
	DDX_Text(pDX, IDC_TEAM0, m_TeamName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PropertyPageBatters, CPropertyPage)
	//{{AFX_MSG_MAP(PropertyPageBatters)
	ON_CBN_CLOSEUP(IDC_COMBO_PLAYERNAME1, OnCloseupComboPlayerName)
	ON_EN_CHANGE(IDC_CATCHER, OnChangeCatcher)
	ON_EN_CHANGE(IDC_CENTERFIELD, OnChangeCenterfield)
	ON_CBN_EDITCHANGE(IDC_COMBO_PLAYERNAME1, OnEditchangeComboPlayerName)
	ON_EN_CHANGE(IDC_ER1B, OnChangeER1B)
	ON_EN_CHANGE(IDC_ER2B, OnChangeER2B)
	ON_EN_CHANGE(IDC_ER3B, OnChangeER3B)
	ON_EN_CHANGE(IDC_ERC, OnChangeERC)
	ON_EN_CHANGE(IDC_ERCF, OnChangeERCF)
	ON_EN_CHANGE(IDC_ERLF, OnChangeERLF)
	ON_EN_CHANGE(IDC_ERP, OnChangeERP)
	ON_EN_CHANGE(IDC_ERRF, OnChangeERRF)
	ON_EN_CHANGE(IDC_ERSS, OnChangeERSS)
	ON_EN_CHANGE(IDC_FIRSTBASE, OnChangeFirstbase)
	ON_EN_CHANGE(IDC_LEFTFIELD, OnChangeLeftfield)
	ON_EN_CHANGE(IDC_PITCHER, OnChangePitcher)
	ON_EN_CHANGE(IDC_RIGHTFIELD, OnChangeRightfield)
	ON_EN_CHANGE(IDC_SECONDBASE, OnChangeSecondbase)
	ON_EN_CHANGE(IDC_SHORTSTOP, OnChangeShortstop)
	ON_BN_CLICKED(IDNEW, OnNew)
	ON_BN_CLICKED(IDPLAYERADD1, OnPlayerAdd)
	ON_BN_CLICKED(IDPLAYERUPDATE1, OnPlayerUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertyPageBatters message handlers

void PropertyPageBatters::OnOK() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP2); // OK Button Pressed

	m_bChangedFlag = FALSE;
	CPropertyPage::OnOK();
}

void PropertyPageBatters::OnCancel() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP3); // Cancel Button Pressed
	
	m_bChangedFlag = FALSE;
	CPropertyPage::OnCancel();
}

void PropertyPageBatters::OnNew() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->OnNew();

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(TRUE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(FALSE);

	m_bChangedFlag = FALSE;
}

void PropertyPageBatters::OnPlayerAdd() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP1); // Update Button Pressed

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);
	
	m_bChangedFlag = FALSE;
}

void PropertyPageBatters::OnPlayerUpdate() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP1); // Update Button Pressed
	
	m_bChangedFlag = FALSE;
}

void PropertyPageBatters::OnChangeCatcher() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeCenterfield() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnEditchangeComboPlayerName() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->SetPlayerNameCB(1);
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeER1B() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeER2B() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeER3B() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeERC() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeERCF() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeERLF() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeERP() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeERRF() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeERSS() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeFirstbase() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeLeftfield() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangePitcher() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeRightfield() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeSecondbase() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBatters::OnChangeShortstop() 
{
	m_bChangedFlag = TRUE;
}

BOOL PropertyPageBatters::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_spinPitcher.SetRange(0, 8);
	m_spinCatcher.SetRange(0, 5);
	m_spinFirstBase.SetRange(0, 5);
	m_spinSecondBase.SetRange(0, 5);
	m_spinShortStop.SetRange(0, 5);
	m_spinThirdBase.SetRange(0, 5);
	m_spinLeftField.SetRange(0, 5);
	m_spinCenterField.SetRange(0, 5);
	m_spinRightField.SetRange(0, 5);
	m_spinERP.SetRange(0, 51);
	m_spinERC.SetRange(0, 16);
	m_spinER1B.SetRange(0, 30);
	m_spinER2B.SetRange(0, 71);
	m_spinER3B.SetRange(0, 65);
	m_spinERSS.SetRange(0, 88);
	m_spinERLF.SetRange(0, 25);
	m_spinERCF.SetRange(0, 25);
	m_spinERRF.SetRange(0, 25);

	m_spinPitcher.SetBuddy( &m_ceditPitcher );
	m_spinCatcher.SetBuddy( &m_ceditCatcher );
	m_spinFirstBase.SetBuddy( &m_ceditFirstBase );
	m_spinSecondBase.SetBuddy( &m_ceditSecondBase );
	m_spinShortStop.SetBuddy( &m_ceditShortStop );
	m_spinThirdBase.SetBuddy( &m_ceditThirdBase );
	m_spinLeftField.SetBuddy( &m_ceditLeftField );
	m_spinCenterField.SetBuddy( &m_ceditCenterField );
	m_spinRightField.SetBuddy( &m_ceditRightField );
	m_spinERP.SetBuddy( &m_ceditERP );
	m_spinERC.SetBuddy( &m_ceditERC );
	m_spinER1B.SetBuddy( &m_ceditER1B );
	m_spinER2B.SetBuddy( &m_ceditER2B );
	m_spinERSS.SetBuddy( &m_ceditERSS );
	m_spinER3B.SetBuddy( &m_ceditER3B );
	m_spinERLF.SetBuddy( &m_ceditERLF );
	m_spinERCF.SetBuddy( &m_ceditERCF );
	m_spinERRF.SetBuddy( &m_ceditERRF );

	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	SetDlgItemText( IDC_TEAM0, pDoc->m_pPropertySheetBatters->m_TeamName );

	OnInitDialogPublic();

	// Build combo table for player display
	BuildPlayerNameComboBox();

	// Enable / Disable Update and Add buttons
	if (pDoc->m_pPropertySheetBatters->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PropertyPageBatters::BuildPlayerNameComboBox()
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->BuildPlayerNameComboBox(1);
	if (pDoc->m_pPropertySheetBatters->m_rgetcursel != -1)
		pDoc->m_pPropertySheetBatters->OnCloseupComboPlayerName(6);
}

void PropertyPageBatters::OnCloseupComboPlayerName() 
{
	// TODO: Add your control notification handler code here
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->OnCloseupComboPlayerName(1);

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);
}

void PropertyPageBatters::OnInitDialogPublic()
{
	SetDlgItemInt( IDC_PITCHER, 0, FALSE );
	SetDlgItemInt( IDC_CATCHER, 0, FALSE );
	SetDlgItemInt( IDC_FIRSTBASE, 0, FALSE );
	SetDlgItemInt( IDC_SECONDBASE, 0, FALSE );
	SetDlgItemInt( IDC_SHORTSTOP, 0, FALSE );
	SetDlgItemInt( IDC_THIRDBASE, 0, FALSE );
	SetDlgItemInt( IDC_LEFTFIELD, 0, FALSE );
	SetDlgItemInt( IDC_CENTERFIELD, 0, FALSE );
	SetDlgItemInt( IDC_RIGHTFIELD, 0, FALSE );
	SetDlgItemInt( IDC_ERP, 0, FALSE );
	SetDlgItemInt( IDC_ERC, 0, FALSE );
	SetDlgItemInt( IDC_ER1B, 0, FALSE );
	SetDlgItemInt( IDC_ER2B, 0, FALSE );
	SetDlgItemInt( IDC_ERSS, 0, FALSE );
	SetDlgItemInt( IDC_ER3B, 0, FALSE );
	SetDlgItemInt( IDC_ERLF, 0, FALSE );
	SetDlgItemInt( IDC_ERCF, 0, FALSE );
	SetDlgItemInt( IDC_ERRF, 0, FALSE );
	SetDlgItemText( IDC_COMBO_PLAYERNAME1, NULL );
}

BOOL PropertyPageBatters::OnSetActive() 
{
	// Enable / Disable Update and Add buttons
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	if (pDoc->m_pPropertySheetBatters->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}
	
	return CPropertyPage::OnSetActive();
}

/////////////////////////////////////////////////////////////////////////////
// PropertyPageBattersStats property page

IMPLEMENT_DYNCREATE(PropertyPageBattersStats, CPropertyPage)

PropertyPageBattersStats::PropertyPageBattersStats() : CPropertyPage(PropertyPageBattersStats::IDD)
{
	//{{AFX_DATA_INIT(PropertyPageBattersStats)
	m_TeamName = _T("");
	//}}AFX_DATA_INIT
	
	// Get pointer to Doc
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window.
	CBaseballView *pView = (CBaseballView *) pChild->GetActiveView();
	m_pDocVoid = pView->GetDocument();

	m_bChangedFlag = FALSE;
}

PropertyPageBattersStats::~PropertyPageBattersStats()
{
}

void PropertyPageBattersStats::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropertyPageBattersStats)
	DDX_Control(pDX, IDC_SLG, m_ceditSLG);
	DDX_Control(pDX, IDC_ONBASEPERCENT, m_ceditOnBasePercent);
	DDX_Control(pDX, IDC_BATTINGAVERAGE, m_ceditBattingAverage);
	DDX_Control(pDX, IDC_STRIKEOUT1, m_ceditK);
	DDX_Control(pDX, IDC_STOLENBASE1, m_ceditSB);
	DDX_Control(pDX, IDC_SPIN_WALK1, m_spinW);
	DDX_Control(pDX, IDC_SPIN_STRIKOUT1, m_spinK);
	DDX_Control(pDX, IDC_SPIN_STOLENBASE1, m_spinSB);
	DDX_Control(pDX, IDC_SPIN_SACRICIFE1, m_spinSACRICIFE);
	DDX_Control(pDX, IDC_SPIN_RUNS1, m_spinRUNS);
	DDX_Control(pDX, IDC_SPIN_REACHEDONERROR1, m_spinRE);
	DDX_Control(pDX, IDC_SPIN_RBI1, m_spinRBI);
	DDX_Control(pDX, IDC_SPIN_HR1, m_spinHR);
	DDX_Control(pDX, IDC_SPIN_HITS1, m_spinHITS);
	DDX_Control(pDX, IDC_SPIN_HBP1, m_spinHBP);
	DDX_Control(pDX, IDC_SPIN_GAMES2, m_spinGAMES);
	DDX_Control(pDX, IDC_SPIN_CS1, m_spinCS);
	DDX_Control(pDX, IDC_SPIN_AB1, m_spinAB);
	DDX_Control(pDX, IDC_SPIN_3B1, m_spin3B);
	DDX_Control(pDX, IDC_SPIN_2B1, m_spin2B);
	DDX_Control(pDX, IDC_WALK1, m_ceditWALK);
	DDX_Control(pDX, IDC_SACRICIFE1, m_ceditSACRICIFE);
	DDX_Control(pDX, IDC_RUNS1, m_ceditRUNS);
	DDX_Control(pDX, IDC_REACHEDONERROR1, m_ceditROE);
	DDX_Control(pDX, IDC_RBI1, m_ceditRBI);
	DDX_Control(pDX, IDC_HR1, m_ceditHR);
	DDX_Control(pDX, IDC_HITS1, m_ceditHITS);
	DDX_Control(pDX, IDC_HBP1, m_ceditHBP);
	DDX_Control(pDX, IDC_GAMES2, m_ceditGames);
	DDX_Control(pDX, IDC_CS1, m_ceditCS);
	DDX_Control(pDX, IDC_AB1, m_ceditAB);
	DDX_Control(pDX, IDC_3B1, m_cedit3B);
	DDX_Control(pDX, IDC_2B1, m_cedit2B);
	DDX_Control(pDX, IDC_COMBO_PLAYERNAME1, m_comboPlayerName);
	DDX_Text(pDX, IDC_TEAM0, m_TeamName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PropertyPageBattersStats, CPropertyPage)
	//{{AFX_MSG_MAP(PropertyPageBattersStats)
	ON_CBN_CLOSEUP(IDC_COMBO_PLAYERNAME1, OnCloseupComboPlayerName)
	ON_EN_CHANGE(IDC_BATTINGAVERAGE, OnChangeBattingaverage)
	ON_EN_CHANGE(IDC_2B1, OnChange2B)
	ON_EN_CHANGE(IDC_3B1, OnChange3B)
	ON_EN_CHANGE(IDC_AB1, OnChangeAB)
	ON_CBN_EDITCHANGE(IDC_COMBO_PLAYERNAME1, OnEditchangeComboPlayerName)
	ON_EN_CHANGE(IDC_CS1, OnChangeCS)
	ON_EN_CHANGE(IDC_GAMES2, OnChangeGames)
	ON_EN_CHANGE(IDC_HBP1, OnChangeHBP)
	ON_EN_CHANGE(IDC_HITS1, OnChangeHits)
	ON_EN_CHANGE(IDC_HR1, OnChangeHR)
	ON_EN_CHANGE(IDC_ONBASEPERCENT, OnChangeOnBasePercent)
	ON_EN_CHANGE(IDC_RBI1, OnChangeRBI)
	ON_EN_CHANGE(IDC_REACHEDONERROR1, OnChangeReachedOnError)
	ON_EN_CHANGE(IDC_RUNS1, OnChangeRuns)
	ON_EN_CHANGE(IDC_SACRICIFE1, OnChangeSacricife)
	ON_EN_CHANGE(IDC_SLG, OnChangeSLG)
	ON_EN_CHANGE(IDC_STOLENBASE1, OnChangeStolenbase)
	ON_EN_CHANGE(IDC_STRIKEOUT1, OnChangeStrikeout)
	ON_EN_CHANGE(IDC_WALK1, OnChangeWalk)
	ON_BN_CLICKED(IDPLAYERUPDATE1, OnPlayerUpdate)
	ON_BN_CLICKED(IDPLAYERADD1, OnPlayerAdd)
	ON_BN_CLICKED(IDNEW, OnNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertyPageBattersStats message handlers

void PropertyPageBattersStats::OnPlayerUpdate() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP1); // Update Button Pressed
	
	m_bChangedFlag = FALSE;
}

void PropertyPageBattersStats::OnPlayerAdd() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP1); // Update Button Pressed

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);
	
	m_bChangedFlag = FALSE;
}

void PropertyPageBattersStats::OnNew() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->OnNew();

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(TRUE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(FALSE);

	m_bChangedFlag = FALSE;
}

void PropertyPageBattersStats::OnOK() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP2); // OK Button Pressed
	
	m_bChangedFlag = FALSE;
	CPropertyPage::OnOK();
}

void PropertyPageBattersStats::OnCancel() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP3); // Cancel Button Pressed
	
	m_bChangedFlag = FALSE;
	CPropertyPage::OnCancel();
}

BOOL PropertyPageBattersStats::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_spin2B.SetRange(0, 1000);
	m_spin3B.SetRange(0, 1000);
	m_spinHR.SetRange(0, 1000);
	m_spinAB.SetRange(0, 1000);
	m_spinHITS.SetRange(0, 1000);
	m_spinRBI.SetRange(0, 500);
	m_spinRE.SetRange(0, 100);
	m_spinRUNS.SetRange(0, 1000);
	m_spinSACRICIFE.SetRange(0, 100);
	m_spinSB.SetRange(0, 100);
	m_spinK.SetRange(0, 300);
	m_spinW.SetRange(0, 300);
	m_spinHBP.SetRange(0, 300);
	m_spinGAMES.SetRange(0, 500);
	m_spinCS.SetRange(0, 300);

	m_spin2B.SetBuddy( &m_cedit2B );
	m_spin3B.SetBuddy( &m_cedit3B );
	m_spinHR.SetBuddy( &m_ceditHR );
	m_spinAB.SetBuddy( &m_ceditAB );
	m_spinHITS.SetBuddy( &m_ceditHITS );
	m_spinRBI.SetBuddy( &m_ceditRBI );
	m_spinRE.SetBuddy( &m_ceditROE );
	m_spinRUNS.SetBuddy( &m_ceditRUNS );
	m_spinSACRICIFE.SetBuddy( &m_ceditSACRICIFE );
	m_spinSB.SetBuddy( &m_ceditSB );
	m_spinK.SetBuddy( &m_ceditK );
	m_spinW.SetBuddy( &m_ceditWALK );
	m_spinCS.SetBuddy( &m_ceditCS );
	m_spinHBP.SetBuddy( &m_ceditHBP );
	m_spinGAMES.SetBuddy( &m_ceditGames);

	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	SetDlgItemText( IDC_TEAM0, pDoc->m_pPropertySheetBatters->m_TeamName );
	
	OnInitDialogPublic();

	// Build combo table for player display
	BuildPlayerNameComboBox();

	// Enable / Disable Update and Add buttons
	if (pDoc->m_pPropertySheetBatters->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PropertyPageBattersStats::BuildPlayerNameComboBox()
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->BuildPlayerNameComboBox(3);
	if (pDoc->m_pPropertySheetBatters->m_rgetcursel != -1)
		pDoc->m_pPropertySheetBatters->OnCloseupComboPlayerName(6);
}

void PropertyPageBattersStats::OnCloseupComboPlayerName() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->OnCloseupComboPlayerName(3);

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);

	m_bChangedFlag = FALSE;
}

void PropertyPageBattersStats::OnChangeBattingaverage() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChange2B() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChange3B() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeAB() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnEditchangeComboPlayerName() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->SetPlayerNameCB(3);
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeCS() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeGames() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeHBP() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeHits() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeHR() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeOnBasePercent() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeRBI() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeReachedOnError() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeRuns() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeSacricife() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeSLG() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeStolenbase() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeStrikeout() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnChangeWalk() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersStats::OnInitDialogPublic()
{
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
	SetDlgItemText( IDC_BATTINGAVERAGE, NULL );
	SetDlgItemText( IDC_SLG, NULL );
	SetDlgItemText( IDC_ONBASEPERCENT, NULL );
	SetDlgItemInt( IDC_CS1, 0, FALSE );
	SetDlgItemInt( IDC_HBP1, 0, FALSE );
	SetDlgItemInt( IDC_GAMES2, 0, FALSE );
}

BOOL PropertyPageBattersStats::OnSetActive() 
{
	// Enable / Disable Update and Add buttons
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	if (pDoc->m_pPropertySheetBatters->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}
	
	return CPropertyPage::OnSetActive();
}

/////////////////////////////////////////////////////////////////////////////
// PropertyPageBattersChance property page

IMPLEMENT_DYNCREATE(PropertyPageBattersChance, CPropertyPage)

PropertyPageBattersChance::PropertyPageBattersChance() : CPropertyPage(PropertyPageBattersChance::IDD)
{
	//{{AFX_DATA_INIT(PropertyPageBattersChance)
	m_TeamName = _T("");
	//}}AFX_DATA_INIT
	// Get pointer to Doc
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window.
	CBaseballView *pView = (CBaseballView *) pChild->GetActiveView();
	m_pDocVoid = pView->GetDocument();

	m_bChangedFlag = FALSE;
}

PropertyPageBattersChance::~PropertyPageBattersChance()
{
}

void PropertyPageBattersChance::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropertyPageBattersChance)
	DDX_Control(pDX, IDC_CHANCEWALKR, m_ceditWalkRight);
	DDX_Control(pDX, IDC_CHANCEWALKL, m_ceditWalkLeft);
	DDX_Control(pDX, IDC_CHANCETRIPLER, m_ceditTripleRight);
	DDX_Control(pDX, IDC_CHANCETRIPLEL, m_ceditTripleLeft);
	DDX_Control(pDX, IDC_CHANCESINGLER, m_ceditSingleRight);
	DDX_Control(pDX, IDC_CHANCESINGLEL, m_ceditSingleLeft);
	DDX_Control(pDX, IDC_CHANCEHRR, m_ceditHRRight);
	DDX_Control(pDX, IDC_CHANCEHRL, m_ceditHRLeft);
	DDX_Control(pDX, IDC_CHANCEDOUBLER, m_ceditDoubleRight);
	DDX_Control(pDX, IDC_CHANCEDOUBLEPLAYL, m_ceditDoublePlayLeft);
	DDX_Control(pDX, IDC_CHANCEDOUBLEPLAYR, m_ceditDoublePlayRight);
	DDX_Control(pDX, IDC_CHANCEDOUBLEL, m_cdeitDoubleLeft);
	DDX_Control(pDX, IDC_CHANCEDOUBLEPLAY, m_ceditDoublePlay);
	DDX_Control(pDX, IDC_CHANCEWALK, m_ceditWalk);
	DDX_Control(pDX, IDC_CHANCETRIPLE, m_ceditTriple);
	DDX_Control(pDX, IDC_CHANCESINGLE, m_ceditSingle);
	DDX_Control(pDX, IDC_CHANCEHR, m_ceditHR);
	DDX_Control(pDX, IDC_CHANCEDOUBLE, m_ceditDouble);
	DDX_Control(pDX, IDC_CHANCEBASIC, m_ceditBasic);
	DDX_Control(pDX, IDC_CHANCELEFT, m_ceditLeft);
	DDX_Control(pDX, IDC_CHANCERIGHT, m_ceditRight);
	DDX_Control(pDX, IDC_COMBO_PLAYERNAME1, m_comboPlayerName);
	DDX_Text(pDX, IDC_TEAM0, m_TeamName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PropertyPageBattersChance, CPropertyPage)
	//{{AFX_MSG_MAP(PropertyPageBattersChance)
	ON_CBN_CLOSEUP(IDC_COMBO_PLAYERNAME1, OnCloseupComboPlayerName)
	ON_BN_CLICKED(IDPLAYERUPDATE1, OnPlayerUpdate)
	ON_BN_CLICKED(IDNEW, OnNew)
	ON_EN_CHANGE(IDC_CHANCEBASIC, OnChangeChanceBasic)
	ON_EN_CHANGE(IDC_CHANCELEFT, OnChangeChanceLeft)
	ON_EN_CHANGE(IDC_CHANCERIGHT, OnChangeChanceRight)
	ON_EN_CHANGE(IDC_CHANCEDOUBLE, OnChangeChanceDouble)
	ON_EN_CHANGE(IDC_CHANCEHR, OnChangeChanceHR)
	ON_EN_CHANGE(IDC_CHANCESINGLE, OnChangeChanceSingle)
	ON_EN_CHANGE(IDC_CHANCETRIPLE, OnChangeChanceTriple)
	ON_EN_CHANGE(IDC_CHANCEWALK, OnChangeChanceWalk)
	ON_EN_CHANGE(IDC_CHANCEDOUBLEPLAY, OnChangeChanceDoublePlay)
	ON_CBN_EDITCHANGE(IDC_COMBO_PLAYERNAME1, OnEditChangeComboPlayerName)
	ON_BN_CLICKED(IDPLAYERADD1, OnPlayerAdd)
	ON_EN_CHANGE(IDC_CHANCEDOUBLEL, OnChangeChanceDoubleLeft)
	ON_EN_CHANGE(IDC_CHANCEDOUBLER, OnChangeChanceDoubleRight)
	ON_EN_CHANGE(IDC_CHANCEDOUBLEPLAYL, OnChangeChanceDoublePlayLeft)
	ON_EN_CHANGE(IDC_CHANCEDOUBLEPLAYR, OnChangeChanceDoublePlayRight)
	ON_EN_CHANGE(IDC_CHANCEHRL, OnChangeChanceHRLeft)
	ON_EN_CHANGE(IDC_CHANCEHRR, OnChangeChanceHRRight)
	ON_EN_CHANGE(IDC_CHANCESINGLEL, OnChangeChanceSingleLeft)
	ON_EN_CHANGE(IDC_CHANCESINGLER, OnChangeChanceSingleRight)
	ON_EN_CHANGE(IDC_CHANCETRIPLEL, OnChangeChanceTripleLeft)
	ON_EN_CHANGE(IDC_CHANCETRIPLER, OnChangeChanceTripleRight)
	ON_EN_CHANGE(IDC_CHANCEWALKL, OnChangeChanceWalkLeft)
	ON_EN_CHANGE(IDC_CHANCEWALKR, OnChangeChanceWalkRight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertyPageBattersChance message handlers

BOOL PropertyPageBattersChance::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	SetDlgItemText( IDC_TEAM0, pDoc->m_pPropertySheetBatters->m_TeamName );

	OnInitDialogPublic();

	// Build combo table for player display
	BuildPlayerNameComboBox();

	// Enable / Disable Update and Add buttons
	if (pDoc->m_pPropertySheetBatters->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PropertyPageBattersChance::BuildPlayerNameComboBox()
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->BuildPlayerNameComboBox(2);
	if (pDoc->m_pPropertySheetBatters->m_rgetcursel != -1)
		pDoc->m_pPropertySheetBatters->OnCloseupComboPlayerName(6);
}

void PropertyPageBattersChance::OnCloseupComboPlayerName() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->OnCloseupComboPlayerName(2);

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);

	m_bChangedFlag = FALSE;
}

void PropertyPageBattersChance::OnCancel() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP3); // Cancel Button Pressed
	
	m_bChangedFlag = FALSE;
	CPropertyPage::OnCancel();
}

void PropertyPageBattersChance::OnOK() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP2); // OK Button Pressed
	
	m_bChangedFlag = FALSE;
	CPropertyPage::OnOK();
}

void PropertyPageBattersChance::OnPlayerAdd() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP1); // Update Button Pressed

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);
	
	m_bChangedFlag = FALSE;
}

void PropertyPageBattersChance::OnPlayerUpdate() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP1); // Update Button Pressed
	
	m_bChangedFlag = FALSE;
}

void PropertyPageBattersChance::OnInitDialogPublic()
{
	SetDlgItemText( IDC_COMBO_PLAYERNAME1, NULL );
	SetDlgItemText( IDC_CHANCEBASIC, "0" );
	SetDlgItemText( IDC_CHANCELEFT, "0" );
	SetDlgItemText( IDC_CHANCERIGHT, "0" );
	SetDlgItemText( IDC_CHANCEWALK, "0" );
	SetDlgItemText( IDC_CHANCETRIPLE, "0" );
	SetDlgItemText( IDC_CHANCESINGLE, "0" );
	SetDlgItemText( IDC_CHANCEHR, "0" );
	SetDlgItemText( IDC_CHANCEDOUBLE, "0" );
	SetDlgItemText( IDC_CHANCEDOUBLEPLAY, "0" );
	SetDlgItemText( IDC_CHANCEWALKL, "0" );
	SetDlgItemText( IDC_CHANCETRIPLEL, "0" );
	SetDlgItemText( IDC_CHANCESINGLEL, "0" );
	SetDlgItemText( IDC_CHANCEHRL, "0" );
	SetDlgItemText( IDC_CHANCEDOUBLEL, "0" );
	SetDlgItemText( IDC_CHANCEDOUBLEPLAYL, "0" );
	SetDlgItemText( IDC_CHANCEWALKR, "0" );
	SetDlgItemText( IDC_CHANCETRIPLER, "0" );
	SetDlgItemText( IDC_CHANCESINGLER, "0" );
	SetDlgItemText( IDC_CHANCEHRR, "0" );
	SetDlgItemText( IDC_CHANCEDOUBLER, "0" );
	SetDlgItemText( IDC_CHANCEDOUBLEPLAYR, "0" );
}

void PropertyPageBattersChance::OnNew() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->OnNew();

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(TRUE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(FALSE);

	m_bChangedFlag = FALSE;
}

void PropertyPageBattersChance::OnChangeChanceBasic() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceDouble() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceDoubleLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceDoubleRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceHR() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceHRLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceHRRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceSingle() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceSingleLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceSingleRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceTriple() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceTripleLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceTripleRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceWalk() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceWalkLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceWalkRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceDoublePlay() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceDoublePlayLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnChangeChanceDoublePlayRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersChance::OnEditChangeComboPlayerName() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->SetPlayerNameCB(2);
	m_bChangedFlag = TRUE;
}

BOOL PropertyPageBattersChance::OnSetActive() 
{
	// Enable / Disable Update and Add buttons
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	if (pDoc->m_pPropertySheetBatters->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}
	
	return CPropertyPage::OnSetActive();
}

/////////////////////////////////////////////////////////////////////////////
// PropertySheetBatters

IMPLEMENT_DYNAMIC(PropertySheetBatters, CPropertySheet)

PropertySheetBatters::PropertySheetBatters(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_rgetcursel = -1;
	m_newFlag = FALSE;
}

PropertySheetBatters::PropertySheetBatters(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_rgetcursel = -1;
	m_newFlag = FALSE;
}

PropertySheetBatters::~PropertySheetBatters()
{
}


BEGIN_MESSAGE_MAP(PropertySheetBatters, CPropertySheet)
	//{{AFX_MSG_MAP(PropertySheetBatters)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_APP1,OnUpdate)
	ON_MESSAGE(WM_APP2,OnOK)
	ON_MESSAGE(WM_APP3,OnCancel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertySheetBatters message handlers

BOOL PropertySheetBatters::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here

	RECT rcWnd;
	RECT rcOK;

	// Get size info on OK button and then hide the button
	CWnd* pOKWnd = GetDlgItem(IDOK);
	ASSERT (pOKWnd);
	pOKWnd->GetWindowRect(&rcOK);
	pOKWnd->ShowWindow(SW_HIDE);

	// Hide the Cancel button
	CWnd* pCancelWnd = GetDlgItem(IDCANCEL);
	ASSERT (pCancelWnd);
	pCancelWnd->ShowWindow(SW_HIDE);

	// Hide the Help button
	CWnd* pHelpWnd = GetDlgItem(IDHELP);
	ASSERT (pHelpWnd);
	pHelpWnd->ShowWindow(SW_HIDE);

	// Resize the window to remove the buttons
	GetWindowRect(&rcWnd);
	rcWnd.bottom -= (rcOK.bottom-rcOK.top+6); // 6 = spacing
 	MoveWindow (rcWnd.left, rcWnd.top, 
		rcWnd.right-rcWnd.left, rcWnd.bottom-rcWnd.top);
	
	// Now center the dialog based on the desktop
	CenterWindow(GetDesktopWindow());

	m_rgetcursel = -1;

	return TRUE;
}

void PropertySheetBatters::OnNew()
{
	if (m_pPage1->m_hWnd != 0)
	{
		m_pPage1->OnInitDialogPublic();
	}
	if (m_pPage2->m_hWnd != 0)
	{
		m_pPage2->OnInitDialogPublic();
	}
	if (m_pPage3->m_hWnd != 0)
	{
		m_pPage3->OnInitDialogPublic();
	}
	if (m_pPage4->m_hWnd != 0)
	{
		m_pPage4->OnInitDialogPublic();
	}
	OnNewInitStruct();
	m_flagNew = TRUE;
	m_rgetcursel = -1;
}

void PropertySheetBatters::OnNewInitStruct()
{
	CString filler10("          ");

	m_structBatter.m_PlayerName		= filler10+filler10+filler10+filler10+filler10;
	m_structBatter.m_Pitcher		= 0;
	m_structBatter.m_Catcher		= 0;
	m_structBatter.m_FirstBase		= 0;
	m_structBatter.m_SecondBase		= 0;
	m_structBatter.m_ShortStop		= 0;
	m_structBatter.m_ThirdBase		= 0;
	m_structBatter.m_LeftField		= 0;
	m_structBatter.m_CenterField	= 0;
	m_structBatter.m_RightField		= 0;
	m_structBatter.m_bER1		= 0;
	m_structBatter.m_bER2		= 0;
	m_structBatter.m_bER3		= 0;
	m_structBatter.m_bER4		= 0;
	m_structBatter.m_bER5		= 0;
	m_structBatter.m_bER6		= 0;
	m_structBatter.m_bER7		= 0;
	m_structBatter.m_bER8		= 0;
	m_structBatter.m_bER9		= 0;
	m_structBatter.m_OBChanceBasic		= "0"+filler10;
	m_structBatter.m_OBChanceLeft		= "0"+filler10;
	m_structBatter.m_OBChanceRight		= "0"+filler10;
	m_structBatter.m_OBChanceHomeRun	= "0"+filler10;
	m_structBatter.m_OBChanceDouble		= "0"+filler10;
	m_structBatter.m_OBChanceSingle		= "0"+filler10;
	m_structBatter.m_OBChanceTriple		= "0"+filler10;
	m_structBatter.m_OBChanceWalk		= "0"+filler10;
	m_structBatter.m_ChanceDoublePlay	= "0"+filler10;
	m_structBatter.m_OBChanceHomeRunLeft	= "0"+filler10;
	m_structBatter.m_OBChanceDoubleLeft		= "0"+filler10;
	m_structBatter.m_OBChanceSingleLeft		= "0"+filler10;
	m_structBatter.m_OBChanceTripleLeft		= "0"+filler10;
	m_structBatter.m_OBChanceWalkLeft		= "0"+filler10;
	m_structBatter.m_ChanceDoublePlayLeft	= "0"+filler10;
	m_structBatter.m_OBChanceHomeRunRight	= "0"+filler10;
	m_structBatter.m_OBChanceDoubleRight	= "0"+filler10;
	m_structBatter.m_OBChanceSingleRight	= "0"+filler10;
	m_structBatter.m_OBChanceTripleRight	= "0"+filler10;
	m_structBatter.m_OBChanceWalkRight		= "0"+filler10;
	m_structBatter.m_ChanceDoublePlayRight	= "0"+filler10;
	m_structBatter.m_AB				= 0;
	m_structBatter.m_Runs			= 0;
	m_structBatter.m_Hits			= 0;
	m_structBatter.m_RBI			= 0;
	m_structBatter.m_2B				= 0;
	m_structBatter.m_3B				= 0;
	m_structBatter.m_HomeRuns		= 0;
	m_structBatter.m_Walk			= 0;
	m_structBatter.m_StrikeOut		= 0;
	m_structBatter.m_ReachedOnError	= 0;
	m_structBatter.m_Sacrifice		= 0;
	m_structBatter.m_StolenBase		= 0;
	m_structBatter.m_CS				= 0;
	m_structBatter.m_HBP			= 0;
	m_structBatter.m_Games			= 0;
	m_structBatter.m_bBunting		= 0;
	m_structBatter.m_bStealing		= 0;
	m_structBatter.m_bRunning		= 0;
	m_structBatter.m_bHitRun		= 0;
	m_structBatter.m_bBatterHits	= 0;
	m_structBatter.m_bCatchArm		= 0;
	m_structBatter.m_bOutArm		= 0;
	m_structBatter.m_bPass			= 0;
	m_structBatter.m_bPowerL		= 0;
	m_structBatter.m_bPowerR		= 0;
	m_structBatter.m_bTRate			= 0;
}

// Handler for Button click od WM_APP1
LRESULT PropertySheetBatters::OnUpdate(WPARAM wParam,LPARAM lParam)
{
	BOOL rc_GetDlgItemInt;
	char cTemp[31];
	CString filler10("          ");
	char buf[10];
	if (m_pPage1->m_hWnd != 0)
	{
		m_pPage1->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		cTemp[30]		= NULL;
		m_structBatter.m_PlayerName		= cTemp+filler10+filler10+filler10+filler10;
		m_structBatter.m_Pitcher		= m_pPage1->GetDlgItemInt( IDC_PITCHER, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_Catcher		= m_pPage1->GetDlgItemInt( IDC_CATCHER, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_FirstBase		= m_pPage1->GetDlgItemInt( IDC_FIRSTBASE, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_SecondBase		= m_pPage1->GetDlgItemInt( IDC_SECONDBASE, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_ShortStop		= m_pPage1->GetDlgItemInt( IDC_SHORTSTOP, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_ThirdBase		= m_pPage1->GetDlgItemInt( IDC_THIRDBASE, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_LeftField		= m_pPage1->GetDlgItemInt( IDC_LEFTFIELD, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_CenterField	= m_pPage1->GetDlgItemInt( IDC_CENTERFIELD, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_RightField		= m_pPage1->GetDlgItemInt( IDC_RIGHTFIELD, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_bER1		= m_pPage1->GetDlgItemInt( IDC_ERP, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_bER2		= m_pPage1->GetDlgItemInt( IDC_ERC, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_bER3		= m_pPage1->GetDlgItemInt( IDC_ER1B, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_bER4		= m_pPage1->GetDlgItemInt( IDC_ER2B, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_bER5		= m_pPage1->GetDlgItemInt( IDC_ER3B, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_bER6		= m_pPage1->GetDlgItemInt( IDC_ERSS, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_bER7		= m_pPage1->GetDlgItemInt( IDC_ERLF, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_bER8		= m_pPage1->GetDlgItemInt( IDC_ERCF, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_bER9		= m_pPage1->GetDlgItemInt( IDC_ERRF, &rc_GetDlgItemInt, FALSE );
		m_pPage1->m_bChangedFlag	= FALSE;
	}
	if (m_pPage2->m_hWnd != 0)
	{
		m_pPage2->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		cTemp[30]		= NULL;
		m_structBatter.m_PlayerName		= cTemp+filler10+filler10+filler10+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEBASIC, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceBasic		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCELEFT, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceLeft		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCERIGHT, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceRight		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEHR, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceHomeRun	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLE, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceDouble		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCESINGLE, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceSingle		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCETRIPLE, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceTriple		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEWALK, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceWalk		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEPLAY, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_ChanceDoublePlay	= cTemp+filler10;

		m_pPage2->GetDlgItemText( IDC_CHANCEHRR, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceHomeRunRight	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLER, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceDoubleRight		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCESINGLER, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceSingleRight		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCETRIPLER, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceTripleRight		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEWALKR, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceWalkRight		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEPLAYR, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_ChanceDoublePlayRight	= cTemp+filler10;

		m_pPage2->GetDlgItemText( IDC_CHANCEHRL, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceHomeRunLeft	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEL, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceDoubleLeft		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCESINGLEL, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceSingleLeft		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCETRIPLEL, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceTripleLeft		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEWALKL, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_OBChanceWalkLeft		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEPLAYL, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structBatter.m_ChanceDoublePlayLeft	= cTemp+filler10;

		m_pPage2->m_bChangedFlag		= FALSE;
	}
	if (m_pPage3->m_hWnd != 0)
	{
		m_pPage3->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		cTemp[30]		= NULL;
		m_structBatter.m_PlayerName		= cTemp+filler10+filler10+filler10+filler10;
		m_structBatter.m_AB				= m_pPage3->GetDlgItemInt( IDC_AB1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_Runs			= m_pPage3->GetDlgItemInt( IDC_RUNS1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_Hits			= m_pPage3->GetDlgItemInt( IDC_HITS1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_RBI			= m_pPage3->GetDlgItemInt( IDC_RBI1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_2B				= m_pPage3->GetDlgItemInt( IDC_2B1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_3B				= m_pPage3->GetDlgItemInt( IDC_3B1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_HomeRuns		= m_pPage3->GetDlgItemInt( IDC_HR1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_Walk			= m_pPage3->GetDlgItemInt( IDC_WALK1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_StrikeOut		= m_pPage3->GetDlgItemInt( IDC_STRIKEOUT1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_ReachedOnError	= m_pPage3->GetDlgItemInt( IDC_REACHEDONERROR1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_Sacrifice		= m_pPage3->GetDlgItemInt( IDC_SACRICIFE1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_StolenBase		= m_pPage3->GetDlgItemInt( IDC_STOLENBASE1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_CS				= m_pPage3->GetDlgItemInt( IDC_CS1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_HBP			= m_pPage3->GetDlgItemInt( IDC_HBP1, &rc_GetDlgItemInt, FALSE );
		m_structBatter.m_Games			= m_pPage3->GetDlgItemInt( IDC_GAMES2, &rc_GetDlgItemInt, FALSE );
		m_pPage3->m_bChangedFlag		= FALSE;
	}
	if (m_pPage4->m_hWnd != 0)
	{
		m_pPage4->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		cTemp[30]		= NULL;
		m_structBatter.m_PlayerName		= cTemp+filler10+filler10+filler10+filler10;
		m_structBatter.m_bBunting		= m_pPage4->m_comboBunting.GetCurSel();
		m_structBatter.m_bStealing		= m_pPage4->m_comboStealing.GetCurSel();
		m_structBatter.m_bRunning		= m_pPage4->m_comboRunning.GetCurSel();
		m_structBatter.m_bHitRun		= m_pPage4->m_comboHitRun.GetCurSel();
		m_structBatter.m_bBatterHits	= m_pPage4->m_comboBatterHits.GetCurSel();
		m_structBatter.m_bCatchArm		= m_pPage4->m_comboCatcherArm.GetCurSel();
		m_structBatter.m_bOutArm		= m_pPage4->m_comboOutArm.GetCurSel();
		m_structBatter.m_bPass			= m_pPage4->m_comboPassBall.GetCurSel();
		m_structBatter.m_bPowerL		= m_pPage4->m_comboPowerLeft.GetCurSel();
		m_structBatter.m_bPowerR		= m_pPage4->m_comboPowerRight.GetCurSel();
		m_structBatter.m_bTRate			= m_pPage4->m_comboTRate.GetCurSel();
		m_pPage4->m_bChangedFlag		= FALSE;
	}

	// Open file and update player
	if (m_flagNew == TRUE)
	{
		m_structBatter.AddBatter(m_FileName);
		m_flagNew = FALSE;
	}
	else
	{
		if (m_lSeekPlayerFile!=0)
		{
			{
				m_structBatter.UpdateBatter(m_FileName,m_lSeekPlayerFile);
			}

			if (m_pPage3->m_hWnd != 0)
			{
				if (m_structBatter.m_AB == 0)
				{
					m_pPage3->SetDlgItemText( IDC_BATTINGAVERAGE, "0" );
					m_pPage3->SetDlgItemText( IDC_SLG, "0" );
					m_pPage3->SetDlgItemText( IDC_ONBASEPERCENT, "0" );
					m_pPage3->m_bChangedFlag		= FALSE;
				}
				else
				{
					m_fBattingAverage = (float)m_structBatter.m_Hits/m_structBatter.m_AB;
					sprintf_s(buf,"%1.3f",m_fBattingAverage);
					m_pPage3->SetDlgItemText( IDC_BATTINGAVERAGE, buf );
					m_fSLG = (float)((m_structBatter.m_Hits-(m_structBatter.m_2B+m_structBatter.m_3B+m_structBatter.m_HomeRuns))+(2*m_structBatter.m_2B)+(3*m_structBatter.m_3B)+(4*m_structBatter.m_HomeRuns))/(m_structBatter.m_AB);
					sprintf_s(buf,"%1.3f",m_fSLG);
					m_pPage3->SetDlgItemText( IDC_SLG, buf );
					m_fOnBasePercentage = (float)(m_structBatter.m_Hits+m_structBatter.m_Walk+m_structBatter.m_ReachedOnError+m_structBatter.m_Sacrifice)/(m_structBatter.m_AB+m_structBatter.m_Walk+m_structBatter.m_ReachedOnError+m_structBatter.m_Sacrifice);
					sprintf_s(buf,"%1.3f",m_fOnBasePercentage);
					m_pPage3->SetDlgItemText( IDC_ONBASEPERCENT, buf );
					m_pPage3->m_bChangedFlag		= FALSE;
				}
			}
		}
	}
	// ReBuild combo table for player display
	if (m_pPage1->m_hWnd != 0)
	{
		BuildPlayerNameComboBox(1);
	}
	if (m_pPage2->m_hWnd != 0)
	{
		BuildPlayerNameComboBox(2);
	}
	if (m_pPage3->m_hWnd != 0)
	{
		BuildPlayerNameComboBox(3);
	}
	if (m_pPage4->m_hWnd != 0)
	{
		BuildPlayerNameComboBox(4);
	}
	return (LRESULT)0;
}

LRESULT PropertySheetBatters::OnOK(WPARAM wParam,LPARAM lParam) 
{
//	AfxMessageBox("OnOK was Clicked!");
	EndDialog(IDOK);
	return (LRESULT)0;
}

LRESULT PropertySheetBatters::OnCancel(WPARAM wParam,LPARAM lParam) 
{
//	AfxMessageBox("OnCancel was Clicked!");
	EndDialog(IDCANCEL);
	return (LRESULT)0;
}

void PropertySheetBatters::BuildPlayerNameComboBox(int iPage)
{
	BYTE count;
	int i;
	LONG lTeamSection = 74;
	LONG lPlayerSection = m_structBatter.m_RecordSize;
	CString	strPlayerName;	// Length of 30


	// If needed save Player Name
	if (m_flagNew == TRUE)
		strPlayerName = m_structBatter.m_PlayerName;
	// Get count of players in file
	count = m_structBatter.GetCountBatter(m_FileName);
	// Open file and build player ComboBox
	switch (iPage)
	{
	case 1:
		m_pPage1->m_comboPlayerName.ResetContent();
		break;
	case 2:
		m_pPage2->m_comboPlayerName.ResetContent();
		break;
	case 3:
		m_pPage3->m_comboPlayerName.ResetContent();
		break;
	case 4:
		m_pPage4->m_comboPlayerName.ResetContent();
		break;
	}
	for (i=0; i<count; i++)
	{
		m_lSeekPlayerFile = lTeamSection+(i*lPlayerSection);
		m_structBatter.GetBatter(m_FileName ,m_lSeekPlayerFile);
		switch (iPage)
		{
		case 1:
			m_pPage1->m_comboPlayerName.AddString(m_structBatter.m_PlayerName);
			break;
		case 2:
			m_pPage2->m_comboPlayerName.AddString(m_structBatter.m_PlayerName);
			break;
		case 3:
			m_pPage3->m_comboPlayerName.AddString(m_structBatter.m_PlayerName);
			break;
		case 4:
			m_pPage4->m_comboPlayerName.AddString(m_structBatter.m_PlayerName);
			break;
		}
	}
	switch (iPage)
	{
	case 1:
		m_pPage1->m_bChangedFlag = FALSE;
		break;
	case 2:
		m_pPage2->m_bChangedFlag = FALSE;
		break;
	case 3:
		m_pPage3->m_bChangedFlag = FALSE;
		break;
	case 4:
		m_pPage4->m_bChangedFlag = FALSE;
		break;
	}
	m_lSeekPlayerFile = 0;

	if (m_flagNew == TRUE)
	{
		OnNewInitStruct();
		// put back player name cause it was wiped out in this routine
		m_structBatter.m_PlayerName = strPlayerName;
		switch (iPage)
		{
		case 1:
			m_pPage1->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structBatter.m_PlayerName );
			break;
		case 2:
			m_pPage2->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structBatter.m_PlayerName );
			break;
		case 3:
			m_pPage3->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structBatter.m_PlayerName );
			break;
		case 4:
			m_pPage4->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structBatter.m_PlayerName );
			break;
		}
	}
}

void PropertySheetBatters::OnCloseupComboPlayerName(int iPage)
{
	int i, rcompare;
	BYTE count;
	CString csPlayer;
	LONG lTeamSection = 74;
	LONG lPlayerSection = m_structBatter.m_RecordSize;
	char buf[10];
	int changed;
	int yesno;

	// Test for changed pages NOT SURE HOW TO HANDLE NEW PLAYERS
	changed = FALSE;
	if (m_pPage1->m_hWnd != 0)
		changed |= m_pPage1->m_bChangedFlag;
	if (m_pPage2->m_hWnd != 0)
		changed |= m_pPage2->m_bChangedFlag;
	if (m_pPage3->m_hWnd != 0)
		changed |= m_pPage3->m_bChangedFlag;
	if (m_pPage4->m_hWnd != 0)
		changed |= m_pPage4->m_bChangedFlag;
	if (changed == TRUE)
	{
		// Display a window asking to save changed data
		yesno = AfxMessageBox("Player information has changed, Do you want to save it?",
			MB_YESNO,0);
		switch (yesno)
		{
		case IDYES:
			SendMessage(WM_APP1);	// Update requested, wait for return from update
			break;
		case IDNO:
			break;
		}
		// Now reset the changed flags
		if (m_pPage1->m_hWnd != 0)
			m_pPage1->m_bChangedFlag = FALSE;
		if (m_pPage2->m_hWnd != 0)
			m_pPage2->m_bChangedFlag = FALSE;
		if (m_pPage3->m_hWnd != 0)
			m_pPage3->m_bChangedFlag = FALSE;
		if (m_pPage4->m_hWnd != 0)
			m_pPage4->m_bChangedFlag = FALSE;
	}

	switch (iPage)
	{
	case 1:
		m_rgetcursel = m_pPage1->m_comboPlayerName.GetCurSel();
		if ( m_rgetcursel != CB_ERR )
			m_pPage1->m_comboPlayerName.GetLBText( m_rgetcursel, m_rString );
		m_newFlag = FALSE;
		break;
	case 2:
		m_rgetcursel = m_pPage2->m_comboPlayerName.GetCurSel();
		if ( m_rgetcursel != CB_ERR )
			m_pPage2->m_comboPlayerName.GetLBText( m_rgetcursel, m_rString );
		m_newFlag = FALSE;
		break;
	case 3:
		m_rgetcursel = m_pPage3->m_comboPlayerName.GetCurSel();
		if ( m_rgetcursel != CB_ERR )
			m_pPage3->m_comboPlayerName.GetLBText( m_rgetcursel, m_rString );
		m_newFlag = FALSE;
		break;
	case 4:
		m_rgetcursel = m_pPage4->m_comboPlayerName.GetCurSel();
		if ( m_rgetcursel != CB_ERR )
			m_pPage4->m_comboPlayerName.GetLBText( m_rgetcursel, m_rString );
		m_newFlag = FALSE;
		break;
	default:	// If call other that 1 - 5, then just load variables
		break;
	}
	if (m_rgetcursel != CB_ERR)
	{
		count = m_structBatter.GetCountBatter(m_FileName);
		csPlayer.Empty();
		rcompare = m_rString.Compare(csPlayer);
		i = -1;
		while (rcompare)
		{
			i++;
			if (i >= count)
			{
				// Player compare failed so display message
				AfxMessageBox("Player Compare Failed");
				break;
			}
			// Read in the player Data
			m_lSeekPlayerFile = lTeamSection+(i*lPlayerSection);
			m_structBatter.GetBatter(m_FileName,m_lSeekPlayerFile);
			csPlayer = m_structBatter.m_PlayerName;
			rcompare = m_rString.Compare(csPlayer);
		}

		// Read in the player Data
		m_structBatter.GetBatter(m_FileName,m_lSeekPlayerFile);
		// Set the Dialog Items for page 1
		if ((m_pPage1->m_hWnd != 0) && (m_pPage1->m_bChangedFlag == FALSE))
		{
			m_pPage1->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage1->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structBatter.m_PlayerName );
			m_pPage1->SetDlgItemInt( IDC_PITCHER, m_structBatter.m_Pitcher, FALSE );
			m_pPage1->SetDlgItemInt( IDC_CATCHER, m_structBatter.m_Catcher, FALSE );
			m_pPage1->SetDlgItemInt( IDC_FIRSTBASE, m_structBatter.m_FirstBase, FALSE );
			m_pPage1->SetDlgItemInt( IDC_SECONDBASE, m_structBatter.m_SecondBase, FALSE );
			m_pPage1->SetDlgItemInt( IDC_SHORTSTOP, m_structBatter.m_ShortStop, FALSE );
			m_pPage1->SetDlgItemInt( IDC_THIRDBASE, m_structBatter.m_ThirdBase, FALSE );
			m_pPage1->SetDlgItemInt( IDC_LEFTFIELD, m_structBatter.m_LeftField, FALSE );
			m_pPage1->SetDlgItemInt( IDC_CENTERFIELD, m_structBatter.m_CenterField, FALSE );
			m_pPage1->SetDlgItemInt( IDC_RIGHTFIELD, m_structBatter.m_RightField, FALSE );
			m_pPage1->SetDlgItemInt( IDC_ERP, m_structBatter.m_bER1, FALSE );
			m_pPage1->SetDlgItemInt( IDC_ERC, m_structBatter.m_bER2, FALSE );
			m_pPage1->SetDlgItemInt( IDC_ER1B, m_structBatter.m_bER3, FALSE );
			m_pPage1->SetDlgItemInt( IDC_ER2B, m_structBatter.m_bER4, FALSE );
			m_pPage1->SetDlgItemInt( IDC_ER3B, m_structBatter.m_bER5, FALSE );
			m_pPage1->SetDlgItemInt( IDC_ERSS, m_structBatter.m_bER6, FALSE );
			m_pPage1->SetDlgItemInt( IDC_ERLF, m_structBatter.m_bER7, FALSE );
			m_pPage1->SetDlgItemInt( IDC_ERCF, m_structBatter.m_bER8, FALSE );
			m_pPage1->SetDlgItemInt( IDC_ERRF, m_structBatter.m_bER9, FALSE );
			m_pPage1->m_bChangedFlag = FALSE;
		}

		if ((m_pPage2->m_hWnd != 0) && (m_pPage2->m_bChangedFlag == FALSE))
		{
			m_pPage2->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage2->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structBatter.m_PlayerName );
			m_pPage2->SetDlgItemText( IDC_CHANCEBASIC, m_structBatter.m_OBChanceBasic );
			m_pPage2->SetDlgItemText( IDC_CHANCELEFT, m_structBatter.m_OBChanceLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCERIGHT, m_structBatter.m_OBChanceRight );
			m_pPage2->SetDlgItemText( IDC_CHANCEHR, m_structBatter.m_OBChanceHomeRun );
			m_pPage2->SetDlgItemText( IDC_CHANCEDOUBLE, m_structBatter.m_OBChanceDouble );
			m_pPage2->SetDlgItemText( IDC_CHANCESINGLE, m_structBatter.m_OBChanceSingle );
			m_pPage2->SetDlgItemText( IDC_CHANCETRIPLE, m_structBatter.m_OBChanceTriple );
			m_pPage2->SetDlgItemText( IDC_CHANCEWALK, m_structBatter.m_OBChanceWalk );
			m_pPage2->SetDlgItemText( IDC_CHANCEDOUBLEPLAY, m_structBatter.m_ChanceDoublePlay );
			m_pPage2->SetDlgItemText( IDC_CHANCEHRL, m_structBatter.m_OBChanceHomeRunLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCEDOUBLEL, m_structBatter.m_OBChanceDoubleLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCESINGLEL, m_structBatter.m_OBChanceSingleLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCETRIPLEL, m_structBatter.m_OBChanceTripleLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCEWALKL, m_structBatter.m_OBChanceWalkLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCEDOUBLEPLAYL, m_structBatter.m_ChanceDoublePlayLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCEHRR, m_structBatter.m_OBChanceHomeRunRight );
			m_pPage2->SetDlgItemText( IDC_CHANCEDOUBLER, m_structBatter.m_OBChanceDoubleRight );
			m_pPage2->SetDlgItemText( IDC_CHANCESINGLER, m_structBatter.m_OBChanceSingleRight );
			m_pPage2->SetDlgItemText( IDC_CHANCETRIPLER, m_structBatter.m_OBChanceTripleRight );
			m_pPage2->SetDlgItemText( IDC_CHANCEWALKR, m_structBatter.m_OBChanceWalkRight );
			m_pPage2->SetDlgItemText( IDC_CHANCEDOUBLEPLAYR, m_structBatter.m_ChanceDoublePlayRight );
			m_pPage2->m_bChangedFlag = FALSE;
		}

		if ((m_pPage3->m_hWnd != 0) && (m_pPage3->m_bChangedFlag == FALSE))
		{
			m_pPage3->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage3->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structBatter.m_PlayerName );
			m_pPage3->SetDlgItemInt( IDC_AB1, m_structBatter.m_AB, FALSE );
			m_pPage3->SetDlgItemInt( IDC_RUNS1, m_structBatter.m_Runs, FALSE );
			m_pPage3->SetDlgItemInt( IDC_HITS1, m_structBatter.m_Hits, FALSE );
			m_pPage3->SetDlgItemInt( IDC_RBI1, m_structBatter.m_RBI, FALSE );
			m_pPage3->SetDlgItemInt( IDC_2B1, m_structBatter.m_2B, FALSE );
			m_pPage3->SetDlgItemInt( IDC_3B1, m_structBatter.m_3B, FALSE );
			m_pPage3->SetDlgItemInt( IDC_HR1, m_structBatter.m_HomeRuns, FALSE );
			m_pPage3->SetDlgItemInt( IDC_WALK1, m_structBatter.m_Walk, FALSE );
			m_pPage3->SetDlgItemInt( IDC_STRIKEOUT1, m_structBatter.m_StrikeOut, FALSE );
			m_pPage3->SetDlgItemInt( IDC_REACHEDONERROR1, m_structBatter.m_ReachedOnError, FALSE );
			m_pPage3->SetDlgItemInt( IDC_SACRICIFE1, m_structBatter.m_Sacrifice, FALSE );
			m_pPage3->SetDlgItemInt( IDC_STOLENBASE1, m_structBatter.m_StolenBase, FALSE );
			m_pPage3->SetDlgItemInt( IDC_CS1, m_structBatter.m_CS, FALSE );
			m_pPage3->SetDlgItemInt( IDC_GAMES2, m_structBatter.m_Games, FALSE );
			m_pPage3->SetDlgItemInt( IDC_HBP1, m_structBatter.m_HBP, FALSE );
			if (m_structBatter.m_AB == 0)
			{
				m_pPage3->SetDlgItemText( IDC_BATTINGAVERAGE, "0" );
				m_pPage3->SetDlgItemText( IDC_SLG, "0" );
				m_pPage3->SetDlgItemText( IDC_ONBASEPERCENT, "0" );
			}
			else
			{
				m_fBattingAverage = (float)m_structBatter.m_Hits/m_structBatter.m_AB;
				sprintf_s(buf,"%1.3f",m_fBattingAverage);
				m_pPage3->SetDlgItemText( IDC_BATTINGAVERAGE, buf );
				m_fSLG = (float)((m_structBatter.m_Hits-(m_structBatter.m_2B+m_structBatter.m_3B+m_structBatter.m_HomeRuns))+(2*m_structBatter.m_2B)+(3*m_structBatter.m_3B)+(4*m_structBatter.m_HomeRuns))/(m_structBatter.m_AB);
				sprintf_s(buf,"%1.3f",m_fSLG);
				m_pPage3->SetDlgItemText( IDC_SLG, buf );
				m_fOnBasePercentage = (float)(m_structBatter.m_Hits+m_structBatter.m_Walk+m_structBatter.m_ReachedOnError+m_structBatter.m_Sacrifice)/(m_structBatter.m_AB+m_structBatter.m_Walk+m_structBatter.m_ReachedOnError+m_structBatter.m_Sacrifice);
				sprintf_s(buf,"%1.3f",m_fOnBasePercentage);
				m_pPage3->SetDlgItemText( IDC_ONBASEPERCENT, buf );
			}
			m_pPage3->m_bChangedFlag = FALSE;
		}

		if ((m_pPage4->m_hWnd != 0) && (m_pPage4->m_bChangedFlag == FALSE))
		{
			m_pPage4->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage4->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structBatter.m_PlayerName );
			m_pPage4->m_comboBunting.SetCurSel(m_structBatter.m_bBunting);
			m_pPage4->m_comboStealing.SetCurSel(m_structBatter.m_bStealing);
			m_pPage4->m_comboRunning.SetCurSel(m_structBatter.m_bRunning);
			m_pPage4->m_comboHitRun.SetCurSel(m_structBatter.m_bHitRun);
			m_pPage4->m_comboBatterHits.SetCurSel(m_structBatter.m_bBatterHits);
			m_pPage4->m_comboCatcherArm.SetCurSel(m_structBatter.m_bCatchArm);
			m_pPage4->m_comboOutArm.SetCurSel(m_structBatter.m_bOutArm);
			m_pPage4->m_comboPassBall.SetCurSel(m_structBatter.m_bPass);
			m_pPage4->m_comboPowerLeft.SetCurSel(m_structBatter.m_bPowerL);
			m_pPage4->m_comboPowerRight.SetCurSel(m_structBatter.m_bPowerR);
			m_pPage4->m_comboTRate.SetCurSel(m_structBatter.m_bTRate);
			m_pPage4->m_bChangedFlag = FALSE;
		}
		m_flagNew = FALSE;
	}
	else
	{
		// No player selected Edit Box being used, set seek to 0 as flag
		m_lSeekPlayerFile = 0;
	}
}

void PropertySheetBatters::SetPlayerNameCB(int iPage)
{
	char cTemp[31];
	CString filler10("          ");

	switch (iPage)
	{
	case 1:
		m_pPage1->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		break;
	case 2:
		m_pPage2->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		break;
	case 3:
		m_pPage3->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		break;
	case 4:
		m_pPage4->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		break;
	}
	
	cTemp[30]		= NULL;
	m_structBatter.m_PlayerName	= cTemp+filler10+filler10+filler10+filler10;

	if ((m_pPage1->m_hWnd != 0) && (iPage != 1))
	{
		m_pPage1->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structBatter.m_PlayerName );
	}
	if ((m_pPage2->m_hWnd != 0) && (iPage != 2))
	{
		m_pPage2->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structBatter.m_PlayerName );
	}
	if ((m_pPage3->m_hWnd != 0) && (iPage != 3))
	{
		m_pPage3->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structBatter.m_PlayerName );
	}
	if ((m_pPage4->m_hWnd != 0) && (iPage != 4))
	{
		m_pPage4->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structBatter.m_PlayerName );
	}
}

/////////////////////////////////////////////////////////////////////////////
// PropertyPageBattersInfo property page

IMPLEMENT_DYNCREATE(PropertyPageBattersInfo, CPropertyPage)

PropertyPageBattersInfo::PropertyPageBattersInfo() : CPropertyPage(PropertyPageBattersInfo::IDD)
{
	//{{AFX_DATA_INIT(PropertyPageBattersInfo)
	m_strTeam = _T("");
	//}}AFX_DATA_INIT

	// Get pointer to Doc
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window.
	CBaseballView *pView = (CBaseballView *) pChild->GetActiveView();
	m_pDocVoid = pView->GetDocument();

	m_bChangedFlag = FALSE;
}

PropertyPageBattersInfo::~PropertyPageBattersInfo()
{
}

void PropertyPageBattersInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropertyPageBattersInfo)
	DDX_Control(pDX, IDC_COMBO_TRATE, m_comboTRate);
	DDX_Control(pDX, IDC_COMBO_STEALING, m_comboStealing);
	DDX_Control(pDX, IDC_COMBO_RUNNING, m_comboRunning);
	DDX_Control(pDX, IDC_COMBO_POWERRIGHT, m_comboPowerRight);
	DDX_Control(pDX, IDC_COMBO_POWERLEFT, m_comboPowerLeft);
	DDX_Control(pDX, IDC_COMBO_PLAYERNAME1, m_comboPlayerName);
	DDX_Control(pDX, IDC_COMBO_PASSBALL, m_comboPassBall);
	DDX_Control(pDX, IDC_COMBO_OUTARM, m_comboOutArm);
	DDX_Control(pDX, IDC_COMBO_HITRUN, m_comboHitRun);
	DDX_Control(pDX, IDC_COMBO_CATCHERARM, m_comboCatcherArm);
	DDX_Control(pDX, IDC_COMBO_BUNTING, m_comboBunting);
	DDX_Control(pDX, IDC_COMBO_BATTERHITS, m_comboBatterHits);
	DDX_Text(pDX, IDC_TEAM0, m_strTeam);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PropertyPageBattersInfo, CPropertyPage)
	//{{AFX_MSG_MAP(PropertyPageBattersInfo)
	ON_CBN_CLOSEUP(IDC_COMBO_PLAYERNAME1, OnCloseupComboPlayerName)
	ON_BN_CLICKED(IDNEW, OnNew)
	ON_BN_CLICKED(IDPLAYERADD1, OnPlayerAdd)
	ON_BN_CLICKED(IDPLAYERUPDATE1, OnPlayerUpdate)
	ON_CBN_EDITCHANGE(IDC_COMBO_BATTERHITS, OnEditChangeComboBatterHits)
	ON_CBN_EDITCHANGE(IDC_COMBO_BUNTING, OnEditChangeComboBunting)
	ON_CBN_EDITCHANGE(IDC_COMBO_CATCHERARM, OnEditChangeComboCatcherArm)
	ON_CBN_EDITCHANGE(IDC_COMBO_HITRUN, OnEditChangeComboHitRun)
	ON_CBN_EDITCHANGE(IDC_COMBO_OUTARM, OnEditChangeComboOutArm)
	ON_CBN_EDITCHANGE(IDC_COMBO_PASSBALL, OnEditChangeComboPassball)
	ON_CBN_EDITCHANGE(IDC_COMBO_PLAYERNAME1, OnEditChangeComboPlayerName)
	ON_CBN_EDITCHANGE(IDC_COMBO_POWERLEFT, OnEditChangeComboPowerLeft)
	ON_CBN_EDITCHANGE(IDC_COMBO_POWERRIGHT, OnEditChangeComboPowerRight)
	ON_CBN_EDITCHANGE(IDC_COMBO_RUNNING, OnEditChangeComboRunning)
	ON_CBN_EDITCHANGE(IDC_COMBO_STEALING, OnEditChangeComboStealing)
	ON_CBN_EDITCHANGE(IDC_COMBO_TRATE, OnEditChangeComboTRate)
	ON_CBN_SELCHANGE(IDC_COMBO_BATTERHITS, OnSelchangeComboBatterHits)
	ON_CBN_SELCHANGE(IDC_COMBO_BUNTING, OnSelchangeComboBunting)
	ON_CBN_SELCHANGE(IDC_COMBO_CATCHERARM, OnSelchangeComboCatcherArm)
	ON_CBN_SELCHANGE(IDC_COMBO_HITRUN, OnSelchangeComboHitRun)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTARM, OnSelchangeComboOutArm)
	ON_CBN_SELCHANGE(IDC_COMBO_PASSBALL, OnSelchangeComboPassball)
	ON_CBN_SELCHANGE(IDC_COMBO_POWERLEFT, OnSelchangeComboPowerLeft)
	ON_CBN_SELCHANGE(IDC_COMBO_POWERRIGHT, OnSelchangeComboPowerRight)
	ON_CBN_SELCHANGE(IDC_COMBO_RUNNING, OnSelchangeComboRunning)
	ON_CBN_SELCHANGE(IDC_COMBO_STEALING, OnSelchangeComboStealing)
	ON_CBN_SELCHANGE(IDC_COMBO_TRATE, OnSelchangeComboTRate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertyPageBattersInfo message handlers

void PropertyPageBattersInfo::OnCloseupComboPlayerName() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->OnCloseupComboPlayerName(4);

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);

	m_bChangedFlag = FALSE;
}

void PropertyPageBattersInfo::OnCancel() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP3); // Cancel Button Pressed
	
	m_bChangedFlag = FALSE;
	CPropertyPage::OnCancel();
}

void PropertyPageBattersInfo::OnOK() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP2); // OK Button Pressed

	m_bChangedFlag = FALSE;
	CPropertyPage::OnOK();
}

void PropertyPageBattersInfo::OnNew() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->OnNew();

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(TRUE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(FALSE);

	m_bChangedFlag = FALSE;
}

void PropertyPageBattersInfo::OnPlayerAdd() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP1); // Update Button Pressed

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);
	
	m_bChangedFlag = FALSE;
}

void PropertyPageBattersInfo::OnPlayerUpdate() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP1); // Update Button Pressed
	
	m_bChangedFlag = FALSE;
}

BOOL PropertyPageBattersInfo::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here

	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	SetDlgItemText( IDC_TEAM0, pDoc->m_pPropertySheetBatters->m_TeamName );
	
	OnInitDialogPublic();

	// Build combo table for player display
	BuildPlayerNameComboBox();

	// Enable / Disable Update and Add buttons
	if (pDoc->m_pPropertySheetBatters->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PropertyPageBattersInfo::BuildPlayerNameComboBox()
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->BuildPlayerNameComboBox(4);
	if (pDoc->m_pPropertySheetBatters->m_rgetcursel != -1)
		pDoc->m_pPropertySheetBatters->OnCloseupComboPlayerName(6);
}

void PropertyPageBattersInfo::OnInitDialogPublic()
{
	SetDlgItemText( IDC_COMBO_PLAYERNAME1, NULL );
	m_comboBunting.SetCurSel(3);
	m_comboStealing.SetCurSel(5);
	m_comboRunning.SetCurSel(5);
	m_comboHitRun.SetCurSel(3);
	m_comboBatterHits.SetCurSel(0);
	m_comboCatcherArm.SetCurSel(4);
	m_comboOutArm.SetCurSel(6);
	m_comboPassBall.SetCurSel(0);
	m_comboPowerLeft.SetCurSel(0);
	m_comboPowerRight.SetCurSel(0);
	m_comboTRate.SetCurSel(0);
}

void PropertyPageBattersInfo::OnEditChangeComboBatterHits() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnEditChangeComboBunting() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnEditChangeComboCatcherArm() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnEditChangeComboHitRun() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnEditChangeComboOutArm() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnEditChangeComboPassball() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnEditChangeComboPlayerName() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetBatters->SetPlayerNameCB(4);
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnEditChangeComboPowerLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnEditChangeComboPowerRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnEditChangeComboRunning() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnEditChangeComboStealing() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnEditChangeComboTRate() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnSelchangeComboBatterHits() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnSelchangeComboBunting() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnSelchangeComboCatcherArm() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnSelchangeComboHitRun() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnSelchangeComboOutArm() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnSelchangeComboPassball() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnSelchangeComboPowerLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnSelchangeComboPowerRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnSelchangeComboRunning() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnSelchangeComboStealing() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnSelchangeComboTRate() 
{
	m_bChangedFlag = TRUE;
}

BOOL PropertyPageBattersInfo::OnSetActive() 
{
	// Enable / Disable Update and Add buttons
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	if (pDoc->m_pPropertySheetBatters->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}
	
	return CPropertyPage::OnSetActive();
}

/////////////////////////////////////////////////////////////////////////////
// PropertyPagePitchersInfo property page

IMPLEMENT_DYNCREATE(PropertyPagePitchersInfo, CPropertyPage)

PropertyPagePitchersInfo::PropertyPagePitchersInfo() : CPropertyPage(PropertyPagePitchersInfo::IDD)
{
	//{{AFX_DATA_INIT(PropertyPagePitchersInfo)
	m_TeamName = _T("");
	//}}AFX_DATA_INIT
	// Get pointer to Doc
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window.
	CBaseballView *pView = (CBaseballView *) pChild->GetActiveView();
	m_pDocVoid = pView->GetDocument();

	m_bChangedFlag = FALSE;
}

PropertyPagePitchersInfo::~PropertyPagePitchersInfo()
{
}

void PropertyPagePitchersInfo::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropertyPagePitchersInfo)
	DDX_Control(pDX, IDC_WP, m_ceditWP);
	DDX_Control(pDX, IDC_STARTER1, m_ceditStarter);
	DDX_Control(pDX, IDC_SPIN_WP, m_spinWP);
	DDX_Control(pDX, IDC_SPIN_STARER1, m_spinStarter);
	DDX_Control(pDX, IDC_SPIN_RELIEF1, m_spinRelief);
	DDX_Control(pDX, IDC_SPIN_PITCHER, m_spinPitcher);
	DDX_Control(pDX, IDC_SPIN_ERP, m_spinERP);
	DDX_Control(pDX, IDC_SPIN_BALK, m_spinBalk);
	DDX_Control(pDX, IDC_RELIEF1, m_ceditRelief);
	DDX_Control(pDX, IDC_PITCHER, m_ceditPitcher);
	DDX_Control(pDX, IDC_ERP, m_ceditERP);
	DDX_Control(pDX, IDC_COMBO_PLAYERNAME1, m_comboPlayerName);
	DDX_Control(pDX, IDC_COMBO_PITCHERTHROWS, m_comboThrows);
	DDX_Control(pDX, IDC_COMBO_HOLD1, m_comboHold);
	DDX_Control(pDX, IDC_COMBO_BUNTING1, m_comboBunting);
	DDX_Control(pDX, IDC_BALK, m_ceditBalk);
	DDX_Text(pDX, IDC_TEAM0, m_TeamName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PropertyPagePitchersInfo, CPropertyPage)
	//{{AFX_MSG_MAP(PropertyPagePitchersInfo)
	ON_CBN_CLOSEUP(IDC_COMBO_PLAYERNAME1, OnCloseupComboPlayername1)
	ON_BN_CLICKED(IDNEW, OnNew)
	ON_BN_CLICKED(IDPLAYERADD1, OnPlayerAdd)
	ON_BN_CLICKED(IDPLAYERUPDATE1, OnPlayerUpdate)
	ON_CBN_EDITCHANGE(IDC_COMBO_PLAYERNAME1, OnEditChangeComboPlayerName)
	ON_CBN_SELCHANGE(IDC_COMBO_BUNTING1, OnSelchangeComboBunting)
	ON_CBN_SELCHANGE(IDC_COMBO_HOLD1, OnSelchangeComboHold)
	ON_CBN_SELCHANGE(IDC_COMBO_PITCHERTHROWS, OnSelchangeComboPitcherThrows)
	ON_EN_CHANGE(IDC_ERP, OnChangeERP)
	ON_EN_CHANGE(IDC_PITCHER, OnChangePitcher)
	ON_EN_CHANGE(IDC_RELIEF1, OnChangeRelief)
	ON_EN_CHANGE(IDC_STARTER1, OnChangeStarter)
	ON_EN_CHANGE(IDC_WP, OnChangeWP)
	ON_EN_CHANGE(IDC_BALK, OnChangeBalk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertyPagePitchersInfo message handlers

void PropertyPagePitchersInfo::OnCloseupComboPlayername1() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->OnCloseupComboPlayerName(1);

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);

	m_bChangedFlag = FALSE;
}

BOOL PropertyPagePitchersInfo::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_spinRelief.SetRange(0, 4);
	m_spinRelief.SetBuddy( &m_ceditRelief );
	m_spinStarter.SetRange(0, 9);
	m_spinStarter.SetBuddy( &m_ceditStarter );
	m_spinPitcher.SetRange(0, 5);
	m_spinPitcher.SetBuddy( &m_ceditPitcher );
	m_spinWP.SetRange(0, 20);
	m_spinWP.SetBuddy( &m_ceditWP );
	m_spinERP.SetRange(0, 51);
	m_spinERP.SetBuddy( &m_ceditERP );
	m_spinBalk.SetRange(0, 20);
	m_spinBalk.SetBuddy( &m_ceditBalk );

	m_comboBunting.SetCurSel(4);
	m_comboHold.SetCurSel(9);
	m_comboThrows.SetCurSel(1);
	
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	SetDlgItemText( IDC_TEAM0, pDoc->m_pPropertySheetPitchers->m_TeamName );

	OnInitDialogPublic();

	// Build combo table for player display
	BuildPlayerNameComboBox();

	// Enable / Disable Update and Add buttons
	if (pDoc->m_pPropertySheetPitchers->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PropertyPagePitchersInfo::OnInitDialogPublic()
{
	
	SetDlgItemText( IDC_COMBO_PLAYERNAME1, NULL );
	SetDlgItemInt( IDC_STARTER1, 0, FALSE );
	SetDlgItemInt( IDC_RELIEF1, 0, FALSE );
	SetDlgItemInt( IDC_PITCHER, 0, FALSE );
	SetDlgItemInt( IDC_WP, 0, FALSE );
	SetDlgItemInt( IDC_ERP, 0, FALSE );
	SetDlgItemInt( IDC_BALK, 0, FALSE );
	m_comboBunting.SetCurSel(4);
	m_comboHold.SetCurSel(9);
	m_comboThrows.SetCurSel(1);
}

void PropertyPagePitchersInfo::BuildPlayerNameComboBox()
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->BuildPlayerNameComboBox(1);
	if (pDoc->m_pPropertySheetPitchers->m_rgetcursel != -1)
		pDoc->m_pPropertySheetPitchers->OnCloseupComboPlayerName(6);
}

void PropertyPagePitchersInfo::OnCancel() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->PostMessage(WM_APP3); // Cancel Button Pressed
	
	m_bChangedFlag = FALSE;
	CPropertyPage::OnCancel();
}

void PropertyPagePitchersInfo::OnNew() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->OnNew();

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(TRUE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(FALSE);

	m_bChangedFlag = FALSE;
}

void PropertyPagePitchersInfo::OnOK() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->PostMessage(WM_APP2); // OK Button Pressed

	m_bChangedFlag = FALSE;
	CPropertyPage::OnOK();
}

void PropertyPagePitchersInfo::OnPlayerAdd() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->PostMessage(WM_APP1); // Update Button Pressed

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);
	
	m_bChangedFlag = FALSE;
}

void PropertyPagePitchersInfo::OnPlayerUpdate() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->PostMessage(WM_APP1); // Update Button Pressed
	
	m_bChangedFlag = FALSE;
}

void PropertyPagePitchersInfo::OnEditChangeComboPlayerName() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->SetPlayerNameCB(1);
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersInfo::OnSelchangeComboBunting() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersInfo::OnSelchangeComboHold() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersInfo::OnSelchangeComboPitcherThrows() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersInfo::OnChangeERP() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersInfo::OnChangePitcher() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersInfo::OnChangeRelief() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersInfo::OnChangeStarter() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersInfo::OnChangeWP() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersInfo::OnChangeBalk() 
{
	m_bChangedFlag = TRUE;
}

BOOL PropertyPagePitchersInfo::OnSetActive() 
{
	// Enable / Disable Update and Add buttons
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	if (pDoc->m_pPropertySheetPitchers->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}
	
	return CPropertyPage::OnSetActive();
}

/////////////////////////////////////////////////////////////////////////////
// PropertyPagePitchersChance property page

IMPLEMENT_DYNCREATE(PropertyPagePitchersChance, CPropertyPage)

PropertyPagePitchersChance::PropertyPagePitchersChance() : CPropertyPage(PropertyPagePitchersChance::IDD)
{
	//{{AFX_DATA_INIT(PropertyPagePitchersChance)
	m_TeamName = _T("");
	//}}AFX_DATA_INIT
	// Get pointer to Doc
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window.
	CBaseballView *pView = (CBaseballView *) pChild->GetActiveView();
	m_pDocVoid = pView->GetDocument();

	m_bChangedFlag = FALSE;
}

PropertyPagePitchersChance::~PropertyPagePitchersChance()
{
}

void PropertyPagePitchersChance::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropertyPagePitchersChance)
	DDX_Control(pDX, IDC_CHANCEWALKR, m_ceditWalkRight);
	DDX_Control(pDX, IDC_CHANCEWALKL, m_ceditWalkLeft);
	DDX_Control(pDX, IDC_CHANCETRIPLER, m_ceditTripleRight);
	DDX_Control(pDX, IDC_CHANCETRIPLEL, m_ceditTripleLeft);
	DDX_Control(pDX, IDC_CHANCESINGLER, m_ceditSingleRight);
	DDX_Control(pDX, IDC_CHANCESINGLEL, m_ceditSingleLeft);
	DDX_Control(pDX, IDC_CHANCEHRR, m_ceditHRRight);
	DDX_Control(pDX, IDC_CHANCEHRL, m_ceditHRLeft);
	DDX_Control(pDX, IDC_CHANCEDOUBLER, m_ceditDoubleRight);
	DDX_Control(pDX, IDC_CHANCEDOUBLEPLAYR, m_ceditDoublePlayRight);
	DDX_Control(pDX, IDC_CHANCEDOUBLEPLAYL, m_ceditDoublePlayLeft);
	DDX_Control(pDX, IDC_CHANCEDOUBLEL, m_ceditDoubleLeft);
	DDX_Control(pDX, IDC_COMBO_PLAYERNAME1, m_comboPlayerName);
	DDX_Control(pDX, IDC_CHANCEDOUBLEPLAY, m_ceditDoublePlay);
	DDX_Control(pDX, IDC_CHANCEWALK, m_ceditWalk);
	DDX_Control(pDX, IDC_CHANCETRIPLE, m_ceditTriple);
	DDX_Control(pDX, IDC_CHANCESINGLE, m_ceditSingle);
	DDX_Control(pDX, IDC_CHANCEHR, m_ceditHR);
	DDX_Control(pDX, IDC_CHANCEDOUBLE, m_ceditDouble);
	DDX_Control(pDX, IDC_CHANCEBASIC, m_ceditBasic);
	DDX_Control(pDX, IDC_CHANCERIGHT, m_ceditRight);
	DDX_Control(pDX, IDC_CHANCELEFT, m_ceditLeft);
	DDX_Text(pDX, IDC_TEAM0, m_TeamName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PropertyPagePitchersChance, CPropertyPage)
	//{{AFX_MSG_MAP(PropertyPagePitchersChance)
	ON_CBN_CLOSEUP(IDC_COMBO_PLAYERNAME1, OnCloseupComboPlayerName)
	ON_BN_CLICKED(IDNEW, OnNew)
	ON_BN_CLICKED(IDPLAYERADD1, OnPlayerAdd)
	ON_BN_CLICKED(IDPLAYERUPDATE1, OnPlayerUpdate)
	ON_CBN_EDITCHANGE(IDC_COMBO_PLAYERNAME1, OnEditChangeComboPlayerName)
	ON_EN_CHANGE(IDC_CHANCEBASIC, OnChangeChanceBasic)
	ON_EN_CHANGE(IDC_CHANCEDOUBLE, OnChangeChanceDouble)
	ON_EN_CHANGE(IDC_CHANCEHR, OnChangeChanceHR)
	ON_EN_CHANGE(IDC_CHANCELEFT, OnChangeChanceLeft)
	ON_EN_CHANGE(IDC_CHANCERIGHT, OnChangeChancerRight)
	ON_EN_CHANGE(IDC_CHANCESINGLE, OnChangeChanceSingle)
	ON_EN_CHANGE(IDC_CHANCETRIPLE, OnChangeChanceTriple)
	ON_EN_CHANGE(IDC_CHANCEWALK, OnChangeChanceWalk)
	ON_EN_CHANGE(IDC_CHANCEDOUBLEPLAY, OnChangeChanceDoublePlay)
	ON_EN_CHANGE(IDC_CHANCEDOUBLEL, OnChangeChanceDoubleLeft)
	ON_EN_CHANGE(IDC_CHANCEDOUBLEPLAYL, OnChangeChanceDoublePlayLeft)
	ON_EN_CHANGE(IDC_CHANCEDOUBLEPLAYR, OnChangeChanceDoublePlayRight)
	ON_EN_CHANGE(IDC_CHANCEDOUBLER, OnChangeChanceDoubleRight)
	ON_EN_CHANGE(IDC_CHANCEHRL, OnChangeChanceHRLeft)
	ON_EN_CHANGE(IDC_CHANCEHRR, OnChangeChanceHRRight)
	ON_EN_CHANGE(IDC_CHANCESINGLEL, OnChangeChanceSingleLeft)
	ON_EN_CHANGE(IDC_CHANCESINGLER, OnChangeChanceSingleRight)
	ON_EN_CHANGE(IDC_CHANCETRIPLEL, OnChangeChanceTripleLeft)
	ON_EN_CHANGE(IDC_CHANCETRIPLER, OnChangeChanceTripleRight)
	ON_EN_CHANGE(IDC_CHANCEWALKL, OnChangeChanceWalkLeft)
	ON_EN_CHANGE(IDC_CHANCEWALKR, OnChangeChanceWalkRight)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertyPagePitchersChance message handlers

void PropertyPagePitchersChance::OnCloseupComboPlayerName() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->OnCloseupComboPlayerName(2);

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);

	m_bChangedFlag = FALSE;
}

BOOL PropertyPagePitchersChance::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	SetDlgItemText( IDC_TEAM0, pDoc->m_pPropertySheetPitchers->m_TeamName );

	OnInitDialogPublic();

	// Build combo table for player display
	BuildPlayerNameComboBox();

	// Enable / Disable Update and Add buttons
	if (pDoc->m_pPropertySheetPitchers->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PropertyPagePitchersChance::OnInitDialogPublic()
{
	SetDlgItemText( IDC_COMBO_PLAYERNAME1, NULL );
	SetDlgItemText( IDC_CHANCELEFT, "0" );
	SetDlgItemText( IDC_CHANCEBASIC, "0" );
	SetDlgItemText( IDC_CHANCERIGHT, "0" );
	SetDlgItemText( IDC_CHANCEWALK, "0" );
	SetDlgItemText( IDC_CHANCETRIPLE, "0" );
	SetDlgItemText( IDC_CHANCESINGLE, "0" );
	SetDlgItemText( IDC_CHANCEHR, "0" );
	SetDlgItemText( IDC_CHANCEDOUBLE, "0" );
	SetDlgItemText( IDC_CHANCEDOUBLEPLAY, "0" );
	SetDlgItemText( IDC_CHANCEWALKL, "0" );
	SetDlgItemText( IDC_CHANCETRIPLEL, "0" );
	SetDlgItemText( IDC_CHANCESINGLEL, "0" );
	SetDlgItemText( IDC_CHANCEHRL, "0" );
	SetDlgItemText( IDC_CHANCEDOUBLEL, "0" );
	SetDlgItemText( IDC_CHANCEDOUBLEPLAYL, "0" );
	SetDlgItemText( IDC_CHANCEWALKR, "0" );
	SetDlgItemText( IDC_CHANCETRIPLER, "0" );
	SetDlgItemText( IDC_CHANCESINGLER, "0" );
	SetDlgItemText( IDC_CHANCEHRR, "0" );
	SetDlgItemText( IDC_CHANCEDOUBLER, "0" );
	SetDlgItemText( IDC_CHANCEDOUBLEPLAYR, "0" );
}

void PropertyPagePitchersChance::BuildPlayerNameComboBox()
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->BuildPlayerNameComboBox(2);
	if (pDoc->m_pPropertySheetPitchers->m_rgetcursel != -1)
		pDoc->m_pPropertySheetPitchers->OnCloseupComboPlayerName(6);
}

void PropertyPagePitchersChance::OnCancel() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->PostMessage(WM_APP3); // Cancel Button Pressed
	
	m_bChangedFlag = FALSE;
	CPropertyPage::OnCancel();
}

void PropertyPagePitchersChance::OnNew() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->OnNew();

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(TRUE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(FALSE);

	m_bChangedFlag = FALSE;
}

void PropertyPagePitchersChance::OnOK() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->PostMessage(WM_APP2); // OK Button Pressed

	m_bChangedFlag = FALSE;
	CPropertyPage::OnOK();
}

void PropertyPagePitchersChance::OnPlayerAdd() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->PostMessage(WM_APP1); // Update Button Pressed

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);
	
	m_bChangedFlag = FALSE;
}

void PropertyPagePitchersChance::OnPlayerUpdate() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->PostMessage(WM_APP1); // Update Button Pressed
	
	m_bChangedFlag = FALSE;
}

void PropertyPagePitchersChance::OnEditChangeComboPlayerName() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->SetPlayerNameCB(2);
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceBasic() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceDouble() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceDoubleLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceDoubleRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceHR() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceHRLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceHRRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChancerRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceSingle() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceSingleLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceSingleRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceTriple() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceTripleLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceTripleRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceWalk() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceWalkLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceWalkRight() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceDoublePlay() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceDoublePlayLeft() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersChance::OnChangeChanceDoublePlayRight() 
{
	m_bChangedFlag = TRUE;
}

BOOL PropertyPagePitchersChance::OnSetActive() 
{
	// Enable / Disable Update and Add buttons
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	if (pDoc->m_pPropertySheetPitchers->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}
	
	return CPropertyPage::OnSetActive();
}

/////////////////////////////////////////////////////////////////////////////
// PropertyPagePitchersStats property page

IMPLEMENT_DYNCREATE(PropertyPagePitchersStats, CPropertyPage)

PropertyPagePitchersStats::PropertyPagePitchersStats() : CPropertyPage(PropertyPagePitchersStats::IDD)
{
	//{{AFX_DATA_INIT(PropertyPagePitchersStats)
	m_TeamName = _T("");
	//}}AFX_DATA_INIT
	// Get pointer to Doc
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *) pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window.
	CBaseballView *pView = (CBaseballView *) pChild->GetActiveView();
	m_pDocVoid = pView->GetDocument();

	m_bChangedFlag = FALSE;
}

PropertyPagePitchersStats::~PropertyPagePitchersStats()
{
}

void PropertyPagePitchersStats::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropertyPagePitchersStats)
	DDX_Control(pDX, IDC_WINS1, m_ceditWins);
	DDX_Control(pDX, IDC_WALK1, m_ceditWalk);
	DDX_Control(pDX, IDC_TRG1, m_ceditTRG);
	DDX_Control(pDX, IDC_STARTS1, m_ceditStarts);
	DDX_Control(pDX, IDC_STRIKEOUT1, m_ceditStrikeOut);
	DDX_Control(pDX, IDC_SPIN_WINS1, m_spinWins);
	DDX_Control(pDX, IDC_SPIN_WALK1, m_spinWalk);
	DDX_Control(pDX, IDC_SPIN_STRIKOUT1, m_spinK);
	DDX_Control(pDX, IDC_SPIN_STARTS1, m_spinStarts);
	DDX_Control(pDX, IDC_SPIN_SAVES1, m_spinSaves);
	DDX_Control(pDX, IDC_SPIN_LOSS1, m_spinLoss);
	DDX_Control(pDX, IDC_SPIN_HR1, m_spinHR);
	DDX_Control(pDX, IDC_SPIN_HITS1, m_spinHits);
	DDX_Control(pDX, IDC_SPIN_GAMES1, m_spinGames);
	DDX_Control(pDX, IDC_SPIN_ER1, m_spinER);
	DDX_Control(pDX, IDC_SPIN_COMPLETEGAMES1, m_spinCompGames);
	DDX_Control(pDX, IDC_SAVES1, m_ceditSaves);
	DDX_Control(pDX, IDC_LOSS1, m_ceditLoss);
	DDX_Control(pDX, IDC_IP1, m_ceditIP);
	DDX_Control(pDX, IDC_HR1, m_ceditHR);
	DDX_Control(pDX, IDC_HITS1, m_ceditHits);
	DDX_Control(pDX, IDC_GAMES1, m_ceditGames);
	DDX_Control(pDX, IDC_ERA1, m_ceditERA);
	DDX_Control(pDX, IDC_ER1, m_ceditER);
	DDX_Control(pDX, IDC_COMPLETEGAMES1, m_ceditCompGames);
	DDX_Control(pDX, IDC_COMBO_PLAYERNAME1, m_comboPlayerName);
	DDX_Text(pDX, IDC_TEAM0, m_TeamName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PropertyPagePitchersStats, CPropertyPage)
	//{{AFX_MSG_MAP(PropertyPagePitchersStats)
	ON_CBN_CLOSEUP(IDC_COMBO_PLAYERNAME1, OnCloseupComboPlayerName)
	ON_BN_CLICKED(IDNEW, OnNew)
	ON_BN_CLICKED(IDPLAYERADD1, OnPlayerAdd)
	ON_BN_CLICKED(IDPLAYERUPDATE1, OnPlayerUpdate)
	ON_CBN_EDITCHANGE(IDC_COMBO_PLAYERNAME1, OnEditChangeComboPlayerName)
	ON_EN_CHANGE(IDC_ER1, OnChangeER)
	ON_EN_CHANGE(IDC_ERA1, OnChangeERA)
	ON_EN_CHANGE(IDC_GAMES1, OnChangeGames)
	ON_EN_CHANGE(IDC_HITS1, OnChangeHits)
	ON_EN_CHANGE(IDC_HR1, OnChangeHR)
	ON_EN_CHANGE(IDC_IP1, OnChangeIP)
	ON_EN_CHANGE(IDC_LOSS1, OnChangeLoss)
	ON_EN_CHANGE(IDC_SAVES1, OnChangeSaves)
	ON_EN_CHANGE(IDC_STARTS1, OnChangeStarts)
	ON_EN_CHANGE(IDC_STRIKEOUT1, OnChangeStrikeout)
	ON_EN_CHANGE(IDC_TRG1, OnChangeTRG)
	ON_EN_CHANGE(IDC_WALK1, OnChangeWalk)
	ON_EN_CHANGE(IDC_WINS1, OnChangeWins)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertyPagePitchersStats message handlers

void PropertyPagePitchersStats::OnCloseupComboPlayerName() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->OnCloseupComboPlayerName(3);

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);

	m_bChangedFlag = FALSE;
}

BOOL PropertyPagePitchersStats::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_spinER.SetRange(0, 300);
	m_spinER.SetBuddy( &m_ceditER );
	m_spinHits.SetRange(0, 300);
	m_spinHits.SetBuddy( &m_ceditHits );
	m_spinHR.SetRange(0, 300);
	m_spinHR.SetBuddy( &m_ceditHR );
	m_spinLoss.SetRange(0, 300);
	m_spinLoss.SetBuddy( &m_ceditLoss );
	m_spinSaves.SetRange(0, 300);
	m_spinSaves.SetBuddy( &m_ceditSaves );
	m_spinK.SetRange(0, 300);
	m_spinK.SetBuddy( &m_ceditStrikeOut );
	m_spinWalk.SetRange(0, 300);
	m_spinWalk.SetBuddy( &m_ceditWalk );
	m_spinWins.SetRange(0, 300);
	m_spinWins.SetBuddy( &m_ceditWins );
	m_spinStarts.SetRange(0, 100);
	m_spinStarts.SetBuddy( &m_ceditStarts );
	m_spinGames.SetRange(0, 500);
	m_spinGames.SetBuddy( &m_ceditGames );
	m_spinCompGames.SetRange(0, 500);
	m_spinCompGames.SetBuddy( &m_ceditCompGames );
	
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	SetDlgItemText( IDC_TEAM0, pDoc->m_pPropertySheetPitchers->m_TeamName );

	OnInitDialogPublic();

	// Build combo table for player display
	BuildPlayerNameComboBox();

	// Enable / Disable Update and Add buttons
	if (pDoc->m_pPropertySheetPitchers->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PropertyPagePitchersStats::OnInitDialogPublic()
{
	SetDlgItemText( IDC_COMBO_PLAYERNAME1, NULL );
	SetDlgItemText( IDC_IP1, NULL );
	SetDlgItemText( IDC_ERA1, NULL );
	SetDlgItemText( IDC_TRG1, NULL );
	SetDlgItemInt( IDC_STARTS1, 0, FALSE );
	SetDlgItemInt( IDC_WINS1, 0, FALSE );
	SetDlgItemInt( IDC_WALK1, 0, FALSE );
	SetDlgItemInt( IDC_STRIKEOUT1, 0, FALSE );
	SetDlgItemInt( IDC_SAVES1, 0, FALSE );
	SetDlgItemInt( IDC_LOSS1, 0, FALSE );
	SetDlgItemInt( IDC_HR1, 0, FALSE );
	SetDlgItemInt( IDC_HITS1, 0, FALSE );
	SetDlgItemInt( IDC_ER1, 0, FALSE );
	SetDlgItemInt( IDC_GAMES1, 0, FALSE );
	SetDlgItemInt( IDC_COMPLETEGAMES1, 0, FALSE );
}

void PropertyPagePitchersStats::BuildPlayerNameComboBox()
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->BuildPlayerNameComboBox(3);
	if (pDoc->m_pPropertySheetPitchers->m_rgetcursel != -1)
		pDoc->m_pPropertySheetPitchers->OnCloseupComboPlayerName(6);
}

void PropertyPagePitchersStats::OnCancel() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->PostMessage(WM_APP3); // Cancel Button Pressed
	
	m_bChangedFlag = FALSE;
	CPropertyPage::OnCancel();
}

void PropertyPagePitchersStats::OnNew() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->OnNew();

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(TRUE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(FALSE);

	m_bChangedFlag = FALSE;
}

void PropertyPagePitchersStats::OnOK() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->PostMessage(WM_APP2); // OK Button Pressed

	m_bChangedFlag = FALSE;
	CPropertyPage::OnOK();
}

void PropertyPagePitchersStats::OnPlayerAdd() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->PostMessage(WM_APP1); // Update Button Pressed

	// Enable / Disable Update and Add buttons
	CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
	ASSERT (pAddWnd);
	pAddWnd->EnableWindow(FALSE);
	CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
	ASSERT (pUpdateWnd);
	pUpdateWnd->EnableWindow(TRUE);
	
	m_bChangedFlag = FALSE;
}

void PropertyPagePitchersStats::OnPlayerUpdate() 
{
	// Notify Main Sheet of button being pressed
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->PostMessage(WM_APP1); // Update Button Pressed
	
	m_bChangedFlag = FALSE;
}

void PropertyPagePitchersStats::OnEditChangeComboPlayerName() 
{
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	pDoc->m_pPropertySheetPitchers->SetPlayerNameCB(3);
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersStats::OnChangeER() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersStats::OnChangeERA() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersStats::OnChangeGames() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersStats::OnChangeHits() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersStats::OnChangeHR() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersStats::OnChangeIP() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersStats::OnChangeLoss() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersStats::OnChangeSaves() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersStats::OnChangeStarts() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersStats::OnChangeStrikeout() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersStats::OnChangeTRG() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersStats::OnChangeWalk() 
{
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersStats::OnChangeWins() 
{
	m_bChangedFlag = TRUE;
}

BOOL PropertyPagePitchersStats::OnSetActive() 
{
	// Enable / Disable Update and Add buttons
	CBaseballDoc* pDoc = (CBaseballDoc*) m_pDocVoid;
	if (pDoc->m_pPropertySheetPitchers->m_flagNew == TRUE)
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(TRUE);	// ON
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(FALSE);	// Off
	}
	else
	{
		CWnd* pAddWnd = GetDlgItem(IDPLAYERADD1);
		ASSERT (pAddWnd);
		pAddWnd->EnableWindow(FALSE);	// Off
		CWnd* pUpdateWnd = GetDlgItem(IDPLAYERUPDATE1);
		ASSERT (pUpdateWnd);
		pUpdateWnd->EnableWindow(TRUE);	//On
	}
	
	return CPropertyPage::OnSetActive();
}

/////////////////////////////////////////////////////////////////////////////
// PropertySheetPitchers

IMPLEMENT_DYNAMIC(PropertySheetPitchers, CPropertySheet)

PropertySheetPitchers::PropertySheetPitchers(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	m_rgetcursel = -1;
	m_newFlag = FALSE;
}

PropertySheetPitchers::PropertySheetPitchers(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_rgetcursel = -1;
	m_newFlag = FALSE;
}

PropertySheetPitchers::~PropertySheetPitchers()
{
}


BEGIN_MESSAGE_MAP(PropertySheetPitchers, CPropertySheet)
	//{{AFX_MSG_MAP(PropertySheetPitchers)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_APP1,OnUpdate)
	ON_MESSAGE(WM_APP2,OnOK)
	ON_MESSAGE(WM_APP3,OnCancel)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertySheetPitchers message handlers

BOOL PropertySheetPitchers::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();
	
	// TODO: Add your specialized code here

	RECT rcWnd;
	RECT rcOK;

	// Get size info on OK button and then hide the button
	CWnd* pOKWnd = GetDlgItem(IDOK);
	ASSERT (pOKWnd);
	pOKWnd->GetWindowRect(&rcOK);
	pOKWnd->ShowWindow(SW_HIDE);

	// Hide the Cancel button
	CWnd* pCancelWnd = GetDlgItem(IDCANCEL);
	ASSERT (pCancelWnd);
	pCancelWnd->ShowWindow(SW_HIDE);

	// Hide the Help button
	CWnd* pHelpWnd = GetDlgItem(IDHELP);
	ASSERT (pHelpWnd);
	pHelpWnd->ShowWindow(SW_HIDE);

	// Resize the window to remove the buttons
	GetWindowRect(&rcWnd);
	rcWnd.bottom -= (rcOK.bottom-rcOK.top+6); // 6 = spacing
 	MoveWindow (rcWnd.left, rcWnd.top, 
		rcWnd.right-rcWnd.left, rcWnd.bottom-rcWnd.top);
	
	// Now center the dialog based on the desktop
	CenterWindow(GetDesktopWindow());

	m_rgetcursel = -1;

	return TRUE;
}

void PropertySheetPitchers::BuildPlayerNameComboBox(int iPage)
{
	BYTE count;
	int i;
	LONG lTeamSection = sizeof(BYTE);
	LONG lPlayerSection = m_structPitcher.m_RecordSize;
	CString	strPlayerName;	// Length of 30


	// If needed save Player Name
	if (m_flagNew == TRUE)
		strPlayerName = m_structPitcher.m_PitcherName;
	// Get count of players in file
	count = m_structPitcher.GetCountPitcher(m_FileName);
	// Open file and build player ComboBox
	switch (iPage)
	{
	case 1:
		m_pPage1->m_comboPlayerName.ResetContent();
		break;
	case 2:
		m_pPage2->m_comboPlayerName.ResetContent();
		break;
	case 3:
		m_pPage3->m_comboPlayerName.ResetContent();
		break;
	}
	for (i=0; i<count; i++)
	{
		m_lSeekPlayerFile = lTeamSection+(i*lPlayerSection);
		m_structPitcher.GetPitcher(m_FileName ,m_lSeekPlayerFile);
		switch (iPage)
		{
		case 1:
			m_pPage1->m_comboPlayerName.AddString(m_structPitcher.m_PitcherName);
			break;
		case 2:
			m_pPage2->m_comboPlayerName.AddString(m_structPitcher.m_PitcherName);
			break;
		case 3:
			m_pPage3->m_comboPlayerName.AddString(m_structPitcher.m_PitcherName);
			break;
		}
	}
	switch (iPage)
	{
	case 1:
		m_pPage1->m_bChangedFlag = FALSE;
		break;
	case 2:
		m_pPage2->m_bChangedFlag = FALSE;
		break;
	case 3:
		m_pPage3->m_bChangedFlag = FALSE;
		break;
	}
	m_lSeekPlayerFile = 0;

	if (m_flagNew == TRUE)
	{
		OnNewInitStruct();
		// put back player name cause it was wiped out in this routine
		m_structPitcher.m_PitcherName = strPlayerName;
		switch (iPage)
		{
		case 1:
			m_pPage1->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structPitcher.m_PitcherName );
			break;
		case 2:
			m_pPage2->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structPitcher.m_PitcherName );
			break;
		case 3:
			m_pPage3->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structPitcher.m_PitcherName );
			break;
		}
	}
}

void PropertySheetPitchers::OnNew()
{
	if (m_pPage1->m_hWnd != 0)
	{
		m_pPage1->OnInitDialogPublic();
	}
	if (m_pPage2->m_hWnd != 0)
	{
		m_pPage2->OnInitDialogPublic();
	}
	if (m_pPage3->m_hWnd != 0)
	{
		m_pPage3->OnInitDialogPublic();
	}

	OnNewInitStruct();
	m_flagNew = TRUE;
	m_rgetcursel = -1;
}

void PropertySheetPitchers::OnNewInitStruct()
{
	CString filler10("          ");

	m_structPitcher.m_PitcherName		= filler10+filler10+filler10+filler10+filler10;
	m_structPitcher.m_PitcherField	= 0;
	m_structPitcher.m_Starter		= 0;
	m_structPitcher.m_Relief		= 0;
	m_structPitcher.m_bWP			= 0;
	m_structPitcher.m_bER1			= 0;
	m_structPitcher.m_bBalk			= 0;
	m_structPitcher.m_Throws		= 0;
	m_structPitcher.m_Hold			= 0;
	m_structPitcher.m_Bunting		= 0;
	m_structPitcher.m_OBChanceBasic		= "0"+filler10;
	m_structPitcher.m_OBChanceLeft		= "0"+filler10;
	m_structPitcher.m_OBChanceRight		= "0"+filler10;
	m_structPitcher.m_OBChanceHomeRun	= "0"+filler10;
	m_structPitcher.m_OBChanceDouble	= "0"+filler10;
	m_structPitcher.m_OBChanceSingle	= "0"+filler10;
	m_structPitcher.m_OBChanceTriple	= "0"+filler10;
	m_structPitcher.m_OBChanceWalk		= "0"+filler10;
	m_structPitcher.m_ChanceDoublePlay	= "0"+filler10;
	m_structPitcher.m_OBChanceHomeRunLeft	= "0"+filler10;
	m_structPitcher.m_OBChanceDoubleLeft	= "0"+filler10;
	m_structPitcher.m_OBChanceSingleLeft	= "0"+filler10;
	m_structPitcher.m_OBChanceTripleLeft	= "0"+filler10;
	m_structPitcher.m_OBChanceWalkLeft		= "0"+filler10;
	m_structPitcher.m_ChanceDoublePlayLeft	= "0"+filler10;
	m_structPitcher.m_OBChanceHomeRunRight	= "0"+filler10;
	m_structPitcher.m_OBChanceDoubleRight	= "0"+filler10;
	m_structPitcher.m_OBChanceSingleRight	= "0"+filler10;
	m_structPitcher.m_OBChanceTripleRight	= "0"+filler10;
	m_structPitcher.m_OBChanceWalkRight		= "0"+filler10;
	m_structPitcher.m_ChanceDoublePlayRight	= "0"+filler10;
	m_structPitcher.m_IP			= "0"+filler10;
	m_structPitcher.m_Starts		= 0;
	m_structPitcher.m_Wins			= 0;
	m_structPitcher.m_Walks			= 0;
	m_structPitcher.m_Strikeouts	= 0;
	m_structPitcher.m_Saves			= 0;
	m_structPitcher.m_Loss			= 0;
	m_structPitcher.m_HomeRuns		= 0;
	m_structPitcher.m_Hits			= 0;
	m_structPitcher.m_ER			= 0;
	m_structPitcher.m_Games			= 0;
	m_structPitcher.m_CompGames		= 0;
}

void PropertySheetPitchers::SetPlayerNameCB(int iPage)
{
	char cTemp[31];
	CString filler10("          ");

	switch (iPage)
	{
	case 1:
		m_pPage1->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		break;
	case 2:
		m_pPage2->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		break;
	case 3:
		m_pPage3->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		break;
	}
	
	cTemp[30]		= NULL;
	m_structPitcher.m_PitcherName	= cTemp+filler10+filler10+filler10+filler10;

	if ((m_pPage1->m_hWnd != 0) && (iPage != 1))
	{
		m_pPage1->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structPitcher.m_PitcherName );
	}
	if ((m_pPage2->m_hWnd != 0) && (iPage != 2))
	{
		m_pPage2->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structPitcher.m_PitcherName );
	}
	if ((m_pPage3->m_hWnd != 0) && (iPage != 3))
	{
		m_pPage3->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structPitcher.m_PitcherName );
	}
}

void PropertySheetPitchers::OnCloseupComboPlayerName(int iPage)
{
	int i, rcompare;
	BYTE count;
	CString csPlayer;
	LONG lTeamSection = sizeof(BYTE);
	LONG lPlayerSection = m_structPitcher.m_RecordSize;
	char buf[10];
	int changed;
	int yesno;
	double fIP;
	double fTRG;
	double fERA;

	// Test for changed pages NOT SURE HOW TO HANDLE NEW PLAYERS
	changed = FALSE;
	if (m_pPage1->m_hWnd != 0)
		changed |= m_pPage1->m_bChangedFlag;
	if (m_pPage2->m_hWnd != 0)
		changed |= m_pPage2->m_bChangedFlag;
	if (m_pPage3->m_hWnd != 0)
		changed |= m_pPage3->m_bChangedFlag;
	if (changed == TRUE)
	{
		// Display a window asking to save changed data
		yesno = AfxMessageBox("Pitcher information has changed, Do you want to save it?",
			MB_YESNO,0);
		switch (yesno)
		{
		case IDYES:
			SendMessage(WM_APP1);	// Update requested, wait for return from update
			break;
		case IDNO:
			break;
		}
		// Now reset the changed flags
		if (m_pPage1->m_hWnd != 0)
			m_pPage1->m_bChangedFlag = FALSE;
		if (m_pPage2->m_hWnd != 0)
			m_pPage2->m_bChangedFlag = FALSE;
		if (m_pPage3->m_hWnd != 0)
			m_pPage3->m_bChangedFlag = FALSE;
	}

	switch (iPage)
	{
	case 1:
		m_rgetcursel = m_pPage1->m_comboPlayerName.GetCurSel();
		if ( m_rgetcursel != CB_ERR )
			m_pPage1->m_comboPlayerName.GetLBText( m_rgetcursel, m_rString );
		m_newFlag = FALSE;
		break;
	case 2:
		m_rgetcursel = m_pPage2->m_comboPlayerName.GetCurSel();
		if ( m_rgetcursel != CB_ERR )
			m_pPage2->m_comboPlayerName.GetLBText( m_rgetcursel, m_rString );
		m_newFlag = FALSE;
		break;
	case 3:
		m_rgetcursel = m_pPage3->m_comboPlayerName.GetCurSel();
		if ( m_rgetcursel != CB_ERR )
			m_pPage3->m_comboPlayerName.GetLBText( m_rgetcursel, m_rString );
		m_newFlag = FALSE;
		break;
	default:	// If call other that 1 - 3, then just load variables
		break;
	}
	if (m_rgetcursel != CB_ERR)
	{
		count = m_structPitcher.GetCountPitcher(m_FileName);
		csPlayer.Empty();
		rcompare = m_rString.Compare(csPlayer);
		i = -1;
		while (rcompare)
		{
			i++;
			if (i >= count)
			{
				// Player compare failed so display message
				AfxMessageBox("Player Compare Failed");
				break;
			}
			// Read in the player Data
			m_lSeekPlayerFile = lTeamSection+(i*lPlayerSection);
			m_structPitcher.GetPitcher(m_FileName,m_lSeekPlayerFile);
			csPlayer = m_structPitcher.m_PitcherName;
			rcompare = m_rString.Compare(csPlayer);
		}

		// Read in the player Data
		m_structPitcher.GetPitcher(m_FileName,m_lSeekPlayerFile);
		// Set the Dialog Items for page 1
		if ((m_pPage1->m_hWnd != 0) && (m_pPage1->m_bChangedFlag == FALSE))
		{
			m_pPage1->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage1->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structPitcher.m_PitcherName );
			m_pPage1->SetDlgItemInt( IDC_STARTER1, m_structPitcher.m_Starter, FALSE );
			m_pPage1->SetDlgItemInt( IDC_RELIEF1, m_structPitcher.m_Relief, FALSE );
			m_pPage1->SetDlgItemInt( IDC_PITCHER, m_structPitcher.m_PitcherField, FALSE );
			m_pPage1->SetDlgItemInt( IDC_WP, m_structPitcher.m_bWP, FALSE );
			m_pPage1->SetDlgItemInt( IDC_ERP, m_structPitcher.m_bER1, FALSE );
			m_pPage1->SetDlgItemInt( IDC_BALK, m_structPitcher.m_bBalk, FALSE );
			m_pPage1->m_comboThrows.SetCurSel(m_structPitcher.m_Throws);
			m_pPage1->m_comboHold.SetCurSel(m_structPitcher.m_Hold);
			m_pPage1->m_comboBunting.SetCurSel(m_structPitcher.m_Bunting);
			m_pPage1->m_bChangedFlag = FALSE;
		}

		if ((m_pPage2->m_hWnd != 0) && (m_pPage2->m_bChangedFlag == FALSE))
		{
			m_pPage2->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage2->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structPitcher.m_PitcherName );
			m_pPage2->SetDlgItemText( IDC_CHANCEBASIC, m_structPitcher.m_OBChanceBasic );
			m_pPage2->SetDlgItemText( IDC_CHANCELEFT, m_structPitcher.m_OBChanceLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCERIGHT, m_structPitcher.m_OBChanceRight );
			m_pPage2->SetDlgItemText( IDC_CHANCEHR, m_structPitcher.m_OBChanceHomeRun );
			m_pPage2->SetDlgItemText( IDC_CHANCEDOUBLE, m_structPitcher.m_OBChanceDouble );
			m_pPage2->SetDlgItemText( IDC_CHANCESINGLE, m_structPitcher.m_OBChanceSingle );
			m_pPage2->SetDlgItemText( IDC_CHANCETRIPLE, m_structPitcher.m_OBChanceTriple );
			m_pPage2->SetDlgItemText( IDC_CHANCEWALK, m_structPitcher.m_OBChanceWalk );
			m_pPage2->SetDlgItemText( IDC_CHANCEDOUBLEPLAY, m_structPitcher.m_ChanceDoublePlay );
			m_pPage2->SetDlgItemText( IDC_CHANCEHRL, m_structPitcher.m_OBChanceHomeRunLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCEDOUBLEL, m_structPitcher.m_OBChanceDoubleLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCESINGLEL, m_structPitcher.m_OBChanceSingleLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCETRIPLEL, m_structPitcher.m_OBChanceTripleLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCEWALKL, m_structPitcher.m_OBChanceWalkLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCEDOUBLEPLAYL, m_structPitcher.m_ChanceDoublePlayLeft );
			m_pPage2->SetDlgItemText( IDC_CHANCEHRR, m_structPitcher.m_OBChanceHomeRunRight );
			m_pPage2->SetDlgItemText( IDC_CHANCEDOUBLER, m_structPitcher.m_OBChanceDoubleRight );
			m_pPage2->SetDlgItemText( IDC_CHANCESINGLER, m_structPitcher.m_OBChanceSingleRight );
			m_pPage2->SetDlgItemText( IDC_CHANCETRIPLER, m_structPitcher.m_OBChanceTripleRight );
			m_pPage2->SetDlgItemText( IDC_CHANCEWALKR, m_structPitcher.m_OBChanceWalkRight );
			m_pPage2->SetDlgItemText( IDC_CHANCEDOUBLEPLAYR, m_structPitcher.m_ChanceDoublePlayRight );
			m_pPage2->m_bChangedFlag = FALSE;
		}

		if ((m_pPage3->m_hWnd != 0) && (m_pPage3->m_bChangedFlag == FALSE))
		{
			m_pPage3->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage3->SetDlgItemText( IDC_COMBO_PLAYERNAME1, m_structPitcher.m_PitcherName );
			m_pPage3->SetDlgItemText( IDC_IP1, m_structPitcher.m_IP );
			m_pPage3->SetDlgItemInt( IDC_STARTS1, m_structPitcher.m_Starts, FALSE );
			m_pPage3->SetDlgItemInt( IDC_WINS1, m_structPitcher.m_Wins, FALSE );
			m_pPage3->SetDlgItemInt( IDC_WALK1, m_structPitcher.m_Walks, FALSE );
			m_pPage3->SetDlgItemInt( IDC_STRIKEOUT1, m_structPitcher.m_Strikeouts, FALSE );
			m_pPage3->SetDlgItemInt( IDC_SAVES1, m_structPitcher.m_Saves, FALSE );
			m_pPage3->SetDlgItemInt( IDC_LOSS1, m_structPitcher.m_Loss, FALSE );
			m_pPage3->SetDlgItemInt( IDC_HR1, m_structPitcher.m_HomeRuns, FALSE );
			m_pPage3->SetDlgItemInt( IDC_HITS1, m_structPitcher.m_Hits, FALSE );
			m_pPage3->SetDlgItemInt( IDC_ER1, m_structPitcher.m_ER, FALSE );
			m_pPage3->SetDlgItemInt( IDC_GAMES1, m_structPitcher.m_Games, FALSE );
			m_pPage3->SetDlgItemInt( IDC_COMPLETEGAMES1, m_structPitcher.m_CompGames, FALSE );

			fIP = atof(m_structPitcher.m_IP);

			if (fIP == 0)
			{
				m_pPage3->SetDlgItemText( IDC_ERA1, "0" );
				m_pPage3->SetDlgItemText( IDC_TRG1, "0" );
			}
			else
			{
				fERA = (double)(m_structPitcher.m_ER*9)/fIP;
				sprintf_s(buf,"%1.2f",fERA);
				m_pPage3->SetDlgItemText( IDC_ERA1, buf );
				fTRG = (double)((m_structPitcher.m_Hits+m_structPitcher.m_Walks)*9)/fIP;
				sprintf_s(buf,"%1.2f",fTRG);
				m_pPage3->SetDlgItemText( IDC_TRG1, buf );
			}

			m_pPage3->m_bChangedFlag = FALSE;
		}
		m_flagNew = FALSE;
	}
	else
	{
		// No player selected Edit Box being used, set seek to 0 as flag
		m_lSeekPlayerFile = 0;
	}
}

LRESULT PropertySheetPitchers::OnOK(WPARAM wParam, LPARAM lParam)
{
	EndDialog(IDOK);
	return (LRESULT)0;
}

LRESULT PropertySheetPitchers::OnCancel(WPARAM wParam, LPARAM lParam)
{
	EndDialog(IDCANCEL);
	return (LRESULT)0;
}

LRESULT PropertySheetPitchers::OnUpdate(WPARAM wParam, LPARAM lParam)
{
	BOOL rc_GetDlgItemInt;
	char cTemp[31];
	CString filler10("          ");
	char buf[10];
	double fIP;
	double fTRG;
	double fERA;

	if (m_pPage1->m_hWnd != 0)
	{
		m_pPage1->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		cTemp[30]		= NULL;
		m_structPitcher.m_PitcherName	= cTemp+filler10+filler10+filler10+filler10;
		m_structPitcher.m_PitcherField	= m_pPage1->GetDlgItemInt( IDC_PITCHER, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_Starter	= m_pPage1->GetDlgItemInt( IDC_STARTER1, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_Relief	= m_pPage1->GetDlgItemInt( IDC_RELIEF1, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_bWP		= m_pPage1->GetDlgItemInt( IDC_WP, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_bER1		= m_pPage1->GetDlgItemInt( IDC_ERP, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_bBalk		= m_pPage1->GetDlgItemInt( IDC_BALK, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_Throws	= m_pPage1->m_comboThrows.GetCurSel();
		m_structPitcher.m_Hold		= m_pPage1->m_comboHold.GetCurSel();
		m_structPitcher.m_Bunting	= m_pPage1->m_comboBunting.GetCurSel();
		m_pPage1->m_bChangedFlag	= FALSE;
	}
	if (m_pPage2->m_hWnd != 0)
	{
		m_pPage2->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		cTemp[30]		= NULL;
		m_structPitcher.m_PitcherName		= cTemp+filler10+filler10+filler10+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEBASIC, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceBasic		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCELEFT, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceLeft		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCERIGHT, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceRight		= cTemp+filler10;

		m_pPage2->GetDlgItemText( IDC_CHANCEHR, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceHomeRun	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLE, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceDouble	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCESINGLE, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceSingle	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCETRIPLE, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceTriple	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEWALK, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceWalk		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEPLAY, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_ChanceDoublePlay	= cTemp+filler10;

		m_pPage2->GetDlgItemText( IDC_CHANCEHRL, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceHomeRunLeft	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEL, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceDoubleLeft	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCESINGLEL, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceSingleLeft	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCETRIPLEL, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceTripleLeft	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEWALKL, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceWalkLeft		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEPLAYL, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_ChanceDoublePlayLeft	= cTemp+filler10;

		m_pPage2->GetDlgItemText( IDC_CHANCEHRR, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceHomeRunRight	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLER, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceDoubleRight	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCESINGLER, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceSingleRight	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCETRIPLER, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceTripleRight	= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEWALKR, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_OBChanceWalkRight		= cTemp+filler10;
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEPLAYR, cTemp, 6 );
		cTemp[6]		= NULL;
		m_structPitcher.m_ChanceDoublePlayRight	= cTemp+filler10;

		m_pPage2->m_bChangedFlag		= FALSE;
	}
	if (m_pPage3->m_hWnd != 0)
	{
		m_pPage3->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		cTemp[30]		= NULL;
		m_structPitcher.m_PitcherName		= cTemp+filler10+filler10+filler10+filler10;
		m_pPage3->GetDlgItemText( IDC_IP1, cTemp, 7 );
		cTemp[7]		= NULL;
		m_structPitcher.m_IP		= cTemp;
		m_structPitcher.m_Starts	= m_pPage3->GetDlgItemInt( IDC_STARTS1, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_Wins		= m_pPage3->GetDlgItemInt( IDC_WINS1, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_Walks		= m_pPage3->GetDlgItemInt( IDC_WALK1, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_Strikeouts	= m_pPage3->GetDlgItemInt( IDC_STRIKEOUT1, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_Saves		= m_pPage3->GetDlgItemInt( IDC_SAVES1, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_Loss		= m_pPage3->GetDlgItemInt( IDC_LOSS1, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_HomeRuns	= m_pPage3->GetDlgItemInt( IDC_HR1, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_Hits		= m_pPage3->GetDlgItemInt( IDC_HITS1, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_ER		= m_pPage3->GetDlgItemInt( IDC_ER1, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_Games		= m_pPage3->GetDlgItemInt( IDC_GAMES1, &rc_GetDlgItemInt, FALSE );
		m_structPitcher.m_CompGames	= m_pPage3->GetDlgItemInt( IDC_COMPLETEGAMES1, &rc_GetDlgItemInt, FALSE );
		m_pPage3->m_bChangedFlag	= FALSE;
	}

	// Open file and update player
	if (m_flagNew == TRUE)
	{
		m_structPitcher.AddPitcher(m_FileName);
		m_flagNew = FALSE;
	}
	else
	{
		if (m_lSeekPlayerFile!=0)
		{
			{
				m_structPitcher.UpdatePitcher(m_FileName,m_lSeekPlayerFile);
			}

			if (m_pPage3->m_hWnd != 0)
			{
				fIP = atof(m_structPitcher.m_IP);

				if (fIP == 0)
				{
					m_pPage3->SetDlgItemText( IDC_ERA1, "0" );
					m_pPage3->SetDlgItemText( IDC_TRG1, "0" );
				}
				else
				{
					fERA = (double)(m_structPitcher.m_ER*9)/fIP;
					sprintf_s(buf,"%1.2f",fERA);
					m_pPage3->SetDlgItemText( IDC_ERA1, buf );
					fTRG = (double)((m_structPitcher.m_Hits+m_structPitcher.m_Walks)*9)/fIP;
					sprintf_s(buf,"%1.2f",fTRG);
					m_pPage3->SetDlgItemText( IDC_TRG1, buf );
				}
			}
		}
	}
	// ReBuild combo table for player display
	if (m_pPage1->m_hWnd != 0)
	{
		BuildPlayerNameComboBox(1);
	}
	if (m_pPage2->m_hWnd != 0)
	{
		BuildPlayerNameComboBox(2);
	}
	if (m_pPage3->m_hWnd != 0)
	{
		BuildPlayerNameComboBox(3);
	}
	return (LRESULT)0;
}

/////////////////////////////////////////////////////////////////////////////
// PropertyPageTeamHTMLOptions property page
// Black = "#000000"
// Silver = "#C0C0C0"
// Gray = "#808080"
// White = "#FFFFFF"
// Maroon = "#800000"
// Red = "#FF0000"
// Purple = "#800080"
// Fuchsia = "#FF00FF"
// Green = "#008000" 
// Lime = "#00FF00" 
// Olive = "#808000"
// Yellow = "#FFFF00" 
// Navy = "#000080" 
// Blue = "#0000FF" 
// Teal = "#008080" 
// Aqua = "#00FFFF" 
//
// Hyperlink Defaults:
//		to Blue initially LINK
//		to Red when activated ALINK
//		to Purple when viewed VLINK
//		Black for TEXT
//		White for BGColor

IMPLEMENT_DYNCREATE(PropertyPageTeamHTMLOptions, CPropertyPage)

PropertyPageTeamHTMLOptions::PropertyPageTeamHTMLOptions() : CPropertyPage(PropertyPageTeamHTMLOptions::IDD)
{
	//{{AFX_DATA_INIT(PropertyPageTeamHTMLOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

PropertyPageTeamHTMLOptions::~PropertyPageTeamHTMLOptions()
{
}

void PropertyPageTeamHTMLOptions::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropertyPageTeamHTMLOptions)
	DDX_Control(pDX, IDC_INDEX, m_ceditIndex);
	DDX_Control(pDX, IDC_COMBOVLINKCOLOR, m_comboVLinkColor);
	DDX_Control(pDX, IDC_COMBOTEXTCOLOR, m_comboTextColor);
	DDX_Control(pDX, IDC_COMBOLINKCOLOR, m_comboLinkColor);
	DDX_Control(pDX, IDC_COMBOBGCOLOR, m_comboBGColor);
	DDX_Control(pDX, IDC_BACKGROUNDPICTURE, m_ceditBackgroundPicture);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PropertyPageTeamHTMLOptions, CPropertyPage)
	//{{AFX_MSG_MAP(PropertyPageTeamHTMLOptions)
	ON_CBN_SELENDOK(IDC_COMBOBGCOLOR, OnSelEndOKComboxBGColor)
	ON_CBN_SELENDOK(IDC_COMBOLINKCOLOR, OnSelendOKComboxLinkColor)
	ON_CBN_SELENDOK(IDC_COMBOTEXTCOLOR, OnSelEndOKComboTextColor)
	ON_CBN_SELENDOK(IDC_COMBOVLINKCOLOR, OnSelEndOKComboxVlinkColor)
	ON_EN_CHANGE(IDC_BACKGROUNDPICTURE, OnChangeBackgroundPicture)
	ON_EN_CHANGE(IDC_INDEX, OnChangeIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertyPageTeamHTMLOptions message handlers

void PropertyPageTeamHTMLOptions::OnOK() 
{
	CString strLinkColor;
	CString strVLinkColor;
	CString strTextColor;
	CString strBGColor;
	CString strIndex;
	CString strBackgroundPicture;

	Registry myReg(m_strLeagueDir + REGTEAMS);

	m_comboLinkColor.GetLBText( m_comboLinkColor.GetCurSel(), strLinkColor );
	myReg.SetRegistryOptionLinkColor(strLinkColor);
	m_comboLinkColor.GetLBText( m_comboVLinkColor.GetCurSel(), strVLinkColor );
	myReg.SetRegistryOptionVLinkColor(strVLinkColor);
	m_comboLinkColor.GetLBText( m_comboTextColor.GetCurSel(), strTextColor );
	myReg.SetRegistryOptionTextColor(strTextColor);
	m_comboLinkColor.GetLBText( m_comboBGColor.GetCurSel(), strBGColor );
	myReg.SetRegistryOptionBGColor(strBGColor);
	m_ceditIndex.GetWindowText(strIndex);
	myReg.SetRegistryOptionIndex(strIndex);
	m_ceditBackgroundPicture.GetWindowText(strBackgroundPicture);
	myReg.SetRegistryOptionBackgroundPicture(strBackgroundPicture);
	
	CPropertyPage::OnOK();
}

void PropertyPageTeamHTMLOptions::OnSelEndOKComboxBGColor() 
{
	SetModified( TRUE );
}

void PropertyPageTeamHTMLOptions::OnSelendOKComboxLinkColor() 
{
	SetModified( TRUE );
}

void PropertyPageTeamHTMLOptions::OnSelEndOKComboTextColor() 
{
	SetModified( TRUE );
}

void PropertyPageTeamHTMLOptions::OnSelEndOKComboxVlinkColor() 
{
	SetModified( TRUE );
}

void PropertyPageTeamHTMLOptions::OnChangeBackgroundPicture() 
{
	SetModified( TRUE );
}

void PropertyPageTeamHTMLOptions::OnChangeIndex() 
{
	SetModified( TRUE );
}

BOOL PropertyPageTeamHTMLOptions::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString myColors;

	Registry myReg(m_strLeagueDir + REGTEAMS);

	myColors = myReg.GetRegistryOptionLinkColor();
	m_comboLinkColor.SetCurSel( m_comboLinkColor.FindStringExact( -1, myColors ) );

	myColors = myReg.GetRegistryOptionVLinkColor();
	m_comboVLinkColor.SetCurSel( m_comboVLinkColor.FindStringExact( -1, myColors ) );

	myColors = myReg.GetRegistryOptionTextColor();
	m_comboTextColor.SetCurSel( m_comboTextColor.FindStringExact( -1, myColors ) );

	myColors = myReg.GetRegistryOptionBGColor();
	m_comboBGColor.SetCurSel( m_comboBGColor.FindStringExact( -1, myColors ) );

	myColors = myReg.GetRegistryOptionBackgroundPicture();
	m_ceditBackgroundPicture.SetWindowText(myColors);

	myColors = myReg.GetRegistryOptionIndex();
	m_ceditIndex.SetWindowText(myColors);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// PropertyPageLeagueHTMLOptions property page

IMPLEMENT_DYNCREATE(PropertyPageLeagueHTMLOptions, CPropertyPage)

PropertyPageLeagueHTMLOptions::PropertyPageLeagueHTMLOptions() : CPropertyPage(PropertyPageLeagueHTMLOptions::IDD)
{
	//{{AFX_DATA_INIT(PropertyPageLeagueHTMLOptions)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

PropertyPageLeagueHTMLOptions::~PropertyPageLeagueHTMLOptions()
{
}

void PropertyPageLeagueHTMLOptions::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PropertyPageLeagueHTMLOptions)
	DDX_Control(pDX, IDC_INDEX, m_ceditIndex);
	DDX_Control(pDX, IDC_COMBOVLINKCOLOR, m_comboVLinkColor);
	DDX_Control(pDX, IDC_COMBOTEXTCOLOR, m_comboTextColor);
	DDX_Control(pDX, IDC_COMBOLINKCOLOR, m_comboLinkColor);
	DDX_Control(pDX, IDC_COMBOBGCOLOR, m_comboBGColor);
	DDX_Control(pDX, IDC_BACKGROUNDPICTURE, m_ceditBackgroundPicture);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(PropertyPageLeagueHTMLOptions, CPropertyPage)
	//{{AFX_MSG_MAP(PropertyPageLeagueHTMLOptions)
	ON_CBN_SELENDOK(IDC_COMBOBGCOLOR, OnSelEndOKComboxBGColor)
	ON_CBN_SELENDOK(IDC_COMBOLINKCOLOR, OnSelEndOKComboxLinkColor)
	ON_CBN_SELENDOK(IDC_COMBOTEXTCOLOR, OnSelEndOKComboxTextColor)
	ON_CBN_SELENDOK(IDC_COMBOVLINKCOLOR, OnSelEndOKComboxVlinkColor)
	ON_EN_CHANGE(IDC_BACKGROUNDPICTURE, OnChangeBackgroundPicture)
	ON_EN_CHANGE(IDC_INDEX, OnChangeIndex)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertyPageLeagueHTMLOptions message handlers

void PropertyPageLeagueHTMLOptions::OnOK() 
{
	CString strLinkColor;
	CString strVLinkColor;
	CString strTextColor;
	CString strBGColor;
	CString strIndex;
	CString strBackgroundPicture;

	Registry myReg(m_strLeagueDir + REGLEAGUE);

	m_comboLinkColor.GetLBText( m_comboLinkColor.GetCurSel(), strLinkColor );
	myReg.SetRegistryOptionLinkColor(strLinkColor);
	m_comboLinkColor.GetLBText( m_comboVLinkColor.GetCurSel(), strVLinkColor );
	myReg.SetRegistryOptionVLinkColor(strVLinkColor);
	m_comboLinkColor.GetLBText( m_comboTextColor.GetCurSel(), strTextColor );
	myReg.SetRegistryOptionTextColor(strTextColor);
	m_comboLinkColor.GetLBText( m_comboBGColor.GetCurSel(), strBGColor );
	myReg.SetRegistryOptionBGColor(strBGColor);
	m_ceditIndex.GetWindowText(strIndex);
	myReg.SetRegistryOptionIndex(strIndex);
	m_ceditBackgroundPicture.GetWindowText(strBackgroundPicture);
	myReg.SetRegistryOptionBackgroundPicture(strBackgroundPicture);
	
	CPropertyPage::OnOK();
}

BOOL PropertyPageLeagueHTMLOptions::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString myColors;

	Registry myReg(m_strLeagueDir + REGLEAGUE);

	myColors = myReg.GetRegistryOptionLinkColor();
	m_comboLinkColor.SetCurSel( m_comboLinkColor.FindStringExact( -1, myColors ) );

	myColors = myReg.GetRegistryOptionVLinkColor();
	m_comboVLinkColor.SetCurSel( m_comboVLinkColor.FindStringExact( -1, myColors ) );

	myColors = myReg.GetRegistryOptionTextColor();
	m_comboTextColor.SetCurSel( m_comboTextColor.FindStringExact( -1, myColors ) );

	myColors = myReg.GetRegistryOptionBGColor();
	m_comboBGColor.SetCurSel( m_comboBGColor.FindStringExact( -1, myColors ) );

	myColors = myReg.GetRegistryOptionBackgroundPicture();
	m_ceditBackgroundPicture.SetWindowText(myColors);

	myColors = myReg.GetRegistryOptionIndex();
	m_ceditIndex.SetWindowText(myColors);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PropertyPageLeagueHTMLOptions::OnSelEndOKComboxBGColor() 
{
	SetModified( TRUE );
}

void PropertyPageLeagueHTMLOptions::OnSelEndOKComboxLinkColor() 
{
	SetModified( TRUE );
}

void PropertyPageLeagueHTMLOptions::OnSelEndOKComboxTextColor() 
{
	SetModified( TRUE );
}

void PropertyPageLeagueHTMLOptions::OnSelEndOKComboxVlinkColor() 
{
	SetModified( TRUE );
}

void PropertyPageLeagueHTMLOptions::OnChangeBackgroundPicture() 
{
	SetModified( TRUE );
}

void PropertyPageLeagueHTMLOptions::OnChangeIndex() 
{
	SetModified( TRUE );
}

/////////////////////////////////////////////////////////////////////////////
// PropertySheetLeagueOptions

IMPLEMENT_DYNAMIC(PropertySheetLeagueOptions, CPropertySheet)

PropertySheetLeagueOptions::PropertySheetLeagueOptions(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
}

PropertySheetLeagueOptions::PropertySheetLeagueOptions(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
}

PropertySheetLeagueOptions::~PropertySheetLeagueOptions()
{
}


BEGIN_MESSAGE_MAP(PropertySheetLeagueOptions, CPropertySheet)
	//{{AFX_MSG_MAP(PropertySheetLeagueOptions)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PropertySheetLeagueOptions message handlers
