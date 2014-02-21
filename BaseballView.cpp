// BaseballView.cpp : implementation of the CBaseballView class
//

#include "stdafx.h"
#include "Baseball.h"

#include "dialogs.h"
#include "BaseballDoc.h"
#include "FormA.h"
#include "FormB.h"
#include "BaseballView.h"
#include <winspool.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBaseballView

IMPLEMENT_DYNCREATE(CBaseballView, CScrollView)

BEGIN_MESSAGE_MAP(CBaseballView, CScrollView)
	//{{AFX_MSG_MAP(CBaseballView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBaseballView construction/destruction

CBaseballView::CBaseballView()
{
//	&m_FormA = new FormA();
}

CBaseballView::~CBaseballView()
{
//	delete &m_FormA;
}

BOOL CBaseballView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBaseballView drawing

void CBaseballView::OnDraw(CDC* pDC)
{
	CWnd* pmyCWnd;

	CBaseballDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
	pmyCWnd = AfxGetMainWnd();

	if (pDoc->GetNormalView())
	{
		FormA* pFormA = new FormA();
		pFormA->OnDraw(pDC, pDoc);
		delete pFormA;
	}
	if (pDoc->GetScoresheetForm()||pDoc->GetScoresheetFormXtra())
	{
		FormA* pFormA = new FormA();
		pFormA->OnDraw(pDC, pDoc);
		delete pFormA;
	}
	if (pDoc->GetStatisticsForm())
	{
		FormB* pFormB = new FormB();
		pFormB->OnDraw(pDC, pDoc);
		delete pFormB;
	}

}

/////////////////////////////////////////////////////////////////////////////
// CBaseballView printing

BOOL CBaseballView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBaseballView::OnBeginPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBaseballView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBaseballView diagnostics

#ifdef _DEBUG
void CBaseballView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CBaseballView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CBaseballDoc* CBaseballView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBaseballDoc)));
	return (CBaseballDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBaseballView message handlers

void CBaseballView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
	// TODO: Add your specialized code here and/or call the base class
	CSize sizeTotal;
	CScrollView::OnUpdate(pSender, lHint, pHint);
	// TODO: calculate the total size of this view
	CBaseballDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (pDoc->GetStatisticsForm())
	{
		sizeTotal.cx = 8500;
		sizeTotal.cy = 11000;
	}
	else
	{
		sizeTotal.cx = 11000;
		sizeTotal.cy = 8500;
	}
	SetScrollSizes(MM_HIENGLISH, sizeTotal);
}

LPDEVMODE CBaseballView::ChangeDevMode(HWND hWnd, char *pDevice)
{
   HANDLE      hPrinter;
   LPDEVMODE   pDevMode;
   DWORD       dwNeeded, dwRet;

   /* Start by opening the printer */
   if (!OpenPrinter(pDevice, &hPrinter, NULL))
       return NULL;

   /*
    * Step 1:
    * Allocate a buffer of the correct size.
    */
   dwNeeded = DocumentProperties(hWnd,
       hPrinter,       /* handle to our printer */
       pDevice,        /* Name of the printer */
       NULL,           /* Asking for size so */
       NULL,           /* these are not used. */
       0);             /* Zero returns buffer size. */
   pDevMode = (LPDEVMODE)malloc(dwNeeded);

   /*
    * Step 2:
    * Get the default DevMode for the printer and
    * modify it for our needs.
    */
   dwRet = DocumentProperties(hWnd,
       hPrinter,
       pDevice,
       pDevMode,       /* The address of the buffer to fill. */
       NULL,           /* Not using the input buffer. */
       DM_OUT_BUFFER); /* Have the output buffer filled. */
   if (dwRet != IDOK)
   {
       /* if failure, cleanup and return failure */
       free(pDevMode);
       ClosePrinter(hPrinter);
       return NULL;
   }

   /*
    * Make changes to the DevMode which are supported.
    */
	if (pDevMode->dmFields & DM_ORIENTATION)       
	{
       /* if the printer supports paper orientation, set it*/
       pDevMode->dmOrientation = DMORIENT_LANDSCAPE;       
	}
   /*
    * Step 3:
    * Merge the new settings with the old.
    * This gives the driver a chance to update any private
    * portions of the DevMode structure.
    */
   dwRet = DocumentProperties(hWnd,
       hPrinter,
       pDevice,
       pDevMode,       /* Reuse our buffer for output. */
       pDevMode,       /* Pass the driver our changes. */
       DM_IN_BUFFER |  /* Commands to Merge our changes and */
       DM_OUT_BUFFER); /* write the result. */

   /* Done with the printer */
   ClosePrinter(hPrinter);

   if (dwRet != IDOK)
   {
       /* if failure, cleanup and return failure */
       free(pDevMode);
       return NULL;
   }

   /* return the modified DevMode structure */
   return pDevMode;
}

void CBaseballView::OnPrepareDC(CDC* pDC, CPrintInfo* pInfo) 
{
	LPDEVMODE lpDevMode;
	int rc;

	// TODO: Add your specialized code here and/or call the base class
	if(pDC->IsPrinting())
	{
			LPPRINTER_INFO_1 lpPrinterInfo2 = NULL;
			DWORD dwReturned=0, dwNeeded=0;
			char* PrinterName = NULL;

			rc = EnumPrinters(PRINTER_ENUM_LOCAL
						|PRINTER_ENUM_CONNECTIONS, 
						NULL, 
						1, 
						(LPBYTE)lpPrinterInfo2,
						dwNeeded, 
						&dwNeeded, 
						&dwReturned );
        
			lpPrinterInfo2 = (LPPRINTER_INFO_1)MyAllocMem(dwNeeded);

			EnumPrinters(PRINTER_ENUM_LOCAL
						|PRINTER_ENUM_CONNECTIONS,  
						NULL,
						1, 
						(LPBYTE)lpPrinterInfo2,
						dwNeeded, 
						&dwNeeded, 
						&dwReturned );
			
	    PrinterName = (char*)lpPrinterInfo2->pName;
        lpDevMode = ChangeDevMode(m_hWnd,PrinterName);
		pDC->ResetDC(lpDevMode);
	}
	
	CScrollView::OnPrepareDC(pDC, pInfo);
}

LPVOID CBaseballView::MyAllocMem(DWORD cb)
{
	return VirtualAlloc(NULL, cb, MEM_RESERVE|MEM_COMMIT, PAGE_READWRITE);
}
