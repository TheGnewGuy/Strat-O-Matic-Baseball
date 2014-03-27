// Batter.h : Declaration of the CBatter

#pragma once

// code generated on Thursday, March 27, 2014, 6:37 PM

class CBatter : public CRecordset
{
public:
	CBatter(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBatter)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_BatterID;	//BatterID Key
	CString	m_FirstName;
	CString	m_LastName;
	BYTE	m_Pitcher;
	BYTE	m_Catcher;
	BYTE	m_FirstBase;
	BYTE	m_SecondBase;
	BYTE	m_ShortStop;
	BYTE	m_ThirdBase;
	BYTE	m_LeftField;
	BYTE	m_CenterField;
	BYTE	m_RightField;
	BYTE	m_Bunting;
	BYTE	m_HitRun;
	BYTE	m_Running;
	BYTE	m_Stealing;
	BYTE	m_CatchArm;
	BYTE	m_OutArm;
	BYTE	m_PowerRight;
	BYTE	m_PowerLeft;
	BYTE	m_Pass;
	BYTE	m_TRate;
	BYTE	m_ER1;
	BYTE	m_ER2;
	BYTE	m_ER3;
	BYTE	m_ER4;
	BYTE	m_ER5;
	BYTE	m_ER6;
	BYTE	m_ER7;
	BYTE	m_ER8;
	BYTE	m_ER9;
	CString	m_OBChanceHomeRun;
	CString	m_OBChanceTriple;
	CString	m_OBChanceDouble;
	CString	m_OBChanceSingle;
	CString	m_OBChanceWalk;
	CString	m_ChanceDoublePlay;
	CString	m_OBChanceHomeRunRight;
	CString	m_OBChanceTripleRight;
	CString	m_OBChanceDoubleRight;
	CString	m_OBChanceSingleRight;
	CString	m_OBChanceWalkRight;
	CString	m_ChanceDoublePlayRight;
	CString	m_OBChanceHomeRunLeft;
	CString	m_OBChanceTripleLeft;
	CString	m_OBChanceDoubleLeft;
	CString	m_OBChanceSingleLeft;
	CString	m_OBChanceWalkLeft;
	CString	m_ChanceDoublePlayLeft;
	CString	m_OBChanceBasic;
	CString	m_OBChanceLeft;
	CString	m_OBChanceRight;
	BYTE	m_BatterHits;
	long	m_TeamID;	//Pointer to TeamID Key
	COleDateTime	m_LastUpdateTime;

// Overrides
	// Wizard generated virtual function overrides
	public:
	virtual CString GetDefaultConnect();	// Default connection string

	virtual CString GetDefaultSQL(); 	// default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX support

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


