// FileStruct.cpp : implementation file
//

#include "stdafx.h"
#include "Baseball.h"
#include "BaseballDoc.h"
#include "Leagues.h"
#include "Teams.h"
#include "FileStruct.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// BatterStruct

BatterStruct::BatterStruct()
{
	// This file has a 74 byte header as follows
	//
	// Read Count byte (number of players)
	// Read team name 40 char
	// Read short team name 3 char
	// Read Ballpark 30 char
	//
	// Player layout repeats
	m_RecordSize = 30 +
		sizeof(m_AB)+
		sizeof(m_Runs)+
		sizeof(m_Hits)+
		sizeof(m_RBI)+
		sizeof(m_2B)+
		sizeof(m_3B)+
		sizeof(m_HomeRuns)+
		sizeof(m_Walk)+
		sizeof(m_StrikeOut)+
		sizeof(m_ReachedOnError)+
		sizeof(m_Sacrifice)+
		sizeof(m_StolenBase)+
		sizeof(m_CS)+
		sizeof(m_Filler1)+
		sizeof(m_Filler2)+
		sizeof(m_Games)+
		sizeof(m_HBP)+
		sizeof(m_Pitcher)+
		sizeof(m_Catcher)+
		sizeof(m_FirstBase)+
		sizeof(m_SecondBase)+
		sizeof(m_ShortStop)+
		sizeof(m_ThirdBase)+
		sizeof(m_LeftField)+
		sizeof(m_CenterField)+
		sizeof(m_RightField)+
		sizeof(m_bER1)+
		sizeof(m_bER2)+
		sizeof(m_bER3)+
		sizeof(m_bER4)+
		sizeof(m_bER5)+
		sizeof(m_bER6)+
		sizeof(m_bER7)+
		sizeof(m_bER8)+
		sizeof(m_bER9)+
		sizeof(m_bBatterHits)+
		6 +				// On Base Chance Basic
		6 +				// On Base Chance Left
		6 +				// On Base Chance Right
		6 +				// On Base Chance Walk
		6 +				// On Base Chance Single
		6 +				// On Base Chance Double
		6 +				// On Base Chance Triple
		6 +				// On Base Chance HomeRun
		6 +				// Chance Double Play
		6 +				// On Base Chance Walk Right
		6 +				// On Base Chance Single Right
		6 +				// On Base Chance Double Right
		6 +				// On Base Chance Triple Right
		6 +				// On Base Chance HomeRun Right
		6 +				// Chance Double Play Right
		6 +				// On Base Chance Walk Left
		6 +				// On Base Chance Single Left
		6 +				// On Base Chance Double Left
		6 +				// On Base Chance Triple Left
		6 +				// On Base Chance HomeRun Left
		6 +				// Chance Double Play Left
		6 +				// Filler
		6 +				// Filler
		6 +				// Filler
		sizeof(m_bBunting)+
		sizeof(m_bHitRun)+
		sizeof(m_bRunning)+
		sizeof(m_bStealing)+
		sizeof(m_bTRate)+
		sizeof(m_bPass)+
		sizeof(m_bPowerL)+
		sizeof(m_bPowerR)+
		sizeof(m_bOutArm)+
		sizeof(m_bCatchArm)+
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE);	// Filler
	m_Filler1 = 0;
	m_Filler2 = 0;
	m_bFiller1 = 0;
	m_CS = 0;
	m_OBChanceBasic.Empty();
	m_OBChanceLeft.Empty();
	m_OBChanceRight.Empty();

	CBaseballDoc* pDoc = CBaseballDoc::GetDoc();
	ASSERT_VALID(pDoc);

	// Allocate the recordset
	m_pBatter_set = new CBatter(&pDoc->m_pDatabase);

	TRY
	{
		// Execute the query
		m_pBatter_set->Open(CRecordset::dynaset, NULL, CRecordset::none);
	}
		CATCH(CDBException, e)
	{
			// If a database exception occured, show error msg
			AfxMessageBox("Database Batter RS error: " + e->m_strError);
	}
	END_CATCH;

	// Allocate the recordset
	m_pBatterStats_set = new CBatterStats(&pDoc->m_pDatabase);

	TRY
	{
		// Execute the query
		m_pBatterStats_set->Open(CRecordset::dynaset, NULL, CRecordset::none);
	}
		CATCH(CDBException, e)
	{
			// If a database exception occured, show error msg
			AfxMessageBox("Database BatterStats RS error: " + e->m_strError);
	}
	END_CATCH;

	// Allocate the recordset
	m_pTeams_set = new CTeams(&pDoc->m_pDatabase);

	TRY
	{
		// Execute the query
		m_pTeams_set->Open(CRecordset::dynaset, NULL, CRecordset::none);
	}
		CATCH(CDBException, e)
	{
			// If a database exception occured, show error msg
			AfxMessageBox("Database m_pTeams_set RS error: " + e->m_strError);
	}
	END_CATCH;
	m_arrayBatterNames = new CStringArray();
	m_saveBatterStatsID = 0;
	m_saveTeamID = 0;
}

BatterStruct::~BatterStruct()
{
	TRY
	{
		if (m_pBatterStats_set->IsOpen())
		m_pBatterStats_set->Close();
	}
		CATCH(CDBException, e)
	{
			// If a database exception occured, show error msg
			AfxMessageBox("Database Close error BatterStruct: " + e->m_strError);
	}
	END_CATCH;
	TRY
	{
		if (m_pBatter_set->IsOpen())
		m_pBatter_set->Close();
	}
		CATCH(CDBException, e)
	{
			// If a database exception occured, show error msg
			AfxMessageBox("Database Close error BatterStruct: " + e->m_strError);
	}
	END_CATCH;
	TRY
	{
		if (m_pTeams_set->IsOpen())
		m_pTeams_set->Close();
	}
		CATCH(CDBException, e)
	{
			// If a database exception occured, show error msg
			AfxMessageBox("Database Close error m_pTeams_set: " + e->m_strError);
	}
	END_CATCH;
}

int BatterStruct::UpdateBatter(CString BatterFileName, LONG BatterStatsID)
{
	BatterWrite(m_saveBatterStatsID);
	return 1;
}

// Adding a Batter needs to pick a Batter from a base team and then create a new 
// BatterStat. If this is adding a new Batter to a Base team then a new Batter
// needs to be created in the Batter table as well as a new entry in BatterStats,
int BatterStruct::AddBatter(CString BatterName)
{
	if (m_pTeams_set->m_BaseTeam)
	{
		// Yes this is a Base team. Create a new Batter and Batterstats records.
	}
	else
	{
		// This is not a base team. Add by pointing back to base Batter and 
		// zeroing out the batterstats
	}
	return 1;
}

int BatterStruct::GetBatter(CString BatterName, LONG TeamID)
{
	CString tmpBatterID;
	CString tmpBatterStatID;
	CString tmpTeamID;
	long saveBatterID;
	CString lLastName;
	std::string strBatterLastName;
	CString BatterFirstName;

	m_saveTeamID = TeamID;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpTeamID.Format("%d", TeamID);
	m_pBatterStats_set->m_strFilter = "[TeamID] = " + tmpTeamID;
	m_pBatterStats_set->Requery();	// Get list of BatterStats associated to this team.

	// When the last name is something like O'Tool, the "'" causes a problem
	// with the SQL search. By editing the string to insert a double "'"
	// in the search, the search works correctly.
	lLastName = BatterName.Left(BatterName.Find(','));
	std::string str1 = lLastName;
	if (str1.find('\'', 0) != std::string::npos)
	{
		std::string str2 = str1.substr(0, str1.find('\'', 0));
		// Insert the double "'" in the string.
		str2 = str2 + '\'' + '\'';
		strBatterLastName = str2 + str1.substr((str1.find('\'', 0) + 1), std::string::npos);
	}
	else
	{
		strBatterLastName = lLastName;
	}

	BatterFirstName = BatterName.Right(
		BatterName.GetLength() - BatterName.Find(", ") - 2).TrimRight(' ');

	while (!m_pBatterStats_set->IsEOF())
	{
		tmpBatterID.Format("%d", m_pBatterStats_set->m_BatterID);
		m_pBatter_set->m_strFilter = "[FirstName] = '" + BatterFirstName + "'" +
			" AND [LastName] = '" + strBatterLastName.c_str() + "'" +
			" AND [BatterID] = " + tmpBatterID;
		m_pBatter_set->Requery();
		if (!m_pBatter_set->IsBOF())
		{
			// Records have been returned. 
			// This should be a single record with a match between Batter and Batterstats
			saveBatterID = m_pBatter_set->m_BatterID;
			m_saveBatterStatsID = m_pBatterStats_set->m_BatterStatsID;
		}

		m_pBatterStats_set->MoveNext();
	}

	BatterRead(m_saveBatterStatsID);
	// Close file
	return 1;
}

void BatterStruct::BatterWrite(long BatterStatID)
{
	CString tmpBatterID;
	CString tmpBatterStatID;
	SYSTEMTIME lt;
	GetLocalTime(&lt);

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpBatterStatID.Format("%d", BatterStatID);
	m_pBatterStats_set->m_strFilter = "[BatterStatsID] = " + tmpBatterStatID;
	// Execute the query for BatterStats
	m_pBatterStats_set->Requery();
	tmpBatterID.Format("%d", m_pBatterStats_set->m_BatterID);
	m_pBatter_set->m_strFilter = "[BatterID] = " + tmpBatterID;
	// Execute the query for Batter
	m_pBatter_set->Requery();

	m_pBatterStats_set->Edit();

	m_pBatterStats_set->m_AB = m_AB;
	m_pBatterStats_set->m_Runs = m_Runs;
	m_pBatterStats_set->m_Hits = m_Hits;
	m_pBatterStats_set->m_RBI = m_RBI;
	m_pBatterStats_set->m_2B = m_2B;
	m_pBatterStats_set->m_3B = m_3B;
	m_pBatterStats_set->m_HomeRuns = m_HomeRuns;
	m_pBatterStats_set->m_Walk = m_Walk;
	m_pBatterStats_set->m_StrikeOut = m_StrikeOut;
	m_pBatterStats_set->m_ReachedOnError = m_ReachedOnError;
	m_pBatterStats_set->m_Sacrifice = m_Sacrifice;
	m_pBatterStats_set->m_StolenBase = m_StolenBase;
	m_pBatterStats_set->m_CS = m_CS;
	m_pBatterStats_set->m_Games = m_Games;
	m_pBatterStats_set->m_HBP = m_HBP;
	//m_pBatterStats_set->m_AVG;
	//m_pBatterStats_set->m_SLG;
	//m_pBatterStats_set->m_OBP;
	m_pBatterStats_set->m_LastUpdateTime = lt;

	m_pBatterStats_set->Update();

	m_pBatter_set->Edit();

	m_pBatter_set->m_Pitcher = m_Pitcher;
	m_pBatter_set->m_Catcher = m_Catcher;
	m_pBatter_set->m_FirstBase = m_FirstBase;
	m_pBatter_set->m_SecondBase = m_SecondBase;
	m_pBatter_set->m_ThirdBase = m_ThirdBase;
	m_pBatter_set->m_ShortStop = m_ShortStop;
	m_pBatter_set->m_LeftField = m_LeftField;
	m_pBatter_set->m_CenterField = m_CenterField;
	m_pBatter_set->m_RightField = m_RightField;
	m_pBatter_set->m_ER1 = m_bER1;
	m_pBatter_set->m_ER2 = m_bER2;
	m_pBatter_set->m_ER3 = m_bER3;
	m_pBatter_set->m_ER4 = m_bER4;
	m_pBatter_set->m_ER5 = m_bER5;
	m_pBatter_set->m_ER6 = m_bER6;
	m_pBatter_set->m_ER7 = m_bER7;
	m_pBatter_set->m_ER8 = m_bER8;
	m_pBatter_set->m_ER9 = m_bER9;
	m_pBatter_set->m_OBChanceBasic = m_OBChanceBasic;
	m_pBatter_set->m_OBChanceLeft = m_OBChanceLeft;
	m_pBatter_set->m_OBChanceRight = m_OBChanceRight;
	m_pBatter_set->m_OBChanceWalk = m_OBChanceWalk;
	m_pBatter_set->m_OBChanceSingle = m_OBChanceSingle;
	m_pBatter_set->m_OBChanceDouble = m_OBChanceDouble;
	m_pBatter_set->m_OBChanceTriple = m_OBChanceTriple;
	m_pBatter_set->m_OBChanceHomeRun = m_OBChanceHomeRun;
	m_pBatter_set->m_ChanceDoublePlay = m_ChanceDoublePlay;
	m_pBatter_set->m_OBChanceWalkRight = m_OBChanceWalkRight;
	m_pBatter_set->m_OBChanceSingleRight = m_OBChanceSingleRight;
	m_pBatter_set->m_OBChanceDoubleRight = m_OBChanceDoubleRight;
	m_pBatter_set->m_OBChanceTripleRight = m_OBChanceTripleRight;
	m_pBatter_set->m_OBChanceHomeRunRight = m_OBChanceHomeRunRight;
	m_pBatter_set->m_ChanceDoublePlayRight = m_ChanceDoublePlayRight;
	m_pBatter_set->m_OBChanceWalkLeft = m_OBChanceWalkLeft;
	m_pBatter_set->m_OBChanceSingleLeft = m_OBChanceSingleLeft;
	m_pBatter_set->m_OBChanceDoubleLeft = m_OBChanceDoubleLeft;
	m_pBatter_set->m_OBChanceTripleLeft = m_OBChanceTripleLeft;
	m_pBatter_set->m_OBChanceHomeRunLeft = m_OBChanceHomeRunLeft;
	m_pBatter_set->m_ChanceDoublePlayLeft = m_ChanceDoublePlayLeft;
	m_pBatter_set->m_Bunting = m_bBunting;
	m_pBatter_set->m_HitRun = m_bHitRun;
	m_pBatter_set->m_Running = m_bRunning;
	m_pBatter_set->m_Stealing = m_bStealing;
	m_pBatter_set->m_TRate = m_bTRate;
	m_pBatter_set->m_Pass = m_bPass;
	m_pBatter_set->m_PowerLeft = m_bPowerL;
	m_pBatter_set->m_PowerRight = m_bPowerR;
	m_pBatter_set->m_OutArm = m_bOutArm;
	m_pBatter_set->m_CatchArm = m_bCatchArm;
	m_pBatter_set->m_BatterHits = m_bBatterHits;
	m_pBatter_set->m_LastUpdateTime = lt;

	m_pBatter_set->Update();
}

void BatterStruct::BatterRead(long BatterStatID)
{
	CString tmpBatterID;
	CString tmpBatterStatID;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpBatterStatID.Format("%d", BatterStatID);
	m_pBatterStats_set->m_strFilter = "[BatterStatsID] = " + tmpBatterStatID;
	// Execute the query for BatterStats
	m_pBatterStats_set->Requery();
	tmpBatterID.Format("%d", m_pBatterStats_set->m_BatterID);
	m_pBatter_set->m_strFilter = "[BatterID] = " + tmpBatterID;
	// Execute the query for Batter
	m_pBatter_set->Requery();

	m_PlayerName = m_pBatter_set->m_LastName + ", " + m_pBatter_set->m_FirstName;
	m_AB = m_pBatterStats_set->m_AB;
	m_Runs = m_pBatterStats_set->m_Runs;
	m_Hits = m_pBatterStats_set->m_Hits;
	m_RBI = m_pBatterStats_set->m_RBI;
	m_2B = m_pBatterStats_set->m_2B;
	m_3B = m_pBatterStats_set->m_3B;
	m_HomeRuns = m_pBatterStats_set->m_HomeRuns;
	m_Walk = m_pBatterStats_set->m_Walk;
	m_StrikeOut = m_pBatterStats_set->m_StrikeOut;
	m_ReachedOnError = m_pBatterStats_set->m_ReachedOnError;
	m_Sacrifice = m_pBatterStats_set->m_Sacrifice;
	m_StolenBase = m_pBatterStats_set->m_StolenBase;
	m_CS = m_pBatterStats_set->m_CS;
	m_Games = m_pBatterStats_set->m_Games;
	m_HBP = m_pBatterStats_set->m_HBP;
	//m_pBatterStats_set->m_AVG;
	//m_pBatterStats_set->m_SLG;
	//m_pBatterStats_set->m_OBP;

	m_Pitcher = m_pBatter_set->m_Pitcher;
	m_Catcher = m_pBatter_set->m_Catcher;
	m_FirstBase = m_pBatter_set->m_FirstBase;
	m_SecondBase = m_pBatter_set->m_SecondBase;
	m_ThirdBase = m_pBatter_set->m_ThirdBase;
	m_ShortStop = m_pBatter_set->m_ShortStop;
	m_LeftField = m_pBatter_set->m_LeftField;
	m_CenterField = m_pBatter_set->m_CenterField;
	m_RightField = m_pBatter_set->m_RightField;
	m_bER1 = m_pBatter_set->m_ER1;
	m_bER2 = m_pBatter_set->m_ER2;
	m_bER3 = m_pBatter_set->m_ER3;
	m_bER4 = m_pBatter_set->m_ER4;
	m_bER5 = m_pBatter_set->m_ER5;
	m_bER6 = m_pBatter_set->m_ER6;
	m_bER7 = m_pBatter_set->m_ER7;
	m_bER8 = m_pBatter_set->m_ER8;
	m_bER9 = m_pBatter_set->m_ER9;
	m_OBChanceBasic = m_pBatter_set->m_OBChanceBasic;
	m_OBChanceLeft = m_pBatter_set->m_OBChanceLeft;
	m_OBChanceRight = m_pBatter_set->m_OBChanceRight;
	m_OBChanceWalk = m_pBatter_set->m_OBChanceWalk;
	m_OBChanceSingle = m_pBatter_set->m_OBChanceSingle;
	m_OBChanceDouble = m_pBatter_set->m_OBChanceDouble;
	m_OBChanceTriple = m_pBatter_set->m_OBChanceTriple;
	m_OBChanceHomeRun = m_pBatter_set->m_OBChanceHomeRun;
	m_ChanceDoublePlay = m_pBatter_set->m_ChanceDoublePlay;
	m_OBChanceWalkRight = m_pBatter_set->m_OBChanceWalkRight;
	m_OBChanceSingleRight = m_pBatter_set->m_OBChanceSingleRight;
	m_OBChanceDoubleRight = m_pBatter_set->m_OBChanceDoubleRight;
	m_OBChanceTripleRight = m_pBatter_set->m_OBChanceTripleRight;
	m_OBChanceHomeRunRight = m_pBatter_set->m_OBChanceHomeRunRight;
	m_ChanceDoublePlayRight = m_pBatter_set->m_ChanceDoublePlayRight;
	m_OBChanceWalkLeft = m_pBatter_set->m_OBChanceWalkLeft;
	m_OBChanceSingleLeft = m_pBatter_set->m_OBChanceSingleLeft;
	m_OBChanceDoubleLeft = m_pBatter_set->m_OBChanceDoubleLeft;
	m_OBChanceTripleLeft = m_pBatter_set->m_OBChanceTripleLeft;
	m_OBChanceHomeRunLeft = m_pBatter_set->m_OBChanceHomeRunLeft;
	m_ChanceDoublePlayLeft = m_pBatter_set->m_ChanceDoublePlayLeft;
	m_bBunting = m_pBatter_set->m_Bunting;
	m_bHitRun = m_pBatter_set->m_HitRun;
	m_bRunning = m_pBatter_set->m_Running;
	m_bStealing = m_pBatter_set->m_Stealing;
	m_bTRate = m_pBatter_set->m_TRate;
	m_bPass = m_pBatter_set->m_Pass;
	m_bPowerL = m_pBatter_set->m_PowerLeft;
	m_bPowerR = m_pBatter_set->m_PowerRight;
	m_bOutArm = m_pBatter_set->m_OutArm;
	m_bCatchArm = m_pBatter_set->m_CatchArm;
	m_bBatterHits =  m_pBatter_set->m_BatterHits;
}

BYTE BatterStruct::GetCountBatter(CString BatterFileName)
{
	BYTE count;
	CFile myFile;
	myFile.Open( BatterFileName,CFile::modeRead);
	// Read Count
	myFile.Read(&count,sizeof(count));
	// Close file
	myFile.Close();
	return count;
}

int BatterStruct::CopyBatterFile(CString inFileName, CString outFileName)
{
	int i;
	BYTE count;
	LONG lSeekPlayerFile;
	LONG lTeamSection = 74;
	CFile inFile;
	CFile outFile;
	char cTemp[41];
	CString strTemp;

	inFile.Open( inFileName, CFile::modeRead);
	outFile.Open( outFileName, CFile::modeCreate | CFile::modeWrite);
	// Read Count
	inFile.Read(&count,sizeof(count));
	outFile.Write(&count,sizeof(count));
	// Read team name
	inFile.Read(cTemp,40);
	cTemp[40]=NULL;
	strTemp = cTemp;
	outFile.Write(strTemp,40);
	// Read short team name
	inFile.Read(cTemp,3);
	cTemp[3]=NULL;
	strTemp = cTemp;
	outFile.Write(strTemp,3);
	// Read Ballpark
	inFile.Read(cTemp,30);
	cTemp[30]=NULL;
	strTemp = cTemp;
	outFile.Write(strTemp,30);
	// Read all of the players
	for (i=0; i<count; i++)
	{
		lSeekPlayerFile = lTeamSection+(i*m_RecordSize);
		inFile.Seek( lSeekPlayerFile, CFile::begin );
//		BatterRead(&inFile);
		// Zero out fields
		m_2B = 0;
		m_3B = 0;
		m_AB = 0;
		m_CS = 0;
		m_Hits = 0;
		m_HomeRuns = 0;
		m_RBI = 0;
		m_ReachedOnError = 0;
		m_Runs = 0;
		m_Sacrifice = 0;
		m_StolenBase = 0;
		m_StrikeOut = 0;
		m_Walk = 0;
		m_HBP = 0;
		m_Games = 0;
		// Write Batter info at EOF, Already positioned there
		BatterWrite(m_saveBatterStatsID);
	}
	// Close file
	inFile.Close();
	outFile.Close();
	return 1;
}

// Get Batter Stats and then Batter for Name
CStringArray* BatterStruct::GetBatterNameArray(long TeamID)
{
	CString tmpTeamID;
	CString tmpBatterID;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpTeamID.Format("%d", TeamID);
	m_pBatterStats_set->m_strFilter = "[TeamID] = " + tmpTeamID;
	// Execute the query
	m_pBatterStats_set->Requery();

	m_arrayBatterNames->RemoveAll();

	while (!m_pBatterStats_set->IsEOF())
	{
		tmpBatterID.Format("%d", m_pBatterStats_set->m_BatterID);
		m_pBatter_set->m_strFilter = "[BatterID] = " + tmpBatterID;
		m_pBatter_set->Requery();

		while (!m_pBatter_set->IsEOF())
		{
			m_arrayBatterNames->Add(m_pBatter_set->m_LastName);
			m_pBatter_set->MoveNext();
		}

		m_pBatterStats_set->MoveNext();
	}

	return m_arrayBatterNames;
}

// Return array with "Lastname, Firstname"
CStringArray* BatterStruct::GetBatterLastFirstArray(long TeamID)
{
	CString tmpTeamID;
	CString tmpBatterID;
	CString tmpName;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpTeamID.Format("%d", TeamID);
	m_pBatterStats_set->m_strFilter = "[TeamID] = " + tmpTeamID;
	// Execute the query
	m_pBatterStats_set->Requery();

	m_arrayBatterNames->RemoveAll();

	while (!m_pBatterStats_set->IsEOF())
	{
		tmpBatterID.Format("%d", m_pBatterStats_set->m_BatterID);
		m_pBatter_set->m_strFilter = "[BatterID] = " + tmpBatterID;
		m_pBatter_set->Requery();

		while (!m_pBatter_set->IsEOF())
		{
			tmpName = m_pBatter_set->m_LastName + ", " + m_pBatter_set->m_FirstName;
			m_arrayBatterNames->Add(tmpName);
			m_pBatter_set->MoveNext();
		}

		m_pBatterStats_set->MoveNext();
	}

	return m_arrayBatterNames;
}

/////////////////////////////////////////////////////////////////////////////
// PitcherStruct

PitcherStruct::PitcherStruct()
{
	// This file has a 1 byte header as follows
	//
	// Read Count byte (number of players)
	//
	// Player layout repeats
		m_RecordSize = 30 +
		sizeof(m_Wins)+
		sizeof(m_Loss)+
		sizeof(m_Saves)+
		7+				// Innings Pitched 9999.99
		sizeof(m_ER)+
		sizeof(m_Hits)+
		sizeof(m_Walks)+
		sizeof(m_Strikeouts)+
		sizeof(m_HomeRuns)+
		sizeof(m_Filler1)+
		sizeof(m_Games)+
		sizeof(m_CompGames)+
		sizeof(m_Starts)+
		6+				// On Base Chance Basic
		6+				// On Base Chance Left
		6+				// On Base Chance Right
		6+				// On Base Chance Walk
		6+				// On Base Chance Single
		6+				// On Base Chance Double
		6+				// On Base Chance Triple
		6+				// On Base Chance HomeRun
		6+				// Chance Double Play
		6+				// On Base Chance Walk Right
		6+				// On Base Chance Single Right
		6+				// On Base Chance Double Right
		6+				// On Base Chance Triple Right
		6+				// On Base Chance HomeRun Right
		6+				// Chance Double Play Right
		6+				// On Base Chance Walk Left
		6+				// On Base Chance Single Left
		6+				// On Base Chance Double Left
		6+				// On Base Chance Triple Left
		6+				// On Base Chance HomeRun Left
		6+				// Chance Double Play Left
		6+				// Filler
		6+				// Filler
		6+				// Filler
		sizeof(m_Starter)+
		sizeof(m_Relief)+
		sizeof(m_Throws)+
		sizeof(m_Bunting)+
		sizeof(m_Hold)+
		sizeof(m_bWP)+
		sizeof(m_bBalk)+
		sizeof(m_bER1)+
		sizeof(m_PitcherField)+
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE)+	// Filler
		sizeof(BYTE);	// Filler

	m_Filler1 = 0;
	m_bFiller1 = 0;
	m_OBChanceBasic.Empty();
	m_OBChanceLeft.Empty();
	m_OBChanceRight.Empty();

	CBaseballDoc* pDoc = CBaseballDoc::GetDoc();
	ASSERT_VALID(pDoc);

	// Allocate the recordset
	m_pPitcher_set = new CPitcher(&pDoc->m_pDatabase);

	TRY
	{
		// Execute the query
		m_pPitcher_set->Open(CRecordset::dynaset, NULL, CRecordset::none);
	}
		CATCH(CDBException, e)
	{
		// If a database exception occured, show error msg
		AfxMessageBox("Database Pitcher RS error: " + e->m_strError);
	}
	END_CATCH;

	// Allocate the recordset
	m_pPitcherStats_set = new CPitcherStats(&pDoc->m_pDatabase);

	TRY
	{
		// Execute the query
		m_pPitcherStats_set->Open(CRecordset::dynaset, NULL, CRecordset::none);
	}
		CATCH(CDBException, e)
	{
		// If a database exception occured, show error msg
		AfxMessageBox("Database PitcherStats RS error: " + e->m_strError);
	}
	END_CATCH;

	// Allocate the recordset
	m_pTeams_set = new CTeams(&pDoc->m_pDatabase);

	TRY
	{
		// Execute the query
		m_pTeams_set->Open(CRecordset::dynaset, NULL, CRecordset::none);
	}
		CATCH(CDBException, e)
	{
		// If a database exception occured, show error msg
		AfxMessageBox("Database m_pTeams_set RS error: " + e->m_strError);
	}
	END_CATCH;
	m_arrayPitcherNames = new CStringArray();
	m_savePitcherStatsID = 0;
	m_saveTeamID = 0;
}

PitcherStruct::~PitcherStruct()
{
	TRY
	{
		if (m_pPitcherStats_set->IsOpen())
		m_pPitcherStats_set->Close();
	}
		CATCH(CDBException, e)
	{
		// If a database exception occured, show error msg
		AfxMessageBox("Database Close error BatterStruct: " + e->m_strError);
	}
	END_CATCH;
	TRY
	{
		if (m_pPitcher_set->IsOpen())
		m_pPitcher_set->Close();
	}
		CATCH(CDBException, e)
	{
		// If a database exception occured, show error msg
		AfxMessageBox("Database Close error BatterStruct: " + e->m_strError);
	}
	END_CATCH;
	TRY
	{
		if (m_pTeams_set->IsOpen())
		m_pTeams_set->Close();
	}
		CATCH(CDBException, e)
	{
		// If a database exception occured, show error msg
		AfxMessageBox("Database Close error m_pTeams_set: " + e->m_strError);
	}
	END_CATCH;
}

//int PitcherStruct::UpdatePitcher(CString PitcherFileName, LONG SeekPosition)
//{
//	CFile m_cFileTeam;
//	m_cFileTeam.Open( PitcherFileName,CFile::modeReadWrite);
//	m_cFileTeam.Seek( SeekPosition, CFile::begin );
//	PitcherWrite(&m_cFileTeam);
//	// Close file
//	m_cFileTeam.Close();
//	return 1;
//}
int PitcherStruct::UpdatePitcher(CString PitcherFileName, LONG BatterStatsID)
{
	PitcherWrite(m_savePitcherStatsID);
	return 1;
}

//int PitcherStruct::AddPitcher(CString PitcherFileName)
//{
//	BYTE count;
//	CFile m_cFileTeam;
//
//	count = 0;
//	// Open file and write new player
//	m_cFileTeam.Open(PitcherFileName,CFile::modeReadWrite);
//	m_cFileTeam.Read(&count,sizeof(count));
//	count++;
//	m_cFileTeam.SeekToBegin();
//	m_cFileTeam.Write(&count,sizeof(count));
//	m_cFileTeam.SeekToEnd();
//	PitcherWrite(&m_cFileTeam);
//	// Close file
//	m_cFileTeam.Close();
//	return 1;
//}
// Adding a Pitcher needs to pick a Pitcher from a base team and then create a new 
// PitcherStat. If this is adding a new Batter to a Base team then a new Pitcher
// needs to be created in the Pitcher table as well as a new entry in PitcherStats,
int PitcherStruct::AddPitcher(CString PitcherName)
{
	if (m_pTeams_set->m_BaseTeam)
	{
		// Yes this is a Base team. Create a new Pitcher and Pitcherstats records.
	}
	else
	{
		// This is not a base team. Add by pointing back to base Batter and 
		// zeroing out the batterstats
	}
	return 1;
}

//int PitcherStruct::GetPitcher(CString PitcherFileName, LONG SeekPosition)
//{
//	CFile m_cFileTeam;
//	m_cFileTeam.Open( PitcherFileName,CFile::modeRead);
//	m_cFileTeam.Seek( SeekPosition, CFile::begin );
//	PitcherRead(&m_cFileTeam);
//	// Close file
//	m_cFileTeam.Close();
//	return 1;
//}
int PitcherStruct::GetPitcher(CString PitcherName, LONG TeamID)
{
	CString tmpPitcherID;
	CString tmpPitcherStatID;
	CString tmpTeamID;
	long savePitcherID;
	CString lLastName;
	std::string strPitcherLastName;
	CString PitcherFirstName;

	m_saveTeamID = TeamID;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpTeamID.Format("%d", TeamID);
	m_pPitcherStats_set->m_strFilter = "[TeamID] = " + tmpTeamID;
	m_pPitcherStats_set->Requery();	// Get list of BatterStats associated to this team.

	// When the last name is something like O'Tool, the "'" causes a problem
	// with the SQL search. By editing the string to insert a double "'"
	// in the search, the search works correctly.
	lLastName = PitcherName.Left(PitcherName.Find(','));
	std::string str1 = lLastName;
	if (str1.find('\'', 0) != std::string::npos)
	{
		std::string str2 = str1.substr(0, str1.find('\'', 0));
		// Insert the double "'" in the string.
		str2 = str2 + '\'' + '\'';
		strPitcherLastName = str2 + str1.substr((str1.find('\'', 0) + 1), std::string::npos);
	}
	else
	{
		strPitcherLastName = lLastName;
	}

	PitcherFirstName = PitcherName.Right(
		PitcherName.GetLength() - PitcherName.Find(", ") - 2).TrimRight(' ');

	while (!m_pPitcherStats_set->IsEOF())
	{
		tmpPitcherID.Format("%d", m_pPitcherStats_set->m_PitcherID);
		m_pPitcher_set->m_strFilter = "[FirstName] = '" + PitcherFirstName + "'" +
			" AND [LastName] = '" + strPitcherLastName.c_str() + "'" +
			" AND [PitcherID] = " + tmpPitcherID;
		m_pPitcher_set->Requery();
		if (!m_pPitcher_set->IsBOF())
		{
			// Records have been returned. 
			// This should be a single record with a match between Pitcher and Pitcherstats
			savePitcherID = m_pPitcher_set->m_PitcherID;
			m_savePitcherStatsID = m_pPitcherStats_set->m_PitcherStatsID;
		}

		m_pPitcherStats_set->MoveNext();
	}

	PitcherRead(m_savePitcherStatsID);
	// Close file
	return 1;
}

//int PitcherStruct::PitcherWrite(CFile * myFile)
//{
//	myFile->Write(m_PitcherName,30);
//	myFile->Write(&m_Wins,sizeof(m_Wins));
//	myFile->Write(&m_Loss,sizeof(m_Loss));
//	myFile->Write(&m_Saves,sizeof(m_Saves));
//	myFile->Write(m_IP,7);
//	myFile->Write(&m_ER,sizeof(m_ER));
//	myFile->Write(&m_Hits,sizeof(m_Hits));
//	myFile->Write(&m_Walks,sizeof(m_Walks));
//	myFile->Write(&m_Strikeouts,sizeof(m_Strikeouts));
//	myFile->Write(&m_HomeRuns,sizeof(m_HomeRuns));
//	myFile->Write(&m_Filler1,sizeof(m_Filler1));
//	myFile->Write(&m_Games,sizeof(m_Games));
//	myFile->Write(&m_CompGames,sizeof(m_CompGames));
//	myFile->Write(&m_Starts,sizeof(m_Starts));
//	myFile->Write(m_OBChanceBasic,6);
//	myFile->Write(m_OBChanceLeft,6);
//	myFile->Write(m_OBChanceRight,6);
//	myFile->Write(m_OBChanceWalk,6);
//	myFile->Write(m_OBChanceSingle,6);
//	myFile->Write(m_OBChanceDouble,6);
//	myFile->Write(m_OBChanceTriple,6);
//	myFile->Write(m_OBChanceHomeRun,6);
//	myFile->Write(m_ChanceDoublePlay,6);
//	myFile->Write(m_OBChanceWalkRight,6);
//	myFile->Write(m_OBChanceSingleRight,6);
//	myFile->Write(m_OBChanceDoubleRight,6);
//	myFile->Write(m_OBChanceTripleRight,6);
//	myFile->Write(m_OBChanceHomeRunRight,6);
//	myFile->Write(m_ChanceDoublePlayRight,6);
//	myFile->Write(m_OBChanceWalkLeft,6);
//	myFile->Write(m_OBChanceSingleLeft,6);
//	myFile->Write(m_OBChanceDoubleLeft,6);
//	myFile->Write(m_OBChanceTripleLeft,6);
//	myFile->Write(m_OBChanceHomeRunLeft,6);
//	myFile->Write(m_ChanceDoublePlayLeft,6);
//	myFile->Write("0     ",6);		// Filler
//	myFile->Write("0     ",6);		// Filler
//	myFile->Write("0     ",6);		// Filler
//	myFile->Write(&m_Starter,sizeof(m_Starter));
//	myFile->Write(&m_Relief,sizeof(m_Relief));
//	myFile->Write(&m_Throws,sizeof(m_Throws));
//	myFile->Write(&m_Bunting,sizeof(m_Bunting));
//	myFile->Write(&m_Hold,sizeof(m_Hold));
//	myFile->Write(&m_bWP,sizeof(m_bWP));
//	myFile->Write(&m_bBalk,sizeof(m_bBalk));
//	myFile->Write(&m_bER1,sizeof(m_bER1));
//	myFile->Write(&m_PitcherField,sizeof(m_PitcherField));	// Pitcher field rating
//	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
//	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
//	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
//	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
//	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
//	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
//	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
//	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
//	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
//	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
//	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
//	return 1;
//}
void PitcherStruct::PitcherWrite(long PitcherStatID)
{
	CString tmpPitcherID;
	CString tmpPitcherStatID;
	SYSTEMTIME lt;
	GetLocalTime(&lt);

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpPitcherStatID.Format("%d", PitcherStatID);
	m_pPitcherStats_set->m_strFilter = "PitcherStatsID] = " + tmpPitcherStatID;
	// Execute the query for BatterStats
	m_pPitcherStats_set->Requery();
	tmpPitcherID.Format("%d", m_pPitcherStats_set->m_PitcherID);
	m_pPitcher_set->m_strFilter = "[PitcherID] = " + tmpPitcherID;
	// Execute the query for Batter
	m_pPitcher_set->Requery();

	m_pPitcherStats_set->Edit();

	m_pPitcherStats_set->m_Wins = m_Wins;
	m_pPitcherStats_set->m_Loss = m_Loss;
	m_pPitcherStats_set->m_Saves = m_Saves;
	//m_pPitcherStats_set->m_InningsPitched = m_IP; // float conversion
	m_pPitcherStats_set->m_ER = m_ER;
	m_pPitcherStats_set->m_Hits = m_Hits;
	m_pPitcherStats_set->m_Walks = m_Walks;
	m_pPitcherStats_set->m_Strikeouts = m_Strikeouts;
	m_pPitcherStats_set->m_HomeRuns = m_HomeRuns;
	m_pPitcherStats_set->m_Games = m_Games;
	m_pPitcherStats_set->m_CompleteGames = m_CompGames;
	m_pPitcherStats_set->m_Starts = m_Starts;
	//m_pPitcherStats_set->m_ERA = m_ERA;		// float conversion
	//m_pPitcherStats_set->m_WHIP = m_WHIP;		// float conversion

	m_pPitcherStats_set->m_LastUpdateTime = lt;

	m_pPitcherStats_set->Update();

	m_pPitcher_set->Edit();

	m_pPitcher_set->m_OBChanceBasic = m_OBChanceBasic;
	m_pPitcher_set->m_OBChanceLeft = m_OBChanceLeft;
	m_pPitcher_set->m_OBChanceRight = m_OBChanceRight;
	m_pPitcher_set->m_OBChanceWalk = m_OBChanceWalk;
	m_pPitcher_set->m_OBChanceSingle = m_OBChanceSingle;
	m_pPitcher_set->m_OBChanceDouble = m_OBChanceDouble;
	m_pPitcher_set->m_OBChanceTriple = m_OBChanceTriple;
	m_pPitcher_set->m_OBChanceHomeRun = m_OBChanceHomeRun;
	m_pPitcher_set->m_ChanceDoublePlay = m_ChanceDoublePlay;
	m_pPitcher_set->m_OBChanceWalkRight = m_OBChanceWalkRight;
	m_pPitcher_set->m_OBChanceSingleRight = m_OBChanceSingleRight;
	m_pPitcher_set->m_OBChanceDoubleRight = m_OBChanceDoubleRight;
	m_pPitcher_set->m_OBChanceTripleRight = m_OBChanceTripleRight;
	m_pPitcher_set->m_OBChanceHomeRunRight = m_OBChanceHomeRunRight;
	m_pPitcher_set->m_ChanceDoublePlayRight = m_ChanceDoublePlayRight;
	m_pPitcher_set->m_OBChanceWalkLeft = m_OBChanceWalkLeft;
	m_pPitcher_set->m_OBChanceSingleLeft = m_OBChanceSingleLeft;
	m_pPitcher_set->m_OBChanceDoubleLeft = m_OBChanceDoubleLeft;
	m_pPitcher_set->m_OBChanceTripleLeft = m_OBChanceTripleLeft;
	m_pPitcher_set->m_OBChanceHomeRunLeft = m_OBChanceHomeRunLeft;
	m_pPitcher_set->m_ChanceDoublePlayLeft = m_ChanceDoublePlayLeft;
	m_pPitcher_set->m_Starter = m_Starter;
	m_pPitcher_set->m_Relief = m_Relief;
	m_pPitcher_set->m_Throws = m_Throws;
	m_pPitcher_set->m_Bunting = m_Bunting;
	m_pPitcher_set->m_Hold = m_Hold;
	m_pPitcher_set->m_WP = m_bWP;
	m_pPitcher_set->m_Balk = m_bBalk;
	m_pPitcher_set->m_PitcherField = m_PitcherField;
	m_pPitcher_set->m_ER1 = m_bER1;
	m_pPitcher_set->m_LastUpdateTime = lt;

	m_pPitcher_set->Update();
}

//int PitcherStruct::PitcherRead(CFile * myFile)
//{
//	char cTemp[31];
//	BYTE bTemp;
//
//	myFile->Read(cTemp,30);
//	cTemp[30]=NULL;
//	m_PitcherName = cTemp;
//	myFile->Read(&m_Wins,sizeof(m_Wins));
//	myFile->Read(&m_Loss,sizeof(m_Loss));
//	myFile->Read(&m_Saves,sizeof(m_Saves));
//	myFile->Read(cTemp,7);
//	cTemp[7]=NULL;
//	m_IP = cTemp;
//	myFile->Read(&m_ER,sizeof(m_ER));
//	myFile->Read(&m_Hits,sizeof(m_Hits));
//	myFile->Read(&m_Walks,sizeof(m_Walks));
//	myFile->Read(&m_Strikeouts,sizeof(m_Strikeouts));
//	myFile->Read(&m_HomeRuns,sizeof(m_HomeRuns));
//	myFile->Read(&m_Filler1,sizeof(m_Filler1));
//	myFile->Read(&m_Games,sizeof(m_Games));
//	myFile->Read(&m_CompGames,sizeof(m_CompGames));
//	myFile->Read(&m_Starts,sizeof(m_Starts));
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceBasic = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceLeft = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceRight = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceWalk = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceSingle = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceDouble = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceTriple = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceHomeRun = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_ChanceDoublePlay = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceWalkRight = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceSingleRight = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceDoubleRight = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceTripleRight = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceHomeRunRight = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_ChanceDoublePlayRight = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceWalkLeft = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceSingleLeft = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceDoubleLeft = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceTripleLeft = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_OBChanceHomeRunLeft = cTemp;
//	myFile->Read(cTemp,6);
//	cTemp[6]=NULL;
//	m_ChanceDoublePlayLeft = cTemp;
//	myFile->Read(cTemp,6);
//	myFile->Read(cTemp,6);
//	myFile->Read(cTemp,6);
//	myFile->Read(&m_Starter,sizeof(m_Starter));
//	myFile->Read(&m_Relief,sizeof(m_Relief));
//	myFile->Read(&m_Throws,sizeof(m_Throws));
//	myFile->Read(&m_Bunting,sizeof(m_Bunting));
//	myFile->Read(&m_Hold,sizeof(m_Hold));
//	myFile->Read(&m_bWP,sizeof(m_bWP));
//	myFile->Read(&m_bBalk,sizeof(m_bBalk));
//	myFile->Read(&m_bER1,sizeof(m_bER1));
//	myFile->Read(&m_PitcherField,sizeof(m_PitcherField));
//	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
//	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
//	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
//	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
//	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
//	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
//	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
//	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
//	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
//	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
//	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
//	return 1;
//}
void PitcherStruct::PitcherRead(long PitcherStatID)
{
	CString tmpPitcherID;
	CString tmpPitcherStatID;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpPitcherStatID.Format("%d", PitcherStatID);
	m_pPitcherStats_set->m_strFilter = "[PitcherStatsID] = " + tmpPitcherStatID;
	// Execute the query for BatterStats
	m_pPitcherStats_set->Requery();
	tmpPitcherID.Format("%d", m_pPitcherStats_set->m_PitcherID);
	m_pPitcher_set->m_strFilter = "[PitcherID] = " + tmpPitcherID;
	// Execute the query for Batter
	m_pPitcher_set->Requery();

	m_PitcherName = m_pPitcher_set->m_LastName + ", " + m_pPitcher_set->m_FirstName;
	m_Wins = m_pPitcherStats_set->m_Wins;
	m_Loss = m_pPitcherStats_set->m_Loss;
	m_Saves = m_pPitcherStats_set->m_Saves;
	//m_IP = m_pPitcherStats_set->m_InningsPitched;	// float conversion
	m_ER = m_pPitcherStats_set->m_ER;
	m_Hits = m_pPitcherStats_set->m_Hits;
	m_Walks = m_pPitcherStats_set->m_Walks;
	m_Strikeouts = m_pPitcherStats_set->m_Strikeouts;
	m_HomeRuns = m_pPitcherStats_set->m_HomeRuns;
	m_Games = m_pPitcherStats_set->m_Games;
	m_CompGames = m_pPitcherStats_set->m_CompleteGames;
	m_Starts = m_pPitcherStats_set->m_Starts;
	//m_ERA = m_pPitcherStats_set->m_ERA;		// float conversion
	//m_WHIP = m_pPitcherStats_set->m_WHIP;		// float conversion

	m_OBChanceBasic = m_pPitcher_set->m_OBChanceBasic;
	m_OBChanceLeft = m_pPitcher_set->m_OBChanceLeft;
	m_OBChanceRight = m_pPitcher_set->m_OBChanceRight;
	m_OBChanceWalk = m_pPitcher_set->m_OBChanceWalk;
	m_OBChanceSingle = m_pPitcher_set->m_OBChanceSingle;
	m_OBChanceDouble = m_pPitcher_set->m_OBChanceDouble;
	m_OBChanceTriple = m_pPitcher_set->m_OBChanceTriple;
	m_OBChanceHomeRun = m_pPitcher_set->m_OBChanceHomeRun;
	m_ChanceDoublePlay = m_pPitcher_set->m_ChanceDoublePlay;
	m_OBChanceWalkRight = m_pPitcher_set->m_OBChanceWalkRight;
	m_OBChanceSingleRight = m_pPitcher_set->m_OBChanceSingleRight;
	m_OBChanceDoubleRight = m_pPitcher_set->m_OBChanceDoubleRight;
	m_OBChanceTripleRight = m_pPitcher_set->m_OBChanceTripleRight;
	m_OBChanceHomeRunRight = m_pPitcher_set->m_OBChanceHomeRunRight;
	m_ChanceDoublePlayRight = m_pPitcher_set->m_ChanceDoublePlayRight;
	m_OBChanceWalkLeft = m_pPitcher_set->m_OBChanceWalkLeft;
	m_OBChanceSingleLeft = m_pPitcher_set->m_OBChanceSingleLeft;
	m_OBChanceDoubleLeft = m_pPitcher_set->m_OBChanceDoubleLeft;
	m_OBChanceTripleLeft = m_pPitcher_set->m_OBChanceTripleLeft;
	m_OBChanceHomeRunLeft = m_pPitcher_set->m_OBChanceHomeRunLeft;
	m_ChanceDoublePlayLeft = m_pPitcher_set->m_ChanceDoublePlayLeft;
	m_Starter = m_pPitcher_set->m_Starter;
	m_Relief = m_pPitcher_set->m_Relief;
	m_Throws = m_pPitcher_set->m_Throws;
	m_Bunting = m_pPitcher_set->m_Bunting;
	m_Hold = m_pPitcher_set->m_Hold;
	m_bWP = m_pPitcher_set->m_WP;
	m_bBalk = m_pPitcher_set->m_Balk;
	m_PitcherField = m_pPitcher_set->m_PitcherField;
	m_bER1 = m_pPitcher_set->m_ER1;
}

BYTE PitcherStruct::GetCountPitcher(CString PitcherFileName)
{
	BYTE count;
	CFile myFile;
	myFile.Open( PitcherFileName,CFile::modeRead);
	// Read Count
	myFile.Read(&count,sizeof(count));
	// Close file
	myFile.Close();
	return count;
}

int PitcherStruct::CopyPitcherFile(CString inFileName, CString outFileName)
{
	int i;
	BYTE count;
	LONG lSeekPlayerFile;
	LONG lCountSection = 1;
	CFile inFile;
	CFile outFile;

	inFile.Open( inFileName,CFile::modeRead);
	outFile.Open( outFileName, CFile::modeCreate | CFile::modeWrite);
	// Read Count
	inFile.Read(&count,sizeof(count));
	outFile.Write(&count,sizeof(count));
	// Read all of the pitchers
	for (i=0; i<count; i++)
	{
		lSeekPlayerFile = lCountSection+(i*m_RecordSize);
		inFile.Seek( lSeekPlayerFile, CFile::begin );
//		PitcherRead(&inFile);
		// Zero out fields
		m_ER = 0;
		m_Hits = 0;
		m_HomeRuns = 0;
		m_IP.Empty();
		m_IP = "0";
		m_Loss = 0;
		m_Saves = 0;
		m_Strikeouts = 0;
		m_Walks = 0;
		m_Wins = 0;
		m_Starts = 0;
		m_Games = 0;
		m_CompGames = 0;
		// Write Pitcher info at EOF, Already positioned there
//		PitcherWrite(&outFile);
	}
	// Close file
	inFile.Close();
	outFile.Close();
	return 1;
}

// Get Pitcher Stats and then Batter for Name
CStringArray* PitcherStruct::GetPitcherNameArray(long TeamID)
{
	CString tmpTeamID;
	CString tmpPitcherID;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpTeamID.Format("%d", TeamID);
	m_pPitcherStats_set->m_strFilter = "[TeamID] = " + tmpTeamID;
	// Execute the query
	m_pPitcherStats_set->Requery();

	m_arrayPitcherNames->RemoveAll();

	while (!m_pPitcherStats_set->IsEOF())
	{
		tmpPitcherID.Format("%d", m_pPitcherStats_set->m_PitcherID);
		m_pPitcher_set->m_strFilter = "[PitcherID] = " + tmpPitcherID;
		m_pPitcher_set->Requery();

		while (!m_pPitcher_set->IsEOF())
		{
			m_arrayPitcherNames->Add(m_pPitcher_set->m_LastName);
			m_pPitcher_set->MoveNext();
		}

		m_pPitcherStats_set->MoveNext();
	}

	return m_arrayPitcherNames;
}

// Return array with "Lastname, Firstname"
CStringArray* PitcherStruct::GetPitcherLastFirstArray(long TeamID)
{
	CString tmpTeamID;
	CString tmpPitcherID;
	CString tmpName;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpTeamID.Format("%d", TeamID);
	m_pPitcherStats_set->m_strFilter = "[TeamID] = " + tmpTeamID;
	// Execute the query
	m_pPitcherStats_set->Requery();

	m_arrayPitcherNames->RemoveAll();

	while (!m_pPitcherStats_set->IsEOF())
	{
		tmpPitcherID.Format("%d", m_pPitcherStats_set->m_PitcherID);
		m_pPitcher_set->m_strFilter = "[PitcherID] = " + tmpPitcherID;
		m_pPitcher_set->Requery();

		while (!m_pPitcher_set->IsEOF())
		{
			tmpName = m_pPitcher_set->m_LastName + ", " + m_pPitcher_set->m_FirstName;
			m_arrayPitcherNames->Add(tmpName);
			m_pPitcher_set->MoveNext();
		}

		m_pPitcherStats_set->MoveNext();
	}

	return m_arrayPitcherNames;
}

/////////////////////////////////////////////////////////////////////////////
// LeagueStruct

LeagueStruct::LeagueStruct()
{
	CBaseballDoc* pDoc = CBaseballDoc::GetDoc();
	ASSERT_VALID(pDoc);

	// Allocate the recordset
	m_pLeagues_set = new CLeagues(&pDoc->m_pDatabase);

	// Allocate the Teams recordset
	CTeams rsTeam(&pDoc->m_pDatabase);
	TRY
	{
		// Execute the query
		m_pLeagues_set->Open(CRecordset::dynaset, NULL, CRecordset::none);
	}
		CATCH(CDBException, e)
	{
			// If a database exception occured, show error msg
			AfxMessageBox("Database Leagues RS error: " + e->m_strError);
	}
	END_CATCH;
	m_arrayLeagueNames = new CStringArray();
}

LeagueStruct::~LeagueStruct()
{
	TRY
	{
		if (m_pLeagues_set->IsOpen())
		m_pLeagues_set->Close();
	}
		CATCH(CDBException, e)
	{
			// If a database exception occured, show error msg
			AfxMessageBox("Database Close error LeagueStruct: " + e->m_strError);
	}
	END_CATCH;
}

long LeagueStruct::GetLeagueID(CString strLeagueName)
{
	long retLeagueID = 0;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	m_pLeagues_set->m_strFilter = "[LeagueName] = '" + strLeagueName + "'";
	// Execute the query
	m_pLeagues_set->Requery();

	if (!m_pLeagues_set->IsEOF())
	{
		retLeagueID = m_pLeagues_set->m_LeagueID;
	}

	return retLeagueID;
}

CStringArray* LeagueStruct::GetAllLeagues()
{
	CString tmpLaegueID;

	// Execute the query
	m_pLeagues_set->Requery();

	m_arrayLeagueNames->RemoveAll();

	while (!m_pLeagues_set->IsEOF())
	{
		m_arrayLeagueNames->Add(m_pLeagues_set->m_LeagueName);
		m_pLeagues_set->MoveNext();
	}

	return m_arrayLeagueNames;
}

/////////////////////////////////////////////////////////////////////////////
// TeamStruct

TeamStruct::TeamStruct()
{
	CBaseballDoc* pDoc = CBaseballDoc::GetDoc();
	ASSERT_VALID(pDoc);

	// Allocate the recordset
	m_pTeams_set = new CTeams(&pDoc->m_pDatabase);

	// Allocate the Teams recordset
	CTeams rsTeam(&pDoc->m_pDatabase);
	TRY
	{
		// Execute the query
		m_pTeams_set->Open(CRecordset::dynaset, NULL, CRecordset::none);
	}
		CATCH(CDBException, e)
	{
			// If a database exception occured, show error msg
			AfxMessageBox("Database Teams RS error: " + e->m_strError);
	}
	END_CATCH;
	m_arrayTeamNames = new CStringArray();
}

TeamStruct::~TeamStruct()
{
	TRY
	{
		if (m_pTeams_set->IsOpen())
		m_pTeams_set->Close();
	}
		CATCH(CDBException, e)
	{
			// If a database exception occured, show error msg
			AfxMessageBox("Database Close error TeamStruct: " + e->m_strError);
	}
	END_CATCH;
}

/////////////////////////////////////////////////////////////////////////////

// Return an array of team names
CStringArray* TeamStruct::GetTeams(long LeagueID)
{
	CString tmpLaegueID;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpLaegueID.Format("%d", LeagueID);
	m_pTeams_set->m_strFilter = "[LeagueID] = " + tmpLaegueID;
	// Execute the query
	m_pTeams_set->Requery();

	m_arrayTeamNames->RemoveAll();

	while (!m_pTeams_set->IsEOF())
	{
		m_arrayTeamNames->Add(m_pTeams_set->m_TeamName);
		m_pTeams_set->MoveNext();
	}

	return m_arrayTeamNames;
}


long TeamStruct::GetTeamID(CString strTeamName, long LeagueID)
{
	CString tmpLaegueID;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpLaegueID.Format("%d", LeagueID);
	m_pTeams_set->m_strFilter = "[TeamName] = '" + strTeamName + "' AND " + "[LeagueID] = " + tmpLaegueID;
	// Execute the query
	m_pTeams_set->Requery();

	return m_pTeams_set->m_TeamID;
}

CString TeamStruct::GetTeamName(long TeamID)
{
	CString tmpTeamID;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpTeamID.Format("%d", TeamID);
	m_pTeams_set->m_strFilter = "[TeamID] = " + tmpTeamID;
	// Execute the query
	m_pTeams_set->Requery();

	return m_pTeams_set->m_TeamName;
}

CString TeamStruct::GetTeamShortName(long TeamID)
{
	CString tmpTeamID;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpTeamID.Format("%d", TeamID);
	m_pTeams_set->m_strFilter = "[TeamID] = " + tmpTeamID;
	// Execute the query
	m_pTeams_set->Requery();

	return m_pTeams_set->m_TeamNameShort;
}

CString TeamStruct::GetBallparkName(long TeamID)
{
	CString tmpTeamID;

	// Update the filter which is the WHERE portion to find the teams
	// based on a given league.
	tmpTeamID.Format("%d", TeamID);
	m_pTeams_set->m_strFilter = "[TeamID] = " + tmpTeamID;
	// Execute the query
	m_pTeams_set->Requery();

	return m_pTeams_set->m_BallparkName;
}
