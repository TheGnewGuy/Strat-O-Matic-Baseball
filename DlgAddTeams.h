#if !defined(AFX_DLGADDTEAMS_H__348D1D61_8B7A_11D2_B0EE_444553540000__INCLUDED_)
#define AFX_DLGADDTEAMS_H__348D1D61_8B7A_11D2_B0EE_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgAddTeams.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgAddTeams dialog

class DlgAddTeams : public CDialog
{
// Construction
public:
	CStringArray m_arrayTeams;
	DlgAddTeams(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAddTeams)
	enum { IDD = IDD_ADDTEAMS1 };
	CListBox	m_CListBoxTeams;
	CString	m_Division0;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAddTeams)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgAddTeams)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDTEAMS_H__348D1D61_8B7A_11D2_B0EE_444553540000__INCLUDED_)
