// Divisions.h : Implementation of the CDivisions class



// CDivisions implementation

// code generated on Thursday, March 27, 2014, 6:38 PM

#include "stdafx.h"
#include "Divisions.h"
IMPLEMENT_DYNAMIC(CDivisions, CRecordset)

CDivisions::CDivisions(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_DivisionID = 0;
	m_DivisionName = L"";
	m_ConferenceID = 0;
	m_LastUpdateTime;
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CDivisions::GetDefaultConnect()
{
	return _T("DSN=MS Access Database;DBQ=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball\\Baseball.accdb;DefaultDir=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CDivisions::GetDefaultSQL()
{
	return _T("[Divisions]");
}

void CDivisions::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[DivisionID]"), m_DivisionID);
	RFX_Text(pFX, _T("[DivisionName]"), m_DivisionName);
	RFX_Long(pFX, _T("[ConferenceID]"), m_ConferenceID);
	RFX_Date(pFX, _T("[LastUpdateTime]"), m_LastUpdateTime);

}
/////////////////////////////////////////////////////////////////////////////
// CDivisions diagnostics

#ifdef _DEBUG
void CDivisions::AssertValid() const
{
	CRecordset::AssertValid();
}

void CDivisions::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


