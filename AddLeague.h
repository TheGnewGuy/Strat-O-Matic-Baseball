#include "afxwin.h"
#define AFX_ADDLEAGUE_H__01BF1281_8A03_11D2_B0EE_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// AddLeague.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AddLeague dialog

class AddLeague : public CDialog
{
// Construction
public:
	AddLeague(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AddLeague)
	enum { IDD = IDD_LEAGUE1 };
	CString	m_NewLeagueName;
	CString	m_Conference1;
	CString	m_Conference2;
	CString	m_Conference3;
	CString	m_Conference4;
	CString	m_Conference5;
	CString	m_Conference6;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AddLeague)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AddLeague)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
#pragma once
#pragma once


// AddLeagueName dialog

class AddLeagueName : public CDialog
{
	DECLARE_DYNAMIC(AddLeagueName)

public:
	AddLeagueName(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddLeagueName();

// Dialog Data
	enum { IDD = IDD_LEAGUENAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	CString m_NewLeagueName;
	int m_Year;
};
