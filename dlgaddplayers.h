#if !defined(AFX_DLGADDPLAYERS_H__06762501_8C3F_11D2_B0EE_444553540000__INCLUDED_)
#define AFX_DLGADDPLAYERS_H__06762501_8C3F_11D2_B0EE_444553540000__INCLUDED_

#include "FileStruct.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgAddPlayers.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgAddPlayers dialog

class DlgAddPlayers : public CDialog
{
// Construction
public:
	PitcherStruct m_structPitcher;
	BatterStruct m_structBatter;
	float m_fSLG;
	float m_fOnBasePercentage;
	float m_fBattingAverage;
	LONG m_lSeekPlayerFile;
	CFile m_cFileTeam1;
	CString m_FileName1;
	BYTE m_bHitRun;
	BYTE m_bRunning;
	BYTE m_bStealing;
	BYTE m_bBunting;
	DlgAddPlayers(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAddPlayers)
	enum { IDD = IDD_PLAYERS1 };
	CSpinButtonCtrl	m_spinHBP1;
	CSpinButtonCtrl	m_spinGAMES2;
	CEdit	m_ceditGAMES2;
	CEdit	m_ceditHBP1;
	CComboBox	m_BatterHits;
	CEdit	m_ceditRightField;
	CEdit	m_ceditCenterField;
	CEdit	m_ceditLeftField;
	CEdit	m_ceditThirdBase;
	CEdit	m_ceditShortStop;
	CEdit	m_ceditSecondBase;
	CEdit	m_ceditFirstBase;
	CEdit	m_ceditCatcher;
	CEdit	m_ceditPitcher;
	CSpinButtonCtrl	m_spinThirdBase;
	CSpinButtonCtrl	m_spinShortStop;
	CSpinButtonCtrl	m_spinSecondBase;
	CSpinButtonCtrl	m_spinRightField;
	CSpinButtonCtrl	m_spinPitcher;
	CSpinButtonCtrl	m_spinLeftField;
	CSpinButtonCtrl	m_spinFirstBase;
	CSpinButtonCtrl	m_spinCenterField;
	CSpinButtonCtrl	m_spinCatcher;
	CEdit	m_ceditCS;
	CSpinButtonCtrl	m_spinCS;
	CComboBox	m_comboPlayerName;
	CEdit	m_ceditWalk;
	CEdit	m_ceditStrikeOut;
	CEdit	m_ceditStolenBase;
	CEdit	m_ceditSacrifie;
	CEdit	m_ceditRuns;
	CEdit	m_ceditReachedOnError;
	CEdit	m_ceditRBI;
	CEdit	m_ceditHomeRuns;
	CEdit	m_ceditHits;
	CEdit	m_ceditAB;
	CEdit	m_cedit3B;
	CEdit	m_cedit2B;
	CComboBox	m_Stealing;
	CComboBox	m_Running;
	CComboBox	m_HitRun;
	CComboBox	m_Bunting;
	CSpinButtonCtrl	m_spinWalk;
	CSpinButtonCtrl	m_spinStrikeOut;
	CSpinButtonCtrl	m_spinStolenBase;
	CSpinButtonCtrl	m_spinSacricife;
	CSpinButtonCtrl	m_spinRuns;
	CSpinButtonCtrl	m_spinReachedOnError;
	CSpinButtonCtrl	m_spinRBI;
	CSpinButtonCtrl	m_spinHR;
	CSpinButtonCtrl	m_spinAB;
	CSpinButtonCtrl	m_spin3B;
	CSpinButtonCtrl	m_spin2B;
	CSpinButtonCtrl	m_spinHits;
	CString	m_TeamName;
	CString	m_strBattingAverage;
	CString	m_strOnBasePercentage;
	CString	m_strSLG;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAddPlayers)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgAddPlayers)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPlayerAdd();
	afx_msg void OnPlayerUpdate();
	afx_msg void OnNewPlayer();
	afx_msg void OnCloseupComboPlayername1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void BuildPlayerNameCombo(CString myFileName);
};

/////////////////////////////////////////////////////////////////////////////
// DlgAddPitchers dialog

class DlgAddPitchers : public CDialog
{
// Construction
public:
	double m_fIP;
	double m_fTRG;
	double m_fERA;
	LONG m_lSeekPlayerFile;
	PitcherStruct m_structPitcher;
	BatterStruct m_structBatter;
	CString m_FileName1;
	DlgAddPitchers(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAddPitchers)
	enum { IDD = IDD_PITCHERS1 };
	CSpinButtonCtrl	m_spinGAMES1;
	CSpinButtonCtrl	m_spinCOMPLETEGAMES1;
	CEdit	m_ceditCOMPLETEGAMES1;
	CEdit	m_ceditGAMES1;
	CEdit	m_ceditSTARTS1;
	CSpinButtonCtrl	m_spinSTARTS1;
	CEdit	m_ceditSTARTER1;
	CComboBox	m_comboPLAYERNAME;
	CComboBox	m_comboPITCHERTHROWS;
	CComboBox	m_comboHOLD;
	CComboBox	m_comboBUNTING;
	CEdit	m_ceditWINS1;
	CEdit	m_ceditWALK1;
	CEdit	m_ceditSTRIKEOUT1;
	CSpinButtonCtrl	m_spinSTARTER1;
	CSpinButtonCtrl	m_spinWINS1;
	CSpinButtonCtrl	m_spinWALK1;
	CSpinButtonCtrl	m_spinSTRIKEOUT;
	CSpinButtonCtrl	m_spinSAVES1;
	CSpinButtonCtrl	m_spinRELIEF1;
	CSpinButtonCtrl	m_spinLOSS1;
	CSpinButtonCtrl	m_spinHR1;
	CSpinButtonCtrl	m_spinHITS1;
	CSpinButtonCtrl	m_spinER1;
	CEdit	m_ceditSAVES1;
	CEdit	m_ceditRELIEF1;
	CEdit	m_ceditLOSS1;
	CEdit	m_ceditHR1;
	CEdit	m_ceditHITS1;
	CEdit	m_ceditER1;
	CString	m_TeamName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAddPitchers)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgAddPitchers)
	virtual BOOL OnInitDialog();
	afx_msg void OnCloseupComboPlayername1();
	afx_msg void OnNew();
	afx_msg void OnPitcherUpdate();
	afx_msg void OnPitcherAdd();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void BuildPlayerNameCombo(CString myFileName);
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDPLAYERS_H__06762501_8C3F_11D2_B0EE_444553540000__INCLUDED_)
