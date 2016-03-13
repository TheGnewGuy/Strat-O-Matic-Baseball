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
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP4); // Add Button Pressed

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
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP4); // Add Button Pressed

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
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP4); // Add Button Pressed

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
	SetDlgItemText( IDC_CHANCEBASIC, _T("0") );
	SetDlgItemText( IDC_CHANCELEFT, _T("0") );
	SetDlgItemText( IDC_CHANCERIGHT, _T("0") );
	SetDlgItemText( IDC_CHANCEWALK, _T("0") );
	SetDlgItemText( IDC_CHANCETRIPLE, _T("0") );
	SetDlgItemText( IDC_CHANCESINGLE, _T("0") );
	SetDlgItemText( IDC_CHANCEHR, _T("0") );
	SetDlgItemText( IDC_CHANCEDOUBLE, _T("0") );
	SetDlgItemText( IDC_CHANCEDOUBLEPLAY, _T("0") );
	SetDlgItemText( IDC_CHANCEWALKL, _T("0") );
	SetDlgItemText( IDC_CHANCETRIPLEL, _T("0") );
	SetDlgItemText( IDC_CHANCESINGLEL, _T("0") );
	SetDlgItemText( IDC_CHANCEHRL, _T("0") );
	SetDlgItemText( IDC_CHANCEDOUBLEL, _T("0") );
	SetDlgItemText( IDC_CHANCEDOUBLEPLAYL, _T("0") );
	SetDlgItemText( IDC_CHANCEWALKR, _T("0") );
	SetDlgItemText( IDC_CHANCETRIPLER, _T("0") );
	SetDlgItemText( IDC_CHANCESINGLER, _T("0") );
	SetDlgItemText( IDC_CHANCEHRR, _T("0") );
	SetDlgItemText( IDC_CHANCEDOUBLER, _T("0") );
	SetDlgItemText( IDC_CHANCEDOUBLEPLAYR, _T("0") );
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
	m_TeamID = 0;
	m_BatterStatsID = 0;

	// Get pointer to Doc
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *)pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window.
	CBaseballView *pView = (CBaseballView *)pChild->GetActiveView();
	m_pDocVoid = pView->GetDocument();
}

PropertySheetBatters::PropertySheetBatters(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_rgetcursel = -1;
	m_newFlag = FALSE;
	m_TeamID = 0;

	m_BatterStatsID = 0;

	// Get pointer to Doc
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *)pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window.
	CBaseballView *pView = (CBaseballView *)pChild->GetActiveView();
	m_pDocVoid = pView->GetDocument();

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
	ON_MESSAGE(WM_APP4, &PropertySheetBatters::OnAdd)
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
	m_structBatter.m_OBChanceBasic		= _T("0")+filler10;
	m_structBatter.m_OBChanceLeft		= _T("0")+filler10;
	m_structBatter.m_OBChanceRight		= _T("0")+filler10;
	m_structBatter.m_OBChanceHomeRun	= _T("0")+filler10;
	m_structBatter.m_OBChanceDouble		= _T("0")+filler10;
	m_structBatter.m_OBChanceSingle		= _T("0")+filler10;
	m_structBatter.m_OBChanceTriple		= _T("0")+filler10;
	m_structBatter.m_OBChanceWalk		= _T("0")+filler10;
	m_structBatter.m_ChanceDoublePlay	= _T("0")+filler10;
	m_structBatter.m_OBChanceHomeRunLeft	= _T("0")+filler10;
	m_structBatter.m_OBChanceDoubleLeft		= _T("0")+filler10;
	m_structBatter.m_OBChanceSingleLeft		= _T("0")+filler10;
	m_structBatter.m_OBChanceTripleLeft		= _T("0")+filler10;
	m_structBatter.m_OBChanceWalkLeft		= _T("0")+filler10;
	m_structBatter.m_ChanceDoublePlayLeft	= _T("0")+filler10;
	m_structBatter.m_OBChanceHomeRunRight	= _T("0")+filler10;
	m_structBatter.m_OBChanceDoubleRight	= _T("0")+filler10;
	m_structBatter.m_OBChanceSingleRight	= _T("0")+filler10;
	m_structBatter.m_OBChanceTripleRight	= _T("0")+filler10;
	m_structBatter.m_OBChanceWalkRight		= _T("0")+filler10;
	m_structBatter.m_ChanceDoublePlayRight	= _T("0")+filler10;
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
	char buf[10];
	CBaseballDoc::m_BatterStatsRecord batterStatsRecord;
	CBaseballDoc::m_BatterRecord batterRecord;
	CBaseballDoc::m_TeamRecord teamRecord;

	CBaseballDoc* pDoc = (CBaseballDoc*)m_pDocVoid;

	// Read in the player Data so data is present for update
	batterStatsRecord = pDoc->GetBatterStats(m_BatterStatsID);
	batterRecord = pDoc->GetBatter(batterStatsRecord.BatterID);
	teamRecord = pDoc->GetTeam(m_TeamID);

	if (m_pPage1->m_hWnd != 0)
	{
		m_pPage1->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		m_structBatter.m_PlayerName = cTemp;
		batterRecord.Pitcher = m_pPage1->GetDlgItemInt(IDC_PITCHER, &rc_GetDlgItemInt, FALSE);
		batterRecord.Catcher = m_pPage1->GetDlgItemInt(IDC_CATCHER, &rc_GetDlgItemInt, FALSE);
		batterRecord.FirstBase = m_pPage1->GetDlgItemInt(IDC_FIRSTBASE, &rc_GetDlgItemInt, FALSE);
		batterRecord.SecondBase = m_pPage1->GetDlgItemInt(IDC_SECONDBASE, &rc_GetDlgItemInt, FALSE);
		batterRecord.ShortStop = m_pPage1->GetDlgItemInt(IDC_SHORTSTOP, &rc_GetDlgItemInt, FALSE);
		batterRecord.ThirdBase = m_pPage1->GetDlgItemInt(IDC_THIRDBASE, &rc_GetDlgItemInt, FALSE);
		batterRecord.LeftField = m_pPage1->GetDlgItemInt(IDC_LEFTFIELD, &rc_GetDlgItemInt, FALSE);
		batterRecord.CenterField = m_pPage1->GetDlgItemInt(IDC_CENTERFIELD, &rc_GetDlgItemInt, FALSE);
		batterRecord.RightField = m_pPage1->GetDlgItemInt(IDC_RIGHTFIELD, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER1 = m_pPage1->GetDlgItemInt(IDC_ERP, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER2 = m_pPage1->GetDlgItemInt(IDC_ERC, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER3 = m_pPage1->GetDlgItemInt(IDC_ER1B, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER4 = m_pPage1->GetDlgItemInt(IDC_ER2B, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER5 = m_pPage1->GetDlgItemInt(IDC_ER3B, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER6 = m_pPage1->GetDlgItemInt(IDC_ERSS, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER7 = m_pPage1->GetDlgItemInt(IDC_ERLF, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER8 = m_pPage1->GetDlgItemInt(IDC_ERCF, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER9 = m_pPage1->GetDlgItemInt(IDC_ERRF, &rc_GetDlgItemInt, FALSE);
		m_pPage1->m_bChangedFlag	= FALSE;
	}
	if (m_pPage2->m_hWnd != 0)
	{
		m_pPage2->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		m_structBatter.m_PlayerName = cTemp;
		m_pPage2->GetDlgItemText(IDC_CHANCEBASIC, cTemp, 6);
		batterRecord.OBChanceBasic = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCELEFT, cTemp, 6 );
		batterRecord.OBChanceLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCERIGHT, cTemp, 6 );
		batterRecord.OBChanceRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEHR, cTemp, 6 );
		batterRecord.OBChanceHomeRun = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLE, cTemp, 6 );
		batterRecord.OBChanceDouble = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCESINGLE, cTemp, 6 );
		batterRecord.OBChanceSingle = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCETRIPLE, cTemp, 6 );
		batterRecord.OBChanceTriple = (float)_ttof(cTemp);;
		m_pPage2->GetDlgItemText( IDC_CHANCEWALK, cTemp, 6 );
		batterRecord.OBChanceWalk = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEPLAY, cTemp, 6 );
		batterRecord.ChanceDoublePlay = (float)_ttof(cTemp);

		m_pPage2->GetDlgItemText( IDC_CHANCEHRR, cTemp, 6 );
		batterRecord.OBChanceHomeRunRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLER, cTemp, 6 );
		batterRecord.OBChanceDoubleRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCESINGLER, cTemp, 6 );
		batterRecord.OBChanceSingleRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCETRIPLER, cTemp, 6 );
		batterRecord.OBChanceTripleRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEWALKR, cTemp, 6 );
		batterRecord.OBChanceWalkRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEPLAYR, cTemp, 6 );
		batterRecord.ChanceDoublePlayRight = (float)_ttof(cTemp);

		m_pPage2->GetDlgItemText( IDC_CHANCEHRL, cTemp, 6 );
		batterRecord.OBChanceHomeRunLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEL, cTemp, 6 );
		batterRecord.OBChanceDoubleLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCESINGLEL, cTemp, 6 );
		batterRecord.OBChanceSingleLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCETRIPLEL, cTemp, 6 );
		batterRecord.OBChanceTripleLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEWALKL, cTemp, 6 );
		batterRecord.OBChanceWalkLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEPLAYL, cTemp, 6 );
		batterRecord.ChanceDoublePlayLeft = (float)_ttof(cTemp);

		m_pPage2->m_bChangedFlag		= FALSE;
	}
	if (m_pPage3->m_hWnd != 0)
	{
		m_pPage3->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		m_structBatter.m_PlayerName = cTemp;
		batterStatsRecord.AB = m_pPage3->GetDlgItemInt(IDC_AB1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Runs = m_pPage3->GetDlgItemInt(IDC_RUNS1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Hits = m_pPage3->GetDlgItemInt(IDC_HITS1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.RBI = m_pPage3->GetDlgItemInt(IDC_RBI1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Doubles = m_pPage3->GetDlgItemInt(IDC_2B1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Triples = m_pPage3->GetDlgItemInt(IDC_3B1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.HomeRuns = m_pPage3->GetDlgItemInt(IDC_HR1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Walk = m_pPage3->GetDlgItemInt(IDC_WALK1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Stirkeout = m_pPage3->GetDlgItemInt(IDC_STRIKEOUT1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.ReachedOnError = m_pPage3->GetDlgItemInt(IDC_REACHEDONERROR1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Sacrifice = m_pPage3->GetDlgItemInt(IDC_SACRICIFE1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.StolenBase = m_pPage3->GetDlgItemInt(IDC_STOLENBASE1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.CS = m_pPage3->GetDlgItemInt(IDC_CS1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.HBP = m_pPage3->GetDlgItemInt(IDC_HBP1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Games = m_pPage3->GetDlgItemInt(IDC_GAMES2, &rc_GetDlgItemInt, FALSE);
		if (batterStatsRecord.AB == 0)
		{
			batterStatsRecord.AVG = 0.0f;
			batterStatsRecord.SLG = 0.0f;
			batterStatsRecord.OBP = 0.0f;
		}
		else
		{
			batterStatsRecord.AVG = (float)batterStatsRecord.Hits / batterStatsRecord.AB;
			batterStatsRecord.SLG = (float)((batterStatsRecord.Hits - (batterStatsRecord.Doubles + batterStatsRecord.Triples + batterStatsRecord.HomeRuns)) + (2 * batterStatsRecord.Doubles) + (3 * batterStatsRecord.Triples) + (4 * batterStatsRecord.HomeRuns)) / (batterStatsRecord.AB);
			batterStatsRecord.OBP = (float)(batterStatsRecord.Hits + batterStatsRecord.Walk + batterStatsRecord.ReachedOnError + batterStatsRecord.Sacrifice) / (batterStatsRecord.AB + batterStatsRecord.Walk + batterStatsRecord.ReachedOnError + batterStatsRecord.Sacrifice);
		}
		m_pPage3->m_bChangedFlag = FALSE;
	}
	if (m_pPage4->m_hWnd != 0)
	{
		m_pPage4->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		m_structBatter.m_PlayerName = cTemp;
		batterRecord.Bunting = m_pPage4->m_comboBunting.GetCurSel();
		batterRecord.Stealing = m_pPage4->m_comboStealing.GetCurSel();
		batterRecord.Running = m_pPage4->m_comboRunning.GetCurSel();
		batterRecord.HitRun = m_pPage4->m_comboHitRun.GetCurSel();
		batterRecord.BatterHits = m_pPage4->m_comboBatterHits.GetCurSel();
		batterRecord.CatchArm = m_pPage4->m_comboCatcherArm.GetCurSel();
		batterRecord.OutArm = m_pPage4->m_comboOutArm.GetCurSel();
		batterRecord.Pass = m_pPage4->m_comboPassBall.GetCurSel();
		batterRecord.PowerLeft = m_pPage4->m_comboPowerLeft.GetCurSel();
		batterRecord.PowerRight = m_pPage4->m_comboPowerRight.GetCurSel();
		batterRecord.TRate = m_pPage4->m_comboTRate.GetCurSel();
		m_pPage4->GetDlgItemText(IDC_FIRSTNAME1, cTemp, 30);
		batterRecord.FirstName = cTemp;
		m_pPage4->GetDlgItemText(IDC_LASTNAME1, cTemp, 30);
		batterRecord.LastName = cTemp;

		m_pPage4->m_bChangedFlag		= FALSE;
	}

	// Open file and update player
	if (m_flagNew == TRUE)
	{
		//m_structBatter.AddBatter(m_FileName);
		m_flagNew = FALSE;
	}
	else
	{
		// Only update the Batter record if this is a BASE team.
		if (teamRecord.BaseTeam == 1)
		{
			pDoc->BatterStatsUpdate(batterStatsRecord);
			pDoc->BatterUpdate(batterRecord);
		}
		else
		{
			// We still could be updating the BASE stats record.
			pDoc->BatterStatsUpdate(batterStatsRecord);
		}

		if (m_pPage3->m_hWnd != 0)
		{
			if (batterStatsRecord.AB == 0)
			{
				m_pPage3->SetDlgItemText( IDC_BATTINGAVERAGE, _T("0") );
				m_pPage3->SetDlgItemText( IDC_SLG, _T("0") );
				m_pPage3->SetDlgItemText( IDC_ONBASEPERCENT, _T("0") );
				m_pPage3->m_bChangedFlag		= FALSE;
			}
			else
			{
				m_fBattingAverage = (float)batterStatsRecord.Hits / batterStatsRecord.AB;
				sprintf_s(buf,"%1.3f",m_fBattingAverage);
				m_pPage3->SetDlgItemText( IDC_BATTINGAVERAGE, buf );
				m_fSLG = (float)((batterStatsRecord.Hits - (batterStatsRecord.Doubles + batterStatsRecord.Triples + batterStatsRecord.HomeRuns)) + (2 * batterStatsRecord.Doubles) + (3 * batterStatsRecord.Triples) + (4 * batterStatsRecord.HomeRuns)) / (batterStatsRecord.AB);
				sprintf_s(buf,"%1.3f",m_fSLG);
				m_pPage3->SetDlgItemText( IDC_SLG, buf );
				m_fOnBasePercentage = (float)(batterStatsRecord.Hits + batterStatsRecord.Walk + batterStatsRecord.ReachedOnError + batterStatsRecord.Sacrifice) / (batterStatsRecord.AB + batterStatsRecord.Walk + batterStatsRecord.ReachedOnError + batterStatsRecord.Sacrifice);
				sprintf_s(buf,"%1.3f",m_fOnBasePercentage);
				m_pPage3->SetDlgItemText( IDC_ONBASEPERCENT, buf );
				m_pPage3->m_bChangedFlag		= FALSE;
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

// Handler for Button click od WM_APP4
afx_msg LRESULT PropertySheetBatters::OnAdd(WPARAM wParam, LPARAM lParam)
{
	BOOL rc_GetDlgItemInt;
	char cTemp[31];
	char buf[10];
	CBaseballDoc::m_BatterStatsRecord batterStatsRecord;
	CBaseballDoc::m_BatterRecord batterRecord;
	CBaseballDoc::m_TeamRecord teamRecord;

	CBaseballDoc* pDoc = (CBaseballDoc*)m_pDocVoid;

	// Read in the player Data so data is present for update
	//batterStatsRecord = pDoc->GetBatterStats(m_BatterStatsID);
	//batterRecord = pDoc->GetBatter(batterStatsRecord.BatterID);
	teamRecord = pDoc->GetTeam(m_TeamID);

	if (m_pPage1->m_hWnd != 0)
	{
		m_pPage1->GetDlgItemText(IDC_COMBO_PLAYERNAME1, cTemp, 30);
		m_structBatter.m_PlayerName = cTemp;
		batterRecord.Pitcher = m_pPage1->GetDlgItemInt(IDC_PITCHER, &rc_GetDlgItemInt, FALSE);
		batterRecord.Catcher = m_pPage1->GetDlgItemInt(IDC_CATCHER, &rc_GetDlgItemInt, FALSE);
		batterRecord.FirstBase = m_pPage1->GetDlgItemInt(IDC_FIRSTBASE, &rc_GetDlgItemInt, FALSE);
		batterRecord.SecondBase = m_pPage1->GetDlgItemInt(IDC_SECONDBASE, &rc_GetDlgItemInt, FALSE);
		batterRecord.ShortStop = m_pPage1->GetDlgItemInt(IDC_SHORTSTOP, &rc_GetDlgItemInt, FALSE);
		batterRecord.ThirdBase = m_pPage1->GetDlgItemInt(IDC_THIRDBASE, &rc_GetDlgItemInt, FALSE);
		batterRecord.LeftField = m_pPage1->GetDlgItemInt(IDC_LEFTFIELD, &rc_GetDlgItemInt, FALSE);
		batterRecord.CenterField = m_pPage1->GetDlgItemInt(IDC_CENTERFIELD, &rc_GetDlgItemInt, FALSE);
		batterRecord.RightField = m_pPage1->GetDlgItemInt(IDC_RIGHTFIELD, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER1 = m_pPage1->GetDlgItemInt(IDC_ERP, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER2 = m_pPage1->GetDlgItemInt(IDC_ERC, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER3 = m_pPage1->GetDlgItemInt(IDC_ER1B, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER4 = m_pPage1->GetDlgItemInt(IDC_ER2B, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER5 = m_pPage1->GetDlgItemInt(IDC_ER3B, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER6 = m_pPage1->GetDlgItemInt(IDC_ERSS, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER7 = m_pPage1->GetDlgItemInt(IDC_ERLF, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER8 = m_pPage1->GetDlgItemInt(IDC_ERCF, &rc_GetDlgItemInt, FALSE);
		batterRecord.ER9 = m_pPage1->GetDlgItemInt(IDC_ERRF, &rc_GetDlgItemInt, FALSE);
		m_pPage1->m_bChangedFlag = FALSE;
	}
	if (m_pPage2->m_hWnd != 0)
	{
		m_pPage2->GetDlgItemText(IDC_COMBO_PLAYERNAME1, cTemp, 30);
		m_structBatter.m_PlayerName = cTemp;
		m_pPage2->GetDlgItemText(IDC_CHANCEBASIC, cTemp, 6);
		batterRecord.OBChanceBasic = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCELEFT, cTemp, 6);
		batterRecord.OBChanceLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCERIGHT, cTemp, 6);
		batterRecord.OBChanceRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCEHR, cTemp, 6);
		batterRecord.OBChanceHomeRun = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCEDOUBLE, cTemp, 6);
		batterRecord.OBChanceDouble = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCESINGLE, cTemp, 6);
		batterRecord.OBChanceSingle = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCETRIPLE, cTemp, 6);
		batterRecord.OBChanceTriple = (float)_ttof(cTemp);;
		m_pPage2->GetDlgItemText(IDC_CHANCEWALK, cTemp, 6);
		batterRecord.OBChanceWalk = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCEDOUBLEPLAY, cTemp, 6);
		batterRecord.ChanceDoublePlay = (float)_ttof(cTemp);

		m_pPage2->GetDlgItemText(IDC_CHANCEHRR, cTemp, 6);
		batterRecord.OBChanceHomeRunRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCEDOUBLER, cTemp, 6);
		batterRecord.OBChanceDoubleRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCESINGLER, cTemp, 6);
		batterRecord.OBChanceSingleRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCETRIPLER, cTemp, 6);
		batterRecord.OBChanceTripleRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCEWALKR, cTemp, 6);
		batterRecord.OBChanceWalkRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCEDOUBLEPLAYR, cTemp, 6);
		batterRecord.ChanceDoublePlayRight = (float)_ttof(cTemp);

		m_pPage2->GetDlgItemText(IDC_CHANCEHRL, cTemp, 6);
		batterRecord.OBChanceHomeRunLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCEDOUBLEL, cTemp, 6);
		batterRecord.OBChanceDoubleLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCESINGLEL, cTemp, 6);
		batterRecord.OBChanceSingleLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCETRIPLEL, cTemp, 6);
		batterRecord.OBChanceTripleLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCEWALKL, cTemp, 6);
		batterRecord.OBChanceWalkLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText(IDC_CHANCEDOUBLEPLAYL, cTemp, 6);
		batterRecord.ChanceDoublePlayLeft = (float)_ttof(cTemp);

		m_pPage2->m_bChangedFlag = FALSE;
	}
	if (m_pPage3->m_hWnd != 0)
	{
		m_pPage3->GetDlgItemText(IDC_COMBO_PLAYERNAME1, cTemp, 30);
		m_structBatter.m_PlayerName = cTemp;
		batterStatsRecord.AB = m_pPage3->GetDlgItemInt(IDC_AB1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Runs = m_pPage3->GetDlgItemInt(IDC_RUNS1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Hits = m_pPage3->GetDlgItemInt(IDC_HITS1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.RBI = m_pPage3->GetDlgItemInt(IDC_RBI1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Doubles = m_pPage3->GetDlgItemInt(IDC_2B1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Triples = m_pPage3->GetDlgItemInt(IDC_3B1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.HomeRuns = m_pPage3->GetDlgItemInt(IDC_HR1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Walk = m_pPage3->GetDlgItemInt(IDC_WALK1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Stirkeout = m_pPage3->GetDlgItemInt(IDC_STRIKEOUT1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.ReachedOnError = m_pPage3->GetDlgItemInt(IDC_REACHEDONERROR1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Sacrifice = m_pPage3->GetDlgItemInt(IDC_SACRICIFE1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.StolenBase = m_pPage3->GetDlgItemInt(IDC_STOLENBASE1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.CS = m_pPage3->GetDlgItemInt(IDC_CS1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.HBP = m_pPage3->GetDlgItemInt(IDC_HBP1, &rc_GetDlgItemInt, FALSE);
		batterStatsRecord.Games = m_pPage3->GetDlgItemInt(IDC_GAMES2, &rc_GetDlgItemInt, FALSE);
		if (batterStatsRecord.AB == 0)
		{
			batterStatsRecord.AVG = 0.0f;
			batterStatsRecord.SLG = 0.0f;
			batterStatsRecord.OBP = 0.0f;
		}
		else
		{
			batterStatsRecord.AVG = (float)batterStatsRecord.Hits / batterStatsRecord.AB;
			batterStatsRecord.SLG = (float)((batterStatsRecord.Hits - (batterStatsRecord.Doubles + batterStatsRecord.Triples + batterStatsRecord.HomeRuns)) + (2 * batterStatsRecord.Doubles) + (3 * batterStatsRecord.Triples) + (4 * batterStatsRecord.HomeRuns)) / (batterStatsRecord.AB);
			batterStatsRecord.OBP = (float)(batterStatsRecord.Hits + batterStatsRecord.Walk + batterStatsRecord.ReachedOnError + batterStatsRecord.Sacrifice) / (batterStatsRecord.AB + batterStatsRecord.Walk + batterStatsRecord.ReachedOnError + batterStatsRecord.Sacrifice);
		}
		m_pPage3->m_bChangedFlag = FALSE;
	}
	if (m_pPage4->m_hWnd != 0)
	{
		m_pPage4->GetDlgItemText(IDC_COMBO_PLAYERNAME1, cTemp, 30);
		m_structBatter.m_PlayerName = cTemp;
		batterRecord.Bunting = m_pPage4->m_comboBunting.GetCurSel();
		batterRecord.Stealing = m_pPage4->m_comboStealing.GetCurSel();
		batterRecord.Running = m_pPage4->m_comboRunning.GetCurSel();
		batterRecord.HitRun = m_pPage4->m_comboHitRun.GetCurSel();
		batterRecord.BatterHits = m_pPage4->m_comboBatterHits.GetCurSel();
		batterRecord.CatchArm = m_pPage4->m_comboCatcherArm.GetCurSel();
		batterRecord.OutArm = m_pPage4->m_comboOutArm.GetCurSel();
		batterRecord.Pass = m_pPage4->m_comboPassBall.GetCurSel();
		batterRecord.PowerLeft = m_pPage4->m_comboPowerLeft.GetCurSel();
		batterRecord.PowerRight = m_pPage4->m_comboPowerRight.GetCurSel();
		batterRecord.TRate = m_pPage4->m_comboTRate.GetCurSel();
		m_pPage4->GetDlgItemText(IDC_FIRSTNAME1, cTemp, 30);
		batterRecord.FirstName = cTemp;
		m_pPage4->GetDlgItemText(IDC_LASTNAME1, cTemp, 30);
		batterRecord.LastName = cTemp;

		m_pPage4->m_bChangedFlag = FALSE;
	}

	// Open file and update player
	if (m_flagNew == TRUE)
	{
		//m_structBatter.AddBatter(m_FileName);
		batterRecord.TeamID = m_TeamID;
		batterStatsRecord.TeamID = m_TeamID;
		pDoc->BatterAdd(batterRecord);
		// Need to retrieve batter ID that was just created, maybe first and last name with teamID
		batterStatsRecord.BatterID = pDoc->GetBatter(teamRecord.TeamID, batterRecord.FirstName, batterRecord.LastName);
		pDoc->BatterStatsAdd(batterStatsRecord);
		m_flagNew = FALSE;
	}
	else
	{
		// If this is a base team, then add the batter and batterstats records.
		if (teamRecord.BaseTeam == 1)
		{
			pDoc->BatterAdd(batterRecord);
			// Need to retrieve batter ID that was just created, maybe first and last name with teamID
			batterStatsRecord.BatterID = pDoc->GetBatter(teamRecord.TeamID, batterRecord.FirstName, batterRecord.LastName);
			pDoc->BatterStatsAdd(batterStatsRecord);
		}
		else
		{
			// We still could be updating the BASE stats record.
			//pDoc->BatterStatsAdd(batterStatsRecord);
		}

		if (m_pPage3->m_hWnd != 0)
		{
			if (batterStatsRecord.AB == 0)
			{
				m_pPage3->SetDlgItemText(IDC_BATTINGAVERAGE, _T("0"));
				m_pPage3->SetDlgItemText(IDC_SLG, _T("0"));
				m_pPage3->SetDlgItemText(IDC_ONBASEPERCENT, _T("0"));
				m_pPage3->m_bChangedFlag = FALSE;
			}
			else
			{
				m_fBattingAverage = (float)batterStatsRecord.Hits / batterStatsRecord.AB;
				sprintf_s(buf, "%1.3f", m_fBattingAverage);
				m_pPage3->SetDlgItemText(IDC_BATTINGAVERAGE, buf);
				m_fSLG = (float)((batterStatsRecord.Hits - (batterStatsRecord.Doubles + batterStatsRecord.Triples + batterStatsRecord.HomeRuns)) + (2 * batterStatsRecord.Doubles) + (3 * batterStatsRecord.Triples) + (4 * batterStatsRecord.HomeRuns)) / (batterStatsRecord.AB);
				sprintf_s(buf, "%1.3f", m_fSLG);
				m_pPage3->SetDlgItemText(IDC_SLG, buf);
				m_fOnBasePercentage = (float)(batterStatsRecord.Hits + batterStatsRecord.Walk + batterStatsRecord.ReachedOnError + batterStatsRecord.Sacrifice) / (batterStatsRecord.AB + batterStatsRecord.Walk + batterStatsRecord.ReachedOnError + batterStatsRecord.Sacrifice);
				sprintf_s(buf, "%1.3f", m_fOnBasePercentage);
				m_pPage3->SetDlgItemText(IDC_ONBASEPERCENT, buf);
				m_pPage3->m_bChangedFlag = FALSE;
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
	CString	strPlayerName;	// Length of 30
	char *sqlBatterStats;
	int rc;
	CHAR buffer[100];
	CString strFirstName;
	CString strLastName;

	CBaseballDoc* pDoc = (CBaseballDoc*)m_pDocVoid;

	// If needed save Player Name
	if (m_flagNew == TRUE)
		strPlayerName = m_structBatter.m_PlayerName;

	/* Create SQL statement */
	sqlBatterStats = "SELECT "  \
		"FirstName," \
		"LastName " \
		" FROM BATTERSTATS AS S " \
		" JOIN BATTER AS B " \
		" ON S.BatterID=B.BatterID " \
		" WHERE S.TeamID = ?1 ";

	rc = sqlite3_prepare_v2(pDoc->m_db, sqlBatterStats, strlen(sqlBatterStats), &pDoc->m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(pDoc->m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS JOIN Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(pDoc->m_stmt, 1, m_TeamID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(pDoc->m_db));
		AfxMessageBox(buffer);
	}

	// Build player ComboBox
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

	// Need to loop through each batter and extract their names
	while (sqlite3_step(pDoc->m_stmt) == SQLITE_ROW)
	{
		strFirstName = sqlite3_column_text(pDoc->m_stmt, 0);
		strLastName = sqlite3_column_text(pDoc->m_stmt, 1);
		switch (iPage)
		{
		case 1:
//			m_pPage1->m_comboPlayerName.AddString(m_structBatter.m_PlayerName);
			m_pPage1->m_comboPlayerName.AddString(strFirstName + _T(" ") + strLastName);
			break;
		case 2:
			m_pPage2->m_comboPlayerName.AddString(strFirstName + _T(" ") + strLastName);
			break;
		case 3:
			m_pPage3->m_comboPlayerName.AddString(strFirstName + _T(" ") + strLastName);
			break;
		case 4:
			m_pPage4->m_comboPlayerName.AddString(strFirstName + _T(" ") + strLastName);
			break;
		}
	}

	sqlite3_finalize(pDoc->m_stmt);

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
	int rcompare;
	char buf[10];
	int changed;
	int yesno;
	char *sqlBatterStats;
	int rc;
	int rcSqlStep = 0;
	CHAR buffer[100];
	CString csPlayer;
	CString strFirstName;
	CString strLastName;
	CBaseballDoc::m_BatterStatsRecord batterStatsRecord;
	CBaseballDoc::m_BatterRecord batterRecord;

	CBaseballDoc* pDoc = (CBaseballDoc*)m_pDocVoid;

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

		/* Create SQL statement */
		sqlBatterStats = "SELECT "  \
			"S.BatterStatsID, " \
			"B.FirstName," \
			"B.LastName " \
			" FROM BATTERSTATS AS S " \
			" JOIN BATTER AS B " \
			" ON S.BatterID=B.BatterID " \
			" WHERE S.TeamID = ?1 ";

		rc = sqlite3_prepare_v2(pDoc->m_db, sqlBatterStats, strlen(sqlBatterStats), &pDoc->m_stmt, 0);
		if (rc != SQLITE_OK)
		{
			sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(pDoc->m_db));
			AfxMessageBox(buffer);
		}
		else
		{
			sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS JOIN Select OK:\n");
			//AfxMessageBox(buffer);
		}
		// Bind the data to field '1' which is the first '?' in the INSERT statement
		rc = sqlite3_bind_int(pDoc->m_stmt, 1, m_TeamID);
		if (rc != SQLITE_OK)
		{
			sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(pDoc->m_db));
			AfxMessageBox(buffer);
		}

		csPlayer.Empty();
		rcompare = m_rString.Compare(csPlayer);
		while (rcompare)
		{
			rcSqlStep = sqlite3_step(pDoc->m_stmt);
			while (rcSqlStep == SQLITE_ROW)
			{
				m_BatterStatsID = sqlite3_column_int(pDoc->m_stmt, 0);
				strFirstName = sqlite3_column_text(pDoc->m_stmt, 1);
				strLastName = sqlite3_column_text(pDoc->m_stmt, 2);
				csPlayer = strFirstName + _T(" ") + strLastName;
				rcompare = m_rString.Compare(csPlayer);
				if (rcompare == 0) break;
				rcSqlStep = sqlite3_step(pDoc->m_stmt);
			}
			if (rcSqlStep != SQLITE_ROW)
			{
				// Player compare failed so display message
				AfxMessageBox("Player Compare Failed");
				break;
			}
		}

		sqlite3_finalize(pDoc->m_stmt);

		// Read in the player Data
		batterStatsRecord = pDoc->GetBatterStats(m_BatterStatsID);
		batterRecord = pDoc->GetBatter(batterStatsRecord.BatterID);

		// Set the Dialog Items for page 1
		if ((m_pPage1->m_hWnd != 0) && (m_pPage1->m_bChangedFlag == FALSE))
		{
			m_pPage1->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage1->SetDlgItemText(IDC_COMBO_PLAYERNAME1, batterRecord.FirstName + _T(" ") + batterRecord.LastName);
			m_pPage1->SetDlgItemInt(IDC_PITCHER, batterRecord.Pitcher, FALSE);
			m_pPage1->SetDlgItemInt(IDC_CATCHER, batterRecord.Catcher, FALSE);
			m_pPage1->SetDlgItemInt(IDC_FIRSTBASE, batterRecord.FirstBase, FALSE);
			m_pPage1->SetDlgItemInt(IDC_SECONDBASE, batterRecord.SecondBase, FALSE);
			m_pPage1->SetDlgItemInt(IDC_SHORTSTOP, batterRecord.ShortStop, FALSE);
			m_pPage1->SetDlgItemInt(IDC_THIRDBASE, batterRecord.ThirdBase, FALSE);
			m_pPage1->SetDlgItemInt(IDC_LEFTFIELD, batterRecord.LeftField, FALSE);
			m_pPage1->SetDlgItemInt(IDC_CENTERFIELD, batterRecord.CenterField, FALSE);
			m_pPage1->SetDlgItemInt(IDC_RIGHTFIELD, batterRecord.RightField, FALSE);
			m_pPage1->SetDlgItemInt(IDC_ERP, batterRecord.ER1, FALSE);
			m_pPage1->SetDlgItemInt(IDC_ERC, batterRecord.ER2, FALSE);
			m_pPage1->SetDlgItemInt(IDC_ER1B, batterRecord.ER3, FALSE);
			m_pPage1->SetDlgItemInt(IDC_ER2B, batterRecord.ER4, FALSE);
			m_pPage1->SetDlgItemInt(IDC_ER3B, batterRecord.ER5, FALSE);
			m_pPage1->SetDlgItemInt(IDC_ERSS, batterRecord.ER6, FALSE);
			m_pPage1->SetDlgItemInt(IDC_ERLF, batterRecord.ER7, FALSE);
			m_pPage1->SetDlgItemInt(IDC_ERCF, batterRecord.ER8, FALSE);
			m_pPage1->SetDlgItemInt(IDC_ERRF, batterRecord.ER9, FALSE);
			m_pPage1->m_bChangedFlag = FALSE;
		}

		if ((m_pPage2->m_hWnd != 0) && (m_pPage2->m_bChangedFlag == FALSE))
		{
			m_pPage2->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage2->SetDlgItemText(IDC_COMBO_PLAYERNAME1, batterRecord.FirstName + _T(" ") + batterRecord.LastName);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceBasic);
			m_pPage2->SetDlgItemText(IDC_CHANCEBASIC, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCELEFT, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceRight);
			m_pPage2->SetDlgItemText(IDC_CHANCERIGHT, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceHomeRun);
			m_pPage2->SetDlgItemText(IDC_CHANCEHR, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceDouble);
			m_pPage2->SetDlgItemText(IDC_CHANCEDOUBLE, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceSingle);
			m_pPage2->SetDlgItemText(IDC_CHANCESINGLE, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceTriple);
			m_pPage2->SetDlgItemText(IDC_CHANCETRIPLE, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceWalk);
			m_pPage2->SetDlgItemText(IDC_CHANCEWALK, buf);
			sprintf_s(buf, "%2.2f", batterRecord.ChanceDoublePlay);
			m_pPage2->SetDlgItemText(IDC_CHANCEDOUBLEPLAY, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceHomeRunLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCEHRL, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceDoubleLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCEDOUBLEL, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceSingleLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCESINGLEL, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceTripleLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCETRIPLEL, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceWalkLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCEWALKL, buf);
			sprintf_s(buf, "%2.2f", batterRecord.ChanceDoublePlayLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCEDOUBLEPLAYL, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceHomeRunRight);
			m_pPage2->SetDlgItemText(IDC_CHANCEHRR, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceDoubleRight);
			m_pPage2->SetDlgItemText(IDC_CHANCEDOUBLER, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceSingleRight);
			m_pPage2->SetDlgItemText(IDC_CHANCESINGLER, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceTripleRight);
			m_pPage2->SetDlgItemText(IDC_CHANCETRIPLER, buf);
			sprintf_s(buf, "%2.2f", batterRecord.OBChanceWalkRight);
			m_pPage2->SetDlgItemText(IDC_CHANCEWALKR, buf);
			sprintf_s(buf, "%2.2f", batterRecord.ChanceDoublePlayRight);
			m_pPage2->SetDlgItemText(IDC_CHANCEDOUBLEPLAYR, buf);
			m_pPage2->m_bChangedFlag = FALSE;
		}

		if ((m_pPage3->m_hWnd != 0) && (m_pPage3->m_bChangedFlag == FALSE))
		{
			m_pPage3->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage3->SetDlgItemText(IDC_COMBO_PLAYERNAME1, batterRecord.FirstName + _T(" ") + batterRecord.LastName);
			m_pPage3->SetDlgItemInt(IDC_AB1, batterStatsRecord.AB, FALSE);
			m_pPage3->SetDlgItemInt(IDC_RUNS1, batterStatsRecord.Runs, FALSE);
			m_pPage3->SetDlgItemInt(IDC_HITS1, batterStatsRecord.Hits, FALSE);
			m_pPage3->SetDlgItemInt(IDC_RBI1, batterStatsRecord.RBI, FALSE);
			m_pPage3->SetDlgItemInt(IDC_2B1, batterStatsRecord.Doubles, FALSE);
			m_pPage3->SetDlgItemInt(IDC_3B1, batterStatsRecord.Triples, FALSE);
			m_pPage3->SetDlgItemInt(IDC_HR1, batterStatsRecord.HomeRuns, FALSE);
			m_pPage3->SetDlgItemInt(IDC_WALK1, batterStatsRecord.Walk, FALSE);
			m_pPage3->SetDlgItemInt(IDC_STRIKEOUT1, batterStatsRecord.Stirkeout, FALSE);
			m_pPage3->SetDlgItemInt(IDC_REACHEDONERROR1, batterStatsRecord.ReachedOnError, FALSE);
			m_pPage3->SetDlgItemInt(IDC_SACRICIFE1, batterStatsRecord.Sacrifice, FALSE);
			m_pPage3->SetDlgItemInt(IDC_STOLENBASE1, batterStatsRecord.StolenBase, FALSE);
			m_pPage3->SetDlgItemInt(IDC_CS1, batterStatsRecord.CS, FALSE);
			m_pPage3->SetDlgItemInt(IDC_GAMES2, batterStatsRecord.Games, FALSE);
			m_pPage3->SetDlgItemInt(IDC_HBP1, batterStatsRecord.HBP, FALSE);
			//if (batterStatsRecord.AB == 0)
			//{
			//	m_pPage3->SetDlgItemText( IDC_BATTINGAVERAGE, _T("0") );
			//	m_pPage3->SetDlgItemText( IDC_SLG, _T("0") );
			//	m_pPage3->SetDlgItemText( IDC_ONBASEPERCENT, _T("0") );
			//}
			//else
			//{
				//m_fBattingAverage = (float)batterStatsRecord.Hits / batterStatsRecord.AB;
				//sprintf_s(buf,"%1.3f",m_fBattingAverage);
				sprintf_s(buf, "%1.3f", batterStatsRecord.AVG);
				m_pPage3->SetDlgItemText(IDC_BATTINGAVERAGE, buf);
				//m_fSLG = (float)((batterStatsRecord.Hits - (batterStatsRecord.Doubles + batterStatsRecord.Triples + batterStatsRecord.HomeRuns)) + (2 * batterStatsRecord.Doubles) + (3 * batterStatsRecord.Triples) + (4 * batterStatsRecord.HomeRuns)) / (batterStatsRecord.AB);
				//sprintf_s(buf,"%1.3f",m_fSLG);
				sprintf_s(buf, "%1.3f", batterStatsRecord.SLG);
				m_pPage3->SetDlgItemText(IDC_SLG, buf);
				//m_fOnBasePercentage = (float)(batterStatsRecord.Hits + batterStatsRecord.Walk + batterStatsRecord.ReachedOnError + batterStatsRecord.Sacrifice) / (batterStatsRecord.AB + batterStatsRecord.Walk + batterStatsRecord.ReachedOnError + batterStatsRecord.Sacrifice);
				//sprintf_s(buf,"%1.3f",m_fOnBasePercentage);
				sprintf_s(buf, "%1.3f", batterStatsRecord.OBP);
				m_pPage3->SetDlgItemText(IDC_ONBASEPERCENT, buf);
			//}
			m_pPage3->m_bChangedFlag = FALSE;
		}

		if ((m_pPage4->m_hWnd != 0) && (m_pPage4->m_bChangedFlag == FALSE))
		{
			m_pPage4->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage4->SetDlgItemText(IDC_COMBO_PLAYERNAME1, batterRecord.FirstName + _T(" ") + batterRecord.LastName);
			m_pPage4->m_comboBunting.SetCurSel(batterRecord.Bunting);
			m_pPage4->m_comboStealing.SetCurSel(batterRecord.Stealing);
			m_pPage4->m_comboRunning.SetCurSel(batterRecord.Running);
			m_pPage4->m_comboHitRun.SetCurSel(batterRecord.HitRun);
			m_pPage4->m_comboBatterHits.SetCurSel(batterRecord.BatterHits);
			m_pPage4->m_comboCatcherArm.SetCurSel(batterRecord.CatchArm);
			m_pPage4->m_comboOutArm.SetCurSel(batterRecord.OutArm);
			m_pPage4->m_comboPassBall.SetCurSel(batterRecord.Pass);
			m_pPage4->m_comboPowerLeft.SetCurSel(batterRecord.PowerLeft);
			m_pPage4->m_comboPowerRight.SetCurSel(batterRecord.PowerRight);
			m_pPage4->m_comboTRate.SetCurSel(batterRecord.TRate);
			m_pPage4->SetDlgItemText(IDC_FIRSTNAME1, batterRecord.FirstName);
			m_pPage4->SetDlgItemText(IDC_LASTNAME1, batterRecord.LastName);
			m_pPage4->m_bChangedFlag = FALSE;
		}
		m_flagNew = FALSE;
	}
	else
	{
		// No player selected Edit Box being used, set seek to 0 as flag
		//m_lSeekPlayerFile = 0;
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
	ON_EN_CHANGE(IDC_FIRSTNAME1, &PropertyPageBattersInfo::OnEditChangeFirstname)
	ON_EN_CHANGE(IDC_LASTNAME1, &PropertyPageBattersInfo::OnEditChangeLastname)
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
	pDoc->m_pPropertySheetBatters->PostMessage(WM_APP4); // Add Button Pressed

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
	SetDlgItemText(IDC_FIRSTNAME1, NULL);
	SetDlgItemText(IDC_LASTNAME1, NULL);
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

void PropertyPageBattersInfo::OnEditChangeFirstname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	m_bChangedFlag = TRUE;
}

void PropertyPageBattersInfo::OnEditChangeLastname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
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
	ON_EN_CHANGE(IDC_FIRSTNAME1, &PropertyPagePitchersInfo::OnChangeFirstName)
	ON_EN_CHANGE(IDC_LASTNAME1, &PropertyPagePitchersInfo::OnChangeLastName)
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

void PropertyPagePitchersInfo::OnChangeFirstName()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	m_bChangedFlag = TRUE;
}

void PropertyPagePitchersInfo::OnChangeLastName()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CPropertyPage::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
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
	SetDlgItemText( IDC_CHANCELEFT, _T("0") );
	SetDlgItemText( IDC_CHANCEBASIC, _T("0") );
	SetDlgItemText( IDC_CHANCERIGHT, _T("0") );
	SetDlgItemText( IDC_CHANCEWALK, _T("0") );
	SetDlgItemText( IDC_CHANCETRIPLE, _T("0") );
	SetDlgItemText( IDC_CHANCESINGLE, _T("0") );
	SetDlgItemText( IDC_CHANCEHR, _T("0") );
	SetDlgItemText( IDC_CHANCEDOUBLE, _T("0") );
	SetDlgItemText( IDC_CHANCEDOUBLEPLAY, _T("0") );
	SetDlgItemText( IDC_CHANCEWALKL, _T("0") );
	SetDlgItemText( IDC_CHANCETRIPLEL, _T("0") );
	SetDlgItemText( IDC_CHANCESINGLEL, _T("0") );
	SetDlgItemText( IDC_CHANCEHRL, _T("0") );
	SetDlgItemText( IDC_CHANCEDOUBLEL, _T("0") );
	SetDlgItemText( IDC_CHANCEDOUBLEPLAYL, _T("0") );
	SetDlgItemText( IDC_CHANCEWALKR, _T("0") );
	SetDlgItemText( IDC_CHANCETRIPLER, _T("0") );
	SetDlgItemText( IDC_CHANCESINGLER, _T("0") );
	SetDlgItemText( IDC_CHANCEHRR, _T("0") );
	SetDlgItemText( IDC_CHANCEDOUBLER, _T("0") );
	SetDlgItemText( IDC_CHANCEDOUBLEPLAYR, _T("0") );
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

	// Get pointer to Doc
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *)pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window.
	CBaseballView *pView = (CBaseballView *)pChild->GetActiveView();
	m_pDocVoid = pView->GetDocument();
	m_TeamID = 0;
	m_PitcherStatsID = 0;
}

PropertySheetPitchers::PropertySheetPitchers(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_rgetcursel = -1;
	m_newFlag = FALSE;

	// Get pointer to Doc
	CMDIFrameWnd *pFrame = (CMDIFrameWnd*)AfxGetApp()->m_pMainWnd;
	// Get the active MDI child window.
	CMDIChildWnd *pChild = (CMDIChildWnd *)pFrame->GetActiveFrame();
	// or CMDIChildWnd *pChild = pFrame->MDIGetActive();
	// Get the active view attached to the active MDI child window.
	CBaseballView *pView = (CBaseballView *)pChild->GetActiveView();
	m_pDocVoid = pView->GetDocument();
	m_TeamID = 0;

	m_PitcherStatsID = 0;

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
	CString	strPlayerName;	// Length of 30
	char *sqlPitcherStats;
	int rc;
	CHAR buffer[100];
	CString strFirstName;
	CString strLastName;

	CBaseballDoc* pDoc = (CBaseballDoc*)m_pDocVoid;

	// If needed save Player Name
	if (m_flagNew == TRUE)
		strPlayerName = m_structPitcher.m_PitcherName;

	/* Create SQL statement */
	sqlPitcherStats = "SELECT "  \
		"FirstName," \
		"LastName " \
		" FROM PITCHERSTATS AS S " \
		" JOIN PITCHER AS B " \
		" ON S.PitcherID=B.PitcherID " \
		" WHERE S.TeamID = ?1 ";

	rc = sqlite3_prepare_v2(pDoc->m_db, sqlPitcherStats, strlen(sqlPitcherStats), &pDoc->m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(pDoc->m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS JOIN Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(pDoc->m_stmt, 1, m_TeamID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(pDoc->m_db));
		AfxMessageBox(buffer);
	}

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

	// Need to loop through each batter and extract their names
	while (sqlite3_step(pDoc->m_stmt) == SQLITE_ROW)
	{
		strFirstName = sqlite3_column_text(pDoc->m_stmt, 0);
		strLastName = sqlite3_column_text(pDoc->m_stmt, 1);
		switch (iPage)
		{
		case 1:
			m_pPage1->m_comboPlayerName.AddString(strFirstName + _T(" ") + strLastName);
			break;
		case 2:
			m_pPage2->m_comboPlayerName.AddString(strFirstName + _T(" ") + strLastName);
			break;
		case 3:
			m_pPage3->m_comboPlayerName.AddString(strFirstName + _T(" ") + strLastName);
			break;
		}
	}

	sqlite3_finalize(pDoc->m_stmt);

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
	m_structPitcher.m_OBChanceBasic		= _T("0")+filler10;
	m_structPitcher.m_OBChanceLeft		= _T("0")+filler10;
	m_structPitcher.m_OBChanceRight		= _T("0")+filler10;
	m_structPitcher.m_OBChanceHomeRun	= _T("0")+filler10;
	m_structPitcher.m_OBChanceDouble	= _T("0")+filler10;
	m_structPitcher.m_OBChanceSingle	= _T("0")+filler10;
	m_structPitcher.m_OBChanceTriple	= _T("0")+filler10;
	m_structPitcher.m_OBChanceWalk		= _T("0")+filler10;
	m_structPitcher.m_ChanceDoublePlay	= _T("0")+filler10;
	m_structPitcher.m_OBChanceHomeRunLeft	= _T("0")+filler10;
	m_structPitcher.m_OBChanceDoubleLeft	= _T("0")+filler10;
	m_structPitcher.m_OBChanceSingleLeft	= _T("0")+filler10;
	m_structPitcher.m_OBChanceTripleLeft	= _T("0")+filler10;
	m_structPitcher.m_OBChanceWalkLeft		= _T("0")+filler10;
	m_structPitcher.m_ChanceDoublePlayLeft	= _T("0")+filler10;
	m_structPitcher.m_OBChanceHomeRunRight	= _T("0")+filler10;
	m_structPitcher.m_OBChanceDoubleRight	= _T("0")+filler10;
	m_structPitcher.m_OBChanceSingleRight	= _T("0")+filler10;
	m_structPitcher.m_OBChanceTripleRight	= _T("0")+filler10;
	m_structPitcher.m_OBChanceWalkRight		= _T("0")+filler10;
	m_structPitcher.m_ChanceDoublePlayRight	= _T("0")+filler10;
	m_structPitcher.m_IP			= _T("0")+filler10;
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
	int rcompare;
	CString csPlayer;
	LONG lTeamSection = sizeof(BYTE);
	LONG lPlayerSection = m_structPitcher.m_RecordSize;
	char buf[10];
	int changed;
	int yesno;
	char *sqlPitcherStats;
	int rc;
	int rcSqlStep = 0;
	CHAR buffer[100];
	CString strFirstName;
	CString strLastName;
	CBaseballDoc::m_PitcherStatsRecord pitcherStatsRecord;
	CBaseballDoc::m_PitcherRecord pitcherRecord;

	CBaseballDoc* pDoc = (CBaseballDoc*)m_pDocVoid;

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

		/* Create SQL statement */
		sqlPitcherStats = "SELECT "  \
			"S.PitcherStatsID, " \
			"P.FirstName," \
			"P.LastName " \
			" FROM PITCHERSTATS AS S " \
			" JOIN PITCHER AS P " \
			" ON S.PitcherID=P.PitcherID " \
			" WHERE S.TeamID = ?1 ";

		rc = sqlite3_prepare_v2(pDoc->m_db, sqlPitcherStats, strlen(sqlPitcherStats), &pDoc->m_stmt, 0);
		if (rc != SQLITE_OK)
		{
			sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(pDoc->m_db));
			AfxMessageBox(buffer);
		}
		else
		{
			sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS JOIN Select OK:\n");
			//AfxMessageBox(buffer);
		}
		// Bind the data to field '1' which is the first '?' in the INSERT statement
		rc = sqlite3_bind_int(pDoc->m_stmt, 1, m_TeamID);
		if (rc != SQLITE_OK)
		{
			sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(pDoc->m_db));
			AfxMessageBox(buffer);
		}

		csPlayer.Empty();
		rcompare = m_rString.Compare(csPlayer);
		while (rcompare)
		{
			rcSqlStep = sqlite3_step(pDoc->m_stmt);
			while (rcSqlStep == SQLITE_ROW)
			{
				m_PitcherStatsID = sqlite3_column_int(pDoc->m_stmt, 0);
				strFirstName = sqlite3_column_text(pDoc->m_stmt, 1);
				strLastName = sqlite3_column_text(pDoc->m_stmt, 2);
				csPlayer = strFirstName + _T(" ") + strLastName;
				rcompare = m_rString.Compare(csPlayer);
				if (rcompare == 0) break;
				rcSqlStep = sqlite3_step(pDoc->m_stmt);
			}
			if (rcSqlStep != SQLITE_ROW)
			{
				// Player compare failed so display message
				AfxMessageBox("Player Compare Failed");
				break;
			}
		}

		sqlite3_finalize(pDoc->m_stmt);

		// Read in the player Data
		pitcherStatsRecord = pDoc->GetPitcherStats(m_PitcherStatsID);
		pitcherRecord = pDoc->GetPitcher(pitcherStatsRecord.PitcherID);

		// Set the Dialog Items for page 1
		if ((m_pPage1->m_hWnd != 0) && (m_pPage1->m_bChangedFlag == FALSE))
		{
			m_pPage1->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage1->SetDlgItemText(IDC_COMBO_PLAYERNAME1, pitcherRecord.FirstName + _T(" ") + pitcherRecord.LastName);
			m_pPage1->SetDlgItemText(IDC_FIRSTNAME1, pitcherRecord.FirstName);
			m_pPage1->SetDlgItemText(IDC_LASTNAME1, pitcherRecord.LastName);
			m_pPage1->SetDlgItemInt(IDC_STARTER1, pitcherRecord.Starter, FALSE);
			m_pPage1->SetDlgItemInt(IDC_RELIEF1, pitcherRecord.Relief, FALSE);
			m_pPage1->SetDlgItemInt(IDC_PITCHER, pitcherRecord.Pitcher, FALSE);
			m_pPage1->SetDlgItemInt(IDC_WP, pitcherRecord.WP, FALSE);
			m_pPage1->SetDlgItemInt(IDC_ERP, pitcherRecord.ER1, FALSE);
			m_pPage1->SetDlgItemInt(IDC_BALK, pitcherRecord.Balk, FALSE);
			m_pPage1->m_comboThrows.SetCurSel(pitcherRecord.Throws);
			m_pPage1->m_comboHold.SetCurSel(pitcherRecord.Hold);
			m_pPage1->m_comboBunting.SetCurSel(pitcherRecord.Bunting);
			m_pPage1->m_bChangedFlag = FALSE;
		}

		if ((m_pPage2->m_hWnd != 0) && (m_pPage2->m_bChangedFlag == FALSE))
		{
			m_pPage2->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage2->SetDlgItemText(IDC_COMBO_PLAYERNAME1, pitcherRecord.FirstName + _T(" ") + pitcherRecord.LastName);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceBasic);
			m_pPage2->SetDlgItemText(IDC_CHANCEBASIC, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCELEFT, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceRight);
			m_pPage2->SetDlgItemText(IDC_CHANCERIGHT, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceHomeRun);
			m_pPage2->SetDlgItemText(IDC_CHANCEHR, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceDouble);
			m_pPage2->SetDlgItemText(IDC_CHANCEDOUBLE, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceSingle);
			m_pPage2->SetDlgItemText(IDC_CHANCESINGLE, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceTriple);
			m_pPage2->SetDlgItemText(IDC_CHANCETRIPLE, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceWalk);
			m_pPage2->SetDlgItemText(IDC_CHANCEWALK, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.ChanceDoublePlay);
			m_pPage2->SetDlgItemText(IDC_CHANCEDOUBLEPLAY, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceHomeRunLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCEHRL, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceDoubleLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCEDOUBLEL, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceSingleLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCESINGLEL, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceTripleLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCETRIPLEL, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceWalkLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCEWALKL, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.ChanceDoublePlayLeft);
			m_pPage2->SetDlgItemText(IDC_CHANCEDOUBLEPLAYL, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceHomeRunRight);
			m_pPage2->SetDlgItemText(IDC_CHANCEHRR, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceDoubleRight);
			m_pPage2->SetDlgItemText(IDC_CHANCEDOUBLER, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceSingleRight);
			m_pPage2->SetDlgItemText(IDC_CHANCESINGLER, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceTripleRight);
			m_pPage2->SetDlgItemText(IDC_CHANCETRIPLER, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.OBChanceWalkRight);
			m_pPage2->SetDlgItemText(IDC_CHANCEWALKR, buf);
			sprintf_s(buf, "%2.2f", pitcherRecord.ChanceDoublePlayRight);
			m_pPage2->SetDlgItemText(IDC_CHANCEDOUBLEPLAYR, buf);
			m_pPage2->m_bChangedFlag = FALSE;
		}

		if ((m_pPage3->m_hWnd != 0) && (m_pPage3->m_bChangedFlag == FALSE))
		{
			m_pPage3->m_comboPlayerName.SetCurSel(m_rgetcursel);
			m_pPage3->SetDlgItemText(IDC_COMBO_PLAYERNAME1, pitcherRecord.FirstName + _T(" ") + pitcherRecord.LastName);
			sprintf_s(buf, "%3.2f", pitcherStatsRecord.InningsPitched);
			m_pPage3->SetDlgItemText(IDC_IP1, buf);
			m_pPage3->SetDlgItemInt(IDC_STARTS1, pitcherStatsRecord.Starts, FALSE);
			m_pPage3->SetDlgItemInt(IDC_WINS1, pitcherStatsRecord.Wins, FALSE);
			m_pPage3->SetDlgItemInt(IDC_WALK1, pitcherStatsRecord.Walks, FALSE);
			m_pPage3->SetDlgItemInt(IDC_STRIKEOUT1, pitcherStatsRecord.Strikeouts, FALSE);
			m_pPage3->SetDlgItemInt(IDC_SAVES1, pitcherStatsRecord.Saves, FALSE);
			m_pPage3->SetDlgItemInt(IDC_LOSS1, pitcherStatsRecord.Loss, FALSE);
			m_pPage3->SetDlgItemInt(IDC_HR1, pitcherStatsRecord.HomeRuns, FALSE);
			m_pPage3->SetDlgItemInt(IDC_HITS1, pitcherStatsRecord.Hits, FALSE);
			m_pPage3->SetDlgItemInt(IDC_ER1, pitcherStatsRecord.ER, FALSE);
			m_pPage3->SetDlgItemInt(IDC_GAMES1, pitcherStatsRecord.Games, FALSE);
			m_pPage3->SetDlgItemInt(IDC_COMPLETEGAMES1, pitcherStatsRecord.CompleteGames, FALSE);
			sprintf_s(buf, "%1.2f", pitcherStatsRecord.ERA);
			m_pPage3->SetDlgItemText(IDC_ERA1, buf);
			sprintf_s(buf, "%1.2f", pitcherStatsRecord.WHIP);
			m_pPage3->SetDlgItemText(IDC_TRG1, buf);

			//fIP = atof(m_structPitcher.m_IP);

			//if (fIP == 0)
			//{
			//	m_pPage3->SetDlgItemText( IDC_ERA1, _T("0") );
			//	m_pPage3->SetDlgItemText( IDC_TRG1, _T("0") );
			//}
			//else
			//{
			//	fERA = (double)(m_structPitcher.m_ER*9)/fIP;
			//	sprintf_s(buf,"%1.2f",fERA);
			//	m_pPage3->SetDlgItemText( IDC_ERA1, buf );
			//	fTRG = (double)((m_structPitcher.m_Hits+m_structPitcher.m_Walks)*9)/fIP;
			//	sprintf_s(buf,"%1.2f",fTRG);
			//	m_pPage3->SetDlgItemText( IDC_TRG1, buf );
			//}

			m_pPage3->m_bChangedFlag = FALSE;
		}
		m_flagNew = FALSE;
	}
	else
	{
		// No player selected Edit Box being used, set seek to 0 as flag
		//m_lSeekPlayerFile = 0;
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
	//double fIP;
	double fTRG;
	double fERA;
	CBaseballDoc::m_PitcherStatsRecord pitcherStatsRecord;
	CBaseballDoc::m_PitcherRecord pitcherRecord;
	CBaseballDoc::m_TeamRecord teamRecord;

	CBaseballDoc* pDoc = (CBaseballDoc*)m_pDocVoid;

	// Read in the player Data so data is present for update
	pitcherStatsRecord = pDoc->GetPitcherStats(m_PitcherStatsID);
	pitcherRecord = pDoc->GetPitcher(pitcherStatsRecord.PitcherID);
	teamRecord = pDoc->GetTeam(m_TeamID);


	if (m_pPage1->m_hWnd != 0)
	{
		m_pPage1->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		m_structPitcher.m_PitcherName	= cTemp;
		m_pPage1->GetDlgItemText(IDC_FIRSTNAME1, cTemp, 30);
		pitcherRecord.FirstName = cTemp;
		m_pPage1->GetDlgItemText(IDC_LASTNAME1, cTemp, 30);
		pitcherRecord.LastName = cTemp;
		pitcherRecord.Pitcher = m_pPage1->GetDlgItemInt(IDC_PITCHER, &rc_GetDlgItemInt, FALSE);
		pitcherRecord.Starter = m_pPage1->GetDlgItemInt(IDC_STARTER1, &rc_GetDlgItemInt, FALSE);
		pitcherRecord.Relief = m_pPage1->GetDlgItemInt(IDC_RELIEF1, &rc_GetDlgItemInt, FALSE);
		pitcherRecord.WP = m_pPage1->GetDlgItemInt(IDC_WP, &rc_GetDlgItemInt, FALSE);
		pitcherRecord.ER1 = m_pPage1->GetDlgItemInt(IDC_ERP, &rc_GetDlgItemInt, FALSE);
		pitcherRecord.Balk = m_pPage1->GetDlgItemInt(IDC_BALK, &rc_GetDlgItemInt, FALSE);
		pitcherRecord.Throws = m_pPage1->m_comboThrows.GetCurSel();
		pitcherRecord.Hold = m_pPage1->m_comboHold.GetCurSel();
		pitcherRecord.Bunting = m_pPage1->m_comboBunting.GetCurSel();
		m_pPage1->m_bChangedFlag	= FALSE;
	}
	if (m_pPage2->m_hWnd != 0)
	{
		m_pPage2->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		m_structPitcher.m_PitcherName		= cTemp;
		m_pPage2->GetDlgItemText( IDC_CHANCEBASIC, cTemp, 6 );
		pitcherRecord.OBChanceBasic = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCELEFT, cTemp, 6 );
		pitcherRecord.OBChanceLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCERIGHT, cTemp, 6 );
		pitcherRecord.OBChanceRight = (float)_ttof(cTemp);

		m_pPage2->GetDlgItemText( IDC_CHANCEHR, cTemp, 6 );
		pitcherRecord.OBChanceHomeRun = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLE, cTemp, 6 );
		pitcherRecord.OBChanceDouble = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCESINGLE, cTemp, 6 );
		pitcherRecord.OBChanceSingle = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCETRIPLE, cTemp, 6 );
		pitcherRecord.OBChanceTriple = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEWALK, cTemp, 6 );
		pitcherRecord.OBChanceWalk = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEPLAY, cTemp, 6 );
		pitcherRecord.ChanceDoublePlay = (float)_ttof(cTemp);

		m_pPage2->GetDlgItemText( IDC_CHANCEHRL, cTemp, 6 );
		pitcherRecord.OBChanceHomeRunLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEL, cTemp, 6 );
		pitcherRecord.OBChanceDoubleLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCESINGLEL, cTemp, 6 );
		pitcherRecord.OBChanceSingleLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCETRIPLEL, cTemp, 6 );
		pitcherRecord.OBChanceTripleLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEWALKL, cTemp, 6 );
		pitcherRecord.OBChanceWalkLeft = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEPLAYL, cTemp, 6 );
		pitcherRecord.ChanceDoublePlayLeft = (float)_ttof(cTemp);

		m_pPage2->GetDlgItemText( IDC_CHANCEHRR, cTemp, 6 );
		pitcherRecord.OBChanceHomeRunRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLER, cTemp, 6 );
		pitcherRecord.OBChanceDoubleRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCESINGLER, cTemp, 6 );
		pitcherRecord.OBChanceSingleRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCETRIPLER, cTemp, 6 );
		pitcherRecord.OBChanceTripleRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEWALKR, cTemp, 6 );
		pitcherRecord.OBChanceWalkRight = (float)_ttof(cTemp);
		m_pPage2->GetDlgItemText( IDC_CHANCEDOUBLEPLAYR, cTemp, 6 );
		pitcherRecord.ChanceDoublePlayRight = (float)_ttof(cTemp);

		m_pPage2->m_bChangedFlag		= FALSE;
	}
	if (m_pPage3->m_hWnd != 0)
	{
		m_pPage3->GetDlgItemText( IDC_COMBO_PLAYERNAME1, cTemp, 30 );
		m_structPitcher.m_PitcherName		= cTemp;
		m_pPage3->GetDlgItemText(IDC_IP1, cTemp, 7);
		pitcherStatsRecord.InningsPitched = (float)_ttof(cTemp);
		pitcherStatsRecord.Starts = m_pPage3->GetDlgItemInt(IDC_STARTS1, &rc_GetDlgItemInt, FALSE);
		pitcherStatsRecord.Wins = m_pPage3->GetDlgItemInt(IDC_WINS1, &rc_GetDlgItemInt, FALSE);
		pitcherStatsRecord.Walks = m_pPage3->GetDlgItemInt(IDC_WALK1, &rc_GetDlgItemInt, FALSE);
		pitcherStatsRecord.Strikeouts = m_pPage3->GetDlgItemInt(IDC_STRIKEOUT1, &rc_GetDlgItemInt, FALSE);
		pitcherStatsRecord.Saves = m_pPage3->GetDlgItemInt(IDC_SAVES1, &rc_GetDlgItemInt, FALSE);
		pitcherStatsRecord.Loss = m_pPage3->GetDlgItemInt(IDC_LOSS1, &rc_GetDlgItemInt, FALSE);
		pitcherStatsRecord.HomeRuns = m_pPage3->GetDlgItemInt(IDC_HR1, &rc_GetDlgItemInt, FALSE);
		pitcherStatsRecord.Hits = m_pPage3->GetDlgItemInt(IDC_HITS1, &rc_GetDlgItemInt, FALSE);
		pitcherStatsRecord.ER = m_pPage3->GetDlgItemInt(IDC_ER1, &rc_GetDlgItemInt, FALSE);
		pitcherStatsRecord.Games = m_pPage3->GetDlgItemInt(IDC_GAMES1, &rc_GetDlgItemInt, FALSE);
		pitcherStatsRecord.CompleteGames = m_pPage3->GetDlgItemInt(IDC_COMPLETEGAMES1, &rc_GetDlgItemInt, FALSE);
		if (pitcherStatsRecord.InningsPitched == 0)
		{
			pitcherStatsRecord.ERA = 0.0f;
			pitcherStatsRecord.WHIP = 0.0f;
		}
		else
		{
			pitcherStatsRecord.ERA = (float)(pitcherStatsRecord.ER * 9) / pitcherStatsRecord.InningsPitched;
			pitcherStatsRecord.WHIP = (float)((pitcherStatsRecord.Hits + pitcherStatsRecord.Walks) * 9) / pitcherStatsRecord.InningsPitched;
		}
		m_pPage3->m_bChangedFlag = FALSE;
	}


	// Open file and update player
	if (m_flagNew == TRUE)
	{
		//m_structPitcher.AddPitcher(m_FileName);
		m_flagNew = FALSE;
	}
	else
	{
		// Only update the Batter record if this is a BASE team.
		if (teamRecord.BaseTeam == 1)
		{
			pDoc->PitcherStatsUpdate(pitcherStatsRecord);
			pDoc->PitcherUpdate(pitcherRecord);
		}
		else
		{
			// We still could be updating the BASE stats record.
			pDoc->PitcherStatsUpdate(pitcherStatsRecord);
		}

		if (m_pPage3->m_hWnd != 0)
		{
			if (pitcherStatsRecord.InningsPitched == 0)
			{
				m_pPage3->SetDlgItemText(IDC_ERA1, _T("0"));
				m_pPage3->SetDlgItemText(IDC_TRG1, _T("0"));
				m_pPage3->m_bChangedFlag = FALSE;
			}
			else
			{
				fERA = (double)(pitcherStatsRecord.ER * 9) / pitcherStatsRecord.InningsPitched;
				sprintf_s(buf, "%1.2f", fERA);
				m_pPage3->SetDlgItemText(IDC_ERA1, buf);
				fTRG = (double)((pitcherStatsRecord.Hits + pitcherStatsRecord.Walks) * 9) / pitcherStatsRecord.InningsPitched;
				sprintf_s(buf, "%1.2f", fTRG);
				m_pPage3->SetDlgItemText(IDC_TRG1, buf);
				m_pPage3->m_bChangedFlag = FALSE;
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

