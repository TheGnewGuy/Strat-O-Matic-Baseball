// BaseballDoc.h : interface of the CBaseballDoc class
//
/////////////////////////////////////////////////////////////////////////////

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
	static CBaseballDoc * GetDoc();

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
	CString GetTeams(CString strDir);
	CString GetLeagues(BOOL baseFlag);
	PropertySheetBatters* m_pPropertySheetBatters;
	PropertySheetPitchers* m_pPropertySheetPitchers;
	int m_StatCount;
	void BuildPlayerArray(CStringArray* arrayFileNames, CString strLeagueName, CString strDivisionName, CString strConferenceName, int iDiv);
	void HTMLLeagueStats(CString strLeagueName);
	void EditTeams(CString strDir);
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
	afx_msg void OnTeamsEditTeams();
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
	CDatabase m_pDatabase;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEBALLDOC_H__20B4846F_70F7_11D2_B0EE_444553540000__INCLUDED_)
