#if !defined(AFX_ADDTEAM_H__06762502_8C3F_11D2_B0EE_444553540000__INCLUDED_)
#define AFX_ADDTEAM_H__06762502_8C3F_11D2_B0EE_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AddTeam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AddTeam dialog

class AddTeam : public CDialog
{
// Construction
public:
	AddTeam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AddTeam)
	enum { IDD = IDD_TEAM1 };
	CString	m_TeamName;
	CString	m_ShortTeamName;
	CString	m_BallPark;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AddTeam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AddTeam)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
// dlgSelTeam dialog

class dlgSelTeam : public CDialog
{
// Construction
public:
	int m_selIndex;
	CStringArray m_arrayTeams;
	dlgSelTeam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(dlgSelTeam)
	enum { IDD = IDD_SELTEAM1 };
	CListBox	m_selTeamListBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(dlgSelTeam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(dlgSelTeam)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// DlgSelLeague dialog

class DlgSelLeague : public CDialog
{
// Construction
public:
	int m_selIndex;
	CStringArray m_arrayLeagues;
	DlgSelLeague(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgSelLeague)
	enum { IDD = IDD_SELLEAGUE1 };
	CListBox	m_selLeagueListBox;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgSelLeague)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgSelLeague)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
/////////////////////////////////////////////////////////////////////////////
// EditTeam dialog

class EditTeam : public CDialog
{
// Construction
public:
	EditTeam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(EditTeam)
	enum { IDD = IDD_TEAM1 };
	CString	m_BallPark;
	CString	m_ShortTeamName;
	CString	m_TeamName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(EditTeam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(EditTeam)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDTEAM_H__06762502_8C3F_11D2_B0EE_444553540000__INCLUDED_)
