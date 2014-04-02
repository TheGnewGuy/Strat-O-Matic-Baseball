// FileStruct.cpp : implementation file
//

#include "stdafx.h"
#include "Baseball.h"
#include "BaseballDoc.h"
#include "Leagues.h"
#include "Teams.h"
#include "FileStruct.h"

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
		m_pBatter_set->Open(CRecordset::snapshot, NULL, CRecordset::none);
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
		m_pBatterStats_set->Open(CRecordset::snapshot, NULL, CRecordset::none);
	}
		CATCH(CDBException, e)
	{
			// If a database exception occured, show error msg
			AfxMessageBox("Database BatterStats RS error: " + e->m_strError);
	}
	END_CATCH;
	m_arrayBatterNames = new CStringArray();
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
}

int BatterStruct::UpdateBatter(CString BatterFileName, LONG SeekPosition)
{
	CFile m_cFileTeam;
	m_cFileTeam.Open( BatterFileName,CFile::modeReadWrite);
	m_cFileTeam.Seek( SeekPosition, CFile::begin );
	BatterWrite(&m_cFileTeam);
	// Close file
	m_cFileTeam.Close();
	return 1;
}

int BatterStruct::AddBatter(CString BatterFileName)
{
	BYTE count;
	CFile m_cFileTeam;

	count = 0;
	// Open file and write new player
	m_cFileTeam.Open(BatterFileName,CFile::modeReadWrite);
	m_cFileTeam.Read(&count,sizeof(count));
	count++;
	m_cFileTeam.SeekToBegin();
	m_cFileTeam.Write(&count,sizeof(count));
	m_cFileTeam.SeekToEnd();
	BatterWrite(&m_cFileTeam);
	// Close file
	m_cFileTeam.Close();
	return 1;
}

int BatterStruct::GetBatter(CString BatterFileName, LONG SeekPosition)
{
	CFile m_cFileTeam;
	m_cFileTeam.Open( BatterFileName,CFile::modeRead);
	m_cFileTeam.Seek( SeekPosition, CFile::begin );
	BatterRead(&m_cFileTeam);
	// Close file
	m_cFileTeam.Close();
	return 1;
}

int BatterStruct::BatterWrite(CFile * myFile)
{
	myFile->Write(m_PlayerName,30);
	myFile->Write(&m_AB,sizeof(m_AB));
	myFile->Write(&m_Runs,sizeof(m_Runs));
	myFile->Write(&m_Hits,sizeof(m_Hits));
	myFile->Write(&m_RBI,sizeof(m_RBI));
	myFile->Write(&m_2B,sizeof(m_2B));
	myFile->Write(&m_3B,sizeof(m_3B));
	myFile->Write(&m_HomeRuns,sizeof(m_HomeRuns));
	myFile->Write(&m_Walk,sizeof(m_Walk));
	myFile->Write(&m_StrikeOut,sizeof(m_StrikeOut));
	myFile->Write(&m_ReachedOnError,sizeof(m_ReachedOnError));
	myFile->Write(&m_Sacrifice,sizeof(m_Sacrifice));
	myFile->Write(&m_StolenBase,sizeof(m_StolenBase));
	myFile->Write(&m_CS,sizeof(m_CS));
	myFile->Write(&m_Filler1,sizeof(m_Filler1));
	myFile->Write(&m_Filler2,sizeof(m_Filler2));
	myFile->Write(&m_Games,sizeof(m_Games));
	myFile->Write(&m_HBP,sizeof(m_HBP));
	myFile->Write(&m_Pitcher,sizeof(m_Pitcher));
	myFile->Write(&m_Catcher,sizeof(m_Catcher));
	myFile->Write(&m_FirstBase,sizeof(m_FirstBase));
	myFile->Write(&m_SecondBase,sizeof(m_SecondBase));
	myFile->Write(&m_ShortStop,sizeof(m_ShortStop));
	myFile->Write(&m_ThirdBase,sizeof(m_ThirdBase));
	myFile->Write(&m_LeftField,sizeof(m_LeftField));
	myFile->Write(&m_CenterField,sizeof(m_CenterField));
	myFile->Write(&m_RightField,sizeof(m_RightField));
	myFile->Write(&m_bER1,sizeof(m_bER1));
	myFile->Write(&m_bER2,sizeof(m_bER2));
	myFile->Write(&m_bER3,sizeof(m_bER3));
	myFile->Write(&m_bER4,sizeof(m_bER4));
	myFile->Write(&m_bER5,sizeof(m_bER5));
	myFile->Write(&m_bER6,sizeof(m_bER6));
	myFile->Write(&m_bER7,sizeof(m_bER7));
	myFile->Write(&m_bER8,sizeof(m_bER8));
	myFile->Write(&m_bER9,sizeof(m_bER9));
	myFile->Write(&m_bBatterHits,sizeof(m_bBatterHits));
	myFile->Write(m_OBChanceBasic,6);
	myFile->Write(m_OBChanceLeft,6);
	myFile->Write(m_OBChanceRight,6);
	myFile->Write(m_OBChanceWalk,6);
	myFile->Write(m_OBChanceSingle,6);
	myFile->Write(m_OBChanceDouble,6);
	myFile->Write(m_OBChanceTriple,6);
	myFile->Write(m_OBChanceHomeRun,6);
	myFile->Write(m_ChanceDoublePlay,6);
	myFile->Write(m_OBChanceWalkRight,6);		// Filler
	myFile->Write(m_OBChanceSingleRight,6);
	myFile->Write(m_OBChanceDoubleRight,6);
	myFile->Write(m_OBChanceTripleRight,6);
	myFile->Write(m_OBChanceHomeRunRight,6);
	myFile->Write(m_ChanceDoublePlayRight,6);
	myFile->Write(m_OBChanceWalkLeft,6);
	myFile->Write(m_OBChanceSingleLeft,6);
	myFile->Write(m_OBChanceDoubleLeft,6);
	myFile->Write(m_OBChanceTripleLeft,6);
	myFile->Write(m_OBChanceHomeRunLeft,6);
	myFile->Write(m_ChanceDoublePlayLeft,6);
	myFile->Write("0     ",6);		// Filler
	myFile->Write("0     ",6);		// Filler
	myFile->Write("0     ",6);		// Filler
	myFile->Write(&m_bBunting,sizeof(m_bBunting));
	myFile->Write(&m_bHitRun,sizeof(m_bHitRun));
	myFile->Write(&m_bRunning,sizeof(m_bRunning));
	myFile->Write(&m_bStealing,sizeof(m_bStealing));
	myFile->Write(&m_bTRate,sizeof(m_bTRate));	// Place holder for T Rating
	myFile->Write(&m_bPass,sizeof(m_bPass));	// Place holder for Passball
	myFile->Write(&m_bPowerL,sizeof(m_bPowerL));	// Place holder for Power Left
	myFile->Write(&m_bPowerR,sizeof(m_bPowerR));	// Place holder for Power Right
	myFile->Write(&m_bOutArm,sizeof(m_bOutArm));	// Place holder for Outfielder Arm
	myFile->Write(&m_bCatchArm,sizeof(m_bCatchArm));	// Place holder for Catcher Arm
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	return 1;
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
	//m_pBatter_set->m_BatterHits;
}

int BatterStruct::BatterRead(CFile * myFile)
{
	char cTemp[31];
	BYTE bTemp;

	myFile->Read(cTemp,30);
	cTemp[30]=NULL;
	m_PlayerName = cTemp;
	myFile->Read(&m_AB,sizeof(m_AB));
	myFile->Read(&m_Runs,sizeof(m_Runs));
	myFile->Read(&m_Hits,sizeof(m_Hits));
	myFile->Read(&m_RBI,sizeof(m_RBI));
	myFile->Read(&m_2B,sizeof(m_2B));
	myFile->Read(&m_3B,sizeof(m_3B));
	myFile->Read(&m_HomeRuns,sizeof(m_HomeRuns));
	myFile->Read(&m_Walk,sizeof(m_Walk));
	myFile->Read(&m_StrikeOut,sizeof(m_StrikeOut));
	myFile->Read(&m_ReachedOnError,sizeof(m_ReachedOnError));
	myFile->Read(&m_Sacrifice,sizeof(m_Sacrifice));
	myFile->Read(&m_StolenBase,sizeof(m_StolenBase));
	myFile->Read(&m_CS,sizeof(m_CS));
	myFile->Read(&m_Filler1,sizeof(m_Filler1));
	myFile->Read(&m_Filler2,sizeof(m_Filler2));
	myFile->Read(&m_Games,sizeof(m_Games));
	myFile->Read(&m_HBP,sizeof(m_HBP));
	myFile->Read(&m_Pitcher,sizeof(m_Pitcher));
	myFile->Read(&m_Catcher,sizeof(m_Catcher));
	myFile->Read(&m_FirstBase,sizeof(m_FirstBase));
	myFile->Read(&m_SecondBase,sizeof(m_SecondBase));
	myFile->Read(&m_ShortStop,sizeof(m_ShortStop));
	myFile->Read(&m_ThirdBase,sizeof(m_ThirdBase));
	myFile->Read(&m_LeftField,sizeof(m_LeftField));
	myFile->Read(&m_CenterField,sizeof(m_CenterField));
	myFile->Read(&m_RightField,sizeof(m_RightField));
	myFile->Read(&m_bER1,sizeof(m_bER1));
	myFile->Read(&m_bER2,sizeof(m_bER2));
	myFile->Read(&m_bER3,sizeof(m_bER3));
	myFile->Read(&m_bER4,sizeof(m_bER4));
	myFile->Read(&m_bER5,sizeof(m_bER5));
	myFile->Read(&m_bER6,sizeof(m_bER6));
	myFile->Read(&m_bER7,sizeof(m_bER7));
	myFile->Read(&m_bER8,sizeof(m_bER8));
	myFile->Read(&m_bER9,sizeof(m_bER9));
	myFile->Read(&m_bBatterHits,sizeof(m_bBatterHits));
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceBasic = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceLeft = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceWalk = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceSingle = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceDouble = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceTriple = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceHomeRun = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_ChanceDoublePlay = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceWalkRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceSingleRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceDoubleRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceTripleRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceHomeRunRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_ChanceDoublePlayRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceWalkLeft = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceSingleLeft = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceDoubleLeft = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceTripleLeft = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceHomeRunLeft = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_ChanceDoublePlayLeft = cTemp;
	myFile->Read(cTemp,6);
	myFile->Read(cTemp,6);
	myFile->Read(cTemp,6);
	myFile->Read(&m_bBunting,sizeof(m_bBunting));
	myFile->Read(&m_bHitRun,sizeof(m_bHitRun));
	myFile->Read(&m_bRunning,sizeof(m_bRunning));
	myFile->Read(&m_bStealing,sizeof(m_bStealing));
	myFile->Read(&m_bTRate,sizeof(m_bTRate));	// Place holder for T Rating
	myFile->Read(&m_bPass,sizeof(m_bPass));	// Place holder for Passball
	myFile->Read(&m_bPowerL,sizeof(m_bPowerL));	// Place holder for Power Left
	myFile->Read(&m_bPowerR,sizeof(m_bPowerR));	// Place holder for Power Right
	myFile->Read(&m_bOutArm,sizeof(m_bOutArm));	// Place holder for Outfielder Arm
	myFile->Read(&m_bCatchArm,sizeof(m_bCatchArm));	// Place holder for Catcher Arm
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	return 1;
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
		BatterRead(&inFile);
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
		BatterWrite(&outFile);
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
}

PitcherStruct::~PitcherStruct()
{
}

int PitcherStruct::UpdatePitcher(CString PitcherFileName, LONG SeekPosition)
{
	CFile m_cFileTeam;
	m_cFileTeam.Open( PitcherFileName,CFile::modeReadWrite);
	m_cFileTeam.Seek( SeekPosition, CFile::begin );
	PitcherWrite(&m_cFileTeam);
	// Close file
	m_cFileTeam.Close();
	return 1;
}

int PitcherStruct::AddPitcher(CString PitcherFileName)
{
	BYTE count;
	CFile m_cFileTeam;

	count = 0;
	// Open file and write new player
	m_cFileTeam.Open(PitcherFileName,CFile::modeReadWrite);
	m_cFileTeam.Read(&count,sizeof(count));
	count++;
	m_cFileTeam.SeekToBegin();
	m_cFileTeam.Write(&count,sizeof(count));
	m_cFileTeam.SeekToEnd();
	PitcherWrite(&m_cFileTeam);
	// Close file
	m_cFileTeam.Close();
	return 1;
}

int PitcherStruct::GetPitcher(CString PitcherFileName, LONG SeekPosition)
{
	CFile m_cFileTeam;
	m_cFileTeam.Open( PitcherFileName,CFile::modeRead);
	m_cFileTeam.Seek( SeekPosition, CFile::begin );
	PitcherRead(&m_cFileTeam);
	// Close file
	m_cFileTeam.Close();
	return 1;
}

int PitcherStruct::PitcherWrite(CFile * myFile)
{
	myFile->Write(m_PitcherName,30);
	myFile->Write(&m_Wins,sizeof(m_Wins));
	myFile->Write(&m_Loss,sizeof(m_Loss));
	myFile->Write(&m_Saves,sizeof(m_Saves));
	myFile->Write(m_IP,7);
	myFile->Write(&m_ER,sizeof(m_ER));
	myFile->Write(&m_Hits,sizeof(m_Hits));
	myFile->Write(&m_Walks,sizeof(m_Walks));
	myFile->Write(&m_Strikeouts,sizeof(m_Strikeouts));
	myFile->Write(&m_HomeRuns,sizeof(m_HomeRuns));
	myFile->Write(&m_Filler1,sizeof(m_Filler1));
	myFile->Write(&m_Games,sizeof(m_Games));
	myFile->Write(&m_CompGames,sizeof(m_CompGames));
	myFile->Write(&m_Starts,sizeof(m_Starts));
	myFile->Write(m_OBChanceBasic,6);
	myFile->Write(m_OBChanceLeft,6);
	myFile->Write(m_OBChanceRight,6);
	myFile->Write(m_OBChanceWalk,6);
	myFile->Write(m_OBChanceSingle,6);
	myFile->Write(m_OBChanceDouble,6);
	myFile->Write(m_OBChanceTriple,6);
	myFile->Write(m_OBChanceHomeRun,6);
	myFile->Write(m_ChanceDoublePlay,6);
	myFile->Write(m_OBChanceWalkRight,6);
	myFile->Write(m_OBChanceSingleRight,6);
	myFile->Write(m_OBChanceDoubleRight,6);
	myFile->Write(m_OBChanceTripleRight,6);
	myFile->Write(m_OBChanceHomeRunRight,6);
	myFile->Write(m_ChanceDoublePlayRight,6);
	myFile->Write(m_OBChanceWalkLeft,6);
	myFile->Write(m_OBChanceSingleLeft,6);
	myFile->Write(m_OBChanceDoubleLeft,6);
	myFile->Write(m_OBChanceTripleLeft,6);
	myFile->Write(m_OBChanceHomeRunLeft,6);
	myFile->Write(m_ChanceDoublePlayLeft,6);
	myFile->Write("0     ",6);		// Filler
	myFile->Write("0     ",6);		// Filler
	myFile->Write("0     ",6);		// Filler
	myFile->Write(&m_Starter,sizeof(m_Starter));
	myFile->Write(&m_Relief,sizeof(m_Relief));
	myFile->Write(&m_Throws,sizeof(m_Throws));
	myFile->Write(&m_Bunting,sizeof(m_Bunting));
	myFile->Write(&m_Hold,sizeof(m_Hold));
	myFile->Write(&m_bWP,sizeof(m_bWP));
	myFile->Write(&m_bBalk,sizeof(m_bBalk));
	myFile->Write(&m_bER1,sizeof(m_bER1));
	myFile->Write(&m_PitcherField,sizeof(m_PitcherField));	// Pitcher field rating
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	myFile->Write(&m_bFiller1,sizeof(BYTE));	// Filler
	return 1;
}

int PitcherStruct::PitcherRead(CFile * myFile)
{
	char cTemp[31];
	BYTE bTemp;

	myFile->Read(cTemp,30);
	cTemp[30]=NULL;
	m_PitcherName = cTemp;
	myFile->Read(&m_Wins,sizeof(m_Wins));
	myFile->Read(&m_Loss,sizeof(m_Loss));
	myFile->Read(&m_Saves,sizeof(m_Saves));
	myFile->Read(cTemp,7);
	cTemp[7]=NULL;
	m_IP = cTemp;
	myFile->Read(&m_ER,sizeof(m_ER));
	myFile->Read(&m_Hits,sizeof(m_Hits));
	myFile->Read(&m_Walks,sizeof(m_Walks));
	myFile->Read(&m_Strikeouts,sizeof(m_Strikeouts));
	myFile->Read(&m_HomeRuns,sizeof(m_HomeRuns));
	myFile->Read(&m_Filler1,sizeof(m_Filler1));
	myFile->Read(&m_Games,sizeof(m_Games));
	myFile->Read(&m_CompGames,sizeof(m_CompGames));
	myFile->Read(&m_Starts,sizeof(m_Starts));
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceBasic = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceLeft = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceWalk = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceSingle = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceDouble = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceTriple = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceHomeRun = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_ChanceDoublePlay = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceWalkRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceSingleRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceDoubleRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceTripleRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceHomeRunRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_ChanceDoublePlayRight = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceWalkLeft = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceSingleLeft = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceDoubleLeft = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceTripleLeft = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_OBChanceHomeRunLeft = cTemp;
	myFile->Read(cTemp,6);
	cTemp[6]=NULL;
	m_ChanceDoublePlayLeft = cTemp;
	myFile->Read(cTemp,6);
	myFile->Read(cTemp,6);
	myFile->Read(cTemp,6);
	myFile->Read(&m_Starter,sizeof(m_Starter));
	myFile->Read(&m_Relief,sizeof(m_Relief));
	myFile->Read(&m_Throws,sizeof(m_Throws));
	myFile->Read(&m_Bunting,sizeof(m_Bunting));
	myFile->Read(&m_Hold,sizeof(m_Hold));
	myFile->Read(&m_bWP,sizeof(m_bWP));
	myFile->Read(&m_bBalk,sizeof(m_bBalk));
	myFile->Read(&m_bER1,sizeof(m_bER1));
	myFile->Read(&m_PitcherField,sizeof(m_PitcherField));
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	myFile->Read(&bTemp,sizeof(BYTE));	// Filler
	return 1;
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
		PitcherRead(&inFile);
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
		PitcherWrite(&outFile);
	}
	// Close file
	inFile.Close();
	outFile.Close();
	return 1;
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
		m_pLeagues_set->Open(CRecordset::snapshot, NULL, CRecordset::none);
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
		m_pTeams_set->Open(CRecordset::snapshot, NULL, CRecordset::none);
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
