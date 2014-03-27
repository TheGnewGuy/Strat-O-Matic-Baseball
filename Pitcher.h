// Pitcher.h : Declaration of the CPitcher

#pragma once

// code generated on Thursday, March 27, 2014, 6:39 PM

class CPitcher : public CRecordset
{
public:
	CPitcher(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CPitcher)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_PitcherID;	//Pitcher Key
	CString	m_FirstName;
	CString	m_LastName;
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
	BYTE	m_Starter;
	BYTE	m_Relief;
	BYTE	m_Throws;
	BYTE	m_Bunting;
	BYTE	m_Hold;
	BYTE	m_WP;
	BYTE	m_Balk;
	BYTE	m_PitcherField;
	BYTE	m_ER1;
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


