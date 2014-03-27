// Pitcher.h : Implementation of the CPitcher class



// CPitcher implementation

// code generated on Thursday, March 27, 2014, 6:39 PM

#include "stdafx.h"
#include "Pitcher.h"
IMPLEMENT_DYNAMIC(CPitcher, CRecordset)

CPitcher::CPitcher(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_PitcherID = 0;
	m_FirstName = L"";
	m_LastName = L"";
	m_OBChanceHomeRun = L"";
	m_OBChanceTriple = L"";
	m_OBChanceDouble = L"";
	m_OBChanceSingle = L"";
	m_OBChanceWalk = L"";
	m_ChanceDoublePlay = L"";
	m_OBChanceHomeRunRight = L"";
	m_OBChanceTripleRight = L"";
	m_OBChanceDoubleRight = L"";
	m_OBChanceSingleRight = L"";
	m_OBChanceWalkRight = L"";
	m_ChanceDoublePlayRight = L"";
	m_OBChanceHomeRunLeft = L"";
	m_OBChanceTripleLeft = L"";
	m_OBChanceDoubleLeft = L"";
	m_OBChanceSingleLeft = L"";
	m_OBChanceWalkLeft = L"";
	m_ChanceDoublePlayLeft = L"";
	m_OBChanceBasic = L"";
	m_OBChanceLeft = L"";
	m_OBChanceRight = L"";
	m_Starter = 0;
	m_Relief = 0;
	m_Throws = 0;
	m_Bunting = 0;
	m_Hold = 0;
	m_WP = 0;
	m_Balk = 0;
	m_PitcherField = 0;
	m_ER1 = 0;
	m_TeamID = 0;
	m_LastUpdateTime;
	m_nFields = 35;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CPitcher::GetDefaultConnect()
{
	return _T("DSN=MS Access Database;DBQ=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball\\Baseball.accdb;DefaultDir=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CPitcher::GetDefaultSQL()
{
	return _T("[Pitcher]");
}

void CPitcher::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[PitcherID]"), m_PitcherID);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Text(pFX, _T("[OBChanceHomeRun]"), m_OBChanceHomeRun);
	RFX_Text(pFX, _T("[OBChanceTriple]"), m_OBChanceTriple);
	RFX_Text(pFX, _T("[OBChanceDouble]"), m_OBChanceDouble);
	RFX_Text(pFX, _T("[OBChanceSingle]"), m_OBChanceSingle);
	RFX_Text(pFX, _T("[OBChanceWalk]"), m_OBChanceWalk);
	RFX_Text(pFX, _T("[ChanceDoublePlay]"), m_ChanceDoublePlay);
	RFX_Text(pFX, _T("[OBChanceHomeRunRight]"), m_OBChanceHomeRunRight);
	RFX_Text(pFX, _T("[OBChanceTripleRight]"), m_OBChanceTripleRight);
	RFX_Text(pFX, _T("[OBChanceDoubleRight]"), m_OBChanceDoubleRight);
	RFX_Text(pFX, _T("[OBChanceSingleRight]"), m_OBChanceSingleRight);
	RFX_Text(pFX, _T("[OBChanceWalkRight]"), m_OBChanceWalkRight);
	RFX_Text(pFX, _T("[ChanceDoublePlayRight]"), m_ChanceDoublePlayRight);
	RFX_Text(pFX, _T("[OBChanceHomeRunLeft]"), m_OBChanceHomeRunLeft);
	RFX_Text(pFX, _T("[OBChanceTripleLeft]"), m_OBChanceTripleLeft);
	RFX_Text(pFX, _T("[OBChanceDoubleLeft]"), m_OBChanceDoubleLeft);
	RFX_Text(pFX, _T("[OBChanceSingleLeft]"), m_OBChanceSingleLeft);
	RFX_Text(pFX, _T("[OBChanceWalkLeft]"), m_OBChanceWalkLeft);
	RFX_Text(pFX, _T("[ChanceDoublePlayLeft]"), m_ChanceDoublePlayLeft);
	RFX_Text(pFX, _T("[OBChanceBasic]"), m_OBChanceBasic);
	RFX_Text(pFX, _T("[OBChanceLeft]"), m_OBChanceLeft);
	RFX_Text(pFX, _T("[OBChanceRight]"), m_OBChanceRight);
	RFX_Byte(pFX, _T("[Starter]"), m_Starter);
	RFX_Byte(pFX, _T("[Relief]"), m_Relief);
	RFX_Byte(pFX, _T("[Throws]"), m_Throws);
	RFX_Byte(pFX, _T("[Bunting]"), m_Bunting);
	RFX_Byte(pFX, _T("[Hold]"), m_Hold);
	RFX_Byte(pFX, _T("[WP]"), m_WP);
	RFX_Byte(pFX, _T("[Balk]"), m_Balk);
	RFX_Byte(pFX, _T("[PitcherField]"), m_PitcherField);
	RFX_Byte(pFX, _T("[ER1]"), m_ER1);
	RFX_Long(pFX, _T("[TeamID]"), m_TeamID);
	RFX_Date(pFX, _T("[LastUpdateTime]"), m_LastUpdateTime);

}
/////////////////////////////////////////////////////////////////////////////
// CPitcher diagnostics

#ifdef _DEBUG
void CPitcher::AssertValid() const
{
	CRecordset::AssertValid();
}

void CPitcher::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


