// FileStruct.cpp : implementation file
//

#include "stdafx.h"
#include "Baseball.h"
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
}

BatterStruct::~BatterStruct()
{
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
	//
	// Version byte
	// Number of Conferences byte
	// LeagueName 30 char
	// Number of Divisions in Conference byte
	// Conference Name 30 char
	// Number of Teams in Division byte
	// Division Name 30 char
	// Team Name 40 char
	// Team file 8 char
	// Short team 3 char
	// Ballpark 20 char
	// Home game wins short
	// Home game losses short
	// Away game wins short
	// Away game losses short
}

LeagueStruct::~LeagueStruct()
{
}

/////////////////////////////////////////////////////////////////////////////
// TeamStruct

TeamStruct::TeamStruct()
{
}

TeamStruct::~TeamStruct()
{
}

/////////////////////////////////////////////////////////////////////////////
