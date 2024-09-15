#include "afxwin.h"

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// DlgCopyPlayer.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgCopyPlayer dialog

class DlgCopyPlayer : public CDialog
{
	DECLARE_DYNAMIC(DlgCopyPlayer)

public:
	// Construction
	DlgCopyPlayer(CWnd* pParent = NULL);   // standard constructor
	virtual ~DlgCopyPlayer();

// Dialog Data
	//{{AFX_DATA(DlgCopyPlayer)
	enum { IDD = IDD_SELPLAYER1
	};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_playerListBox;
	CStringArray m_arrayPlayers;
	CString m_selection;
	int m_Index;

	virtual BOOL OnInitDialog();
	virtual void OnOK();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.
