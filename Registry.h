#if !defined(AFX_REGISTRY_H__5630B8C0_8A6E_11D4_BC6A_00C04FC98650__INCLUDED_)
#define AFX_REGISTRY_H__5630B8C0_8A6E_11D4_BC6A_00C04FC98650__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Registry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// Registry window

class Registry : public CObject
{
// Construction
public:
	Registry();
	Registry(CString strLeagueDir);

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Registry)
	//}}AFX_VIRTUAL

// Implementation
public:
	int SetRegistryOptionVLinkColor(CString strVLinkColor);
	int SetRegistryOptionLinkColor(CString strLinkColor);
	int SetRegistryOptionBGColor(CString strBGColor);
	int SetRegistryOptionTextColor(CString strTextColor);
	int SetRegistryOptionIndex(CString strIndex);
	int SetRegistryOptionBackgroundPicture(CString strPicture);
	CString GetRegistryOptionVLinkColor();
	CString GetRegistryOptionBGColor();
	CString GetRegistryOptionLinkColor();
	CString GetRegistryOptionTextColor();
	CString GetRegistryOptionBackgroundPicture();
	CString GetRegistryOptionIndex();
	virtual ~Registry();

	// Generated message map functions
protected:

private:
	int CloseRegistryOptions();
	CString m_strLeagueDir;
	CString m_strLinkColor;
	CString m_strVLinkColor;
	CString m_strTextColor;
	CString m_strBGColor;
	CString m_strIndex;
	CString m_strBackgroundPicture;
	HKEY m_RegistryKey;
	int OpenRegistryOptions();
	int GetRegistryOptions();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTRY_H__5630B8C0_8A6E_11D4_BC6A_00C04FC98650__INCLUDED_)
