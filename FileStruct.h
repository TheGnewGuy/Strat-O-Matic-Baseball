#if !defined(AFX_FILESTRUCT_H__3F0DC441_945A_11D2_B0EE_444553540000__INCLUDED_)
#define AFX_FILESTRUCT_H__3F0DC441_945A_11D2_B0EE_444553540000__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// FileStruct.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// BatterStruct window

class BatterStruct : public CObject
{
// Construction
public:
	BatterStruct();

// Attributes
public:
	int		m_RecordSize;	// Calculated in constructor

	CString	m_PlayerName;	// Length of 30
	short	m_AB;
	short	m_Runs;
	short	m_Hits;
	short	m_RBI;
	short	m_2B;
	short	m_3B;
	short	m_HomeRuns;
	short	m_Walk;
	short	m_StrikeOut;
	short	m_ReachedOnError;
	short	m_Sacrifice;
	short	m_StolenBase;
	short	m_CS;
	short	m_Filler1;		// For Growth if needed
	short	m_Filler2;		// For Growth if needed
	short	m_Games;
	short	m_HBP;
	BYTE	m_Pitcher;
	BYTE	m_Catcher;
	BYTE	m_FirstBase;
	BYTE	m_SecondBase;
	BYTE	m_ShortStop;
	BYTE	m_ThirdBase;
	BYTE	m_LeftField;
	BYTE	m_CenterField;
	BYTE	m_RightField;
	BYTE	m_bBunting;
	BYTE	m_bHitRun;
	BYTE	m_bRunning;
	BYTE	m_bStealing;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BatterStruct)
	//}}AFX_VIRTUAL

// Implementation
public:
	BYTE m_bCatchArm;
	BYTE m_bOutArm;
	BYTE m_bPowerR;
	BYTE m_bPowerL;
	BYTE m_bPass;
	BYTE m_bTRate;
	BYTE m_bER9;
	BYTE m_bER8;
	BYTE m_bER7;
	BYTE m_bER6;
	BYTE m_bER5;
	BYTE m_bER4;
	BYTE m_bER3;
	BYTE m_bER2;
	BYTE m_bER1;
	CString m_OBChanceHomeRun;
	CString m_OBChanceTriple;
	CString m_OBChanceDouble;
	CString m_OBChanceSingle;
	CString m_OBChanceWalk;
	CString m_ChanceDoublePlay;
	CString m_OBChanceHomeRunRight;
	CString m_OBChanceTripleRight;
	CString m_OBChanceDoubleRight;
	CString m_OBChanceSingleRight;
	CString m_OBChanceWalkRight;
	CString m_ChanceDoublePlayRight;
	CString m_OBChanceHomeRunLeft;
	CString m_OBChanceTripleLeft;
	CString m_OBChanceDoubleLeft;
	CString m_OBChanceSingleLeft;
	CString m_OBChanceWalkLeft;
	CString m_ChanceDoublePlayLeft;
	int CopyBatterFile(CString inFileName, CString outFileName);
	BYTE GetCountBatter(CString BatterFileName);
	BYTE m_bBatterHits;
	CString m_OBChanceRight;
	CString m_OBChanceLeft;
	CString m_OBChanceBasic;
	BYTE m_bFiller1;
	int GetBatter(CString BatterFileName, LONG SeekPosition);
	int AddBatter(CString BatterFileName);
	int UpdateBatter(CString BatterFileName, LONG SeekPosition);
	virtual ~BatterStruct();

	// Generated message map functions
protected:
private:
	int BatterRead(CFile* myFile);
	int BatterWrite(CFile* myFile);
protected:
	// Generated message map functions
};

/////////////////////////////////////////////////////////////////////////////
// PitcherStruct window

class PitcherStruct : public CObject
{
// Construction
public:
	PitcherStruct();

// Attributes
public:
	int		m_RecordSize;	// Calculated in constructor

	BYTE	m_PitcherNumber;// Count of Pitchers in file
	CString	m_PitcherName;
	short	m_Wins;
	short	m_Loss;
	short	m_Saves;
	short	m_ER;
	CString	m_IP;
	short	m_Hits;
	short	m_Walks;
	short	m_Strikeouts;
	short	m_HomeRuns;
	short	m_Filler1;		// For Growth if needed
	short	m_Games;
	short	m_CompGames;
	short	m_Starts;
	BYTE	m_Starter;
	BYTE	m_Throws;
	BYTE	m_Relief;
	BYTE	m_Bunting;
	BYTE	m_Hold;
	BYTE	m_PitcherField;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PitcherStruct)
	//}}AFX_VIRTUAL

// Implementation
public:
	BYTE m_bER1;
	BYTE m_bBalk;
	BYTE m_bWP;
	CString m_OBChanceHomeRun;
	CString m_OBChanceTriple;
	CString m_OBChanceDouble;
	CString m_OBChanceSingle;
	CString m_OBChanceWalk;
	CString m_ChanceDoublePlay;
	CString m_OBChanceHomeRunRight;
	CString m_OBChanceTripleRight;
	CString m_OBChanceDoubleRight;
	CString m_OBChanceSingleRight;
	CString m_OBChanceWalkRight;
	CString m_ChanceDoublePlayRight;
	CString m_OBChanceHomeRunLeft;
	CString m_OBChanceTripleLeft;
	CString m_OBChanceDoubleLeft;
	CString m_OBChanceSingleLeft;
	CString m_OBChanceWalkLeft;
	CString m_ChanceDoublePlayLeft;
	int CopyPitcherFile(CString inFileName, CString outFileName);
	BYTE m_bFiller1;
	CString m_OBChanceRight;
	CString m_OBChanceLeft;
	CString m_OBChanceBasic;
	int GetPitcher(CString PitcherFileName, LONG SeekPosition);
	BYTE GetCountPitcher(CString PitcherFileName);
	int AddPitcher(CString PitcherFileName);
	int UpdatePitcher(CString PitcherFileName, LONG SeekPosition);
	virtual ~PitcherStruct();

protected:
	// Generated message map functions
private:
	int PitcherWrite(CFile * myFile);
	int PitcherRead(CFile * myFile);
};

/////////////////////////////////////////////////////////////////////////////
// LeagueStruct window

class LeagueStruct : public CObject
{
// Construction
public:
	LeagueStruct();

// Attributes
public:
	// We will always have 1 Conference and one Division. If these
	// are not specified, then they will be assigned NULL
	//
	// Record Layout varies, each indentation will duplicat number:
	//  Version byte
	//	BYTE Number of Conferences
	//	30 char League Name
	//		BYTE Number of Divisions
	//		30 char Conference Name (Always 1, Name may be NULL)
	//			BYTE Number of teams
	//			30 char Division Name (Always 1, Name may be NULL)
	//				40 char Team Name
	//				8 char Team File Name no extension
	//				Short team 3 char
	//				Ballpark 20 char
	//              home short Wins
	//              home short Loss
	//              away short Wins
	//              away short Loss
	BYTE	m_Conferencenumber;
	BYTE	m_Divisionnumber;
	BYTE	m_Teamsnumber;
	CString	m_LeagueName;
	CString	m_Conference1;
	CString	m_Conference2;
	CString	m_Conference3;
	CString	m_Conference4;
	CString	m_Conference5;
	CString	m_Conference6;
	CString	m_Division1;
	CString	m_Division2;
	CString	m_Division3;
	CString	m_Division4;
	CString	m_Division5;
	CString	m_Division6;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(LeagueStruct)
	//}}AFX_VIRTUAL

// Implementation
public:
	int UpdatePitcher(CString PitcherFileName, LONG SeekPosition);
	virtual ~LeagueStruct();

protected:
	// Generated message map functions
};

/////////////////////////////////////////////////////////////////////////////
// TeamStruct window

class TeamStruct : public CObject
{
// Construction
public:
	TeamStruct();

// Attributes
public:
	// Record Structure
	//	BYTE Number of Batters
	//	BYTE Number of Pitchers
	//	40 char Team Name
	//		Batter records based on number of batters

	BYTE	m_BatterNumber;
	CString	m_TeamName;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TeamStruct)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~TeamStruct();

protected:
	// Generated message map functions
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FILESTRUCT_H__3F0DC441_945A_11D2_B0EE_444553540000__INCLUDED_)
