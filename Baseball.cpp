// Baseball.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "Baseball.h"

#include "MainFrm.h"
#include "ChildFrm.h"
#include "dialogs.h"
#include "BaseballDoc.h"
#include "BaseballView.h"
#include "Batter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseballApp

BEGIN_MESSAGE_MAP(CBaseballApp, CWinApp)
	//{{AFX_MSG_MAP(CBaseballApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinApp::OnFileNew)
//	ON_COMMAND(ID_FILE_OPEN, CWinApp::OnFileOpen)
	// Standard print setup command
	ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
	ON_COMMAND(ID_FILE_OPEN, &CBaseballApp::OnFileOpen)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseballApp construction

CBaseballApp::CBaseballApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBaseballApp object

CBaseballApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBaseballApp initialization

BOOL CBaseballApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	// Change the registry key under which our settings are stored.
	// You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Sunbeams and Rainbows"));
  
	LoadStdProfileSettings(5);  // Load standard INI file options (including MRU)

	// Register the application's document templates.  Document templates
	//  serve as the connection between documents, frame windows and views.

	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(
		IDR_BASEBATYPE,
		RUNTIME_CLASS(CBaseballDoc),
		RUNTIME_CLASS(CChildFrame), // custom MDI child frame
		RUNTIME_CLASS(CBaseballView));
	AddDocTemplate(pDocTemplate);

	// create main MDI Frame window
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame->LoadFrame(IDR_MAINFRAME))
		return FALSE;
	m_pMainWnd = pMainFrame;

	// Enable drag/drop open
	m_pMainWnd->DragAcceptFiles();

	// Enable DDE Execute open
	EnableShellOpen();
	RegisterShellFileTypes(FALSE);

	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

	// setup Splash window
	if (!cmdInfo.m_bRunEmbedded)
	{
		if (!m_pMainWnd->IsIconic() && cmdInfo.m_bShowSplash &&
			m_splash.Create(m_pMainWnd))
		{
			m_splash.ShowWindow(SW_SHOW);
			m_splash.UpdateWindow();
		}
		m_dwSplashTime = ::GetCurrentTime();
	}

	// Dispatch commands specified on the command line
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// The main window has been initialized, so show and update it.
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBaseballApp commands

BOOL CBaseballApp::OnIdle(LONG lCount) 
{
	// TODO: Add your specialized code here and/or call the base class
	// call base class idle first
	BOOL bResult = CWinApp::OnIdle(lCount);

	// then do our work
	if (m_splash.m_hWnd != NULL)
	{
		if (::GetCurrentTime() - m_dwSplashTime > 5000)
		{
			// timeout expired, destroy the splash window
			m_splash.DestroyWindow();
			m_pMainWnd->UpdateWindow();

			// NOTE: don't set bResult to FALSE,
			//  CWinApp::OnIdle may have returned TRUE
		}
		else
		{
			// check again later...
			bResult = TRUE;
		}
	}

	return bResult;
}

BOOL CBaseballApp::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	BOOL bResult = CWinApp::PreTranslateMessage(pMsg);

	if (m_splash.m_hWnd != NULL &&
		(pMsg->message == WM_KEYDOWN ||
		 pMsg->message == WM_SYSKEYDOWN ||
		 pMsg->message == WM_LBUTTONDOWN ||
		 pMsg->message == WM_RBUTTONDOWN ||
		 pMsg->message == WM_MBUTTONDOWN ||
		 pMsg->message == WM_NCLBUTTONDOWN ||
		 pMsg->message == WM_NCRBUTTONDOWN ||
		 pMsg->message == WM_NCMBUTTONDOWN))
	{
		m_splash.DestroyWindow();
		m_pMainWnd->UpdateWindow();
	}

	return bResult;
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CBaseballApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}


void CBaseballApp::OnFileOpen()
{
	CDatabase database;
	CString SqlString;
	CString sCatID, sCategory;
	CString sDriver = "MICROSOFT ACCESS DRIVER (*.mdb, *.accdb)";
//	CString sDriver = "MS Access Database";  // This does not work
	CString sDsn; 
//	CString sFile = "C:\\Users\\gnew\\Documents\\Baseball.accdb";
	CString sFile = "C:\\Family\\SOURCE\\C\\Strat - O - Matic - Baseball\\Baseball.accdb";
	// You must change above path if it's different
	int iRec = 0;

	// Build ODBC connection string
	sDsn.Format("ODBC;DRIVER={%s};DSN='';DBQ=%s", sDriver, sFile);
	TRY
	{
		// Open the database
		if (database.Open(NULL, false, false, sDsn))
		{

			// Allocate the recordset
			CBatter rs(&database);

			// Build the SQL statement
			SqlString = "SELECT FirstName, LastName "
				"FROM Batter";

			// Execute the query
			//rs.Open(CRecordset::snapshot, NULL, CRecordset::none);
			//rs.AddNew();
			//rs.m_FirstName = "John";
			//rs.m_LastName = "Gnew";
			//rs.Update();
			//rs.AddNew();
			//rs.m_FirstName = "Johnny";
			//rs.m_LastName = "New";
			//rs.Update();
			//rs.Close();
			//// Reset List control if there is any data
			//ResetListControl();
			//// populate Grids
			//ListView_SetExtendedListViewStyle(m_ListControl, LVS_EX_GRIDLINES);

			//// Column width and heading
			//m_ListControl.InsertColumn(0, "Emp Id", LVCFMT_LEFT, -1, 0);
			//m_ListControl.InsertColumn(1, "Emp Name", LVCFMT_LEFT, -1, 1);
			//m_ListControl.SetColumnWidth(0, 120);
			//m_ListControl.SetColumnWidth(1, 200);

			//// Loop through each record
			//while (!recset.IsEOF())
			//{
			//	// Copy each column into a variable
			//	recset.GetFieldValue("EmpID", sCatID);
			//	recset.GetFieldValue("EmpName", sCategory);

			//	// Insert values into the list control
			//	iRec = m_ListControl.InsertItem(0, sCatID, 0);
			//	m_ListControl.SetItemText(0, 1, sCategory);

			//	// goto next record
			//	recset.MoveNext();
			//}
			// Close the database
			database.Close();
		}
	}
		CATCH(CDBException, e)
	{
			// If a database exception occured, show error msg
			AfxMessageBox("Database error: " + e->m_strError);
	}
	END_CATCH;
}
