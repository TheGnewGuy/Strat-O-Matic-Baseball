#if !defined(AFX_DIALOGS_H__F19BA612_5E4A_11D4_BC44_00C04FC98650__INCLUDED_)
#define AFX_DIALOGS_H__F19BA612_5E4A_11D4_BC44_00C04FC98650__INCLUDED_

#include "FileStruct.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// dialogs.h : header file
//
#define REGTEAMS "\\HTML\\Team"
#define REGLEAGUE "\\HTML\\League"

/////////////////////////////////////////////////////////////////////////////
// PropertyPageBatters dialog

class PropertyPageBatters : public CPropertyPage
{
	DECLARE_DYNCREATE(PropertyPageBatters)

// Construction
public:
	void OnInitDialogPublic();
	BOOL m_bChangedFlag;
	void* m_pDocVoid;
	void BuildPlayerNameComboBox();
//	PropertySheetBatters* m_pmyBattersSheet;
	PropertyPageBatters();
	~PropertyPageBatters();

// Dialog Data
	//{{AFX_DATA(PropertyPageBatters)
	enum { IDD = IDD_BATTERS };
	CSpinButtonCtrl	m_spinThirdBase;
	CSpinButtonCtrl	m_spinShortStop;
	CSpinButtonCtrl	m_spinSecondBase;
	CSpinButtonCtrl	m_spinRightField;
	CSpinButtonCtrl	m_spinPitcher;
	CSpinButtonCtrl	m_spinLeftField;
	CSpinButtonCtrl	m_spinFirstBase;
	CSpinButtonCtrl	m_spinERSS;
	CSpinButtonCtrl	m_spinERRF;
	CSpinButtonCtrl	m_spinERP;
	CSpinButtonCtrl	m_spinERLF;
	CSpinButtonCtrl	m_spinERCF;
	CSpinButtonCtrl	m_spinERC;
	CSpinButtonCtrl	m_spinER3B;
	CSpinButtonCtrl	m_spinER2B;
	CSpinButtonCtrl	m_spinER1B;
	CSpinButtonCtrl	m_spinCenterField;
	CSpinButtonCtrl	m_spinCatcher;
	CEdit	m_ceditERSS;
	CEdit	m_ceditERRF;
	CEdit	m_ceditERP;
	CEdit	m_ceditERLF;
	CEdit	m_ceditERCF;
	CEdit	m_ceditERC;
	CEdit	m_ceditER3B;
	CEdit	m_ceditER2B;
	CEdit	m_ceditER1B;
	CComboBox	m_comboPlayerName;
	CEdit	m_ceditThirdBase;
	CEdit	m_ceditShortStop;
	CEdit	m_ceditSecondBase;
	CEdit	m_ceditRightField;
	CEdit	m_ceditPitcher;
	CEdit	m_ceditLeftField;
	CEdit	m_ceditFirstBase;
	CEdit	m_ceditCenterField;
	CEdit	m_ceditCatcher;
	CString	m_TeamName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PropertyPageBatters)
	public:
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PropertyPageBatters)
	virtual BOOL OnInitDialog();
	afx_msg void OnCloseupComboPlayerName();
	afx_msg void OnChangeCatcher();
	afx_msg void OnChangeCenterfield();
	afx_msg void OnEditchangeComboPlayerName();
	afx_msg void OnChangeER1B();
	afx_msg void OnChangeER2B();
	afx_msg void OnChangeER3B();
	afx_msg void OnChangeERC();
	afx_msg void OnChangeERCF();
	afx_msg void OnChangeERLF();
	afx_msg void OnChangeERP();
	afx_msg void OnChangeERRF();
	afx_msg void OnChangeERSS();
	afx_msg void OnChangeFirstbase();
	afx_msg void OnChangeLeftfield();
	afx_msg void OnChangePitcher();
	afx_msg void OnChangeRightfield();
	afx_msg void OnChangeSecondbase();
	afx_msg void OnChangeShortstop();
	afx_msg void OnNew();
	afx_msg void OnPlayerAdd();
	afx_msg void OnPlayerUpdate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// PropertyPageBattersStats dialog

class PropertyPageBattersStats : public CPropertyPage
{
	DECLARE_DYNCREATE(PropertyPageBattersStats)

// Construction
public:
	void OnInitDialogPublic();
	BOOL m_bChangedFlag;
	void* m_pDocVoid;
	void BuildPlayerNameComboBox();
//	CWnd* m_pmyBattersSheet;
	PropertyPageBattersStats();
	~PropertyPageBattersStats();

// Dialog Data
	//{{AFX_DATA(PropertyPageBattersStats)
	enum { IDD = IDD_BATTERSSTATS };
	CEdit	m_ceditSLG;
	CEdit	m_ceditOnBasePercent;
	CEdit	m_ceditBattingAverage;
	CEdit	m_ceditK;
	CEdit	m_ceditSB;
	CSpinButtonCtrl	m_spinW;
	CSpinButtonCtrl	m_spinK;
	CSpinButtonCtrl	m_spinSB;
	CSpinButtonCtrl	m_spinSACRICIFE;
	CSpinButtonCtrl	m_spinRUNS;
	CSpinButtonCtrl	m_spinRE;
	CSpinButtonCtrl	m_spinRBI;
	CSpinButtonCtrl	m_spinHR;
	CSpinButtonCtrl	m_spinHITS;
	CSpinButtonCtrl	m_spinHBP;
	CSpinButtonCtrl	m_spinGAMES;
	CSpinButtonCtrl	m_spinCS;
	CSpinButtonCtrl	m_spinAB;
	CSpinButtonCtrl	m_spin3B;
	CSpinButtonCtrl	m_spin2B;
	CEdit	m_ceditWALK;
	CEdit	m_ceditSACRICIFE;
	CEdit	m_ceditRUNS;
	CEdit	m_ceditROE;
	CEdit	m_ceditRBI;
	CEdit	m_ceditHR;
	CEdit	m_ceditHITS;
	CEdit	m_ceditHBP;
	CEdit	m_ceditGames;
	CEdit	m_ceditCS;
	CEdit	m_ceditAB;
	CEdit	m_cedit3B;
	CEdit	m_cedit2B;
	CComboBox	m_comboPlayerName;
	CString	m_TeamName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PropertyPageBattersStats)
	public:
	void OnCancel();
	void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PropertyPageBattersStats)
	virtual BOOL OnInitDialog();
	afx_msg void OnCloseupComboPlayerName();
	afx_msg void OnChangeBattingaverage();
	afx_msg void OnChange2B();
	afx_msg void OnChange3B();
	afx_msg void OnChangeAB();
	afx_msg void OnEditchangeComboPlayerName();
	afx_msg void OnChangeCS();
	afx_msg void OnChangeGames();
	afx_msg void OnChangeHBP();
	afx_msg void OnChangeHits();
	afx_msg void OnChangeHR();
	afx_msg void OnChangeOnBasePercent();
	afx_msg void OnChangeRBI();
	afx_msg void OnChangeReachedOnError();
	afx_msg void OnChangeRuns();
	afx_msg void OnChangeSacricife();
	afx_msg void OnChangeSLG();
	afx_msg void OnChangeStolenbase();
	afx_msg void OnChangeStrikeout();
	afx_msg void OnChangeWalk();
	afx_msg void OnPlayerUpdate();
	afx_msg void OnPlayerAdd();
	afx_msg void OnNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// PropertyPageBattersChance dialog

class PropertyPageBattersChance : public CPropertyPage
{
	DECLARE_DYNCREATE(PropertyPageBattersChance)

// Construction
public:
	void OnInitDialogPublic();
	void BuildPlayerNameComboBox();
	void* m_pDocVoid;
	BOOL m_bChangedFlag;
//	CWnd* m_pmyBattersSheet;
	PropertyPageBattersChance();
	~PropertyPageBattersChance();

// Dialog Data
	//{{AFX_DATA(PropertyPageBattersChance)
	enum { IDD = IDD_BATTERSCHANCE };
	CEdit	m_ceditWalkRight;
	CEdit	m_ceditWalkLeft;
	CEdit	m_ceditTripleRight;
	CEdit	m_ceditTripleLeft;
	CEdit	m_ceditSingleRight;
	CEdit	m_ceditSingleLeft;
	CEdit	m_ceditHRRight;
	CEdit	m_ceditHRLeft;
	CEdit	m_ceditDoubleRight;
	CEdit	m_ceditDoublePlayLeft;
	CEdit	m_ceditDoublePlayRight;
	CEdit	m_cdeitDoubleLeft;
	CEdit	m_ceditDoublePlay;
	CEdit	m_ceditWalk;
	CEdit	m_ceditTriple;
	CEdit	m_ceditSingle;
	CEdit	m_ceditHR;
	CEdit	m_ceditDouble;
	CEdit	m_ceditBasic;
	CEdit	m_ceditLeft;
	CEdit	m_ceditRight;
	CComboBox	m_comboPlayerName;
	CString	m_TeamName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PropertyPageBattersChance)
	public:
	virtual void OnCancel();
	virtual void OnOK();
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PropertyPageBattersChance)
	virtual BOOL OnInitDialog();
	afx_msg void OnCloseupComboPlayerName();
	afx_msg void OnPlayerUpdate();
	afx_msg void OnNew();
	afx_msg void OnChangeChanceBasic();
	afx_msg void OnChangeChanceLeft();
	afx_msg void OnChangeChanceRight();
	afx_msg void OnChangeChanceDouble();
	afx_msg void OnChangeChanceHR();
	afx_msg void OnChangeChanceSingle();
	afx_msg void OnChangeChanceTriple();
	afx_msg void OnChangeChanceWalk();
	afx_msg void OnChangeChanceDoublePlay();
	afx_msg void OnChangeChanceDoubleLeft();
	afx_msg void OnChangeChanceHRLeft();
	afx_msg void OnChangeChanceSingleLeft();
	afx_msg void OnChangeChanceTripleLeft();
	afx_msg void OnChangeChanceWalkLeft();
	afx_msg void OnChangeChanceDoublePlayLeft();
	afx_msg void OnChangeChanceDoubleRight();
	afx_msg void OnChangeChanceHRRight();
	afx_msg void OnChangeChanceSingleRight();
	afx_msg void OnChangeChanceTripleRight();
	afx_msg void OnChangeChanceWalkRight();
	afx_msg void OnChangeChanceDoublePlayRight();
	afx_msg void OnEditChangeComboPlayerName();
	afx_msg void OnPlayerAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// PropertyPageBattersInfo dialog

class PropertyPageBattersInfo : public CPropertyPage
{
	DECLARE_DYNCREATE(PropertyPageBattersInfo)

// Construction
public:
	void OnInitDialogPublic();
	void BuildPlayerNameComboBox();
	void* m_pDocVoid;
	BOOL m_bChangedFlag;
	PropertyPageBattersInfo();
	~PropertyPageBattersInfo();

// Dialog Data
	//{{AFX_DATA(PropertyPageBattersInfo)
	enum { IDD = IDD_BATTERSINFO };
	CComboBox	m_comboTRate;
	CComboBox	m_comboStealing;
	CComboBox	m_comboRunning;
	CComboBox	m_comboPowerRight;
	CComboBox	m_comboPowerLeft;
	CComboBox	m_comboPlayerName;
	CComboBox	m_comboPassBall;
	CComboBox	m_comboOutArm;
	CComboBox	m_comboHitRun;
	CComboBox	m_comboCatcherArm;
	CComboBox	m_comboBunting;
	CComboBox	m_comboBatterHits;
	CString	m_strTeam;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PropertyPageBattersInfo)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PropertyPageBattersInfo)
	afx_msg void OnCloseupComboPlayerName();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnNew();
	afx_msg void OnPlayerAdd();
	afx_msg void OnPlayerUpdate();
	virtual BOOL OnInitDialog();
	afx_msg void OnEditChangeComboBatterHits();
	afx_msg void OnEditChangeComboBunting();
	afx_msg void OnEditChangeComboCatcherArm();
	afx_msg void OnEditChangeComboHitRun();
	afx_msg void OnEditChangeComboOutArm();
	afx_msg void OnEditChangeComboPassball();
	afx_msg void OnEditChangeComboPlayerName();
	afx_msg void OnEditChangeComboPowerLeft();
	afx_msg void OnEditChangeComboPowerRight();
	afx_msg void OnEditChangeComboRunning();
	afx_msg void OnEditChangeComboStealing();
	afx_msg void OnEditChangeComboTRate();
	afx_msg void OnSelchangeComboBatterHits();
	afx_msg void OnSelchangeComboBunting();
	afx_msg void OnSelchangeComboCatcherArm();
	afx_msg void OnSelchangeComboHitRun();
	afx_msg void OnSelchangeComboOutArm();
	afx_msg void OnSelchangeComboPassball();
	afx_msg void OnSelchangeComboPowerLeft();
	afx_msg void OnSelchangeComboPowerRight();
	afx_msg void OnSelchangeComboRunning();
	afx_msg void OnSelchangeComboStealing();
	afx_msg void OnSelchangeComboTRate();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnEditChangeFirstname();
	afx_msg void OnEditChangeLastname();
};
/////////////////////////////////////////////////////////////////////////////
// PropertySheetBatters

#define WM_APP1 WM_APP + 1	// Update
#define WM_APP2 WM_APP + 2	// OnOK
#define WM_APP3 WM_APP + 3	// OnCancel
#define WM_APP4 WM_APP + 4	// OnAdd

class PropertySheetBatters : public CPropertySheet
{
	DECLARE_DYNAMIC(PropertySheetBatters)

// Construction
public:
	PropertySheetBatters(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	PropertySheetBatters(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	LONG m_lSeekPlayerFile;
	BatterStruct m_structBatter;
	CString m_FileName;
// Not working
	CFont myfont;


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PropertySheetBatters)
	public:
	virtual BOOL OnInitDialog();
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	CString m_TeamName;
	void OnNewInitStruct();
	void SetPlayerNameCB(int iPage);
	int m_flagNew;
	void OnNew();
	int m_newFlag;
	float m_fBattingAverage;
	float m_fOnBasePercentage;
	float m_fSLG;
	CString m_rString;
	int m_rgetcursel;
	void OnCloseupComboPlayerName(int iPage);
	void BuildPlayerNameComboBox(int iPage);
	PropertyPageBatters* m_pPage1;
	PropertyPageBattersChance* m_pPage2;
	PropertyPageBattersStats* m_pPage3;
	PropertyPageBattersInfo* m_pPage4;
	virtual ~PropertySheetBatters();

	// Generated message map functions
protected:
	//{{AFX_MSG(PropertySheetBatters)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	afx_msg LRESULT OnUpdate(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnOK(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnCancel(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	int m_TeamID;
	int m_BatterStatsID;
	void *m_pDocVoid;
	struct m_BatterRecord{
		int BatterID;
		CStringA FirstName;
		CStringA LastName;
		int Pitcher;
		int Catcher;
		int FirstBase;
		int SecondBase;
		int ShortStop;
		int ThirdBase;
		int LeftField;
		int CenterField;
		int RightField;
		int Bunting;
		int HitRun;
		int Running;
		int Stealing;
		int CatchArm;
		int OutArm;
		int PowerRight;
		int PowerLeft;
		int Pass;
		int TRate;
		int ER1;
		int ER2;
		int ER3;
		int ER4;
		int ER5;
		int ER6;
		int ER7;
		int ER8;
		int ER9;
		int BatterHits;
		int TeamID;
		double OBChanceHomeRun;
		double OBChanceTriple;
		double OBChanceDouble;
		double OBChanceSingle;
		double OBChanceWalk;
		double ChanceDoublePlay;
		double OBChanceHomeRunRight;
		double OBChanceTripleRight;
		double OBChanceDoubleRight;
		double OBChanceSingleRight;
		double OBChanceWalkRight;
		double ChanceDoublePlayRight;
		double OBChanceHomeRunLeft;
		double OBChanceTripleLeft;
		double OBChanceDoubleLeft;
		double OBChanceSingleLeft;
		double OBChanceWalkLeft;
		double ChanceDoublePlayLeft;
		double OBChanceBasic;
		double OBChanceLeft;
		double OBChanceRight;
		CStringA CreateTime;
		CStringA LastUpdateTime;
	} m_batterRecord;
	struct m_BatterStatsRecord{
		int BatterStatsID;
		int AB;
		int Runs;
		int Hits;
		int RBI;
		int Doubles;
		int Triples;
		int HomeRuns;
		int Walk;
		int Stirkeout;
		int ReachedOnError;
		int Sacrifice;
		int StolenBase;
		int CS;
		int Games;
		int HBP;
		double AVG;
		double SLG;
		double OBP;
		int BatterID;
		int TeamID;
		CStringA CreateTime;
		CStringA LastUpdateTime;
	} m_batterStatsRecord;
	struct m_PitcherRecord{
		int PitcherID;
		CStringA FirstName;
		CStringA LastName;
		double OBChanceHomeRun;
		double OBChanceTriple;
		double OBChanceDouble;
		double OBChanceSingle;
		double OBChanceWalk;
		double ChanceDoublePlay;
		double OBChanceHomeRunRight;
		double OBChanceTripleRight;
		double OBChanceDoubleRight;
		double OBChanceSingleRight;
		double OBChanceWalkRight;
		double ChanceDoublePlayRight;
		double OBChanceHomeRunLeft;
		double OBChanceTripleLeft;
		double OBChanceDoubleLeft;
		double OBChanceSingleLeft;
		double OBChanceWalkLeft;
		double ChanceDoublePlayLeft;
		double OBChanceBasic;
		double OBChanceLeft;
		double OBChanceRight;
		int Starter;
		int Relief;
		int Throws;
		int Bunting;
		int Hold;
		int WP;
		int Balk;
		int Pitcher;
		int ER1;
		int TeamID;
		CStringA CreateTime;
		CStringA LastUpdateTime;
	} m_pitcherRecord;
	struct m_PitcherStatsRecord{
		int PitcherStatsID;
		int Wins;
		int Loss;
		int Saves;
		double InningsPitched;
		int ER;
		int Hits;
		int Walks;
		int Strikeouts;
		int HomeRuns;
		int Games;
		int CompleteGames;
		int Starts;
		double ERA;
		double WHIP;
		int PitcherID;
		int TeamID;
		CStringA CreateTime;
		CStringA LastUpdateTime;
	} m_pitcherStatsRecord;
protected:
//	afx_msg LRESULT WM_APP4(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAdd(WPARAM wParam, LPARAM lParam);
public:
//	afx_msg void OnAfxIdcFontsizes();
};

/////////////////////////////////////////////////////////////////////////////
// PropertyPagePitchersInfo dialog

class PropertyPagePitchersInfo : public CPropertyPage
{
	DECLARE_DYNCREATE(PropertyPagePitchersInfo)

// Construction
public:
	void BuildPlayerNameComboBox();
	void OnInitDialogPublic();
	int m_bChangedFlag;
	void* m_pDocVoid;
	PropertyPagePitchersInfo();
	~PropertyPagePitchersInfo();

// Dialog Data
	//{{AFX_DATA(PropertyPagePitchersInfo)
	enum { IDD = IDD_PITCHERSINFO };
	CEdit	m_ceditWP;
	CEdit	m_ceditStarter;
	CSpinButtonCtrl	m_spinWP;
	CSpinButtonCtrl	m_spinStarter;
	CSpinButtonCtrl	m_spinRelief;
	CSpinButtonCtrl	m_spinPitcher;
	CSpinButtonCtrl	m_spinERP;
	CSpinButtonCtrl	m_spinBalk;
	CEdit	m_ceditRelief;
	CEdit	m_ceditPitcher;
	CEdit	m_ceditERP;
	CComboBox	m_comboPlayerName;
	CComboBox	m_comboThrows;
	CComboBox	m_comboHold;
	CComboBox	m_comboBunting;
	CEdit	m_ceditBalk;
	CString	m_TeamName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PropertyPagePitchersInfo)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PropertyPagePitchersInfo)
	afx_msg void OnCloseupComboPlayername1();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancel();
	afx_msg void OnNew();
	virtual void OnOK();
	afx_msg void OnPlayerAdd();
	afx_msg void OnPlayerUpdate();
	afx_msg void OnEditChangeComboPlayerName();
	afx_msg void OnSelchangeComboBunting();
	afx_msg void OnSelchangeComboHold();
	afx_msg void OnSelchangeComboPitcherThrows();
	afx_msg void OnChangeERP();
	afx_msg void OnChangePitcher();
	afx_msg void OnChangeRelief();
	afx_msg void OnChangeStarter();
	afx_msg void OnChangeWP();
	afx_msg void OnChangeBalk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnChangeFirstName();
	afx_msg void OnChangeLastName();
};

/////////////////////////////////////////////////////////////////////////////
// PropertyPagePitchersChance dialog

class PropertyPagePitchersChance : public CPropertyPage
{
	DECLARE_DYNCREATE(PropertyPagePitchersChance)

// Construction
public:
	void BuildPlayerNameComboBox();
	void OnInitDialogPublic();
	int m_bChangedFlag;
	void* m_pDocVoid;
	PropertyPagePitchersChance();
	~PropertyPagePitchersChance();

// Dialog Data
	//{{AFX_DATA(PropertyPagePitchersChance)
	enum { IDD = IDD_PITCHERSCHANCE };
	CEdit	m_ceditWalkRight;
	CEdit	m_ceditWalkLeft;
	CEdit	m_ceditTripleRight;
	CEdit	m_ceditTripleLeft;
	CEdit	m_ceditSingleRight;
	CEdit	m_ceditSingleLeft;
	CEdit	m_ceditHRRight;
	CEdit	m_ceditHRLeft;
	CEdit	m_ceditDoubleRight;
	CEdit	m_ceditDoublePlayRight;
	CEdit	m_ceditDoublePlayLeft;
	CEdit	m_ceditDoubleLeft;
	CComboBox	m_comboPlayerName;
	CEdit	m_ceditDoublePlay;
	CEdit	m_ceditWalk;
	CEdit	m_ceditTriple;
	CEdit	m_ceditSingle;
	CEdit	m_ceditHR;
	CEdit	m_ceditDouble;
	CEdit	m_ceditBasic;
	CEdit	m_ceditRight;
	CEdit	m_ceditLeft;
	CString	m_TeamName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PropertyPagePitchersChance)
	public:
	virtual BOOL OnSetActive();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PropertyPagePitchersChance)
	afx_msg void OnCloseupComboPlayerName();
	virtual BOOL OnInitDialog();
	afx_msg void OnCancel();
	afx_msg void OnNew();
	afx_msg void OnOK();
	afx_msg void OnPlayerAdd();
	afx_msg void OnPlayerUpdate();
	afx_msg void OnEditChangeComboPlayerName();
	afx_msg void OnChangeChanceBasic();
	afx_msg void OnChangeChanceDouble();
	afx_msg void OnChangeChanceHR();
	afx_msg void OnChangeChanceLeft();
	afx_msg void OnChangeChancerRight();
	afx_msg void OnChangeChanceSingle();
	afx_msg void OnChangeChanceTriple();
	afx_msg void OnChangeChanceWalk();
	afx_msg void OnChangeChanceDoublePlay();
	afx_msg void OnChangeChanceDoubleLeft();
	afx_msg void OnChangeChanceDoublePlayLeft();
	afx_msg void OnChangeChanceDoublePlayRight();
	afx_msg void OnChangeChanceDoubleRight();
	afx_msg void OnChangeChanceHRLeft();
	afx_msg void OnChangeChanceHRRight();
	afx_msg void OnChangeChanceSingleLeft();
	afx_msg void OnChangeChanceSingleRight();
	afx_msg void OnChangeChanceTripleLeft();
	afx_msg void OnChangeChanceTripleRight();
	afx_msg void OnChangeChanceWalkLeft();
	afx_msg void OnChangeChanceWalkRight();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// PropertyPagePitchersStats dialog

class PropertyPagePitchersStats : public CPropertyPage
{
	DECLARE_DYNCREATE(PropertyPagePitchersStats)

// Construction
public:
	void BuildPlayerNameComboBox();
	void OnInitDialogPublic();
	int m_bChangedFlag;
	void* m_pDocVoid;
	PropertyPagePitchersStats();
	~PropertyPagePitchersStats();

// Dialog Data
	//{{AFX_DATA(PropertyPagePitchersStats)
	enum { IDD = IDD_PITCHERSSTATS };
	CEdit	m_ceditWins;
	CEdit	m_ceditWalk;
	CEdit	m_ceditTRG;
	CEdit	m_ceditStarts;
	CEdit	m_ceditStrikeOut;
	CSpinButtonCtrl	m_spinWins;
	CSpinButtonCtrl	m_spinWalk;
	CSpinButtonCtrl	m_spinK;
	CSpinButtonCtrl	m_spinStarts;
	CSpinButtonCtrl	m_spinSaves;
	CSpinButtonCtrl	m_spinLoss;
	CSpinButtonCtrl	m_spinHR;
	CSpinButtonCtrl	m_spinHits;
	CSpinButtonCtrl	m_spinGames;
	CSpinButtonCtrl	m_spinER;
	CSpinButtonCtrl	m_spinCompGames;
	CEdit	m_ceditSaves;
	CEdit	m_ceditLoss;
	CEdit	m_ceditIP;
	CEdit	m_ceditHR;
	CEdit	m_ceditHits;
	CEdit	m_ceditGames;
	CEdit	m_ceditERA;
	CEdit	m_ceditER;
	CEdit	m_ceditCompGames;
	CComboBox	m_comboPlayerName;
	CString	m_TeamName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PropertyPagePitchersStats)
	public:
	virtual BOOL OnSetActive();
	virtual void OnCancel();
	virtual void OnNew();
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PropertyPagePitchersStats)
	afx_msg void OnCloseupComboPlayerName();
	virtual BOOL OnInitDialog();
	afx_msg void OnPlayerAdd();
	afx_msg void OnPlayerUpdate();
	afx_msg void OnEditChangeComboPlayerName();
	afx_msg void OnChangeER();
	afx_msg void OnChangeERA();
	afx_msg void OnChangeGames();
	afx_msg void OnChangeHits();
	afx_msg void OnChangeHR();
	afx_msg void OnChangeIP();
	afx_msg void OnChangeLoss();
	afx_msg void OnChangeSaves();
	afx_msg void OnChangeStarts();
	afx_msg void OnChangeStrikeout();
	afx_msg void OnChangeTRG();
	afx_msg void OnChangeWalk();
	afx_msg void OnChangeWins();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// PropertySheetPitchers

class PropertySheetPitchers : public CPropertySheet
{
	DECLARE_DYNAMIC(PropertySheetPitchers)

// Construction
public:
	PropertySheetPitchers(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	PropertySheetPitchers(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:
	PitcherStruct m_structPitcher;
	LONG m_lSeekPlayerFile;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PropertySheetPitchers)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// Implementation
public:
	afx_msg LRESULT OnUpdate(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnCancel(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnOK(WPARAM wParam,LPARAM lParam);
	void OnNew();
	CString m_rString;
	void OnCloseupComboPlayerName(int iPage);
	void SetPlayerNameCB(int iPage);
	void OnNewInitStruct();
	int m_flagNew;
	void BuildPlayerNameComboBox(int iPage);
	int m_newFlag;
	int m_rgetcursel;
	CString m_TeamName;
	CString m_FileName;
	PropertyPagePitchersStats* m_pPage3;
	PropertyPagePitchersChance* m_pPage2;
	PropertyPagePitchersInfo* m_pPage1;
	virtual ~PropertySheetPitchers();

	// Generated message map functions
protected:
	//{{AFX_MSG(PropertySheetPitchers)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void *m_pDocVoid;
	int m_TeamID;
	int m_PitcherStatsID;
protected:
//	afx_msg LRESULT WM_APP4(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnAdd(WPARAM wParam, LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// PropertyPageTeamHTMLOptions dialog

class PropertyPageTeamHTMLOptions : public CPropertyPage
{
	DECLARE_DYNCREATE(PropertyPageTeamHTMLOptions)

// Construction
public:
	CString m_strLeagueDir;
	PropertyPageTeamHTMLOptions();
	~PropertyPageTeamHTMLOptions();

// Dialog Data
	//{{AFX_DATA(PropertyPageTeamHTMLOptions)
	enum { IDD = IDD_TEAMHTMLOPTIONS };
	CEdit	m_ceditIndex;
	CComboBox	m_comboVLinkColor;
	CComboBox	m_comboTextColor;
	CComboBox	m_comboLinkColor;
	CComboBox	m_comboBGColor;
	CEdit	m_ceditBackgroundPicture;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PropertyPageTeamHTMLOptions)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PropertyPageTeamHTMLOptions)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelEndOKComboxBGColor();
	afx_msg void OnSelendOKComboxLinkColor();
	afx_msg void OnSelEndOKComboTextColor();
	afx_msg void OnSelEndOKComboxVlinkColor();
	afx_msg void OnChangeBackgroundPicture();
	afx_msg void OnChangeIndex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
/////////////////////////////////////////////////////////////////////////////
// PropertySheetLeagueOptions

class PropertySheetLeagueOptions : public CPropertySheet
{
	DECLARE_DYNAMIC(PropertySheetLeagueOptions)

// Construction
public:
	PropertySheetLeagueOptions(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	PropertySheetLeagueOptions(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PropertySheetLeagueOptions)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~PropertySheetLeagueOptions();

	// Generated message map functions
protected:
	//{{AFX_MSG(PropertySheetLeagueOptions)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// PropertyPageLeagueHTMLOptions dialog

class PropertyPageLeagueHTMLOptions : public CPropertyPage
{
	DECLARE_DYNCREATE(PropertyPageLeagueHTMLOptions)

// Construction
public:
	CString m_strLeagueDir;
	PropertyPageLeagueHTMLOptions();
	~PropertyPageLeagueHTMLOptions();

// Dialog Data
	//{{AFX_DATA(PropertyPageLeagueHTMLOptions)
	enum { IDD = IDD_LEAGUEHTMLOPTIONS };
	CEdit	m_ceditIndex;
	CComboBox	m_comboVLinkColor;
	CComboBox	m_comboTextColor;
	CComboBox	m_comboLinkColor;
	CComboBox	m_comboBGColor;
	CEdit	m_ceditBackgroundPicture;
	//}}AFX_DATA


// Overrides
	// ClassWizard generate virtual function overrides
	//{{AFX_VIRTUAL(PropertyPageLeagueHTMLOptions)
	public:
	virtual void OnOK();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(PropertyPageLeagueHTMLOptions)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelEndOKComboxBGColor();
	afx_msg void OnSelEndOKComboxLinkColor();
	afx_msg void OnSelEndOKComboxTextColor();
	afx_msg void OnSelEndOKComboxVlinkColor();
	afx_msg void OnChangeBackgroundPicture();
	afx_msg void OnChangeIndex();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DIALOGS_H__F19BA612_5E4A_11D4_BC44_00C04FC98650__INCLUDED_)
