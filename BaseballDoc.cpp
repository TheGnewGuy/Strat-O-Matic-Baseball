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
#include "AddTeam.h"
#include "FileStruct.h"
#include "registry.h"
#include <direct.h>
#include <errno.h>

#include "BaseballDoc.h"

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
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseballDoc construction/destruction

CBaseballDoc::CBaseballDoc()
{
	// TODO: add one-time construction code here
	SetAllFormsFalse();
}

CBaseballDoc::~CBaseballDoc()
{
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

void CBaseballDoc::OnFileExportLeagueTeams() 
{
	HCURSOR hCursorWait;
	HCURSOR hCursorNormal;

	CString strLeague;
	CString strLeagueName;
	CString strLeagueFile;
	CString strLeagueDir;

	strLeague = GetLeagues(TRUE);

	strLeagueName = strLeague.Left(30);
	if (strncmp(strLeagueName,"All",3))
	{
		strLeagueFile = strLeague.Right(12);
		strLeagueDir = strLeagueFile.Left(8);
	}
	else
	{
		// This is the base directory
		strLeagueDir = "data";
	}

	hCursorWait = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
	hCursorNormal = SetCursor(hCursorWait);
	ShowCursor(TRUE);
	Export(strLeagueDir);
	ShowCursor(FALSE);
	SetCursor(hCursorNormal);
}

void CBaseballDoc::OnFileExportLeagueTeamsAll() 
{
	DlgSelLeague dlgSelLeague;
	dlgSelTeam dlgSelTeam;
	CFileFind myFileFind;
	CStringArray arrayFileNames;
	CFile myInFile;
	BYTE count;
	char temp[41];
	CString strTemp;
	CString strTeamName;
	BOOL bWorking;
	CWnd* pmyCWnd;
	int i,sortflag;
	HCURSOR hCursorWait;
	HCURSOR hCursorNormal;

	CString strLeague;
	CString strLeagueName;
	CString strLeagueFile;
	CString strLeagueDir;

	strLeague = GetLeagues(TRUE);

	strLeagueName = strLeague.Left(30);
	if (strncmp(strLeagueName,"All",3))
	{
		strLeagueFile = strLeague.Right(12);
		strLeagueDir = strLeagueFile.Left(8);
	}
	else
	{
		// This is the base directory
		strLeagueDir = "data";
	}

	hCursorWait = AfxGetApp()->LoadStandardCursor(IDC_WAIT);

	arrayFileNames.RemoveAll();
	bWorking = myFileFind.FindFile(strLeagueDir+"\\TB*.dat",0);
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
			for (i=0; i<(arrayFileNames.GetSize()-1);i++)
			{
				if (arrayFileNames[i].Compare(arrayFileNames[i+1]) == 1)
				{
					strTemp = arrayFileNames[i];
					arrayFileNames[i] = arrayFileNames[i+1];
					arrayFileNames[i+1] = strTemp;
					sortflag = 1;
				}
			}
		}

		for (i=0; i<arrayFileNames.GetSize(); i++)
		{
			myInFile.Open(strLeagueDir+"\\"+arrayFileNames[i],CFile::modeRead);
			myInFile.Read(&count,sizeof(count));
			myInFile.Read(temp,40);
			myInFile.Close();
			temp[40] = NULL;
			strTeamName = temp;
			strTeamName = strTeamName+"\t"+arrayFileNames[i];
			hCursorNormal = SetCursor(hCursorWait);
			ShowCursor(TRUE);
			ExportFile(strLeagueDir, strTeamName);
			ShowCursor(FALSE);
			SetCursor(hCursorNormal);
		}
	}
	else
	{
		// No teams found so display message
		pmyCWnd = AfxGetMainWnd();
		pmyCWnd->MessageBox("Could not find any Team files. Please create a team",
			"Teams not found!",MB_OK|MB_ICONEXCLAMATION);
	}
}

void CBaseballDoc::Export(CString strLeagueDir)
{
	CString strTeam;
	CString strTeamFile;
	CString strTeamName;

	strTeam = GetTeams(strLeagueDir);
	strTeamFile = strTeam.Right(12);
	strTeamName = strTeam.Left(30);

	ExportFile(strLeagueDir, strTeam);
}

void CBaseballDoc::ExportFile(CString strDir, CString strTeamName)
{
	BatterStruct structBatter;
	PitcherStruct structPitcher;
	BYTE count;
	CFile exportBatter;
	CFile exportPitcher;
	CString exportFileName;
	char exportData[200];
	CString strexportData;
	float fBattingAverage, fSLG, fOnBasePercentage;
	int i;
	CString strTemp;
	CString myFileName;
	LONG lTeamSection = 74;
	LONG lCountSection = 1;
	LONG lPlayerSection = structBatter.m_RecordSize;
	LONG lPitcherSection = structPitcher.m_RecordSize;
	LONG position;
	double fIP;
	double fERA;
	double fTRG;
	char Bunting[5] = {'A','B','C','D','E'};
	char HitRun[4] = {'A','B','C','D'};
	char Stealing[7] = {'3','2','A','B','C','D','E'};
	char BatterHits[3] = {'L','R','S'};
	char Power[2] = {'N','W'};
	int Running[15] = {5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
	int TRate[21] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int Pass[21] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int OutArm[12] = {-6,-5,-4,-3,-2,-1,0,1,2,3,4,5};
	int CatchArm[10] = {-4,-3,-2,-1,0,1,2,3,4,5};
	int PHold[16] = {9,8,7,6,5,4,3,2,1,0,-1,-2,-3,-4,-5,-6};

	count = 0;

	// Process Batter file
	strTemp = "XB" + strTeamName.Left(20);
	exportFileName = strDir+"\\" + strTemp+".txt"; // dir\XB000001.txt
	myFileName = strDir+"\\TB"+strTeamName.Right(10);
	exportBatter.Open(exportFileName,CFile::modeCreate | CFile::modeWrite);
	sprintf_s(exportData,"Team Name,Batter Name,,AB,Runs,Hits,RBI,2B,3B,HR,W,K,RE,");
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"SF,SB,CS,Bunting,Stealing,Running,Hit Run,LRS,P,C,");
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"1B,2B,SS,3B,LF,CF,RF,ChB,ChL,ChR,");
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"AVG,SLG,OBP,Games,HBP,");
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"Ch1B,Ch2B,Ch3B,ChHR,ChW,ChDP,");
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"Ch1BL,Ch2BL,Ch3BL,ChHRL,ChWL,ChDPL,");
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"Ch1BR,Ch2BR,Ch3BR,ChHRR,ChWR,ChDPR,");
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"ER1,ER2,ER3,ER4,ER5,ER6,ER7,ER8,ER9,");
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"T Rating,Passball,Power Left,Power Right,Outfield Arm,Catcher Arm\n");
	strexportData = exportData;
	exportBatter.Write(strexportData,strexportData.GetLength());

	// A Team was selected so export all of the players
	count = structBatter.GetCountBatter(myFileName);
	for (i=0; i<count; i++)
	{
		position = lTeamSection+(i*lPlayerSection);
		structBatter.GetBatter(myFileName, position);
		strexportData.Empty();
		if (structBatter.m_AB == 0)
		{
			fBattingAverage = 0.0f;
			fSLG = 0.0f;
			fOnBasePercentage = 0.0f;
		}
		else
		{
			fBattingAverage = (float)structBatter.m_Hits/structBatter.m_AB;
			fSLG = (float)((structBatter.m_Hits-(structBatter.m_2B+structBatter.m_3B+structBatter.m_HomeRuns))+(2*structBatter.m_2B)+(3*structBatter.m_3B)+(4*structBatter.m_HomeRuns))/(structBatter.m_AB);
			fOnBasePercentage = (float)(structBatter.m_Hits+structBatter.m_Walk+structBatter.m_ReachedOnError+structBatter.m_Sacrifice+structBatter.m_StolenBase)/(structBatter.m_AB+structBatter.m_Walk+structBatter.m_ReachedOnError+structBatter.m_Sacrifice+structBatter.m_StolenBase);
		}
		
		sprintf_s(exportData,"%s,%s,",
			strTeamName.Left(40),
			structBatter.m_PlayerName);
		strexportData = exportData;
		exportBatter.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,%i,%i,%i,%i,%i,%i,%i,%i,%i,",
			structBatter.m_AB,
			structBatter.m_Runs,
			structBatter.m_Hits,
			structBatter.m_RBI,
			structBatter.m_2B,
			structBatter.m_3B,
			structBatter.m_HomeRuns,
			structBatter.m_Walk,
			structBatter.m_StrikeOut,
			structBatter.m_ReachedOnError);
		strexportData = exportData;
		exportBatter.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,%i,%i,%c,%c,%i,%c,%c,%i,%i,",
			structBatter.m_Sacrifice,
			structBatter.m_StolenBase,
			structBatter.m_CS,
			Bunting[structBatter.m_bBunting],
			Stealing[structBatter.m_bStealing],
			Running[structBatter.m_bRunning],
			HitRun[structBatter.m_bHitRun],
			BatterHits[structBatter.m_bBatterHits],
			structBatter.m_Pitcher,
			structBatter.m_Catcher);
		strexportData = exportData;
		exportBatter.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,%i,%i,%i,%i,%i,%i,%s,%s,%s,",
			structBatter.m_FirstBase,
			structBatter.m_SecondBase,
			structBatter.m_ShortStop,
			structBatter.m_ThirdBase,
			structBatter.m_LeftField,
			structBatter.m_CenterField,
			structBatter.m_RightField,
			structBatter.m_OBChanceBasic,
			structBatter.m_OBChanceLeft,
			structBatter.m_OBChanceRight);
		strexportData = exportData;
		exportBatter.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%1.3f,%1.3f,%1.3f,",
			fBattingAverage,
			fSLG,
			fOnBasePercentage);
		strexportData = exportData;
		exportBatter.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,%i,",
			structBatter.m_Games,
			structBatter.m_HBP);
		strexportData = exportData;
		exportBatter.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%s,%s,%s,%s,%s,%s,",
			structBatter.m_OBChanceSingle,
			structBatter.m_OBChanceDouble,
			structBatter.m_OBChanceTriple,
			structBatter.m_OBChanceHomeRun,
			structBatter.m_OBChanceWalk,
			structBatter.m_ChanceDoublePlay);
		strexportData = exportData;
		exportBatter.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%s,%s,%s,%s,%s,%s,",
			structBatter.m_OBChanceSingleLeft,
			structBatter.m_OBChanceDoubleLeft,
			structBatter.m_OBChanceTripleLeft,
			structBatter.m_OBChanceHomeRunLeft,
			structBatter.m_OBChanceWalkLeft,
			structBatter.m_ChanceDoublePlayLeft);
		strexportData = exportData;
		exportBatter.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%s,%s,%s,%s,%s,%s,",
			structBatter.m_OBChanceSingleRight,
			structBatter.m_OBChanceDoubleRight,
			structBatter.m_OBChanceTripleRight,
			structBatter.m_OBChanceHomeRunRight,
			structBatter.m_OBChanceWalkRight,
			structBatter.m_ChanceDoublePlayRight);
		strexportData = exportData;
		exportBatter.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,%i,%i,%i,%i,%i,%i,%i,%i,",
			structBatter.m_bER1,
			structBatter.m_bER2,
			structBatter.m_bER3,
			structBatter.m_bER4,
			structBatter.m_bER5,
			structBatter.m_bER6,
			structBatter.m_bER7,
			structBatter.m_bER8,
			structBatter.m_bER9);
		strexportData = exportData;
		exportBatter.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,%i,%c,%c,%i,%i\n",
			TRate[structBatter.m_bTRate],
			Pass[structBatter.m_bPass],
			Power[structBatter.m_bPowerL],
			Power[structBatter.m_bPowerR],
			OutArm[structBatter.m_bOutArm],
			CatchArm[structBatter.m_bCatchArm]);
		strexportData = exportData;
		exportBatter.Write(strexportData,strexportData.GetLength());
	}
	exportBatter.Close();

	// Process Pitcher file
	strTemp = "XP" + strTeamName.Left(20);
	exportFileName = strDir+"\\" + strTemp+".txt"; // dir\XB000001.txt
	myFileName = strDir+"\\TP"+strTeamName.Right(10);
	exportPitcher.Open(exportFileName,CFile::modeCreate | CFile::modeWrite);
	sprintf_s(exportData,"Team Name,Pitcher Name,,IP,ER,Hits,Walks,Strikeouts,");
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"Homeruns,Hold,Wins,Loss,Saves,Starter,Relief,Throws,");
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"ChB,ChL,ChR,");
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"ERA,TRG,");
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"Starts,");
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"Games,Completed Games,");
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"Ch1B,Ch2B,Ch3B,ChHR,ChW,ChDP,");
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"Ch1BL,Ch2BL,Ch3BL,ChHRL,ChWL,ChDPL,");
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"Ch1BR,Ch2BR,Ch3BR,ChHRR,ChWR,ChDPR,");
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());
	sprintf_s(exportData,"Wild Pitch,Balk,Fielding,ErrorRating,Bunting\n");
	strexportData = exportData;
	exportPitcher.Write(strexportData,strexportData.GetLength());

	// A Team was selected so export all of the players
	count = structPitcher.GetCountPitcher(myFileName);
	for (i=0; i<count; i++)
	{
		position = lCountSection+(i*lPitcherSection);
		structPitcher.GetPitcher(myFileName, position);
		strexportData.Empty();
		
		fIP = atof(structPitcher.m_IP);

		if (fIP == 0)
		{
			fERA = 0;
			fTRG = 0;
		}
		else
		{
			fERA = (double)(structPitcher.m_ER*9)/fIP;
			fTRG = (double)((structPitcher.m_Hits+structPitcher.m_Walks)*9)/fIP;
		}
		
		sprintf_s(exportData,"%s,%s,",
			strTeamName.Left(40),
			structPitcher.m_PitcherName);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%1.2f,%i,%i,%i,%i,%i,%i,%i,%i,",
			fIP,
			structPitcher.m_ER,
			structPitcher.m_Hits,
			structPitcher.m_Walks,
			structPitcher.m_Strikeouts,
			structPitcher.m_HomeRuns,
			PHold[structPitcher.m_Hold],
			structPitcher.m_Wins,
			structPitcher.m_Loss);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,%i,%i,%c,%s,%s,%s,",
			structPitcher.m_Saves,
			structPitcher.m_Starter,
			structPitcher.m_Relief,
			BatterHits[structPitcher.m_Throws],
			structPitcher.m_OBChanceBasic,
			structPitcher.m_OBChanceLeft,
			structPitcher.m_OBChanceRight);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%1.2f,%1.2f,",
			fERA,
			fTRG);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,",
			structPitcher.m_Starts);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,%i,",
			structPitcher.m_Games,structPitcher.m_CompGames);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%s,%s,%s,%s,%s,%s,",
			structPitcher.m_OBChanceSingle,
			structPitcher.m_OBChanceDouble,
			structPitcher.m_OBChanceTriple,
			structPitcher.m_OBChanceHomeRun,
			structPitcher.m_OBChanceWalk,
			structPitcher.m_ChanceDoublePlay);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%s,%s,%s,%s,%s,%s,",
			structPitcher.m_OBChanceSingleLeft,
			structPitcher.m_OBChanceDoubleLeft,
			structPitcher.m_OBChanceTripleLeft,
			structPitcher.m_OBChanceHomeRunLeft,
			structPitcher.m_OBChanceWalkLeft,
			structPitcher.m_ChanceDoublePlayLeft);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%s,%s,%s,%s,%s,%s,",
			structPitcher.m_OBChanceSingleRight,
			structPitcher.m_OBChanceDoubleRight,
			structPitcher.m_OBChanceTripleRight,
			structPitcher.m_OBChanceHomeRunRight,
			structPitcher.m_OBChanceWalkRight,
			structPitcher.m_ChanceDoublePlayRight);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
		sprintf_s(exportData,"%i,%i,%i,%i,%c\n",
			structPitcher.m_bWP,
			structPitcher.m_bBalk,
			structPitcher.m_PitcherField,
			structPitcher.m_bER1,
			Bunting[structPitcher.m_Bunting]);
		strexportData = exportData;
		exportPitcher.Write(strexportData,strexportData.GetLength());
	}
	exportPitcher.Close();
}

void CBaseballDoc::OnFileExportHTMLLeagueTeams() 
{
	CString strLeague;
	CString strLeagueName;
	CString strLeagueFile;
	CString strLeagueDir;

	strLeague = GetLeagues(TRUE);

	strLeagueName = strLeague.Left(30);
	if (strncmp(strLeagueName,"All",3))
	{
		strLeagueFile = strLeague.Right(12);
		strLeagueDir = strLeagueFile.Left(8);
	}
	else
	{
		// This is the base directory
		strLeagueDir = "data";
	}
	ExportHTML(strLeagueDir);
}

void CBaseballDoc::OnFileExportHtmlLeagueTeamsAll() 
{
	CFileFind myFileFind;
	CStringArray arrayFileNames;
	CFile myInFile;
	BYTE count;
	char temp[41];
	CString strTemp;
	CString strTeamName;
	BOOL bWorking;
	int i,sortflag;
	HCURSOR hCursorWait;
	HCURSOR hCursorNormal;

	CString strLeague;
	CString strLeagueName;
	CString strLeagueFile;
	CString strLeagueDir;

	strLeague = GetLeagues(TRUE);

	strLeagueName = strLeague.Left(30);
	if (strncmp(strLeagueName,"All",3))
	{
		strLeagueFile = strLeague.Right(12);
		strLeagueDir = strLeagueFile.Left(8);
	}
	else
	{
		// This is the base directory
		strLeagueDir = "data";
	}

	// Start of findfile code for teams
	arrayFileNames.RemoveAll();
	bWorking = myFileFind.FindFile(strLeagueDir+"\\TB*.dat",0);
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
			for (i=0; i<(arrayFileNames.GetSize()-1);i++)
			{
				if (arrayFileNames[i].Compare(arrayFileNames[i+1]) == 1)
				{
					strTemp = arrayFileNames[i];
					arrayFileNames[i] = arrayFileNames[i+1];
					arrayFileNames[i+1] = strTemp;
					sortflag = 1;
				}
			}
		}

		hCursorWait = AfxGetApp()->LoadStandardCursor(IDC_WAIT);
		for (i=0; i<arrayFileNames.GetSize(); i++)
		{
			myInFile.Open(strLeagueDir+"\\"+arrayFileNames[i],CFile::modeRead);
			myInFile.Read(&count,sizeof(count));
			myInFile.Read(temp,40);
			myInFile.Close();
			temp[40] = NULL;
			strTeamName = temp;
			strTeamName = strTeamName+"\t"+arrayFileNames[i];
			hCursorNormal = SetCursor(hCursorWait);
			ShowCursor(TRUE);
			ExportHTMLFile(strLeagueDir, strTeamName);
			ShowCursor(FALSE);
			SetCursor(hCursorNormal);
		}
	}
	else
	{
		// No teams found so display message
		AfxMessageBox("Could not find any Team files. Please create a team");
	}
}

void CBaseballDoc::ExportHTML(CString strDir)
{
	BOOL bWorking;
	char temp[41];
	BYTE count;
	CString strTeamName;
	CString strTemp;
	CFile myInFile;
	BatterStruct structBatter;
	PitcherStruct structPitcher;
	dlgSelTeam dlgSelTeam;
	CFileFind myFileFind;
	CStringArray arrayFileNames;
	int sortflag;
	int i;
	CWnd* pmyCWnd;

	bWorking = myFileFind.FindFile(strDir+"\\TB*.dat",0);
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
			for (i=0; i<(arrayFileNames.GetSize()-1);i++)
			{
				if (arrayFileNames[i].Compare(arrayFileNames[i+1]) == 1)
				{
					strTemp = arrayFileNames[i];
					arrayFileNames[i] = arrayFileNames[i+1];
					arrayFileNames[i+1] = strTemp;
					sortflag = 1;
				}
			}
		}

		for (i=0; i<arrayFileNames.GetSize(); i++)
		{
			myInFile.Open(strDir+"\\"+arrayFileNames[i],CFile::modeRead);
			myInFile.Read(&count,sizeof(count));
			myInFile.Read(temp,40);
			myInFile.Close();
			temp[40] = NULL;
			strTeamName = temp;
			strTeamName = strTeamName+"\t"+arrayFileNames[i];
			dlgSelTeam.m_arrayTeams.Add(strTeamName);
		}


		if (dlgSelTeam.DoModal() == IDOK)
		{
			strTeamName = dlgSelTeam.m_arrayTeams[0];
			ExportHTMLFile(strDir, strTeamName);
		}
	}
	else
	{
		// No teams found so display message
		pmyCWnd = AfxGetMainWnd();
		pmyCWnd->MessageBox("Could not find any Team files. Please create a team",
			"Teams not found!",MB_OK|MB_ICONEXCLAMATION);
	}
}

void CBaseballDoc::ExportHTMLFile(CString strDir, CString strTeamName)
{
	BYTE count;
	char HTMLData[200];
	CString HTMLFileName;
	CString strHTMLData;
	CString myFileName;
	CString strTemp;
	CString strHTML;
	CString strTempHTML;
	CFile HTMLPlayer;
	BatterStruct structBatter;
	PitcherStruct structPitcher;
	LONG lTeamSection = 74;
	LONG lCountSection = 1;
	LONG lPlayerSection = structBatter.m_RecordSize;
	LONG lPitcherSection = structPitcher.m_RecordSize;
	LONG position;
	dlgSelTeam dlgSelTeam;
	CFileFind myFileFind;
	CStringArray arrayFileNames;
	int i,j;
	float fBattingAverage, fSLG, fOnBasePercentage;
	double fIP;
	double fERA;
	double fTRG;
	int *aiCount,tiCount;
	int *aiAB,tiAB;
	float *afBA,tfBA;
	double *adERA,tdERA;
	double *adIP,tdIP;
	char datebuf[9],timebuf[9];
	CString strIndex;
	CString strBackgroundPicture;
	CString strLinkColor;
	CString strVLinkColor;
	CString strBGColor;
	CString strTextColor;

	Registry myReg(strDir + REGTEAMS);

	strLinkColor	= myReg.GetRegistryOptionLinkColor();
	strVLinkColor	= myReg.GetRegistryOptionVLinkColor();
	strBGColor		= myReg.GetRegistryOptionBGColor();
	strTextColor	= myReg.GetRegistryOptionTextColor();
	strIndex		= myReg.GetRegistryOptionIndex();
	strBackgroundPicture = myReg.GetRegistryOptionBackgroundPicture();

	// Process Batter file
	strTemp = "XB" + strTeamName.Left(20);
	strTempHTML = strTeamName.Left(20);
	strHTML.Empty();
	for (i=0; i<20; i++)
	{
		if (strTempHTML.GetAt(i) != ' ')
			strHTML += strTempHTML.GetAt(i);
	}
	HTMLFileName = strDir+"\\" + strHTML+".htm"; // dir\team.htm
	myFileName = strDir+"\\TB"+strTeamName.Right(10);
	HTMLPlayer.Open(HTMLFileName,CFile::modeCreate | CFile::modeWrite);
	sprintf_s(HTMLData,"<HTML>\n<HEAD>\n<TITLE>%s</TITLE>\n</HEAD>\n",
		strTeamName.Left(40));
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<BODY TEXT=%s LINK=%s VLINK=%s BGCOLOR=%s BACKGROUND=\"%s\">\n",
		strTextColor,strLinkColor,strVLinkColor,strBGColor,strBackgroundPicture);
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<H2>%s</H2>\n",strTeamName.Left(40));
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<A href=\"%s\">Back</A><BR><BR>\n",strIndex);
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TABLE BORDER>\n<TR>\n");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = LEFT><B>Batter</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>AB</B></TD>");
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
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>OB%</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"</TR>\n");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	// Insert table below here

	// A Team was selected so export all of the players
	count = structBatter.GetCountBatter(myFileName);

	afBA = (float *)calloc( count, sizeof( float ) );
	memset( afBA, '\0', count*sizeof( float ) );
	aiAB = (int *)calloc( count, sizeof( int ) );
	memset( aiAB, '\0', count*sizeof( int ) );
	aiCount = (int *)calloc( count, sizeof( int ) );
	memset( aiCount, '\0', count*sizeof( int ) );
	// Fill arrays for count, era and ip
	for (i=0; i<count; i++)
	{
		position = lTeamSection+(i*lPlayerSection);
		structBatter.GetBatter(myFileName, position);
		strHTMLData.Empty();
		aiCount[i] = i;		
	
		aiAB[i] = structBatter.m_AB;
		if (aiAB[i] == 0)
		{
			afBA[i] = 0.0f;
		}
		else
		{
			afBA[i] = (float)structBatter.m_Hits/aiAB[i];
		}
	}
	// Sort at bats then batting average
	for (i=0; i<count; i++)
	{
		for (j=0; j<count-1; j++)
		{
			if ( aiAB[j] < aiAB[j+1])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
				tiAB = aiAB[j];
				aiAB[j] = aiAB[j+1];
				aiAB[j+1] = tiAB;
				tfBA = afBA[j];
				afBA[j] = afBA[j+1];
				afBA[j+1] = tfBA;
			}
		}
	}
	for (i=0; i<count; i++)
	{
		for (j=0; j<count-1; j++)
		{
			if ( afBA[j] < afBA[j+1])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
				tiAB = aiAB[j];
				aiAB[j] = aiAB[j+1];
				aiAB[j+1] = tiAB;
				tfBA = afBA[j];
				afBA[j] = afBA[j+1];
				afBA[j+1] = tfBA;
			}
		}
	}

	for (i=0; i<count; i++)
	{
		position = lTeamSection+(aiCount[i]*lPlayerSection);
		structBatter.GetBatter(myFileName, position);
		strHTMLData.Empty();
		if (structBatter.m_AB == 0)
		{
			fBattingAverage = 0.0f;
			fSLG = 0.0f;
			fOnBasePercentage = 0.0f;
		}
		else
		{
			fBattingAverage = (float)structBatter.m_Hits/structBatter.m_AB;
			fSLG = (float)((structBatter.m_Hits-(structBatter.m_2B+structBatter.m_3B+structBatter.m_HomeRuns))+(2*structBatter.m_2B)+(3*structBatter.m_3B)+(4*structBatter.m_HomeRuns))/(structBatter.m_AB);
			fOnBasePercentage = (float)(structBatter.m_Hits+structBatter.m_Walk+structBatter.m_ReachedOnError+structBatter.m_Sacrifice+structBatter.m_StolenBase)/(structBatter.m_AB+structBatter.m_Walk+structBatter.m_ReachedOnError+structBatter.m_Sacrifice+structBatter.m_StolenBase);
		}

		sprintf_s(HTMLData,"<TR>");
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%s</TD>",
			structBatter.m_PlayerName);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structBatter.m_AB);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structBatter.m_Runs);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structBatter.m_Hits);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structBatter.m_RBI);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structBatter.m_2B);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structBatter.m_3B);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structBatter.m_HomeRuns);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structBatter.m_Walk);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structBatter.m_StrikeOut);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structBatter.m_ReachedOnError);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD><TD>%i</TD>",
			structBatter.m_CS,
			structBatter.m_StolenBase);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%1.3f</TD>",
			fBattingAverage);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%1.3f</TD>",
			fSLG);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%1.3f</TD>",
			fOnBasePercentage);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"</TR>\n");
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	}
	sprintf_s(HTMLData,"</TABLE>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<BR><BR><TABLE BORDER>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	free(afBA);
	free(aiAB);
	free(aiCount);

	// Process Pitcher file
	strTemp = "XP" + strTeamName.Left(20);
	myFileName = strDir+"\\TP"+strTeamName.Right(10);
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
	sprintf_s(HTMLData,"<TD ALIGN = CENTER><B>TRG</B></TD>");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"</TR>\n");
	strHTMLData = HTMLData;
	HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());

	// A Team was selected so export a players
	count = structPitcher.GetCountPitcher(myFileName);

	adERA = (double *)calloc( count, sizeof( double ) );
	memset( adERA, '\0', count*sizeof( double ) );
	adIP = (double *)calloc( count, sizeof( double ) );
	memset( adIP, '\0', count*sizeof( double ) );
	aiCount = (int *)calloc( count, sizeof( int ) );
	memset( aiCount, '\0', count*sizeof( int ) );
	// Fill arrays for count, era and ip
	for (i=0; i<count; i++)
	{
		position = lCountSection+(i*lPitcherSection);
		structPitcher.GetPitcher(myFileName, position);
		strHTMLData.Empty();
		aiCount[i] = i;		
		adIP[i] = atof(structPitcher.m_IP);
		if (adIP[i] == 0)
		{
			adERA[i] = 0;
		}
		else
		{
			adERA[i] = (double)(structPitcher.m_ER*9)/adIP[i];
		}
	}
	// Sort innings pitched and ERA
	for (i=0; i<count; i++)
	{
		for (j=0; j<count-1; j++)
		{
			if ( adIP[j] > adIP[j+1])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
				tdERA = adERA[j];
				adERA[j] = adERA[j+1];
				adERA[j+1] = tdERA;
				tdIP = adIP[j];
				adIP[j] = adIP[j+1];
				adIP[j+1] = tdIP;
			}
		}
	}
	for (i=0; i<count; i++)
	{
		for (j=0; j<count-1; j++)
		{
			if ( adERA[j] > adERA[j+1])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
				tdERA = adERA[j];
				adERA[j] = adERA[j+1];
				adERA[j+1] = tdERA;
				tdIP = adIP[j];
				adIP[j] = adIP[j+1];
				adIP[j+1] = tdIP;
			}
		}
	}

	for (i=0; i<count; i++)
	{
		position = lCountSection+(aiCount[i]*lPitcherSection);
		structPitcher.GetPitcher(myFileName, position);
		strHTMLData.Empty();
	
		fIP = atof(structPitcher.m_IP);

		if (fIP == 0)
		{
			fERA = 0;
			fTRG = 0;
		}
		else
		{
			fERA = (double)(structPitcher.m_ER*9)/fIP;
			fTRG = (double)((structPitcher.m_Hits+structPitcher.m_Walks)*9)/fIP;
		}
		
		sprintf_s(HTMLData,"<TR><TD>%s</TD>",
			structPitcher.m_PitcherName);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%1.2f</TD>",
			fIP);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structPitcher.m_ER);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structPitcher.m_Hits);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structPitcher.m_Walks);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structPitcher.m_Strikeouts);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structPitcher.m_HomeRuns);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structPitcher.m_Starts);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structPitcher.m_Wins);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structPitcher.m_Loss);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%i</TD>",
			structPitcher.m_Saves);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%1.2f</TD>",
			fERA);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"<TD>%1.2f</TD>",
			fTRG);
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
		sprintf_s(HTMLData,"</TR>\n");
		strHTMLData = HTMLData;
		HTMLPlayer.Write(strHTMLData,strHTMLData.GetLength());
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
	free(adERA);
	free(adIP);
	free(aiCount);
}

void CBaseballDoc::OnTeamsEditLeagueTeams() 
{
	// TODO: Add your command handler code here
	DlgSelLeague dlgSelLeague;
	CFileFind myFileFind;
	CStringArray arrayFileNames;
	CFile myInFile;
	CString strLeague;
	CString strLeagueName;
	CString strLeagueFile;
	CString strLeagueDir;

	strLeague = GetLeagues(TRUE);

	strLeagueName = strLeague.Left(30);
	if (strncmp(strLeagueName,"All",3))
	{
		strLeagueFile = strLeague.Right(12);
		strLeagueDir = strLeagueFile.Left(8);
	}
	else
	{
		strLeagueDir = "data";
	}

	EditTeams(strLeagueDir);
}

void CBaseballDoc::EditTeams(CString strLeagueDir)
{
	EditTeam dlg;
	CFile myFileBatter;
	BYTE count;
	CString strTeam;
	CString strTeamFile;
	CString strTeamName;
	CString strShortTeamName;
	CString strBallPark;
	CString filler10("          ");
	CString strFileNameBatter;
	char temp[41];

	strTeam = GetTeams(strLeagueDir);
	strTeamFile = strTeam.Right(12);
	strTeamName = strTeam.Left(30);

	// Process Batter file
	strFileNameBatter = strLeagueDir+"\\TB"+strTeamFile.Right(10);
	myFileBatter.Open(strFileNameBatter, CFile::modeReadWrite);
	myFileBatter.Read(&count,sizeof(count));
	myFileBatter.Read(temp,40);	// Team Name
	temp[40] = NULL;
	dlg.m_TeamName = temp;
	myFileBatter.Read(temp,3);	// Short Team Name
	temp[3] = NULL;
	dlg.m_ShortTeamName = temp;
	myFileBatter.Read(temp,30);	// Ballpark Name
	temp[30] = NULL;
	dlg.m_BallPark = temp;
	if (dlg.DoModal() == IDOK)
	{
		// Update the Batter file with team name, Short name, and Ballpark
		strTeamName = dlg.m_TeamName+filler10+filler10+filler10+filler10;
		strShortTeamName = dlg.m_ShortTeamName;
		strBallPark = dlg.m_BallPark;
		// skip counter field and write data
		myFileBatter.Seek((long)sizeof(count),CFile::begin);
		myFileBatter.Write(strTeamName, 40);
		myFileBatter.Write(strShortTeamName, 3);
		myFileBatter.Write(strBallPark, 30);
	}
	myFileBatter.Close();
}

void CBaseballDoc::OnStatisticsHTMLLeagueStats() 
{
	CString strLeague;
	CString strLeagueName;
	CString strLeagueFile;
	CString strLeagueDir;

	strLeague = GetLeagues(FALSE);

	strLeagueName = strLeague.Left(30);
	if (strncmp(strLeagueName,"All",3))
	{
		strLeagueFile = strLeague.Right(12);
		strLeagueDir = strLeagueFile.Left(8);
		HTMLLeagueStats(strLeague);
	}
	else
	{
		// This is the base directory
		AfxMessageBox("The Base directory can not be selected. Please Select a League Directory");
	}

}

void CBaseballDoc::HTMLLeagueStats(CString strLeague)
{
	// strLeague contains
	// Left 30 League name
	// Right 12 File name L0000001.dat
	CString strLeagueDir;
	CString strLeagueName;
	CString strLeagueFile;
	CString strTeamFileName;
	CString strDivisionName;
	CString strConferenceName;
	CString strTemp;
	CStringArray* arrayFileNames = new CStringArray;
	CFile LeagueFile;
	BYTE version;
	BYTE NumDiv;
	BYTE NumConf;
	BYTE NumTeams;
	short HomeWin,HomeLoss,AwayWin,AwayLoss;
	char temp[41];
	int iDiv,iConf,iTeam;

	strLeagueName = strLeague.Left(30);
	strLeagueFile = strLeague.Right(12);
	strLeagueDir = strLeagueFile.Left(8);
	LeagueFile.Open("data\\"+strLeagueFile,CFile::modeRead);
	LeagueFile.Read(&version,sizeof(version));
	LeagueFile.Read(&NumConf,sizeof(NumConf));
	LeagueFile.Read(temp,30);		// League Name
	temp[30] = NULL;
	strLeagueName = temp;

	for (iConf=0; iConf<NumConf; iConf++)
	{
		LeagueFile.Read(&NumDiv,sizeof(NumDiv));
		LeagueFile.Read(temp,30);		// Conference Name
		temp[30] = NULL;
		strConferenceName = temp;
		for (iDiv=0; iDiv<NumDiv; iDiv++)
		{
			LeagueFile.Read(&NumTeams,sizeof(NumTeams));
			LeagueFile.Read(temp,30);		// Division Name
			temp[30] = NULL;
			strDivisionName = temp;
			arrayFileNames->RemoveAll();
			for (iTeam=0; iTeam<NumTeams; iTeam++)
			{
				LeagueFile.Read(temp,40);		// Team Name
				LeagueFile.Read(temp,8);		// Team File
				temp[8] = NULL;
				strTemp = temp;
				strTeamFileName = strLeagueDir + "\\" + strTemp + ".dat";
				arrayFileNames->Add(strTeamFileName);
				LeagueFile.Read(temp,3);		// Short Team Name Name
				LeagueFile.Read(temp,20);		// Ballpark (Field should be 30 not used)
				LeagueFile.Read(&HomeWin,sizeof(HomeWin));		// Home Wins
				LeagueFile.Read(&HomeLoss,sizeof(HomeLoss));	// Home Loss
				LeagueFile.Read(&AwayWin,sizeof(AwayWin));		// Away Wins
				LeagueFile.Read(&AwayLoss,sizeof(AwayLoss));	// Away Loss
			}
			BuildPlayerArray(arrayFileNames,strLeagueName,strDivisionName,strConferenceName,iDiv);
		}
	}
	LeagueFile.Close();
	delete arrayFileNames;
}

void CBaseballDoc::BuildPlayerArray(CStringArray* arrayFileNames, CString strLeagueName, CString strDivisionName, CString strConferenceName, int iDiv)
{
	// An array of the file names is passed
	// L0000002\TB000001.dat
	int arrayFileNamesSize;
	int iarraySize;
	CFile TeamFile;
	CFile PitcherFile;
	CFile HTMLFile;
	BYTE count;
	CStringArray cstrPlayerName;
	CStringArray cstrPitcherName;
	CStringArray cstrShortTeamName;
	CStringArray cstrShortTeamNameP;
	CStringArray cstrTeamData;
	CStringArray cstrTeamPData;
	CStringArray cstr1,cstr2,cstr3;
	CStringArray cstrTemp1,cstrTemp2,cstrTemp3;
	CString strPitcherFileName;
	CString strShortTeamName;
	CString strTeamName;
	CString strTemp;
	CString strTeamData;
	CString strAVG,strSLG,strOBP;
	CString strERA,strTRG,strIP;
	CString str20Blank("                    ");
	char temp[41];
	int commafind;
	int *aiCount,tiCount,*aiPCount,*aiTCount;
	int *aiAB,*aiRuns,*aiHits,*aiRBI,*ai2B,*ai3B,*aiHR,*aiStolenBase,*aiCS;
	int *aiStrikeOut,*aiWalk;
	int iAB,iRuns,iHits,iRBI,i2B,i3B,iHR,iStolenBase,iCS,iWalk,iROE,iSacrifice;
	int iTAB,iTRuns,iTHits,iTRBI,iT2B,iT3B,iTHR,iTStolenBase,iTCS,iTWalk,iTROE,iTSacrifice;
	int iPER,iPHits,iPWalks,iPK,iPWins,iPLoss,iPStarts,iPSaves,iPHR;
	int iTPER,iTPHits,iTPWalks,iTPK,iTPWins,iTPLoss,iTPStarts,iTPSaves,iTPHR;
	int *aiPER,*aiPHits,*aiPWalks,*aiPK,*aiPWins,*aiPLoss,*aiPStarts,*aiPSaves,*aiPHR;
	float *afBA,*afSLG,*afOBP,*afTBA;
	float fBA,fSLG,fOBP;
	float fTBA,fTSLG,fTOBP;
	float *adERA,*adIP,*adTRG,*adTERA;
	double dERA,dIP,dTRG,dTemp;
	double dTERA,dTIP,dTTRG;
	int totCount = 0;
	int totPCount = 0;
	int i,ii,iii,j;
	int getSize1,getSize2,getSize3,getSizeMax;
	LONG position;
	LONG lCountSection = 1;
	LONG lTeamSection = 74;
	BatterStruct structBatter;
	PitcherStruct structPitcher;
	LONG lPlayerSection = structBatter.m_RecordSize;
	LONG lPitcherSection = structPitcher.m_RecordSize;
	char HTMLData[200];
	CString strHTMLData;
	char datebuf[9],timebuf[9];
	CString strIndex;
	CString strBackgroundPicture;
	CString strLinkColor;
	CString strVLinkColor;
	CString strBGColor;
	CString strTextColor;
	CString strDir;

	strDir = arrayFileNames->GetAt(0).Left(8);
	Registry myReg(strDir + REGLEAGUE);

	strLinkColor	= myReg.GetRegistryOptionLinkColor();
	strVLinkColor	= myReg.GetRegistryOptionVLinkColor();
	strBGColor		= myReg.GetRegistryOptionBGColor();
	strTextColor	= myReg.GetRegistryOptionTextColor();
	strIndex		= myReg.GetRegistryOptionIndex();
	strBackgroundPicture = myReg.GetRegistryOptionBackgroundPicture();

	m_StatCount = HTML_DISP_LINES;	// Counter for number of lines to be displayed

	arrayFileNamesSize = arrayFileNames->GetSize();
	for (iarraySize=0; iarraySize < arrayFileNamesSize; iarraySize++)
	{
		count = structBatter.GetCountBatter(arrayFileNames->GetAt(iarraySize));
		totCount += count;
		strPitcherFileName = arrayFileNames->GetAt(iarraySize);
		strPitcherFileName.SetAt(10,'P');
		count = structPitcher.GetCountPitcher(strPitcherFileName);
		totPCount += count;
	}
	cstrPlayerName.RemoveAll();
	aiCount = (int *)calloc( totCount, sizeof( int ) );
	memset( aiCount, '\0', totCount*sizeof( int ) );
	aiPCount = (int *)calloc( totPCount, sizeof( int ) );
	memset( aiPCount, '\0', totPCount*sizeof( int ) );
	aiTCount = (int *)calloc( arrayFileNamesSize, sizeof( int ) );
	memset( aiTCount, '\0', arrayFileNamesSize*sizeof( int ) );
	aiAB = (int *)calloc( totCount, sizeof( int ) );
	memset( aiAB, '\0', totCount*sizeof( int ) );
	aiRuns = (int *)calloc( totCount, sizeof( int ) );
	memset( aiRuns, '\0', totCount*sizeof( int ) );
	aiHits = (int *)calloc( totCount, sizeof( int ) );
	memset( aiHits, '\0', totCount*sizeof( int ) );
	aiRBI = (int *)calloc( totCount, sizeof( int ) );
	memset( aiRBI, '\0', totCount*sizeof( int ) );
	ai2B = (int *)calloc( totCount, sizeof( int ) );
	memset( ai2B, '\0', totCount*sizeof( int ) );
	ai3B = (int *)calloc( totCount, sizeof( int ) );
	memset( ai3B, '\0', totCount*sizeof( int ) );
	aiHR = (int *)calloc( totCount, sizeof( int ) );
	memset( aiHR, '\0', totCount*sizeof( int ) );
	afBA = (float *)calloc( totCount, sizeof( float ) );
	memset( afBA, '\0', totCount*sizeof( float ) );
	afTBA = (float *)calloc( totCount, sizeof( float ) );
	memset( afTBA, '\0', totCount*sizeof( float ) );
	afSLG = (float *)calloc( totCount, sizeof( float ) );
	memset( afSLG, '\0', totCount*sizeof( float ) );
	afOBP = (float *)calloc( totCount, sizeof( float ) );
	memset( afOBP, '\0', totCount*sizeof( float ) );
	aiStolenBase = (int *)calloc( totCount, sizeof( int ) );
	memset( aiStolenBase, '\0', totCount*sizeof( int ) );
	aiCS = (int *)calloc( totCount, sizeof( int ) );
	memset( aiCS, '\0', totCount*sizeof( int ) );
	aiStrikeOut = (int *)calloc( totCount, sizeof( int ) );
	memset( aiStrikeOut, '\0', totCount*sizeof( int ) );
	aiWalk = (int *)calloc( totCount, sizeof( int ) );
	memset( aiWalk, '\0', totCount*sizeof( int ) );
	adERA = (float *)calloc( totPCount, sizeof( float ) );
	memset( adERA, '\0', totPCount*sizeof( float ) );
	adTERA = (float *)calloc( totPCount, sizeof( float ) );
	memset( adTERA, '\0', totPCount*sizeof( float ) );
	adTRG = (float *)calloc( totPCount, sizeof( float ) );
	memset( adTRG, '\0', totPCount*sizeof( float ) );
	adIP = (float *)calloc( totPCount, sizeof( float ) );
	memset( adIP, '\0', totPCount*sizeof( float ) );
	aiPER = (int *)calloc( totPCount, sizeof( int ) );
	memset( aiPER, '\0', totPCount*sizeof( int ) );
	aiPHits = (int *)calloc( totPCount, sizeof( int ) );
	memset( aiPHits, '\0', totPCount*sizeof( int ) );
	aiPWalks = (int *)calloc( totPCount, sizeof( int ) );
	memset( aiPWalks, '\0', totPCount*sizeof( int ) );
	aiPK = (int *)calloc( totPCount, sizeof( int ) );
	memset( aiPK, '\0', totPCount*sizeof( int ) );
	aiPWins = (int *)calloc( totPCount, sizeof( int ) );
	memset( aiPWins, '\0', totPCount*sizeof( int ) );
	aiPLoss = (int *)calloc( totPCount, sizeof( int ) );
	memset( aiPLoss, '\0', totPCount*sizeof( int ) );
	aiPStarts = (int *)calloc( totPCount, sizeof( int ) );
	memset( aiPStarts, '\0', totPCount*sizeof( int ) );
	aiPSaves = (int *)calloc( totPCount, sizeof( int ) );
	memset( aiPSaves, '\0', totPCount*sizeof( int ) );
	aiPHR = (int *)calloc( totPCount, sizeof( int ) );
	memset( aiPHR, '\0', totPCount*sizeof( int ) );

	// Fill arrays for count
	for (i=0; i<totCount; i++)
		aiCount[i] = i;
	for (i=0; i<totPCount; i++)
		aiPCount[i] = i;
	for (i=0; i<arrayFileNamesSize; i++)
		aiTCount[i] = i;
	iTAB=iTRuns=iTHits=iTRBI=iT2B=iT3B=iTHR=iTStolenBase=iTCS=iTWalk=iTROE=iTSacrifice=0;
	fTBA=fTOBP=fTSLG=0.0f;
	iTPER=iTPHits=iTPWalks=iTPK=iTPWins=iTPLoss=iTPStarts=iTPSaves=iTPHR=0;
	dTIP=dTTRG=dTERA=0.0f;
	ii = 0;
	iii = 0;
	// Process all teams in division
	for (iarraySize=0; iarraySize < arrayFileNamesSize; iarraySize++)
	{
		// L0000002\TB000001.dat Player file
		// Set up Pitcher File
		strPitcherFileName = arrayFileNames->GetAt(iarraySize);
		strPitcherFileName.SetAt(10,'P');
		// Open Batter file
		TeamFile.Open(arrayFileNames->GetAt(iarraySize), CFile::modeRead);
		TeamFile.Read(&count,sizeof(count));
		TeamFile.Read(temp,40);		// Team Name
		temp[40] = NULL;
		strTeamName = temp;
		TeamFile.Read(temp,3);		// Short Team Name
		temp[3] = NULL;
		strShortTeamName = temp;
		TeamFile.Close();
		iAB=iRuns=iHits=iRBI=i2B=i3B=iHR=iStolenBase=iCS=iWalk=iROE=iSacrifice=0;
		iPER=iPHits=iPWalks=iPK=iPWins=iPLoss=iPStarts=iPSaves=iPHR=0;
		dIP=dTRG=dERA=0.0f;
		// Process all batters in file
		for (i=0; i<count; i++)
		{
			position = lTeamSection+(i*lPlayerSection);
			structBatter.GetBatter(arrayFileNames->GetAt(iarraySize), position);
			cstrShortTeamName.Add(strShortTeamName);
			commafind = structBatter.m_PlayerName.Find(',');
			strTemp.Empty();
			strTemp	= structBatter.m_PlayerName.GetAt(commafind+2);
			strTemp	+= ".";
			strTemp	+= structBatter.m_PlayerName.Left(commafind);
			strTemp	+= str20Blank;
			strTemp	+= str20Blank;
			cstrPlayerName.Add(strTemp);
			aiAB[ii]	= structBatter.m_AB;
			aiCS[ii]	= structBatter.m_CS;
			aiHits[ii]	= structBatter.m_Hits;
			ai2B[ii]	= structBatter.m_2B;
			ai3B[ii]	= structBatter.m_3B;
			aiHR[ii]	= structBatter.m_HomeRuns;
			aiRBI[ii]	= structBatter.m_RBI;
			aiRuns[ii]	= structBatter.m_Runs;
			aiStolenBase[ii] = structBatter.m_StolenBase;
			aiStrikeOut[ii]	= structBatter.m_StrikeOut;
			aiWalk[ii]	= structBatter.m_Walk;
			iAB			+= structBatter.m_AB;
			iCS			+= structBatter.m_CS;
			iHits		+= structBatter.m_Hits;
			i2B			+= structBatter.m_2B;
			i3B			+= structBatter.m_3B;
			iHR			+= structBatter.m_HomeRuns;
			iRBI		+= structBatter.m_RBI;
			iROE		+= structBatter.m_ReachedOnError;
			iRuns		+= structBatter.m_Runs;
			iSacrifice	+= structBatter.m_Sacrifice;
			iStolenBase	+= structBatter.m_StolenBase;
			iWalk		+= structBatter.m_Walk;
			if (structBatter.m_AB == 0)
			{
				afBA[ii]	= 0.0f;
				afSLG[ii]	= 0.0f;
				afOBP[ii]	= 0.0f;
			}
			else
			{
				afBA[ii]	= (float)structBatter.m_Hits/structBatter.m_AB;
				afSLG[ii]	= (float)((structBatter.m_Hits-(structBatter.m_2B+structBatter.m_3B+structBatter.m_HomeRuns))+(2*structBatter.m_2B)+(3*structBatter.m_3B)+(4*structBatter.m_HomeRuns))/(structBatter.m_AB);
				afOBP[ii]	= (float)(structBatter.m_Hits+structBatter.m_Walk+structBatter.m_ReachedOnError+structBatter.m_Sacrifice+structBatter.m_StolenBase)/(structBatter.m_AB+structBatter.m_Walk+structBatter.m_ReachedOnError+structBatter.m_Sacrifice+structBatter.m_StolenBase);
				fBA		= (float)iHits/iAB;
				fSLG	= (float)((iHits-(i2B+i3B+iHR))+(2*i2B)+(3*i3B)+(4*iHR))/(iAB);
				fOBP	= (float)(iHits+iWalk+iROE+iSacrifice+iStolenBase)/(iAB+iWalk+iROE+iSacrifice+iStolenBase);
			}
			ii++;
		}	// End of batter processing

		// Open Pitcher file to get count
		count = structPitcher.GetCountPitcher(strPitcherFileName);

		// Fill arrays for count, era and ip
		for (i=0; i<count; i++)
		{
			position = lCountSection+(i*lPitcherSection);
			structPitcher.GetPitcher(strPitcherFileName, position);
			strHTMLData.Empty();

			commafind = structPitcher.m_PitcherName.Find(',');
			strTemp.Empty();
			strTemp = structPitcher.m_PitcherName.GetAt(commafind+2);
			strTemp += ".";
			strTemp += structPitcher.m_PitcherName.Left(commafind);
			strTemp += str20Blank;
			strTemp += str20Blank;
			cstrPitcherName.Add(strTemp);
			cstrShortTeamNameP.Add(strShortTeamName);
			aiPER[iii]		= structPitcher.m_ER;
			aiPHits[iii]	= structPitcher.m_Hits;
			aiPHR[iii]		= structPitcher.m_HomeRuns;
			adIP[iii]		= (float)atof(structPitcher.m_IP);
			aiPLoss[iii]	= structPitcher.m_Loss;
			aiPSaves[iii]	= structPitcher.m_Saves;
			aiPStarts[iii]	= structPitcher.m_Starts;
			aiPK[iii]		= structPitcher.m_Strikeouts;
			aiPWalks[iii]	= structPitcher.m_Walks;
			aiPWins[iii]	= structPitcher.m_Wins;
			iPER	+=	structPitcher.m_ER;
			iPHits	+=	structPitcher.m_Hits;
			iPHR	+=	structPitcher.m_HomeRuns;
			dTemp	=	atof(structPitcher.m_IP);
			dIP		+=	dTemp;
			iPLoss	+=	structPitcher.m_Loss;
			iPSaves	+=	structPitcher.m_Saves;
			iPStarts +=	structPitcher.m_Starts;
			iPK		+=	structPitcher.m_Strikeouts;
			iPWalks	+=	structPitcher.m_Walks;
			iPWins	+=	structPitcher.m_Wins;

			if (adIP[iii] == 0)
			{
				adERA[iii]	= 0.0f;
				adTRG[iii]	= 0.0f;
				dERA	+= 0.0f;
				dTRG	+= 0.0f;
			}
			else
			{
				adERA[iii]	= (float)(structPitcher.m_ER*9)/adIP[iii];
				adTRG[iii]	= (float)((structPitcher.m_Hits+structPitcher.m_Walks)*9)/adIP[iii];
				dERA	= (double)(iPER*9)/dIP;
				dTRG	= (double)((iPHits+iPWalks)*9)/dIP;
			}
			iii++;
		}

		adTERA[iarraySize]	= (float)dERA;	// Team ERA for latter sorting
		afTBA[iarraySize]	= fBA;	// Team Batting Average for latter sorting
		sprintf_s(HTMLData,"%1.3f",fBA);
		strTemp = HTMLData;
		strAVG  = strTemp.Right(4);
		sprintf_s(HTMLData,"%1.3f",fSLG);
		strTemp = HTMLData;
		strSLG  = strTemp.Right(4);
		sprintf_s(HTMLData,"%1.3f",fOBP);
		strTemp = HTMLData;
		strOBP  = strTemp.Right(4);
		sprintf_s(HTMLData,"%s %.15s %s %s %s %5i %4i %5i %4i %4i %4i %3i %4i %4i\n",
			strShortTeamName,strTeamName,strAVG,strSLG,strOBP,iAB,iRuns,iHits,iRBI,
			i2B,i3B,iHR,iStolenBase,iCS);
		strTeamData = HTMLData;
		cstrTeamData.Add(strTeamData);
		sprintf_s(HTMLData,"%5.2f",dERA);
		strTemp = HTMLData;
		strERA  = strTemp;
		sprintf_s(HTMLData,"%4.1f",dTRG);
		strTemp = HTMLData;
		strTRG  = strTemp;
		sprintf_s(HTMLData,"%6.1f",dIP);
		strTemp = HTMLData;
		strIP  = strTemp;
		sprintf_s(HTMLData,"%s %.15s %5s %4s   %3i   %3i %6s %5i %4i %3i  %4i %4i\n",
			strShortTeamName,strTeamName,strERA,strTRG,iPWins,iPLoss,strIP,iPHits,
			iPER,iPHR,iPWalks,iPK);
		strTeamData = HTMLData;
		cstrTeamPData.Add(strTeamData);

		iTAB		+= iAB;
		iTRuns		+= iRuns;
		iTHits		+= iHits;
		iTRBI		+= iRBI;
		iT2B		+= i2B;
		iT3B		+= i3B;
		iTHR		+= iHR;
		iTStolenBase += iStolenBase;
		iTCS		+= iCS;
		iTWalk		+= iWalk;
		iTSacrifice	+= iSacrifice;
		iTROE		+= iROE;
		if (iTAB == 0)
		{
			fTBA  = 0.0f;
			fTSLG = 0.0f;
			fTOBP = 0.0f;
		}
		else
		{
			fTBA  = (float)iTHits/iTAB;
			fTSLG = (float)((iTHits-(iT2B+iT3B+iTHR))+(2*iT2B)+(3*iT3B)+(4*iTHR))/(iTAB);
			fTOBP = (float)(iTHits+iTWalk+iTROE+iTSacrifice+iTStolenBase)/(iTAB+iTWalk+iTROE+iTSacrifice+iTStolenBase);
		}

		iTPER		+= iPER;
		iTPHits		+= iPHits;
		iTPHR		+= iPHR;
		dTIP		+= dIP;
		iTPLoss		+= iPLoss;
		iTPSaves	+= iPSaves;
		iTPStarts	+= iPStarts;
		iTPK		+= iPK;
		iTPWalks	+= iPWalks;
		iTPWins		+= iPWins;
		if (dTIP == 0)
		{
			dTERA = 0.0f;
			dTTRG = 0.0f;
		}
		else
		{
			dTERA = (float)(iTPER*9)/dTIP;
			dTTRG = (float)((iTPHits+iTPWalks)*9)/dTIP;
		}
	}	// End processing of all teams in division
	// Open file and create headers
	strLeagueName.TrimRight();
	strConferenceName.TrimRight();
	strDivisionName.TrimRight();
	if (!strcmp("NULL",strDivisionName.Left(4)))
	{
		if (!strcmp("NULL",strConferenceName.Left(4)))
		{
			// Create file name only with League name
			HTMLFile.Open(arrayFileNames->GetAt(0).Left(8)+"\\"+strLeagueName+".htm", CFile::modeWrite|CFile::modeCreate);
		}
		else
		{
			// Create file name with League name and Conference name
			HTMLFile.Open(arrayFileNames->GetAt(0).Left(8)+"\\"+strLeagueName+strConferenceName+".htm", CFile::modeWrite|CFile::modeCreate);
		}
	}
	else
	{
		if (!strcmp("NULL",strConferenceName.Left(4)))
		{
			// Create file name with League name and Division name
			HTMLFile.Open(arrayFileNames->GetAt(0).Left(8)+"\\"+strLeagueName+strDivisionName+".htm", CFile::modeWrite|CFile::modeCreate);
		}
		else
		{
			// Create file name with League name, Conference name, and Division name
			HTMLFile.Open(arrayFileNames->GetAt(0).Left(8)+"\\"+strLeagueName+strConferenceName+strDivisionName+".htm", CFile::modeWrite|CFile::modeCreate);
		}
	}
	sprintf_s(HTMLData,"<HTML>\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<HEAD>\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<TITLE>%s</TITLE>\n", strLeagueName);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"</HEAD>\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());

	sprintf_s(HTMLData,"<BODY TEXT=%s LINK=%s VLINK=%s BGCOLOR=%s BACKGROUND=\"%s\">\n",
		strTextColor,strLinkColor,strVLinkColor,strBGColor,strBackgroundPicture);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<A href=\"%s\">Back</A><BR><BR>\n",strIndex);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"<H2>League: %s</H2>\n", strLeagueName);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	if (strcmp("NULL",strConferenceName.Left(4)))
	{
		sprintf_s(HTMLData,"Conference: <B>%s</B><BR>\n", strConferenceName);
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	}
	if (strcmp("NULL",strDivisionName.Left(4)))
	{
		sprintf_s(HTMLData,"Division: <B>%s</B><BR>\n", strDivisionName);
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	}
	sprintf_s(HTMLData,"<PRE><B>\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"BATTING\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"    TEAM             AVG  SLG  OBP    AB    R     H  RBI   2B   3B  HR   SB   CS\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	for (i=0; i<arrayFileNamesSize-1; i++)
	{
		for (j=0; j<arrayFileNamesSize-1; j++)
		{
			if ( afTBA[aiTCount[j]] < afTBA[aiTCount[j+1]])
			{
				tiCount = aiTCount[j];
				aiTCount[j] = aiTCount[j+1];
				aiTCount[j+1] = tiCount;
			}
		}
	}
	for (iarraySize=0; iarraySize < arrayFileNamesSize; iarraySize++)
	{
		strTemp = cstrTeamData.GetAt(aiTCount[iarraySize]);
		HTMLFile.Write(strTemp,strTemp.GetLength());
	}
	sprintf_s(HTMLData,"--- --------------- ---- ---- ---- ----- ---- ----- ---- ---- ---- --- ---- ----\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"%1.3f",fTBA);
	strTemp = HTMLData;
	strAVG  = strTemp.Right(4);
	sprintf_s(HTMLData,"%1.3f",fTSLG);
	strTemp = HTMLData;
	strSLG  = strTemp.Right(4);
	sprintf_s(HTMLData,"%1.3f",fTOBP);
	strTemp = HTMLData;
	strOBP  = strTemp.Right(4);
	sprintf_s(HTMLData,"LEAGUE TOTALS       %s %s %s %5i %4i %5i %4i %4i %4i %3i %4i %4i\n",
			strAVG,strSLG,strOBP,iTAB,iTRuns,iTHits,iTRBI,
			iT2B,iT3B,iTHR,iTStolenBase,iTCS);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());

	sprintf_s(HTMLData,"\nPITCHING\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"    TEAM             ERA   TRG  Wins  Loss     IP  Hits   ER  HR Walks    K\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	for (i=0; i<arrayFileNamesSize-1; i++)
	{
		for (j=0; j<arrayFileNamesSize-1; j++)
		{
			if ( adTERA[aiTCount[j]] > adTERA[aiTCount[j+1]])
			{
				tiCount = aiTCount[j];
				aiTCount[j] = aiTCount[j+1];
				aiTCount[j+1] = tiCount;
			}
		}
	}
	for (iarraySize=0; iarraySize < arrayFileNamesSize; iarraySize++)
	{
		strTemp = cstrTeamPData.GetAt(aiTCount[iarraySize]);
		HTMLFile.Write(strTemp,strTemp.GetLength());
	}
	sprintf_s(HTMLData,"--- --------------- ----- ----   ---   --- ------ ----- ---- ---  ---- ----\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"%5.2f",dTERA);
	strTemp = HTMLData;
	strERA  = strTemp;
	sprintf_s(HTMLData,"%4.1f",dTTRG);
	strTemp = HTMLData;
	strTRG  = strTemp.Right(4);
	sprintf_s(HTMLData,"%6.1f",dTIP);
	strTemp = HTMLData;
	strIP  = strTemp;
	sprintf_s(HTMLData,"LEAGUE TOTALS       %5s %4s   %3i   %3i %6s %5i %4i %3i  %4i %4i\n\n",
		strERA,strTRG,iTPWins,iTPLoss,strIP,iTPHits,iTPER,iTPHR,iTPWalks,iTPK);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());

	cstr1.RemoveAll();
	cstr2.RemoveAll();
	cstr3.RemoveAll();
	// Sort at bats
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( aiAB[aiCount[j]] < aiAB[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiAB[aiCount[i]] == aiAB[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiAB[aiCount[i]]);
			cstr1.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s %5i", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),aiAB[aiCount[i]]);
			cstr1.Add(HTMLData);
		}
	}
	// Sort runs
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( aiRuns[aiCount[j]] < aiRuns[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiRuns[aiCount[i]] == aiRuns[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiRuns[aiCount[i]]);
			cstr2.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),aiRuns[aiCount[i]]);
			cstr2.Add(HTMLData);
		}
	}
	// Sort Hits
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( aiHits[aiCount[j]] < aiHits[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiHits[aiCount[i]] == aiHits[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiHits[aiCount[i]]);
			cstr3.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s %5i\n", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),aiHits[aiCount[i]]);
			cstr3.Add(HTMLData);
		}
	}
//	                    00000000011111111112222222222333333333344444444445555555555666666666677777777778
//	                    12345678901234567890123456789012345678901234567890123456789012345678901234567890
	sprintf_s(HTMLData,"\nAt Bats                    Runs                       Hits\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	getSize1 = cstr1.GetSize();
	getSize2 = cstr2.GetSize();
	getSize3 = cstr3.GetSize();
	getSizeMax = getSize1;
	if (getSizeMax < getSize2 )
	{
		getSizeMax = getSize2;
	}
	if (getSizeMax < getSize3 )
	{
		getSizeMax = getSize3;
	}
	if (getSize1 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize1;i++)
			cstr1.Add(str20Blank+str20Blank);
	}
	if (getSize2 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize2;i++)
			cstr2.Add(str20Blank+str20Blank);
	}
	if (getSize3 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize3;i++)
			cstr3.Add(str20Blank+str20Blank);
	}
	for (i=0; i < getSizeMax;i++)
	{
		sprintf_s(HTMLData,"%.26s %.26s %.26s\n",cstr1.GetAt(i),cstr2.GetAt(i),cstr3.GetAt(i));
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	}
	cstr1.RemoveAll();
	cstr2.RemoveAll();
	cstr3.RemoveAll();

	// Sort RBI
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( aiRBI[aiCount[j]] < aiRBI[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiRBI[aiCount[i]] == aiRBI[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiRBI[aiCount[i]]);
			cstr1.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),aiRBI[aiCount[i]]);
			cstr1.Add(HTMLData);
		}
	}
	// Sort Batting Averages
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( afBA[aiCount[j]] < afBA[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (afBA[aiCount[i]] == afBA[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH     %1.3f", afBA[aiCount[i]]);
			cstr2.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s %1.3f", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),afBA[aiCount[i]]);
			cstr2.Add(HTMLData);
		}
	}
	// Sort Slugging Percentage
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( afSLG[aiCount[j]] < afSLG[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (afSLG[aiCount[i]] == afSLG[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH     %1.3f", afSLG[aiCount[i]]);
			cstr3.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s %1.3f", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),afSLG[aiCount[i]]);
			cstr3.Add(HTMLData);
		}
	}
//	                    00000000011111111112222222222333333333344444444445555555555666666666677777777778
//	                    12345678901234567890123456789012345678901234567890123456789012345678901234567890
	sprintf_s(HTMLData,"\nRBI's                      Batting Averages           Slugging Percentages\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	getSize1 = cstr1.GetSize();
	getSize2 = cstr2.GetSize();
	getSize3 = cstr3.GetSize();
	getSizeMax = getSize1;
	if (getSizeMax < getSize2 )
	{
		getSizeMax = getSize2;
	}
	if (getSizeMax < getSize3 )
	{
		getSizeMax = getSize3;
	}
	if (getSize1 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize1;i++)
			cstr1.Add(str20Blank+str20Blank);
	}
	if (getSize2 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize2;i++)
			cstr2.Add(str20Blank+str20Blank);
	}
	if (getSize3 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize3;i++)
			cstr3.Add(str20Blank+str20Blank);
	}
	for (i=0; i < getSizeMax;i++)
	{
		sprintf_s(HTMLData,"%.26s %.26s %.26s\n",cstr1.GetAt(i),cstr2.GetAt(i),cstr3.GetAt(i));
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	}
	cstr1.RemoveAll();
	cstr2.RemoveAll();
	cstr3.RemoveAll();

	// Sort On Base Percentage
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( afOBP[aiCount[j]] < afOBP[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (afOBP[aiCount[i]] == afOBP[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH     %1.3f", afOBP[aiCount[i]]);
			cstr1.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s %1.3f", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),afOBP[aiCount[i]]);
			cstr1.Add(HTMLData);
		}
	}
	// Sort Doubles
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( ai2B[aiCount[j]] < ai2B[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (ai2B[aiCount[i]] == ai2B[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", ai2B[aiCount[i]]);
			cstr2.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),ai2B[aiCount[i]]);
			cstr2.Add(HTMLData);
		}
	}
	// Sort Triples
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( ai3B[aiCount[j]] < ai3B[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (ai3B[aiCount[i]] == ai3B[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", ai3B[aiCount[i]]);
			cstr3.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),ai3B[aiCount[i]]);
			cstr3.Add(HTMLData);
		}
	}
//	                    00000000011111111112222222222333333333344444444445555555555666666666677777777778
//	                    12345678901234567890123456789012345678901234567890123456789012345678901234567890
	sprintf_s(HTMLData,"\nOn Base Percentage         Doubles                    Triples\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	getSize1 = cstr1.GetSize();
	getSize2 = cstr2.GetSize();
	getSize3 = cstr3.GetSize();
	getSizeMax = getSize1;
	if (getSizeMax < getSize2 )
	{
		getSizeMax = getSize2;
	}
	if (getSizeMax < getSize3 )
	{
		getSizeMax = getSize3;
	}
	if (getSize1 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize1;i++)
			cstr1.Add(str20Blank+str20Blank);
	}
	if (getSize2 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize2;i++)
			cstr2.Add(str20Blank+str20Blank);
	}
	if (getSize3 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize3;i++)
			cstr3.Add(str20Blank+str20Blank);
	}
	for (i=0; i < getSizeMax;i++)
	{
		sprintf_s(HTMLData,"%.26s %.26s %.26s\n",cstr1.GetAt(i),cstr2.GetAt(i),cstr3.GetAt(i));
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	}
	cstr1.RemoveAll();
	cstr2.RemoveAll();
	cstr3.RemoveAll();

	// Sort Home Runs
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( aiHR[aiCount[j]] < aiHR[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiHR[aiCount[i]] == aiHR[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiHR[aiCount[i]]);
			cstr1.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s   %3i", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),aiHR[aiCount[i]]);
			cstr1.Add(HTMLData);
		}
	}
	// Sort StolenBases
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( aiStolenBase[aiCount[j]] < aiStolenBase[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiStolenBase[aiCount[i]] == aiStolenBase[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiStolenBase[aiCount[i]]);
			cstr2.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),aiStolenBase[aiCount[i]]);
			cstr2.Add(HTMLData);
		}
	}
	// Sort Caught Stealing
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( aiCS[aiCount[j]] < aiCS[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiCS[aiCount[i]] == aiCS[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiCS[aiCount[i]]);
			cstr3.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),aiCS[aiCount[i]]);
			cstr3.Add(HTMLData);
		}
	}
//	                    00000000011111111112222222222333333333344444444445555555555666666666677777777778
//	                    12345678901234567890123456789012345678901234567890123456789012345678901234567890
	sprintf_s(HTMLData,"\nHome Runs                  Stolen Basses              Caught Stealing\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	getSize1 = cstr1.GetSize();
	getSize2 = cstr2.GetSize();
	getSize3 = cstr3.GetSize();
	getSizeMax = getSize1;
	if (getSizeMax < getSize2 )
	{
		getSizeMax = getSize2;
	}
	if (getSizeMax < getSize3 )
	{
		getSizeMax = getSize3;
	}
	if (getSize1 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize1;i++)
			cstr1.Add(str20Blank+str20Blank);
	}
	if (getSize2 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize2;i++)
			cstr2.Add(str20Blank+str20Blank);
	}
	if (getSize3 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize3;i++)
			cstr3.Add(str20Blank+str20Blank);
	}
	for (i=0; i < getSizeMax;i++)
	{
		sprintf_s(HTMLData,"%.26s %.26s %.26s\n",cstr1.GetAt(i),cstr2.GetAt(i),cstr3.GetAt(i));
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	}
	cstr1.RemoveAll();
	cstr2.RemoveAll();
	cstr3.RemoveAll();

	// Sort Strike Outs
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( aiStrikeOut[aiCount[j]] < aiStrikeOut[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiStrikeOut[aiCount[i]] == aiStrikeOut[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiStrikeOut[aiCount[i]]);
			cstr1.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),aiStrikeOut[aiCount[i]]);
			cstr1.Add(HTMLData);
		}
	}
	// Sort Walks
	for (i=0; i<totCount-1; i++)
	{
		for (j=0; j<totCount-1; j++)
		{
			if ( aiWalk[aiCount[j]] < aiWalk[aiCount[j+1]])
			{
				tiCount = aiCount[j];
				aiCount[j] = aiCount[j+1];
				aiCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiWalk[aiCount[i]] == aiWalk[aiCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiWalk[aiCount[i]]);
			cstr2.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamName.GetAt(aiCount[i]), cstrPlayerName.GetAt(aiCount[i]),aiWalk[aiCount[i]]);
			cstr2.Add(HTMLData);
		}
	}
	// Earned Runs
	for (i=0; i<totPCount-1; i++)
	{
		for (j=0; j<totPCount-1; j++)
		{
			if ( aiPER[aiPCount[j]] < aiPER[aiPCount[j+1]])
			{
				tiCount = aiPCount[j];
				aiPCount[j] = aiPCount[j+1];
				aiPCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiPER[aiPCount[i]] == aiPER[aiPCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiPER[aiPCount[i]]);
			cstr3.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamNameP.GetAt(aiPCount[i]), cstrPitcherName.GetAt(aiPCount[i]),aiPER[aiPCount[i]]);
			cstr3.Add(HTMLData);
		}
	}
//	                    00000000011111111112222222222333333333344444444445555555555666666666677777777778
//	                    12345678901234567890123456789012345678901234567890123456789012345678901234567890
	sprintf_s(HTMLData,"\nStrike Outs                Walks                      Earned Runs\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	getSize1 = cstr1.GetSize();
	getSize2 = cstr2.GetSize();
	getSize3 = cstr3.GetSize();
	getSizeMax = getSize1;
	if (getSizeMax < getSize2 )
	{
		getSizeMax = getSize2;
	}
	if (getSizeMax < getSize3 )
	{
		getSizeMax = getSize3;
	}
	if (getSize1 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize1;i++)
			cstr1.Add(str20Blank+str20Blank);
	}
	if (getSize2 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize2;i++)
			cstr2.Add(str20Blank+str20Blank);
	}
	if (getSize3 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize3;i++)
			cstr3.Add(str20Blank+str20Blank);
	}
	for (i=0; i < getSizeMax;i++)
	{
		sprintf_s(HTMLData,"%.26s %.26s %.26s\n",cstr1.GetAt(i),cstr2.GetAt(i),cstr3.GetAt(i));
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	}
	cstr1.RemoveAll();
	cstr2.RemoveAll();
	cstr3.RemoveAll();

	// Earned Run Average
	for (i=0; i<totPCount-1; i++)
	{
		for (j=0; j<totPCount-1; j++)
		{
			if ( adIP[aiPCount[j]] < adIP[aiPCount[j+1]])
			{
				tiCount = aiPCount[j];
				aiPCount[j] = aiPCount[j+1];
				aiPCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<totPCount-1; i++)
	{
		for (j=0; j<totPCount-1; j++)
		{
			if ( adERA[aiPCount[j]] > adERA[aiPCount[j+1]])
			{
				tiCount = aiPCount[j];
				aiPCount[j] = aiPCount[j+1];
				aiPCount[j+1] = tiCount;
			}
		}
	}
	cstrTemp1.RemoveAll();
	cstrTemp2.RemoveAll();
	cstrTemp3.RemoveAll();
	for (i=0; i<totPCount; i++)
	{
		if ( adERA[aiPCount[i]] != 0 )
		{
			cstrTemp1.Add(cstrShortTeamNameP.GetAt(aiPCount[i]));
			cstrTemp2.Add(cstrPitcherName.GetAt(aiPCount[i]));
			sprintf_s(HTMLData,"%5.2f",adERA[aiPCount[i]]);
			cstrTemp3.Add(HTMLData);
		}
	}
	// if ERA is all zeros, then fill array with zeros
	if ( !cstrTemp3.GetSize() )
	{
		for (i=0; i<m_StatCount+1; i++)
		{
			sprintf_s(HTMLData,"%5.2f",adERA[aiPCount[i]]);
			cstrTemp3.Add(HTMLData);
		}
	}

	for (i=0; i<m_StatCount; i++)
	{
		if( (!strcmp(cstrTemp3.GetAt(i), cstrTemp3.GetAt(m_StatCount))) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH     %.5s", cstrTemp3.GetAt(i));
			cstr1.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s %.5s", cstrTemp1.GetAt(i), cstrTemp2.GetAt(i),cstrTemp3.GetAt(i));
			cstr1.Add(HTMLData);
		}
	}
	// Innings Pitched
	for (i=0; i<totPCount-1; i++)
	{
		for (j=0; j<totPCount-1; j++)
		{
			if ( adIP[aiPCount[j]] < adIP[aiPCount[j+1]])
			{
				tiCount = aiPCount[j];
				aiPCount[j] = aiPCount[j+1];
				aiPCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (adIP[aiPCount[i]] == adIP[aiPCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4.1f", adIP[aiPCount[i]]);
			cstr2.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4.1f", cstrShortTeamNameP.GetAt(aiPCount[i]), cstrPitcherName.GetAt(aiPCount[i]),adIP[aiPCount[i]]);
			cstr2.Add(HTMLData);
		}
	}
	// Hits
	for (i=0; i<totPCount-1; i++)
	{
		for (j=0; j<totPCount-1; j++)
		{
			if ( aiPHits[aiPCount[j]] < aiPHits[aiPCount[j+1]])
			{
				tiCount = aiPCount[j];
				aiPCount[j] = aiPCount[j+1];
				aiPCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiPHits[aiPCount[i]] == aiPHits[aiPCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiPHits[aiPCount[i]]);
			cstr3.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamNameP.GetAt(aiPCount[i]), cstrPitcherName.GetAt(aiPCount[i]),aiPHits[aiPCount[i]]);
			cstr3.Add(HTMLData);
		}
	}
//	                    00000000011111111112222222222333333333344444444445555555555666666666677777777778
//	                    12345678901234567890123456789012345678901234567890123456789012345678901234567890
	sprintf_s(HTMLData,"\nEarned Run Average         Innings Pitched            Hits Allowed\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	getSize1 = cstr1.GetSize();
	getSize2 = cstr2.GetSize();
	getSize3 = cstr3.GetSize();
	getSizeMax = getSize1;
	if (getSizeMax < getSize2 )
	{
		getSizeMax = getSize2;
	}
	if (getSizeMax < getSize3 )
	{
		getSizeMax = getSize3;
	}
	if (getSize1 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize1;i++)
			cstr1.Add(str20Blank+str20Blank);
	}
	if (getSize2 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize2;i++)
			cstr2.Add(str20Blank+str20Blank);
	}
	if (getSize3 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize3;i++)
			cstr3.Add(str20Blank+str20Blank);
	}
	for (i=0; i < getSizeMax;i++)
	{
		sprintf_s(HTMLData,"%.26s %.26s %.26s\n",cstr1.GetAt(i),cstr2.GetAt(i),cstr3.GetAt(i));
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	}
	cstr1.RemoveAll();
	cstr2.RemoveAll();
	cstr3.RemoveAll();

	// TRG
	for (i=0; i<totPCount-1; i++)
	{
		for (j=0; j<totPCount-1; j++)
		{
			if ( adTRG[aiPCount[j]] > adTRG[aiPCount[j+1]])
			{
				tiCount = aiPCount[j];
				aiPCount[j] = aiPCount[j+1];
				aiPCount[j+1] = tiCount;
			}
		}
	}
	cstrTemp1.RemoveAll();
	cstrTemp2.RemoveAll();
	cstrTemp3.RemoveAll();
	for (i=0; i<totPCount; i++)
	{
		if ( adTRG[aiPCount[i]] != 0)
		{
			cstrTemp1.Add(cstrShortTeamNameP.GetAt(aiPCount[i]));
			cstrTemp2.Add(cstrPitcherName.GetAt(aiPCount[i]));
			sprintf_s(HTMLData,"%4.1f",adTRG[aiPCount[i]]);
			cstrTemp3.Add(HTMLData);
		}
	}
	// if TRG is all zeros, then fill array with zeros
	if ( !cstrTemp3.GetSize() )
	{
		for (i=0; i<m_StatCount+1; i++)
		{
			sprintf_s(HTMLData,"%5.2f",adERA[aiPCount[i]]);
			cstrTemp3.Add(HTMLData);
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (!strcmp(cstrTemp3.GetAt(i), cstrTemp3.GetAt(m_StatCount))) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %.4s", cstrTemp3.GetAt(i));
			cstr1.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %.4s", cstrTemp1.GetAt(i), cstrTemp2.GetAt(i),cstrTemp3.GetAt(i));
			cstr1.Add(HTMLData);
		}
	}
	// Walks
	for (i=0; i<totPCount-1; i++)
	{
		for (j=0; j<totPCount-1; j++)
		{
			if ( aiPWalks[aiPCount[j]] < aiPWalks[aiPCount[j+1]])
			{
				tiCount = aiPCount[j];
				aiPCount[j] = aiPCount[j+1];
				aiPCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiPWalks[aiPCount[i]] == aiPWalks[aiPCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiPWalks[aiPCount[i]]);
			cstr2.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamNameP.GetAt(aiPCount[i]), cstrPitcherName.GetAt(aiPCount[i]),aiPWalks[aiPCount[i]]);
			cstr2.Add(HTMLData);
		}
	}
	// Strikeouts
	for (i=0; i<totPCount-1; i++)
	{
		for (j=0; j<totPCount-1; j++)
		{
			if ( aiPK[aiPCount[j]] < aiPK[aiPCount[j+1]])
			{
				tiCount = aiPCount[j];
				aiPCount[j] = aiPCount[j+1];
				aiPCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiPK[aiPCount[i]] == aiPK[aiPCount[6]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiPK[aiPCount[i]]);
			cstr3.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamNameP.GetAt(aiPCount[i]), cstrPitcherName.GetAt(aiPCount[i]),aiPK[aiPCount[i]]);
			cstr3.Add(HTMLData);
		}
	}
//	                    00000000011111111112222222222333333333344444444445555555555666666666677777777778
//	                    12345678901234567890123456789012345678901234567890123456789012345678901234567890
	sprintf_s(HTMLData,"\nTRG                        Walks Allowed              Strikeouts\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	getSize1 = cstr1.GetSize();
	getSize2 = cstr2.GetSize();
	getSize3 = cstr3.GetSize();
	getSizeMax = getSize1;
	if (getSizeMax < getSize2 )
	{
		getSizeMax = getSize2;
	}
	if (getSizeMax < getSize3 )
	{
		getSizeMax = getSize3;
	}
	if (getSize1 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize1;i++)
			cstr1.Add(str20Blank+str20Blank);
	}
	if (getSize2 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize2;i++)
			cstr2.Add(str20Blank+str20Blank);
	}
	if (getSize3 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize3;i++)
			cstr3.Add(str20Blank+str20Blank);
	}
	for (i=0; i < getSizeMax;i++)
	{
		sprintf_s(HTMLData,"%.26s %.26s %.26s\n",cstr1.GetAt(i),cstr2.GetAt(i),cstr3.GetAt(i));
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	}
	cstr1.RemoveAll();
	cstr2.RemoveAll();
	cstr3.RemoveAll();

	// Wins
	for (i=0; i<totPCount-1; i++)
	{
		for (j=0; j<totPCount-1; j++)
		{
			if ( aiPWins[aiPCount[j]] < aiPWins[aiPCount[j+1]])
			{
				tiCount = aiPCount[j];
				aiPCount[j] = aiPCount[j+1];
				aiPCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiPWins[aiPCount[i]] == aiPWins[aiPCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiPWins[aiPCount[i]]);
			cstr1.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamNameP.GetAt(aiPCount[i]), cstrPitcherName.GetAt(aiPCount[i]),aiPWins[aiPCount[i]]);
			cstr1.Add(HTMLData);
		}
	}
	// Loss
	for (i=0; i<totPCount-1; i++)
	{
		for (j=0; j<totPCount-1; j++)
		{
			if ( aiPLoss[aiPCount[j]] < aiPLoss[aiPCount[j+1]])
			{
				tiCount = aiPCount[j];
				aiPCount[j] = aiPCount[j+1];
				aiPCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiPLoss[aiPCount[i]] == aiPLoss[aiPCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiPLoss[aiPCount[i]]);
			cstr2.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamNameP.GetAt(aiPCount[i]), cstrPitcherName.GetAt(aiPCount[i]),aiPLoss[aiPCount[i]]);
			cstr2.Add(HTMLData);
		}
	}
	// Starts
	for (i=0; i<totPCount-1; i++)
	{
		for (j=0; j<totPCount-1; j++)
		{
			if ( aiPStarts[aiPCount[j]] < aiPStarts[aiPCount[j+1]])
			{
				tiCount = aiPCount[j];
				aiPCount[j] = aiPCount[j+1];
				aiPCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiPStarts[aiPCount[i]] == aiPStarts[aiPCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiPStarts[aiPCount[i]]);
			cstr3.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamNameP.GetAt(aiPCount[i]), cstrPitcherName.GetAt(aiPCount[i]),aiPStarts[aiPCount[i]]);
			cstr3.Add(HTMLData);
		}
	}
//	                    00000000011111111112222222222333333333344444444445555555555666666666677777777778
//	                    12345678901234567890123456789012345678901234567890123456789012345678901234567890
	sprintf_s(HTMLData,"\nWins                       Loss                       Starts\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	getSize1 = cstr1.GetSize();
	getSize2 = cstr2.GetSize();
	getSize3 = cstr3.GetSize();
	getSizeMax = getSize1;
	if (getSizeMax < getSize2 )
	{
		getSizeMax = getSize2;
	}
	if (getSizeMax < getSize3 )
	{
		getSizeMax = getSize3;
	}
	if (getSize1 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize1;i++)
			cstr1.Add(str20Blank+str20Blank);
	}
	if (getSize2 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize2;i++)
			cstr2.Add(str20Blank+str20Blank);
	}
	if (getSize3 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize3;i++)
			cstr3.Add(str20Blank+str20Blank);
	}
	for (i=0; i < getSizeMax;i++)
	{
		sprintf_s(HTMLData,"%.26s %.26s %.26s\n",cstr1.GetAt(i),cstr2.GetAt(i),cstr3.GetAt(i));
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	}
	cstr1.RemoveAll();
	cstr2.RemoveAll();
	cstr3.RemoveAll();

	// Saves
	for (i=0; i<totPCount-1; i++)
	{
		for (j=0; j<totPCount-1; j++)
		{
			if ( aiPSaves[aiPCount[j]] < aiPSaves[aiPCount[j+1]])
			{
				tiCount = aiPCount[j];
				aiPCount[j] = aiPCount[j+1];
				aiPCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiPSaves[aiPCount[i]] == aiPSaves[aiPCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiPSaves[aiPCount[i]]);
			cstr1.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamNameP.GetAt(aiPCount[i]), cstrPitcherName.GetAt(aiPCount[i]),aiPSaves[aiPCount[i]]);
			cstr1.Add(HTMLData);
		}
	}
	// Homeruns
	for (i=0; i<totPCount-1; i++)
	{
		for (j=0; j<totPCount-1; j++)
		{
			if ( aiPHR[aiPCount[j]] < aiPHR[aiPCount[j+1]])
			{
				tiCount = aiPCount[j];
				aiPCount[j] = aiPCount[j+1];
				aiPCount[j+1] = tiCount;
			}
		}
	}
	for (i=0; i<m_StatCount; i++)
	{
		if( (aiPHR[aiPCount[i]] == aiPHR[aiPCount[m_StatCount]]) )
		{
			sprintf_s(HTMLData,"OTHERS TIED WITH      %4i", aiPHR[aiPCount[i]]);
			cstr2.Add(HTMLData);
			break;
		}
		else
		{
			sprintf_s(HTMLData,"%s %.16s  %4i", cstrShortTeamNameP.GetAt(aiPCount[i]), cstrPitcherName.GetAt(aiPCount[i]),aiPHR[aiPCount[i]]);
			cstr2.Add(HTMLData);
		}
	}
//	                    00000000011111111112222222222333333333344444444445555555555666666666677777777778
//	                    12345678901234567890123456789012345678901234567890123456789012345678901234567890
	sprintf_s(HTMLData,"\nSaves                      HomeRuns Allowed\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	getSize1 = cstr1.GetSize();
	getSize2 = cstr2.GetSize();
	getSize3 = cstr3.GetSize();
	getSizeMax = getSize1;
	if (getSizeMax < getSize2 )
	{
		getSizeMax = getSize2;
	}
	if (getSizeMax < getSize3 )
	{
		getSizeMax = getSize3;
	}
	if (getSize1 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize1;i++)
			cstr1.Add(str20Blank+str20Blank);
	}
	if (getSize2 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize2;i++)
			cstr2.Add(str20Blank+str20Blank);
	}
	if (getSize3 < getSizeMax )
	{
		for (i=0; i<getSizeMax-getSize3;i++)
			cstr3.Add(str20Blank+str20Blank);
	}
	for (i=0; i < getSizeMax;i++)
	{
		sprintf_s(HTMLData,"%.26s %.26s %.26s\n",cstr1.GetAt(i),cstr2.GetAt(i),cstr3.GetAt(i));
		strHTMLData = HTMLData;
		HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	}
	cstr1.RemoveAll();
	cstr2.RemoveAll();
	cstr3.RemoveAll();

	sprintf_s(HTMLData,"\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	sprintf_s(HTMLData,"</B></PRE>\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());
	
    // Write the Last Updated line n the HTML file
	_strtime_s( timebuf );    
    _strdate_s( datebuf );    
	sprintf_s(HTMLData,"<BR>Last Updated on %s at %s<BR>\n",datebuf,timebuf);
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());

	sprintf_s(HTMLData,"</BODY></HTML>\n");
	strHTMLData = HTMLData;
	HTMLFile.Write(strHTMLData,strHTMLData.GetLength());

	HTMLFile.Close();

	// Free up all of the dynamic arrays
	free(aiCount);
	free(aiPCount);
	free(aiTCount);
	free(aiAB);
	free(aiRuns);
	free(aiHits);
	free(aiRBI);
	free(ai2B);
	free(ai3B);
	free(aiHR);
	free(afBA);
	free(afTBA);
	free(afSLG);
	free(afOBP);
	free(aiStolenBase);
	free(aiCS);
	free(aiStrikeOut);
	free(aiWalk);
	free(adERA);
	free(adTERA);
	free(adTRG);
	free(adIP);
	free(aiPER);
	free(aiPHits);
	free(aiPWalks);
	free(aiPK);
	free(aiPWins);
	free(aiPLoss);
	free(aiPStarts);
	free(aiPSaves);
	free(aiPHR);
}

void CBaseballDoc::OnPlayersAddEditBatters() 
{
	CString strLeagueName;
	CString strLeagueFile;
	CString strLeagueDir;
	CString strLeague;
	CString strTeam;
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
	strLeague = GetLeagues(TRUE);

	strLeagueName = strLeague.Left(30);
	if (strncmp(strLeagueName,"All",3))
	{
		strLeagueFile = strLeague.Right(12);
		strLeagueDir = strLeagueFile.Left(8);
	}
	else
	{
		strLeagueDir = "data";
	}
	strTeam = GetTeams(strLeagueDir);
	strTeamFile = strTeam.Right(12);
	strTeamName = strTeam.Left(30);
	myBattersSheet.m_FileName = strLeagueDir+"\\"+strTeamFile;
	myBattersSheet.m_TeamName = strTeamName;

	// Remove the APPLY button from the display
	myBattersSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;
	myBattersSheet.DoModal();
}

// Parse the GetLeagues() subroutine as follows:
//
//	CString strLeague;
//	CString strLeagueName;
//	CString strLeagueFile;
//	CString strLeagueDir;
//
//	strLeague = GetLeagues(TRUE);
//
//	strLeagueName = strLeague.Left(30);
//	if (strncmp(strLeagueName,"All",3))
//	{
//		strLeagueFile = strLeague.Right(12);
//		strLeagueDir = strLeagueFile.Left(8);
//	}
//	else
//	{
//		// This is the base directory
//		strLeagueDir = "data";
//	}
//
CString CBaseballDoc::GetLeagues(BOOL baseFlag)
{
	CFileFind myFileFind;
	CFile myInFile;
	BOOL bWorking;
	CStringArray arrayFileNames;
	int sortflag;
	int i;
	DlgSelLeague dlgSelLeague;
	CString strLeagueName;
	CString strTemp;
	BYTE version;
	BYTE count;
	char temp[41];

	bWorking = myFileFind.FindFile("data\\L*.dat",0);
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
			for (i=0; i<(arrayFileNames.GetSize()-1);i++)
			{
				if (arrayFileNames[i].Compare(arrayFileNames[i+1]) == 1)
				{
					strTemp = arrayFileNames[i];
					arrayFileNames[i] = arrayFileNames[i+1];
					arrayFileNames[i+1] = strTemp;
					sortflag = 1;
				}
			}
		}

		for (i=0; i<arrayFileNames.GetSize(); i++)
		{
			myInFile.Open("data\\"+arrayFileNames[i],CFile::modeRead);
			myInFile.Read(&version,sizeof(version));
			myInFile.Read(&count,sizeof(count));
			myInFile.Read(temp,30);
			myInFile.Close();
			temp[30] = NULL;
			strLeagueName = temp;
			strLeagueName = strLeagueName+"\t"+arrayFileNames[i];
			dlgSelLeague.m_arrayLeagues.Add(strLeagueName);
		}
		// If TRUE add in Base directory
		if (baseFlag == TRUE)
		{
			//           123456789012345678901234567890
			strcpy_s(temp,"All Base Teams                ");
			temp[30] = NULL;
			strLeagueName = temp;
			strLeagueName = strLeagueName+"\t"+"data";
			dlgSelLeague.m_arrayLeagues.Add(strLeagueName);
		}

		if (dlgSelLeague.DoModal() == IDOK)
		{
			strLeagueName = dlgSelLeague.m_arrayLeagues[0];
		}
	}
	else
	{
		// No Leagues found so display message
		AfxMessageBox("Could not find any Leagues files. Please create a League");
		return "";
	}
	return strLeagueName;
}

//	Parse the team names as follows:
//
//	CString strTeam;
//	CString strTeamFile;
//	CString strTeamName;
//
//	strTeam = GetTeams(strLeagueDir);
//	strTeamFile = strTeam.Right(12);
//	strTeamName = strTeam.Left(30);
//
CString CBaseballDoc::GetTeams(CString strDir)
{
	dlgSelTeam dlgSelTeam;
	BOOL bWorking;
	BYTE count;
	CFile myInFile;
	CStringArray arrayFileNames;
	int sortflag;
	int i;
	CString strTemp;
	char temp[41];
	CString strTeamName;
	CFileFind myFileFind;

	count = 0;

	bWorking = myFileFind.FindFile(strDir+"\\TB*.dat",0);
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
			for (i=0; i<(arrayFileNames.GetSize()-1);i++)
			{
				if (arrayFileNames[i].Compare(arrayFileNames[i+1]) == 1)
				{
					strTemp = arrayFileNames[i];
					arrayFileNames[i] = arrayFileNames[i+1];
					arrayFileNames[i+1] = strTemp;
					sortflag = 1;
				}
			}
		}

		for (i=0; i<arrayFileNames.GetSize(); i++)
		{
			myInFile.Open(strDir+"\\"+arrayFileNames[i],CFile::modeRead);
			myInFile.Read(&count,sizeof(count));
			myInFile.Read(temp,40);
			myInFile.Close();
			temp[40] = NULL;
			strTeamName = temp;
			strTeamName = strTeamName+"\t"+arrayFileNames[i];
			dlgSelTeam.m_arrayTeams.Add(strTeamName);
		}

		if (dlgSelTeam.DoModal() == IDOK)
		{
			strTeamName = dlgSelTeam.m_arrayTeams[0];
		}
	}
	else
	{
		// No teams found so display message
		AfxMessageBox("Could not find any Team files. Please create a team");
		return "";
	}
	return strTeamName;
}

void CBaseballDoc::OnPlayersAddEditPitchers() 
{
	CString strLeagueName;
	CString strLeagueFile;
	CString strLeagueDir;
	CString strLeague;
	CString strTeam;
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
	// For testing force to a team name
	strLeague = GetLeagues(TRUE);

	strLeagueName = strLeague.Left(30);
	if (strncmp(strLeagueName,"All",3))
	{
		strLeagueFile = strLeague.Right(12);
		strLeagueDir = strLeagueFile.Left(8);
	}
	else
	{
		strLeagueDir = "data";
	}
	strTeam = GetTeams(strLeagueDir);
	strTeamFile = "TP";
	strTeamFile += strTeam.Right(10);
	strTeamName = strTeam.Left(30);
	myPitchersSheet.m_FileName = strLeagueDir+"\\"+strTeamFile;
	myPitchersSheet.m_TeamName = strTeamName;

	// Remove the APPLY button from the display
	myPitchersSheet.m_psh.dwFlags |= PSH_NOAPPLYNOW;
	myPitchersSheet.DoModal();
}

void CBaseballDoc::OnLeaguesLeagueOptionsHTML() 
{
	CString strLeague;
	CString strLeagueName;
	CString strLeagueFile;
	CString strLeagueDir;

	// Do not retrieve the Base directory
	strLeague = GetLeagues(FALSE);

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
