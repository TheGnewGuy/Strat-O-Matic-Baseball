#if !defined(AFX_DLGADDDIVISION_H__253045C1_8B54_11D2_B0EE_444553540000__INCLUDED_)
#define AFX_DLGADDDIVISION_H__253045C1_8B54_11D2_B0EE_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgAddDivision.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgAddDivision dialog

class DlgAddDivision : public CDialog
{
// Construction
public:
	DlgAddDivision(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgAddDivision)
	enum { IDD = IDD_DIVISION1 };
	CString	m_Division1;
	CString	m_Division2;
	CString	m_Division3;
	CString	m_Division4;
	CString	m_Division5;
	CString	m_Division6;
	CString	m_Conference0;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgAddDivision)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgAddDivision)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGADDDIVISION_H__253045C1_8B54_11D2_B0EE_444553540000__INCLUDED_)
