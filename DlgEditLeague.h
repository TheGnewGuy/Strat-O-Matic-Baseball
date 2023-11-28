#pragma once


// DlgEditLeague dialog

class DlgEditLeague : public CDialog
{
	DECLARE_DYNAMIC(DlgEditLeague)

public:
	DlgEditLeague(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgEditLeague();

// Dialog Data
	enum { IDD = IDD_LEAGUENAME };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
