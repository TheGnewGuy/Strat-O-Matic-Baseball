// Batter.h : Implementation of the CBatter class



// CBatter implementation

// code generated on Thursday, March 27, 2014, 6:37 PM

#include "stdafx.h"
#include "Batter.h"
IMPLEMENT_DYNAMIC(CBatter, CRecordset)

CBatter::CBatter(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_BatterID = 0;
	m_FirstName = L"";
	m_LastName = L"";
	m_Pitcher = 0;
	m_Catcher = 0;
	m_FirstBase = 0;
	m_SecondBase = 0;
	m_ShortStop = 0;
	m_ThirdBase = 0;
	m_LeftField = 0;
	m_CenterField = 0;
	m_RightField = 0;
	m_Bunting = 0;
	m_HitRun = 0;
	m_Running = 0;
	m_Stealing = 0;
	m_CatchArm = 0;
	m_OutArm = 0;
	m_PowerRight = 0;
	m_PowerLeft = 0;
	m_Pass = 0;
	m_TRate = 0;
	m_ER1 = 0;
	m_ER2 = 0;
	m_ER3 = 0;
	m_ER4 = 0;
	m_ER5 = 0;
	m_ER6 = 0;
	m_ER7 = 0;
	m_ER8 = 0;
	m_ER9 = 0;
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
	m_BatterHits = 0;
	m_TeamID = 0;
	m_LastUpdateTime;
	m_nFields = 55;
	m_nDefaultType = dynaset;
}
//#error Security Issue: The connection string may contain a password
// The connection string below may contain plain text passwords and/or
// other sensitive information. Please remove the #error after reviewing
// the connection string for any security related issues. You may want to
// store the password in some other form or use a different user authentication.
CString CBatter::GetDefaultConnect()
{
	return _T("DSN=MS Access Database;DBQ=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball\\Baseball.accdb;DefaultDir=C:\\Family\\SOURCE\\C\\Strat-O-Matic-Baseball;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CBatter::GetDefaultSQL()
{
	return _T("[Batter]");
}

void CBatter::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// Macros such as RFX_Text() and RFX_Int() are dependent on the
// type of the member variable, not the type of the field in the database.
// ODBC will try to automatically convert the column value to the requested type
	RFX_Long(pFX, _T("[BatterID]"), m_BatterID);
	RFX_Text(pFX, _T("[FirstName]"), m_FirstName);
	RFX_Text(pFX, _T("[LastName]"), m_LastName);
	RFX_Byte(pFX, _T("[Pitcher]"), m_Pitcher);
	RFX_Byte(pFX, _T("[Catcher]"), m_Catcher);
	RFX_Byte(pFX, _T("[FirstBase]"), m_FirstBase);
	RFX_Byte(pFX, _T("[SecondBase]"), m_SecondBase);
	RFX_Byte(pFX, _T("[ShortStop]"), m_ShortStop);
	RFX_Byte(pFX, _T("[ThirdBase]"), m_ThirdBase);
	RFX_Byte(pFX, _T("[LeftField]"), m_LeftField);
	RFX_Byte(pFX, _T("[CenterField]"), m_CenterField);
	RFX_Byte(pFX, _T("[RightField]"), m_RightField);
	RFX_Byte(pFX, _T("[Bunting]"), m_Bunting);
	RFX_Byte(pFX, _T("[HitRun]"), m_HitRun);
	RFX_Byte(pFX, _T("[Running]"), m_Running);
	RFX_Byte(pFX, _T("[Stealing]"), m_Stealing);
	RFX_Byte(pFX, _T("[CatchArm]"), m_CatchArm);
	RFX_Byte(pFX, _T("[OutArm]"), m_OutArm);
	RFX_Byte(pFX, _T("[PowerRight]"), m_PowerRight);
	RFX_Byte(pFX, _T("[PowerLeft]"), m_PowerLeft);
	RFX_Byte(pFX, _T("[Pass]"), m_Pass);
	RFX_Byte(pFX, _T("[TRate]"), m_TRate);
	RFX_Byte(pFX, _T("[ER1]"), m_ER1);
	RFX_Byte(pFX, _T("[ER2]"), m_ER2);
	RFX_Byte(pFX, _T("[ER3]"), m_ER3);
	RFX_Byte(pFX, _T("[ER4]"), m_ER4);
	RFX_Byte(pFX, _T("[ER5]"), m_ER5);
	RFX_Byte(pFX, _T("[ER6]"), m_ER6);
	RFX_Byte(pFX, _T("[ER7]"), m_ER7);
	RFX_Byte(pFX, _T("[ER8]"), m_ER8);
	RFX_Byte(pFX, _T("[ER9]"), m_ER9);
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
	RFX_Byte(pFX, _T("[BatterHits]"), m_BatterHits);
	RFX_Long(pFX, _T("[TeamID]"), m_TeamID);
	RFX_Date(pFX, _T("[LastUpdateTime]"), m_LastUpdateTime);

}
/////////////////////////////////////////////////////////////////////////////
// CBatter diagnostics

#ifdef _DEBUG
void CBatter::AssertValid() const
{
	CRecordset::AssertValid();
}

void CBatter::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


