// PitcherStats.h : Implementation of the CPitcherStats class



// CPitcherStats implementation

// code generated on Thursday, March 27, 2014, 6:39 PM

#include "stdafx.h"
#include "PitcherStats.h"
IMPLEMENT_DYNAMIC(CPitcherStats, CRecordset)

CPitcherStats::CPitcherStats(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_PitcherStatsID = 0;
	m_Wins = 0;
	m_Loss = 0;
	m_Saves = 0;
	m_InningsPitched = 0.0;
	m_ER = 0;
	m_Hits = 0;
	m_Walks = 0;
	m_Strikeouts = 0;
	m_HomeRuns = 0;
	m_Games = 0;
	m_CompleteGames = 0;
	m_Starts = 0;
	m_ERA = 0.0;
	m_WHIP = 0.0;
	m_PitcherID = 0;
	m_TeamID = 0;
	m_LastUpdateTime;
	m_nFields = 18;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CPitcherStats::GetDefaultConnect()
{
	return _T("DSN=MS Access Database;DBQ=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball\\Baseball.accdb;DefaultDir=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CPitcherStats::GetDefaultSQL()
{
	return _T("[PitcherStats]");
}

void CPitcherStats::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[PitcherStatsID]"), m_PitcherStatsID);
	RFX_Int(pFX, _T("[Wins]"), m_Wins);
	RFX_Int(pFX, _T("[Loss]"), m_Loss);
	RFX_Int(pFX, _T("[Saves]"), m_Saves);
	RFX_Single(pFX, _T("[InningsPitched]"), m_InningsPitched);
	RFX_Int(pFX, _T("[ER]"), m_ER);
	RFX_Int(pFX, _T("[Hits]"), m_Hits);
	RFX_Int(pFX, _T("[Walks]"), m_Walks);
	RFX_Int(pFX, _T("[Strikeouts]"), m_Strikeouts);
	RFX_Int(pFX, _T("[HomeRuns]"), m_HomeRuns);
	RFX_Int(pFX, _T("[Games]"), m_Games);
	RFX_Int(pFX, _T("[CompleteGames]"), m_CompleteGames);
	RFX_Int(pFX, _T("[Starts]"), m_Starts);
	RFX_Single(pFX, _T("[ERA]"), m_ERA);
	RFX_Single(pFX, _T("[WHIP]"), m_WHIP);
	RFX_Long(pFX, _T("[PitcherID]"), m_PitcherID);
	RFX_Long(pFX, _T("[TeamID]"), m_TeamID);
	RFX_Date(pFX, _T("[LastUpdateTime]"), m_LastUpdateTime);

}
/////////////////////////////////////////////////////////////////////////////
// CPitcherStats diagnostics

#ifdef _DEBUG
void CPitcherStats::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPitcherStats::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


