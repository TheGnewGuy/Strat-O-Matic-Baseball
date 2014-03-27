// BatterStats.h : Declaration of the CBatterStats

#pragma once

// code generated on Thursday, March 27, 2014, 6:38 PM

class CBatterStats : public CRecordset
{
public:
	CBatterStats(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CBatterStats)

// Field/Param Data

// The string types below (if present) reflect the actual data type of the
// database field - CStringA for ANSI datatypes and CStringW for Unicode
// datatypes. This is to prevent the ODBC driver from performing potentially
// unnecessary conversions.  If you wish, you may change these members to
// CString types and the ODBC driver will perform all necessary conversions.
// (Note: You must use an ODBC driver version that is version 3.5 or greater
// to support both Unicode and these conversions).

	long	m_BatterStatsID;	//Batter Stats Key
	int		m_AB;
	int		m_Runs;
	int		m_Hits;
	int		m_RBI;
	int		m_2B;
	int		m_3B;
	int		m_HomeRuns;
	int		m_Walk;
	int		m_StrikeOut;
	int		m_ReachedOnError;
	int		m_Sacrifice;
	int		m_StolenBase;
	int		m_CS;
	int		m_Games;
	int		m_HBP;
	float	m_AVG;	//Hits/AB
	float	m_SLG;	//(1B+2*2B+3*3B+4*HR)/AB
	float	m_OBP;	//(H+BB+HBP)/(AB+BB+HBP+SF)
	long	m_BatterID;	//Pointer to BatterID Key
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


