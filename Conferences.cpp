// Conferences.h : Implementation of the CConferences class



// CConferences implementation

// code generated on Thursday, March 27, 2014, 6:38 PM

#include "stdafx.h"
#include "Conferences.h"
IMPLEMENT_DYNAMIC(CConferences, CRecordset)

CConferences::CConferences(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ConferenceID = 0;
	m_ConferenceName = L"";
	m_LeagueID = 0;
	m_LastUpdateTime;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CConferences::GetDefaultConnect()
{
	return _T("DSN=MS Access Database;DBQ=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball\\Baseball.accdb;DefaultDir=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CConferences::GetDefaultSQL()
{
	return _T("[Conferences]");
}

void CConferences::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[ConferenceID]"), m_ConferenceID);
	RFX_Text(pFX, _T("[ConferenceName]"), m_ConferenceName);
	RFX_Long(pFX, _T("[LeagueID]"), m_LeagueID);
	RFX_Date(pFX, _T("[LastUpdateTime]"), m_LastUpdateTime);

}
/////////////////////////////////////////////////////////////////////////////
// CConferences diagnostics

#ifdef _DEBUG
void CConferences::AssertValid() const
{
	CRecordset::AssertValid();
}

void CConferences::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


