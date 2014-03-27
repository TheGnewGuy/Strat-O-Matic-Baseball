// Baseball.h : main header file for the BASEBALL application
//

#if !defined(AFX_BASEBALL_H__20B48467_70F7_11D2_B0EE_444553540000__INCLUDED_)
#define AFX_BASEBALL_H__20B48467_70F7_11D2_B0EE_444553540000__INCLUDED_

#include "Splash.h"	// Added by ClassView
#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBaseballApp:
// See Baseball.cpp for the implementation of this class
//

class CBaseballApp : public CWinApp
{
public:
	CBaseballApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBaseballApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL OnIdle(LONG lCount);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBaseballApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CSplashWnd m_splash;
	DWORD m_dwSplashTime;
public:
//	afx_msg void OnFileOpen();
	afx_msg void OnFileOpen();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASEBALL_H__20B48467_70F7_11D2_B0EE_444553540000__INCLUDED_)
