// Registry.cpp : implementation file
//

#include "stdafx.h"
#include "baseball.h"
#include "Registry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SUBKEY_OPTIONS_FORMAT_STRING \
	"SOFTWARE\\Sunbeams and Rainbows\\Baseball\\Options\\%s"

/////////////////////////////////////////////////////////////////////////////
// Registry

Registry::Registry()
{
}

// Call with strLeagueDir+"\\HTML\\Teams" or
//    with strLeagueDir+"\\HTML\\Stats" or
Registry::Registry(CString strLeagueDir)
{
	m_strLeagueDir = strLeagueDir;
}

Registry::~Registry()
{
}

int Registry::GetRegistryOptions()
{
	return TRUE;
}

int Registry::OpenRegistryOptions()
{
	CString BackgroundPicture = "images/background.jpg";
	CString Index = "index.htm";
	CString TextColor = "Black";
	CString BGColor = "White";
	CString LinkColor = "Blue";
	CString VLinkColor = "Purple";

	char lpszSubKeyOptions[MAX_PATH];
	unsigned long regRC;
	LPDWORD regRCDisp = &regRC;

	sprintf_s(lpszSubKeyOptions,SUBKEY_OPTIONS_FORMAT_STRING,m_strLeagueDir);

	RegCreateKeyEx(
		HKEY_CURRENT_USER,
		lpszSubKeyOptions,
		0,
		"",
		REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS,
		0,
		&m_RegistryKey,
		regRCDisp);

	// Check to see if this is Key was just created
	// If it was, fill it in with defaults
	if (regRC == REG_CREATED_NEW_KEY)	// Value of 1 (2 = found)
	{
		RegSetValueEx(m_RegistryKey,_T("BackgroundPicture"),0,REG_SZ,
			(unsigned char*)BackgroundPicture.operator LPCTSTR(),BackgroundPicture.GetLength()+1);
		RegSetValueEx(m_RegistryKey,_T("Index"),0,REG_SZ,
			(unsigned char*)Index.operator LPCTSTR(),Index.GetLength()+1);
		RegSetValueEx(m_RegistryKey,_T("TextColor"),0,REG_SZ,
			(unsigned char*)TextColor.operator LPCTSTR(),TextColor.GetLength()+1);
		RegSetValueEx(m_RegistryKey,_T("BGColor"),0,REG_SZ,
			(unsigned char*)BGColor.operator LPCTSTR(),BGColor.GetLength()+1);
		RegSetValueEx(m_RegistryKey,_T("LinkColor"),0,REG_SZ,
			(unsigned char*)LinkColor.operator LPCTSTR(),LinkColor.GetLength()+1);
		RegSetValueEx(m_RegistryKey,_T("VLinkColor"),0,REG_SZ,
			(unsigned char*)VLinkColor.operator LPCTSTR(),VLinkColor.GetLength()+1);
		m_strBackgroundPicture = BackgroundPicture;
		m_strIndex = Index;
		m_strBGColor = BGColor;
		m_strLinkColor = LinkColor;
		m_strVLinkColor = VLinkColor;
		m_strTextColor = TextColor;
	}
	return TRUE;
}

int Registry::CloseRegistryOptions()
{
	RegCloseKey(m_RegistryKey);
	return TRUE;
}

CString Registry::GetRegistryOptionIndex()
{
	DWORD dwSize;

	OpenRegistryOptions();
	// Get the size of the data
	if (RegQueryValueEx(m_RegistryKey,_T("Index"),NULL,
		NULL,NULL,&dwSize) == ERROR_SUCCESS )
	{
		// Now go and get the data
		CString strType;
		LONG lRet = RegQueryValueEx( m_RegistryKey, 
			_T("Index"), NULL, NULL,
			(LPBYTE)strType.GetBuffer( dwSize ), &dwSize );
		strType.ReleaseBuffer();
		// Store the data
		if ( lRet == ERROR_SUCCESS )
			m_strIndex = strType;
	}
	CloseRegistryOptions();
	return m_strIndex;
}

CString Registry::GetRegistryOptionBackgroundPicture()
{
	DWORD dwSize;

	OpenRegistryOptions();
	// Get the size of the data
	if (RegQueryValueEx(m_RegistryKey,_T("BackgroundPicture"),NULL,
		NULL,NULL,&dwSize) == ERROR_SUCCESS )
	{
		// Now go and get the data
		CString strType;
		LONG lRet = RegQueryValueEx( m_RegistryKey, 
			_T("BackgroundPicture"), NULL, NULL,
			(LPBYTE)strType.GetBuffer( dwSize ), &dwSize );
		strType.ReleaseBuffer();
		// Store the data
		if ( lRet == ERROR_SUCCESS )
			m_strBackgroundPicture = strType;
	}
	CloseRegistryOptions();
	return m_strBackgroundPicture;
}

CString Registry::GetRegistryOptionTextColor()
{
	DWORD dwSize;

	OpenRegistryOptions();
	// Get the size of the data
	if (RegQueryValueEx(m_RegistryKey,_T("TextColor"),NULL,
		NULL,NULL,&dwSize) == ERROR_SUCCESS )
	{
		// Now go and get the data
		CString strType;
		LONG lRet = RegQueryValueEx( m_RegistryKey, 
			_T("TextColor"), NULL, NULL,
			(LPBYTE)strType.GetBuffer( dwSize ), &dwSize );
		strType.ReleaseBuffer();
		// Store the data
		if ( lRet == ERROR_SUCCESS )
			m_strTextColor = strType;
	}
	CloseRegistryOptions();
	return m_strTextColor;
}

CString Registry::GetRegistryOptionLinkColor()
{
	DWORD dwSize;

	OpenRegistryOptions();
	// Get the size of the data
	if (RegQueryValueEx(m_RegistryKey,_T("LinkColor"),NULL,
		NULL,NULL,&dwSize) == ERROR_SUCCESS )
	{
		// Now go and get the data
		CString strType;
		LONG lRet = RegQueryValueEx( m_RegistryKey, 
			_T("LinkColor"), NULL, NULL,
			(LPBYTE)strType.GetBuffer( dwSize ), &dwSize );
		strType.ReleaseBuffer();
		// Store the data
		if ( lRet == ERROR_SUCCESS )
			m_strLinkColor = strType;
	}
	CloseRegistryOptions();
	return m_strLinkColor;
}

CString Registry::GetRegistryOptionBGColor()
{
	DWORD dwSize;

	OpenRegistryOptions();
	// Get the size of the data
	if (RegQueryValueEx(m_RegistryKey,_T("BGColor"),NULL,
		NULL,NULL,&dwSize) == ERROR_SUCCESS )
	{
		// Now go and get the data
		CString strType;
		LONG lRet = RegQueryValueEx( m_RegistryKey, 
			_T("BGColor"), NULL, NULL,
			(LPBYTE)strType.GetBuffer( dwSize ), &dwSize );
		strType.ReleaseBuffer();
		// Store the data
		if ( lRet == ERROR_SUCCESS )
			m_strBGColor = strType;
	}
	CloseRegistryOptions();
	return m_strBGColor;
}

CString Registry::GetRegistryOptionVLinkColor()
{
	DWORD dwSize;

	OpenRegistryOptions();
	// Get the size of the data
	if (RegQueryValueEx(m_RegistryKey,_T("VLinkColor"),NULL,
		NULL,NULL,&dwSize) == ERROR_SUCCESS )
	{
		// Now go and get the data
		CString strType;
		LONG lRet = RegQueryValueEx( m_RegistryKey, 
			_T("VLinkColor"), NULL, NULL,
			(LPBYTE)strType.GetBuffer( dwSize ), &dwSize );
		strType.ReleaseBuffer();
		// Store the data
		if ( lRet == ERROR_SUCCESS )
			m_strVLinkColor = strType;
	}
	CloseRegistryOptions();
	return m_strVLinkColor;
}

int Registry::SetRegistryOptionBackgroundPicture(CString strPicture)
{
	m_strBackgroundPicture = strPicture;
	OpenRegistryOptions();
	RegSetValueEx(m_RegistryKey,_T("BackgroundPicture"),0,REG_SZ,
		(unsigned char*)m_strBackgroundPicture.operator LPCTSTR(),m_strBackgroundPicture.GetLength()+1);
	CloseRegistryOptions();
	return TRUE;
}

int Registry::SetRegistryOptionIndex(CString strIndex)
{
	m_strIndex = strIndex;
	OpenRegistryOptions();
	RegSetValueEx(m_RegistryKey,_T("Index"),0,REG_SZ,
		(unsigned char*)m_strIndex.operator LPCTSTR(),m_strIndex.GetLength()+1);
	CloseRegistryOptions();
	return TRUE;
}

int Registry::SetRegistryOptionTextColor(CString strTextColor)
{
	m_strTextColor = strTextColor;
	OpenRegistryOptions();
	RegSetValueEx(m_RegistryKey,_T("TextColor"),0,REG_SZ,
		(unsigned char*)m_strTextColor.operator LPCTSTR(),m_strTextColor.GetLength()+1);
	CloseRegistryOptions();
	return TRUE;
}

int Registry::SetRegistryOptionBGColor(CString strBGColor)
{
	m_strBGColor = strBGColor;
	OpenRegistryOptions();
	RegSetValueEx(m_RegistryKey,_T("BGColor"),0,REG_SZ,
		(unsigned char*)m_strBGColor.operator LPCTSTR(),m_strBGColor.GetLength()+1);
	CloseRegistryOptions();
	return TRUE;
}

int Registry::SetRegistryOptionLinkColor(CString strLinkColor)
{
	m_strLinkColor = strLinkColor;
	OpenRegistryOptions();
	RegSetValueEx(m_RegistryKey,_T("LinkColor"),0,REG_SZ,
		(unsigned char*)m_strLinkColor.operator LPCTSTR(),m_strLinkColor.GetLength()+1);
	CloseRegistryOptions();
	return TRUE;
}

int Registry::SetRegistryOptionVLinkColor(CString strVLinkColor)
{
	m_strVLinkColor = strVLinkColor;
	OpenRegistryOptions();
	RegSetValueEx(m_RegistryKey,_T("VLinkColor"),0,REG_SZ,
		(unsigned char*)m_strVLinkColor.operator LPCTSTR(),m_strVLinkColor.GetLength()+1);
	CloseRegistryOptions();
	return TRUE;
}
