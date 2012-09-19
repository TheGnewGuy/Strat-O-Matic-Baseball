#if !defined(AFX_SPLASH_H__CBCC3BE4_188A_11D4_89F8_D43B2803D279__INCLUDED_)
#define AFX_SPLASH_H__CBCC3BE4_188A_11D4_89F8_D43B2803D279__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "resource.h"
// Splash.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBigIcon window

class CBigIcon : public CButton
{
// Attributes
public:

// Operations
public:
	void SizeToContent();

// Implementation
protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);

	//{{AFX_MSG(CBigIcon)
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
// CSplashWnd dialog

class CSplashWnd : public CDialog
{
// Construction
public:
	BOOL Create(CWnd* pParent);

// Dialog Data
	//{{AFX_DATA(CSplashWnd)
	enum { IDD = IDD_SPLASH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	CBigIcon m_icon; // self-draw button
	CFont m_font;   // light version of dialog font

	// Generated message map functions
	//{{AFX_MSG(CSplashWnd)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPLASH_H__CBCC3BE4_188A_11D4_89F8_D43B2803D279__INCLUDED_)
