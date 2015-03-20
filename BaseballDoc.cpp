// BaseballDoc.cpp : implementation of the CBaseballDoc class
//
//	08/12/99 Fixed League displays after adding version field to 
//		league file
//	07/01/00 Rewrote edit and add player and pitcher code. This
//		was required to allow the updateing of the error and chance
//		fields. 
//		Version 1.0.0.5
//	09/08/00 Removed code for add and editing players and pitchers. 
//		This code was replaced with new routines. Added code for
//		Chance of Double Plays to Batter and Pitchers. 
//		Version 1.0.0.6
//	09/11/00 Removed code and used common routines for GetLeagues
//		and GetTeams.
//		Version 1.0.0.7
//	09/15/00 Setup code for HTML options. This allows different
//		options for Team and Statistics web pages.
//		Version 1.0.0.8
//  11/20/00 Fixed HTML fields for Total pitching for hits, er and 
//      walks. All three fields were one char too small.
//      Fixed ERA and TRG on HTML league stats for teams that 
//      have been just created and the fields are zero.
//      Added define HTML_DISP_LINES to allow quick change of
//      the number of lines displayed in the HTML League Stats.
//		Cleaned up Cancel logic in Create Leagues. If cancel is 
//		pressed, the new league dir is deleted along with any 
//		league files found in the data directory.
//      Version 1.0.0.9
//  02/03/01 Added fields for Right and Left 2b, 3b, hr, w, and dp.
//		This included updating Dialogs for Batter and Pitcher chance,
//		and the export routine.
//      Version 1.0.0.10
//	01/18/14 Changed in ExportHTMLFile OB% to OB%%
//      Version 1.0.0.11 and Copyright to 2014
//  01/22/14 Changed the XBteam.txt and XPteam.txt to trim trailing spaces from team name
//      resulting in "XP1997 Baltland       .txt" being changed to "XP1997 Baltland.txt"
//
//	New Features to add:
//		1.	Deletion of players and pitchers
//		2.	Building of teams from existing players in Base.
//		3.	Saving and editing wins and losses for teams
//		4.	Editing of Division/Conference/League names
//		5.	In the League HTML (BuildPlayerArray)routine, there 
//			is checking against m_StatCount. If for some reason
//			the number of batters or pitchers is less than m_StatCount,
//			an error will occure due to indexes being out of range.
//			
//

#include "stdafx.h"
#include "Baseball.h"
#include "dialogs.h"
#include "AddLeague.h"
#include "DlgAddDivision.h"
#include "DlgAddTeams.h"
#include "DlgEditLeague.h"
#include "AddTeam.h"
#include "FileStruct.h"
#include "registry.h"
#include <direct.h>
#include <errno.h>

#include "BaseballDoc.h"
#include "sqlite3.h"

#define HTML_DISP_LINES 10

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#undef THIS_DATE
static char THIS_DATE[] = __DATE__;
#undef THIS_TIME
static char THIS_TIME[] = __TIME__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseballDoc

IMPLEMENT_DYNCREATE(CBaseballDoc, CDocument)

BEGIN_MESSAGE_MAP(CBaseballDoc, CDocument)
	//{{AFX_MSG_MAP(CBaseballDoc)
	ON_COMMAND(ID_FORMS_SCORESHEETFORM, OnFormsScoresheetform)
	ON_COMMAND(ID_FORMS_SCORESHEETFORMXTRA, OnFormsScoresheetformxtra)
	ON_COMMAND(ID_FORMS_STATISTCSFORM, OnFormsStatistcsform)
	ON_UPDATE_COMMAND_UI(ID_FORMS_SCORESHEETFORM, OnUpdateFormsScoresheetform)
	ON_UPDATE_COMMAND_UI(ID_FORMS_SCORESHEETFORMXTRA, OnUpdateFormsScoresheetformxtra)
	ON_UPDATE_COMMAND_UI(ID_FORMS_STATISTCSFORM, OnUpdateFormsStatistcsform)
	ON_COMMAND(ID_VIEW_NORMAL, OnViewNormal)
	ON_UPDATE_COMMAND_UI(ID_VIEW_NORMAL, OnUpdateViewNormal)
	ON_COMMAND(ID_LEAGUES_ADDLEAGUE, OnLeaguesAddleague)
	ON_COMMAND(ID_TEAMS_ADDTEAMS, OnTeamsAddteams)
	ON_COMMAND(ID_FILE_EXPORTLEAGUETEAMS, OnFileExportLeagueTeams)
	ON_COMMAND(ID_FILE_EXPORTHTMLLEAGUETEAMS, OnFileExportHTMLLeagueTeams)
	ON_COMMAND(ID_TEAMS_EDITLEAGUETEAMS, OnTeamsEditLeagueTeams)
	ON_COMMAND(ID_STATISTICS_HTMLLEAGUESTATS, OnStatisticsHTMLLeagueStats)
	ON_COMMAND(ID_FILE_EXPORTHTMLLEAGUETEAMSALL, OnFileExportHtmlLeagueTeamsAll)
	ON_COMMAND(ID_FILE_EXPORTLEAGUETEAMSALL, OnFileExportLeagueTeamsAll)
	ON_COMMAND(ID_PLAYERS_ADDEDITBATTERS, OnPlayersAddEditBatters)
	ON_COMMAND(ID_PLAYERS_ADDEDITPITCHERS, OnPlayersAddEditPitchers)
	ON_COMMAND(ID_LEAGUES_LEAGUEOPTIONSHTML, OnLeaguesLeagueOptionsHTML)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_OPEN, &CBaseballDoc::OnFileOpen)
	ON_COMMAND(ID_LEAGUES_EDITLEAGUE, &CBaseballDoc::OnLeaguesEditLeague)
	ON_COMMAND(ID_TEAMS_ADDBASETEAMS, &CBaseballDoc::OnTeamsAddBaseTeams)
	ON_COMMAND(ID_LEAGUES_ADDBASELEAGUE, &CBaseballDoc::OnLeaguesAddBaseLeague)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseballDoc construction/destruction

CBaseballDoc::CBaseballDoc()
{
	// TODO: add one-time construction code here
	SetAllFormsFalse();
	// Load the sqlite DataBase file
	//bWorking = myFileFind.FindFile("data\\TB*.dat", 0);


	m_DBFileName = _T("");
	m_dbOpen = 99;		// SQLITE_OK is set to '0'
}

CBaseballDoc::~CBaseballDoc()
{
	if (m_dbOpen = SQLITE_OK)
	{
		sqlite3_close(m_db);
		m_dbOpen = 99;
	}
}

BOOL CBaseballDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBaseballDoc serialization

void CBaseballDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBaseballDoc diagnostics

#ifdef _DEBUG
void CBaseballDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBaseballDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBaseballDoc commands

void CBaseballDoc::OnViewNormal() 
{
	// TODO: Add your command handler code here
	m_NormalView = TRUE;
	m_ScoresheetForm = FALSE;
	m_ScoresheetFormXtra = FALSE;
	m_StatisticsForm = FALSE;
	UpdateAllViews(NULL,0L,NULL);
}

void CBaseballDoc::OnFormsScoresheetform() 
{
	// TODO: Add your command handler code here
	m_NormalView = FALSE;
	m_ScoresheetForm = TRUE;
	m_ScoresheetFormXtra = FALSE;
	m_StatisticsForm = FALSE;
	UpdateAllViews(NULL,0L,NULL);
}

void CBaseballDoc::OnFormsScoresheetformxtra() 
{
	// TODO: Add your command handler code here
	m_NormalView = FALSE;
	m_ScoresheetForm = FALSE;
	m_ScoresheetFormXtra = TRUE;
	m_StatisticsForm = FALSE;
	UpdateAllViews(NULL,0L,NULL);
}

void CBaseballDoc::OnFormsStatistcsform() 
{
	// TODO: Add your command handler code here
	m_NormalView = FALSE;
	m_ScoresheetForm = FALSE;
	m_ScoresheetFormXtra = FALSE;
	m_StatisticsForm = TRUE;
	UpdateAllViews(NULL,0L,NULL);
}

BOOL CBaseballDoc::GetNormalView()
{
	return m_NormalView;
}

BOOL CBaseballDoc::GetScoresheetForm()
{
	return m_ScoresheetForm;
}

BOOL CBaseballDoc::GetScoresheetFormXtra()
{
	return m_ScoresheetFormXtra;
}

BOOL CBaseballDoc::GetStatisticsForm()
{
	return m_StatisticsForm;
}

void CBaseballDoc::SetAllFormsFalse()
{
	m_NormalView = TRUE;
	m_ScoresheetForm = FALSE;
	m_ScoresheetFormXtra = FALSE;
	m_StatisticsForm = FALSE;
}

void CBaseballDoc::OnUpdateViewNormal(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_NormalView)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CBaseballDoc::OnUpdateFormsScoresheetform(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_ScoresheetForm)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CBaseballDoc::OnUpdateFormsScoresheetformxtra(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_ScoresheetFormXtra)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CBaseballDoc::OnUpdateFormsStatistcsform(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if (m_StatisticsForm)
	{
		pCmdUI->SetCheck(TRUE);
	}
	else
	{
		pCmdUI->SetCheck(FALSE);
	}
}

void CBaseballDoc::OnTeamsAddBaseTeams()
{
	// TODO: Add your command handler code here
	AddTeam dlg;
	CString strTeamName;
	CString strShortTeamName;
	CString strBallPark;
	int leagueID = 0;
	int conferenceID = 0;
	int divisionID = 0;
	m_LeagueRecord leagueRecord;
	m_ConferenceRecord conferenceRecord;
	m_DivisionRecord divisionRecord;
	m_TeamRecord teamRecord;

	// Get League, Conference and Division to populate Team fields.
	leagueID = GetLeagues(TRUE);
	leagueRecord = GetLeague(leagueID);
	conferenceID = GetConferenceID(leagueID);
	conferenceRecord = GetConference(conferenceID);
	divisionID = GetDivisionID(leagueID);
	divisionRecord = GetDivision(divisionID);


	dlg.m_TeamName = _T("Team Name");
	dlg.m_League = leagueRecord.LeagueName;
	dlg.m_Conference = conferenceRecord.ConferenceName;
	dlg.m_Division = divisionRecord.DivisionName;
	dlg.m_Base = TRUE;
	if (dlg.DoModal() == IDOK)
	{
		teamRecord.TeamName = dlg.m_TeamName;
		teamRecord.TeamNameShort = dlg.m_ShortTeamName;
		teamRecord.BallparkName = dlg.m_BallPark;
		teamRecord.HomeWins = dlg.m_HomeWin;
		teamRecord.HomeLosses = dlg.m_HomeLoss;
		teamRecord.AwayWins = dlg.m_AwayWin;
		teamRecord.AwayLosses = dlg.m_AwayLoss;
		teamRecord.LeagueID = leagueID;
		teamRecord.ConferenceID = conferenceID;
		teamRecord.DivisionID = divisionID;
		teamRecord.TeamYear = dlg.m_Year;
		teamRecord.BaseTeam = dlg.m_Base;
		TeamInsert(teamRecord);
	}
}

void CBaseballDoc::OnTeamsAddteams() 
{
	// TODO: Add your command handler code here
	AddTeam dlg;
	CFile myFileBatter;
	CFile myFilePitcher;
	BYTE count;
	CString strTeamName;
	CString strShortTeamName;
	CString strBallPark;
	CString filler10("          ");
	CString strFileNameBatter;
	CString strFileNamePitcher;
	CString strFileTitle;
	CStringArray arrayFileNumber;
	CString strFileNumber;
	char strNewFileNumber[10];
	CFileFind myFileFind;
	BOOL bWorking;
	long lFileNumber;
	int i,sortflag;
	CString strTemp;

	count = 0;

	// Find all existing batter files TB000000.dat
	// Create the next sequential file. If not found
	// start at 0
	bWorking = myFileFind.FindFile("data\\TB*.dat",0);
	if (bWorking)
	{
		while (bWorking)
		{
			bWorking = myFileFind.FindNextFile();
			strFileTitle = myFileFind.GetFileTitle();
			arrayFileNumber.Add(strFileTitle.Right(6));
		}
	}
	else
	{
		arrayFileNumber.Add("000000");
	}
	myFileFind.Close();

	// Since the FindNextFile does not return the files in any order
	// we must sort the file names to get highest number
	sortflag = 1;
	while (sortflag)
	{
		sortflag = 0;
		for (i=0; i<(arrayFileNumber.GetSize()-1);i++)
		{
			if (arrayFileNumber[i].Compare(arrayFileNumber[i+1]) == 1)
			{
				strTemp = arrayFileNumber[i];
				arrayFileNumber[i] = arrayFileNumber[i+1];
				arrayFileNumber[i+1] = strTemp;
				sortflag = 1;
			}
		}
	}

	lFileNumber = atol(arrayFileNumber[arrayFileNumber.GetSize()-1]);
	lFileNumber++;
	sprintf_s(strNewFileNumber,"%6.6lu",lFileNumber);
	strFileNumber = strNewFileNumber;
	strFileNameBatter = "data\\TB"+strFileNumber+".dat";
	strFileNamePitcher = "data\\TP"+strFileNumber+".dat";

	if (dlg.DoModal() == IDOK)
	{
		// Create a Batter file with zero counter and team name
		strTeamName = dlg.m_TeamName+filler10+filler10+filler10+filler10;
		strShortTeamName = dlg.m_BallPark;
		strBallPark = dlg.m_ShortTeamName;
		myFileBatter.Open(strFileNameBatter,CFile::modeCreate | CFile::modeWrite);
		myFileBatter.Write(&count, sizeof(count));
		myFileBatter.Write(strTeamName, 40);
		myFileBatter.Write(strShortTeamName, 3);
		myFileBatter.Write(strBallPark, 30);
		myFileBatter.Close();
		// Create Pitcher file only with a zero counter
		myFilePitcher.Open(strFileNamePitcher,CFile::modeCreate | CFile::modeWrite);
		myFilePitcher.Write(&count, sizeof(count));
		myFilePitcher.Close();
	}
}

void CBaseballDoc::OnLeaguesAddBaseLeague()
{
	// TODO: Add your command handler code here
}

void CBaseballDoc::OnLeaguesAddleague() 
{
	// TODO: Add your command handler code here
	BatterStruct structBatter;
	PitcherStruct structPitcher;
	int i,j,k,ii;
	AddLeague dlg;
	DlgAddDivision dlgDivision;
	DlgAddTeams dlgTeams;
	CFile myFile;
	CString filler10("          ");
	CStringArray arrayConference;
	CStringArray arrayDivision;
	BYTE version;
	BYTE conferencenumber;
	CString leaguename;
	BYTE divisionnumber;
	CString conferencename;
	BYTE teamsnumber;
	CString divisionname;
	CString teamname;
	CString strFileName;
	CString strFileTitle;
	CStringArray arrayFileNumber;
	CString strFileNumber;
	CString strLeagueDir;
	char strNewFileNumber[10];
	CFileFind myFileFind;
	BOOL bWorking;
	long lFileNumber;
	int sortflag;
	CString strTemp;
	CStringArray arrayFileNames;
	BYTE count;
	CFile myInFile;
	CFile myTempFile;
	char temp[41];
	CString strTeamName;
	short winloss = 0;
	CFileStatus myFileStatus;
	int myFileCancel = FALSE;

	version = 1;	// Set version of file
	arrayConference.RemoveAll();
	arrayDivision.RemoveAll();
	dlg.m_Conference1.Empty();
	dlg.m_Conference2.Empty();
	dlg.m_Conference3.Empty();
	dlg.m_Conference4.Empty();
	dlg.m_Conference5.Empty();
	dlg.m_Conference6.Empty();
	dlgDivision.m_Division1.Empty();
	dlgDivision.m_Division2.Empty();
	dlgDivision.m_Division3.Empty();
	dlgDivision.m_Division4.Empty();
	dlgDivision.m_Division5.Empty();
	dlgDivision.m_Division6.Empty();

	if (dlg.DoModal() == IDOK)
	{
		leaguename = dlg.m_NewLeagueName+filler10+filler10+filler10;
		conferencenumber = 0;
		arrayConference.RemoveAll();
		if (!dlg.m_Conference1.IsEmpty()) arrayConference.Add(dlg.m_Conference1+filler10+filler10+filler10);
		if (!dlg.m_Conference2.IsEmpty()) arrayConference.Add(dlg.m_Conference2+filler10+filler10+filler10);
		if (!dlg.m_Conference3.IsEmpty()) arrayConference.Add(dlg.m_Conference3+filler10+filler10+filler10);
		if (!dlg.m_Conference4.IsEmpty()) arrayConference.Add(dlg.m_Conference4+filler10+filler10+filler10);
		if (!dlg.m_Conference5.IsEmpty()) arrayConference.Add(dlg.m_Conference5+filler10+filler10+filler10);
		if (!dlg.m_Conference6.IsEmpty()) arrayConference.Add(dlg.m_Conference6+filler10+filler10+filler10);
		if (!arrayConference.GetSize()) arrayConference.Add("NULL"+filler10+filler10+filler10);
		conferencenumber = arrayConference.GetSize();

		bWorking = myFileFind.FindFile("data\\L*.dat",0);
		if (bWorking)
		{
			while (bWorking)
			{
				bWorking = myFileFind.FindNextFile();
				strFileTitle = myFileFind.GetFileTitle();
				arrayFileNumber.Add(strFileTitle.Right(7));
			}
		}
		else
		{
			arrayFileNumber.Add("0000000");
		}
		myFileFind.Close();

		// Since the FindNextFile does not return the files in any order
		// we must sort the file names
		sortflag = 1;
		while (sortflag)
		{
			sortflag = 0;
			for (i=0; i<(arrayFileNumber.GetSize()-1);i++)
			{
				if (arrayFileNumber[i].Compare(arrayFileNumber[i+1]) == 1)
				{
					strTemp = arrayFileNumber[i];
					arrayFileNumber[i] = arrayFileNumber[i+1];
					arrayFileNumber[i+1] = strTemp;
					sortflag = 1;
				}
			}
		}

		lFileNumber = atol(arrayFileNumber[arrayFileNumber.GetSize()-1]);
		lFileNumber++;
		sprintf_s(strNewFileNumber,"%7.7lu",lFileNumber);
		strFileNumber = strNewFileNumber;
		strFileName = "data\\L"+strFileNumber+".dat";
		strLeagueDir = "L"+ strFileNumber;
		_mkdir(strLeagueDir); // make a directory for league files

		myFile.Open(strFileName,CFile::modeCreate | CFile::modeWrite);
		// Write file version number
		myFile.Write(&version, sizeof(version));
		myFile.Write(&conferencenumber, sizeof(conferencenumber));
		myFile.Write(leaguename, 30);
		for (i=0; i<arrayConference.GetSize(); i++)
		{
			conferencename = arrayConference[i];
			divisionnumber = 0;
			dlgDivision.m_Division1.Empty();
			dlgDivision.m_Division2.Empty();
			dlgDivision.m_Division3.Empty();
			dlgDivision.m_Division4.Empty();
			dlgDivision.m_Division5.Empty();
			dlgDivision.m_Division6.Empty();
			dlgDivision.m_Conference0 = conferencename.Left(30);

			if (dlgDivision.DoModal() == IDOK)
			{
				arrayDivision.RemoveAll();
				if (!dlgDivision.m_Division1.IsEmpty()) arrayDivision.Add(dlgDivision.m_Division1+filler10+filler10+filler10);
				if (!dlgDivision.m_Division2.IsEmpty()) arrayDivision.Add(dlgDivision.m_Division2+filler10+filler10+filler10);
				if (!dlgDivision.m_Division3.IsEmpty()) arrayDivision.Add(dlgDivision.m_Division3+filler10+filler10+filler10);
				if (!dlgDivision.m_Division4.IsEmpty()) arrayDivision.Add(dlgDivision.m_Division4+filler10+filler10+filler10);
				if (!dlgDivision.m_Division5.IsEmpty()) arrayDivision.Add(dlgDivision.m_Division5+filler10+filler10+filler10);
				if (!dlgDivision.m_Division6.IsEmpty()) arrayDivision.Add(dlgDivision.m_Division6+filler10+filler10+filler10);
				if (!arrayDivision.GetSize()) arrayDivision.Add("NULL"+filler10+filler10+filler10);
				divisionnumber = arrayDivision.GetSize();

				myFile.Write(&divisionnumber,sizeof(divisionnumber));
				myFile.Write(conferencename,30);
				for (j=0; j<arrayDivision.GetSize(); j++)
				{
					divisionname = arrayDivision[j];
					dlgTeams.m_Division0 = divisionname.Left(30);
					teamsnumber = 0;
					dlgTeams.m_arrayTeams.RemoveAll();
					arrayFileNames.RemoveAll();

					count = 0;

					bWorking = myFileFind.FindFile("data\\TB*.dat",0);
					if (bWorking)
					{
						while (bWorking)
						{
							bWorking = myFileFind.FindNextFile();
							arrayFileNames.Add(myFileFind.GetFileName());
						}
						myFileFind.Close();

						// Since the FindNextFile does not return the files in any order
						// we must sort the file names
						sortflag = 1;
						while (sortflag)
						{
							sortflag = 0;
							for (ii=0; ii<(arrayFileNames.GetSize()-1);ii++)
							{
								if (arrayFileNames[ii].Compare(arrayFileNames[ii+1]) == 1)
								{
									strTemp = arrayFileNames[ii];
									arrayFileNames[ii] = arrayFileNames[ii+1];
									arrayFileNames[ii+1] = strTemp;
									sortflag = 1;
								}
							}
						}

						for (ii=0; ii<arrayFileNames.GetSize(); ii++)
						{
							myInFile.Open("data\\"+arrayFileNames[ii],CFile::modeRead);
							myInFile.Read(&count,sizeof(count));
							myInFile.Read(temp,40);
							myInFile.Close();
							temp[40] = NULL;
							strTeamName = temp;
							strTeamName = strTeamName+"\t"+arrayFileNames[ii];
							dlgTeams.m_arrayTeams.Add(strTeamName);
						}
						if (dlgTeams.DoModal() == IDOK)
						{
							teamsnumber = dlgTeams.m_arrayTeams.GetSize();

							myFile.Write(&teamsnumber,sizeof(teamsnumber));
							myFile.Write(divisionname,30);
							for (k=0; k<dlgTeams.m_arrayTeams.GetSize(); k++)
							{
								teamname = dlgTeams.m_arrayTeams[k];
								myFile.Write(teamname.Left(40),40);
								myFile.Write(teamname.Right(12),8);
								// Add 3 characters to identify team
								myFile.Write("   ",3);
								// Add 20 characters to identify Ballpark
								myFile.Write("                    ",20);
								// Home game wins and losses
								myFile.Write(&winloss,sizeof(winloss));	// Wins
								myFile.Write(&winloss,sizeof(winloss)); // Loss
								// Away game wins and losses
								myFile.Write(&winloss,sizeof(winloss));	// Wins
								myFile.Write(&winloss,sizeof(winloss)); // Loss
								// Build team files with zeroed out fields in league dir
								structBatter.CopyBatterFile("data\\"+teamname.Right(12),strLeagueDir+"\\"+teamname.Right(12));
								structPitcher.CopyPitcherFile("data\\TP"+teamname.Right(10),strLeagueDir+"\\TP"+teamname.Right(10));
							}
						}		// End - dlgTeams.DoModal()
						else
						{
							myFileCancel = TRUE;
							break;
						}
					}		// End - (bWorking)
					else
					{
						// No teams found so display message
						AfxMessageBox("Could not find any Team files. Please create a team",
							MB_OK|MB_ICONEXCLAMATION);
						myFileCancel = TRUE;
						break;
					}		// End - (bWorking) else
				}		//End - for (j=0; j<arrayDivision.GetSize(); j++)
			}		// End - dlgDivision.DoModal()
			else
			{
				myFileCancel = TRUE;
				break;
			}
			if (myFileCancel)
				break;
		}		//End - for (i=0; i<arrayConference.GetSize(); i++)

		if (myFileCancel)
		{
			// remove the directory due to cancel being pressed
			if (_rmdir(strLeagueDir))
			{
				// Check to see if error was due to non empty dir
				if ( errno  == ENOTEMPTY)
				{
					bWorking = myFileFind.FindFile(strLeagueDir+"\\*.*",0);
					if (bWorking)
					{
						while (bWorking)
						{
							bWorking = myFileFind.FindNextFile();
							if (myFileFind.IsDots())
								continue;
							myTempFile.Remove(myFileFind.GetFilePath());
						}
						myFileFind.Close();
						_rmdir(strLeagueDir);
					}
				}
			}
			// Delete the leage filename due to cancel
			myFile.Close();
			myFile.Remove(strFileName);
		}
		else
		{
			if (!myFile.GetStatus(myFileStatus))
				myFile.Close();
		}
	}		//end - dlg.DoModal()
}

void CBaseballDoc::OnLeaguesEditLeague()
{
	// TODO: Add your command handler code here
	DlgEditLeague dlg;
	INT_PTR nRet = -1;

	nRet = dlg.DoModal();

	// Handle the return value from DoModal 
	switch (nRet)
	{
	case -1:
		AfxMessageBox(_T("Dialog box could not be created!"));
		break;
	case IDABORT:
		// Do something 
		AfxMessageBox(_T("Abort pressed!"));
		break;
	case IDOK:
		// Do something 
		AfxMessageBox(_T("OK pressed!"));
		break;
	case IDCANCEL:
		// Do something 
		AfxMessageBox(_T("Cancel pressed!"));
		break;
	default:
		// Do something 
		AfxMessageBox(_T("Default pressed!"));
		break;
	};
}

void CBaseballDoc::OnFileExportLeagueTeams() 
{
	HCURSOR hCursorWait;
	HCURSOR hCursorNormal;

	CString strLeague;
	int leagueID = 0;
	CString strLeagueName;
	CString strLeagueFile;
	CString strLeagueDir;

	leagueID = GetLeagues(TRUE);

	hCursorWait = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	hCursorNormal = SetCursor(hCursorWait);
	ShowCursor(TRUE);
	Export(leagueID);
	ShowCursor(FALSE);
	SetCursor(hCursorNormal);
}

void CBaseballDoc::OnFileExportLeagueTeamsAll() 
{
	HCURSOR hCursorWait;
	HCURSOR hCursorNormal;

	int leagueID = 0;
	int teamID = 0;
	char *sqlTeam;
	int rc = 0;
	int rcSqlStep = 0;
	CHAR buffer[100];
	sqlite3_stmt *localStmt;

	hCursorWait = AfxGetApp()->LoadStandardCursor(IDC_WAIT);

	hCursorNormal = SetCursor(hCursorWait);
	ShowCursor(TRUE);

	leagueID = GetLeagues(TRUE);

	/* Create SQL statement */
	sqlTeam = "SELECT "  \
		"TeamID" \
		" FROM TEAM " \
		" WHERE LeagueID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlTeam, strlen(sqlTeam), &localStmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for TEAM Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmt, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rcSqlStep = sqlite3_step(localStmt);
	while (rcSqlStep == SQLITE_ROW)
	{
		teamID = sqlite3_column_int(localStmt, 0);
		ExportFile(teamID);
		// Get next Team
		rcSqlStep = sqlite3_step(localStmt);
	}

	sqlite3_finalize(localStmt);
	
	ShowCursor(FALSE);
	SetCursor(hCursorNormal);
}

void CBaseballDoc::Export(int leagueID)
{
	int teamID = 0;

	teamID = GetTeams(leagueID);

	ExportFile(teamID);
}

void CBaseballDoc::ExportFile(int teamID)
{
	CFile exportBatter;
	CFile exportPitcher;
	CString exportFileName;
	char exportData[200];
	CString strexportData;
	char Bunting[5] = {'A','B','C','D','E'};
	char HitRun[4] = {'A','B','C','D'};
//	char Stealing[7] = {'3','2','A','B','C','D','E'};
	CStringA Stealing[7] = { "AAA", "AA", "A", "B", "C", "D", "E" };
	char BatterHits[3] = { 'L', 'R', 'S' };
	char Power[2] = {'N','W'};
	int Running[15] = {5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int TRate[21] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int Pass[21] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int OutArm[12] = {-6,-5,-4,-3,-2,-1,0,1,2,3,4,5};
	int CatchArm[10] = {-4,-3,-2,-1,0,1,2,3,4,5};
	int PHold[16] = {9,8,7,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6};
	m_TeamRecord teamRecord;
	m_LeagueRecord leagueRecord;
	m_ConferenceRecord conferenceRecord;
	m_DivisionRecord divisionRecord;
	m_BatterStatsRecord batterStatsRecord;
	m_BatterRecord batterRecord;
	m_PitcherStatsRecord pitcherStatsRecord;
	m_PitcherRecord pitcherRecord;

	sqlite3_stmt *localStmt;
	char *sqlBatterStats;
	char *sqlPitcherStats;
	int rc;
	int rcSqlStep = 0;
	CHAR buffer[100];
	int batterStatsID = 0;
	int pitcherStatsID = 0;

	teamRecord = GetTeam(teamID);
	leagueRecord = GetLeague(teamRecord.LeagueID);
	conferenceRecord = GetConference(teamRecord.ConferenceID);
	divisionRecord = GetDivision(teamRecord.DivisionID);

	// Division of 1 and or Conference of 1 are pointers to DEFAULT
	if (teamRecord.DivisionID == 1)
	{
		if (teamRecord.ConferenceID == 1)
		{
			// Create file name only with League name
			exportFileName = CStringA(m_dir) + leagueRecord.LeagueName + 
				_T(" ") + _T("Batter") + 
				_T(" ") + teamRecord.TeamName + _T(".csv");
		}
		else
		{
			// Create file name with League name and Conference name
			exportFileName = CStringA(m_dir) + leagueRecord.LeagueName + 
				_T(" ") + conferenceRecord.ConferenceName +
				_T(" ") + _T("Batter") + 
				_T(" ") + teamRecord.TeamName + _T(".csv");
		}
	}
	else
	{
		if (teamRecord.ConferenceID == 1)
		{
			// Create file name with League name and Division name
			exportFileName = CStringA(m_dir) + leagueRecord.LeagueName + 
				_T(" ") + divisionRecord.DivisionName +
				_T(" ") + _T("Batter") + 
				_T(" ") + teamRecord.TeamName + _T(".csv");
		}
		else
		{
			// Create file name with League name, Conference name, and Division name
			exportFileName = CStringA(m_dir) + leagueRecord.LeagueName + 
				_T(" ") + conferenceRecord.ConferenceName +
				_T(" ") + divisionRecord.DivisionName + 
				_T(" ") + _T("Batter") + 
				_T(" ") + teamRecord.TeamName + _T(".csv");
		}
	}

	// Process Batter file
	//strTemp = "XB" + strTeamName.Left(20);
	//exportFileName = CStringA(m_dir) + _T("XB") + teamRecord.TeamName + _T(".csv"); // XBTeamName.csv
	//myFileName = strDir+"\\TB"+strTeamName.Right(10);
	exportBatter.Open(exportFileName,CFile::modeCreate | CFile::modeWrite);
	sprintf_s(exportData,_T("Team Name,LastName,FirstName,AB,Runs,Hits,RBI,2B,3B,HR,W,K,RE,"));
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("SF,SB,CS,Bunting,Stealing,Running,Hit Run,LRS,P,C,"));
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("1B,2B,SS,3B,LF,CF,RF,ChB,ChL,ChR,"));
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("AVG,SLG,OBP,Games,HBP,"));
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("Ch1B,Ch2B,Ch3B,ChHR,ChW,ChDP,"));
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("Ch1BL,Ch2BL,Ch3BL,ChHRL,ChWL,ChDPL,"));
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("Ch1BR,Ch2BR,Ch3BR,ChHRR,ChWR,ChDPR,"));
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("ER1,ER2,ER3,ER4,ER5,ER6,ER7,ER8,ER9,"));
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("T Rating,Passball,Power Left,Power Right,Outfield Arm,Catcher Arm\n"));
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());

	// A Team was selected so export all of the players

	/* Create SQL statement */
	sqlBatterStats = "SELECT "  \
		"BatterStatsID " \
		" from BATTERSTATS "
		" WHERE TeamID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlBatterStats, strlen(sqlBatterStats), &localStmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmt, 1, teamID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rcSqlStep = sqlite3_step(localStmt);
	while (rcSqlStep == SQLITE_ROW)
	{
		// Get ID of batter
		batterStatsID = sqlite3_column_int(localStmt, 0);

		// Read in the player Data
		batterStatsRecord = GetBatterStats(batterStatsID);
		batterRecord = GetBatter(batterStatsRecord.BatterID);

		// Process batters
		sprintf_s(exportData, "%s,%s,%s,",
			teamRecord.TeamName,
			batterRecord.LastName,
			batterRecord.FirstName);
		strexportData = exportData;
		exportBatter.Write(strexportData, strexportData.GetLength());
		sprintf_s(exportData, "%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,",
			batterStatsRecord.AB,
			batterStatsRecord.Runs,
			batterStatsRecord.Hits,
			batterStatsRecord.RBI,
			batterStatsRecord.Doubles,
			batterStatsRecord.Triples,
			batterStatsRecord.HomeRuns,
			batterStatsRecord.Walk,
			batterStatsRecord.Stirkeout,
			batterStatsRecord.ReachedOnError);
		strexportData = exportData;
		exportBatter.Write(strexportData, strexportData.GetLength());
		sprintf_s(exportData, "%i,%i,%i,%c,%s,%i,%c,%c,%i,%i,",
			batterStatsRecord.Sacrifice,
			batterStatsRecord.StolenBase,
			batterStatsRecord.CS,
			Bunting[batterRecord.Bunting],
			Stealing[batterRecord.Stealing],
			Running[batterRecord.Running],
			HitRun[batterRecord.HitRun],
			BatterHits[batterRecord.BatterHits],
			batterRecord.Pitcher,
			batterRecord.Catcher);
		strexportData = exportData;
		exportBatter.Write(strexportData, strexportData.GetLength());
		sprintf_s(exportData, "%i,%i,%i,%i,%i,%i,%i,%2.2f,%2.2f,%2.2f,",
			batterRecord.FirstBase,
			batterRecord.SecondBase,
			batterRecord.ShortStop,
			batterRecord.ThirdBase,
			batterRecord.LeftField,
			batterRecord.CenterField,
			batterRecord.RightField,
			batterRecord.OBChanceBasic,
			batterRecord.OBChanceLeft,
			batterRecord.OBChanceRight);
		strexportData = exportData;
		exportBatter.Write(strexportData, strexportData.GetLength());
		sprintf_s(exportData, "%1.3f,%1.3f,%1.3f,",
			batterStatsRecord.AVG,
			batterStatsRecord.SLG,
			batterStatsRecord.OBP);
		strexportData = exportData;
		exportBatter.Write(strexportData, strexportData.GetLength());
		sprintf_s(exportData, "%i,%i,",
			batterStatsRecord.Games,
			batterStatsRecord.HBP);
		strexportData = exportData;
		exportBatter.Write(strexportData, strexportData.GetLength());
		sprintf_s(exportData, "%2.2f,%2.2f,%2.2f,%2.2f,%2.2f,%2.2f,",
			batterRecord.OBChanceSingle,
			batterRecord.OBChanceDouble,
			batterRecord.OBChanceTriple,
			batterRecord.OBChanceHomeRun,
			batterRecord.OBChanceWalk,
			batterRecord.ChanceDoublePlay);
		strexportData = exportData;
		exportBatter.Write(strexportData, strexportData.GetLength());
		sprintf_s(exportData, "%2.2f,%2.2f,%2.2f,%2.2f,%2.2f,%2.2f,",
			batterRecord.OBChanceSingleLeft,
			batterRecord.OBChanceDoubleLeft,
			batterRecord.OBChanceTripleLeft,
			batterRecord.OBChanceHomeRunLeft,
			batterRecord.OBChanceWalkLeft,
			batterRecord.ChanceDoublePlayLeft);
		strexportData = exportData;
		exportBatter.Write(strexportData, strexportData.GetLength());
		sprintf_s(exportData, "%2.2f,%2.2f,%2.2f,%2.2f,%2.2f,%2.2f,",
			batterRecord.OBChanceSingleRight,
			batterRecord.OBChanceDoubleRight,
			batterRecord.OBChanceTripleRight,
			batterRecord.OBChanceHomeRunRight,
			batterRecord.OBChanceWalkRight,
			batterRecord.ChanceDoublePlayRight);
		strexportData = exportData;
		exportBatter.Write(strexportData, strexportData.GetLength());
		sprintf_s(exportData, "%i,%i,%i,%i,%i,%i,%i,%i,%i,",
			batterRecord.ER1,
			batterRecord.ER2,
			batterRecord.ER3,
			batterRecord.ER4,
			batterRecord.ER5,
			batterRecord.ER6,
			batterRecord.ER7,
			batterRecord.ER8,
			batterRecord.ER9);
		strexportData = exportData;
		exportBatter.Write(strexportData, strexportData.GetLength());
		sprintf_s(exportData, "%i,%i,%c,%c,%i,%i\n",
			TRate[batterRecord.TRate],
			Pass[batterRecord.Pass],
			Power[batterRecord.PowerLeft],
			Power[batterRecord.PowerRight],
			OutArm[batterRecord.OutArm],
			CatchArm[batterRecord.CatchArm]);
		strexportData = exportData;
		exportBatter.Write(strexportData, strexportData.GetLength());

		// Get next Batter
		rcSqlStep = sqlite3_step(localStmt);
	}
	sqlite3_finalize(localStmt);

	// Division of 1 and or Conference of 1 are pointers to DEFAULT
	if (teamRecord.DivisionID == 1)
	{
		if (teamRecord.ConferenceID == 1)
		{
			// Create file name only with League name
			exportFileName = CStringA(m_dir) + leagueRecord.LeagueName +
				_T(" ") + _T("Pitcher") + 
				_T(" ") + teamRecord.TeamName + _T(".csv");
		}
		else
		{
			// Create file name with League name and Conference name
			exportFileName = CStringA(m_dir) + leagueRecord.LeagueName + 
				_T(" ") + conferenceRecord.ConferenceName +
				_T(" ") + _T("Pitcher") + 
				_T(" ") + teamRecord.TeamName + _T(".csv");
		}
	}
	else
	{
		if (teamRecord.ConferenceID == 1)
		{
			// Create file name with League name and Division name
			exportFileName = CStringA(m_dir) + leagueRecord.LeagueName + 
				_T(" ") + divisionRecord.DivisionName +
				_T(" ") + _T("Pitcher") + 
				_T(" ") + teamRecord.TeamName + _T(".csv");
		}
		else
		{
			// Create file name with League name, Conference name, and Division name
			exportFileName = CStringA(m_dir) + leagueRecord.LeagueName + 
				_T(" ") + conferenceRecord.ConferenceName +
				_T(" ") + divisionRecord.DivisionName +
				_T(" ") + _T("Pitcher") + 
				_T(" ") + teamRecord.TeamName + _T(".csv");
		}
	}

	// Process Pitcher file
	//strTemp = "XP" + strTeamName.Left(20);
	//exportFileName = strDir+"\\" + strTemp+".txt"; // dir\XB000001.txt
	//exportFileName = CStringA(m_dir) + _T("XP") + teamRecord.TeamName + _T(".csv"); // XPTeamName.csv
	//myFileName = strDir+"\\TP"+strTeamName.Right(10);
	exportPitcher.Open(exportFileName,CFile::modeCreate | CFile::modeWrite);
	sprintf_s(exportData,_T("Team Name,LastName,FirstName,IP,ER,Hits,Walks,Strikeouts,"));
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("Homeruns,Hold,Wins,Loss,Saves,Starter,Relief,Throws,"));
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("ChB,ChL,ChR,"));
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("ERA,WHIP,"));
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("Starts,"));
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("Games,Completed Games,"));
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("Ch1B,Ch2B,Ch3B,ChHR,ChW,ChDP,"));
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("Ch1BL,Ch2BL,Ch3BL,ChHRL,ChWL,ChDPL,"));
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("Ch1BR,Ch2BR,Ch3BR,ChHRR,ChWR,ChDPR,"));
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,_T("Wild Pitch,Balk,Fielding,ErrorRating,Bunting\n"));
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());

	// A Team was selected so export all of the players

	/* Create SQL statement */
	sqlPitcherStats = "SELECT "  \
		"PitcherStatsID " \
		" from PITCHERSTATS "
		" WHERE TeamID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlPitcherStats, strlen(sqlPitcherStats), &localStmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmt, 1, teamID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rcSqlStep = sqlite3_step(localStmt);
	while (rcSqlStep == SQLITE_ROW)
	{
		// Get ID of pitcher
		pitcherStatsID = sqlite3_column_int(localStmt, 0);

		// Read in the player Data
		pitcherStatsRecord = GetPitcherStats(pitcherStatsID);
		pitcherRecord = GetPitcher(pitcherStatsRecord.PitcherID);

		// Process pitchers
		sprintf_s(exportData,"%s,%s,%s,",
			teamRecord.TeamName,
			pitcherRecord.LastName,
			pitcherRecord.FirstName);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%3.2f,%i,%i,%i,%i,%i,%i,%i,%i,",
			pitcherStatsRecord.InningsPitched,
			pitcherStatsRecord.ER,
			pitcherStatsRecord.Hits,
			pitcherStatsRecord.Walks,
			pitcherStatsRecord.Strikeouts,
			pitcherStatsRecord.HomeRuns,
			PHold[pitcherRecord.Hold],
			pitcherStatsRecord.Wins,
			pitcherStatsRecord.Loss);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,%i,%i,%c,%2.2f,%2.2f,%2.2f,",
			pitcherStatsRecord.Saves,
			pitcherRecord.Starter,
			pitcherRecord.Relief,
			BatterHits[pitcherRecord.Throws],
			pitcherRecord.OBChanceBasic,
			pitcherRecord.OBChanceLeft,
			pitcherRecord.OBChanceRight);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%1.2f,%1.2f,",
			pitcherStatsRecord.ERA,
			pitcherStatsRecord.WHIP);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,",
			pitcherStatsRecord.Starts);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,%i,",
			pitcherStatsRecord.Games, 
			pitcherStatsRecord.CompleteGames);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%2.2f,%2.2f,%2.2f,%2.2f,%2.2f,%2.2f,",
			pitcherRecord.OBChanceSingle,
			pitcherRecord.OBChanceDouble,
			pitcherRecord.OBChanceTriple,
			pitcherRecord.OBChanceHomeRun,
			pitcherRecord.OBChanceWalk,
			pitcherRecord.ChanceDoublePlay);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%2.2f,%2.2f,%2.2f,%2.2f,%2.2f,%2.2f,",
			pitcherRecord.OBChanceSingleLeft,
			pitcherRecord.OBChanceDoubleLeft,
			pitcherRecord.OBChanceTripleLeft,
			pitcherRecord.OBChanceHomeRunLeft,
			pitcherRecord.OBChanceWalkLeft,
			pitcherRecord.ChanceDoublePlayLeft);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%2.2f,%2.2f,%2.2f,%2.2f,%2.2f,%2.2f,",
			pitcherRecord.OBChanceSingleRight,
			pitcherRecord.OBChanceDoubleRight,
			pitcherRecord.OBChanceTripleRight,
			pitcherRecord.OBChanceHomeRunRight,
			pitcherRecord.OBChanceWalkRight,
			pitcherRecord.ChanceDoublePlayRight);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,%i,%i,%i,%c\n",
			pitcherRecord.WP,
			pitcherRecord.Balk,
			pitcherRecord.Pitcher,
			pitcherRecord.ER1,
			Bunting[pitcherRecord.Bunting]);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());

		// Get next Pitcher
		rcSqlStep = sqlite3_step(localStmt);
	}
	sqlite3_finalize(localStmt);
}

void CBaseballDoc::OnFileExportHTMLLeagueTeams() 
{
	int leagueID = 0;

	leagueID = GetLeagues(TRUE);

	ExportHTML(leagueID);
}

void CBaseballDoc::OnFileExportHtmlLeagueTeamsAll() 
{
	HCURSOR hCursorWait;
	HCURSOR hCursorNormal;

	int leagueID = 0;
	int teamID = 0;
	char *sqlTeam;
	int rc = 0;
	int rcSqlStep = 0;
	CHAR buffer[100];
	sqlite3_stmt *localStmt;

	hCursorWait = AfxGetApp()->LoadStandardCursor(IDC_WAIT);

	hCursorNormal = SetCursor(hCursorWait);
	ShowCursor(TRUE);

	leagueID = GetLeagues(TRUE);

	/* Create SQL statement */
	sqlTeam = "SELECT "  \
		"TeamID" \
		" FROM TEAM " \
		" WHERE LeagueID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlTeam, strlen(sqlTeam), &localStmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for TEAM Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmt, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rcSqlStep = sqlite3_step(localStmt);
	while (rcSqlStep == SQLITE_ROW)
	{
		teamID = sqlite3_column_int(localStmt, 0);
		ExportHTMLFile(teamID);
		// Get next Team
		rcSqlStep = sqlite3_step(localStmt);
	}

	sqlite3_finalize(localStmt);

	ShowCursor(FALSE);
	SetCursor(hCursorNormal);
}

void CBaseballDoc::ExportHTML(int leagueID)
{
	int teamID = 0;

	teamID = GetTeams(leagueID);

	ExportHTMLFile(teamID);
}

void CBaseballDoc::ExportHTMLFile(int teamID)
{
	char HTMLData[200];
	CString HTMLFileName;
	CString strHTMLData;
	CFile HTMLPlayer;
	char datebuf[9],timebuf[9];
	CString strIndex;
	CString strBackgroundPicture;
	CString strLinkColor;
	CString strVLinkColor;
	CString strBGColor;
	CString strTextColor;
	m_TeamRecord teamRecord;
	m_LeagueRecord leagueRecord;
	m_ConferenceRecord conferenceRecord;
	m_DivisionRecord divisionRecord;
	m_BatterStatsRecord batterStatsRecord;
	m_BatterRecord batterRecord;
	m_PitcherStatsRecord pitcherStatsRecord;
	m_PitcherRecord pitcherRecord;

	//Registry myReg(strDir + REGTEAMS);

	//strLinkColor	= myReg.GetRegistryOptionLinkColor();
	//strVLinkColor	= myReg.GetRegistryOptionVLinkColor();
	//strBGColor		= myReg.GetRegistryOptionBGColor();
	//strTextColor	= myReg.GetRegistryOptionTextColor();
	//strIndex		= myReg.GetRegistryOptionIndex();
	//strBackgroundPicture = myReg.GetRegistryOptionBackgroundPicture();
	strLinkColor	= "Blue";
	strVLinkColor	= "Purple";
	strBGColor = "White";
	strTextColor = "Black";
	strIndex = "index.htm";
	strBackgroundPicture = "images/background.jpg";

	sqlite3_stmt *localStmt;
	char *sqlBatterStats;
	char *sqlPitcherStats;
	int rc;
	int rcSqlStep = 0;
	CHAR buffer[100];
	int batterStatsID = 0;
	int pitcherStatsID = 0;

	teamRecord = GetTeam(teamID);
	leagueRecord = GetLeague(teamRecord.LeagueID);
	conferenceRecord = GetConference(teamRecord.ConferenceID);
	divisionRecord = GetDivision(teamRecord.DivisionID);

	// Division of 1 and or Conference of 1 are pointers to DEFAULT
	if (teamRecord.DivisionID == 1)
	{
		if (teamRecord.ConferenceID == 1)
		{
			// Create file name only with League name
			HTMLFileName = CStringA(m_dir) + leagueRecord.LeagueName +
				_T(" ") + teamRecord.TeamName + _T(".htm");
		}
		else
		{
			// Create file name with League name and Conference name
			HTMLFileName = CStringA(m_dir) + leagueRecord.LeagueName +
				_T(" ") + conferenceRecord.ConferenceName +
				_T(" ") + teamRecord.TeamName + _T(".htm");
		}
	}
	else
	{
		if (teamRecord.ConferenceID == 1)
		{
			// Create file name with League name and Division name
			HTMLFileName = CStringA(m_dir) + leagueRecord.LeagueName +
				_T(" ") + divisionRecord.DivisionName +
				_T(" ") + teamRecord.TeamName + _T(".htm");
		}
		else
		{
			// Create file name with League name, Conference name, and Division name
			HTMLFileName = CStringA(m_dir) + leagueRecord.LeagueName +
				_T(" ") + conferenceRecord.ConferenceName +
				_T(" ") + divisionRecord.DivisionName +
				_T(" ") + teamRecord.TeamName + _T(".htm");
		}
	}

	// Process Batter file
	//HTMLFileName = CStringA(m_dir) + teamRecord.TeamName + _T(".htm"); // dir\TeamName.htm

	HTMLPlayer.Open(HTMLFileName,CFile::modeCreate | CFile::modeWrite);
	sprintf_s(HTMLData,"<HTML>\n<HEAD>\n<TITLE>%s</TITLE>\n</HEAD>\n",
		teamRecord.TeamName);
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<BODY TEXT=%s LINK=%s VLINK=%s BGCOLOR=%s BACKGROUND=\"%s\">\n",
		strTextColor,strLinkColor,strVLinkColor,strBGColor,strBackgroundPicture);
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData, "<H2>%s</H2>\n", teamRecord.TeamName);
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<A href=\"%s\">Back</A><BR><BR>\n",strIndex);
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TABLE BORDER>\n<TR>\n");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData, "<TD ALIGN = LEFT><B>Batter Name</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData, strHTMLData.GetLength());
	sprintf_s(HTMLData, "<TD ALIGN = CENTER><B>AB</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>R</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>H</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>RBI</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>2B</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>3B</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>HR</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>W</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>K</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>RE</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>CS</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>SB</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>AVG</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>SLG</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>OB%%</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"</TR>\n");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	// Insert table below here

	// A Team was selected so export all of the players

	/* Create SQL statement */
	sqlBatterStats = "SELECT "  \
		"BatterStatsID " \
		" from BATTERSTATS "
		" WHERE TeamID = ?1 " \
		" ORDER BY AVG DESC, AB DESC ";

	rc = sqlite3_prepare_v2(m_db, sqlBatterStats, strlen(sqlBatterStats), &localStmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmt, 1, teamID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rcSqlStep = sqlite3_step(localStmt);
	while (rcSqlStep == SQLITE_ROW)
	{
		// Get ID of batter
		batterStatsID = sqlite3_column_int(localStmt, 0);

		// Read in the player Data
		batterStatsRecord = GetBatterStats(batterStatsID);
		batterRecord = GetBatter(batterStatsRecord.BatterID);

		sprintf_s(HTMLData,"<TR>");
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%s, %s</TD>",
			batterRecord.LastName, batterRecord.FirstName);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData, "<TD>%i</TD>",
			batterStatsRecord.AB);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			batterStatsRecord.Runs);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			batterStatsRecord.Hits);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			batterStatsRecord.RBI);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			batterStatsRecord.Doubles);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			batterStatsRecord.Triples);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			batterStatsRecord.HomeRuns);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			batterStatsRecord.Walk);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			batterStatsRecord.Stirkeout);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			batterStatsRecord.ReachedOnError);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD><TD>%i</TD>",
			batterStatsRecord.CS,
			batterStatsRecord.StolenBase);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%1.3f</TD>",
			batterStatsRecord.AVG);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%1.3f</TD>",
			batterStatsRecord.SLG);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%1.3f</TD>",
			batterStatsRecord.OBP);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"</TR>\n");
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());

		// Get next Batter
		rcSqlStep = sqlite3_step(localStmt);
	}
	sprintf_s(HTMLData,"</TABLE>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<BR><BR><TABLE BORDER>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sqlite3_finalize(localStmt);

	// Process Pitcher file
	sprintf_s(HTMLData,"<TR>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TR><TD ALIGN = LEFT><B>Pitcher Name</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>IP</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>ER</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>H</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>W</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>K</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>HR</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>Start</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>Win</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>Loss</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>Saves</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>ERA</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>WHIP</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"</TR>\n");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());

	// A Team was selected so export a players

	/* Create SQL statement */
	sqlPitcherStats = "SELECT "  \
		"PitcherStatsID " \
		" from PITCHERSTATS "
		" WHERE TeamID = ?1 " \
		" ORDER BY ERA ASC, InningsPitched DESC ";

	rc = sqlite3_prepare_v2(m_db, sqlPitcherStats, strlen(sqlPitcherStats), &localStmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmt, 1, teamID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rcSqlStep = sqlite3_step(localStmt);
	while (rcSqlStep == SQLITE_ROW)
	{
		// Get ID of pitcher
		pitcherStatsID = sqlite3_column_int(localStmt, 0);

		// Read in the player Data
		pitcherStatsRecord = GetPitcherStats(pitcherStatsID);
		pitcherRecord = GetPitcher(pitcherStatsRecord.PitcherID);

		// Process pitchers
		sprintf_s(HTMLData,"<TR><TD>%s, %s</TD>",
			pitcherRecord.LastName, pitcherRecord.FirstName);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%1.2f</TD>",
			pitcherStatsRecord.InningsPitched);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			pitcherStatsRecord.ER);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			pitcherStatsRecord.Hits);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			pitcherStatsRecord.Walks);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			pitcherStatsRecord.Strikeouts);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			pitcherStatsRecord.HomeRuns);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			pitcherStatsRecord.Starts);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			pitcherStatsRecord.Wins);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			pitcherStatsRecord.Loss);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			pitcherStatsRecord.Saves);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%1.2f</TD>",
			pitcherStatsRecord.ERA);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%1.2f</TD>",
			pitcherStatsRecord.WHIP);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"</TR>\n");
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());

		// Get next Pitcher
		rcSqlStep = sqlite3_step(localStmt);
	}
	// Insert table above here

	sprintf_s(HTMLData,"</TABLE>\n");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
    _strtime_s( timebuf );    
    _strdate_s( datebuf );    
	sprintf_s(HTMLData,"<BR>Last Updated on %s at %s<BR>\n",datebuf,timebuf);
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	// End of HTML file
	sprintf_s(HTMLData,"</BODY>\n</HTML>\n");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	HTMLPlayer.Close();

	sqlite3_finalize(localStmt);
}

void CBaseballDoc::OnTeamsEditLeagueTeams() 
{
	// TODO: Add your command handler code here
	int leagueID = 0;

	leagueID = GetLeagues(TRUE);

	EditTeams(leagueID);
}

void CBaseballDoc::EditTeams(int leagueID)
{
	EditTeam dlg;
	int teamID = 0;
	CString strTeamName;
	CString strShortTeamName;
	CString strBallPark;
	m_TeamRecord teamResult;
	m_TeamRecord teamUpdate;

	teamID = GetTeams(leagueID);
	teamResult = GetTeam(teamID);

	strTeamName = teamResult.TeamName;

	dlg.m_TeamName = teamResult.TeamName;
	dlg.m_ShortTeamName = teamResult.TeamNameShort;
	dlg.m_BallPark = teamResult.BallparkName;
	if (dlg.DoModal() == IDOK)
	{
		// Update the Database with team name, Short name, and Ballpark
		// That is all that is setup
		// TeamUpdate(...);
		teamUpdate.TeamID = teamResult.TeamID;
		teamUpdate.TeamName = dlg.m_TeamName;
		teamUpdate.TeamNameShort = dlg.m_ShortTeamName;
		teamUpdate.BallparkName = dlg.m_BallPark;
		teamUpdate.HomeWins = teamResult.HomeWins;
		teamUpdate.HomeLosses = teamResult.HomeLosses;
		teamUpdate.AwayWins = teamResult.AwayWins;
		teamUpdate.AwayLosses = teamResult.AwayLosses;
		teamUpdate.LeagueID = teamResult.LeagueID;
		teamUpdate.ConferenceID = teamResult.ConferenceID;
		teamUpdate.DivisionID = teamResult.DivisionID;
		teamUpdate.TeamYear = teamResult.TeamYear;
		teamUpdate.BaseTeam = teamResult.BaseTeam;

		TeamUpdate(teamUpdate);
	}
}

void CBaseballDoc::OnStatisticsHTMLLeagueStats() 
{
	int leagueID = 0;

	leagueID = GetLeagues(FALSE);

	HTMLLeagueStats(leagueID);
}

void CBaseballDoc::HTMLLeagueStats(int leagueID)
{
	m_LeagueRecord leagueRecord;
	m_ConferenceRecord conferenceRecord;
	m_DivisionRecord divisionRecord;
	int rcSqlStepConf = 0;
	int rcSqlStepDiv = 0;
	int rc = 0;
	CHAR buffer[100];
	CHAR *sqlConference;
	CHAR *sqlDivision;
	sqlite3_stmt *localStmtConf;
	sqlite3_stmt *localStmtDivision;
	int conferenceID = 0;
	int divisionID = 0;

	leagueRecord = GetLeague(leagueID);

	/* Create SQL statement */
	sqlConference = "SELECT "  \
		"ConferenceID " \
		" from CONFERENCES "
		" WHERE LeagueID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlConference, strlen(sqlConference), &localStmtConf, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for CONFERENCES Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtConf, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rcSqlStepConf = sqlite3_step(localStmtConf);
	while (rcSqlStepConf == SQLITE_ROW)
	{
		// Get ID of conference
		conferenceID = sqlite3_column_int(localStmtConf, 0);

		/* Create SQL statement */
		sqlDivision = "SELECT "  \
			"DivisionID " \
			" from DIVISIONS "
			" WHERE LeagueID = ?1 AND ConferenceID = ?2";

		rc = sqlite3_prepare_v2(m_db, sqlDivision, strlen(sqlDivision), &localStmtDivision, 0);
		if (rc != SQLITE_OK)
		{
			sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
			AfxMessageBox(buffer);
		}
		else
		{
			sprintf_s(buffer, sizeof(buffer), "Prepare for CONFERENCES Select OK:\n");
			//AfxMessageBox(buffer);
		}
		// Bind the data to field '1' which is the first '?' in the INSERT statement
		rc = sqlite3_bind_int(localStmtDivision, 1, leagueID);
		if (rc != SQLITE_OK)
		{
			sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
			AfxMessageBox(buffer);
		}
		rc = sqlite3_bind_int(localStmtDivision, 2, conferenceID);
		if (rc != SQLITE_OK)
		{
			sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
			AfxMessageBox(buffer);
		}

		rcSqlStepDiv = sqlite3_step(localStmtDivision);
		if (rcSqlStepDiv == SQLITE_DONE)
		{
			// Process League data with default division
			BuildPlayerArray(leagueID, conferenceID, 1);
		}
		else
		{
			while (rcSqlStepDiv == SQLITE_ROW)
			{
				// Get ID of division
				divisionID = sqlite3_column_int(localStmtDivision, 0);

				// Process League data
				BuildPlayerArray(leagueID, conferenceID, divisionID);

				// Get next Division
				rcSqlStepDiv = sqlite3_step(localStmtDivision);
			}
		}
		sqlite3_finalize(localStmtDivision);

		// Get next Conference
		rcSqlStepConf = sqlite3_step(localStmtConf);
	}
	sqlite3_finalize(localStmtConf);
}

void CBaseballDoc::BuildPlayerArray(int leagueID, int conferenceID, int divisionID)
{
	CFile HTMLFile;
	char HTMLData[200];
	CString strHTMLData;
	CStringArray strArrayHTMLData1;
	CStringArray strArrayHTMLData2;
	CStringArray strArrayHTMLData3;
	char datebuf[9], timebuf[9];
	CString strIndex;
	CString strBackgroundPicture;
	CString strLinkColor;
	CString strVLinkColor;
	CString strBGColor;
	CString strTextColor;

	m_LeagueRecord leagueRecord;
	m_ConferenceRecord conferenceRecord;
	m_DivisionRecord divisionRecord;
	m_TeamRecord teamRecord;
	int rcSqlStepTeam = 0;
	int rc = 0;
	CHAR buffer[100];
	CHAR *sqlTeam;
	CHAR *sqlSelect;
	sqlite3_stmt *localStmtTeam;
	sqlite3_stmt *localStmtSelect;
	int teamID = 0;
	int sumAB = 0;
	int sumRuns = 0;
	int sumHits = 0;
	int sumPHits = 0;
	int sumRBI = 0;
	int sumDouble = 0;
	int sumTriple = 0;
	int sumHomeRun = 0;
	int sumPHomeRun = 0;
	int sumWalk = 0;
	int sumROE = 0;
	int sumSacrifice = 0;
	int sumStollen = 0;
	int sumCS = 0;
	int sumWins = 0;
	int sumLoss = 0;
	float sumInningsPitched = 0.0;
	int sumER = 0;
	int sumWalks = 0;
	int sumStrikeouts = 0;
	int totalWins = 0;
	int totalLoss = 0;
	float totalInningsPitched = 0.0;
	int totalER = 0;
	int totalWalks = 0;
	int totalStrikeouts = 0;

	int totalAB = 0;
	int totalRuns = 0;
	int totalHits = 0;
	int totalPHits = 0;
	int totalRBI = 0;
	int totalDouble = 0;
	int totalTriple = 0;
	int totalHomeRun = 0;
	int totalPHomeRun = 0;
	int totalWalk = 0;
	int totalROE = 0;
	int totalSacrifice = 0;
	int totalStollen = 0;
	int totalCS = 0;
	CString strAVG;
	float fBA;
	float fSLG;
	float fOBP;
	float fERA;
	float fWHIP;
	CString teamNameShort;
	CString firstName;
	CString lastName;
	CString playerName;
	int homeRuns = 0;
	int atBats = 0;
	int runs = 0;
	int hits = 0;
	int rbi = 0;
	float avg;
	float slg;
	float obp;
	int doubles;
	int triples;
	int stolenBase = 0;
	int cs = 0;
	int strikeouts = 0;
	int walks = 0;
	int er = 0;
	float era;
	float ip;
	float whip;
	int wins = 0;
	int loss = 0;
	int starts = 0;
	int saves = 0;

	leagueRecord = GetLeague(leagueID);
	conferenceRecord = GetConference(conferenceID);
	divisionRecord = GetDivision(divisionID);

	strLinkColor = "Blue";
	strVLinkColor = "Purple";
	strBGColor = "White";
	strTextColor = "Black";
	strIndex = "index.htm";
	strBackgroundPicture = "images/background.jpg";

	// Division of 1 and or Conference of 1 are pointers to DEFAULT
	if (divisionID == 1)
	{
		if (conferenceID == 1)
		{
			// Create file name only with League name
			HTMLFile.Open(CStringA(m_dir) + leagueRecord.LeagueName + _T(".htm"), CFile::modeWrite | CFile::modeCreate);
		}
		else
		{
			// Create file name with League name and Conference name
			HTMLFile.Open(CStringA(m_dir) + leagueRecord.LeagueName + _T(" ") + conferenceRecord.ConferenceName + 
				_T(".htm"), CFile::modeWrite | CFile::modeCreate);
		}
	}
	else
	{
		if (conferenceID == 1)
		{
			// Create file name with League name and Division name
			HTMLFile.Open(CStringA(m_dir) + leagueRecord.LeagueName + _T(" ") + divisionRecord.DivisionName + 
				_T(".htm"), CFile::modeWrite | CFile::modeCreate);
		}
		else
		{
			// Create file name with League name, Conference name, and Division name
			HTMLFile.Open(CStringA(m_dir) + leagueRecord.LeagueName + _T(" ") + conferenceRecord.ConferenceName + 
				_T(" ") + divisionRecord.DivisionName + _T(".htm"), CFile::modeWrite | CFile::modeCreate);
		}
	}
	sprintf_s(HTMLData, "<HTML>\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	sprintf_s(HTMLData, "<HEAD>\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	sprintf_s(HTMLData, "<TITLE>%s</TITLE>\n", leagueRecord.LeagueName);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	sprintf_s(HTMLData, "</HEAD>\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	sprintf_s(HTMLData, "<BODY TEXT=%s LINK=%s VLINK=%s BGCOLOR=%s BACKGROUND=\"%s\">\n",
		strTextColor, strLinkColor, strVLinkColor, strBGColor, strBackgroundPicture);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	sprintf_s(HTMLData, "<A href=\"%s\">Back</A><BR><BR>\n", strIndex);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	sprintf_s(HTMLData, "<H2>League: %s</H2>\n", leagueRecord.LeagueName);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	if (conferenceID != 1)
	{
		sprintf_s(HTMLData, "Conference: <B>%s</B><BR>\n", conferenceRecord.ConferenceName);
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	}
	if (divisionID != 1)
	{
		sprintf_s(HTMLData, "Division: <B>%s</B><BR>\n", divisionRecord.DivisionName);
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	}

	sprintf_s(HTMLData, "<PRE><B>\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	sprintf_s(HTMLData, "BATTING\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	sprintf_s(HTMLData, "    TEAM             AVG   SLG   OBP     AB    R     H  RBI   2B   3B  HR   SB   CS\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	/* Create SQL statement */
	sqlTeam = "SELECT "  \
		"T.TeamID, " \
		"sum(B.AB) AS sumAB, " \
		"sum(B.Runs), " \
		"sum(B.Hits) as sumHits, " \
		"sum(B.RBI), " \
		"sum(B.Doubles)," \
		"sum(B.Triples), " \
		"sum(B.HomeRuns), " \
		"sum(B.Walk), " \
		"sum(B.ReachedOnError), " \
		"sum(B.Sacrifice), " \
		"sum(B.StolenBase), " \
		"sum(B.CS) " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as B " \
		"ON T.TeamID = B.TeamID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"GROUP BY T.TeamID " \
		"ORDER BY (CAST(sumAB AS FLOAT) / sumHits) ASC";

	rc = sqlite3_prepare_v2(m_db, sqlTeam, strlen(sqlTeam), &localStmtTeam, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtTeam, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtTeam, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtTeam, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rcSqlStepTeam = sqlite3_step(localStmtTeam);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		// Get ID of team
		teamID = sqlite3_column_int(localStmtTeam, 0);
		sumAB = sqlite3_column_int(localStmtTeam, 1);
		sumRuns = sqlite3_column_int(localStmtTeam, 2);
		sumHits = sqlite3_column_int(localStmtTeam, 3);
		sumRBI = sqlite3_column_int(localStmtTeam, 4);
		sumDouble = sqlite3_column_int(localStmtTeam, 5);
		sumTriple = sqlite3_column_int(localStmtTeam, 6);
		sumHomeRun = sqlite3_column_int(localStmtTeam, 7);
		sumWalk = sqlite3_column_int(localStmtTeam, 8);
		sumROE = sqlite3_column_int(localStmtTeam, 9);
		sumSacrifice = sqlite3_column_int(localStmtTeam, 10);
		sumStollen = sqlite3_column_int(localStmtTeam, 11);
		sumCS = sqlite3_column_int(localStmtTeam, 12);
		totalAB += sumAB;
		totalRuns += sumRuns;
		totalHits += sumHits;
		totalRBI += sumRBI;
		totalDouble += sumDouble;
		totalTriple += sumTriple;
		totalHomeRun += sumHomeRun;
		totalWalk += sumWalk;
		totalROE += sumROE;
		totalSacrifice += sumSacrifice;
		totalStollen += sumStollen;
		totalCS += sumCS;

		fBA = (float)sumHits / sumAB;
		fSLG = (float)((sumHits - (sumDouble + sumTriple + sumHomeRun)) + (2 * sumDouble) + (3 * sumTriple) + (4 * sumHomeRun)) / (sumAB);
		fOBP = (float)(sumHits + sumWalk + sumROE + sumSacrifice + sumStollen) / (sumAB + sumWalk + sumROE + sumSacrifice + sumStollen);

		teamRecord = GetTeam(teamID);

		sprintf_s(HTMLData, "%s %-15.15s %1.3f %1.3f %1.3f %5i %4i %5i %4i %4i %4i %3i %4i %4i\n",
			teamRecord.TeamNameShort, teamRecord.TeamName, fBA, fSLG, fOBP, sumAB, sumRuns, sumHits, sumRBI,
			sumDouble, sumTriple, sumHomeRun, sumStollen, sumCS);
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

		// Get next team
		rcSqlStepTeam = sqlite3_step(localStmtTeam);
	}
	sqlite3_finalize(localStmtTeam);

	sprintf_s(HTMLData, "--- --------------- ----- ----- ----- ----- ---- ----- ---- ---- ---- --- ---- ----\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	fBA = (float)totalHits / totalAB;
	fSLG = (float)((totalHits - (totalDouble + totalTriple + totalHomeRun)) + (2 * totalDouble) + (3 * totalTriple) + (4 * totalHomeRun)) / (totalAB);
	fOBP = (float)(totalHits + totalWalk + totalROE + totalSacrifice + totalStollen) / (totalAB + totalWalk + totalROE + totalSacrifice + totalStollen);
	sprintf_s(HTMLData, "LEAGUE TOTALS       %1.3f %1.3f %1.3f %5i %4i %5i %4i %4i %4i %3i %4i %4i\n",
		fBA, fSLG, fOBP, totalAB, totalRuns, totalHits, totalRBI,
		totalDouble, totalTriple, totalHomeRun, totalStollen, totalCS);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	sprintf_s(HTMLData, "\nPITCHING\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	sprintf_s(HTMLData, "    TEAM             ERA   WHIP  Wins  Loss      IP  Hits   ER  HR Walks    K\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	/* Create SQL statement */
	sqlTeam = "SELECT "  \
		"T.TeamID, " \
		"sum(P.Wins) AS wins, " \
		"sum(P.Loss) AS loss, " \
		"sum(CAST(P.InningsPitched AS FLOAT)) AS sumIP, " \
		"sum(P.ER) AS sumER, " \
		"sum(P.Hits)," \
		"sum(P.HomeRuns), " \
		"sum(P.Walks), " \
		"sum(P.Strikeouts) " \
		"FROM TEAM AS T " \
		"JOIN PITCHERSTATS as P " \
		"ON T.TeamID = P.TeamID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"GROUP BY T.TeamID " \
		"ORDER BY wins DESC, loss ASC";
//	"ORDER BY ((CAST(sumER AS FLOAT) * 9) / CAST(sumIP AS FLOAT)) ASC";

	rc = sqlite3_prepare_v2(m_db, sqlTeam, strlen(sqlTeam), &localStmtTeam, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtTeam, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtTeam, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtTeam, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rcSqlStepTeam = sqlite3_step(localStmtTeam);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		// Get ID of team
		teamID = sqlite3_column_int(localStmtTeam, 0);
		sumWins = sqlite3_column_int(localStmtTeam, 1);
		sumLoss = sqlite3_column_int(localStmtTeam, 2);
		sumInningsPitched = (float)sqlite3_column_double(localStmtTeam, 3);
		sumER = sqlite3_column_int(localStmtTeam, 4);
		sumPHits = sqlite3_column_int(localStmtTeam, 5);
		sumPHomeRun = sqlite3_column_int(localStmtTeam, 6);
		sumWalks = sqlite3_column_int(localStmtTeam, 7);
		sumStrikeouts = sqlite3_column_int(localStmtTeam, 8);
		totalWins += sumWins;
		totalLoss += sumLoss;
		totalInningsPitched += sumInningsPitched;
		totalER += sumER;
		totalPHits += sumPHits;
		totalPHomeRun += sumPHomeRun;
		totalWalks += sumWalks;
		totalStrikeouts += sumStrikeouts;

		fERA = ((float)sumER * 9) / sumInningsPitched;
		fWHIP = (float)((sumPHits + sumWalks) * 9) / sumInningsPitched;

		teamRecord = GetTeam(teamID);

		sprintf_s(HTMLData, "%s %-15.15s %5.2f  %4.1f   %3i   %3i  %6.1f %5i %4i %3i  %4i %4i\n",
			teamRecord.TeamNameShort, teamRecord.TeamName, fERA, fWHIP, sumWins, sumLoss, sumInningsPitched, sumPHits,
			sumER, sumPHomeRun, sumWalks, sumStrikeouts);
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

		// Get next team
		rcSqlStepTeam = sqlite3_step(localStmtTeam);
	}
	sqlite3_finalize(localStmtTeam);

	sprintf_s(HTMLData, "--- --------------- -----  ----  ----  ---- -------  ---- ---- ---   ---  ---\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	fERA = ((float)totalER * 9) / totalInningsPitched;
	fWHIP = (float)((totalHits + totalWalks) * 9) / totalInningsPitched;
	sprintf_s(HTMLData, "LEAGUE TOTALS       %5.2f  %4.1f   %3i   %3i  %6.1f %5i %4i %3i  %4i %4i\n\n",
		fERA, fWHIP, totalWins, totalLoss, totalInningsPitched, totalHits, totalER, totalHomeRun, totalWalks, totalStrikeouts);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.AB " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.AB DESC, BS.AVG DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData1.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		atBats = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i  ",
			teamNameShort, playerName, atBats);
		strArrayHTMLData1.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.Runs " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.Runs DESC, BS.AVG DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData2.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		runs = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i  ",
			teamNameShort, playerName, runs);
		strArrayHTMLData2.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.Hits " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.Hits DESC, BS.AVG DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData3.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		hits = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i\n",
			teamNameShort, playerName, hits);
		strArrayHTMLData3.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	strHTMLData = _T("At Bats                    Runs                       Hits\n");
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	for (int i = 0; i < strArrayHTMLData3.GetSize(); i++)
	{
		strHTMLData = strArrayHTMLData1[i] + strArrayHTMLData2[i] + strArrayHTMLData3[i];
		HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	}

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.RBI " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.RBI DESC, BS.AVG DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData1.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		rbi = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i  ",
			teamNameShort, playerName, rbi);
		strArrayHTMLData1.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.AVG " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.AVG DESC, BS.AB DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData2.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		avg = (float)sqlite3_column_double(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %1.3f  ",
			teamNameShort, playerName, avg);
		strArrayHTMLData2.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.SLG " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.SLG DESC, BS.AVG DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData3.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		slg = (float)sqlite3_column_double(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %1.3f\n",
			teamNameShort, playerName, slg);
		strArrayHTMLData3.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	strHTMLData = _T("\nRBI's                      Batting Averages            Slugging Percentages\n");
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	for (int i = 0; i < strArrayHTMLData3.GetSize(); i++)
	{
		strHTMLData = strArrayHTMLData1[i] + strArrayHTMLData2[i] + strArrayHTMLData3[i];
		HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	}

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.OBP " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.OBP DESC, BS.AVG DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData1.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		obp = (float)sqlite3_column_double(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %1.3f ",
			teamNameShort, playerName, obp);
		strArrayHTMLData1.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.Doubles " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.Doubles DESC, BS.AVG DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData2.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		doubles = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i  ",
			teamNameShort, playerName, doubles);
		strArrayHTMLData2.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.Triples " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.Triples DESC, BS.AVG DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData3.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		triples = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i\n",
			teamNameShort, playerName, triples);
		strArrayHTMLData3.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	strHTMLData = _T("\nOn Base Percentage         Doubles                    Triples\n");
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	for (int i = 0; i < strArrayHTMLData3.GetSize(); i++)
	{
		strHTMLData = strArrayHTMLData1[i] + strArrayHTMLData2[i] + strArrayHTMLData3[i];
		HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	}

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.HomeRuns " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.HomeRuns DESC, BS.AVG DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData1.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		// Get ID of team
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		homeRuns = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i  ",
			teamNameShort, playerName, homeRuns);
		strArrayHTMLData1.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.StolenBase " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.StolenBase DESC, BS.AVG DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData2.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		stolenBase = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i  ",
			teamNameShort, playerName, stolenBase);
		strArrayHTMLData2.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.CS " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.CS DESC, BS.AVG DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData3.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		cs = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i\n",
			teamNameShort, playerName, cs);
		strArrayHTMLData3.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	strHTMLData = _T("\nHome Runs                  Stolen Basses              Caught Stealing\n");
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	for (int i = 0; i < strArrayHTMLData3.GetSize(); i++)
	{
		strHTMLData = strArrayHTMLData1[i] + strArrayHTMLData2[i] + strArrayHTMLData3[i];
		HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	}

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.Stirkeout " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.Stirkeout DESC, BS.AVG DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData1.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		// Get ID of team
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		strikeouts = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i  ",
			teamNameShort, playerName, strikeouts);
		strArrayHTMLData1.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"B.FirstName, " \
		"B.LastName, " \
		"BS.Walk " \
		"FROM TEAM AS T " \
		"JOIN BATTERSTATS as BS " \
		"ON T.TeamID = BS.TeamID " \
		"JOIN BATTER as B " \
		"ON BS.BatterID = B.BatterID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY BS.Walk DESC, BS.AVG DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData2.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		walks = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i\n",
			teamNameShort, playerName, walks);
		strArrayHTMLData2.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	strHTMLData = _T("\nStrike Outs                Walks\n");
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	for (int i = 0; i < strArrayHTMLData3.GetSize(); i++)
	{
		strHTMLData = strArrayHTMLData1[i] + strArrayHTMLData2[i];
		HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	}

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"P.FirstName, " \
		"P.LastName, " \
		"PS.ER " \
		"FROM TEAM AS T " \
		"JOIN PITCHERSTATS as PS " \
		"ON T.TeamID = PS.TeamID " \
		"JOIN PITCHER as P " \
		"ON PS.PitcherID = P.PitcherID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY PS.ER DESC, PS.ERA DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData1.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		er = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i  ",
			teamNameShort, playerName, er);
		strArrayHTMLData1.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	// Limit on InningsPitched set to greater that 4 innings
	// Need better limit. A pitcher can have ERA of 0 but there are 
	// way too many with zero that have not pitched many innings.
	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"P.FirstName, " \
		"P.LastName, " \
		"PS.ERA " \
		"FROM TEAM AS T " \
		"JOIN PITCHERSTATS as PS " \
		"ON T.TeamID = PS.TeamID " \
		"JOIN PITCHER as P " \
		"ON PS.PitcherID = P.PitcherID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 AND PS.InningsPitched > 4 " \
		"ORDER BY PS.ERA ASC, PS.InningsPitched DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData2.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		era = (float)sqlite3_column_double(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %5.2f ",
			teamNameShort, playerName, era);
		strArrayHTMLData2.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);
	if (strArrayHTMLData2.IsEmpty())
		for (int i = 0; i < 10; i++)
			strArrayHTMLData2.Add("All Pitchers have 0 ERA");

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"P.FirstName, " \
		"P.LastName, " \
		"PS.InningsPitched " \
		"FROM TEAM AS T " \
		"JOIN PITCHERSTATS as PS " \
		"ON T.TeamID = PS.TeamID " \
		"JOIN PITCHER as P " \
		"ON PS.PitcherID = P.PitcherID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY PS.InningsPitched DESC, PS.ERA DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData3.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		ip = (float)sqlite3_column_double(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %6.1f\n",
			teamNameShort, playerName, ip);
		strArrayHTMLData3.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	strHTMLData = _T("\nEarned Runs                Earned Run Average         Innings Pitched\n");
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	for (int i = 0; i < strArrayHTMLData1.GetSize(); i++)
	{
		strHTMLData = strArrayHTMLData1[i] + strArrayHTMLData2[i] + strArrayHTMLData3[i];
		HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	}

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"P.FirstName, " \
		"P.LastName, " \
		"PS.Hits " \
		"FROM TEAM AS T " \
		"JOIN PITCHERSTATS as PS " \
		"ON T.TeamID = PS.TeamID " \
		"JOIN PITCHER as P " \
		"ON PS.PitcherID = P.PitcherID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY PS.Hits DESC, PS.ERA DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData1.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		hits = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i  ",
			teamNameShort, playerName, hits);
		strArrayHTMLData1.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"P.FirstName, " \
		"P.LastName, " \
		"PS.WHIP " \
		"FROM TEAM AS T " \
		"JOIN PITCHERSTATS as PS " \
		"ON T.TeamID = PS.TeamID " \
		"JOIN PITCHER as P " \
		"ON PS.PitcherID = P.PitcherID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 AND PS.InningsPitched > 0 " \
		"ORDER BY PS.WHIP ASC, PS.ERA DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData2.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		whip = (float)sqlite3_column_double(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %5.2f ",
			teamNameShort, playerName, whip);
		strArrayHTMLData2.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);
	if (strArrayHTMLData2.IsEmpty())
		for (int i = 0; i < 10; i++)
			strArrayHTMLData2.Add("All Pitchers have 0 WHIP");

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"P.FirstName, " \
		"P.LastName, " \
		"PS.Walks " \
		"FROM TEAM AS T " \
		"JOIN PITCHERSTATS as PS " \
		"ON T.TeamID = PS.TeamID " \
		"JOIN PITCHER as P " \
		"ON PS.PitcherID = P.PitcherID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY PS.Walks DESC, PS.ERA DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData3.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		walks = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i\n",
			teamNameShort, playerName, walks);
		strArrayHTMLData3.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	strHTMLData = _T("\nHits Allowed               WHIP                       Walks Allowed\n");
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	for (int i = 0; i < strArrayHTMLData1.GetSize(); i++)
	{
		strHTMLData = strArrayHTMLData1[i] + strArrayHTMLData2[i] + strArrayHTMLData3[i];
		HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	}

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"P.FirstName, " \
		"P.LastName, " \
		"PS.Strikeouts " \
		"FROM TEAM AS T " \
		"JOIN PITCHERSTATS as PS " \
		"ON T.TeamID = PS.TeamID " \
		"JOIN PITCHER as P " \
		"ON PS.PitcherID = P.PitcherID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY PS.Strikeouts DESC, PS.ERA DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData1.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		strikeouts = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i  ",
			teamNameShort, playerName, strikeouts);
		strArrayHTMLData1.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"P.FirstName, " \
		"P.LastName, " \
		"PS.Wins " \
		"FROM TEAM AS T " \
		"JOIN PITCHERSTATS as PS " \
		"ON T.TeamID = PS.TeamID " \
		"JOIN PITCHER as P " \
		"ON PS.PitcherID = P.PitcherID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY PS.Wins DESC, PS.ERA DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData2.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		wins = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i ",
			teamNameShort, playerName, wins);
		strArrayHTMLData2.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"P.FirstName, " \
		"P.LastName, " \
		"PS.Loss " \
		"FROM TEAM AS T " \
		"JOIN PITCHERSTATS as PS " \
		"ON T.TeamID = PS.TeamID " \
		"JOIN PITCHER as P " \
		"ON PS.PitcherID = P.PitcherID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY PS.Loss DESC, PS.ERA DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData3.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		loss = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i\n",
			teamNameShort, playerName, loss);
		strArrayHTMLData3.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	strHTMLData = _T("\nStrikeouts                 Wins                      Loss\n");
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	for (int i = 0; i < strArrayHTMLData1.GetSize(); i++)
	{
		strHTMLData = strArrayHTMLData1[i] + strArrayHTMLData2[i] + strArrayHTMLData3[i];
		HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	}

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"P.FirstName, " \
		"P.LastName, " \
		"PS.Starts " \
		"FROM TEAM AS T " \
		"JOIN PITCHERSTATS as PS " \
		"ON T.TeamID = PS.TeamID " \
		"JOIN PITCHER as P " \
		"ON PS.PitcherID = P.PitcherID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY PS.Starts DESC, PS.ERA DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData1.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		starts = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i  ",
			teamNameShort, playerName, starts);
		strArrayHTMLData1.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"P.FirstName, " \
		"P.LastName, " \
		"PS.Saves " \
		"FROM TEAM AS T " \
		"JOIN PITCHERSTATS as PS " \
		"ON T.TeamID = PS.TeamID " \
		"JOIN PITCHER as P " \
		"ON PS.PitcherID = P.PitcherID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY PS.Saves DESC, PS.ERA DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData2.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		saves = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i ",
			teamNameShort, playerName, saves);
		strArrayHTMLData2.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	/* Create SQL statement */
	sqlSelect = "SELECT "  \
		"T.TeamNameShort, " \
		"P.FirstName, " \
		"P.LastName, " \
		"PS.HomeRuns " \
		"FROM TEAM AS T " \
		"JOIN PITCHERSTATS as PS " \
		"ON T.TeamID = PS.TeamID " \
		"JOIN PITCHER as P " \
		"ON PS.PitcherID = P.PitcherID " \
		"WHERE T.LeagueID = ?1 AND T.ConferenceID = ?2 AND T.DivisionID = ?3 " \
		"ORDER BY PS.HomeRuns DESC, PS.ERA DESC LIMIT 10";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &localStmtSelect, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(localStmtSelect, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 2, conferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind conferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(localStmtSelect, 3, divisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind divisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	strArrayHTMLData3.RemoveAll();
	rcSqlStepTeam = sqlite3_step(localStmtSelect);
	while (rcSqlStepTeam == SQLITE_ROW)
	{
		teamNameShort = sqlite3_column_text(localStmtSelect, 0);
		firstName = sqlite3_column_text(localStmtSelect, 1);
		lastName = sqlite3_column_text(localStmtSelect, 2);
		homeRuns = sqlite3_column_int(localStmtSelect, 3);

		playerName = firstName + _T(" ") + lastName;
		sprintf_s(HTMLData, "%s %-16.16s %4i\n",
			teamNameShort, playerName, homeRuns);
		strArrayHTMLData3.Add(HTMLData);

		// Get next player
		rcSqlStepTeam = sqlite3_step(localStmtSelect);
	}
	sqlite3_finalize(localStmtSelect);

	strHTMLData = _T("\nStarts                     Saves                     HomeRuns Allowed\n");
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	for (int i = 0; i < strArrayHTMLData1.GetSize(); i++)
	{
		strHTMLData = strArrayHTMLData1[i] + strArrayHTMLData2[i] + strArrayHTMLData3[i];
		HTMLFile.Write(strHTMLData, strHTMLData.GetLength());
	}

	sprintf_s(HTMLData, "</B></PRE>\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	// Write the Last Updated line n the HTML file
	_strtime_s(timebuf);
	_strdate_s(datebuf);
	sprintf_s(HTMLData, "<BR>Last Updated on %s at %s<BR>\n", datebuf, timebuf);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	sprintf_s(HTMLData, "</BODY></HTML>\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData, strHTMLData.GetLength());

	HTMLFile.Close();
}

void CBaseballDoc::OnPlayersAddEditBatters() 
{
	CString strLeagueName;
	CString strLeagueFile;
	CString strLeagueDir;
	CString strLeague;
	int leagueID = 0;
	CString strTeam;
	int teamID = 0;
	CString strTeamFile;
	CString strTeamName;
	PropertyPageBatters myBatters1;
	PropertyPageBattersChance myBatters2;
	PropertyPageBattersStats myBatters3;
	PropertyPageBattersInfo myBatters4;
	PropertySheetBatters myBattersSheet("Batters",NULL,0);

	// Save CWnd pointer for message processing
	m_pPropertySheetBatters = &myBattersSheet;

	myBattersSheet.m_pPage1 = &myBatters1;
	myBattersSheet.m_pPage2 = &myBatters2;
	myBattersSheet.m_pPage3 = &myBatters3;
	myBattersSheet.m_pPage4 = &myBatters4;

	myBattersSheet.AddPage(&myBatters1);
	myBattersSheet.AddPage(&myBatters2);
	myBattersSheet.AddPage(&myBatters3);
	myBattersSheet.AddPage(&myBatters4);
	// For testing force to a team name

	leagueID = GetLeagues(TRUE);

	myBattersSheet.m_TeamID = GetTeams(leagueID);
	m_TeamRecord teamRecord = GetTeam(myBattersSheet.m_TeamID);

	myBattersSheet.m_TeamName = teamRecord.TeamName;

	// Remove the APPLY button from the display
	myBattersSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;
	myBattersSheet.DoModal();
}

int CBaseballDoc::GetLeagues(BOOL baseFlag)
{
	DlgSelLeague dlgSelLeague;
	int leagueID = 0;
	CString strLeagueName;
	int numConf = 0;
	int numDivision = 0;
	int base = false;
	char *sqlLeague;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlLeague = "SELECT "  \
		"LeagueID," \
		"LeagueName," \
		"NumberOfConferences," \
		"NumberOfDivisions," \
		"BaseLeague" \
		" FROM LEAGUES ";
//		" WHERE BaseLeague = ?1 " ;

	rc = sqlite3_prepare_v2(m_db, sqlLeague, strlen(sqlLeague), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for LEAGUES Select OK:\n");
		//AfxMessageBox(buffer);
	}
	//// Bind the data to field '1' which is the first '?' in the INSERT statement
	//rc = sqlite3_bind_int(m_stmt, 1, baseFlag);
	//if (rc != SQLITE_OK)
	//{
	//	sprintf_s(buffer, sizeof(buffer), "Could not bind int: %s\n", sqlite3_errmsg(m_db));
	//	AfxMessageBox(buffer);
	//}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		//leagueID = sqlite3_column_int(m_stmt, 0);
		strLeagueName = sqlite3_column_text(m_stmt, 1);
		//numConf = sqlite3_column_int(m_stmt, 2);
		//numDivision = sqlite3_column_int(m_stmt, 3);
		//base = sqlite3_column_int(m_stmt, 4);
		if (strLeagueName != "DEFAULT")
			dlgSelLeague.m_arrayLeagues.Add(strLeagueName);
	}

	sqlite3_finalize(m_stmt);

	if (dlgSelLeague.DoModal() == IDOK)
	{
		strLeagueName = dlgSelLeague.m_arrayLeagues[0];
	}
	else
	{
		// No Leagues found so display message
		AfxMessageBox(_T("Could not find any Leagues files. Please create a League"));
		return 0;
	}
	
	leagueID = GetLeagueID(strLeagueName);

	return leagueID;
}

int CBaseballDoc::GetConferenceID(int LeagueID)
{
	DlgSelLeague dlgSelConference;
	int conferenceID = 0;
	CString strConferenceName;
	char *sqlLeague;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlLeague = "SELECT "  \
		"ConferenceName " \
		" FROM CONFERENCES " \
		" WHERE LeagueID = ?1 " ;

	rc = sqlite3_prepare_v2(m_db, sqlLeague, strlen(sqlLeague), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for LEAGUES Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, LeagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeagueID: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		strConferenceName = sqlite3_column_text(m_stmt, 0);
//		if (strConferenceName != "DEFAULT")
			dlgSelConference.m_arrayLeagues.Add(strConferenceName);
	}

	sqlite3_finalize(m_stmt);

	if (dlgSelConference.m_arrayLeagues.GetCount() != 0)
	{
		if (dlgSelConference.DoModal() == IDOK)
		{
			strConferenceName = dlgSelConference.m_arrayLeagues[0];
		}
		else
		{
			// No Leagues found so display message
			//AfxMessageBox(_T("Could not find any Conferences. Please create a Conference"));
			strConferenceName = _T("DEFAULT");
			return 1;		// 1 is default
		}
	}
	else
	{
		// No Leagues found so display message
		strConferenceName = _T("DEFAULT");
		return 1;		// 1 is default
	}

	conferenceID = GetConferenceIDName(strConferenceName, LeagueID);

	return conferenceID;
}

int CBaseballDoc::GetDivisionID(int LeagueID)
{
	DlgSelLeague dlgSelDivision;
	int divisionID = 0;
	CString strDivisionName;
	char *sqlLeague;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlLeague = "SELECT "  \
		"DivisionName " \
		" FROM DIVISIONS " \
		" WHERE LeagueID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlLeague, strlen(sqlLeague), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for LEAGUES Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, LeagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeagueID: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		strDivisionName = sqlite3_column_text(m_stmt, 0);
		dlgSelDivision.m_arrayLeagues.Add(strDivisionName);
	}

	sqlite3_finalize(m_stmt);

	if (dlgSelDivision.m_arrayLeagues.GetCount() != 0)
	{
		if (dlgSelDivision.DoModal() == IDOK)
		{
			strDivisionName = dlgSelDivision.m_arrayLeagues[0];
		}
		else
		{
			// No Leagues found so display message
			//AfxMessageBox(_T("Could not find any Divisions. Please create a Division"));
			strDivisionName = _T("DEFAULT");
			return 1;		// 1 is default
		}
	}
	else
	{
		// No Leagues found so display message
		strDivisionName = _T("DEFAULT");
		return 1;		// 1 is default
	}

	divisionID = GetDivisionIDName(strDivisionName, LeagueID);

	return divisionID;
}

// Create a list of teams based on teams in a given League.
// Place team neames in dlgSelTeam.m_arrayTeams
// return with the chosen team ID
int CBaseballDoc::GetTeams(int leagueID)
{
	dlgSelTeam dlgSelTeam;
	int teamID = 0;
	CString strTeamName;
	int numConf = 0;
	int numDivision = 0;
	int base = false;
	char *sqlTeam;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlTeam = "SELECT "  \
		"TeamName" \
		" FROM TEAM " \
		" WHERE LeagueID = ?1 " ;

	rc = sqlite3_prepare_v2(m_db, sqlTeam, strlen(sqlTeam), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for TEAM Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, leagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind leagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		strTeamName = sqlite3_column_text(m_stmt, 0);
		dlgSelTeam.m_arrayTeams.Add(strTeamName);
	}

	sqlite3_finalize(m_stmt);

	if (dlgSelTeam.DoModal() == IDOK)
	{
		strTeamName = dlgSelTeam.m_arrayTeams[0];
	}
	else
	{
		// No Teams found so display message
		AfxMessageBox(_T("Could not find any Teams files. Please create a Team"));
		return 0;
	}

	teamID = GetTeamID(strTeamName, leagueID);

	return teamID;	// Return the ID of the selected team
}

void CBaseballDoc::OnPlayersAddEditPitchers() 
{
	CString strLeagueName;
	CString strLeagueFile;
	CString strLeagueDir;
	CString strLeague;
	int leagueID = 0;
	CString strTeam;
	int teamID = 0;
	CString strTeamFile;
	CString strTeamName;
	PropertyPagePitchersInfo myPitchers1;
	PropertyPagePitchersChance myPitchers2;
	PropertyPagePitchersStats myPitchers3;
	PropertySheetPitchers myPitchersSheet("Pitchers",NULL,0);

	// Save CWnd pointer for message processing
	m_pPropertySheetPitchers = &myPitchersSheet;

	myPitchersSheet.m_pPage1 = &myPitchers1;
	myPitchersSheet.m_pPage2 = &myPitchers2;
	myPitchersSheet.m_pPage3 = &myPitchers3;

	myPitchersSheet.AddPage(&myPitchers1);
	myPitchersSheet.AddPage(&myPitchers2);
	myPitchersSheet.AddPage(&myPitchers3);

	leagueID = GetLeagues(TRUE);

	myPitchersSheet.m_TeamID = GetTeams(leagueID);
	m_TeamRecord teamRecord = GetTeam(myPitchersSheet.m_TeamID);

	myPitchersSheet.m_TeamName = teamRecord.TeamName;

	// Remove the APPLY button from the display
	myPitchersSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;
	myPitchersSheet.DoModal();
}

void CBaseballDoc::OnLeaguesLeagueOptionsHTML() 
{
	CString strLeague;
	int leagueID = 0;
	CString strLeagueName;
	CString strLeagueFile;
	CString strLeagueDir;

	// Do not retrieve the Base directory
//	strLeague = GetLeagues(FALSE);
	leagueID = GetLeagues(FALSE);

	strLeagueName = strLeague.Left(30);
	strLeagueFile = strLeague.Right(12);
	strLeagueDir = strLeagueFile.Left(8);

	PropertyPageTeamHTMLOptions myTeamHTMLOptions;
	PropertyPageLeagueHTMLOptions myLeagueHTMLOptions;
	myTeamHTMLOptions.m_strLeagueDir = strLeagueDir;
	myLeagueHTMLOptions.m_strLeagueDir = strLeagueDir;

	PropertySheetLeagueOptions myLeagueOptions("League and Team Options",NULL,0);

	myLeagueOptions.AddPage(&myTeamHTMLOptions);
	myLeagueOptions.AddPage(&myLeagueHTMLOptions);

	myLeagueOptions.DoModal();
}

void CBaseballDoc::OnFileOpen()
{
	// TODO: Add your command handler code here
	CFileDialog* myfiledlg;
	INT_PTR nRet = -1;

	LPCTSTR lpszFilter = _T("DataBase Files (*.db)|*.db|All Files (*.*)|*.*||");
	myfiledlg = new CFileDialog(TRUE, _T("*.db"), _T("baseball.db"), NULL, lpszFilter, NULL);
	myfiledlg->m_ofn.lpstrTitle = _T("Load DataBase File");
	nRet = myfiledlg->DoModal();

	// Handle the return value from DoModal 
	switch (nRet)
	{
	case -1:
		AfxMessageBox(_T("Dialog box could not be created!"));
		break;
	case IDABORT:
		// Do something 
		break;
	case IDOK:
		// Do something 
		m_DBFileName = myfiledlg->GetPathName();
		_splitpath_s(m_DBFileName, m_drive, _MAX_DRIVE, m_dir, _MAX_DIR, m_dbfname,	_MAX_FNAME, m_ext, _MAX_EXT);
		OpenDatabase();
		//AfxMessageBox(_T("OK pressed!"));
		break;
	case IDCANCEL:
		// Do something 
		AfxMessageBox(_T("Cancel pressed!"));
		break;
	default:
		// Do something 
		break;
	};
}

int CBaseballDoc::OpenDatabase()
{
	CStringA ansiString(m_DBFileName);
	CHAR buffer[100];

	if (m_dbOpen = SQLITE_OK)
	{
		sqlite3_close(m_db);
		m_dbOpen = 99;
	}

	m_dbOpen = sqlite3_open(ansiString, &m_db);
	if (m_dbOpen)
	{
		sprintf_s(buffer, sizeof(buffer), "Can't open database: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Database opened: %s\n", ansiString);
		AfxMessageBox(buffer);

		// Display version of Database
		//DBVersion();

		// Enable Foregin Keyss support in sqlite
		DBSetForeginKeys(true);
	}

	return 0;
}

int CBaseballDoc::DBSetForeginKeys(bool OnOff)
{
	CHAR buffer[100];
	int rc = 0;

	// Display that initial setting for foregin keys is off or "0"
	rc = sqlite3_prepare_v2(m_db, "PRAGMA foreign_keys", -1, &m_stmt, 0);

	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "PRAGMA foreign_keys 1 Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc == SQLITE_ROW)
	{
		sprintf_s(buffer, sizeof(buffer), "%s  %s\n", sqlite3_column_name(m_stmt, 0), sqlite3_column_text(m_stmt, 0));
		//AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);

	if (OnOff)
	{
	// Turn on foreign key support
		rc = sqlite3_prepare_v2(m_db, "PRAGMA foreign_keys = ON", -1, &m_stmt, 0);
	}
	else
	{
		rc = sqlite3_prepare_v2(m_db, "PRAGMA foreign_keys = OFF", -1, &m_stmt, 0);
	}

	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "PRAGMA foreign_keys 2 Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc == SQLITE_ROW)
	{
		sprintf_s(buffer, sizeof(buffer), "%s  %s\n", sqlite3_column_name(m_stmt, 0), sqlite3_column_text(m_stmt, 0));
		//AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);

	// Display that the setting for foregin keys is now on or "1"
	rc = sqlite3_prepare_v2(m_db, "PRAGMA foreign_keys", -1, &m_stmt, 0);

	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "PRAGMA foreign_keys 3 Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc == SQLITE_ROW)
	{
		sprintf_s(buffer, sizeof(buffer), "%s  %s\n", sqlite3_column_name(m_stmt, 0), sqlite3_column_text(m_stmt, 0));
		//AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);
	return 0;
}

int CBaseballDoc::DBVersion()
{
	CHAR buffer[100];
	int rc;

	rc = sqlite3_prepare_v2(m_db, "SELECT SQLITE_VERSION()", -1, &m_stmt, 0);

	if (rc != SQLITE_OK)
	{
		//fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		sprintf_s(buffer, sizeof(buffer), "SELECT SQLITE_VERSION Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc == SQLITE_ROW)
	{
		//printf("%s  %s\n", sqlite3_column_name(m_stmt, 0), sqlite3_column_text(m_stmt, 0));
		sprintf_s(buffer, sizeof(buffer), "%s  %s\n", sqlite3_column_name(m_stmt, 0), sqlite3_column_text(m_stmt, 0));
		AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);

	return 0;
}

int CBaseballDoc::GetLeagueID(CStringA strLeagueName)
{
	int rc;
	CHAR buffer[100];
	char *sqlSelect;
	int myLeagueID = 0;

	// Select the LeagueId
	sqlSelect = "SELECT LeagueId from LEAGUES WHERE LeagueName = ?1";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &m_stmt, 0);

	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "SELECT LeagueId Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the SELECT statement
	rc = sqlite3_bind_text(m_stmt, 1, strLeagueName, strlen(strLeagueName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeagueName: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc == SQLITE_ROW)
	{
		sprintf_s(buffer, sizeof(buffer), "%s  %i\n", sqlite3_column_name(m_stmt, 0), sqlite3_column_int(m_stmt, 0));
		//AfxMessageBox(buffer);
		myLeagueID = sqlite3_column_int(m_stmt, 0);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "LeagueID Select returned nothing: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);
	return myLeagueID;
}

int CBaseballDoc::GetTeamID(CStringA strTeamName, int LeagueID)
{
	int myTeamId = 0;
	int rc;
	CHAR buffer[100];
	char *sqlSelect;

	sqlSelect = "SELECT TeamId from TEAM WHERE TeamName = ?1 and LeagueID = ?2";

	rc = sqlite3_prepare_v2(m_db, sqlSelect, strlen(sqlSelect), &m_stmt, 0);

	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch SELECT TeamId data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	// Bind the data to field '1' which is the first '?' in the SELECT statement
	rc = sqlite3_bind_text(m_stmt, 1, strTeamName, strlen(strTeamName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind teamname: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 2, LeagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeagueID: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc == SQLITE_ROW)
	{
		sprintf_s(buffer, sizeof(buffer), "%s  %i\n", sqlite3_column_name(m_stmt, 0), sqlite3_column_int(m_stmt, 0));
		//AfxMessageBox(buffer);
		myTeamId = sqlite3_column_int(m_stmt, 0);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Select TeamID returned nothing: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	return myTeamId;
}

CBaseballDoc::m_TeamRecord CBaseballDoc::GetTeam(int TeamID)
{
	char *sqlTeam;
	int rc;
	CHAR buffer[100];
	m_TeamRecord teamResult;

	/* Create SQL statement */
	sqlTeam = "SELECT "  \
		"TeamID," \
		"TeamName," \
		"TeamNameShort," \
		"BallparkName," \
		"HomeWins," \
		"HomeLosses," \
		"AwayWins," \
		"AwayLosses," \
		"LeagueID," \
		"ConferenceID," \
		"DivisionID," \
		"TeamYear," \
		"BaseTeam," \
		"CreateTime," \
		"LastUpdateTime" \
		" FROM TEAM " \
		" WHERE TeamID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlTeam, strlen(sqlTeam), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for TEAM Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, TeamID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		teamResult.TeamID = sqlite3_column_int(m_stmt, 0);
		teamResult.TeamName = sqlite3_column_text(m_stmt, 1);
		teamResult.TeamNameShort = sqlite3_column_text(m_stmt, 2);
		teamResult.BallparkName = sqlite3_column_text(m_stmt, 3);
		teamResult.HomeWins = sqlite3_column_int(m_stmt, 4);
		teamResult.HomeLosses = sqlite3_column_int(m_stmt, 5);
		teamResult.AwayWins = sqlite3_column_int(m_stmt, 6);
		teamResult.AwayLosses = sqlite3_column_int(m_stmt, 7);
		teamResult.LeagueID = sqlite3_column_int(m_stmt, 8);
		teamResult.ConferenceID = sqlite3_column_int(m_stmt, 9);
		teamResult.DivisionID = sqlite3_column_int(m_stmt, 10);
		teamResult.TeamYear = sqlite3_column_int(m_stmt, 11);
		teamResult.BaseTeam = sqlite3_column_int(m_stmt, 12);
		teamResult.CreateTime = sqlite3_column_text(m_stmt, 13);
		teamResult.LastUpdateTime = sqlite3_column_text(m_stmt, 14);
	}

	sqlite3_finalize(m_stmt);

	return teamResult;
}

CBaseballDoc::m_LeagueRecord CBaseballDoc::GetLeague(int LeagueID)
{
	m_LeagueRecord leagueResult;
	char *sqlLeague;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlLeague = "SELECT "  \
		"LeagueID," \
		"LeagueName," \
		"NumberOfConferences," \
		"NumberOfDivisions," \
		"BaseLeague," \
		"CreateTime," \
		"LastUpdateTime" \
		" FROM LEAGUES " \
		" WHERE LeagueID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlLeague, strlen(sqlLeague), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for LEAGUES Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, LeagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		leagueResult.LeagueID = sqlite3_column_int(m_stmt, 0);
		leagueResult.LeagueName = sqlite3_column_text(m_stmt, 1);
		leagueResult.NumberOfConferences = sqlite3_column_int(m_stmt, 2);
		leagueResult.NumberOfDivisions = sqlite3_column_int(m_stmt, 3);
		leagueResult.BaseLeague = sqlite3_column_int(m_stmt, 4);
		leagueResult.CreateTime = sqlite3_column_text(m_stmt, 5);
		leagueResult.LastUpdateTime = sqlite3_column_text(m_stmt, 6);
	}

	sqlite3_finalize(m_stmt);

	return leagueResult;
}

CBaseballDoc::m_ConferenceRecord CBaseballDoc::GetConference(int ConferenceID)
{
	m_ConferenceRecord conferenceResult;
	char *sqlConference;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlConference = "SELECT "  \
		"ConferenceID," \
		"ConferenceName," \
		"LeagueID," \
		"BaseConference," \
		"CreateTime," \
		"LastUpdateTime" \
		" FROM CONFERENCES " \
		" WHERE ConferenceID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlConference, strlen(sqlConference), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for CONFERENCES Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, ConferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ConferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		conferenceResult.ConferenceID = sqlite3_column_int(m_stmt, 0);
		conferenceResult.ConferenceName = sqlite3_column_text(m_stmt, 1);
		conferenceResult.LeagueID = sqlite3_column_int(m_stmt, 2);
		conferenceResult.BaseConference = sqlite3_column_int(m_stmt, 3);
		conferenceResult.CreateTime = sqlite3_column_text(m_stmt, 4);
		conferenceResult.LastUpdateTime = sqlite3_column_text(m_stmt, 5);
	}

	sqlite3_finalize(m_stmt);

	return conferenceResult;
}

int CBaseballDoc::GetConferenceIDName(CString strConferenceName, int LeagueID)
{
	int conferenceID;
	char *sqlConference;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlConference = "SELECT "  \
		"ConferenceID " \
		" FROM CONFERENCES " \
		" WHERE LeagueID = ?1 AND ConferenceName = ?2 ";

	rc = sqlite3_prepare_v2(m_db, sqlConference, strlen(sqlConference), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for CONFERENCES Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, LeagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_text(m_stmt, 2, strConferenceName, strlen(strConferenceName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind strConferenceName int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		conferenceID = sqlite3_column_int(m_stmt, 0);
	}

	sqlite3_finalize(m_stmt);

	return conferenceID;
}

int CBaseballDoc::GetDivisionIDName(CString strDivisionName, int LeagueID)
{
	int divisionID;
	char *sqlDivision;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlDivision = "SELECT "  \
		"DivisionID " \
		" FROM DIVISIONS " \
		" WHERE LeagueID = ?1 AND DivisionName = ?2 ";

	rc = sqlite3_prepare_v2(m_db, sqlDivision, strlen(sqlDivision), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for DIVISIONS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, LeagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_text(m_stmt, 2, strDivisionName, strlen(strDivisionName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind strDivisionName int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		divisionID = sqlite3_column_int(m_stmt, 0);
	}

	sqlite3_finalize(m_stmt);

	return divisionID;
}

CBaseballDoc::m_DivisionRecord CBaseballDoc::GetDivision(int DivisionID)
{
	m_DivisionRecord divisionResult;
	char *sqlDivision;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlDivision = "SELECT "  \
		"DivisionID," \
		"DivisionName," \
		"LeagueID," \
		"ConferenceID," \
		"BaseDivisions," \
		"CreateTime," \
		"LastUpdateTime" \
		" FROM DIVISIONS " \
		" WHERE DivisionID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlDivision, strlen(sqlDivision), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for DIVISIONS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, DivisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind DivisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		divisionResult.DivisionID = sqlite3_column_int(m_stmt, 0);
		divisionResult.DivisionName = sqlite3_column_text(m_stmt, 1);
		divisionResult.LeagueID = sqlite3_column_int(m_stmt, 2);
		divisionResult.ConferenceID = sqlite3_column_int(m_stmt, 3);
		divisionResult.BaseDivisions = sqlite3_column_int(m_stmt, 4);
		divisionResult.CreateTime = sqlite3_column_text(m_stmt, 5);
		divisionResult.LastUpdateTime = sqlite3_column_text(m_stmt, 6);
	}

	sqlite3_finalize(m_stmt);

	return divisionResult;
}

CBaseballDoc::m_BatterRecord CBaseballDoc::GetBatter(int BatterID)
{
	m_BatterRecord batterResult;
	char *sqlBatter;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlBatter = "SELECT "  \
		"BatterID," \
		"FirstName," \
		"LastName," \
		"Pitcher," \
		"Catcher," \
		"FirstBase," \
		"SecondBase," \
		"ShortStop," \
		"ThirdBase," \
		"LeftField," \
		"CenterField," \
		"RightField," \
		"Bunting," \
		"HitRun," \
		"Running," \
		"Stealing," \
		"CatchArm," \
		"OutArm," \
		"PowerRight," \
		"PowerLeft," \
		"Pass," \
		"TRate," \
		"ER1," \
		"ER2," \
		"ER3," \
		"ER4," \
		"ER5," \
		"ER6," \
		"ER7," \
		"ER8," \
		"ER9," \
		"BatterHits," \
		"TeamID," \
		"OBChanceHomeRun," \
		"OBChanceTriple," \
		"OBChanceDouble," \
		"OBChanceSingle," \
		"OBChanceWalk," \
		"ChanceDoublePlay," \
		"OBChanceHomeRunRight," \
		"OBChanceTripleRight," \
		"OBChanceDoubleRight," \
		"OBChanceSingleRight," \
		"OBChanceWalkRight," \
		"ChanceDoublePlayRight," \
		"OBChanceHomeRunLeft," \
		"OBChanceTripleLeft," \
		"OBChanceDoubleLeft," \
		"OBChanceSingleLeft," \
		"OBChanceWalkLeft," \
		"ChanceDoublePlayLeft," \
		"OBChanceBasic," \
		"OBChanceLeft," \
		"OBChanceRight," \
		"CreateTime," \
		"LastUpdateTime" \
		" FROM BATTER " \
		" WHERE BatterID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlBatter, strlen(sqlBatter), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTER Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, BatterID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind BatterID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		batterResult.BatterID = sqlite3_column_int(m_stmt, 0);
		batterResult.FirstName = sqlite3_column_text(m_stmt, 1);
		batterResult.LastName = sqlite3_column_text(m_stmt, 2);
		batterResult.Pitcher = sqlite3_column_int(m_stmt, 3);
		batterResult.Catcher = sqlite3_column_int(m_stmt, 4);
		batterResult.FirstBase = sqlite3_column_int(m_stmt, 5);
		batterResult.SecondBase = sqlite3_column_int(m_stmt, 6);
		batterResult.ShortStop = sqlite3_column_int(m_stmt, 7);
		batterResult.ThirdBase = sqlite3_column_int(m_stmt, 8);
		batterResult.LeftField = sqlite3_column_int(m_stmt, 9);
		batterResult.CenterField = sqlite3_column_int(m_stmt, 10);
		batterResult.RightField = sqlite3_column_int(m_stmt, 11);
		batterResult.Bunting = sqlite3_column_int(m_stmt, 12);
		batterResult.HitRun = sqlite3_column_int(m_stmt, 13);
		batterResult.Running = sqlite3_column_int(m_stmt, 14);
		batterResult.Stealing = sqlite3_column_int(m_stmt, 15);
		batterResult.CatchArm = sqlite3_column_int(m_stmt, 16);
		batterResult.OutArm = sqlite3_column_int(m_stmt, 17);
		batterResult.PowerRight = sqlite3_column_int(m_stmt, 18);
		batterResult.PowerLeft = sqlite3_column_int(m_stmt, 19);
		batterResult.Pass = sqlite3_column_int(m_stmt, 20);
		batterResult.TRate = sqlite3_column_int(m_stmt, 21);
		batterResult.ER1 = sqlite3_column_int(m_stmt, 22);
		batterResult.ER2 = sqlite3_column_int(m_stmt, 23);
		batterResult.ER3 = sqlite3_column_int(m_stmt, 24);
		batterResult.ER4 = sqlite3_column_int(m_stmt, 25);
		batterResult.ER5 = sqlite3_column_int(m_stmt, 26);
		batterResult.ER6 = sqlite3_column_int(m_stmt, 27);
		batterResult.ER7 = sqlite3_column_int(m_stmt, 28);
		batterResult.ER8 = sqlite3_column_int(m_stmt, 29);
		batterResult.ER9 = sqlite3_column_int(m_stmt, 30);
		batterResult.BatterHits = sqlite3_column_int(m_stmt, 31);
		batterResult.TeamID = sqlite3_column_int(m_stmt, 32);
		batterResult.OBChanceHomeRun = sqlite3_column_double(m_stmt, 33);
		batterResult.OBChanceTriple = sqlite3_column_double(m_stmt, 34);
		batterResult.OBChanceDouble = sqlite3_column_double(m_stmt, 35);
		batterResult.OBChanceSingle = sqlite3_column_double(m_stmt, 36);
		batterResult.OBChanceWalk = sqlite3_column_double(m_stmt, 37);
		batterResult.ChanceDoublePlay = sqlite3_column_double(m_stmt, 38);
		batterResult.OBChanceHomeRunRight = sqlite3_column_double(m_stmt, 39);
		batterResult.OBChanceTripleRight = sqlite3_column_double(m_stmt, 40);
		batterResult.OBChanceDoubleRight = sqlite3_column_double(m_stmt, 41);
		batterResult.OBChanceSingleRight = sqlite3_column_double(m_stmt, 42);
		batterResult.OBChanceWalkRight = sqlite3_column_double(m_stmt, 43);
		batterResult.ChanceDoublePlayRight = sqlite3_column_double(m_stmt, 44);
		batterResult.OBChanceHomeRunLeft = sqlite3_column_double(m_stmt, 45);
		batterResult.OBChanceTripleLeft = sqlite3_column_double(m_stmt, 46);
		batterResult.OBChanceDoubleLeft = sqlite3_column_double(m_stmt, 47);
		batterResult.OBChanceSingleLeft = sqlite3_column_double(m_stmt, 48);
		batterResult.OBChanceWalkLeft = sqlite3_column_double(m_stmt, 49);
		batterResult.ChanceDoublePlayLeft = sqlite3_column_double(m_stmt, 50);
		batterResult.OBChanceBasic = sqlite3_column_double(m_stmt, 51);
		batterResult.OBChanceLeft = sqlite3_column_double(m_stmt, 52);
		batterResult.OBChanceRight = sqlite3_column_double(m_stmt, 53);
		batterResult.CreateTime = sqlite3_column_text(m_stmt, 54);
		batterResult.LastUpdateTime = sqlite3_column_text(m_stmt, 55);
	}

	sqlite3_finalize(m_stmt);

	return batterResult;
}

CBaseballDoc::m_BatterStatsRecord CBaseballDoc::GetBatterStats(int BatterStatsID)
{
	m_BatterStatsRecord batterstatsResult;
	char *sqlBatterStats;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlBatterStats = "SELECT "  \
		"BatterStatsID," \
		"AB," \
		"Runs," \
		"Hits," \
		"RBI," \
		"Doubles," \
		"Triples," \
		"HomeRuns," \
		"Walk," \
		"Stirkeout," \
		"ReachedOnError," \
		"Sacrifice," \
		"StolenBase," \
		"CS," \
		"Games," \
		"HBP," \
		"AVG," \
		"SLG," \
		"OBP," \
		"BatterID," \
		"TeamID," \
		"CreateTime," \
		"LastUpdateTime" \
		" FROM BATTERSTATS " \
		" WHERE BatterStatsID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlBatterStats, strlen(sqlBatterStats), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for BATTERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, BatterStatsID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind BatterStatsID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		batterstatsResult.BatterStatsID = sqlite3_column_int(m_stmt, 0);
		batterstatsResult.AB = sqlite3_column_int(m_stmt, 1);
		batterstatsResult.Runs = sqlite3_column_int(m_stmt, 2);
		batterstatsResult.Hits = sqlite3_column_int(m_stmt, 3);
		batterstatsResult.RBI = sqlite3_column_int(m_stmt, 4);
		batterstatsResult.Doubles = sqlite3_column_int(m_stmt, 5);
		batterstatsResult.Triples = sqlite3_column_int(m_stmt, 6);
		batterstatsResult.HomeRuns = sqlite3_column_int(m_stmt, 7);
		batterstatsResult.Walk = sqlite3_column_int(m_stmt, 8);
		batterstatsResult.Stirkeout = sqlite3_column_int(m_stmt, 9);
		batterstatsResult.ReachedOnError = sqlite3_column_int(m_stmt, 10);
		batterstatsResult.Sacrifice = sqlite3_column_int(m_stmt, 11);
		batterstatsResult.StolenBase = sqlite3_column_int(m_stmt, 12);
		batterstatsResult.CS = sqlite3_column_int(m_stmt, 13);
		batterstatsResult.Games = sqlite3_column_int(m_stmt, 14);
		batterstatsResult.HBP = sqlite3_column_int(m_stmt, 15);
		batterstatsResult.AVG = sqlite3_column_double(m_stmt, 16);
		batterstatsResult.SLG = sqlite3_column_double(m_stmt, 17);
		batterstatsResult.OBP = sqlite3_column_double(m_stmt, 18);
		batterstatsResult.BatterID = sqlite3_column_int(m_stmt, 19);
		batterstatsResult.TeamID = sqlite3_column_int(m_stmt, 20);
		batterstatsResult.CreateTime = sqlite3_column_text(m_stmt, 21);
		batterstatsResult.LastUpdateTime = sqlite3_column_text(m_stmt, 22);
	}

	sqlite3_finalize(m_stmt);

	return batterstatsResult;
}

CBaseballDoc::m_PitcherRecord CBaseballDoc::GetPitcher(int PitcherID)
{
	m_PitcherRecord pitcherResult;
	char *sqlPitcher;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlPitcher = "SELECT "  \
		"PitcherID," \
		"FirstName," \
		"LastName," \
		"OBChanceHomeRun," \
		"OBChanceTriple," \
		"OBChanceDouble," \
		"OBChanceSingle," \
		"OBChanceWalk," \
		"ChanceDoublePlay," \
		"OBChanceHomeRunRight," \
		"OBChanceTripleRight," \
		"OBChanceDoubleRight," \
		"OBChanceSingleRight," \
		"OBChanceWalkRight," \
		"ChanceDoublePlayRight," \
		"OBChanceHomeRunLeft," \
		"OBChanceTripleLeft," \
		"OBChanceDoubleLeft," \
		"OBChanceSingleLeft," \
		"OBChanceWalkLeft," \
		"ChanceDoublePlayLeft," \
		"OBChanceBasic," \
		"OBChanceLeft," \
		"OBChanceRight," \
		"Starter," \
		"Relief," \
		"Throws," \
		"Bunting," \
		"Hold," \
		"WP," \
		"Balk," \
		"Pitcher," \
		"ER1," \
		"TeamID," \
		"CreateTime," \
		"LastUpdateTime" \
		" FROM PITCHER " \
		" WHERE PitcherID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlPitcher, strlen(sqlPitcher), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHER Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, PitcherID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind PitcherID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		pitcherResult.PitcherID = sqlite3_column_int(m_stmt, 0);
		pitcherResult.FirstName = sqlite3_column_text(m_stmt, 1);
		pitcherResult.LastName = sqlite3_column_text(m_stmt, 2);
		pitcherResult.OBChanceHomeRun = sqlite3_column_double(m_stmt, 3);
		pitcherResult.OBChanceTriple = sqlite3_column_double(m_stmt, 4);
		pitcherResult.OBChanceDouble = sqlite3_column_double(m_stmt, 5);
		pitcherResult.OBChanceSingle = sqlite3_column_double(m_stmt, 6);
		pitcherResult.OBChanceWalk = sqlite3_column_double(m_stmt, 7);
		pitcherResult.ChanceDoublePlay = sqlite3_column_double(m_stmt, 8);
		pitcherResult.OBChanceHomeRunRight = sqlite3_column_double(m_stmt, 9);
		pitcherResult.OBChanceTripleRight = sqlite3_column_double(m_stmt, 10);
		pitcherResult.OBChanceDoubleRight = sqlite3_column_double(m_stmt, 11);
		pitcherResult.OBChanceSingleRight = sqlite3_column_double(m_stmt, 12);
		pitcherResult.OBChanceWalkRight = sqlite3_column_double(m_stmt, 13);
		pitcherResult.ChanceDoublePlayRight = sqlite3_column_double(m_stmt, 14);
		pitcherResult.OBChanceHomeRunLeft = sqlite3_column_double(m_stmt, 15);
		pitcherResult.OBChanceTripleLeft = sqlite3_column_double(m_stmt, 16);
		pitcherResult.OBChanceDoubleLeft = sqlite3_column_double(m_stmt, 17);
		pitcherResult.OBChanceSingleLeft = sqlite3_column_double(m_stmt, 18);
		pitcherResult.OBChanceWalkLeft = sqlite3_column_double(m_stmt, 19);
		pitcherResult.ChanceDoublePlayLeft = sqlite3_column_double(m_stmt, 20);
		pitcherResult.OBChanceBasic = sqlite3_column_double(m_stmt, 21);
		pitcherResult.OBChanceLeft = sqlite3_column_double(m_stmt, 22);
		pitcherResult.OBChanceRight = sqlite3_column_double(m_stmt, 23);
		pitcherResult.Starter = sqlite3_column_int(m_stmt, 24);
		pitcherResult.Relief = sqlite3_column_int(m_stmt, 25);
		pitcherResult.Throws = sqlite3_column_int(m_stmt, 26);
		pitcherResult.Bunting = sqlite3_column_int(m_stmt, 27);
		pitcherResult.Hold = sqlite3_column_int(m_stmt, 28);
		pitcherResult.WP = sqlite3_column_int(m_stmt, 29);
		pitcherResult.Balk = sqlite3_column_int(m_stmt, 30);
		pitcherResult.Pitcher = sqlite3_column_int(m_stmt, 31);
		pitcherResult.ER1 = sqlite3_column_int(m_stmt, 32);
		pitcherResult.TeamID = sqlite3_column_int(m_stmt, 33);
		pitcherResult.CreateTime = sqlite3_column_text(m_stmt, 34);
		pitcherResult.LastUpdateTime = sqlite3_column_text(m_stmt, 35);
	}

	sqlite3_finalize(m_stmt);

	return pitcherResult;
}

CBaseballDoc::m_PitcherStatsRecord CBaseballDoc::GetPitcherStats(int PitcherStatsID)
{
	m_PitcherStatsRecord pitcherstatsResult;
	char *sqlPitcherStats;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlPitcherStats = "SELECT "  \
		"PitcherStatsID," \
		"Wins," \
		"Loss," \
		"Saves," \
		"InningsPitched," \
		"ER," \
		"Hits," \
		"Walks," \
		"Strikeouts," \
		"HomeRuns," \
		"Games," \
		"CompleteGames," \
		"Starts," \
		"ERA," \
		"WHIP," \
		"PitcherID," \
		"TeamID," \
		"CreateTime," \
		"LastUpdateTime" \
		" FROM PITCHERSTATS " \
		" WHERE PitcherStatsID = ?1 ";

	rc = sqlite3_prepare_v2(m_db, sqlPitcherStats, strlen(sqlPitcherStats), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for PITCHERSTATS Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, PitcherStatsID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind PitcherStatsID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	while (sqlite3_step(m_stmt) == SQLITE_ROW)
	{
		pitcherstatsResult.PitcherStatsID = sqlite3_column_int(m_stmt, 0);
		pitcherstatsResult.Wins = sqlite3_column_int(m_stmt, 1);
		pitcherstatsResult.Loss = sqlite3_column_int(m_stmt, 2);
		pitcherstatsResult.Saves = sqlite3_column_int(m_stmt, 3);
		pitcherstatsResult.InningsPitched = sqlite3_column_double(m_stmt, 4);
		pitcherstatsResult.ER = sqlite3_column_int(m_stmt, 5);
		pitcherstatsResult.Hits = sqlite3_column_int(m_stmt, 6);
		pitcherstatsResult.Walks = sqlite3_column_int(m_stmt, 7);
		pitcherstatsResult.Strikeouts = sqlite3_column_int(m_stmt, 8);
		pitcherstatsResult.HomeRuns = sqlite3_column_int(m_stmt, 9);
		pitcherstatsResult.Games = sqlite3_column_int(m_stmt, 10);
		pitcherstatsResult.CompleteGames = sqlite3_column_int(m_stmt, 11);
		pitcherstatsResult.Starts = sqlite3_column_int(m_stmt, 12);
		pitcherstatsResult.ERA = sqlite3_column_double(m_stmt, 13);
		pitcherstatsResult.WHIP = sqlite3_column_double(m_stmt, 14);
		pitcherstatsResult.PitcherID = sqlite3_column_int(m_stmt, 15);
		pitcherstatsResult.TeamID = sqlite3_column_int(m_stmt, 16);
		pitcherstatsResult.CreateTime = sqlite3_column_text(m_stmt, 17);
		pitcherstatsResult.LastUpdateTime = sqlite3_column_text(m_stmt, 18);
	}

	sqlite3_finalize(m_stmt);

	return pitcherstatsResult;
}

int CBaseballDoc::TeamUpdate(m_TeamRecord TeamRecord)
{
	char *sqlTeam;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlTeam = "UPDATE TEAM "  \
		"SET " \
		"TeamName = ?1," \
		"TeamNameShort = ?2," \
		"BallparkName = ?3," \
		"HomeWins = ?4," \
		"HomeLosses = ?5," \
		"AwayWins = ?6," \
		"AwayLosses = ?7," \
		"LeagueID = ?8," \
		"ConferenceID = ?9," \
		"DivisionID = ?10," \
		"TeamYear = ?11," \
		"BaseTeam = ?12," \
		"LastUpdateTime = datetime('NOW','localtime')" \
		" WHERE TeamID = ?13 ";

	rc = sqlite3_prepare_v2(m_db, sqlTeam, strlen(sqlTeam), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for TEAM Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_text(m_stmt, 1, TeamRecord.TeamName, strlen(TeamRecord.TeamName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamName int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_text(m_stmt, 2, TeamRecord.TeamNameShort, strlen(TeamRecord.TeamNameShort), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamNameShort int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_text(m_stmt, 3, TeamRecord.BallparkName, strlen(TeamRecord.BallparkName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind BallparkName int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 4, TeamRecord.HomeWins);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind HomeWins int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 5, TeamRecord.HomeLosses);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind HomeLosses int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 6, TeamRecord.AwayWins);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind AwayWins int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 7, TeamRecord.AwayLosses);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind AwayLosses int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 8, TeamRecord.LeagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 9, TeamRecord.ConferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ConferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 10, TeamRecord.DivisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind DivisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 11, TeamRecord.TeamYear);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamYear int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 12, TeamRecord.BaseTeam);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind BaseTeam int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 13, TeamRecord.TeamID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc != SQLITE_DONE)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to Update TEAM item: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);

	return 0;
}

int CBaseballDoc::LeagueUpdate(m_LeagueRecord LeagueRecord)
{
	char *sqlLeague;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlLeague = "UPDATE LEAGUES "  \
		"SET " \
		"LeagueName = ?1," \
		"NumberOfConferences = ?2," \
		"NumberOfDivisions = ?3," \
		"BaseLeague = ?4," \
		"LastUpdateTime = datetime('NOW','localtime')" \
		" WHERE LeagueID = ?5 ";

	rc = sqlite3_prepare_v2(m_db, sqlLeague, strlen(sqlLeague), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for TEAM Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_text(m_stmt, 1, LeagueRecord.LeagueName, strlen(LeagueRecord.LeagueName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeagueName int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 2, LeagueRecord.NumberOfConferences);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind NumberOfConferences int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 3, LeagueRecord.NumberOfDivisions);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind NumberOfDivisions int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 4, LeagueRecord.BaseLeague);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind BaseLeague int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 5, LeagueRecord.LeagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc != SQLITE_DONE)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to Update LEAGUES item: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);

	return 0;
}

int CBaseballDoc::ConfUpdate(m_ConferenceRecord ConferenceRecord)
{
	char *sqlConference;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlConference = "UPDATE CONFERENCES "  \
		"SET " \
		"ConferenceName = ?1," \
		"LeagueID = ?2," \
		"BaseConference = ?3," \
		"LastUpdateTime = datetime('NOW','localtime')" \
		" WHERE ConferenceID = ?4 ";

	rc = sqlite3_prepare_v2(m_db, sqlConference, strlen(sqlConference), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for TEAM Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_text(m_stmt, 1, ConferenceRecord.ConferenceName, strlen(ConferenceRecord.ConferenceName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ConferenceName int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 2, ConferenceRecord.LeagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 3, ConferenceRecord.BaseConference);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind BaseConference int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 4, ConferenceRecord.ConferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ConferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc != SQLITE_DONE)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to Update CONFERENCES item: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);

	return 0;
}

int CBaseballDoc::DivisionUpdate(m_DivisionRecord DivisionRecord)
{
	char *sqlDivision;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlDivision = "UPDATE DIVISIONS "  \
		"SET " \
		"DivisionName = ?1," \
		"LeagueID = ?2," \
		"ConferenceID = ?3," \
		"BaseDivisions = ?4," \
		"LastUpdateTime = datetime('NOW','localtime')" \
		" WHERE ConferenceID = ?5 ";

	rc = sqlite3_prepare_v2(m_db, sqlDivision, strlen(sqlDivision), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for TEAM Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_text(m_stmt, 1, DivisionRecord.DivisionName, strlen(DivisionRecord.DivisionName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind DivisionName int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 2, DivisionRecord.LeagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeagueID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 3, DivisionRecord.ConferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ConferenceID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 4, DivisionRecord.BaseDivisions);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind BaseDivisions int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 5, DivisionRecord.DivisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind DivisionID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc != SQLITE_DONE)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to Update DIVISIONS item: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);

	return 0;
}

int CBaseballDoc::BatterUpdate(m_BatterRecord BatterRecord)
{
	char *sqlBatter;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlBatter = "UPDATE BATTER "  \
		"SET " \
		"FirstName = ?1," \
		"LastName = ?2," \
		"Pitcher = ?3," \
		"Catcher = ?4," \
		"FirstBase = ?5," \
		"SecondBase = ?6," \
		"ShortStop = ?7," \
		"ThirdBase = ?8," \
		"LeftField = ?9," \
		"CenterField = ?10," \
		"RightField = ?11," \
		"Bunting = ?12," \
		"HitRun = ?13," \
		"Running = ?14," \
		"Stealing = ?15," \
		"CatchArm = ?16," \
		"OutArm = ?17," \
		"PowerRight = ?18," \
		"PowerLeft = ?19," \
		"Pass = ?20," \
		"TRate = ?21," \
		"ER1 = ?22," \
		"ER2 = ?23," \
		"ER3 = ?24," \
		"ER4 = ?25," \
		"ER5 = ?26," \
		"ER6 = ?27," \
		"ER7 = ?28," \
		"ER8 = ?29," \
		"ER9 = ?30," \
		"BatterHits = ?31," \
		"TeamID = ?32," \
		"OBChanceHomeRun = ?33," \
		"OBChanceTriple = ?34," \
		"OBChanceDouble = ?35," \
		"OBChanceSingle = ?36," \
		"OBChanceWalk = ?37," \
		"ChanceDoublePlay = ?38," \
		"OBChanceHomeRunRight = ?39," \
		"OBChanceTripleRight = ?40," \
		"OBChanceDoubleRight = ?41," \
		"OBChanceSingleRight = ?42," \
		"OBChanceWalkRight = ?43," \
		"ChanceDoublePlayRight = ?44," \
		"OBChanceHomeRunLeft = ?45," \
		"OBChanceTripleLeft = ?46," \
		"OBChanceDoubleLeft = ?47," \
		"OBChanceSingleLeft = ?48," \
		"OBChanceWalkLeft = ?49," \
		"ChanceDoublePlayLeft = ?50," \
		"OBChanceBasic = ?51," \
		"OBChanceLeft = ?52," \
		"OBChanceRight = ?53," \
		"LastUpdateTime = datetime('NOW','localtime')" \
		" WHERE BatterID = ?54 ";

	rc = sqlite3_prepare_v2(m_db, sqlBatter, strlen(sqlBatter), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for TEAM Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_text(m_stmt, 1, BatterRecord.FirstName, strlen(BatterRecord.FirstName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind FirstName int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_text(m_stmt, 2, BatterRecord.LastName, strlen(BatterRecord.LastName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LastName int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 3, BatterRecord.Pitcher);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Pitcher int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 4, BatterRecord.Catcher);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Catcher int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 5, BatterRecord.FirstBase);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind FirstBase int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 6, BatterRecord.SecondBase);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind SecondBase int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 7, BatterRecord.ShortStop);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ShortStop int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 8, BatterRecord.ThirdBase);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ThirdBase int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 9, BatterRecord.LeftField);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeftField int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 10, BatterRecord.CenterField);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind CenterField int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 11, BatterRecord.RightField);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind RightField int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 12, BatterRecord.Bunting);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Bunting int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 13, BatterRecord.HitRun);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind HitRun int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 14, BatterRecord.Running);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Running int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 15, BatterRecord.Stealing);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Stealing int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 16, BatterRecord.CatchArm);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind CatchArm int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 17, BatterRecord.OutArm);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OutArm int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 18, BatterRecord.PowerRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind PowerRight int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 19, BatterRecord.PowerLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind PowerLeft int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 20, BatterRecord.Pass);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Pass int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 21, BatterRecord.TRate);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TRate int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 22, BatterRecord.ER1);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ER1 int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 23, BatterRecord.ER2);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ER2 int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 24, BatterRecord.ER3);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ER3 int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 25, BatterRecord.ER4);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ER4 int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 26, BatterRecord.ER5);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ER5 int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 27, BatterRecord.ER6);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ER6 int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 28, BatterRecord.ER7);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ER7 int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 29, BatterRecord.ER8);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ER8 int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 30, BatterRecord.ER9);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ER9 int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 31, BatterRecord.BatterHits);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind BatterHits int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 32, BatterRecord.TeamID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 33, BatterRecord.OBChanceHomeRun);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceHomeRun double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 34, BatterRecord.OBChanceTriple);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceTriple double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 35, BatterRecord.OBChanceDouble);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceDouble double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 36, BatterRecord.OBChanceSingle);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceSingle double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 37, BatterRecord.OBChanceWalk);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceWalk double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 38, BatterRecord.ChanceDoublePlay);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ChanceDoublePlay double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 39, BatterRecord.OBChanceHomeRunRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceHomeRunRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 40, BatterRecord.OBChanceTripleRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceTripleRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 41, BatterRecord.OBChanceDoubleRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceDoubleRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 42, BatterRecord.OBChanceSingleRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceSingleRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 43, BatterRecord.OBChanceWalkRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceWalkRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 44, BatterRecord.ChanceDoublePlayRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ChanceDoublePlayRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 45, BatterRecord.OBChanceHomeRunLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceHomeRunLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 46, BatterRecord.OBChanceTripleLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceTripleLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 47, BatterRecord.OBChanceDoubleLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceDoubleLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 48, BatterRecord.OBChanceSingleLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceSingleLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 49, BatterRecord.OBChanceWalkLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceWalkLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 50, BatterRecord.ChanceDoublePlayLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ChanceDoublePlayLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 51, BatterRecord.OBChanceBasic);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceBasic double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 52, BatterRecord.OBChanceLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 53, BatterRecord.OBChanceRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_bind_int(m_stmt, 54, BatterRecord.BatterID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind BatterID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc != SQLITE_DONE)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to Update BATTER item: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);

	return 0;
}

int CBaseballDoc::BatterStatsUpdate(m_BatterStatsRecord BatterStatsRecord)
{
	char *sqlBatterStats;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlBatterStats = "UPDATE BATTERSTATS "  \
		"SET " \
		"AB = ?1," \
		"Runs = ?2," \
		"Hits = ?3," \
		"RBI = ?4," \
		"Doubles = ?5," \
		"Triples = ?6," \
		"HomeRuns = ?7," \
		"Walk = ?8," \
		"Stirkeout = ?9," \
		"ReachedOnError = ?10," \
		"Sacrifice = ?11," \
		"StolenBase = ?12," \
		"CS = ?13," \
		"Games = ?14," \
		"HBP = ?15," \
		"AVG = ?16," \
		"SLG = ?17," \
		"OBP = ?18," \
		"BatterID = ?19," \
		"TeamID = ?20," \
		"LastUpdateTime = datetime('NOW','localtime')" \
		" WHERE BatterStatsID = ?21 ";

	rc = sqlite3_prepare_v2(m_db, sqlBatterStats, strlen(sqlBatterStats), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for TEAM Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, BatterStatsRecord.AB);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind AB int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 2, BatterStatsRecord.Runs);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Runs int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 3, BatterStatsRecord.Hits);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Hits int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 4, BatterStatsRecord.RBI);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind RBI int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 5, BatterStatsRecord.Doubles);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Doubles int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 6, BatterStatsRecord.Triples);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Triples int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 7, BatterStatsRecord.HomeRuns);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind HomeRuns int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 8, BatterStatsRecord.Walk);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Walk int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 9, BatterStatsRecord.Stirkeout);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Stirkeout int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 10, BatterStatsRecord.ReachedOnError);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ReachedOnError int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 11, BatterStatsRecord.Sacrifice);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Sacrifice int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 12, BatterStatsRecord.StolenBase);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind StolenBase int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 13, BatterStatsRecord.CS);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind CS int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 14, BatterStatsRecord.Games);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Games int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 15, BatterStatsRecord.HBP);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind HBP int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 16, BatterStatsRecord.AVG);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind AVG double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 17, BatterStatsRecord.SLG);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind SLG double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 18, BatterStatsRecord.OBP);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBP double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 19, BatterStatsRecord.BatterID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind BatterID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 20, BatterStatsRecord.TeamID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 21, BatterStatsRecord.BatterStatsID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind BatterStatsID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc != SQLITE_DONE)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to Update BatterStats item: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);

	return 0;
}

int CBaseballDoc::PitcherUpdate(m_PitcherRecord PitcherRecord)
{
	char *sqlPitcher;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlPitcher = "UPDATE PITCHER "  \
		"SET " \
		"FirstName = ?1," \
		"LastName = ?2," \
		"OBChanceHomeRun = ?3," \
		"OBChanceTriple = ?4," \
		"OBChanceDouble = ?5," \
		"OBChanceSingle = ?6," \
		"OBChanceWalk = ?7," \
		"ChanceDoublePlay = ?8," \
		"OBChanceHomeRunRight = ?9," \
		"OBChanceTripleRight = ?10," \
		"OBChanceDoubleRight = ?11," \
		"OBChanceSingleRight = ?12," \
		"OBChanceWalkRight = ?13," \
		"ChanceDoublePlayRight = ?14," \
		"OBChanceHomeRunLeft = ?15," \
		"OBChanceTripleLeft = ?16," \
		"OBChanceDoubleLeft = ?17," \
		"OBChanceSingleLeft = ?18," \
		"OBChanceWalkLeft = ?19," \
		"ChanceDoublePlayLeft = ?20," \
		"OBChanceBasic = ?21," \
		"OBChanceLeft = ?22," \
		"OBChanceRight = ?23," \
		"Starter = ?24," \
		"Relief = ?25," \
		"Throws = ?26," \
		"Bunting = ?27," \
		"Hold = ?28," \
		"WP = ?29," \
		"Balk = ?30," \
		"Pitcher = ?31," \
		"ER1 = ?32," \
		"TeamID = ?33," \
		"LastUpdateTime = datetime('NOW','localtime')" \
		" WHERE BatterID = ?34 ";

	rc = sqlite3_prepare_v2(m_db, sqlPitcher, strlen(sqlPitcher), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for TEAM Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_text(m_stmt, 1, PitcherRecord.FirstName, strlen(PitcherRecord.FirstName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind FirstName int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_text(m_stmt, 2, PitcherRecord.LastName, strlen(PitcherRecord.LastName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LastName int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 3, PitcherRecord.OBChanceHomeRun);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceHomeRun double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 4, PitcherRecord.OBChanceTriple);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceTriple double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 5, PitcherRecord.OBChanceDouble);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceDouble double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 6, PitcherRecord.OBChanceSingle);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceSingle double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 7, PitcherRecord.OBChanceWalk);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceWalk double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 8, PitcherRecord.ChanceDoublePlay);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ChanceDoublePlay double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 9, PitcherRecord.OBChanceHomeRunRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceHomeRunRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 10, PitcherRecord.OBChanceTripleRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceTripleRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 11, PitcherRecord.OBChanceDoubleRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceDoubleRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 12, PitcherRecord.OBChanceSingleRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceSingleRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 13, PitcherRecord.OBChanceWalkRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceWalkRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 14, PitcherRecord.ChanceDoublePlayRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ChanceDoublePlayRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 15, PitcherRecord.OBChanceHomeRunLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceHomeRunLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 16, PitcherRecord.OBChanceTripleLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceTripleLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 17, PitcherRecord.OBChanceDoubleLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceDoubleLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 18, PitcherRecord.OBChanceSingleLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceSingleLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 19, PitcherRecord.OBChanceWalkLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceWalkLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 20, PitcherRecord.ChanceDoublePlayLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ChanceDoublePlayLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 21, PitcherRecord.OBChanceBasic);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceBasic double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 22, PitcherRecord.OBChanceLeft);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceLeft double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 23, PitcherRecord.OBChanceRight);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind OBChanceRight double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 24, PitcherRecord.Starter);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Starter int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 25, PitcherRecord.Relief);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Relief int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 26, PitcherRecord.Throws);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Throws int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 27, PitcherRecord.Bunting);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Bunting int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 28, PitcherRecord.Hold);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Hold int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 29, PitcherRecord.WP);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind WP int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 30, PitcherRecord.Balk);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Balk int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 31, PitcherRecord.Pitcher);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Pitcher int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 32, PitcherRecord.ER1);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ER1 int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 33, PitcherRecord.TeamID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_bind_int(m_stmt, 34, PitcherRecord.PitcherID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind PitcherID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc != SQLITE_DONE)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to Update BATTER item: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);

	return 0;
}

int CBaseballDoc::PitcherStatsUpdate(m_PitcherStatsRecord PitcherStatsRecord)
{
	char *sqlPitcher;
	int rc;
	CHAR buffer[100];

	/* Create SQL statement */
	sqlPitcher = "UPDATE PITCHERSTATS "  \
		"SET " \
		"Wins = ?1," \
		"Loss = ?2," \
		"Saves = ?3," \
		"InningsPitched = ?4," \
		"ER = ?5," \
		"Hits = ?6," \
		"Walks = ?7," \
		"Strikeouts = ?8," \
		"HomeRuns = ?9," \
		"Games = ?10," \
		"CompleteGames = ?11," \
		"Starts = ?12," \
		"ERA = ?13," \
		"WHIP = ?14," \
		"PitcherID = ?15," \
		"TeamID = ?16," \
		"LastUpdateTime = datetime('NOW','localtime')" \
		" WHERE PitcherStatsID = ?17 ";

	rc = sqlite3_prepare_v2(m_db, sqlPitcher, strlen(sqlPitcher), &m_stmt, 0);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for TEAM Select OK:\n");
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the INSERT statement
	rc = sqlite3_bind_int(m_stmt, 1, PitcherStatsRecord.Wins);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Wins int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 2, PitcherStatsRecord.Loss);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Loss int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 3, PitcherStatsRecord.Saves);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Saves int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 4, PitcherStatsRecord.InningsPitched);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind InningsPitched double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 5, PitcherStatsRecord.ER);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ER int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 6, PitcherStatsRecord.Hits);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Hits int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 7, PitcherStatsRecord.Walks);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Walks int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 8, PitcherStatsRecord.Strikeouts);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Strikeouts int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 9, PitcherStatsRecord.HomeRuns);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind HomeRuns int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 10, PitcherStatsRecord.Games);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Games int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 11, PitcherStatsRecord.CompleteGames);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind CompleteGames int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 12, PitcherStatsRecord.Starts);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Starts int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 13, PitcherStatsRecord.ERA);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ERA double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_double(m_stmt, 14, PitcherStatsRecord.WHIP);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind WHIP double: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 15, PitcherStatsRecord.PitcherID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind PitcherID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 16, PitcherStatsRecord.TeamID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind TeamID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 17, PitcherStatsRecord.PitcherStatsID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind PitcherStatsID int: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc != SQLITE_DONE)
	{
		sprintf_s(buffer, sizeof(buffer), "Failed to Update BatterStats item: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);

	return 0;
}

int CBaseballDoc::TeamInsert(m_TeamRecord TeamRecord)
{
	int rc;
	CHAR buffer[100];
	char *sqlTeam;

	/* Create SQL statement */
	sqlTeam = "INSERT INTO TEAM("  \
		"TeamName," \
		"TeamNameShort," \
		"BallparkName," \
		"HomeWins," \
		"HomeLosses," \
		"AwayWins," \
		"AwayLosses," \
		"LeagueID," \
		"ConferenceID," \
		"DivisionID," \
		"TeamYear," \
		"BaseTeam" \
		")" \
		"VALUES (" \
		"?1," \
		"?2," \
		"?3," \
		"?4," \
		"?5," \
		"?6," \
		"?7," \
		"?8," \
		"?9," \
		"?10," \
		"?11," \
		"?12" \
		");";
	rc = sqlite3_prepare_v2(m_db, sqlTeam, -1, &m_stmt, 0);
	if (rc != SQLITE_OK)
	{

		//fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		sprintf_s(buffer, sizeof(buffer), "Failed to fetch data: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Prepare for Team Insert OK: %s\n", sqlite3_errmsg(m_db));
		//AfxMessageBox(buffer);
	}
	// Bind the data to field '1' which is the first '?' in the SELECT statement
	rc = sqlite3_bind_text(m_stmt, 1, TeamRecord.TeamName, strlen(TeamRecord.TeamName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind strTeamName: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_text(m_stmt, 2, TeamRecord.TeamNameShort, strlen(TeamRecord.TeamNameShort), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind strTeamNameShort: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_text(m_stmt, 3, TeamRecord.BallparkName, strlen(TeamRecord.BallparkName), SQLITE_STATIC);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind strBallParkName: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 4, TeamRecord.HomeWins);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind HomeWins: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 5, TeamRecord.HomeLosses);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind HomeLosses: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 6, TeamRecord.AwayWins);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind AwayWins: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 7, TeamRecord.AwayLosses);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind AwayLosses: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 8, TeamRecord.LeagueID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind LeagueID: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 9, TeamRecord.ConferenceID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind ConferenceID: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 10, TeamRecord.DivisionID);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind DivisionID: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 11, TeamRecord.TeamYear);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Year: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	rc = sqlite3_bind_int(m_stmt, 12, TeamRecord.BaseTeam);
	if (rc != SQLITE_OK)
	{
		sprintf_s(buffer, sizeof(buffer), "Could not bind Base: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}

	rc = sqlite3_step(m_stmt);

	if (rc != SQLITE_DONE)
	{
		//printf("%s  %s\n", sqlite3_column_name(m_stmt, 0), sqlite3_column_text(m_stmt, 0));
		sprintf_s(buffer, sizeof(buffer), "Failed to insert item: %s\n", sqlite3_errmsg(m_db));
		AfxMessageBox(buffer);
	}
	else
	{
		sprintf_s(buffer, sizeof(buffer), "Step for Team Insert OK: %s\n", sqlite3_errmsg(m_db));
		//AfxMessageBox(buffer);
	}

	sqlite3_finalize(m_stmt);
	return 0;
}
