// BatterStats.h : Implementation of the CBatterStats class



// CBatterStats implementation

// code generated on Thursday, March 27, 2014, 6:38 PM

#include "stdafx.h"
#include "BatterStats.h"
IMPLEMENT_DYNAMIC(CBatterStats, CRecordset)

CBatterStats::CBatterStats(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_BatterStatsID = 0;
	m_AB = 0;
	m_Runs = 0;
	m_Hits = 0;
	m_RBI = 0;
	m_2B = 0;
	m_3B = 0;
	m_HomeRuns = 0;
	m_Walk = 0;
	m_StrikeOut = 0;
	m_ReachedOnError = 0;
	m_Sacrifice = 0;
	m_StolenBase = 0;
	m_CS = 0;
	m_Games = 0;
	m_HBP = 0;
	m_AVG = 0.0;
	m_SLG = 0.0;
	m_OBP = 0.0;
	m_BatterID = 0;
	m_TeamID = 0;
	m_LastUpdateTime;
	m_nFields = 22;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CBatterStats::GetDefaultConnect()
{
	return _T("DSN=MS Access Database;DBQ=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball\\Baseball.accdb;DefaultDir=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CBatterStats::GetDefaultSQL()
{
	return _T("[BatterStats]");
}

void CBatterStats::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[BatterStatsID]"), m_BatterStatsID);
	RFX_Int(pFX, _T("[AB]"), m_AB);
	RFX_Int(pFX, _T("[Runs]"), m_Runs);
	RFX_Int(pFX, _T("[Hits]"), m_Hits);
	RFX_Int(pFX, _T("[RBI]"), m_RBI);
	RFX_Int(pFX, _T("[2B]"), m_2B);
	RFX_Int(pFX, _T("[3B]"), m_3B);
	RFX_Int(pFX, _T("[HomeRuns]"), m_HomeRuns);
	RFX_Int(pFX, _T("[Walk]"), m_Walk);
	RFX_Int(pFX, _T("[StrikeOut]"), m_StrikeOut);
	RFX_Int(pFX, _T("[ReachedOnError]"), m_ReachedOnError);
	RFX_Int(pFX, _T("[Sacrifice]"), m_Sacrifice);
	RFX_Int(pFX, _T("[StolenBase]"), m_StolenBase);
	RFX_Int(pFX, _T("[CS]"), m_CS);
	RFX_Int(pFX, _T("[Games]"), m_Games);
	RFX_Int(pFX, _T("[HBP]"), m_HBP);
	RFX_Single(pFX, _T("[AVG]"), m_AVG);
	RFX_Single(pFX, _T("[SLG]"), m_SLG);
	RFX_Single(pFX, _T("[OBP]"), m_OBP);
	RFX_Long(pFX, _T("[BatterID]"), m_BatterID);
	RFX_Long(pFX, _T("[TeamID]"), m_TeamID);
	RFX_Date(pFX, _T("[LastUpdateTime]"), m_LastUpdateTime);

}
/////////////////////////////////////////////////////////////////////////////
// CBatterStats diagnostics

#ifdef _DEBUG
void CBatterStats::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBatterStats::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


