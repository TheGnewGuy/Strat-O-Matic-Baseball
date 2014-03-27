// Leagues.h : Implementation of the CLeagues class



// CLeagues implementation

// code generated on Thursday, March 27, 2014, 6:39 PM

#include "stdafx.h"
#include "Leagues.h"
IMPLEMENT_DYNAMIC(CLeagues, CRecordset)

CLeagues::CLeagues(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_LeagueID = 0;
	m_LeagueName = L"";
	m_NumberOfConferences = 0;
	m_NumberOfDivisions = 0;
	m_LastUpdateTime;
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CLeagues::GetDefaultConnect()
{
	return _T("DSN=MS Access Database;DBQ=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball\\Baseball.accdb;DefaultDir=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CLeagues::GetDefaultSQL()
{
	return _T("[Leagues]");
}

void CLeagues::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[LeagueID]"), m_LeagueID);
	RFX_Text(pFX, _T("[LeagueName]"), m_LeagueName);
	RFX_Int(pFX, _T("[NumberOfConferences]"), m_NumberOfConferences);
	RFX_Int(pFX, _T("[NumberOfDivisions]"), m_NumberOfDivisions);
	RFX_Date(pFX, _T("[LastUpdateTime]"), m_LastUpdateTime);

}
/////////////////////////////////////////////////////////////////////////////
// CLeagues diagnostics

#ifdef _DEBUG
void CLeagues::AssertValid() const
{
	CRecordset::AssertValid();
}

void CLeagues::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


