#pragma once
#include "afxwin.h"


// AddConference dialog

class AddConference : public CDialog
{
	DECLARE_DYNAMIC(AddConference)

public:
	AddConference(CWnd* pParent = NULL);   // standard constructor
	virtual ~AddConference();

// Dialog Data
	enum { IDD = IDD_CONFERENCE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_LeagueName;
	CString m_Conference1;
	CString m_Conference2;
	CString m_Conference3;
	CString m_Conference4;
	CString m_Conference5;
	CString m_Conference6;
	virtual void OnOK();
};
