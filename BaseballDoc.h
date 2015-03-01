// BaseballDoc.h : interface of the CBaseballDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include "sqlite3.h"

#if !defined(AFX_BASEBALLDOC_H__20B4846F_70F7_11D2_B0EE_444553540000__INCLUDED_)
#define AFX_BASEBALLDOC_H__20B4846F_70F7_11D2_B0EE_444553540000__INCLUDED_

#include "FileStruct.h"	// Added by ClassView
#include "dialogs.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CBaseballDoc : public CDocument
{
protected: // create from serialization only
	CBaseballDoc();
	DECLARE_DYNCREATE(CBaseballDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseballDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
//	CString GetTeams(CString strDir);
	int GetTeams(int leagueID);
	int GetLeagues(BOOL baseFlag);
	PropertySheetBatters* m_pPropertySheetBatters;
	PropertySheetPitchers* m_pPropertySheetPitchers;
	int m_StatCount;
	void BuildPlayerArray(CStringArray* arrayFileNames, CString strLeagueName, CString strDivisionName, CString strConferenceName, int iDiv);
	void HTMLLeagueStats(CString strLeagueName);
//	void EditTeams(CString strDir);
	void EditTeams(int leagueID);
	void ExportHTML(CString strDir);
	void ExportHTMLFile(CString strDir, CString strTeamName);
	BOOL GetNormalView();
	void SetAllFormsFalse();
	BOOL GetStatisticsForm();
	BOOL GetScoresheetFormXtra();
	BOOL GetScoresheetForm();
	virtual ~CBaseballDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	BOOL m_NormalView;
	BOOL m_StatisticsForm;
	BOOL m_ScoresheetFormXtra;
	BOOL m_ScoresheetForm;
	//{{AFX_MSG(CBaseballDoc)
	afx_msg void OnFormsScoresheetform();
	afx_msg void OnFormsScoresheetformxtra();
	afx_msg void OnFormsStatistcsform();
	afx_msg void OnUpdateFormsScoresheetform(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFormsScoresheetformxtra(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFormsStatistcsform(CCmdUI* pCmdUI);
	afx_msg void OnViewNormal();
	afx_msg void OnUpdateViewNormal(CCmdUI* pCmdUI);
	afx_msg void OnLeaguesAddleague();
	afx_msg void OnTeamsAddteams();
	afx_msg void OnFileExportLeagueTeams();
	afx_msg void OnFileExportHTMLLeagueTeams();
	afx_msg void OnTeamsEditLeagueTeams();
	afx_msg void OnStatisticsHTMLLeagueStats();
	afx_msg void OnFileExportHtmlLeagueTeamsAll();
	afx_msg void OnFileExportLeagueTeamsAll();
	afx_msg void OnPlayersAddEditBatters();
	afx_msg void OnPlayersAddEditPitchers();
	afx_msg void OnLeaguesLeagueOptionsHTML();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Export(CString strDir);
	void ExportFile(CString strDir, CString strTeamName);
	CString m_Conference4;
	CString m_Conference3;
	CString m_Conference2;
	CString m_Conference1;
	CString m_NewLeagueName;
public:
	CString m_DBFileName;
	int m_dbOpen;
	sqlite3 *m_db;
	sqlite3_stmt *m_stmt;
	afx_msg void OnFileOpen();
	int OpenDatabase();
	int DBSetForeginKeys(bool OnOff);
	int DBVersion();
	afx_msg void OnLeaguesEditLeague();
	int GetLeagueID(CStringA strLeagueName);
	int GetTeamID(CStringA strTeamName, int LeagueID);
	struct m_TeamRecord{
		int TeamID;
		CStringA TeamName;
		CStringA TeamNameShort;
		CStringA BallparkName;
		int HomeWins;
		int HomeLosses;
		int AwayWins;
		int AwayLosses;
		int LeagueID;
		int ConferenceID;
		int DivisionID;
		int TeamYear;
		int BaseTeam;
		CStringA CreateTime;
		CStringA LastUpdateTime;
	};
	struct m_LeagueRecord{
		int LeagueID;
		CStringA LeagueName;
		int NumberOfConferences;
		int NumberOfDivisions;
		int BaseLeague;
		CStringA CreateTime;
		CStringA LastUpdateTime;
	};
	struct m_ConferenceRecord{
		int ConferenceID;
		CStringA ConferenceName;
		int LeagueID;
		int BaseConference;
		CStringA CreateTime;
		CStringA LastUpdateTime;
	};
	struct m_DivisionRecord{
		int DivisionID;
		CStringA DivisionName;
		int LeagueID;
		int ConferenceID;
		int BaseDivisions;
		CStringA CreateTime;
		CStringA LastUpdateTime;
	};
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
		float OBChanceHomeRun;
		float OBChanceTriple;
		float OBChanceDouble;
		float OBChanceSingle;
		float OBChanceWalk;
		float ChanceDoublePlay;
		float OBChanceHomeRunRight;
		float OBChanceTripleRight;
		float OBChanceDoubleRight;
		float OBChanceSingleRight;
		float OBChanceWalkRight;
		float ChanceDoublePlayRight;
		float OBChanceHomeRunLeft;
		float OBChanceTripleLeft;
		float OBChanceDoubleLeft;
		float OBChanceSingleLeft;
		float OBChanceWalkLeft;
		float ChanceDoublePlayLeft;
		float OBChanceBasic;
		float OBChanceLeft;
		float OBChanceRight;
		CStringA CreateTime;
		CStringA LastUpdateTime;
	};
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
		float AVG;
		float SLG;
		float OBP;
		int BatterID;
		int TeamID;
		CStringA CreateTime;
		CStringA LastUpdateTime;
	};
	struct m_PitcherRecord{
		int PitcherID;
		CStringA FirstName;
		CStringA LastName;
		float OBChanceHomeRun;
		float OBChanceTriple;
		float OBChanceDouble;
		float OBChanceSingle;
		float OBChanceWalk;
		float ChanceDoublePlay;
		float OBChanceHomeRunRight;
		float OBChanceTripleRight;
		float OBChanceDoubleRight;
		float OBChanceSingleRight;
		float OBChanceWalkRight;
		float ChanceDoublePlayRight;
		float OBChanceHomeRunLeft;
		float OBChanceTripleLeft;
		float OBChanceDoubleLeft;
		float OBChanceSingleLeft;
		float OBChanceWalkLeft;
		float ChanceDoublePlayLeft;
		float OBChanceBasic;
		float OBChanceLeft;
		float OBChanceRight;
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
	};
	struct m_PitcherStatsRecord{
		int PitcherStatsID;
		int Wins;
		int Loss;
		int Saves;
		float InningsPitched;
		int ER;
		int Hits;
		int Walks;
		int Strikeouts;
		int HomeRuns;
		int Games;
		int CompleteGames;
		int Starts;
		float ERA;
		float WHIP;
		int PitcherID;
		int TeamID;
		CStringA CreateTime;
		CStringA LastUpdateTime;
	};
	m_TeamRecord GetTeam(int TeamID);
	int TeamUpdate(m_TeamRecord TeamRecord);
	int LeagueUpdate(m_LeagueRecord LeagueRecord);
	int ConfUpdate(m_ConferenceRecord ConferenceRecord);
	int DivisionUpdate(m_DivisionRecord DIvisionRecord);
	int BatterUpdate(m_BatterRecord BatterRecord);
	int BatterStatsUpdate(m_BatterStatsRecord BatterStatsRecord);
	int PitcherUpdate(m_PitcherRecord PitcherRecord);
	int PitcherStatsUpdate(m_PitcherStatsRecord PitcherStatsRecord);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEBALLDOC_H__20B4846F_70F7_11D2_B0EE_444553540000__INCLUDED_)
